#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-003
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void FUN_7103754ef0(void **);

// External data
extern u8 PTR_LAB_7105185330[];
extern u8 DAT_7103390ac0[];
extern u8 DAT_7103390d10[];
extern u8 DAT_7103390e50[];
extern void *FUN_7103390cb0;

// ---- Functions ---------------------------------------------------------------

// 0x7103390960 — event dispatcher: switch on event type, construct closure, call via vtable (848 bytes)
void FUN_7103390960(s64 param_1)
{
    void ***pppuVar1;
    void (*pcVar2)();
    void **local_110;
    void *puStack_108;
    u64 local_100;
    s64 lStack_f8;
    void ***local_f0;
    void **local_e0;
    void *puStack_d8;
    u64 local_d0;
    s64 lStack_c8;
    void ***local_c0;
    void **local_b0;
    void (*pcStack_a8)();
    u64 local_a0;
    s64 lStack_98;
    void ***local_90;
    void **local_80;
    void *puStack_78;
    u64 local_70;
    s64 lStack_68;
    void ***local_60;
    void **appuStack_50[4];
    void ***local_30;

    switch (*(u32 *)(param_1 + 0xc)) {
    case 1:
        local_70 = 0;
        local_80 = (void **)PTR_LAB_7105185330;
        puStack_78 = (void *)DAT_7103390ac0;
        lStack_68 = param_1;
        local_60 = &local_80;
        FUN_7103754ef0((void **)&local_80);
        pppuVar1 = local_60;
        if (&local_80 == local_60) {
LAB_7103390a2c:
            pcVar2 = (void (*)())(*pppuVar1)[4];
            goto LAB_7103390a34;
        }
        break;
    default:
        local_30 = nullptr;
        FUN_7103754ef0((void **)appuStack_50);
        pppuVar1 = local_30;
        if ((void ***)appuStack_50 == local_30) goto LAB_7103390a2c;
        break;
    case 7:
        local_a0 = 0;
        local_b0 = (void **)PTR_LAB_7105185330;
        pcStack_a8 = (void (*)())&FUN_7103390cb0;
        lStack_98 = param_1;
        local_90 = &local_b0;
        FUN_7103754ef0((void **)&local_b0);
        pppuVar1 = local_90;
        if (&local_b0 == local_90) goto LAB_7103390a2c;
        break;
    case 0xe:
    case 0xf:
    case 0x10:
        local_d0 = 0;
        local_e0 = (void **)PTR_LAB_7105185330;
        puStack_d8 = (void *)DAT_7103390d10;
        lStack_c8 = param_1;
        local_c0 = &local_e0;
        FUN_7103754ef0((void **)&local_e0);
        pppuVar1 = local_c0;
        if (&local_e0 == local_c0) goto LAB_7103390a2c;
        break;
    case 0x12:
        local_100 = 0;
        local_110 = (void **)PTR_LAB_7105185330;
        puStack_108 = (void *)DAT_7103390e50;
        lStack_f8 = param_1;
        local_f0 = &local_110;
        FUN_7103754ef0((void **)&local_110);
        pppuVar1 = local_f0;
        if (&local_110 == local_f0) goto LAB_7103390a2c;
    }
    if (pppuVar1 == nullptr) {
        return;
    }
    pcVar2 = (void (*)())(*pppuVar1)[5];
LAB_7103390a34:
    pcVar2();
    return;
}
