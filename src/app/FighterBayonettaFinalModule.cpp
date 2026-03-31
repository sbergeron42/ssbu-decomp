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
void FighterBayonettaFinalModule__final_start_exec_impl(FighterBayonettaFinalModule*, BattleObjectModuleAccessor* a) {
    auto* p = reinterpret_cast<u8*>(a);
    auto* work = *reinterpret_cast<u8**>(p + 0x50);
    auto* work_vt = *reinterpret_cast<void***>(work);

    auto get_int = reinterpret_cast<s32 (*)(void*, u64)>(work_vt[0x98 / 8]);
    s32 motion_kind = get_int(work, 0x11000006);

    auto get_int2 = reinterpret_cast<s32 (*)(void*, u64, u64)>(work_vt[0x250 / 8]);
    s32 fighter_motion = get_int2(work, 0xdf05c072bULL, 0x1cd9b199acULL);

    if (motion_kind != fighter_motion)
        return;

    auto* work2 = *reinterpret_cast<u8**>(p + 0x50);
    auto* effect = *reinterpret_cast<u8**>(p + 0x140);

    auto* w2_vt = *reinterpret_cast<void***>(work2);
    auto get_int3 = reinterpret_cast<s32 (*)(void*, u64)>(w2_vt[0x98 / 8]);
    s32 eff_handle = get_int3(work2, 0x100000da);

    if (eff_handle == 0)
        return;

    auto* eff_vt = *reinterpret_cast<void***>(effect);
    auto eff_fn = reinterpret_cast<void (*)(void*, s32, s32, s32)>(eff_vt[0xd8 / 8]);
    eff_fn(effect, eff_handle, 0, 0);

    auto tail_fn = reinterpret_cast<void (*)(void*, s32, u64)>(w2_vt[0xa0 / 8]);
    tail_fn(work2, 0, 0x100000da);
}

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
