// Batch C - 006: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 31

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// Forward declarations for external functions
extern "C" void FUN_71006ab9d0(u64);
extern "C" void FUN_71006be630(u64);
extern "C" void FUN_7101610890(u64);
extern "C" void FUN_710067f640(u64);
extern "C" void FUN_71026084c0(u64);

namespace app {
    struct Fighter;

    namespace FighterUtil {
        void adjust_butterflynet(BattleObjectModuleAccessor*);
        void end_butterflynet(BattleObjectModuleAccessor*);
        void adjust_bitten_wario(BattleObjectModuleAccessor*);
        void init_big_small(BattleObjectModuleAccessor*);
        void exec_big_small(BattleObjectModuleAccessor*);
        void exit_big_small(BattleObjectModuleAccessor*);
        void reset_hit_data(BattleObjectModuleAccessor*);
        void clung_thrown_diddy_unlink_capture(BattleObjectModuleAccessor*);
        void set_restart_up_position(BattleObjectModuleAccessor*);
        void set_parent_external_stat_bank_handle(BattleObjectModuleAccessor*);
        void flash_eye_info(BattleObjectModuleAccessor*);
        void set_stage_pause_for_final(u8, BattleObjectModuleAccessor*);
        void jump_board_on(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Link {
        void set_item_hold_anim_for_script(Fighter*);
    }

    namespace WeaponSpecializer_LinkBowarrow {
        void to_item(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Kirby {
        void inhale_object(Fighter*);
    }

    namespace FighterSpecializer_Purin {
        void special_n_set_power(BattleObjectModuleAccessor*);
    }
}

// 0x71020a7160 — lua_bind vtable dispatch, calls vtable+0x3b8 on hidden x8 object
u32 FUN_71020a7160(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x3b8 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x3b8))(in_x8);
    return 0;
}

// 0x71020a79e0 — lua_bind vtable dispatch, calls vtable+0x70 on hidden x8 object
u32 FUN_71020a79e0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    // +0x70 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x70))(in_x8);
    return 0;
}

// 0x71020a8f1c — lua_bind forwarding wrapper, dereferences param and dispatches to FUN_71006ab9d0
u64 FUN_71020a8f1c(u64 *param_1)
{
    FUN_71006ab9d0(*param_1);
    return 0;
}

// 0x71020adef0 — lua_bind vtable dispatch, calls vtable+0x280 on hidden x8 object
u32 FUN_71020adef0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x280 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x280))(in_x8);
    return 0;
}

// 0x71020af048 — lua_bind forwarding wrapper, dispatches to FUN_71006be630
u64 FUN_71020af048(u64 param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71006be630(param_1);
    return 0;
}

// 0x71020afd68 — lua_bind vtable dispatch, calls vtable+0x460 on hidden x8 object
u32 FUN_71020afd68(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x460 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x460))(in_x8);
    return 0;
}

// 0x71020bf850 — lua_bind forwarding wrapper, dispatches to FighterUtil::adjust_butterflynet
u64 FUN_71020bf850(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_butterflynet(param_1);
    return 0;
}

// 0x71020bf910 — lua_bind forwarding wrapper, dispatches to FighterUtil::end_butterflynet
u64 FUN_71020bf910(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::end_butterflynet(param_1);
    return 0;
}

// 0x71020bf9d0 — lua_bind forwarding wrapper, dispatches to FighterUtil::adjust_bitten_wario
u64 FUN_71020bf9d0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_bitten_wario(param_1);
    return 0;
}

// 0x71020c04f0 — lua_bind forwarding wrapper, dispatches to FighterUtil::init_big_small
u64 FUN_71020c04f0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::init_big_small(param_1);
    return 0;
}

// 0x71020c05b0 — lua_bind forwarding wrapper, dispatches to FighterUtil::exec_big_small
u64 FUN_71020c05b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exec_big_small(param_1);
    return 0;
}

// 0x71020c0670 — lua_bind forwarding wrapper, dispatches to FighterUtil::exit_big_small
u64 FUN_71020c0670(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exit_big_small(param_1);
    return 0;
}

// 0x71020c0d90 — lua_bind forwarding wrapper, dispatches to FighterUtil::reset_hit_data
u64 FUN_71020c0d90(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::reset_hit_data(param_1);
    return 0;
}

// 0x71020c11b0 — lua_bind forwarding wrapper, dispatches to FighterUtil::clung_thrown_diddy_unlink_capture
u64 FUN_71020c11b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::clung_thrown_diddy_unlink_capture(param_1);
    return 0;
}

// 0x71020c13b0 — lua_bind forwarding wrapper, dispatches to FighterUtil::set_restart_up_position
u64 FUN_71020c13b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_restart_up_position(param_1);
    return 0;
}

// 0x71020c1690 — lua_bind forwarding wrapper, dispatches to FighterUtil::set_parent_external_stat_bank_handle
u64 FUN_71020c1690(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_parent_external_stat_bank_handle(param_1);
    return 0;
}

// 0x71020c3ba0 — lua_bind forwarding wrapper, dispatches to FighterUtil::flash_eye_info
u64 FUN_71020c3ba0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::flash_eye_info(param_1);
    return 0;
}

// 0x71020c4454 — lua_bind forwarding wrapper, dispatches to FighterUtil::set_stage_pause_for_final
u64 FUN_71020c4454(s64 param_1, app::BattleObjectModuleAccessor *param_2)
{
    u8 in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterUtil::set_stage_pause_for_final(in_w8, param_2);
    return 0;
}

// 0x71020c6d60 — lua_bind forwarding wrapper, dispatches to FighterUtil::jump_board_on
u64 FUN_71020c6d60(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::jump_board_on(param_1);
    return 0;
}

// 0x71020d2620 — lua_bind forwarding wrapper, dispatches to FUN_7101610890
u64 FUN_71020d2620(u64 param_1)
{
    FUN_7101610890(param_1);
    return 0;
}

// 0x71020f47d0 — lua_bind vtable dispatch, calls vtable+0x70 on hidden x8 object
u32 FUN_71020f47d0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x70 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x70))(in_x8);
    return 0;
}

// 0x71020f7020 — lua_bind vtable dispatch, calls vtable+0x48 on hidden x8 object
u32 FUN_71020f7020(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x48 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x48))(in_x8);
    return 0;
}

// 0x71020f70f0 — lua_bind vtable dispatch, calls vtable+0x50 on hidden x8 object
u32 FUN_71020f70f0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x50 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x71020f7dc0 — lua_bind vtable dispatch, calls vtable+0x78 on hidden x8 object
u32 FUN_71020f7dc0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x78 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x78))(in_x8);
    return 0;
}

// 0x71020f7e90 — lua_bind vtable dispatch, calls vtable+0x80 on hidden x8 object
u32 FUN_71020f7e90(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    // +0x80 [inferred: vtable method on hidden x8 object]
    (**(void (**)(s64 *))(*in_x8 + 0x80))(in_x8);
    return 0;
}

// 0x7102143d5c — lua_bind wrapper, double-dereferences param at +0xb80 and dispatches to FUN_710067f640
u64 FUN_7102143d5c(s64 *param_1)
{
    // +0xb80 [inferred: pointer-to-pointer field on param_1's pointee, dereferenced twice before dispatch]
    FUN_710067f640(**(u64 **)(*param_1 + 0xb80));
    return 0;
}

// 0x71021456d4 — lua_bind forwarding wrapper, dereferences param and dispatches to FUN_71026084c0
u64 FUN_71021456d4(u64 *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71026084c0(*param_1);
    return 0;
}

// 0x7102146620 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Link::set_item_hold_anim_for_script
u64 FUN_7102146620(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Link::set_item_hold_anim_for_script(param_1);
    return 0;
}

// 0x7102146bd0 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_LinkBowarrow::to_item
u64 FUN_7102146bd0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LinkBowarrow::to_item(param_1);
    return 0;
}

// 0x7102149810 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Kirby::inhale_object
u64 FUN_7102149810(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Kirby::inhale_object(param_1);
    return 0;
}

// 0x7102149e50 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Purin::special_n_set_power
u64 FUN_7102149e50(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_set_power(param_1);
    return 0;
}
