// =====================================================================================================================
//	STE DMA sound: 4-voice software mixer modelled on the Amiga game's Paula use (reverse-engineering/notes/render_sound.md 6,
//	reverse-engineering/notes/sound_ste.md). Stereo like the Amiga (channels 0+3 left, 1+2 right), SND_RATE (12517 Hz), 8-bit.
//	The DMA plays a ring buffer in loop mode; snd_mix() (once per drawn frame) fills it up to SND_LEAD bytes ahead
//	of the play position. Samples keep their native rate; every voice steps through its data at
//	rate = 3546895 / Amiga period (16.16 step = SND_STEP_K / period).
//	Volume 0..64 (Amiga), halved for headroom (two voices per side never clip).
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
static s8 g_snd_vt[33][256];					// [vol/2][unsigned sample] -> sample * vol / 128
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
			g_snd_vt[v][u] = (s8)(((s16)(s8)u * v) / 64);
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

// inner loop: n output bytes at stride 2 (one stereo side), mix-add, 16.16 stepping; 4x unrolled with fixed
// output offsets (~56 cycles per sample instead of ~66)
#define SND_STEP(_off_) \
		"	move.b	0(%[b],%[ip].w),%%d0\n" \
		"	move.b	0(%[vt],%%d0.w),%%d1\n" \
		"	add.b	%%d1," #_off_ "(%[o])\n" \
		"	add.w	%[fs],%[fr]\n" \
		"	addx.w	%[is],%[ip]\n"
static void snd_mix_loop(const s8 *_base, u16 &_ipos, u16 &_frac, u16 _istep, u16 _fstep, const s8 *_vt, s8 *_out, s16 _n)
{
	u16 ip = _ipos, fr = _frac;		// (word index, signed on the 68000: samples must stay below 32768 bytes)
	s16 rem = (_n & 3) - 1;
	s16 quads = (_n >> 2) - 1;
	__asm__ volatile(
		"	moveq	#0,%%d0\n"
		"	tst.w	%[r]\n"
		"	bmi.s	2f\n"
		"1:\n"
		SND_STEP(0)
		"	addq.l	#2,%[o]\n"
		"	dbra	%[r],1b\n"
		"2:	tst.w	%[q]\n"
		"	bmi.s	4f\n"
		"3:\n"
		SND_STEP(0)
		SND_STEP(2)
		SND_STEP(4)
		SND_STEP(6)
		"	addq.l	#8,%[o]\n"
		"	dbra	%[q],3b\n"
		"4:\n"
		: [ip] "+d" (ip), [fr] "+d" (fr), [o] "+a" (_out), [r] "+d" (rem), [q] "+d" (quads)
		: [b] "a" (_base), [vt] "a" (_vt), [fs] "d" (_fstep), [is] "d" (_istep)
		: "d0", "d1", "cc", "memory");
	_ipos = ip; _frac = fr;
}

// mix all voices into ring bytes [_off, _off + _bytes)
static bool snd_music_on();
static void snd_mix_segment(u16 _off, u16 _bytes)
{
	// clear exactly _bytes (even): a long-word loop wrote 2 bytes past the ring at every wrap when the segment
	// length was not a multiple of 4, zeroing whatever variable the linker had placed behind it
	u16 *p = (u16 *)(g_snd_ring + _off);
	for (u16 i = 0; i < _bytes; i += 2) *p++ = 0;
	if (g_snd_paused && !snd_music_on()) return;	// help / pause: silence, the voices keep their positions (menu music plays on its pages)
	for (s16 c = 0; c < SND_VOICES; c++)
	{
		voice_t &v = g_voice[c];
		if (!v.base || v.vol == 0) continue;
		s8 *out = g_snd_ring + _off + ((c == 1 || c == 2) ? 1 : 0);		// Amiga: 0/3 left, 1/2 right
		const s8 *vt = g_snd_vt[v.vol >> 1];
		u32 step = ((u32)v.istep << 16) | v.fstep;
		if (!step) continue;
		s16 n = _bytes >> 1;
		while (n > 0 && v.base)
		{
			u32 left = (((u32)(v.len - v.ipos)) << 16) - v.frac;
			u32 avail = (left + step - 1) / step;		// output samples before the data runs out
			s16 k = (avail < (u32)n) ? (s16)avail : n;
			if (k > 0)
			{
				snd_mix_loop(v.base, v.ipos, v.frac, v.istep, v.fstep, vt, out, k);
				out += 2 * k;
				n -= k;
			}
			if (v.ipos >= v.len)
			{
				if (v.loop) v.ipos -= v.llen;
				else v.base = 0;
			}
		}
	}
}

// fill the ring ahead of the DMA play position (call once per drawn frame). The lead follows the frame time: the
// last frame's VBLs + 3 (5..14 VBLs), so a slow frame (carrier in view, many sprites) doesn't let the DMA run into
// stale data; over open sea it stays short and the sounds follow their cause quickly
static void mus_mix_segment(u16 _off, u16 _bytes);
static void snd_mix(s16 _frame_vbls)
{
	s16 lv = _frame_vbls + 3;
	if (lv < 5) lv = 5;
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
