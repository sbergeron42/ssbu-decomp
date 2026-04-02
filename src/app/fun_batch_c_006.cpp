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

// 0x71020a7160
u64 FUN_71020a7160(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x3b8))(param_1);
    return 0;
}

// 0x71020a79e0
u64 FUN_71020a79e0(s64 *param_1)
{
    (**(void (**)(s64 *))(*param_1 + 0x70))(param_1);
    return 0;
}

// 0x71020a8f1c
u64 FUN_71020a8f1c(u64 *param_1)
{
    FUN_71006ab9d0(*param_1);
    return 0;
}

// 0x71020adef0
u64 FUN_71020adef0(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x280))(param_1);
    return 0;
}

// 0x71020af048
u64 FUN_71020af048(u64 param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71006be630(param_1);
    return 0;
}

// 0x71020afd68
u64 FUN_71020afd68(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x460))(param_1);
    return 0;
}

// 0x71020bf850
u64 FUN_71020bf850(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_butterflynet(param_1);
    return 0;
}

// 0x71020bf910
u64 FUN_71020bf910(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::end_butterflynet(param_1);
    return 0;
}

// 0x71020bf9d0
u64 FUN_71020bf9d0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_bitten_wario(param_1);
    return 0;
}

// 0x71020c04f0
u64 FUN_71020c04f0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::init_big_small(param_1);
    return 0;
}

// 0x71020c05b0
u64 FUN_71020c05b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exec_big_small(param_1);
    return 0;
}

// 0x71020c0670
u64 FUN_71020c0670(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exit_big_small(param_1);
    return 0;
}

// 0x71020c0d90
u64 FUN_71020c0d90(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::reset_hit_data(param_1);
    return 0;
}

// 0x71020c11b0
u64 FUN_71020c11b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::clung_thrown_diddy_unlink_capture(param_1);
    return 0;
}

// 0x71020c13b0
u64 FUN_71020c13b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_restart_up_position(param_1);
    return 0;
}

// 0x71020c1690
u64 FUN_71020c1690(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_parent_external_stat_bank_handle(param_1);
    return 0;
}

// 0x71020c3ba0
u64 FUN_71020c3ba0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::flash_eye_info(param_1);
    return 0;
}

// 0x71020c4454
u64 FUN_71020c4454(s64 param_1, app::BattleObjectModuleAccessor *param_2)
{
    u8 in_w8;
    u64 in_x10;
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterUtil::set_stage_pause_for_final(in_w8, param_2);
    return 0;
}

// 0x71020c6d60
u64 FUN_71020c6d60(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::jump_board_on(param_1);
    return 0;
}

// 0x71020d2620
u64 FUN_71020d2620(u64 param_1)
{
    FUN_7101610890(param_1);
    return 0;
}

// 0x71020f47d0
u64 FUN_71020f47d0(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x70))(param_1);
    return 0;
}

// 0x71020f7020
u64 FUN_71020f7020(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x48))(param_1);
    return 0;
}

// 0x71020f70f0
u64 FUN_71020f70f0(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x71020f7dc0
u64 FUN_71020f7dc0(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x78))(param_1);
    return 0;
}

// 0x71020f7e90
u64 FUN_71020f7e90(s64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*param_1 + 0x80))(param_1);
    return 0;
}

// 0x7102143d5c
u64 FUN_7102143d5c(s64 *param_1)
{
    FUN_710067f640(**(u64 **)(*param_1 + 0xb80));
    return 0;
}

// 0x71021456d4
u64 FUN_71021456d4(u64 *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71026084c0(*param_1);
    return 0;
}

// 0x7102146620
u64 FUN_7102146620(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Link::set_item_hold_anim_for_script(param_1);
    return 0;
}

// 0x7102146bd0
u64 FUN_7102146bd0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LinkBowarrow::to_item(param_1);
    return 0;
}

// 0x7102149810
u64 FUN_7102149810(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Kirby::inhale_object(param_1);
    return 0;
}

// 0x7102149e50
u64 FUN_7102149e50(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_set_power(param_1);
    return 0;
}
