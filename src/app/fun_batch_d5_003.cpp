#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7101fa-0x7101fb range, batch d5-003
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: app::sv_kinetic_energy + app::sv_animcmd lua_bind entry-point wrappers

// ---- External declarations -----------------------------------------------

struct lua_State;

namespace app {

    namespace sv_kinetic_energy {
        void set_accel_x_mul(lua_State *);
        void set_accel_x_add(lua_State *);
        void mul_x_accel_mul(lua_State *);
        void mul_x_accel_add(lua_State *);
        void set_accel_y_mul(lua_State *);
        void set_accel_y_add(lua_State *);
    }

    namespace sv_animcmd {
        void ATTACK_IGNORE_THROW(lua_State *);
        void ATTACK_ABS(lua_State *);
        void ATK_LERP_RATIO(lua_State *);
        void ATK_SET_SHIELD_SETOFF_MUL(lua_State *);
        void ATK_SET_SHIELD_SETOFF_MUL_arg3(lua_State *);
        void ATK_SET_SHIELD_SETOFF_MUL_arg4(lua_State *);
        void ATK_SET_SHIELD_SETOFF_MUL_arg5(lua_State *);
        void ATK_SET_SHIELD_SETOFF_MUL2(lua_State *);
        void FILL_SCREEN_arg9(lua_State *);
        void FILL_SCREEN_MODEL_COLOR(lua_State *);
        void COLOR_COLLECTION(lua_State *);
        void CANCEL_FILL_SCREEN(lua_State *);
        void REMOVE_FINAL_SCREEN_EFFECT(lua_State *);
        void EFFECT(lua_State *);
        void EFFECT_WORK(lua_State *);
        void EFFECT_VARIATION(lua_State *);
        void EFFECT_GLOBAL(lua_State *);
        void EFFECT_GLOBAL_BACK_GROUND(lua_State *);
        void EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE(lua_State *);
        void EFFECT_FOLLOW(lua_State *);
        void EFFECT_FOLLOW_WORK(lua_State *);
        void EFFECT_FOLLOW_VARIATION(lua_State *);
    }

}  // namespace app

// ---- sv_kinetic_energy wrappers -------------------------------------------

// 0x7101fa2f30
u64 FUN_7101fa2f30(lua_State *param_1)
{
    app::sv_kinetic_energy::set_accel_x_mul(param_1);
    return 0;
}

// 0x7101fa2f50
u64 FUN_7101fa2f50(lua_State *param_1)
{
    app::sv_kinetic_energy::set_accel_x_add(param_1);
    return 0;
}

// 0x7101fa2f70
u64 FUN_7101fa2f70(lua_State *param_1)
{
    app::sv_kinetic_energy::mul_x_accel_mul(param_1);
    return 0;
}

// 0x7101fa2f90
u64 FUN_7101fa2f90(lua_State *param_1)
{
    app::sv_kinetic_energy::mul_x_accel_add(param_1);
    return 0;
}

// 0x7101fa2fb0
u64 FUN_7101fa2fb0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_accel_y_mul(param_1);
    return 0;
}

// 0x7101fa2fd0
u64 FUN_7101fa2fd0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_accel_y_add(param_1);
    return 0;
}

// ---- sv_animcmd wrappers --------------------------------------------------

// 0x7101fa4fc0
u64 FUN_7101fa4fc0(lua_State *param_1)
{
    app::sv_animcmd::ATTACK_IGNORE_THROW(param_1);
    return 0;
}

// 0x7101fa4fe0
u64 FUN_7101fa4fe0(lua_State *param_1)
{
    app::sv_animcmd::ATTACK_ABS(param_1);
    return 0;
}

// 0x7101fac7d0
u64 FUN_7101fac7d0(lua_State *param_1)
{
    app::sv_animcmd::ATK_LERP_RATIO(param_1);
    return 0;
}

// 0x7101fac7f0
u64 FUN_7101fac7f0(lua_State *param_1)
{
    app::sv_animcmd::ATK_SET_SHIELD_SETOFF_MUL(param_1);
    return 0;
}

// 0x7101fac810
u64 FUN_7101fac810(lua_State *param_1)
{
    app::sv_animcmd::ATK_SET_SHIELD_SETOFF_MUL_arg3(param_1);
    return 0;
}

// 0x7101fac830
u64 FUN_7101fac830(lua_State *param_1)
{
    app::sv_animcmd::ATK_SET_SHIELD_SETOFF_MUL_arg4(param_1);
    return 0;
}

// 0x7101fac850
u64 FUN_7101fac850(lua_State *param_1)
{
    app::sv_animcmd::ATK_SET_SHIELD_SETOFF_MUL_arg5(param_1);
    return 0;
}

// 0x7101fac870
u64 FUN_7101fac870(lua_State *param_1)
{
    app::sv_animcmd::ATK_SET_SHIELD_SETOFF_MUL2(param_1);
    return 0;
}

// 0x7101fafaf0
u64 FUN_7101fafaf0(lua_State *param_1)
{
    app::sv_animcmd::FILL_SCREEN_arg9(param_1);
    return 0;
}

// 0x7101fafb10
u64 FUN_7101fafb10(lua_State *param_1)
{
    app::sv_animcmd::FILL_SCREEN_MODEL_COLOR(param_1);
    return 0;
}

// 0x7101fafb30
u64 FUN_7101fafb30(lua_State *param_1)
{
    app::sv_animcmd::COLOR_COLLECTION(param_1);
    return 0;
}

// 0x7101fb1710
u64 FUN_7101fb1710(lua_State *param_1)
{
    app::sv_animcmd::CANCEL_FILL_SCREEN(param_1);
    return 0;
}

// 0x7101fb1730
u64 FUN_7101fb1730(lua_State *param_1)
{
    app::sv_animcmd::REMOVE_FINAL_SCREEN_EFFECT(param_1);
    return 0;
}

// 0x7101fb1750
u64 FUN_7101fb1750(lua_State *param_1)
{
    app::sv_animcmd::EFFECT(param_1);
    return 0;
}

// 0x7101fb1770
u64 FUN_7101fb1770(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_WORK(param_1);
    return 0;
}

// 0x7101fb1790
u64 FUN_7101fb1790(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_VARIATION(param_1);
    return 0;
}

// 0x7101fb2670
u64 FUN_7101fb2670(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_GLOBAL(param_1);
    return 0;
}

// 0x7101fb2760
u64 FUN_7101fb2760(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_GLOBAL_BACK_GROUND(param_1);
    return 0;
}

// 0x7101fb2780
u64 FUN_7101fb2780(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE(param_1);
    return 0;
}

// 0x7101fb38a0
u64 FUN_7101fb38a0(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_FOLLOW(param_1);
    return 0;
}

// 0x7101fb38c0
u64 FUN_7101fb38c0(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_FOLLOW_WORK(param_1);
    return 0;
}

// 0x7101fb38e0
u64 FUN_7101fb38e0(lua_State *param_1)
{
    app::sv_animcmd::EFFECT_FOLLOW_VARIATION(param_1);
    return 0;
}
