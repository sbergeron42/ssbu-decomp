#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/PostureModule.h"

namespace app::lua_bind {

static inline PostureModule* PM(BattleObjectModuleAccessor* a) {
    return static_cast<PostureModule*>(a->posture_module);
}

// Position dispatchers
void PostureModule__init_pos_impl(BattleObjectModuleAccessor* a, void* p1, bool p2, bool p3) {
    PM(a)->init_pos(p1, p2, p3);
}

void* PostureModule__pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = PM(a)->pos();
    asm("");
    return ret;
}

void* PostureModule__pos_2d_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->pos_2d();
}

void PostureModule__set_pos_impl(BattleObjectModuleAccessor* a, void* p1) {
    PM(a)->set_pos(p1);
}

void PostureModule__set_pos_2d_impl(BattleObjectModuleAccessor* a, void* pos) {
    PM(a)->set_pos_2d(pos);
}

void PostureModule__add_pos_impl(BattleObjectModuleAccessor* a, void* pos) {
    PM(a)->add_pos(pos);
}

void PostureModule__add_pos_2d_impl(BattleObjectModuleAccessor* a, void* pos) {
    PM(a)->add_pos_2d(pos);
}

void* PostureModule__prev_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = PM(a)->prev_pos();
    asm("");
    return ret;
}

void* PostureModule__prev_pos_2d_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->prev_pos_2d();
}

// Component extractors — call pos()/rot() then index the returned Vector3f
f32 PostureModule__pos_x_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->pos()[0];
}

f32 PostureModule__pos_y_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->pos()[1];
}

f32 PostureModule__pos_z_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->pos()[2];
}

// Direction dispatchers
f32 PostureModule__lr_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->lr();
}

void PostureModule__set_lr_impl(BattleObjectModuleAccessor* a, f32 lr) {
    PM(a)->set_lr(lr);
}

void PostureModule__reverse_lr_impl(BattleObjectModuleAccessor* a) {
    PM(a)->reverse_lr();
}

// Rotation dispatchers
void* PostureModule__init_rot_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->init_rot();
}

void PostureModule__init_rot_2_impl(BattleObjectModuleAccessor* a, void* p1) {
    PM(a)->init_rot_2(p1);
}

void* PostureModule__rot_impl(BattleObjectModuleAccessor* a) {
    void* ret = PM(a)->rot();
    asm("");
    return ret;
}

f32 PostureModule__rot_x_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->rot()[0];
}

f32 PostureModule__rot_y_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->rot()[1];
}

f32 PostureModule__rot_z_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->rot()[2];
}

void PostureModule__set_rot_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    PM(a)->set_rot(p1, p2);
}

void PostureModule__init_rot_y_lr_impl(BattleObjectModuleAccessor* a) {
    PM(a)->init_rot_y_lr();
}

bool PostureModule__is_rot_y_lr_different_inner_lr_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->is_rot_y_lr_different_inner_lr();
}

f32 PostureModule__rot_y_lr_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->rot_y_lr();
}

void PostureModule__update_rot_y_lr_impl(BattleObjectModuleAccessor* a) {
    PM(a)->update_rot_y_lr();
}

void PostureModule__reverse_rot_y_lr_impl(BattleObjectModuleAccessor* a) {
    PM(a)->reverse_rot_y_lr();
}

// Scale dispatchers
f32 PostureModule__base_scale_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->base_scale();
}

void* PostureModule__scale_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->scale();
}

void PostureModule__set_scale_2_impl(BattleObjectModuleAccessor* a, bool p1) {
    PM(a)->set_scale(p1);
}

void PostureModule__set_scale_status_impl(BattleObjectModuleAccessor* a) {
    PM(a)->set_scale_status();
}

void* PostureModule__init_scale_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->init_scale();
}

f32 PostureModule__owner_scale_impl(BattleObjectModuleAccessor* a) {
    return PM(a)->owner_scale();
}

void PostureModule__set_owner_scale_impl(BattleObjectModuleAccessor* a) {
    PM(a)->set_owner_scale();
}

void PostureModule__set_link_scale_impl(BattleObjectModuleAccessor* a, bool p1) {
    PM(a)->set_link_scale(p1);
}

// Misc dispatchers
void PostureModule__set_stick_lr_impl(BattleObjectModuleAccessor* a) {
    PM(a)->set_stick_lr();
}

void PostureModule__set_sync_constraint_joint_impl(BattleObjectModuleAccessor* a, u64 p1) {
    PM(a)->set_sync_constraint_joint(p1);
}

} // namespace app::lua_bind
