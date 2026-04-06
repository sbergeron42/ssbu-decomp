# Worker: pool-d

## Model: Opus

## Task: jemalloc 5.1.0 decomp — continue lower range (round 3)

Continue matching jemalloc functions against upstream source at `lib/jemalloc/`.
Pick up where the previous round left off.

### Upstream Reference
- jemalloc 5.1.0, upstream source at `lib/jemalloc/src/`
- Every function gets `// jemalloc 5.1.0: file.c:line` provenance comment

### Address Range
0x7103920000 — 0x7103940000 (skip functions already in build/*.o)

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/lib/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- ONLY create src/lib/jemalloc_d2_*.cpp
- Use upstream jemalloc field names
- 3-attempt limit per function
