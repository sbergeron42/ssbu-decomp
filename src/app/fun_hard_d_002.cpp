#include "types.h"

// HARD-tier FUN_* functions — 0x71000–0x710009 address range, batch hard-d-002
// Pool-d worker: misc networking/util helpers

// ---- External declarations -----------------------------------------------

extern "C" {
    extern u64  strlen(const char *s);
    extern void *memcpy(void *dst, const void *src, u64 n);
}

extern void FUN_710007a160(void);
extern u64  FUN_7100045fd0(u64, u32);
extern void FUN_71000322b0(u64, u64);
extern u64  FUN_7100044dd0(u64, u64, u32);
extern void FUN_7100047800(u64, u64, u32);
extern void FUN_7100044db0(u64, u64);
extern void FUN_71000397f0(s64);
extern void FUN_71000399d0(s64, u64);
extern void FUN_7100039580(s64, u64);
extern void FUN_71000b5a90(s32 *);
extern u32  FUN_71001602e0(u64);
extern void FUN_71000c9c60(s64, u32);

// ---- Functions ---------------------------------------------------------------

// 0x7100044d00 — assert two fields null; second call is tail-call (64 bytes)
void FUN_7100044d00(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xc8) != 0) {
        FUN_710007a160();
    }
    if (*(s64 *)(param_1 + 0xd0) != 0) {
        FUN_710007a160();
    }
}

// 0x7100059f60 — wrapper: pass field +0xb8 of param_3 to fn, forward result (48 bytes)
void FUN_7100059f60(u64 param_1, u64 param_2, s64 param_3)
{
    u64 uVar1 = FUN_7100045fd0(*(u64 *)(param_3 + 0xb8), 1);
    FUN_71000322b0(param_2, uVar1);
}

// 0x7100066060 — total byte length of string array at +0x50 (96 bytes)
s64 FUN_7100066060(s64 param_1, u32 param_2)
{
    s64 lVar2;
    u64 uVar3;
    u64 *puVar4;

    if ((s32)param_2 < 1) {
        lVar2 = 0;
    } else {
        lVar2 = 0;
        uVar3 = (u64)param_2;
        puVar4 = (u64 *)(param_1 + 0x50);
        do {
            u64 sVar1 = strlen((const char *)*puVar4++);
            lVar2 = lVar2 + (s64)sVar1 + 1;
            uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
    }
    return lVar2;
}

// 0x7100066600 — conditional insert then always update (96 bytes)
void FUN_7100066600(u64 param_1, u64 param_2, u64 param_3, u32 param_4)
{
    u64 uVar1 = FUN_7100044dd0(param_1, param_3, param_4 & 0xff);
    if ((uVar1 & 1) != 0) {
        FUN_7100047800(param_3, param_2, param_4);
    }
    FUN_7100044db0(param_1, param_2);
}

// 0x7100099520 — init three sub-objects at fixed offsets (64 bytes)
void FUN_7100099520(s64 param_1, u64 param_2)
{
    FUN_71000397f0(param_1 + 8);
    FUN_71000399d0(param_1 + 0x30, param_2);
    FUN_7100039580(param_1 + 0x4c, param_2);
}

// 0x71000b5a40 — state guard then memcpy 0x10 bytes from +0x18 (80 bytes)
// NOTE: ~35% — NX Clang tail-calls memcpy; upstream Clang 8 inlines it as LDP+STP
void FUN_71000b5a40(s32 *param_1, void *param_2)
{
    if (*param_1 != 5) {
        FUN_71000b5a90(param_1);
        *param_1 = 5;
    }
    memcpy(param_2, param_1 + 6, 0x10);
}

// 0x71000cf220 — convert param_2, store result into param_1+0x178 (48 bytes)
void FUN_71000cf220(s64 param_1, u64 param_2)
{
    s64 lVar1 = param_1 + 0x178;  // precompute so compiler saves it in x19 before the call
    u32 uVar1 = FUN_71001602e0(param_2);
    FUN_71000c9c60(lVar1, uVar1);
}
