// =====================================================================================================================
//	STE DMA sound: 4-voice software mixer modelled on the Amiga game's Paula use (reverse-engineering/notes/render_sound.md 6,
//	reverse-engineering/notes/sound_ste.md). Stereo like the Amiga (channels 0+3 left, 1+2 right), SND_RATE (12517 Hz), 8-bit.
//	The DMA plays a ring buffer in loop mode; snd_mix() (once per drawn frame) fills it up to SND_LEAD bytes ahead
//	of the play position. Samples keep their native rate; every voice steps through its data at
//	rate = 3546895 / Amiga period (16.16 step = SND_STEP_K / period).
//	Volume 0..64 (Amiga); a voice at 64 plays at full scale like a Paula channel, two voices on one side are added
//	with saturation (they clip only where both are loud at the same moment).
// =====================================================================================================================

#include "snd_data.h"

#define SND_RING	16384					// bytes, L/R interleaved (~650 ms)
#define SND_VBL	((SND_RATE * 2 / 50) & ~3)		// bytes the DMA plays per VBL
#define SND_LEAD	(SND_VBL * 5)					// minimum lead over the DMA play position (see snd_mix)
#define SND_VOICES	4

struct voice_t
{
	const s8 *base;		// sample data (0 = idle)
	u16 len;			// bytes
	u16 llen;			// bytes repeated at the end when looping (len: the whole sample)
	u16 ipos, frac;		// position 16.16
	u16 istep, fstep;	// step 16.16
	s16 vol;			// 0..64
	s16 snd;			// SND_ id
	s16 prio;			// slot: 0 = high priority, 1 = low
	bool loop;
};

static voice_t g_voice[SND_VOICES];
static s8 g_snd_ring[SND_RING] __attribute__((aligned(4)));
static s8 g_snd_vt[33][256];					// [vol/2][unsigned sample] -> sample * vol / 64
static u16 g_snd_wr = 0;						// next ring byte to mix (multiple of 2)
static bool g_snd_ok = false;
static u16 g_snd_resyncs = 0, g_snd_ahead = 0;	// diagnostics: DMA overtook the writer; lead (bytes) at the last mix
static bool g_snd_paused = false;				// set by the game while it is paused

// engine sound state (FUN_12132): current / target volume, current period, period base
static s16 g_eng_vol = 0, g_eng_vol_target = 0, g_eng_per = 0x328, g_eng_per_base = 0x328;

#define SNDREG8(_a_) (*(volatile u8 *)(_a_))
#define SNDREG16(_a_) (*(volatile u16 *)(_a_))

static void snd_microwire(u16 _cmd)
{
	SNDREG16(0xFF8924) = 0x07FF;
	SNDREG16(0xFF8922) = _cmd;
	for (s16 t = 0; t < 2000 && SNDREG16(0xFF8924) != 0x07FF; t++) { }	// shifted out after ~16 us
}

static u32 snd_dma_pos()
{
	u32 a, b;
	do
	{
		a = ((u32)SNDREG8(0xFF8909) << 16) | ((u32)SNDREG8(0xFF890B) << 8) | SNDREG8(0xFF890D);
		b = ((u32)SNDREG8(0xFF8909) << 16) | ((u32)SNDREG8(0xFF890B) << 8) | SNDREG8(0xFF890D);
	} while (a != b);
	return a;
}

static void snd_init()
{
	for (s16 v = 0; v <= 32; v++)
		for (s16 u = 0; u < 256; u++)
			g_snd_vt[v][u] = (s8)(((s16)(s8)u * v) / 32);
	for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = 0;
	for (s16 i = 0; i < SND_VOICES; i++) g_voice[i].base = 0;

	u32 s = (u32)g_snd_ring, e = s + SND_RING;
	SNDREG8(0xFF8901) = 0;					// stop
	SNDREG8(0xFF8903) = (u8)(s >> 16); SNDREG8(0xFF8905) = (u8)(s >> 8); SNDREG8(0xFF8907) = (u8)s;
	SNDREG8(0xFF890F) = (u8)(e >> 16); SNDREG8(0xFF8911) = (u8)(e >> 8); SNDREG8(0xFF8913) = (u8)e;
	SNDREG8(0xFF8921) = (SND_RATE == 6258) ? 0x00 : (SND_RATE == 25033) ? 0x02 : 0x01;	// stereo + rate
	// LMC1992: master 0 dB, left/right 0 dB, flat tone, YM mixed in
	snd_microwire(0x0400 | (3 << 6) | 40);
	snd_microwire(0x0400 | (5 << 6) | 20);
	snd_microwire(0x0400 | (4 << 6) | 20);
	snd_microwire(0x0400 | (2 << 6) | 6);
	snd_microwire(0x0400 | (1 << 6) | 6);
	snd_microwire(0x0400 | (0 << 6) | 1);
	SNDREG8(0xFF8901) = 3;					// play, loop
	g_snd_wr = SND_LEAD / 2;
	g_snd_ok = true;
}

static void snd_close()
{
	if (!g_snd_ok) return;
	SNDREG8(0xFF8901) = 0;
	g_snd_ok = false;
}

// start / update a voice (same sound: only period and volume change; different: restart)
static bool g_snd_off = false;				// [25447] Ctrl+S: sound switched off (as the original)
static void snd_voice(s16 _ch, s16 _snd, s16 _vol, u16 _period, bool _loop, s16 _prio)
{
	if (g_snd_off) return;
	voice_t &v = g_voice[_ch];
	u32 step = (SND_STEP_K / _period) << c_snd_shift[_snd];		// (oversampled data: proportionally larger step)
	if (!v.base || v.snd != _snd)
	{
		v.base = c_snd_data[_snd];
		v.len = c_snd_len[_snd];
		v.llen = v.len;
		v.ipos = 0; v.frac = 0;
		v.snd = _snd;
	}
	v.istep = (u16)(step >> 16);
	v.fstep = (u16)step;
	v.vol = _vol < 0 ? 0 : _vol > 64 ? 64 : _vol;
	v.loop = _loop;
	v.prio = _prio;
}

static void snd_stop(s16 _ch) { g_voice[_ch].base = 0; }

// one-shot request on a channel (FUN_12066 arbitration, simplified): a playing slot-0 sound is not cut off by slot 1
static void snd_play(s16 _ch, s16 _snd, s16 _vol, s16 _prio)
{
	voice_t &v = g_voice[_ch];
	if (_vol <= 0) return;
	if (v.base && !v.loop && v.prio < _prio) return;
	v.base = 0;							// restart even if the same sound
	snd_voice(_ch, _snd, _vol, c_snd_period[_snd], false, _prio);
}

// distance volume for one-shots (FUN_12306): d = |x - plane_x| + |20 - plane_alt|, >> 5; 64 - d (0 beyond)
static s16 snd_dist_vol(s16 _x, s16 _px, s16 _palt)
{
	s16 dx = _x - _px; if (dx < 0) dx = -dx;
	s16 dy = 20 - _palt; if (dy < 0) dy = -dy;
	s16 d = (s16)(((u16)dx + (u16)dy) >> 5);
	return d > 64 ? 0 : 64 - d;
}

// Inner loops, one stereo side (output bytes at stride 2), 16.16 stepping (word index: signed on the 68000, samples
// must stay below 32768 bytes), 4x unrolled with fixed output offsets. Each side is written once per segment, so
// nothing needs clearing first: two voices are added in a register with saturation (~47 cycles per voice and sample), one voice is
// copied through its volume table (~44), a silent side is cleared (~12). (The former loop added every voice into
// a cleared ring: ~56 per voice and sample plus the clearing.)
struct snd_mixp_t
{
	const s8 *b1, *vt1, *b2, *vt2;		// 0 4 8 12: sample data, volume tables
	s8 *out;							// 16
	u16 ip1, fr1, is1, fs1;				// 20 22 24 26: position, step (16.16)
	u16 ip2, fr2, is2, fs2;				// 28 30 32 34
	s16 quads, rem;						// 36 38: (n >> 2) - 1, (n & 3) - 1
};
static snd_mixp_t g_mixp;

#define SND_STEP2(_off_) \
		"	move.b	0(%%a1,%%d2.w),%%d0\n" \
		"	move.b	0(%%a2,%%d0.w),%%d1\n" \
		"	add.w	%%a6,%%d3\n" \
		"	addx.w	%%d4,%%d2\n" \
		"	move.b	0(%%a3,%%d5.w),%%d0\n" \
		"	add.b	0(%%a4,%%d0.w),%%d1\n" \
		"	bvc.s	9f\n" \
		"	smi	%%d1\n" \
		"	eor.b	#0x80,%%d1\n" \
		"9:	add.w	%%a0,%%d6\n" \
		"	addx.w	%%d7,%%d5\n" \
		"	move.b	%%d1," #_off_ "(%%a5)\n"
static void snd_mix2(snd_mixp_t *_p)
{
	// all registers: the counters live on the stack; a5 / a6 are saved here (a6 may be gcc's frame pointer)
	__asm__ volatile(
		"	movem.l	%%d2-%%d7/%%a2-%%a6,-(%%sp)\n"
		"	move.l	%[p],%%a0\n"
		"	move.l	%%a0,-(%%sp)\n"
		"	move.w	36(%%a0),-(%%sp)\n"		// quads at 2(sp)
		"	move.w	38(%%a0),-(%%sp)\n"		// rem at (sp)
		"	movem.l	(%%a0),%%a1-%%a5\n"
		"	move.w	20(%%a0),%%d2\n"
		"	move.w	22(%%a0),%%d3\n"
		"	move.w	24(%%a0),%%d4\n"
		"	move.w	26(%%a0),%%a6\n"
		"	move.w	28(%%a0),%%d5\n"
		"	move.w	30(%%a0),%%d6\n"
		"	move.w	32(%%a0),%%d7\n"
		"	move.w	34(%%a0),%%a0\n"
		"	moveq	#0,%%d0\n"
		"	tst.w	(%%sp)\n"
		"	bmi.s	2f\n"
		"1:\n"
		SND_STEP2(0)
		"	addq.l	#2,%%a5\n"
		"	subq.w	#1,(%%sp)\n"
		"	bpl.s	1b\n"
		"2:	tst.w	2(%%sp)\n"
		"	bmi	4f\n"
		"3:\n"
		SND_STEP2(0)
		SND_STEP2(2)
		SND_STEP2(4)
		SND_STEP2(6)
		"	addq.l	#8,%%a5\n"
		"	subq.w	#1,2(%%sp)\n"
		"	bpl	3b\n"
		"4:	addq.l	#4,%%sp\n"
		"	move.l	(%%sp)+,%%a0\n"
		"	move.w	%%d2,20(%%a0)\n"
		"	move.w	%%d3,22(%%a0)\n"
		"	move.w	%%d5,28(%%a0)\n"
		"	move.w	%%d6,30(%%a0)\n"
		"	move.l	%%a5,16(%%a0)\n"
		"	movem.l	(%%sp)+,%%d2-%%d7/%%a2-%%a6\n"
		:
		: [p] "a" (_p)
		: "d0", "d1", "a0", "a1", "cc", "memory");
}

#define SND_STEP1(_off_) \
		"	move.b	0(%[b],%[ip].w),%%d0\n" \
		"	move.b	0(%[vt],%%d0.w)," #_off_ "(%[o])\n" \
		"	add.w	%[fs],%[fr]\n" \
		"	addx.w	%[is],%[ip]\n"
static void snd_mix1(const s8 *_base, u16 &_ipos, u16 &_frac, u16 _istep, u16 _fstep, const s8 *_vt, s8 *&_out, s16 _n)
{
	u16 ip = _ipos, fr = _frac;
	s16 rem = (_n & 3) - 1;
	s16 quads = (_n >> 2) - 1;
	s8 *o = _out;
	__asm__ volatile(
		"	moveq	#0,%%d0\n"
		"	tst.w	%[r]\n"
		"	bmi.s	2f\n"
		"1:\n"
		SND_STEP1(0)
		"	addq.l	#2,%[o]\n"
		"	dbra	%[r],1b\n"
		"2:	tst.w	%[q]\n"
		"	bmi.s	4f\n"
		"3:\n"
		SND_STEP1(0)
		SND_STEP1(2)
		SND_STEP1(4)
		SND_STEP1(6)
		"	addq.l	#8,%[o]\n"
		"	dbra	%[q],3b\n"
		"4:\n"
		: [ip] "+d" (ip), [fr] "+d" (fr), [o] "+a" (o), [r] "+d" (rem), [q] "+d" (quads)
		: [b] "a" (_base), [vt] "a" (_vt), [fs] "d" (_fstep), [is] "d" (_istep)
		: "d0", "cc", "memory");
	_ipos = ip; _frac = fr; _out = o;
}

static void snd_mix0(s8 *&_out, s16 _n)
{
	s16 rem = (_n & 3) - 1;
	s16 quads = (_n >> 2) - 1;
	s8 *o = _out;
	__asm__ volatile(
		"	moveq	#0,%%d0\n"
		"	tst.w	%[r]\n"
		"	bmi.s	2f\n"
		"1:	move.b	%%d0,(%[o])\n"
		"	addq.l	#2,%[o]\n"
		"	dbra	%[r],1b\n"
		"2:	tst.w	%[q]\n"
		"	bmi.s	4f\n"
		"3:	move.b	%%d0,(%[o])\n"
		"	move.b	%%d0,2(%[o])\n"
		"	move.b	%%d0,4(%[o])\n"
		"	move.b	%%d0,6(%[o])\n"
		"	addq.l	#8,%[o]\n"
		"	dbra	%[q],3b\n"
		"4:\n"
		: [o] "+a" (o), [r] "+d" (rem), [q] "+d" (quads)
		:
		: "d0", "cc", "memory");
	_out = o;
}

static inline bool snd_live(const voice_t &_v) { return _v.base && _v.vol && (_v.istep | _v.fstep); }

// output samples before a voice's data runs out
static inline s16 snd_avail(const voice_t &_v, s16 _n)
{
	u32 step = ((u32)_v.istep << 16) | _v.fstep;
	u32 left = (((u32)(_v.len - _v.ipos)) << 16) - _v.frac;
	u32 avail = (left + step - 1) / step;
	return (avail < (u32)_n) ? (s16)avail : _n;
}

// at the end of its data a voice loops or stops
static inline void snd_wrap(voice_t &_v)
{
	if (_v.ipos >= _v.len)
	{
		if (_v.loop) _v.ipos -= _v.llen;
		else _v.base = 0;
	}
}

// one side (Amiga: channels 0 + 3 left, 1 + 2 right) of ring bytes [_off, _off + 2 * _n). A side that has been
// silent for a whole ring is left as it is (all zeros already).
static u16 g_snd_quiet[2] = { 0, 0 };				// bytes of the side written silent since its last sound
static void snd_mix_side(s16 _side, u16 _off, s16 _n, voice_t *_va, voice_t *_vb)
{
	s8 *out = g_snd_ring + _off + _side;
	while (_n > 0)
	{
		voice_t *a = (_va && snd_live(*_va)) ? _va : 0;
		voice_t *b = (_vb && snd_live(*_vb)) ? _vb : 0;
		if (!a) { a = b; b = 0; }
		if (!a)
		{
			if (g_snd_quiet[_side] < SND_RING) { snd_mix0(out, _n); g_snd_quiet[_side] += (u16)_n * 2; }
			return;
		}
		g_snd_quiet[_side] = 0;
		s16 k = snd_avail(*a, _n);
		if (b) k = snd_avail(*b, k);
		if (k > 0)
		{
			if (b)
			{
				snd_mixp_t &p = g_mixp;
				p.b1 = a->base; p.vt1 = g_snd_vt[a->vol >> 1]; p.ip1 = a->ipos; p.fr1 = a->frac; p.is1 = a->istep; p.fs1 = a->fstep;
				p.b2 = b->base; p.vt2 = g_snd_vt[b->vol >> 1]; p.ip2 = b->ipos; p.fr2 = b->frac; p.is2 = b->istep; p.fs2 = b->fstep;
				p.out = out; p.quads = (k >> 2) - 1; p.rem = (k & 3) - 1;
				snd_mix2(&p);
				a->ipos = p.ip1; a->frac = p.fr1; b->ipos = p.ip2; b->frac = p.fr2;
				out = p.out;
			}
			else
				snd_mix1(a->base, a->ipos, a->frac, a->istep, a->fstep, g_snd_vt[a->vol >> 1], out, k);
			_n -= k;
		}
		snd_wrap(*a);
		if (b) snd_wrap(*b);
	}
}

// mix all voices into ring bytes [_off, _off + _bytes) (_bytes even)
static bool snd_music_on();
static void snd_mix_segment(u16 _off, u16 _bytes)
{
	s16 n = _bytes >> 1;
	if (g_snd_paused && !snd_music_on())	// help / pause: silence, the voices keep their positions (menu music plays on its pages)
	{
		snd_mix_side(0, _off, n, 0, 0);
		snd_mix_side(1, _off, n, 0, 0);
		return;
	}
	snd_mix_side(0, _off, n, &g_voice[0], &g_voice[3]);
	snd_mix_side(1, _off, n, &g_voice[1], &g_voice[2]);
}

// fill the ring ahead of the DMA play position (call once per drawn frame). The lead follows the frame time: the
// last frame's VBLs + 2 (6..14 VBLs), so a slow frame (carrier in view, many sprites) doesn't let the DMA run into
// stale data; at the usual 3 VBLs it stays short and the sounds follow their cause quickly. (The lead must not grow
// at once after a frame of 4 VBLs: the extra VBL of mixing then made the next frame late too.)
static void mus_mix_segment(u16 _off, u16 _bytes);
static void snd_mix(s16 _frame_vbls)
{
	s16 lv = _frame_vbls + 2;
	if (lv < 6) lv = 6;
	if (lv > 14) lv = 14;
	const u16 lead = (u16)lv * SND_VBL;
	if (!g_snd_ok) return;
	u16 play = (u16)(snd_dma_pos() - (u32)g_snd_ring) & (SND_RING - 1) & ~1;
	u16 ahead = (g_snd_wr - play) & (SND_RING - 1);
	if (ahead > 14 * SND_VBL + 1000)				// more than the largest lead: the DMA overtook the writer (stall): resync
	{
		g_snd_resyncs++;
		g_snd_wr = (play + 64) & (SND_RING - 1);
		ahead = 64;
	}
	g_snd_ahead = ahead;
	if (ahead >= lead) return;
	u16 bytes = (lead - ahead) & ~3;
	while (bytes)
	{
		u16 seg = SND_RING - g_snd_wr;
		if (seg > bytes) seg = bytes;
		mus_mix_segment(g_snd_wr, seg);		// (music.h: the sequencer ticks, then snd_mix_segment)
		g_snd_wr = (g_snd_wr + seg) & (SND_RING - 1);
		bytes -= seg;
	}
}

#if defined(WOF_MIXTEST)
// test of the mixer against the former one (make mixtest; tools/hatari_run.py ... --prg WOFMIXT.PRG): the same
// voices mixed by both into the ring, which must come out the same byte for byte; the result goes into the run log
static void snd_mix_loop_ref(const s8 *_base, u16 &_ipos, u16 &_frac, u16 _istep, u16 _fstep, const s8 *_vt, s8 *_out, s16 _n)
{
	for (s16 i = 0; i < _n; i++)
	{
		s16 o = (s16)_out[2 * i] + _vt[(u8)_base[(s16)_ipos]];
		_out[2 * i] = (s8)(o > 127 ? 127 : o < -128 ? -128 : o);
		u32 f = (u32)_frac + _fstep;
		_frac = (u16)f;
		_ipos = (u16)(_ipos + _istep + (f >> 16));
	}
}
static void snd_mix_segment_ref(u16 _off, u16 _bytes)
{
	u16 *p = (u16 *)(g_snd_ring + _off);
	for (u16 i = 0; i < _bytes; i += 2) *p++ = 0;
	for (s16 c = 0; c < SND_VOICES; c++)
	{
		voice_t &v = g_voice[c];
		if (!v.base || v.vol == 0) continue;
		s8 *out = g_snd_ring + _off + ((c == 1 || c == 2) ? 1 : 0);
		const s8 *vt = g_snd_vt[v.vol >> 1];
		u32 step = ((u32)v.istep << 16) | v.fstep;
		if (!step) continue;
		s16 n = _bytes >> 1;
		while (n > 0 && v.base)
		{
			u32 left = (((u32)(v.len - v.ipos)) << 16) - v.frac;
			u32 avail = (left + step - 1) / step;
			s16 k = (avail < (u32)n) ? (s16)avail : n;
			if (k > 0) { snd_mix_loop_ref(v.base, v.ipos, v.frac, v.istep, v.fstep, vt, out, k); out += 2 * k; n -= k; }
			if (v.ipos >= v.len) { if (v.loop) v.ipos -= v.llen; else v.base = 0; }
		}
	}
}
static s8 g_mixt_a[SND_RING] __attribute__((aligned(4)));
static void snd_mixtest()
{
	static voice_t save[SND_VOICES];
	u32 seed = 12345;
	s16 bad = 0, cases = 0;
	for (s16 t = 0; t < 300; t++)
	{
		for (s16 c = 0; c < SND_VOICES; c++)
		{
			seed = seed * 1103515245UL + 12345UL;
			voice_t &v = g_voice[c];
			v.base = 0;
			if ((seed >> 16) % 3 == 0) continue;					// a third of the voices idle
			s16 snd = (s16)((seed >> 8) % SND_COUNT);
			u16 per = (u16)(120 + (seed >> 4) % 900);
			snd_voice(c, snd, (s16)((seed >> 20) % 70), per, ((seed >> 12) & 1) != 0, 0);
			if (((seed >> 24) & 3) == 0) { v.ipos = v.len - 1 - (u16)((seed >> 3) % 40); }	// ends within the segment
			else v.ipos = (u16)((seed >> 5) % v.len);
			v.frac = (u16)(seed * 7);
		}
		u16 off = (u16)(((seed >> 7) % (SND_RING / 2)) & ~3);
		u16 bytes = (u16)((((seed >> 9) % 3000) + 2) & ~1);
		if (off + bytes > SND_RING) bytes = (SND_RING - off) & ~1;
		for (s16 c = 0; c < SND_VOICES; c++) save[c] = g_voice[c];
		for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = (s8)(i * 37);		// (garbage: every byte must be written)
		g_snd_quiet[0] = g_snd_quiet[1] = 0;
		snd_mix_segment(off, bytes);
		for (s16 i = 0; i < SND_RING; i++) g_mixt_a[i] = g_snd_ring[i];
		voice_t after[SND_VOICES];
		for (s16 c = 0; c < SND_VOICES; c++) { after[c] = g_voice[c]; g_voice[c] = save[c]; }
		for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = (s8)(i * 37);
		snd_mix_segment_ref(off, bytes);
		cases++;
		bool ok = true;
		for (s16 i = 0; i < SND_RING; i++) if (g_mixt_a[i] != g_snd_ring[i]) { ok = false; break; }
		for (s16 c = 0; c < SND_VOICES; c++)
			if (after[c].base != g_voice[c].base || (after[c].base && (after[c].ipos != g_voice[c].ipos || after[c].frac != g_voice[c].frac)))
				ok = false;
		if (!ok) { bad++; dbg_s("MIXTEST case "); dbg_h(t); dbg_s(" differs\n"); }
	}
	for (s16 c = 0; c < SND_VOICES; c++) g_voice[c].base = 0;
	for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = 0;
	dbg_s("MIXTEST cases "); dbg_h(cases); dbg_s(" bad "); dbg_h(bad); dbg_s("\n");
}
#endif

