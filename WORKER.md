# Worker: pool-e

## Model: Opus

## Task: ResLoadingThread cleanup + resource service polish

### Goal
Make the resource service decomp presentable for the community. This is what they asked for — clean it up and ship it.

### Tasks
1. **ResLoadingThread.cpp cleanup**: Ensure every code path has a comment explaining what it does. Add section headers. Make it readable even though it doesn't byte-match.
2. **Remove duplicate functions**: Check for any remaining duplicate definitions across res_*.cpp files
3. **Rename FUN_ symbols**: Where comments already have semantic names, rename the actual function symbols (e.g., `FUN_710353d5e0` → `copy_dir_child_paths`)
4. **Verify all resource files compile cleanly**: Single-file compile each res_*.cpp

### Files
- `src/resource/ResLoadingThread.cpp` — main cleanup target
- `src/resource/res_*.cpp` — all resource source files
- `include/resource/*.h` — verify header consistency

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
