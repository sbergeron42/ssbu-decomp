#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/PostureModule.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-025
// PostureModule 0x710206af80–0x710206b120, ReflectModule 0x710206ed10–0x710206ed80

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- PostureModule (accessor+0x38) — rot_x/y/z component extractors -------

// 0x710206af80 (36 bytes) — PostureModule__rot_x_impl (.dynsym)
// Calls rot() → extract x-component of rotation vector
float FUN_710206af80(u64 a) {
    // [derived: PostureModule__rot_impl (.dynsym) → slot 27 (0xd8/8), returns f32*]
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    f32* rot = posture->rot();
    return rot[0];
}

// 0x710206afb0 (36 bytes) — PostureModule__rot_y_impl (.dynsym)
// Calls rot() → extract y-component of rotation vector
float FUN_710206afb0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    f32* rot = posture->rot();
    return rot[1];
}

// 0x710206afe0 (36 bytes) — PostureModule__rot_z_impl (.dynsym)
// Calls rot() → extract z-component of rotation vector
float FUN_710206afe0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    f32* rot = posture->rot();
    return rot[2];
}

// ---- PostureModule (accessor+0x38) — continued ----------------------------

// 0x710206b010 (16 bytes) — PostureModule__set_rot_impl (.dynsym)
// [derived: set_rot → slot 28 (0xe0/8)]
void FUN_710206b010(u64 a, u64 p1, u64 p2) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_rot(p1, p2);
}

// 0x710206b020 (16 bytes) — PostureModule__init_rot_y_lr_impl (.dynsym)
// [derived: init_rot_y_lr → slot 29 (0xe8/8)]
void FUN_710206b020(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->init_rot_y_lr();
}

// 0x710206b030 (16 bytes) — PostureModule__is_rot_y_lr_different_inner_lr_impl (.dynsym)
// [derived: is_rot_y_lr_different_inner_lr → slot 30 (0xf0/8)]
bool FUN_710206b030(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    return posture->is_rot_y_lr_different_inner_lr();
}

// 0x710206b040 (16 bytes) — PostureModule__rot_y_lr_impl (.dynsym)
// [derived: rot_y_lr → slot 31 (0xf8/8)]
float FUN_710206b040(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    return posture->rot_y_lr();
}

// 0x710206b050 (16 bytes) — PostureModule__update_rot_y_lr_impl (.dynsym)
// [derived: update_rot_y_lr → slot 32 (0x100/8)]
void FUN_710206b050(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->update_rot_y_lr();
}

// 0x710206b060 (16 bytes) — PostureModule__reverse_rot_y_lr_impl (.dynsym)
// [derived: reverse_rot_y_lr → slot 33 (0x108/8)]
void FUN_710206b060(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->reverse_rot_y_lr();
}

// 0x710206b070 (16 bytes) — PostureModule__base_scale_impl (.dynsym)
// [derived: base_scale → slot 34 (0x110/8)]
float FUN_710206b070(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    return posture->base_scale();
}

// 0x710206b080 (16 bytes) — PostureModule__scale_impl (.dynsym)
// [derived: scale → slot 35 (0x118/8)]
// scale() returns void* in vtable; tail call passes return through regardless of type
void* FUN_710206b080(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    return posture->scale();
}

// 0x710206b090 (20 bytes) — PostureModule__set_scale_impl (.dynsym)
// [derived: set_scale → slot 36 (0x120/8)]
void FUN_710206b090(u64 a, u32 p1) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_scale(p1 & 1);
}

// 0x710206b0b0 (16 bytes) — PostureModule__set_scale_status_impl (.dynsym)
// [derived: set_scale_status → slot 38 (0x130/8)]
void FUN_710206b0b0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_scale_status();
}

// 0x710206b0c0 (16 bytes) — PostureModule__init_scale_impl (.dynsym)
// [derived: init_scale → slot 39 (0x138/8)]
void FUN_710206b0c0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->init_scale();
}

// 0x710206b0d0 (16 bytes) — PostureModule__owner_scale_impl (.dynsym)
// [derived: owner_scale → slot 40 (0x140/8)]
float FUN_710206b0d0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    return posture->owner_scale();
}

// 0x710206b0e0 (16 bytes) — PostureModule__set_owner_scale_impl (.dynsym)
// [derived: set_owner_scale → slot 41 (0x148/8)]
void FUN_710206b0e0(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_owner_scale();
}

// 0x710206b0f0 (20 bytes) — PostureModule__set_link_scale_impl (.dynsym)
// [derived: set_link_scale → slot 42 (0x150/8)]
void FUN_710206b0f0(u64 a, u32 p1) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_link_scale(p1 & 1);
}

// 0x710206b110 (16 bytes) — PostureModule__set_stick_lr_impl (.dynsym)
// [derived: set_stick_lr → slot 47 (0x178/8)]
void FUN_710206b110(u64 a) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_stick_lr();
}

// 0x710206b120 (16 bytes) — PostureModule__set_sync_constraint_joint_impl (.dynsym)
// [derived: set_sync_constraint_joint → slot 48 (0x180/8)]
void FUN_710206b120(u64 a, u64 p1) {
    app::PostureModule* posture = static_cast<app::PostureModule*>(
        reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    posture->set_sync_constraint_joint(p1);
}

// ---- ReflectModule (accessor+0xf8) ----------------------------------------

// 0x710206ed10 (16 bytes) — void, 0 int args, vtable[0x50]
// ReflectModule no-arg dispatch via vtable slot 0x50/8 = 10
void FUN_710206ed10(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
}

// 0x710206ed20 (16 bytes) — u64 return, 0 int args, vtable[0x58]
// ReflectModule u64 query via vtable slot 0x58/8 = 11
u64 FUN_710206ed20(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(u64(**)(u64))(*(u64*)mod + 0x58))(mod);
}

// 0x710206ed30 (16 bytes) — void, 1 int arg (hash), vtable[0x60]
// ReflectModule dispatch with hash arg via vtable slot 0x60/8 = 12
void FUN_710206ed30(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x60))(mod, p1);
}

// 0x710206ed40 (16 bytes) — u64 return, 0 int args, vtable[0x68]
// ReflectModule u64 query via vtable slot 0x68/8 = 13
u64 FUN_710206ed40(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(u64(**)(u64))(*(u64*)mod + 0x68))(mod);
}

// 0x710206ed50 (16 bytes) — void, 1 int arg, vtable[0x70]
// ReflectModule dispatch with int arg via vtable slot 0x70/8 = 14
void FUN_710206ed50(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x70))(mod, p1);
}

// 0x710206ed60 (16 bytes) — float return, 0 int args, vtable[0x78]
// ReflectModule float query via vtable slot 0x78/8 = 15
float FUN_710206ed60(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x78))(mod);
}

// 0x710206ed70 (16 bytes) — void, 0 int args (float via SIMD), vtable[0x80]
// ReflectModule no-arg dispatch via vtable slot 0x80/8 = 16
void FUN_710206ed70(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64))(*(u64*)mod + 0x80))(mod);
}

// 0x710206ed80 (16 bytes) — float return, 0 int args, vtable[0x88]
// ReflectModule float query via vtable slot 0x88/8 = 17
float FUN_710206ed80(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x88))(mod);
}
