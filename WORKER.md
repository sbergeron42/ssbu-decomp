# Worker: pool-a

## Model: Opus

## Task: ResLoadingThread — THE critical path function (12,496 bytes)

This is the function the community has been asking for. `ResLoadingThread` at `0x7103542f30` is the combined loading/inflate processing loop where 6 of 9 ARCropolis hooks land.

### CRITICAL: How to get the Ghidra decompilation
The 13.0.4 Ghidra instance CANNOT decompile this function (wrong boundaries).
The 13.0.1 instance CAN. Use:
```
mcp__ghidra-1301__decompile_function_by_address("0x7103542f30")
```
This returns the full `ResLoadingThread` decompilation with typed structs.

### What it does (from Ghidra 13.0.1)
- Main loop for ResLoadingThread — processes file/directory load requests
- Drains 5 request queues from ResServiceNX
- For file requests: looks up in LoadedArc tables, reads data via nn::fs
- For directory requests: processes child directories recursively
- Uses semaphores for I/O synchronization, double-buffered reads
- All 6 inline ARCropolis hooks are in this function

### Approach
This is a 12,496-byte function — too large to match in one shot. Break it into logical sections:
1. **Outer loop + queue drain** (lines ~1-50 of Ghidra output) — event wait, mutex lock, swap queues
2. **File loading path** (the `*(int *)&pvVar47->eos == 1` branch) — LoadedArc lookup, nn::fs read, double-buffer
3. **Directory loading path** (the `*(int *)&pvVar47->eos == 0` branch) — recursive dir processing
4. **Post-iteration cleanup** — directory state updates, SleepThread, queue cleanup

Write each section as clean C++ using the resource headers, then combine.

### Headers: include/resource/*.h (ResServiceNX, LoadedArc, containers, Fiber)
### Derivation Chains MANDATORY on every offset
### Output: src/resource/ResLoadingThread.cpp
### Do NOT use naked asm. This function is the project's showcase.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
