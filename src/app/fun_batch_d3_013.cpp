#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-013
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    u64 strlen(const char *);
    char *strncpy(char *, const char *, u64);
}

// External data
extern u8 PTR_DAT_71052a37b0[] HIDDEN;

// External FUN_* forward declarations
extern s8  *FUN_7100048db0(u64);

namespace nn { namespace util {
    int SNPrintf(char *, s64, const char *, ...);
} }

// Forward declaration (defined later in this file)
s8 *FUN_71000666b0(s8 *param_1);

// ---- Functions ---------------------------------------------------------------

// 0x71000626a0 — vtable dispatch at +0x50 (no args), return 0 or param_1[0x28] (32 bytes)
s64 FUN_71000626a0(s64 *param_1, s32 param_2)
{
    (*(void (**)(void))(*param_1 + 0x50))();
    if (param_2 != 0) {
        return 0;
    }
    return param_1[0x28];
}

// 0x7100064450 — conditional store: if param_3==0 write via deref, else at offset+4 (48 bytes)
void FUN_7100064450(u32 param_1, s64 param_2, s32 param_3)
{
    if (param_3 != 1) {
        if (param_3 == 0) {
            **(u32 **)(param_2 + 0x150) = param_1;
        }
        *(u16 *)(param_2 + 0x114) = *(u16 *)(param_2 + 0x114) | 4;
        return;
    }
    *(u32 *)(*(s64 *)(param_2 + 0x150) + 4) = param_1;
    *(u16 *)(param_2 + 0x114) = *(u16 *)(param_2 + 0x114) | 4;
}

// 0x7100065310 — ctor: set vtable, clear field, set -1, strdup param_2 into field (48 bytes)
void FUN_7100065310(s64 *param_1, u64 param_2)
{
    u8 *puVar1;
    s64 lVar2;

    puVar1 = PTR_DAT_71052a37b0 + 0x10;
    param_1[2] = 0;
    *param_1 = (s64)puVar1;
    param_1[1] = -1;
    lVar2 = (s64)FUN_71000666b0((s8 *)param_2);
    param_1[2] = lVar2;
}

// 0x7100066040 — bool: null-guard deref-chain, return (*(*+0x68) != '\0') (16 bytes)
u64 FUN_7100066040(u64 param_1)
{
    if (param_1 != 0) {
        param_1 = (u64)(**(s8 **)(param_1 + 0x68) != '\0');
    }
    return param_1;
}

// 0x7100066660 — write float as int-truncated (into param_4) and float (into param_3) (48 bytes)
void FUN_7100066660(float param_1, float param_2, u64 *param_3, u64 *param_4)
{
    *param_4 = 0;
    *(s32 *)(param_4 + 1) = (s32)param_1;
    *(s32 *)((s64)param_4 + 0xc) = (s32)param_2;
    *param_3 = 0;
    *(float *)(param_3 + 1) = param_1;
    *(float *)((s64)param_3 + 0xc) = param_2;
}

// 0x71000666b0 — strdup: allocate and copy string via strlen+alloc+strncpy (64 bytes)
s8 *FUN_71000666b0(s8 *param_1)
{
    u64 sVar1;
    s8 *__dest;

    sVar1 = strlen((const char *)param_1);
    __dest = (s8 *)FUN_7100048db0(sVar1 + 1);
    strncpy((char *)__dest, (const char *)param_1, sVar1 + 1);
    return __dest;
}

// 0x7100077eb0 — delegate: nn::util::SNPrintf with "%s_%d" format (32 bytes)
void FUN_7100077eb0(s8 *param_1, s32 param_2, u64 param_3, s64 param_4)
{
    nn::util::SNPrintf((char *)param_1, (s64)param_2, "%s_%d", param_3,
                       (u64)*(u32 *)(param_4 + 4));
}

// 0x7100078970 — conditional float setter: update +0x150, OR flag at +0x158 (32 bytes)
void FUN_7100078970(float param_1, s64 param_2)
{
    if (*(float *)(param_2 + 0x150) != param_1) {
        *(float *)(param_2 + 0x150) = param_1;
        *(u8 *)(param_2 + 0x158) = *(u8 *)(param_2 + 0x158) | 1;
    }
}

// 0x71000789e0 — vtable dispatch at +0x30 (self, 0), return result+1 (32 bytes)
s32 FUN_71000789e0(s64 *param_1)
{
    s32 iVar1;

    iVar1 = (*(s32 (**)(s64 *, u64))(*param_1 + 0x30))(param_1, 0);
    return iVar1 + 1;
}

// 0x7100078b20 — init: set sentinel, float-pair constants, clear 4 fields (48 bytes)
void FUN_7100078b20(u64 *param_1)
{
    *param_1 = 0xffffffffffffffff;
    param_1[1] = 0x3f80000000000000;
    *(u16 *)(param_1 + 7) = 0xff00;
    param_1[2] = 0x3f800000;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
}

// 0x7100078bc0 — double-deref vtable at +0x20, multiply float by result (32 bytes)
float FUN_7100078bc0(s64 param_1)
{
    s32 iVar1;

    iVar1 = (*(s32 (**)())(*(s64 *)*(s64 **)(param_1 + 0x28) + 0x20))();
    return *(float *)(param_1 + 0xc) * (float)iVar1;
}

// 0x7100078c00 — double-deref vtable at +0x28, multiply float by result (32 bytes)
float FUN_7100078c00(s64 param_1)
{
    s32 iVar1;

    iVar1 = (*(s32 (**)())(*(s64 *)*(s64 **)(param_1 + 0x28) + 0x28))();
    return *(float *)(param_1 + 0x10) * (float)iVar1;
}

// 0x7100078c40 — double-deref vtable at +0x30, multiply float by result (32 bytes)
float FUN_7100078c40(s64 param_1)
{
    s32 iVar1;

    iVar1 = (*(s32 (**)())(*(s64 *)*(s64 **)(param_1 + 0x28) + 0x30))();
    return *(float *)(param_1 + 0x10) * (float)iVar1;
}

// 0x7100078f80 — zero-init: clear 23 u64 fields (non-sequential) (96 bytes)
void FUN_7100078f80(u64 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 1) = 0;
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
}

// 0x710007a9d0 — callback invoke: call param_2(param_1+0x408, param_1+0x390), then sentinel (32 bytes)
void FUN_710007a9d0(s64 param_1, void (*param_2)(s64, s64))
{
    param_2(param_1 + 0x408, param_1 + 0x390);
    *(u64 *)(param_1 + 0x408) = 0xffffffffffffffff;
}
