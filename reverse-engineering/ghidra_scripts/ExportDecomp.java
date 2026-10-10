// Decompile every function and write C to <arg0>, plus a function list to <arg0>.funcs
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;

public class ExportDecomp extends GhidraScript {
    @Override
    public void run() throws Exception {
        String out = getScriptArgs()[0];
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        try (PrintWriter pw = new PrintWriter(new FileWriter(out));
             PrintWriter fl = new PrintWriter(new FileWriter(out + ".funcs"))) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                fl.printf("%s %s %d%n", f.getEntryPoint(), f.getName(), f.getBody().getNumAddresses());
                DecompileResults r = ifc.decompileFunction(f, 60, monitor);
                pw.printf("// ==== %s @ %s ====%n", f.getName(), f.getEntryPoint());
                if (r.decompileCompleted()) pw.println(r.getDecompiledFunction().getC());
                else pw.println("// decompile failed: " + r.getErrorMessage());
            }
        }
    }
}
