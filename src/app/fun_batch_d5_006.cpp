#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7101fb-0x7101fc range, batch d5-006
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: app::sv_animcmd lua_bind entry-point wrappers (speed/motion/sound/misc)

// ---- External declarations -----------------------------------------------

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void SET_RATE_ARTICLE(lua_State *);
        void ADD_SPEED_NO_LIMIT(lua_State *);
        void SET_SPEED(lua_State *);
        void SET_SPEED_EX(lua_State *);
        void WHOLE_HIT(lua_State *);
        void HIT_NODE(lua_State *);
        void CAM_ZOOM_IN_arg5(lua_State *);
        void CAM_ZOOM_IN_arg6(lua_State *);
        void CAM_ZOOM_IN_FINAL(lua_State *);
        void REQ_FINAL_START_CAMERA(lua_State *);
        void REQ_FINAL_START_CAMERA_arg3(lua_State *);
        void REQ_MOTION_CAMERA(lua_State *);
        void CHECK_FINISH_CAMERA(lua_State *);
        void QUAKE(lua_State *);
        void FT_MOTION_INTP_WAIT(lua_State *);
        void FT_MOTION_INTP_WAIT_ITEM(lua_State *);
        void FT_MOTION_INTP_TURN_END(lua_State *);
        void FT_MOTION_CHANGE_HAVE_ITEM(lua_State *);
        void ATK_NO_REACTION_SEARCH_WITCH_TIME(lua_State *);
        void FT_CATCH_STOP(lua_State *);
        void FT_ADD_DAMAGE(lua_State *);
        void RUMBLE_HIT(lua_State *);
        void RUMBLE_FINAL_TARGET(lua_State *);
        void RUMBLE_FINAL_OTHER(lua_State *);
        void FT_START_CUTIN(lua_State *);
        void FT_START_CUTIN_arg1(lua_State *);
        void FT_SET_FINAL_FEAR_FACE(lua_State *);
        void FT_UPDATE_FACE_MOTION(lua_State *);
        void FT_REQ_FINAL_AURA(lua_State *);
        void FT_REMOVE_FINAL_AURA(lua_State *);
        void FT_LEAVE_NEAR_OTTOTTO(lua_State *);
        void FT_SHOOTING_ATTACK_GROUND_CHECK_NEW(lua_State *);
        void PLAY_SE(lua_State *);
        void PLAY_SE_NO_3D(lua_State *);
        void PLAY_SE_NO_3D_FORCE_AUTO_PITCH(lua_State *);
        void PLAY_SE_REMAIN(lua_State *);
        void PLAY_STATUS(lua_State *);
        void STOP_SE(lua_State *);
        void PLAY_STEP(lua_State *);
        void PLAY_STEP_FLIPPABLE(lua_State *);
        void PLAY_LANDING_SE(lua_State *);
        void PLAY_SEQUENCE(lua_State *);
        void PLAY_DAMAGESTOP(lua_State *);
        void PLAY_SEQUENCE_DAMAGESTOP(lua_State *);
        void SET_TAKEOUT_SE(lua_State *);
        void PLAY_FLY_VOICE(lua_State *);
    }
}

// ---- Functions ---------------------------------------------------------------

// 0x7101fbfaf0
u32 FUN_7101fbfaf0(lua_State *param_1) { app::sv_animcmd::SET_RATE_ARTICLE(param_1); return 0; }

// 0x7101fbfd30
u32 FUN_7101fbfd30(lua_State *param_1) { app::sv_animcmd::ADD_SPEED_NO_LIMIT(param_1); return 0; }

// 0x7101fc0db0
u32 FUN_7101fc0db0(lua_State *param_1) { app::sv_animcmd::SET_SPEED(param_1); return 0; }

// 0x7101fc0dd0
u32 FUN_7101fc0dd0(lua_State *param_1) { app::sv_animcmd::SET_SPEED_EX(param_1); return 0; }

// 0x7101fc0df0
u32 FUN_7101fc0df0(lua_State *param_1) { app::sv_animcmd::SET_SPEED_EX(param_1); return 0; }

// 0x7101fc0e10
u32 FUN_7101fc0e10(lua_State *param_1) { app::sv_animcmd::SET_SPEED_EX(param_1); return 0; }

// 0x7101fc0e30
u32 FUN_7101fc0e30(lua_State *param_1) { app::sv_animcmd::WHOLE_HIT(param_1); return 0; }

// 0x7101fc0e50
u32 FUN_7101fc0e50(lua_State *param_1) { app::sv_animcmd::HIT_NODE(param_1); return 0; }

// 0x7101fc0fe0
u32 FUN_7101fc0fe0(lua_State *param_1) { app::sv_animcmd::CAM_ZOOM_IN_arg5(param_1); return 0; }

// 0x7101fc1000
u32 FUN_7101fc1000(lua_State *param_1) { app::sv_animcmd::CAM_ZOOM_IN_arg6(param_1); return 0; }

// 0x7101fc1020
u32 FUN_7101fc1020(lua_State *param_1) { app::sv_animcmd::CAM_ZOOM_IN_FINAL(param_1); return 0; }

// 0x7101fc1140
u32 FUN_7101fc1140(lua_State *param_1) { app::sv_animcmd::REQ_FINAL_START_CAMERA(param_1); return 0; }

// 0x7101fc1160
u32 FUN_7101fc1160(lua_State *param_1) { app::sv_animcmd::REQ_FINAL_START_CAMERA_arg3(param_1); return 0; }

// 0x7101fc1180
u32 FUN_7101fc1180(lua_State *param_1) { app::sv_animcmd::REQ_MOTION_CAMERA(param_1); return 0; }

// 0x7101fc11a0
u32 FUN_7101fc11a0(lua_State *param_1) { app::sv_animcmd::CHECK_FINISH_CAMERA(param_1); return 0; }

// 0x7101fc12a0
u32 FUN_7101fc12a0(lua_State *param_1) { app::sv_animcmd::QUAKE(param_1); return 0; }

// 0x7101fc22c0
u32 FUN_7101fc22c0(lua_State *param_1) { app::sv_animcmd::FT_MOTION_INTP_WAIT(param_1); return 0; }

// 0x7101fc22e0
u32 FUN_7101fc22e0(lua_State *param_1) { app::sv_animcmd::FT_MOTION_INTP_WAIT_ITEM(param_1); return 0; }

// 0x7101fc2300
u32 FUN_7101fc2300(lua_State *param_1) { app::sv_animcmd::FT_MOTION_INTP_TURN_END(param_1); return 0; }

// 0x7101fc2320
u32 FUN_7101fc2320(lua_State *param_1) { app::sv_animcmd::FT_MOTION_CHANGE_HAVE_ITEM(param_1); return 0; }

// 0x7101fc2b80
u32 FUN_7101fc2b80(lua_State *param_1) { app::sv_animcmd::ATK_NO_REACTION_SEARCH_WITCH_TIME(param_1); return 0; }

// 0x7101fc2ba0
u32 FUN_7101fc2ba0(lua_State *param_1) { app::sv_animcmd::FT_CATCH_STOP(param_1); return 0; }

// 0x7101fc2bc0
u32 FUN_7101fc2bc0(lua_State *param_1) { app::sv_animcmd::FT_ADD_DAMAGE(param_1); return 0; }

// 0x7101fc2be0
u32 FUN_7101fc2be0(lua_State *param_1) { app::sv_animcmd::RUMBLE_HIT(param_1); return 0; }

// 0x7101fc2c60
u32 FUN_7101fc2c60(lua_State *param_1) { app::sv_animcmd::RUMBLE_FINAL_TARGET(param_1); return 0; }

// 0x7101fc2c80
u32 FUN_7101fc2c80(lua_State *param_1) { app::sv_animcmd::RUMBLE_FINAL_OTHER(param_1); return 0; }

// 0x7101fc2e80
u32 FUN_7101fc2e80(lua_State *param_1) { app::sv_animcmd::FT_START_CUTIN(param_1); return 0; }

// 0x7101fc2ea0
u32 FUN_7101fc2ea0(lua_State *param_1) { app::sv_animcmd::FT_START_CUTIN_arg1(param_1); return 0; }

// 0x7101fc2f20
u32 FUN_7101fc2f20(lua_State *param_1) { app::sv_animcmd::FT_SET_FINAL_FEAR_FACE(param_1); return 0; }

// 0x7101fc2f40
u32 FUN_7101fc2f40(lua_State *param_1) { app::sv_animcmd::FT_UPDATE_FACE_MOTION(param_1); return 0; }

// 0x7101fc2f60
u32 FUN_7101fc2f60(lua_State *param_1) { app::sv_animcmd::FT_REQ_FINAL_AURA(param_1); return 0; }

// 0x7101fc2f80
u32 FUN_7101fc2f80(lua_State *param_1) { app::sv_animcmd::FT_REMOVE_FINAL_AURA(param_1); return 0; }

// 0x7101fc3010
u32 FUN_7101fc3010(lua_State *param_1) { app::sv_animcmd::FT_LEAVE_NEAR_OTTOTTO(param_1); return 0; }

// 0x7101fc3030
u32 FUN_7101fc3030(lua_State *param_1) { app::sv_animcmd::FT_SHOOTING_ATTACK_GROUND_CHECK_NEW(param_1); return 0; }

// 0x7101fc3190
u32 FUN_7101fc3190(lua_State *param_1) { app::sv_animcmd::PLAY_SE(param_1); return 0; }

// 0x7101fc31b0
u32 FUN_7101fc31b0(lua_State *param_1) { app::sv_animcmd::PLAY_SE_NO_3D(param_1); return 0; }

// 0x7101fc31d0
u32 FUN_7101fc31d0(lua_State *param_1) { app::sv_animcmd::PLAY_SE_NO_3D_FORCE_AUTO_PITCH(param_1); return 0; }

// 0x7101fc31f0
u32 FUN_7101fc31f0(lua_State *param_1) { app::sv_animcmd::PLAY_SE_REMAIN(param_1); return 0; }

// 0x7101fc3210
u32 FUN_7101fc3210(lua_State *param_1) { app::sv_animcmd::PLAY_STATUS(param_1); return 0; }

// 0x7101fc3230
u32 FUN_7101fc3230(lua_State *param_1) { app::sv_animcmd::STOP_SE(param_1); return 0; }

// 0x7101fc33b0
u32 FUN_7101fc33b0(lua_State *param_1) { app::sv_animcmd::PLAY_STEP(param_1); return 0; }

// 0x7101fc33d0
u32 FUN_7101fc33d0(lua_State *param_1) { app::sv_animcmd::PLAY_STEP_FLIPPABLE(param_1); return 0; }

// 0x7101fc33f0
u32 FUN_7101fc33f0(lua_State *param_1) { app::sv_animcmd::PLAY_LANDING_SE(param_1); return 0; }

// 0x7101fc3b30
u32 FUN_7101fc3b30(lua_State *param_1) { app::sv_animcmd::PLAY_SEQUENCE(param_1); return 0; }

// 0x7101fc3b50
u32 FUN_7101fc3b50(lua_State *param_1) { app::sv_animcmd::PLAY_DAMAGESTOP(param_1); return 0; }

// 0x7101fc3b70
u32 FUN_7101fc3b70(lua_State *param_1) { app::sv_animcmd::PLAY_SEQUENCE_DAMAGESTOP(param_1); return 0; }

// 0x7101fc3b90
u32 FUN_7101fc3b90(lua_State *param_1) { app::sv_animcmd::SET_TAKEOUT_SE(param_1); return 0; }

// 0x7101fc3e90
u32 FUN_7101fc3e90(lua_State *param_1) { app::sv_animcmd::PLAY_FLY_VOICE(param_1); return 0; }
