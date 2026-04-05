#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d2-001
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void abort();

extern void FUN_710377a930(u32, s64);
extern "C" void ui2d_apply_named_animation(u32, u64, const char *);

// External data
extern void *DAT_71052b5fd8;   // pointer to singleton with collision region list
extern float DAT_7104471398;   // float constant (default rate)
extern float DAT_7104471b54;   // float constant (alt rate)
extern u8 DAT_710532e7b0[];    // pointer-to-manager base

// ---- Functions ---------------------------------------------------------------

// 0x710317d6e0 -- collision region submit: read rect from param_1, find free slot, write and tag (1424 bytes)
// Reads an axis-aligned bounding rect from the request struct, finds a free slot in the
// collision region table (8 slots max at +0x464), writes min/max X/Y, and tags the slot
// with a type byte. Each switch case handles a different collision type (1-4 + default).
void FUN_710317d6e0(s64 param_1)
{
    char tag;
    s32 *region_table;
    s32 slot_idx_s32;
    s64 slot_idx;
    u8 new_tag;
    u8 *tag_ptr;
    float min_x;
    float x1;
    float y1;
    float max_x;
    float y2;

    if ((*(u8 *)(param_1 + 9) != '\0') || (*(u8 *)(param_1 + 8) == '\0'))
        goto LAB_710317dc60;

    switch (*(u32 *)(param_1 + 0x40)) {
    case 1: // collision type A (0x41)
        x1 = *(float *)(param_1 + 0x10);
        max_x = *(float *)(param_1 + 0x20);
        y1 = *(float *)(param_1 + 0x14);
        min_x = x1;
        if (max_x <= x1) { min_x = max_x; max_x = x1; }
        y2 = *(float *)(param_1 + 0x24);
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        x1 = y2;
        if (y2 <= y1) { x1 = y1; y1 = y2; }
        // Find first free slot in tag array at +0x464 (8 slots)
        if (*(u8 *)((s64)region_table + 0x464) == '\0') { slot_idx = 0; }
        else if (*(u8 *)((s64)region_table + 0x465) == '\0') { slot_idx = 1; }
        else if (*(u8 *)((s64)region_table + 0x466) == '\0') { slot_idx = 2; }
        else if (*(u8 *)((s64)region_table + 0x467) == '\0') { slot_idx = 3; }
        else if (*(u8 *)((s64)region_table + 0x468) == '\0') { slot_idx = 4; }
        else if (*(u8 *)((s64)region_table + 0x469) == '\0') { slot_idx = 5; }
        else if (*(u8 *)((s64)region_table + 0x46a) == '\0') { slot_idx = 6; }
        else {
            if (*(u8 *)((s64)region_table + 0x46b) != '\0') { slot_idx = 0xffffffff; break; }
            slot_idx = 7;
        }
        // Write AABB: min_x, max_x, max_y, min_y, sentinel
        region_table[slot_idx * 5 + 1] = (s32)min_x;
        region_table[slot_idx * 5 + 2] = (s32)max_x;
        region_table[slot_idx * 5 + 3] = (s32)x1;
        region_table[slot_idx * 5 + 4] = (s32)y1;
        region_table[slot_idx * 5 + 5] = -1;
        tag = *(u8 *)((s64)region_table + slot_idx + 0x464);
        if (tag != 'A') {
            tag_ptr = (u8 *)((s64)region_table + slot_idx + 0x464);
            if (tag == '\0') { *region_table = *region_table + 1; }
            new_tag = 0x41;
            *tag_ptr = new_tag;
        }
        break;
    case 2: // collision type 0x03
        x1 = *(float *)(param_1 + 0x10);
        max_x = *(float *)(param_1 + 0x20);
        y1 = *(float *)(param_1 + 0x14);
        min_x = x1;
        if (max_x <= x1) { min_x = max_x; max_x = x1; }
        y2 = *(float *)(param_1 + 0x24);
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        x1 = y2;
        if (y2 <= y1) { x1 = y1; y1 = y2; }
        if (*(u8 *)((s64)region_table + 0x464) == '\0') { slot_idx = 0; }
        else if (*(u8 *)((s64)region_table + 0x465) == '\0') { slot_idx = 1; }
        else if (*(u8 *)((s64)region_table + 0x466) == '\0') { slot_idx = 2; }
        else if (*(u8 *)((s64)region_table + 0x467) == '\0') { slot_idx = 3; }
        else if (*(u8 *)((s64)region_table + 0x468) == '\0') { slot_idx = 4; }
        else if (*(u8 *)((s64)region_table + 0x469) == '\0') { slot_idx = 5; }
        else if (*(u8 *)((s64)region_table + 0x46a) == '\0') { slot_idx = 6; }
        else {
            if (*(u8 *)((s64)region_table + 0x46b) != '\0') { slot_idx = 0xffffffff; break; }
            slot_idx = 7;
        }
        region_table[slot_idx * 5 + 1] = (s32)min_x;
        region_table[slot_idx * 5 + 2] = (s32)max_x;
        region_table[slot_idx * 5 + 3] = (s32)x1;
        region_table[slot_idx * 5 + 4] = (s32)y1;
        region_table[slot_idx * 5 + 5] = -1;
        tag = *(u8 *)((s64)region_table + slot_idx + 0x464);
        if (tag != '\x03') {
            tag_ptr = (u8 *)((s64)region_table + slot_idx + 0x464);
            if (tag == '\0') { *region_table = *region_table + 1; }
            new_tag = 3;
            *tag_ptr = new_tag;
        }
        break;
    case 3: // collision type 0x81
        x1 = *(float *)(param_1 + 0x10);
        max_x = *(float *)(param_1 + 0x20);
        y1 = *(float *)(param_1 + 0x14);
        min_x = x1;
        if (max_x <= x1) { min_x = max_x; max_x = x1; }
        y2 = *(float *)(param_1 + 0x24);
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        x1 = y2;
        if (y2 <= y1) { x1 = y1; y1 = y2; }
        if (*(u8 *)((s64)region_table + 0x464) == '\0') { slot_idx = 0; }
        else if (*(u8 *)((s64)region_table + 0x465) == '\0') { slot_idx = 1; }
        else if (*(u8 *)((s64)region_table + 0x466) == '\0') { slot_idx = 2; }
        else if (*(u8 *)((s64)region_table + 0x467) == '\0') { slot_idx = 3; }
        else if (*(u8 *)((s64)region_table + 0x468) == '\0') { slot_idx = 4; }
        else if (*(u8 *)((s64)region_table + 0x469) == '\0') { slot_idx = 5; }
        else if (*(u8 *)((s64)region_table + 0x46a) == '\0') { slot_idx = 6; }
        else {
            if (*(u8 *)((s64)region_table + 0x46b) != '\0') { slot_idx = 0xffffffff; break; }
            slot_idx = 7;
        }
        region_table[slot_idx * 5 + 1] = (s32)min_x;
        region_table[slot_idx * 5 + 2] = (s32)max_x;
        region_table[slot_idx * 5 + 3] = (s32)x1;
        region_table[slot_idx * 5 + 4] = (s32)y1;
        region_table[slot_idx * 5 + 5] = -1;
        tag = *(u8 *)((s64)region_table + slot_idx + 0x464);
        if (tag != '\x81') {
            tag_ptr = (u8 *)((s64)region_table + slot_idx + 0x464);
            if (tag == '\0') { *region_table = *region_table + 1; }
            new_tag = 0x81;
            *tag_ptr = new_tag;
        }
        break;
    case 4: // collision type 0x20
        x1 = *(float *)(param_1 + 0x10);
        max_x = *(float *)(param_1 + 0x20);
        y1 = *(float *)(param_1 + 0x14);
        min_x = x1;
        if (max_x <= x1) { min_x = max_x; max_x = x1; }
        y2 = *(float *)(param_1 + 0x24);
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        x1 = y2;
        if (y2 <= y1) { x1 = y1; y1 = y2; }
        if (*(u8 *)((s64)region_table + 0x464) == '\0') { slot_idx = 0; }
        else if (*(u8 *)((s64)region_table + 0x465) == '\0') { slot_idx = 1; }
        else if (*(u8 *)((s64)region_table + 0x466) == '\0') { slot_idx = 2; }
        else if (*(u8 *)((s64)region_table + 0x467) == '\0') { slot_idx = 3; }
        else if (*(u8 *)((s64)region_table + 0x468) == '\0') { slot_idx = 4; }
        else if (*(u8 *)((s64)region_table + 0x469) == '\0') { slot_idx = 5; }
        else if (*(u8 *)((s64)region_table + 0x46a) == '\0') { slot_idx = 6; }
        else {
            if (*(u8 *)((s64)region_table + 0x46b) != '\0') { slot_idx = 0xffffffff; break; }
            slot_idx = 7;
        }
        region_table[slot_idx * 5 + 1] = (s32)min_x;
        region_table[slot_idx * 5 + 2] = (s32)max_x;
        region_table[slot_idx * 5 + 3] = (s32)x1;
        region_table[slot_idx * 5 + 4] = (s32)y1;
        region_table[slot_idx * 5 + 5] = -1;
        tag = *(u8 *)((s64)region_table + slot_idx + 0x464);
        if (tag != ' ') {
            tag_ptr = (u8 *)((s64)region_table + slot_idx + 0x464);
            if (tag == '\0') { *region_table = *region_table + 1; }
            new_tag = 0x20;
            *tag_ptr = new_tag;
        }
        break;
    default:
        x1 = *(float *)(param_1 + 0x10);
        max_x = *(float *)(param_1 + 0x20);
        y1 = *(float *)(param_1 + 0x14);
        min_x = x1;
        if (max_x <= x1) { min_x = max_x; max_x = x1; }
        y2 = *(float *)(param_1 + 0x24);
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        x1 = y2;
        if (y2 <= y1) { x1 = y1; y1 = y2; }
        if (*(u8 *)((s64)region_table + 0x464) == '\0') { slot_idx = 0; }
        else if (*(u8 *)((s64)region_table + 0x465) == '\0') { slot_idx = 1; }
        else if (*(u8 *)((s64)region_table + 0x466) == '\0') { slot_idx = 2; }
        else if (*(u8 *)((s64)region_table + 0x467) == '\0') { slot_idx = 3; }
        else if (*(u8 *)((s64)region_table + 0x468) == '\0') { slot_idx = 4; }
        else if (*(u8 *)((s64)region_table + 0x469) == '\0') { slot_idx = 5; }
        else if (*(u8 *)((s64)region_table + 0x46a) == '\0') { slot_idx = 6; }
        else {
            if (*(u8 *)((s64)region_table + 0x46b) != '\0') { slot_idx = 0xffffffff; break; }
            slot_idx = 7;
        }
        region_table[slot_idx * 5 + 1] = (s32)min_x;
        region_table[slot_idx * 5 + 2] = (s32)max_x;
        region_table[slot_idx * 5 + 3] = (s32)x1;
        region_table[slot_idx * 5 + 4] = (s32)y1;
        region_table[slot_idx * 5 + 5] = -1;
        tag = *(u8 *)((s64)region_table + slot_idx + 0x464);
        if (tag != '\t') {
            tag_ptr = (u8 *)((s64)region_table + slot_idx + 0x464);
            if (tag == '\0') { *region_table = *region_table + 1; }
            new_tag = 9;
            *tag_ptr = new_tag;
        }
    }

    slot_idx_s32 = (s32)slot_idx;
    *(s32 *)(param_1 + 0xc) = slot_idx_s32;
    if ((slot_idx_s32 != -1) && (*(u32 *)(param_1 + 0x40) < 5)) {
        region_table = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        if (*(u8 *)((s64)region_table + slot_idx_s32 + 0x464) != '\0') {
            s64 slot_idxb = *(s64 *)&DAT_71052b5fd8;
            slot_idxb = *(s64 *)(slot_idxb + 0xc0) + (s64)slot_idx_s32 * 0x14;
            *(float *)(slot_idxb + 4) = *(float *)(slot_idxb + 4) + *(float *)(param_1 + 0x30);
            *(float *)(slot_idxb + 8) = *(float *)(slot_idxb + 8) + *(float *)(param_1 + 0x30);
            *(float *)(slot_idxb + 0xc) = *(float *)(slot_idxb + 0xc) + *(float *)(param_1 + 0x34);
            *(float *)(slot_idxb + 0x10) = *(float *)(slot_idxb + 0x10) + *(float *)(param_1 + 0x34);
        }
    }
    *(u8 *)(param_1 + 9) = 1;

LAB_710317dc60:
    *(u8 *)(param_1 + 10) = 1;
    return;
}

// 0x71032d05a0 -- tournament UI slot set: update anim state on resource load complete (688 bytes)
// Each slot is 0x130 bytes. When resource (param_3) becomes null, resets the slot's
// animation rate and optionally plays "tournament_off" animation.
void FUN_71032d05a0(s64 param_1, u32 slot_index, s64 resource)
{
    s64 slot_base;
    s64 slot_ext;
    float anim_rate;

    if (9 < slot_index) {
        abort();
    }
    *(s64 *)(param_1 + (s64)(s32)slot_index * 0x130 + 0x110) = resource;
    if (resource == 0) {
        slot_ext = (s64)(s32)slot_index;
        slot_base = param_1 + slot_ext * 0x130;
        if (*(u8 *)(slot_base + 0x11f) != '\0') {
            *(u8 *)(slot_base + 0x11f) = 0;
            anim_rate = DAT_7104471398; // default rate
            if (((*(s32 *)(param_1 + slot_ext * 0x130 + 0x10) == 1) &&
                 (*(u8 *)(param_1 + slot_ext * 0x130 + 0x11e) != '\0')) &&
                (*(u8 *)(param_1 + slot_ext * 0x130 + 0x126) != '\0')) {
                anim_rate = DAT_7104471b54; // alt rate
            }
            slot_base = param_1 + slot_ext * 0x130;
            *(float *)(slot_base + 0x104) = anim_rate;
            *(float *)(slot_base + 0x10c) = anim_rate * *(float *)(slot_base + 0x100);
            if ((*(s64 *)(*(s64 *)(slot_base + 0x88)) != 0) &&
                ((*(s64 **)(slot_base + 0x88))[1] != 0)) {
                FUN_710377a930(0x3f800000, slot_base + 0x80);
            }
            if (*(s32 *)(param_1 + slot_ext * 0x130 + 0x14) == 2) {
                ui2d_apply_named_animation(0x3f800000,
                    *(u64 *)(param_1 + slot_ext * 0x130 + 0x28), "tournament_off");
                return;
            }
        }
    }
    return;
}

// 0x71032e2f20 -- stage mode → Hash40 constant lookup (small)
// Returns a Hash40 identifying a stage resource based on the current game mode.
// The 0x58ffff prefix indicates these are pre-computed Hash40 values.
u64 FUN_71032e2f20(u64 param_1)
{
    s32 game_mode;
    u64 result;

    game_mode = *(s32 *)(*(s64 *)(DAT_710532e7b0 + 8) + 0x210);
    if (game_mode == 0x11) { // mode 17
        result = 0x58ffff270aab93dcULL;
        if ((param_1 & 1) == 0) {
            result = 0x58ffff0000000000ULL; // default/empty
        }
        return result;
    }
    if (game_mode != 3) {
        if (game_mode == 2) {
            return 0x58ffff27d91566bfULL;
        }
        return 0x58ffff0000000000ULL; // default/empty
    }
    return 0x58ffff202a6b270cULL; // mode 3
}
