# Worker: pool-b

## Model: Opus

## Task: Resource service — large pipeline functions

### Targets
- `FUN_710354a7e0` (2,960B)
- `FUN_710354bb90` (2,960B)
- `FUN_710354d400` (3,456B)
- `FUN_710354e4e0` (3,360B)
- `FUN_71035472b0` (3,872B)
- `FUN_7103548310` (3,680B)

These are the larger pipeline functions. Start with the smallest, use Ghidra MCP to decompile, write clean C++ with resource headers.

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_large_pipeline.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
