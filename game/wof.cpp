//======================================================================================================================
//	Wings of Fury STE - prototype v2
//	level 'a' with the original Amiga flight model (port of FUN_0001c660 player_update, see wof/reverse-engineering/notes/player.md)
//----------------------------------------------------------------------------------------------------------------------
//	- game logic at the original fixed 12.5 Hz (one tick every 4 VBLs); display every VBL with interpolation
//	- camera locked to the plane: plane at screen x = 160 (original), follows vertically when climbing
//	controls: joystick port 2 or arrow keys + space. Esc pauses, Ctrl+R rank selection, Ctrl+Q quits.
//	  up/down = stick forward/back (forward = nose up), left/right = throttle (toward the nose) / half-loop (against)
//======================================================================================================================

#include <mint/sysbind.h>
#include <mint/osbind.h>
#include <stdio.h>

#include "agtsys/common_cpp.h"
#include "agtsys/ealloc.h"
#include "agtsys/compress.h"
#include "agtsys/system.h"
#include "agtsys/shifter.h"
#include "agtsys/input.h"
#include "agtsys/tileset.h"
#include "agtsys/worldmap.h"
#include "agtsys/playfield.h"
#include "agtsys/arena.h"
#include "agtsys/spritesheet.h"
#include "agtsys/slabsheet.h"
#include "agtsys/spritelib.h"
#include "agtsys/entity.h"

#include "flight_data.h"
#include "fpv_data.h"		// forward view sheet tables (tools/make_panel.py)
#include "flash_data.h"		// muzzle flash sheet (tools/make_flash_sheet.py)

// ---------------------------------------------------------------------------------------------------------------------
//	per-map data: map_<x>.dat (tools/make_proto_assets.py), loaded with the level tiles/map of the mission
//	big-endian words: header (mapinfo_t), then c_map, c_wave_src, huts, bunkers, wreck sources, flags, LSO cells, pillboxes

struct mapinfo_t
{
	u16 magic, version, level_w, map_cells, deck_x0, deck_x1, home_x, bob_col0, bob_src_col, wave_sea_col;
	u16 nhuts, nbunkers, npills, nflags, nlso, nislands, mapidx, nships, pad[2];
};
static mapinfo_t g_mi;
static u16 c_map[MAX_MAP_CELLS];					// mutable: huts get wrecked
static u16 c_wave_src[MAX_LEVEL_W / 16];			// wave strip source column per level column, 0xffff = open sea
static s16 c_hut_cells[MAX_HUTS], c_wreck_src[MAX_HUTS], c_bunker_cells[MAX_BUNKERS], c_pill_cells[MAX_PILLBOXES];
static s16 c_flags[MAX_FLAGS * 3];					// x, y (top-left image position), kind (0 carrier tower, 1 island)
static s16 c_lso_cells[MAX_LSO];
#define MAX_ISLANDS 4
#define MAX_SHIPS 4
static s16 c_island_end[MAX_ISLANDS];				// 'bchr' cell of island i
static u16 c_island_bonus[MAX_ISLANDS];				// table 0x233cc[m * 4 + i]
static s16 c_hut_isl[MAX_HUTS], c_bunker_isl[MAX_BUNKERS], c_pill_isl[MAX_PILLBOXES];
static s16 c_ships[MAX_SHIPS * 2];					// anchor type, cell
static s16 c_pill_src[MAX_PILLBOXES];				// band column of the pillbox's damage tiles (row = mask - 1)
// per ship, when it is gone: band column, dst column, columns, dst row, rows of the ship-less tiles; wave strip columns
// first..last (open sea afterwards); 1/8-view first column and columns (from the mini wreck rows)
static s16 c_ship_rm[MAX_SHIPS * 9];
#define MAX_AIRF 2
static u16 c_nairf;
static s16 c_airf[MAX_AIRF * 5];				// per airfield: x_start, x_end, max airborne, planes, dir
static s16 c_ship_planes[MAX_SHIPS * 2];			// per ship: planes, max airborne (mission tables 0x23480..)
static s16 c_carrier_rm[10];						// own carrier gone: as c_ship_rm + band row of the tiles

#define LEVEL_W			((s16)g_mi.level_w)
#define MAP_CELLS		((s16)g_mi.map_cells)
#define HOME_X			((s32)g_mi.home_x)
#define DECK_X0			((s32)g_mi.deck_x0)
#define DECK_X1			((s32)g_mi.deck_x1)
#define BOB_COL0		((s16)g_mi.bob_col0)
#define BOB_SRC_COL		((s16)g_mi.bob_src_col)
#define WAVE_SEA_COL	((s16)g_mi.wave_sea_col)
#define NHUTS			((s16)g_mi.nhuts)
#define NBUNKERS		((s16)g_mi.nbunkers)
#define NPILLBOXES		((s16)g_mi.npills)
#define NFLAGS			((s16)g_mi.nflags)
#define LSO_COUNT		((s16)g_mi.nlso)
#define NISLANDS		((s16)g_mi.nislands)
#define NSHIPS			((s16)g_mi.nships)

static s16 g_map_letter = 'a';

// "<prefix><letter><suffix>" (the tiny CRT has no printf family)
static char *map_fname(char *_buf, const char *_pre, s16 _letter, const char *_suf)
{
	char *d = _buf;
	while (*_pre) *d++ = *_pre++;
	*d++ = (char)_letter;
	while (*_suf) *d++ = *_suf++;
	*d = 0;
	return _buf;
}

// the map file is loaded as an AGT asset (it may be packed on a release disk) and parsed from memory
static const u8 *s_map_pos = 0;
static s32 s_map_left = 0;
static bool map_read(void *_dst, u16 _words, u16 _max)
{
	if (_words > _max) return false;
	s32 n = (s32)_words * 2;
	if (n > s_map_left) return false;
	if (n) qmemcpy(_dst, s_map_pos, n);
	s_map_pos += n; s_map_left -= n;
	return true;
}

// (through AGT's file layer: a file may come from the memory bundle, see bundle_load)
static bool file_exists(const char *_name)
{
	FILE *f = fopen(_name, "rb");
	if (!f) return false;
	fclose(f);
	return true;
}

// load map_<letter>.dat; false if missing or too big for the MAX_ arrays
static bool map_load(s16 _letter)
{
	char name[16];
	map_fname(name, "map_", _letter, ".dat");
	if (!file_exists(name)) return false;
	u32 info = 0;
	u8 *buf = load_asset(name, AssetFlags(af_load_unwrapped | af_asset_scratch), &info);	// (no heap use: see scratch_begin)
	if (!buf) return false;
	s_map_pos = buf; s_map_left = (s32)(info & 0x7fffffffUL);
	bool ok = map_read(&g_mi, sizeof(g_mi) / 2, sizeof(g_mi) / 2) && g_mi.magic == 0x574d && g_mi.version == 6
		&& map_read(c_map, g_mi.map_cells, MAX_MAP_CELLS)
		&& map_read(c_wave_src, g_mi.level_w / 16, MAX_LEVEL_W / 16)
		&& map_read(c_hut_cells, g_mi.nhuts, MAX_HUTS)
		&& map_read(c_bunker_cells, g_mi.nbunkers, MAX_BUNKERS)
		&& map_read(c_wreck_src, g_mi.nhuts, MAX_HUTS)
		&& map_read(c_flags, g_mi.nflags * 3, MAX_FLAGS * 3)
		&& map_read(c_lso_cells, g_mi.nlso, MAX_LSO)
		&& map_read(c_pill_cells, g_mi.npills, MAX_PILLBOXES)
		&& map_read(c_island_end, g_mi.nislands, MAX_ISLANDS)
		&& map_read(c_island_bonus, 4, MAX_ISLANDS)
		&& map_read(c_hut_isl, g_mi.nhuts, MAX_HUTS)
		&& map_read(c_bunker_isl, g_mi.nbunkers, MAX_BUNKERS)
		&& map_read(c_pill_isl, g_mi.npills, MAX_PILLBOXES)
		&& map_read(c_ships, g_mi.nships * 2, MAX_SHIPS * 2)
		&& map_read(c_pill_src, g_mi.npills, MAX_PILLBOXES)
		&& map_read(c_ship_rm, g_mi.nships * 9, MAX_SHIPS * 9)
		&& map_read(&c_nairf, 1, 1)
		&& map_read(c_airf, c_nairf * 5, MAX_AIRF * 5)
		&& map_read(c_ship_planes, g_mi.nships * 2, MAX_SHIPS * 2)
		&& map_read(c_carrier_rm, 10, 10);
	efree(buf);
	if (ok) g_map_letter = _letter;
	return ok;
}

// ---------------------------------------------------------------------------------------------------------------------
//	WOF_DIAG: diagnostics over the SidecarTridge md-devops debug channel (read of $FBFF00+c emits byte c;
//	view with `sidecart.py debug tail`). Built only by `make diag`.

#if defined(WOF_DIAG) && defined(WOF_HDIAG)
// Hatari variant (make hdiag): lines go to Hatari's console via NatFeats
static char s_dbg_line[320];
static s16 s_dbg_len = 0;
static void dbg_c(char _c)
{
	if (_c != '\n' && s_dbg_len < (s16)sizeof(s_dbg_line) - 2) s_dbg_line[s_dbg_len++] = _c;
	if (_c == '\n') { s_dbg_line[s_dbg_len++] = '\n'; s_dbg_line[s_dbg_len] = 0; if (g_hnf_ok) nf_print(s_dbg_line); s_dbg_len = 0; }
}
#elif defined(WOF_DIAG)
static void dbg_c(char _c) { (void)*(volatile u8*)(0xFBFF00ul + (u8)_c); }
#endif
#if defined(WOF_DIAG)
static void dbg_s(const char *_s) { while (*_s) dbg_c(*_s++); }
static void dbg_h(u32 _v) { for (s16 i = 28; i >= 0; i -= 4) dbg_c("0123456789ABCDEF"[(_v >> i) & 15]); }
#endif

// ---------------------------------------------------------------------------------------------------------------------

enum EntityType : int
{
	EntityType_VIEWPORT,
	EntityType_HELLCAT,
	EntityType_WHEELS,
	EntityType_TORP,		// torpedo slung under the plane (overlay per plane frame, IMSPR layer 1)
	EntityType_FX,			// bombs, explosions, splashes, gun impacts (fixed pool, see fx_*)
	EntityType_FLASH,		// muzzle flash (Hellcat sheet frames, IMSPR in layer 1)
	EntityType_CREW,		// deck crew / landing signal officer: two layered poses
	EntityType_FLAG,		// carrier tower flag + radar (flg3..6), island flag (flg0..2 / POST)
	EntityType_HUD,			// hook rope segments (pool)
	EntityType_SOLDIER,		// island soldiers (pool, see g_sold)
	EntityType_GUN,			// AA guns on bunkers (one per building slot, drawn when g_gun_frame >= 0)
	EntityType_WEAPON,		// rockets / torpedoes in flight (one per projectile slot) + weapon menu (2), IMSPR layer 1
	EntityType_PANEL,		// cockpit panel digits/icon (drawn in the panel view)
	EntityType_MINI,		// player plane in the 1/8 high-altitude view (8thscale lpn*)
	EntityType_SEPBAR,		// black fill over the playfield's last SEP_H lines (shown with the panel palette)
	EntityType_ZERO,		// enemy planes, parked / rolling planes, wrecks (pool fed by zeros_draw_build), layer 1
	EntityType_MAX_
};

#define SCREEN_XSIZE (320)
// The standard 200-line display (AGT_CONFIG_NICKEL_NOTOP, set by the Makefile; a local AGT patch): the VBL sets the
// playfield's screen address and the split is timed by Timer B counting display lines.
#if PF_H != 163
#error "the playfield is 163 lines (200 with the panel)"
#endif
#define SCREEN_YSIZE (PF_H + 37)		// 200 lines
#define VIEWPORT_XSIZE (SCREEN_XSIZE)
#define VIEWPORT_YSIZE (PF_H)			// playfield view above the 37-line cockpit panel
#define PANEL_YSIZE (SCREEN_YSIZE - PF_H)

typedef playfield_template
<
	/*tilesize=*/4,								// 16x16 tiles
	/*max_scroll=*/32000,						// widest map (m) + 1024 px open sea each side = 30576 px
	/*vscroll=*/VScrollMode_LOOPBACK,			// sky up to the flight ceiling
	/*hscroll=*/HScrollMode_SCANWALK,
	/*restore=*/RestoreMode_PAGERESTORE,
	/*updatemode=*/UpdateMode_NORMAL,
	/*hwattr=*/PlayfieldHardware(PFH_STE|PFH_Blitter),
	/*pfattr=*/PlayfieldAttributes(PFA_TileAnimation|PFA_UpdateFullTiles),	// map edits at run time (wrecked huts)
	/*guardx=*/32,
	/*guardy=*/32,
	/*mapaddr=*/s32								// > 32768 map entries
> playfield_t;

typedef arena_template
<
	/*buffers=*/2,
	/*singleframe=*/true,
	/*dualfield=*/false,
	/*playfield_type=*/playfield_t
> arena_t;

// cockpit panel: same playfield, small scroll range (AGT sizes per-playfield lookup tables by max_scroll)
typedef playfield_template
<
	/*tilesize=*/4,
	/*max_scroll=*/1024,
	/*vscroll=*/VScrollMode_LOOPBACK,
	/*hscroll=*/HScrollMode_SCANWALK,
	/*restore=*/RestoreMode_PAGERESTORE,
	/*updatemode=*/UpdateMode_NORMAL,
	/*hwattr=*/PlayfieldHardware(PFH_STE|PFH_Blitter),
	/*pfattr=*/PlayfieldAttributes(PFA_TileAnimation|PFA_UpdateFullTiles),
	/*guardx=*/32,
	/*guardy=*/32,
	/*mapaddr=*/s32
> panel_playfield_t;

typedef arena_template
<
	/*buffers=*/2,
	/*singleframe=*/true,
	/*dualfield=*/false,
	/*playfield_type=*/panel_playfield_t
> panel_arena_t;

extern "C" u8 bTT030;		// (system.h declares it as bTT)
machine machinestate;

S_SUPER_SSP(AGT_CONFIG_STACK);

AGT_MAIN;

static const s16 c_viewport_xmargin = playfield_t::c_guardx;
static const s16 c_viewport_ymargin = playfield_t::c_guardy;

static entity_t *s_pe_viewport = NULL;
static entity_t *s_pe_player = NULL;
static entity_t *s_pe_wheels = NULL;
static entity_t *s_pe_torp = NULL;
static drawcontext_t drawcontext;

tileset mytiles;
worldmap mymap;

// ---------------------------------------------------------------------------------------------------------------------
//	level memory: one zone for the level tiles + map, sized for the largest map on the disk and allocated before
//	everything else. A map switch reuses it (local AGT patch ealloc_zone), so the heap never fragments.

static u8 *g_level_zone = 0;
static s32 g_level_zone_size = 0;

static s32 file_size(const char *_name)
{
	_DTA *d = (_DTA *)Fgetdta();
	if (Fsfirst(_name, 0) != 0) return 0;
	return d->dta_size;
}

// packed disk (tools/pack_disk.py): a wrapped asset's header gives its unpacked size (prefix 'wrap', code, packed
// size, unpacked size). _skip = 8 for a .ccm, whose 8-byte header stays unpacked. 0 = not packed
static s32 unpacked_size(const char *_name, s32 _skip)
{
	s32 h = Fopen(_name, 0);
	if (h < 0) return 0;
	u32 buf[6] = { 0, 0, 0, 0, 0, 0 };
	Fread((s16)h, _skip + 16, buf);							// (no Fseek: the SidecarTridge's GEMDRIVE fails every seek)
	Fclose((s16)h);
	const u32 *b = buf + (_skip >> 2);
	return b[0] == 0x77726170UL ? (s32)b[3] : 0;
}

// Loading uses AGT's scratch area: packed data is read into it before unpacking (PACK.INF holds the largest packed
// size on the disk), and the map data file is parsed from it. The area exists only while files are loaded
// (start-up, map switch); nothing else is allocated meanwhile, so the heap does not fragment.
static s32 g_scratch_size = 20000;			// (map data: up to 14 KB, plus its packed form)
static void *g_scratch = 0;
static u32 g_pack_sizes[15][2];				// PACK.INF: unpacked sizes of level_a..o (.cct, .ccm)
static bool g_pack_sizes_ok = false;
static void scratch_init()
{
	s32 h = Fopen("PACK.INF", 0);
	if (h < 0) return;
	u32 sz = 0;
	Fread((s16)h, 4, &sz);
	g_pack_sizes_ok = Fread((s16)h, sizeof(g_pack_sizes), g_pack_sizes) == (s32)sizeof(g_pack_sizes);
	Fclose((s16)h);
	if (sz <= 200000UL && (s32)sz + 64 > g_scratch_size) g_scratch_size = (s32)sz + 64;
}
static void scratch_begin()
{
	if (g_scratch) return;
	g_scratch = (void *)Malloc(g_scratch_size);
	if (g_scratch) M_InitScratch(g_scratch, (int)g_scratch_size);
}
static void scratch_end()
{
	if (!g_scratch) return;
	M_ResetScratch();
	Mfree(g_scratch);
	g_scratch = 0;
}

// Bundles (packed disk, tools/pack_disk.py): the files of one loading phase in a single file (START.BIN, LVL_x.BIN),
// read in one go and served from memory by AGT's file layer (local patch g_zl_bundle in zerolibc). Opening and
// reading the files one by one took 3-4 s each from a floppy. The block sits at the top of the free memory while
// it is used, so what is loaded meanwhile does not end up behind a hole.
extern const unsigned char *g_zl_bundle;
static void *g_bundle = 0;
static void bundle_free()
{
	g_zl_bundle = 0;
	if (g_bundle) Mfree(g_bundle);
	g_bundle = 0;
}
static bool bundle_load(const char *_name)
{
	bundle_free();
	s32 size = file_size(_name);
	if (size <= 0) return false;
	s32 largest = (s32)Malloc(-1);
	if (largest < size + 4096) return false;
	void *below = (void *)Malloc(largest - size - 256);
	g_bundle = (void *)Malloc(size);
	if (below) Mfree(below);
	if (!g_bundle) return false;
	s32 h = Fopen(_name, 0);
	bool ok = h >= 0 && Fread((s16)h, size, g_bundle) == size;
	if (h >= 0) Fclose((s16)h);
	if (!ok) { bundle_free(); return false; }
	g_zl_bundle = (const unsigned char *)g_bundle;
	return true;
}

static bool level_zone_init()
{
	s32 best = 0;
	char n[16];
	for (const char *l = MAP_LETTERS; *l; l++)
	{
		s32 t, m;
		if (g_pack_sizes_ok && *l >= 'a' && *l <= 'o')			// packed disk: from PACK.INF (no file access)
		{
			t = (s32)g_pack_sizes[*l - 'a'][0];
			m = (s32)g_pack_sizes[*l - 'a'][1];
			if (!t || !m) continue;
		}
		else
		{
			t = file_size(map_fname(n, "level_", *l, ".cct"));
			m = file_size(map_fname(n, "level_", *l, ".ccm"));
			if (!t || !m) continue;
			s32 u = unpacked_size(n, 8);						// (n = the .ccm name)
			if (u) m = u + 8;
			u = unpacked_size(map_fname(n, "level_", *l, ".cct"), 0);
			if (u) t = u;
		}
		s32 row = (m - 8) / (LEVEL_H / 16);					// bytes per map row (8-byte ccm header)
		s32 need = t + 16 + row * (LEVEL_H / 16 + 6) + 64;	// + AGT's padding rows (4 before, 2 after: POSTPAD) + headers
		if (need > best) best = need;
	}
	g_level_zone = best ? (u8 *)Malloc(best) : 0;
	g_level_zone_size = best;
	return g_level_zone != 0;
}

// load the level tiles + map of map_<letter> into the zone (the previous level must be purged)
static void level_load(s16 _letter)
{
	char n[16];
	ealloc_zone(g_level_zone, g_level_zone_size);
	mytiles.load_cct(map_fname(n, "level_", _letter, ".cct"));
	mymap.load_ccm(map_fname(n, "level_", _letter, ".ccm"));
	ealloc_zone(0, 0);
}

spritesheet hellcat_asset;
spritesheet wheels_asset;
spritesheet torp_asset;
spritesheet gmov_asset;		// 'gmov' game-over sign (drawn directly)
spritesheet elev_asset;		// carrier elevator platform 'elev' (drawn directly, see the main loop)
spritesheet fx_asset;
spritesheet crew_asset;
spritesheet flag_asset;
spritesheet soldier_asset;
spritesheet gun_asset;
spritesheet weapon_asset;
spritesheet hud_asset;
tileset paneltiles;
worldmap panelmap;
spritesheet panel_asset;
spritesheet sepbar_asset;
spritesheet tfont_asset;	// message line font (tools/make_tfont.py), drawn directly
spritesheet font_asset;		// help screen font (tools/make_font.py), drawn directly
spritesheet mini_asset;
spritesheet zero_asset;
spritesheet zmini_asset;
static entity_t *s_pe_panelview = NULL;
static drawcontext_t panelcontext;
static arena_t *g_world = NULL;		// for map edits from the game logic

// =====================================================================================================================
//	Player state (names follow player.md; Amiga addresses in brackets)
// =====================================================================================================================

enum PlayerState { PS_FLYING = 0, PS_DECK = 1, PS_CRASH = 4, PS_SINKING = 6, PS_ARRESTED = 7, PS_WRECK = 8 };

// input word bits as the Amiga logic sees them (player.md 1.2)
enum { IN_UP = 0x01, IN_DOWN = 0x02, IN_RIGHT = 0x04, IN_LEFT = 0x08, IN_HOLD = 0x10, IN_TAP = 0x20 };

struct player_t
{
	s32 x;					// [24fca] world x, px
	s16 y;					// [24fc8] altitude, px, up positive, 0 = top of the wave strip
	s16 state;				// [24fd4]
	s16 fuel;				// [24fd6]
	s16 oil;				// [24fda]
	s16 dir;				// [24fdc] -1 left, +1 right
	s16 hspeed;				// [24fde]
	s16 vspeed;				// [24fe0]
	s16 airspeed;			// [25364] 0..1400, 1000 = cruise
	s16 throttle_accel;		// [27d3a]
	s16 pitch;				// [25352] centidegrees, + nose up
	s16 pitch_smooth;		// [259f2]
	s16 pitch_bias;			// [25358]
	s16 landing_attitude;	// [259fa]
	s16 turn;				// [2535e] 0, 1..25 half-loop frame (on deck: taxi turn 0..7)
	s16 turn_timer;			// [259f0]
	s16 attitude_frame;		// [254e2]
	s16 gear;				// [2535a] 5 down, 0 up
	s16 tail_up;			// [259ec]
	s16 fuel_timer;			// [2729e]
	s16 oil_timer;			// [272a0]
	s16 dead_ticks;			// [259f6]
	s16 sink_sub;			// [259f4]
	s16 frame;				// sprite frame (hellcat sheet)
	s16 wheel_frame;		// wheel sheet frame, -1 = not shown
	s16 wire_x;				// [26c8a] x of the caught arrester wire (state 7)
	s16 signal;				// [252af] deck crew signal 0..5 (player.md 6.6)
	s16 first_takeoff;		// [252b7] nonzero until the first take-off
};

static player_t P;

#include "snd.h"					// DMA sound mixer + samples (tools/make_sounds.py)
#include "music.h"					// menu music: the Amiga's song player on the mixer
static s16 g_wave_bob = 3;		// [252fe] carrier wave bob 2..4 (bob_tick); the carrier tiles follow via bob_apply_step
static s16 g_bob_drawn = 3;		// bob of the carrier deck tiles being shown (plane / crew sprites follow this)
static s16 g_bob_flag = 3;		// bob of the tower's top rows (updated last): the flag sprite follows this
static s16 g_deck_bob_prev = 3;		// the same one tick earlier (pairs with prev_y)
// carrier operations (player.md 6.2): phase [252e4] 1 = plane below deck on the elevator, weapon menu up;
// 2 = elevator rising; 0 = normal play; 3 = elevator going down after a landing (then re-arm, phase 1).
// g_elev [252e6] = elevator offset in px (0x20 = down, 0 = at deck level), one step per drawn frame.
static s16 g_phase = 1, g_elev = 0x20;
static s16 g_menu_db = 0;				// [252be] menu key debounce
static s16 g_deck_elev_logic = 0x20, g_deck_elev_prev = 0x20;	// elevator offset the logic used for the deck height
static s16 g_deck_bob_logic = 3;	// bob the logic used for the plane's deck height (last tick)

static s16 g_pitch_rate = 600;			// [25e66] (the cheat keys i / k change it)
static s32 g_gravity = 0x6000;			// [252a0] gravity of bombs, 0.375 px/tick^2 (cheat keys 8 / 2 / 6 / 4)
static s16 g_cheat = 0;					// [25e68] letters of "colin" typed; 5 = cheat keys on
static bool g_invuln = false;			// [26ec2] cheat key d: no damage from guns and enemy planes

static void weapons_reset();
static s16 g_lives = 3;					// [252ac] planes left (no game over yet: refills)
static s16 g_cam_x = 0, g_cam_y = 0;	// playfield camera (image coordinates)
#if !defined(WOF_FRAME_VBLS)
#define WOF_FRAME_VBLS 3
#endif
static s16 g_frame_vbls = WOF_FRAME_VBLS;	// 1 = as fast as possible; 3 = the Amiga's steady 16.7 fps
// build identification: version.h (make, tools/version.sh) + the variant, e.g. "0.3.0+3d78c39 2026-10-03 200L SND"
#include "version.h"
#if !defined(WOF_SOUND)
#define WOF_SOUND 1			// the DMA sound is always built in; D on the pause page switches it off / on
#endif
#define WOF_LINES " 200L"
#define WOF_SND ""
#define WOF_BUILD "V" WOF_VERSION WOF_LINES WOF_SND
static bool g_help = false;				// H: game paused, help page shown
static bool g_pause = false;				// Esc: game paused (as on the Amiga, which shows nothing; here a page with the build id)
static bool g_help_peek = false;		// replay HELP: page shown without pausing (test aid)
// the help page covers the playfield: no playfield sprites on top of it (every fntick sets its drawtype per tick)
enum { PG_NONE = 0, PG_RANK, PG_BRIEF, PG_NAME, PG_SCORES, PG_LOAD, PG_SAVE };
static s16 g_page = PG_NONE;			// front-end page over the frozen game (rank select, briefing, name entry, high scores)
#if defined(WOF_REPLAY)
static bool g_frontend = false;			// (test flights start on the deck; replay NEWGAME switches the front end on)
#else
static bool g_frontend = true;
#endif
// Night (G_252e0): from mission h on, a random bit decides at every advance to a new mission whether it is flown at
// night: night palettes for the playfield ('night.p', 'nightocean.p') and the panel ('nightdash'). No logic change.
static bool g_night = false, g_night_roll = false;	// roll: the next map switch is an advance (not a new game)
static u16 g_pal[16], g_panel_pal[16];				// the palettes in use (day: from the tile sets)
static bool g_pal_dirty = false;					// set the hardware palette again (main loop)
static bool g_map_fresh = true;			// the loaded map has not been played yet (no reload when it is chosen)
static bool g_session_over = false;		// G_25312: game over -> high scores -> rank select
// front end, start-up and other rarely run code: small rather than fast, and never inlined into the main loop
#define COLD __attribute__((noinline, optimize("Os")))
static void page_open(s16 _p);
static void page_request(s16 _p);
static void page_close();
// saved games (the dialog and the file code are further down)
static s16 g_load_slot = -1;			// slot to restore once its map is loaded (the main loop's map switch)
static bool g_quit = false;				// "Exit Game" in the save / load dialog
static bool g_dlg_edit = false;			// save dialog: the slot name is being typed
static bool save_write(s16 _slot, const char *_name);
static s16 save_letter(s16 _slot);
// A page with its original picture: 16 palette words + a 320x200 ST low-res screen (+ strips, tools/make_pics.py)
// in memory, copied into the playfield's and the panel's frame buffers; both palettes are the picture's. 0 = the
// page is drawn as text over the dimmed playfield (picture file missing).
static u8 *g_pic = 0;
static u8 *g_loader = 0;					// the loading screen's buffer (permanent)
static s16 g_pic_dirty = 0;				// frames left in which the picture is copied to the screen (both buffers)
static bool g_pic_restore = false;		// the last picture page closed: rebuild playfield, panel and palettes
static s16 g_panel_dirty = 2;			// frames left in which the panel sprites are redrawn (see the panel pass)
static bool g_fpv_redraw = false;		// copy the forward view to the screen again
static s16 g_loading = 0;				// > 0: the loading screen is up; the map switch / page load follows when it reaches 1
static s16 g_page_next = 0;				// page to open once the loading screen shows (its picture is read from disk)
static s16 g_cover = 0;					// frames the whole screen stays black (a transition: nothing half-built is shown)
static bool g_pic_pending = false;		// a new picture is being copied to the screen buffers: black until it is complete
static s16 g_pic_hold = 0;				// frames before that copy starts (the black palette must be showing first)
static bool g_pic_loader = false;		// the picture in the buffers is the loading screen (shown and removed without a fade)
static s16 g_pic_closing = 0;			// frames a closed picture page stays in the buffers (black) before the game is rebuilt
#define HELP_HIDES(_e) do { if (g_help || g_help_peek || g_pause || g_loading || g_page) { (_e).drawtype = EntityDraw_NONE; return; } } while (0)
static u32 g_idle = 0, g_idle_per_vbl = 0;	// diag: CPU headroom measurement
static s16 g_hit_sub = 6;					// [24fd8] AA hits until the next damage step
static u16 rnd16();
static s32 g_out = 0;					// px of open sea behind the plane: > 0 beyond the right end, < 0 beyond the left
static s16 g_mini_dx = 0;				// 1/8 view: see mini_plane_x()
static s16 g_sky_flash = 0;					// [25366] sky flash frames left
static u16 g_sky_flash_col = 0;				// [25368] flash colour (0xf00 red / 0xfff white are the same in STE format)
static bool g_engine_boost = false;			// [27d38] thrust/dive input (oil needle +0x18)
static bool g_zoom = false;			// 1/8 high-altitude view active (player y > 186)
static bool g_cam_jump = false;		// set by respawn(): the playfield must be fully refilled (camera jumps)

// ---------------------------------------------------------------------------------------------------------------------
//	map helpers

static bool g_carrier_ok = true;			// own carrier afloat (G_25511 clear)
static u8 g_fpv_stat[4];					// diag: scans, list rebuilds, composes, copies since the last log line
static s16 g_fpv_mode = 3;					// (replay test aid VIEW n: 0 off, 1 sea only, 2 + bands, 3 all)
static bool g_blank = false;				// a new plane after a crash: black playfield for 20 VBLs (G_273a2)
static bool g_fpv_stale = true;				// forward view: the map changed, rebuild its cell class table
static s16 g_carrier_sunk = 0;				// tile rows of the sinking own carrier that have gone under (carrier_sink_step)
static s16 g_cell_x = 0;					// x of the last map_cell() lookup (obj_height needs it for ship decks)
static s16 ship_deck_height(s16 _x);
static bool carrier_afloat();				// own carrier not sinking (hits > 0)
static bool zero_blocks_turn();
static inline u16 map_cell(s32 _x)
{
	g_cell_x = (s16)_x;
	s32 i = _x >> 3;
	if (i < 0) i = 0;
	if (i >= MAP_CELLS) i = MAP_CELLS - 1;
	return c_map[i];
}

static inline s16 cell_surface(u16 _c) { return _c & 3; }	// 0 sea, 1 carrier, 2 island

// object height FUN_00015710 (player.md 8 / table at 0x25712: tre1,tre2,tre3,cama,dugo,huta,pill)
static s16 carrier_sink_px();			// how far the own carrier's picture has gone down
static s16 obj_height(u16 _c)
{
	s16 t = (_c >> 2) & 0x1ff;
	s16 j = (_c >> 11) & 7;
	switch (t)
	{
	case 6:		return c_objh[0] - j;
	case 7:		return c_objh[1] - j;
	case 8:		return c_objh[2] - j;
	case 0xb:	return c_objh[2] - j;
	case 3:		return c_objh[3] - j;
	case 4:		return c_objh[4] - j;
	default:	break;
	}
	if (t >= 0xf && t <= 0x1e)
		return c_objh[5] - j;
	if ((t >= 0x1f && t <= 0x27) || t == 0x9f)
	{
		g_deck_bob_logic = g_bob_drawn;
		g_deck_elev_logic = g_elev;
		return 0x21 - g_bob_drawn - g_elev - carrier_sink_px();	// own carrier deck: 0x21 - sink - wave_bob - elevator (as drawn)
	}
	// enemy ship decks (FUN_15714): ship+14 - sink stage - wave bob. Transport 0xcc, J-carrier 0xf1..0xf6,
	// battleship 0x10c..0x110, destroyer 0xe4..0xe7
	if (t == 0xcc || (t >= 0xf1 && t <= 0xf6) || (t >= 0x10c && t <= 0x110) || (t >= 0xe4 && t <= 0xe7))
		return ship_deck_height(g_cell_x);
	return 0;
}

// wheel clearance FUN_0001aaea (player.md 3.4)
static s16 wheel_clearance()
{
	if (P.turn == 0 || P.state == PS_DECK)
	{
		s16 a = P.attitude_frame;
		return c_clr[a] + (P.gear ? c_gear[a] : 0);
	}
	if (P.turn < 6) return c_turnclr[P.turn];
	if (P.turn > 19) return c_turnclr[25 - P.turn];
	return 11;
}

// half-loop step FUN_0001ab80 (player.md 4)
static void turn_step(s16 _p)
{
	if (P.state == PS_FLYING && zero_blocks_turn()) return;		// FUN_1aa6e
	if (--P.turn_timer != 0)
		return;
	P.turn_timer = 2;
	s16 n = P.turn + 1;
	if (n >= 26)
	{
		P.turn = 0;
		return;
	}
	if (n > 19 && _p == 0)
		n = 25 - P.turn;
	P.turn = n;
	if (P.turn == 14)
		P.dir = -P.dir;
}

static inline void turn_relax()
{
	if (P.turn) { if (P.turn < 7) P.turn--; else turn_step(0); }
}

// "no vertical input" pitch handling shared by two branches of controls()
static void pitch_relax(s16 k)
{
	if (P.turn)
	{
		P.pitch -= k / 4;
		if (P.pitch < -2250) P.pitch = -2250;
		if (P.pitch > 0 && P.pitch <= 500) P.pitch_bias = -P.pitch;
	}
	else
	if (P.pitch > 0)
	{
		P.pitch -= k;
		if (P.pitch < 0) P.pitch = 0;
		if (P.pitch <= 500) P.pitch_bias = -P.pitch;
	}
}

// controls() FUN_0001bff4 (player.md 3.1)
static void controls(u8 in)
{
	const s16 k = g_pitch_rate;
	s16 stick = (in & IN_LEFT) ? -1 : +1;
	P.landing_attitude = 0;
	P.pitch_bias = 0;

	// engine sound / boost: cruise (0x31 / 0x181, boost off) is set only with the stick released or straight up / down;
	// while the stick points against the flying direction (the turn) they keep their last value, as in the original
	if ((in & 0xF) == 0)
	{
		g_eng_vol_target = 0x31; g_eng_per_base = 0x181; g_engine_boost = false;
		if (P.turn) turn_relax();
		pitch_relax(k);
		if (--P.throttle_accel < 4) P.throttle_accel = 4;
		if (P.airspeed > 1000)
		{
			P.airspeed -= P.throttle_accel;
			if (P.airspeed < 1000) P.airspeed = 1000;
		}
	}
	else
	if ((in & 0xC) == 0)
	{
		g_eng_vol_target = 0x31; g_eng_per_base = 0x181; g_engine_boost = false;
		if (in & IN_DOWN)
		{
			g_eng_vol_target = 0x40; g_eng_per_base = 0x14f; g_engine_boost = true;
			P.pitch -= 2 * k;
			if (P.pitch < -4500) P.pitch = -4500;
		}
		else
		if (in & IN_UP)
		{
			if (P.dir == -1)
			{
				if (P.pitch < 600) { P.pitch += k; if (P.pitch > 600) P.pitch = 600; }
				else { P.pitch -= k; if (P.pitch < 600) P.pitch = 600; }
				P.landing_attitude = 1;
			}
			else
			{
				P.pitch -= k;
				if (P.pitch < -600) P.pitch -= (P.pitch + 600) / 2;
				P.landing_attitude = 0;
			}
		}
		if (P.turn) turn_relax();
	}
	else
	{
		if (P.dir == stick)
		{
			g_eng_vol_target = 0x40; g_eng_per_base = 0x14f; g_engine_boost = true;
			if (P.turn) { if (P.turn <= 6) P.turn--; else turn_step(1); }
			if (++P.throttle_accel > 8) P.throttle_accel = 8;
			P.airspeed += P.throttle_accel;
			if (P.airspeed > 1400) P.airspeed = 1400;
		}
		else
		{
			turn_step(0);
		}

		if ((in & 3) == 0)
			pitch_relax(k);
		else
		if (in & IN_DOWN)
		{
			P.pitch -= P.turn ? k / 2 : k;
			if (P.pitch < -4500) P.pitch = -4500;
		}
		else
		{
			if (P.airspeed > 1000) P.pitch += k;
			else P.pitch += (P.dir > 0) ? k / 4 : k / 8;
			if (P.pitch > 3000) P.pitch = 3000;
		}
	}
}

// physics() FUN_0001bdfa (player.md 3.2), FFP maths ported to 16.16 fixed point
static void physics(u8 in)
{
	const s16 k = g_pitch_rate;
	s16 target = (P.landing_attitude && P.pitch == 600) ? -800 : P.pitch;
	P.pitch_smooth += (target - P.pitch_smooth) / 4;

	s16 a = P.pitch_smooth + P.pitch_bias;
	s16 t = a < 0 ? -a : a;
	s16 si = t / 100;		if (si > 91) si = 91;
	s16 ci = (9000 - t) / 100;	if (ci < 0) ci = 0; if (ci > 91) ci = 91;
	s32 s = c_sin16[si];
	s32 c = c_sin16[ci];
	if (P.pitch_smooth < 0 || P.pitch_bias < 0) s = -s;

	if (s >= 65536) P.throttle_accel -= 1;		// SPFix(s): only nonzero at exactly 90 degrees
	else if (s <= -65536) P.throttle_accel += 1;
	if (P.dir > 0 && P.airspeed < 1000) P.throttle_accel -= P.throttle_accel / 10;

	// hspeed = round(TURNCOS[turn] * airspeed * cos / 100)
	s32 tc = c_turncos16[P.turn] >> 1;					// <= 32768
	s32 v = ((tc * P.airspeed) >> 15) * (c >> 1);		// <= 1400 * 32768
	v >>= 15;
	P.hspeed = (s16)((v + 50) / 100);
	P.x += (s32)P.hspeed * P.dir;

	// vspeed = trunc(airspeed * sin / 100)
	s32 sm = s < 0 ? -s : s;
	s32 vm = (((s32)P.airspeed * (sm >> 1)) >> 15) / 100;
	P.vspeed = (s16)(s < 0 ? -vm : vm);

	if (P.airspeed < 1000 && P.state == PS_FLYING)		// stall
	{
		if (!(in & IN_UP))
		{
			P.pitch -= k / 2;
			if (P.pitch < -4500) P.pitch = -4500;
		}
		P.vspeed -= (1000 - P.airspeed) / 100;
	}

	P.y += P.vspeed;
	if (P.y > 1100)
	{
		P.y = 1100;
		P.pitch = -P.pitch;
		P.vspeed = -(P.vspeed / 2);
	}
	else
	if (P.y < -4)
		P.y = -4;
}

static void start_crash()
{
	P.state = PS_CRASH;
	P.airspeed = P.hspeed * 100;
	g_eng_vol_target = 0x19; g_eng_per_base = 0x3c0;	// state 4: dying engine (player.md 5)
	g_engine_boost = false;
}

// crash effects (defined with the weapons code below)
static void crash_fx_explosion(s32 x, s16 y);	// FUN_10820(cell under x, y, 0): explosion at the cell's x, altitude y + 12
static void spawn_explosion(s16 x, s16 alt, s16 surf);
static void crash_fx_splash(s32 x);			// FUN_152ac: splash in the gun impact list
static void crash_ground_impact(s32 x);		// FUN_146c6: wrecks the hut / empties the bunker under x
static void soldiers_kill(s16 _x, s16 _r);
static void select_frame();
static void crash_update();

// ground_check() FUN_0001ba80 (player.md 3.3)
static void ground_check()
{
	u16 cell = map_cell(P.x);
	s16 H = obj_height(cell);
	s16 clr = wheel_clearance();
	bool over_deck = g_carrier_ok && (P.x >= DECK_X0) && (P.x <= DECK_X1) && (P.turn == 0) && (P.y >= H + clr - 4);
	bool touching = (P.y - clr < H) || (P.y - clr < 1);
	if (P.state == PS_FLYING && touching)
	{
		if (over_deck)
		{
			if (P.dir == -1 && P.landing_attitude)
			{
				P.state = PS_DECK;
				P.y = H + clr;
				snd_play(3, SND_SCREECH, 64, 1);		// deck touch-down (FUN_1ba80)
			}
			else
			{
				P.vspeed = -P.vspeed;		// bounce off the deck
				P.pitch = -P.pitch;
				P.y += 6;
				snd_play(3, SND_SCREECH, 64, 1);
			}
		}
		else
		{
			start_crash();
			s16 surf = cell_surface(cell);
			if (surf != 0 && (surf != 1 || P.y > 0x13)) { crash_fx_explosion(P.x + P.dir * 16, P.y); crash_ground_impact(P.x); }	// 1bbc4: 16 px ahead, at the plane's height (checked against the Amiga 2026-10-08: plane 6678 / 38 -> explosion 6688 / 50)
			crash_update();
		}
	}
}

// crash_update FUN_0001afba (player.md 5.1): on touching the surface the plane is levelled out, then it slides and
// loses 85 airspeed per tick with a splash (sea) or an explosion (land, deck) every tick; in the air it falls
static void crash_update()
{
	const s32 x0 = P.x;					// (where the tick began: 1afd4 takes the cell pointer once)
	const s16 k = g_pitch_rate;
	u16 cell = map_cell(P.x);
	s16 surf = cell_surface(cell);			// 0 sea, 1 carrier, 2 island
	s16 lim = wheel_clearance();
	bool landed = false, falling = false;

	if (surf == 2)
	{
		if (P.y - wheel_clearance() < 1 && P.turn == 0)
		{
			P.attitude_frame = 0; P.pitch_smooth = 0; P.pitch = 0;
			P.y = wheel_clearance();
			select_frame();
			landed = true;
			crash_fx_explosion(x0, P.y - 1);		// 1b0be: the cell of the tick's start
		}
		else
			falling = true;
	}
	else
	if (surf == 0)
	{
		landed = P.y <= wheel_clearance();
		if (landed)
		{
			P.attitude_frame = 0; P.pitch_smooth = 0; P.pitch = 0;
			P.y = wheel_clearance();
			crash_fx_splash(P.x + P.dir * 8);		// 1b048: at x + dir * 8 (checked against the Amiga 2026-10-08)
		}
	}
	else
	{
		s16 sp = P.airspeed / 100;
		lim += obj_height(cell);
		if (P.y <= lim)
		{
			if (cell_surface(map_cell(P.x + P.dir * -40)) != 0)		// deck 5 cells behind too: on the deck
			{
				landed = true;
				P.attitude_frame = 0; P.pitch_smooth = 0; P.pitch = 0;
				P.y = obj_height(cell) + wheel_clearance();
			}
			else												// hit the ship's edge: thrown back, falls into the sea
			{
				P.x -= sp * P.dir + 4;
				P.airspeed = 0;
				lim = 2;
				g_sky_flash = 7; g_sky_flash_col = 0xf00;		// FUN_1cab4(7, 0xf00): red sky flash
				crash_fx_explosion(x0, P.y);			// 1b15a
			}
		}
	}

	// turn frames unwind during a crash (past the top of the half-loop they run on, and the plane faces the other way)
	if (P.turn < 14) { P.turn -= 2; if (P.turn < 0) P.turn = 0; }
	else
	{
		if (P.turn == 14) P.dir = -P.dir;
		P.turn += 2;
		if (P.turn > 25) P.turn = 0;
	}

	if (P.turn == 0 || lim < P.y)
	{
		if (landed)
		{
			P.x += (P.airspeed / 100) * P.dir;
			P.airspeed -= 85;
			if (P.airspeed < 100) P.airspeed = 0;
			if (surf == 0)
				crash_fx_splash(P.x + P.dir * 8);	// 1b2de
			else
			{
				// 1b304 passes (x, y) where FUN_10820 wants a cell pointer: the explosion lands off the map (x about
				// -1200) and is never seen, and its boom has volume 0, which cuts off the crash's boom in this tick.
				// So a slide on the deck shows the one explosion of the contact and nothing more until the wreck
				// burns (checked against the Amiga 2026-10-08); on an island the contact call above shows one a tick.
				if (g_voice[2].base && g_voice[2].snd == SND_BOOM) snd_stop(2);
				if (surf == 2) { crash_ground_impact(x0); soldiers_kill((s16)P.x, 8); }		// 1b322: the cell of the tick's start
			}
		}
		else
		{
			P.pitch -= k;
			if (P.pitch < -3100) P.pitch = -3100;
			falling = true;
		}
	}
	else
	{
		s16 tc = 11;
		if (P.turn < 6) tc = c_turnclr[P.turn];
		else if (P.turn > 19) tc = c_turnclr[25 - P.turn];
		if (surf != 2) P.y = tc + obj_height(cell);
		P.x += (P.airspeed / 100) * P.dir;
	}

	if (falling)
	{
		if (--P.vspeed < -10) P.vspeed = -10;
		P.y += P.vspeed;
		if (P.y - wheel_clearance() < 1)
		{
			P.y = wheel_clearance();
			// 1b3b4. At sea this is the orange explosion of a crash near the carrier: the gear is still down at the
			// first contact (within 1280 px of the carrier), the plane sits 5 px high, the gear goes up, and the
			// next tick it falls those 5 px. On the Amiga it is at the tick's start x, rounded down to 8 px,
			// altitude y - 1 + 12 (checked 2026-10-08: plane 5860, explosion 5856 / 13).
			crash_fx_explosion(x0, P.y - 1);
		}
		P.x += (P.airspeed / 100) * P.dir;
	}

	if (P.airspeed == 0 && P.turn == 0 && P.y <= lim)
	{
		P.state = (surf != 0 && (surf != 1 || P.y > 0x13)) ? PS_WRECK : PS_SINKING;
		g_eng_vol_target = 0;			// (states 6 and 8 fade the engine out; the clang belongs to the elevator, FUN_11460)
		P.oil = 0;
		P.dead_ticks = 0;
		P.sink_sub = 0;
	}
}

static void place_on_deck()
{
	P.y = obj_height(map_cell(P.x)) + wheel_clearance();
}

static void weapons_reset();
// re-arm FUN_00013684 (after the elevator has gone down, and for every new plane): menu after 15 ticks, bombs, full
// ordnance, fuel and oil; the plane waits below deck (phase 1). x and dir are kept.
static void rearm()
{
	g_hit_sub = 6 + (rnd16() & 7);
	weapons_reset();
#if defined(WOF_REPLAY)
	g_menu_db = 0;						// (test scripts press fire / select at once)
#else
	g_menu_db = 15;						// FUN_13684: the menu takes input after 15 ticks
#endif
	g_phase = 1; g_elev = 0x20;
	g_eng_vol = g_eng_vol_target = 0;				// engine off below deck (started when the elevator is up, 1b9cc)
	P.state = PS_DECK;
	P.hspeed = P.vspeed = 0;
	P.airspeed = 0;
	P.throttle_accel = 0;
	P.pitch = P.pitch_smooth = P.pitch_bias = 0;
	P.oil = 0x80;
	P.fuel = 0xc0;
	P.fuel_timer = 28;
	P.gear = 5;
	P.tail_up = 0;
	place_on_deck();
}

// the plane is fully on the elevator (FUN_0001b4de, state 1): extents by deck turn frame
static bool on_elevator()
{
	static const s8 c_l[7] = { 19, 18, 17, 18, 20, 20, 23 }, c_r[7] = { 22, 21, 20, 20, 22, 23, 23 };
	s16 t = P.turn < 0 ? 0 : P.turn > 6 ? 6 : P.turn;
	s32 left = P.x - (P.dir < 0 ? c_l[t] : c_r[t]);
	s32 right = P.x + (P.dir < 0 ? c_r[t] : c_l[t]);
	return left >= HOME_X - 0x17 && right <= HOME_X + 0x21;
}

// deck crew signal FUN_1bcce (with FUN_1b4de): on the first take-off the crew waves the plane off; later it waves it
// towards the elevator (1: the plane's left edge is left of it, 0: its right edge is right of it), shows 5 on the
// elevator, and "cut" (4) once the plane moving towards the elevator is within its braking distance. The braking
// distance is computed in 16 bits as in the original (it wraps above airspeed 515). Also called in flight, where
// only the cut can appear (over the low / high signal).
static void crew_signal()
{
	if (P.first_takeoff)
	{
		P.signal = (P.x - DECK_X0 < 0x136 && P.airspeed < 400) ? 1 : 0;
		return;
	}
	if (P.state == PS_DECK)
	{
		static const s8 c_l[7] = { 19, 18, 17, 18, 20, 20, 23 }, c_r[7] = { 22, 21, 20, 20, 22, 23, 23 };
		s16 t = P.turn < 0 ? 0 : P.turn > 6 ? 6 : P.turn;
		s32 left = P.x - (P.dir < 0 ? c_l[t] : c_r[t]);
		s32 right = P.x + (P.dir < 0 ? c_r[t] : c_l[t]);
		if (left < HOME_X - 0x17) P.signal = 1;
		else if (right > HOME_X + 0x21) P.signal = 0;
		else { P.signal = 5; return; }
	}
	s16 d = P.airspeed / 4;
	s16 stop = (s16)((s32)d * d * 2) / 100;
	s32 dist = P.x - HOME_X;
	s16 ad = (s16)(dist < 0 ? -dist : dist) - 16;
	if (ad < stop && P.airspeed > 0 && P.dir == (dist < 0 ? 1 : -1)) P.signal = 4;
}

// new plane FUN_0001b7ec + respawn FUN_000135ce (player.md 5.2, 6.5): on the elevator below deck, facing left
static void respawn()
{
	g_out = 0;
	g_hit_sub = 6 + (rnd16() & 7);
	g_eng_per = g_eng_per_base = 0x328;
	P.x = HOME_X;
	P.dir = -1;
	P.state = PS_DECK;
	P.turn = 0;
	P.turn_timer = 2;
	P.hspeed = P.vspeed = 0;
	P.airspeed = 0;
	P.throttle_accel = 0;
	P.pitch = P.pitch_smooth = P.pitch_bias = 0;
	P.landing_attitude = 0;
	P.oil = 0x80;
	P.fuel = 0xc0;
	P.fuel_timer = 28;
	P.oil_timer = 0x50;
	P.gear = 5;
	P.tail_up = 0;
	P.attitude_frame = 4;
	P.dead_ticks = 0;
	P.first_takeoff = 1;
	rearm();
	g_fpv_stale = true;						// (forward view: rebuilt from the map as it is now)
	g_fpv_redraw = true;
	g_cam_jump = true;
}

static void game_over();

static void respawn_timer(u8 in)
{
	P.dead_ticks++;
	if (P.dead_ticks >= 150 || (P.dead_ticks > 30 && (in & (IN_TAP | IN_HOLD))))
	{
		// FUN_000135ce lives--; 135d8: no lives left or the carrier sunk = game over. There is no high score / rank
		// select yet: the mission restarts (score 0, 3 planes)
		if (--g_lives < 1 || !carrier_afloat()) { game_over(); return; }
		g_blank = true;
		respawn();
	}
}

// deck handling: FUN_0001c4e8 throttle, FUN_0001bdba move, FUN_0001c5f4 take-off, FUN_0001b92e wires
static void deck_update(u8 in)
{
	s16 stick = (in & IN_LEFT) ? -1 : +1;
	// engine sound / boost as in the original deck controls (idle 0x28 / 0x328, full throttle 0x40 / 0x14f)
	g_eng_vol_target = 0x28; g_eng_per_base = 0x328;
	if ((in & (IN_LEFT | IN_RIGHT)) == 0)
	{
		g_engine_boost = false;
		P.airspeed -= 8;
		P.throttle_accel = 0;
	}
	else
	if (stick == P.dir)
	{
		g_engine_boost = true;
		if (P.turn == 0) { g_eng_vol_target = 0x40; g_eng_per_base = 0x14f; if (++P.throttle_accel > 8) P.throttle_accel = 8; }
		else P.turn--;
		P.airspeed += P.throttle_accel;
	}
	else
	{
		g_engine_boost = false;
		P.throttle_accel = 0;
		if (P.airspeed == 0)
		{
			if (++P.turn > 6) { P.dir = -P.dir; P.turn = 5; }
		}
		P.airspeed -= 8;
	}
	P.tail_up = (P.airspeed > 600 && !(in & IN_UP));
	if (P.airspeed < 0) P.airspeed = 0;
	if (P.airspeed > 1400) P.airspeed = 1400;

	// arrester wires (only after a landing; take-off rolls away from them)
	if (P.airspeed >= 600 && !P.tail_up)
	{
		s32 hook = P.x - 0x18 * P.dir;
		for (s16 k = 0; k < 4; k++)
		{
			s32 w = HOME_X + 0x46 + k * 0x38;
			s32 d = hook - w;
			if (d >= -8 && d <= 8)
			{
				P.state = PS_ARRESTED;
				P.wire_x = (s16)w;
				snd_play(3, SND_SCREECH, 64, 1);		// hook caught
				break;
			}
		}
	}

	P.hspeed = (P.airspeed + 50) / 100;
	P.x += (s32)P.hspeed * P.dir;

	if (P.x < DECK_X0 || P.x > DECK_X1)
	{
		P.first_takeoff = 0;
		P.state = PS_FLYING;		// rolled off the deck: airborne (usually below cruise speed -> hold UP)
		P.turn = 0;
	}
	else
		place_on_deck();
}

// frame selection FUN_0001c378 / FUN_0001abde (player.md 7)
static void select_frame()
{
	s16 pidx = 9;
	if (P.state != PS_DECK && P.turn == 0)
	{
		pidx = (P.pitch + 5000) / 500;
		if (pidx < 0) pidx = 0;
		if (pidx > 19) pidx = 19;
	}
	if (P.turn != 0 && P.state != PS_DECK)
		pidx = 0;

	P.wheel_frame = -1;

	if (P.state == PS_WRECK)
	{
		P.frame = (P.dir < 0) ? FR_CRASH_L : FR_CRASH_R;
		return;
	}
	if (P.state == PS_DECK)
	{
		P.attitude_frame = 4;
		if (P.tail_up)
			P.frame = (P.dir < 0) ? c_fr_pitch_l[9] : c_fr_pitch_r[9];		// 'hc05'
		else
		{
			s16 t = P.turn > 7 ? 7 : P.turn;
			P.frame = (P.dir < 0) ? c_fr_deck_l[t] : c_fr_deck_r[t];
		}
		if (P.tail_up && P.turn == 0)
			P.wheel_frame = (P.dir < 0) ? c_fr_wheel_l[pidx] : c_fr_wheel_r[pidx];
		return;
	}
	if (P.turn == 0)
	{
		P.frame = (P.dir < 0) ? c_fr_pitch_l[pidx] : c_fr_pitch_r[pidx];
		P.attitude_frame = c_frameno[pidx];
		if (P.gear && P.state != PS_SINKING)
			P.wheel_frame = (P.dir < 0) ? c_fr_wheel_l[pidx] : c_fr_wheel_r[pidx];
	}
	else
	{
		P.frame = (P.dir < 0) ? c_fr_loop_l[P.turn] : c_fr_loop_r[P.turn];
		P.attitude_frame = 0;
	}
}

// =====================================================================================================================
//	Weapons (reverse-engineering/notes/weapons_missions.md 1-4). Bombs only for now (the original default after re-arming).
// =====================================================================================================================

static s32 g_score = 0;
static s16 g_zero_kills = 0;				// [252cf] enemy planes shot down (panel counter and tally)

// smoke particles (spawn_smoke_particle 15460, update_draw_debris 10ee0): 40 slots; x/alt 16.16, velocity 1.0..2.0
// px per drawn frame right and up; frame n drawn as smk(n-1), n drops every 7 drawn frames, the particle dies at 0
struct smoke_t { s32 x, y, vx, vy; s16 n, t; };
#define NSMOKE 40
static smoke_t g_smoke[NSMOKE];
static u32 g_rng = 0x2545F491;
static u16 rnd16() { g_rng = g_rng * 1103515245u + 12345u; return (u16)(g_rng >> 16); }	// stand-in for FUN_203be

static void spawn_smoke(s16 x, s16 y, s16 n)
{
	for (s16 i = 0; i < NSMOKE; i++)
	{
		smoke_t &k = g_smoke[i];
		if (k.n) continue;
		k.x = (s32)x << 16;
		k.y = (y < 16 ? 16 : y) * 65536L;
		k.n = n;
		k.t = 6;
		k.vx = (s32)rnd16() + 0x10000;
		k.vy = (s32)rnd16() + 0x10000;
		return;
	}
}

static void smoke_frame_tick()
{
	for (s16 i = 0; i < NSMOKE; i++)
	{
		smoke_t &k = g_smoke[i];
		if (!k.n) continue;
		k.x += k.vx;
		k.y += k.vy;
		if (--k.t < 0) { k.t = 6; k.n--; }
	}
}

// explosions not tied to a projectile (spawn_explosion_at_cell, e.g. the player's wreck): same animation as a bomb
// impact, explosion frames on land / deck, splash frames on water
struct expl_t { s16 x, alt, anim, surf; };
#define NEXPL 6
static expl_t g_expl[NEXPL];
static void spawn_explosion(s16 x, s16 alt, s16 surf)
{
	for (s16 i = 0; i < NEXPL; i++)
		if (!g_expl[i].anim) { g_expl[i].x = x; g_expl[i].alt = alt; g_expl[i].surf = surf; g_expl[i].anim = 1; return; }
}

// burning wrecked huts (14e18 via draw_special_map_cell, only while the hut is drawn): 50 puffs, delay 50 - left
struct hutsmoke_t { s16 x, y, puffs, delay; };	// destroyed hut / pillbox / ship gun smoke (14e18): puff x, altitude
#define NHUTSMOKE 16
static hutsmoke_t g_hutsmoke[NHUTSMOKE];
static bool g_gun_firing = false;		// [252ba]
static s16 g_ammo = 30;					// [252bd] ordnance left for the selected weapon
static s16 g_weapon = 1;				// [252f4] 0 rockets, 1 bombs, 2 torpedo
static const s16 c_ammo_tab[3] = { 15, 30, 1 };	// 0x24b49
static bool g_menu = true;				// [252b4] weapon-select menu (plane parked, before take-off)

// projectile pool [0x24bfe], 15 slots. y is in object coordinates (player y + 11; sea/ground = 12)
struct proj_t
{
	s16 state;		// 0 free, 1 flying, 8 exploding
	s32 x, y;		// 16.16
	s32 dx, dy;		// 16.16 per tick
	s16 frame;		// bomb 0..11
	s16 surf;		// surface hit: 0 sea, 1 deck, 2 island
	s16 anim;		// explosion frame counter 1..7 (advanced per drawn frame, see fx_frame_tick)
	s16 px, py;		// previous tick position (px), for interpolation
	s16 type;		// 0 rocket, 1 bomb, 2 torpedo
	s32 ddx, ddy;	// rocket thrust (16.16 per tick^2)
	s16 delay;		// rocket ignition delay (ticks)
	s16 facing;		// torpedo / rocket facing (-1 / +1)
	s16 life;		// running torpedo: ticks left
	s16 ang, spd;	// rocket: launch angle (1024 per turn) and airspeed (+38, +40)
	bool enemy;		// the bomber's torpedo (slot NPROJ_PLAYER, G_254e4)
};
#define NPROJ_PLAYER 15
#define NPROJ 16
static proj_t g_proj[NPROJ];

// gun impact list [26e80], 20 entries
struct impact_t { s16 x; s16 timer; s16 surf; };
#define NIMPACT 20
static impact_t g_impact[NIMPACT];

static s16 g_tick_parity = 0;			// [27296] even/odd tick toggle

static void weapons_reset()
{
	for (s16 i = 0; i < NPROJ; i++) g_proj[i].state = 0;
	for (s16 i = 0; i < NIMPACT; i++) g_impact[i].timer = 0;
	g_weapon = 1;							// FUN_13684 start of sortie: bombs, full ammo, menu
	g_ammo = c_ammo_tab[g_weapon];
	g_menu = true;
}

// weapon menu FUN_112b0 (logic tick, while parked): up/down cycle the weapon (reloads its ammo), fire takes off
static void menu_tick(u8 in)
{
	if (g_menu_db) { g_menu_db--; return; }
	if (in & (IN_UP | IN_DOWN))
	{
		g_weapon += (in & IN_UP) ? -1 : 1;		// FUN_10258: up (bit 0 / cursor up 0x4c) = -1, towards ROCKETS; down = +1
		if (g_weapon < 0) g_weapon = 2;
		if (g_weapon > 2) g_weapon = 0;
		g_ammo = c_ammo_tab[g_weapon];
		g_menu_db = 2;
	}
	else if (in & (IN_TAP | IN_HOLD))
	{
		g_menu = false;				// FUN_112b0: fire -> elevator up (state 0xb, phase 2)
		g_phase = 2;
	}
}

// sin / cos of a binary angle (1024 per turn) in 16.16, from the FFP degree table
static s32 sin1024(s16 _a)
{
	s16 deg = (s16)(((s32)_a * 360) / 1024);
	bool neg = deg < 0; if (neg) deg = -deg;
	if (deg > 180) { deg = 360 - deg; neg = !neg; }
	if (deg > 90) deg = 180 - deg;
	s32 v = c_sin16[deg > 91 ? 91 : deg];
	return neg ? -v : v;
}
static s32 cos1024(s16 _a) { return sin1024((s16)(256 - _a)); }

// wreck a hut: cells type 4 -> 5 and swap in the pre-rendered wrecked tiles (multimod_copy)

// =====================================================================================================================
//	island garrison (enemies.md 3): huts and bunkers hold 5 soldiers each; a bombed hut (or a manned bunker hit by a
//	bomb) lets them run out one by one; soldiers run back and forth across the island at 3 px per drawn frame, turn
//	at the sea, re-man empty bunkers, and die from bombs / bullets within 16 px (+25 points each)
// =====================================================================================================================

struct building_t { s16 x, xl, xr; s16 inside, queued, next, silent, reman; bool bunker; s8 island, dir; };
#define NBUILD (NHUTS + NBUNKERS)
#define NSOLD (NBUILD * 5)
#define MAX_BUILD (MAX_HUTS + MAX_BUNKERS)
static building_t g_build[MAX_BUILD];		// bunkers first, then huts (FUN_11de4 order)
struct soldier_t { s16 x; s8 dir; s8 frame; s8 delay; s8 state; s8 island; s8 pad; };	// state 0 free, 1 running, 2 dying, 3 dead
static soldier_t g_sold[MAX_BUILD * 5];
static s16 g_isl_soldiers[MAX_ISLANDS], g_isl_pills[MAX_ISLANDS];	// G_253a0: per island soldiers / pillboxes alive
static bool g_isl_garrisoned[MAX_ISLANDS];
static s16 g_islands_left = 0;				// G_252d3: enemy islands still to clear
static s16 g_ships_left = 0;				// G_252c1: ships still to sink (ships are not implemented yet: 0)
static bool g_mission_done = false;			// G_2530c: mission complete, return to the carrier
static s16 g_msg_len = 0;					// message line: characters in g_msg, 0 = no message
static s16 g_map_request = 0;				// map letter to switch to (after the landing that ends a mission; replay MAP)

// next mission's map (FUN_15694 + 12adc): a..o in order, Captain loops m -> n -> o; a new rank (after c f h j k l o)
// gives an extra plane
// Victory ceremony (FUN_1557c draw + FUN_11c5e move): from the end of a rank's last mission until the next mission
// loads, 20 balloons rise from the carrier (x home - 116, altitude 56) and drift right at 1..3 px per tick; one that
// reaches altitude 170 starts again. They spawn in the draw routine, so only in the normal view.
#define NBALLOON 20
struct balloon_t { s32 x, y, dx, dy; u8 col; bool active; };
static balloon_t g_balloon[NBALLOON];
static bool g_ceremony = false;				// G_252ad
static void balloons_tick()
{
	if (!g_ceremony) return;
	for (s16 i = 0; i < NBALLOON; i++)
	{
		balloon_t &b = g_balloon[i];
		if (!b.active) continue;
		b.x += b.dx; b.y += b.dy;
		if ((s16)(b.y >> 16) >= 170) b.active = false;
	}
}

static bool mission_promotes()				// the last mission of a rank (missions per rank 3,3,2,2,1,1,3: table 0x25498)
{
	s16 l = g_map_letter;
	return l == 'c' || l == 'f' || l == 'h' || l == 'j' || l == 'k' || l == 'l' || l == 'o';
}
static s16 mission_next_letter()
{
	s16 l = g_map_letter;
	if (mission_promotes()) g_lives++;
	return l == 'o' ? 'm' : l + 1;
}
static s16 g_soldier_kills = 0;				// [26c8c]

static void garrison_init()
{
	s16 k = 0;
	for (s16 i = 0; i < MAX_ISLANDS; i++) { g_isl_soldiers[i] = 0; g_isl_pills[i] = 0; }
	for (s16 i = 0; i < NBUNKERS; i++, k++)
	{
		building_t &b = g_build[k];
		b.bunker = true; b.x = c_bunker_cells[i] * 8; b.xl = b.x - 44; b.xr = b.x + 16;
		b.inside = 5; b.queued = 0; b.next = 0; b.silent = 0; b.reman = 200;
		b.island = (s8)c_bunker_isl[i];
		// soldiers leaving: the island's first bunker sends them right, its last one left (G_25390), others random
		bool first = i == 0 || c_bunker_isl[i - 1] != b.island;
		bool last = i == NBUNKERS - 1 || c_bunker_isl[i + 1] != b.island;
		b.dir = first ? 1 : last ? -1 : 0;
	}
	for (s16 i = 0; i < NHUTS; i++, k++)
	{
		building_t &b = g_build[k];
		b.bunker = false; b.x = c_hut_cells[i] * 8; b.xl = b.xr = b.x;
		b.inside = 5; b.queued = 0; b.next = 0; b.silent = 0; b.reman = 0;
		b.island = (s8)c_hut_isl[i]; b.dir = 0;
	}
	for (s16 i = 0; i < NBUILD; i++) g_isl_soldiers[g_build[i].island & 3] += 5;
	for (s16 i = 0; i < NPILLBOXES; i++) g_isl_pills[c_pill_isl[i] & 3]++;
	for (s16 i = 0; i < NSOLD; i++) g_sold[i].state = 0;
	g_islands_left = 0;
	for (s16 i = 0; i < MAX_ISLANDS; i++)
	{
		g_isl_garrisoned[i] = g_isl_soldiers[i] > 0 || g_isl_pills[i] > 0;
		if (g_isl_garrisoned[i]) g_islands_left++;
	}
	g_ships_left = 0;
	g_mission_done = false;
	g_ceremony = false;
	g_msg_len = 0;
}

static void pillboxes_init();
static void ships_init();
static void zeros_init();
static void carrier_init();

static building_t *building_at(s16 _x)
{
	for (s16 i = 0; i < NBUILD; i++)
		if (_x >= g_build[i].x - 24 && _x <= g_build[i].x + 8) return &g_build[i];	// 4 cells around the anchor
	return 0;
}

// game over (no lives, or the carrier lost): no high scores / rank select yet, so the mission restarts
static void game_over()
{
	if (g_frontend) g_session_over = true;		// (score and rank are still needed for the high scores)
	else
	{
		g_score = 0;
		g_lives = 3;
		g_map_request = g_map_letter;			// no front end (test flights): the mission restarts
	}
#if defined(WOF_DIAG)
	dbg_s("game over\n");
#endif
}

// Message line (scroll pointer G_25706, buffer G_270ba): one message scrolls right to left; a new one is dropped
// while another is showing (FUN_1555a), only the mission text is appended to it (15694). The Amiga scrolls its hires
// font by 1 hires px per VBL, from its VBL. Here: 6 px characters in the separator strip, in a window of TK_W px in
// the middle of it, 1 px every 2nd VBL (the same speed), also from the VBL: the text is rendered once into a 1-plane
// bitmap, and AGT's VBL service writes the window into the strip of the buffer on display. (Drawn as sprites with
// the game's frames it moved 2-3 px at a time and cost about a millisecond per character.)
static char g_msg[224];
#define TK_W 224							// window width (a multiple of 16)
#define TK_X ((SCREEN_XSIZE - TK_W) / 2)
static u16 g_tk_bits[7][sizeof(g_msg) * 6 / 16 + 4];	// (one empty word before the text, some after)
static s16 g_tk_len = -1;					// characters rendered (-1: render)
static volatile s16 g_tk_pos = 0;			// scroll position in px (the VBL advances it)
static s16 g_tk_w = 0;						// text width in px
static u16 * volatile g_tk_addr = 0;		// strip row 0 in the buffer on display, at the word of screen x 0 (0: off)
static s16 g_tk_fine = 0, g_tk_pitch = 0;	// its pixel scroll (0..15), bytes per buffer line
// What the VBL overwrites is saved first, per screen buffer, and put back when that buffer is drawn again: the
// camera may have moved by then, and the old text rows would stand somewhere in the picture.
static s16 g_tk_slot = 0;					// buffer the address belongs to
static u16 g_tk_save[2][7 * 60];
static u16 *g_tk_save_at[2];				// first word saved (row 0); 0 = nothing saved
static s16 g_tk_save_pitch[2];
static void tk_restore(s16 _slot)
{
	u16 *at = g_tk_save_at[_slot];
	if (!at) return;
	g_tk_save_at[_slot] = 0;
	const u16 *q = g_tk_save[_slot];
	for (s16 r = 0; r < 7; r++, at = (u16 *)((u8 *)at + g_tk_save_pitch[_slot]))
		for (s16 k = 0; k < 60; k++) at[k] = *q++;
}
// its own 5x5 capitals (the 5x7 message font filled the strip from its top line)
static const u8 c_tk_font[64][5] = {		// ASCII 32..95, 5x5, bit 7 = left column
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x20, 0x20, 0x20, 0x00, 0x20 }, { 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0xc8, 0xd0, 0x20, 0x58, 0x98 }, { 0x60, 0x90, 0x68, 0x90, 0x68 }, { 0x20, 0x20, 0x00, 0x00, 0x00 },
	{ 0x10, 0x20, 0x20, 0x20, 0x10 }, { 0x40, 0x20, 0x20, 0x20, 0x40 }, { 0x00, 0x50, 0x20, 0x50, 0x00 }, { 0x00, 0x20, 0x70, 0x20, 0x00 },
	{ 0x00, 0x00, 0x00, 0x20, 0x40 }, { 0x00, 0x00, 0x70, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x20 }, { 0x08, 0x10, 0x20, 0x40, 0x80 },
	{ 0x70, 0x98, 0xa8, 0xc8, 0x70 }, { 0x20, 0x60, 0x20, 0x20, 0x70 }, { 0xf0, 0x08, 0x70, 0x80, 0xf8 }, { 0xf0, 0x08, 0x70, 0x08, 0xf0 },
	{ 0x90, 0x90, 0xf8, 0x10, 0x10 }, { 0xf8, 0x80, 0xf0, 0x08, 0xf0 }, { 0x70, 0x80, 0xf0, 0x88, 0x70 }, { 0xf8, 0x08, 0x10, 0x20, 0x20 },
	{ 0x70, 0x88, 0x70, 0x88, 0x70 }, { 0x70, 0x88, 0x78, 0x08, 0x70 }, { 0x00, 0x20, 0x00, 0x20, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x70, 0x00, 0x70, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x70, 0x08, 0x30, 0x00, 0x20 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x70, 0x88, 0xf8, 0x88, 0x88 }, { 0xf0, 0x88, 0xf0, 0x88, 0xf0 }, { 0x78, 0x80, 0x80, 0x80, 0x78 },
	{ 0xf0, 0x88, 0x88, 0x88, 0xf0 }, { 0xf8, 0x80, 0xf0, 0x80, 0xf8 }, { 0xf8, 0x80, 0xf0, 0x80, 0x80 }, { 0x78, 0x80, 0x98, 0x88, 0x78 },
	{ 0x88, 0x88, 0xf8, 0x88, 0x88 }, { 0x70, 0x20, 0x20, 0x20, 0x70 }, { 0x38, 0x08, 0x08, 0x88, 0x70 }, { 0x88, 0x90, 0xe0, 0x90, 0x88 },
	{ 0x80, 0x80, 0x80, 0x80, 0xf8 }, { 0x88, 0xd8, 0xa8, 0x88, 0x88 }, { 0x88, 0xc8, 0xa8, 0x98, 0x88 }, { 0x70, 0x88, 0x88, 0x88, 0x70 },
	{ 0xf0, 0x88, 0xf0, 0x80, 0x80 }, { 0x70, 0x88, 0xa8, 0x90, 0x68 }, { 0xf0, 0x88, 0xf0, 0x90, 0x88 }, { 0x78, 0x80, 0x70, 0x08, 0xf0 },
	{ 0xf8, 0x20, 0x20, 0x20, 0x20 }, { 0x88, 0x88, 0x88, 0x88, 0x70 }, { 0x88, 0x88, 0x88, 0x50, 0x20 }, { 0x88, 0x88, 0xa8, 0xd8, 0x88 },
	{ 0x88, 0x50, 0x20, 0x50, 0x88 }, { 0x88, 0x50, 0x20, 0x20, 0x20 }, { 0xf8, 0x10, 0x20, 0x40, 0xf8 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00, 0x00 },
};
static void tk_reset() { g_tk_pos = 0; g_tk_len = -1; }
static void tk_render()
{
	for (s16 r = 0; r < 7; r++) for (u16 k = 0; k < sizeof(g_tk_bits[0]) / 2; k++) g_tk_bits[r][k] = 0;
	for (s16 i = 0; i < g_msg_len; i++)
	{
		char ch = g_msg[i];
		if (ch >= 'a' && ch <= 'z') ch -= 32;
		if (ch <= 32 || ch > 95) continue;
		const u8 *gl = c_tk_font[ch - 32];
		s16 x = i * 6, sh = x & 15;
		for (s16 r = 0; r < 5; r++)					// rows 1..5 of the 7 written: a line of space above, two below
		{
			u16 ink = (u16)gl[r] << 8;
			u16 *q = &g_tk_bits[1 + r][1 + (x >> 4)];
			q[0] |= ink >> sh;
			if (sh) q[1] |= (u16)(ink << (16 - sh));
		}
	}
	g_tk_w = g_msg_len * 6;
	g_tk_len = g_msg_len;
}
static void tk_vbl()						// AGT's VBL service while a message shows
{
	__asm__ volatile("move.w #0x2300,%sr");	// (AGT calls it at IPL 0: keep the HBL out)
	static u8 s_phase = 0;
	u16 *base = g_tk_addr;
	if (!base) return;
	if ((s_phase ^= 1)) g_tk_pos++;
	s16 bit0 = g_tk_fine + TK_X;			// the window's first pixel in the row
	{
		u16 *at = base + (bit0 >> 4) * 4;
		s16 slot = g_tk_slot;
		if (g_tk_save_at[slot] != at)		// a new frame is on display: keep what is under the window
		{
			u16 *q = g_tk_save[slot];
			const u16 *p = at;
			for (s16 r = 0; r < 7; r++, p = (const u16 *)((const u8 *)p + g_tk_pitch))
				for (s16 k = 0; k < 60; k++) *q++ = p[k];
			g_tk_save_pitch[slot] = g_tk_pitch;
			g_tk_save_at[slot] = at;
		}
	}
	s16 sh = bit0 & 15;
	s16 nw = TK_W / 16 + (sh ? 1 : 0);
	s16 t0 = g_tk_pos - TK_W - sh;			// text pixel at bit 0 of the first word written
	u16 first = (u16)(0xffff >> sh), last = sh ? (u16)~(0xffff >> sh) : 0xffff;
	for (s16 r = 0; r < 7; r++)
	{
		u16 *d = (u16 *)((u8 *)base + r * g_tk_pitch) + (bit0 >> 4) * 4;
		const u16 *src = g_tk_bits[r] + 1;
		s16 t = t0;
		for (s16 k = 0; k < nw; k++, t += 16, d += 4)
		{
			u16 v = 0;
			if (t > -16 && t < g_tk_w)
			{
				s16 wi = t >> 4, b = t & 15;
				v = b ? (u16)((src[wi] << b) | (src[wi + 1] >> (16 - b))) : src[wi];
			}
			if (k == 0) v &= first;
			if (k == nw - 1) v &= last;
			d[0] = v; d[1] = v; d[2] = v; d[3] = v;		// (colour 15 on 0)
		}
	}
}
static void msg_cat(const char *_s)
{
	while (*_s && g_msg_len < (s16)sizeof(g_msg) - 1) g_msg[g_msg_len++] = *_s++;
}
static void msg_num(s32 _v)
{
	char b[12]; s16 n = 0;
	do { b[n++] = (char)('0' + _v % 10); _v /= 10; } while (_v && n < 11);
	while (n && g_msg_len < (s16)sizeof(g_msg) - 1) g_msg[g_msg_len++] = b[--n];
}
static bool msg_begin()
{
	if (g_msg_len) return false;
	tk_reset();
	return true;
}

// FUN_15694: mission complete (both counters at zero); the next map loads after the next landing
static void mission_complete()
{
	if (g_mission_done) return;
	g_mission_done = true;
	if (g_msg_len) g_msg_len--;				// appended: overwrites the last character of the message on show
	else tk_reset();
	if (mission_promotes())
	{
		g_ceremony = true;
		for (s16 i = 0; i < NBALLOON; i++) g_balloon[i].active = false;
		msg_cat(". . . Congratulations! You have completed your mission!! You are instructed to return to carrier for victory ceremony!! . . .");
	}
	else
		msg_cat(". . . Good work ! You are ordered to return to carrier to receive your next mission ! . . .");
#if defined(WOF_DIAG)
	dbg_s("mission complete\n");
#endif
}

// island cleared (146dc / 13eee): bonus word table 0x233cc[map*4 + island]. The "All enemy forces on island have
// been destroyed . . . Bonus" message (0x2394a).
static void garrison_check_cleared(s16 _isl)
{
	_isl &= 3;
	if (!g_isl_garrisoned[_isl] || g_isl_soldiers[_isl] > 0 || g_isl_pills[_isl] > 0) return;
	g_isl_garrisoned[_isl] = false;
	g_score += c_island_bonus[_isl];
	if (msg_begin())
	{
		msg_cat("All enemy forces on island have been destroyed . . . Bonus ");
		msg_num(c_island_bonus[_isl]);
		msg_cat(" points . . .");
	}
	if (--g_islands_left <= 0 && g_ships_left <= 0) mission_complete();
}

// island flag (13b1c): the state of the island at the player's position (first island whose right beach is
// to the right of the player; beyond the last one: the last island)
static bool island_flag_garrisoned()
{
	s16 n = NISLANDS;
	if (n == 0) return false;
	s16 i = 0;
	while (i < n - 1 && (s32)c_island_end[i] * 8 < P.x) i++;
	return g_isl_garrisoned[i];
}

// 14b40: the soldiers inside start running out
static void building_empty(building_t &_b)
{
	_b.queued += _b.inside;
	_b.inside = 0;
	_b.next = 60;
}

// FUN_11e82: one soldier leaves a building
static void soldier_spawn(building_t &_b, s16 _dir)
{
	for (s16 i = 0; i < NSOLD; i++)
	{
		soldier_t &so = g_sold[i];
		if (so.state) continue;
		s8 byte = (s8)(rnd16() >> 8);
		if (_dir == 0) _dir = byte < 0 ? -1 : 1;
		else byte = (s8)((byte & 0x7f) | (_dir < 0 ? 0x80 : 0));
		so.dir = (s8)_dir;
		so.x = (_dir < 0 ? _b.xl : _b.xr) + (byte & 7) * 4;
		so.frame = byte & 3;
		so.delay = 0;
		so.state = 1;
		so.island = _b.island;
		return;
	}
}

// FUN_11de4 (per logic tick): queued soldiers leave one at a time
static void garrison_tick()
{
	for (s16 i = 0; i < NBUILD; i++)
	{
		building_t &b = g_build[i];
		if (!b.next) continue;
		if (--b.next) continue;
		s16 dir = 0;
		if (b.bunker)
		{
			dir = b.dir;								// first bunker of the island: right, last: left
			if ((rnd16() & 31) == 0) dir = -dir;
		}
		soldier_spawn(b, dir);
		if (--b.queued > 0)
		{
			s16 r = (rnd16() >> 4) & 31;
			b.next = r ? r : 3;
		}
	}
}

// FUN_11a8c: running soldiers within _r of _x start dying
// FUN_11ae2(x, r): every torpedo within r of x (dropped or running, the bomber's too) explodes, without an impact.
// This is how the player's gun and bombs defend the carrier
static void torpedoes_explode(s16 _x, s16 _r)
{
	for (s16 j = 0; j < NPROJ; j++)
	{
		proj_t &t = g_proj[j];
		if ((t.state != 1 && t.state != 2) || t.type != 2) continue;
		s16 d = (s16)(t.x >> 16) - _x; if (d < 0) d = -d;
		if (d > _r) continue;
		if (t.state == 2) t.surf = 0;
		t.state = 8; t.anim = 1;
	}
}

static void soldiers_kill(s16 _x, s16 _r)
{
	bool hit = false;
	for (s16 i = 0; i < NSOLD; i++)
	{
		soldier_t &so = g_sold[i];
		if (so.state != 1) continue;
		s16 d = so.x - _x; if (d < 0) d = -d;
		if (d > _r) continue;
		so.state = 2; so.frame = 5; so.delay = 2;
		hit = true;
	}
	if (hit) snd_play(3, SND_SCREAM, snd_dist_vol(_x, (s16)P.x, P.y) / 2, 1);
	torpedoes_explode(_x - _r, 2 * _r);		// 11a8c: the window is [x - 3r, x + r] (as in the original)
}

// FUN_13eee (per drawn frame): run, turn at the sea, enter bunkers, die
static void soldiers_frame_tick()
{
	for (s16 i = 0; i < NSOLD; i++)
	{
		soldier_t &so = g_sold[i];
		if (so.state == 1)
		{
			if (++so.frame > 4) so.frame = 0;
			s16 step = so.dir < 0 ? -3 : 3;
			if (cell_surface(map_cell(so.x + step)) == 0) { so.dir = -so.dir; step = -step; }
			so.x += step;
			u16 c = map_cell(so.x);
			if (((c >> 2) & 0x1ff) == 3)
			{
				building_t *b = building_at(so.x);
				if (b && b->bunker)
				{
					if (b->silent == 0 && b->inside == 0) b->silent = 360;
					b->inside++;
					so.state = 0;
				}
			}
		}
		else if (so.state == 2)
		{
			if (--so.delay < 0)
			{
				so.delay = 2;
				if (++so.frame > 7)
				{
					so.state = 3;
					g_score += 25;
					g_soldier_kills++;
					g_isl_soldiers[so.island & 3]--;
					garrison_check_cleared(so.island);
				}
			}
		}
	}
}

// =====================================================================================================================
//	AA guns (enemies.md 5): manned bunkers fire every drawn frame once their silent delay has run out; aim from the
//	FUN_14db8 table (altitude band x horizontal distance), firing frame 6 times in 16; hit roll FUN_14f5c costs oil
//	and fuel every 6..13 hits. Empty bunkers call a soldier over from the nearest hut (14fee) every 200 frames.
// =====================================================================================================================

static s16 g_gun_frame[MAX_BUILD];			// per bunker: frame drawn this frame (-1 none; 100 = 1/8-view miniature)
// drawn guns / soldiers: small entity pools fed with what is near the camera each frame (vis_build); the wide maps have
// up to 27 buildings and 135 soldiers
#define NGUN_ENT 12
#define NSOLD_ENT 24
static s16 g_gun_vis[NGUN_ENT], g_gun_nvis = 0;
static s16 g_sold_vis[NSOLD_ENT], g_sold_nvis = 0;
static bool g_aa_fire = false;				// a gun fired since the last tick (sound)
static s16 g_aa_mind = 0x7fff;				// nearest firing gun (sound volume)

// FUN_14d50 / 14db8: gun frame for a gun at gx, or -1
static s16 aa_aim(s16 _gx, s16 _fire16 = 6)
{
	if (P.state != PS_FLYING) return -1;
	if (g_zoom) return (rnd16() & 1) ? 100 : -1;
	s16 dx = (s16)P.x - _gx;
	if (dx > 512 || dx < -512) return -1;
	s16 idx = ((P.y >> 5) - 1) * 8 + dx / 40 + 3 + AA_TAB_PRE;
	if (idx < 0 || idx >= AA_TAB_LEN) return -1;
	s16 v = c_aa_tab[idx];
	if (v < 0) return -1;
	if ((rnd16() & 15) < _fire16) v += 7;		// gnf: muzzle flash (land guns 6/16, ship guns 8/16)
	return v;
}

// FUN_14f5c: hit roll for a gun at gx that got a frame
// smoke puff at the player's plane (FUN_154e0): 10 px ahead of the centre (the engine), 13 px up, shifted by the
// bank table 0x24b40 during the middle of a half-loop
static void player_smoke(s16 _n)
{
	static const u8 c_roll[9] = { 12, 19, 23, 27, 28, 27, 23, 19, 12 };
	s16 x = (s16)P.x + (P.dir >= 0 ? 10 : -10);
	if (P.turn > 8 && P.turn < 18)
	{
		s16 d = c_roll[P.turn - 8] & 15;
		if (P.dir >= 0 ? (d < 11) : !(d > 11)) d = -d;
		x += d;
	}
	spawn_smoke(x, P.y + 13, _n);
}

// oil-leak smoke trail (FUN_11bfc, every other tick, not while sinking or wrecked): damage = 128 - oil. Below 20 the
// bit table 0x2551a thins the trail out (more bits with more damage), from 20 on there is a puff every time
static void oil_leak_smoke()
{
	static const u8 c_bits[20] = { 128, 192, 192, 192, 192, 224, 224, 224, 224, 240, 240, 240, 244, 248, 248, 248, 248, 252, 252, 252 };
	if (!g_tick_parity || P.state == PS_SINKING || P.state == PS_WRECK) return;
	s16 dmg = 0x80 - P.oil;
	if (dmg == 0) return;
	if (dmg > 0 && dmg <= 19)
	{
		u16 v = (u16)((dmg << 3) & 0xf0) + (rnd16() & 15);
		if (!(c_bits[v >> 3] & (1 << (v & 7)))) return;
	}
	player_smoke(5);
}

static void aa_hit(s16 _gx)
{
	s16 d = _gx - (s16)P.x; if (d < 0) d = -d;
	if (d > 448 || g_out) return;				// (g_out: over the open sea beyond a map end, truly out of range)
	g_aa_fire = true;
	if (d < g_aa_mind) g_aa_mind = d;
	s16 alt = P.y < 0 ? 0 : P.y;
	s16 r = (d > alt ? d : alt) + (d < alt ? d : alt) / 4;
	if (!g_invuln && (s16)(rnd16() & 511) >= r && (rnd16() & 2047) <= 409)
	{
		player_smoke(6);						// 154e0(6)
		if (--g_hit_sub <= 0)
		{
			P.oil--;
			P.fuel -= rnd16() & 3;
			g_hit_sub = 6 + (rnd16() & 7);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------
//	pillboxes (13de8 / 146dc): every intact pillbox is an AA gun (y 22); one rocket destroys it (+200), further hits add
//	damage. The cells become 'pila' + 4-bit damage mask; the tiles of each mask come from the source band.

struct pillbox_t { s16 x; s8 island, mask; bool alive; };
static pillbox_t g_pill[MAX_PILLBOXES];
static s16 g_pill_gun[MAX_PILLBOXES];				// frame drawn this frame (-1 none; 100 = 1/8-view miniature)

static void mini_pill_reset(bool _restore);
static void pillboxes_init()
{
	mini_pill_reset(false);						// (the map is fresh: no pillbox damage shown in the 1/8 view)
	for (s16 i = 0; i < NPILLBOXES; i++)
	{
		pillbox_t &p = g_pill[i];
		p.x = c_pill_cells[i] * 8; p.island = (s8)c_pill_isl[i]; p.mask = 0; p.alive = true;
		g_pill_gun[i] = -1;
	}
}

// rocket hit at wx (146dc): FUN_14ae4 looks for the anchor in the cells x-8 .. x+16
static void pillbox_hit(s16 _wx)
{
	for (s16 k = 0; k < NPILLBOXES; k++)
	{
		s16 a = c_pill_cells[k];
		s16 ci = _wx >> 3;
		if (ci < a - 2 || ci > a + 1) continue;
		s16 d = ((_wx >> 2) - a * 2) / 2;				// cell delta, truncated like divs
		s16 sh = 4 - (d + 3);
		if (sh < 0 || sh > 3) return;
		pillbox_t &p = g_pill[k];
		p.mask |= (s8)(1 << sh);
		for (s16 i = a - 2; i <= a + 1; i++)
			if (i >= 0 && i < MAP_CELLS) c_map[i] = (c_map[i] & ~(0x1ff << 2)) | ((0x0f + p.mask) << 2);
		if (g_world)
		{
			s16 c0 = (MARGIN + a * 8 - 15) >> 4;
			s16 v = p.mask - 1;						// variants: BAND_ROWS per column group
			g_world->multimod_copy(c_pill_src[k] + PILL_COLS * (v / BAND_ROWS), BAND_ROW + v % BAND_ROWS, c0, PILL_ROW, PILL_COLS, 1, mymap);
		}
		if (p.alive)
		{
			p.alive = false;
			g_score += 200;
			for (s16 i = 0; i < NHUTSMOKE; i++)
				if (!g_hutsmoke[i].puffs) { g_hutsmoke[i].x = p.x; g_hutsmoke[i].y = 17; g_hutsmoke[i].puffs = 50; g_hutsmoke[i].delay = 1; break; }
			g_isl_pills[p.island & 3]--;
			garrison_check_cleared(p.island);
		}
		return;
	}
}

// Pillbox damage in the 1/8 view (checked against the Amiga 2026-10-08): there a pillbox is 4 px wide and 2 high
// (8thscale pila..pilp): the bottom row always, the top row without the pixels whose damage bit is set (pixel k from
// the left: bit 3 - k). Our 1/8 picture is tiles with every pillbox whole, and two pillboxes can share a tile, so a
// damaged one gets the tile as a copy of its own with those pixels in the sky's colour (as a sinking ship's tiles:
// a map entry is a byte offset from the tile set). The entries are remade when something else replaced the tile
// (a wrecked hut, a ship gone) and after a load.
#define NMPT 32
static u16 g_mpt[NMPT][64];				// the copies
static s32 g_mpt_orig[NMPT], g_mpt_cell[NMPT];		// the map entry each replaced, its map index
static s16 g_mpt_n = 0;
static u8 g_mp_done[MAX_PILLBOXES];		// damage bits shown per pillbox

// the copies out of the map (_keep: only for a moment, for a saved game) / back in
static void mini_pill_map(bool _own)
{
	s32 *m = (s32 *)mymap.get();
	if (!m) return;
	for (s16 i = 0; i < g_mpt_n; i++)
		m[g_mpt_cell[i]] = _own ? (s32)((u8 *)g_mpt[i] - (u8 *)mytiles.get()) : g_mpt_orig[i];
}
static void mini_pill_reset(bool _restore)
{
	if (_restore) mini_pill_map(false);
	g_mpt_n = 0;
	for (s16 k = 0; k < MAX_PILLBOXES; k++) g_mp_done[k] = 0;
}
static void mini_pill_sync()
{
	if (!g_world) return;
	s32 *m = (s32 *)mymap.get();
	const u8 *base = (const u8 *)mytiles.get();
	s16 W = mymap.getwidth();
	for (s16 i = 0; i < g_mpt_n; i++)						// a copy's cell holds another tile now: all of them again
		if (m[g_mpt_cell[i]] != (s32)((u8 *)g_mpt[i] - base))
		{
			for (s16 j = 0; j < g_mpt_n; j++)
				if (m[g_mpt_cell[j]] == (s32)((u8 *)g_mpt[j] - base)) m[g_mpt_cell[j]] = g_mpt_orig[j];
			mini_pill_reset(false);
			break;
		}
	for (s16 k = 0; k < NPILLBOXES; k++)
	{
		u8 want = (u8)g_pill[k].mask & 15, todo = want & ~g_mp_done[k];
		if (!todo) continue;
		g_mp_done[k] = want;
		for (s16 px = 0; px < 4; px++)
		{
			if (!(todo & (8 >> px))) continue;
			s16 X = MINI_X0 + ((c_pill_cells[k] * 8 + MARGIN) >> 3) - 2 + px, Y = MINI_ROW + MINI_SEA - 2;
			s32 cell = (s32)(Y >> 4) * W + (X >> 4);
			s16 i = 0;
			while (i < g_mpt_n && g_mpt_cell[i] != cell) i++;
			if (i == g_mpt_n)
			{
				if (g_mpt_n == NMPT) continue;
				g_mpt_n++;
				g_mpt_cell[i] = cell; g_mpt_orig[i] = m[cell];
				const u16 *t = (const u16 *)(base + m[cell]);
				for (s16 w = 0; w < 64; w++) g_mpt[i][w] = t[w];
				m[cell] = (s32)((u8 *)g_mpt[i] - base);
			}
			u16 *row = &g_mpt[i][(Y & 15) * 4], bit = (u16)(0x8000 >> (X & 15));
			row[0] |= bit; row[1] &= ~bit; row[2] &= ~bit; row[3] &= ~bit;		// the sky: colour 1
			g_world->multitouch_rect(X >> 4, Y >> 4, 1, 1);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------
//	enemy ships (enemies.md 6, weapons_missions.md 3): torpedoes sink them, rockets silence their guns (+200 each).
//	Sinking (11cd8, per tick): stage 10 = bonus + "sunk", stage 120 = gone (cells cleared; ship-less tiles from the band).
//	The sinking picture goes down in steps of a tile row (ship_sink_step), not 1 px per stage.

static s16 g_wave_drawn = -1;			// wave strip phase shown (-1: refresh)
#define MAX_SGUNS 48
struct ship_t { s32 x0, x1; s16 type, hits, base_y, bonus, stage, timer, reload, gun0, ngun, sunk; bool alive; };	// sunk: tile rows gone under
struct sgun_t { s16 x; s8 yoff, ship; bool alive; };
static ship_t g_ship[MAX_SHIPS];
static sgun_t g_sgun[MAX_SGUNS];
static s16 g_sgun_frame[MAX_SGUNS], g_nsgun = 0;
static const s16 c_sgx_destroyer[8] = { 78, 88, 108, 118, 558, 568, 588, 598 };		// gun x tables (0x25552..)
static const s16 c_sgx_battleship[14] = { 43, 53, 74, 84, 106, 116, 603, 613, 635, 645, 666, 676, 698, 708 };
static const s16 c_sgx_jcarrier[15] = { 63, 79, 102, 119, 144, 154, 181, 199, 424, 455, 486, 517, 548, 577, 601 };
static const s16 c_sgx_transport[4] = { 24, 35, 89, 103 };

static void sink_free_all();
static void ships_init()
{
	sink_free_all();
	g_nsgun = 0;
	for (s16 k = 0; k < NSHIPS; k++)
	{
		ship_t &sh = g_ship[k];
		s16 t = c_ships[k * 2], cell = c_ships[k * 2 + 1];
		const s16 *gx; s16 n, x0 = -128, w;
		switch (t)
		{
		case 0xe4:	gx = c_sgx_destroyer; n = 8; sh.hits = 1; sh.base_y = 27; sh.bonus = 2500; w = 640; break;
		case 0x10d:	gx = c_sgx_battleship; n = 14; sh.hits = 2; sh.base_y = 27; sh.bonus = 4500; w = 768; break;
		case 0xcc:	gx = c_sgx_transport; n = 4; sh.hits = 1; sh.base_y = 28; sh.bonus = 1000; x0 = -64; w = 128; break;
		default:	gx = c_sgx_jcarrier; n = 15; sh.hits = 3; sh.base_y = 21; sh.bonus = 6000; w = 624; break;
		}
		sh.type = t;
		sh.x0 = (s32)cell * 8 + x0; sh.x1 = sh.x0 + w;
		sh.stage = 0; sh.reload = 0; sh.sunk = 0;
		sh.timer = (t == 0x10d) ? 0 : 20;				// the parser sets +22 = 20 for all but the battleship
		sh.alive = true;
		sh.gun0 = g_nsgun; sh.ngun = n;
		for (s16 i = 0; i < n && g_nsgun < MAX_SGUNS; i++)
		{
			sgun_t &g = g_sgun[g_nsgun];
			g.x = (s16)(sh.x0 + gx[i]); g.ship = (s8)k; g.alive = true;
			g.yoff = (t == 0xcc && (i == 1 || i == 2)) ? 5 : 0;	// transport guns 1 and 2
			g_sgun_frame[g_nsgun] = -1;
			g_nsgun++;
		}
	}
	g_ships_left = NSHIPS;
}

static ship_t *ship_at(s16 _x)
{
	for (s16 k = 0; k < NSHIPS; k++)
		if (g_ship[k].alive && _x >= g_ship[k].x0 && _x <= g_ship[k].x1) return &g_ship[k];
	return 0;
}

static s16 ship_deck_height(s16 _x)			// (the ship tiles are drawn at bob 3)
{
	ship_t *sh = ship_at(_x);
	return sh ? sh->base_y - sh->stage - 3 : 0;
}

// gun altitude (14c3e): base - sink - wave bob + gun offset + 13 (the ship tiles are drawn at bob 3)
static s16 sgun_alt(const sgun_t &_g) { const ship_t &sh = g_ship[_g.ship]; return sh.base_y - sh.stage - 3 + _g.yoff + 13; }
// the same for drawing: the picture sinks in steps of one tile row (ship_sink_step)
struct sink_t;
static bool sink_smooth(s16 _k);
static void sink_free(s16 _k);
static s16 sgun_draw_alt(const sgun_t &_g) { const ship_t &sh = g_ship[_g.ship]; return sh.base_y - (sink_smooth(_g.ship) ? sh.stage : sh.sunk * 16) - 3 + _g.yoff + 13; }

// stage 120: the ship's cells become sea, the ship-less tiles replace it, its wave strip columns become open sea
static void ship_remove(s16 _k)
{
	ship_t &sh = g_ship[_k];
	sh.alive = false;
	sh.hits = -1;
	g_fpv_stale = true;
	for (s32 c = sh.x0 >> 3; c <= (sh.x1 >> 3); c++)
		if (c >= 0 && c < MAP_CELLS) c_map[c] = 0;
	const s16 *r = &c_ship_rm[_k * 9];
	for (s16 c = r[5]; c <= r[6]; c++) c_wave_src[c] = 0xffff;
#if defined(WOF_DIAG)
	dbg_s("ship gone: band "); dbg_h(r[0]); dbg_s(" col "); dbg_h(r[1]); dbg_s(" waves "); dbg_h(r[5]); dbg_s(".."); dbg_h(r[6]); dbg_s("\n");
#endif
	if (g_world)
	{
		for (s16 c = 0; c < r[2]; c += 24)
		{
			s16 w = r[2] - c < 24 ? r[2] - c : 24;
			g_world->multimod_copy(r[0] + c, BAND_ROW, r[1] + c, r[3], w, r[4], mymap);
		}
		if (r[8]) g_world->multimod_copy(r[7], MINI_WRECK_SRC_ROW, r[7], MINI_WRECK_DST_ROW, r[8], MINI_WRECK_ROWS, mymap);
		g_wave_drawn = -1;									// refresh the strip
	}
	sink_free(_k);
}

// ---------------------------------------------------------------------------------------------------------------------
//	Smooth sinking: 1 px per stage, as the original lowers a ship.
//	A ship is part of the tile map, so it cannot simply be moved. While it sinks, its map cells (the rows above the
//	wave strip) point at tiles of its own in a block of memory taken for the purpose (a map entry is the byte offset
//	of its tile from the tile set's start: the tiles may lie anywhere), and at every stage those tiles are drawn
//	anew: the ship's own tiles shifted down by the stage's pixels, the ship-less tiles of the band above them.
//	Only the columns near the screen are drawn (a ship is up to 48 columns wide), and only the cells the ship is in:
//	where the shifted picture is nothing but the ship-less tile (the sky beside and above the ship), the map entry
//	is that tile. A row that has gone under gets the ship-less map entries back. Without memory for the block the ship sinks in steps of a tile row (ship_sink_step).

#if !defined(WOF_SINK_STEPS)
#define WOF_SINK_STEPS 0			// 1: always sink in steps of a tile row (to compare)
#endif
static s16 g_bob_row = BOB_ROWS;		// bob block: next row to update (BOB_ROWS = done)
static bool bob_apply_step();
struct sink_t
{
	u16 *tiles;				// 0: not sinking smoothly
	s32 *orig, *bg;			// the map entries of the ship as it was / of the ship-less picture
	s16 cols, rows;
	s16 stage;				// as drawn (-1: nothing yet)
	s16 c0, c1;				// columns drawn at that stage
	s16 gone;				// rows given back
	u8 *own;				// per cell: 1 = the map entry is the cell's own tile (0: the ship-less tile)
	const s16 *rm;			// its c_ship_rm / c_carrier_rm entry: band column, map column, columns, top row, rows
	u16 *strip;				// tiles of its own for the wave strip under it (sink_strip), one per column
	s16 band;				// tile row of its ship-less picture in the band
};
#define SINK_CARRIER MAX_SHIPS		// (the own carrier sinks the same way)
#define NSINK (MAX_SHIPS + 1)
static sink_t g_sink[NSINK];

static bool sink_smooth(s16 _k) { return g_sink[_k].tiles != 0; }
static void sink_free(s16 _k)
{
	if (g_sink[_k].tiles) Mfree(g_sink[_k].tiles);
	g_sink[_k].tiles = 0;
}
static void sink_free_all() { for (s16 k = 0; k < NSINK; k++) sink_free(k); }

// the ship's map entries: its own tiles (_own) or the ship as it was (for a saved game: the entries of its own
// tiles mean nothing outside this run)
static void sink_map(s16 _k, bool _own)
{
	sink_t &s = g_sink[_k];
	if (!s.tiles) return;
	const s16 *r = s.rm;
	s32 *m = (s32 *)mymap.get();
	s16 W = mymap.getwidth();
	s32 off = (s32)((u8 *)s.tiles - (u8 *)mytiles.get());
	for (s16 R = s.gone; R < s.rows; R++)
	{
		s32 *p = &m[(s32)(r[3] + R) * W + r[1]];
		s16 i = R * s.cols;
		for (s16 c = 0; c < s.cols; c++, i++) p[c] = !_own ? s.orig[i] : s.own[i] ? off + (s32)i * 128 : s.bg[i];
	}
}

static bool sink_begin(s16 _k)
{
	sink_t &s = g_sink[_k];
	const s16 *r = _k == SINK_CARRIER ? c_carrier_rm : &c_ship_rm[_k * 9];
	if (s.tiles) return true;
	if (WOF_SINK_STEPS || !g_world) return false;
	if (_k == SINK_CARRIER ? g_carrier_sunk : g_ship[_k].sunk) return false;	// (it began in steps, e.g. in an older saved game)
	if (_k == SINK_CARRIER)
	{
		while (bob_apply_step()) { }								// (a bob step under way: all of its rows first)
		// The block that sinks is the carrier's at bob 3, as generated. At bob 2 the picture is 1 px higher and the
		// mast's top row lies in the tile row above the block: it would stay in the sky. Sink from bob 3.
		if (g_bob_drawn != 3) { g_bob_drawn = 3; g_bob_row = 0; while (bob_apply_step()) { } }
		g_bob_flag = g_bob_drawn;
	}
	s16 bot = WAVE_DST_ROW - 1;
	if (r[3] + r[4] - 1 < bot) bot = r[3] + r[4] - 1;
	s16 rows = bot - r[3] + 1, cols = r[2];
	if (rows <= 0 || cols <= 0) return false;
	s32 n = (s32)rows * cols;
	u8 *mem = (u8 *)Malloc(n * 128 + n * 8 + n + (n & 1) + cols * 128L);
	if ((s32)mem <= 0) return false;
	s.tiles = (u16 *)mem; s.orig = (s32 *)(mem + n * 128); s.bg = s.orig + n; s.own = (u8 *)(s.bg + n); s.strip = (u16 *)(s.own + n + (n & 1));
	s.cols = cols; s.rows = rows; s.stage = -1; s.c0 = 0; s.c1 = -1; s.gone = 0;
	s.rm = r; s.band = BAND_ROW + (_k == SINK_CARRIER ? r[9] : 0);
	const s32 *m = mymap.get();
	s16 W = mymap.getwidth();
	for (s16 R = 0; R < rows; R++)
		for (s16 c = 0; c < cols; c++)
		{
			s.orig[R * cols + c] = m[(s32)(r[3] + R) * W + r[1] + c];
			s.bg[R * cols + c] = m[(s32)(s.band + R) * W + r[0] + c];
			s.own[R * cols + c] = 0;
		}
	return true;
}

// Bring the columns _c0.._c1 to stage _st: draw the cells' own tiles (a tile: 16 rows of 4 words) and tell the engine
// which cells to draw again.
static void sink_render(s16 _k, s16 _st, s16 _c0, s16 _c1)
{
	sink_t &s = g_sink[_k];
	const s16 *r = s.rm;
	const u8 *base = (const u8 *)mytiles.get();
	s32 *m = (s32 *)mymap.get();
	s16 W = mymap.getwidth();
	s32 off = (s32)((u8 *)s.tiles - base);
	s16 kk = _st & 15, q = _st >> 4;
	for (s16 R = q; R < s.rows; R++)							// (rows above q are all ship-less: given back)
	{
		s16 RA = R - q - 1, RB = R - q;
		s32 *p = &m[(s32)(r[3] + R) * W + r[1]];
		s16 t0 = 0x7fff, t1 = -1;								// columns of this row to redraw
		for (s16 c = _c0; c <= _c1; c++)
		{
			s16 i = R * s.cols + c;
			s32 bgv = s.bg[i], ob = s.orig[RB * s.cols + c];
			s32 oa = (kk && RA >= 0) ? s.orig[RA * s.cols + c] : bgv;
			if (ob == bgv && oa == bgv)							// nothing of the ship in this cell: the ship-less tile
			{
				if (s.own[i]) { s.own[i] = 0; p[c] = bgv; if (c < t0) t0 = c; t1 = c; }
				continue;
			}
			u32 *d = (u32 *)(s.tiles + (s32)i * 64);
			if (kk)												// the top kk pixel rows: the bottom of the tile above
			{
				const u32 *a = (const u32 *)(base + oa) + (RA >= 0 ? (16 - kk) * 2 : 0);
				for (s16 n = kk; n > 0; n--) { *d++ = *a++; *d++ = *a++; }
			}
			const u32 *b = (const u32 *)(base + ob);
			for (s16 n = 16 - kk; n > 0; n--) { *d++ = *b++; *d++ = *b++; }
			if (!s.own[i]) { s.own[i] = 1; p[c] = off + (s32)i * 128; }
			if (c < t0) t0 = c;
			t1 = c;
		}
		for (s16 c = t0; c <= t1; c += 24)
		{
			s16 w = t1 - c + 1 < 24 ? t1 - c + 1 : 24;
			g_world->multitouch_rect(r[1] + c, r[3] + R, w, 1);
		}
	}
}

static void sink_touch(const s16 *_r, s16 _c0, s16 _c1, s16 _R0, s16 _rows)
{
	if (_rows <= 0) return;
	for (s16 c = _c0; c <= _c1; c += 24)
	{
		s16 w = _c1 - c + 1 < 24 ? _c1 - c + 1 : 24;
		g_world->multitouch_rect(_r[1] + c, _r[3] + _R0, w, _rows);
	}
}

// per logic tick for a sinking ship: bring the picture to the ship's stage
static void sink_tick(s16 _k, s16 _stage)
{
	sink_t &s = g_sink[_k];
	if (!s.tiles && !sink_begin(_k)) return;
	const s16 *r = s.rm;
	s16 st = _stage, q = st >> 4;
	// rows that have gone under altogether: the ship-less entries, in all columns
	while (s.gone < q && s.gone < s.rows)
	{
		s32 *p = &((s32 *)mymap.get())[(s32)(r[3] + s.gone) * mymap.getwidth() + r[1]];
		for (s16 c = 0; c < s.cols; c++) p[c] = s.bg[s.gone * s.cols + c];
		sink_touch(r, 0, s.cols - 1, s.gone, 1);
		s.gone++;
	}
	if (q >= s.rows) return;
	// the columns near the screen
	s16 v0 = (g_cam_x >> 4) - 3 - r[1], v1 = v0 + SCREEN_XSIZE / 16 + 7;
	if (v0 < 0) v0 = 0;
	if (v1 > s.cols - 1) v1 = s.cols - 1;
	if (v0 > v1) { s.c1 = s.c0 - 1; return; }
	if (st != s.stage || s.c1 < s.c0 || v0 > s.c1 || v1 < s.c0)
	{
		sink_render(_k, st, v0, v1);
	}
	else													// same stage: only the columns that came near
	{
		if (v0 < s.c0) sink_render(_k, st, v0, s.c0 - 1);
		if (v1 > s.c1) sink_render(_k, st, s.c1 + 1, v1);
	}
	if (st != s.stage) g_wave_drawn = -1;					// (the wave strip under the ship: sink_strip)
	s.stage = st; s.c0 = v0; s.c1 = v1;
}

// Fallback (no memory for sink_t's block): the ship's tile rows above the wave strip move down by
// one row (16 px) every 16 stages, sky tiles follow from the top; the hull in the wave strip stays until stage 120.
// c_ship_rm: source band column, map column, columns, top row, rows.
static void ship_sink_step(s16 _k)
{
	ship_t &sh = g_ship[_k];
	const s16 *r = &c_ship_rm[_k * 9];
	s16 top = r[3] + sh.sunk, bot = WAVE_DST_ROW - 1;
	if (r[3] + r[4] - 1 < bot) bot = r[3] + r[4] - 1;
	if (!g_world || top > bot) return;
	for (s16 c = 0; c < r[2]; c += 24)
	{
		s16 w = r[2] - c < 24 ? r[2] - c : 24;
		for (s16 row = bot; row > top; row--)
			g_world->multimod_copy(r[1] + c, row - 1, r[1] + c, row, w, 1, mymap);
		g_world->multimod_copy(r[0] + c, BAND_ROW + (top - r[3]), r[1] + c, top, w, 1, mymap);	// the ship-less row
	}
	sh.sunk++;
}

// FUN_11cae / 11cd8 (per logic tick)
static void ships_tick()
{
	for (s16 k = 0; k < NSHIPS; k++)
	{
		ship_t &sh = g_ship[k];
		if (!sh.alive || sh.hits != 0) continue;
		if (sh.stage > 0 && sh.stage < 120) sink_tick(k, sh.stage);
		if (--sh.timer > 0) continue;
		sh.stage++;
		sh.timer = sh.reload;
		if (sh.reload) sh.reload--;
		if (sh.stage == 10)
		{
			g_score += sh.bonus;
			if (msg_begin())							// FUN_15640: the name comes from the points value
			{
				msg_cat(". . . ");
				msg_cat(sh.bonus == 4500 ? "Battleship" : sh.bonus == 6000 ? "Carrier" : sh.bonus == 2500 ? "Destroyer" : "Cruiser");
				msg_cat(" sunk . . . BONUS ");
				msg_num(sh.bonus);
				msg_cat(" points . . .");
			}
#if defined(WOF_DIAG)
			dbg_s("ship sunk bonus="); dbg_h(sh.bonus); dbg_s(" score="); dbg_h(g_score); dbg_s("\n");
#endif
			if (--g_ships_left <= 0 && g_islands_left <= 0) mission_complete();
		}
		else if (sh.stage == 120)
			ship_remove(k);
		else if (sh.stage >= 16 && (sh.stage & 15) == 0 && !sink_smooth(k))
			ship_sink_step(k);
	}
}

// 14c3e (per drawn frame): guns of the living, not sinking ships fire while the player flies
static void ship_guns_frame_tick()
{
	for (s16 i = 0; i < g_nsgun; i++)
	{
		sgun_t &g = g_sgun[i];
		g_sgun_frame[i] = -1;
		const ship_t &sh = g_ship[g.ship];
		if (!g.alive || !sh.alive || sh.hits <= 0 || P.state != PS_FLYING || g_out) continue;	// (g_out: as aa_hit)
		s16 d = g.x - (s16)P.x; if (d < 0) d = -d;
		if ((s16)(rnd16() & 511) > d)					// 14efc: in range: sound, splashes that stop torpedoes
		{
			g_aa_fire = true;
			if (P.y <= 200 && (rnd16() & 15) < 6)
			{
				s16 sx = (s16)P.x + (s16)(rnd16() & 63) - 32;
				crash_fx_splash(sx);						// 152b0: a splash in the gun-impact list
				torpedoes_explode(sx, 10);				// 11ae2(x, 10)
			}
		}
		s16 f = aa_aim(g.x, 8);
		g_sgun_frame[i] = f;
		if (f >= 0) aa_hit(g.x);
	}
}

// 146dc on a ship: rocket = the first live gun within 16 px is destroyed (+200); torpedo in the water = one hit
static void ship_hit(proj_t &_p, s16 _wx)
{
	ship_t *sh = ship_at(_wx);
	if (!sh) return;
	if (_p.type != 1) { g_sky_flash = 5; g_sky_flash_col = 0xfff; }		// 146dc: white flash (bombs do nothing)
	if (_p.type == 0 || (_p.type == 2 && _p.state != 2))		// (a torpedo dropped on the deck counts like a rocket)
	{
		for (s16 i = sh->gun0; i < sh->gun0 + sh->ngun; i++)
		{
			sgun_t &g = g_sgun[i];
			s16 d = g.x - _wx; if (d < 0) d = -d;
			if (!g.alive || d > 16) continue;
			g.alive = false;
			g_score += 200;
			g_sky_flash_col = 0xf00;						// gun destroyed: red flash
			for (s16 j = 0; j < NHUTSMOKE; j++)
				if (!g_hutsmoke[j].puffs)
				{
					g_hutsmoke[j].x = g.x; g_hutsmoke[j].y = sh->base_y - sh->stage + 13;
					g_hutsmoke[j].puffs = 50; g_hutsmoke[j].delay = 1; break;
				}
			return;
		}
	}
	else if (_p.type == 2 && _p.state == 2 && sh->hits > 0)
	{
		g_sky_flash_col = 0xf00;						// torpedo hit: red flash
		if (--sh->hits == 0) sh->reload = 20;			// the fatal torpedo: sinking steps 20, 20, 19, 18, ...
	}
}

// ---------------------------------------------------------------------------------------------------------------------
//	own carrier record 0x25428 (FUN_12d5a): 4 torpedo hits sink it. Stage 33 takes a plane on the deck down with it
//	(lives 0, game over after 100 frames); stage 120 removes it (game over at the next respawn).

struct carrier_t { s32 x0, x1; s16 hits, stage, timer, reload; bool alive; };
static carrier_t g_carrier;
static bool carrier_afloat() { return g_carrier.alive && g_carrier.hits > 0; }
static s16 g_gameover_timer = 0;			// G_25512 (frames)

static void carrier_init()
{
	g_carrier.x0 = DECK_X0 - 16;				// rcar byte offset - 160 (4 px each)
	g_carrier.x1 = g_carrier.x0 + 768;
	g_carrier.hits = 4; g_carrier.stage = 0; g_carrier.timer = 20; g_carrier.reload = 0;
	g_carrier.alive = true;
	g_carrier_sunk = 0;
	g_carrier_ok = true;
	g_gameover_timer = 0;
}

static void carrier_remove()
{
	g_fpv_stale = true;
	g_carrier.alive = false;
	g_carrier_ok = false;
	for (s32 c = g_carrier.x0 >> 3; c <= (g_carrier.x1 >> 3); c++)
		if (c >= 0 && c < MAP_CELLS) c_map[c] = 0;
	const s16 *r = c_carrier_rm;
	for (s16 c = r[5]; c <= r[6]; c++) c_wave_src[c] = 0xffff;
	if (g_world)
	{
		for (s16 c = 0; c < r[2]; c += 24)
		{
			s16 w = r[2] - c < 24 ? r[2] - c : 24;
			g_world->multimod_copy(r[0] + c, BAND_ROW + r[9], r[1] + c, r[3], w, r[4], mymap);
		}
		if (r[8]) g_world->multimod_copy(r[7], MINI_WRECK_SRC_ROW, r[7], MINI_WRECK_DST_ROW, r[8], MINI_WRECK_ROWS, mymap);
		g_wave_drawn = -1;
	}
	sink_free(SINK_CARRIER);
}

// the sinking own carrier goes down like the ships (ship_sink_step): one tile row every 16 stages. c_carrier_rm as
// c_ship_rm, [9] = the band row of its carrier-less tiles. The wave bob of its tiles stops meanwhile (main loop).
static void carrier_sink_step()
{
	const s16 *r = c_carrier_rm;
	s16 top = r[3] + g_carrier_sunk, bot = WAVE_DST_ROW - 1;
	if (r[3] + r[4] - 1 < bot) bot = r[3] + r[4] - 1;
	if (!g_world || top > bot) return;
	for (s16 c = 0; c < r[2]; c += 24)
	{
		s16 w = r[2] - c < 24 ? r[2] - c : 24;
		for (s16 row = bot; row > top; row--)
			g_world->multimod_copy(r[1] + c, row - 1, r[1] + c, row, w, 1, mymap);
		g_world->multimod_copy(r[0] + c, BAND_ROW + r[9] + (top - r[3]), r[1] + c, top, w, 1, mymap);
	}
	g_carrier_sunk++;
}

static s16 carrier_sink_px() { return sink_smooth(SINK_CARRIER) ? g_carrier.stage : g_carrier_sunk * 16; }

// 11cd8 for the own carrier (per tick)
static void carrier_tick()
{
	if (g_gameover_timer && --g_gameover_timer == 0) game_over();	// 110c2 (frames there, ticks here)
	if (!g_carrier.alive || g_carrier.hits != 0) return;
	if (g_carrier.stage > 0 && g_carrier.stage < 120) sink_tick(SINK_CARRIER, g_carrier.stage);
	if (--g_carrier.timer > 0) return;
	g_carrier.stage++;
	if (g_phase == 1) { g_menu = false; g_phase = 2; }	// 11cd8: sinking with the plane below deck forces the launch (every step)
	g_carrier.timer = g_carrier.reload;
	if (g_carrier.reload) g_carrier.reload--;
	if (g_carrier.stage == 33 && P.state == PS_DECK)
	{
		P.state = PS_SINKING; P.y = 0;			// the plane goes down with the carrier
		g_lives = 0;
		g_gameover_timer = 100;
	}
	else if (g_carrier.stage == 120)
		carrier_remove();
	else if (g_carrier.stage >= 16 && (g_carrier.stage & 15) == 0 && !sink_smooth(SINK_CARRIER))
		carrier_sink_step();
}

// a torpedo in the water (the bomber's or the player's own) hits the own carrier
static void carrier_hit(proj_t &_p, s16 _wx)
{
	if (!g_carrier.alive || _wx < g_carrier.x0 || _wx > g_carrier.x1) return;
	if (_p.type != 1) { g_sky_flash = 5; g_sky_flash_col = 0xfff; }	// 149a6: white flash (rocket, crash, torpedo)
	if (_p.type != 2 || _p.state != 2 || g_carrier.hits <= 0) return;
	g_sky_flash = 5; g_sky_flash_col = 0xf00;		// 146dc: a torpedo hit on a ship flashes the sky red
	if (--g_carrier.hits == 0) g_carrier.reload = 20;
#if defined(WOF_DIAG)
	dbg_s("carrier hit, left "); dbg_h(g_carrier.hits); dbg_s("\n");
#endif
}

// ---------------------------------------------------------------------------------------------------------------------
//	enemy aircraft (enemies.md 7, port of FUN_1d35a..1e7d6): 4 slots. Zeros take off from airfields (11622) and ship
//	decks (11510), chase / attack / evade the player with half-loop manoeuvres, fall when shot down (+350), burn as a
//	wreck on an island. Not yet: carrier bombers (mode 4) and the bomber timer.

#define NZERO 4
struct zero_t
{
	s16 state, mode, rel, washit, health, hsub, queue, pursuit, firing, dir, mframe, mdelay, mrep;
	s16 speed, tspeed, x, fallv, talt, alt, adx, muzzle, sprite, mstep;
};
static zero_t g_zero[NZERO];
// FUN_1aa6e: the half-loop does not advance while a chasing Zero (state 2, mode 1, rel 3) is at manoeuvre frame 13
static bool zero_blocks_turn()
{
	for (s16 i = 0; i < NZERO; i++)
		if (g_zero[i].state == 2 && g_zero[i].mode == 1 && g_zero[i].rel == 3 && g_zero[i].mframe == 13) return true;
	return false;
}
static s16 g_zeros_air = 0;					// G_25126: Zeros airborne (not bombers / escapers)
static s16 g_launch_cool = 0;				// G_27298: launch cooldown (ticks)
static s16 g_bomber_timer = 1350;			// G_24fe4: next carrier bomber (ticks)
static s16 g_evaders = 0;					// G_27db6: evaders handled this tick
#define NZWRECK 16
static s16 g_zwreck[NZWRECK], g_nzwreck = 0;	// G_2512a: floating wrecks, x * dir
struct airfield_t { s16 xs, xe, maxair, parked, roll_x, roll_v, dir; };
static airfield_t g_airf[MAX_AIRF];
struct shipplanes_t { s16 n, maxair, xa, xb, roll; s16 ex[8], ey[8], edir[8]; };
static shipplanes_t g_splanes[MAX_SHIPS];
static s16 g_jroll_v = 0;					// G_2729a: J-carrier take-off roll speed
static const s16 c_zero_alt_step[6] = { 1, 2, 2, 3, 4, 5 };	// G_26148
static const s16 c_spl_destroyer[12] = { 194, 51, 1, 525, 40, -1, 484, 40, 1, 234, 51, -1 };
static const s16 c_spl_battleship[15] = { 233, 56, -1, 507, 47, 1, 746, 32, 1, 194, 56, 1, 546, 47, -1 };
static const s16 c_spl_transport[9] = { 29, 62, 1, 115, 69, -1, 76, 69, 1 };
static const s16 c_spl_jcarrier[7] = { 604, 571, 538, 505, 472, 439, 459 };
static void impact(proj_t &p);

static s16 rnd(s16 _n) { return (s16)(rnd16() % (u16)_n); }		// FUN_1cac8

static void zeros_init()
{
	for (s16 i = 0; i < NZERO; i++) g_zero[i].state = 0;
	g_zeros_air = 0; g_nzwreck = 0; g_launch_cool = 0; g_jroll_v = 0;
	g_bomber_timer = 1350;
	g_proj[NPROJ_PLAYER].state = 0;
	for (s16 k = 0; k < (s16)c_nairf; k++)
	{
		airfield_t &a = g_airf[k];
		a.xs = c_airf[k * 5]; a.xe = c_airf[k * 5 + 1]; a.maxair = c_airf[k * 5 + 2];
		a.parked = c_airf[k * 5 + 3]; a.dir = c_airf[k * 5 + 4]; a.roll_x = 0; a.roll_v = 0;
	}
	// ship plane blocks (FUN_1252c): parked entries at ship x0 + table x; launch window xa..xb around the ship
	for (s16 k = 0; k < NSHIPS; k++)
	{
		shipplanes_t &b = g_splanes[k];
		const ship_t &sh = g_ship[k];
		s16 x0 = (s16)sh.x0;
		b.n = c_ship_planes[k * 2]; b.maxair = c_ship_planes[k * 2 + 1]; b.roll = 0;
		b.xa = x0 - 200; b.xb = x0 + 620;
		const s16 *t = 0; s16 cap = 0;
		switch (sh.type)
		{
		case 0xe4:	t = c_spl_destroyer; cap = 4; break;
		case 0x10d:	t = c_spl_battleship; cap = 5; break;
		case 0xcc:	t = c_spl_transport; cap = 3; b.xb = x0 + 320; break;
		default:	cap = 7; b.xa = x0 - 250; b.xb = x0 + 20; break;
		}
		if (b.n > cap) b.n = cap;						// (battleship m9: 6 planes, 5 entries)
		for (s16 i = 0; i < cap; i++)
		{
			if (t) { b.ex[i] = x0 + t[i * 3]; b.ey[i] = t[i * 3 + 1]; b.edir[i] = t[i * 3 + 2]; }
			else { b.ex[i] = x0 + c_spl_jcarrier[i]; b.ey[i] = 16; b.edir[i] = -1; }
		}
	}
}

// FUN_1e4d0
static void zero_spawn(bool _bomber, s16 _x, s16 _alt, s16 _dir)
{
	s16 slot = -1; bool bomber_up = false;
	for (s16 i = 0; i < NZERO; i++)
	{
		if (g_zero[i].state == 0) slot = i;
		else if (g_zero[i].mode & 4) bomber_up = true;
	}
	if (slot < 0 || (_bomber && bomber_up)) return;
	zero_t &z = g_zero[slot];
	z.state = 2; z.dir = _dir; z.x = _x; z.talt = 50; z.speed = z.tspeed = 900; z.health = 240;
	z.hsub = rnd(3) + 5; z.washit = 0; z.rel = 0; z.mdelay = 0; z.mframe = 0; z.queue = 0;
	z.muzzle = 0; z.mstep = 0;			// (1e4d0 leaves fallv, pursuit, firing and mrep of the slot's last plane)
	if (!_bomber) { g_zeros_air++; z.mode = 1; z.alt = _alt; }
	else { z.mode = 4; z.alt = 50; }
}

static void zero_smoke(const zero_t &_z, s16 _n, s16 _dy) { spawn_smoke(_z.x + (s16)(rnd16() & 7), _z.alt + _dy, _n); }	// (1e75a)

// FUN_1d530: one manoeuvre step every 3 ticks
static void zero_mstep(zero_t &_z)
{
	_z.pursuit = 0;
	if (_z.mstep-- < 1) { _z.mstep = 2; _z.mframe++; }
}

// FUN_1d562: half loop / Immelmann (frames 0..26, direction flips at 14, re-engage S-turn at 20)
static void zero_manoeuvre(zero_t &_z)
{
	s16 ps = P.state;
	if (ps == 0 && (_z.mode & 3)) _z.talt = P.y;
	if (P.turn != 0 || ps != 0 || _z.mframe < 19 || (_z.rel != 1 && _z.rel != 3) || (_z.mode & 3) == 0)
	{
		zero_mstep(_z);
		if (_z.mframe >= 26) { _z.mframe = 0; _z.mode &= ~8; return; }
		if (_z.mframe == 14) { _z.dir = -_z.dir; _z.mframe++; return; }
		if (_z.mframe == 20 && (_z.mode & 3) && ps == 0)
		{
			if (_z.mrep < 3)
			{
				bool again = false;
				switch (_z.rel)
				{
				case 1:
					if (P.turn > 0 && P.turn < 6 && _z.pursuit == 0) _z.mdelay = (s16)(_z.adx * 100) / _z.speed;	// (16-bit product, as in the original)
					again = true; break;
				case 2: if (P.turn > 0 && P.turn < 6) again = true; break;
				case 3: again = true; break;
				case 4:
					if (_z.pursuit == 0) _z.mdelay = (s16)(((s32)_z.adx * 100) / (P.airspeed + _z.speed));
					again = true; break;
				}
				if (again && ps != 1 && _z.pursuit == 0) { _z.mframe -= (_z.mframe - 13) * 2; _z.mrep++; }
			}
			else { _z.mrep = 0; _z.pursuit = 550; }
		}
	}
	else { _z.mframe = 0; _z.mode &= ~8; }			// cut short: the player flies level in front of it
}

// FUN_1d9c6: chase
static void zero_chase(zero_t &_z)
{
	switch (_z.rel)
	{
	case 1:
		if (_z.adx < 160)
		{
			if (P.turn < 1 || P.turn > 5 || P.state == 1 || _z.mdelay != 0)
			{
				if (_z.adx < 160 && _z.mdelay == 0 && _z.queue == 1) _z.mode = (_z.mode & 8) | 2;
				else { _z.firing = 0; _z.talt = P.y; _z.tspeed = P.airspeed - _z.queue * 70; }
			}
			else _z.mdelay = _z.queue * 2 + (s16)(_z.adx * 100) / _z.speed;	// (16-bit product)
		}
		else if (_z.mframe == 0)
		{
			_z.tspeed = P.airspeed + _z.adx;
			if (_z.queue == 1) _z.tspeed += _z.queue * 80; else _z.tspeed -= _z.queue * 80;
		}
		break;
	case 2:
		if (P.state == 0 && P.turn > 0 && P.turn < 11) _z.tspeed = 900;
		else _z.mode |= 8;
		break;
	case 3:
		if (_z.adx < 0x600)
		{
			if (--_z.pursuit < 1 || (P.turn > 0 && P.turn < 6) || P.state == 1) { _z.mode |= 8; _z.pursuit = 0; }
			else if (_z.washit == 1)
			{
				_z.washit = 0;
				if (_z.mdelay == 0) _z.mdelay = rnd(6) + 8;
				_z.pursuit = 550;
			}
			else
			{
				_z.tspeed = P.airspeed - _z.adx / 4 + (g_evaders++) * 70;
				if (_z.alt == _z.talt) _z.talt = rnd(7) * 10 + 35;
			}
		}
		else _z.mode |= 8;
		break;
	case 4:
		if (P.state == 0)
		{
			_z.tspeed = 900;
			_z.talt = (_z.alt < P.y) ? P.y - 32 : P.y + 32;
			_z.mdelay = (s16)(((s32)_z.adx * 100) / (P.hspeed + _z.speed));
			_z.mode |= 8;
		}
		break;
	}
}

// FUN_1dccc: attack from behind; fires when level, in line and at the same altitude
static void zero_attack(zero_t &_z)
{
	if (_z.rel != 1) { _z.mode = 1; return; }
	if (P.turn == 0 && P.state != 1)
	{
		if (_z.adx >= 131) _z.tspeed = P.airspeed + 50;
		else if (_z.adx < 130) _z.tspeed = P.airspeed - 50;
	}
	else
	{
		_z.mode = 9;
		_z.mdelay = _z.adx / (_z.speed / 100);
	}
	_z.talt = P.y;
	s16 da = P.y - _z.alt; if (da < 0) da = -da;
	if (P.state == 0 && _z.mode == 2 && _z.queue == 1 && da < 8 && _z.mframe == 0 && _z.adx < 160 && P.dir == _z.dir
		&& (s16)((_z.x - (s16)P.x) ^ P.dir) < 0)
	{
		_z.firing = 1;
		if (!g_invuln && _z.alt == P.y && g_tick_parity && --g_hit_sub < 1)
		{
			P.oil -= 8;
			P.fuel -= rnd(32);
			g_hit_sub = rnd(5) + 6;
		}
	}
	else _z.firing = 0;
}

// FUN_1e17a: escaper (mode 0x10); FUN_1d18c despawns it 2600 px from the player
static void zero_escape(zero_t &_z)
{
	s16 d = (s16)P.x - _z.x; if (d < 0) d = -d;
	if (d > 0xa28) { _z.state = 0; _z.mode = 0; return; }
	if (_z.mframe != 0) return;
	if (_z.rel == 3)
	{
		if (_z.washit == 1) { _z.washit = 0; if (_z.mdelay == 0) _z.mdelay = rnd(6) + 8; _z.pursuit = 550; }
		else if (_z.alt == _z.talt && _z.adx < 160) _z.talt = rnd(7) * 10 + 25;
	}
	else if (_z.rel == 1) _z.mode |= 8;
}

// FUN_1dea4: carrier bomber: approaches the own carrier at altitude 20, drops a torpedo, then escapes (mode 0x10)
static void zero_bomber(zero_t &_z)
{
	s16 cx0 = (s16)g_carrier.x0, cx1 = (s16)g_carrier.x1;
	if (_z.rel == 3)
	{
		if (_z.washit == 1) { _z.washit = 0; if (_z.mdelay == 0) _z.mdelay = rnd(6) + 8; _z.pursuit = 0x113; }
		s16 a = _z.adx;
		if (a > 150) a = 240;
		if (a < 150) { a -= 150; if (_z.alt == _z.talt) _z.talt = rnd(7) * 10 + 35; }
		_z.tspeed = P.airspeed - a;
	}
	else if (_z.dir == -1 && _z.x < cx0 - 500) _z.mode |= 8;
	else if (_z.dir == 1 && _z.x > cx1 + 500) _z.mode |= 8;
	if (_z.dir == -1 && _z.x > cx1 && _z.x - cx1 < 1000) _z.talt = 20;
	else if (_z.dir == 1 && _z.x < cx0 && cx0 - _z.x < 1000) _z.talt = 20;
	bool before = (_z.dir == -1 && _z.x > cx1) || (_z.dir == 1 && _z.x < cx0);
	if (before)
	{
		if (_z.alt == 20 && _z.mframe == 0)
		{
			proj_t &t = g_proj[NPROJ_PLAYER];					// the 16th weapon slot
			t.state = 1; t.type = 2; t.enemy = true; t.delay = 0;
			t.x = (s32)_z.x << 16; t.y = (s32)(_z.alt + 15) << 16;
			t.dx = (s32)_z.speed * 655 * _z.dir; t.dy = 0;
			t.facing = _z.dir; t.frame = 0;
			t.px = _z.x; t.py = _z.alt + 15;
			_z.state = 2; _z.tspeed = 2600 / 2; _z.talt = 60; _z.mode = 0x10;
			g_bomber_timer = 500;
		}
	}
	else if (--_z.pursuit < 1) { _z.mode |= 8; _z.pursuit = 0; }
}

// FUN_1bc02 (per tick): while the carrier floats, a bomber comes 6144 px away 1350 ticks after the mission start and
// 500 ticks after each torpedo drop. The timer only runs on ticks without the fire button; pressing fire puts it
// back to at least 750 ticks (one minute), so an active player meets far fewer bombers.
static u8 g_tick_in = 0;				// the input word of the current tick (G_26c92)
static void bomber_tick()
{
	if (g_tick_in & (IN_TAP | IN_HOLD))
	{
		if (g_bomber_timer != 0 && g_bomber_timer < 750) g_bomber_timer = 750;
		return;
	}
	if (!g_bomber_timer || !g_carrier.alive || g_carrier.hits <= 0) return;
	if (--g_bomber_timer != 0) return;
	s16 d = 0x7fff - (s16)P.x; if (d < 0) d = -d;
	if (d <= 0x1a00) return;
	if ((s16)P.x < (s16)g_carrier.x0 || ((s16)P.x <= (s16)g_carrier.x1 && (rnd16() & 0x8000)))
		zero_spawn(true, (s16)P.x - 0x1800, 50, 1);
	else
		zero_spawn(true, (s16)P.x + 0x1800, 50, -1);
}

// FUN_1e244: shot down, falling; at the target altitude it skids on the sea or crashes on an island
static void zero_fall(zero_t &_z)
{
	if ((s16)(rnd16() & 63) < 128 - _z.health) zero_smoke(_z, ((128 - _z.health) >> 3) + 1, 10);
	if (_z.alt != _z.talt) return;
	u16 c = map_cell(_z.x);
	if (cell_surface(c) == 0 && _z.speed < 300)
	{
		static s16 s_skid = 0;
		if (++s_skid > 1) { s_skid = 0; _z.talt--; }
		_z.speed += 24;
	}
	_z.speed -= 35;
	soldiers_kill(_z.x, 20);
	if (_z.speed > 500)
	{
		proj_t t; t.x = (s32)_z.x << 16; t.type = 0; t.state = 0;	// 146c6: hits the ground like a rocket
		impact(t);
	}
	crash_fx_splash(_z.x + _z.dir * 4);				// 1e35c: FUN_152ac, the gun-impact splash / puff
	if (_z.speed < 100)
	{
		g_zero_kills++;
		if (cell_surface(c) != 2)
		{
			if (_z.mode != 4 && _z.mode != 0x10) g_zeros_air--;
			_z.state = 0; _z.mode = 0;
		}
		else { _z.state = 0x10; _z.tspeed = 6; _z.speed = 30; _z.mode = 0; }
	}
}

// FUN_1e3e8: burning wreck on an island; then a floating wreck in the list
static void zero_wreck(zero_t &_z)
{
	if (--_z.speed == 0) { _z.tspeed--; _z.speed = _z.tspeed * 5; }
	if (_z.tspeed < 2)
	{
		if (g_nzwreck < NZWRECK) g_zwreck[g_nzwreck++] = _z.dir * _z.x;
		if (_z.mode != 4 && _z.mode != 0x10) g_zeros_air--;
		_z.state = 0; _z.mode = 0;
	}
	else if ((_z.speed & 3) == 0) spawn_smoke(_z.x - 4 + (s16)(rnd16() & 7), 6, _z.tspeed);	// (1e45e)
}

// FUN_1d796: speed, altitude, x, manoeuvre trigger
static void zero_move(zero_t &_z)
{
	if ((_z.state & 0x14) == 0 && (P.state == 4 || P.state == 8 || P.state == 6)) _z.tspeed = 1700;
	_z.x += (s16)(((s32)((_z.speed / 100) * _z.dir) * c_turncos16[_z.mframe]) >> 16);
	if ((_z.state & 0x14) == 0 && (_z.mode & 4) == 0)
	{
		if (P.state == 1) _z.talt = 70;
		if (_z.talt < 33) _z.talt = 33;
	}
	s16 d = _z.talt - _z.alt; if (d < 0) d = -d;
	if (d > 100) d = 100;
	if (_z.state & 4)
	{
		if (_z.talt < _z.alt) { _z.alt += _z.fallv / 100; _z.fallv -= 10; }
		else if (_z.alt < _z.talt) _z.alt = _z.talt;
	}
	if (_z.talt < _z.alt) _z.alt -= rnd(2) + c_zero_alt_step[d / 20];		// (no clamp: it may overshoot, 1d924 / 1d966)
	else if (_z.alt < _z.talt) _z.alt += rnd(2) + c_zero_alt_step[d / 20];
	if ((_z.state & 0x14) == 0 && _z.mdelay != 0 && --_z.mdelay < 1) { _z.mode |= 8; _z.mdelay = 0; }
	if ((_z.mode & 8) && _z.state == 2) zero_manoeuvre(_z);
}

// FUN_1e7d6 (per logic tick) + launches (11622 airfields, 11510 ships)
static void zeros_tick()
{
	if (g_launch_cool > 0) g_launch_cool--;
	// airfields: a rolling plane accelerates and lifts off past the end; else maybe launch the next parked one
	bool rolling = false;
	for (s16 k = 0; k < (s16)c_nairf && !rolling; k++)
	{
		airfield_t &a = g_airf[k];
		if (!a.roll_x) continue;
		rolling = true;
		if (++a.roll_v > 56) a.roll_v = 56;
		a.roll_x += a.dir * (a.roll_v >> 3);
		if ((a.dir == -1 && a.roll_x < a.xs) || (a.dir != -1 && a.roll_x > a.xe))
		{
			zero_spawn(false, a.roll_x, 0, a.dir);
			a.roll_x = 0;
		}
	}
	if (!rolling && g_launch_cool == 0 && !g_out)			// (g_out: as aa_hit)
		for (s16 k = 0; k < (s16)c_nairf; k++)
		{
			airfield_t &a = g_airf[k];
			if ((s16)P.x < a.xs - 480 || (s16)P.x > a.xe + 480) continue;
			if (g_zeros_air >= a.maxair || a.parked < 1) break;
			a.parked--;
			g_launch_cool = 100;
			a.roll_x = (a.dir == -1) ? a.xe - 32 - 64 * a.parked : a.xs + 32 + 64 * a.parked;
			a.roll_v = 0;
		}
	// ships: the J-carrier's plane rolls off the bow; the others lift straight off the deck
	for (s16 k = 0; k < NSHIPS; k++)
	{
		shipplanes_t &b = g_splanes[k];
		if (!b.roll || b.n == 0) continue;
		g_jroll_v = g_jroll_v + 8 - (g_jroll_v >> 4);
		b.ex[b.n - 1] -= g_jroll_v >> 4;
		if (b.ex[b.n - 1] < (s16)g_ship[k].x0) { b.n--; b.roll = 0; zero_spawn(false, b.ex[b.n], 33, -1); }
	}
	if (g_launch_cool == 0 && !g_out)
		for (s16 k = 0; k < NSHIPS; k++)
		{
			shipplanes_t &b = g_splanes[k];
			const ship_t &sh = g_ship[k];
			if (!sh.alive || sh.hits <= 0 || b.roll || (s16)P.x < b.xa || (s16)P.x > b.xb) continue;
			if (g_zeros_air >= b.maxair || b.n == 0) continue;
			if (sh.type == 0xf2)
			{
				b.roll = 1; g_jroll_v = 0;
				b.ex[b.n - 1] = (s16)sh.x0 + 380; b.ey[b.n - 1] = 33;
				g_launch_cool = 100;
				break;
			}
			b.n--;
			zero_spawn(false, b.ex[b.n], b.ey[b.n], -1);
			g_launch_cool = 100;
		}

	bomber_tick();
	g_evaders = 0;
	for (s16 i = 0; i < NZERO; i++)
	{
		zero_t &z = g_zero[i];
		if (!z.state) continue;
		// 1d3b4 relation to the player
		s16 dx = z.x - (s16)P.x;
		if (P.dir == z.dir)
		{
			z.rel = 1;
			if ((s16)(dx ^ P.dir) >= 0) { z.rel = 3; if (z.pursuit == 0) z.pursuit = 550; }
		}
		else z.rel = (dx < 0) ? 4 : 2;
		z.adx = dx < 0 ? -dx : dx;
		// 1d476 queue among the planes behind the player (as in the original: every slot with a mode and rel 1 is
		// ranked by distance, attackers included; a farther lower slot is moved back; no state test in the inner loop)
		for (s16 j = 0; j < NZERO; j++)
		{
			zero_t &a = g_zero[j];
			if (a.mode == 0 || a.rel != 1) continue;
			s16 q = 1;
			for (s16 m = 0; m < j; m++)
			{
				if (g_zero[m].rel != 1) continue;
				if (g_zero[m].adx < a.adx) q++; else g_zero[m].queue++;
			}
			a.queue = q;
		}
		if (z.state == 2)
		{
			// 1e728: smoke when damaged, then the mode handler
			if ((s16)(rnd16() & 63) < 128 - z.health) zero_smoke(z, ((128 - z.health) >> 3) + 1, 11);
			switch (z.mode & ~8)
			{
			case 1: zero_chase(z); break;
			case 2: zero_attack(z); break;
			case 4: zero_bomber(z); break;
			case 0x10: zero_escape(z); break;
			}
			if (!z.state) continue;
			if ((z.mode & 4) == 0 && z.talt < 33) z.talt = 33;
		}
		else if (z.state == 4) zero_fall(z);
		else if (z.state == 0x10) zero_wreck(z);
		if (!z.state) continue;
		if (z.state == 2)								// 1e64e speed toward the target
		{
			if (z.tspeed < 900) z.tspeed = 900;
			if (z.tspeed > 2600) z.tspeed = 2600;
			if (z.speed < z.tspeed) { z.speed += (z.tspeed - z.speed) / 2 + 5; if (z.speed > 2600) z.speed = 2600; }
			else if (z.speed > z.tspeed) { z.speed -= (z.speed - z.tspeed) / 2 - 5; if (z.speed < 900) z.speed = 900; }
		}
		if (z.state != 0x10) zero_move(z);
		// 1d35a sprite index
		s16 f = z.mframe;
		if ((z.mode & 4) && z.mframe == 0) f = 26;
		if (z.state == 0x10) f = 27;
		z.sprite = (z.dir == -1) ? f : f + 28;
	}
}

// FUN_1b682 (per tick while the gun fires): Zeros in the gun line take hits; 19 hits -> shot down (+350)
static void zeros_gun_tick()
{
	if (!g_gun_firing) return;
	for (s16 i = 0; i < NZERO; i++)
	{
		zero_t &z = g_zero[i];
		if (z.state != 2 || z.rel != 3) continue;
		s16 da = P.y - z.alt; if (da < 0) da = -da;
		if (z.adx >= 160 || da >= 20 || P.pitch != 0) continue;
		z.washit = 1;
		if (--z.hsub < 1)
		{
			zero_smoke(z, 6, 10);
			z.health -= 8;
			if (z.health < 96)
			{
				g_score += 350;
				z.state = 4; z.talt = -3; z.mframe = 0; z.mode &= ~8;
			}
			z.hsub = rnd(4) + 6;
		}
	}
}

// drawing (10da6 planes + muzzle flash + wrecks, 13a18 airfield planes, 1391e ship deck planes): a list of draw items
// for the ZERO entity pool, culled to the view
#define NZDRAW 14
struct zdraw_t { s16 x, y, frame; bool direct; };	// world x, image y of the frame anchor, sheet frame
// direct: AGT's entity pass skips every sprite whose left edge is more than the guard band (32 px) left of the screen,
// so a 112 px wide plane cell would vanish with the plane still in view: those are drawn directly (clipped) instead
static zdraw_t g_zd[NZDRAW];
static s16 g_nzd = 0;

static s16 g_zd_dx = 0;					// 1/8 view: g_mini_dx for what the treadmill moves with the plane
static void zd_add(s16 _x, s16 _alt, s16 _frame)
{
	if (g_nzd >= NZDRAW) return;
	s16 ix = _x + MARGIN;
	if (g_zoom)
	{
		ix = MINI_X0 + (ix >> 3) + g_zd_dx;
		if (ix < g_cam_x - 48 || ix > g_cam_x + SCREEN_XSIZE + 48) return;
		g_zd[g_nzd].x = ix - MI_AX;
		g_zd[g_nzd].y = MINI_ROW + MINI_SEA - 151 + ((1208 - _alt) >> 3) - MI_AY;
		g_zd[g_nzd].direct = false;
	}
	else
	{
		if (ix < g_cam_x - 64 || ix > g_cam_x + SCREEN_XSIZE + 64) return;
		g_zd[g_nzd].x = ix - ZP_AX;
		g_zd[g_nzd].y = WATER_ROW - _alt - ZP_AY;
		g_zd[g_nzd].direct = g_zd[g_nzd].x < g_cam_x - c_viewport_xmargin + 16;	// (16: the camera may move before the draw)
	}
	g_zd[g_nzd].frame = _frame;
	g_nzd++;
}

#if defined(WOF_REPLAY)
static s16 g_rp_zpass = 0;					// ZPASS: frame counter of the test plane, 0 = off
#endif
static void zeros_draw_build()
{
	g_nzd = 0;
#if defined(WOF_REPLAY)
	if (g_rp_zpass) { zd_add((s16)P.x + 260 - g_rp_zpass * 6, 50, c_fr_zero[0]); if (++g_rp_zpass > 100) g_rp_zpass = 0; }
#endif
	for (s16 i = 0; i < NZERO; i++)
	{
		zero_t &z = g_zero[i];
		if (!z.state) continue;
		s16 alt = (z.state == 0x10) ? 4 : z.alt + 7;
		{ s16 dz = z.x - (s16)P.x; g_zd_dx = (dz > -600 && dz < 600) ? g_mini_dx : 0; }		// (as world_shift)
		zd_add(z.x, alt, g_zoom ? c_fr_zmini[z.sprite] : c_fr_zero[z.sprite]);
		g_zd_dx = 0;
		if (z.firing && !g_zoom && (++z.muzzle & 1))			// 10e98: on odd counts, the frame from bit 1
			zd_add(z.x, alt, z.dir == -1 ? ((z.muzzle & 2) ? ZP_FR_FD1A : ZP_FR_FC1A) : ((z.muzzle & 2) ? ZP_FR_FD10 : ZP_FR_FC10));
	}
	for (s16 i = 0; i < g_nzwreck; i++)
	{
		s16 w = g_zwreck[i];
		zd_add(w < 0 ? -w : w, 4, g_zoom ? c_fr_zmini[w < 0 ? 27 : 55] : c_fr_zero[w < 0 ? 27 : 55]);
	}
	for (s16 k = 0; k < (s16)c_nairf; k++)
	{
		const airfield_t &a = g_airf[k];
		s16 fr = g_zoom ? c_fr_zmini[a.dir == -1 ? 0 : 28] : (a.dir == -1 ? ZP_FR_PARK1 : ZP_FR_PARK2);
		for (s16 n = 0; n < a.parked; n++)
			zd_add(a.dir == -1 ? a.xe - 32 - 64 * n : a.xs + 32 + 64 * n, 0, fr);
		if (a.roll_x) zd_add(a.roll_x, 0, fr);
	}
	for (s16 k = 0; k < NSHIPS; k++)
	{
		const shipplanes_t &b = g_splanes[k];
		const ship_t &sh = g_ship[k];
		if (!sh.alive) continue;
		for (s16 n = 0; n < b.n; n++)
			zd_add(b.ex[n], b.ey[n] - sh.stage, g_zoom ? c_fr_zmini[b.edir[n] == -1 ? 0 : 28] : (b.edir[n] == -1 ? ZP_FR_PARK1 : ZP_FR_PARK2));
	}
}

void zero_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	s16 k = self.counter;
	if (k >= g_nzd || g_zd[k].direct) { self.drawtype = EntityDraw_NONE; return; }
	self.rx = g_zd[k].x; self.ry = g_zd[k].y; self.frame = g_zd[k].frame;
	if (g_zoom) { self.passet = zmini_asset.get(); self.drawtype = EntityDraw_IMSPR; }
	else { self.passet = zero_asset.get(); self.drawtype = EntityDraw_IMSPR; }
}

// FUN_14fee: an empty bunker calls one soldier from the nearest hut with at least 2 inside, searching its own island
// first, then the later islands
static void bunker_reman(building_t &_b)
{
	building_t *best = 0;
	for (s16 isl = _b.island; isl < MAX_ISLANDS && !best; isl++)
	{
		s16 bd = 0x7fff;
		for (s16 i = 0; i < NBUILD; i++)
		{
			building_t &h = g_build[i];
			if (h.bunker || h.inside < 2 || h.island != isl) continue;
			s16 d = h.x - _b.x; if (d < 0) d = -d;
			if (d < bd) { bd = d; best = &h; }
		}
	}
	if (!best) return;
	best->inside--;
	soldier_spawn(*best, (best->x > _b.x) ? -1 : 1);
}

static void vis_build()
{
	// guns and soldiers within the view (+ a sprite width), normal or 1/8 view coordinates
	s16 x0 = g_cam_x - 64, x1 = g_cam_x + SCREEN_XSIZE + 64;
	g_gun_nvis = 0;
	for (s16 i = 0; i < NBUILD && g_gun_nvis < NGUN_ENT; i++)
	{
		if (g_gun_frame[i] < 0) continue;
		s16 x = g_zoom ? MINI_X0 + ((g_build[i].x + MARGIN) >> 3) : g_build[i].x + MARGIN;
		if (x >= x0 && x <= x1) g_gun_vis[g_gun_nvis++] = i;
	}
	for (s16 i = 0; i < NPILLBOXES && g_gun_nvis < NGUN_ENT; i++)
	{
		if (g_pill_gun[i] < 0) continue;
		s16 x = g_zoom ? MINI_X0 + ((g_pill[i].x + MARGIN) >> 3) : g_pill[i].x + MARGIN;
		if (x >= x0 && x <= x1) g_gun_vis[g_gun_nvis++] = MAX_BUILD + i;
	}
	for (s16 i = 0; i < g_nsgun && g_gun_nvis < NGUN_ENT; i++)
	{
		if (g_sgun_frame[i] < 0) continue;
		s16 x = g_zoom ? MINI_X0 + ((g_sgun[i].x + MARGIN) >> 3) : g_sgun[i].x + MARGIN;
		if (x >= x0 && x <= x1) g_gun_vis[g_gun_nvis++] = MAX_BUILD + MAX_PILLBOXES + i;
	}
	g_sold_nvis = 0;
	for (s16 i = 0; i < NSOLD && g_sold_nvis < NSOLD_ENT; i++)
	{
		const soldier_t &so = g_sold[i];
		if (so.state != 1 && so.state != 2) continue;
		s16 x = g_zoom ? MINI_X0 + ((so.x + MARGIN) >> 3) : so.x + MARGIN;
		if (x >= x0 && x <= x1) g_sold_vis[g_sold_nvis++] = i;
	}
}

// FUN_13d78 (per drawn frame)
static void bunkers_frame_tick()
{
	mini_pill_sync();
	for (s16 i = 0; i < NBUILD; i++)
	{
		building_t &b = g_build[i];
		g_gun_frame[i] = -1;
		if (!b.bunker) continue;
		if (b.inside == 0)
		{
			if (--b.reman <= 0) { b.reman = 200; bunker_reman(b); }
			continue;
		}
		if (b.silent && --b.silent) continue;
		s16 f = aa_aim(b.x);
		g_gun_frame[i] = f;
		if (f >= 0) aa_hit(b.x);
	}
	for (s16 i = 0; i < NPILLBOXES; i++)			// 13de8: every intact pillbox
	{
		g_pill_gun[i] = -1;
		if (!g_pill[i].alive) continue;
		s16 f = aa_aim(g_pill[i].x);
		g_pill_gun[i] = f;
		if (f >= 0) aa_hit(g_pill[i].x);
	}
}

static void wreck_hut(s16 ci)
{
	s16 a = ci, b = ci;
	while (a > 0 && ((c_map[a - 1] >> 2) & 0x1ff) == 4) a--;
	while (b < MAP_CELLS - 1 && ((c_map[b + 1] >> 2) & 0x1ff) == 4) b++;
	s16 anchor = -1;
	for (s16 i = a; i <= b; i++)
	{
		if (c_map[i] & 0x8000) anchor = i;
		c_map[i] = (c_map[i] & ~(0x1ff << 2)) | (5 << 2);
	}
	if (anchor >= 0 && g_world)
	{
		s16 x0 = MARGIN + anchor * 8 - 16;		// drawn at cell_x - hot_x ('huta' hot_x = 16, 32 px wide)
		s16 c0 = x0 >> 4;
		for (s16 k = 0; k < NHUTS; k++)				// source block of this hut in the band
			if (c_hut_cells[k] == anchor)
				g_world->multimod_copy(c_wreck_src[k], WRECK_SRC_ROW, c0, WRECK_DST_ROW, 3, WRECK_ROWS, mymap);
		// 1/8 view: 8thscale 'huta' (16 px, hot_x 8) at MINI_X0 + MARGIN/8 + cell - hot_x
		s16 m0 = (MINI_X0 + MARGIN / 8 + anchor - 8) >> 4;
		g_world->multimod_copy(m0, MINI_WRECK_SRC_ROW, m0, MINI_WRECK_DST_ROW, 2, MINI_WRECK_ROWS, mymap);
	}
	if (anchor >= 0)
	{
		building_t *b = building_at(anchor * 8);
		if (b && !b->bunker) building_empty(*b);
		for (s16 i = 0; i < NHUTSMOKE; i++)
			if (!g_hutsmoke[i].puffs) { g_hutsmoke[i].x = anchor * 8 + 8; g_hutsmoke[i].y = 17; g_hutsmoke[i].puffs = 50; g_hutsmoke[i].delay = 1; break; }
	}
	g_score += 150;
}

// impact resolution FUN_000146dc (bombs: huts only; bunkers/pillboxes/ships/soldiers not implemented yet)
static void impact(proj_t &p)
{
	s16 wx = (s16)(p.x >> 16);
	s16 ci = wx >> 3;
	if (ci < 0 || ci >= MAP_CELLS) return;
	u16 c = c_map[ci];
	s16 t = (c >> 2) & 0x1ff;
	// 1470e: a rocket (or a crashing plane, which counts as one) on an island flashes the sky white, red if it
	// hits a bunker, hut or pillbox
	if (cell_surface(c) == 2 && p.type == 0) { g_sky_flash = 5; g_sky_flash_col = 0xfff; }
	if (cell_surface(c) == 2 && t == 4)
	{
		if (p.type == 0) g_sky_flash_col = 0xf00;
		wreck_hut(ci);
	}
	else if (t == 3)
	{
		building_t *b = building_at(wx);			// bunkers are indestructible; a manned one empties (+200)
		if (b && b->bunker && p.type == 0) g_sky_flash_col = 0xf00;
		if (b && b->bunker && b->inside) { b->reman = 200; g_score += 200; building_empty(*b); }
	}
	else if (t >= 0x0f && t <= 0x1e && p.type == 0)
	{
		g_sky_flash_col = 0xf00;
		pillbox_hit(wx);							// pillboxes: rockets only
	}
	if (cell_surface(c) != 2)							// sea / deck surface: ships and the own carrier (14a4e)
	{
		carrier_hit(p, wx);							// (the player's own torpedo counts too)
		if (!p.enemy) ship_hit(p, wx);
	}
#if defined(WOF_DIAG)
	dbg_s("impact x="); dbg_h(wx); dbg_s(" t="); dbg_h(t); dbg_s(" w="); dbg_h(p.type); dbg_s("\n");
#endif
	soldiers_kill(wx, 16);
}

// FUN_10820(cell under x, y, 0): explosion at the cell's x (x rounded down to 8 px), altitude y + 12, boom by distance
static void crash_fx_explosion(s32 x, s16 y)
{
	if (x < 0) x = 0;					// (1c982 clamps)
	x &= ~7;
	s16 surf = cell_surface(map_cell(x));
	spawn_explosion((s16)x, y + 12, surf == 0 ? 1 : surf);
	snd_play(2, SND_BOOM, snd_dist_vol((s16)x, (s16)P.x, P.y), 0);
}
static void crash_fx_splash(s32 x)			// FUN_152ac: the first free of the 20 slots; none free = no splash
{
	for (s16 i = 0; i < NIMPACT; i++)
	{
		impact_t &im = g_impact[i];
		if (im.timer) continue;
		im.x = (s16)x;
		im.surf = cell_surface(map_cell(x));
		im.timer = (im.surf == 2) ? 5 : 7;		// (one more than the Amiga's 4 / 6: here the timer is counted down before the first draw)
		return;
	}
}
static void crash_ground_impact(s32 x)			// FUN_146c6: a full impact of weapon type 0 (rocket)
{
	proj_t t;
	t.x = x << 16; t.type = 0; t.state = 0; t.enemy = false;
	impact(t);
}

// launch FUN_000107f2
static void release_ordnance()
{
	if (g_ammo == 0) return;
	for (s16 i = 0; i < NPROJ_PLAYER; i++)
	{
		proj_t &p = g_proj[i];
		if (p.state) continue;
		g_ammo--;
		p.state = 1;
		p.enemy = false;
		p.type = g_weapon;
		p.dy = (s32)P.vspeed << 16;
		p.dx = ((s32)P.hspeed << 16) * P.dir;
		p.y = (s32)(P.y + 11) << 16;
		p.x = P.x << 16;
		p.frame = (p.dx < 0) ? 3 : 9;
		p.facing = P.dir;
		p.px = (s16)P.x; p.py = P.y + 11;
		if (p.type == 0)
		{
			// rocket: thrust along the plane's pitch (G_25354 >> 1, 1024 per turn), ~1 px/tick^2
			s16 ang = (s16)(((s32)P.pitch_smooth * 1024) / 18000);		// [25354] 2048 per turn
			s16 a = ang >> 1;
			p.ddy = sin1024(a);
			p.ddx = cos1024(a) * (p.dx < 0 ? -1 : 1);
			p.ang = a; p.spd = P.airspeed;
			s16 d = (s16)(((rnd16() >> 12) << 1) & 12);		// (rnd4 rol 1) & 12: 4, 8 or 12 ticks (0 -> 8)
			p.delay = d ? d : 8;
			s16 f = 4 - (ang >> 5); if (f < 0) f = 0; if (f > 9) f = 9;
			p.frame = f + (p.dx < 0 ? 10 : 0);
#if defined(WOF_DIAG)
			dbg_s("rocket delay="); dbg_h(p.delay); dbg_s(" frame="); dbg_h(p.frame); dbg_s(" ddx="); dbg_h((u32)p.ddx); dbg_s(" ddy="); dbg_h((u32)p.ddy); dbg_s("\n");
#endif
		}
		return;
	}
}

// per-tick projectile update FUN_00010aa6 (bomb branch)
// projectile hit the ground / sea / a deck: impact, sound, explosion animation
static void proj_explode(proj_t &p, s16 surf, s16 wx)
{
	p.surf = surf;
	impact(p);
	// FUN_10aa6: boom on land / deck (ch2 slot 0), splash on water (slot 1), volume by distance
	if (surf == 0) snd_play(2, SND_SPLASH, snd_dist_vol(wx, (s16)P.x, P.y), 1);
	else snd_play(2, SND_BOOM, snd_dist_vol(wx, (s16)P.x, P.y), 0);
	p.state = 8;
	p.anim = 1;
}

// FUN_11a46: x where the player's line of sight at angle _a (1024 per turn, < 0 = down) meets the sea, 0 = none
static s16 ray_x(s16 _a)
{
	if (_a >= 0) return 0;
	if (_a == -255) _a++;
	s16 t = c_tantab[(-_a) & 255];
	if (t <= 0) return 0;
	s32 dist = ((s32)P.y * 256) / t;
	return (s16)(P.x + (P.dir >= 0 ? dist : -dist));
}

// FUN_1099a: rocket ignition at the end of the drop. Fired nose-down, it looks along the player's line of sight
// (angle, +20, -20) for a ship gun (FUN_111a6), else an intact pillbox (FUN_1115c), and flies straight at it:
// velocity = (cos, sin)(-atan(y / dx)) * airspeed / 100 with the half-amplitude sine table (5 px/tick at cruise)
static void rocket_ignite(proj_t &p)
{
	s16 a = p.ang >> 1;
	if (a >= 0) return;
	s16 x7 = ray_x(a), x6 = ray_x(a + 20), x5 = ray_x(a - 20);
	if (!x7 || !x6 || !x5) return;
	s16 tx = 0;
	for (s16 pass = 0; pass < 2 && !tx; pass++)				// ship guns between x7 and x6, then x7 and x5
	{
		s16 lo = x7, hi = pass ? x5 : x6;
		if (hi < lo) { s16 t = lo; lo = hi; hi = t; }
		for (s16 i = 0; i < g_nsgun && !tx; i++)
		{
			const ship_t &sh = g_ship[g_sgun[i].ship];
			if (sh.alive && g_sgun[i].x >= lo && g_sgun[i].x <= hi) tx = g_sgun[i].x;
		}
	}
	for (s16 pass = 0; pass < 2 && !tx; pass++)				// intact pillboxes, in map byte offsets (4 px)
	{
		s16 lo = x7 >> 2, hi = (pass ? x5 : x6) >> 2;
		if (hi < lo) { s16 t = lo; lo = hi; hi = t; }
		for (s16 i = 0; i < NPILLBOXES && !tx; i++)
			if (g_pill[i].alive && c_pill_cells[i] * 2 >= lo && c_pill_cells[i] * 2 < hi) tx = c_pill_cells[i] * 8;
	}
	if (!tx) return;
	s16 dx = tx - (s16)(p.x >> 16); if (dx < 0) dx = -dx;
	s16 y = (s16)(p.y >> 16);
	// FUN_15ca6 atan2: the angle whose tangent is y / dx (c_tantab = 256 * tan, 1024 per turn)
	s16 best = 1; s32 be = 0x7fffffff;
	for (s16 k = 1; k < 256; k++)
	{
		s32 e = (s32)c_tantab[k] * dx - (s32)y * 256; if (e < 0) e = -e;
		if (e < be) { be = e; best = k; }
	}
	if (dx == 0) best = 255;
	s16 spd = (s16)((u16)p.spd / 100);
	s32 ndx = (cos1024(best) >> 1) * spd;
	p.dx = (p.dx < 0) ? -ndx : ndx;
	p.dy = -((sin1024(best) >> 1) * spd);
#if defined(WOF_DIAG)
	dbg_s("rocket homing on x="); dbg_h(tx); dbg_s("\n");
#endif
}

// per-tick update FUN_00010aa6 (weapons_missions.md 2.2): bombs, rockets, torpedoes
// A running torpedo reaches a ship or the shore (10d7c): the hit counts and sounds (boom, then splash), but nothing
// is drawn: the Amiga's draw routine leaves a running torpedo before its explosion code (10730; checked 2026-10-08)
static void torpedo_hit(proj_t &p, s16 surf, s16 wx)
{
	p.surf = surf;
	impact(p);
	snd_play(2, SND_BOOM, snd_dist_vol(wx, (s16)P.x, P.y), 0);
	snd_play(2, SND_SPLASH, snd_dist_vol(wx, (s16)P.x, P.y), 1);
	p.state = 0;
}

static void projectiles_tick()
{
	for (s16 i = 0; i < NPROJ; i++)
	{
		proj_t &p = g_proj[i];
		if (p.state == 2)									// torpedo running in the water
		{
			p.px = (s16)(p.x >> 16);
			if (--p.life <= 0) { p.state = 0; continue; }
			p.x += p.dx;
			s16 wx = (s16)(p.x >> 16);
			s16 surf = (wx < 0 || (wx >> 3) >= MAP_CELLS) ? 0 : cell_surface(map_cell(wx));
			if (surf != 0) { torpedo_hit(p, surf, wx); continue; }
			crash_fx_splash(wx);							// the visible wake (FUN_152b0 every tick)
			continue;
		}
		if (p.state != 1) continue;
		p.px = (s16)(p.x >> 16);
		p.py = (s16)(p.y >> 16);
		s16 ny;
		if (p.type == 0)
		{
			if (p.delay)
			{
				if (--p.delay == 0)
				{
					rocket_ignite(p);						// may re-aim at a ship gun / pillbox
					p.dy += p.ddy; p.dx += p.ddx;
#if defined(WOF_DIAG)
					dbg_s("rocket ignite\n");
#endif
				}
				else { p.x -= (s32)p.facing << 16; p.y -= 0x10000; }		// drop-away: slips back 1 px, falls 1 px
			}
			else { p.dy += p.ddy; p.dx += p.ddx; }
			p.x += p.dx;
			s32 d = (p.x >> 16) - P.x; if (d < 0) d = -d;
			if (d - 640 > (g_zoom ? 640 + 4480 : 640)) { p.state = 0; continue; }
			ny = (s16)((p.y + p.dy + p.ddy) >> 16);
		}
		else
		{
			s32 dxi = p.dx >> 16;
			p.dx -= (dxi / 10) << 16;					// drag removes whole pixels only
			p.x += p.dx;
			p.dy -= g_gravity;							// gravity 0.375 px/tick^2
			ny = (s16)((p.y + p.dy) >> 16);
		}
		s16 wx = (s16)(p.x >> 16);
		bool zone = false;								// FUN_11126: over an airfield (x_start..x_end)
		for (s16 k = 0; k < c_nairf && !zone; k++) zone = wx >= g_airf[k].xs && wx <= g_airf[k].xe;
		if (zone)
		{
			// airfields can't be hit: below altitude 30 a rocket vanishes, a bomb or torpedo bounces (dy reversed
			// and halved, dx halved) until either reaches 0
			if (ny > 30)
			{
				if (p.type == 0) p.y = ((s32)ny << 16) | (p.y & 0xffff); else p.y += p.dy;
			}
			else if (p.type == 0) { p.state = 0; continue; }
			else
			{
				p.y = (s32)30 << 16;
				s16 di = (s16)((-p.dy) >> 16) >> 1; if (di > 9) di = 9;
				p.dy = ((s32)di << 16) | (p.dy & 0xffff);
				s16 xi = (s16)(p.dx >> 16) >> 1;
				p.dx = ((s32)xi << 16) | (p.dx & 0xffff);
				if (di == 0 || xi == 0) { p.state = 0; continue; }
			}
			if (p.type == 1 && g_tick_parity) p.frame = (p.frame + 1) % 12;
			continue;
		}
		u16 c = map_cell(wx);
		s16 surf = (wx < 0 || (wx >> 3) >= MAP_CELLS) ? 0 : cell_surface(c);
		s16 ground = (surf == 1) ? obj_height(c) + 11 : 12;
		if (ny <= ground)
		{
			p.y = (s32)ground << 16;
			if (p.type == 2 && surf == 0 && (p.dy >> 16) >= -5)
			{
				// torpedo enters the water: runs at 4.3125 px/tick, 199 steps = 858 px (not drawn, only its wake).
				// The first step is made in this tick, with the first splash at the new x: none where it went in
				// (10d50; checked against the Amiga 2026-10-08: in at 5646, first splash at 5641)
				p.dx = (p.dx < 0) ? -0x45000 : 0x45000;
				p.life = 199;
				p.state = 2;
				snd_play(2, SND_SPLASH, snd_dist_vol(wx, (s16)P.x, P.y), 1);
				p.x += p.dx;
				wx = (s16)(p.x >> 16);
				surf = (wx < 0 || (wx >> 3) >= MAP_CELLS) ? 0 : cell_surface(map_cell(wx));
				if (surf != 0) torpedo_hit(p, surf, wx);
				else crash_fx_splash(wx);
				continue;
			}
			proj_explode(p, surf, wx);
		}
		else if (p.type == 0)
			p.y = ((s32)ny << 16) | (p.y & 0xffff);		// rocket: y = predicted int (ddy counted twice, as the original)
		else
			p.y += p.dy;
		if (p.type == 1 && g_tick_parity) p.frame = (p.frame + 1) % 12;	// tumbling bomb
	}
}

// machine gun ground strafing FUN_000119bc / FUN_00011a46: one ray per tick, no travel time
static void gun_tick(u8 in)
{
	g_gun_firing = (in & IN_HOLD) && P.state == PS_FLYING && P.turn == 0;
	if (!g_gun_firing) return;
	if (P.vspeed >= 0 || P.y >= 160 || P.landing_attitude) return;
	s32 angle = ((s32)P.pitch_smooth * 1024) / 18000;		// [25354] binary angle, 2048/turn
	if (angle >= 0) return;
	s16 t = c_tantab[(-angle) & 255];						// table is 1024/turn: original aims at twice the dive angle
	if (t <= 0) return;
	s32 dist = ((s32)P.y * 256) / t;
	s32 xh = P.x + (P.dir >= 0 ? dist : -dist);
	crash_fx_splash(xh);
	soldiers_kill((s16)xh, 16);					// FUN_119bc: bullets kill soldiers too
}

// deck crew arms (FUN_00013b1c, type 0x9f): two poses walk toward targets that alternate between table pairs
static const s16 c_crew_a[6][2] = { {1,1}, {1,7}, {1,7}, {0,0}, {7,7}, {4,4} };	// 0x255ac
static const s16 c_crew_b[6][2] = { {1,7}, {1,1}, {1,7}, {0,0}, {7,7}, {4,4} };	// 0x255c4
static s16 g_crew_sig = -1, g_crew_a = 1, g_crew_at = 1, g_crew_b = 1, g_crew_bt = 1;
static s16 g_flash_ctr = 0;			// [252d8] muzzle flash pattern index (0x24b58 = {0,1,0,2})
static const u8 c_flash_pat[4] = { 0, 1, 0, 2 };

static void crew_frame_tick()
{
	s16 sig = P.signal;
	if (sig < 0 || sig > 5) sig = 3;
	if (sig != g_crew_sig)
	{
		g_crew_sig = sig;
		g_crew_at = c_crew_a[sig][1];
		g_crew_bt = c_crew_b[sig][1];
	}
	if (g_crew_a != g_crew_at)
		g_crew_a += (g_crew_at > g_crew_a) ? 1 : -1;
	else
	if (sig != 2 || g_crew_a == g_crew_b)
		g_crew_at = (g_crew_at == c_crew_a[sig][0]) ? c_crew_a[sig][1] : c_crew_a[sig][0];
	if (g_crew_b != g_crew_bt)
		g_crew_b += (g_crew_bt > g_crew_b) ? 1 : -1;
	else
		g_crew_bt = (g_crew_bt == c_crew_b[sig][0]) ? c_crew_b[sig][1] : c_crew_b[sig][0];
}

// effects advance per drawn frame on the Amiga (~16.7 fps there); here every 3rd VBL
// flags (draw_special_map_cell 13b1c): tower 252dd counts 3..0 on every 2nd drawn frame, frame = flg3 + {3,2,1,0}[n];
// island 252d0 counts 2..0 every drawn frame, frame = flg0 + n while the island is garrisoned, else 'POST'
static s16 g_flag_us = 3, g_flag_jp = 2, g_flag_fc = 0;
static void flag_frame_tick()
{
	if (++g_flag_fc & 1)
		if (--g_flag_us < 0) g_flag_us = 3;
	if (--g_flag_jp < 0) g_flag_jp = 2;
}

// soldiers: world frame guy0..7 (+8 facing left) at alt 12; 1/8 view: guy0/guy1 miniatures; dead ones not drawn
void soldier_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	if (self.counter >= g_sold_nvis) { self.drawtype = EntityDraw_NONE; return; }
	soldier_t &so = g_sold[g_sold_vis[self.counter]];
	if (so.state == 1 || so.state == 2)
	{
		if (g_zoom)
		{
			self.passet = mini_asset.get();
			self.rx = MINI_X0 + ((so.x + MARGIN) >> 3) - MI_AX;
			self.ry = MINI_ROW + MINI_SEA - 151 + ((1219 - 12) >> 3) - MI_AY;
			self.frame = c_fr_minisold[so.frame & 1];
		}
		else
		{
			self.passet = soldier_asset.get();
			self.rx = so.x + MARGIN - SO_AX;
			self.ry = BASE_ROW - 12 - SO_AY;
			self.frame = so.frame + (so.dir < 0 ? 8 : 0);
		}
		self.drawtype = EntityDraw_IMSPR;
		return;
	}
	self.drawtype = EntityDraw_NONE;
}

// rockets (rc/ro frames) and torpedoes (tor2/tor7) in flight; the last two slots are the weapon menu: 'selt' and the
// highlighted row, drawn at Amiga screen (250,60) (+33 lines: our playfield shows more sky above the waterline)
static s16 g_fx_q = 0;				// interpolation quarter of this frame (fx_build)
void weapon_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	s16 k = self.counter;
	self.drawtype = EntityDraw_NONE;
	if (g_zoom) return;
	if (k >= NPROJ)
	{
		self.rx = g_cam_x + 250 - WP_AX;
		self.ry = g_cam_y + 60 + (MINI_SEA - 151) - WP_AY;
		if (g_menu && P.state == PS_DECK && k == NPROJ && !g_help && !g_help_peek)
		{
			self.frame = WP_FR_ROW + g_weapon;		// box with the selected row highlighted (composed in the generator)
			self.drawtype = EntityDraw_IMSPR;
		}
		return;
	}
	proj_t &p = g_proj[k];
	if (p.state != 1 || p.type == 1) return;
	// interpolated between ticks like the plane and the bombs (the Amiga draws once per tick at most)
	s16 cx = (s16)(p.x >> 16), cy = (s16)(p.y >> 16);
	self.rx = p.px + (((cx - p.px) * g_fx_q) >> 2) + MARGIN - WP_AX;
	self.ry = BASE_ROW - (p.py + (((cy - p.py) * g_fx_q) >> 2)) - WP_AY;
	if (p.type == 0) self.frame = (p.delay ? WP_FR_RO : WP_FR_RC) + p.frame;
	else self.frame = WP_FR_TOR + (p.facing < 0 ? 1 : 0);
	self.drawtype = EntityDraw_IMSPR;
}

// AA gun: frame at the bunker anchor, 20 px above the waterline (draw_world_object y = 20)
void gun_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	if (self.counter >= g_gun_nvis) { self.drawtype = EntityDraw_NONE; return; }
	s16 k = g_gun_vis[self.counter], f, gx, gy;
	if (k >= MAX_BUILD + MAX_PILLBOXES) { k -= MAX_BUILD + MAX_PILLBOXES; f = g_sgun_frame[k]; gx = g_sgun[k].x; gy = sgun_draw_alt(g_sgun[k]); }	// ship gun
	else if (k >= MAX_BUILD) { k -= MAX_BUILD; f = g_pill_gun[k]; gx = g_pill[k].x; gy = 22; }	// pillbox gun
	else { f = g_gun_frame[k]; gx = g_build[k].x; gy = 20; }								// bunker gun
	if (f == 100)
	{
		self.rx = MINI_X0 + ((gx + MARGIN) >> 3) - GN_AX;
		self.ry = MINI_ROW + MINI_SEA - 151 + ((1219 - gy) >> 3) - GN_AY;
		self.frame = GUN_FR_MINI;				// 1/8 view: 8thscale 'expl' (gun sheet frame 14)
	}
	else
	{
		self.rx = gx + MARGIN - GN_AX;
		self.ry = BASE_ROW - gy - GN_AY;
		self.frame = f;
	}
	self.drawtype = EntityDraw_IMSPR;
}

void flag_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	s16 k = self.counter;
	// the tower's flag goes down with the sinking carrier, until it reaches the water
	s16 sink = (k < NFLAGS && c_flags[k * 3 + 2] == 0) ? carrier_sink_px() : 0;
	if (k >= NFLAGS || (c_flags[k * 3 + 2] == 0 && (!g_carrier.alive || c_flags[k * 3 + 1] + sink + 24 >= WATER_ROW)))
	{
		self.drawtype = EntityDraw_NONE; return;
	}
	self.rx = c_flags[k * 3];
	self.ry = c_flags[k * 3 + 1] + ((c_flags[k * 3 + 2] == 0) ? g_bob_flag - 3 + sink : 0);	// tower: generated at bob 3
	if (g_zoom || g_help || g_help_peek || g_pause || g_loading || g_page)
	{
		self.drawtype = EntityDraw_NONE;	// not drawn in the 1/8 view, nor over the help page
		return;
	}
	if (c_flags[k * 3 + 2] == 0)
		self.frame = 3 - g_flag_us;			// flg3..6
	else
		self.frame = island_flag_garrisoned() ? 4 + g_flag_jp : 7;
	self.drawtype = EntityDraw_IMSPR;
}

// wave strip (FUN_13e6c): frame 0x4e + n, n steps 11..0 once every 2 drawn frames. The strip is one tile row
// (WAVE_DST_ROW); the visible part is refreshed from the phase's row of the source band (objects composited).
static s16 g_wave_n = 0, g_wave_fc = 0;
static void wave_frame_tick()
{
	if (++g_wave_fc & 1)
		if (--g_wave_n < 0) g_wave_n = WAVE_PHASES - 1;
}

// The wave strip under a smoothly sinking ship (checked against the Amiga 2026-10-08): there the waves are drawn
// over the ship at the fixed waterline, and their two top pixel rows have gaps between the crests through which the
// ship's row at the waterline shows: the hull first, later the superstructure, the tower, at last the sky. The strip
// tiles in the band have the hull as it floats. So while a ship sinks, the strip tiles under it are composed here:
// the open sea's wave tile of the phase, and in rows 0 and 1, where it is sky (colour 1), the ship picture's pixel
// for that row at the ship's stage. Called for the map columns _c0.._c1 after every strip refresh.
static void sink_strip(s16 _k, s16 _c0, s16 _c1)
{
	sink_t &s = g_sink[_k];
	if (!s.tiles || s.stage < 1) return;
	const s16 *r = s.rm;
	if (r[3] + s.rows != WAVE_DST_ROW) return;				// (the ship's picture does not reach down to the strip)
	s16 j0 = _c0 - r[1], j1 = _c1 - r[1];
	if (j0 < 0) j0 = 0;
	if (j1 > s.cols - 1) j1 = s.cols - 1;
	if (j0 > j1) return;
	s32 *m = (s32 *)mymap.get();
	const u8 *base = (const u8 *)mytiles.get();
	s16 W = mymap.getwidth();
	for (s16 j = j0; j <= j1; j++)
	{
		s16 mc = r[1] + j;
		if (c_wave_src[mc] == 0xffff) continue;				// (open sea beside the hull: as it is)
		const u16 *sea = (const u16 *)(base + m[(s32)(WAVE_SRC_ROW + g_wave_n) * W + WAVE_SEA_COL + mc % WAVE_PERIOD]);
		const u16 *hull = (const u16 *)(base + m[(s32)(WAVE_SRC_ROW + g_wave_n) * W + c_wave_src[mc]]);
		u16 *d = s.strip + (s32)j * 64;
		for (s16 i = 0; i < 64; i++) d[i] = sea[i];
		for (s16 y = 0; y < 2; y++)
		{
			u16 *dw = d + y * 4;
			u16 gap = dw[0] & ~dw[1] & ~dw[2] & ~dw[3];		// the sky between the crests
			if (!gap) continue;
			s16 Y = s.rows * 16 + y - s.stage;				// the ship picture's row that is at this height now
			const u16 *sp;
			if (Y >= s.rows * 16) sp = hull + (Y - s.rows * 16) * 4;		// (the first stages: the hull's own rows)
			else if (Y >= 0) sp = (const u16 *)(base + s.orig[(Y >> 4) * s.cols + j]) + (Y & 15) * 4;
			else continue;									// (all of it under: the sky)
			for (s16 p = 0; p < 4; p++) dw[p] = (dw[p] & ~gap) | (sp[p] & gap);
		}
		m[(s32)WAVE_DST_ROW * W + mc] = (s32)((u8 *)d - base);
	}
	for (s16 c = j0; c <= j1; c += 24)
	{
		s16 w = j1 - c + 1 < 24 ? j1 - c + 1 : 24;
		g_world->multitouch_rect(r[1] + c, WAVE_DST_ROW, w, 1);
	}
}

static void waves_apply()
{
	if (!g_world) return;
	s16 c = (g_cam_x >> 4) - 2;
	if (c < 0) c = 0;
	s16 w = SCREEN_XSIZE / 16 + 5;			// <= 25 columns: within multitouch_rect's 32-column limit
	if (c + w > LEVEL_W / 16) w = LEVEL_W / 16 - c;
	// runs of open sea copy from the periodic sea columns, runs of object columns from their stored columns
	s16 e = c + w;
	while (c < e)
	{
		u16 src = c_wave_src[c];
		s16 n = 1;
		if (src == 0xffff)
		{
			src = WAVE_SEA_COL + c % WAVE_PERIOD;
			while (c + n < e && c_wave_src[c + n] == 0xffff) n++;
		}
		else
			while (c + n < e && c_wave_src[c + n] == src + n) n++;
		g_world->multimod_copy(src, WAVE_SRC_ROW + g_wave_n, c, WAVE_DST_ROW, n, 1, mymap);
		c += n;
	}
	for (s16 k = 0; k < NSINK; k++) sink_strip(k, e - w, e - 1);
}

// carrier wave bob (252fe = {1,2,3,2,1,2,3,2}[i] + 1, i steps every 21 ticks): copy the carrier tile block for the
// new bob from the source band (whole carrier, in chunks of <= 24 columns for multitouch_rect)
static s16 g_bob_i = 0, g_bob_timer = 0;
static const s16 c_bob_tbl[8] = { 1, 2, 3, 2, 1, 2, 3, 2 };
static void bob_tick()
{
	if (--g_bob_timer < 0)
	{
		g_bob_timer = 20;
		g_bob_i = (g_bob_i + 1) & 7;
		g_wave_bob = c_bob_tbl[g_bob_i] + 1;
	}
}

// one band of BOB_ROWS_PER_FRAME tile rows per call (a whole-block copy in one frame made it ~2 VBLs longer and the
// STE showed a black flash); returns true while rows remain
#define BOB_ROWS_PER_FRAME 2
static bool bob_apply_step()
{
	if (!g_world || g_bob_row >= BOB_ROWS || !g_carrier.alive) return false;
	s16 sx = BOB_SRC_COL + (g_bob_drawn - 2) * BOB_COLS;
	s16 h = BOB_ROWS - g_bob_row < BOB_ROWS_PER_FRAME ? BOB_ROWS - g_bob_row : BOB_ROWS_PER_FRAME;
	s16 r = BOB_ROWS - g_bob_row - h;		// bottom-up: the deck rows move in the first frame
	for (s16 c = 0; c < BOB_COLS; c += 24)
	{
		s16 w = BOB_COLS - c < 24 ? BOB_COLS - c : 24;
		g_world->multimod_copy(sx + c, BOB_SRC_ROW + r, BOB_COL0 + c, BOB_DST_ROW + r, w, h, mymap);
	}
	g_bob_row += h;
	return g_bob_row < BOB_ROWS;
}

static void hutsmoke_frame_tick()
{
	for (s16 i = 0; i < NHUTSMOKE; i++)
	{
		hutsmoke_t &h = g_hutsmoke[i];
		if (!h.puffs) continue;
		s16 dx = h.x - 8 - (s16)P.x;
		s16 range = g_zoom ? 2000 : 300;		// the cell must be on screen (normal view +-288 px)
		if (dx < -range || dx > range) continue;
		s16 d = h.delay;
		h.delay = d - 1;
		if ((h.delay == 0 || d < 1) && --h.puffs != 0)
		{
			h.delay = 50 - h.puffs;
			spawn_smoke(h.x, h.y, 5);
		}
	}
}

// per logic tick: engine slews (FUN_12132) and channel 0 arbitration (FUN_12066: player gun > engine)
static void sound_tick()
{
	if (g_eng_vol != g_eng_vol_target)
	{
		if (g_eng_vol_target < g_eng_vol) { g_eng_vol -= 2; if (g_eng_vol < g_eng_vol_target) g_eng_vol = g_eng_vol_target; }
		else g_eng_vol++;
	}
	if (g_eng_vol)
	{
		s16 t = (P.y >> 4) + g_eng_per_base + (P.pitch >> 7);
		if (t < g_eng_per) { g_eng_per -= 10; if (g_eng_per < t) g_eng_per = t; }
		else if (t > g_eng_per) { g_eng_per += 20; if (g_eng_per > t) g_eng_per = t; }
	}
	// ch3 slot 0: AA guns (machine gun, period 320, loop), volume 64 - min(nearest/8, 64)
	if (g_aa_fire) { s16 v = g_aa_mind / 8; snd_voice(3, SND_GUN_AA, 64 - (v > 64 ? 64 : v), 320, true, 0); }
	else if (g_voice[3].base && g_voice[3].snd == SND_GUN_AA) snd_stop(3);
	g_aa_fire = false; g_aa_mind = 0x7fff;
	// carrier phases (sound_update_continuous 12132): the sea (splash sample, period 800, vol 34, loop) on ch2 while
	// the plane waits below deck with the weapon menu (phase 1); the elevator (Grind.1, period 450, vol 64, loop) on
	// ch3 while it moves (phases 2 and 3)
	if (g_phase == 1) { if (!g_voice[2].base) snd_voice(2, SND_SPLASH_LOOP, 34, 800, true, 1); }
	else if (g_voice[2].base && g_voice[2].snd == SND_SPLASH_LOOP) snd_stop(2);
	if (g_phase == 2 || g_phase == 3) { if (!g_voice[3].base || g_voice[3].snd == SND_GRIND) snd_voice(3, SND_GRIND, 64, 450, true, 1); }
	else if (g_voice[3].base && g_voice[3].snd == SND_GRIND) snd_stop(3);
	// ch1 (sound_update_continuous 12132): enemy planes in the air (state 1 or 2): machine gun (period 160, vol 57,
	// loop) while one of them fires, else their engine (period 330) at a volume by the Manhattan distance of the
	// nearest one (FUN_122ce: d >>= 4; d > 44 -> off; d <= 5 -> 64 - 4d; else 64 - (d + 20))
	{
		u16 best = 0xffff; bool efire = false;
		for (s16 i = 0; i < NZERO; i++)
		{
			const zero_t &z = g_zero[i];
			if (z.state != 1 && z.state != 2) continue;
			s16 dx = z.x - (s16)P.x; if (dx < 0) dx = -dx;
			s16 dy = z.alt - P.y; if (dy < 0) dy = -dy;
			if ((u16)(dx + dy) < best) best = (u16)(dx + dy);
			if (z.firing) efire = true;
		}
		u16 d = best >> 4;
		s16 ev = (best == 0xffff || d > 44) ? 0 : 64 - (d <= 5 ? (s16)(d << 2) : (s16)(d + 20));
		if (efire) snd_voice(1, SND_GUN_ENEMY, 57, 160, true, 0);
		else if (ev > 0) snd_voice(1, SND_ENGINE, ev, 330, true, 1);
		else snd_stop(1);
	}
	if (g_gun_firing) snd_voice(0, SND_GUN, 64, 200, true, 0);
	else if (g_eng_vol > 0 && g_eng_per > 100) snd_voice(0, SND_ENGINE, g_eng_vol, (u16)g_eng_per, true, 1);
	else snd_stop(0);
}

// dashboard gauges, per drawn frame (draw_dashboard 1ee16)
static s16 g_gauge_oil = 0, g_gauge_fuel = 0, g_blink_oil = 0, g_blink_fuel = 0;
static bool g_lamp_oil = false, g_lamp_fuel = false;
static bool lamp_blink(s16 &_cnt, s16 _period)	// 9-of-11 / 7-of-9 on: cnt-- > 0 on; at 0 off; then reload
{
	if (--_cnt > 0) return true;
	if (_cnt != 0) _cnt = _period;
	return false;
}
static void gauges_frame_tick()
{
	bool active = P.state == PS_FLYING || P.state == PS_DECK || P.state == PS_ARRESTED;
	s16 t = (P.oil < 0x60 ? 0 : P.oil - 0x60) * 2 & ~3;
	if (P.state < 2 && g_engine_boost) t += 0x18;
	if (t > 88) t = 88;
	if (t != g_gauge_oil) g_gauge_oil += (t < g_gauge_oil) ? -4 : 4;
	g_lamp_oil = active && P.oil < 0x74 && lamp_blink(g_blink_oil, 10);
	t = (P.fuel < 0 ? 0 : P.fuel) >> 1;
	if (t > 0x58) t = 0x58;
	t &= ~3;
	if (t == 0 && active) t = (rnd16() >> 13) & 4;
	if (t != g_gauge_fuel) g_gauge_fuel += (t < g_gauge_fuel) ? -4 : 4;
	g_lamp_fuel = active && P.fuel <= 0x40 && lamp_blink(g_blink_fuel, 8);
}

static void fx_frame_tick()
{
	crew_frame_tick();
	flag_frame_tick();
	wave_frame_tick();
	hutsmoke_frame_tick();
	smoke_frame_tick();
	soldiers_frame_tick();
	bunkers_frame_tick();
	ship_guns_frame_tick();
	gauges_frame_tick();
	for (s16 i = 0; i < NEXPL; i++)
		if (g_expl[i].anim && ++g_expl[i].anim >= 8) g_expl[i].anim = 0;
	g_flash_ctr = (g_flash_ctr + 1) & 3;
	for (s16 i = 0; i < NPROJ; i++)
	{
		proj_t &p = g_proj[i];
		if (p.state == 8 && ++p.anim >= 8) p.state = 0;
	}
	for (s16 i = 0; i < NIMPACT; i++)
		if (g_impact[i].timer > 0) g_impact[i].timer--;
}

// The original's world has no edges: x is a 16-bit value, the map lies at 0..map width, everything else is open sea,
// and x wraps at 32768, so the world is a circle of 65536 px. Our tile map ends, so the open sea is played on a
// "treadmill" in the map's sea margin: 200 px before an end the plane (with its smoke, shots and nearby enemy planes)
// is set back by 576 px (a multiple of the wave pattern, both places are open sea, the picture is the same) and the
// distance is counted in g_out. Flying back unwinds it; after the original's ocean length the plane comes in at the
// other end of the map.
static s32 g_wrap_dx = 0;				// set for the main loop: shift since the last frame (interpolation, camera)
static void world_shift(s32 d)
{
	s16 px = (s16)P.x;
	P.x += d;
	g_wrap_dx += d;
	for (s16 i = 0; i < NSMOKE; i++) if (g_smoke[i].n) g_smoke[i].x += d << 16;
	for (s16 i = 0; i < NPROJ; i++) if (g_proj[i].state) { g_proj[i].x += d << 16; g_proj[i].px += (s16)d; }
	for (s16 i = 0; i < NEXPL; i++) if (g_expl[i].anim) g_expl[i].x += (s16)d;
	for (s16 i = 0; i < NZERO; i++)
	{
		zero_t &z = g_zero[i];
		s16 dz = z.x - px; if (dz < 0) dz = -dz;
		if (z.state && dz < 600) z.x += (s16)d;
	}
}
static void clamp_world_x()
{
	const s32 STEP = 576;
	const s32 xmin = -MARGIN + 200;
	const s32 xmax = (s32)LEVEL_W - MARGIN - 200;
	const s32 map_w = (s32)LEVEL_W - 2 * MARGIN;			// the map itself (world 0..map_w)
	const s32 ocean = 65536 - map_w;						// open sea around the circle
	if (P.x > xmax) { world_shift(-STEP); g_out += STEP; }
	else if (P.x < xmin) { world_shift(STEP); g_out -= STEP; }
	else if (g_out > 0 && P.x < xmax - STEP) { world_shift(STEP); g_out -= STEP; if (g_out < 0) g_out = 0; }	// heading back
	else if (g_out < 0 && P.x > xmin + STEP) { world_shift(-STEP); g_out += STEP; if (g_out > 0) g_out = 0; }
	if (g_out >= ocean || g_out <= -ocean)					// all the way round: in at the other end
	{
		s32 span = ((xmax - xmin - STEP) / 192) * 192;
		world_shift(g_out > 0 ? -span : span);
		g_out = 0;
	}
}

// one logic tick: FUN_00011386 (player part) + FUN_0001c660
// wreck_explosions FUN_1aed8 (states 6 and 8): for 75 ticks after the crash, an explosion at the plane every
// rand&12 ticks (on the ground / deck: at the plane's lowest point; sinking: at the sea surface, as a splash)
static s16 g_next_expl = 0;
static void wreck_explosions()
{
	if (P.dead_ticks == 0) g_next_expl = 0;
	g_eng_vol_target = 0;
	if (P.dead_ticks < 0x4b && g_next_expl <= P.dead_ticks)
	{
		g_next_expl = P.dead_ticks + (rnd16() & 0xc);
		s16 x = ((s16)P.x + (s16)(rnd16() & 15) - 8) & ~7;		// (the cell's x, as FUN_10820 gets a cell)
		if (x < 0) x = 0;
		bool sinking = P.state == PS_SINKING;
		s16 alt = sinking ? 0 : P.y - wheel_clearance();
		u16 c = map_cell(x);
		s16 surf = (x < 0 || (x >> 3) >= MAP_CELLS) ? 0 : cell_surface(c);
		spawn_explosion(x, (alt < 0 ? 0 : alt) + 12, sinking ? 0 : (surf == 0 ? 1 : surf));	// (altitude y - clearance + 12; sinking: 12)
		if (!sinking) snd_play(2, SND_BOOM, 64, 0);		// FUN_10820: the boom only with the explosion, not the splash
	}
}

static void logic_tick(u8 in)
{
	g_map_fresh = false;
	g_tick_in = in;
	bob_tick();					// player tick start on the Amiga (player.md 2)
	garrison_tick();
	ships_tick();
	carrier_tick();
	balloons_tick();
	zeros_tick();
	zeros_gun_tick();
	if (P.state == PS_FLYING)
	{
		if (P.oil != 0x80 && --P.oil_timer == 0) { P.oil_timer = 0x50; P.oil--; }
		if (--P.fuel_timer == 0) { P.fuel_timer = 28; P.fuel--; }
	}

	g_tick_parity ^= 1;
	oil_leak_smoke();

	// ordnance release / gun (FUN_0001b5b0): flying only, not during turn frames 6..16
	if (P.state == PS_FLYING && (in & IN_TAP) && (P.turn < 6 || P.turn > 16))
		release_ordnance();
	projectiles_tick();
	gun_tick(in);

	switch (P.state)
	{
	case PS_FLYING:
		if (P.oil < 0x60 || P.fuel < 0) { start_crash(); crash_update(); break; }
		if (P.y < -6) { P.state = PS_SINKING; P.dead_ticks = 0; P.sink_sub = 0; break; }
		controls(in);
		physics(in);
		ground_check();
		break;

	case PS_DECK:
		if (g_phase == 1) { menu_tick(in); deck_update(0); }	// below deck: the weapon menu takes the input
		else if (g_phase != 0) deck_update(0);					// riding the elevator (state 0xb): y = deck height
		else
		{
			deck_update(in);
			// FUN_1b5b0: stopped fully on the elevator, fire -> elevator down, then re-arm
			if (P.state == PS_DECK && P.airspeed == 0 && (in & (IN_TAP | IN_HOLD)) && on_elevator() && carrier_afloat())
			{
				g_phase = 3;
				g_eng_vol = g_eng_vol_target = 0;
				place_on_deck();
			}
		}
		if (g_phase != 0) g_eng_vol = g_eng_vol_target = 0;		// engine off until the elevator is up
		break;

	case PS_ARRESTED:
		P.pitch = 0;
		P.airspeed -= 110;
		if (P.airspeed < 0)
		{
			P.airspeed = 0; P.state = PS_DECK;			// (re-arm: taxi onto the elevator, stop, fire)
		}
		P.hspeed = (P.airspeed + 50) / 100;
		P.x += (s32)P.hspeed * P.dir;
		place_on_deck();
		break;

	case PS_CRASH:
		crash_update();
		break;

	case PS_SINKING:
		if (++P.sink_sub >= 3) { P.sink_sub = 0; P.y--; }
		P.pitch -= 250;
		if (P.pitch < -4500) P.pitch = -4500;
		wreck_explosions();
		respawn_timer(in);
		break;

	case PS_WRECK:
		P.attitude_frame = 0;							// lies on the ground / deck
		{
			u16 wc = map_cell(P.x);
			P.y = wheel_clearance() + (cell_surface(wc) == 1 ? obj_height(wc) : 0);
		}
		if ((P.dead_ticks & 3) == 0)					// smoke every 4 ticks (1cae0(6, y+11))
			spawn_smoke((s16)P.x + (rnd16() & 7), P.y + 11, 6);
		wreck_explosions();
		respawn_timer(in);
		break;
	}

	// gear FUN_0001b45a: lowered automatically near the carrier
	if (P.state == PS_FLYING)
	{
		s32 d = P.x - HOME_X;
		// (only while the carrier is there; over the open sea beyond a map end the map position is not the true
		// one: clamp_world_x)
		P.gear = (g_carrier_ok && g_out == 0 && d > -1280 && d < 1280) ? 5 : 0;
	}
	else
	if (P.state == PS_DECK || P.state == PS_ARRESTED)
		P.gear = 5;
	else
		P.gear = 0;				// crashing, sinking, wreck: gear up (the plane lies on its belly)

	// deck crew signal [252af]: 0 / 1 wave towards the elevator, 2 low, 3 high, 4 cut, 5 on the elevator
	if (P.state == PS_FLYING) { P.signal = (P.y < 0x51) ? 2 : 3; crew_signal(); }	// (1c660 case 0)
	else if (P.state == PS_ARRESTED) P.signal = 4;
	else if (P.state == PS_DECK) { if (g_phase != 0) P.signal = 3; else crew_signal(); }	// (3 while the elevator moves: 1b5b0, 13684)
	else P.signal = 3;																// crashing, sinking, wreck

	clamp_world_x();
	select_frame();
}

// =====================================================================================================================
//	input: stick + keys -> Amiga input word; fire tap/hold timing per VBL (FUN_0001c9ca)
// =====================================================================================================================

// AGT's g_vbl counts DOWN once per VBL; vbl_now() is an up-counting view of it
static inline s16 vbl_now() { return (s16)(-g_vbl); }

static s16 s_fire_down_vbl = 0;			// VBL of the press (valid while s_fire_down)
static bool s_fire_down = false;		// (a flag: the 16-bit VBL counter is negative half of the time)
static u8 s_fire_tap = 0;

static void poll_fire()
{
	bool fire = (joy1 & 0x80) || key_states[ScanCode_SPACE];
	if (fire && !s_fire_down)
	{
		s_fire_down = true;
		s_fire_down_vbl = vbl_now();
	}
	else
	if (!fire && s_fire_down)
	{
		if ((s16)(vbl_now() - s_fire_down_vbl) < 10)
			s_fire_tap = 1;
		s_fire_down = false;
	}
}

static bool g_stick_swap = false;			// [25446] Ctrl+F: stick up and down swapped
static u8 read_input()
{
	u8 j = joy1;
	u8 in = 0;
	if ((j & 1) || key_states[ScanCode_UP])    in |= g_stick_swap ? IN_DOWN : IN_UP;		// (Ctrl+F swaps up and down)
	if ((j & 2) || key_states[ScanCode_DOWN])  in |= g_stick_swap ? IN_UP : IN_DOWN;
	if ((j & 4) || key_states[ScanCode_LEFT])  in |= IN_LEFT;
	if ((j & 8) || key_states[ScanCode_RIGHT]) in |= IN_RIGHT;
	if (s_fire_down && (s16)(vbl_now() - s_fire_down_vbl) >= 10) in |= IN_HOLD;
	if (s_fire_tap) { in |= IN_TAP; s_fire_tap = 0; }
	return in;
}

// =====================================================================================================================
//	WOF_REPLAY (make play -> disk1/WOFPLAY.PRG): scripted input for automated runs in Hatari (tools/hatari_play.sh).
//	REPLAY.TXT, one command per line ('#' starts a comment):
//	  <ticks> <keys>   hold the input for <ticks> logic ticks (12.5 Hz); keys: U D L R, H = fire held (gun),
//	                   T = fire tap (bomb, first tick only), '-' = nothing
//	  RESTART          press R (respawn on the deck)
//	  SNAP <name>      pause after drawing the frame, print "SNAP <name>" and wait for Space (the host screenshots)
//	  JUMP             force a full playfield rebuild at the current camera (test aid)
//	  GOTO <x>         move the plane to world x (test aid)
//	  MAP <letter>     switch to another map (as after a completed mission)
//	  CLEAR            clear every island (test aid: mission complete)
//	  BOMBER           send the next carrier bomber now
//	  NEWGAME          switch the front end on and open the rank select (script lines count frames on a page)
//	  OVER <n>         game over, with a score if n = 1 (name entry and high scores follow)
//	  NIGHT            toggle day / night palettes
//	  LOW              oil and fuel low: the warning lamps blink (test aid)
//	  ZPASS            draws an enemy plane crossing the screen from 260 px right of the player to the left,
//	                   6 px per frame (a draw test: no plane logic behind it)
//	  KILLCARRIER      the own carrier starts sinking (test aid)
//	  XPILL <x>        a hit on the pillbox at world x (test aid; x within its 4 cells picks the damage bit)
//	  HELP             show / hide the help page without pausing (test aid)
//	  KILLS <n>        set the planes-shot-down counter (test aid)
//	  FAROUT           set the open-sea distance to 600 px before the wrap-around (test aid)
//	  WAITDECK         feed neutral input until the elevator has brought the plane up (does not count as ticks)
//	  END              print "REPLAY END" and quit
// =====================================================================================================================

#if defined(WOF_REPLAY)
static char s_rp_buf[8192];
static s16 s_rp_len = 0, s_rp_pos = 0;
static s16 s_rp_left = 0;
static u8 s_rp_in = 0;
static bool g_rp_snap = false, g_rp_end = false, g_rp_restart = false;
static char s_rp_name[40];

static void replay_load()
{
	FILE *f = fopen("REPLAY.TXT", "rb");
	if (f) { s_rp_len = (s16)fread(s_rp_buf, 1, sizeof(s_rp_buf) - 1, f); fclose(f); }
	s_rp_buf[s_rp_len] = 0;
	dbg_s("REPLAY loaded "); dbg_h(s_rp_len); dbg_s("\n");
}

// next line without comment/whitespace; false at end of script
static bool g_rp_night = false;
static bool replay_line(char *_out, s16 _max)
{
	while (s_rp_pos < s_rp_len)
	{
		s16 n = 0;
		bool comment = false;
		while (s_rp_pos < s_rp_len && s_rp_buf[s_rp_pos] != '\n')
		{
			char c = s_rp_buf[s_rp_pos++];
			if (c == '#') comment = true;
			if (!comment && c != '\r' && n < _max - 1) _out[n++] = c;
		}
		s_rp_pos++;
		while (n > 0 && _out[n - 1] == ' ') n--;
		_out[n] = 0;
		s16 k = 0;
		while (_out[k] == ' ' || _out[k] == '\t') k++;
		if (_out[k]) { if (k) { s16 i = 0; while ((_out[i] = _out[i + k]) != 0) i++; } return true; }
	}
	return false;
}

// input for the next logic tick; returns false when the tick must not run (a command stops this frame's ticks)
static bool g_rp_waitdeck = false;
static bool replay_input(u8 &_in)
{
	if (g_rp_waitdeck)
	{
		if (g_phase == 0 && P.state == PS_DECK) g_rp_waitdeck = false;
		else { _in = 0; return true; }
	}
	while (s_rp_left <= 0)
	{
		char line[64];
		if (!replay_line(line, sizeof(line))) { g_rp_end = true; return false; }
		if (line[0] >= '0' && line[0] <= '9')
		{
			s16 i = 0, n = 0;
			while (line[i] >= '0' && line[i] <= '9') n = n * 10 + (line[i++] - '0');
			u8 in = 0;
			for (; line[i]; i++)
			{
				switch (line[i])
				{
				case 'U': in |= IN_UP; break;
				case 'D': in |= IN_DOWN; break;
				case 'L': in |= IN_LEFT; break;
				case 'R': in |= IN_RIGHT; break;
				case 'H': in |= IN_HOLD; break;
				case 'T': in |= IN_TAP; break;
				}
			}
			s_rp_left = n;
			s_rp_in = in;
		}
		else if (line[0] == 'R') { g_rp_restart = true; return false; }
		else if (line[0] == 'Q' && line[1] == 'S') { dbg_s(save_write(line[6] - '1', "TEST") ? "QSAVE ok, bytes=" : "QSAVE failed "); dbg_h((u32)file_size("SAVE1.WOF")); dbg_s("\n"); }	// QSAVE n
		else if (line[0] == 'Q' && line[1] == 'L')						// QLOAD n: load slot n (1..6)
		{
			s16 l = save_letter(line[6] - '1');
			if (l) { g_load_slot = line[6] - '1'; g_map_request = l; dbg_s("QLOAD\n"); } else dbg_s("QLOAD failed\n");
			_in = 0; return true;
		}
		else if (line[0] == 'S')
		{
			s16 i = 4, k = 0;
			while (line[i] == ' ') i++;
			while (line[i] && k < (s16)sizeof(s_rp_name) - 1) s_rp_name[k++] = line[i++];
			s_rp_name[k] = 0;
			g_rp_snap = true;
			return false;
		}
		else if (line[0] == 'F') { g_out = (g_out < 0 ? -1 : 1) * (65536L - ((s32)LEVEL_W - 2 * MARGIN) - 600); }	// FAROUT: almost round the ocean (test aid)
		else if (line[0] == 'K' && line[4] == 'S') { s16 i = 5, n = 0; while (line[i] == ' ') i++; while (line[i] >= '0' && line[i] <= '9') n = n * 10 + (line[i++] - '0'); g_zero_kills = n; }	// KILLS n (test aid)
		else if (line[0] == 'W') { g_rp_waitdeck = true; break; }	// WAITDECK: neutral input until the elevator is up
		else if (line[0] == 'E') { g_rp_end = true; return false; }
		else if (line[0] == 'H') { g_help_peek = !g_help_peek; }	// HELP: show / hide the help page (no pause)
		else if (line[0] == 'J') { g_cam_jump = true; }			// JUMP: force a full playfield rebuild (test aid)
		else if (line[0] == 'M')										// MAP <letter>
		{
			s16 i = 3;
			while (line[i] == ' ') i++;
			g_map_request = line[i];
			return false;
		}
		else if (line[0] == 'B') { g_bomber_timer = 1; }				// BOMBER: the next carrier bomber now
		else if (line[0] == 'Z') { g_rp_zpass = 1; }					// ZPASS
		else if (line[0] == 'N' && line[1] == 'E') { g_frontend = true; page_open(PG_RANK); _in = 0; return true; }	// NEWGAME: front end on, rank select
		else if (line[0] == 'O') { g_frontend = true; g_score = line[5] == '1' ? 12345 : 0; game_over(); _in = 0; return true; }	// OVER n: game over (n = 1: with a score)
		else if (line[0] == 'N' && line[1] == 'I') { g_rp_night = true; }		// NIGHT: toggle day / night
		else if (line[0] == 'L') { P.oil = 0x70; P.fuel = 0x40; }		// LOW: oil and fuel low (warning lamps)
		else if (line[0] == 'V') { g_fpv_mode = line[5] - '0'; dbg_s("VIEW\n"); }	// VIEW n: forward view parts (timing tests)
		else if (line[0] == 'K') { g_carrier.hits = 0; g_carrier.reload = 20; }	// KILLCARRIER: the 4th torpedo hit
		else if (line[0] == 'C')										// CLEAR: all islands cleared
		{
			for (s16 i = 0; i < NSOLD; i++) if (g_sold[i].state == 1 || g_sold[i].state == 2) g_sold[i].state = 3;
			for (s16 i = 0; i < NBUILD; i++) { g_build[i].inside = 0; g_build[i].queued = 0; g_build[i].next = 0; }
			for (s16 i = 0; i < MAX_ISLANDS; i++) { g_isl_soldiers[i] = 0; g_isl_pills[i] = 0; garrison_check_cleared(i); }
		}
		else if (line[0] == 'X')										// XPILL <x>: a hit on the pillbox at world x (test aid)
		{
			s16 i = 5; s32 x = 0;
			while (line[i] == ' ') i++;
			while (line[i] >= '0' && line[i] <= '9') x = x * 10 + (line[i++] - '0');
			pillbox_hit((s16)x);
		}
		else if (line[0] == 'A')										// AWAY <px>: that far out over the open sea beyond the right end, negative: the left end (test aid)
		{
			s16 i = 4; s32 x = 0; bool neg = false;
			while (line[i] == ' ') i++;
			if (line[i] == '-') { neg = true; i++; }					// (negative: beyond the left end)
			while (line[i] >= '0' && line[i] <= '9') x = x * 10 + (line[i++] - '0');
			g_out = neg ? -x : x;
		}
		else if (line[0] == 'G')										// GOTO <x>: move the plane to world x (test aid)
		{
			s16 i = 4; s32 x = 0;
			while (line[i] == ' ') i++;
			while (line[i] >= '0' && line[i] <= '9') x = x * 10 + (line[i++] - '0');
			P.x = x;
			g_cam_jump = true;
			return false;
		}
	}
	_in = s_rp_in;
	s_rp_in &= ~IN_TAP;			// a tap lasts one tick
	s_rp_left--;
	return true;
}
#endif

// =====================================================================================================================
//	rendering positions (interpolated between ticks), applied to entities in their tick functions
// =====================================================================================================================

#define CAM_Y_REST (WATER_ROW - (PF_H - SEP_H - 11))	// waves just above the 5 separator lines
static s16 g_plane_ix = 0, g_plane_iy = 0;		// interpolated plane origin in image coordinates

// 1/8 high-altitude view (render_sound.md 4): above altitude 186 the camera moves to the pre-rendered miniature
// world (MINI_ROW..), x = MINI_X0 + image_x/8, and the player is drawn with 8thscale frames (draw_player_plane 103a6)
// Beyond a map end the plane flies on a treadmill (clamp_world_x): it is set back by 576 px whenever it nears the
// end of the tile map. In the normal view both places are open sea; the 1/8 view shows 2560 px of the world, so the
// map would jump with every step. It therefore scrolls by the true position (x + g_out) until the map has left the
// screen and the camera stands over open sea; g_mini_dx is what the plane and everything the treadmill moves with
// it (shots, smoke, explosions, nearby enemy planes) are drawn further along for that.
static s16 mini_plane_x() { return MINI_X0 + (g_plane_ix >> 3) + g_mini_dx; }
static s16 mini_plane_y() { return MINI_ROW + MINI_SEA - 151 + ((1208 - (WATER_ROW - g_plane_iy)) >> 3); }

void mini_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	if (!g_zoom)
	{
		self.drawtype = EntityDraw_NONE;
		return;
	}
	s16 n;
	if (P.turn == 0)
	{
		n = -P.vspeed >> 2;
		if (n < -2) n = -2;
		if (n > 3) n = 3;
		if (P.dir >= 0) n += 6;
		n += 0x2a;
	}
	else if (P.turn > 8 && P.turn < 0x12)
	{
		s16 sg = (P.turn > 0xd) ? -P.dir : P.dir;
		n = P.turn + ((sg >= 0) ? 0x38 : 0x2f);
	}
	else
	{
		s16 u = (P.turn <= 8) ? P.turn : 0x1a - P.turn;
		n = ((u - 1) >> 2) + ((P.dir >= 0) ? 0x36 : 0x34);
	}
	n -= MINI_PLANE_N0;
	if (n < 0) n = 0;
	if (n > (s16)sizeof(c_fr_mini) - 1) n = sizeof(c_fr_mini) - 1;
	self.frame = c_fr_mini[n];
	self.rx = mini_plane_x() - MI_AX;
	self.ry = mini_plane_y() - MI_AY;
	self.drawtype = EntityDraw_IMSPR;
}


// sinking (state 6): the Amiga draws the wave strip over the plane; our waves are background tiles, so the plane is
// drawn directly with the scissor ending just below the wave crests (main loop) instead of as an entity
static inline bool plane_clipped() { return (P.state == PS_SINKING || g_phase != 0) && !g_zoom; }

void hellcat_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	self.rx = g_plane_ix - PL_AX;
	self.ry = g_plane_iy - PL_AY;
	self.frame = P.frame;
	self.drawtype = plane_clipped() ? EntityDraw_NONE : EntityDraw_IMSPR;
}

void wheels_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	self.rx = g_plane_ix - WH_AX;
	self.ry = g_plane_iy - WH_AY;
	if (P.wheel_frame >= 0 && !plane_clipped())
	{
		self.frame = P.wheel_frame;
		self.drawtype = EntityDraw_IMSPR;
	}
	else
		self.drawtype = EntityDraw_NONE;
}

// torpedo slung under the plane (draw_player_plane 103a6): while the torpedo is selected and not yet dropped
void torp_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	self.rx = g_plane_ix - TP_AX;			// (TP_AX < WH_AX < PL_AX: drawn first, under the gear and the plane)
	self.ry = g_plane_iy - PL_AY;
	u8 f = (g_weapon == 2 && g_ammo != 0 && !g_zoom && !plane_clipped() && P.frame >= 0 && P.frame < PLANE_FRAMES) ? c_fr_torp[P.frame] : 255;
	if (f != 255)
	{
		self.frame = f;
		self.drawtype = EntityDraw_IMSPR;
	}
	else
		self.drawtype = EntityDraw_NONE;
}

#define NFX 56
struct fxdraw_t { s16 x, y, frame; };		// image coords of the hotspot, frame -1 = hidden
static fxdraw_t g_fx[NFX];
static fxdraw_t g_bal[20];					// the ceremony's balloons (drawn directly, on top)
static s16 g_bal_count = 0;
static s16 g_fx_count = 0;

static void fx_add(s16 x, s16 y, s16 frame)
{
	if (g_fx_count < NFX) { g_fx[g_fx_count].x = x; g_fx[g_fx_count].y = y; g_fx[g_fx_count].frame = frame; g_fx_count++; }
}

// build the draw list for this frame (q = interpolation 0..3 quarters)
static void fx_build(s16 q)
{
	g_fx_q = q;
	g_fx_count = 0;
	g_bal_count = 0;
	if (g_ceremony && !g_zoom)							// FUN_1557c: all 20 balloons are always alive
		for (s16 i = 0; i < NBALLOON; i++)
		{
			balloon_t &b = g_balloon[i];
			if (!b.active)
			{
				b.x = (HOME_X - 116) << 16; b.y = (s32)56 << 16;
				u16 r = rnd16(); r = (u16)((r << 4) | (r >> 12)) & 3;
				if (r == 0) r = 2;						// blue 25 %, red 50 %, white 25 %
				b.col = (u8)(r - 1);
				b.dx = 0x10000L + 2 * (s32)rnd16();
				b.dy = 0x10000L + 2 * (s32)rnd16();
				b.active = true;
			}
			// (drawn after the sprites, see the main loop: as entities they went behind the tower flag's opaque frame)
			if (g_bal_count < NBALLOON) { g_bal[g_bal_count].x = (s16)(b.x >> 16) + MARGIN; g_bal[g_bal_count].y = BASE_ROW - (s16)(b.y >> 16); g_bal[g_bal_count].frame = FX_BAL0 + b.col; g_bal_count++; }
		}
	for (s16 i = 0; i < NPROJ; i++)
	{
		proj_t &p = g_proj[i];
		if (p.state == 1 && (p.type == 1 || g_zoom))
		{
			s16 cx = (s16)(p.x >> 16), cy = (s16)(p.y >> 16);
			s16 ix = p.px + (((cx - p.px) * q) >> 2);
			s16 iy = p.py + (((cy - p.py) * q) >> 2);
			fx_add(ix + MARGIN, BASE_ROW - iy, FX_BOMB0 + (p.type == 1 ? p.frame : 0));
		}
		else
		if (p.state == 8 && p.anim >= 1)
		{
			// 10784: the counter is advanced first, then frame 89 / 101 + counter is drawn for counter 2..7:
			// exp0..exp5 or spl0..spl5 (here the frame tick comes before the draw too: anim is 2 at the first)
			s16 n = p.anim < 2 ? 0 : p.anim - 2;
			if (p.surf == 0) fx_add((s16)(p.x >> 16) + MARGIN, BASE_ROW - (s16)(p.y >> 16), FX_SPL0 + n);
			else fx_add((s16)(p.x >> 16) + MARGIN, BASE_ROW - (s16)(p.y >> 16), FX_EXP0 + n);
		}
	}
	for (s16 i = 0; i < NEXPL; i++)
	{
		expl_t &e = g_expl[i];
		if (e.anim < 1) continue;
		s16 n = e.anim < 2 ? 0 : e.anim - 2;
		if (e.surf == 0) fx_add(e.x + MARGIN, BASE_ROW - e.alt, FX_SPL0 + n);
		else fx_add(e.x + MARGIN, BASE_ROW - e.alt, FX_EXP0 + n);
	}
	for (s16 i = 0; i < NSMOKE; i++)
	{
		smoke_t &k = g_smoke[i];
		if (k.n) fx_add((s16)(k.x >> 16) + MARGIN, BASE_ROW - (s16)(k.y >> 16), FX_SMK0 + k.n - 1);
	}
	for (s16 i = 0; i < NIMPACT; i++)
	{
		impact_t &im = g_impact[i];
		if (im.timer <= 0) continue;
		if (im.surf == 2) fx_add(im.x + MARGIN, BASE_ROW - 9, FX_RIC0);
		else fx_add(im.x + MARGIN, BASE_ROW - 13, FX_SPL0 + (im.timer > 6 ? 6 : im.timer));		// FUN_152f8: frame 103 + timer, 6 down to 1
	}
}

void flash_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	u8 pat = c_flash_pat[g_flash_ctr];
	s16 a = P.attitude_frame;
	if (g_gun_firing && P.turn == 0 && pat && a >= 1 && a <= 10)
	{
		if (pat == 1) self.frame = (P.dir < 0) ? c_fr_flash_a_l[a] : c_fr_flash_a_r[a];
		else          self.frame = (P.dir < 0) ? c_fr_flash_b_l[a] : c_fr_flash_b_r[a];
		self.rx = g_plane_ix - PL_AX;
		self.ry = g_plane_iy - PL_AY;
		self.drawtype = EntityDraw_IMSPR;
	}
	else
	{
		self.drawtype = EntityDraw_NONE;
	}
}

// deck crew: the LSO cell nearest the plane (only one is animated on the Amiga too)
void crew_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	s16 best = -1; s32 bd = 0x7fffffff;
	for (s16 i = 0; i < LSO_COUNT; i++)
	{
		s32 d = (s32)c_lso_cells[i] * 8 - P.x; if (d < 0) d = -d;
		if (d < bd) { bd = d; best = c_lso_cells[i]; }
	}
	s16 sink = carrier_sink_px();				// (the crew goes down with the sinking carrier, until the deck is awash)
	if (best < 0 || bd > 400 || !g_carrier.alive || sink >= 0x21 - 4)
	{
		self.drawtype = EntityDraw_NONE;
		return;
	}
	self.rx = MARGIN + best * 8 - CR_AX;
	self.ry = WATER_ROW + g_bob_drawn + sink - CR_AY;	// carrier cells: + wave bob (as drawn)
	self.frame = (self.counter == 0) ? g_crew_a : 8 + g_crew_b;
	self.drawtype = EntityDraw_IMSPR;
}

#define NHUD 16			// (the rope: 16 px per sprite. AGT has 192 entities in all: 28 here left none for the last panel sprites)
static fxdraw_t g_hud[NHUD];
static s16 g_hud_count = 0;
static void hud_add(s16 x, s16 y, s16 frame) { if (g_hud_count < NHUD) { g_hud[g_hud_count].x = x; g_hud[g_hud_count].y = y; g_hud[g_hud_count].frame = frame; g_hud_count++; } }

// HUD in image coordinates (screen-fixed: relative to the camera) + the arrester rope (world-fixed)
static void hud_build()
{
	g_hud_count = 0;
	// arrester rope (draw_player_plane, state 7): from the caught wire on the deck to the tail hook
	if (P.state == PS_ARRESTED)
	{
		s16 hook = g_plane_ix + ((P.dir < 0) ? 16 : -16);
		s16 wire = P.wire_x + MARGIN;
		s16 xa = wire < hook ? wire : hook, len = wire < hook ? hook - wire : wire - hook;
		s16 y = g_plane_iy + 6;
		while (len > 0)
		{
			s16 w = len > 16 ? 16 : len;
			hud_add(xa, y, HUD_ROPE1 + w - 1);
			xa += w; len -= w;
		}
	}
}

// cockpit panel: sprites in panel coordinates (panel view origin 0,0). Positions from tools/make_panel.py PANEL_POS.
#define NPANEL 20
static fxdraw_t g_panel[NPANEL];
static s16 g_panel_count = 0;
#define PANEL_MAP_X0 16		// panel map is padded by 16 px; the panel view is positioned at map x 16
static void panel_add(s16 x, s16 y, s16 frame) { if (g_panel_count < NPANEL) { g_panel[g_panel_count].x = x + PANEL_MAP_X0; g_panel[g_panel_count].y = y; g_panel[g_panel_count].frame = frame; g_panel_count++; } }

static void panel_build()
{
	g_panel_count = 0;
	panel_add(8, 11, g_weapon == 0 ? 21 : g_weapon == 1 ? 20 : 22);	// weapon icon misl / bomb / torp
	{
		s16 a = g_ammo < 0 ? 99 : g_ammo;				// (cheat: unlimited)
		panel_add(19, 20, (a / 10) % 10);				// ammo, dark digits in the white boxes
		panel_add(31, 20, a % 10);
	}
	panel_add(61, 20, g_lives % 10);					// planes left
	s32 v = g_score;
	for (s16 i = 6; i >= 0; i--) { panel_add(253 + i * 7, 11, 10 + (s16)(v % 10)); v /= 10; }	// score, white digits
	// planes shot down (G_252cf, shown up to 99); its tally is drawn directly in the panel pass (main loop)
	s16 kills = g_zero_kills > 99 ? 99 : g_zero_kills;
	panel_add(251, 21, 10 + (kills / 10) % 10);
	panel_add(258, 21, 10 + kills % 10);
	// gauges (draw_dashboard 1ee16): needle frame 92 + value/4 at hires (208,18) oil / (431,18) fuel, lamps at (202,10)/(424,10)
	panel_add(104 - 16, 18 - 12, 23 + (g_gauge_oil >> 2));
	panel_add(215 - 16, 18 - 12, 23 + (g_gauge_fuel >> 2));
	if (g_lamp_oil) panel_add(101, 10, 46);
	if (g_lamp_fuel) panel_add(212, 10, 46);
}

void panel_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	s16 k = self.counter;
	if (k < g_panel_count)
	{
		self.rx = g_panel[k].x; self.ry = g_panel[k].y;
		self.frame = g_panel[k].frame;
		self.drawtype = EntityDraw_IMSPR;
	}
	else
	{
		self.rx = 0; self.ry = 0;
		self.drawtype = EntityDraw_NONE;
	}
}

void hud_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	s16 k = self.counter;
	if (k < g_hud_count)
	{
		self.rx = g_hud[k].x; self.ry = g_hud[k].y;
		self.frame = g_hud[k].frame;
		self.drawtype = EntityDraw_IMSPR;
	}
	else
	{
		self.drawtype = EntityDraw_NONE;
	}
}

void fx_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	HELP_HIDES(self);
	s16 k = self.counter;
	if (k < g_fx_count && g_zoom)
	{
		// 1/8 view (FUN_15174 with zoom shift 3): x = MINI_X0 + image_x/8, y = (refY + 11 - alt)/8 with refY = 1208
		s16 fr = g_fx[k].frame;
		if (fr >= FX_SMK0 && fr < FX_SMK0 + 6) fr = FX_SMK0 + (fr - FX_SMK0 >= 3 ? 1 : 0);	// 10ee0: smk0 up to 3 puffs, else smk1
		u8 mf = c_fr_minifx[fr];
		if (mf != 255)
		{
			s16 alt = BASE_ROW - g_fx[k].y;
			self.passet = mini_asset.get();
			self.rx = MINI_X0 + (g_fx[k].x >> 3) + g_mini_dx - MI_AX;
			self.ry = MINI_ROW + MINI_SEA - 151 + ((1219 - alt) >> 3) - MI_AY;
			self.frame = mf;
			self.drawtype = EntityDraw_IMSPR;
			return;
		}
	}
	else if (k < g_fx_count)
	{
		self.passet = fx_asset.get();
		self.rx = g_fx[k].x - FX_AX;
		self.ry = g_fx[k].y - FX_AY;
		self.frame = g_fx[k].frame;
		self.drawtype = EntityDraw_IMSPR;
		return;
	}
	self.drawtype = EntityDraw_NONE;		// (hidden entities stay where they are: moving them with the camera made AGT re-sort them every frame)
}

// =====================================================================================================================

void sepbar_fntick(entity_t *_pself);

static u16 g_shown[32];						// the palettes showing: playfield, panel (see the main loop's fades)
extern u16 *g_nickel_last_burst;			// (local AGT patch, shifter_ste.cpp)


// load another map in place (next mission, replay MAP): map data, level tiles + map, and all per-map state.
// The entity pools stay (sized for the largest map).
static bool mission_switch(arena_t &_w, s16 _letter)
{
	scratch_begin();
	{ char b[16]; bundle_load(map_fname(b, "lvl_", _letter, ".bin")); }
	if (!map_load(_letter)) { bundle_free(); scratch_end(); return false; }
	mymap.purge();								// (zone blocks: efree is a no-op, the zone is reused)
	mytiles.purge();
	level_load(_letter);
	bundle_free();
	scratch_end();
	g_fpv_stale = true;							// (also when the same map is loaded again: a new game)
	g_fpv_redraw = true;
	_w.remap(&mymap);							// local AGT patch: setmap + re-point every field
	for (int b = _w.c_num_buffers_-1; b >= 0; b--)
	{
		_w.select_buffer(b);
		_w.settiles(&mytiles, &mytiles);
	}
	garrison_init();
	pillboxes_init();
	ships_init();
	carrier_init();
	zeros_init();
	for (s16 i = 0; i < NPROJ; i++) g_proj[i].state = 0;
	for (s16 i = 0; i < NSMOKE; i++) g_smoke[i].n = 0;
	for (s16 i = 0; i < NHUTSMOKE; i++) g_hutsmoke[i].puffs = 0;
	g_bob_i = 0; g_bob_timer = 0; g_wave_bob = 3; g_bob_drawn = 3; g_bob_row = BOB_ROWS;	// tiles are generated at bob 3
	g_wave_drawn = -1;
	respawn();
#if defined(WOF_DIAG)
	dbg_s("map "); dbg_c((char)_letter); dbg_s(" loaded, free="); dbg_h((u32)Malloc(-1)); dbg_s("\n");
#endif
	return true;
}

// ---------------------------------------------------------------------------------------------------------------------
//	Help page (H): controls and shortcuts, drawn with the font sheet (ASCII 32..95, 7 px pitch)
//	straight into the playfield like the sinking plane (restored by the page restore)

// STE palette word (each gun: bits 2..0 = high bits, bit 3 = LSB): brightness sum, and the colour at half brightness
static s16 ste_gun(u16 _c, s16 _sh) { s16 n = (_c >> _sh) & 15; return ((n & 7) << 1) | (n >> 3); }
static s16 ste_lum(u16 _c) { return ste_gun(_c, 8) + ste_gun(_c, 4) + ste_gun(_c, 0); }
static u16 ste_mix(u16 _a, u16 _b, s16 _s)		// fade step s = 0..15: a + (b - a) * s / 15 per gun
{
	u16 out = 0;
	for (s16 sh = 0; sh <= 8; sh += 4)
	{
		s16 x = ste_gun(_a, sh), y = ste_gun(_b, sh);
		s16 v = x + (y - x) * _s / 15;
		out |= (u16)(((v >> 1) | ((v & 1) << 3)) << sh);
	}
	return out;
}
static u16 ste_half(u16 _c)
{
	u16 out = 0;
	for (s16 sh = 0; sh <= 8; sh += 4)
	{
		s16 v = ste_gun(_c, sh) >> 1;
		out |= (u16)(((v >> 1) | ((v & 1) << 3)) << sh);
	}
	return out;
}


// =====================================================================================================================
//	Front end (reverse-engineering/notes/frontend.md): rank select (FUN_18262), mission briefing (FUN_18590), name entry and high
//	scores (FUN_19856), for now as text pages over the dimmed, frozen playfield (the original's pictures and music are
//	not in yet). Flow as in the original (FUN_10006): rank select -> briefing -> mission ... -> game over -> name entry
//	if the score is in the best ten -> high scores -> rank select.

static void help_text(drawcontext_t &_c, s16 _col, s16 _line, const char *_s);

static const char *const c_rank_menu[7] = { "MIDSHIPMAN", "ENSIGN", "LT. JUNIOR GRADE", "LIEUTENANT", "LT. COMMANDER", "COMMANDER", "CAPTAIN" };
static const char *const c_rank_name[7] = { "MIDSHIPMAN", "ENSIGN", "LT. JR. GR.", "LIEUTENANT", "LT.COMMD", "COMMANDER", "CAPTAIN" };	// 0x25860
static const char c_rank_map[8] = "adgiklm";		// first map of each rank (0x235a0)

struct hiscore_t { s32 score; s16 rank; char name[30]; };	// the original's 36-byte entry (file "highscore")
static hiscore_t g_hi[10];
static char g_name[17];
static s16 g_name_len = 0;
static s16 g_rank_sel = 0;				// menu cursor (G_26bb4)
static s16 g_page_t0 = 0;				// VBL at which the page opened (time-outs)

static s16 map_rank(s16 _letter, s16 *_mission)
{
	s16 r = 6;
	while (r > 0 && _letter < c_rank_map[r]) r--;
	if (_mission) *_mission = _letter - c_rank_map[r] + 1;
	return r;
}

// ---------------------------------------------------------------------------------------------------------------------
//	Disk access by the game itself (high scores, saved games). TOS reports a write-protected or missing disk through
//	the critical error handler, which under GEM puts up an alert box nobody would see here: ours returns the error
//	to the caller. AGT's flag for disk activity is set too, so the loading screen shows meanwhile (g_dmasafe_screen).
extern "C" { void wof_critic(); }
__asm__(
	"	.text\n"
	"	.even\n"
	"	.globl	_wof_critic\n"
	"_wof_critic:\n"									// (error code at 4(sp): returned = the call fails with it)
	"	move.w	4(%sp),%d0\n"
	"	ext.l	%d0\n"
	"	rts\n");
static void (*s_critic_old)() = 0;
static u8 s_dma_old = 0;
COLD static void disk_begin()
{
	s_critic_old = *(void (**)())0x404L;
	*(void (**)())0x404L = wof_critic;
	s_dma_old = *(volatile u8 *)0xa4L;
	*(volatile u8 *)0xa4L = 1;
}
COLD static void disk_end()
{
	*(volatile u8 *)0xa4L = s_dma_old;
	*(void (**)())0x404L = s_critic_old;
}

// ---------------------------------------------------------------------------------------------------------------------
//	Saved games (FUN_18b96, reverse-engineering/notes/frontend.md 2.1): the mission as it stands. Six slots, files SAVE1..6.WOF (the
//	original's 'wof.<name>' does not fit 8.3 names: the name is in the file). A file holds a header, the state
//	blocks below as they are in memory, and the tile map entries that differ from the mission's map file (wrecks,
//	sunk ships, the wave and deck rows are drawn into the map): pairs of index and entry, ended by index 0xffff.
//	Saving reads the map file once more to compare; loading reloads the mission's map, then puts the state over it.
//	(The whole map as runs of equal entries was 30-94 KB per save: too much for six slots on the floppy.)
#define SAVE_MAGIC 0x574f4653UL				// 'WOFS'
#define SAVE_VERSION 2
struct save_head_t { u32 magic; u16 version; s16 letter; u32 bytes; char name[20]; };
#define SB(_x_) { &(_x_), (u32)sizeof(_x_) }
static const struct { void *p; u32 n; } c_save_blocks[] =
{
	SB(P), SB(c_map),
	SB(g_wave_bob), SB(g_bob_drawn), SB(g_bob_flag), SB(g_deck_bob_prev), SB(g_phase), SB(g_elev),
	SB(g_deck_elev_logic), SB(g_deck_elev_prev), SB(g_deck_bob_logic), SB(g_lives), SB(g_night), SB(g_hit_sub), SB(g_out),
	SB(g_carrier_ok), SB(g_carrier_sunk), SB(g_score), SB(g_zero_kills), SB(g_smoke), SB(g_rng), SB(g_expl),
	SB(g_hutsmoke), SB(g_ammo), SB(g_weapon), SB(g_menu), SB(g_proj), SB(g_impact), SB(g_tick_parity),
	SB(g_build), SB(g_sold), SB(g_isl_soldiers), SB(g_isl_pills), SB(g_isl_garrisoned), SB(g_islands_left),
	SB(g_ships_left), SB(g_mission_done), SB(g_soldier_kills), SB(g_pill), SB(g_ship), SB(g_sgun), SB(g_nsgun),
	SB(g_carrier), SB(g_zero), SB(g_zeros_air), SB(g_launch_cool), SB(g_bomber_timer), SB(g_zwreck), SB(g_nzwreck),
	SB(g_airf), SB(g_splanes), SB(g_jroll_v), SB(g_flag_us), SB(g_flag_jp), SB(g_flag_fc), SB(g_wave_n), SB(g_wave_fc),
	SB(g_bob_i), SB(g_bob_timer), SB(g_bob_row), SB(g_next_expl),
};
#define SAVE_NBLOCKS (s16)(sizeof(c_save_blocks) / sizeof(c_save_blocks[0]))

static bool g_save_nomem = false;			// the last save failed for lack of memory (not the disk)
static worldmap s_save_ref;					// the mission's map from the disk while a game is saved
static s16 s_sv_h = -1, s_sv_n = 0, s_sv_fill = 0;
static bool s_sv_err = false;
static u8 s_sv_buf[512];
COLD static void sv_flush()
{
	if (s_sv_n && Fwrite(s_sv_h, s_sv_n, s_sv_buf) != s_sv_n) s_sv_err = true;	// (short: the disk is full)
	s_sv_n = 0;
}
COLD static void sv_put(const void *_p, s32 _n)
{
	const u8 *q = (const u8 *)_p;
	while (_n-- > 0 && !s_sv_err)
	{
		s_sv_buf[s_sv_n++] = *q++;
		if (s_sv_n == (s16)sizeof(s_sv_buf)) sv_flush();
	}
}
COLD static void sv_get(void *_p, s32 _n)
{
	u8 *q = (u8 *)_p;
	while (_n-- > 0 && !s_sv_err)
	{
		if (s_sv_n == s_sv_fill)
		{
			s32 r = Fread(s_sv_h, sizeof(s_sv_buf), s_sv_buf);
			if (r <= 0) { s_sv_err = true; return; }
			s_sv_fill = (s16)r; s_sv_n = 0;
		}
		*q++ = s_sv_buf[s_sv_n++];
	}
}
COLD static u32 save_bytes()
{
	u32 n = 0;
	for (s16 i = 0; i < SAVE_NBLOCKS; i++) n += c_save_blocks[i].n;
	return n;
}
// Folders (hard disk layout): with a DATA folder beside the program the game's files are read from there and what
// it writes (saved games, high scores) goes to a SAVE folder, made on the first start. Without DATA (floppy,
// cartridge, emulator folder) everything is in the program's folder.
static char *str_cat(char *_d, const char *_s);
static char g_root_dir[100] = "";			// the program's folder ("": not used)
static char g_save_dir[112] = "";			// "" or the SAVE folder with a trailing backslash
COLD static void dirs_init()
{
	_DTA *d = (_DTA *)Fgetdta();
	if (Fsfirst("DATA", 0x10) != 0 || !(d->dta_attribute & 0x10))
	{
		// not here: one folder up? The floppy has the program in AUTO and DATA beside it; started by hand from the
		// desktop (a machine with a hard disk boots from that, the floppy's AUTO folder is not run) we are in AUTO.
		// Only looked for, nothing changed, unless it is there: with the files beside the program (the developer
		// layout, /WOF on the cartridges) the folder must stay as it is, and the cartridge's GEMDRIVE gets no path
		// calls it did not get before (changing to ".." and back left a black screen on the Mega STE)
		if (Fsfirst("..\\DATA", 0x10) != 0 || !(d->dta_attribute & 0x10)) return;
		if (Dsetpath("..") != 0) return;
	}
	char path[80];
	path[0] = 0;
	if (Dgetpath(path, 0) != 0) return;
	s16 n = 0;
	g_root_dir[n++] = (char)('A' + Dgetdrv()); g_root_dir[n++] = ':';
	for (s16 i = 0; path[i] && n < 90; i++) g_root_dir[n++] = path[i];
	g_root_dir[n] = 0;
	char *e = str_cat(str_cat(g_save_dir, g_root_dir), "\\SAVE");
	void (*old)() = *(void (**)())0x404L;	// (a write-protected disk: no alert box, no folder; saving reports it later)
	*(void (**)())0x404L = wof_critic;
	Dcreate(g_save_dir);					// (fails when it exists)
	*(void (**)())0x404L = old;
	str_cat(e, "\\");
	Dsetpath("DATA");
}
COLD static void dirs_exit() { if (g_root_dir[0]) Dsetpath(g_root_dir[2] ? g_root_dir : "\\"); }
COLD static const char *save_path(const char *_name)
{
	static char fn[128];
	fn[0] = 0;
	str_cat(str_cat(fn, g_save_dir), _name);
	return fn;
}
COLD static const char *save_fname(s16 _slot)
{
	static char n[] = "SAVE1.WOF";
	n[4] = (char)('1' + _slot);
	return save_path(n);
}

// false: nothing was saved (write-protected or full disk, no disk): the caller says so, the game goes on
COLD static bool save_write(s16 _slot, const char *_name)
{
	if (_slot < 0 || _slot > 5) return false;
	g_save_nomem = false;
	// the mission's map as it is on the disk, to compare with (about 90 KB, freed again below)
	s32 cells = (s32)mymap.getwidth() * mymap.getheight();
	if (cells >= 0xffffL) return false;
	if ((s32)Malloc(-1) < cells * 4 + 60000L) { g_save_nomem = true; return false; }
	{
		char n[16];
		scratch_begin();
		bundle_load(map_fname(n, "lvl_", g_map_letter, ".bin"));
		s_save_ref.load_ccm(map_fname(n, "level_", g_map_letter, ".ccm"));
		bundle_free();
		scratch_end();
	}
	if (!s_save_ref.get() || s_save_ref.getwidth() != mymap.getwidth() || s_save_ref.getheight() != mymap.getheight())
	{
		s_save_ref.purge();
		return false;
	}
	disk_begin();
	s32 h = Fcreate(save_fname(_slot), 0);
	bool ok = h >= 0;
	if (ok)
	{
		s_sv_h = (s16)h; s_sv_n = 0; s_sv_err = false;
		save_head_t hd;
		hd.magic = SAVE_MAGIC; hd.version = SAVE_VERSION; hd.letter = g_map_letter; hd.bytes = save_bytes();
		for (s16 i = 0; i < 20; i++) hd.name[i] = 0;
		for (s16 i = 0; i < 16 && _name[i]; i++) hd.name[i] = _name[i];
		sv_put(&hd, sizeof(hd));
		for (s16 i = 0; i < SAVE_NBLOCKS; i++) sv_put(c_save_blocks[i].p, (s32)c_save_blocks[i].n);
		for (s16 k = 0; k < NSINK; k++) sink_map(k, false);		// (a smoothly sinking ship: saved as it was)
		mini_pill_map(false);
		const s32 *m = mymap.get(), *r = s_save_ref.get();	// tile map: the entries changed since the map was loaded
		for (s32 i = 0; i < cells && !s_sv_err; i++)
			if (m[i] != r[i]) { u16 ix = (u16)i; sv_put(&ix, 2); sv_put(&m[i], 4); }
		for (s16 k = 0; k < NSINK; k++) sink_map(k, true);
		mini_pill_map(true);
		{ u16 end = 0xffff; sv_put(&end, 2); }
		sv_flush();
		if (Fclose((s16)h) < 0) s_sv_err = true;
		ok = !s_sv_err;
		if (!ok) Fdelete(save_fname(_slot));				// (no half-written file)
	}
	disk_end();
	s_save_ref.purge();
	return ok;
}

// the header of a slot; false: empty or not a saved game of this version
COLD static bool save_peek(s16 _slot, save_head_t &_hd)
{
	s32 h = Fopen(save_fname(_slot), 0);
	if (h < 0) return false;
	bool ok = Fread((s16)h, sizeof(_hd), &_hd) == (s32)sizeof(_hd);
	Fclose((s16)h);
	_hd.name[16] = 0;
	return ok && _hd.magic == SAVE_MAGIC && _hd.version == SAVE_VERSION && _hd.bytes == save_bytes()
		&& _hd.letter >= 'a' && _hd.letter <= 'o';
}
COLD static s16 save_letter(s16 _slot)
{
	save_head_t hd;
	if (_slot < 0 || _slot > 5) return 0;
	disk_begin();
	bool ok = save_peek(_slot, hd);
	disk_end();
	return ok ? hd.letter : 0;
}

// the state of a slot over the freshly loaded map of its mission. false: the file is bad (the state may be half
// set: the caller loads the mission again)
COLD static bool save_restore(s16 _slot)
{
	save_head_t hd;
	for (s16 k = 0; k < NSINK; k++) { sink_map(k, false); sink_free(k); }	// (no ship keeps tiles of its own across a load)
	mini_pill_reset(true);
	disk_begin();
	bool ok = save_peek(_slot, hd) && hd.letter == g_map_letter;
	s32 h = ok ? Fopen(save_fname(_slot), 0) : -1;
	if (h < 0) ok = false;
	if (ok)
	{
		s_sv_h = (s16)h; s_sv_n = s_sv_fill = 0; s_sv_err = false;
		sv_get(&hd, sizeof(hd));
		for (s16 i = 0; i < SAVE_NBLOCKS; i++) sv_get(c_save_blocks[i].p, (s32)c_save_blocks[i].n);
		s32 *m = mymap.get();
		s32 n = (s32)mymap.getwidth() * mymap.getheight();
		while (!s_sv_err)
		{
			u16 ix = 0xffff; s32 v = 0;
			sv_get(&ix, 2);
			if (s_sv_err || ix == 0xffff) break;
			sv_get(&v, 4);
			if (s_sv_err || (s32)ix >= n) { s_sv_err = true; break; }
			m[ix] = v;
		}
		Fclose((s16)h);
		ok = !s_sv_err;
	}
	disk_end();
	return ok;
}

COLD static void hi_load()
{
	for (s16 i = 0; i < 10; i++) { g_hi[i].score = 0; g_hi[i].rank = 0; g_hi[i].name[0] = 0; }
	disk_begin();
	s32 h = Fopen(save_path("HISCORE.DAT"), 0);
	if (h >= 0)
	{
		Fread((s16)h, sizeof(g_hi), g_hi);
		Fclose((s16)h);
	}
	disk_end();
}
COLD static void hi_save()
{
	disk_begin();								// (a write-protected disk: the table stays in memory only)
	s32 h = Fcreate(save_path("HISCORE.DAT"), 0);
	if (h >= 0)
	{
		Fwrite((s16)h, sizeof(g_hi), g_hi);
		Fclose((s16)h);
	}
	disk_end();
}
COLD static void hi_clear()					// Ctrl+C (the original: DeleteFile("highscore"))
{
	for (s16 i = 0; i < 10; i++) { g_hi[i].score = 0; g_hi[i].rank = 0; g_hi[i].name[0] = 0; }
	disk_begin();
	Fdelete(save_path("HISCORE.DAT"));
	disk_end();
}
COLD static void hi_sort()					// 19320: descending by score
{
	for (s16 n = 0; n < 9; n++)
		for (s16 i = 0; i < 9; i++)
			if (g_hi[i].score < g_hi[i + 1].score) { hiscore_t t = g_hi[i]; g_hi[i] = g_hi[i + 1]; g_hi[i + 1] = t; }
}

static char *str_cat(char *_d, const char *_s) { while (*_s) *_d++ = *_s++; *_d = 0; return _d; }
static char *str_num(char *_d, s32 _v, s16 _width)		// left-aligned, padded with spaces to _width
{
	char b[12]; s16 n = 0;
	do { b[n++] = (char)('0' + _v % 10); _v /= 10; } while (_v && n < 11);
	s16 w = n;
	while (n) *_d++ = b[--n];
	for (; w < _width; w++) *_d++ = ' ';
	*_d = 0;
	return _d;
}

// ---- picture pages ----
COLD static void pic_close()
{
	g_pic_loader = false;
	if (!g_pic) return;
	if (g_pic != g_loader) efree(g_pic);
	g_pic = 0;
	g_pic_restore = true;
}

static inline u16 ste_rgb(u16 _rgb)			// 0x0RGB with 4-bit guns -> STE colour word (lowest bit of a gun in bit 3)
{
	u16 n = ((_rgb >> 1) & 0x777) | ((_rgb & 0x111) << 3);
	return n;
}

// a strip in screen format (16-px groups of 4 plane words) into the picture at group column _gx, row _y
COLD static void pic_strip(const u8 *_src, s16 _gx, s16 _y, s16 _groups, s16 _rows)
{
	for (s16 r = 0; r < _rows; r++, _src += _groups * 8)
		qmemcpy(g_pic + 32 + (_y + r) * 160 + _gx * 8, _src, _groups * 8);
	g_pic_dirty = 2;
}

// text in the 5x7 message font (upper case), drawn into the picture in colour _col
COLD static void pic_text(s16 _x, s16 _y, const char *_s, s16 _col)
{
	for (; *_s; _s++, _x += 6)
	{
		char ch = *_s;
		if (ch >= 'a' && ch <= 'z') ch -= 32;
		if (ch <= 32 || ch > 95) continue;
		spritesheet::spf_header *f = tfont_asset.get()->frameindex[ch - 32];
		s16 wg = (f->w + 15) >> 4;
		const u16 *d = (const u16 *)f->framedata;		// per row, per 16 px: mask (1 = transparent) + 4 planes
		for (s16 r = 0; r < f->h; r++)
			for (s16 g = 0; g < wg; g++, d += 5)
			{
				u16 ink = ~d[0];
				if (g == wg - 1 && (f->w & 15)) ink &= (u16)(0xffff << (16 - (f->w & 15)));
				s16 px = _x + f->xo + g * 16, py = _y + f->yo + r;
				if (!ink || py < 0 || py >= 200 || px < 0 || px > 303) continue;
				u16 *b = (u16 *)(g_pic + 32 + py * 160 + (px >> 4) * 8);
				s16 sh = px & 15;
				u16 hi = ink >> sh, lo = sh ? (u16)(ink << (16 - sh)) : 0;
				for (s16 p = 0; p < 4; p++)
				{
					if ((_col >> p) & 1) { b[p] |= hi; b[4 + p] |= lo; }
					else { b[p] &= ~hi; b[4 + p] &= ~lo; }
				}
			}
	}
	g_pic_dirty = 2;
}

COLD static void pic_hline(s16 _x0, s16 _x1, s16 _y, s16 _col)
{
	for (s16 x = _x0; x <= _x1; x++)
	{
		u16 *b = (u16 *)(g_pic + 32 + _y * 160 + (x >> 4) * 8), m = (u16)(0x8000 >> (x & 15));
		for (s16 p = 0; p < 4; p++) { if ((_col >> p) & 1) b[p] |= m; else b[p] &= ~m; }
	}
}
COLD static void pic_fill(s16 _x0, s16 _x1, s16 _y0, s16 _y1, s16 _col) { for (s16 y = _y0; y <= _y1; y++) pic_hline(_x0, _x1, y, _col); g_pic_dirty = 2; }

static s16 pic_brightest()					// palette index of the lightest colour (text)
{
	s16 best = -1, idx = 1;
	const u16 *pal = (const u16 *)g_pic;
	for (s16 c = 1; c < 16; c++) { s16 v = ste_lum(pal[c]); if (v > best) { best = v; idx = c; } }
	return idx;
}

COLD static void pic_rank_cursor(s16 _old, s16 _new)	// rank select: the bar behind the chosen line (strips after the screen)
{
	const u8 *x = g_pic + 32032;
	if (_old >= 0) pic_strip(x + (8 + _old) * 864, 4, 91 + 10 * _old, 12, 9);
	pic_strip(x + _new * 864, 4, 91 + 10 * _new, 12, 9);
}

COLD static void pic_name_field()				// name entry: the text field at (82, 102), pen 6, with its cursor
{
	pic_fill(81, 224, 101, 112, 0);
	pic_text(82, 103, g_name, 6);
	pic_fill(82 + g_name_len * 6, 82 + g_name_len * 6 + 4, 110, 110, 6);
}

// ---- save / load dialog (FUN_18b96): 6 slots, Exit Game, Cancel; the cursor line is shown inverted ----
static s16 g_dlg_cur = 7;				// 0..5 slots, 6 Exit Game, 7 Cancel
static bool g_dlg_rank = false;			// opened from the rank selection (Cancel goes back there)
static bool g_dlg_used[6];
static char g_dlg_name[6][20];
static s16 g_dlg_letter[6];
static const char *g_dlg_msg = 0;
COLD static void dlg_scan()
{
	disk_begin();
	for (s16 i = 0; i < 6; i++)
	{
		save_head_t hd;
		g_dlg_used[i] = save_peek(i, hd);
		g_dlg_letter[i] = g_dlg_used[i] ? hd.letter : 0;
		for (s16 k = 0; k < 20; k++) g_dlg_name[i][k] = g_dlg_used[i] ? hd.name[k] : 0;
	}
	disk_end();
}
COLD static void dlg_box(s16 _x0, s16 _y0, s16 _x1, s16 _y1, bool _hl)
{
	pic_hline(_x0, _x1, _y0, 15); pic_hline(_x0, _x1, _y1, 15);
	pic_fill(_x0, _x0, _y0, _y1, 15); pic_fill(_x1, _x1, _y0, _y1, 15);
	if (_hl) pic_fill(_x0 + 1, _x1 - 1, _y0 + 1, _y1 - 1, 15);
}
COLD static void dlg_draw()
{
	if (!g_pic) return;
	qmemclr(g_pic + 32, 32000);
	pic_text(85, 13, g_page == PG_SAVE ? "SAVE GAME" : "LOAD GAME", 15);
	if (g_dlg_msg) pic_text(10, 3, g_dlg_msg, 7);
	else if (g_dlg_edit) pic_text(43, 44, "TYPE A NAME, THEN RETURN", 6);
	for (s16 i = 0; i < 6; i++)
	{
		s16 y0 = 59 + 16 * i;
		bool hl = g_dlg_cur == i, edit = hl && g_dlg_edit;
		dlg_box(43, y0, 282, y0 + 10, hl);
		pic_text(46, y0 + 2, edit ? g_name : g_dlg_name[i], hl ? 0 : 15);
		if (edit) pic_fill(46 + g_name_len * 6, 46 + g_name_len * 6 + 4, y0 + 9, y0 + 9, 0);
	}
	dlg_box(43, 183, 147, 199, g_dlg_cur == 6);
	pic_text(63, 188, "EXIT GAME", g_dlg_cur == 6 ? 0 : 15);
	dlg_box(205, 183, 285, 199, g_dlg_cur == 7);
	pic_text(222, 188, "CANCEL", g_dlg_cur == 7 ? 0 : 15);
	g_pic_dirty = 2;
}

COLD static void pic_open(s16 _p)
{
	static const u16 c_dlg_pal[16] = { 0x000, 0x28F, 0x05E, 0x00C, 0xF80, 0x0F0, 0xCCC, 0xF26, 0xFF0, 0xBF0, 0x8E0, 0x0F0, 0x2C0, 0x0B1, 0xFFF, 0x999 };	// 0x25960
	static const u16 c_name_pal[16] = { 0x000, 0xECA, 0xE00, 0xA00, 0xD80, 0xFE0, 0x8F0, 0x080, 0x0B6, 0x0DD, 0x0AF, 0x07C, 0x00F, 0x70F, 0xC0E, 0xC08 };	// 0x259ac
	u32 info = 0;
	const char *name = _p == PG_RANK ? "rank.pic" : _p == PG_BRIEF ? "brief.pic" : _p == PG_SCORES ? "hiscore.pic" : 0;
	if (name)
	{
		if (!file_exists(name)) return;
		g_pic = load_asset(name, af_load_unwrapped, &info);
	}
	else
	{
		g_pic = (u8 *)ealloc(32032);
		bool dlg = _p == PG_LOAD || _p == PG_SAVE;
		if (g_pic) { qmemclr(g_pic, 32032); for (s16 c = 0; c < 16; c++) ((u16 *)g_pic)[c] = ste_rgb(dlg ? c_dlg_pal[c] : c_name_pal[c]); }
	}
	if (!g_pic) return;
	g_pic_restore = false;
	g_pic_pending = true; g_pic_hold = 3;	// (black from this frame on; the copy starts when it shows)
	g_pic_dirty = 2;
	switch (_p)
	{
	case PG_RANK:
		pic_rank_cursor(-1, g_rank_sel);
		break;
	case PG_BRIEF:							// rank name at (148,61), mission (170,73), islands (170,119), ships (170,131)
	{
		s16 mission, rank = map_rank(g_map_letter, &mission);
		const u8 *x = g_pic + 32032;
		pic_strip(x + rank * 480, 9, 61, 5, 12);
		pic_strip(x + 7 * 480 + (mission % 10) * 192, 10, 73, 2, 12);
		pic_strip(x + 7 * 480 + (g_islands_left % 10) * 192, 10, 119, 2, 12);
		pic_strip(x + 7 * 480 + (g_ships_left % 10) * 192, 10, 131, 2, 12);
		break;
	}
	case PG_LOAD:							// load: starts on the first saved game, or on Cancel when there is none
	case PG_SAVE:
		dlg_scan();
		g_dlg_edit = false;
		g_dlg_msg = 0;
		g_dlg_cur = _p == PG_SAVE ? 0 : 7;
		if (_p == PG_LOAD) for (s16 i = 5; i >= 0; i--) if (g_dlg_used[i]) g_dlg_cur = i;
		dlg_draw();
		break;
	case PG_NAME:							// 19472: pen 8 texts, pen 2 box (80,100)-(225,113), the field at (82,102)
		pic_text(82, 76, "YOUR NAME IS TO BE ENTERED", 8);
		pic_text(100, 86, "IN THE HALL OF FAME.", 8);
		pic_hline(80, 225, 100, 2); pic_hline(80, 225, 113, 2);
		pic_fill(80, 80, 100, 113, 2); pic_fill(225, 225, 100, 113, 2);
		pic_name_field();
		break;
	case PG_SCORES:							// 1967e: rows of 12 lines on the slab (from line 76), white on a black shadow
	{
		s16 white = pic_brightest();
		char b[20];
		for (s16 i = 0; i < 10; i++)
		{
			if (!g_hi[i].score) continue;
			s16 y = 76 + 6 + 12 * i;
			for (s16 pass = 0; pass < 3; pass++)
			{
				s16 o = pass == 0 ? -1 : pass == 1 ? 1 : 0, col = pass == 2 ? white : 0;
				str_num(b, i + 1, 0); pic_text(6 + o, y + o, b, col);
				str_num(b, g_hi[i].score, 0); pic_text(26 + o, y + o, b, col);
				pic_text(81 + o, y + o, c_rank_name[g_hi[i].rank < 0 || g_hi[i].rank > 6 ? 0 : g_hi[i].rank], col);
				pic_text(156 + o, y + o, g_hi[i].name, col);
			}
		}
		break;
	}
	}
}

// copy screen rows _row0.. of a picture page into a playfield's frame buffer at world position (_wx, _wy): the
// address as in AGT's sprite blitter (b_spr.s): buffer + (x & -16) / 2 + (y - snap) * line bytes. _wx must be a
// multiple of 16. The pictures have 200 rows, as the screen.
COLD static void pic_copy(const drawcontext_t &_c, s16 _wx, s16 _wy, s16 _row0, s16 _rows)
{
	u8 *row = (u8 *)_c.p_pfframebuffer + ((_wx & -16) >> 1) + (s32)(_wy - _c.pfsnapadjy) * g_linebytes;
	s16 p = _row0;
	for (; _rows > 0; _rows--, p++, row += g_linebytes)
	{
		u32 *d = (u32 *)row;
		if (p >= 0 && p < 200)
		{
			const u32 *q = (const u32 *)(g_pic + 32 + p * 160);
			for (s16 n = 5; n > 0; n--, d += 8, q += 8)
			{
				d[0] = q[0]; d[1] = q[1]; d[2] = q[2]; d[3] = q[3]; d[4] = q[4]; d[5] = q[5]; d[6] = q[6]; d[7] = q[7];
			}
		}
		else
			for (s16 n = 40; n > 0; n--) *d++ = 0;
	}
}

// 3.5" disk icon (16x16, two tones): shown in the top right corner whenever files are read
#define ICON_Y 2
#define ICON_TOS(_scr_) (_scr_)
COLD static void icon_draw(u8 *_scr, s16 _body, s16 _detail, u16 *_save)	// _scr: 4-plane screen rows of 160 bytes
{
	static const u16 c_body[16] = { 0x7ffc, 0xfffe, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7ffe };
	static const u16 c_detail[16] = { 0x0000, 0x0fe0, 0x0f20, 0x0f20, 0x0f20, 0x0fe0, 0x0000, 0x0000,
		0x0000, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0000 };
	for (s16 r = 0; r < 16; r++)
	{
		u16 *w = (u16 *)(_scr + (ICON_Y + r) * 160 + 18 * 8);
		u16 b = c_body[r], d = c_detail[r];
		for (s16 p = 0; p < 4; p++)
		{
			if (_save) _save[r * 4 + p] = w[p];
			w[p] = (u16)((w[p] & ~b) | (((_body >> p) & 1) ? (b & ~d) : 0) | (((_detail >> p) & 1) ? d : 0));
		}
	}
}
COLD static void icon_restore(u8 *_scr, const u16 *_save)
{
	for (s16 r = 0; r < 16; r++)
		for (s16 p = 0; p < 4; p++) ((u16 *)(_scr + (ICON_Y + r) * 160 + 18 * 8))[p] = _save[r * 4 + p];
}

// The loading screen: black with the disk icon; one permanent buffer (a picture page of 200 rows).
// While files are read AGT's display runs without the screen split (its 'DMA safe' VBL): the playfield buffers
// would show with whatever lies below them. With the local AGT patch g_dmasafe_screen that mode shows this buffer
// instead.
extern "C" u32 g_dmasafe_screen;
COLD static void loader_init()
{
	g_loader = (u8 *)ealloc(32 + 200 * 160);
	if (!g_loader) return;
	qmemclr(g_loader, 32 + 200 * 160);
	((u16 *)g_loader)[15] = ste_rgb(0xBBB);
	((u16 *)g_loader)[1] = ste_rgb(0x446);
	icon_draw(g_loader + 32, 15, 1, 0);
	g_dmasafe_screen = (u32)(g_loader + 32);
}
COLD static void load_screen()
{
	if (!g_loader) return;
	if (g_pic && g_pic != g_loader) efree(g_pic);
	g_pic = g_loader;
	g_pic_loader = true;
	g_pic_restore = false;
	g_pic_pending = true; g_pic_hold = 3;	// (black from this frame on; the copy starts when it shows)
	g_pic_dirty = 2;
}

COLD static void page_close()
{
	if (g_pic)								// back to the game: black first, then the picture goes (see the main loop)
	{
		if (!g_pic_closing) { g_pic_closing = 3; g_cover = 8; }
		return;
	}
	g_page = PG_NONE;
}

COLD static void page_open(s16 _p)
{
	pic_close();
	g_page = _p;
	g_page_t0 = vbl_now();
	g_help = false; g_pause = false;
	// music: song4 on the rank selection (18272), song1 from the name entry / high scores on (19856)
	if (_p == PG_RANK) { if (!(g_mus_state && g_mus_song == 4)) mus_play(4); }	// (back from the load dialog: it plays on)
	else if ((_p == PG_NAME || _p == PG_SCORES) && !(g_mus_state && g_mus_song == 0)) mus_play(0);
	pic_open(_p);
}

// open a page whose picture comes from disk: the loading screen first (the main loop opens the page when it shows)
COLD static void page_request(s16 _p)
{
	if (_p == PG_RANK && g_mus_state && g_mus_song != 4) mus_wait();	// (the song fades while the old page is still up)
	g_page = PG_NONE;
	g_page_next = _p;
	g_help = false; g_pause = false;
	load_screen();
	g_loading = 5;
}

static const char c_keys[0x3a] = {			// scancode -> character for the name fields
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', 0, 0, 0,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, 0, 0, 0, 'A', 'S',
	'D', 'F', 'G', 'H', 'J', 'K', 'L', 0, 0, 0, 0, 0, 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', ',', '.', 0, 0, 0, 0, ' ' };

// one call per frame while a page is up. _up / _down / _fire: stick or keys (the test rig passes its script input)
COLD static void page_tick(bool _up, bool _down, bool _fire)
{
	static bool s_fire_prev = true;		// (a fire held from before must be released first)
	static s16 s_rep = 0;
	if (g_pic_closing) return;
	bool hit = _fire && !s_fire_prev;
	s_fire_prev = _fire;
	s16 age = (s16)(vbl_now() - g_page_t0);
	switch (g_page)
	{
	case PG_RANK:						// stick up / down moves (repeats about every 9 VBLs), fire selects; 36 s time-out
		if (!_up && !_down) s_rep = 0;
		else if (s_rep > 0) s_rep--;
		else
		{
			s16 old = g_rank_sel;
			g_rank_sel += _up ? -1 : 1;
			s16 last = 7;									// (line 7: RETURN FROM R&R = load a saved game)
			if (g_rank_sel < 0) g_rank_sel = last;
			if (g_rank_sel > last) g_rank_sel = 0;
			if (g_pic) pic_rank_cursor(old, g_rank_sel);
			s_rep = 3;
			g_page_t0 = vbl_now();
		}
		if ((hit || age > 1800) && g_rank_sel == 7) { g_dlg_rank = true; page_request(PG_LOAD); }
		else if (hit || age > 1800)
		{
			g_score = 0; g_lives = 3; g_zero_kills = 0;		// new_game_init 13562
			g_gravity = 0x6000;
			mus_stop();										// (fades out: about 2 s)
			if (g_map_fresh && c_rank_map[g_rank_sel] == g_map_letter) page_request(PG_BRIEF);	// (already loaded and untouched)
			else { g_map_request = c_rank_map[g_rank_sel]; g_page = PG_NONE; }	// (the picture buffer becomes the loading screen)
		}
		break;
	case PG_BRIEF:						// 240 frames or fire
		if (hit || age > 240) page_close();
		break;
	case PG_LOAD:						// the save / load dialog: up / down, fire; in the save dialog then the slot's name
	case PG_SAVE:
		if (g_dlg_edit)
		{
			s16 was = g_name_len;
			for (s16 sc = 2; sc < 0x3a; sc++)
				if (debounced_key_releases[sc] && c_keys[sc] && g_name_len < 16) g_name[g_name_len++] = c_keys[sc];
			if (debounced_key_releases[ScanCode_BS] && g_name_len > 0) g_name_len--;
			g_name[g_name_len] = 0;
			if (debounced_key_releases[ScanCode_RETURN] || hit)
			{
				if (save_write(g_dlg_cur, g_name)) page_close();
				else
				{
					g_dlg_msg = g_save_nomem ? "NOT SAVED: NOT ENOUGH MEMORY" : "NOT SAVED: THE DISK IS FULL OR WRITE PROTECTED";
					g_dlg_edit = false;
					dlg_scan();
					dlg_draw();
				}
			}
			else if (debounced_key_releases[ScanCode_ESC]) { g_dlg_edit = false; dlg_draw(); }	// (Esc: back to the slots)
			else if (was != g_name_len) dlg_draw();
			break;
		}
		if (!_up && !_down) s_rep = 0;
		else if (s_rep > 0) s_rep--;
		else
		{
			for (s16 k = 0; k < 8; k++)				// (the load dialog skips the empty slots)
			{
				g_dlg_cur += _up ? -1 : 1;
				if (g_dlg_cur < 0) g_dlg_cur = 7;
				if (g_dlg_cur > 7) g_dlg_cur = 0;
				if (g_page == PG_SAVE || g_dlg_cur > 5 || g_dlg_used[g_dlg_cur]) break;
			}
			g_dlg_msg = 0;
			dlg_draw();
			s_rep = 3;
		}
		if (hit)
		{
			if (g_dlg_cur == 6) g_quit = true;							// Exit Game: quits the program
			else if (g_dlg_cur == 7) { if (g_dlg_rank) page_request(PG_RANK); else page_close(); }
			else if (g_page == PG_SAVE)
			{
				g_name_len = 0;
				for (; g_name_len < 16 && g_dlg_name[g_dlg_cur][g_name_len]; g_name_len++) g_name[g_name_len] = g_dlg_name[g_dlg_cur][g_name_len];
				g_name[g_name_len] = 0;
				g_dlg_edit = true;
				g_dlg_msg = 0;
				dlg_draw();
			}
			else if (g_dlg_used[g_dlg_cur])								// load: the mission's map first, then the state
			{
				mus_stop();
				g_load_slot = g_dlg_cur;
				g_map_request = g_dlg_letter[g_dlg_cur];
				g_page = PG_NONE;										// (the picture buffer becomes the loading screen)
			}
		}
		break;
	case PG_NAME:						// keyboard, 16 characters; Return or fire ends
	{
		for (s16 sc = 2; sc < 0x3a; sc++)
			if (debounced_key_releases[sc] && c_keys[sc] && g_name_len < 16) g_name[g_name_len++] = c_keys[sc];
		if (debounced_key_releases[ScanCode_BS] && g_name_len > 0) g_name_len--;
		{
			static s16 s_shown = -1;				// (the picture's field follows the typing)
			if (g_pic && (s_shown != g_name_len || age < 4)) { g_name[g_name_len] = 0; pic_name_field(); }
			s_shown = g_name_len;
		}
		g_name[g_name_len] = 0;
		if (hit || debounced_key_releases[ScanCode_RETURN])
		{
			hiscore_t &e = g_hi[9];
			e.score = g_score; e.rank = map_rank(g_map_letter, 0);
			for (s16 i = 0; i <= g_name_len; i++) e.name[i] = g_name[i];
			hi_sort();
			hi_save();
			page_request(PG_SCORES);
		}
		break;
	}
	case PG_SCORES:						// 1800 frames or fire, then back to the rank select
		if (hit || age > 1800) page_request(PG_RANK);
		break;
	}
	for (s16 sc = 2; sc < 0x80; sc++) debounced_key_releases[sc] = 0;	// (no game keys while a page is up; Esc still quits)
}

COLD static void page_draw(drawcontext_t &_c)
{
	char b[48];
	AGT_BLiT_IMSprInit();
	switch (g_page)
	{
	case PG_RANK:
		help_text(_c, 15, 1, "WINGS OF FURY");
		help_text(_c, 16, 3, "SELECT RANK");
		for (s16 i = 0; i < 7; i++)
		{
			if (i == g_rank_sel) help_text(_c, 11, 5 + i, ">");
			help_text(_c, 13, 5 + i, c_rank_menu[i]);
			if (i == g_rank_sel) help_text(_c, 31, 5 + i, "<");
		}
		help_text(_c, 7, 13, "STICK UP / DOWN, FIRE TO START");
		break;
	case PG_BRIEF:
	{
		s16 mission, rank = map_rank(g_map_letter, &mission);
		str_cat(str_cat(b, "RANK:     "), c_rank_name[rank]);
		help_text(_c, 10, 3, b);
		str_num(str_cat(b, "MISSION:  "), mission, 0);
		help_text(_c, 10, 5, b);
		help_text(_c, 10, 8, "MISSION OBJECTIVES:");
		str_num(str_cat(b, "ISLANDS:  "), g_islands_left, 0);
		help_text(_c, 10, 10, b);
		str_num(str_cat(b, "SHIPS:    "), g_ships_left, 0);
		help_text(_c, 10, 11, b);
		break;
	}
	case PG_NAME:
		help_text(_c, 9, 4, "YOUR NAME IS TO BE ENTERED");
		help_text(_c, 12, 5, "IN THE HALL OF FAME.");
		str_cat(str_cat(b, g_name), "_");
		help_text(_c, 13, 8, b);
		help_text(_c, 11, 12, "RETURN OR FIRE WHEN DONE");
		break;
	case PG_SCORES:
		help_text(_c, 12, 0, "WINGS OF FURY - ACES");
		for (s16 i = 0; i < 10; i++)
		{
			if (!g_hi[i].score) continue;
			char *d = str_num(b, i + 1, 3);
			d = str_num(d, g_hi[i].score, 8);
			d = str_cat(d, c_rank_name[g_hi[i].rank < 0 || g_hi[i].rank > 6 ? 0 : g_hi[i].rank]);
			while (d < b + 24) *d++ = ' ';
			*d = 0;
			str_cat(d, g_hi[i].name);
			help_text(_c, 1, 2 + i, b);
		}
		break;
	}
}

// ---------------------------------------------------------------------------------------------------------------------
//	3-D forward view FUN_1417e (reverse-engineering/notes/forward_view.md): the window in the middle of the panel shows what lies
//	ahead in 11 depth bands (far to near, one row lower each): enemy planes, a sand line, a tree strip and one
//	object or ship per band, then the landing view over a deck and the target reticle. Every shape is centred, there
//	is no lateral position. The shapes (fpv_data.h) are halved and pre-clipped to the window (panel x 130..189).

static const u8 c_fpv_T[12] = { 6, 13, 21, 30, 40, 51, 63, 76, 90, 105, 130, 160 };	// 0x245f0: band limits (cells)
static const u8 c_fpv_S1[11] = { 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1 };					// G_24608: island object size
static const u8 c_fpv_S2[11] = { 7, 7, 6, 6, 5, 4, 3, 2, 1, 0, 0 };					// G_24614: ship size
static const u8 c_fpv_OFF[11] = { 0, 0, 0, 28, 28, 28, 56, 56, 56, 84, 84 };		// G_245e2: enemy plane size
static bool g_fpv_nolanding = false;		// G_2764c: set by an enemy ship in a band, cleared by a carrier

// FUN_14a52: 0 none, 1 transport, 2 destroyer, 3 battleship, 4 J-carrier, 5 own carrier
static s16 fpv_ship_at(s16 _cell)
{
	if (_cell < 0 || _cell >= MAP_CELLS) return 0;
	s16 x = _cell * 8;
	ship_t *sh = ship_at(x);
	if (sh) return sh->type == 0xcc ? 1 : sh->type == 0xe4 ? 2 : sh->type == 0x10d ? 3 : 4;
	if (g_carrier.alive && x >= g_carrier.x0 && x <= g_carrier.x1) return 5;
	return 0;
}

// The view is composed in a 64x25 buffer in screen format (per row 4 words x 4 planes; the window is its pixels
// 2..61) and copied into both screen buffers when it changes: one AGT sprite draw per shape cost about 1 ms each,
// and a single 60x25 sprite about 4 ms. The list of draw operations is rebuilt only when its inputs change, and the
// base layer is composed again only when the list changes.
struct fpv_op_t { u8 shape; s8 y; u8 clip, bot; };	// shape 254 = sand line; y = reference row; window rows clip..bot-1
#define FPV_MAXOPS 96
static fpv_op_t g_fpv_ops[FPV_MAXOPS];
static s16 g_fpv_nops = 0;
static u16 g_fpv_base[25 * 16], g_fpv_top[25 * 16];	// layers in screen format (window rows 0..24 = panel rows 7..31):
static u16 *g_fpv_cv = g_fpv_top;					// base = sky, sea, bands, landing view; top = base + reticle + arrow

static inline void fpv_op(s16 _shape, s16 _y, s16 _clip, s16 _bot)
{
	if (_shape == 255 || g_fpv_nops >= FPV_MAXOPS || _y < -100 || _y > 100) return;
	fpv_op_t &o = g_fpv_ops[g_fpv_nops++];
	o.shape = (u8)_shape; o.y = (s8)_y; o.clip = (u8)_clip; o.bot = (u8)_bot;
}

static void fpv_fill(s16 _r0, s16 _r1, s16 _col)		// rows _r0.._r1 of the window in one colour
{
	if (_r0 < 0) _r0 = 0;
	if (_r1 > 24) _r1 = 24;
	if (_r0 > _r1) return;
	u16 row[16];
	for (s16 c = 0; c < 4; c++)
	{
		u16 full = (c == 0) ? 0x3fff : (c == 3) ? 0xfffc : 0xffff;		// pixels 2..61
		for (s16 pl = 0; pl < 4; pl++) row[c * 4 + pl] = ((_col >> pl) & 1) ? full : 0;
	}
	u32 *d = (u32 *)(g_fpv_cv + _r0 * 16);
	const u32 *q = (const u32 *)row;
	u32 a = q[0], b = q[1], c2 = q[2], e = q[3], f = q[4], g = q[5], h = q[6], k = q[7];
	for (s16 r = _r1 - _r0; r >= 0; r--, d += 8)
	{
		d[0] = a; d[1] = b; d[2] = c2; d[3] = e; d[4] = f; d[5] = g; d[6] = h; d[7] = k;
	}
}

static void fpv_blit(const fpv_op_t &_o)
{
	if (_o.shape == 254) { if (_o.y - 7 < (s16)_o.bot) fpv_fill(_o.y - 7, _o.y - 7, 5); return; }
	const fpv_shape_t &h = c_fpv_hdr[_o.shape];
	s16 r = _o.y - 7 + h.top;
	s16 clip = (s16)_o.clip - 7, bot = _o.bot;
	const u16 *src = &c_fpv_bits[h.ofs];
	s16 stride = h.nc * 5;
	for (s16 i = h.rows; i > 0; i--, r++, src += stride)
	{
		if (r < clip || r < 0) continue;
		if (r >= bot) break;
		u16 *d = g_fpv_cv + r * 16 + h.c0 * 4;
		const u16 *q = src;
		for (s16 c = h.nc; c > 0; c--, d += 4, q += 5)
		{
			u16 m = q[0];
			if (!m) continue;
			if (m == 0xffff) { d[0] = q[1]; d[1] = q[2]; d[2] = q[3]; d[3] = q[4]; continue; }
			m = ~m;
			d[0] = (d[0] & m) | q[1]; d[1] = (d[1] & m) | q[2];
			d[2] = (d[2] & m) | q[3]; d[3] = (d[3] & m) | q[4];
		}
	}
}

// FUN_145a6: cell type -> frame
static s16 fpv_shape(s16 _type, s16 _surf, s16 _k, s16 _after, s16 _dir)
{
	s16 s1 = c_fpv_S1[_k];
	if (_type >= 6 && _type <= 8) return c_fpv_dash[14 + s1];		// trees: 3dl5..3dl9, dug0
	if (_type == 4) return c_fpv_dash[27 + s1];						// hut
	if (_type == 5) return c_fpv_dash[34 + s1];						// destroyed hut
	if (_type == 3) return c_fpv_dash[20 + s1];						// bunker
	if (_surf == 1)
	{
		s16 D = (_dir < 0) ? 10 : 0, s2 = c_fpv_S2[_k];
		if (_type == 34 || _type == 246) return c_fpv_dash[77 + D + s2];	// tower cell (index as in the original)
		s16 r = fpv_ship_at(_after);
		if (!r) return 255;
		if (r <= 3) { g_fpv_nolanding = true; return c_fpv_ship[(r - 1) * 16 + (_dir < 0 ? 8 : 0) + s2]; }
		g_fpv_nolanding = false;
		return c_fpv_dash[60 + D + s2];								// own carrier / J-carrier
	}
	if (_type == 15) return c_fpv_dash[41 + s1];					// pillbox
	if (_type >= 16 && _type <= 30) return c_fpv_dash[48 + s1];		// damaged pillbox
	return 255;
}

struct fpv_band_t { u8 trees, obj; bool sand, any; };
static fpv_band_t g_fpv_band[11];
static s16 g_fpv_tower_lo = 0, g_fpv_tower_hi = -1;	// range of the cells with tower types 34 / 246
// per map cell, for a fast scan: 1 island surface, 2 tree type (6..8), 4 other type, 8 tower type, 16 deck surface
static u8 g_fpv_cls[MAX_MAP_CELLS];

static void fpv_reset()
{
	g_fpv_tower_lo = 0x7fff; g_fpv_tower_hi = -1;
	for (s16 c = 0; c < MAP_CELLS; c++)
	{
		u16 m = c_map[c];
		s16 t = (m >> 2) & 0x1ff, surf = m & 3;
		u8 f = (surf == 2) ? 1 : (surf == 1) ? 16 : 0;
		if (t >= 6 && t <= 8) f |= 2;
		else if (t) f |= 4;
		if (t == 34 || t == 246)
		{
			f |= 8;
			if (c < g_fpv_tower_lo) g_fpv_tower_lo = c;
			g_fpv_tower_hi = c;
		}
		g_fpv_cls[c] = f;
	}
	g_fpv_stale = false;
}

// the terrain scan of the 11 bands (FUN_14206 part b + FUN_145a6). The original scans each band from near to far
// and keeps the last type found (a tower cell 34 / 246 sticks); here from the far end, so the first hit is the
// result and the scan stops early. Only a band that may hold tower cells (carriers) is scanned to its end.
static void fpv_scan(s16 xc, s16 dir, s16 hide)
{
	static s16 s_last_surf = 0;										// G_255dd
	for (s16 k = 10; k >= 0; k--)
	{
		s16 fr = c_fpv_T[k + 1], count = fr - c_fpv_T[k];
		s16 obj = -1, trees = -1;
		bool sand = false;
		s16 c0 = dir > 0 ? xc + fr : xc - fr - count;				// lowest cell of the band; off-map cells are skipped
		s16 c1 = c0 + count;
		if (c0 < 0) c0 = 0;
		if (c1 >= MAP_CELLS) c1 = MAP_CELLS - 1;
		if (c0 <= c1)
		{
			s16 far_c = dir > 0 ? c1 : c0;
			s_last_surf = c_map[far_c] & 3;
			bool towers = c0 <= g_fpv_tower_hi && c1 >= g_fpv_tower_lo;
			u8 want = 1 | 2 | 4, skip = (hide == 1) ? 16 : 0;
			const u8 *p = &g_fpv_cls[far_c];
			for (s16 i = c1 - c0; i >= 0; i--, p -= dir)
			{
				u8 f = *p;
				if (!(f & want)) continue;
				if (f & 1) { sand = true; want &= ~1; }
				if (f & skip) continue;								// (over a carrier its cells are no band objects)
				if (f & want & 2) { trees = (c_map[p - g_fpv_cls] >> 2) & 0x1ff; want &= ~2; }
				else if (f & want & 4)
				{
					s16 type = (c_map[p - g_fpv_cls] >> 2) & 0x1ff;
					if (f & 8) obj = type;							// (the nearest tower cell wins)
					else if (obj < 0) obj = type;
					if (!towers) want &= ~4;
				}
				if (!want) break;
			}
		}
		s16 after = dir > 0 ? xc + fr + count + 1 : xc - fr - count - 1;
		fpv_band_t &b = g_fpv_band[k];
		b.sand = sand;
		b.trees = (trees >= 0) ? (u8)fpv_shape(trees, s_last_surf, k, after, dir) : 255;
		b.obj = (obj >= 0) ? (u8)fpv_shape(obj, s_last_surf, k, after, dir) : 255;
		b.any = sand || b.trees != 255 || b.obj != 255;
	}
}

static void fpv_draw(drawcontext_t &_pc)
{
	if (g_fpv_mode == 0) return;
	static s16 s_xc = 0x7fff, s_dir = 0, s_hide = 0, s_age = 0, s_n = 0, s_map = 0;
	static u16 s_gen = 0, s_sig = 0xffff;
	static u32 s_key = 0xffffffffUL;
	static s16 s_top = -1, s_dirty = 0, s_age2 = 0;
	static bool s_have_base = false;			// (nothing is shown before the base layer was composed once)
	static bool s_odd = false;

	// The view is evaluated every second frame, and a scan, a composition and the copies to the screen are done
	// in different frames (compiled C on a 68000: a terrain scan costs about 4 ms, a composition up to 7 ms, a
	// copy 2 ms; together they would cost the main view a VBL). The original redraws it every frame.
	bool worked = false;
	s_odd = !s_odd;
	if (s_odd || g_fpv_stale)
	{
		s16 alt = P.y < 0 ? 0 : P.y;
		s16 H = (alt >> 4) + 24;									// horizon row G_25336
		s16 ry = alt >= 81 ? 13 : 13 + ((81 - alt) >> 2);			// target reticle row FUN_141b4
		s16 xc = (s16)(P.x >> 3);
		s16 xt = (s16)((P.x + g_out) >> 3);						// the terrain's cell: the true position (clamp_world_x)
		s16 dir = (P.dir < 0) ? -1 : 1;
		bool view = !g_zoom && g_fpv_mode > 1;						// (1/8 view: sky and sea only)
		bool on_deck_cell = false;
		s16 zn = 0, zd[NZERO], zf[NZERO], zy[NZERO];
		s16 arrow = 255;
		for (s16 e = 0; e < NZERO; e++)
		{
			const zero_t &z = g_zero[e];
			if (!z.state) continue;
			// enemy-plane warning (FUN_1f21a): 'ltar' / 'rtar' at hires (320,10) while a carrier bomber
			// (mode & 7 == 4) is in the air, pointing to its side of the player. It lies inside the window
			if (arrow == 255 && (z.mode & 7) == 4) arrow = c_fpv_arrow[(s16)P.x - z.x >= 0 ? 0 : 1];
			// planes ahead: distance in flight direction (cells) and frame
			s16 d = (z.x >> 3) - xc; if (dir < 0) d = -d;
			if (!view || d < 6 || d > 160) continue;
			s16 f = z.sprite;
			if (dir >= 0) { f += 28; if (f >= 56) f -= 56; }
			zd[zn] = d; zf[zn] = f; zy[zn] = 4 + (z.alt >> 2); zn++;
		}
		if (view)
		{
			if (s_map != g_map_letter) { s_map = g_map_letter; g_fpv_stale = true; }
			if (g_fpv_stale) { fpv_reset(); s_xc = 0x7fff; }
			on_deck_cell = xt >= 0 && xt < MAP_CELLS && (c_map[xt] & 3) == 1;
			s16 hide = 4;
			if (on_deck_cell) { s16 r = fpv_ship_at(xt); if (r == 0 || r >= 4) hide = 1; }	// over a carrier: its cells are not band objects
			// the scan is redone when the plane has moved 4 cells (the bands are 7..30 cells deep) or turned, and
			// now and then for changes of the map (wrecked huts)
			s16 moved = xt - s_xc; if (moved < 0) moved = -moved;
			if (s_dirty == 0 && (moved >= 4 || dir != s_dir || hide != s_hide || ++s_age >= 8))	// (not while a change waits for its copies)
			{
				s_xc = xt; s_dir = dir; s_hide = hide; s_age = 0;
				fpv_band_t old[11];
				for (s16 k = 0; k < 11; k++) old[k] = g_fpv_band[k];
				s16 n = 0;											// FUN_14430: deck cells behind the plane
				fpv_scan(xt, dir, hide);
				if (on_deck_cell)
				{
					const u16 *p = &c_map[xt];
					s16 left = (dir >= 0) ? xt : MAP_CELLS - 1 - xt;
					if (left > 95) left = 95;
					while (n <= left && ((*p >> 2) & 0x1ff) != 0) { n++; p -= dir; }
				}
				bool same = n / 6 == s_n / 6;
				for (s16 k = 0; k < 11 && same; k++)
					same = old[k].trees == g_fpv_band[k].trees && old[k].obj == g_fpv_band[k].obj && old[k].sand == g_fpv_band[k].sand;
				s_n = n;
				if (!same) s_gen++;
				g_fpv_stat[0]++;
				worked = true;
			}
		}

		// base layer (sky, sea, bands, landing view): its list of draw operations is rebuilt when the inputs
		// changed (always while enemy planes are in the view, and once more when the last one has left it), and
		// composed when the list changed
		u32 key = ((u32)s_gen << 16) ^ ((u32)H << 8) ^ (view ? 0x80UL : 0) ^ (on_deck_cell ? 0x40UL : 0)
			^ (g_fpv_nolanding ? 0x20UL : 0) ^ (u32)g_fpv_mode;
		static bool s_planes = false;
		if (!worked && (key != s_key || zn || s_planes))
		{
			s_key = key; g_fpv_stat[1]++;
			s_planes = zn != 0;
			g_fpv_nops = 0;
			if (view)
			{
				// rows of a band that a nearer band's tree strip covers completely are not drawn: bot[k] = first such row
				s16 bot[11], cover = 25;
				for (s16 k = 0; k <= 10; k++)
				{
					bot[k] = cover;
					u8 t = g_fpv_band[k].trees;
					if (t == 255) continue;
					const fpv_shape_t &h = c_fpv_hdr[t];
					if (h.solid >= h.rows) continue;
					s16 r = (H + 10 - k) - 7 + h.top + h.solid;
					if (r < cover) cover = r < 0 ? 0 : r;
				}
				s16 Y = H;
				for (s16 k = 10; k >= 0; k--, Y++)
				{
					for (s16 e = 0; e < zn; e++)					// planes at distance near..far (both ends inclusive)
						if (zd[e] >= c_fpv_T[k] && zd[e] <= c_fpv_T[k + 1]) fpv_op(c_fpv_zr[zf[e] + c_fpv_OFF[k]], Y - zy[e], 7, bot[k]);
					const fpv_band_t &b = g_fpv_band[k];
					if (!b.any) continue;
					if (b.sand && Y <= 31) fpv_op(254, Y, 7, bot[k]);
					fpv_op(b.trees, Y, 7, bot[k]);
					fpv_op(b.obj, Y, 7, bot[k]);
				}
				if (g_fpv_mode > 2 && !g_fpv_nolanding && on_deck_cell)	// landing view FUN_14430
				{
					s16 idx = s_n / 6; if (idx > 15) idx = 15;
					s16 yb = H + 9 + idx;
					s16 v = idx >> 1; if (v > 3) v = 3;
					s16 ytop = H + (idx > 7 ? idx - 7 : 0);			// clip top for the deck pieces
					fpv_op(c_fpv_dash[56 + v], yb + 1, ytop, 25);	// dec0..dec3: the striped deck
					fpv_op(c_fpv_dash[dir >= 0 ? 65 : 73], yb, ytop, 25);	// 3dcf / 3dcn: near part of the deck
					fpv_op(c_fpv_dash[dir >= 0 ? 81 : 89], yb, 7, 25);	// 3dtf / 3dtn: the tower
				}
			}
			u16 sig = (u16)(H * 31 + g_fpv_nops);
			for (s16 i = 0; i < g_fpv_nops; i++)
				sig = (u16)((sig << 3) ^ (sig >> 13) ^ ((u16)g_fpv_ops[i].shape << 8) ^ (u8)g_fpv_ops[i].y ^ ((u16)g_fpv_ops[i].clip << 4) ^ g_fpv_ops[i].bot);
			if (sig != s_sig)
			{
				s_sig = sig; g_fpv_stat[2]++;
				u16 *cv = g_fpv_cv;
				g_fpv_cv = g_fpv_base;								// (compose into the base layer)
				fpv_fill(0, H - 8, 2);								// sky (colour 2), sea from the horizon (colour 1)
				fpv_fill(H - 7, 24, 1);
				for (s16 i = 0; i < g_fpv_nops; i++) fpv_blit(g_fpv_ops[i]);
				g_fpv_cv = cv;
				s_top = -1;
				s_have_base = true;
				worked = true;
			}
		}

		// top layer: target reticle and warning arrow over a copy of the base layer
		s16 top = (view && g_fpv_mode > 2 ? ry : 0) | (arrow << 8);
		if (top != s_top && s_have_base)
		{
			s_top = top;
			const u32 *q = (const u32 *)g_fpv_base;
			u32 *d = (u32 *)g_fpv_cv;
			for (s16 n = 25; n > 0; n--, d += 8, q += 8)
			{
				d[0] = q[0]; d[1] = q[1]; d[2] = q[2]; d[3] = q[3]; d[4] = q[4]; d[5] = q[5]; d[6] = q[6]; d[7] = q[7];
			}
			fpv_op_t o;
			o.clip = 7; o.bot = 25;
			if (view && g_fpv_mode > 2) { o.shape = c_fpv_dash[5]; o.y = (s8)ry; fpv_blit(o); }
			if (arrow != 255) { o.shape = (u8)arrow; o.y = 10; fpv_blit(o); }
			s_dirty = 2;
		}
	}
	if ((++s_age2 >= 64 || g_fpv_redraw) && s_have_base) { s_age2 = 0; s_dirty = 2; g_fpv_redraw = false; }				// (refresh now and then: heals a rebuilt panel)
	if (s_dirty && !worked)
	{
		// copied into the frame buffer being drawn, for two frames (both buffers). Nothing else is drawn inside
		// the window, so AGT's sprite restore never touches it. Address as in AGT's sprite blitter (b_spr.s):
		// buffer + (x & -16) / 2 + (y - snap) * line bytes; the 2 border pixels left and right are kept.
		s_dirty--; g_fpv_stat[3]++;
		u32 *d = (u32 *)((u8 *)_pc.p_pfframebuffer + ((PANEL_MAP_X0 + 128) >> 1) + (s32)(7 - _pc.pfsnapadjy) * g_linebytes);
		const u32 *q = (const u32 *)g_fpv_cv;
		for (s16 r = 25; r > 0; r--, d = (u32 *)((u8 *)d + g_linebytes), q += 8)
		{
			d[0] = (d[0] & 0xc000c000UL) | q[0]; d[1] = (d[1] & 0xc000c000UL) | q[1];
			d[2] = q[2]; d[3] = q[3]; d[4] = q[4]; d[5] = q[5];
			d[6] = (d[6] & 0x00030003UL) | q[6]; d[7] = (d[7] & 0x00030003UL) | q[7];
		}
	}
}

static void help_text(drawcontext_t &_c, s16 _col, s16 _line, const char *_s)
{
	s16 x = g_cam_x + 8 + _col * 7, y = g_cam_y + 3 + _line * 10;		// 15 lines fit the 200-line playfield
	for (; *_s; _s++, x += 7)
	{
		char ch = *_s;
		if (ch >= 'a' && ch <= 'z') ch -= 32;
		if (ch <= 32 || ch > 95) continue;
		AGT_BLiT_IMSprDrawClipped(&_c, font_asset.get(), ch - 32, x, y);
	}
}

COLD static void help_draw(drawcontext_t &_c)
{
	AGT_BLiT_IMSprInit();
	static const char *const c_lines[] = {
		"WINGS OF FURY STE - HELP",
		"STICK UP / DOWN   PITCH",
		"STICK TO NOSE     THROTTLE",
		"STICK TO TAIL     TURN AROUND",
		"FIRE TAP          BOMB / ROCKET / TORPEDO",
		"FIRE HOLD         MACHINE GUN",
		"ON DECK           UP / DOWN WEAPON, FIRE GO",
		"KEYS: CURSOR + SPACE",
		"ESC               PAUSE",
		"CTRL+R            BACK TO RANK SELECT",
		"CTRL+G / CTRL+L   SAVE (ON DECK) / LOAD",
		"CTRL+Q            QUIT" };
	s16 n = sizeof(c_lines) / sizeof(c_lines[0]);
	for (s16 i = 0; i < n; i++) help_text(_c, 0, i, c_lines[i]);
	help_text(_c, 0, n + 2, "H: BACK TO THE GAME");
}

// Start-up pictures (FUN_18022: 'broderbund', 'wingstitle', 'creditscreen'; tools/make_pics.py): raw 16-colour
// low-res screens shown on the plain TOS screen before the engine takes over the display. Any key skips; the
// original's fades and music are not in yet.
#if !defined(WOF_REPLAY)
static bool g_pics_skip = false;
// joystick fire before the engine starts: TOS hands the keyboard processor's joystick packets to a vector
extern "C" { volatile u8 s_intro_joy[2] = { 0, 0 }; void intro_joyvec(); }
__asm__(
	"	.text\n"
	"	.even\n"
	"	.globl	_intro_joyvec\n"
	"_intro_joyvec:\n"								// a0: packet (header, joystick 0, joystick 1)
	"	move.b	1(%a0),_s_intro_joy\n"
	"	move.b	2(%a0),_s_intro_joy+1\n"
	"	rts\n");
static void (*s_joy_old)() = 0;
COLD static void intro_joy(bool _on)
{
	void (**kv)() = (void (**)())Kbdvbase();		// (+24: joyvec)
	if (_on && !s_joy_old)
	{
		static const char c_cmd[] = { 0x14 };		// SET JOYSTICK EVENT REPORTING (TOS does not leave it on)
		s_joy_old = kv[6]; kv[6] = intro_joyvec;
		Ikbdws(0, c_cmd);
	}
	if (!_on && s_joy_old) { kv[6] = s_joy_old; s_joy_old = 0; }
}
COLD static bool intro_fire()						// fire pressed since the last call
{
	static bool s_prev = true;
	bool f = ((s_intro_joy[0] | s_intro_joy[1]) & 0x80) != 0, hit = f && !s_prev;
	s_prev = f;
	return hit;
}
static u16 s_icon_save[64];
COLD static void intro_icon(bool _on)				// the disk icon on the TOS screen (the title picture while the game loads)
{
	u8 *scr = (u8 *)Physbase();
	if (!_on) { icon_restore(ICON_TOS(scr), s_icon_save); return; }
	s16 hi = 0, lo = 0, best = -1, worst = 0x7fff;
	for (s16 c = 0; c < 16; c++)
	{
		s16 v = ste_lum(*(volatile u16 *)(0xffff8240L + 2 * c) & 0xfff);
		if (v > best) { best = v; hi = c; }
		if (v < worst) { worst = v; lo = c; }
	}
	icon_draw(ICON_TOS(scr), hi, lo, s_icon_save);
}
// Intro text scroller (FUN_17e80, reverse-engineering/notes/frontend.md 1.1): 53 lines in the Amiga's 'newarmyfont', justified to
// 615 px, scroll up 1 px every 4 frames on a 640x200 screen: ST medium resolution here, text in plane 0. The text
// fades in over the bottom 16 lines and out over the top 16: the original's copper list is a Timer B interrupt per
// line that sets colour 1. The scrolling is the STE's video base address moving down a line through a buffer that
// holds the picture twice (nothing is copied but the new text line). A key ends it.
static u16 s_intro_ramp[204];						// colour 1 per display line (STE colour words)
extern "C" { const u16 * volatile s_intro_ptr = 0; void intro_timer_b(); }
__asm__(											// per display line: the next colour (kept short: 200 calls per frame)
	"	.text\n"
	"	.even\n"
	"	.globl	_intro_timer_b\n"
	"_intro_timer_b:\n"
	"	move.l	%a0,-(%sp)\n"
	"	move.l	_s_intro_ptr,%a0\n"
	"	move.w	(%a0)+,0xffff8242:w\n"
	"	move.l	%a0,_s_intro_ptr\n"
	"	move.l	(%sp)+,%a0\n"
	"	move.b	#0xfe,0xfffffa0f:w\n"			// end of interrupt (ISRA bit 0)
	"	rte\n");
static volatile u32 s_intro_base = 0;				// video base address for the next frame
// The scroll steps are made here, every 4th VBL, whatever the main loop is doing (rendering a text line takes it
// several frames with the music mixing: stepping from the loop made the text hitch at every new line).
static volatile s16 s_intro_step = 0;				// steps made
static volatile bool s_intro_go = false;
static u32 s_intro_ring = 0;
static s16 s_intro_top = 0, s_intro_div = 0;
static void intro_vbl()								// in TOS's VBL queue: restart the line count, set the scroll position
{
	if (s_intro_go && ++s_intro_div >= 4)
	{
		s_intro_div = 0;
		s_intro_step++;
		if (++s_intro_top == 212) s_intro_top = 0;
		s_intro_base = s_intro_ring + (u32)s_intro_top * 160;
	}
	*(volatile u8 *)0xffff8201L = (u8)(s_intro_base >> 16);
	*(volatile u8 *)0xffff8203L = (u8)(s_intro_base >> 8);
	*(volatile u8 *)0xffff820dL = (u8)s_intro_base;	// (STE: the low byte last)
	*(volatile u8 *)0xfffffa1bL = 0;
	*(volatile u16 *)0xffff8242L = s_intro_ramp[0];
	s_intro_ptr = s_intro_ramp + 1;
	*(volatile u8 *)0xfffffa21L = 1;
	*(volatile u8 *)0xfffffa1bL = 8;				// event count: one interrupt per displayed line
}
COLD static void intro_ramp(s16 _n)						// FUN_17d4e: line L < n: grey L; middle: n - 1; lines 181..196: 196 - L
{
	for (s16 l = 0; l < 204; l++)
	{
		s16 v = (l < _n) ? l : _n - 1;
		if (l >= 181) { v = 196 - l; if (v > _n - 1) v = _n - 1; }
		if (v < 0) v = 0;
		u16 nib = (u16)((v >> 1) | ((v & 1) << 3));	// STE: the lowest bit of a gun is bit 3
		s_intro_ramp[l] = (u16)(nib * 0x111);
	}
}

COLD static void intro_scroller()
{
	u32 info = 0;
	u8 *dat = load_asset("intro.dat", af_load_unwrapped, &info);
	enum { IH = 212 };									// ring of 212 lines: 0..199 from the top line are visible, new text enters at 196
	u8 *work = (u8 *)ealloc(12 * 80 + 8);				// the new text line, 1 plane
	u8 *ring = (u8 *)ealloc(2 * IH * 160);
	if (!dat || !work || !ring) { if (dat) efree(dat); if (work) efree(work); if (ring) efree(ring); return; }
	const u8 *font = dat + 2;
	s16 fh = (font[0] << 8) | font[1], first = font[2], nch = font[3] - font[2] + 1;
	const u8 *fw = font + 4;
	const u8 *glyphs = fw + nch + (nch & 1);
	const u8 *txt = font + ((dat[0] << 8) | dat[1]);
	s16 nlines = (txt[0] << 8) | txt[1];
	txt += 2;
	static u16 goff[128];								// glyphs are stored one after the other: (w + 15) / 16 words x height
	{ u16 o = 0; for (s16 q = 0; q < nch && q < 128; q++) { goff[q] = o; o += ((fw[q] + 15) >> 4) * 2 * fh; } }
	qmemclr(ring, 2 * IH * 160);
	s16 top = 0;										// ring line shown at the top of the screen
	s_intro_base = s_intro_ring = (u32)ring;
	s_intro_step = 0; s_intro_top = 0; s_intro_div = 0; s_intro_go = false;

	Setscreen(-1L, -1L, 1);								// ST medium resolution
	Vsync();
	u16 *scr = (u16 *)Physbase();
	qmemclr(scr, 32000);
	static const u16 c_pal[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Setpalette((void *)c_pal);
	intro_ramp(16);

	// Timer B per line + a VBL queue entry
	volatile u8 *mfp = (volatile u8 *)0xfffffa01L;		// (+6: IERA, +0x12: IMRA, +0x1a: TBCR)
	u8 old_iera = mfp[6], old_imra = mfp[0x12];
	void (**vec)() = (void (**)())0x120L;
	void (*old_vec)() = *vec;
	mfp[0x1a] = 0;
	*vec = (void (*)())intro_timer_b;
	mfp[6] = old_iera | 1; mfp[0x12] = old_imra | 1;
	void (**vq)() = *(void (***)())0x456L;
	s16 nvq = *(s16 *)0x454L, slot = -1;
	bool music = g_mus_hooked;							// (the line count must restart before the music mixes: lower slot)
	mus_hook(false);
	for (s16 i = 0; i < nvq; i++) if (!vq[i]) { slot = i; break; }
	if (slot >= 0) vq[slot] = intro_vbl;
	if (music) mus_hook(true);

	volatile u32 *vbclock = (volatile u32 *)0x462L;
	u32 next = *vbclock;
	s16 c = 0, lines = 0, left = 210, fade = 0, iter = 0;
	const u8 *line = txt;
	s_intro_go = true;
	while (left >= 0 || fade > 0)
	{
		if (Bconstat(2)) { Bconin(2); break; }			// a key or fire ends the scroller only (the pictures follow)
		if (intro_fire()) break;
		if (left < 0)									// fade out: 2 frames per step
		{
			intro_ramp(fade--);
			next += 2;
			while ((s32)(*vbclock - next) < 0) { }
			continue;
		}
		if (c % 14 == 0)
		{
			qmemclr(work, 12 * 80 + 8);
			if (lines < nlines)
			{
				// justified text (FUN_15956): advance = glyph width + 1 (space: 10 + 1); a line followed by a
				// non-empty one is stretched to 615 px: every character gets extra / (len - 1) more, the first
				// extra % (len - 1) one more
				s16 len = 0, natural = 0;
				for (const u8 *p = line; *p; p++, len++) { s16 w = (*p >= first && *p < first + nch) ? fw[*p - first] : 0; natural += (w ? w : 10) + 1; }
				const u8 *nxt = line + len + 1;
				bool justify = lines + 1 < nlines && *nxt != 0 && len > 1 && natural < 615;
				s16 each = justify ? (615 - natural) / (len - 1) : 0, more = justify ? (615 - natural) % (len - 1) : 0;
				s16 x = 0;
				for (s16 k = 0; k < len; k++)
				{
					s16 ch = line[k] - first;
					s16 w = (ch >= 0 && ch < nch) ? fw[ch] : 0;
					if (w && x + w <= 640)
					{
						const u8 *g = glyphs + goff[ch & 127];
						s16 gw = (w + 15) >> 4;
						for (s16 r = 0; r < fh && r < 12; r++)
						{
							u32 bits = ((u32)g[0] << 24) | ((u32)g[1] << 16);
							if (gw > 1) bits |= ((u32)g[2] << 8) | g[3];
							g += gw * 2;
							u8 *d = work + r * 80 + (x >> 3);
							s16 sh = x & 7;
							d[0] |= (u8)(bits >> (24 + sh));
							d[1] |= (u8)(bits >> (16 + sh));
							d[2] |= (u8)(bits >> (8 + sh));
							d[3] |= (u8)(bits >> sh);
							if (sh) d[4] |= (u8)(bits << (8 - sh));
						}
					}
					x += (w ? w : 10) + 1 + each + (k < more ? 1 : 0);
				}
				line = nxt;
				left = 210;
				for (s16 r = 0; r < 12; r++)			// into plane 0 of ring lines top + 196 + r, both copies
				{
					s16 l = top + 196 + r;
					if (l >= IH) l -= IH;
					const u16 *w = (const u16 *)(work + r * 80);
					u16 *d0 = (u16 *)(ring + (s32)l * 160), *d1 = d0 + IH * 80;
					for (s16 k = 0; k < 40; k++) { d0[2 * k] = w[k]; d1[2 * k] = w[k]; }
				}
			}
			lines++;
		}
		// one step: the line leaving the top is cleared (it comes back at the bottom), the picture starts a line lower
		qmemclr(ring + (s32)top * 160, 160);
		qmemclr(ring + (s32)(top + IH) * 160, 160);
		if (++top == IH) top = 0;
		iter++;											// (the VBL shows this step when its turn has come)
		while ((s16)(s_intro_step - iter) < 0) { }
		left--;
		if (++c == 210) c = 0;
		if (left < 0) { fade = 16; s_intro_go = false; next = *vbclock; }
	}
	s_intro_go = false;

	if (slot >= 0) vq[slot] = 0;
	mfp[0x1a] = 0;
	mfp[6] = old_iera; mfp[0x12] = old_imra;
	*vec = old_vec;
	qmemclr(scr, 32000);
	*(volatile u8 *)0xffff8201L = (u8)((u32)scr >> 16);
	*(volatile u8 *)0xffff8203L = (u8)((u32)scr >> 8);
	*(volatile u8 *)0xffff820dL = (u8)(u32)scr;
	Vsync();
	efree(ring);
	efree(work);
	efree(dat);
}

static u16 s_tos_pal[16];						// the palette showing on the TOS screen
COLD static void tos_fade(const u16 *_target)	// fade_to 17084 (0: fade_out): 16 steps, 2 VBLs each
{
	static u16 step[16];
	u16 from[16], to[16];
	bool same = true;
	for (s16 c = 0; c < 16; c++) { from[c] = s_tos_pal[c]; to[c] = _target ? _target[c] : 0; same &= from[c] == to[c]; }
	if (same) return;
	for (s16 s = 1; s <= 15; s++)
	{
		for (s16 c = 0; c < 16; c++) step[c] = ste_mix(from[c], to[c], s);
		Setpalette(step);
		Vsync(); Vsync();
	}
	for (s16 c = 0; c < 16; c++) s_tos_pal[c] = to[c];
}
// a picture onto the (black) screen; its palette into _pal for the fade-in
COLD static bool pic_show(const char *_name, u16 *_pal)
{
	u32 info = 0;
	u8 *p = load_asset(_name, AssetFlags(af_load_unwrapped | af_asset_scratch), &info);
	if (!p) return false;
	tos_fade(0);
	for (s16 c = 0; c < 16; c++) _pal[c] = ((const u16 *)p)[c];
	qmemcpy((void *)Physbase(), p + 32, 32000);
	efree(p);
	return true;
}
// up to _frames VBLs; fire (or a key) ends this and all following pictures (FUN_18022: any wait jumps to the end)
COLD static bool pic_wait(s16 _frames)
{
	for (; _frames > 0 && !g_pics_skip; _frames--)
	{
		Vsync();
		if (Bconstat(2)) { Bconin(2); g_pics_skip = true; }
		if (intro_fire()) g_pics_skip = true;
	}
	return !g_pics_skip;
}
#endif

// Pooled sprites (effects, soldiers, guns, enemy planes, panel digits: 126 of the 190 entities) are not ticked by AGT.
// Most of them are idle, and a tick call per entity per frame cost about half a VBL. Each pool's update function is
// called for the entities in use, and for those in use the frame before, so they hide themselves.
enum { POOL_FX, POOL_SOLDIER, POOL_GUN, POOL_ZERO, POOL_PANEL, POOL_N };
struct pool_t { entity_t *pe[NFX]; s16 n, prev; void (*fn)(entity_t *); };
static pool_t g_pool[POOL_N];
static void pool_add(s16 _p, entity_t *_pe, void (*_fn)(entity_t *))
{
	pool_t &p = g_pool[_p];
	p.fn = _fn;
	if (_pe && p.n < NFX) p.pe[p.n++] = _pe;	// (a null entity: AGT's pool of 192 is exhausted, see the check after the spawns)
}
static void pool_tick(s16 _p, s16 _active)
{
	pool_t &p = g_pool[_p];
	if (_active > p.n) _active = p.n;
	s16 lim = _active > p.prev ? _active : p.prev;
	for (s16 i = 0; i < lim; i++) p.fn(p.pe[i]);
	p.prev = _active;
}

// day or night palettes into g_pal / g_panel_pal (the main loop sets the hardware palette when g_pal_dirty)
static bool g_map_request_night(s16 _letter) { return _letter > 'g' && (rnd16() & 1); }	// mission index > 6: a random bit
COLD static void pal_select(tileset &_tiles, tileset &_ptiles)
{
	for (s16 c = 0; c < 16; ++c)
	{
		g_pal[c] = g_night ? c_night_pal[c] : _tiles.getcol(c);
		g_panel_pal[c] = g_night ? c_night_dash[c] : _ptiles.getcol(c);
	}
	g_pal_dirty = true;
}

static s16 g_tos_rez = 0;

// GEM's mouse pointer (started from the desktop: the busy bee) is drawn by TOS's VBL whenever the mouse moves:
// it is hidden while the start-up screens are up (line-A hide / show, so the count stays balanced for the desktop).
extern "C" { void wof_mouse_hide(); void wof_mouse_show(); }
// resolution and palette when the program was started (AGT's start-up switches to medium resolution and blanks
// colours 1..3 before AGT_EntryPoint: Getrez() and the palette registers show that, not the desktop's)
extern "C" { extern short g_agt_start_rez; extern unsigned short g_agt_start_pal[16]; }
__asm__(
	"	.text\n"
	"	.even\n"
	"	.globl	_wof_mouse_hide\n"
	"	.globl	_wof_mouse_show\n"
	"_wof_mouse_hide:\n"
	"	movem.l	%d2/%a2,-(%sp)\n"
	"	.short	0xa000\n"						// line-A init (the calls below use its variables)
	"	.short	0xa00a\n"						// hide mouse
	"	movem.l	(%sp)+,%d2/%a2\n"
	"	rts\n"
	"_wof_mouse_show:\n"
	"	movem.l	%d2/%a2,-(%sp)\n"
	"	.short	0xa000\n"						// a0 = line-A variables: +4 CONTRL, +8 INTIN
	"	lea	wof_la_contrl,%a1\n"
	"	move.l	%a1,4(%a0)\n"
	"	clr.w	2(%a1)\n"
	"	move.w	#1,6(%a1)\n"
	"	lea	wof_la_intin,%a1\n"
	"	move.l	%a1,8(%a0)\n"
	"	move.w	#1,(%a1)\n"					// INTIN[0] != 0: one level (0 would force it visible)
	"	.short	0xa009\n"						// show mouse
	"	movem.l	(%sp)+,%d2/%a2\n"
	"	rts\n"
	"	.bss\n"
	"	.even\n"
	"wof_la_contrl:	.space	24\n"
	"wof_la_intin:	.space	8\n"
	"	.text\n");

// Back to the resolution and palette we were started with. AGT's start-up and ours switch to medium and low
// resolution, and the engine's own restore puts back what it saw at AGT_EntryPoint: medium, colours 1..3 black
// (a low resolution desktop came back squeezed into half the screen in wrong colours). The register is written
// too: Setscreen does not when TOS thinks it is in that resolution already.
COLD static void tos_screen_back()
{
	Setscreen(-1L, -1L, g_tos_rez);
	Vsync();
	*(volatile u8 *)0xffff8260L = (u8)g_tos_rez;
	if (bSTE)
	{
		*(volatile u8 *)0xffff820fL = 0;
		*(volatile u8 *)0xffff8265L = 0;
	}
	Setpalette(g_agt_start_pal);
}

int AGT_EntryPoint()
{
	g_tracked_allocation_ += (int)(&end);

	g_tos_rez = g_agt_start_rez;
	wof_mouse_hide();

	{
		machinestate.configure();
		// STE / Mega STE only (_MCH 1.x): the engine needs the blitter, STE hardware scrolling and the STE video
		// timing. A TT has no blitter (bus error), a Falcon's Videl shows no picture with AGT's display code.
		if (!bSTE)
		{
			Cconws("This game needs an Atari STE or Mega STE.\r\n");
			Cconws(bFalcon030 ? "(Falcon030 found: not supported yet)\r\n" : bTT030 ? "(TT030 found: no blitter)\r\n" : "(ST found)\r\n");
			Cconws("Press space...\r\n");
			Crawcin();
			tos_screen_back();
			wof_mouse_show();
			return -1;
		}
		machinestate.save();

		shifter_ste shift;
		shift.configure();
		shift.save();

#if defined(WOF_DIAG)
		dbg_s("start, free="); dbg_h((u32)Malloc(-1)); dbg_s("\n");
		dbg_s("entry at="); dbg_h((u32)&AGT_EntryPoint); dbg_s("\n");	// (maps crash PCs: see _AGT_EntryPoint in build_play/wof.map)
#endif
#if !defined(WOF_REPLAY)
		{	// black screen with the disk icon while the first files load (messages: white on black)
			static const u16 c_pal[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xfff };
			Setscreen(-1L, -1L, 0);
			Setpalette((void *)c_pal);
			Cconws("\033E\033f");
			Vsync();
			intro_icon(true);
		}
#endif
		dirs_init();
		{
			// Enough memory? Without the check a machine with too little sat on the black loading screen for ever
			// (2 MB with much of it taken by resident programs) or fell over after the title picture (1 MB).
			// Needed, as the largest free block at this point (measured in Hatari, TOS 1.62, by taking memory away
			// until the start failed): files as they are 1185 KB fails / 1190 KB works; packed files (floppy)
			// 1262 KB fails / 1272 KB works, plus the largest level bundle over the first one's. A plain 2 MB STE
			// has 1547 KB (TOS 1.62) or 1538 KB (TOS 2.06) here; a 1 MB one 499 KB.
			s32 need = file_exists("PACK.INF") ? 1288000L : 1192000L;
			s32 have = (s32)Malloc(-1L);
			if (have < need)
			{
				char m[48], *p = m;
				for (const char *t = "Free: "; *t; ) *p++ = *t++;
				s32 kb[2] = { have / 1024, need / 1024 };
				for (s16 k = 0; k < 2; k++)
				{
					for (s32 d = 1000; d; d /= 10) if (kb[k] >= d || d == 1) *p++ = (char)('0' + kb[k] / d % 10);
					for (const char *t = k ? " KB\r\n" : " KB, needed: "; *t; ) *p++ = *t++;
				}
				*p = 0;
#if !defined(WOF_REPLAY)
				intro_icon(false);
#endif
				Cconws("\033E\r\n Wings of Fury STE\r\n\r\n Not enough free memory.\r\n ");
				Cconws(m);
				Cconws("\r\n The game needs an STE or Mega STE\r\n with 2 MB. Programs that stay in\r\n memory (accessories, AUTO folder)\r\n take some of it.\r\n\r\n Press space...\r\n");
				Crawcin();
				machinestate.restore();
				tos_screen_back();
				wof_mouse_show();
				return -1;
			}
		}
		bundle_load("start.bin");
		scratch_init();
		scratch_begin();
		mus_load();
		loader_init();
#if defined(WOF_SOUND)
		snd_init();
#endif
#if !defined(WOF_REPLAY)
		intro_joy(true);
		mus_play(2);						// FUN_18022: song3 with the scroller, song2 from the publisher's logo on
		intro_scroller();
		mus_play(1);
		Setscreen(-1L, -1L, 0);				// ST low resolution
		// (and the display hardware itself, in the vertical blank: on real machines started from a floppy or the
		// hard disk the pictures came up in stripes: half of each line, black columns between. Not reproduced in
		// Hatari. Setting every register the scroller or a resolution change can leave behind cured it, confirmed
		// on the STE; which one was off is not known)
		Vsync();
		*(volatile u8 *)0xffff8260L = 0;	// low resolution
		*(volatile u8 *)0xffff820fL = 0;	// STE: no extra words per line
		*(volatile u8 *)0xffff8265L = 0;	// STE: no pixel scroll
		{
			u32 b = (u32)Physbase();
			*(volatile u8 *)0xffff8201L = (u8)(b >> 16);
			*(volatile u8 *)0xffff8203L = (u8)(b >> 8);
			*(volatile u8 *)0xffff820dL = (u8)b;
		}
		Vsync();
		u16 ppal[16];
		u32 title_t0;
		for (s16 c = 0; c < 16; c++) s_tos_pal[c] = 0;
		Setpalette(s_tos_pal);
		Vsync();
		if (pic_show("broder.pic", ppal))	// the logo first (PAL_A 0x2589c: the greys of 'presents' stay black), then all of it
		{
			u16 logo[16];
			for (s16 c = 0; c < 16; c++)
			{
				u16 v = ppal[c];
				logo[c] = ((v & 15) == ((v >> 4) & 15) && (v & 15) == ((v >> 8) & 15)) ? 0 : v;
			}
			tos_fade(logo);
			if (pic_wait(60)) { tos_fade(ppal); pic_wait(120); }
		}
		// the title: 300 frames, during which the game loads (also when the pictures are skipped)
		if (pic_show("title.pic", ppal)) tos_fade(ppal);
		title_t0 = *(volatile u32 *)0x462L;
		intro_icon(true);
#endif
		if (!level_zone_init())
		{
#if !defined(WOF_REPLAY)
			intro_joy(false);
#endif
			Cconws("level files missing. press space...\r\n");
			Crawcin();
			tos_screen_back();
			wof_mouse_show();
			return -1;
		}
#if defined(WOF_DIAG)
		dbg_s("level zone="); dbg_h(g_level_zone_size); dbg_s("\n");
#endif
		hellcat_asset.load("hellcat.spr");
		EntityDefAsset_Sprite(EntityType_HELLCAT, &hellcat_asset);
		wheels_asset.load("wheels.spr");
		EntityDefAsset_Sprite(EntityType_WHEELS, &wheels_asset);
		torp_asset.load("torp.spr");
		elev_asset.load("elev.spr");
		gmov_asset.load("gmov.spr");
		EntityDefAsset_Sprite(EntityType_TORP, &torp_asset);
		fx_asset.load("fx.spr");
		EntityDefAsset_Sprite(EntityType_FX, &fx_asset);
		EntityDefAsset_Sprite(EntityType_FLASH, &hellcat_asset);	// flash frames are in the Hellcat sheet (IMSPR, layer 1)
		crew_asset.load("crew.spr");
		EntityDefAsset_Sprite(EntityType_CREW, &crew_asset);
		weapon_asset.load("weapons.spr");
		EntityDefAsset_Sprite(EntityType_WEAPON, &weapon_asset);
		gun_asset.load("guns.spr");
		EntityDefAsset_Sprite(EntityType_GUN, &gun_asset);
		soldier_asset.load("soldiers.spr");
		EntityDefAsset_Sprite(EntityType_SOLDIER, &soldier_asset);
		flag_asset.load("flags.spr");
		EntityDefAsset_Sprite(EntityType_FLAG, &flag_asset);
		hud_asset.load("hud.spr");
		EntityDefAsset_Sprite(EntityType_HUD, &hud_asset);
		paneltiles.load_cct("panel.cct");
		panelmap.load_ccm("panel.ccm");
		panel_asset.load("panelspr.spr");			// IMSPR (EMX: 165 KB); the panel pass ends with the EMX tail (sepbar 10)
		EntityDefAsset_Sprite(EntityType_PANEL, &panel_asset);
		zero_asset.load("zeros.spr");
		EntityDefAsset_Sprite(EntityType_ZERO, &zero_asset);
		zmini_asset.load("zmini.spr");
		mini_asset.load("mini.spr");
		EntityDefAsset_Sprite(EntityType_MINI, &mini_asset);
		sepbar_asset.load("sepbar.emx");
		font_asset.load("font.spr");
		tfont_asset.load("tfont.spr");
		EntityDefAsset_Sprite(EntityType_SEPBAR, &sepbar_asset);
		// level last: its blocks then border the free memory, so a bigger map can replace it later
		// start map: first letter of MAP.TXT if present (testing), else the first map built in
		s16 letter = MAP_LETTERS[0];
		{
			s16 fh = (s16)Fopen("map.txt", 0);
			if (fh >= 0)
			{
				char c = 0;
				if (Fread(fh, 1, &c) == 1 && c >= 'a' && c <= 'o') letter = c;
				Fclose(fh);
			}
		}
		if (!map_load(letter) && !map_load(MAP_LETTERS[0]))
		{
#if !defined(WOF_REPLAY)
			intro_joy(false);
#endif
			Cconws("map data missing. press space...\r\n");
			Crawcin();
			tos_screen_back();
			wof_mouse_show();
			return -1;
		}
		level_load(g_map_letter);
#if !defined(WOF_REPLAY)
		intro_icon(false);
		{
			s32 left = 300 - (s32)(*(volatile u32 *)0x462L - title_t0);
			if (left > 0) pic_wait((s16)left);
		}
		if (!g_pics_skip && pic_show("credits.pic", ppal)) { tos_fade(ppal); pic_wait(600); }
		tos_fade(0);
		mus_stop();							// (the original fades it at the rank selection; here the engine starts first)
		qmemclr((void *)Physbase(), 32000);	// (black while the engine takes over)
		intro_joy(false);
#endif

		arena_t myworld(shift, SCREEN_XSIZE, PF_H);			// Nickel port 0
		panel_arena_t panelworld(shift, SCREEN_XSIZE, PANEL_YSIZE);	// Nickel port 1 (cockpit panel)
		myworld.bind_displayport(0);
		panelworld.bind_displayport(1);
		g_world = &myworld;
		myworld.setmap(&mymap);
		for (int b = myworld.c_num_buffers_-1; b >= 0; b--)
		{
			myworld.select_buffer(b);
			myworld.settiles(&mytiles, &mytiles);
		}
		panelworld.setmap(&panelmap);
		for (int b = panelworld.c_num_buffers_-1; b >= 0; b--)
		{
			panelworld.select_buffer(b);
			panelworld.settiles(&paneltiles, &paneltiles);
		}

		respawn();
		select_frame();

		s32 prev_x = P.x, prev_y = P.y;

		// camera at the start position
		g_cam_x = (s16)(P.x + MARGIN - 160);
		g_cam_y = CAM_Y_REST;
		myworld.init(g_cam_x, g_cam_y);
		panelworld.init(0, 0);

		machinestate.claim();
		AGT_InstallInputService();

		// split screen: playfield (port 0) for PF_H lines, cockpit panel (port 1) below
		// the VBL only loads the port 0 palette: the panel palette is a colour burst just before the split
		pal_select(mytiles, paneltiles);
		// Nickel events need >= 5 lines spacing (timing pad 2). The panel palette is burst SEP_H lines before the split:
		// those playfield rows show palette index 0 at rest = black with the panel palette (a separator like the Amiga's).
		// The first port has no event: the VBL sets it, and the list ends with NE_End, which only halts the timer
		// (NE_Stop waits for display lines that would not come after line 200).
		static nickel_op_t nickel_commands[] =
		{
			{ NE_PortSelect,	0,						NickelPort0	},
			{ NE_ColourBurst,	PF_H-SEP_H,				0, 16, g_panel_pal },
			{ NE_PortSelect,	PF_H,					NickelPort1	},
			{ NE_End,			SCREEN_YSIZE			}
		};
#if defined(WOF_PLAIN)
		// diagnostic build (make plain -> WOFPLAIN.PRG): AGT's standard 200-line mode, no Nickel (no screen split, no
		// palette burst). Shows the playfield only; the panel is drawn but never displayed.
		shift.set_fieldmode(false);
		shift.init(STLow200);
#else
		{
			u16 keep[16];								// (front end: the panel's colour burst starts black too)
			for (s16 c = 0; c < 16; ++c) { keep[c] = g_panel_pal[c]; if (g_frontend) g_panel_pal[c] = 0; }
			shift.load_nickel(nickel_commands);
			for (s16 c = 0; c < 16; ++c) g_panel_pal[c] = keep[c];
		}
		shift.set_fieldmode(false);
		shift.init(Nickel);
#endif
		g_mus_engine = true;
		for (s16 c = 0; c < 16; ++c)
		{
			u16 col = g_frontend ? 0 : g_pal[c], pcol = g_frontend ? 0 : g_panel_pal[c];	// (front end: black until its first page shows)
			shift.setcolour(0, 0, c, col, 0);
			shift.setcolour(1, 0, c, col, 0);
			shift.setcolour(0, 0, c, pcol, 1);
			shift.setcolour(1, 0, c, pcol, 1);
		}

		EntitySetup(EntityType_MAX_);
		myworld.bgrestore_reset();
		myworld.reset(g_cam_x, g_cam_y);
		panelworld.bgrestore_reset();
		panelworld.reset(PANEL_MAP_X0, 0);

		s_pe_panelview = EntitySpawn(EntityType_VIEWPORT, PANEL_MAP_X0 - c_viewport_xmargin, 0 - c_viewport_ymargin);
		s_pe_viewport = EntitySpawn(EntityType_VIEWPORT, g_cam_x - c_viewport_xmargin, g_cam_y - c_viewport_ymargin);
		EntitySelectViewport(s_pe_viewport);
		s_pe_torp = EntitySpawn(EntityType_TORP, g_cam_x + 160 - PL_AX, g_cam_y);		// (before the plane: drawn under it)
		s_pe_player = EntitySpawn(EntityType_HELLCAT, g_cam_x + 160 - PL_AX, g_cam_y);
		s_pe_wheels = EntitySpawn(EntityType_WHEELS, g_cam_x + 160 - WH_AX, g_cam_y);
		for (s16 k = 0; k < NFX; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_FX, g_cam_x, g_cam_y);
			pe->counter = k;
			pool_add(POOL_FX, pe, &fx_fntick);
		}
		EntitySpawn(EntityType_FLASH, g_cam_x, g_cam_y);
		EntitySpawn(EntityType_MINI, g_cam_x, g_cam_y);
		for (s16 k = 0; k <= SCREEN_XSIZE / 32; k++)		// 10 bars + the panel pass tail (counter 10)
		{
			entity_t *pe = EntitySpawn(EntityType_SEPBAR, g_cam_x, g_cam_y + PF_H - SEP_H);
			pe->counter = k;
		}
		for (s16 k = 0; k < 2; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_CREW, g_cam_x, g_cam_y);
			pe->counter = k;
		}
		for (s16 k = 0; k < NPROJ + 2; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_WEAPON, g_cam_x, g_cam_y);
			pe->counter = k;
		}
		for (s16 k = 0; k < NGUN_ENT; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_GUN, g_cam_x, g_cam_y);
			pe->counter = k;
			pool_add(POOL_GUN, pe, &gun_fntick);
		}
		for (s16 k = 0; k < NSOLD_ENT; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_SOLDIER, g_cam_x, g_cam_y);
			pe->counter = k;
			pool_add(POOL_SOLDIER, pe, &soldier_fntick);
		}
		for (s16 k = 0; k < MAX_FLAGS; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_FLAG, g_cam_x, g_cam_y);
			pe->counter = k;
		}
		for (s16 k = 0; k < NHUD; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_HUD, g_cam_x, g_cam_y);
			pe->counter = k;
		}
		for (s16 k = 0; k < NZDRAW; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_ZERO, g_cam_x, g_cam_y);
			pe->counter = k;
			pool_add(POOL_ZERO, pe, &zero_fntick);
		}
		for (s16 k = 0; k < NPANEL; k++)
		{
			entity_t *pe = EntitySpawn(EntityType_PANEL, 0, 0);
			pe->counter = k;
			pool_add(POOL_PANEL, pe, &panel_fntick);
		}
		EntityExecuteAllLinks();
#if defined(WOF_DIAG)
		if (g_pool[POOL_PANEL].n < NPANEL || g_pool[POOL_ZERO].n < NZDRAW) dbg_s("ERROR: entity pool exhausted (AGT c_max_entities)\n");
#endif

		s16 buffer_index = 0;
		s16 tick_vbl = vbl_now();
		bundle_free();
		scratch_end();
		hi_load();
		if (g_frontend) page_request(PG_RANK);
#if defined(WOF_DIAG)
		dbg_s("init done, free="); dbg_h((u32)Malloc(-1)); dbg_s("\n");
#endif

#if defined(WOF_REPLAY)
		replay_load();
#endif
#if defined(WOF_DIAG)
		{	// calibrate: idle loop iterations in one full VBL
			s16 f = g_vbl; while (g_vbl == f) { }
			f = g_vbl; u32 n = 0; while (g_vbl == f) n++;
			g_idle_per_vbl = n;
			dbg_s("idle loops per VBL="); dbg_h(n); dbg_s("\n");
		}
#endif
#if defined(WOF_DIAG)
		{	// the dictionary must list the entity types in enum order (a mismatch crashed the draw in the 1/8 view)
			static const struct { s16 t; fnptr_t f; } c_chk[] = {
				{ EntityType_HELLCAT, &hellcat_fntick }, { EntityType_WHEELS, &wheels_fntick }, { EntityType_TORP, &torp_fntick }, { EntityType_FX, &fx_fntick },
				{ EntityType_FLASH, &flash_fntick }, { EntityType_CREW, &crew_fntick }, { EntityType_FLAG, &flag_fntick },
				{ EntityType_HUD, &hud_fntick }, { EntityType_SOLDIER, &soldier_fntick }, { EntityType_GUN, &gun_fntick }, { EntityType_WEAPON, &weapon_fntick },
				{ EntityType_PANEL, &panel_fntick }, { EntityType_MINI, &mini_fntick }, { EntityType_SEPBAR, &sepbar_fntick }, { EntityType_ZERO, &zero_fntick } };
			for (u16 i = 0; i < sizeof(c_chk) / sizeof(c_chk[0]); i++)
				if (entity_dictionary[c_chk[i].t].fntick != c_chk[i].f) { dbg_s("ERROR: entity_dictionary order, type "); dbg_h(c_chk[i].t); dbg_s("\n"); }
		}
#endif
		garrison_init();
		pillboxes_init();
		ships_init();
		carrier_init();
		zeros_init();
#if defined(WOF_SOUND)
		if (!g_snd_ok) snd_init();
#endif
		// Esc pauses and Ctrl+R goes back to the rank selection, as in the original (which has no quit key: Ctrl+Q here)
		while (!(key_states[ScanCode_CTRL] && key_states[ScanCode_Q]) && !g_quit)
		{
			// frame pacing: at least g_frame_vbls VBLs per drawn frame (1 = as fast as possible, ~25 fps here;
			// 3 = the Amiga's steady 16.7 fps with headroom for sound / more objects)
			static s16 s_frame_vbl = 0;		// 16-bit like vbl_now(): differences survive the counter wrap (10.9 min)
			{
				u32 n = 0;
				s16 field_index = g_vbl;
				while (g_vbl == field_index) n++;
				while ((s16)(vbl_now() - s_frame_vbl) < g_frame_vbls) n++;
				s_frame_vbl = vbl_now();
#if defined(WOF_DIAG)
				g_idle += n;				// idle loop count (CPU headroom)
#endif
			}

			poll_fire();

			if (g_session_over && !g_page && !g_loading && !g_map_request)	// game over: name entry if in the best ten, then the table
			{
				g_session_over = false;
				hi_sort();
				if (g_score > g_hi[9].score) { g_name_len = 0; g_name[0] = 0; page_open(PG_NAME); }
				else page_request(PG_SCORES);
			}
			// Ctrl+R (0x1027c): back to the rank selection without the high scores; also from the briefing
			if (key_states[ScanCode_CTRL] && debounced_key_releases[ScanCode_R])
			{
				debounced_key_releases[ScanCode_R] = 0;
				if (g_frontend && g_page != PG_RANK && !g_loading && !g_map_request && !g_pic_closing)
				{
					g_session_over = false;
					g_msg_len = 0;
					page_request(PG_RANK);
				}
			}
			// The original's other Ctrl keys (frontend.md 7): Ctrl+F swaps stick up / down, Ctrl+C deletes the high score
			// file, Ctrl+V shows the version in the message line, Ctrl+S switches the sound off / on (off: the sounds
			// stop, and the menu music does not start).
			if (key_states[ScanCode_CTRL])
			{
				if (debounced_key_releases[ScanCode_S])
				{
					debounced_key_releases[ScanCode_S] = 0;
					g_snd_off = !g_snd_off;
					if (g_snd_off) { g_mus_state = 0; for (s16 c = 0; c < SND_VOICES; c++) snd_stop(c); }
				}
				if (debounced_key_releases[ScanCode_F]) { debounced_key_releases[ScanCode_F] = 0; g_stick_swap = !g_stick_swap; }
				if (debounced_key_releases[ScanCode_C])
				{
					debounced_key_releases[ScanCode_C] = 0;
					if (!g_page && !g_loading && !g_map_request && !g_pic) hi_clear();
				}
				if (debounced_key_releases[ScanCode_V])
				{
					debounced_key_releases[ScanCode_V] = 0;
					if (msg_begin()) { msg_cat("Version "); msg_cat(WOF_VERSION); }
				}
			}
			// Cheat keys (FUN_1ccf6): type c o l i n, then the keys below work. Not with Ctrl held.
			if (!g_page && !g_loading && !g_map_request && !g_help && !g_pause && !g_pic && !key_states[ScanCode_CTRL])
			{
				static const u8 c_word[5] = { ScanCode_C, ScanCode_O, ScanCode_L, ScanCode_I, ScanCode_N };
				if (g_cheat < 5)
				{
					for (s16 k = 0; k < 5; k++)
						if (debounced_key_releases[c_word[k]])
							g_cheat = (c_word[k] == c_word[g_cheat]) ? g_cheat + 1 : (c_word[k] == ScanCode_C ? 1 : 0);
				}
				else
				{
#define CK(_sc_) (debounced_key_releases[_sc_] != 0)
					if (CK(ScanCode_M)) g_ammo = g_ammo < 0 ? c_ammo_tab[g_weapon] : -1;	// unlimited ordnance on / off
					if (CK(ScanCode_C)) { if (++g_weapon > 2) g_weapon = 0; }				// next weapon
					if (CK(ScanCode_R)) for (s16 i = 0; i < NPROJ; i++) g_proj[i].state = 0;	// clear projectiles
					if (CK(ScanCode_F)) P.fuel = 128;
					if (CK(ScanCode_D)) { P.oil = 128; P.state = 0; g_invuln = !g_invuln; }
					if (CK(ScanCode_P)) g_lives++;
					if (CK(0x09) || CK(0x68)) g_gravity += 0x1000;							// 8 / 2: gravity +- 0x1000
					if (CK(0x03) || CK(0x6e)) g_gravity -= 0x1000;
					if (CK(0x07) || CK(0x6c)) g_gravity += 0x100;							// 6 / 4: +- 0x100
					if (CK(0x05) || CK(0x6a)) g_gravity -= 0x100;
					if (CK(ScanCode_I)) g_pitch_rate += 50;
					if (CK(ScanCode_K)) g_pitch_rate -= 50;
					if (CK(ScanCode_Q)) g_quit = true;										// quits the program
					if (CK(0x44)) g_msg_len = 0;											// F10: clear the message line
					if (CK(0x62) && msg_begin())											// Help: the island under the plane
					{
						s16 n = NISLANDS, i = 0;
						while (i < n - 1 && (s32)c_island_end[i] * 8 < P.x) i++;
						msg_cat("Island has "); msg_num(n ? g_isl_soldiers[i] : 0);
						msg_cat(" soldiers and "); msg_num(n ? g_isl_pills[i] : 0); msg_cat(" pillboxes.");
					}
#undef CK
					static const u8 c_used[] = { ScanCode_M, ScanCode_C, ScanCode_R, ScanCode_F, ScanCode_D, ScanCode_P, 0x09, 0x68, 0x03, 0x6e,
						0x07, 0x6c, 0x05, 0x6a, ScanCode_I, ScanCode_K, ScanCode_Q, 0x44, 0x62 };
					for (u16 k = 0; k < sizeof(c_used); k++) debounced_key_releases[c_used[k]] = 0;
				}
				for (s16 k = 0; k < 5; k++) debounced_key_releases[c_word[k]] = 0;
			}
			// Ctrl+G: save (only with the plane on the deck, player state 1), Ctrl+L: load (frontend.md 2.1)
			if (key_states[ScanCode_CTRL] && (debounced_key_releases[ScanCode_G] || debounced_key_releases[ScanCode_L]))
			{
				bool save = debounced_key_releases[ScanCode_G] != 0;
				debounced_key_releases[ScanCode_G] = debounced_key_releases[ScanCode_L] = 0;
				if (!g_page && !g_loading && !g_map_request && !g_pic && !g_session_over && (!save || P.state == PS_DECK))
				{
					g_dlg_rank = false;
					page_request(save ? PG_SAVE : PG_LOAD);
				}
			}
			if (g_page)
			{
#if defined(WOF_REPLAY)
				u8 pin = 0;
				if (!g_rp_snap && !g_rp_end) replay_input(pin);		// (script lines count frames while a page is up)
				page_tick((pin & IN_UP) != 0, (pin & IN_DOWN) != 0, (pin & (IN_TAP | IN_HOLD)) != 0);
#else
				page_tick((joy1 & 1) || key_states[ScanCode_UP], (joy1 & 2) || key_states[ScanCode_DOWN],
					(joy1 & 0x80) || (g_page != PG_NAME && !g_dlg_edit && key_states[ScanCode_SPACE]));
#endif
			}
			// a picture page opened: the screen is black until the picture is in both buffers, then its palette is
			// set for both screen parts
			if (g_cover) g_cover--;
			if (g_pic_closing && --g_pic_closing == 0) { pic_close(); g_page = PG_NONE; }
			if (g_pic_pending && (!g_pic || (g_pic_dirty == 0 && g_pic_hold == 0)))
			{
				g_pic_pending = false;
				if (g_pic)
				{
					for (s16 c = 0; c < 16; c++) g_pal[c] = g_panel_pal[c] = ((const u16 *)g_pic)[c];
					g_pal_dirty = true;
				}
			}
			if (g_pic_restore && !g_pic)						// the picture pages are over: playfield, panel and palettes again
			{
				g_pic_restore = false;
				g_cam_jump = true;
				panelworld.bgrestore_reset();
				panelworld.reset(PANEL_MAP_X0, 0);
				g_panel_dirty = 2;
				g_fpv_redraw = true;
				pal_select(mytiles, paneltiles);
				g_cover = 4;								// (black while the playfield and the panel are rebuilt)
			}
			bool restart = false;						// (only the test rig's RESTART: the R key is gone)
#if defined(WOF_REPLAY)
			if (g_rp_restart) { restart = true; g_rp_restart = false; }
#endif
			// a map switch takes seconds on real hardware: first show the loading page (dimmed, sprites hidden, sound
			// silent) in both buffers, then load
			if (g_map_request && !g_loading) { g_loading = 5; g_help = false; g_pause = false; g_page_next = 0; load_screen(); }
			if (g_loading > 1) { if (!g_pic_pending) g_loading--; }	// (counts once the loading screen shows)
			else if (g_loading == 1 && !g_map_request)
			{
				s16 p = g_page_next;
				g_page_next = 0;
				g_loading = 0;
				if (p) page_open(p);
			}
			else if (g_loading == 1)
			{
				s16 l = g_map_request;
				g_map_request = 0;
				g_loading = 0;
				if (g_night_roll) { g_night_roll = false; g_night = g_map_request_night(l); }	// FUN_111fc
				if (!mission_switch(myworld, l)) mission_switch(myworld, MAP_LETTERS[0]);
				bool loaded = false;
				if (g_load_slot >= 0)							// a saved game: its state over the fresh map
				{
					loaded = g_map_letter == l && save_restore(g_load_slot);
					g_load_slot = -1;
					if (loaded) { g_cam_jump = true; g_fpv_stale = true; g_fpv_redraw = true; g_panel_dirty = 2; g_wave_drawn = -1; }
					else { mission_switch(myworld, g_map_letter); g_score = 0; g_lives = 3; g_zero_kills = 0; }	// (bad file: the mission from its start)
				}
				pal_select(mytiles, paneltiles);
				select_frame();
				prev_x = P.x; prev_y = P.y;
				g_map_fresh = !loaded;
				if (g_frontend) page_open(PG_BRIEF);			// FUN_18590: before every mission
				else page_close();								// (the loading screen)
			}
			if (restart)
			{
				g_pause = false;				// (restarting while paused left the plane hanging above the deck)
				respawn();
				select_frame();
				prev_x = P.x; prev_y = P.y;		// no interpolation across the jump
			}

			// H: pause with the help page (not the Atari's Help key: emulators have no obvious key for it)
			if (debounced_key_releases[ScanCode_H])
			{
				debounced_key_releases[ScanCode_H] = 0;
				if (g_help) g_help = false; else if (!g_page && !g_loading) g_help = true;
			}
			// Esc: pause page (title + build id). Like the help page it dims the playfield and hides the sprites
			if (debounced_key_releases[ScanCode_ESC])
			{
				debounced_key_releases[ScanCode_ESC] = 0;
				if (g_help) g_help = false; else if (!g_page && !g_loading) g_pause = !g_pause;	// (not under a menu page)
			}
			{
				// the playfield palette is dimmed to half while the page shows; the font's white stays bright.
				// After a crash the playfield is black for 20 VBLs before the new plane appears (FUN_135ce).
				static s16 s_dimmed = 0, s_blank_end = 0;			// 0 normal, 1 dimmed, 2 black
				if (g_blank) { g_blank = false; s_blank_end = vbl_now() + 20; s_dimmed = -1; }
				bool black = s_dimmed != 0 && s_dimmed != 1 && (s16)(vbl_now() - s_blank_end) < 0;
				static bool s_cover = false;					// a transition: playfield and panel black
				bool cover = g_cover > 0 || g_pic_pending;
				bool edge = cover != s_cover;					// the cover goes on / off: fade out / in
				if (edge) { s_cover = cover; g_pal_dirty = true; }
				if (cover) black = true;
				s16 want = black ? 2 : g_pic ? 0 : (g_help || g_help_peek || g_pause || g_loading || g_page) ? 1 : 0;
				if (want != s_dimmed || g_pal_dirty)
				{
					g_pal_dirty = false;
					s_dimmed = want;
					s16 white = 1, best = -1;
					for (s16 c = 1; c < 16; ++c)
					{
						s16 v = ste_lum(g_pal[c]);
						if (v > best) { best = v; white = c; }
					}
					// The playfield palette is loaded by the VBL: it is set right after one, so a VBL never sees half of
					// it. The panel's colours are a burst that AGT compiles into its display list as 8 x
					// 'move.l #c0c1,(a0)+': the colour words are set in place (local AGT patch g_nickel_last_burst), one
					// VBL later, so both parts of the screen change in the same frame. (Recompiling the list with
					// load_nickel cost a frame with a broken split.)
					// A change of screen fades (fade_to / fade_out 17084, 173b0: 16 steps, cur + (target - cur) * s / 15):
					// to black when the cover goes on, from black when it comes off. Everything else is set at once.
					u16 end[32];
					for (s16 c = 0; c < 16; ++c)
					{
						u16 col = g_pal[c];
						if (want == 2) col = 0;
						else if (want && c != white) col = ste_half(col);
						end[c] = col;
						end[16 + c] = cover ? 0 : g_panel_pal[c];
					}
					s16 s0 = 15, s1 = 15, ds = 1;
					const u16 *base = end;
					static bool s_shown_loader = false;
					bool loader = g_pic && g_pic_loader;
					if (edge && cover) { base = g_shown; s0 = 14; s1 = 0; ds = -1; if (s_shown_loader) s0 = 0; }
					else if (edge && !loader) s0 = 1;
					if (!cover) s_shown_loader = loader;
					if (edge)
					{
						bool any = false;
						for (s16 c = 0; c < 32; ++c) any |= base[c] != 0;
						if (!any) s0 = s1;						// (black to black)
#if defined(WOF_SOUND)
						if (!g_mus_hooked) for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = 0;	// (the game's sounds are not mixed meanwhile)
#endif
					}
					for (s16 st = s0; ; st += ds)
					{
						{ s16 f = g_vbl; while (g_vbl == f) { } }
						for (s16 c = 0; c < 16; ++c)
						{
							u16 col = ste_mix(0, base[c], st), pcol = ste_mix(0, base[16 + c], st);
							shift.setcolour(0, 0, c, col, 0);
							shift.setcolour(1, 0, c, col, 0);
							shift.setcolour(0, 0, c, pcol, 1);
							shift.setcolour(1, 0, c, pcol, 1);
						}
#if !defined(WOF_PLAIN)
						{ s16 f = g_vbl; while (g_vbl == f) { } }
						if (g_nickel_last_burst)
						{
							for (s16 c = 0; c < 16; ++c) g_nickel_last_burst[(c >> 1) * 3 + 1 + (c & 1)] = ste_mix(0, base[16 + c], st);
							// Under a picture page the whole screen has one palette, and the burst would rewrite the
							// colour registers in the middle of a picture line (line 155: in the game that is the black
							// separator): on the real machines that can show as stray pixels. The eight
							// 'move.l #c0c1,(a0)+' become 'cmpi.l #c0c1,(a0)+': same length and time, no write.
							u16 op = g_pic ? 0x0c98 : 0x20fc;
							for (s16 k = 0; k < 8; ++k) g_nickel_last_burst[k * 3] = op;
						}
#endif
						if (st == s1) break;
					}
					for (s16 c = 0; c < 32; ++c) g_shown[c] = (edge && cover) ? 0 : end[c];
				}
			}

			// fixed 12.5 Hz logic: one tick per 4 VBLs (catch up if a frame took longer)
			s16 behind = (s16)(vbl_now() - tick_vbl);
			if (behind > 16 || behind < 0) { tick_vbl = vbl_now() - 4; behind = 4; }
			if (g_help || g_pause || g_loading || g_page || g_cover || g_pic_closing || g_pic) { tick_vbl = vbl_now(); behind = 0; }	// paused (also under the black of a transition)
			while (behind >= 4)
			{
				prev_x = P.x;
				prev_y = P.y;
				g_deck_bob_prev = g_deck_bob_logic;
				g_deck_elev_prev = g_deck_elev_logic;
				s16 old_state = P.state;
				u8 in = read_input();
#if defined(WOF_REPLAY)
				if (g_rp_snap || g_rp_end || g_rp_restart || !replay_input(in)) break;
#endif
				logic_tick(in);
				sound_tick();
				if (P.state == PS_DECK && old_state != PS_DECK && old_state != PS_FLYING && old_state != PS_ARRESTED)
				{
					prev_x = P.x; prev_y = P.y;		// respawn: no interpolation across the jump
				}
				tick_vbl += 4;
				behind -= 4;
			}

			if (g_wrap_dx) { prev_x += g_wrap_dx; g_wrap_dx = 0; if (!g_zoom) g_cam_jump = true; }	// the plane wrapped to the other map end

#if defined(WOF_SOUND)
			{
				bool sp = g_help || g_pause || g_loading || g_page;		// no sound while paused or loading
				if (sp && !g_snd_paused && !g_mus_hooked) for (s16 i = 0; i < SND_RING; i++) g_snd_ring[i] = 0;	// whole ring silent at once
				g_snd_paused = sp;
			}
			{ static s16 s_mix_vbl = 0; s16 v = vbl_now(); if (!g_mus_hooked) snd_mix((s16)(v - s_mix_vbl)); s_mix_vbl = v; }	// (menu music mixes in the VBL)
#endif

			// effects advance per drawn frame on the Amiga (~16.7 fps): once per 3 VBLs here, whatever our frame time
			// is (counting loop passes made them run at a third of the speed once a frame took 3 VBLs)
			{
				static s16 s_fx_vbl = 0, s_fx_acc = 0;
				{ s16 v = vbl_now(); s16 dv = (s16)(v - s_fx_vbl); s_fx_vbl = v; if (dv < 0 || dv > 12) dv = 3; s_fx_acc += dv; }
				while (s_fx_acc >= 3)
				{
					s_fx_acc -= 3;
					if (!g_help && !g_pause && !g_loading && !g_page)			// (frozen while paused)
					{
						fx_frame_tick();
						if (g_phase == 2)
						{
							if (--g_elev <= 0)				// elevator up: normal play, engine start (1b9cc)
							{
								g_elev = 0; g_phase = 0;
								for (s16 c = 0; c < SND_VOICES; c++) snd_stop(c);		// FUN_11460: stop all, metal clang
								snd_play(3, SND_CLANG, 64, 1);
								g_eng_vol = g_eng_vol_target = 0x28; g_eng_per = g_eng_per_base = 0x328;
							}
						}
						else if (g_phase == 3)
						{
							if (++g_elev >= 0x20)			// elevator down: stop all, metal clang, re-arm, menu
							{
								for (s16 c = 0; c < SND_VOICES; c++) snd_stop(c);
								snd_play(3, SND_CLANG, 64, 1);
								rearm();
								if (g_mission_done) { g_map_request = mission_next_letter(); g_night_roll = true; }	// landed after mission complete: next map
							}
						}
						// sky flash (FUN_10228, 1031a): the flash colour shows while the count is odd BEFORE it is
						// counted down (5 = on, off, on, off, on); the sky's own colour is back on the frame after
						// the last (checked against the Amiga 2026-10-08: a deck crash gives three white frames)
						{
							static bool s_flash_shown = false;
							if (g_sky_flash)
							{
								u16 col = (g_sky_flash & 1) ? g_sky_flash_col : g_pal[1];
								g_sky_flash--;
								shift.setcolour(0, 0, 1, col, 0);
								shift.setcolour(1, 0, 1, col, 0);
								s_flash_shown = true;
							}
							else if (s_flash_shown)
							{
								s_flash_shown = false;
								shift.setcolour(0, 0, 1, g_pal[1], 0);
								shift.setcolour(1, 0, 1, g_pal[1], 0);
							}
						}
					}
				}
			}
			fx_build(behind);

			// carrier bob tiles, before the sprites are placed: the deck rows (bottom of the block) move in the first
			// step, so the plane / crew use the new bob at once; the tower flag follows when its rows (top) are done
			if (g_bob_row >= BOB_ROWS && g_wave_bob != g_bob_drawn && g_carrier.hits > 0)	// (a sinking carrier does not bob)
			{
				g_bob_drawn = g_wave_bob;		// start a new spread-out block update
				g_bob_row = 0;
			}
			bob_apply_step();
			if (g_bob_row >= BOB_ROWS) g_bob_flag = g_bob_drawn;

			// interpolate between the last two ticks (0..3/4 of the way)
			s32 ix = prev_x + (((P.x - prev_x) * behind) >> 2);
			s32 iy = prev_y + (((s32)(P.y - prev_y) * behind) >> 2);
			g_plane_ix = (s16)(ix + MARGIN);
			if (P.state == PS_DECK || P.state == PS_ARRESTED)
			{
				// on deck y = 0x21 - bob: interpolate the bob-free height, then apply the bob of the tiles as drawn
				// (interpolating y itself undid the bob for up to a tick after every second bob step)
				s32 a = prev_y + g_deck_bob_prev + g_deck_elev_prev, b = P.y + g_deck_bob_logic + g_deck_elev_logic;
				iy = a + (((b - a) * behind) >> 2) - g_bob_drawn - g_elev;
			}
			g_plane_iy = (s16)(WATER_ROW - iy);

			g_zoom = P.y > 0xba;		// end of every player tick on the Amiga: zoom = (y > 186) ? 1 : 8

			// camera: plane at screen x = 160 (original: cam = x - 160, never clamped; we have 1024 px of sea per side)
			s16 cx = g_plane_ix - 160;
			if (cx < 16) cx = 16;
			if (cx > LEVEL_W - SCREEN_XSIZE - 16) cx = LEVEL_W - SCREEN_XSIZE - 16;
			s16 cy = CAM_Y_REST;				// never lower than the Amiga view (rows below hold wrecked-hut tiles)
			if (g_plane_iy - cy < 40) cy = g_plane_iy - 40;
			if (cy < 0) cy = 0;
			if (g_zoom)
			{
				s32 cp = MINI_X0 + (g_plane_ix >> 3) - 160;			// camera in the treadmill's coordinates
				s32 ct = cp + g_out / 8;							// and where it truly is
				s32 cmax = MINI_X0 + (LEVEL_W >> 3) - 128;			// (the map's right end at the screen's left edge)
				if (ct < 16) ct = 16;								// (the map's left end is at x = MINI_X0 + 128 = 16 + 320)
				if (ct > cmax) ct = cmax;
				g_mini_dx = (s16)(ct - cp);
				cx = (s16)ct;
				cy = MINI_ROW;
			}
			g_cam_x = g_pic ? (cx & ~15) : cx;		// (a picture page is copied to the screen at a 16-px position)
			g_cam_y = cy;

			hud_build();
			panel_build();

			g_pe_viewport->rx = g_cam_x - c_viewport_xmargin;
			g_pe_viewport->ry = g_cam_y - c_viewport_ymargin;

			vis_build();
			zeros_draw_build();
			pool_tick(POOL_FX, g_fx_count);			// (before EntityTickAll: its spatial pass sorts what moved)
			pool_tick(POOL_SOLDIER, g_sold_nvis);
			pool_tick(POOL_GUN, g_gun_nvis);
			pool_tick(POOL_ZERO, g_nzd);
			pool_tick(POOL_PANEL, g_panel_count);
			EntityTickAll();
			EntityExecuteAllLinks();
			EntityExecuteAllRemoves();

			// (day / night: decided per mission from map h on; the test rig's NIGHT command toggles it)
#if defined(WOF_REPLAY)
			if (g_rp_night) { g_rp_night = false; g_night = !g_night; pal_select(mytiles, paneltiles); }
#endif
			if (!g_zoom && (g_wave_n != g_wave_drawn || g_cam_jump))	// (a jump refills from the map: strip first)
			{
				waves_apply();
				g_wave_drawn = g_wave_n;
			}

			// A new plane after a crash: the playfield goes black now, before the frame with the carrier is shown
			// (the palette block above sees g_blank only in the next frame: the new scene flashed up for one frame
			// before the 20 black VBLs).
			if (g_blank)
			{
				{ s16 f = g_vbl; while (g_vbl == f) { } }
				for (s16 c = 0; c < 16; ++c) { shift.setcolour(0, 0, c, 0, 0); shift.setcolour(1, 0, c, 0, 0); g_shown[c] = 0; }
			}
			// any camera move too big for the scroller's edge refill (respawn, R) needs a full rebuild
			{
				static s16 s_last_cx = 0, s_last_cy = 0;
				s16 dx = g_cam_x - s_last_cx, dy = g_cam_y - s_last_cy;
				if (dx > 32 || dx < -32 || dy > 32 || dy < -32) g_cam_jump = true;
				s_last_cx = g_cam_x; s_last_cy = g_cam_y;
			}
			if (g_cam_jump && !g_pic)					// (under a picture page it waits: the rebuild would draw over it)
			{
				// a camera jump (respawn) leaves stale tiles in both buffers: rebuild them (as AGT's examples do)
				g_cam_jump = false;
				g_tk_addr = 0; g_tk_save_at[0] = g_tk_save_at[1] = 0;	// (both buffers are rebuilt)
				myworld.bgrestore_reset();
				myworld.reset(g_cam_x, g_cam_y);
			}

			static bool s_pic_up = false;
			static s16 s_pic_cx = 0, s_pic_cy = 0;
			static u16 *s_tk_next = 0;
			static s16 s_tk_fine = 0, s_tk_pitch = 0;
			if (g_pic) { g_tk_addr = 0; s_tk_next = 0; g_tk_save_at[0] = g_tk_save_at[1] = 0; }	// (a picture goes over the buffers)
			if (!g_pic) s_pic_up = false;
			if (g_pic)
			{
				// a picture page: no world, no sprites. The picture goes into both screen buffers when it changed
				// (rows 0..PF_H-1 into the playfield, the rest into the panel)
				// (no hybrid_fill: after a map switch it would draw the new level's tiles into the buffers, and they
				// showed for a frame in the loading screen's colours. Leaving the page rebuilds both playfields.)
				// The camera is frozen while pictures are up: a new mission moves it, and the display window would
				// slide off the copied picture.
				if (!s_pic_up) { s_pic_up = true; s_pic_cx = g_cam_x & -16; s_pic_cy = g_cam_y; }	// (& -16: the picture is copied to whole words)
				myworld.select_buffer(buffer_index & 1);
				myworld.setpos(s_pic_cx, s_pic_cy);
				myworld.get_context(drawcontext, 0, VIEWPORT_XSIZE, VIEWPORT_YSIZE);
				bool copy = g_pic_dirty && !g_pic_hold && !g_pic_closing;
				if (g_pic_hold) g_pic_hold--;
				if (copy) pic_copy(drawcontext, s_pic_cx, s_pic_cy, 0, PF_H);
				panelworld.select_buffer(buffer_index & 1);
				panelworld.setpos(PANEL_MAP_X0, 0);
				panelworld.get_context(panelcontext, 0, VIEWPORT_XSIZE, PANEL_YSIZE);
				if (copy) { pic_copy(panelcontext, PANEL_MAP_X0, 0, PF_H, SCREEN_YSIZE - PF_H); g_pic_dirty--; }
				myworld.activate_buffer();
				panelworld.activate_buffer();
				buffer_index++;
			}
			else
			{
			// view 0: playfield
			EntitySelectViewport(s_pe_viewport);
			{
			myworld.select_buffer(buffer_index & 1);
			tk_restore(buffer_index & 1);				// (the message line's text of two frames ago)
			myworld.setpos(g_cam_x, g_cam_y);
			myworld.bgrestore();
			myworld.hybrid_fill(false);
			myworld.get_context(drawcontext, 0, VIEWPORT_XSIZE, VIEWPORT_YSIZE);
			if (!g_zoom && !g_help && !g_help_peek && !g_pause && !g_loading && !g_page)
			{
				// drawn directly, before the entity pass (an IMSPR draw must not be the last one before the EMX panel
				// pass), in the original's order: elevator, torpedo, gear, plane.
				// Scissor bottom: sinking -> just below the wave crests (the Amiga draws the wave strip over the plane);
				// elevator moving or down (phase != 0) -> the deck edge, 14 lines under the deck surface (clip_to_deck
				// 1526e: 162 - 0x21 + bob + 3 with the waterline at 151)
				bool zinit = false;
				for (s16 k = 0; k < g_nzd; k++)		// enemy planes leaving the screen on the left (see zdraw_t)
				{
					if (!g_zd[k].direct) continue;
					if (!zinit) { AGT_BLiT_IMSprInit(); zinit = true; }
					AGT_BLiT_IMSprDrawClipped(&drawcontext, zero_asset.get(), g_zd[k].frame, g_zd[k].x, g_zd[k].y);
				}
				drawcontext_t c = drawcontext;
				bool clip = plane_clipped();
				s16 y2 = c.scissor_window_y1 + ((P.state == PS_SINKING ? WATER_ROW + 2 : WATER_ROW + g_bob_drawn - 19) - g_cam_y);
				if (clip && y2 < c.scissor_window_y2) { c.scissor_window_y2 = y2; c.scissor_window_ys = y2 - c.scissor_window_y1; }
				bool room = !clip || y2 > c.scissor_window_y1;
				s16 ex = (s16)(HOME_X + MARGIN) - EL_AX;
				s16 esink = carrier_sink_px();				// (the platform goes down with the sinking carrier, cut off at the water)
				bool elev = g_phase != 1 && g_carrier.alive && esink < 0x21 && ex > g_cam_x - 80 && ex < g_cam_x + SCREEN_XSIZE + 16;	// 'elev' (FUN_1409c): not in phase 1
				if (room && (elev || clip))
				{
					AGT_BLiT_IMSprInit();
					if (elev)
					{
						drawcontext_t ce = c;
						s16 yw = drawcontext.scissor_window_y1 + (WATER_ROW + 2 - g_cam_y);
						if (esink && yw < ce.scissor_window_y2) { ce.scissor_window_y2 = yw; ce.scissor_window_ys = yw - ce.scissor_window_y1; }
						if (ce.scissor_window_y2 > ce.scissor_window_y1)
							AGT_BLiT_IMSprDrawClipped(&ce, elev_asset.get(), 0, ex, WATER_ROW - (0x21 - g_bob_drawn - g_elev) + esink - EL_AY);
					}
					if (clip)
					{
						u8 tf = (g_weapon == 2 && g_ammo != 0 && P.frame >= 0 && P.frame < PLANE_FRAMES) ? c_fr_torp[P.frame] : 255;
						if (tf != 255) AGT_BLiT_IMSprDrawClipped(&c, torp_asset.get(), tf, g_plane_ix - TP_AX, g_plane_iy - PL_AY);
						if (P.wheel_frame >= 0)
							AGT_BLiT_IMSprDrawClipped(&c, wheels_asset.get(), P.wheel_frame, g_plane_ix - WH_AX, g_plane_iy - WH_AY);
						AGT_BLiT_IMSprDrawClipped(&c, hellcat_asset.get(), P.frame, g_plane_ix - PL_AX, g_plane_iy - PL_AY);
					}
				}
			}
			// 'gmov' at screen (160,81) (FUN_110c2): while the last plane is a wreck (FUN_1af7c: lives <= 1 in the
			// crash states) or the carrier took the plane down
			if (((g_lives <= 1 && (P.state == PS_CRASH || P.state == PS_SINKING || P.state == PS_WRECK)) || g_gameover_timer)
				&& !g_help && !g_help_peek && !g_pause && !g_loading && !g_page)
			{
				AGT_BLiT_IMSprInit();
				AGT_BLiT_IMSprDrawClipped(&drawcontext, gmov_asset.get(), 0, g_cam_x + 160 - 100, g_cam_y + 81 - 12);
			}
			if (g_help || g_help_peek) help_draw(drawcontext);
			else if (g_page && !g_pic) page_draw(drawcontext);
			else if (g_loading)			// shown for a few frames before the (slow, from a cartridge or disk) map load
			{
				AGT_BLiT_IMSprInit();		
				help_text(drawcontext, 11, 6, "LOADING ...");
			}
			else if (g_pause)			// (before the entity pass: it must end with an EMX sprite)
			{
				AGT_BLiT_IMSprInit();
				help_text(drawcontext, 9, 4, "WINGS OF FURY STE - PAUSED");
				help_text(drawcontext, (s16)((44 - (s16)sizeof(WOF_BUILD) + 1) / 2), 6, WOF_BUILD);
				help_text(drawcontext, 11, 9, "ESC: BACK TO THE GAME");	// (the shortcuts are on the help page)
				help_text(drawcontext, 8, 11, "H: CONTROLS AND SHORTCUTS");
				{	// free memory (largest block), to watch the 2 MB headroom on real machines
					static char m[] = "FREE 0000 KB OF 0000";	// (of the machine's RAM: phystop)
					u32 kb = (u32)Malloc(-1) >> 10;
					for (s16 i = 8; i >= 5; i--) { m[i] = (char)('0' + kb % 10); kb /= 10; }
					kb = *(u32 *)0x42eL >> 10;
					for (s16 i = 19; i >= 16; i--) { m[i] = (char)('0' + kb % 10); kb /= 10; }
					help_text(drawcontext, 12, 13, m);
				}
			}
			EntityDrawVisible(&drawcontext);
			if (g_bal_count && !g_help && !g_help_peek && !g_pause && !g_loading && !g_page)
			{
				// the ceremony's balloons over everything (FUN_1557c draws them last). IMSPR must not be the last thing
				// drawn in a pass (AGT draw crash): the separator bar's 16x1 black line (EMX) follows
				AGT_BLiT_IMSprInit();
				for (s16 i = 0; i < g_bal_count; i++)
					AGT_BLiT_IMSprDrawClipped(&drawcontext, fx_asset.get(), g_bal[i].frame, g_bal[i].x - FX_AX, g_bal[i].y - FX_AY);
				AGT_BLiT_EMXSprInit();
				AGT_BLiT_EMXSprDrawClipped(&drawcontext, sepbar_asset.get(), 1, g_cam_x + 152, g_cam_y + PF_H - SEP_H + 7);
			}
			{	// message line: the VBL writes it into the separator strip of the buffer on display (tk_vbl); here its
				// place in the buffer being drawn is worked out, and handed over when the buffer goes on display
				s_tk_next = 0;
				if (g_msg_len && !g_help && !g_help_peek && !g_pause && !g_loading && !g_page && !g_pic)
				{
					if (g_tk_len != g_msg_len) { g_tk_addr = 0; tk_render(); }
					if (g_tk_pos >= TK_W + g_tk_w) g_msg_len = 0;
					else
					{
						s_tk_next = (u16 *)((u8 *)drawcontext.p_pfframebuffer + ((g_cam_x & -16) >> 1)
							+ (s32)(g_cam_y + PF_H - SEP_H - drawcontext.pfsnapadjy) * g_linebytes);
						s_tk_fine = g_cam_x & 15;
						s_tk_pitch = g_linebytes;
					}
				}
			}

			// view 1: cockpit panel (static map, sprites for the counters). Its sprites rarely change, and restoring
			// and drawing them costs about half a VBL: done only for the two frames (both buffers) after a change
			static u16 s_panel_sig = 0xffff;
			static s16 s_panel_age = 0;
			{
				u16 sig = (u16)(g_panel_count * 131 + g_zero_kills);
				for (s16 i = 0; i < g_panel_count; i++)
					sig = (u16)(((sig << 3) | (sig >> 13)) ^ (g_panel[i].frame << 7) ^ (g_panel[i].x * 3) ^ (g_panel[i].y << 11));
				if (sig != s_panel_sig || ++s_panel_age >= 128) { s_panel_sig = sig; s_panel_age = 0; g_panel_dirty = 2; }
			}
			EntitySelectViewport(s_pe_panelview);
			panelworld.select_buffer(buffer_index & 1);
			panelworld.setpos(PANEL_MAP_X0, 0);
			if (g_panel_dirty) panelworld.bgrestore();
			panelworld.hybrid_fill(false);
			panelworld.get_context(panelcontext, 0, VIEWPORT_XSIZE, PANEL_YSIZE);
			fpv_draw(panelcontext);
			if (g_panel_dirty)
			{
			g_panel_dirty--;
			{	// kill tally (hud_draw_kill_tally 1f200): one small Zero per kill, two rows of 7 at hires (534,19) /
				// (534,25), 13 hires px apart. Drawn directly (AGT's entity pool of 192 is nearly used up)
				s16 kills = g_zero_kills > 99 ? 99 : g_zero_kills;
				if (kills > 0)
				{
					AGT_BLiT_IMSprInit();
					for (s16 i = 0; i < 7 && i < kills; i++)
						AGT_BLiT_IMSprDrawClipped(&panelcontext, panel_asset.get(), 47, PANEL_MAP_X0 + 265 + (i * 13) / 2, 17);
					for (s16 i = 0; i < 7 && i < kills - 7; i++)
						AGT_BLiT_IMSprDrawClipped(&panelcontext, panel_asset.get(), 47, PANEL_MAP_X0 + 265 + (i * 13) / 2, 23);
				}
			}
			EntityDrawVisible(&panelcontext);
			}
			EntitySelectViewport(s_pe_viewport);

			g_tk_addr = 0;								// (ticker: not while its values change)
			g_tk_fine = s_tk_fine; g_tk_pitch = s_tk_pitch; g_tk_slot = buffer_index & 1;
			g_tk_addr = s_tk_next;
			if (!g_mus_hooked) *(void (* volatile *)())0xa0L = s_tk_next ? tk_vbl : 0;	// AGT's VBServiceVec
			myworld.activate_buffer();
			panelworld.activate_buffer();
			buffer_index++;
			}
			}

#if defined(WOF_REPLAY)
			if (g_rp_snap)
			{
				// let the new frame reach the screen, then hold it until the host has taken the screenshot
				for (s16 w = 0; w < 3; w++) { s16 f = g_vbl; while (g_vbl == f) { } }
				dbg_s("SNAP "); dbg_s(s_rp_name); dbg_s("\n");
				s16 t0 = vbl_now();
				while (!key_states[ScanCode_SPACE] && (s16)(vbl_now() - t0) < 500) { }
				t0 = vbl_now();
				while (key_states[ScanCode_SPACE] && (s16)(vbl_now() - t0) < 50) { }
				dbg_s("SNAP done\n");
				g_rp_snap = false;
				tick_vbl = vbl_now() - 4;
			}
			if (g_rp_end)
			{
				dbg_s("REPLAY END\n");
				break;
			}
#endif

#if defined(WOF_DIAG)
			static s16 s_last_state = -1;
			if ((buffer_index & 3) == 1 || buffer_index < 8 || P.state != s_last_state)
			{
				s_last_state = P.state;
				dbg_s("st="); dbg_h(P.state); dbg_s(" x="); dbg_h(P.x); dbg_s(" y="); dbg_h(P.y);
				dbg_s(" spd="); dbg_h(P.airspeed); dbg_s(" pitch="); dbg_h((u16)P.pitch); dbg_s(" turn="); dbg_h(P.turn);
				dbg_s(" fr="); dbg_h(P.frame); dbg_s(" cam="); dbg_h(g_cam_x); dbg_h(g_cam_y); dbg_s(" fx="); dbg_h(g_fx_count); dbg_s(" gun="); dbg_h(g_gun_firing);
				{ s16 ns = 0; for (s16 i = 0; i < NSMOKE; i++) if (g_smoke[i].n) ns++; dbg_s(" smk="); dbg_h(ns); }
				{ s16 n1 = 0, n2 = 0; for (s16 i = 0; i < NSOLD; i++) { if (g_sold[i].state == 1) n1++; if (g_sold[i].state == 3) n2++; } dbg_s(" sol="); dbg_h(n1); dbg_s(" dead="); dbg_h(n2); }
				for (s16 i = 0; i < NZERO; i++)
					if (g_zero[i].state) { dbg_s(" z"); dbg_h(g_zero[i].state); dbg_s("/"); dbg_h(g_zero[i].mode); dbg_s("/"); dbg_h(g_zero[i].x); dbg_s("/"); dbg_h(g_zero[i].alt); }
				{ static s32 s_dv = 0; s32 v = vbl_now(); dbg_s(" vbl="); dbg_h((u32)(v - s_dv)); s_dv = v; }	// VBLs since the previous line (4 frames)
				dbg_s(" fpv="); dbg_h(((u32)g_fpv_stat[0] << 24) | ((u32)g_fpv_stat[1] << 16) | ((u32)g_fpv_stat[2] << 8) | g_fpv_stat[3]); g_fpv_stat[0] = g_fpv_stat[1] = g_fpv_stat[2] = g_fpv_stat[3] = 0;
				dbg_s(" idle%="); dbg_h(g_idle_per_vbl ? (u32)(g_idle * 100 / g_idle_per_vbl) : 0); g_idle = 0;	// idle VBL-% over the 4 frames
				dbg_s(" lag="); dbg_h(behind); dbg_s(" ammo="); dbg_h(g_ammo); dbg_s(" score="); dbg_h(g_score); dbg_s("\n");
			}
#endif
		}

		g_mus_state = 0; mus_hook(false);
		snd_close();
		AGT_RemoveInputService();
		shift.restore();
	}

	machinestate.restore();
	dirs_exit();
	tos_screen_back();
	Cconws("\033E");
	wof_mouse_show();
	return 0;
}

// =====================================================================================================================

// the panel palette is loaded SEP_H lines above the panel (Nickel events need >= 8 lines spacing), so the
// playfield's last SEP_H lines would show sky/water in panel colours when the camera climbs: cover them
void sepbar_fntick(entity_t *_pself)
{
	entity_t &self = *_pself;
	if (self.counter == 10)
	{
		// panel pass tail: a 16x1 black line on the black frame above the centre screen (panel map x 150, line 4).
		// The panel's IMSPR sprites must not be the last thing drawn in a pass (AGT draw crash).
		self.rx = PANEL_MAP_X0 + 150 - 16;
		self.ry = 4;
		self.frame = 1;
		return;
	}
	self.rx = g_cam_x + self.counter * 32;
	self.ry = g_cam_y + PF_H - SEP_H;
	self.frame = 0;			// solid index 11 = black in the panel palette (RFILL crashed on the real STE)
}

entitydef_t entity_dictionary[EntityType_MAX_] =
{
	// tick,collide,asset,hasset				px/y,vx/y,sx/y,ox/y				tickpri,drflag	h,d,frame,counter	drawtype,drawlayer		f_self,f_interactswith
	{ 0,0,0,0,									{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,0,		EntityFlag_VIEWPORT|EntityFlag_SPATIAL,	0 },
	{ &hellcat_fntick,0,0,0,					{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_IMSPR,EntityLayer_1,	EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &wheels_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &torp_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &fx_fntick,0,0,0,							{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_SPATIAL,	0 },
	{ &flash_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	// (crew: IMSPR in layer 1 with the other IMSPR sprites; as the only sprite of layer 0 it crashed AGT's draw pass)
	{ &crew_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &flag_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &hud_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &soldier_fntick,0,0,0,					{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_SPATIAL,	0 },
	{ &gun_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_SPATIAL,	0 },
	{ &weapon_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &panel_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_SPATIAL,	0 },
	{ &mini_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &sepbar_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_EMXSPR,EntityLayer_3,		EntityFlag_TICKED|EntityFlag_SPATIAL,	0 },
	{ &zero_fntick,0,0,0,						{0},{0},{0},{0},0,0,0,0,		0,0,			0,0,0,0,			EntityDraw_NONE,EntityLayer_1,		EntityFlag_SPATIAL,	0 },
};
