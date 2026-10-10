// Pre-analysis setup for Wings of Fury flat image (base 0x10000).
// Sets A4 (small-data base) across the code hunk, creates functions for the
// Aztec-C jump table in the data hunk and for the entry point.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.mem.*;
import java.math.BigInteger;

public class SetupWings extends GhidraScript {
    @Override
    public void run() throws Exception {
        AddressSpace sp = currentProgram.getAddressFactory().getDefaultAddressSpace();
        Address codeStart = sp.getAddress(0x10000), codeEnd = sp.getAddress(0x22f4b);
        Register a4 = currentProgram.getRegister("A4");
        currentProgram.getProgramContext().setValue(a4, codeStart, codeEnd, BigInteger.valueOf(0x2af4eL));

        Memory mem = currentProgram.getMemory();
        // split the flat block so the data hunk is not executable
        MemoryBlock blk = mem.getBlock(codeStart);
        mem.split(blk, sp.getAddress(0x22f50));
        MemoryBlock data = mem.getBlock(sp.getAddress(0x22f50));
        data.setName("DATA"); data.setExecute(false);
        mem.getBlock(codeStart).setName("CODE");

        createFunction(codeStart, "entry");
        for (long a = 0x22f50; a < 0x233a6; a += 6) {
            Address at = sp.getAddress(a);
            disassemble(at);
            long tgt = mem.getInt(at.add(2)) & 0xffffffffL;
            Address t = sp.getAddress(tgt);
            disassemble(t);
            if (getFunctionAt(t) == null) createFunction(t, null);
            createFunction(at, String.format("jt_%04x", (int)(a - 0x2af4eL) & 0xffff));
        }
    }
}
