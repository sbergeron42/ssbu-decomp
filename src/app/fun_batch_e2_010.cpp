#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-010
// Pool-e worker: auto-generated from Ghidra decompilation
// Pattern: WorkModule flag setters — *(*(*(param_1-8)+0x1a0)+0x68) vtable dispatch

// Macro helper for readability (not used, but documents the pattern):
// plVar1 = *(*(*(param_1-8)+0x1a0)+0x68); lVar2 = vtable[0x60](plVar1,idx); *(u8*)(lVar2+off)=val

// 0x7102223fc0 — WorkModule.get(4).flag[0x31]=1
u64 FUN_7102223fc0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 4);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102224000 — WorkModule.get(4).flag[0x31]=0
u64 FUN_7102224000(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 4);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x7102225ae0 — WorkModule.get(5).flag[0x30]=1
u64 FUN_7102225ae0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 5);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102225bc0 — WorkModule.get(5).flag[0x31]=1
u64 FUN_7102225bc0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 5);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102227c00 — WorkModule.get(6).flag[0x30]=1
u64 FUN_7102227c00(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 6);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102227ce0 — WorkModule.get(6).flag[0x31]=1
u64 FUN_7102227ce0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 6);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102227d20 — WorkModule.get(6).flag[0x31]=0
u64 FUN_7102227d20(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 6);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x7102229da0 — WorkModule.get(7).flag[0x30]=1
u64 FUN_7102229da0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 7);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102229e80 — WorkModule.get(7).flag[0x31]=1
u64 FUN_7102229e80(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 7);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102229ec0 — WorkModule.get(7).flag[0x31]=0
u64 FUN_7102229ec0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 7);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x710222dc20 — WorkModule.get(8).flag[0x30]=1
u64 FUN_710222dc20(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 8);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x710222dd00 — WorkModule.get(8).flag[0x31]=1
u64 FUN_710222dd00(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 8);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x710222dd40 — WorkModule.get(8).flag[0x31]=0
u64 FUN_710222dd40(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 8);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x710222bde0 — WorkModule.get(9).flag[0x30]=1
u64 FUN_710222bde0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 9);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x710222bec0 — WorkModule.get(9).flag[0x31]=1
u64 FUN_710222bec0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 9);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x710222bf00 — WorkModule.get(9).flag[0x31]=0
u64 FUN_710222bf00(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 9);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x710222cd00 — WorkModule.get(10).flag[0x30]=1
u64 FUN_710222cd00(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 10);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x710222cde0 — WorkModule.get(10).flag[0x31]=1
u64 FUN_710222cde0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 10);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x710222ce20 — WorkModule.get(10).flag[0x31]=0
u64 FUN_710222ce20(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 10);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x710222fa90 — WorkModule.get(0xb).flag[0x30]=1
u64 FUN_710222fa90(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xb);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}
