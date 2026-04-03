#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-026
// Pool-d worker: string formatter, vtable dispatch, linked-list callback, parallel-array build,
//                bounded string search, float scale update (160B/176B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u64 PTR_DAT_71052a1420 HIDDEN;

// ---- External functions --------------------------------------------------

extern s64 FUN_71000055b0(s64 *, u64, u64);
extern s64 FUN_7100007ef0(char *, u64, const char *, ...);  // snprintf-like (curl_maprintf)

extern "C" {
    u64 strlen(const char *);
}

// ---- Functions ---------------------------------------------------------------

// 0x7100004360 — format "%ld%s" from selected subfield, pass to FUN_71000055b0 (160 bytes)
s64 FUN_7100004360(s64 param_1, s64 param_2)
{
    if (param_2 == 0) {
        return 0;
    }
    s64 *field_ptr;
    if (*(u8 *)(param_1 + 0x817) != 0) {
        field_ptr = (s64 *)(param_1 + 0x120);
    } else if (*(u8 *)(param_1 + 0x816) != 0) {
        field_ptr = (s64 *)(param_1 + 0x160);
    } else if (*(u8 *)(param_1 + 0x813) != 0) {
        field_ptr = (s64 *)(param_1 + 0x100);
    } else {
        field_ptr = (s64 *)(param_1 + 0xd8);
    }
    char buf[128];
    FUN_7100007ef0(buf, 0x80, "%ld%s", *(s64 *)(param_1 + 0x190), *field_ptr);
    u64 len = strlen(buf);
    return FUN_71000055b0((s64 *)param_2, (u64)buf, len);
}

// 0x710003b8e0 — call vtable[+0x20] on three child nodes, then vtable[+0xb8] on +0x50 node (160 bytes)
void FUN_710003b8e0(s64 param_1)
{
    s64 *sentinel = *(s64 **)(param_1 + 0x50);
    if (sentinel == nullptr) {
        return;
    }
    s64 *nodeA = *(s64 **)(param_1 + 0x48);
    s64 *cur = sentinel;
    if (nodeA != nullptr) {
        (*(void (**)(s64 *, bool))(*nodeA + 0x20))(nodeA, nodeA == sentinel);
        cur = *(s64 **)(param_1 + 0x50);
        if (cur == nullptr) {
            goto done;
        }
    }
    (*(void (**)(s64 *, bool))(*cur + 0x20))(cur, cur == sentinel);
done:
    {
        s64 *nodeC = *(s64 **)(param_1 + 0x58);
        if (nodeC != nullptr) {
            (*(void (**)(s64 *, bool))(*nodeC + 0x20))(nodeC, nodeC == sentinel);
        }
        s64 *finalNode = *(s64 **)(param_1 + 0x50);
        (*(void (**)(f32, s64 *, s32))(*finalNode + 0xb8))(1.0f, finalNode, 0);
    }
}

// 0x7100064f90 — walk linked list, fire callback for ready nodes (flag +0x98 set, field[1]==-1) (160 bytes)
void FUN_7100064f90(s64 param_1, void (*param_2)(s64 *, s64, u64), u64 param_3)
{
    s64 node = *(s64 *)(param_1 + 8);
    do {
        if (param_1 == node) {
            return;
        }
        while (*(u8 *)(node + 0x98) != 0) {
            s64 *obj = *(s64 **)(node + 0x90);
            if (obj[1] != -1) {
                break;
            }
            s64 val = (*(s64 (**)())(*obj + 0x40))();
            param_2(obj + 1, val, param_3);
            node = *(s64 *)(node + 8);
            if (param_1 == node) {
                return;
            }
        }
        node = *(s64 *)(node + 8);
    } while (true);
}

// 0x7100032500 — pack node[+0x8]/[+0x10] into parallel arrays, dispatch via function pointer (176 bytes)
void FUN_7100032500(s64 param_1, u32 param_2, s64 *param_3, s64 param_4)
{
    u64 local_90[16] = {};
    if ((s32)param_2 > 0) {
        u64 n    = (u64)param_2;
        u64 *dst10 = &local_90[0];
        u64 *dst8  = &local_90[8];
        do {
            s64 node = *param_3;
            if (node != 0) {
                *dst8  = *(u64 *)(node + 0x8);
                *dst10 = *(u64 *)(node + 0x10);
            }
            dst10++;
            dst8++;
            param_3++;
            n--;
        } while (n != 0);
    }
    u64 extra8, extra10;
    if (param_4 == 0) {
        extra8  = 0;
        extra10 = 0;
    } else {
        extra8  = *(u64 *)(param_4 + 0x8);
        extra10 = *(u64 *)(param_4 + 0x10);
    }
    (*(void (**)(u64, u32, u64 *, u64 *, u64, u64))PTR_DAT_71052a1420)(
        *(u64 *)(param_1 + 0xb8), param_2, &local_90[8], &local_90[0], extra8, extra10);
}

// 0x710005df60 — bounded string search (28 chars) through vtable-managed collection (176 bytes)
s64 FUN_710005df60(s64 *param_1, s64 param_2)
{
    u8 count = (*(u8 (**)())(*(u64 *)param_1 + 0x50))();
    if (count == 0) {
        return 0;
    }
    u32 i = 0;
    do {
        s64 entry = (*(s64 (**)(s64 *, u32))(*(u64 *)param_1 + 0x58))(param_1, i);
        if (entry != 0) {
            u64 k = 0;
            while (true) {
                char c = *(char *)(*(s64 *)(entry + 0x28) + (s64)k);
                if (c == *(char *)(param_2 + (s64)k)) {
                    if (c == '\0') {
                        return entry;
                    }
                    k++;
                    if (k > 0x1b) {
                        return entry;
                    }
                } else {
                    break;
                }
            }
        }
        i++;
    } while (i < count);
    return 0;
}

// 0x71000640c0 — update scale pair +0xf8/+0xfc, set dirty bit, proportionally rescale two f32s (176 bytes)
void FUN_71000640c0(s64 param_1, f32 *param_2)
{
    f32 old_x = *(f32 *)(param_1 + 0xf8);
    f32 old_y = *(f32 *)(param_1 + 0xfc);
    f32 new_x = param_2[0];
    f32 new_y = param_2[1];
    u32 changed = (old_x != new_x) ? 1u : (u32)(old_y != new_y);
    u16 flags = *(u16 *)(param_1 + 0x114);
    flags = (u16)((flags & ~0x4u) | (((flags >> 2 & 1) | changed) << 2));
    *(u16 *)(param_1 + 0x114) = flags;
    if (changed) {
        if (old_y == 0.0f) {
            *(u64 *)(param_1 + 0xf8) = *(u64 *)param_2;
            return;
        }
        f32 ratio  = old_x / old_y;
        f32 aspect = new_y / new_x;
        *(u64 *)(param_1 + 0xf8) = *(u64 *)param_2;
        *(f32 *)(param_1 + 0x118) = ratio * *(f32 *)(param_1 + 0x118) * aspect;
        *(f32 *)(param_1 + 0x134) = ratio * *(f32 *)(param_1 + 0x134) * aspect;
    }
}
