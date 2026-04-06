#include "types.h"
#include "app/modules/LinkModule.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-005
// Pool-e worker: singleton dispatch, chain loads, two-/three-level nested CXA guard inits

// ---- External declarations -----------------------------------------------

extern u64 DAT_71053299d8;   // lib::Singleton<app::StageManager>::instance_
extern u64 DAT_71052c2958;   // global pointer used by FUN_710220bf70

extern void FUN_710260c800(u64);
extern void FUN_71015b8f40(u64, u64);
extern void FUN_71015b4d40(u64, u64);

extern "C" {
    int __cxa_guard_acquire(u64 *guard);
    void __cxa_guard_release(u64 *guard);
}

// Shared inner/middle guard values (same set used by all nested-guard functions)
extern u64 DAT_7105323748;
extern u64 DAT_7105323750;
extern u64 DAT_7105323758;
extern u64 DAT_7105323760;

// Two-level guard (FUN_71022dece0)
extern u64 DAT_7105327150;  extern u64 DAT_7105327158;

// Three-level guard: outer/result pairs
extern u64 DAT_7105323808;  extern u64 DAT_7105323810;  // FUN_71022f71e0
extern u64 DAT_71053237f8;  extern u64 DAT_7105323800;  // FUN_71022f7360
extern u64 DAT_7105323828;  extern u64 DAT_7105323830;  // FUN_71022fde80
extern u64 DAT_7105323838;  extern u64 DAT_7105323840;  // FUN_71022feef0
extern u64 DAT_7105323848;  extern u64 DAT_7105323850;  // FUN_71022ff070
extern u64 DAT_7105323858;  extern u64 DAT_7105323860;  // FUN_7102302640
extern u64 DAT_7105323868;  extern u64 DAT_7105323870;  // FUN_7102307120
extern u64 DAT_71053238a8;  extern u64 DAT_71053238b0;  // FUN_7102330180
extern u64 DAT_71053238b8;  extern u64 DAT_71053238c0;  // FUN_7102330300
extern u64 DAT_71053238c8;  extern u64 DAT_71053238d0;  // FUN_7102363050
extern u64 DAT_7105323978;  extern u64 DAT_7105323980;  // FUN_7102378bc0
extern u64 DAT_7105323998;  extern u64 DAT_71053239a0;  // FUN_7102384f50

// ---- StageManager singleton dispatch (simple) ----------------------------

// 0x7102143184 (924 bytes) — store x9 at param_1+0x10, call FUN_710260c800(SM)
// Disasm: str x9,[x0,#0x10]; adrp+ldr(instance_)→ldr x0,[x8]; bl FUN_710260c800; ldp; mov w0,wzr; ret
u64 FUN_7102143184(u64 param_1)
{
    register u64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(u64 *)(param_1 + 0x10) = in_x9;
    FUN_710260c800(*(u64 *)DAT_71053299d8);
    return 0;
}

// ---- link_module vtable dispatch -----------------------------------------

// 0x7102259440 (2320 bytes) — link_module (acc+0xd0), vtable[0x3b0/8](mod, 0, 0)
// Same pattern as FUN_7102250050
u64 FUN_7102259440(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    // [derived: LinkModule__adjust_model_constraint_posture_impl (.dynsym) -> vtable slot 0x3b0/8]
    auto *mod = reinterpret_cast<app::LinkModule *>(*(void **)(acc + 0xd0));
    mod->adjust_model_constraint_posture(0, 0);
    return 0;
}

// ---- Chain load dispatches -----------------------------------------------

// 0x710220bf70 (336 bytes) — load chain from *(param_1-8), FUN_71015b8f40(*DAT_71052c2958, chain_result)
// Disasm: ldur x8,[x0,-8]; ldr x8,[x8,#0x1a0]; ldr x8,[x8,#0x190]; ldr x1,[x8,#0x220];
//         adrp+ldr(DAT_71052c2958)→ldr x0,[x8]; bl FUN_71015b8f40; mov w0,wzr; ldp; ret
u64 FUN_710220bf70(u64 param_1)
{
    u64 base = *(u64 *)(param_1 - 8);
    u64 x8 = *(u64 *)(base + 0x1a0);
    x8 = *(u64 *)(x8 + 0x190);
    u64 x1 = *(u64 *)(x8 + 0x220);
    u64 x0 = *(u64 *)DAT_71052c2958;
    FUN_71015b8f40(x0, x1);
    return 0;
}

// 0x710220c588 (216 bytes) — FUN_71015b4d40(*(x9+0x190+0x220), chain_result_0x220)
// Disasm: ldur x8,[x0,-8]; ldr x8,[x8,#0x1a0]; ldr x8,[x8,#0x190]; ldr x9,[x9,#0x190];
//         ldr x0,[x9,#0x220]; ldr x1,[x8,#0x220]; bl FUN_71015b4d40; ldp; mov w0,wzr; ret
// Note: epilogue scheduled before mov w0,wzr
u64 FUN_710220c588(u64 param_1)
{
    register u8 *acc asm("x9");
    asm volatile("" : "+r"(acc));
    u64 base = *(u64 *)(param_1 - 8);
    u64 x8 = *(u64 *)(base + 0x1a0);
    x8 = *(u64 *)(x8 + 0x190);
    u64 x9v = *(u64 *)(acc + 0x190);
    FUN_71015b4d40(*(u64 *)(x9v + 0x220), *(u64 *)(x8 + 0x220));
    return 0;
}

// ---- Two-level CXA guard init --------------------------------------------

// 0x71022dece0 (512 bytes) — outer DAT_7105327150; inner DAT_7105323750 → DAT_7105323758
// Returns &DAT_7105327158
u64 *FUN_71022dece0(void)
{
    if ((DAT_7105327150 & 1) == 0) {
        if (__cxa_guard_acquire(&DAT_7105327150) != 0) {
            if ((DAT_7105323750 & 1) == 0) {
                if (__cxa_guard_acquire(&DAT_7105323750) != 0) {
                    DAT_7105323758 = 0;
                    __cxa_guard_release(&DAT_7105323750);
                }
            }
            DAT_7105327158 = (u64)&DAT_7105323758;
            __cxa_guard_release(&DAT_7105327150);
        }
    }
    return (u64 *)&DAT_7105327158;
}

// ---- Three-level nested CXA guard inits ----------------------------------
// Shared inner logic: init_inner_guard() inlines DAT_7105323750→DAT_7105323758→DAT_7105323760
// Macro to avoid repetition

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

// 0x71022f71e0 (384 bytes)
NESTED_GUARD_FN(FUN_71022f71e0, DAT_7105323808, DAT_7105323810)
// 0x71022f7360 (1536 bytes)
NESTED_GUARD_FN(FUN_71022f7360, DAT_71053237f8, DAT_7105323800)
// 0x71022fde80 (384 bytes)
NESTED_GUARD_FN(FUN_71022fde80, DAT_7105323828, DAT_7105323830)
// 0x71022feef0 (384 bytes)
NESTED_GUARD_FN(FUN_71022feef0, DAT_7105323838, DAT_7105323840)
// 0x71022ff070 (384 bytes)
NESTED_GUARD_FN(FUN_71022ff070, DAT_7105323848, DAT_7105323850)
// 0x7102302640 (416 bytes)
NESTED_GUARD_FN(FUN_7102302640, DAT_7105323858, DAT_7105323860)
// 0x7102307120 (400 bytes)
NESTED_GUARD_FN(FUN_7102307120, DAT_7105323868, DAT_7105323870)
// 0x7102330180 (384 bytes)
NESTED_GUARD_FN(FUN_7102330180, DAT_71053238a8, DAT_71053238b0)
// 0x7102330300 (384 bytes)
NESTED_GUARD_FN(FUN_7102330300, DAT_71053238b8, DAT_71053238c0)
// 0x7102363050 (384 bytes)
NESTED_GUARD_FN(FUN_7102363050, DAT_71053238c8, DAT_71053238d0)
// 0x7102378bc0 (400 bytes)
NESTED_GUARD_FN(FUN_7102378bc0, DAT_7105323978, DAT_7105323980)
// 0x7102384f50 (384 bytes)
NESTED_GUARD_FN(FUN_7102384f50, DAT_7105323998, DAT_71053239a0)
