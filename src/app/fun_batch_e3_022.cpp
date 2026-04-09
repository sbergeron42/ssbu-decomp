#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"

using app::MotionModule;

// MotionModule lua_bind thunks — 0x710205ce20..0x710205d200
// All functions: accessor->motion_module (+0x88) -> vtable dispatch, 4/5-insn tail calls
// +0x88 -> motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]

// ---- Module offset 0x88 (MotionModule) — continued -------------------------

// 0x710205ce20 (16 bytes) — MotionModule::resource_id [slot 80]
// [derived: MotionModule__resource_id_impl (.dynsym) -> slot 80 (0x280/8)]
u64 FUN_710205ce20(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->resource_id(p1));
}

// 0x710205ce30 (16 bytes) — MotionModule::animcmd_name_hash [slot 81]
// [derived: MotionModule__animcmd_name_hash_impl (.dynsym) -> slot 81 (0x288/8)]
u64 FUN_710205ce30(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->animcmd_name_hash(p1));
}

// 0x710205ce40 (16 bytes) — MotionModule::trans_hash [slot 83]
// [derived: MotionModule__trans_hash_impl (.dynsym) -> slot 83 (0x298/8)]
u64 FUN_710205ce40(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->trans_hash();
}

// 0x710205ce50 (16 bytes) — MotionModule::prev_weight [slot 84]
// [derived: MotionModule__prev_weight_impl (.dynsym) -> slot 84 (0x2a0/8)]
float FUN_710205ce50(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->prev_weight();
}

// 0x710205ce60 (16 bytes) — MotionModule::body_hash [slot 86]
// [derived: MotionModule__body_hash_impl (.dynsym) -> slot 86 (0x2b0/8)]
u64 FUN_710205ce60(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->body_hash();
}

// 0x710205ce70 (16 bytes) — MotionModule::calc_joint [slot 87]
// [derived: MotionModule__calc_joint_impl (.dynsym) -> slot 87 (0x2b8/8)]
void FUN_710205ce70(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2, u64 p3) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->calc_joint(p1, p2, p3);
}

// 0x710205ce80 (16 bytes) — MotionModule::update_dynamic_skeleton_without_complete_matrix [slot 88]
// [derived: MotionModule__update_dynamic_skeleton_without_complete_matrix_impl (.dynsym) -> slot 88 (0x2c0/8)]
void FUN_710205ce80(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->update_dynamic_skeleton_without_complete_matrix();
}

// 0x710205ce90 (16 bytes) — MotionModule::joint_local_rotation [slot 90]
// [derived: MotionModule__joint_local_rotation_impl (.dynsym) -> slot 90 (0x2d0/8)]
u64 FUN_710205ce90(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->joint_local_rotation(p1, p2));
}

// 0x710205cea0 (16 bytes) — MotionModule::joint_local_tra_2nd [slot 91]
// [derived: MotionModule__joint_local_tra_2nd_impl (.dynsym) -> slot 91 (0x2d8/8)]
u64 FUN_710205cea0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->joint_local_tra_2nd(p1));
}

// 0x710205ceb0 (16 bytes) — MotionModule::end_frame_2nd [slot 92]
// [derived: MotionModule__end_frame_2nd_impl (.dynsym) -> slot 92 (0x2e0/8)]
float FUN_710205ceb0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->end_frame_2nd();
}

// 0x710205cec0 (16 bytes) — MotionModule::is_end_2nd [slot 93]
// [derived: MotionModule__is_end_2nd_impl (.dynsym) -> slot 93 (0x2e8/8)]
bool FUN_710205cec0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_end_2nd();
}

// 0x710205ced0 (16 bytes) — MotionModule::motion_kind_2nd [slot 94]
// [derived: MotionModule__motion_kind_2nd_impl (.dynsym) -> slot 94 (0x2f0/8)]
u64 FUN_710205ced0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->motion_kind_2nd();
}

// 0x710205cee0 (16 bytes) — MotionModule::is_flag_link [slot 95]
// [derived: MotionModule__is_flag_link_impl (.dynsym) -> slot 95 (0x2f8/8)]
bool FUN_710205cee0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_link(p1);
}

// 0x710205cef0 (16 bytes) — MotionModule::is_flag_start_1_frame_from_motion_kind [slot 96]
// [derived: MotionModule__is_flag_start_1_frame_from_motion_kind_impl (.dynsym) -> slot 96 (0x300/8)]
bool FUN_710205cef0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_start_1_frame_from_motion_kind(p1);
}

// 0x710205cf00 (16 bytes) — MotionModule::is_flag_start_1_frame [slot 97]
// [derived: MotionModule__is_flag_start_1_frame_impl (.dynsym) -> slot 97 (0x308/8)]
bool FUN_710205cf00(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_start_1_frame();
}

// 0x710205cf10 (16 bytes) — MotionModule::is_flag_start_1_frame_2nd [slot 98]
// [derived: MotionModule__is_flag_start_1_frame_2nd_impl (.dynsym) -> slot 98 (0x310/8)]
bool FUN_710205cf10(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_start_1_frame_2nd();
}

// 0x710205cf20 (16 bytes) — MotionModule::joint_rotate [slot 99]
// [derived: MotionModule__joint_rotate_impl (.dynsym) -> slot 99 (0x318/8)]
u64 FUN_710205cf20(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->joint_rotate(p1, p2));
}

// 0x710205cf60 (20 bytes) — MotionModule::remove_motion_partial [slot 101]
// [derived: MotionModule__remove_motion_partial_impl (.dynsym) -> slot 101 (0x328/8)]
void FUN_710205cf60(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->remove_motion_partial(p1, p2 & 1);
}

// 0x710205cf80 (16 bytes) — MotionModule::remove_motion_partial_comp [slot 103]
// [derived: MotionModule__remove_motion_partial_comp_impl (.dynsym) -> slot 103 (0x338/8)]
void FUN_710205cf80(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->remove_motion_partial_comp(p1);
}

// 0x710205cf90 (16 bytes) — MotionModule::motion_kind_partial [slot 104]
// [derived: MotionModule__motion_kind_partial_impl (.dynsym) -> slot 104 (0x340/8)]
u64 FUN_710205cf90(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->motion_kind_partial(p1));
}

// 0x710205cfa0 (16 bytes) — MotionModule::is_end_partial [slot 105]
// [derived: MotionModule__is_end_partial_impl (.dynsym) -> slot 105 (0x348/8)]
bool FUN_710205cfa0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_end_partial(p1);
}

// 0x710205cfb0 (16 bytes) — MotionModule::end_frame_partial [slot 106]
// [derived: MotionModule__end_frame_partial_impl (.dynsym) -> slot 106 (0x350/8)]
float FUN_710205cfb0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->end_frame_partial_f32(p1);
}

// 0x710205cfc0 (16 bytes) — MotionModule::set_rate_partial [slot 107]
// [derived: MotionModule__set_rate_partial_impl (.dynsym) -> slot 107 (0x358/8)]
void FUN_710205cfc0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_rate_partial(p1);
}

// 0x710205cfd0 (16 bytes) — MotionModule::rate_partial [slot 108]
// [derived: MotionModule__rate_partial_impl (.dynsym) -> slot 108 (0x360/8)]
float FUN_710205cfd0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->rate_partial_f32(p1);
}

// 0x710205cfe0 (16 bytes) — MotionModule::frame_partial [slot 109]
// [derived: MotionModule__frame_partial_impl (.dynsym) -> slot 109 (0x368/8)]
float FUN_710205cfe0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->frame_partial_f32(p1);
}

// 0x710205cff0 (16 bytes) — MotionModule::prev_frame_partial [slot 110]
// [derived: MotionModule__prev_frame_partial_impl (.dynsym) -> slot 110 (0x370/8)]
float FUN_710205cff0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->prev_frame_partial_f32(p1);
}

// 0x710205d000 (20 bytes) — MotionModule::set_frame_partial [slot 111]
// [derived: MotionModule__set_frame_partial_impl (.dynsym) -> slot 111 (0x378/8)]
void FUN_710205d000(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_frame_partial(p1, p2 & 1);
}

// 0x710205d020 (20 bytes) — MotionModule::set_frame_partial_sync_anim_cmd [slot 112]
// [derived: MotionModule__set_frame_partial_sync_anim_cmd_impl (.dynsym) -> slot 112 (0x380/8)]
void FUN_710205d020(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_frame_partial_sync_anim_cmd(p1, p2 & 1);
}

// 0x710205d040 (16 bytes) — MotionModule::is_flag_start_1_frame_partial [slot 113]
// [derived: MotionModule__is_flag_start_1_frame_partial_impl (.dynsym) -> slot 113 (0x388/8)]
bool FUN_710205d040(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_start_1_frame_partial(p1);
}

// 0x710205d050 (16 bytes) — MotionModule::is_flip [slot 114]
// [derived: MotionModule__is_flip_impl (.dynsym) -> slot 114 (0x390/8)]
bool FUN_710205d050(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flip();
}

// 0x710205d080 (20 bytes) — MotionModule::set_link_flip_target_joint [slot 117]
// [derived: MotionModule__set_link_flip_target_joint_impl (.dynsym) -> slot 117 (0x3a8/8)]
void FUN_710205d080(app::BattleObjectModuleAccessor* acc, u32 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_link_flip_target_joint(p1 & 1);
}

// 0x710205d0a0 (16 bytes) — MotionModule::set_frame_material [slot 118]
// [derived: MotionModule__set_frame_material_impl (.dynsym) -> slot 118 (0x3b0/8)]
void FUN_710205d0a0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_frame_material(p1);
}

// 0x710205d0b0 (16 bytes) — MotionModule::set_frame_material_2nd [slot 119]
// [derived: MotionModule__set_frame_material_2nd_impl (.dynsym) -> slot 119 (0x3b8/8)]
void FUN_710205d0b0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_frame_material_2nd(p1);
}

// 0x710205d0c0 (16 bytes) — MotionModule::set_loop_flag_material [slot 120]
// [derived: MotionModule__set_loop_flag_material_impl (.dynsym) -> slot 120 (0x3c0/8)]
void FUN_710205d0c0(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_loop_flag_material(p1, p2);
}

// 0x710205d0d0 (16 bytes) — MotionModule::get_frame_material [slot 121]
// [derived: MotionModule__get_frame_material_impl (.dynsym) -> slot 121 (0x3c8/8)]
u64 FUN_710205d0d0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->get_frame_material(p1));
}

// 0x710205d120 (16 bytes) — MotionModule::whole_rate [slot 126]
// [derived: MotionModule__whole_rate_impl (.dynsym) -> slot 126 (0x3f0/8)]
float FUN_710205d120(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->whole_rate_f32();
}

// 0x710205d130 (16 bytes) — MotionModule::is_flag_disable_change_motion [slot 127]
// [derived: MotionModule__is_flag_disable_change_motion_impl (.dynsym) -> slot 127 (0x3f8/8)]
bool FUN_710205d130(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flag_disable_change_motion();
}

// 0x710205d140 (16 bytes) — MotionModule vtable[130] dispatch (f32 return)
// [inferred: slot 130 (0x410/8) returns f32 in this lua_bind context]
float FUN_710205d140(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->update_rate_f32();
}

// 0x710205d190 (16 bytes) — MotionModule::is_no_comp [slot 136]
// [derived: MotionModule__is_no_comp_impl (.dynsym) -> slot 136 (0x440/8)]
bool FUN_710205d190(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_no_comp();
}

// 0x710205d1a0 (16 bytes) — MotionModule::set_kind_offset [slot 137]
// [derived: MotionModule__set_kind_offset_impl (.dynsym) -> slot 137 (0x448/8)]
void FUN_710205d1a0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_kind_offset(p1);
}

// 0x710205d1d0 (16 bytes) — MotionModule::trans_joint_scale [slot 142]
// [derived: MotionModule__trans_joint_scale_impl (.dynsym) -> slot 142 (0x470/8)]
u64 FUN_710205d1d0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->trans_joint_scale());
}

// 0x710205d200 (16 bytes) — MotionModule::is_flip_resource [slot 148]
// [derived: MotionModule__is_flip_resource_impl (.dynsym) -> slot 148 (0x4a0/8)]
bool FUN_710205d200(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_flip_resource();
}
