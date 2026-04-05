#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d2-004
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

extern void FUN_71003a4ca0(u32 *, const char *, s32);

// External data
extern u64 PTR_PTR_710529c400[];
extern u8 DAT_710532e9a0[];
extern u8 DAT_710532e9a8[];
extern u8 PTR_FUN_71051ac5d0[];

// ---- Functions ---------------------------------------------------------------

// 0x710339d440 -- controller icon name -> FNV-1a hash40 writer (640 bytes)
// Writes an inline string constant for the controller type name and computes its FNV-1a hash.
// String constants are stored as u32 immediates (little-endian ASCII).
void FUN_710339d440(u32 *out, u32 controller_type)
{
    u32 hash;
    u8 *str_ptr;
    u32 ch;

    hash = 0x811c9dc5;
    switch (controller_type) {
    case 1:
        // "controller_handheld"
        out[0] = 0; out[1] = 0x13;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        out[4] = 0x685f7265; out[5] = 0x68646e61;
        ch = 99; out[6] = 0x646c65;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 2:
        // "controller_joy_dual"
        out[0] = 0; out[1] = 0x13;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        out[4] = 0x6a5f7265; out[5] = 0x645f796f;
        ch = 99; out[6] = 0x6c6175;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 3:
        // "controller_joy_l"
        *(u8 *)(out + 6) = 0;
        out[4] = 0x6a5f7265; out[5] = 0x6c5f796f;
        out[0] = 0; out[1] = 0x10;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        ch = 99;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 4:
        // "controller_joy_r"
        *(u8 *)(out + 6) = 0;
        out[4] = 0x6a5f7265; out[5] = 0x725f796f;
        out[0] = 0; out[1] = 0x10;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        ch = 99;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 5:
        // "controller_pro"
        *(u8 *)((s64)out + 0x16) = 0;
        out[0] = 0; out[1] = 0xe;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        *(u16 *)(out + 5) = 0x6f72;
        ch = 99; out[4] = 0x705f7265;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 6:
        // "controller_gc"
        out[4] = 0x675f7265;
        out[0] = 0; out[1] = 0xd;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        ch = 99; *(u16 *)(out + 5) = 99;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    default:
        // "controller_off"
        *(u8 *)((s64)out + 0x16) = 0;
        out[0] = 0; out[1] = 0xe;
        out[2] = 0x746e6f63; out[3] = 0x6c6c6f72;
        *(u16 *)(out + 5) = 0x6666;
        ch = 99; out[4] = 0x6f5f7265;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
    }
    *out = hash;
    return;
}

// 0x710339d6c0 -- player/team color index -> FNV-1a hash40 writer (368 bytes)
void FUN_710339d6c0(u32 *out, s16 color_index)
{
    s32 index;
    u32 hash;
    const char *fmt;
    u8 *str_ptr;
    u32 ch;

    switch (color_index) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        index = (s32)color_index;
        fmt = "player_color_%dp";
        goto LAB_710339d710;
    case 9:
        // "player_color_cp"
        hash = 0x811c9dc5;
        out[0] = 0; out[1] = 0xf;
        out[2] = 0x79616c70; out[3] = 0x635f7265;
        out[4] = 0x726f6c6f; out[5] = 0x70635f;
        ch = 0x70;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 10:
        // "player_color_fp"
        hash = 0x811c9dc5;
        out[0] = 0; out[1] = 0xf;
        out[2] = 0x79616c70; out[3] = 0x635f7265;
        out[4] = 0x726f6c6f; out[5] = 0x70665f;
        ch = 0x70;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 0xb: case 0xc: case 0xd: case 0xe:
        index = color_index + -10;
        goto LAB_710339d708;
    case 0xf: case 0x10: case 0x11: case 0x12:
        index = color_index + -0xe;
LAB_710339d708:
        fmt = "team_color_%d";
LAB_710339d710:
        FUN_71003a4ca0(out, fmt, index);
        return;
    default:
        // "player_color_off"
        *(u8 *)(out + 6) = 0;
        out[0] = 0; out[1] = 0x10;
        out[2] = 0x79616c70; out[3] = 0x635f7265;
        hash = 0x811c9dc5;
        out[4] = 0x726f6c6f; out[5] = 0x66666f5f;
        ch = 0x70;
        str_ptr = (u8 *)((s64)out + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
    }
    *out = hash;
    return;
}

// 0x71033be790 -- lookup fighter action-info pointer by index, or return static singleton (816 bytes)
u64 *FUN_71033be790(u32 param_1)
{
    s32 acquired;

    if (param_1 < 0x267) {
        return (u64 *)PTR_PTR_710529c400[(s32)param_1];
    }
    if (((*(u8 *)DAT_710532e9a0 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64 *)DAT_710532e9a0), acquired != 0)) {
        *(u8 **)DAT_710532e9a8 = PTR_FUN_71051ac5d0;
        __cxa_guard_release((u64 *)DAT_710532e9a0);
    }
    return (u64 *)DAT_710532e9a8;
}

// 0x7103441ae0 -- set flag byte then vtable call at +0x10 (816 bytes)
void FUN_7103441ae0(u64 param_1, u64 param_2, s64 *param_3)
{
    u64 local_buf[2];

    *(u8 *)(param_3 + 0x10) = 1;
    local_buf[0] = 0;
    local_buf[1] = 0;
    (*(void (*)(s64 *, u64 *))(*param_3 + 0x10))(param_3, local_buf);
    return;
}

// 0x71034d0c20 -- vtable call at +0x10 on param_3 (416 bytes)
void FUN_71034d0c20(u64 param_1, u64 param_2, s64 *param_3)
{
    u64 local_buf[2];

    local_buf[0] = 0;
    local_buf[1] = 0;
    (*(void (*)(s64 *, u64 *))(*param_3 + 0x10))(param_3, local_buf);
    return;
}
