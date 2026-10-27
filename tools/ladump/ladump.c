/* LADUMP.PRG: TOS's screen state as the desktop leaves it, into LADUMPn.BIN (n = the first free 1..9) beside the
   program: 0x400 bytes of line-A variables (base - 0x3a0 .. base + 0x60), then the system variables $44a..$462 and the
   video registers $ffff8201/03/05/07/09 (base, counter), $820a (sync), $820d (base low), $820f (line offset),
   $8260 (resolution), $8265 (h-scroll), 2 spare bytes, then $ffff8240..$ffff825f (palette).
   For the WoF exit fault on the Mega STE (the desktop drawn as if in 2 planes after the game): one dump on a clean
   desktop, one after the game; tools/ladump/ladiff.py compares them. */
#include <osbind.h>

static const unsigned short regs[12] = { 0x01, 0x03, 0x05, 0x07, 0x09, 0x0a, 0x0d, 0x0f, 0x60, 0x65, 0x0b, 0x0c };
static unsigned char buf[0x400 + 0x18 + 12 + 0x20];
static unsigned char *la;

static long grab(void)
{
	long i;
	unsigned char *p = buf;
	for (i = 0; i < 0x400; i++) *p++ = la[i - 0x3a0];
	for (i = 0x44a; i < 0x462; i++) *p++ = *(volatile unsigned char *)i;
	for (i = 0; i < 10; i++) *p++ = *(volatile unsigned char *)(0xffff8200L + regs[i]);
	*p++ = 0; *p++ = 0;
	for (i = 0; i < 0x20; i++) *p++ = *(volatile unsigned char *)(0xffff8240L + i);
	return 0;
}

int main(void)
{
	char name[] = "LADUMP1.BIN";
	long h;
	__asm__ volatile(".short 0xa000; move.l %%a0,%0" : "=g"(la) : : "d0", "d1", "d2", "a0", "a1", "a2", "cc");
	Supexec(grab);
	for (name[6] = '1'; name[6] <= '9'; name[6]++) { h = Fopen(name, 0); if (h < 0) break; Fclose((short)h); }
	h = Fcreate(name, 0);
	if (h >= 0) { Fwrite((short)h, sizeof buf, buf); Fclose((short)h); }
	return 0;
}
