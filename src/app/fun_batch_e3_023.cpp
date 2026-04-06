#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"
#include "app/modules/MotionAnimcmdModule.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-023
// MotionModule thunks 0x710205d0e0–0x710205d3a0
// MotionAnimcmdModule thunks 0x7102069040–0x71020691a0
// Pattern: accessor->module → vtable dispatch, 4/5-insn tail calls

// ---- MotionModule (accessor+0x88) — bool-setter variants ---------------

// 0x710205d0e0 (20 bytes)
// [derived: MotionModule__set_helper_calculation_impl (.dynsym) -> slot 122 (0x3d0/8)]
void FUN_710205d0e0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_helper_calculation(p1 & 1);
}

// 0x710205d100 (20 bytes)
// [derived: MotionModule__set_helper_calculation_2nd_impl (.dynsym) -> slot 123 (0x3d8/8); also set_skip_rate]
void FUN_710205d100(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_helper_calculation_2nd(p1 & 1);
}

// 0x710205d150 (20 bytes)
// [derived: MotionModule__set_recalc_ik_impl (.dynsym) -> slot 132 (0x420/8)]
void FUN_710205d150(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_recalc_ik(p1 & 1);
}

// 0x710205d170 (20 bytes)
// [derived: MotionModule__set_no_comp_impl (.dynsym) -> slot 135 (0x438/8); also set_no_comp_2nd]
void FUN_710205d170(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_no_comp(p1 & 1);
}

// 0x710205d1b0 (20 bytes)
// [derived: MotionModule__enable_shift_material_animation_impl (.dynsym) -> slot 141 (0x468/8)]
void FUN_710205d1b0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->enable_shift_material_animation(p1 & 1);
}

// 0x710205d1e0 (20 bytes)
// [derived: MotionModule__enable_shift_material_animation_2nd_impl (.dynsym) -> slot 143 (0x478/8); also set_stop_interpolation]
void FUN_710205d1e0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->enable_shift_material_animation_2nd(p1 & 1);
}

// 0x710205d210 (20 bytes)
// [derived: MotionModule__set_force_progress_2nd_weight_2nd_impl (.dynsym) -> slot 152 (0x4c0/8); also set_reverse]
void FUN_710205d210(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_force_progress_2nd_weight_2nd(p1 & 1);
}

// 0x710205d230 (20 bytes)
// [derived: MotionModule__set_force_progress_2nd_weight_impl (.dynsym) -> slot 159 (0x4f8/8)]
void FUN_710205d230(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_force_progress_2nd_weight(p1 & 1);
}

// 0x710205d250 (16 bytes)
// [derived: MotionModule__clear_joint_srt_impl (.dynsym) -> slot 160 (0x500/8)]
void FUN_710205d250(app::BattleObjectModuleAccessor* acc, u64 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->clear_joint_srt(p1);
}

// 0x710205d280 (20 bytes)
// [derived: MotionModule__set_keep_pose_change_motion_impl (.dynsym) -> slot 177 (0x588/8)]
void FUN_710205d280(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_keep_pose_change_motion(p1 & 1);
}

// 0x710205d2a0 (16 bytes)
// [derived: MotionModule__set_keep_anim_frame_change_motion_impl (.dynsym) -> slot 178 (0x590/8); also set_next_no_comp]
void FUN_710205d2a0(app::BattleObjectModuleAccessor* acc) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_keep_anim_frame_change_motion();
}

// 0x710205d2b0 (16 bytes)
// [derived: MotionModule__set_keep_anim_frame_change_motion_2nd_impl (.dynsym) -> slot 179 (0x598/8); also set_remove_change_motion_partial]
void FUN_710205d2b0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_keep_anim_frame_change_motion_2nd(p1);
}

// 0x710205d2c0 (20 bytes)
// [derived: MotionModule__set_keep_anim_frame_change_motion_partial_impl (.dynsym) -> slot 180 (0x5a0/8); also set_remove_partial_after_intp]
void FUN_710205d2c0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_keep_anim_frame_change_motion_partial(p1 & 1);
}

// 0x710205d2e0 (20 bytes)
// [derived: MotionModule__enable_remove_2nd_change_motion_impl (.dynsym) -> slot 183 (0x5b8/8)]
void FUN_710205d2e0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->enable_remove_2nd_change_motion(p1 & 1);
}

// 0x710205d300 (20 bytes)
// [derived: MotionModule__enable_set_frame_2nd_partial_impl (.dynsym) -> slot 184 (0x5c0/8)]
void FUN_710205d300(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->enable_set_frame_2nd_partial(p1, p2 & 1);
}

// 0x710205d320 (20 bytes)
// [derived: MotionModule__set_frame_partial_sync_anim_cmd_revised_impl (.dynsym) -> slot 185 (0x5c8/8)]
void FUN_710205d320(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_frame_partial_sync_anim_cmd_revised(p1, p2 & 1);
}

// 0x710205d340 (20 bytes)
// [derived: MotionModule__set_link_no_2nd_impl (.dynsym) -> slot 186 (0x5d0/8); also set_part_animcmd_fix]
void FUN_710205d340(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_link_no_2nd(p1 & 1);
}

// 0x710205d360 (20 bytes)
// [derived: MotionModule__set_keep_pose_change_motion_with_update_pose_impl (.dynsym) -> slot 188 (0x5e0/8)]
void FUN_710205d360(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_keep_pose_change_motion_with_update_pose(p1 & 1);
}

// 0x710205d380 (20 bytes)
// [derived: MotionModule__set_animcmd_done_impl (.dynsym) -> slot 191 (0x5f8/8)]
void FUN_710205d380(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_animcmd_done(p1 & 1);
}

// 0x710205d3a0 (16 bytes)
// [derived: MotionModule__set_link_no_impl (.dynsym) -> slot 192 (0x600/8)]
void FUN_710205d3a0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    app::MotionModule* mod = static_cast<app::MotionModule*>(acc->motion_module);
    mod->set_link_no(p1);
}

// ---- MotionAnimcmdModule (accessor+0x188) ----------------------------------

// 0x7102069040 (16 bytes)
// [derived: MotionAnimcmdModule__exec_motion_lines_impl (.dynsym) -> slot 11 (0x58/8)]
void FUN_7102069040(app::BattleObjectModuleAccessor* acc) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->exec_motion_lines();
}

// 0x7102069090 (16 bytes)
// [derived: MotionAnimcmdModule__call_script_single_impl (.dynsym) -> slot 15 (0x78/8)]
void FUN_7102069090(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2, u64 p3) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->call_script_single(p1, p2, p3);
}

// 0x71020690a0 (16 bytes)
// [derived: MotionAnimcmdModule__change_script_motion_line_single_impl (.dynsym) -> slot 16 (0x80/8)]
void FUN_71020690a0(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2, u64 p3) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->change_script_motion_line_single(p1, p2, p3);
}

// 0x71020690b0 (20 bytes)
// [derived: MotionAnimcmdModule__exec_motion_lines_initialize_impl (.dynsym) -> slot 17 (0x88/8)]
void FUN_71020690b0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->exec_motion_lines_initialize(p1 & 1);
}

// 0x71020690d0 (16 bytes)
// [derived: MotionAnimcmdModule__flush_current_motion_impl (.dynsym) -> slot 18 (0x90/8)]
void FUN_71020690d0(app::BattleObjectModuleAccessor* acc) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->flush_current_motion();
}

// 0x71020690e0 (20 bytes)
// [derived: MotionAnimcmdModule__flush_impl (.dynsym) -> slot 19 (0x98/8)]
void FUN_71020690e0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->flush(p1 & 1);
}

// 0x7102069100 (20 bytes)
// [derived: MotionAnimcmdModule__set_sleep_impl (.dynsym) -> slot 20 (0xa0/8)]
void FUN_7102069100(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->set_sleep(p1 & 1);
}

// 0x7102069120 (20 bytes)
// [derived: MotionAnimcmdModule__set_sleep_game_impl (.dynsym) -> slot 21 (0xa8/8)]
void FUN_7102069120(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->set_sleep_game(p1 & 1);
}

// 0x7102069140 (20 bytes)
// [derived: MotionAnimcmdModule__set_sleep_effect_impl (.dynsym) -> slot 22 (0xb0/8)]
void FUN_7102069140(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->set_sleep_effect(p1 & 1);
}

// 0x7102069160 (20 bytes)
// [derived: MotionAnimcmdModule__set_sleep_sound_impl (.dynsym) -> slot 23 (0xb8/8)]
void FUN_7102069160(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->set_sleep_sound(p1 & 1);
}

// 0x7102069180 (16 bytes)
// [derived: MotionAnimcmdModule__is_sleep_impl (.dynsym) -> slot 24 (0xc0/8)]
bool FUN_7102069180(app::BattleObjectModuleAccessor* acc) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    return mod->is_sleep();
}

// 0x7102069190 (16 bytes)
// [derived: MotionAnimcmdModule__enable_skip_delay_update_impl (.dynsym) -> slot 25 (0xc8/8)]
void FUN_7102069190(app::BattleObjectModuleAccessor* acc) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->enable_skip_delay_update();
}

// 0x71020691a0 (20 bytes)
// [derived: MotionAnimcmdModule__set_change_partial_immediate_impl (.dynsym) -> slot 26 (0xd0/8)]
void FUN_71020691a0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    app::MotionAnimcmdModule* mod = static_cast<app::MotionAnimcmdModule*>(acc->motion_animcmd_module);
    mod->set_change_partial_immediate(p1 & 1);
}
