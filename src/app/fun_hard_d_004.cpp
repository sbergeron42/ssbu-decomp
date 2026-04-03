#include "types.h"

// HARD-tier FUN_* functions — 0x71000 address range, batch hard-d-004
// Pool-d worker: struct init, field ops, list search

// ---- External declarations -----------------------------------------------

extern void FUN_7100048dd0(s64 *);
extern void FUN_7100048db0(u64 *, s64);
extern f32  FUN_7100057760(void *, void *, u64);

// ---- Functions ---------------------------------------------------------------

// 0x7100031ae0 — zero 29 u64 slots of struct (64 bytes)
void FUN_7100031ae0(u64 *param_1)
{
    param_1[0x1b] = 0; param_1[0x1c] = 0;
    param_1[0]    = 0;
    param_1[0x19] = 0; param_1[0x1a] = 0;
    param_1[0x17] = 0; param_1[0x18] = 0;
    param_1[0x15] = 0; param_1[0x16] = 0;
    param_1[0x13] = 0; param_1[0x14] = 0;
    param_1[0x11] = 0; param_1[0x12] = 0;
    param_1[0x0f] = 0; param_1[0x10] = 0;
    param_1[0x0d] = 0; param_1[0x0e] = 0;
    param_1[0x0b] = 0; param_1[0x0c] = 0;
    param_1[9]    = 0; param_1[10]   = 0;
    param_1[7]    = 0; param_1[8]    = 0;
    param_1[5]    = 0; param_1[6]    = 0;
    param_1[3]    = 0; param_1[4]    = 0;
    param_1[1]    = 0; param_1[2]    = 0;
}

// 0x7100031190 — init descriptor: set magic, clear flags (80 bytes)
void FUN_7100031190(u32 *param_1)
{
    *param_1 = 0x3020002;
    *(u16 *)(param_1 + 1) = *(u16 *)(param_1 + 1) & 0xfff0;
    *(u16 *)((s64)param_1 + 0x1a) = *(u16 *)((s64)param_1 + 0x1a) & 0xfffe;
    *(u8 *)(param_1 + 6) = 1;
    param_1[4] = 0;
    *(u64 *)(param_1 + 2) = 0;
    *(u8 *)((s64)param_1 + 6) = 0;
    param_1[7] = 0xffffffff;
}

// 0x7100031490 — init event: set enable flag, copy handle, set type and options (80 bytes)
void FUN_7100031490(u8 *param_1, u64 param_2, u32 param_3, u32 param_4)
{
    u8 bVar1;
    u32 uVar2;

    *param_1 = 1;
    *(u64 *)(param_1 + 8) = param_2;
    bVar1 = param_1[1] | 5;
    if ((param_3 & 1) == 0) {
        bVar1 = param_1[1] & 0xfe | 4;
    }
    param_1[1] = bVar1;
    uVar2 = 0x1f;
    if ((param_4 & 0x20) != 0) {
        uVar2 = 0x20;
    }
    *(u32 *)(param_1 + 4) = uVar2;
    *(u64 *)(param_1 + 0xd0) = 0;
}

// 0x7100044d60 — scatter-copy 8 u64s from array to struct offsets (80 bytes)
void FUN_7100044d60(s64 param_1, u64 *param_2)
{
    u64 uVar1;

    uVar1 = param_2[1];
    *(u64 *)(param_1 + 0x28) = param_2[3];
    *(u64 *)(param_1 + 0x18) = uVar1;
    uVar1 = param_2[5];
    *(u64 *)(param_1 + 0x48) = param_2[7];
    *(u64 *)(param_1 + 0x38) = uVar1;
    uVar1 = *param_2;
    *(u64 *)(param_1 + 0x20) = param_2[2];
    *(u64 *)(param_1 + 0x10) = uVar1;
    uVar1 = param_2[4];
    *(u64 *)(param_1 + 0x40) = param_2[6];
    *(u64 *)(param_1 + 0x30) = uVar1;
}

// 0x7100059f90 — build render param struct from two sources (80 bytes)
void FUN_7100059f90(u64 *param_1, s64 param_2, u64 param_3)
{
    u8 bVar1;

    *param_1       = *(u64 *)(*(s64 *)(param_2 + 0xb8) + 0x80);
    param_1[1]     = (u64)(param_2 + 0x50);
    param_1[2]     = *(u64 *)(param_2 + 0xb0);
    *(u32 *)(param_1 + 3) = 0x3f800000;
    *(u8 *)((s64)param_1 + 0x1c) = *(u8 *)(param_2 + 0x18e) & 1;
    *(u8 *)((s64)param_1 + 0x1d) = *(u8 *)(param_2 + 0x18e) >> 1 & 1;
    bVar1 = *(u8 *)(param_2 + 0x18e);
    *(u8 *)((s64)param_1 + 0x1f) = 0;
    param_1[4]     = param_3;
    *(u8 *)((s64)param_1 + 0x1e) = bVar1 >> 2 & 1;
}

// 0x7100045170 — circular list: relink param_2 after param_1's successor (64 bytes)
void FUN_7100045170(s64 *param_1, s64 *param_2)
{
    s64 *plVar1;
    s64 lVar2;

    if (param_1 != param_2) {
        plVar1 = (s64 *)param_2[1];
        lVar2 = *plVar1;
        *(s64 **)(*param_2 + 8) = plVar1;
        *plVar1 = *param_2;
        *(s64 **)(lVar2 + 8) = param_2;
        *param_2 = lVar2;
        FUN_7100048dd0(param_2);
        return;
    }
    if (param_2 != nullptr) {
        FUN_7100048dd0(param_2);
    }
}

// 0x7100081a30 — tree search: find node matching 48-bit key (80 bytes)
void FUN_7100081a30(s64 *param_1, u32 param_2, s64 param_3, u32 param_4)
{
    s64 lVar1;
    u64 uVar2;
    u64 uVar3;

    lVar1 = *param_1;
    if (lVar1 != 0) {
        uVar2 = ((u64)param_3 << 0x30) | (((u64)param_4 << 32 | (u64)param_2) & 0xffffffffffffULL);
        do {
            while (uVar3 = *(u64 *)(lVar1 + 0x30), uVar2 > uVar3 || uVar3 == uVar2) {
                if (uVar2 <= uVar3) {
                    return;
                }
                lVar1 = *(s64 *)(lVar1 + 0x28);
                if (lVar1 == 0) {
                    return;
                }
            }
            lVar1 = *(s64 *)(lVar1 + 0x20);
        } while (lVar1 != 0);
    }
}

// 0x7100070890 — swap or pass-through float pair based on vtable flag (96 bytes)
void FUN_7100070890(f32 param_1, f32 param_2, s64 *param_3)
{
    s32 iVar1;
    f32 fVar2;

    iVar1 = (**(s32 (**)(void))(*param_3 + 0x60))();
    if (iVar1 == 1) {
        fVar2 = 1.0f - param_2;
        param_2 = 1.0f - param_1;
        *(f32 *)(param_3 + 1) = fVar2;
    } else {
        if (iVar1 != 0) {
            return;
        }
        *(f32 *)(param_3 + 1) = param_1;
    }
    *(f32 *)((s64)param_3 + 0xc) = param_2;
}

// 0x7100047c90 — string search in circular list: compare up to 32 chars (112 bytes)
s64 FUN_7100047c90(s64 param_1, s64 param_2)
{
    char cVar1;
    s64 lVar2;
    u64 uVar3;

    lVar2 = *(s64 *)(param_1 + 8);
    do {
        if (lVar2 == param_1) {
            return 0;
        }
        uVar3 = 0;
        while (cVar1 = *(char *)(*(s64 *)(lVar2 + 0x20) + uVar3),
               cVar1 == *(char *)(param_2 + uVar3)) {
            if ((cVar1 == '\0') || (uVar3 = uVar3 + 1, 0x1f < uVar3)) {
                return lVar2 - 8;
            }
        }
        lVar2 = *(s64 *)(lVar2 + 8);
    } while (true);
}
