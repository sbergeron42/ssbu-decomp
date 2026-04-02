#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-009
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int memcmp(const void *, const void *, u64);

// External data
extern s32 DAT_71052a90e8;
extern u32 DAT_71052a90f0;
extern s8  DAT_71052a90f8;
extern u8  DAT_71052a9100;

// External FUN_* forward declarations
extern void FUN_7100002540(u64);
extern void FUN_71000058b0(u64, u8 *);
extern s64  FUN_71000058c0(u8 *);
extern void FUN_7100005640(u8 *);
extern void FUN_7100027f90(void);
extern void FUN_7100026140(void);
extern void FUN_7100004780(void);
extern s32  FUN_710001f100(s64);
extern void FUN_710001e860(s64, u64);
extern s32  FUN_7100026170(u64, u64, u64);
extern void FUN_7100004200(u64, u64);
extern void FUN_710002a1f0(s64);
extern int  nnsocketFcntl(u64, s32, u32);

// Forward declaration for intra-file caller below
void FUN_7100005b40(void);

// ---- Functions ---------------------------------------------------------------

// 0x7100000250 — memcmp-like: byte-by-byte compare up to param_3 bytes (64 bytes)
u64 FUN_7100000250(s64 param_1, s64 param_2, s32 param_3)
{
    s64 lVar1;

    if (param_3 < 1) {
        return 1;
    }
    lVar1 = 0;
    do {
        if (*(s8 *)(param_1 + lVar1) != *(s8 *)(param_2 + lVar1)) {
            return 0;
        }
        lVar1 = lVar1 + 1;
    } while (lVar1 < param_3);
    return 1;
}

// 0x71000007c0 — string hash: djb2-variant, return hash % param_2 (64 bytes)
s32 FUN_71000007c0(u8 *param_1, u32 param_2)
{
    u8 bVar1;
    u32 uVar2;
    u32 uVar3;

    uVar2 = 0;
    do {
        uVar3 = uVar2;
        bVar1 = *param_1;
        param_1 = param_1 + 1;
        uVar2 = (u32)bVar1 + uVar3 * 0x492;
    } while (bVar1 != 0);
    uVar2 = 0;
    if (param_2 != 0) {
        uVar2 = uVar3 / param_2;
    }
    return uVar3 - uVar2 * param_2;
}

// 0x7100002690 — cleanup: null-guard, free *param_1, clear two fields (48 bytes)
void FUN_7100002690(u64 *param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    if (param_1 != (u64 *)0x0) {
        FUN_7100002540(*param_1);
        *param_1 = 0;
        param_1[3] = 0;
    }
}

// 0x7100002ac0 — reverse search: find last occurrence of param_2 in [param_1, +param_3) (64 bytes)
s8 *FUN_7100002ac0(s8 *param_1, s8 param_2, s64 param_3)
{
    s8 *pcVar1;

    if (-1 < param_3 + -1) {
        pcVar1 = param_1 + param_3 + -1;
        do {
            if (*pcVar1 == param_2) {
                return pcVar1;
            }
            pcVar1 = pcVar1 + -1;
        } while (param_1 <= pcVar1);
    }
    return (s8 *)0x0;
}

// 0x7100004720 — iterator: walk container via 24-byte stack state, return first non-null payload (96 bytes)
u64 FUN_7100004720(u64 param_1)
{
    s64 lVar1;
    u64 *puVar2;
    u8 auStack_28[24];

    FUN_71000058b0(param_1, auStack_28);
    do {
        lVar1 = FUN_71000058c0(auStack_28);
        if (lVar1 == 0) {
            return 0;
        }
        puVar2 = *(u64 **)(*(s64 *)(lVar1 + 0x18) + 0x10);
    } while (puVar2 == (u64 *)0x0);
    return *puVar2;
}

// 0x7100005878 — memcmp wrapper: return 1 if equal, 0 otherwise (32 bytes)
u64 FUN_7100005878(void *param_1, u64 param_2, void *param_3)
{
    int iVar1;

    iVar1 = memcmp(param_1, param_3, param_2);
    if (iVar1 != 0) {
        return 0;
    }
    return 1;
}

// 0x7100005b40 — cleanup: if global flag set, destruct DAT_71052a9100 and clear flag (32 bytes)
void FUN_7100005b40(void)
{
    if (DAT_71052a90f8 == '\x01') {
        FUN_7100005640(&DAT_71052a9100);
        DAT_71052a90f8 = '\0';
    }
}

// 0x7100000900 — refcount release: decrement counter, on zero run shutdown sequence (80 bytes)
void FUN_7100000900(void)
{
    if ((DAT_71052a90e8 != 0) && (DAT_71052a90e8 = DAT_71052a90e8 + -1, DAT_71052a90e8 == 0)) {
        FUN_7100027f90();
        FUN_7100005b40();
        if ((DAT_71052a90f0 & 1) != 0) {
            FUN_7100026140();
        }
        FUN_7100004780();
        DAT_71052a90f0 = 0;
    }
}

// 0x7100005a10 — swap pending ptr to +0x70, call update fn, conditionally flush (80 bytes)
s32 FUN_7100005a10(s64 param_1)
{
    s32 iVar1;

    if (*(s64 *)(param_1 + 0xa48) != 0) {
        *(s64 *)(param_1 + 0x70) = *(s64 *)(param_1 + 0xa48);
        *(u64 *)(param_1 + 0xa48) = 0;
    }
    iVar1 = FUN_710001f100(param_1);
    if (iVar1 != 0) {
        FUN_710001e860(param_1, 0);
    }
    return iVar1;
}

// 0x71000093f0 — bit test: return (field+0xe8 & param_2) != 0, or 0 if null (32 bytes)
u64 FUN_71000093f0(u64 param_1, s32 param_2)
{
    if (param_1 != 0) {
        param_1 = (u64)((*(u64 *)(param_1 + 0xe8) & (s64)param_2) != 0);
    }
    return param_1;
}

// 0x710000c8f0 — bool: if field+0xb70 non-null, return (sub+0x4024 == 2) (32 bytes)
bool FUN_710000c8f0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xb70) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 0xb70) + 0x4024) == 2;
    }
    return false;
}

// 0x710000c920 — bool: if field+0xb70 non-null, return (sub+0x4024 != 2) (32 bytes)
bool FUN_710000c920(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xb70) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 0xb70) + 0x4024) != 2;
    }
    return false;
}

// 0x710000e730 — delegate: call FUN_7100026170(p1,0,p2), conditionally call second fn (48 bytes)
s32 FUN_710000e730(u64 param_1, u64 param_2)
{
    s32 iVar1;

    iVar1 = FUN_7100026170(param_1, 0, param_2);
    if (iVar1 != 0) {
        FUN_7100004200(param_1, 1);
    }
    return iVar1;
}

// 0x7100013480 — cleanup: deref, check +0x194, call fn on +0x198 then clear (48 bytes)
void FUN_7100013480(s64 *param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    s64 lVar1;

    lVar1 = *param_1;
    if (*(s32 *)(lVar1 + 0x194) != 0) {
        FUN_710002a1f0(lVar1 + 0x198);
        *(u32 *)(lVar1 + 0x194) = 0;
    }
}

// 0x7100013730 — socket: set O_NONBLOCK (param_2!=0) or clear via nnsocketFcntl (32 bytes)
void FUN_7100013730(u64 param_1, s32 param_2)
{
    u32 uVar1;

    uVar1 = 2;
    if (param_2 != 0) {
        uVar1 = 0x802;
    }
    nnsocketFcntl(param_1, 4, uVar1);
}
