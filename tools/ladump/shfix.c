/* SHFIX1/2/3.PRG: tries to resynchronise the STE shifter's plane counter (the desktop shown with every 16-pixel block's
   planes mixed with the next one's after the game, Mega STE). Each variant at the start of a frame:
   1: one frame in medium resolution, back to low
   2: one frame in high resolution, back to low
   3: the STE fine scroll written as a word at $ffff8264 (no prefetch) and the line offset cleared, twice */
#include <osbind.h>
#ifndef VARIANT
#define VARIANT 1
#endif
static long fix(void)
{
	volatile unsigned char *rez = (volatile unsigned char *)0xffff8260L;
	unsigned char old = *rez;
	short i;
	for (i = 0; i < 2; i++)
	{
		Vsync();
#if VARIANT == 1
		*rez = 1; Vsync(); *rez = old;
#elif VARIANT == 2
		*rez = 2; Vsync(); *rez = old;
#else
		*(volatile unsigned short *)0xffff8264L = 0; *(volatile unsigned char *)0xffff820fL = 0;
#endif
	}
	return 0;
}
int main(void) { Supexec(fix); return 0; }
