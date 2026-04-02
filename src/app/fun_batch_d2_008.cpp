#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-008
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x7103392a80 — button fill name → FNV-1a hash40 writer; param_2=controller type, param_3=button bitmask (5376 bytes)
// Note: fun_triage.csv lists entry at 0x71033934b0 (FUN_71033934b0) which falls inside this function
void FUN_7103392a80(u32 *param_1, u32 param_2, s32 param_3)
{
    char cVar1;
    u32 uVar2;
    u64 uVar3;
    u8 *pbVar4;
    u32 uVar5;

    if (param_2 == 6) {
        if (param_3 < 0x80) {
            switch (param_3) {
            case 1:
                *(u8 *)(param_1 + 6) = 0;
                param_1[0] = 0;
                param_1[1] = 0x10;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                uVar2 = 0x811c9dc5;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x70755f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 2:
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x13;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x69725f63;
                param_1[6] = 0x746867;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 4:
                *(u8 *)((s64)param_1 + 0x1a) = 0;
                param_1[0] = 0;
                param_1[1] = 0x12;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x6f645f63;
                uVar2 = 0x811c9dc5;
                *(u16 *)(param_1 + 6) = 0x6e77;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 8:
                *(u8 *)((s64)param_1 + 0x1a) = 0;
                param_1[0] = 0;
                param_1[1] = 0x12;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x656c5f63;
                uVar2 = 0x811c9dc5;
                *(u16 *)(param_1 + 6) = 0x7466;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 0x10:
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x785f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 0x20:
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x615f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            case 0x40:
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x625f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
        } else if (param_3 < 0x200) {
            if (param_3 == 0x80) {
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x795f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
            if (param_3 == 0x100) {
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x6c5f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
        } else {
            if (param_3 == 0x200) {
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x725f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
            if (param_3 == 0x800) {
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0xf;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x7a5f63;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
            if (param_3 == 0x40000) {
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x13;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x675f6e6f;
                param_1[5] = 0x74735f63;
                param_1[6] = 0x747261;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                *param_1 = uVar2;
                return;
            }
        }
        goto LAB_return_empty;
    }
    if ((param_2 | 4) != 5) {
        if (param_2 == 4) {
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
                        uVar2 = 0x811c9dc5;
                        param_1[6] = 0x70755f6e;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
                        return;
                    }
                    if (param_3 == 0x20) {
                        uVar2 = 0x811c9dc5;
                        param_1[0] = 0;
                        param_1[1] = 0x17;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x68676972;
                        *(u16 *)((s64)param_1 + 0x1e) = 0x74;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                        uVar2 = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x6e776f64;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                        uVar2 = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x7466656c;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                    for (uVar3 = 0; "cmn_button_fil_nx_stick_btn"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                        cVar1 = "cmn_button_fil_nx_stick_btn"[uVar3 + 1];
                        *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fil_nx_stick_btn"[uVar3];
                        if (cVar1 == '\0') { uVar3++; break; }
                        *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                    }
                    *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                    uVar5 = (u32)(u8)param_1[2];
                    uVar2 = 0x811c9dc5;
                    param_1[1] = (u32)uVar3;
                    if ((u8)param_1[2] != 0) {
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        uVar2 = 0x811c9dc5;
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                    }
                    goto LAB_return_with_hash;
                }
                if (param_3 == 0x80000) { param_3 = 0x40000; }
            }
        } else if (param_2 == 3) {
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
                        uVar2 = 0x811c9dc5;
                        param_1[6] = 0x70755f6e;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
                        return;
                    }
                    if (param_3 == 0x20) {
                        uVar2 = 0x811c9dc5;
                        param_1[0] = 0;
                        param_1[1] = 0x17;
                        param_1[2] = 0x5f6e6d63;
                        param_1[3] = 0x74747562;
                        param_1[4] = 0x6a5f6e6f;
                        param_1[5] = 0x6f63796f;
                        *(u16 *)(param_1 + 6) = 0x5f6e;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x68676972;
                        *(u16 *)((s64)param_1 + 0x1e) = 0x74;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                        uVar2 = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x6e776f64;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                        uVar2 = 0x811c9dc5;
                        *(u32 *)((s64)param_1 + 0x1a) = 0x7466656c;
                        uVar5 = 99;
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        *param_1 = uVar2;
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
                    for (uVar3 = 0; "cmn_button_fil_nx_stick_btn"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                        cVar1 = "cmn_button_fil_nx_stick_btn"[uVar3 + 1];
                        *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fil_nx_stick_btn"[uVar3];
                        if (cVar1 == '\0') { uVar3++; break; }
                        *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                    }
                    *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                    uVar5 = (u32)(u8)param_1[2];
                    uVar2 = 0x811c9dc5;
                    param_1[1] = (u32)uVar3;
                    if ((u8)param_1[2] != 0) {
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        uVar2 = 0x811c9dc5;
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                    }
                    goto LAB_return_with_hash;
                }
                if (param_3 == 0x40000) { param_3 = 0x80000; }
            }
        } else if (param_2 == 2) {
            if (param_3 == 0x800) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_zr"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_zr"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_zr"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
LAB_return_with_hash:
                *param_1 = uVar2;
                return;
            }
            if (param_3 == 0x400) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_zl"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_zl"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_zl"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
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
                        for (uVar3 = 0; "cmn_button_fill_nx_round_plus"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                            cVar1 = "cmn_button_fill_nx_round_plus"[uVar3 + 1];
                            *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_round_plus"[uVar3];
                            if (cVar1 == '\0') { uVar3++; break; }
                            *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                        }
                        *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                        uVar5 = (u32)(u8)param_1[2];
                        uVar2 = 0x811c9dc5;
                        param_1[1] = (u32)uVar3;
                        if ((u8)param_1[2] != 0) {
                            pbVar4 = (u8 *)((s64)param_1 + 9);
                            uVar2 = 0x811c9dc5;
                            do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                        }
                        goto LAB_7103393f60;
                    }
                    goto LAB_7103393a08;
                }
                if (param_3 == 0x80000) {
                    param_1[0] = 0;
                    param_1[1] = 0;
                    for (uVar3 = 0; "cmn_button_fill_nx_round_minus"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                        cVar1 = "cmn_button_fill_nx_round_minus"[uVar3 + 1];
                        *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_round_minus"[uVar3];
                        if (cVar1 == '\0') { uVar3++; break; }
                        *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                    }
                    *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                    uVar5 = (u32)(u8)param_1[2];
                    uVar2 = 0x811c9dc5;
                    param_1[1] = (u32)uVar3;
                    if ((u8)param_1[2] != 0) {
                        pbVar4 = (u8 *)((s64)param_1 + 9);
                        uVar2 = 0x811c9dc5;
                        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
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
LAB_7103393a08:
                uVar2 = 0x811c9dc5;
                param_1[0] = 0;
                param_1[1] = 0x15;
                param_1[2] = 0x5f6e6d63;
                param_1[3] = 0x74747562;
                param_1[4] = 0x6e5f6e6f;
                param_1[5] = 0x74735f78;
                *(u16 *)(param_1 + 6) = 0x6369;
                *(u32 *)((s64)param_1 + 0x1a) = 0x725f6b;
                uVar5 = 99;
                pbVar4 = (u8 *)((s64)param_1 + 9);
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                goto LAB_7103393a70;
            }
            if (((param_3 != 0x200000) && (param_3 != 0x400000)) && (param_3 != 0x800000))
                goto LAB_return_empty;
        }
        uVar2 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x15;
        param_1[2] = 0x5f6e6d63;
        param_1[3] = 0x74747562;
        param_1[4] = 0x6e5f6e6f;
        param_1[5] = 0x74735f78;
        *(u16 *)(param_1 + 6) = 0x6369;
        *(u32 *)((s64)param_1 + 0x1a) = 0x6c5f6b;
        uVar5 = 99;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        goto LAB_7103393a70;
    }
    if (0x7f < param_3) {
        if (param_3 < 0x400) {
            if (param_3 == 0x80) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_y"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_y"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_y"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    uVar2 = 0x811c9dc5;
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
            } else if (param_3 == 0x100) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_l"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_l"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_l"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    uVar2 = 0x811c9dc5;
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
            } else {
                if (param_3 != 0x200) goto LAB_return_empty;
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_r"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_r"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_r"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
            }
            goto LAB_7103393f60;
        }
        if (param_3 < 0x1000) {
            if (param_3 == 0x400) {
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_zl"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_zl"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_zl"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
            } else {
                if (param_3 != 0x800) goto LAB_return_empty;
                param_1[0] = 0;
                param_1[1] = 0;
                for (uVar3 = 0; "cmn_button_fill_nx_zr"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                    cVar1 = "cmn_button_fill_nx_zr"[uVar3 + 1];
                    *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_zr"[uVar3];
                    if (cVar1 == '\0') { uVar3++; break; }
                    *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
                }
                *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
                uVar5 = (u32)(u8)param_1[2];
                uVar2 = 0x811c9dc5;
                param_1[1] = (u32)uVar3;
                if ((u8)param_1[2] != 0) {
                    pbVar4 = (u8 *)((s64)param_1 + 9);
                    do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
                }
            }
            goto LAB_7103393f60;
        }
        if (param_3 != 0x1000) {
            if (param_3 != 0x2000) goto LAB_return_empty;
LAB_7103393978:
            param_1[0] = 0;
            param_1[1] = 0;
            for (uVar3 = 0; "cmn_button_fill_nx_sr"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
                cVar1 = "cmn_button_fill_nx_sr"[uVar3 + 1];
                *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_sr"[uVar3];
                if (cVar1 == '\0') { uVar3++; break; }
                *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
            }
            *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
            uVar5 = (u32)(u8)param_1[2];
            uVar2 = 0x811c9dc5;
            param_1[1] = (u32)uVar3;
            if ((u8)param_1[2] != 0) {
                pbVar4 = (u8 *)((s64)param_1 + 9);
                uVar2 = 0x811c9dc5;
                do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
            }
            goto LAB_7103393f60;
        }
LAB_7103393a78:
        param_1[0] = 0;
        param_1[1] = 0;
        for (uVar3 = 0; "cmn_button_fill_nx_sl"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
            cVar1 = "cmn_button_fill_nx_sl"[uVar3 + 1];
            *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_sl"[uVar3];
            if (cVar1 == '\0') { uVar3++; break; }
            *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
        }
        *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
        uVar5 = (u32)(u8)param_1[2];
        uVar2 = 0x811c9dc5;
        param_1[1] = (u32)uVar3;
        if ((u8)param_1[2] != 0) {
            pbVar4 = (u8 *)((s64)param_1 + 9);
            uVar2 = 0x811c9dc5;
            do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        }
        goto LAB_7103393f60;
    }
    switch (param_3) {
    case 1:
        *(u8 *)(param_1 + 6) = 0;
        param_1[0] = 0;
        param_1[1] = 0x10;
        param_1[2] = 0x5f6e6d63;
        param_1[3] = 0x74747562;
        uVar2 = 0x811c9dc5;
        param_1[4] = 0x6e5f6e6f;
        param_1[5] = 0x70755f78;
        uVar5 = 99;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    case 2:
        uVar2 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f6e6d63;
        param_1[3] = 0x74747562;
        param_1[4] = 0x6e5f6e6f;
        param_1[5] = 0x69725f78;
        param_1[6] = 0x746867;
        uVar5 = 99;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    default:
        goto LAB_return_empty;
    case 4:
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[0] = 0;
        param_1[1] = 0x12;
        param_1[2] = 0x5f6e6d63;
        param_1[3] = 0x74747562;
        param_1[4] = 0x6e5f6e6f;
        param_1[5] = 0x6f645f78;
        uVar2 = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x6e77;
        uVar5 = 99;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    case 8:
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[0] = 0;
        param_1[1] = 0x12;
        param_1[2] = 0x5f6e6d63;
        param_1[3] = 0x74747562;
        param_1[4] = 0x6e5f6e6f;
        param_1[5] = 0x656c5f78;
        uVar2 = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x7466;
        uVar5 = 99;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    case 0x10:
        param_1[0] = 0;
        param_1[1] = 0;
        for (uVar3 = 0; "cmn_button_fill_nx_x"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
            cVar1 = "cmn_button_fill_nx_x"[uVar3 + 1];
            *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_x"[uVar3];
            if (cVar1 == '\0') { uVar3++; break; }
            *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
        }
        *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
        uVar5 = (u32)(u8)param_1[2];
        uVar2 = 0x811c9dc5;
        param_1[1] = (u32)uVar3;
        if ((u8)param_1[2] != 0) {
            pbVar4 = (u8 *)((s64)param_1 + 9);
            uVar2 = 0x811c9dc5;
            do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        }
        goto LAB_7103393f60;
    case 0x20:
        param_1[0] = 0;
        param_1[1] = 0;
        for (uVar3 = 0; "cmn_button_fill_nx_a"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
            cVar1 = "cmn_button_fill_nx_a"[uVar3 + 1];
            *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_a"[uVar3];
            if (cVar1 == '\0') { uVar3++; break; }
            *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
        }
        *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
        uVar5 = (u32)(u8)param_1[2];
        uVar2 = 0x811c9dc5;
        param_1[1] = (u32)uVar3;
        if ((u8)param_1[2] != 0) {
            pbVar4 = (u8 *)((s64)param_1 + 9);
            uVar2 = 0x811c9dc5;
            do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        }
        goto LAB_7103393f60;
    case 0x40:
        param_1[0] = 0;
        param_1[1] = 0;
        for (uVar3 = 0; "cmn_button_fill_nx_b"[uVar3] != '\0'; uVar3 = uVar3 + 2) {
            cVar1 = "cmn_button_fill_nx_b"[uVar3 + 1];
            *(char *)((s64)param_1 + uVar3 + 8) = "cmn_button_fill_nx_b"[uVar3];
            if (cVar1 == '\0') { uVar3++; break; }
            *(char *)((s64)param_1 + uVar3 + 9) = cVar1;
        }
        *(u8 *)((s64)param_1 + (uVar3 & 0xffffffff) + 8) = 0;
        uVar5 = (u32)(u8)param_1[2];
        uVar2 = 0x811c9dc5;
        param_1[1] = (u32)uVar3;
        if ((u8)param_1[2] != 0) {
            pbVar4 = (u8 *)((s64)param_1 + 9);
            uVar2 = 0x811c9dc5;
            do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        }
LAB_7103393f60:
        *param_1 = uVar2;
        return;
    }
LAB_7103393a70:
    *param_1 = uVar2;
    return;
LAB_return_empty:
    *(u8 *)(param_1 + 2) = 0;
    param_1[0] = 0;
    param_1[1] = 0;
    return;
}
