#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7101fb range, batch d5-005
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: app::sv_animcmd lua_bind entry-point wrappers (effect/flash/misc)

// ---- External declarations -----------------------------------------------

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void EFFECT_OFF(lua_State *);
        void EFFECT_FLW_POS(lua_State *);
        void EFFECT_FLW_POS_NO_STOP(lua_State *);
        void EFFECT_FLW_POS_UNSYNC_VIS(lua_State *);
        void EFFECT_FLW_UNSYNC_VIS(lua_State *);
        void EFFECT_FOLLOW_FLIP(lua_State *);
        void EFFECT_FOLLOW_NO_STOP_FLIP(lua_State *);
        void EFFECT_FOLLOW_LIGHT(lua_State *);
        void EFFECT_LIGHT_END(lua_State *);
        void FOOT_EFFECT(lua_State *);
        void LANDING_EFFECT(lua_State *);
        void DOWN_EFFECT(lua_State *);
        void EFFECT_FOLLOW_COLOR(lua_State *);
        void EFFECT_FOLLOW_arg11(lua_State *);
        void EFFECT_OFF_KIND_WORK(lua_State *);
        void EFFECT_COLOR(lua_State *);
        void EFFECT_COLOR_WORK(lua_State *);
        void EFFECT_ALPHA(lua_State *);
        void EFFECT_FOLLOW_ALPHA(lua_State *);
        void EFFECT_FOLLOW_RND(lua_State *);
        void EFFECT_FOLLOW_RND_WORK(lua_State *);
        void EFFECT_FOLLOW_FLIP_RND(lua_State *);
        void EFFECT_FLIP_ALPHA(lua_State *);
        void EFFECT_FOLLOW_FLIP_ALPHA(lua_State *);
        void FOOT_EFFECT_FLIP(lua_State *);
        void EFFECT_BRANCH_SITUATION(lua_State *);
        void FLASH(lua_State *);
        void FLASH_FRM(lua_State *);
        void FLASH_NO_STOP(lua_State *);
        void BURN_COLOR(lua_State *);
        void BURN_COLOR_FRAME(lua_State *);
        void COL_PRI(lua_State *);
        void FLASH_SET_LAST_ATTACK_DIRECTION(lua_State *);
        void FLASH_SET_DIRECTION(lua_State *);
        void FLASH_SET_DIRECTION_NO_LR(lua_State *);
        void LAST_EFFECT_SET_RATE(lua_State *);
        void LAST_EFFECT_SET_SCALE_W(lua_State *);
        void LAST_EFFECT_SET_COLOR(lua_State *);
        void LAST_EFFECT_SET_ALPHA(lua_State *);
        void LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT(lua_State *);
        void EFFECT_DETACH_KIND(lua_State *);
        void AFTER_IMAGE4_ON_arg29(lua_State *);
        void AFTER_IMAGE4_ON_WORK_arg29(lua_State *);
        void EFFECT_OFF_HANDLE(lua_State *);
        void LAST_EFFECT_SET_TOP_OFFSET(lua_State *);
        void ENABLE_AREA(lua_State *);
        void SA_SET(lua_State *);
        void SET_AIR(lua_State *);
    }
}

// ---- Functions ---------------------------------------------------------------

// 0x7101fb4140
u32 FUN_7101fb4140(lua_State *param_1) { app::sv_animcmd::EFFECT_OFF(param_1); return 0; }

// 0x7101fb4270
u32 FUN_7101fb4270(lua_State *param_1) { app::sv_animcmd::EFFECT_FLW_POS(param_1); return 0; }

// 0x7101fb4290
u32 FUN_7101fb4290(lua_State *param_1) { app::sv_animcmd::EFFECT_FLW_POS_NO_STOP(param_1); return 0; }

// 0x7101fb42b0
u32 FUN_7101fb42b0(lua_State *param_1) { app::sv_animcmd::EFFECT_FLW_POS_UNSYNC_VIS(param_1); return 0; }

// 0x7101fb42d0
u32 FUN_7101fb42d0(lua_State *param_1) { app::sv_animcmd::EFFECT_FLW_UNSYNC_VIS(param_1); return 0; }

// 0x7101fb42f0
u32 FUN_7101fb42f0(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_FLIP(param_1); return 0; }

// 0x7101fb4c10
u32 FUN_7101fb4c10(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_NO_STOP_FLIP(param_1); return 0; }

// 0x7101fb4c30
u32 FUN_7101fb4c30(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_LIGHT(param_1); return 0; }

// 0x7101fb6650
u32 FUN_7101fb6650(lua_State *param_1) { app::sv_animcmd::EFFECT_LIGHT_END(param_1); return 0; }

// 0x7101fb6670
u32 FUN_7101fb6670(lua_State *param_1) { app::sv_animcmd::FOOT_EFFECT(param_1); return 0; }

// 0x7101fb6690
u32 FUN_7101fb6690(lua_State *param_1) { app::sv_animcmd::LANDING_EFFECT(param_1); return 0; }

// 0x7101fb66b0
u32 FUN_7101fb66b0(lua_State *param_1) { app::sv_animcmd::DOWN_EFFECT(param_1); return 0; }

// 0x7101fb6ef0
u32 FUN_7101fb6ef0(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_COLOR(param_1); return 0; }

// 0x7101fb7d50
u32 FUN_7101fb7d50(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_arg11(param_1); return 0; }

// 0x7101fb9410
u32 FUN_7101fb9410(lua_State *param_1) { app::sv_animcmd::EFFECT_OFF_KIND_WORK(param_1); return 0; }

// 0x7101fb9430
u32 FUN_7101fb9430(lua_State *param_1) { app::sv_animcmd::EFFECT_COLOR(param_1); return 0; }

// 0x7101fb9450
u32 FUN_7101fb9450(lua_State *param_1) { app::sv_animcmd::EFFECT_COLOR_WORK(param_1); return 0; }

// 0x7101fb9470
u32 FUN_7101fb9470(lua_State *param_1) { app::sv_animcmd::EFFECT_ALPHA(param_1); return 0; }

// 0x7101fb9490
u32 FUN_7101fb9490(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_ALPHA(param_1); return 0; }

// 0x7101fb94b0
u32 FUN_7101fb94b0(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_RND(param_1); return 0; }

// 0x7101fb94d0
u32 FUN_7101fb94d0(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_RND_WORK(param_1); return 0; }

// 0x7101fb94f0
u32 FUN_7101fb94f0(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_FLIP_RND(param_1); return 0; }

// 0x7101fb9510
u32 FUN_7101fb9510(lua_State *param_1) { app::sv_animcmd::EFFECT_FLIP_ALPHA(param_1); return 0; }

// 0x7101fb9530
u32 FUN_7101fb9530(lua_State *param_1) { app::sv_animcmd::EFFECT_FOLLOW_FLIP_ALPHA(param_1); return 0; }

// 0x7101fb9550
u32 FUN_7101fb9550(lua_State *param_1) { app::sv_animcmd::FOOT_EFFECT_FLIP(param_1); return 0; }

// 0x7101fb9890
u32 FUN_7101fb9890(lua_State *param_1) { app::sv_animcmd::EFFECT_BRANCH_SITUATION(param_1); return 0; }

// 0x7101fb9940
u32 FUN_7101fb9940(lua_State *param_1) { app::sv_animcmd::FLASH(param_1); return 0; }

// 0x7101fb9960
u32 FUN_7101fb9960(lua_State *param_1) { app::sv_animcmd::FLASH_FRM(param_1); return 0; }

// 0x7101fb9980
u32 FUN_7101fb9980(lua_State *param_1) { app::sv_animcmd::FLASH_NO_STOP(param_1); return 0; }

// 0x7101fb99a0
u32 FUN_7101fb99a0(lua_State *param_1) { app::sv_animcmd::BURN_COLOR(param_1); return 0; }

// 0x7101fb99c0
u32 FUN_7101fb99c0(lua_State *param_1) { app::sv_animcmd::BURN_COLOR_FRAME(param_1); return 0; }

// 0x7101fb9a70
u32 FUN_7101fb9a70(lua_State *param_1) { app::sv_animcmd::COL_PRI(param_1); return 0; }

// 0x7101fb9a90
u32 FUN_7101fb9a90(lua_State *param_1) { app::sv_animcmd::FLASH_SET_LAST_ATTACK_DIRECTION(param_1); return 0; }

// 0x7101fb9ab0
u32 FUN_7101fb9ab0(lua_State *param_1) { app::sv_animcmd::FLASH_SET_DIRECTION(param_1); return 0; }

// 0x7101fb9ad0
u32 FUN_7101fb9ad0(lua_State *param_1) { app::sv_animcmd::FLASH_SET_DIRECTION_NO_LR(param_1); return 0; }

// 0x7101fb9af0
u32 FUN_7101fb9af0(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_RATE(param_1); return 0; }

// 0x7101fba150
u32 FUN_7101fba150(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_SCALE_W(param_1); return 0; }

// 0x7101fba170
u32 FUN_7101fba170(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_COLOR(param_1); return 0; }

// 0x7101fba190
u32 FUN_7101fba190(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_ALPHA(param_1); return 0; }

// 0x7101fba2c0
u32 FUN_7101fba2c0(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT(param_1); return 0; }

// 0x7101fba370
u32 FUN_7101fba370(lua_State *param_1) { app::sv_animcmd::EFFECT_DETACH_KIND(param_1); return 0; }

// 0x7101fbda20
u32 FUN_7101fbda20(lua_State *param_1) { app::sv_animcmd::AFTER_IMAGE4_ON_arg29(param_1); return 0; }

// 0x7101fbda40
u32 FUN_7101fbda40(lua_State *param_1) { app::sv_animcmd::AFTER_IMAGE4_ON_WORK_arg29(param_1); return 0; }

// 0x7101fbdb90
u32 FUN_7101fbdb90(lua_State *param_1) { app::sv_animcmd::EFFECT_OFF_HANDLE(param_1); return 0; }

// 0x7101fbdc60
u32 FUN_7101fbdc60(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_TOP_OFFSET(param_1); return 0; }

// 0x7101fbdc80
u32 FUN_7101fbdc80(lua_State *param_1) { app::sv_animcmd::ENABLE_AREA(param_1); return 0; }

// 0x7101fbfab0
u32 FUN_7101fbfab0(lua_State *param_1) { app::sv_animcmd::SA_SET(param_1); return 0; }

// 0x7101fbfad0
u32 FUN_7101fbfad0(lua_State *param_1) { app::sv_animcmd::SET_AIR(param_1); return 0; }
