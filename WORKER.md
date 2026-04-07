# Worker: pool-a

## Model: Opus

## Task: ResLoadingThread iteration — structural matching

The function is in src/resource/ResLoadingThread.cpp. **Three binary functions** share this compilation unit:
- 0x7103542f30: `something_file_version` (104 bytes) — version resolver
- 0x7103542fa0: Small outer loop function (232 bytes) — update/idle thread
- **0x7103543090**: The main ResLoadingThread body (~12,136 bytes) — THIS is our target

### Completed fixes (this session)
1. **Field mapping corrected**: `service->state` (s16 at +0xE4) was wrong for loading_thread_state → changed to `service->unk4` (u32 at +0xE0)
2. **Header fix**: Changed `s16 state` → `u8 state; u8 pad_e5;` at +0xE4 (binary accesses this as byte only)
3. **WaitEvent fixed**: Was using wrong field (unk_event2 at +0x20) with single deref → now uses res_update_event (+0x08) with double deref
4. **io_swap_event signal fixed**: Single deref → double deref (`**(void***)`)
5. **vec_push_u32 inlined**: Added `__attribute__((always_inline))` — compiler was outlining it
6. **Re-queue unified**: Merged "for 4 + separate 1" into single "for 5" loop

### Current status
- **CRITICAL FINDING**: The 12,136 byte range contains 3 SEPARATE functions, not 1!
  - Function 1 (ResLoadingThread): 0x3543090-0x35444B4 = **5156 bytes** ← OUR TARGET
  - Function 2 (inflate/processing): 0x35444C0-0x35456C0 = 4608 bytes (not yet decompiled)
  - Function 3 (FUN_7103544ca0): 0x35456D0-0x3545E64 = 1940 bytes (declared extern)
- Compiled: 5064 bytes → **98.2% of expected Function 1 size** (only 92 bytes short!)
- Match rate: ~0.6% — low because 32-byte frame size mismatch cascades to all sp-relative insns
- Frame size: 384 (compiled) vs 416 (expected) — 32 bytes short

### What still needs work (priority order)
1. **Frame size (32 bytes short)**: Need function-scope temporaries (aiStack_78[2] + uStack_70) to match expected 416-byte frame. Once this matches, many more instructions will align.
2. **Queue swap**: Still "simplified" — needs full doubly-linked list swap
3. **Re-queue unrolling**: Binary shows 5 unrolled while loops; our for-loop may not unroll
4. **92 bytes missing**: Likely from queue swap / re-queue differences
5. **Function 2 (inflate thread)**: 4608 bytes of processing loop — entirely unwritten, next major target
6. **Function 3**: FUN_7103544ca0 directory dispatch — 1940 bytes, currently extern

### ELF comparison note
Use proper segment mapping: `file_offset = seg_offset + (vaddr - seg_vaddr)`. First segment: vaddr=0x0, offset=0x888.
Compare against Function 1 only: vaddr 0x3543090, size 5156 bytes.

### How to get Ghidra decompilation
```
mcp__ghidra-1301__decompile_function_by_address("0x7103542f30")
```
This returns the full function (Ghidra 13.0.1 merges the version resolver + ResLoadingThread).

### Compare against binary
```
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=0x3542fa0 --stop-address=0x35460c0 data/main.elf
```

### Headers: include/resource/*.h
### Output: Edit src/resource/ResLoadingThread.cpp
### Do NOT use naked asm. This is the project's showcase function.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/ResLoadingThread.cpp -o build/ResLoadingThread.o

python tools/compare_bytes.py ResLoadingThread
```
