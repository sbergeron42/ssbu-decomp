// Batch C - 014: MEDIUM FUN_* batch decompilation (upper 0x7102 range)
// Functions: 8 - Misc patterns from 0x7102a-0x7102f range

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
    s64 inner;
    inner = *(s64 *)(param_1 + 0x10);
    if (inner != 0) {
        *(u8 *)(inner + 0x110) = param_2 & 1;
        FUN_71025e9900(inner + 0x108);
    }
}

// 0x7102a676b0
void FUN_7102a676b0(s64 param_1)
{
    u64 *end;
    u64 *cur;
    end = *(u64 **)(param_1 + 0x28);
    for (cur = *(u64 **)(param_1 + 0x20); cur != end; cur = cur + 2) {
        FUN_71025f4930(*(u64 *)*cur, ((u64 *)*cur)[1], 1);
    }
}

// 0x7102fe2308
u64 FUN_7102fe2308()
{
    s32 count;
    count = FUN_7102ff3000();
    if (count < 2) {
        return 1;
    }
    return 0;
}

// 0x7102c561a8
bool FUN_7102c561a8(s64 *param_1)
{
    char result;
    result = (**(char (**)(void))(*param_1 + 0x908))();
    return result == 5;
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
    s64 inner;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    inner = *(s64 *)(param_1 + 8);
    if (inner != 0) {
        *(u8 *)(inner + 0xf0) = 1;
        FUN_7102a399d0(**(u64 **)(inner + 0x18));
        if (0x12 < *(u32 *)(inner + 0xdc)) {
            abort();
        }
        *(u32 *)(inner + (s64)(s32)*(u32 *)(inner + 0xdc) * 4 + 0x90) = 1;
    }
}

// 0x7102a36350
void FUN_7102a36350(s64 param_1)
{
    s64 inner;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    inner = *(s64 *)(param_1 + 8);
    if (inner != 0) {
        *(u8 *)(inner + 0xf0) = 1;
        FUN_7102a399d0(**(u64 **)(inner + 0x18));
        if (0x12 < *(u32 *)(inner + 0xdc)) {
            abort();
        }
        *(u32 *)(inner + (s64)(s32)*(u32 *)(inner + 0xdc) * 4 + 0x90) = 1;
    }
}

// 0x7102b6e920
void FUN_7102b6e920(s64 param_1)
{
    s64 *end;
    s64 *cur;
    end = *(s64 **)(param_1 + 0x38);
    for (cur = *(s64 **)(param_1 + 0x30); cur != end; cur = cur + 1) {
        if (*cur != 0) {
            FUN_7102b63b80();
        }
    }
}
