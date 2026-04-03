#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-014
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8 PTR_DAT_71052a22d8[] HIDDEN;

// External FUN_* forward declarations
extern void FUN_7100082590(u64, u64 *, u64, u32);
extern void FUN_71000397f0(s64);
extern void FUN_71000399d0(s64, u64);
extern void FUN_7100039580(s64, u64);
extern void FUN_7100099520(s64, u64);

// ---- Functions ---------------------------------------------------------------
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
// 0x71000a4f20 — InitializeEmitter: copy u64 field from system to emitter (16 bytes)
void FUN_71000a4f20(s64 param_1, s64 param_2)
{
    *(u64 *)(param_2 + 0x98) = *(u64 *)(param_1 + 0x8c0);
}
