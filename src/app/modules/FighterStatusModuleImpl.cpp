#include "app/BattleObjectModuleAccessor.h"

extern "C" void FUN_71006eb6c0(void*, bool, u64, bool, bool, bool, u64, u64, u32);
extern "C" void FUN_71006eb8c0(void*);

namespace app::lua_bind {

// 71020a99f0 -- set_fighter_status_data: forward to status module with bool masks + stack param
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterStatusModuleImpl__set_fighter_status_data_impl(
    BattleObjectModuleAccessor* a, bool p1, u64 p2, bool p3, bool p4, bool p5, u64 p6, u64 p7, u32 p8) {
    asm("ldr w8, [sp]\n"
        "ldr x0, [x0, #0x40]\n"
        "and w1, w1, #0x1\n"
        "and w3, w3, #0x1\n"
        "and w4, w4, #0x1\n"
        "and w5, w5, #0x1\n"
        "str w8, [sp]\n"
        "b FUN_71006eb6c0\n");
}
#endif

// 71020a9a10 -- reset_log_action_info: load status module, tail call
void FighterStatusModuleImpl__reset_log_action_info_impl(BattleObjectModuleAccessor* a) {
    FUN_71006eb8c0(a->status_module);
}

// 71020a9a20 -- 3 instructions (field write: clear byte)
void FighterStatusModuleImpl__off_disable_intrrupt_warp_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(a->status_module);
    module[0x12c] = 0;
}

} // namespace app::lua_bind
