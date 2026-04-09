#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"

using app::MotionModule;

// MotionModule lua_bind thunks — 0x710205cb70..0x710205ce10
// All functions: accessor->motion_module (+0x88) -> vtable dispatch, 4/5-insn tail calls
// +0x88 -> motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]

// ---- Module offset 0x88 (MotionModule) -------------------------------------

// 0x710205cb70 (16 bytes) — MotionModule::change_motion_inherit_frame_keep_rate [slot 30]
// [derived: MotionModule__change_motion_inherit_frame_keep_rate_impl (.dynsym) -> slot 30 (0xf0/8)]
void FUN_710205cb70(app::BattleObjectModuleAccessor* acc, u64 hash) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->change_motion_inherit_frame_keep_rate(hash);
}

// 0x710205cb80 (16 bytes) — MotionModule::change_motion_force_inherit_frame [slot 31]
// [derived: MotionModule__change_motion_force_inherit_frame_impl (.dynsym) -> slot 31 (0xf8/8)]
void FUN_710205cb80(app::BattleObjectModuleAccessor* acc, u64 hash) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->change_motion_force_inherit_frame(hash);
}

// 0x710205cb90 (16 bytes) — MotionModule::change_motion_kind [slot 32]
// [derived: MotionModule__change_motion_kind_impl (.dynsym) -> slot 32 (0x100/8)]
void FUN_710205cb90(app::BattleObjectModuleAccessor* acc, u64 hash) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->change_motion_kind(hash);
}

// 0x710205cbe0 (16 bytes) — MotionModule::get_weight [slot 35]
// [derived: MotionModule__get_weight_impl (.dynsym) -> slot 35 (0x118/8)]
float FUN_710205cbe0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->get_weight();
}

// 0x710205cbf0 (16 bytes) — MotionModule::get_weight_2nd [slot 36]
// [derived: MotionModule__get_weight_2nd_impl (.dynsym) -> slot 36 (0x120/8)]
float FUN_710205cbf0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->get_weight_2nd();
}

// 0x710205cc00 (16 bytes) — MotionModule::is_blend [slot 37]
// [derived: MotionModule__is_blend_impl (.dynsym) -> slot 37 (0x128/8)]
bool FUN_710205cc00(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_blend();
}

// 0x710205cc10 (16 bytes) — MotionModule::is_changing [slot 38]
// [derived: MotionModule__is_changing_impl (.dynsym) -> slot 38 (0x130/8)]
bool FUN_710205cc10(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_changing();
}

// 0x710205cc20 (16 bytes) — MotionModule::motion_kind [slot 39]
// [derived: MotionModule__motion_kind_impl (.dynsym) -> slot 39 (0x138/8)]
u64 FUN_710205cc20(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->motion_kind();
}

// 0x710205cc30 (16 bytes) — MotionModule::rate [slot 40]
// [derived: MotionModule__rate_impl (.dynsym) -> slot 40 (0x140/8)]
float FUN_710205cc30(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->rate();
}

// 0x710205cc40 (16 bytes) — MotionModule::is_changing_2nd [slot 41]
// [derived: MotionModule__is_changing_2nd_impl (.dynsym) -> slot 41 (0x148/8)]
bool FUN_710205cc40(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_changing_2nd();
}

// 0x710205cc50 (16 bytes) — MotionModule::rate_2nd [slot 42]
// [derived: MotionModule__rate_2nd_impl (.dynsym) -> slot 42 (0x150/8)]
float FUN_710205cc50(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->rate_2nd();
}

// 0x710205cc60 (16 bytes) — MotionModule::motion_kind_prev [slot 43]
// [derived: MotionModule__motion_kind_prev_impl (.dynsym) -> slot 43 (0x158/8)]
u64 FUN_710205cc60(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->motion_kind_prev();
}

// 0x710205cc70 (16 bytes) — MotionModule::frame [slot 44]
// [derived: MotionModule__frame_impl (.dynsym) -> slot 44 (0x160/8)]
float FUN_710205cc70(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->frame();
}

// 0x710205cc80 (16 bytes) — MotionModule::prev_frame [slot 45]
// [derived: MotionModule__prev_frame_impl (.dynsym) -> slot 45 (0x168/8)]
float FUN_710205cc80(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->prev_frame();
}

// 0x710205ccd0 (16 bytes) — MotionModule::end_frame [slot 48]
// [derived: MotionModule__end_frame_impl (.dynsym) -> slot 48 (0x180/8)]
float FUN_710205ccd0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->end_frame();
}

// 0x710205cce0 (16 bytes) — MotionModule::end_frame_from_hash [slot 49]
// [derived: MotionModule__end_frame_from_hash_impl (.dynsym) -> slot 49 (0x188/8)]
float FUN_710205cce0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->end_frame_from_hash_f32(p1);
}

// 0x710205ccf0 (20 bytes) — MotionModule::set_frame_2nd [slot 50]
// [derived: MotionModule__set_frame_2nd_impl (.dynsym) -> slot 50 (0x190/8)]
void FUN_710205ccf0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->set_frame_2nd(p1 & 1);
}

// 0x710205cd10 (16 bytes) — MotionModule::frame_2nd [slot 51]
// [derived: MotionModule__frame_2nd_impl (.dynsym) -> slot 51 (0x198/8)]
float FUN_710205cd10(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->frame_2nd();
}

// 0x710205cd80 (16 bytes) — MotionModule::trans_tra_end_frame [slot 56]
// [derived: MotionModule__trans_tra_end_frame_impl (.dynsym) -> slot 56 (0x1c0/8)]
u64 FUN_710205cd80(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return reinterpret_cast<u64>(mod->trans_tra_end_frame(p1, p2));
}

// 0x710205cd90 (16 bytes) — MotionModule::is_end [slot 57]
// [derived: MotionModule__is_end_impl (.dynsym) -> slot 57 (0x1c8/8)]
bool FUN_710205cd90(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_end();
}

// 0x710205cda0 (16 bytes) — MotionModule::is_looped [slot 58]
// [derived: MotionModule__is_looped_impl (.dynsym) -> slot 58 (0x1d0/8)]
bool FUN_710205cda0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_looped();
}

// 0x710205cdb0 (16 bytes) — MotionModule::is_loop_flag [slot 63]
// [derived: MotionModule__is_loop_flag_impl (.dynsym) -> slot 63 (0x1f8/8)]
bool FUN_710205cdb0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_loop_flag();
}

// 0x710205cdc0 (16 bytes) — MotionModule::is_interpreting [slot 67]
// [derived: MotionModule__is_interpreting_impl (.dynsym) -> slot 67 (0x218/8)]
bool FUN_710205cdc0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_interpreting();
}

// 0x710205cdd0 (16 bytes) — MotionModule::is_interpreting_2nd [slot 69]
// [derived: MotionModule__is_interpreting_2nd_impl (.dynsym) -> slot 69 (0x228/8)]
bool FUN_710205cdd0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_interpreting_2nd();
}

// 0x710205cde0 (16 bytes) — MotionModule::is_interpreting_partial [slot 71]
// [derived: MotionModule__is_interpreting_partial_impl (.dynsym) -> slot 71 (0x238/8)]
bool FUN_710205cde0(app::BattleObjectModuleAccessor* acc) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_interpreting_partial();
}

// 0x710205ce10 (16 bytes) — MotionModule::is_anim_resource [slot 78]
// [derived: MotionModule__is_anim_resource_impl (.dynsym) -> slot 78 (0x270/8)]
bool FUN_710205ce10(app::BattleObjectModuleAccessor* acc, u64 p1) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    return mod->is_anim_resource(p1);
}
