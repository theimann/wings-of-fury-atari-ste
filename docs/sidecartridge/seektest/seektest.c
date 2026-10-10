/* GEMDOS seek test for SidecarTridge md-devops GEMDRIVE.
 * Mirrors AGT's raw-asset load: Fopen, Fread 24, Fseek(0,END), Fseek(0,CUR), Fseek(0,SET), Fread 16.
 * Output goes to the md-devops debug channel (read of $FBFF00+c emits c) and to the screen.
 */
#include <osbind.h>
#include <stdio.h>

static void dbg_c(char c) { (void)*(volatile unsigned char*)(0xFBFF00ul + (unsigned char)c); }
static void out(const char *s) { const char *p = s; while (*p) dbg_c(*p++); printf("%s", s); }

static void hex(const unsigned char *b, int n)
{
	char t[4];
	for (int i = 0; i < n; i++) { sprintf(t, "%02x ", b[i]); out(t); }
	out("\n");
}

int main(void)
{
	char line[96];
	unsigned char buf[32];
	long h = Fopen("LEVEL.CCT", 0);
	sprintf(line, "\n=== seektest ===\nFopen -> %ld\n", h); out(line);
	if (h < 0) return 1;
	long r = Fread((short)h, 24, buf);
	sprintf(line, "Fread 24 -> %ld : ", r); out(line); hex(buf, 8);
	long e = Fseek(0, (short)h, 2);
	sprintf(line, "Fseek(0,END) -> %ld\n", e); out(line);
	long c = Fseek(0, (short)h, 1);
	sprintf(line, "Fseek(0,CUR) -> %ld\n", c); out(line);
	long s = Fseek(0, (short)h, 0);
	sprintf(line, "Fseek(0,SET) -> %ld\n", s); out(line);
	r = Fread((short)h, 16, buf);
	sprintf(line, "Fread 16 -> %ld : ", r); out(line); hex(buf, 16);
	out("expected: 8a 10 b4 40 03 df 08 2b 06 6e 02 b5 05 5d 0f ff\n");
	Fclose((short)h);
	/* second variant: rewind without the SEEK_END step */
	h = Fopen("LEVEL.CCT", 0);
	Fread((short)h, 24, buf);
	s = Fseek(0, (short)h, 0);
	r = Fread((short)h, 16, buf);
	sprintf(line, "[no END] Fseek(0,SET) -> %ld, Fread 16 -> %ld : ", s, r); out(line); hex(buf, 16);
	Fclose((short)h);
	out("=== done ===\n");
	return 0;
}
