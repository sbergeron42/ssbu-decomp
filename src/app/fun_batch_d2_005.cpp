#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d2-005
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void FUN_710356bb20(void);
extern void FUN_710392e590(void *);

namespace nu {
    extern void VirtualFreeHook(void *);
}

// External data
extern u8 PTR_VirtualFreeHook_71052a7a70[];
extern u8 PTR_FUN_710522ee80[];

// ---- Functions ---------------------------------------------------------------

// 0x7103398410 -- Hash40 builder for "src_appeal_*" Star Fox character voice lines (1664 bytes)
// Fox's taunt calls different Star Fox team members by index.
// Writes packed string into Hash40 struct {u32 hash, u32 len, char str[]}.
void FUN_7103398410(u32 *param_1, u32 param_2)
{
    u32 hash;
    u8 *str_ptr;
    u32 ch;

    *(u8 *)(param_1 + 2) = 0;
    param_1[0] = 0;
    param_1[1] = 0;
    switch (param_2) {
    case 1: // "src_appeal_fox"
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x665f6c61; // "al_f"
        hash = 0x811c9dc5;
        *(u8 *)((s64)param_1 + 0x16) = 0;
        *(u16 *)(param_1 + 5) = 0x786f; // "ox"
        ch = 0x73; // 's'
        param_1[1] = 0xe;        // length = 14
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 2: // "src_appeal_peppy"
        *(u8 *)(param_1 + 6) = 0;
        hash = 0x811c9dc5;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x705f6c61; // "al_p"
        param_1[5] = 0x79707065; // "eppy"
        ch = 0x73; // 's'
        param_1[1] = 0x10;       // length = 16
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 3: // "src_appeal_slippy"
        hash = 0x811c9dc5;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x735f6c61; // "al_s"
        param_1[5] = 0x7070696c; // "lipp"
        *(u16 *)(param_1 + 6) = 0x79; // "y\0"
        param_1[1] = 0x11;       // length = 17
        ch = 0x73; // 's'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 4: // "src_appeal_falco"
        *(u8 *)(param_1 + 6) = 0;
        hash = 0x811c9dc5;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x665f6c61; // "al_f"
        param_1[5] = 0x6f636c61; // "alco"
        ch = 0x73; // 's'
        param_1[1] = 0x10;       // length = 16
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 5: // "src_appeal_krystal"
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x6b5f6c61; // "al_k"
        param_1[5] = 0x74737972; // "ryst"
        hash = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x6c61; // "al"
        param_1[1] = 0x12;       // length = 18
        ch = 0x73; // 's'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 6: // "src_appeal_wolf"
        hash = 0x811c9dc5;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x775f6c61; // "al_w"
        param_1[5] = 0x666c6f;   // "olf\0"
        param_1[1] = 0xf;        // length = 15
        ch = 0x73; // 's'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 7: // "src_appeal_panther"
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x705f6c61; // "al_p"
        param_1[5] = 0x68746e61; // "anth"
        hash = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x7265; // "er"
        param_1[1] = 0x12;       // length = 18
        ch = 0x73; // 's'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    default: // no name — zero out and return
        *(u8 *)(param_1 + 2) = 0;
        param_1[0] = 0;
        param_1[1] = 0;
        return;
    case 9: // "src_appeal_leon"
        hash = 0x811c9dc5;
        param_1[2] = 0x5f726373; // "src_"
        param_1[3] = 0x65707061; // "appe"
        param_1[4] = 0x6c5f6c61; // "al_l"
        param_1[5] = 0x6e6f65;   // "eon\0"
        param_1[1] = 0xf;        // length = 15
        ch = 0x73; // 's'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
    }
    *param_1 = hash;
    return;
}

// 0x71035212e0 -- guarded vtable dispatch: skip if flag at vt+0x88 is set (80 bytes)
void FUN_71035212e0(s64 *param_1, s64 param_2)
{
    u64 flag;
    flag = (**(u64 (**)())(*(*(s64 **)(param_2 + 0x90)) + 0x88))();
    if ((flag & 1) != 0) {
        return;
    }
    (*(void (*)(s64 *, s64))(*param_1 + 0x10))(param_1, param_2);
    return;
}

// 0x710354d0d0 -- conditional vtable dispatch chain: test vt+0x418, then call vt+0x450 and vt+0x28 (96 bytes)
void FUN_710354d0d0(s64 param_1)
{
    s64 obj;
    u64 can_proceed;
    s64 data;

    obj = *(s64 *)(param_1 + 0x18);
    data = **(s64 **)(param_1 + 0x20);
    can_proceed = (**(u64 (**)())(*(*(s64 **)(obj + 0x10)) + 0x418))();
    if ((can_proceed & 1) == 0) {
        return;
    }
    (*(void (*)(s64 *, u32))(*(*(s64 **)(obj + 0x10)) + 0x450))(*(s64 **)(obj + 0x10), *(u32 *)(data + 100));
    (**(void (**)())(*(*(s64 **)(obj + 0x10)) + 0x28))();
    return;
}

// 0x71035517b0 -- set vtable ptr, conditionally call slot +8 (160 bytes)
void FUN_71035517b0(u64 *param_1)
{
    *param_1 = (u64)PTR_FUN_710522ee80;
    if (((s64 *)param_1[2] != nullptr) &&
        (*(s64 *)param_1[2] == (s64)param_1[3]) &&
        ((s64 *)param_1[1] != nullptr)) {
        (**(void (**)())(*(s64 *)param_1[1] + 8))();
        return;
    }
    return;
}

// 0x7103566d40 -- collision slot initialization (928 bytes)
// Locates a collision slot by index (param_8 >> 24), validates it, then:
//   1. Copies initial transform from +0x20..+0x88 to saved state at +0xa0..+0x108
//   2. Writes param_9/param_10 float4 vectors to +0x120..+0x13c
//   3. Sets collision params (param_2..param_6, param_11) at +0x140..+0x154
//   4. Initializes scale to 1.0f (0x3f800000) at +0x160..+0x184
// Slot stride is 0x1b0 bytes.
void FUN_7103566d40(u32 param_1, u32 param_2, u32 param_3, u32 param_4,
                    u32 param_5, u32 param_6, s64 slot_array, u32 slot_key,
                    u32 *vec_a, u32 *vec_b, u32 param_11)
{
    u32 va0, va1, va2, va3, vb0, vb1, vb2, vb3;
    u64 slot_index;
    u32 *slot_ptr;

    if (slot_key >> 0x19 < 5) {
        slot_index = (u64)(slot_key >> 0x18);
        slot_ptr = (u32 *)(slot_array + (s64)slot_index * 0x1b0);
        if ((slot_ptr != nullptr) && (*slot_ptr == slot_key) &&
            (*(s32 *)(slot_array + (s64)slot_index * 0x1b0 + 0x90) == 0)) {
            slot_array = slot_array + (s64)slot_index * 0x1b0;
            va0 = *vec_a;
            va1 = vec_a[1];
            va2 = vec_a[2];
            va3 = vec_a[3];
            vb0 = *vec_b;
            vb1 = vec_b[1];
            vb2 = vec_b[2];
            vb3 = vec_b[3];
            // State = active
            *(u32 *)(slot_array + 4) = 2;
            // Copy vec_a to +0x120
            *(u32 *)(slot_array + 0x120) = va0;
            // Save initial transform: +0x20→+0xa0, +0x40→+0xc0, etc.
            *(u64 *)(slot_array + 0xa0) = *(u64 *)(slot_array + 0x20);
            *(u64 *)(slot_array + 0xa8) = *(u64 *)(slot_array + 0x28);
            *(u32 *)(slot_array + 0x124) = va1;
            *(u64 *)(slot_array + 0xc0) = *(u64 *)(slot_array + 0x40);
            *(u64 *)(slot_array + 200) = *(u64 *)(slot_array + 0x48);
            *(u32 *)(slot_array + 0x128) = va2;
            // Scale = {1.0f, 1.0f, 1.0f, 1.0f}
            *(u64 *)(slot_array + 0x160) = 0x3f8000003f800000ULL;
            *(u64 *)(slot_array + 0x168) = 0x3f8000003f800000ULL;
            *(u32 *)(slot_array + 300) = va3;
            *(u64 *)(slot_array + 0xb0) = *(u64 *)(slot_array + 0x30);
            *(u64 *)(slot_array + 0xb8) = *(u64 *)(slot_array + 0x38);
            // Copy vec_b to +0x130
            *(u32 *)(slot_array + 0x130) = vb0;
            *(u32 *)(slot_array + 0x134) = vb1;
            *(u64 *)(slot_array + 0xe0) = *(u64 *)(slot_array + 0x60);
            *(u64 *)(slot_array + 0xe8) = *(u64 *)(slot_array + 0x68);
            *(u32 *)(slot_array + 0x138) = vb2;
            *(u32 *)(slot_array + 0x13c) = vb3;
            *(u64 *)(slot_array + 0xd0) = *(u64 *)(slot_array + 0x50);
            *(u64 *)(slot_array + 0xd8) = *(u64 *)(slot_array + 0x58);
            *(u32 *)(slot_array + 0x110) = *(u32 *)(slot_array + 0x90);
            *(u64 *)(slot_array + 0x100) = *(u64 *)(slot_array + 0x80);
            *(u64 *)(slot_array + 0x108) = *(u64 *)(slot_array + 0x88);
            // Collision parameters
            *(u32 *)(slot_array + 0x140) = param_2;
            *(u32 *)(slot_array + 0x144) = param_3;
            *(u64 *)(slot_array + 0xf0) = *(u64 *)(slot_array + 0x70);
            *(u64 *)(slot_array + 0xf8) = *(u64 *)(slot_array + 0x78);
            *(u32 *)(slot_array + 0x148) = param_4;
            *(u32 *)(slot_array + 0x14c) = param_5;
            *(u32 *)(slot_array + 0x150) = param_6;
            *(u32 *)(slot_array + 0x154) = param_11;
            // Zero out runtime state, init remaining scale to 1.0f
            *(u32 *)(slot_array + 0x170) = 0;
            *(u64 *)(slot_array + 0x174) = 0;
            *(u64 *)(slot_array + 0x17c) = 0x3f8000003f800000ULL;
            *(u32 *)(slot_array + 0x184) = 0x3f800000;
            *(u32 *)(slot_array + 400) = 0;
            *(u32 *)(slot_array + 0x10) = 0;
            *(u32 *)(slot_array + 0x14) = param_1;
            return;
        }
    }
    return;
}

// 0x710356ba40 -- type-dispatch: free/destroy variant value by type tag (224 bytes)
// Types 0-8,10,15,18: trivial (no cleanup needed)
// Type 9: heap buffer — free it
// Types 11,13,14,16,17: polymorphic — call virtual destructor
// Type 12: vector of polymorphic objects — destroy each element then free buffer
void FUN_710356ba40(u32 type_tag, u64 *value)
{
    u64 *buf;
    u64 *iter;
    u64 *base;

    switch (type_tag) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
    case 10: case 0xf: case 0x12:
        break;
    case 9: // heap buffer
        buf = (u64 *)*value;
        if (buf != nullptr) {
            value[1] = (u64)buf;
LAB_710356baec:
            if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                nu::VirtualFreeHook(buf);
            }
            FUN_710392e590(buf);
            return;
        }
        break;
    case 0xb: case 0xd: case 0xe: case 0x10: case 0x11: // polymorphic
        (*(void (*)(u64 *))(*(u64 *)*value))(value);
        return;
    case 0xc: // vector of polymorphic objects
        base = (u64 *)*value;
        if (base != nullptr) {
            iter = (u64 *)value[1];
            buf = base;
            if (iter != base) {
                do {
                    iter = iter - 4;
                    (*(void (*)(u64 *))(*(u64 *)*iter))(iter);
                } while (base != iter);
                buf = (u64 *)*value;
            }
            value[1] = (u64)base;
            goto LAB_710356baec;
        }
        break;
    default:
        FUN_710356bb20();
    }
    return;
}

// 0x7103598a60 -- type-dispatch: free/destroy vector variant value (208 bytes)
// Types 0,1,3,4,5,6: polymorphic — call virtual destructor
// Type 2: vector of polymorphic objects — destroy each then free buffer
void FUN_7103598a60(u32 type_tag, u64 *value)
{
    u64 *iter;
    u64 *buf;
    u64 *base;

    switch (type_tag) {
    case 0: case 1: case 3: case 4: case 5: case 6: // polymorphic
        (*(void (*)(u64 *))(*(u64 *)*value))(value);
        return;
    case 2: // vector — fall through to cleanup below
        break;
    default:
        FUN_710356bb20();
    }
    base = (u64 *)*value;
    if (base != nullptr) {
        iter = (u64 *)value[1];
        buf = base;
        if (iter != base) {
            do {
                iter = iter - 4;
                (*(void (*)(u64 *))(*(u64 *)*iter))(iter);
            } while (base != iter);
            buf = (u64 *)*value;
        }
        value[1] = (u64)base;
        if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            nu::VirtualFreeHook(buf);
        }
        FUN_710392e590(buf);
        return;
    }
    return;
}
