# Worker: pool-e

## Model: Sonnet

## Task: Batch MEDIUM decomp (0x7102-0x7103 range, continued)

Continue batch-decompiling MEDIUM-tier functions. Now use the struct headers in include/app/ for better readability.

### Batch pipeline workflow
1. Pick 20-30 uncompiled MEDIUM functions from data/fun_triage.csv in 0x7102-0x7103 range
2. For each, call mcp__ghidra__decompile_function_by_address(address)
3. Apply type fixups (undefined8->u64, uint->u32, etc.)
4. Where possible, use BattleObjectModuleAccessor fields instead of raw offsets
5. Write to src/app/fun_batch_e3_NNN.cpp with // 0x71XXXXXXXX address comments
6. Build, verify, commit, repeat

### Using structs
If a function takes BattleObjectModuleAccessor* as first param:
    #include "app/BattleObjectModuleAccessor.h"
    void func(app::BattleObjectModuleAccessor* acc) {
        auto* m = acc->camera_module;  // instead of *(void**)((u8*)acc + 0x60)
    }

### Progress (session 2)
Batches e3-017 through e3-025 committed (2026-04-02):
- e3-017: 13 ComboModule (0xb8) lua_bind wrappers
- e3-018/019: 22 ModelModule (+0x78) _impl thunks (4/5-insn tail calls)
- e3-020: 9 more ModelModule thunks
- e3-021/022/023: 93 MotionModule (+0x88) thunks
- e3-023 also: 13 MotionAnimcmdModule (+0x188) thunks
- e3-024/025: 41 PostureModule (+0x38) + ReflectModule (+0xf8) thunks

### Progress (session 3)
Batches e3-028 through e3-041 committed (2026-04-02):
- e3-028/029/030/031: vtable dispatch thunks (framed_vtable_call, pattern A/B)
- e3-032/033: named bl-direct thunks (framed_vtable_call, x8-dispatch)
- e3-034 through e3-041: 147 more bl-direct thunks discovered via raw ELF byte scan
  (Ghidra missed most as separate function boundaries; identified via raw bytes)
  Coverage: 0x710215e150 through 0x710226e0c0, all 8-insn/6-insn thunk patterns
ALL simple framed_vtable_call thunks in N-quality are now written.
Next: look for other compilable patterns in remaining N-quality (0x7103 range)

### Rules
- ONLY create NEW files named src/app/fun_batch_e3_*.cpp
- Do NOT edit any existing files
- Do NOT modify data/functions.csv or tools/
