#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-009
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: flag setters, nn::os wrappers, string utils, struct inits, ref-count

// ---- External declarations -----------------------------------------------

// nn::os SDK types (MessageQueue wrappers)
struct MessageQueueType;
namespace nn { namespace os {
    void SendMessageQueue(MessageQueueType *, u64);
    void JamMessageQueue(MessageQueueType *, u64);
}}

// Linked-list node remove (FUN_710001ebb0)
extern "C" void FUN_7100006870(s64 *, s64 *, s32);

// Ref-count globals (FUN_7100000900)
extern u64 DAT_71052a90e8;
extern u64 DAT_71052a90f0;
extern "C" void FUN_7100027f90();
extern "C" void FUN_7100005b40();
extern "C" void FUN_7100026140();
extern "C" void FUN_7100004780();

// ---- Functions ---------------------------------------------------------------

// 0x7100000250 — memcmp-like: compare param_3 bytes at two addresses
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

// 0x71000007c0 — hash: accumulate bytes * 0x492, return mod param_2
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

// 0x7100000900 — ref-count shutdown: decrement DAT_71052a90e8, teardown when zero
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

// 0x7100002ac0 — memrchr-like: scan backward from param_1+param_3-1 for param_2
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

// 0x710000c8f0 — check if nested ptr at param_1+0xb70, field+0x4024 == 2
u8 FUN_710000c8f0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xb70) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 0xb70) + 0x4024) == 2;
    }
    return 0;
}

// 0x710000c920 — check if nested ptr at param_1+0xb70, field+0x4024 != 2
u8 FUN_710000c920(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xb70) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 0xb70) + 0x4024) != 2;
    }
    return 0;
}

// 0x71000145a0 — check if *(param_2+0x8f0) != null and **ptr == param_1
u8 FUN_71000145a0(s64 param_1, s64 param_2)
{
    if (*(s64 **)(param_2 + 0x8f0) != (s64 *)0x0) {
        return **(s64 **)(param_2 + 0x8f0) == param_1;
    }
    return 0;
}

// 0x71000145c0 — check if *(param_2+0x8d0) != null and **ptr == param_1
u8 FUN_71000145c0(s64 param_1, s64 param_2)
{
    if (*(s64 **)(param_2 + 0x8d0) != (s64 *)0x0) {
        return **(s64 **)(param_2 + 0x8d0) == param_1;
    }
    return 0;
}

// 0x7100014fc0 — set field+0x9d8 if param_2 >= 0; else clear and mask out bit 6
void FUN_7100014fc0(s64 param_1, s64 param_2)
{
    if (-1 < param_2) {
        *(s64 *)(param_1 + 0x9d8) = param_2;
        *(u32 *)(param_1 + 0xa08) = *(u32 *)(param_1 + 0xa08) | 0x40;
        return;
    }
    *(u64 *)(param_1 + 0x9d8) = 0;
    *(u32 *)(param_1 + 0xa08) = *(u32 *)(param_1 + 0xa08) & 0xffffffbf;
}

// 0x7100017450 — to-uppercase loop: ASCII lowercase [a-z] → [A-Z], up to param_3 bytes
void FUN_7100017450(u8 *param_1, u8 *param_2, s64 param_3)
{
    u8 bVar1;
    u8 bVar2;

    if (param_3 != 0) {
        do {
            bVar2 = *param_2;
            bVar1 = bVar2 - 0x20;
            if (0x19 < (u8)(bVar2 - 0x61)) {
                bVar1 = bVar2;
            }
            *param_1 = bVar1;
            if (*param_2 == 0) {
                return;
            }
            param_2 = param_2 + 1;
            param_1 = param_1 + 1;
            param_3 = param_3 + -1;
        } while (param_3 != 0);
    }
}

// 0x710001ebb0 — linked-list search: find node with key == param_1, remove and return 1
u64 FUN_710001ebb0(s64 param_1, s64 *param_2)
{
    s64 *plVar1;

    if (param_2 != (s64 *)0x0) {
        for (plVar1 = (s64 *)*param_2; plVar1 != (s64 *)0x0; plVar1 = (s64 *)plVar1[2]) {
            if (*plVar1 == param_1) {
                FUN_7100006870(param_2, plVar1, 0);
                return 1;
            }
        }
    }
    return 0;
}

// 0x7100031140 — init struct with packed constants (audio/format descriptor)
void FUN_7100031140(u32 *param_1)
{
    *param_1 = 0x20202;
    *(u64 *)(param_1 + 1) = 0xc47a0000002a0100ULL;
    *(u64 *)(param_1 + 3) = 0x447a0000;
}

// 0x71000311e0 — init byte array: set version/flag fields
void FUN_71000311e0(u8 *param_1)
{
    param_1[1] = 1;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 1;
    *param_1 = *param_1 & 0xfe;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0xf;
}

// 0x7100031210 — init mixed u16/u64 struct (float 1.0 sentinel at offset 12)
void FUN_7100031210(u16 *param_1)
{
    *(u64 *)(param_1 + 6) = 0x3f80000000000000ULL;
    param_1[1] = param_1[1] & 0xfff0;
    *(u64 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 0xc) = 0;
    *param_1 = 0x500;
}

// 0x7100031250 — init mixed u16/u32/u8 struct (two identical sub-descriptors)
void FUN_7100031250(u16 *param_1)
{
    *param_1 = 0xff01;
    *(u8 *)(param_1 + 1) = 0xff;
    *(u32 *)(param_1 + 4) = 0x7000000;
    *(u8 *)(param_1 + 6) = 0;
    param_1[2] = param_1[2] & 0xfff0;
    *(u32 *)(param_1 + 0xc) = 0x7000000;
    *(u8 *)(param_1 + 0xe) = 0;
}

// 0x7100031850 — zero-fill 9 u64 fields in out-of-order sequence
void FUN_7100031850(u64 *param_1)
{
    param_1[7] = 0;
    param_1[8] = 0;
    *param_1 = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x71001133a0 — write 0xffff + param_2 to u16 pair at +0xa38/+0xa3a, set flag bit 1
void FUN_71001133a0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0xa38) = 0xffff;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133c0 — write param_3/param_2 to u16 pair at +0xa38/+0xa3a, set flag bit 1
void FUN_71001133c0(s64 param_1, u16 param_2, u16 param_3)
{
    *(u16 *)(param_1 + 0xa38) = param_3;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133e0 — store bit0 of param_2 at byte +0xa3c, set flag bit 2
void FUN_71001133e0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3c) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 4;
}

// 0x7100113400 — store bit0 of param_2 at byte +0xa3d, set flag bit 3
void FUN_7100113400(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3d) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 8;
}

// 0x7100113480 — store bit0 of param_2 at byte +0x9ca, set flag bit 0x1000
void FUN_7100113480(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9ca) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x1000;
}

// 0x71001134a0 — store bit0 of param_2 at byte +0x9cb, set flag bit 0x2000
void FUN_71001134a0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9cb) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x2000;
}

// 0x71001136c0 — store bit0 of param_2 at byte +0xa08, set flag bit 0x100000
void FUN_71001136c0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa08) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x100000;
}

// 0x710012eb20 — write param_2 to two u16 offsets +0x256/600, set flag bit 0
void FUN_710012eb20(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x256) = param_2;
    *(u16 *)(param_1 + 600) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 1;
}

// 0x710013bc98 — nn::os::SendMessageQueue wrapper, return 1
u64 FUN_710013bc98(MessageQueueType *param_1, u64 param_2)
{
    nn::os::SendMessageQueue(param_1, param_2);
    return 1;
}

// 0x710013bd08 — nn::os::JamMessageQueue wrapper, return 1
u64 FUN_710013bd08(MessageQueueType *param_1, u64 param_2)
{
    nn::os::JamMessageQueue(param_1, param_2);
    return 1;
}
