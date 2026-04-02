// Batch C - 014: MEDIUM FUN_* batch decompilation (upper 0x7102 range)
// Functions: 8 - Misc patterns from 0x7102a–0x7102f range

#include "types.h"

extern "C" void FUN_71025e9900(s64);
extern "C" void FUN_71025f4930(u64, u64, s64);
extern "C" s32 FUN_7102ff3000();
extern "C" void FUN_7102a399d0(u64);
extern "C" __attribute__((noreturn)) void abort();
extern "C" void FUN_7102b63b80();

// 0x7102e12870
void FUN_7102e12870(s64 param_1, u8 param_2)
{
    s64 lVar1;
    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 != 0) {
        *(u8 *)(lVar1 + 0x110) = param_2 & 1;
        FUN_71025e9900(lVar1 + 0x108);
    }
}

// 0x7102a676b0
void FUN_7102a676b0(s64 param_1)
{
    u64 *puVar1;
    u64 *puVar2;
    puVar1 = *(u64 **)(param_1 + 0x28);
    for (puVar2 = *(u64 **)(param_1 + 0x20); puVar2 != puVar1; puVar2 = puVar2 + 2) {
        FUN_71025f4930(*(u64 *)*puVar2, ((u64 *)*puVar2)[1], 1);
    }
}

// 0x7102fe2308
u64 FUN_7102fe2308()
{
    s32 iVar1;
    iVar1 = FUN_7102ff3000();
    if (iVar1 < 2) {
        return 1;
    }
    return 0;
}

// 0x7102c561a8
bool FUN_7102c561a8(s64 *param_1)
{
    char cVar1;
    cVar1 = (**(char (**)(void))(*param_1 + 0x908))();
    return cVar1 == 5;
}

// 0x7102a65c84
u32 FUN_7102a65c84(s64 *param_1, s64 param_2)
{
    (**(void (**)(s64 *, u32, u32))(*param_1 + 0x58))(param_1, *(u32 *)(param_2 + 0x20), *(u32 *)(param_2 + 0x10));
    return 0;
}

// 0x7102a364b0
void FUN_7102a364b0(s64 param_1)
{
    s64 lVar1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    lVar1 = *(s64 *)(param_1 + 8);
    if (lVar1 != 0) {
        *(u8 *)(lVar1 + 0xf0) = 1;
        FUN_7102a399d0(**(u64 **)(lVar1 + 0x18));
        if (0x12 < *(u32 *)(lVar1 + 0xdc)) {
            abort();
        }
        *(u32 *)(lVar1 + (s64)(s32)*(u32 *)(lVar1 + 0xdc) * 4 + 0x90) = 1;
    }
}

// 0x7102a36350
void FUN_7102a36350(s64 param_1)
{
    s64 lVar1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    lVar1 = *(s64 *)(param_1 + 8);
    if (lVar1 != 0) {
        *(u8 *)(lVar1 + 0xf0) = 1;
        FUN_7102a399d0(**(u64 **)(lVar1 + 0x18));
        if (0x12 < *(u32 *)(lVar1 + 0xdc)) {
            abort();
        }
        *(u32 *)(lVar1 + (s64)(s32)*(u32 *)(lVar1 + 0xdc) * 4 + 0x90) = 1;
    }
}

// 0x7102b6e920
void FUN_7102b6e920(s64 param_1)
{
    s64 *plVar1;
    s64 *plVar2;
    plVar2 = *(s64 **)(param_1 + 0x38);
    for (plVar1 = *(s64 **)(param_1 + 0x30); plVar1 != plVar2; plVar1 = plVar1 + 1) {
        if (*plVar1 != 0) {
            FUN_7102b63b80();
        }
    }
}
