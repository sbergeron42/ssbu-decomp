#include "types.h"
#include "app/modules/StatusModule.h"

// Batch E2 - 012: x9-register wrappers, state checkers, noreturn wrappers (0x7103 range)

#define VT(m) (*reinterpret_cast<void***>(m))

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_7103775b40(u64);
extern "C" void FUN_710376b3b0(u64);

// abort_710356bb30: [[noreturn]] panic/abort
[[noreturn]] extern "C" void abort_710356bb30(void);

// ---- x9-register dispatch wrappers ----------------------------------------
// x9 is a live register input (hidden param). Three dispatch variants:
//   A) FUN_7103775b40(**(u64**)x9)  — double-deref x9
//   B) vtable[N](*x9)               — single-deref x9, vtable call
//   C) FUN_710376b3b0(*x9)          — single-deref x9, direct call

// 0x7103353804 — double-deref x9, call FUN_7103775b40
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
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x60 / 8])(obj);
    return 0;
}

// 0x7103360568 — vtable[0x70/8](*x9)
u32 FUN_7103360568(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x70 / 8])(obj);
    return 0;
}

// 0x71033613cc — single-deref x9, call FUN_710376b3b0
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
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x60 / 8])(obj);
    return 0;
}

// 0x7103362aa8 — vtable[0x70/8](*x9)
u32 FUN_7103362aa8(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x70 / 8])(obj);
    return 0;
}

// 0x7103365e68 — vtable[0x60/8](*x9)
u32 FUN_7103365e68(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x60 / 8])(obj);
    return 0;
}

// 0x7103365f68 — vtable[0x70/8](*x9)
u32 FUN_7103365f68(void)
{
    register s64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *in_x9;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x70 / 8])(obj);
    return 0;
}

// ---- State-checker bool functions -------------------------------------------
// Load module from accessor (param_2+0x20 = BattleObject, then module offset),
// vtable call, return comparison result.

// 0x71034324e0 — StatusModule vtable[0x110/8], return != 0
// acc+0x40 = status_module [derived: StatusModule__*_impl (.dynsym)]
u8 FUN_71034324e0(u64 param_1, s64 param_2)
{
    auto* status_mod = reinterpret_cast<app::StatusModule*>(*(void**)(*(s64 *)(param_2 + 0x20) + 0x40));
    s32 status_kind = status_mod->vtbl->StatusKind(status_mod);
    return (u8)(status_kind != 0);
}

// 0x71033c8650 — WorkModule vtable[0x108/8](mod, 0x20000006), return ~result & 1
// acc+0x50 = work_module [derived: WorkModule__*_impl (.dynsym)]
u32 FUN_71033c8650(u64 param_1, s64 param_2)
{
    s64 *work_mod = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x50);
    u32 flag = reinterpret_cast<u32 (*)(s64 *, u32)>(VT(work_mod)[0x108 / 8])(work_mod, 0x20000006);
    return ~flag & 1;
}

// ---- abort_710356bb30 noreturn wrappers (16 bytes each) -----------------------
// Callee is [[noreturn]]; u64 return type with no return statement
// → Clang emits: stp + mov + bl + udf (unreachable trap)

// 0x71035da3c0
u64 FUN_71035da3c0(void) { abort_710356bb30(); }

// 0x71035dae20
u64 FUN_71035dae20(void) { abort_710356bb30(); }

// 0x71035f33d0
u64 FUN_71035f33d0(void) { abort_710356bb30(); }

// 0x71036350d0
u64 FUN_71036350d0(void) { abort_710356bb30(); }

// 0x71036350e0
u64 FUN_71036350e0(void) { abort_710356bb30(); }

// 0x710363b690
u64 FUN_710363b690(void) { abort_710356bb30(); }

// 0x7103662290
u64 FUN_7103662290(void) { abort_710356bb30(); }

// 0x71036622a0
u64 FUN_71036622a0(void) { abort_710356bb30(); }

// 0x71036ac780
u64 FUN_71036ac780(void) { abort_710356bb30(); }

// 0x71036b1be0
u64 FUN_71036b1be0(void) { abort_710356bb30(); }

// 0x71036c5e90
u64 FUN_71036c5e90(void) { abort_710356bb30(); }

// 0x71036ccf30
u64 FUN_71036ccf30(void) { abort_710356bb30(); }

// 0x71036d6450
u64 FUN_71036d6450(void) { abort_710356bb30(); }

// 0x71036d6460
u64 FUN_71036d6460(void) { abort_710356bb30(); }
