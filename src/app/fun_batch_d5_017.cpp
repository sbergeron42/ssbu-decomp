#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100-0x7101 range, batch d5-017
// Pool-d worker: auto-generated from Ghidra decompilation
// 192-byte (0xC0) group: abort thunks, nested CXA-guard functions,
//   vtable dispatchers, in_x10 wrappers, PTR_ConstantZero guard inits

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
extern "C" void FUN_71000b4160(s64);

// PTR_ConstantZero guard init DATs
extern "C" u64  DAT_71052b6eb0;
extern "C" u64  DAT_71052b6ec0;
extern "C" u64  DAT_71052b6ec8;
extern "C" u8  *PTR_ConstantZero_71052a7a88;

extern "C" u64  DAT_71052b6f90;
extern "C" u64  DAT_71052b6fa0;
extern "C" u64  DAT_71052b6fa8;
extern "C" u8  *PTR_ConstantZero_71052a7a80;

// Shared inner guard / value (DAT_7105323690 series)
extern "C" u64  DAT_7105323690;
extern "C" u64  DAT_7105323698;

// Outer guard/pointer pairs for nested CXA-guard series
extern "C" u64  DAT_71053236a8;
extern "C" u64  DAT_71053236b0;
extern "C" u64  DAT_71053236b8;
extern "C" u64  DAT_71053236c0;
extern "C" u64  DAT_71053236c8;
extern "C" u64  DAT_71053236d0;
extern "C" u64  DAT_71053236d8;
extern "C" u64  DAT_71053236e0;
extern "C" u64  DAT_71053236e8;
extern "C" u64  DAT_71053236f0;
extern "C" u64  DAT_71053236f8;
extern "C" u64  DAT_7105323700;
extern "C" u64  DAT_7105323728;
extern "C" u64  DAT_7105323730;
extern "C" u64  DAT_7105323738;
extern "C" u64  DAT_7105323740;

// ---- abort() / __throw_out_of_range thunks (192 bytes each) ----------------

// 0x71005b571c
[[noreturn]] void FUN_71005b571c(void) { abort(); }
// 0x71005de68c
[[noreturn]] void FUN_71005de68c(void) { abort(); }
// 0x710089ca3c
[[noreturn]] void FUN_710089ca3c(void) { abort(); }
// 0x710096178c
[[noreturn]] void FUN_710096178c(void) { abort(); }
// 0x7100b194ac
[[noreturn]] void FUN_7100b194ac(void) { abort(); }
// 0x7100d2ecac
[[noreturn]] void FUN_7100d2ecac(void) { abort(); }
// 0x7100d5fcec
[[noreturn]] void FUN_7100d5fcec(void) { abort(); }
// 0x7100d7e7ec
[[noreturn]] void FUN_7100d7e7ec(void) { abort(); }
// 0x7100e6788c
[[noreturn]] void FUN_7100e6788c(void) { abort(); }
// 0x7100e6912c
[[noreturn]] void FUN_7100e6912c(void) { abort(); }
// 0x7100f99ccc
[[noreturn]] void FUN_7100f99ccc(void) { abort(); }
// 0x710104af6c
[[noreturn]] void FUN_710104af6c(void) { abort(); }
// 0x710104b02c
[[noreturn]] void FUN_710104b02c(void) { abort(); }
// 0x710106955c
[[noreturn]] void FUN_710106955c(void) { abort(); }
// 0x710106961c
[[noreturn]] void FUN_710106961c(void) { abort(); }
// 0x71010696dc
[[noreturn]] void FUN_71010696dc(void) { abort(); }
// 0x710106979c
[[noreturn]] void FUN_710106979c(void) { abort(); }
// 0x710106985c
[[noreturn]] void FUN_710106985c(void) { abort(); }
// 0x71010df9bc
[[noreturn]] void FUN_71010df9bc(void) { abort(); }
// 0x71010fafbc
[[noreturn]] void FUN_71010fafbc(void) { abort(); }
// 0x7101152b0c
[[noreturn]] void FUN_7101152b0c(void) { abort(); }
// 0x71011a11ec
[[noreturn]] void FUN_71011a11ec(void) { abort(); }
// 0x71012345ec
[[noreturn]] void FUN_71012345ec(void) { abort(); }

// ---- Misc call wrapper -------------------------------------------------------

// 0x7100187670 — set param_2[0xb]=param_3, call FUN_71000b4160, vtable +0x30
void FUN_7100187670(u64 param_1, s64 *param_2, s64 param_3)
{
    if (param_3 != 0) {
        param_2[0xb] = param_3;
        FUN_71000b4160(param_3);
    }
    (*(void(**)(u64, s64*))(*param_2 + 0x30))(param_1, param_2);
}

// ---- CXA guard with PTR_ConstantZero init ------------------------------------

// 0x71003b02c0 — guard: copy 16 bytes from PTR_ConstantZero → DAT_71052b6ec0/ec8
u64 *FUN_71003b02c0(void)
{
    if (!(DAT_71052b6eb0 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71052b6eb0);
        if (iVar1 != 0) {
            DAT_71052b6ec0 = *(u64*)PTR_ConstantZero_71052a7a88;
            DAT_71052b6ec8 = *(u64*)(PTR_ConstantZero_71052a7a88 + 8);
            __cxa_guard_release((s64*)&DAT_71052b6eb0);
        }
    }
    return &DAT_71052b6ec0;
}

// 0x71003b21a0 — guard: copy 16 bytes from PTR_ConstantZero → DAT_71052b6fa0/fa8, return by value
struct FUN_71003b21a0_ret { u64 lo; u64 hi; };
FUN_71003b21a0_ret FUN_71003b21a0(void)
{
    if (!(DAT_71052b6f90 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71052b6f90);
        if (iVar1 != 0) {
            DAT_71052b6fa0 = *(u64*)PTR_ConstantZero_71052a7a80;
            DAT_71052b6fa8 = *(u64*)(PTR_ConstantZero_71052a7a80 + 8);
            __cxa_guard_release((s64*)&DAT_71052b6f90);
        }
    }
    return { DAT_71052b6fa0, DAT_71052b6fa8 };
}

// ---- Vtable dispatchers (192 bytes) -----------------------------------------

// 0x7101658c00 — double-deref vtable +0x110 via *(param_2+0xd8), return iVar1==3
bool FUN_7101658c00(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64**)(param_2 + 0xd8);
    s32 iVar1 = (*(s32(**)())(*obj + 0x110))();
    return iVar1 == 3;
}

// 0x710165c990 — same structure, return iVar1==5
bool FUN_710165c990(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64**)(param_2 + 0xd8);
    s32 iVar1 = (*(s32(**)())(*obj + 0x110))();
    return iVar1 == 5;
}

// ---- in_x10 vtable wrappers (192 bytes) ------------------------------------

// 0x7101fcc480 — in_x10 → param_2+0x10, vtable call at *param_1+0x58
u64 FUN_7101fcc480(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64*)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x58))(param_1);
    return 0;
}

// 0x7101fe1fe0 — in_x10 → param_2+0x10, vtable call at *param_1+0x4e8
u64 FUN_7101fe1fe0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64*)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x4e8))(param_1);
    return 0;
}

// ---- Nested CXA-guard series (inner: DAT_7105323690/7698) -------------------
// Each outer guard initializes DAT_7105323698=0 once (via inner guard),
// then sets its own pointer variable to &DAT_7105323698.

// 0x71017f3da0 — outer: DAT_71053236a8 → DAT_71053236b0
u64 *FUN_71017f3da0(void)
{
    if (!(DAT_71053236a8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236a8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_71053236b0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236a8);
        }
    }
    return (u64*)&DAT_71053236b0;
}

// 0x71017f3ef0 — outer: DAT_71053236b8 → DAT_71053236c0
u64 *FUN_71017f3ef0(void)
{
    if (!(DAT_71053236b8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236b8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_71053236c0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236b8);
        }
    }
    return (u64*)&DAT_71053236c0;
}

// 0x71017f4040 — outer: DAT_71053236c8 → DAT_71053236d0
u64 *FUN_71017f4040(void)
{
    if (!(DAT_71053236c8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236c8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_71053236d0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236c8);
        }
    }
    return (u64*)&DAT_71053236d0;
}

// 0x71017f4190 — outer: DAT_71053236d8 → DAT_71053236e0
u64 *FUN_71017f4190(void)
{
    if (!(DAT_71053236d8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236d8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_71053236e0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236d8);
        }
    }
    return (u64*)&DAT_71053236e0;
}

// 0x71017f42e0 — outer: DAT_71053236e8 → DAT_71053236f0
u64 *FUN_71017f42e0(void)
{
    if (!(DAT_71053236e8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236e8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_71053236f0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236e8);
        }
    }
    return (u64*)&DAT_71053236f0;
}

// 0x71017f4430 — outer: DAT_71053236f8 → DAT_7105323700
u64 *FUN_71017f4430(void)
{
    if (!(DAT_71053236f8 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71053236f8);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_7105323700 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_71053236f8);
        }
    }
    return (u64*)&DAT_7105323700;
}

// 0x71017f4f90 — outer: DAT_7105323728 → DAT_7105323730
u64 *FUN_71017f4f90(void)
{
    if (!(DAT_7105323728 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_7105323728);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_7105323730 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_7105323728);
        }
    }
    return (u64*)&DAT_7105323730;
}

// 0x71017f50e0 — outer: DAT_7105323738 → DAT_7105323740
u64 *FUN_71017f50e0(void)
{
    if (!(DAT_7105323738 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_7105323738);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_7105323740 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_7105323738);
        }
    }
    return (u64*)&DAT_7105323740;
}
