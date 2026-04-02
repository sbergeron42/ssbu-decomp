#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e2-012
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

// x9-register callees
extern "C" void FUN_7103775b40(u64);
extern "C" void FUN_710376b3b0(u64);

// FUN_710356bb30: [[noreturn]] panic. Wrappers use u64 return type with no return statement
// so Clang emits: stp + mov + bl + udf (unreachable trap) = 16 bytes each.
[[noreturn]] extern "C" void FUN_710356bb30(void);

// ---- x9-register wrappers -----------------------------------------------
// Pattern: x9 is a live register input (hidden param); no C++ visible params.
// Dispatch variants:
//   A) FUN_7103775b40(**(u64**)x9)  — double-dereference x9
//   B) vtable[0xNN/8](*x9)          — single-dereference x9 → object, vtable call
//   C) FUN_710376b3b0(*x9)          — single-dereference x9, pass as arg

// 0x7103353804 — FUN_7103775b40(**(u64**)x9)
u32 FUN_7103353804(void)
{
    register u64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    FUN_7103775b40(**in_x9);
    return 0;
}

// 0x71033603c8 — vtable[0x60/8](*x9)
u32 FUN_71033603c8(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x60))(obj);
    return 0;
}

// 0x7103360568 — vtable[0x70/8](*x9)
u32 FUN_7103360568(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x70))(obj);
    return 0;
}

// 0x71033613cc — FUN_710376b3b0(*x9)
u32 FUN_71033613cc(void)
{
    register u64 *in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    FUN_710376b3b0(*in_x9);
    return 0;
}

// 0x7103362908 — vtable[0x60/8](*x9)
u32 FUN_7103362908(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x60))(obj);
    return 0;
}

// 0x7103362aa8 — vtable[0x70/8](*x9)
u32 FUN_7103362aa8(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x70))(obj);
    return 0;
}

// 0x7103365e68 — vtable[0x60/8](*x9)
u32 FUN_7103365e68(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x60))(obj);
    return 0;
}

// 0x7103365f68 — vtable[0x70/8](*x9)
u32 FUN_7103365f68(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    (**(void (**)(s64 *))(*obj + 0x70))(obj);
    return 0;
}

// ---- state-checker bool functions -----------------------------------------------
// Pattern: get Status/Work module via param_2, vtable call, return comparison result

// 0x71034324e0 — iVar1 != 0 (Status module at +0x40, vtable[0x110/8])
u8 FUN_71034324e0(u64 param_1, s64 param_2)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x40);
    s32 iVar1 = (**(s32 (**)(s64 *))(*plVar1 + 0x110))(plVar1);
    return (u8)(iVar1 != 0);
}

// 0x71033c8650 — ~uVar1 & 1 (Work module at +0x50, vtable[0x108/8], arg 0x20000006)
u32 FUN_71033c8650(u64 param_1, s64 param_2)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x50);
    u32 uVar1 = (**(u32 (**)(s64 *, u32))(*plVar1 + 0x108))(plVar1, 0x20000006);
    return ~uVar1 & 1;
}

// ---- FUN_710356bb30 call wrappers (16 bytes each) -----------------------------------------------
// Pattern: stp+mov+bl FUN_710356bb30+udf
// Callee is [[noreturn]]; wrappers use u64 return type with no return statement
// so Clang emits: stp + mov + bl + udf (unreachable trap) = 16 bytes each.

// 0x71035da3c0
u64 FUN_71035da3c0(void) { FUN_710356bb30(); }

// 0x71035dae20
u64 FUN_71035dae20(void) { FUN_710356bb30(); }

// 0x71035f33d0
u64 FUN_71035f33d0(void) { FUN_710356bb30(); }

// 0x71036350d0
u64 FUN_71036350d0(void) { FUN_710356bb30(); }

// 0x71036350e0
u64 FUN_71036350e0(void) { FUN_710356bb30(); }

// 0x710363b690
u64 FUN_710363b690(void) { FUN_710356bb30(); }

// 0x7103662290
u64 FUN_7103662290(void) { FUN_710356bb30(); }

// 0x71036622a0
u64 FUN_71036622a0(void) { FUN_710356bb30(); }

// 0x71036ac780
u64 FUN_71036ac780(void) { FUN_710356bb30(); }

// 0x71036b1be0
u64 FUN_71036b1be0(void) { FUN_710356bb30(); }

// 0x71036c5e90
u64 FUN_71036c5e90(void) { FUN_710356bb30(); }

// 0x71036ccf30
u64 FUN_71036ccf30(void) { FUN_710356bb30(); }

// 0x71036d6450
u64 FUN_71036d6450(void) { FUN_710356bb30(); }

// 0x71036d6460
u64 FUN_71036d6460(void) { FUN_710356bb30(); }
