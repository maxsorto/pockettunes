import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*; import java.nio.file.*; import java.util.*;
public class Dump extends GhidraScript {
  public void run() throws Exception {
    String[] a = getScriptArgs();
    List<String> lines = Files.readAllLines(Paths.get(a[0]));
    DecompInterface d = new DecompInterface(); d.openProgram(currentProgram);
    Map<String,PrintWriter> outs = new HashMap<>();
    Set<String> seen = new HashSet<>();
    for (String l : lines) {
      String[] p = l.split(" "); String file=p[0], addr=p[1], name=p[2];
      if (!seen.add(addr)) continue;
      Address ad = toAddr(Long.parseLong(addr,16));
      Function f = getFunctionAt(ad);
      if (f == null) { createFunction(ad, name); f = getFunctionAt(ad); }
      if (f == null) continue;
      DecompileResults r = d.decompileFunction(f, 120, monitor);
      String c = r.decompileCompleted() ? r.getDecompiledFunction().getC() : "/* FAILED "+name+" */\n";
      PrintWriter w = outs.computeIfAbsent(file, k -> { try { return new PrintWriter(new FileWriter(a[1]+"/"+k+".decomp.c")); } catch(Exception e){throw new RuntimeException(e);} });
      w.println("// ===== "+name+" @ "+addr+" =====\n"+c);
    }
    for (PrintWriter w : outs.values()) w.close();
  }
}
