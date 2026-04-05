#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-009
// Pool-d worker: abort thunks, global-dispatch wrappers,
//   in_x10 vtable wrappers, deref-chain vtable dispatchers, misc

// NOTE: FUN_7101fdf3e0 / FUN_7101fe0350 / FUN_7101fe3400 carry a value in
// AArch64 register X10 that cannot be represented in standard C++.
// Initialized to 0 here; will not verify.

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_71014f8940(u64);
extern "C" void FUN_71014fe660(u64);
extern "C" void FUN_7103775b40(u64, s32);
extern "C" void FUN_71037759f0(u64);
extern "C" void FUN_710377ab90(s64);

extern "C" u64 *DAT_71052c2760;
extern "C" u8   DAT_710593a988[];

// ---- abort() thunks -------------------------------------------------------

// 0x71003bcdfc
[[noreturn]] void FUN_71003bcdfc(void) { abort(); }

// 0x71004afac0
[[noreturn]] void FUN_71004afac0(void) { abort(); }

// 0x7101485e30
[[noreturn]] void FUN_7101485e30(void) { abort(); }

// 0x71014867b0
[[noreturn]] void FUN_71014867b0(void) { abort(); }

// 0x7101541b8c
[[noreturn]] void FUN_7101541b8c(void) { abort(); }

// 0x71018594bc
[[noreturn]] void FUN_71018594bc(void) { abort(); }

// 0x7101d2de80
[[noreturn]] void FUN_7101d2de80(void) { abort(); }

// ---- Global-dispatch wrappers (via *DAT_71052c2760) ----------------------

// 0x71013427a0 — dispatch to FUN_71014fe660
void FUN_71013427a0(void)
{
    FUN_71014fe660(*DAT_71052c2760);
}

// 0x71013427f0 — dispatch to FUN_71014f8940
void FUN_71013427f0(void)
{
    FUN_71014f8940(*DAT_71052c2760);
}

// ---- in_x10 vtable wrappers (register artifact, cannot match) ------------

// 0x7101fdf3e0 — store in_x10 at result+0x10, vtable call +0x368
u64 FUN_7101fdf3e0(s64 *obj, s64 result)
{
    u64 in_x10 = 0;
    *(u64 *)(result + 0x10) = in_x10;
    (*(void(**)(s64 *))(*obj + 0x368))(obj);
    return 0;
}

// 0x7101fe0350 — store in_x10 at result+0x10, vtable call +0x430
u64 FUN_7101fe0350(s64 *obj, s64 result)
{
    u64 in_x10 = 0;
    *(u64 *)(result + 0x10) = in_x10;
    (*(void(**)(s64 *))(*obj + 0x430))(obj);
    return 0;
}

// 0x7101fe3400 — store in_x10 at result+0x10, vtable call +0x568
u64 FUN_7101fe3400(s64 *obj, s64 result)
{
    u64 in_x10 = 0;
    *(u64 *)(result + 0x10) = in_x10;
    (*(void(**)(s64 *))(*obj + 0x568))(obj);
    return 0;
}

// ---- Deref-chain vtable dispatcher ----------------------------------------

// 0x7101f95750 — triple deref to module ptr, vtable +0xc0 with hash 0x10b3dc8ba9
u64 FUN_7101f95750(s64 this_ptr)
{
    s64 *module = *(s64 **)(*(s64 *)(*(s64 *)(this_ptr - 8) + 0x1a0) + 0x190);
    (*(void(**)(s64 *, s64, u64))(*module + 0xc0))(module, this_ptr, 0x10b3dc8ba9ULL);
    return 1;
}

// ---- Double-deref vtable dispatchers -------------------------------------

// 0x71013298b0 — WorkModule vtable +0x108, const 0x2100000c, return ~result&1
u32 FUN_71013298b0(u64 unused, s64 accessor)
{
    s64 *work = *(s64 **)(accessor + 0x50);
    u32 flag = (*(u32(**)(s64 *, u32))(*work + 0x108))(work, 0x2100000c);
    return ~flag & 1;
}

// 0x7101661e20 — vtable +0x110 via *(accessor+0xe8), const 0x20000002
u32 FUN_7101661e20(u64 unused, s64 accessor)
{
    s64 *search = *(s64 **)(accessor + 0xe8);
    (*(void(**)(s64 *, u32))(*search + 0x110))(search, 0x20000002);
    return 0;
}

// ---- Two-vtable dispatch -------------------------------------------------

// 0x710014fde0 — vtable call at *obj+0x20 (no arg), then *obj+0x10 (obj, 1)
void FUN_710014fde0(s64 *obj)
{
    (*(void (**)())(*obj + 0x20))();
    (*(void(**)(s64 *, s32))(*obj + 0x10))(obj, 1);
}

// ---- Misc wrappers -------------------------------------------------------

// 0x71013bccf0 — three cleanup calls on sub-offsets, decrement timer
void FUN_71013bccf0(s64 this_ptr)
{
    s64 sub_obj = *(s64 *)(*(s64 *)(this_ptr + 0x10) + 0x80);
    FUN_710377ab90(sub_obj + 0x40);
    FUN_710377ab90(sub_obj + 0x4e0);
    FUN_710377ab90(sub_obj + 0x520);
    if (0 < *(s32 *)(this_ptr + 0x1fc)) {
        *(s32 *)(this_ptr + 0x1fc) = *(s32 *)(this_ptr + 0x1fc) - 1;
    }
}

// 0x710147c79c — deref chain, call FUN_71037759f0, set two flag bytes
void FUN_710147c79c(s64 this_ptr)
{
    s64 inner = *(s64 *)(this_ptr + 8);
    FUN_71037759f0(**(u64 **)(*(s64 *)(inner + 0x80) + 8));
    *(u8 *)(inner + 0x70) = 1;
    *(u8 *)(this_ptr + 0x188) = 1;
}

// 0x7101d9c59c — call FUN_7103775b40 with double-deref arg, clear bit 1 of global
void FUN_7101d9c59c(s64 this_ptr)
{
    FUN_7103775b40(*(u64 *)*(u64 **)(this_ptr + 0x148), 1);
    *(u32 *)*(u32 **)(DAT_710593a988 + 8) = *(u32 *)*(u32 **)(DAT_710593a988 + 8) & 0xfffffffd;
}
