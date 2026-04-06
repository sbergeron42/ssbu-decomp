# Worker: pool-b

## Model: Opus

## Task: Resource service — directory_file_read (0x71039a4040, 11,408 bytes)

This is ARCropolis hook point #3: `inflate_dir_file`. ARCropolis replaces this entire function to handle directory file decompression for modded content.

### Function Details
- Address: 0x71039a4040
- Size: 11,408 bytes
- ARCropolis hook name: `inflate_dir_file` / `directory_file_read`

### Key Context
- Handles decompression of directory-level file entries from the ARC archive
- Uses zlib or zstd depending on FileData.flags (bit 0 = compressed, bit 1 = use_zstd)
- Accesses LoadedArc tables: folder_offsets, file_infos, file_info_to_datas, file_datas
- Global: DAT_7105331f28 = ResServiceNX singleton, DAT_7105331f20 = FilesystemInfo

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Derivation Chains (MANDATORY)
- `[derived: ARCropolis inflate_dir_file hook]` — function purpose
- `[derived: smash-arc FileData/DirectoryOffset]` — ARC struct fields
- `[inferred:]` for any fields not in community sources

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_inflate.cpp
- This is a large function — focus on getting the structure right with correct types
- 3-attempt limit per section
- Do NOT use naked asm
