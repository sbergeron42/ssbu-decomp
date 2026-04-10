#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71035-0x71037 address range, batch d-019
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" [[noreturn]] void abortWrapper_71039c20a0();  // abort

extern void FUN_7103540560(s64);
extern void FUN_71035231c0(u64);
extern void FUN_71037f7ad0(void);
extern void FUN_71037f7ae0(void);
extern void FUN_710356bb20(void);

namespace nn { namespace os {
    extern void* GetCurrentThread();
}}

// External data
extern s64  DAT_7105331f20;
extern s64  DAT_7105331f18;

// ---- Functions ---------------------------------------------------------------

// 0x71035237f0 -- wrapper: FUN_71035231c0(*(param_2+0x20)), return 1 (32 bytes)
// param_2 [inferred: context struct]
//   +0x20 [inferred: sub-object pointer, passed to FUN_71035231c0]
u64 FUN_71035237f0(u64 param_1, s64 param_2)
{
    FUN_71035231c0(*(u64*)(param_2 + 0x20));
    return 1;
}

// 0x7103534380 -- double-deref vtable[0x110], return result != 1 (48 bytes)
// param_2 [inferred: context struct]
//   +0x20 [inferred: sub-object pointer (same pattern as FUN_71035237f0)]
//   *(+0x20)+0x40 [inferred: nested object pointer, deref'd for vtable dispatch]
//   vtable+0x110 [inferred: virtual method, result compared against 1]
u8 FUN_7103534380(u64 param_1, s64 param_2)
{
    // +0x20 [inferred: sub-object pointer from context]
    // +0x40 [inferred: nested pointer to vtable-bearing object]
    s64 *plVar1 = *(s64**)(*(s64*)(param_2 + 0x20) + 0x40);
    // vtable+0x110 [inferred: virtual method returning status code]
    s32 iVar1 = (*(s32(*)())(*(s64*)(*plVar1 + 0x110)))();
    return (u8)(iVar1 != 1);
}

// 0x710353cfd0 -- return current thread == DAT_7105331f18 (48 bytes)
u8 FUN_710353cfd0(void)
{
    s64 lVar1 = (s64)nn::os::GetCurrentThread();
    return (u8)(DAT_7105331f18 == lVar1);
}

// 0x710353d5a0 -- conditional reset of *param_1 to 0xffffff (64 bytes)
void FUN_710353d5a0(s32 *param_1)
{
    if (*param_1 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        *param_1 = 0xffffff;
    }
}

// 0x71037f7a90 -- abs check then abort if out of range 0-1 (64 bytes)
void FUN_71037f7a90(u32 param_1)
{
    param_1 = param_1 ^ (u32)((s32)param_1 >> 0x1f);
    if (1 < param_1) {
        switch (param_1) {
        case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
        case 0x10: case 0x11: case 0x12: case 0x13:
            FUN_71037f7ad0();
        }
        FUN_71037f7ae0();
        FUN_710356bb20();
    }
}
