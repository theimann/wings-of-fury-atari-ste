# GEMDRIVE: Fseek() fails with -37 (EIHNDL): handle and offset are read in the wrong order

## Summary
On md-devops v1.1.0, a GEMDOS `Fseek()` on a file opened from the GEMDRIVE folder returns **-37 (EIHNDL, invalid handle)** for `SEEK_SET`, `SEEK_CUR` and `SEEK_END` (seen with offset 0, the common case). The file position is not changed, so the next `Fread()` continues from where the previous read stopped.

Reading the source, the cause looks like a parameter order mismatch between the Atari side and the RP side (details under "Likely cause").

Any program that reads part of a file and then seeks (back to the start, to the end to find the size, or anywhere else) gets wrong data. For example, programs built with AGT (Atari Game Tools) read a header, seek to the end for the size, seek back to 0 and read the whole file. Under GEMDRIVE they load every asset shifted by the header size, which gives garbage graphics or crashes. The same programs work from a hard disk and in Hatari (GEMDOS HD emulation).

## Environment
- SidecarTridge Multi-device v2, Booster v2.4.2, **DevOps toolkit v1.1.0** (installed from the public catalog)
- Atari STE, 2 MB RAM, TOS 2.06
- Reproduced in **Runner mode (U)**. The original symptom (garbled AGT program) also appears in **GEMDRIVE-only mode (G)**.
- GEMDRIVE folder default `/devops`, mounted as `C:`

## Steps to reproduce
1. Put any file of a few KB into the GEMDRIVE folder, e.g. `C:\WOF\LEVEL.CCT`.
2. Build the test program below (m68k-atari-mint-gcc 4.6.4: `m68k-atari-mint-gcc -std=gnu99 -O2 -m68000 -o SEEKTEST.TOS seektest.c`) and copy it next to the file.
3. `sidecart runner cd /WOF`, `sidecart runner run SEEKTEST.TOS`, and watch `sidecart debug tail`. The output also goes to the screen.

The test does: `Fopen`, `Fread` 24 bytes, `Fseek(0,END)`, `Fseek(0,CUR)`, `Fseek(0,SET)`, `Fread` 16 bytes.

## Actual result
```
=== seektest ===
Fopen -> 64
Fread 24 -> 24 : 8a 10 b4 40 03 df 08 2b
Fseek(0,END) -> -37
Fseek(0,CUR) -> -37
Fseek(0,SET) -> -37
Fread 16 -> 16 : 03 3b 0e c3 02 2a 06 7f 02 52 00 35 14 04 02 56
expected: 8a 10 b4 40 03 df 08 2b 06 6e 02 b5 05 5d 0f ff
```
All three `Fseek` calls return -37. The read after the "rewind" returns bytes from offset 24 (where the first read ended), not from offset 0.

## Expected result
- `Fseek(0,END)` returns the file size, `Fseek(0,CUR)` returns the current position, and `Fseek(0,SET)` returns 0.
- The following `Fread` returns the file's first 16 bytes.

## Likely cause
From the v1.1.0 source (commit 1b5788d); I have not rebuilt the firmware to confirm it.

`target/atarist/src/gemdrive.s`, `.Fseek`, loads the registers like this:
```
move.l  8(a0), d4    ; offset
move.w  12(a0), d3   ; handle
move.w  14(a0), d5   ; mode
send_sync CMD_FSEEK_CALL, 12
```
The payload is sent in the order d3, d4, d5 (`inc/sidecart_functions.s`), so it arrives as **handle, offset, mode**.

`rp/src/gemdrive.c`, `handleFseekCall()`, reads it as **offset, handle, mode**:
```c
uint32_t offset = TPROTO_GET_PAYLOAD_PARAM32(payload);
TPROTO_NEXT32_PAYLOAD_PTR(payload);
uint16_t handle = (uint16_t)TPROTO_GET_PAYLOAD_PARAM32(payload);
TPROTO_NEXT32_PAYLOAD_PTR(payload);
uint16_t mode = (uint16_t)TPROTO_GET_PAYLOAD_PARAM32(payload);
```
So the RP side uses the low word of the caller's offset as the handle. With offset 0 that is handle 0, `fileSlotByHandle()` finds nothing, and the call returns -37. (`handleReadBuffCall()` reads the handle first and works.)

If that is right, a seek whose offset happens to equal an open handle number (64 and up) would be accepted and would seek to the handle number instead. Note also that `move.w 12(a0), d3` leaves the upper word of d3 as it was, which matters once d3 is read as a 32-bit value.

Suggested fix: read the handle first in `handleFseekCall()`, then the offset (or swap the registers on the Atari side), and clear d3 before loading the handle.

## Possibly related
After the test program had printed its last line and returned from `main()` (exit through mintlib), the ST showed **bombs, then a garbled screen**. The machine had to be power-cycled. I haven't investigated this further. It may be a separate issue in the Pexec/return path, or a consequence of the failing calls above.

## Workaround
I patched the C runtime of my program so that when `Fseek` fails it emulates the seek: the file size comes from `Fsfirst`, and repositioning reopens the file and skips forward by reading. A fix in GEMDRIVE would be much better, because many existing programs rely on `Fseek`.

## Test program (seektest.c)
```c
/* GEMDOS seek test for SidecarTridge md-devops GEMDRIVE.
 * Mirrors a typical asset loader: Fopen, Fread 24, Fseek(0,END), Fseek(0,CUR), Fseek(0,SET), Fread 16.
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
```
(The "expected" bytes are specific to my test file; use any file and compare with its first 16 bytes.)
