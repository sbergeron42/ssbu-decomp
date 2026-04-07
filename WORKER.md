# Worker: pool-b

## Model: Opus

## Task: Resource service — medium functions (400-1400 bytes)

### Targets
- `FUN_710353af30` (656B), `FUN_710353b200` (656B)
- `FUN_710353b930` (752B)
- `FUN_710353dc20` (432B), `FUN_710353ddd0` (608B)
- `FUN_710353e330` (432B), `FUN_710353e5d0` (400B), `FUN_710353e760` (544B)
- `FUN_710353ec40` (944B), `FUN_710353eff0` (448B)
- `FUN_710353a8f0` (1,280B) — filesystem scanner (DONE in res_filesystem.cpp)
- `FUN_710353a230` (1,376B) — battle object function, not resource service

### Progress
| Function | Status | Match | Notes |
|----------|--------|-------|-------|
| FUN_710353e760 | compiled | 65% | region/language resolver, register swap diffs |
| FUN_710353e5d0 | compiled | 56% | dual bsearch, cmn/adds NX fork diff |
| FUN_710353ec40 | compiled | 5% | recursive dir unload, complex control flow |
| FUN_710353dc20 | compiled | 4% | CRC32 hash + directory child search |
| FUN_710353e330 | compiled | 4% | path normalize + bsearch |
| FUN_710353eff0 | compiled | 2% | vector push loop |
| FUN_710353ddd0 | compiled | 1% | hash match + binary search |
| FUN_710353a8f0 | DONE | — | already in res_filesystem.cpp |
| FUN_710353af30 | TODO | — | file open/init |
| FUN_710353b200 | TODO | — | tree insertion |
| FUN_710353b930 | TODO | — | vtable handler swap |
| FUN_710353a230 | SKIP | — | battle object function, wrong module |

Low match rates are mostly due to NX Clang fork divergences:
- Prologue shrink-wrapping (comparison before register saves)
- `cmn` vs `adds` codegen (upstream discards result, NX keeps it)
- Comparison operand ordering
- ADRP/LDR relocation differences (not patched in compare_bytes)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_medium_helpers.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
