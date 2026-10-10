// =====================================================================================================================
//	Menu music: the Amiga's 'songplay' sequencer (reverse-engineering/notes/music.md 2) on the DMA mixer of snd.h. The four tracks of
//	a song are the mixer's four voices (tracks 0+3 left, 1+2 right, as on the Amiga); the samples and note data are
//	the original's (music.dat, tools/make_music.py). Music and game sounds never play together (as in the original:
//	both own all four channels).
//	The tick (CIA timer, 46 / 49.5 Hz) is counted in output samples inside the mix, and while a song plays the mix
//	runs in the VBL (TOS's VBL queue before the engine starts, AGT's VBL service vector after), so the music keeps
//	playing while pictures and levels load.
// =====================================================================================================================

struct mtrack_t
{
	const u16 *list;	// track list entry: pattern offset, transpose
	const u8 *ev;		// next event
	s16 count;			// ticks left of the current note
	s16 gate_off;		// count value at which the note is cut
	s16 vol;			// 0..64 (start: 32)
	s16 transpose;
	u8 tie;				// 0 none, 2 first tied note pending, 1 tied
	u8 inst;
	bool active;
};

static const u8 *g_mus = 0;						// music.dat (0: no music)
static volatile s16 g_mus_state = 0;			// 0 stopped, 2 playing, 4 fading (songplay's PlayState)
static s16 g_mus_song = -1;
static u16 g_mus_tick = 253;					// output samples per tick
static u16 g_mus_left = 0;						// output samples until the next tick
static s16 g_mus_fade_speed = 0, g_mus_fade_count = 0;
static const u8 *g_mus_voices = 0;				// the song's instrument per argument of command 0xdc
static mtrack_t g_mtrack[4];
static bool g_mus_hooked = false;				// the mix runs in the VBL (the main loop must not mix)
static bool g_mus_engine = false;				// AGT owns the VBL (else TOS's VBL queue)

#define MUS16(_o_) (*(const u16 *)(g_mus + (_o_)))

static bool snd_music_on() { return g_mus_state != 0; }

static void mus_track_entry(mtrack_t &_tr)
{
	_tr.ev = g_mus + _tr.list[0];
	_tr.transpose = (s16)_tr.list[1];
}

// one sequencer tick (songplay 0x4f4 per track)
static void mus_tick()
{
	if (g_mus_state == 4 && g_mus_fade_count-- == 0)		// fade: every speed + 1 ticks all track volumes - 1
	{
		g_mus_fade_count = g_mus_fade_speed;
		s16 any = 0;
		for (s16 t = 0; t < 4; t++) { if (g_mtrack[t].vol > 0) g_mtrack[t].vol--; any |= g_mtrack[t].vol; }
		if (!any)
		{
			for (s16 t = 0; t < 4; t++) g_voice[t].base = 0;
			g_mus_state = 0;
			return;
		}
	}
	for (s16 t = 0; t < 4; t++)
	{
		mtrack_t &tr = g_mtrack[t];
		if (!tr.active) continue;
		if (tr.count)
		{
			tr.count--;
			if (tr.count == tr.gate_off && tr.tie == 0) g_voice[t].base = 0;	// gate end: cut (no release)
			continue;
		}
		for (;;)
		{
			u8 c = tr.ev[0], a = tr.ev[1];
			tr.ev += 2;
			if (c < 0xd9)
			{
				if (c & 0x80) { if (tr.tie == 0) tr.tie = 2; } else tr.tie = 0;
				const u8 *dur = g_mus + 16 + 2 * (a < 20 ? a : 0);
				tr.count = dur[0] - 1;
				tr.gate_off = dur[0] - 1 - dur[1];
				const u16 *in = (const u16 *)(g_mus + MUS16(12)) + 4 * tr.inst;	// sample, one-shot, repeat, shift
				if (!in[0]) break;								// rest voice
				if (tr.tie == 1) break;							// tied continuation: the note holds
				if (tr.tie == 2) tr.tie = 1;
				s16 n = (s16)(c & 0x7f) + tr.transpose + 33;
				if (n < 0) n = 0;
				if (n > 131) n = 131;
				u16 period = (u16)(((const u32 *)(g_mus + MUS16(14)))[n] >> in[3]);
				if (period < 100) period = 100;
				u32 step = SND_STEP_K / period;
				voice_t &v = g_voice[t];
				v.base = 0;
				v.len = in[1] + in[2];
				v.llen = in[2];									// the repeat part loops until the note is cut
				v.loop = in[2] != 0;
				v.ipos = 0; v.frac = 0;
				v.istep = (u16)(step >> 16);
				v.fstep = (u16)step;
				v.vol = tr.vol > 32 ? 64 : tr.vol * 2;			// (twice the Amiga's level: its 32 of 64 would leave 6 bits)
				v.snd = -1;
				v.prio = 0;
				v.base = (const s8 *)(g_mus + in[0]);
				break;
			}
			if (c == 0xd9) { tr.list += 2; mus_track_entry(tr); }
			else if (c == 0xda) { tr.active = false; g_voice[t].base = 0; break; }
			else if (c == 0xdb) { tr.list = (const u16 *)(g_mus + ((const u16 *)(g_mus + MUS16(2 + 2 * g_mus_song)))[t]); mus_track_entry(tr); }
			else if (c == 0xdc) tr.inst = g_mus_voices[a & 7];
			else if (c == 0xdd) g_mus_tick = (u16)(((u16)a * 1156 + 128) >> 8);	// CIA timer high byte: 709379 / (a * 256) Hz
			else if (c == 0xdf) { if (g_mus_state != 4) tr.vol = a; }
		}
	}
}

// mix ring bytes [_off, _off + _bytes), running the sequencer at its tick positions
static void mus_mix_segment(u16 _off, u16 _bytes)
{
	while (_bytes)
	{
		if (g_mus_state == 0) { snd_mix_segment(_off, _bytes); return; }
		if (g_mus_left == 0) { mus_tick(); g_mus_left = g_mus_tick; }
		u16 n = (u16)(g_mus_left * 2);
		if (n > _bytes) n = _bytes;
		snd_mix_segment(_off, n);
		_off += n; _bytes -= n;
		g_mus_left -= n >> 1;
	}
}

static void mus_vbl_tos() { snd_mix(0); }
static void mus_vbl_agt()
{
	__asm__ volatile("move.w #0x2300,%sr");		// (AGT calls its VBL service at IPL 0: keep the HBL out)
	snd_mix(0);
}

static void (**g_mus_slot)() = 0;
static void mus_hook(bool _on)
{
	if (_on == g_mus_hooked) return;
	if (g_mus_engine) *(void (* volatile *)())0xa0L = _on ? mus_vbl_agt : 0;	// AGT's VBServiceVec
	else if (_on)
	{
		void (**vq)() = *(void (***)())0x456L;
		s16 nvq = *(s16 *)0x454L;
		g_mus_slot = 0;
		for (s16 i = 0; i < nvq; i++) if (!vq[i]) { g_mus_slot = &vq[i]; break; }
		if (!g_mus_slot) return;
		*g_mus_slot = mus_vbl_tos;
	}
	else *g_mus_slot = 0;
	g_mus_hooked = _on;
}

// fade the running song out and wait until it is silent (FadeSong(2) + the busy wait of play_song: about 2 s)
static void __attribute__((noinline)) mus_wait()
{
	if (g_mus_state && g_mus_hooked)
	{
		g_mus_fade_speed = g_mus_fade_count = 2;
		g_mus_state = 4;
		volatile u32 *vbclock = (volatile u32 *)0x462L;
		u32 t0 = *vbclock;
		while (g_mus_state && *vbclock - t0 < 200) { }
	}
	g_mus_state = 0;
	for (s16 t = 0; t < 4; t++) g_voice[t].base = 0;
}

// play_song 123dc: a running song fades out first
static void __attribute__((noinline)) mus_play(s16 _n)
{
	if (!g_mus || !g_snd_ok || g_snd_off) return;		// (sound off: the music does not start either)
	mus_wait();
	const u16 *s = (const u16 *)(g_mus + MUS16(2 + 2 * _n));
	for (s16 t = 0; t < 4; t++)
	{
		mtrack_t &tr = g_mtrack[t];
		tr.list = (const u16 *)(g_mus + s[t]);
		mus_track_entry(tr);
		tr.count = 0; tr.gate_off = 0; tr.vol = 32; tr.tie = 0; tr.inst = 0;
		tr.active = true;
	}
	g_mus_voices = (const u8 *)(s + 4);
	g_mus_left = 0;
	g_mus_song = _n;
	g_mus_state = 2;
	mus_hook(true);
}

// stop_song 12470
static void __attribute__((noinline)) mus_stop()
{
	if (!g_mus_hooked) return;
	mus_wait();
	mus_hook(false);
	for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = 0;
	g_mus_song = -1;
}

static void __attribute__((noinline)) mus_load()
{
	u32 info = 0;
	if (!file_exists("music.dat")) return;
	g_mus = load_asset("music.dat", af_load_unwrapped, &info);
	if (g_mus && MUS16(0) != 0x574d) g_mus = 0;
}
