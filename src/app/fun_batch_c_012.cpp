// Batch C - 012: Module vtable flag patterns
// Functions: 40 — All follow the same pattern:
//   1. Navigate *(*(*(param_1 - 8) + 0x1a0) + 0x68) to get a module pointer
//   2. Call vtable[0x60/8] on the module with an index to get a sub-entry
//   3. Set a flag byte at entry+0x30 or entry+0x31 to 0 or 1

#include "types.h"

// 0x7102208730
u32 FUN_7102208730(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102208770
u32 FUN_7102208770(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xd);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102208810
u32 FUN_7102208810(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102208850
u32 FUN_7102208850(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xd);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710221c620
u32 FUN_710221c620(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s32))(*module + 0x60))(module, 0);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710221c700
u32 FUN_710221c700(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s32))(*module + 0x60))(module, 0);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710221e780
u32 FUN_710221e780(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 1);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x710221e860
u32 FUN_710221e860(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 1);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x71022208e0
u32 FUN_71022208e0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x71022209c0
u32 FUN_71022209c0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102220a00
u32 FUN_7102220a00(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x71022220e0
u32 FUN_71022220e0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 3);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x71022221c0
u32 FUN_71022221c0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 3);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102222200
u32 FUN_7102222200(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 3);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102222240
u32 FUN_7102222240(s64 param_1)
{
    s64 *module;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    module = (s64 *)(**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 3);
    (**(void (**)(void))(*module + 0x48))();
    return 0;
}

// 0x7102223ee0
u32 FUN_7102223ee0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 4);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102223fc0
u32 FUN_7102223fc0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 4);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102224000
u32 FUN_7102224000(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 4);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102225ae0
u32 FUN_7102225ae0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 5);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102225bc0
u32 FUN_7102225bc0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 5);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102227c00
u32 FUN_7102227c00(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 6);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102227ce0
u32 FUN_7102227ce0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 6);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102227d20
u32 FUN_7102227d20(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 6);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102229da0
u32 FUN_7102229da0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 7);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102229e80
u32 FUN_7102229e80(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 7);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102229ec0
u32 FUN_7102229ec0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 7);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222bde0
u32 FUN_710222bde0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 9);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222bec0
u32 FUN_710222bec0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 9);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222bf00
u32 FUN_710222bf00(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 9);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222cd00
u32 FUN_710222cd00(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xa);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222cde0
u32 FUN_710222cde0(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xa);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222ce20
u32 FUN_710222ce20(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xa);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222dc20
u32 FUN_710222dc20(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 8);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222dd00
u32 FUN_710222dd00(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 8);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222dd40
u32 FUN_710222dd40(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 8);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222fa90
u32 FUN_710222fa90(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xb);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222fb70
u32 FUN_710222fb70(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xb);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102230c40
u32 FUN_7102230c40(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102230d20
u32 FUN_7102230d20(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102230d60
u32 FUN_7102230d60(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 0xc);
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}
