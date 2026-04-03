#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7101fa range, batch d5-002
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: app::sv_kinetic_energy lua_bind entry-point wrappers

// ---- External declarations -----------------------------------------------

struct lua_State;

namespace app {
    namespace sv_kinetic_energy {
        void reset_energy(lua_State *);
        void enable(lua_State *);
        void clear_speed(lua_State *);
        void mul_speed(lua_State *);
        void mul_accel(lua_State *);
        void friction_on(lua_State *);
        void suspend(lua_State *);
        void resume(lua_State *);
        void set_needs_set_param(lua_State *);
        void set_speed(lua_State *);
        void set_accel(lua_State *);
        void set_brake(lua_State *);
        void set_stable_speed(lua_State *);
        void set_limit_speed(lua_State *);
        void set_speed_mul(lua_State *);
        void set_speed_mul_2nd(lua_State *);
        void set_chara_dir(lua_State *);
        void set_angle(lua_State *);
        void add_speed(lua_State *);
        void mul_x_speed_max(lua_State *);
        void set_ground_trans(lua_State *);
        void set_damage_speed(lua_State *);
        void controller_set_accel_x_mul(lua_State *);
    }
}

// ---- Functions ---------------------------------------------------------------

// 0x7101fa2750
u64 FUN_7101fa2750(lua_State *param_1)
{
    app::sv_kinetic_energy::reset_energy(param_1);
    return 0;
}

// 0x7101fa2770
u64 FUN_7101fa2770(lua_State *param_1)
{
    app::sv_kinetic_energy::enable(param_1);
    return 0;
}

// 0x7101fa2800
u64 FUN_7101fa2800(lua_State *param_1)
{
    app::sv_kinetic_energy::clear_speed(param_1);
    return 0;
}

// 0x7101fa2820
u64 FUN_7101fa2820(lua_State *param_1)
{
    app::sv_kinetic_energy::mul_speed(param_1);
    return 0;
}

// 0x7101fa2840
u64 FUN_7101fa2840(lua_State *param_1)
{
    app::sv_kinetic_energy::mul_accel(param_1);
    return 0;
}

// 0x7101fa2860
u64 FUN_7101fa2860(lua_State *param_1)
{
    app::sv_kinetic_energy::friction_on(param_1);
    return 0;
}

// 0x7101fa2b60
u64 FUN_7101fa2b60(lua_State *param_1)
{
    app::sv_kinetic_energy::suspend(param_1);
    return 0;
}

// 0x7101fa2b80
u64 FUN_7101fa2b80(lua_State *param_1)
{
    app::sv_kinetic_energy::resume(param_1);
    return 0;
}

// 0x7101fa2ba0
u64 FUN_7101fa2ba0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_needs_set_param(param_1);
    return 0;
}

// 0x7101fa2bc0
u64 FUN_7101fa2bc0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_speed(param_1);
    return 0;
}

// 0x7101fa2be0
u64 FUN_7101fa2be0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_accel(param_1);
    return 0;
}

// 0x7101fa2c00
u64 FUN_7101fa2c00(lua_State *param_1)
{
    app::sv_kinetic_energy::set_brake(param_1);
    return 0;
}

// 0x7101fa2c20
u64 FUN_7101fa2c20(lua_State *param_1)
{
    app::sv_kinetic_energy::set_stable_speed(param_1);
    return 0;
}

// 0x7101fa2c40
u64 FUN_7101fa2c40(lua_State *param_1)
{
    app::sv_kinetic_energy::set_limit_speed(param_1);
    return 0;
}

// 0x7101fa2c60
u64 FUN_7101fa2c60(lua_State *param_1)
{
    app::sv_kinetic_energy::set_speed_mul(param_1);
    return 0;
}

// 0x7101fa2c80
u64 FUN_7101fa2c80(lua_State *param_1)
{
    app::sv_kinetic_energy::set_speed_mul_2nd(param_1);
    return 0;
}

// 0x7101fa2ca0
u64 FUN_7101fa2ca0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_chara_dir(param_1);
    return 0;
}

// 0x7101fa2cc0
u64 FUN_7101fa2cc0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_angle(param_1);
    return 0;
}

// 0x7101fa2ce0
u64 FUN_7101fa2ce0(lua_State *param_1)
{
    app::sv_kinetic_energy::add_speed(param_1);
    return 0;
}

// 0x7101fa2d00
u64 FUN_7101fa2d00(lua_State *param_1)
{
    app::sv_kinetic_energy::mul_x_speed_max(param_1);
    return 0;
}

// 0x7101fa2d90
u64 FUN_7101fa2d90(lua_State *param_1)
{
    app::sv_kinetic_energy::set_ground_trans(param_1);
    return 0;
}

// 0x7101fa2db0
u64 FUN_7101fa2db0(lua_State *param_1)
{
    app::sv_kinetic_energy::set_damage_speed(param_1);
    return 0;
}

// 0x7101fa2dd0
u64 FUN_7101fa2dd0(lua_State *param_1)
{
    app::sv_kinetic_energy::controller_set_accel_x_mul(param_1);
    return 0;
}
