// fun_typed_d_012.cpp — GroundModule + ControlModule signature-fix dispatchers
// Binary mangled names have different parameter encodings than our builds.
// These asm()-labeled functions produce the correct CSV symbol names.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/GroundModule.h"
#include "app/modules/ControlModule.h"

using app::BattleObjectModuleAccessor;
using app::GroundModule;
using app::ControlModule;

static inline GroundModule* _GM(BattleObjectModuleAccessor* a) {
    return static_cast<GroundModule*>(a->ground_module);
}
#define CM(a) static_cast<ControlModule*>((a)->fighter_control_module)

namespace app::lua_bind {

// ======================= GroundModule =======================

// attach_ground: CSV=(acc,u64,bool), build=(acc,bool)
void* GroundModule__attach_ground_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind32GroundModule__attach_ground_implEPNS_26BattleObjectModuleAccessorEyb");
void* GroundModule__attach_ground_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    return _GM(a)->attach_ground(p2);
}

// set_attach_ground: CSV=(acc,u64,bool), build=(acc,bool)
void GroundModule__set_attach_ground_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind36GroundModule__set_attach_ground_implEPNS_26BattleObjectModuleAccessorEyb");
void GroundModule__set_attach_ground_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    _GM(a)->set_attach_ground(p2);
}

// set_keep_distant_cliff: CSV=(acc,u64,bool), build=(acc,bool)
void GroundModule__set_keep_distant_cliff_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind41GroundModule__set_keep_distant_cliff_implEPNS_26BattleObjectModuleAccessorEyb");
void GroundModule__set_keep_distant_cliff_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    _GM(a)->set_keep_distant_cliff(p2);
}

// can_entry_cliff_hang_data: CSV=no extra params, build=(u64,u64)
bool GroundModule__can_entry_cliff_hang_data_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind44GroundModule__can_entry_cliff_hang_data_implEPNS_26BattleObjectModuleAccessorE");
bool GroundModule__can_entry_cliff_hang_data_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return _GM(a)->can_entry_cliff_hang_data(p1, p2);
}

// can_entry_cliff_same: CSV=no extra params, build=(u64)
bool GroundModule__can_entry_cliff_same_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind39GroundModule__can_entry_cliff_same_implEPNS_26BattleObjectModuleAccessorE");
bool GroundModule__can_entry_cliff_same_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return _GM(a)->can_entry_cliff_same(p1);
}

// get_down_correct_edge_pos: CSV=no extra params, build=(u64,u64)
void* GroundModule__get_down_correct_edge_pos_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind44GroundModule__get_down_correct_edge_pos_implEPNS_26BattleObjectModuleAccessorE");
void* GroundModule__get_down_correct_edge_pos_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return _GM(a)->get_down_correct_edge_pos(p1, p2);
}

// is_attachable: CSV=no extra params, build=(u64)
bool GroundModule__is_attachable_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind32GroundModule__is_attachable_implEPNS_26BattleObjectModuleAccessorE");
bool GroundModule__is_attachable_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return _GM(a)->is_attachable(p1);
}

// check_down_correct_pos: CSV=(acc,u64), build=(acc) no params
void* GroundModule__check_down_correct_pos_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind41GroundModule__check_down_correct_pos_implEPNS_26BattleObjectModuleAccessorEy");
void* GroundModule__check_down_correct_pos_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return _GM(a)->check_down_correct_pos();
}

// clear_pass_floor: CSV=(acc,u64), build=(acc)
void GroundModule__clear_pass_floor_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35GroundModule__clear_pass_floor_implEPNS_26BattleObjectModuleAccessorEy");
void GroundModule__clear_pass_floor_fix(BattleObjectModuleAccessor* a, u64 p1) {
    _GM(a)->clear_pass_floor();
}

// enable_recovery: CSV=(acc,u64), build=(acc)
void GroundModule__enable_recovery_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind34GroundModule__enable_recovery_implEPNS_26BattleObjectModuleAccessorEy");
void GroundModule__enable_recovery_fix(BattleObjectModuleAccessor* a, u64 p1) {
    _GM(a)->enable_recovery();
}

// entry_cliff: CSV=(acc,u64), build=(acc)
void GroundModule__entry_cliff_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind30GroundModule__entry_cliff_implEPNS_26BattleObjectModuleAccessorEy");
void GroundModule__entry_cliff_fix(BattleObjectModuleAccessor* a, u64 p1) {
    _GM(a)->entry_cliff();
}

// set_coll_stop_slidable_length: CSV=(acc,u64), build=(acc)
void GroundModule__set_coll_stop_slidable_length_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind48GroundModule__set_coll_stop_slidable_length_implEPNS_26BattleObjectModuleAccessorEy");
void GroundModule__set_coll_stop_slidable_length_fix(BattleObjectModuleAccessor* a, u64 p1) {
    _GM(a)->set_coll_stop_slidable_length();
}

// set_init_shape_kind: CSV=(acc,u64), build=(acc)
void GroundModule__set_init_shape_kind_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind38GroundModule__set_init_shape_kind_implEPNS_26BattleObjectModuleAccessorEy");
void GroundModule__set_init_shape_kind_fix(BattleObjectModuleAccessor* a, u64 p1) {
    _GM(a)->set_init_shape_kind();
}

// ======================= ControlModule =======================

// clear_command_one: CSV=(acc,u64), build=(acc,u64,u64)
void ControlModule__clear_command_one_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind37ControlModule__clear_command_one_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__clear_command_one_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->clear_command_one(p1, p2);
}

// delete_reserve_turn_lr: CSV=no params, build=(u64,u64)
void* ControlModule__delete_reserve_turn_lr_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind42ControlModule__delete_reserve_turn_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__delete_reserve_turn_lr_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return CM(a)->delete_reserve_turn_lr(p1, p2);
}

// end_clatter: CSV=no params, build=(u64)
void* ControlModule__end_clatter_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31ControlModule__end_clatter_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__end_clatter_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->end_clatter(p1);
}

// get_clatter_threshold: CSV=no params, build=(u64)
void* ControlModule__get_clatter_threshold_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind41ControlModule__get_clatter_threshold_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__get_clatter_threshold_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_clatter_threshold(p1);
}

// get_clatter_time: CSV=no params, build=(u64)
void* ControlModule__get_clatter_time_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36ControlModule__get_clatter_time_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__get_clatter_time_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_clatter_time(p1);
}

// get_command_life: CSV=no params, build=(u64,u64)
void* ControlModule__get_command_life_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind36ControlModule__get_command_life_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__get_command_life_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return CM(a)->get_command_life(p1, p2);
}

// get_reserve_turn_lr: CSV=no params, build=(u64,u64)
void* ControlModule__get_reserve_turn_lr_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind39ControlModule__get_reserve_turn_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__get_reserve_turn_lr_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return CM(a)->get_reserve_turn_lr(p1, p2);
}

// get_special_command_lr: CSV=no params, build=(u64)
void* ControlModule__get_special_command_lr_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind42ControlModule__get_special_command_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ControlModule__get_special_command_lr_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_special_command_lr(p1);
}

// get_trigger_count: CSV=no params, build=(u64)
u32 ControlModule__get_trigger_count_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind37ControlModule__get_trigger_count_implEPNS_26BattleObjectModuleAccessorE");
u32 ControlModule__get_trigger_count_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_trigger_count(p1);
}

// get_trigger_count_prev: CSV=no params, build=(u64)
u32 ControlModule__get_trigger_count_prev_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind42ControlModule__get_trigger_count_prev_implEPNS_26BattleObjectModuleAccessorE");
u32 ControlModule__get_trigger_count_prev_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_trigger_count_prev(p1);
}

// is_stick_reversed: CSV=no params, build=(u64)
bool ControlModule__is_stick_reversed_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind37ControlModule__is_stick_reversed_implEPNS_26BattleObjectModuleAccessorE");
bool ControlModule__is_stick_reversed_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->is_stick_reversed(p1);
}

// set_back_command: CSV=(acc,u64), build=(acc)
void ControlModule__set_back_command_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36ControlModule__set_back_command_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__set_back_command_fix(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_back_command();
}

// set_clatter_shake_scale: CSV=(acc,u64), build=(acc)
void ControlModule__set_clatter_shake_scale_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind43ControlModule__set_clatter_shake_scale_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__set_clatter_shake_scale_fix(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_clatter_shake_scale();
}

// set_main_stick_x: CSV=(acc,u64), build=(acc)
void ControlModule__set_main_stick_x_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36ControlModule__set_main_stick_x_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__set_main_stick_x_fix(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_main_stick_x();
}

// set_main_stick_y: CSV=(acc,u64), build=(acc)
void ControlModule__set_main_stick_y_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36ControlModule__set_main_stick_y_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__set_main_stick_y_fix(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_main_stick_y();
}

// set_rumble: CSV=(acc,u64,u64,bool), build=(acc,u64,u64,bool,u64)
void ControlModule__set_rumble_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4)
    asm("_ZN3app8lua_bind30ControlModule__set_rumble_implEPNS_26BattleObjectModuleAccessorEyyb");
void ControlModule__set_rumble_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4) {
    CM(a)->set_rumble(p1, p2, p3, p4);
}

// set_rumble_all: CSV=(acc,u64), build=(acc,u64,u64,u64)
void ControlModule__set_rumble_all_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind34ControlModule__set_rumble_all_implEPNS_26BattleObjectModuleAccessorEy");
void ControlModule__set_rumble_all_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    CM(a)->set_rumble_all(p1, p2, p3);
}

// set_rumble_hit_data: CSV=(acc,u64,u64,bool), build=(acc,u64,u64,bool,u64,u64)
void ControlModule__set_rumble_hit_data_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4, u64 p5)
    asm("_ZN3app8lua_bind39ControlModule__set_rumble_hit_data_implEPNS_26BattleObjectModuleAccessorEyyb");
void ControlModule__set_rumble_hit_data_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4, u64 p5) {
    CM(a)->set_rumble_hit_data(p1, p2, p3, p4, p5);
}

} // namespace app::lua_bind
