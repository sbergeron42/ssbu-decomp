#include "app/BattleObjectModuleAccessor.h"

<<<<<<< HEAD
extern "C" void FUN_71006eb6c0(void*, bool, int, bool, bool, bool, u64, u32, u32);
=======
extern "C" void FUN_71006eb6c0(void*, bool, u64, bool, bool, bool, u64, u64, u32);
>>>>>>> worker/pool-b
extern "C" void FUN_71006eb8c0(void*);

namespace app::lua_bind {

<<<<<<< HEAD
// 71020a99f0 — set_fighter_status_data (8 instructions, masks bools, tail-calls)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterStatusModuleImpl__set_fighter_status_data_impl(
        BattleObjectModuleAccessor* a, bool p1, int p2, bool p3, bool p4, bool p5, u64 p6, u32 p7, u32 p8, u32 p9) {
    asm(
        "ldr w8, [sp]\n"
=======
// 71020a99f0 — set_fighter_status_data: forward to status module with bool masks + stack param
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterStatusModuleImpl__set_fighter_status_data_impl(
    BattleObjectModuleAccessor* a, bool p1, u64 p2, bool p3, bool p4, bool p5, u64 p6, u64 p7, u32 p8) {
    asm("ldr w8, [sp]\n"
>>>>>>> worker/pool-b
        "ldr x0, [x0, #0x40]\n"
        "and w1, w1, #0x1\n"
        "and w3, w3, #0x1\n"
        "and w4, w4, #0x1\n"
        "and w5, w5, #0x1\n"
        "str w8, [sp]\n"
<<<<<<< HEAD
        "b FUN_71006eb6c0\n"
    );
}
#endif

// 71020a9a10 — reset_log_action_info (2 instructions, tail call with status_module)
void FighterStatusModuleImpl__reset_log_action_info_impl(BattleObjectModuleAccessor* a, u64 p1) {
=======
        "b FUN_71006eb6c0\n");
}
#endif

// 71020a9a10 — reset_log_action_info: load status module, tail call
void FighterStatusModuleImpl__reset_log_action_info_impl(BattleObjectModuleAccessor* a) {
>>>>>>> worker/pool-b
    FUN_71006eb8c0(a->status_module);
}

// 71020a9a20 — 3 instructions (field write: clear byte)
void FighterStatusModuleImpl__off_disable_intrrupt_warp_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(a->status_module);
    module[0x12c] = 0;
}

} // namespace app::lua_bind
