#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71001xxxxx range, batch d4-012
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: struct inits, bit ops, zero-fill, network ctx, vtable calls, bool checks

// ---- External declarations -----------------------------------------------

// Multiplier for time conversion (FUN_710015d240)
extern u64 PTR_DAT_71052a3cd0;

// Network context pointer (FUN_7100162ce0 / 7100163d40)
extern u64 PTR_DAT_71052a3bd8;

// Vtable bases for struct inits
extern u64 PTR_DAT_71052a53d8;
extern u64 PTR_DAT_71052a53e0;
extern u64 PTR_DAT_71052a53e8;
extern u64 PTR_DAT_71052a5528;

// FUN_710015e850 / FUN_710015e880 callees
extern "C" u64 FUN_710015f5c0();
extern "C" u64 FUN_710015f600(s64, s8, u32);

// FUN_7100181270 callees
extern "C" u64 FUN_71000b2850(s64);
extern "C" u64 FUN_71000b2b10(s64, s64);

// FUN_7100194e60 callee
extern "C" u64 FUN_7100157cf0(s64);

// ---- Functions ---------------------------------------------------------------
// 0x7100181270 — check network protocol readiness via b2850/b2b10 chain, return field+0x46c
u32 FUN_7100181270(s64 param_1)
{
    s64 lVar1;
    u64 uVar2;

    if (*(s32 *)(param_1 + 0x418) == 0) {
        lVar1 = param_1 + 0x2c0;
        uVar2 = FUN_71000b2850(lVar1);
        if ((uVar2 & 1) != 0) {
            uVar2 = FUN_71000b2850(param_1 + 0x2a0);
            if (((uVar2 & 1) != 0) && (uVar2 = FUN_71000b2b10(param_1 + 0x2a0, lVar1), (uVar2 & 1) != 0))
                goto LAB_710018128c;
        }
        uVar2 = FUN_71000b2850(lVar1);
        if ((uVar2 & 1) == 0) {
            return 0;
        }
        uVar2 = FUN_71000b2850(param_1 + 0x2a0);
        if ((uVar2 & 1) == 0) {
            return 0;
        }
        uVar2 = FUN_71000b2b10(param_1 + 0x2a0, lVar1);
        if ((uVar2 & 1) != 0) {
            return 0;
        }
    }
LAB_710018128c:
    return *(u32 *)(param_1 + 0x46c);
}
