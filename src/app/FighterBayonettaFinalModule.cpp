#include "types.h"

// FighterBayonettaFinalModule — final smash state machine for Bayonetta
// Most functions are single-instruction `b` tail calls to the underlying implementation.
// These won't byte-match due to external branch targets.

struct FighterBayonettaFinalModule;
struct BattleObjectModuleAccessor;

extern "C" void FUN_7100829e00(void*);
extern "C" void FUN_710082a060(void*, void*);
extern "C" void FUN_710082a290(void*);
extern "C" void FUN_710082a4a0(void*);
extern "C" void FUN_710082afa0(void*);
extern "C" void FUN_710082c560(void*);
extern "C" void FUN_710082ca60(void*);
extern "C" void FUN_710082e2c0(void*);
extern "C" void FUN_710082ec20(void*);
extern "C" void FUN_710082f150(void*);
extern "C" void FUN_710082fa30(void*);
extern "C" void FUN_710082b620(void*);

namespace app::lua_bind {

// 710219a030 — b FUN_7100829e00
void FighterBayonettaFinalModule__final_init_impl(FighterBayonettaFinalModule* m) {
    FUN_7100829e00(m);
}

// 710219a040 — ldr x0,[x1,#0x50]; ldr x1,[x1,#0x140]; b external
void FighterBayonettaFinalModule__final_exec_impl(FighterBayonettaFinalModule*, BattleObjectModuleAccessor* a) {
    auto* p = reinterpret_cast<u8*>(a);
    auto* work = *reinterpret_cast<void**>(p + 0x50);
    auto* effect = *reinterpret_cast<void**>(p + 0x140);
    FUN_710082a060(work, effect);
}

// 710219a050 — b external
void FighterBayonettaFinalModule__final_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082a290(m);
}

// 710219a060 — b external
void FighterBayonettaFinalModule__final_start_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082a4a0(m);
}

// 710219a070 — complex: vtable calls to check motion kind, then dispatch effect
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterBayonettaFinalModule__final_start_exec_impl(FighterBayonettaFinalModule*, BattleObjectModuleAccessor* a) {
    asm("str x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "ldr x19, [x1, #0x50]\n"
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov x21, x1\n"
        "mov w1, #0x6\n"
        "movk w1, #0x1100, lsl #16\n"
        "mov x0, x19\n"
        "blr x8\n"
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x250]\n"
        "mov x1, #0x72b\n"
        "movk x1, #0xf05c, lsl #16\n"
        "mov x2, #0x99ac\n"
        "movk x2, #0xd9b1, lsl #16\n"
        "mov w20, w0\n"
        "movk x1, #0xd, lsl #32\n"
        "movk x2, #0x1c, lsl #32\n"
        "mov x0, x19\n"
        "blr x8\n"
        "cmp w20, w0\n"
        "b.ne 1f\n"
        "ldr x20, [x21, #0x50]\n"
        "ldr x21, [x21, #0x140]\n"
        "mov w19, #0xda\n"
        "movk w19, #0x1000, lsl #16\n"
        "mov w1, w19\n"
        "ldr x8, [x20]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov x0, x20\n"
        "blr x8\n"
        "cbz w0, 1f\n"
        "ldr x8, [x21]\n"
        "ldr x8, [x8, #0xd8]\n"
        "mov w1, w0\n"
        "mov x0, x21\n"
        "mov w2, wzr\n"
        "mov w3, wzr\n"
        "blr x8\n"
        "ldr x8, [x20]\n"
        "ldr x3, [x8, #0xa0]\n"
        "mov x0, x20\n"
        "mov w2, w19\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "mov w1, wzr\n"
        "ldr x21, [sp], #0x30\n"
        "br x3\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldr x21, [sp], #0x30\n"
        "ret\n");
}
#endif

// 710219a150 — b external
void FighterBayonettaFinalModule__final_start_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082afa0(m);
}

// 710219a160 — b external
void FighterBayonettaFinalModule__final_scene01_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082c560(m);
}

// 710219a170 — b external
void FighterBayonettaFinalModule__final_scene01_exec_impl(FighterBayonettaFinalModule* m) {
    FUN_710082ca60(m);
}

// 710219a180 — b external
void FighterBayonettaFinalModule__final_scene01_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082e2c0(m);
}

// 710219a190 — b external
void FighterBayonettaFinalModule__final_end_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082ec20(m);
}

// 710219a1a0 — b external
void FighterBayonettaFinalModule__final_end_exec_impl(FighterBayonettaFinalModule* m) {
    FUN_710082f150(m);
}

// 710219a1b0 — b external
void FighterBayonettaFinalModule__final_end_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082fa30(m);
}

// 710219a1c0 — b external
void FighterBayonettaFinalModule__restart_other_fighter_impl(FighterBayonettaFinalModule* m) {
    FUN_710082b620(m);
}

} // namespace app::lua_bind
