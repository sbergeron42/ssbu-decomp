# Worker: pool-d

## Model: Opus

## Task: Game core + params — continue

## Progress
- populate_parameters_for_hash40 (13,536B) — compiled, N-quality (85% size match)
- 6 prior functions: apply_lift_param, sub_rage_system, get_magic_ball_param, UpdateParams, global_param_init_sets_team_flag, nnMain
- Ghidra size mislabeling found on 2 functions
- copy (120B, 0x7103720870) — compiled, N-quality (resource load node alloc with OOM retry)
- open_param_file (448B, 0x7103720680) — compiled, N-quality (opens file by filepath index from FilesystemInfo)
- read_param_file (232B, 0x7103720910) — compiled, N-quality (wraps open_param_file with callback)
- nninitStartup (60B, 0x71002c55e0) — compiled, N-quality (SDK early init: jemalloc config, fs allocator)
- FUN_7103720d80 (96B) — compiled, N-quality (filesystem entry type check with callback)
- is_master_hand_stage (136B, 0x710227ebf0) — compiled, N-quality (checks stage kind 4/5)
- FUN_71031877f0 (220B) — compiled, N-quality (param element reader: base + 8 values)
- FUN_71031876a0 (332B) — compiled, N-quality (param element reader: base + 12 values + conditional)
- FUN_7103185b60 (288B) — compiled, N-quality (param element reader: version < 2 legacy + 4 floats)
- FUN_7103186760 (348B) — compiled, N-quality (param element reader: base + 4 floats + sub + array)
- FUN_71031868c0 (404B) — compiled, N-quality (param element reader: base + 8 floats + u32 + packed)
- FUN_7103188450 (328B) — compiled, N-quality (param element reader: base + s32 + u32 + 7 floats)
- FUN_7103187500 (408B) — compiled, N-quality (param element reader: base + sub + 2 strings)
- FUN_7103188160 (352B) — compiled, N-quality (param array reader: count/ptr pairs, 0x10 stride)
- FUN_7103189710 (320B) — compiled, N-quality (param element reader: base + 8 values + byte + u32)
- FUN_7103186d70 (1176B) — compiled, N-quality (param element reader: base + packed + array + OOM)
- FUN_7103186a60 (784B) — compiled, N-quality (param element reader: base + s32 + array + area calc, NEON approx)

- FUN_71031885c0 (1188B) — compiled, N-quality (base header reader: 2xu32, string, 24 bytes)
- FUN_7103187210 (740B) — compiled, N-quality (common element reader: base + name + packed values)
- FUN_7103187920 (768B) — compiled, N-quality (sub-element reader: u32 + 16 bytes or 4 floats + array)

- FUN_7103185c80 (2772B) — compiled, N-quality (param element reader: 3 sub-arrays + area weights + sentinel fill)
- FUN_7103184f20 (3132B) — compiled, N-quality (param element reader: structured sub-elements + 0x120/0x160 stride)
- FUN_7103187c20 (1332B) — compiled, N-quality (read_string32: 32-byte byte-by-byte string reader)
- FUN_7103188a70 (2612B) — compiled, N-quality (read_string64: 64-byte byte-by-byte string reader)
- FUN_71031882c0 (392B) — compiled, N-quality (array reader: count + 0x10-stride float pairs with OOM)
- FUN_71031894b0 (600B) — compiled, N-quality (array reader: prepended size header + 0x40 sub-elements)
- FUN_7103189880 (564B) — compiled, N-quality (array reader: count + s32 values with 0xfffffffa fill)
- FUN_7103189b00 (304B) — compiled, N-quality (StageCameraPath element reader: base + string + 6 floats)

## Continue with
- All read_element sub-functions COMPLETE — 24/24 element types covered
- Next: look for additional game_core or param functions outside the 0x71031849xx range
- Consider tackling read_file wrapper functions or stage/camera param consumers
- Ghidra analysis saved to data/ghidra_cache/pool-d.txt

## read_file Analysis (0x7103180ad0, 17,488B)
- Signature: `void read_file(long output_struct, long stream_reader, uint version)`
- Stream reader: vtable at `*(*(param_2+8))`, endianness flag at `*(param_2+4)`
- Output struct: ~0x178 bytes, 24 pairs of (u32 count, void* array) at +0x08..+0x170
- Version gates: <2, ==2, <4, ==4, >=5, v12+, v13+, <6, ==6, <8, <9, <10, <11, v11+
- 24 element types with strides 0x110..0x240, common base struct ~0xF8 bytes
- Magic constant 0x7735bb75 in all 24 element initializers (type hash/CRC32)
- **Strategy**: Don't byte-match read_file itself. Target the ~15 read_element sub-functions:
  FUN_7103184f20 (0x160 stride), FUN_7103185b60 (0x110, most common, 10 calls),
  FUN_7103185c80 (0x1A0), FUN_7103186760 (0x240, largest), FUN_71031868c0 (0x140),
  FUN_7103186a60 (0x130), FUN_7103186d70 (0x1B0), FUN_7103187210 (common sub-reader),
  FUN_7103187500 (0x170), FUN_71031876a0 (0x140), FUN_71031877f0 (0x120),
  FUN_7103187920 (sub-element), FUN_7103188160, FUN_7103188450, FUN_71031885c0, FUN_7103189710
- Ghidra output saved: data/ghidra_cache/pool-d_read_file.txt (3,212 lines)

## Deferred
- game_tick (15,376B) — impossible, 94-case switches
- round_manager_update (29,496B) — jump table, too large

## File Territory
- src/app/param_loading.cpp, game_core.cpp, global_param_init.cpp

## Quality Rules
- No naked asm, 3-attempt limit, N-quality is fine for large functions

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-d.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-d: decomp MODULE functions (N new, M matching)`
- If session crashes, uncommitted work will be auto-recovered by the launcher script

## Rewrite Quality Standard
BAD (rename only — NOT acceptable):
```cpp
void FUN_710228d930(void* param_1) {
    void* result = *(void**)((u8*)param_1 + 0x40);
    (*(void(**)(void*))(*(u8**)result + 0x38))(result);
}
```

GOOD (struct access + derivation chain):
```cpp
void StatusModule_change_status(BattleObjectModuleAccessor* acc) {
    StatusModule* mod = acc->status_module;  // +0x40 [derived: .dynsym StatusModule vtable]
    mod->change_status();  // vtable[7] [derived: StatusModule.h]
}
```
