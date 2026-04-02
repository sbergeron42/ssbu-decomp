#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-003
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8  PTR_DAT_71052a4ec0[];
extern u8  PTR_FUN_71052a5728[];
extern u8  PTR_DAT_71052a5868[];
extern u8  PTR_DAT_71052a5870[];
extern u8  PTR_DAT_71052a5970[];
extern u8  PTR_DAT_71052a5d00[];
extern u8  DAT_710449be6f;

// External FUN_* forward declarations
extern u64  FUN_71000b1b90();
extern s64  FUN_7100130810(u64, u64);
extern void FUN_71000baa20();
extern void FUN_71000bce50(s64 *, s64);
extern u64  FUN_71000bb680();
extern void FUN_7100156220(s64);
extern void FUN_7100168450(s64, u32);
extern void FUN_710016df20(s64, u64);
extern void FUN_710016e170(s64, u64);
extern void FUN_7100170d50(s64, u64);
extern void FUN_71001712c0(s64, u64);
extern void FUN_71001b1870();
extern void FUN_71001b6a50(s64 *);
extern void FUN_71001b68a0(s64 *, s32);
extern s64  FUN_71001f2ba0(u64, const char *, s32);
extern void FUN_71001dd4a0(s64 *, u64);

// ---- Functions ---------------------------------------------------------------

// 0x7100149540 — ctor: parent init, clear +0xec/+0xf0, set vtable (128 bytes)
void FUN_7100149540(s64 *param_1)
{
    u8 *puVar1;

    FUN_71000baa20();
    puVar1 = PTR_DAT_71052a4ec0;
    *(u8 *)((s64)param_1 + 0xec) = 0;
    param_1[0x1e] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
}

// 0x7100161d00 — delegate: forward sub-object at +0x60 to FUN_7100156220 at +0xa4c (176 bytes)
void FUN_7100161d00(s64 param_1)
{
    FUN_7100156220(*(s64 *)(param_1 + 0x60) + 0xa4c);
}

// 0x7100168310 — factory: alloc 0x18-byte object, init with FUN_7100168450 (144 bytes)
s64 FUN_7100168310(u64 param_1, u32 param_2)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x18, uVar1);
    if (lVar2 != 0) {
        FUN_7100168450(lVar2, param_2);
    }
    return lVar2;
}

// 0x710016b5f0 — factory: alloc 0x70-byte object, init with FUN_710016df20 (144 bytes)
s64 FUN_710016b5f0(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x70, uVar1);
    if (lVar2 != 0) {
        FUN_710016df20(lVar2, param_1);
    }
    return lVar2;
}

// 0x710016b680 — factory: alloc 0x70-byte object, init with FUN_71001712c0 (144 bytes)
s64 FUN_710016b680(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x70, uVar1);
    if (lVar2 != 0) {
        FUN_71001712c0(lVar2, param_1);
    }
    return lVar2;
}

// 0x710016b710 — factory: alloc 0x310-byte object, init with FUN_710016e170 (144 bytes)
s64 FUN_710016b710(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x310, uVar1);
    if (lVar2 != 0) {
        FUN_710016e170(lVar2, param_1);
    }
    return lVar2;
}

// 0x710016bbc0 — factory: alloc 0x68-byte object, init with FUN_7100170d50 (160 bytes)
s64 FUN_710016bbc0(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x68, uVar1);
    if (lVar2 != 0) {
        FUN_7100170d50(lVar2, param_1);
    }
    return lVar2;
}

// 0x71001a0590 — state check, time-delta calc, set vtable+name ptr (208 bytes)
u64 FUN_71001a0590(s64 param_1)
{
    s32  iVar1;
    s64  lVar2;
    s64 *plVar3;
    s64  lVar4;
    s64  lVar5;
    s64  local_30[2];

    iVar1 = **(s32 **)(param_1 + 0x78);
    if (iVar1 == 1) {
        return 5;
    }
    if (((u32)(iVar1 - 2) < 3) &&
        (FUN_71000bce50(local_30, (s64)(*(s32 **)(param_1 + 0x78) + 1)),
         local_30[0] != 0)) {
        return 1;
    }
    lVar4 = *(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0x70) + 0xa0) + 0x58);
    lVar5 = *(s64 *)(param_1 + 0x58);
    plVar3 = (s64 *)FUN_71000bb680();
    lVar2 = 0;
    if (*plVar3 != 0) {
        lVar2 = (lVar4 - lVar5) / *plVar3;
    }
    if (0 < lVar2) {
        *(u64 *)(param_1 + 0x58) = *(u64 *)(*(s64 *)(*(s64 *)(param_1 + 0x70) + 0xa0) + 0x58);
    }
    *(u8 **)(param_1 + 0x30) = PTR_FUN_71052a5728;
    *(u64 *)(param_1 + 0x38) = 0;
    *(const char **)(param_1 + 0x40) = "ProcessConnectionRequestJob::SendConnectionResponse";
    return 0;
}

// 0x71001d4640 — conditional: return stored field or compute time offset (128 bytes)
s64 FUN_71001d4640(s64 param_1)
{
    s64 local_18;

    if (*(s32 *)(param_1 + 0x28) != 0) {
        return *(s64 *)(param_1 + 0x20);
    }
    if (*PTR_DAT_71052a5868 == '\0') {
        FUN_71001b6a50(&local_18);
    } else {
        FUN_71001b68a0(&local_18, 0);
    }
    *(s64 *)PTR_DAT_71052a5870 = local_18;
    return ((local_18 - *(s64 *)(param_1 + 0x10)) - *(s64 *)(param_1 + 0x18)) +
           *(s64 *)(param_1 + 0x20);
}

// 0x71001d6930 — buffer resize: grow or shrink range at +0x10/+0x18 (128 bytes)
s64 FUN_71001d6930(s64 param_1, u64 param_2)
{
    s64  lVar1;
    u64  uVar2;
    s64 *plVar3;

    plVar3 = (s64 *)(param_1 + 0x10);
    lVar1 = *plVar3;
    uVar2 = (u64)(*(s64 *)(param_1 + 0x18) - lVar1);
    if (uVar2 < param_2) {
        FUN_71001dd4a0(plVar3, param_2 - uVar2);
        return *plVar3;
    }
    if (param_2 < uVar2) {
        *(u64 *)(param_1 + 0x18) = (u64)lVar1 + param_2;
    }
    return lVar1;
}

// 0x71001d76e0 — vtable swap: set dtor-vtable, call FUN_71001b1870 if field[2] set (160 bytes)
void FUN_71001d76e0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5d00 + 0x10);
    if (param_1[2] != 0) {
        FUN_71001b1870();
    }
    *param_1 = (s64)(PTR_DAT_71052a5970 + 0x10);
}

// 0x71001e9f20 — delegate: FUN_71001f2ba0 with DAT string and zero flags (176 bytes)
void FUN_71001e9f20(u64 param_1)
{
    FUN_71001f2ba0(param_1, (const char *)&DAT_710449be6f, 0);
}
