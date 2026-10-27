/* SCRIPTED.PRG: plays every scripted run in RUNS\ one after another (RUN1.TXT, RUN2.TXT, ...) with RUNS\RUN.PRG
   (the run build, started from this folder: it finds WOF.DAT and RUNS\ here), so a run series needs nobody to type arguments: double-click, watch, read RUNS\RUN<n>.LOG afterwards. Between
   two runs it waits 3 seconds; Esc then ends the series. Back to the desktop after the last run, or when a run could
   not be started. (make wofruns -> disk1/SCRIPTED.PRG; RUNS\RUN.PRG is the run build: make runs, or make atwrun for the one
   with the ATW800/2 debug screen. Folder layout: tools/make_debug.sh, README_DBG.TXT.) */
#include <osbind.h>
#include "version.h"

static void out(const char *s) { Cconws(s); }
static void num(long n) { char b[12], *p = b + 11; *p = 0; do *--p = (char)('0' + n % 10); while (n /= 10); out(p); }

static int exists(const char *name)
{
	long h = Fopen(name, 0);
	if (h < 0) return 0;
	Fclose((short)h);
	return 1;
}

static int esc_within(int vbls)         /* 1 when Esc came within that many VBLs */
{
	while (vbls-- > 0) {
		Vsync();
		while (Cconis()) if ((Crawcin() & 0xff) == 27) return 1;
	}
	return 0;
}

int main(void)
{
	char name[20] = "RUNS\\RUN", cmd[8];
	int n, done = 0;
	out("\033E\033f SCRIPTED " WOF_VERSION "\r\n Wings of Fury: the scripted runs\r\n in RUNS\\, one after another.\r\n\r\n");
	if (!exists("RUNS\\RUN.PRG")) { out(" RUNS\\RUN.PRG is missing.\r\n Press a key..."); Crawcin(); return 1; }
	for (n = 1; n <= 99; n++) {
		char *p = name + 8, *c = cmd + 1;
		long r;
		if (n >= 10) *p++ = *c++ = (char)('0' + n / 10);
		*p++ = *c++ = (char)('0' + n % 10);
		p[0] = '.'; p[1] = 'T'; p[2] = 'X'; p[3] = 'T'; p[4] = 0;
		*c = 0;
		cmd[0] = (char)(c - cmd - 1);
		if (!exists(name)) continue;
		if (done) {
			out(" Run "); num(n); out(" in 3 seconds.\r\n Esc ends the series.\r\n");
			if (esc_within(150)) { out(" Ended.\r\n"); break; }
		}
		out(" Run "); num(n); out(": "); num(((long)Malloc(-1L)) >> 10); out(" KB free, starting...\r\n");
		r = Pexec(0, "RUNS\\RUN.PRG", cmd, 0L);
		out("\033E\033f SCRIPTED " WOF_VERSION "\r\n\r\n Run "); num(n);
		if (r < 0) { out(": RUNS\\RUN.PRG did not\r\n start, error "); num(-r); out(".\r\n Press a key..."); Crawcin(); return 1; }
		out(" done.\r\n Log: RUNS\\RUN"); num(n); out(".LOG\r\n");
		done++;
	}
	out("\r\n "); num(done); out(done == 1 ? " run played.\r\n" : " runs played.\r\n");
	esc_within(150);
	return 0;
}
