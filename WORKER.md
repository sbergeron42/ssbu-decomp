# Worker: pool-c

## Model: Opus

## Task: Destructor/cleanup pattern decomp + WorkModule/StatusModule internals

### Completed
- **22 verified functions** in `src/app/fun_typed_c_002.cpp` across 4 patterns:
  - Pattern B (7): sub at +0x50, inner cleanup at sub+8, tail-call parent dtor
  - Pattern C (4): sub at +0x50, direct cleanup call, tail-call parent dtor
  - Pattern A (5): sub at +0x8, stp vtable+zero, cleanup, tail-call delete self
  - Pattern D (6): Binary tree recursive delete (left, right, free)
- **17 thunks** in `src/app/fun_typed_c_001.cpp` (FighterInformation/FighterManager/BattleObjectWorld)

### Key findings
- All named WorkModule/StatusModule lua_bind dispatchers (16B each) already compiled
- Remaining uncompiled in those ranges are Lua VM wrappers (304-2032B) requiring custom Lua headers
- Lua VM wrappers need inlined Lua C API matching — no headers available
- WorkModule Lua registration at 0x7102092330, StatusModule at 0x7102088f60
- Hidden visibility on vtable externs produces correct ADRP+ADD (avoids GOT)

### Output
- `src/app/fun_typed_c_001.cpp` — FighterInformation/FighterManager thunks
- `src/app/fun_typed_c_002.cpp` — Destructors and tree-deletes

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_c_*.cpp
