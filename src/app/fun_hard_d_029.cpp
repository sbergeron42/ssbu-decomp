#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-029
// Pool-d worker: list-node move, vtx-desc init, texture-slot checker, stream-entry appender,
//                BT/HID report sender (192B/208B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a2330 HIDDEN;

// ---- External functions --------------------------------------------------

extern u16 FUN_71002276f0(u32);
extern s32 FUN_71002262a0(s64, void *);

extern "C" {
    void *memcpy(void *, const void *, u64);
}

// ---- Functions ---------------------------------------------------------------

// 0x71000069b0 — remove node from src doubly-linked list, insert into dst after insert_after (192 bytes)
void FUN_71000069b0(s64 *src_head, s64 node, s64 *dst_head, s64 insert_after)
{
    if (node == 0 || src_head[3] == 0) {
        return;
    }
    s64 next = *(s64 *)(node + 0x10);
    if (*src_head == node) {
        *src_head = next;
        if (next == 0) {
            src_head[1] = 0;
        } else {
            *(s64 *)(next + 8) = 0;
        }
    } else {
        *(s64 *)(*(s64 *)(node + 8) + 0x10) = next;
        if (next == 0) {
            src_head[1] = *(s64 *)(node + 8);
        } else {
            *(s64 *)(next + 8) = *(s64 *)(node + 8);
        }
    }
    src_head[3]--;
    s64 *plVar3;
    if (dst_head[3] == 0) {
        *dst_head = node;
        *(s64 *)(node + 8)    = 0;
        *(s64 *)(node + 0x10) = 0;
        plVar3 = dst_head + 1;
    } else {
        s64 next_node = *(s64 *)(insert_after + 0x10);
        *(s64 *)(node + 8)    = insert_after;
        *(s64 *)(node + 0x10) = next_node;
        s64 *plVar1 = dst_head + 1;
        if (next_node != 0) {
            plVar1 = (s64 *)(next_node + 8);
        }
        *plVar1 = node;
        plVar3 = dst_head + 1;
    }
    *plVar3 = node;
    dst_head[3]++;
}

// 0x710003ac40 — vertex/draw-call descriptor init: set vtable, compute index range and stride (192 bytes)
void FUN_710003ac40(s64 *param_1, u32 param_2, s32 param_3, s32 param_4)
{
    *(u32 *)(param_1 + 3)         = param_2;
    *(u32 *)((s64)param_1 + 0x1c) = 2;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (s64)(PTR_DAT_71052a2330 + 0x10);

    u32 uVar1 = (u32)(param_4 + 1);
    *(s32 *)(param_1 + 8) = param_4;
    *(s32 *)(param_1 + 4) = param_3;
    *(u32 *)((s64)param_1 + 0x24) = uVar1;
    *(u32 *)(param_1 + 5) = 0;

    u64 uVar5;
    u32 uVar6;
    u32 uVar3 = uVar1;
    if (param_3 == 2) {
        uVar5 = (u64)uVar3;
        uVar6 = ((s32)uVar3 > 0xffff) ? 2u : 1u;
    } else if (param_3 == 3) {
        uVar3 = (u32)(param_4 * 3);
        uVar5 = (u64)uVar3;
        uVar6 = ((s32)uVar3 > 0xffff) ? 2u : 1u;
    } else {
        uVar5 = 0;
        uVar6 = 1;
    }
    *(u32 *)((s64)param_1 + 0x1c) = uVar6;

    s64 lVar2 = 0;
    if (param_2 & 1) lVar2 += 0xc;
    if (param_2 & 2) lVar2 += 0xc;
    if (param_2 & 4) lVar2 += 8;

    *(s32 *)(param_1 + 5) = (s32)uVar5;
    param_1[6] = lVar2 * (s32)uVar1;
    param_1[7] = (s64)((uVar5 >> 31 ? 0xfffffffc00000000ULL : 0) | (uVar5 << 2));
}

// 0x7100053c10 — count texture slots with special format types (192 bytes)
s32 FUN_7100053c10(s64 param_1, s32 param_2)
{
    u32 uVar4 = *(u32 *)(param_1 + 0x14) & 3;
    u32 uVar2 = (*(u32 *)(param_1 + 0x14) >> 4) & 3;
    if (uVar4 < uVar2) {
        uVar2 = uVar4;
    }
    if (uVar2 == 0) {
        return 0;
    }
    s64 lVar1 = *(s64 *)(param_1 + 0x18)
              + (s64)(u64)(*(u32 *)(param_1 + 0x10) & 3) * 0x10
              + (s64)(u64)((*(u32 *)(param_1 + 0x10) >> 2) & 3) * 0x14;

    u32 t0 = (u32)*(u8 *)(lVar1 + 1);
    s32 iVar3;
    if (t0 != 6 && (t0 - 3) > 2) {
        iVar3 = 0;
    } else {
        if (param_2 == 0) return 0;
        iVar3 = 1;
    }
    if (uVar2 > 1) {
        u8 t1 = *(u8 *)(lVar1 + 0x11);
        if (t1 == 6 || (u8)(t1 - 3) < 3) {
            if (param_2 == 1) return iVar3;
            iVar3++;
        }
        if (uVar2 > 2) {
            u8 t2 = *(u8 *)(lVar1 + 0x21);
            if ((t2 - 3) > 2 && t2 != 6) {
                iVar3 = 0;
            }
            if (param_2 != 2) {
                iVar3 = 0;
            }
            return iVar3;
        }
    }
    return 0;
}

// 0x7100080160 — append encoded stream entry; returns entry pointer or 0 if full (192 bytes)
s64 FUN_7100080160(s64 param_1, u8 param_2)
{
    u32 count = *(u32 *)(param_1 + 0x1880);
    s32 iVar2;
    if (count == 0) {
        iVar2 = 0;
    } else {
        s64 lVar4 = param_1 + (u64)(count - 1) * 0x18;
        u16 uVar1 = *(u16 *)(lVar4 + 0x90);
        s32 (*fn)(u8) = (s32(*)(u8))*(s64 *)(param_1 + 0x1be8);
        iVar2 = (u32)uVar1 + fn(*(u8 *)(lVar4 + 0x94)) + 2;
    }
    s32 (*fn)(u8) = (s32(*)(u8))*(s64 *)(param_1 + 0x1be8);
    s32 iVar3 = fn(param_2);
    if ((u32)(iVar3 + iVar2) < *(u32 *)(param_1 + 0x2c)) {
        u32 idx = *(u32 *)(param_1 + 0x1880);
        s64 lVar4 = param_1 + (u64)idx * 0x18;
        *(u16 *)(lVar4 + 0x92) = 0;
        *(s16 *)(lVar4 + 0x90) = (s16)iVar2;
        *(u8  *)(lVar4 + 0x94) = param_2;
        *(u8  *)(lVar4 + 0x95) = (u8)idx;
        *(u32 *)(param_1 + 0x1880) = idx + 1;
        return lVar4 + 0x80;
    }
    return 0;
}

// 0x71002261d0 — BT/HID report sender: guard checks, build payload, call internal send (208 bytes)
u64 FUN_71002261d0(s64 param_1, u32 param_2, void *param_3, u64 param_4)
{
    if (*(u8 *)(param_1 + 0x21) == 0 || (*(u8 *)(param_1 + 0x11) >> 1 & 1) != 0) {
        return (u64)(u32)0xfffffed2;
    }
    if (param_4 >= 0x7c) {
        return (u64)(u32)0xfffffed4;
    }
    u8  buf[128];
    s64 payload_len;
    if ((param_2 & 0xffff) == 0) {
        payload_len = 0;
    } else {
        u16 hdr = FUN_71002276f0(param_2);
        memcpy(buf, &hdr, 2);
        memcpy(buf + 2, param_3, param_4);
        payload_len = (s64)(param_4 + 2);
    }
    struct { u8 type; u8 *ptr; s64 len; } desc = { 8, buf, payload_len };
    u64 uVar1 = (u64)(u32)FUN_71002262a0(param_1, &desc);
    if ((s32)(u32)uVar1 == 0) {
        *(u8 *)(param_1 + 0x11) |= 2;
    }
    return uVar1;
}
