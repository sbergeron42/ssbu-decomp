#include "types.h"

// FighterBayonettaFinalModule -- final smash state machine for Bayonetta
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

// 710219a030 -- b FUN_7100829e00
void FighterBayonettaFinalModule__final_init_impl(FighterBayonettaFinalModule* m) {
    FUN_7100829e00(m);
}

// 710219a040 -- ldr x0,[x1,#0x50]; ldr x1,[x1,#0x140]; b external
void FighterBayonettaFinalModule__final_exec_impl(FighterBayonettaFinalModule*, BattleObjectModuleAccessor* a) {
    auto* p = reinterpret_cast<u8*>(a);
    auto* work = *reinterpret_cast<void**>(p + 0x50);
    auto* effect = *reinterpret_cast<void**>(p + 0x140);
    FUN_710082a060(work, effect);
}

// 710219a050 -- b external
void FighterBayonettaFinalModule__final_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082a290(m);
}

// 710219a060 -- b external
void FighterBayonettaFinalModule__final_start_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082a4a0(m);
}

// 710219a150 -- b external
void FighterBayonettaFinalModule__final_start_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082afa0(m);
}

// 710219a160 -- b external
void FighterBayonettaFinalModule__final_scene01_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082c560(m);
}

// 710219a170 -- b external
void FighterBayonettaFinalModule__final_scene01_exec_impl(FighterBayonettaFinalModule* m) {
    FUN_710082ca60(m);
}

// 710219a180 -- b external
void FighterBayonettaFinalModule__final_scene01_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082e2c0(m);
}

// 710219a190 -- b external
void FighterBayonettaFinalModule__final_end_init_impl(FighterBayonettaFinalModule* m) {
    FUN_710082ec20(m);
}

// 710219a1a0 -- b external
void FighterBayonettaFinalModule__final_end_exec_impl(FighterBayonettaFinalModule* m) {
    FUN_710082f150(m);
}

// 710219a1b0 -- b external
void FighterBayonettaFinalModule__final_end_exit_impl(FighterBayonettaFinalModule* m) {
    FUN_710082fa30(m);
}

// 710219a1c0 -- b external
void FighterBayonettaFinalModule__restart_other_fighter_impl(FighterBayonettaFinalModule* m) {
    FUN_710082b620(m);
}

} // namespace app::lua_bind
