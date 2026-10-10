// Export per-function facts: size, callees, callers, referenced strings, referenced globals (data hunk)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import java.io.*;
import java.util.*;

public class ExportCallGraph extends GhidraScript {
    @Override
    public void run() throws Exception {
        String out = getScriptArgs()[0];
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        ReferenceManager rm = currentProgram.getReferenceManager();
        try (PrintWriter pw = new PrintWriter(new FileWriter(out))) {
            for (Function f : fm.getFunctions(true)) {
                StringBuilder sb = new StringBuilder();
                sb.append("{\"name\":\"").append(f.getName()).append("\",\"addr\":\"").append(f.getEntryPoint())
                  .append("\",\"size\":").append(f.getBody().getNumAddresses());
                Set<String> callees = new TreeSet<>(), callers = new TreeSet<>(), strs = new TreeSet<>(), globs = new TreeSet<>();
                for (Function c : f.getCalledFunctions(monitor)) callees.add(c.getEntryPoint().toString());
                for (Function c : f.getCallingFunctions(monitor)) callers.add(c.getEntryPoint().toString());
                for (Address a : f.getBody().getAddresses(true)) {
                    for (Reference r : rm.getReferencesFrom(a)) {
                        Address t = r.getToAddress();
                        if (!t.isMemoryAddress()) continue;
                        long v = t.getOffset();
                        if (v >= 0x22f50 && v < 0x28000) {
                            Data d = listing.getDataContaining(t);
                            if (d != null && d.hasStringValue()) strs.add(d.getDefaultValueRepresentation());
                            else globs.add(t.toString() + (r.getReferenceType().isWrite() ? "w" : "r"));
                        }
                    }
                }
                sb.append(",\"callees\":").append(toJson(callees)).append(",\"callers\":").append(toJson(callers))
                  .append(",\"strings\":").append(toJson(strs)).append(",\"globals\":").append(toJson(globs)).append("}");
                pw.println(sb);
            }
        }
    }
    private String toJson(Set<String> s) {
        StringBuilder b = new StringBuilder("[");
        boolean first = true;
        for (String x : s) { if (!first) b.append(','); first = false;
            b.append('"').append(x.replace("\\", "\\\\").replace("\"", "\\\"")).append('"'); }
        return b.append(']').toString();
    }
}
