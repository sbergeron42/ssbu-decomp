#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-014
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8 PTR_DAT_71052a22d8[];

// External FUN_* forward declarations
extern void FUN_7100082590(u64, u64 *, u64, u32);
extern void FUN_71000397f0(s64);
extern void FUN_71000399d0(s64, u64);
extern void FUN_7100039580(s64, u64);

// ---- Functions ---------------------------------------------------------------

// 0x710007d490 — empty stub (32 bytes)
void FUN_710007d490(void)
{
}

// 0x710007d8a0 — empty stub (32 bytes)
void FUN_710007d8a0(void)
{
}

// 0x710007db60 — empty stub (16 bytes)
void FUN_710007db60(void)
{
}

// 0x710007db70 — empty stub (16 bytes)
void FUN_710007db70(void)
{
}

// 0x710007db80 — empty stub (16 bytes)
void FUN_710007db80(void)
{
}

// 0x710007db90 — empty stub (96 bytes)
void FUN_710007db90(void)
{
}

// 0x7100082550 — float subtraction: call sub, return local_18 - local_20 (48 bytes)
float FUN_7100082550(u64 param_1, u64 param_2, u32 param_3)
{
    u64 local_20;
    u64 local_18;

    local_20 = 0;
    local_18 = 0;
    FUN_7100082590(param_1, &local_20, param_2, param_3);
    return (float)local_18 - (float)local_20;
}

// 0x71000837a0 — unicode filter: return 0 for zero-width/format chars, 1 otherwise (64 bytes)
u64 FUN_71000837a0(u32 param_1)
{
    if ((param_1 & 0xffffff00) == 0x2000) {
        switch (param_1) {
        case 0x200b:
        case 0x200e:
        case 0x200f:
        case 0x202a:
        case 0x202b:
        case 0x202c:
        case 0x202d:
        case 0x202e:
        case 0x2060:
            return 0;
        }
        if (param_1 - 0x2066 < 4) {
            return 0;
        }
    }
    return 1;
}

// 0x7100086d10 — GetShader: if index==3 return null, else deref-chain into shader table (64 bytes)
u64 FUN_7100086d10(s64 param_1)
{
    if (*(u32 *)(param_1 + 0x10) == 3) {
        return 0;
    }
    return *(u64 *)(*(s64 *)(*(s64 *)(param_1 + 8) + 0x238) +
                    (u64)*(u32 *)(param_1 + 0x10) * 8 + 0x340);
}

// 0x7100088970 — SetDrawPath: store drawPathFlag at +0x400 (16 bytes)
void FUN_7100088970(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x400) = param_2;
}

// 0x7100088a00 — SetColor0: copy 16 bytes from vector into emitter +0x420 (32 bytes)
void FUN_7100088a00(s64 param_1, u64 *param_2)
{
    *(u64 *)(param_1 + 0x428) = *(u64 *)((s64)param_2 + 8);
    *(u64 *)(param_1 + 0x420) = *(u64 *)param_2;
}

// 0x710008a240 — setter: write 1 to byte at param_1+9 (48 bytes)
void FUN_710008a240(s64 param_1)
{
    *(u8 *)(param_1 + 9) = 1;
}

// 0x710008a3e0 — deref-compare: return ptr if non-null and count matches +0x2c, else 0 (48 bytes)
s64 FUN_710008a3e0(s64 *param_1)
{
    s64 lVar1;

    lVar1 = *param_1;
    if (lVar1 != 0) {
        if ((s32)param_1[1] != *(s32 *)(lVar1 + 0x2c)) {
            lVar1 = 0;
        }
        return lVar1;
    }
    return 0;
}

// 0x710008a740 — delegate: three sub-calls at fixed offsets (16 bytes)
void FUN_710008a740(s64 param_1, u64 param_2)
{
    FUN_71000397f0(param_1 + 0x120);
    FUN_71000399d0(param_1 + 0x148, param_2);
    FUN_7100039580(param_1 + 0x164, param_2);
}

// 0x710008d090 — empty stub (16 bytes)
void FUN_710008d090(void)
{
}

// 0x7100093650 — empty stub — nn::vfx::detail::Warning (16 bytes)
void FUN_7100093650(u64 param_1, u32 param_2)
{
}

// 0x710009c310 — Invalidate: clear first byte (16 bytes)
void FUN_710009c310(u8 *param_1)
{
    *param_1 = 0;
}

// 0x710009c320 — InitializeShader: table-lookup offset chain, set ptr field and flag (48 bytes)
bool FUN_710009c320(s64 param_1, s64 param_2, u32 param_3)
{
    *(u64 *)(param_1 + 8) = *(u64 *)(*(s64 *)(param_2 +
                                *(s64 *)(PTR_DAT_71052a22d8 + (u64)param_3 * 8)) + 0x68);
    *(u8 *)param_1 = 1;
    return true;
}

// 0x710009c9c0 — ShaderManager ctor: zero-init 7 fields (32 bytes)
void FUN_710009c9c0(s64 param_1)
{
    *(u8 *)param_1 = 0;
    *(u64 *)(param_1 + 8) = 0;
    *(u32 *)(param_1 + 0x10) = 0;
    *(u32 *)(param_1 + 0x30) = 0;
    *(u64 *)(param_1 + 0x18) = 0;
    *(u64 *)(param_1 + 0x20) = 0;
    *(u64 *)(param_1 + 0x28) = 0;
}

// 0x710009ce30 — ComputeShaderManager ctor: zero-init 4 fields (16 bytes)
void FUN_710009ce30(s64 param_1)
{
    *(u8 *)param_1 = 0;
    *(u32 *)(param_1 + 0x28) = 0;
    *(u64 *)(param_1 + 0x18) = 0;
    *(u64 *)(param_1 + 0x20) = 0;
}

// 0x710009e130 — counter: walk linked list at +0x418, return count + base (48 bytes)
s32 FUN_710009e130(s64 param_1)
{
    s32 iVar1;
    s64 lVar2;

    if (*(s8 *)(*(s64 *)(param_1 + 0x418) + 0x10) == '\0') {
        return 0;
    }
    iVar1 = *(s32 *)(param_1 + 0x2c);
    for (lVar2 = *(s64 *)(*(s64 *)(param_1 + 0x418) + 0x18); lVar2 != 0;
         lVar2 = *(s64 *)(lVar2 + 0x68)) {
        iVar1 = iVar1 + 1;
    }
    return iVar1;
}

// 0x71000a3920 — counter: walk linked list at +0x418, return count + base (48 bytes)
s32 FUN_71000a3920(s64 param_1)
{
    s32 iVar1;
    s64 lVar2;

    if (*(s8 *)(*(s64 *)(param_1 + 0x418) + 0x10) == '\0') {
        return 0;
    }
    iVar1 = *(s32 *)(param_1 + 0x2c);
    for (lVar2 = *(s64 *)(*(s64 *)(param_1 + 0x418) + 0x18); lVar2 != 0;
         lVar2 = *(s64 *)(lVar2 + 0x68)) {
        iVar1 = iVar1 + 1;
    }
    return iVar1;
}

// 0x71000a4f20 — InitializeEmitter: copy u64 field from system to emitter (16 bytes)
void FUN_71000a4f20(s64 param_1, s64 param_2)
{
    *(u64 *)(param_2 + 0x98) = *(u64 *)(param_1 + 0x8c0);
}
