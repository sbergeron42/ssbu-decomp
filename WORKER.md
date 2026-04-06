# Worker: pool-a

## Model: Opus

## Task: Resource service — lookup_stream_hash (FUN_7103541200, 704 bytes)

This is one of the 9 ARCropolis hook points. It's the stream file hash lookup function — the most decomp-friendly of the hook targets.

### Function Details
- Address: 0x7103541200
- Size: 704 bytes
- ARCropolis hook name: `lookup_stream_hash`
- Signature (from ARCropolis): `void lookup_stream_hash(char* out_path, LoadedArc* arc, size_t* size_out, u64* offset_out, Hash40 hash)`

### Key Context
- This function looks up a file in the stream section of the ARC archive by hash
- ARCropolis replaces this entire function to redirect file loads to modded content
- The LoadedArc struct is defined in `include/resource/LoadedArc.h`
- Stream-related fields: stream_header, stream_hash_to_entries, stream_entries, stream_file_indices, stream_datas

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Derivation Chains (MANDATORY)
- `[derived: ARCropolis lookup_stream_hash hook]` — for function signature and purpose
- `[derived: smash-arc StreamEntry/StreamData]` — for ARC struct fields
- `[inferred:]` for any fields not in ARCropolis/smash-arc

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_stream.cpp
- 3-attempt limit
- Do NOT use naked asm
