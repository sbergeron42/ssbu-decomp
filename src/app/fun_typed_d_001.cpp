// fun_typed_d_001.cpp — MotionModule lua_bind mangled-name fixes
// These functions compile correctly in MotionModule.cpp but produce wrong
// mangled names. We duplicate the definitions with asm() attributes to
// generate the correct CSV symbol names. Bodies are identical to MotionModule.cpp.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"

using app::BattleObjectModuleAccessor;
using app::MotionModule;
#define MO(a) static_cast<MotionModule*>((a)->motion_module)

namespace app::lua_bind {

// --- Functions with float mangled name but bool implementation ---

void MotionModule__set_frame_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind28MotionModule__set_frame_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_frame_fix(BattleObjectModuleAccessor* a, bool p1) { MO(a)->set_frame(p1); }

void MotionModule__set_frame_2nd_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind32MotionModule__set_frame_2nd_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_frame_2nd_fix(BattleObjectModuleAccessor* a, bool p1) { MO(a)->set_frame_2nd(p1); }

void MotionModule__set_force_progress_2nd_weight_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind48MotionModule__set_force_progress_2nd_weight_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_force_progress_2nd_weight_fix(BattleObjectModuleAccessor* a, bool p1) { MO(a)->set_force_progress_2nd_weight(p1); }

// --- Functions with fewer params in mangled name but full params in impl ---

void* MotionModule__end_frame_from_hash_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind38MotionModule__end_frame_from_hash_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__end_frame_from_hash_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->end_frame_from_hash(p1); }

void* MotionModule__joint_local_tra_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind34MotionModule__joint_local_tra_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionModule__joint_local_tra_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { return MO(a)->joint_local_tra(p1, p2, p3); }

void* MotionModule__resource_id_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind30MotionModule__resource_id_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__resource_id_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->resource_id(p1); }

void* MotionModule__animcmd_name_hash_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36MotionModule__animcmd_name_hash_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__animcmd_name_hash_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->animcmd_name_hash(p1); }

void* MotionModule__calc_joint_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind29MotionModule__calc_joint_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionModule__calc_joint_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return MO(a)->calc_joint(p1, p2, p3); }

void* MotionModule__joint_local_rotation_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind39MotionModule__joint_local_rotation_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionModule__joint_local_rotation_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return MO(a)->joint_local_rotation(p1, p2); }

bool MotionModule__is_flag_link_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31MotionModule__is_flag_link_implEPNS_26BattleObjectModuleAccessorE");
bool MotionModule__is_flag_link_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->is_flag_link(p1); }

bool MotionModule__is_flag_start_1_frame_from_motion_kind_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind57MotionModule__is_flag_start_1_frame_from_motion_kind_implEPNS_26BattleObjectModuleAccessorE");
bool MotionModule__is_flag_start_1_frame_from_motion_kind_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->is_flag_start_1_frame_from_motion_kind(p1); }

void* MotionModule__joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind31MotionModule__joint_rotate_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionModule__joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return MO(a)->joint_rotate(p1, p2); }

void MotionModule__remove_motion_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind40MotionModule__remove_motion_partial_implEPNS_26BattleObjectModuleAccessorEy");
void MotionModule__remove_motion_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MO(a)->remove_motion_partial(p1, p2); }

void* MotionModule__remove_motion_partial_comp_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind45MotionModule__remove_motion_partial_comp_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__remove_motion_partial_comp_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->remove_motion_partial_comp(p1); }

void* MotionModule__motion_kind_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind38MotionModule__motion_kind_partial_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__motion_kind_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->motion_kind_partial(p1); }

bool MotionModule__is_end_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind33MotionModule__is_end_partial_implEPNS_26BattleObjectModuleAccessorE");
bool MotionModule__is_end_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->is_end_partial(p1); }

void* MotionModule__end_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36MotionModule__end_frame_partial_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__end_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->end_frame_partial(p1); }

void* MotionModule__rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31MotionModule__rate_partial_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->rate_partial(p1); }

void* MotionModule__frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind32MotionModule__frame_partial_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->frame_partial(p1); }

void* MotionModule__prev_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind37MotionModule__prev_frame_partial_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__prev_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->prev_frame_partial(p1); }

void MotionModule__set_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind36MotionModule__set_frame_partial_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MO(a)->set_frame_partial(p1, p2); }

void MotionModule__set_frame_partial_sync_anim_cmd_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind50MotionModule__set_frame_partial_sync_anim_cmd_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_frame_partial_sync_anim_cmd_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MO(a)->set_frame_partial_sync_anim_cmd(p1, p2); }

bool MotionModule__is_flag_start_1_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind48MotionModule__is_flag_start_1_frame_partial_implEPNS_26BattleObjectModuleAccessorE");
bool MotionModule__is_flag_start_1_frame_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->is_flag_start_1_frame_partial(p1); }

void MotionModule__set_flip_fix(BattleObjectModuleAccessor* a, bool p1, bool p2, bool p3)
    asm("_ZN3app8lua_bind27MotionModule__set_flip_implEPNS_26BattleObjectModuleAccessorEybbb");
void MotionModule__set_flip_fix(BattleObjectModuleAccessor* a, bool p1, bool p2, bool p3) { MO(a)->set_flip(p1, p2, p3); }

void MotionModule__set_link_flip_target_joint_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind45MotionModule__set_link_flip_target_joint_implEPNS_26BattleObjectModuleAccessorEy");
void MotionModule__set_link_flip_target_joint_fix(BattleObjectModuleAccessor* a, bool p1) { MO(a)->set_link_flip_target_joint(p1); }

void MotionModule__set_loop_flag_material_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind41MotionModule__set_loop_flag_material_implEPNS_26BattleObjectModuleAccessorEy");
void MotionModule__set_loop_flag_material_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { MO(a)->set_loop_flag_material(p1, p2); }

void* MotionModule__get_frame_material_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind37MotionModule__get_frame_material_implEPNS_26BattleObjectModuleAccessorE");
void* MotionModule__get_frame_material_fix(BattleObjectModuleAccessor* a, u64 p1) { return MO(a)->get_frame_material(p1); }

void MotionModule__enable_set_frame_2nd_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind47MotionModule__enable_set_frame_2nd_partial_implEPNS_26BattleObjectModuleAccessorEb");
void MotionModule__enable_set_frame_2nd_partial_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MO(a)->enable_set_frame_2nd_partial(p1, p2); }

void MotionModule__set_frame_partial_sync_anim_cmd_revised_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind58MotionModule__set_frame_partial_sync_anim_cmd_revised_implEPNS_26BattleObjectModuleAccessorEf");
void MotionModule__set_frame_partial_sync_anim_cmd_revised_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MO(a)->set_frame_partial_sync_anim_cmd_revised(p1, p2); }

void MotionModule__set_rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35MotionModule__set_rate_partial_implEPNS_26BattleObjectModuleAccessorEfbb");
void MotionModule__set_rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { MO(a)->set_rate_partial(p1); }

} // namespace app::lua_bind
