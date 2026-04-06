#include "types.h"
#include "app/modules/GroundModule.h"
#include "app/modules/WorkModule.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-004
// Pool-e worker: StageManager dispatch, ground vtable, work module, chain loads, nested CXA guards

// ---- External declarations -----------------------------------------------

#define VT(m) (*reinterpret_cast<void***>(m))

// Singleton
extern u64 DAT_71053299d8;  // lib::Singleton<app::StageManager>::instance_

// Module callees
extern void FUN_710082a060(u64, u64);
extern void FUN_71015b0a00(u64);

// FUN_7102149f10/7102182150: array at DAT_71052c10d0, stride 0x110, byte field at +0
extern u8 DAT_71052c10d0;

// CXA guards (used by nested guard init functions)
extern "C" {
    int __cxa_guard_acquire(u64 *guard);
    void __cxa_guard_release(u64 *guard);
}

// Shared inner guards/values for 0x71022f series
extern u64 DAT_7105323748;  // middle guard
extern u64 DAT_7105323750;  // inner guard
extern u64 DAT_7105323758;  // inner value (init to 0)
extern u64 DAT_7105323760;  // holds &DAT_7105323758

// Outer guards + result slots (one per nested-guard function)
extern u64 DAT_71053237a8;  extern u64 DAT_71053237b0;  // FUN_71022f19b0
extern u64 DAT_71053237b8;  extern u64 DAT_71053237c0;  // FUN_71022f1b30
extern u64 DAT_71053237c8;  extern u64 DAT_71053237d0;  // FUN_71022f1cb0
extern u64 DAT_7105323788;  extern u64 DAT_7105323790;  // FUN_71022f1f50
extern u64 DAT_7105323778;  extern u64 DAT_7105323780;  // FUN_71022f20d0
extern u64 DAT_71053237d8;  extern u64 DAT_71053237e0;  // FUN_71022f2250
extern u64 DAT_7105323798;  extern u64 DAT_71053237a0;  // FUN_71022f23d0

// ---- StageManager dispatch with w12 branch --------------------------------

// 0x71020c6598 (248 bytes) — load StageManager, dispatch vtable[0x1a8/8] or [0x1b0/8] based on w12
// Disasm: str x9,[x0,#0x10]; adrp+ldr(instance_)→ldr x8,[x8];
//         add x0,x8,#0x128; ldr x8,[x8,#0x128]; cbz w12,→ldr x8,[x8,#0x1a8]; else ldr x8,[x8,#0x1b0]; blr x8
u64 FUN_71020c6598(u64 param_1)
{
    register u64 in_x9 asm("x9");
    register u32 in_w12 asm("w12");
    asm volatile("" : "+r"(in_x9), "+r"(in_w12));
    *(u64 *)(param_1 + 0x10) = in_x9;
    u8 *SM = (u8 *)*(u64 *)DAT_71053299d8;
    void *sub = SM + 0x128;
    if (in_w12 != 0) {
        reinterpret_cast<void (*)(void *)>(VT(sub)[0x1b0 / 8])(sub);
    } else {
        reinterpret_cast<void (*)(void *)>(VT(sub)[0x1a8 / 8])(sub);
    }
    return 0;
}

// ---- ground_module vtable[0x808/8] dispatch --------------------------------

// 0x71020c6e20 (208 bytes) — ground_module (acc+0x58), vtable[0x808/8](mod, 0)
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x58]; ldr x8,[x0]; ldr x8,[x8,#0x808]; mov w1,wzr; blr x8
u64 FUN_71020c6e20(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    // [inferred: GroundModule vtable slot 0x808/8, unnamed in .dynsym]
    auto *mod = static_cast<app::GroundModule *>(*(void **)(acc + 0x58));
    mod->_vf257(0);
    return 0;
}

// 0x71020c6ef0 (208 bytes) — ground_module (acc+0x58), vtable[0x808/8](mod, 1)
u64 FUN_71020c6ef0(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    // [inferred: GroundModule vtable slot 0x808/8, unnamed in .dynsym]
    auto *mod = static_cast<app::GroundModule *>(*(void **)(acc + 0x58));
    mod->_vf257(1);
    return 0;
}

// ---- work_module → conditional byte store ---------------------------------

// 0x7102149f10 (240 bytes) — work_module vtable[0x98/8](mod, 0x10000000) → if result <= 7, clear byte
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x50]; ldr x8,[x0]; ldr x8,[x8,#0x98]; mov w1,#0x10000000;
//         blr x8; cmp w0,#7; ldp x29,x30,[sp],#0x10; b.gt skip;
//         adrp x8,0x71052c0000; add x8,x8,#0xfd0; mov w9,#0x110;
//         smaddl x8,w0,w9,x8; strb wzr,[x8,#0x100]
//         skip: mov w0,wzr; ret
// Note: base = 0x71052c0fd0, DAT_71052c10d0 = base+0x100; entry stride = 0x110
u64 FUN_7102149f10(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    // [derived: WorkModule__get_int_impl (.dynsym) -> vtable slot 0x98/8]
    auto *mod = reinterpret_cast<app::WorkModule *>(*(void **)(acc + 0x50));
    s32 index = mod->get_int(0x10000000);
    if (index <= 7) {
        (&DAT_71052c10d0)[(s64)index * 0x110] = 0;
    }
    return 0;
}

// 0x7102182150 (240 bytes) — identical to FUN_7102149f10
u64 FUN_7102182150(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    // [derived: WorkModule__get_int_impl (.dynsym) -> vtable slot 0x98/8]
    auto *mod = reinterpret_cast<app::WorkModule *>(*(void **)(acc + 0x50));
    s32 index = mod->get_int(0x10000000);
    if (index <= 7) {
        (&DAT_71052c10d0)[(s64)index * 0x110] = 0;
    }
    return 0;
}

// ---- Two-module dispatch (work + effect) ----------------------------------

// 0x710219a34c (212 bytes) — FUN_710082a060(work_module, effect_module)
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x50]; ldr x1,[x9,#0x140]; bl FUN_710082a060; mov w0,wzr
u64 FUN_710219a34c(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082a060(*(u64 *)(acc + 0x50), *(u64 *)(acc + 0x140));
    return 0;
}

// ---- Chain load dispatch --------------------------------------------------

// 0x71021fdc68 (296 bytes) — loads from *(param_1-8) chain, calls FUN_71015b0a00
// Disasm: ldur x8,[x0,-8]; str x9,[x0,#0x10]; ldr x8,[x8,#0x1a0]; ldr x8,[x8,#0x190];
//         ldr x0,[x8,#0x220]; bl FUN_71015b0a00; mov w0,wzr
u64 FUN_71021fdc68(u64 param_1)
{
    register u64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    u64 base = *(u64 *)(param_1 - 8);
    *(u64 *)(param_1 + 0x10) = in_x9;
    u64 x8 = *(u64 *)(base + 0x1a0);
    x8 = *(u64 *)(x8 + 0x190);
    FUN_71015b0a00(*(u64 *)(x8 + 0x220));
    return 0;
}

// ---- Nested CXA guard static initializers ---------------------------------
// Pattern: check+acquire outer guard → check+acquire middle guard →
//          check+acquire inner guard → init inner value → release all.
// Each function differs only in its outer guard address and result slot.

// Shared helper — inner guard init (inlined by compiler, expanded here for clarity)
static inline void init_inner_guard(void)
{
    if ((DAT_7105323750 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105323750) != 0) {
            DAT_7105323758 = 0;
            __cxa_guard_release(&DAT_7105323750);
        }
    }
    DAT_7105323760 = (u64)&DAT_7105323758;
}

// 0x71022f1e30 (288 bytes) — single-level guard init, returns &DAT_7105323758
u64 *FUN_71022f1e30(void)
{
    if ((DAT_7105323750 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105323750) != 0) {
            DAT_7105323758 = 0;
            __cxa_guard_release(&DAT_7105323750);
        }
    }
    return (u64 *)&DAT_7105323758;
}

// 0x71022f19b0 (384 bytes) — nested guard: outer DAT_71053237a8, result DAT_71053237b0
u64 *FUN_71022f19b0(void)
{
    if ((DAT_71053237a8 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_71053237a8) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_71053237b0 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_71053237a8);
        }
    }
    return (u64 *)&DAT_71053237b0;
}

// 0x71022f1b30 (384 bytes) — nested guard: outer DAT_71053237b8, result DAT_71053237c0
u64 *FUN_71022f1b30(void)
{
    if ((DAT_71053237b8 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_71053237b8) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_71053237c0 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_71053237b8);
        }
    }
    return (u64 *)&DAT_71053237c0;
}

// 0x71022f1cb0 (384 bytes) — nested guard: outer DAT_71053237c8, result DAT_71053237d0
u64 *FUN_71022f1cb0(void)
{
    if ((DAT_71053237c8 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_71053237c8) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_71053237d0 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_71053237c8);
        }
    }
    return (u64 *)&DAT_71053237d0;
}

// 0x71022f1f50 (384 bytes) — nested guard: outer DAT_7105323788, result DAT_7105323790
u64 *FUN_71022f1f50(void)
{
    if ((DAT_7105323788 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105323788) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_7105323790 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_7105323788);
        }
    }
    return (u64 *)&DAT_7105323790;
}

// 0x71022f20d0 (384 bytes) — nested guard: outer DAT_7105323778, result DAT_7105323780
u64 *FUN_71022f20d0(void)
{
    if ((DAT_7105323778 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105323778) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_7105323780 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_7105323778);
        }
    }
    return (u64 *)&DAT_7105323780;
}

// 0x71022f2250 (384 bytes) — nested guard: outer DAT_71053237d8, result DAT_71053237e0
u64 *FUN_71022f2250(void)
{
    if ((DAT_71053237d8 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_71053237d8) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_71053237e0 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_71053237d8);
        }
    }
    return (u64 *)&DAT_71053237e0;
}

// 0x71022f23d0 (544 bytes) — nested guard: outer DAT_7105323798, result DAT_71053237a0
u64 *FUN_71022f23d0(void)
{
    if ((DAT_7105323798 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105323798) != 0) {
            if ((DAT_7105323748 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323748) != 0) {
                    init_inner_guard();
                    __cxa_guard_release(&DAT_7105323748);
                }
            }
            DAT_71053237a0 = (u64)&DAT_7105323760;
            __cxa_guard_release(&DAT_7105323798);
        }
    }
    return (u64 *)&DAT_71053237a0;
}
