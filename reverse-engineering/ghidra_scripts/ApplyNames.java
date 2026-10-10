// Apply function/global names from merged JSON {"functions":{addr:name}, "globals":{addr:name}} (arg0)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.regex.*;

public class ApplyNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        String json = new String(Files.readAllBytes(Paths.get(getScriptArgs()[0])));
        AddressSpace sp = currentProgram.getAddressFactory().getDefaultAddressSpace();
        SymbolTable st = currentProgram.getSymbolTable();
        int nf = 0, ng = 0;
        for (String section : new String[]{"functions", "globals"}) {
            Matcher sm = Pattern.compile("\"" + section + "\"\\s*:\\s*\\{([^}]*)\\}").matcher(json);
            if (!sm.find()) continue;
            Matcher m = Pattern.compile("\"(0x[0-9a-fA-F]+)\"\\s*:\\s*\"([A-Za-z0-9_]+)\"").matcher(sm.group(1));
            while (m.find()) {
                Address a = sp.getAddress(Long.decode(m.group(1)));
                String name = m.group(2);
                if (section.equals("functions")) {
                    Function f = getFunctionAt(a);
                    if (f == null) f = createFunction(a, name);
                    if (f != null) { f.setName(name, SourceType.USER_DEFINED); nf++; }
                } else {
                    st.createLabel(a, name, SourceType.USER_DEFINED).setPrimary(); ng++;
                }
            }
        }
        println("applied " + nf + " function names, " + ng + " global names");
    }
}
