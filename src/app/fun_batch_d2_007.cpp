#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-007
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x71032deaa0 — slot lookup by int key, returns s32* (3072 bytes)
s32 *FUN_71032deaa0(s64 param_1, s32 param_2)
{
    s32 *piVar1;

    if (param_2 != -1) {
        if (*(s32 *)(param_1 + 0xa30) == param_2) {
            return (s32 *)(param_1 + 0xce8);
        }
        if (*(s32 *)(param_1 + 0xe30) == param_2) {
            piVar1 = (s32 *)(param_1 + 0xe30);
        } else {
            if (*(s32 *)(param_1 + 0x1230) == param_2) { return (s32 *)(param_1 + 0x14e8); }
            if (*(s32 *)(param_1 + 0x1630) == param_2) { return (s32 *)(param_1 + 0x18e8); }
            if (*(s32 *)(param_1 + 0x1a30) == param_2) { return (s32 *)(param_1 + 0x1ce8); }
            if (*(s32 *)(param_1 + 0x1e30) == param_2) { return (s32 *)(param_1 + 0x20e8); }
            if (*(s32 *)(param_1 + 0x2230) == param_2) { return (s32 *)(param_1 + 0x24e8); }
            if (*(s32 *)(param_1 + 0x2630) == param_2) { return (s32 *)(param_1 + 0x28e8); }
            if (*(s32 *)(param_1 + 0x2a30) == param_2) { return (s32 *)(param_1 + 0x2ce8); }
            if (*(s32 *)(param_1 + 0x2e30) == param_2) { return (s32 *)(param_1 + 0x30e8); }
            if (*(s32 *)(param_1 + 0x3230) == param_2) { return (s32 *)(param_1 + 0x34e8); }
            if (*(s32 *)(param_1 + 0x3630) == param_2) { return (s32 *)(param_1 + 0x38e8); }
            if (*(s32 *)(param_1 + 0x3a30) == param_2) { return (s32 *)(param_1 + 0x3ce8); }
            if (*(s32 *)(param_1 + 0x3e30) == param_2) { return (s32 *)(param_1 + 0x40e8); }
            piVar1 = (s32 *)(param_1 + 0x4230);
            if (*piVar1 != param_2) {
                if (*(s32 *)(param_1 + 0x4630) == param_2) { return (s32 *)(param_1 + 0x48e8); }
                if (*(s32 *)(param_1 + 0x4a30) == param_2) { return (s32 *)(param_1 + 0x4ce8); }
                if (*(s32 *)(param_1 + 0x4e30) == param_2) { return (s32 *)(param_1 + 0x50e8); }
                if (*(s32 *)(param_1 + 0x5230) == param_2) { return (s32 *)(param_1 + 0x54e8); }
                if (*(s32 *)(param_1 + 0x5630) == param_2) { return (s32 *)(param_1 + 0x58e8); }
                if (*(s32 *)(param_1 + 0x5a30) == param_2) { return (s32 *)(param_1 + 0x5ce8); }
                if (*(s32 *)(param_1 + 0x5e30) == param_2) { return (s32 *)(param_1 + 0x60e8); }
                if (*(s32 *)(param_1 + 0x6230) == param_2) { return (s32 *)(param_1 + 0x64e8); }
                if (*(s32 *)(param_1 + 0x6630) == param_2) { return (s32 *)(param_1 + 0x68e8); }
                if (*(s32 *)(param_1 + 0x6a30) == param_2) { return (s32 *)(param_1 + 0x6ce8); }
                if (*(s32 *)(param_1 + 0x6e30) == param_2) { return (s32 *)(param_1 + 0x70e8); }
                if (*(s32 *)(param_1 + 0x7230) == param_2) { return (s32 *)(param_1 + 0x74e8); }
                if (*(s32 *)(param_1 + 0x7630) == param_2) { return (s32 *)(param_1 + 0x78e8); }
                if (*(s32 *)(param_1 + 0x7a30) == param_2) { return (s32 *)(param_1 + 0x7ce8); }
                if (*(s32 *)(param_1 + 0x7e30) == param_2) { return (s32 *)(param_1 + 0x80e8); }
                piVar1 = (s32 *)(param_1 + 0x8230);
                if (((((((*piVar1 != param_2) &&
                          (piVar1 = (s32 *)(param_1 + 0x8630), *piVar1 != param_2)) &&
                         (piVar1 = (s32 *)(param_1 + 0x8a30), *piVar1 != param_2)) &&
                        (((piVar1 = (s32 *)(param_1 + 0x8e30), *piVar1 != param_2 &&
                           (piVar1 = (s32 *)(param_1 + 0x9230), *piVar1 != param_2)) &&
                          ((piVar1 = (s32 *)(param_1 + 0x9630), *piVar1 != param_2 &&
                            ((piVar1 = (s32 *)(param_1 + 0x9a30), *piVar1 != param_2 &&
                              (piVar1 = (s32 *)(param_1 + 0x9e30), *piVar1 != param_2)))))))) &&
                       (piVar1 = (s32 *)(param_1 + 0xa230), *piVar1 != param_2)) &&
                      (((((((piVar1 = (s32 *)(param_1 + 0xa630), *piVar1 != param_2 &&
                              (piVar1 = (s32 *)(param_1 + 0xaa30), *piVar1 != param_2)) &&
                             (piVar1 = (s32 *)(param_1 + 0xae30), *piVar1 != param_2)) &&
                            ((piVar1 = (s32 *)(param_1 + 0xb230), *piVar1 != param_2 &&
                              (piVar1 = (s32 *)(param_1 + 0xb630), *piVar1 != param_2)))) &&
                           (piVar1 = (s32 *)(param_1 + 0xba30), *piVar1 != param_2)) &&
                          ((((piVar1 = (s32 *)(param_1 + 0xbe30), *piVar1 != param_2 &&
                               (piVar1 = (s32 *)(param_1 + 0xc230), *piVar1 != param_2)) &&
                              (((piVar1 = (s32 *)(param_1 + 0xc630), *piVar1 != param_2 &&
                                 (((piVar1 = (s32 *)(param_1 + 0xca30), *piVar1 != param_2 &&
                                    (piVar1 = (s32 *)(param_1 + 0xce30), *piVar1 != param_2)) &&
                                   (piVar1 = (s32 *)(param_1 + 0xd230), *piVar1 != param_2)))) &&
                                (((piVar1 = (s32 *)(param_1 + 0xd630), *piVar1 != param_2 &&
                                   (piVar1 = (s32 *)(param_1 + 0xda30), *piVar1 != param_2)) &&
                                  (piVar1 = (s32 *)(param_1 + 0xde30), *piVar1 != param_2)))))) &&
                           ((piVar1 = (s32 *)(param_1 + 0xe230), *piVar1 != param_2 &&
                             (piVar1 = (s32 *)(param_1 + 0xe630), *piVar1 != param_2)))))) &&
                         (((piVar1 = (s32 *)(param_1 + 0xea30), *piVar1 != param_2 &&
                             (((piVar1 = (s32 *)(param_1 + 0xee30), *piVar1 != param_2 &&
                                (piVar1 = (s32 *)(param_1 + 0xf230), *piVar1 != param_2)) &&
                               (piVar1 = (s32 *)(param_1 + 0xf630), *piVar1 != param_2)))) &&
                            (((piVar1 = (s32 *)(param_1 + 0xfa30), *piVar1 != param_2 &&
                               (piVar1 = (s32 *)(param_1 + 0xfe30), *piVar1 != param_2)) &&
                              ((piVar1 = (s32 *)(param_1 + 0x10230), *piVar1 != param_2 &&
                                (piVar1 = (s32 *)(param_1 + 0x10630), *piVar1 != param_2)))))))))))
                    goto LAB_71032df050;
            }
        }
        return piVar1 + 0xae;
    }
LAB_71032df050:
    return (s32 *)(param_1 + 0x8d8);
}

// 0x71032e0ef0 — check if s32 key is present in slot array (1920 bytes)
bool FUN_71032e0ef0(s64 param_1, s32 param_2)
{
    if (param_2 == -1) { return false; }
    if (*(s32 *)(param_1 + 0xa30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xe30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x1230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x1630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x1a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x1e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x2230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x2630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x2a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x2e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x3230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x3630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x3a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x3e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x4230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x4630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x4a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x4e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x5230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x5630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x5a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x5e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x6230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x6630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x6a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x6e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x7230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x7630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x7a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x7e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x8230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x8630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x8a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x8e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x9230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x9630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x9a30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x9e30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xa230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xa630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xaa30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xae30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xb230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xb630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xba30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xbe30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xc230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xc630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xca30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xce30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xd230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xd630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xda30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xde30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xe230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xe630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xea30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xee30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xf230) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xf630) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xfa30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0xfe30) == param_2) { return true; }
    if (*(s32 *)(param_1 + 0x10230) == param_2) { return true; }
    return *(s32 *)(param_1 + 0x10630) == param_2;
}
