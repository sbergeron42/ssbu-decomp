# Worker: pool-a

## Model: Opus

## Task: Struct access rewrite with derivation chains — batch_c_012 + batch_c_013

### Target Files (2 files, ~69 functions with heavy module access)
- `src/app/fun_batch_c_012.cpp` — 40 funcs, 41 module dereferences
- `src/app/fun_batch_c_013.cpp` — 29 funcs, 39 module dereferences

These files already have shallow variable renames from a previous round. Your job is to ADD struct field access and derivation chain comments. Do NOT just rename more variables.

### MANDATORY Before/After Example

**BEFORE (this is what the code looks like now — DO NOT submit work that looks like this):**
```cpp
// 0x7102208730
u32 FUN_7102208730(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}
```

**AFTER (this is what "done" looks like — struct access + derivation chains):**
```cpp
// 0x7102208730
// KineticModule flag clear for energy index 0xc
u32 FUN_7102208730(s64 param_1)
{
    // param_1-8 → BattleObject, +0x1a0 → accessor [derived: BattleObject layout in .dynsym ctors]
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    // +0x68 → kinetic_module [derived: KineticModule__*_impl (.dynsym) loads from accessor+0x68]
    KineticModule *kinetic = reinterpret_cast<KineticModule*>(acc->kinetic_module);
    // vtable+0x60 → get_energy_entry [inferred: index-based lookup, returns energy struct]
    s64 energy = reinterpret_cast<s64 (*)(KineticModule*, s64)>(
        VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x30 → enabled flag [inferred: set to 0/1 across 40 functions in this file]
    *(u8 *)(energy + 0x30) = 0;
    return 0;
}
```

**Key differences:**
1. `acc->kinetic_module` instead of `*(ptr + 0x68)` — uses the struct header
2. Every offset has a `[derived:]` or `[inferred:]` comment explaining HOW the name was determined
3. Function has a one-line description of what it does
4. Confidence levels: `[derived: ...]` = proven from binary evidence, `[inferred: ...]` = pattern-based guess

### Confidence Tags (REQUIRED on every named field)
- `[derived: <evidence>]` — name proven from .dynsym, xref, or verified function
- `[inferred: <pattern>]` — name guessed from usage pattern, not proven
- `[unknown]` — offset is used but no name can be determined; use `field_0xNN` naming

### What is NOT acceptable
- Renaming `uVar1` → `result` WITHOUT replacing raw offsets with struct access
- Adding struct access WITHOUT derivation comments
- Guessing field names without tagging confidence level

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name  # NOT address
```

### Rules
- CAN ONLY edit: fun_batch_c_012.cpp, fun_batch_c_013.cpp
- Must `#include "app/BattleObjectModuleAccessor.h"` and use the struct
- 3-attempt limit per function for matching, but derivation comments are required regardless
