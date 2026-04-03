#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-006
// Pool-e worker: nested CXA guards, bool multi-check, leaf store, chain loads

// ---- External declarations -----------------------------------------------

extern "C" {
    int __cxa_guard_acquire(u64 *guard);
    void __cxa_guard_release(u64 *guard);
}

// Shared inner/middle guards
extern u64 DAT_7105323748;
extern u64 DAT_7105323750;
extern u64 DAT_7105323758;
extern u64 DAT_7105323760;

// Nested guard outer/result pairs
extern u64 DAT_7105323988;  extern u64 DAT_7105323990;  // FUN_71023893f0
extern u64 DAT_71053239a8;  extern u64 DAT_71053239b0;  // FUN_7102395a20
extern u64 DAT_7105323a48;  extern u64 DAT_7105323a50;  // FUN_71023afd60
extern u64 DAT_7105323a08;  extern u64 DAT_7105323a10;  // FUN_71023afee0
extern u64 DAT_7105323a18;  extern u64 DAT_7105323a20;  // FUN_71023b0060
extern u64 DAT_7105323a88;  extern u64 DAT_7105323a90;  // FUN_71023b6b90

// FUN_7102389af0 — global manager pointers (each holds a pointer at offset +8)
extern u64 DAT_7105324cc8;
extern u64 DAT_7105323fd8;
extern u64 DAT_7105324cb8;
extern u64 DAT_7105323fa0;
extern u64 DAT_710532e8f8;
extern u64 DAT_7105324c98;
extern u64 DAT_7105324cd0;
extern u64 DAT_710532e838;
extern u64 DAT_71052c3c58;

// FUN_7102407130 — label address
extern u8 PTR_LAB_71050b9f88;

// ---- Nested CXA guard inits (three-level) ---------------------------------

#define NESTED_GUARD_FN(fn, outer_g, result)              \
u64 *fn(void) {                                           \
    if ((outer_g & 1) == 0) {                             \
        if (__cxa_guard_acquire(&(outer_g)) != 0) {       \
            if ((DAT_7105323748 & 1) == 0) {              \
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) { \
                    if ((DAT_7105323750 & 1) == 0) {      \
                        if (__cxa_guard_acquire(&DAT_7105323750) != 0) { \
                            DAT_7105323758 = 0;           \
                            __cxa_guard_release(&DAT_7105323750); \
                        }                                 \
                    }                                     \
                    DAT_7105323760 = (u64)&DAT_7105323758;\
                    __cxa_guard_release(&DAT_7105323748); \
                }                                         \
            }                                             \
            result = (u64)&DAT_7105323760;                \
            __cxa_guard_release(&(outer_g));              \
        }                                                 \
    }                                                     \
    return (u64 *)&(result);                              \
}

// 0x71023893f0 (384 bytes)
NESTED_GUARD_FN(FUN_71023893f0, DAT_7105323988, DAT_7105323990)
// 0x7102395a20 (384 bytes)
NESTED_GUARD_FN(FUN_7102395a20, DAT_71053239a8, DAT_71053239b0)
// 0x71023afd60 (384 bytes)
NESTED_GUARD_FN(FUN_71023afd60, DAT_7105323a48, DAT_7105323a50)
// 0x71023afee0 (384 bytes)
NESTED_GUARD_FN(FUN_71023afee0, DAT_7105323a08, DAT_7105323a10)
// 0x71023b0060 (400 bytes)
NESTED_GUARD_FN(FUN_71023b0060, DAT_7105323a18, DAT_7105323a20)
// 0x71023b6b90 (400 bytes)
NESTED_GUARD_FN(FUN_71023b6b90, DAT_7105323a88, DAT_7105323a90)

// ---- Boolean multi-check (leaf) ------------------------------------------

// 0x7102389af0 (288 bytes) — 9 conditions checking manager state flags; leaf, no frame
// Disasm: chains of adrp+ldr→ldr x8,[x8,#8]→ldr w8,[x8,#offset]→cbz/ret false
//         final section loads DAT_71052c3c58 chain and returns cset eq or true
bool FUN_7102389af0(void)
{
    if (*(u32 *)(*(u64 *)(DAT_7105324cc8 + 8) + 0xb8) != 0)  return false;
    if (*(u32 *)(*(u64 *)(DAT_7105323fd8 + 8) + 0xc8) != 0)  return false;
    if (*(u32 *)(*(u64 *)(DAT_7105324cb8 + 8) + 0xa8) != 0)  return false;
    if (*(u32 *)(*(u64 *)(DAT_7105323fa0 + 8) + 0xa8) != 0)  return false;
    if (*(u32 *)(*(u64 *)(DAT_710532e8f8 + 8) + 0xc8) != 0)  return false;
    if (*(u32 *)(*(u64 *)(DAT_7105324c98 + 8) + 0x108) != 0) return false;
    if (*(u32 *)(*(u64 *)(DAT_7105324cd0 + 8) + 0xa8) != 0)  return false;
    if (DAT_710532e838 != 0 &&
        *(u8 *)(*(u64 *)(DAT_710532e838 + 8) + 0x170) != 0)  return false;
    u64 x8 = *(u64 *)(DAT_71052c3c58 + 8);
    if (*(u8 *)(*(u64 *)(x8 + 0x80) + 0x244) != 0) {
        return *(u32 *)(*(u64 *)(x8 + 0x90) + 0x10) == 0;
    }
    return true;
}

// ---- Leaf store function --------------------------------------------------

// 0x7102407130 (336 bytes) — store &PTR_LAB_71050b9f88 at param_2[0], *(param_1+8) at param_2[1]
// Disasm (leaf): adrp+add(PTR_LAB)→str x8,[x1]; ldr x8,[x0,#8]; str x8,[x1,#8]; ret
void FUN_7102407130(u64 param_1, u64 *param_2)
{
    param_2[0] = (u64)&PTR_LAB_71050b9f88;
    param_2[1] = *(u64 *)(param_1 + 8);
}
