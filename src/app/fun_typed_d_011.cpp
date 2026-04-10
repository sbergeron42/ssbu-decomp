// fun_typed_d_011.cpp — Remaining module signature-fix dispatchers
// Area, ColorBlend, Damage, Jostle, Model, MotionAnimcmd, Posture, Shadow,
// Shake, Slow, Visibility, FighterWorkModuleImpl, FighterControlModuleImpl,
// FighterManager, FighterInformation

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/AreaModule.h"
#include "app/modules/ColorBlendModule.h"
#include "app/modules/JostleModule.h"
#include "app/modules/ModelModule.h"
#include "app/modules/PostureModule.h"
#include "app/FighterManager.h"
#include "app/FighterInformation.h"

using app::BattleObjectModuleAccessor;
using app::AreaModule;
using app::ColorBlendModule;
using app::JostleModule;
using app::ModelModule;
using app::PostureModule;

#define AM(a) static_cast<AreaModule*>((a)->fighter_area_module)
#define CB(a) static_cast<ColorBlendModule*>((a)->color_blend_module)
#define JM(a) static_cast<JostleModule*>((a)->jostle_module)
#define MM(a) static_cast<ModelModule*>((a)->model_module)
#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// ======================= AreaModule =======================

// add_wind_area_2nd: CSV=(acc,u64), build=(acc,u64,u64,u64,u64)
void AreaModule__add_wind_area_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4)
    asm("_ZN3app8lua_bind34AreaModule__add_wind_area_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__add_wind_area_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) {
    AM(a)->add_wind_area_2nd(p1, p2, p3, p4);
}

// add_wind_area_2nd_rad: CSV=(acc,u64), build=(acc,u64,u64,u64)
void AreaModule__add_wind_area_2nd_rad_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind38AreaModule__add_wind_area_2nd_rad_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__add_wind_area_2nd_rad_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    AM(a)->add_wind_area_2nd_rad(p1, p2, p3);
}

// enable_area: CSV=(acc,u64,bool), build=(acc,u64,bool,u64)
void AreaModule__enable_area_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind28AreaModule__enable_area_implEPNS_26BattleObjectModuleAccessorEyb");
void AreaModule__enable_area_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) {
    AM(a)->enable_area(p1, p2, p3);
}

// get_area_contact_count: CSV=no params, build=(u64)
u32 AreaModule__get_area_contact_count_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind39AreaModule__get_area_contact_count_implEPNS_26BattleObjectModuleAccessorE");
u32 AreaModule__get_area_contact_count_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return AM(a)->get_area_contact_count(p1);
}

// get_area_contact_log: CSV=(acc,u64), build=(acc,u64,u64)
void* AreaModule__get_area_contact_log_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind37AreaModule__get_area_contact_log_implEPNS_26BattleObjectModuleAccessorEy");
void* AreaModule__get_area_contact_log_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AM(a)->get_area_contact_log(p1, p2);
}

// get_area_contact_target_id: CSV=(acc,u64), build=(acc,u64,u64)
u32 AreaModule__get_area_contact_target_id_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind43AreaModule__get_area_contact_target_id_implEPNS_26BattleObjectModuleAccessorEy");
u32 AreaModule__get_area_contact_target_id_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AM(a)->get_area_contact_target_id(p1, p2);
}

// get_area_id: CSV=no params, build=(u64)
u32 AreaModule__get_area_id_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind28AreaModule__get_area_id_implEPNS_26BattleObjectModuleAccessorE");
u32 AreaModule__get_area_id_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return AM(a)->get_area_id(p1);
}

// get_group: CSV=no params, build=(u64)
void* AreaModule__get_group_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind26AreaModule__get_group_implEPNS_26BattleObjectModuleAccessorE");
void* AreaModule__get_group_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return AM(a)->get_group(p1);
}

// is_enable_area: CSV=no params, build=(u64)
bool AreaModule__is_enable_area_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31AreaModule__is_enable_area_implEPNS_26BattleObjectModuleAccessorE");
bool AreaModule__is_enable_area_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return AM(a)->is_enable_area(p1);
}

// layer: CSV=no params, build=(u64)
void* AreaModule__layer_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind22AreaModule__layer_implEPNS_26BattleObjectModuleAccessorE");
void* AreaModule__layer_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return AM(a)->layer(p1);
}

// set_area_shape_aabb: CSV=(acc,u64), build=(acc,u64,u64,u64)
void AreaModule__set_area_shape_aabb_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind36AreaModule__set_area_shape_aabb_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_area_shape_aabb_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    AM(a)->set_area_shape_aabb(p1, p2, p3);
}

// set_area_shape_circle: CSV=(acc,u64), build=(acc,u64,u64)
void AreaModule__set_area_shape_circle_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind38AreaModule__set_area_shape_circle_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_area_shape_circle_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AM(a)->set_area_shape_circle(p1, p2);
}

// set_area_shape_type: CSV=(acc,u64), build=(acc,u64,u64)
void AreaModule__set_area_shape_type_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind36AreaModule__set_area_shape_type_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_area_shape_type_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AM(a)->set_area_shape_type(p1, p2);
}

// set_area_target_group_mask: CSV=(acc,u64), build=(acc,u64,u64)
void AreaModule__set_area_target_group_mask_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind43AreaModule__set_area_target_group_mask_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_area_target_group_mask_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AM(a)->set_area_target_group_mask(p1, p2);
}

// set_area_target_local_group_mask: CSV=(acc,u64), build=(acc,u64,u64)
void AreaModule__set_area_target_local_group_mask_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind49AreaModule__set_area_target_local_group_mask_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_area_target_local_group_mask_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AM(a)->set_area_target_local_group_mask(p1, p2);
}

// set_center_x0: CSV=(acc,bool), build=(acc,u64,bool)
void AreaModule__set_center_x0_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind30AreaModule__set_center_x0_implEPNS_26BattleObjectModuleAccessorEb");
void AreaModule__set_center_x0_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    AM(a)->set_center_x0(p1, p2);
}

// set_layer: CSV=(acc,u64), build=(acc,u64,u64)
void AreaModule__set_layer_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind26AreaModule__set_layer_implEPNS_26BattleObjectModuleAccessorEy");
void AreaModule__set_layer_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AM(a)->set_layer(p1, p2);
}

// test_water: CSV=(acc,u64), build=(acc,u64,u64)
void* AreaModule__test_water_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind27AreaModule__test_water_implEPNS_26BattleObjectModuleAccessorEy");
void* AreaModule__test_water_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AM(a)->test_water(p1, p2);
}

// ======================= ColorBlendModule =======================

// set_main_color: CSV=(acc,u64,bool), build=(acc,u64,u64,u64,bool)
void ColorBlendModule__set_main_color_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind37ColorBlendModule__set_main_color_implEPNS_26BattleObjectModuleAccessorEyb");
void ColorBlendModule__set_main_color_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    CB(a)->set_main_color(p1, p2, p3, p4);
}

// set_shadow_bloom: CSV=(acc,u64,bool), ABI: bool in x1
void ColorBlendModule__set_shadow_bloom_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind39ColorBlendModule__set_shadow_bloom_implEPNS_26BattleObjectModuleAccessorEyb");
void ColorBlendModule__set_shadow_bloom_fix(BattleObjectModuleAccessor* a, bool p1) {
    CB(a)->set_shadow_bloom(p1);
}

// set_status: CSV=(acc,u64,bool), ABI: bool in x1
void ColorBlendModule__set_status_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind33ColorBlendModule__set_status_implEPNS_26BattleObjectModuleAccessorEyb");
void ColorBlendModule__set_status_fix(BattleObjectModuleAccessor* a, bool p1) {
    CB(a)->set_status(p1);
}

// ======================= DamageModule =======================

// add_damage: CSV=(acc,f32), build=(acc,u64) [vtable dispatch]
void DamageModule__add_damage_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind29DamageModule__add_damage_implEPNS_26BattleObjectModuleAccessorEf");
void DamageModule__add_damage_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->damage_module;
    reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc0/8])(m, p1);
}

// damage: CSV=no params, build=(u64)
void* DamageModule__damage_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind25DamageModule__damage_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__damage_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->damage_module;
    return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xc8/8])(m, p1);
}

// power_max: CSV=no params, build=(u64)
void* DamageModule__power_max_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind28DamageModule__power_max_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__power_max_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->damage_module;
    return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd8/8])(m, p1);
}

// reaction: CSV=no params, build=(u64)
void* DamageModule__reaction_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind27DamageModule__reaction_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__reaction_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->damage_module;
    return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd0/8])(m, p1);
}

// ======================= JostleModule =======================

// ignore_owner_id: CSV=(acc,u64), build=(acc)
void* JostleModule__ignore_owner_id_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind34JostleModule__ignore_owner_id_implEPNS_26BattleObjectModuleAccessorEy");
void* JostleModule__ignore_owner_id_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return JM(a)->ignore_owner_id();
}

// set_push_speed_x_2: CSV=(acc,bool), build=(acc,u64,bool)
void JostleModule__set_push_speed_x_2_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind37JostleModule__set_push_speed_x_2_implEPNS_26BattleObjectModuleAccessorEb");
void JostleModule__set_push_speed_x_2_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    JM(a)->set_push_speed_x_2(p1, p2);
}

// set_push_speed_x_overlap_rate: CSV=(acc,u64), build=(acc)
void JostleModule__set_push_speed_x_overlap_rate_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind48JostleModule__set_push_speed_x_overlap_rate_implEPNS_26BattleObjectModuleAccessorEy");
void JostleModule__set_push_speed_x_overlap_rate_fix(BattleObjectModuleAccessor* a, u64 p1) {
    JM(a)->set_push_speed_x_overlap_rate();
}

// set_push_speed_x_overlap_rate_status: CSV=(acc,u64), build=(acc)
void JostleModule__set_push_speed_x_overlap_rate_status_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind55JostleModule__set_push_speed_x_overlap_rate_status_implEPNS_26BattleObjectModuleAccessorEy");
void JostleModule__set_push_speed_x_overlap_rate_status_fix(BattleObjectModuleAccessor* a, u64 p1) {
    JM(a)->set_push_speed_x_overlap_rate_status();
}

// set_weight: CSV=(acc,u64), build=(acc)
void JostleModule__set_weight_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind29JostleModule__set_weight_implEPNS_26BattleObjectModuleAccessorEy");
void JostleModule__set_weight_fix(BattleObjectModuleAccessor* a, u64 p1) {
    JM(a)->set_weight();
}

// ======================= ModelModule =======================

// joint_global_offset_from_top: CSV=(acc,u64), build=(acc,u64,u64)
void* ModelModule__joint_global_offset_from_top_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind46ModelModule__joint_global_offset_from_top_implEPNS_26BattleObjectModuleAccessorEy");
void* ModelModule__joint_global_offset_from_top_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return MM(a)->joint_global_offset_from_top(p1, p2);
}

// joint_rotate: CSV=(acc,u64), build=(acc,u64,u64)
void* ModelModule__joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind30ModelModule__joint_rotate_implEPNS_26BattleObjectModuleAccessorEy");
void* ModelModule__joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return MM(a)->joint_rotate(p1, p2);
}

// set_alpha: CSV=(acc,u64), build=(acc)
void ModelModule__set_alpha_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind27ModelModule__set_alpha_implEPNS_26BattleObjectModuleAccessorEy");
void ModelModule__set_alpha_fix(BattleObjectModuleAccessor* a, u64 p1) {
    MM(a)->set_alpha();
}

// set_scale: CSV=(acc,u64), build=(acc)
void ModelModule__set_scale_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind27ModelModule__set_scale_implEPNS_26BattleObjectModuleAccessorEy");
void ModelModule__set_scale_fix(BattleObjectModuleAccessor* a, u64 p1) {
    MM(a)->set_scale();
}

// set_scale_z: CSV=(acc,u64), build=(acc)
void ModelModule__set_scale_z_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind29ModelModule__set_scale_z_implEPNS_26BattleObjectModuleAccessorEy");
void ModelModule__set_scale_z_fix(BattleObjectModuleAccessor* a, u64 p1) {
    MM(a)->set_scale_z();
}

// set_temporary_scale_z: CSV=(acc,u64), build=(acc)
void ModelModule__set_temporary_scale_z_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind39ModelModule__set_temporary_scale_z_implEPNS_26BattleObjectModuleAccessorEy");
void ModelModule__set_temporary_scale_z_fix(BattleObjectModuleAccessor* a, u64 p1) {
    MM(a)->set_temporary_scale_z();
}

// ======================= MotionAnimcmdModule =======================

// call_script_single: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* MotionAnimcmdModule__call_script_single_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind44MotionAnimcmdModule__call_script_single_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionAnimcmdModule__call_script_single_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    auto* m = a->motion_animcmd_module;
    return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x78/8])(m, p1, p2, p3);
}

// change_script_motion_line_single: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* MotionAnimcmdModule__change_script_motion_line_single_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind58MotionAnimcmdModule__change_script_motion_line_single_implEPNS_26BattleObjectModuleAccessorEy");
void* MotionAnimcmdModule__change_script_motion_line_single_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    auto* m = a->motion_animcmd_module;
    return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x80/8])(m, p1, p2, p3);
}

// change_script_motion_partial_lines: CSV=(acc,u64,u64,bool,bool), ABI: bools in w2,w3
void* MotionAnimcmdModule__change_script_motion_partial_lines_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3)
    asm("_ZN3app8lua_bind60MotionAnimcmdModule__change_script_motion_partial_lines_implEPNS_26BattleObjectModuleAccessorEyybb");
void* MotionAnimcmdModule__change_script_motion_partial_lines_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) {
    auto* m = a->motion_animcmd_module;
    return reinterpret_cast<void*(*)(void*,u64,bool,bool)>(VT(m)[0x70/8])(m, p1, p2, p3);
}

// ======================= PostureModule =======================

static inline PostureModule* PM(BattleObjectModuleAccessor* a) {
    return static_cast<PostureModule*>(a->posture_module);
}

// init_rot: CSV=(acc,void*), build=(acc) no params
void* PostureModule__init_rot_fix(BattleObjectModuleAccessor* a, void* p1)
    asm("_ZN3app8lua_bind28PostureModule__init_rot_implEPNS_26BattleObjectModuleAccessorEPv");
void* PostureModule__init_rot_fix(BattleObjectModuleAccessor* a, void* p1) {
    return PM(a)->init_rot();
}

// init_scale: CSV=(acc,u64), build=(acc)
void* PostureModule__init_scale_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind30PostureModule__init_scale_implEPNS_26BattleObjectModuleAccessorEy");
void* PostureModule__init_scale_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return PM(a)->init_scale();
}

// set_owner_scale: CSV=(acc,u64), build=(acc)
void PostureModule__set_owner_scale_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35PostureModule__set_owner_scale_implEPNS_26BattleObjectModuleAccessorEy");
void PostureModule__set_owner_scale_fix(BattleObjectModuleAccessor* a, u64 p1) {
    PM(a)->set_owner_scale();
}

// set_rot: CSV=(acc,void*), build=(acc,u64,u64)
void PostureModule__set_rot_fix(BattleObjectModuleAccessor* a, void* p1, u64 p2)
    asm("_ZN3app8lua_bind27PostureModule__set_rot_implEPNS_26BattleObjectModuleAccessorEPv");
void PostureModule__set_rot_fix(BattleObjectModuleAccessor* a, void* p1, u64 p2) {
    PM(a)->set_rot(reinterpret_cast<u64>(p1), p2);
}

// set_scale_status: CSV=(acc,u64), build=(acc)
void PostureModule__set_scale_status_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36PostureModule__set_scale_status_implEPNS_26BattleObjectModuleAccessorEy");
void PostureModule__set_scale_status_fix(BattleObjectModuleAccessor* a, u64 p1) {
    PM(a)->set_scale_status();
}

// set_stick_lr: CSV=(acc,u64), build=(acc)
void PostureModule__set_stick_lr_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind32PostureModule__set_stick_lr_implEPNS_26BattleObjectModuleAccessorEy");
void PostureModule__set_stick_lr_fix(BattleObjectModuleAccessor* a, u64 p1) {
    PM(a)->set_stick_lr();
}

// ======================= ShadowModule =======================

// set_offset_y: CSV=(acc,u64), build=(acc)
void ShadowModule__set_offset_y_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31ShadowModule__set_offset_y_implEPNS_26BattleObjectModuleAccessorEy");
void ShadowModule__set_offset_y_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->shadow_module;
    reinterpret_cast<void(*)(void*)>(VT(m)[0x78/8])(m);
}

// set_size: CSV=(acc,u64), build=(acc)
void ShadowModule__set_size_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind27ShadowModule__set_size_implEPNS_26BattleObjectModuleAccessorEy");
void ShadowModule__set_size_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->shadow_module;
    reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m);
}

// ======================= ShakeModule =======================

// req_time_scale: CSV=(acc,u64,u64,bool,u64,bool,bool), build=(acc,u64,u64,bool,u64,bool,bool,u64)
void ShakeModule__req_time_scale_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4, bool p5, bool p6, u64 p7)
    asm("_ZN3app8lua_bind32ShakeModule__req_time_scale_implEPNS_26BattleObjectModuleAccessorEyybybb");
void ShakeModule__req_time_scale_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4, bool p5, bool p6, u64 p7) {
    auto* m = a->shake_module;
    reinterpret_cast<void(*)(void*,u64,u64,bool,u64,bool,bool,u64)>(VT(m)[0x58/8])(m, p1, p2, p3, p4, p5, p6, p7);
}

// ======================= SlowModule =======================

// set: CSV=(acc,u64,bool), build=(acc,u64,u64,u64,bool,u64)
void SlowModule__set_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5)
    asm("_ZN3app8lua_bind20SlowModule__set_implEPNS_26BattleObjectModuleAccessorEyb");
void SlowModule__set_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5) {
    auto* m = a->slow_module;
    reinterpret_cast<void(*)(void*,u64,u64,u64,bool,u64)>(VT(m)[0x60/8])(m, p1, p2, p3, p4, p5);
}

// set_whole: CSV=(acc,u64), build=(acc,u64,u64)
void SlowModule__set_whole_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind26SlowModule__set_whole_implEPNS_26BattleObjectModuleAccessorEy");
void SlowModule__set_whole_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = a->slow_module;
    reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xc0/8])(m, p1, p2);
}

// ======================= VisibilityModule =======================

// is_visible: CSV=(acc,u64), build=(acc) -- vtable dispatch
bool VisibilityModule__is_visible_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind33VisibilityModule__is_visible_implEPNS_26BattleObjectModuleAccessorEy");
bool VisibilityModule__is_visible_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->visibility_module;
    return reinterpret_cast<bool(*)(void*)>(VT(m)[0xd0/8])(m);
}

// set_int64: CSV=(acc,u64), build=(acc,u64,u64)
void VisibilityModule__set_int64_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind32VisibilityModule__set_int64_implEPNS_26BattleObjectModuleAccessorEy");
void VisibilityModule__set_int64_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = a->visibility_module;
    reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x58/8])(m, p1, p2);
}

// ======================= FighterWorkModuleImpl =======================

// calc_param: CSV=(acc,bool,bool,u64), build=(acc,bool,bool)
void* FighterWorkModuleImpl__calc_param_fix(BattleObjectModuleAccessor* a, bool p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind38FighterWorkModuleImpl__calc_param_implEPNS_26BattleObjectModuleAccessorEbby");
void* FighterWorkModuleImpl__calc_param_fix(BattleObjectModuleAccessor* a, bool p1, bool p2, u64 p3) {
    auto* m = reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a) + 0x50));
    return reinterpret_cast<void*(*)(void*,bool,bool)>(VT(m)[0x280/8])(m, p1, p2);
}

// ======================= FighterControlModuleImpl =======================

// set_ref_stick_x_org: CSV=(acc,f32), build=(acc,u32)
// Binary uses u32 type (j mangling) but CSV has f32 (f mangling)
void FighterControlModuleImpl__set_ref_stick_x_org_fix(BattleObjectModuleAccessor* a, u32 val)
    asm("_ZN3app8lua_bind50FighterControlModuleImpl__set_ref_stick_x_org_implEPNS_26BattleObjectModuleAccessorEf");
void FighterControlModuleImpl__set_ref_stick_x_org_fix(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->fighter_control_module);
    module[0xAB6] = val & 1;
}

// ======================= FighterManager =======================
// CSV uses P14FighterManager (unqualified), build uses PNS_14FighterManagerE (namespace-qualified)

} // namespace app::lua_bind

// FighterManager fixes must be outside the app::lua_bind namespace to produce unqualified type mangling
namespace app::lua_bind {

u32 FighterManager__entry_count_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind32FighterManager__entry_count_implEP14FighterManager");
u32 FighterManager__entry_count_fix(app::FighterManager* mgr) {
    return mgr->data->entry_count;
}

void FighterManager__enable_ko_camera_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind37FighterManager__enable_ko_camera_implEP14FighterManager");
void FighterManager__enable_ko_camera_fix(app::FighterManager* mgr) {
    mgr->data->ko_camera_enabled = 1;
}

void FighterManager__disable_ko_camera_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind38FighterManager__disable_ko_camera_implEP14FighterManager");
void FighterManager__disable_ko_camera_fix(app::FighterManager* mgr) {
    mgr->data->ko_camera_enabled = 0;
}

bool FighterManager__is_disable_ko_camera_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind41FighterManager__is_disable_ko_camera_implEP14FighterManager");
bool FighterManager__is_disable_ko_camera_fix(app::FighterManager* mgr) {
    return mgr->data->ko_camera_enabled == 0;
}

bool FighterManager__is_melee_mode_homerun_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind42FighterManager__is_melee_mode_homerun_implEP14FighterManager");
bool FighterManager__is_melee_mode_homerun_fix(app::FighterManager* mgr) {
    return mgr->data->melee_mode == 9;
}

bool FighterManager__is_melee_mode_online_tournament_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind52FighterManager__is_melee_mode_online_tournament_implEP14FighterManager");
bool FighterManager__is_melee_mode_online_tournament_fix(app::FighterManager* mgr) {
    return mgr->data->melee_mode == 0x18;
}

u32 FighterManager__get_no_discretion_final_beat_count_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind55FighterManager__get_no_discretion_final_beat_count_implEP14FighterManager");
u32 FighterManager__get_no_discretion_final_beat_count_fix(app::FighterManager* mgr) {
    return mgr->data->no_discretion_final_beat_count;
}

u32 FighterManager__get_final_actor_entry_id_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind45FighterManager__get_final_actor_entry_id_implEP14FighterManager");
u32 FighterManager__get_final_actor_entry_id_fix(app::FighterManager* mgr) {
    return mgr->data->final_actor_entry_id;
}

extern "C" [[noreturn]] void abortWrapper_71039c20a0();

void* FighterManager__get_fighter_entry_fix(app::FighterManager* mgr, u32 index)
    asm("_ZN3app8lua_bind38FighterManager__get_fighter_entry_implEP14FighterManagerj");
void* FighterManager__get_fighter_entry_fix(app::FighterManager* mgr, u32 index) {
    if (index >= 8) { abortWrapper_71039c20a0(); }
    return mgr->data->entries[index];
}

void* FighterManager__get_fighter_information_fix(app::FighterManager* mgr, u32 index)
    asm("_ZN3app8lua_bind44FighterManager__get_fighter_information_implEP14FighterManagerj");
void* FighterManager__get_fighter_information_fix(app::FighterManager* mgr, u32 index) {
    if (index >= 8) { abortWrapper_71039c20a0(); }
    return reinterpret_cast<u8*>(mgr->data->entries[index]) + 0xf0;
}

bool FighterManager__is_end_movie_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind33FighterManager__is_end_movie_implEP14FighterManager");
bool FighterManager__is_end_movie_fix(app::FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) == 8;
}

bool FighterManager__is_prepared_movie_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind38FighterManager__is_prepared_movie_implEP14FighterManager");
bool FighterManager__is_prepared_movie_fix(app::FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) == 4;
}

bool FighterManager__is_process_movie_fix(app::FighterManager* mgr)
    asm("_ZN3app8lua_bind37FighterManager__is_process_movie_implEP14FighterManager");
bool FighterManager__is_process_movie_fix(app::FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) != 0;
}

// ======================= FighterInformation =======================
// CSV uses P18FighterInformation (unqualified), build uses PNS_18FighterInformationE

u8 FighterInformation__fighter_color_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind38FighterInformation__fighter_color_implEP18FighterInformation");
u8 FighterInformation__fighter_color_fix(app::FighterInformation* fi) {
    return fi->data->fighter_color;
}

u8 FighterInformation__fighter_category_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind41FighterInformation__fighter_category_implEP18FighterInformation");
u8 FighterInformation__fighter_category_fix(app::FighterInformation* fi) {
    return fi->data->fighter_category;
}

f32 FighterInformation__gravity_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind32FighterInformation__gravity_implEP18FighterInformation");
f32 FighterInformation__gravity_fix(app::FighterInformation* fi) {
    return fi->data->gravity;
}

f32 FighterInformation__hit_point_max_fix(app::FighterInformation* fi, bool include_temp)
    asm("_ZN3app8lua_bind38FighterInformation__hit_point_max_implEP18FighterInformationb");
f32 FighterInformation__hit_point_max_fix(app::FighterInformation* fi, bool include_temp) {
    auto* d = fi->data;
    f32 base = d->hp_base;
    if (!include_temp) {
        base += d->hp_temp;
    }
    return base;
}

u32 FighterInformation__stock_count_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind36FighterInformation__stock_count_implEP18FighterInformation");
u32 FighterInformation__stock_count_fix(app::FighterInformation* fi) {
    return fi->data->stock_count;
}

s32 FighterInformation__dead_count_fix(app::FighterInformation* fi, s32 index)
    asm("_ZN3app8lua_bind35FighterInformation__dead_count_implEP18FighterInformationi");
s32 FighterInformation__dead_count_fix(app::FighterInformation* fi, s32 index) {
    auto* d = fi->data;
    if (index == -2) {
        s32 a = d->dead_count[0];
        s32 b = d->dead_count[1];
        s32 c = d->dead_count[2];
        s32 temp = b + a;
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(c), "+r"(temp));
#endif
        return c + temp;
    }
    return d->dead_count[index];
}

s32 FighterInformation__suicide_count_fix(app::FighterInformation* fi, s32 index)
    asm("_ZN3app8lua_bind38FighterInformation__suicide_count_implEP18FighterInformationi");
s32 FighterInformation__suicide_count_fix(app::FighterInformation* fi, s32 index) {
    auto* d = fi->data;
    if (index != -2) {
        s32 a = d->suicide_count_a[index];
        s32 b = d->suicide_count_b[index];
        return a + b;
    }
    s32 v0 = d->suicide_count_a[0];
    s32 v1 = d->suicide_count_a[1];
    s32 sum01 = v1 + v0;
    s32 v3 = d->suicide_count_b[0];
    s32 v4 = d->suicide_count_b[1];
    s32 v2 = d->suicide_count_a[2];
    s32 v5 = d->suicide_count_b[2];
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(v3), "+r"(v4), "+r"(v2), "+r"(v5), "+r"(sum01));
#endif
    s32 sum34 = v4 + v3;
    s32 sum012 = v2 + sum01;
    s32 sum345 = v5 + sum34;
    return sum345 + sum012;
}

void FighterInformation__set_add_rebirth_wait_frame_fix(app::FighterInformation* fi, f32 val)
    asm("_ZN3app8lua_bind51FighterInformation__set_add_rebirth_wait_frame_implEP18FighterInformationf");
void FighterInformation__set_add_rebirth_wait_frame_fix(app::FighterInformation* fi, f32 val) {
    fi->data->add_rebirth_wait_frame = val;
}

u32 FighterInformation__summon_boss_id_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind39FighterInformation__summon_boss_id_implEP18FighterInformation");
u32 FighterInformation__summon_boss_id_fix(app::FighterInformation* fi) {
    return fi->data->summon_boss_id;
}

u32 FighterInformation__summon_bomb_ready_frame_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind48FighterInformation__summon_bomb_ready_frame_implEP18FighterInformation");
u32 FighterInformation__summon_bomb_ready_frame_fix(app::FighterInformation* fi) {
    return fi->data->summon_bomb_ready_frame;
}

u32 FighterInformation__summon_pre_bomb_effect_frame_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind53FighterInformation__summon_pre_bomb_effect_frame_implEP18FighterInformation");
u32 FighterInformation__summon_pre_bomb_effect_frame_fix(app::FighterInformation* fi) {
    return fi->data->summon_pre_bomb_effect_frame;
}

f32 FighterInformation__summon_suicide_bomb_attack_mul_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind55FighterInformation__summon_suicide_bomb_attack_mul_implEP18FighterInformation");
f32 FighterInformation__summon_suicide_bomb_attack_mul_fix(app::FighterInformation* fi) {
    return fi->data->summon_suicide_bomb_attack_mul;
}

f32 FighterInformation__summon_suicide_bomb_reaction_mul_fix(app::FighterInformation* fi)
    asm("_ZN3app8lua_bind57FighterInformation__summon_suicide_bomb_reaction_mul_implEP18FighterInformation");
f32 FighterInformation__summon_suicide_bomb_reaction_mul_fix(app::FighterInformation* fi) {
    return fi->data->summon_suicide_bomb_reaction_mul;
}

} // namespace app::lua_bind
