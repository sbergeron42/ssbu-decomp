#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102-0x7103 address range, batch e2-011
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" void FUN_71032e47c0(u64, s32, s32, s32, s32, s32);
extern "C" u64  DAT_710532e7c8;
extern "C" u32  FUN_7103300dd0();

// ---- WorkModule flag setters (continuation from e2-010) -----------------------------------------------

// 0x710222fb70 — WorkModule.get(0xb).flag[0x31]=1
u64 FUN_710222fb70(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xb);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102230c40 — WorkModule.get(0xc).flag[0x30]=1
u64 FUN_7102230c40(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xc);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102230d20 — WorkModule.get(0xc).flag[0x31]=1
u64 FUN_7102230d20(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xc);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102230d60 — WorkModule.get(0xc).flag[0x31]=0
u64 FUN_7102230d60(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xc);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x7102233bb0 — WorkModule.get(0xd).flag[0x30]=1
u64 FUN_7102233bb0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xd);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102233c90 — WorkModule.get(0xd).flag[0x31]=1
u64 FUN_7102233c90(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xd);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102233cd0 — WorkModule.get(0xd).flag[0x31]=0
u64 FUN_7102233cd0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xd);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// ---- abort() wrappers (12-16 bytes each) -----------------------------------------------
// [[noreturn]] generates stp+mov+bl without epilogue

// 0x710275d7ec
[[noreturn]] void FUN_710275d7ec(void) { abort(); }

// 0x7102a66198
[[noreturn]] void FUN_7102a66198(void) { abort(); }

// 0x7102a66768
[[noreturn]] void FUN_7102a66768(void) { abort(); }

// 0x7102a667c8
[[noreturn]] void FUN_7102a667c8(void) { abort(); }

// 0x7102a66828
[[noreturn]] void FUN_7102a66828(void) { abort(); }

// 0x71031534d0
[[noreturn]] void FUN_71031534d0(void) { abort(); }

// 0x71031535c0
[[noreturn]] void FUN_71031535c0(void) { abort(); }

// 0x71031591e0
[[noreturn]] void FUN_71031591e0(void) { abort(); }

// 0x71031597bc
[[noreturn]] void FUN_71031597bc(void) { abort(); }

// 0x7103169e0c
[[noreturn]] void FUN_7103169e0c(void) { abort(); }

// 0x7103169f30
[[noreturn]] void FUN_7103169f30(void) { abort(); }

// 0x710316a038
[[noreturn]] void FUN_710316a038(void) { abort(); }

// 0x710316a12c
[[noreturn]] void FUN_710316a12c(void) { abort(); }

// 0x710316a5dc
[[noreturn]] void FUN_710316a5dc(void) { abort(); }

// 0x7103176f58
[[noreturn]] void FUN_7103176f58(void) { abort(); }

// 0x710317704c
[[noreturn]] void FUN_710317704c(void) { abort(); }

// 0x7103177240
[[noreturn]] void FUN_7103177240(void) { abort(); }

// 0x7103177420
[[noreturn]] void FUN_7103177420(void) { abort(); }

// 0x710317750c
[[noreturn]] void FUN_710317750c(void) { abort(); }

// 0x7103177600
[[noreturn]] void FUN_7103177600(void) { abort(); }

// 0x710317c0d4
[[noreturn]] void FUN_710317c0d4(void) { abort(); }

// 0x71032f142c
[[noreturn]] void FUN_71032f142c(void) { abort(); }

// 0x7103344c38
[[noreturn]] void FUN_7103344c38(void) { abort(); }

// ---- simple wrappers -----------------------------------------------

// 0x7103366ac0 — FUN_71032e47c0(DAT_710532e7c8+8, 1, 0xfffffffe, 2, 0, 0), return 0
u64 FUN_7103366ac0(void)
{
    FUN_71032e47c0(*(u64 *)((u8 *)&DAT_710532e7c8 + 8), 1, 0xfffffffe, 2, 0, 0);
    return 0;
}

// 0x71033011cc — return FUN_7103300dd0()
u32 FUN_71033011cc(void)
{
    return FUN_7103300dd0();
}
