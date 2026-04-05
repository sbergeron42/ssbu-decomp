# Worker: pool-c

## Model: Opus

## Task: Destructor/cleanup pattern decomp + WorkModule/StatusModule internals

### Completed
- **34 verified functions** in `src/app/fun_typed_c_002.cpp` across 8 patterns:
  - Pattern B (7): sub at +0x50, inner cleanup at sub+8, tail-call parent dtor
  - Pattern C (4): sub at +0x50, direct cleanup call, tail-call parent dtor
  - Pattern A (5): sub at +0x8, stp vtable+zero, cleanup, tail-call delete self
  - Pattern D (6): Binary tree recursive delete (left, right, free)
  - Pattern D2 (2): Tree delete with 2 params (ctx passthrough)
  - Pattern D3 (2): Tree delete with extra cleanup (1-param and 2-param variants)
  - Pattern G (3): Linked list walk destructor (walk list, free nodes, null+free field)
  - Pattern F (5): shared_ptr destructor (2 vtables, cleanup inner, tail-call ~__shared_weak_count)
- **22 Pattern E destructors** (simple vtable dtor + cleanup + delete self)
- **17 thunks** in `src/app/fun_typed_c_001.cpp` (FighterInformation/FighterManager/BattleObjectWorld)

### Key findings
- All named WorkModule/StatusModule lua_bind dispatchers (16B each) already compiled
- Remaining uncompiled in those ranges are Lua VM wrappers (304-2032B) requiring custom Lua headers
- Lua VM wrappers need inlined Lua C API matching — no headers available
- WorkModule Lua registration at 0x7102092330, StatusModule at 0x7102088f60
- Hidden visibility on vtable externs produces correct ADRP+ADD (avoids GOT)
- Pattern H (multi-sub-vtable dtors, ~20 functions in 0x710171*) blocked by prologue scheduling:
  upstream Clang 8 hoists ADRP+ADD before stp x29,x30 when 2+ ADRP pairs exist.
  fix_prologue_sched.py only handles add x29 displacement, not stp x29 displacement.
  Code logic verified correct — needs tool enhancement to match.

### Output
- `src/app/fun_typed_c_001.cpp` — FighterInformation/FighterManager thunks
- `src/app/fun_typed_c_002.cpp` — Destructors and tree-deletes

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_c_*.cpp
