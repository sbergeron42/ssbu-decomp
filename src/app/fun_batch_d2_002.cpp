#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d2-002
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x71032dbcf0 -- slot lookup by int key, returns pointer into struct at +0xc44..+0x10844 (1776 bytes)
u8 *FUN_71032dbcf0(s64 param_1, s32 param_2)
{
    if (param_2 != -1) {
        if (*(s32 *)(param_1 + 0xa30) == param_2) return (u8 *)(param_1 + 0xc44);
        if (*(s32 *)(param_1 + 0xe30) == param_2) return (u8 *)(param_1 + 0x1044);
        if (*(s32 *)(param_1 + 0x1230) == param_2) return (u8 *)(param_1 + 0x1444);
        if (*(s32 *)(param_1 + 0x1630) == param_2) return (u8 *)(param_1 + 0x1844);
        if (*(s32 *)(param_1 + 0x1a30) == param_2) return (u8 *)(param_1 + 0x1c44);
        if (*(s32 *)(param_1 + 0x1e30) == param_2) return (u8 *)(param_1 + 0x2044);
        if (*(s32 *)(param_1 + 0x2230) == param_2) return (u8 *)(param_1 + 0x2444);
        if (*(s32 *)(param_1 + 0x2630) == param_2) return (u8 *)(param_1 + 0x2844);
        if (*(s32 *)(param_1 + 0x2a30) == param_2) return (u8 *)(param_1 + 0x2c44);
        if (*(s32 *)(param_1 + 0x2e30) == param_2) return (u8 *)(param_1 + 0x3044);
        if (*(s32 *)(param_1 + 0x3230) == param_2) return (u8 *)(param_1 + 0x3444);
        if (*(s32 *)(param_1 + 0x3630) == param_2) return (u8 *)(param_1 + 0x3844);
        if (*(s32 *)(param_1 + 0x3a30) == param_2) return (u8 *)(param_1 + 0x3c44);
        if (*(s32 *)(param_1 + 0x3e30) == param_2) return (u8 *)(param_1 + 0x4044);
        if (*(s32 *)(param_1 + 0x4230) == param_2) return (u8 *)(param_1 + 0x4444);
        if (*(s32 *)(param_1 + 0x4630) == param_2) return (u8 *)(param_1 + 0x4844);
        if (*(s32 *)(param_1 + 0x4a30) == param_2) return (u8 *)(param_1 + 0x4c44);
        if (*(s32 *)(param_1 + 0x4e30) == param_2) return (u8 *)(param_1 + 0x5044);
        if (*(s32 *)(param_1 + 0x5230) == param_2) return (u8 *)(param_1 + 0x5444);
        if (*(s32 *)(param_1 + 0x5630) == param_2) return (u8 *)(param_1 + 0x5844);
        if (*(s32 *)(param_1 + 0x5a30) == param_2) return (u8 *)(param_1 + 0x5c44);
        if (*(s32 *)(param_1 + 0x5e30) == param_2) return (u8 *)(param_1 + 0x6044);
        if (*(s32 *)(param_1 + 0x6230) == param_2) return (u8 *)(param_1 + 0x6444);
        if (*(s32 *)(param_1 + 0x6630) == param_2) return (u8 *)(param_1 + 0x6844);
        if (*(s32 *)(param_1 + 0x6a30) == param_2) return (u8 *)(param_1 + 0x6c44);
        if (*(s32 *)(param_1 + 0x6e30) == param_2) return (u8 *)(param_1 + 0x7044);
        if (*(s32 *)(param_1 + 0x7230) == param_2) return (u8 *)(param_1 + 0x7444);
        if (*(s32 *)(param_1 + 0x7630) == param_2) return (u8 *)(param_1 + 0x7844);
        if (*(s32 *)(param_1 + 0x7a30) == param_2) return (u8 *)(param_1 + 0x7c44);
        if (*(s32 *)(param_1 + 0x7e30) == param_2) return (u8 *)(param_1 + 0x8044);
        if (*(s32 *)(param_1 + 0x8230) == param_2) return (u8 *)(param_1 + 0x8444);
        if (*(s32 *)(param_1 + 0x8630) == param_2) return (u8 *)(param_1 + 0x8844);
        if (*(s32 *)(param_1 + 0x8a30) == param_2) return (u8 *)(param_1 + 0x8c44);
        if (*(s32 *)(param_1 + 0x8e30) == param_2) return (u8 *)(param_1 + 0x9044);
        if (*(s32 *)(param_1 + 0x9230) == param_2) return (u8 *)(param_1 + 0x9444);
        if (*(s32 *)(param_1 + 0x9630) == param_2) return (u8 *)(param_1 + 0x9844);
        if (*(s32 *)(param_1 + 0x9a30) == param_2) return (u8 *)(param_1 + 0x9c44);
        if (*(s32 *)(param_1 + 0x9e30) == param_2) return (u8 *)(param_1 + 0xa044);
        if (*(s32 *)(param_1 + 0xa230) == param_2) return (u8 *)(param_1 + 0xa444);
        if (*(s32 *)(param_1 + 0xa630) == param_2) return (u8 *)(param_1 + 0xa844);
        if (*(s32 *)(param_1 + 0xaa30) == param_2) return (u8 *)(param_1 + 0xac44);
        if (*(s32 *)(param_1 + 0xae30) == param_2) return (u8 *)(param_1 + 0xb044);
        if (*(s32 *)(param_1 + 0xb230) == param_2) return (u8 *)(param_1 + 0xb444);
        if (*(s32 *)(param_1 + 0xb630) == param_2) return (u8 *)(param_1 + 0xb844);
        if (*(s32 *)(param_1 + 0xba30) == param_2) return (u8 *)(param_1 + 0xbc44);
        if (*(s32 *)(param_1 + 0xbe30) == param_2) return (u8 *)(param_1 + 0xc044);
        if (*(s32 *)(param_1 + 0xc230) == param_2) return (u8 *)(param_1 + 0xc444);
        if (*(s32 *)(param_1 + 0xc630) == param_2) return (u8 *)(param_1 + 0xc844);
        if (*(s32 *)(param_1 + 0xca30) == param_2) return (u8 *)(param_1 + 0xcc44);
        if (*(s32 *)(param_1 + 0xce30) == param_2) return (u8 *)(param_1 + 0xd044);
        if (*(s32 *)(param_1 + 0xd230) == param_2) return (u8 *)(param_1 + 0xd444);
        if (*(s32 *)(param_1 + 0xd630) == param_2) return (u8 *)(param_1 + 0xd844);
        if (*(s32 *)(param_1 + 0xda30) == param_2) return (u8 *)(param_1 + 0xdc44);
        if (*(s32 *)(param_1 + 0xde30) == param_2) return (u8 *)(param_1 + 0xe044);
        if (*(s32 *)(param_1 + 0xe230) == param_2) return (u8 *)(param_1 + 0xe444);
        if (*(s32 *)(param_1 + 0xe630) == param_2) return (u8 *)(param_1 + 0xe844);
        if (*(s32 *)(param_1 + 0xea30) == param_2) return (u8 *)(param_1 + 0xec44);
        if (*(s32 *)(param_1 + 0xee30) == param_2) return (u8 *)(param_1 + 0xf044);
        if (*(s32 *)(param_1 + 0xf230) == param_2) return (u8 *)(param_1 + 0xf444);
        if (*(s32 *)(param_1 + 0xf630) == param_2) return (u8 *)(param_1 + 0xf844);
        if (*(s32 *)(param_1 + 0xfa30) == param_2) return (u8 *)(param_1 + 0xfc44);
        if (*(s32 *)(param_1 + 0xfe30) == param_2) return (u8 *)(param_1 + 0x10044);
        if (*(s32 *)(param_1 + 0x10230) == param_2) return (u8 *)(param_1 + 0x10444);
        if (*(s32 *)(param_1 + 0x10630) == param_2) return (u8 *)(param_1 + 0x10844);
    }
    return (u8 *)(param_1 + 0x834);
}

// 0x71032de4e0 -- slot lookup by int key, returns int* pointer into struct (1472 bytes)
s32 *FUN_71032de4e0(s64 param_1, s32 param_2)
{
    s32 *piVar1;

    if (param_2 != -1) {
        if (*(s32 *)(param_1 + 0xa30) == param_2) return (s32 *)(param_1 + 0xce8);
        if (*(s32 *)(param_1 + 0xe30) == param_2) {
            piVar1 = (s32 *)(param_1 + 0xe30);
        } else {
            if (*(s32 *)(param_1 + 0x1230) == param_2) return (s32 *)(param_1 + 0x14e8);
            if (*(s32 *)(param_1 + 0x1630) == param_2) return (s32 *)(param_1 + 0x18e8);
            if (*(s32 *)(param_1 + 0x1a30) == param_2) return (s32 *)(param_1 + 0x1ce8);
            if (*(s32 *)(param_1 + 0x1e30) == param_2) return (s32 *)(param_1 + 0x20e8);
            if (*(s32 *)(param_1 + 0x2230) == param_2) return (s32 *)(param_1 + 0x24e8);
            if (*(s32 *)(param_1 + 0x2630) == param_2) return (s32 *)(param_1 + 0x28e8);
            if (*(s32 *)(param_1 + 0x2a30) == param_2) return (s32 *)(param_1 + 0x2ce8);
            if (*(s32 *)(param_1 + 0x2e30) == param_2) return (s32 *)(param_1 + 0x30e8);
            if (*(s32 *)(param_1 + 0x3230) == param_2) return (s32 *)(param_1 + 0x34e8);
            if (*(s32 *)(param_1 + 0x3630) == param_2) return (s32 *)(param_1 + 0x38e8);
            if (*(s32 *)(param_1 + 0x3a30) == param_2) return (s32 *)(param_1 + 0x3ce8);
            if (*(s32 *)(param_1 + 0x3e30) == param_2) return (s32 *)(param_1 + 0x40e8);
            piVar1 = (s32 *)(param_1 + 0x4230);
            if (*piVar1 != param_2) {
                if (*(s32 *)(param_1 + 0x4630) == param_2) return (s32 *)(param_1 + 0x48e8);
                if (*(s32 *)(param_1 + 0x4a30) == param_2) return (s32 *)(param_1 + 0x4ce8);
                if (*(s32 *)(param_1 + 0x4e30) == param_2) return (s32 *)(param_1 + 0x50e8);
                if (*(s32 *)(param_1 + 0x5230) == param_2) return (s32 *)(param_1 + 0x54e8);
                if (*(s32 *)(param_1 + 0x5630) == param_2) return (s32 *)(param_1 + 0x58e8);
                if (*(s32 *)(param_1 + 0x5a30) == param_2) return (s32 *)(param_1 + 0x5ce8);
                if (*(s32 *)(param_1 + 0x5e30) == param_2) return (s32 *)(param_1 + 0x60e8);
                if (*(s32 *)(param_1 + 0x6230) == param_2) return (s32 *)(param_1 + 0x64e8);
                if (*(s32 *)(param_1 + 0x6630) == param_2) return (s32 *)(param_1 + 0x68e8);
                if (*(s32 *)(param_1 + 0x6a30) == param_2) return (s32 *)(param_1 + 0x6ce8);
                if (*(s32 *)(param_1 + 0x6e30) == param_2) return (s32 *)(param_1 + 0x70e8);
                if (*(s32 *)(param_1 + 0x7230) == param_2) return (s32 *)(param_1 + 0x74e8);
                if (*(s32 *)(param_1 + 0x7630) == param_2) return (s32 *)(param_1 + 0x78e8);
                if (*(s32 *)(param_1 + 0x7a30) == param_2) return (s32 *)(param_1 + 0x7ce8);
                if (*(s32 *)(param_1 + 0x7e30) == param_2) return (s32 *)(param_1 + 0x80e8);
                piVar1 = (s32 *)(param_1 + 0x8230);
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x8630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x8a30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x8e30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x9230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x9630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x9a30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x9e30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xa230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xa630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xaa30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xae30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xb230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xb630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xba30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xbe30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xc230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xc630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xca30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xce30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xd230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xd630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xda30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xde30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xe230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xe630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xea30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xee30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xf230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xf630); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xfa30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0xfe30); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x10230); }
                if (*piVar1 != param_2) { piVar1 = (s32 *)(param_1 + 0x10630); }
                if (*piVar1 != param_2) goto LAB_71032dea90;
            }
        }
        return piVar1 + 0xae;
    }
LAB_71032dea90:
    return (s32 *)(param_1 + 0x8d8);
}
