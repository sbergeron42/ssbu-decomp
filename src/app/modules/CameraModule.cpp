#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/CameraModule.h"

namespace app::lua_bind {

static inline CameraModule* CM(BattleObjectModuleAccessor* a) {
    return static_cast<CameraModule*>(a->camera_module);
}

// Reset / Update
void CameraModule__reset_all_impl(BattleObjectModuleAccessor* a) {
    CM(a)->reset_all();
}

void CameraModule__update_force_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    CM(a)->update_force(p1, p2, p3);
}

void CameraModule__set_enable_camera_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) {
    CM(a)->set_enable_camera(p1, p2);
}

void CameraModule__set_whole_impl(BattleObjectModuleAccessor* a, bool p1) {
    CM(a)->set_whole(p1);
}

void CameraModule__set_enable_update_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_enable_update_pos(p1, p2);
}

void CameraModule__set_enable_interpolate_pos_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) {
    CM(a)->set_enable_interpolate_pos(p1, p2);
}

// Camera range
void CameraModule__reset_camera_range_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->reset_camera_range(p1);
}

void CameraModule__set_camera_range_offset_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_camera_range_offset(p1, p2);
}

void CameraModule__add_camera_range_offset_impl(BattleObjectModuleAccessor* a, void* p1, u64 p2) {
    CM(a)->add_camera_range_offset(p1, p2);
}

void CameraModule__add_camera_range_rect_impl(BattleObjectModuleAccessor* a, void* p1, u64 p2) {
    CM(a)->add_camera_range_rect(p1, p2);
}

// Registration / Zoom
void* CameraModule__un_regist_camera_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->un_regist_camera(p1);
}

void* CameraModule__zoom_in_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return CM(a)->zoom_in(p1, p2, p3, p4);
}

void* CameraModule__zoom_out_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->zoom_out(p1);
}

// Status / Priority / Player
void CameraModule__set_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_status(p1, p2);
}

void CameraModule__set_priority_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_priority(p1, p2);
}

s32 CameraModule__get_priority_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_priority(p1);
}

void CameraModule__set_player_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_player_no(p1, p2);
}

s32 CameraModule__get_player_no_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->get_player_no(p1);
}

// Damage fly / Run / Carried
void CameraModule__set_damage_fly_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_damage_fly(p1);
}

void CameraModule__exit_damage_fly_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->exit_damage_fly(p1);
}

void CameraModule__set_run_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_run(p1);
}

void CameraModule__exit_run_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->exit_run(p1);
}

void CameraModule__set_being_carried_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_being_carried(p1);
}

void CameraModule__exit_being_carried_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->exit_being_carried(p1);
}

// Clip detection
bool CameraModule__is_clip_in_impl(BattleObjectModuleAccessor* a, bool p1) {
    return CM(a)->is_clip_in(p1);
}

bool CameraModule__is_clip_in_all_impl(BattleObjectModuleAccessor* a, bool p1) {
    return CM(a)->is_clip_in_all(p1);
}

// Global rect / Target pos
void CameraModule__set_camera_range_global_rect_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    CM(a)->set_camera_range_global_rect(p1, p2);
}

void* CameraModule__get_main_camera_target_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = CM(a)->get_main_camera_target_pos();
    asm("");
    return ret;
}

void* CameraModule__get_main_camera_range_impl(BattleObjectModuleAccessor* a) {
    return CM(a)->get_main_camera_range();
}

void* CameraModule__get_internal_camera_target_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = CM(a)->get_internal_camera_target_pos();
    asm("");
    return ret;
}

// Camera type
s32 CameraModule__get_camera_type_impl(BattleObjectModuleAccessor* a) {
    return CM(a)->get_camera_type();
}

s32 CameraModule__get_camera_type_for_save_impl(BattleObjectModuleAccessor* a) {
    return CM(a)->get_camera_type_for_save();
}

void CameraModule__set_camera_type_impl(BattleObjectModuleAccessor* a, u64 p1) {
    CM(a)->set_camera_type(p1);
}

// Quake effects
void* CameraModule__req_quake_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->req_quake(p1);
}

void* CameraModule__req_quake_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return CM(a)->req_quake_pos(p1, p2);
}

void* CameraModule__stop_quake_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return CM(a)->stop_quake(p1);
}

s32 CameraModule__get_quakeKind_impl(BattleObjectModuleAccessor* a) {
    return CM(a)->get_quakeKind();
}

// Final zoom / FOV
void* CameraModule__start_final_zoom_out_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return CM(a)->start_final_zoom_out(p1, p2, p3);
}

void CameraModule__end_final_zoom_out_impl(BattleObjectModuleAccessor* a) {
    CM(a)->end_final_zoom_out();
}

void* CameraModule__get_camera_view_volume_z0_rect_impl(BattleObjectModuleAccessor* a) {
    return CM(a)->get_camera_view_volume_z0_rect();
}

void CameraModule__reset_main_camera_fov_impl(BattleObjectModuleAccessor* a) {
    CM(a)->reset_main_camera_fov();
}

} // namespace app::lua_bind
