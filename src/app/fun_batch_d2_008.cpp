#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d2-008
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x7103392a80 -- Hash40 builder: maps (controller_type, button_bitmask) → button UI resource name (5376 bytes)
// Controller types: 2=ZL/ZR only, 3=Joy-Con single, 4=Joy-Con dual, 5=Pro Controller, 6=GameCube
// Button bitmask is a single-bit flag identifying which button.
// Writes Hash40 struct {u32 hash, u32 len, char str[]} into param_1.
// Note: fun_triage.csv lists entry at 0x71033934b0 (FUN_71033934b0) which falls inside this function
void FUN_7103392a80(u32 *param_1, u32 param_2, s32 param_3)
{
    char ch2;
    u32 hash;
    u64 str_len;
    u8 *str_ptr;
    u32 ch;

    if (param_2 == 6) { // GameCube controller
        if (param_3 < 0x80) {
            switch (param_3) {
            case 1: // "cmn_button_gc_up"
                *(u8 *)(param_1 + 6) = 0;
                param_1[0] = 0;
                param_1[1] = 0x10;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                hash = 0x811c9dc5;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x70755f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 2: // "cmn_button_gc_right"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x13;       // length = 19
                param_1[2] = 0x5f6e6d63; // "cmn_"
                param_1[3] = 0x74747562; // "butt"
                param_1[4] = 0x675f6e6f; // "on_g"
                param_1[5] = 0x69725f63; // "c_ri"
                param_1[6] = 0x746867;   // "ght\0"
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 4: // "cmn_button_gc_down"
                *(u8 *)((s64)param_1 + 0x1a) = 0;
                param_1[0] = 0;
                param_1[1] = 0x12;       // length = 18
                param_1[2] = 0x5f6e6d63; // "cmn_"
                param_1[3] = 0x74747562; // "butt"
                param_1[4] = 0x675f6e6f; // "on_g"
                param_1[5] = 0x6f645f63; // "c_do"
                hash = 0x811c9dc5;
                *(u16 *)(param_1 + 6) = 0x6e77; // "wn"
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 8: // "cmn_button_gc_left"
                *(u8 *)((s64)param_1 + 0x1a) = 0;
                param_1[0] = 0;
                param_1[1] = 0x12;       // length = 18
                param_1[2] = 0x5f6e6d63; // "cmn_"
                param_1[3] = 0x74747562; // "butt"
                param_1[4] = 0x675f6e6f; // "on_g"
                param_1[5] = 0x656c5f63; // "c_le"
                hash = 0x811c9dc5;
                *(u16 *)(param_1 + 6) = 0x7466; // "ft"
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 0x10: // "cmn_button_gc_x"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x785f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 0x20: // "cmn_button_gc_a"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x615f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            case 0x40: // "cmn_button_gc_b"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x625f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
        } else if (param_3 < 0x200) {
            if (param_3 == 0x80) { // "cmn_button_gc_y"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x795f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
            if (param_3 == 0x100) { // "cmn_button_gc_l"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x6c5f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
        } else {
            if (param_3 == 0x200) { // "cmn_button_gc_r"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x725f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
            if (param_3 == 0x800) { // "cmn_button_gc_z"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x7a5f63;
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
            if (param_3 == 0x40000) { // "cmn_button_gc_start"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x13;       // length = 19
                param_1[2] = 0x5f6e6d63; // "cmn_"
                param_1[3] = 0x74747562; // "butt"
                param_1[4] = 0x675f6e6f; // "on_g"
                param_1[5] = 0x74735f63; // "c_st"
                param_1[6] = 0x747261;   // "art\0"
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                *param_1 = hash;
                return;
            }
        }
        goto LAB_return_empty;
    }
    if ((param_2 | 4) != 5) {
        if (param_2 == 4) { // Joy-Con dual
            if (param_3 < 0x100) {
                if (param_3 < 0x40) {
                    if (param_3 == 0x10) { // "cmn_button_joycon_up"
                        *(u8 *)(param_1 + 7) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x14;       // length = 20
                        param_1[2] = 0x5f6e6d63; // "cmn_"
                        param_1[3] = 0x74747562; // "butt"
                        param_1[4] = 0x6a5f6e6f; // "on_j"
                        param_1[5] = 0x6f63796f; // "oyco"
                        hash = 0x811c9dc5;
                        param_1[6] = 0x70755f6e; // "n_up"
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                    if (param_3 == 0x20) { // "cmn_button_joycon_right"
                        hash = 0x811c9dc5;
                        param_1[0] = 0;
                        param_1[1] = 0x17;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x68676972;
                        *(u16 *)((s64)param_1 + 0x1e) = 0x74;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                } else {
                    if (param_3 == 0x40) { // "cmn_button_joycon_down"
                        *(u8 *)((s64)param_1 + 0x1e) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x16;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        hash = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x6e776f64; // "down"
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                    if (param_3 == 0x80) { // "cmn_button_joycon_left"
                        *(u8 *)((s64)param_1 + 0x1e) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x16;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        hash = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x7466656c;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                }
            } else if (param_3 < 0x400) {
                if (param_3 == 0x100) {
                    param_3 = 0x4000;
                } else if (param_3 == 0x200) goto LAB_return_empty;
            } else {
                if (param_3 == 0x400) goto LAB_return_empty;
                if (param_3 == 0x800) {
                    param_1[0] = 0;
                    param_1[1] = 0;
                    for (str_len = 0; "cmn_button_fil_nx_stick_btn"[str_len] != '\0'; str_len = str_len + 2) {
                        ch2 = "cmn_button_fil_nx_stick_btn"[str_len + 1];
                        *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fil_nx_stick_btn"[str_len];
                        if (ch2 == '\0') { str_len++; break; }
                        *(char *)((s64)param_1 + str_len + 9) = ch2;
                    }
                    *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                    ch = (u32)(u8)param_1[2];
                    hash = 0x811c9dc5;
                    param_1[1] = (u32)str_len;
                    if ((u8)param_1[2] != 0) {
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        hash = 0x811c9dc5;
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                    }
                    goto LAB_return_with_hash;
                }
                if (param_3 == 0x80000) { param_3 = 0x40000; }
            }
        } else if (param_2 == 3) { // Joy-Con single
            if (param_3 < 0x100) {
                if (param_3 < 0x40) {
                    if (param_3 == 0x10) {
                        *(u8 *)(param_1 + 7) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x14;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        hash = 0x811c9dc5;
                        param_1[6] = 0x70755f6e;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                    if (param_3 == 0x20) {
                        hash = 0x811c9dc5;
                        param_1[0] = 0;
                        param_1[1] = 0x17;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x68676972;
                        *(u16 *)((s64)param_1 + 0x1e) = 0x74;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                } else {
                    if (param_3 == 0x40) {
                        *(u8 *)((s64)param_1 + 0x1e) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x16;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        hash = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x6e776f64;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                    if (param_3 == 0x80) {
                        *(u8 *)((s64)param_1 + 0x1e) = 0;
                        param_1[0] = 0;
                        param_1[1] = 0x16;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        hash = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x7466656c;
                        ch = 99;
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        *param_1 = hash;
                        return;
                    }
                }
            } else if (param_3 < 0x400) {
                if (param_3 == 0x100) {
                    param_3 = 0x1000;
                } else if (param_3 == 0x200) {
                    param_3 = 0x2000;
                }
            } else {
                if (param_3 == 0x400) goto LAB_return_empty;
                if (param_3 == 0x800) {
                    param_1[0] = 0;
                    param_1[1] = 0;
                    for (str_len = 0; "cmn_button_fil_nx_stick_btn"[str_len] != '\0'; str_len = str_len + 2) {
                        ch2 = "cmn_button_fil_nx_stick_btn"[str_len + 1];
                        *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fil_nx_stick_btn"[str_len];
                        if (ch2 == '\0') { str_len++; break; }
                        *(char *)((s64)param_1 + str_len + 9) = ch2;
                    }
                    *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                    ch = (u32)(u8)param_1[2];
                    hash = 0x811c9dc5;
                    param_1[1] = (u32)str_len;
                    if ((u8)param_1[2] != 0) {
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        hash = 0x811c9dc5;
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                    }
                    goto LAB_return_with_hash;
                }
                if (param_3 == 0x40000) { param_3 = 0x80000; }
            }
        } else if (param_2 == 2) { // ZL/ZR-only controller type
            if (param_3 == 0x800) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_zr"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_zr"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_zr"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
LAB_return_with_hash:
                *param_1 = hash;
                return;
            }
            if (param_3 == 0x400) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_zl"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_zl"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_zl"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
                goto LAB_return_with_hash;
            }
        }
    }
    if (0x3fff < param_3) {
        if (param_3 < 0x200000) {
            if (param_3 < 0x20000) {
                if (param_3 == 0x4000) goto LAB_7103393a78;
                if (param_3 == 0x8000) goto LAB_7103393978;
                if (param_3 != 0x10000) goto LAB_return_empty;
            } else {
                if (param_3 < 0x80000) {
                    if (param_3 != 0x20000) {
                        if (param_3 != 0x40000) goto LAB_return_empty;
                        param_1[0] = 0;
                        param_1[1] = 0;
                        for (str_len = 0; "cmn_button_fill_nx_round_plus"[str_len] != '\0'; str_len = str_len + 2) {
                            ch2 = "cmn_button_fill_nx_round_plus"[str_len + 1];
                            *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_round_plus"[str_len];
                            if (ch2 == '\0') { str_len++; break; }
                            *(char *)((s64)param_1 + str_len + 9) = ch2;
                        }
                        *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                        ch = (u32)(u8)param_1[2];
                        hash = 0x811c9dc5;
                        param_1[1] = (u32)str_len;
                        if ((u8)param_1[2] != 0) {
                            str_ptr = (u8 *)((s64)param_1 + 9);
                            hash = 0x811c9dc5;
                            do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                        }
                        goto LAB_7103393f60;
                    }
                    goto LAB_7103393a08;
                }
                if (param_3 == 0x80000) {
                    param_1[0] = 0;
                    param_1[1] = 0;
                    for (str_len = 0; "cmn_button_fill_nx_round_minus"[str_len] != '\0'; str_len = str_len + 2) {
                        ch2 = "cmn_button_fill_nx_round_minus"[str_len + 1];
                        *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_round_minus"[str_len];
                        if (ch2 == '\0') { str_len++; break; }
                        *(char *)((s64)param_1 + str_len + 9) = ch2;
                    }
                    *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                    ch = (u32)(u8)param_1[2];
                    hash = 0x811c9dc5;
                    param_1[1] = (u32)str_len;
                    if ((u8)param_1[2] != 0) {
                        str_ptr = (u8 *)((s64)param_1 + 9);
                        hash = 0x811c9dc5;
                        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                    }
                    goto LAB_7103393f60;
                }
                if (param_3 != 0x100000) goto LAB_return_empty;
            }
        } else {
            if (0xffffff < param_3) {
                if (param_3 < 0x4000000) {
                    if ((param_3 != 0x1000000) && (param_3 != 0x2000000)) goto LAB_return_empty;
                } else if ((param_3 != 0x4000000) && (param_3 != 0x8000000)) goto LAB_return_empty;
LAB_7103393a08: // "cmn_button_nx_stick_r"
                hash = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x15;       // length = 21
                param_1[2] = 0x5f6e6d63; // "cmn_"
                param_1[3] = 0x74747562; // "butt"
                param_1[4] = 0x6e5f6e6f; // "on_n"
                param_1[5] = 0x74735f78; // "x_st"
                *(u16 *)(param_1 + 6) = 0x6369; // "ic"
                *(u32 *)((s64)param_1 + 0x1a) = 0x725f6b; // "k_r\0"
                ch = 99;
                str_ptr = (u8 *)((s64)param_1 + 9);
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                goto LAB_7103393a70;
            }
            if (((param_3 != 0x200000) && (param_3 != 0x400000)) && (param_3 != 0x800000))
                goto LAB_return_empty;
        }
        // "cmn_button_nx_stick_l"
        hash = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x15;       // length = 21
        param_1[2] = 0x5f6e6d63; // "cmn_"
        param_1[3] = 0x74747562; // "butt"
        param_1[4] = 0x6e5f6e6f; // "on_n"
        param_1[5] = 0x74735f78; // "x_st"
        *(u16 *)(param_1 + 6) = 0x6369; // "ic"
        *(u32 *)((s64)param_1 + 0x1a) = 0x6c5f6b; // "k_l\0"
        ch = 99;
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        goto LAB_7103393a70;
    }
    if (0x7f < param_3) {
        if (param_3 < 0x400) {
            if (param_3 == 0x80) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_y"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_y"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_y"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    hash = 0x811c9dc5;
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
            } else if (param_3 == 0x100) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_l"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_l"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_l"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    hash = 0x811c9dc5;
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
            } else {
                if (param_3 != 0x200) goto LAB_return_empty;
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_r"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_r"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_r"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
            }
            goto LAB_7103393f60;
        }
        if (param_3 < 0x1000) {
            if (param_3 == 0x400) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_zl"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_zl"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_zl"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
            } else {
                if (param_3 != 0x800) goto LAB_return_empty;
                param_1[0] = 0;
                param_1[1] = 0;
                for (str_len = 0; "cmn_button_fill_nx_zr"[str_len] != '\0'; str_len = str_len + 2) {
                    ch2 = "cmn_button_fill_nx_zr"[str_len + 1];
                    *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_zr"[str_len];
                    if (ch2 == '\0') { str_len++; break; }
                    *(char *)((s64)param_1 + str_len + 9) = ch2;
                }
                *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
                ch = (u32)(u8)param_1[2];
                hash = 0x811c9dc5;
                param_1[1] = (u32)str_len;
                if ((u8)param_1[2] != 0) {
                    str_ptr = (u8 *)((s64)param_1 + 9);
                    do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
                }
            }
            goto LAB_7103393f60;
        }
        if (param_3 != 0x1000) {
            if (param_3 != 0x2000) goto LAB_return_empty;
LAB_7103393978:
            param_1[0] = 0;
            param_1[1] = 0;
            for (str_len = 0; "cmn_button_fill_nx_sr"[str_len] != '\0'; str_len = str_len + 2) {
                ch2 = "cmn_button_fill_nx_sr"[str_len + 1];
                *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_sr"[str_len];
                if (ch2 == '\0') { str_len++; break; }
                *(char *)((s64)param_1 + str_len + 9) = ch2;
            }
            *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
            ch = (u32)(u8)param_1[2];
            hash = 0x811c9dc5;
            param_1[1] = (u32)str_len;
            if ((u8)param_1[2] != 0) {
                str_ptr = (u8 *)((s64)param_1 + 9);
                hash = 0x811c9dc5;
                do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
            }
            goto LAB_7103393f60;
        }
LAB_7103393a78:
        param_1[0] = 0;
        param_1[1] = 0;
        for (str_len = 0; "cmn_button_fill_nx_sl"[str_len] != '\0'; str_len = str_len + 2) {
            ch2 = "cmn_button_fill_nx_sl"[str_len + 1];
            *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_sl"[str_len];
            if (ch2 == '\0') { str_len++; break; }
            *(char *)((s64)param_1 + str_len + 9) = ch2;
        }
        *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
        ch = (u32)(u8)param_1[2];
        hash = 0x811c9dc5;
        param_1[1] = (u32)str_len;
        if ((u8)param_1[2] != 0) {
            str_ptr = (u8 *)((s64)param_1 + 9);
            hash = 0x811c9dc5;
            do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        }
        goto LAB_7103393f60;
    }
    // NX generic (Pro Controller / default) direction buttons
    switch (param_3) {
    case 1: // "cmn_button_nx_up"
        *(u8 *)(param_1 + 6) = 0;
        param_1[0] = 0;
        param_1[1] = 0x10;       // length = 16
        param_1[2] = 0x5f6e6d63; // "cmn_"
        param_1[3] = 0x74747562; // "butt"
        hash = 0x811c9dc5;
        param_1[4] = 0x6e5f6e6f; // "on_n"
        param_1[5] = 0x70755f78; // "x_up"
        ch = 99;
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 2: // "cmn_button_nx_right"
        hash = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;       // length = 19
        param_1[2] = 0x5f6e6d63; // "cmn_"
        param_1[3] = 0x74747562; // "butt"
        param_1[4] = 0x6e5f6e6f; // "on_n"
        param_1[5] = 0x69725f78; // "x_ri"
        param_1[6] = 0x746867;   // "ght\0"
        ch = 99;
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    default:
        goto LAB_return_empty;
    case 4: // "cmn_button_nx_down"
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[0] = 0;
        param_1[1] = 0x12;       // length = 18
        param_1[2] = 0x5f6e6d63; // "cmn_"
        param_1[3] = 0x74747562; // "butt"
        param_1[4] = 0x6e5f6e6f; // "on_n"
        param_1[5] = 0x6f645f78; // "x_do"
        hash = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x6e77; // "wn"
        ch = 99;
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 8: // "cmn_button_nx_left"
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[0] = 0;
        param_1[1] = 0x12;       // length = 18
        param_1[2] = 0x5f6e6d63; // "cmn_"
        param_1[3] = 0x74747562; // "butt"
        param_1[4] = 0x6e5f6e6f; // "on_n"
        param_1[5] = 0x656c5f78; // "x_le"
        hash = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x7466; // "ft"
        ch = 99;
        str_ptr = (u8 *)((s64)param_1 + 9);
        do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        break;
    case 0x10:
        param_1[0] = 0;
        param_1[1] = 0;
        for (str_len = 0; "cmn_button_fill_nx_x"[str_len] != '\0'; str_len = str_len + 2) {
            ch2 = "cmn_button_fill_nx_x"[str_len + 1];
            *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_x"[str_len];
            if (ch2 == '\0') { str_len++; break; }
            *(char *)((s64)param_1 + str_len + 9) = ch2;
        }
        *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
        ch = (u32)(u8)param_1[2];
        hash = 0x811c9dc5;
        param_1[1] = (u32)str_len;
        if ((u8)param_1[2] != 0) {
            str_ptr = (u8 *)((s64)param_1 + 9);
            hash = 0x811c9dc5;
            do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        }
        goto LAB_7103393f60;
    case 0x20:
        param_1[0] = 0;
        param_1[1] = 0;
        for (str_len = 0; "cmn_button_fill_nx_a"[str_len] != '\0'; str_len = str_len + 2) {
            ch2 = "cmn_button_fill_nx_a"[str_len + 1];
            *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_a"[str_len];
            if (ch2 == '\0') { str_len++; break; }
            *(char *)((s64)param_1 + str_len + 9) = ch2;
        }
        *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
        ch = (u32)(u8)param_1[2];
        hash = 0x811c9dc5;
        param_1[1] = (u32)str_len;
        if ((u8)param_1[2] != 0) {
            str_ptr = (u8 *)((s64)param_1 + 9);
            hash = 0x811c9dc5;
            do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        }
        goto LAB_7103393f60;
    case 0x40:
        param_1[0] = 0;
        param_1[1] = 0;
        for (str_len = 0; "cmn_button_fill_nx_b"[str_len] != '\0'; str_len = str_len + 2) {
            ch2 = "cmn_button_fill_nx_b"[str_len + 1];
            *(char *)((s64)param_1 + str_len + 8) = "cmn_button_fill_nx_b"[str_len];
            if (ch2 == '\0') { str_len++; break; }
            *(char *)((s64)param_1 + str_len + 9) = ch2;
        }
        *(u8 *)((s64)param_1 + (str_len & 0xffffffff) + 8) = 0;
        ch = (u32)(u8)param_1[2];
        hash = 0x811c9dc5;
        param_1[1] = (u32)str_len;
        if ((u8)param_1[2] != 0) {
            str_ptr = (u8 *)((s64)param_1 + 9);
            hash = 0x811c9dc5;
            do { hash = hash * 0x89 ^ ch; ch = (u32)*str_ptr; str_ptr++; } while (ch != 0);
        }
LAB_7103393f60:
        *param_1 = hash;
        return;
    }
LAB_7103393a70:
    *param_1 = hash;
    return;
LAB_return_empty:
    *(u8 *)(param_1 + 2) = 0;
    param_1[0] = 0;
    param_1[1] = 0;
    return;
}
