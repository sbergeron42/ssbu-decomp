#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-050
// Pool-d worker: misc functions 0x71001*-0x71033* ranges
// FUN_71031b97bc FUN_71031bb28c FUN_71031bdeac FUN_71031bf6fc FUN_71031c267c
// FUN_710317a3e8 FUN_71033c2258 FUN_71033cbda0 FUN_7103582b00 FUN_71036e5730
// FUN_71001683a0 FUN_710065f6b0

extern "C" {
    __attribute__((noreturn)) void abort(void);
}

// ---- External declarations ----

extern void FUN_71001352b0(u64);
extern void FUN_71000b1b90(void);
extern s64  FUN_7100130810(void *, u64);
extern void FUN_7100168f10(s64, u64);
extern void FUN_7101f44910(void *, int, u64, int, u32);
extern void FUN_7103359b40(void);
extern void FUN_7103359c4c(void);
extern void FUN_71037786c0(u64);
extern void FUN_71037790a0(u64);

// ---- 0x710317 ----

// 0x710317a3e8 — abort wrapper (72B)
void FUN_710317a3e8(void) {
    abort();
}

// ---- 0x71031b-0x71031c range — vtable call wrappers ----

// 0x71031b97bc — vtable call at +0x18 (84B)
u64 FUN_71031b97bc(s64 *param_1) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*param_1 + 0x18))();
}

// 0x71031bb28c — vtable call at +0x18 (84B)
u64 FUN_71031bb28c(s64 *param_1) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*param_1 + 0x18))();
}

// 0x71031bdeac — vtable call at +0x18 (84B)
u64 FUN_71031bdeac(s64 *param_1) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*param_1 + 0x18))();
}

// 0x71031bf6fc — vtable call at +0x18 (84B)
u64 FUN_71031bf6fc(s64 *param_1) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*param_1 + 0x18))();
}

// 0x71031c267c — vtable call at +0x18 (84B)
u64 FUN_71031c267c(s64 *param_1) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*param_1 + 0x18))();
}

// ---- 0x71033 range ----

// 0x71033c2258 — call FUN_7101f44910 and return 0 (64B)
extern void FUN_7101f44910(void *, int, u64, int, u32);
u64 FUN_71033c2258(s64 param_1, void *param_2) {
    FUN_7101f44910(param_2, 0, *(u64 *)(param_1 + 0x50), 1, 0xffffffff);
    return 0;
}

// 0x71033cbda0 — vtable call at +0x108, return ~result & 1 (96B)
u32 FUN_71033cbda0(u64 param_1, s64 param_2) {
    s64 *plVar2 = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x50);
    u32 uVar1 = (*reinterpret_cast<u32(*)(s64 *, u32)>((*reinterpret_cast<s64 **>(plVar2))[0x108/8]))(plVar2, 0x20000004);
    return ~uVar1 & 1;
}

// ---- 0x71035 range ----

// 0x7103582b00 — vtable call at +0x240, return iVar > 0xc (96B)
bool FUN_7103582b00(u64 param_1, u64 *param_2) {
    s32 iVar1 = (*reinterpret_cast<s32(**)()>(*(s64 *)*param_2 + 0x240))();
    return 0xc < iVar1;
}

// ---- 0x71036 range ----

// 0x71036e5730 — vtable call at +0x108 then deref +0x128 (80B)
u8 FUN_71036e5730(s64 *param_1) {
    s64 lVar1 = (*reinterpret_cast<s64(*)(s64*)>((*reinterpret_cast<s64 **>(*param_1))[0x108/8]))(param_1);
    return *(u8 *)(*(s64 *)(lVar1 + 8) + 0x128);
}

// ---- 0x71001 range ----

// 0x71001683a0 — create+init from module instance (176B)
extern u64 *PTR_DAT_71052a50b0;
s64 FUN_71001683a0(void) {
    u64 uVar3 = *PTR_DAT_71052a50b0;
    FUN_71000b1b90();
    s64 lVar2 = FUN_7100130810((void *)0x7220, 0);
    if (lVar2 != 0) {
        FUN_7100168f10(lVar2, uVar3);
    }
    return lVar2;
}

// ---- 0x71006 range ----

// 0x710065f6b0 — bit-set/test in a large bit array (128B)
void FUN_710065f6b0(s64 param_1, u16 *param_2, u32 param_3) {
    u16 uVar2 = *param_2;
    if ((param_3 & 1) != 0) {
        if (uVar2 != 0) {
            if (0x11c < uVar2) { abort(); }
            if ((*(u64 *)(*(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8) + 0x968) &
                 (1ULL << ((u64)uVar2 & 0x3f))) != 0) {
                goto do_set;
            }
        }
        return;
    }
    if (uVar2 >= 0x11d) { abort(); }
do_set:
    {
        s64 lVar1 = *(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8);
        *(u64 *)(lVar1 + 0x1b0) = *(u64 *)(lVar1 + 0x1b0) | (1ULL << ((u64)uVar2 & 0x3f));
    }
}
