// fun_typed_d_003.cpp — CameraModule v0xNN alias dispatchers
// The binary has two symbols for certain CameraModule functions: one with a
// human-readable name (already compiled in CameraModule.cpp) and one with a
// vtable-offset name (v0xNN). These produce the v0xNN symbol variants.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/CameraModule.h"

using app::BattleObjectModuleAccessor;
using app::CameraModule;
#define CM(a) static_cast<CameraModule*>((a)->camera_module)

namespace app::lua_bind {

// v0x90 = set_whole
void CameraModule__v0x90(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind19CameraModule__v0x90EPNS_26BattleObjectModuleAccessorEb");
void CameraModule__v0x90(BattleObjectModuleAccessor* a, bool p1) { CM(a)->set_whole(p1); }

// v0xb8 = reset_camera_range
void CameraModule__v0xb8(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind19CameraModule__v0xb8EPNS_26BattleObjectModuleAccessorEy");
void CameraModule__v0xb8(BattleObjectModuleAccessor* a, u64 p1) { CM(a)->reset_camera_range(p1); }

// v0xe8 = un_regist_camera
void* CameraModule__v0xe8(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind19CameraModule__v0xe8EPNS_26BattleObjectModuleAccessorEy");
void* CameraModule__v0xe8(BattleObjectModuleAccessor* a, u64 p1) { return CM(a)->un_regist_camera(p1); }

// v0xf0 = zoom_in
void* CameraModule__v0xf0(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind19CameraModule__v0xf0EPNS_26BattleObjectModuleAccessorEyyyb");
void* CameraModule__v0xf0(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return CM(a)->zoom_in(p1, p2, p3, p4); }

// v0xf8 = zoom_out
void* CameraModule__v0xf8(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind19CameraModule__v0xf8EPNS_26BattleObjectModuleAccessorEy");
void* CameraModule__v0xf8(BattleObjectModuleAccessor* a, u64 p1) { return CM(a)->zoom_out(p1); }

// v0x160 = set_damage_fly
void CameraModule__v0x160(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x160EPNS_26BattleObjectModuleAccessorEy");
void CameraModule__v0x160(BattleObjectModuleAccessor* a, u64 p1) { CM(a)->set_damage_fly(p1); }

// v0x170 = set_run
void CameraModule__v0x170(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x170EPNS_26BattleObjectModuleAccessorEy");
void CameraModule__v0x170(BattleObjectModuleAccessor* a, u64 p1) { CM(a)->set_run(p1); }

// v0x180 = set_being_carried
void CameraModule__v0x180(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x180EPNS_26BattleObjectModuleAccessorEy");
void CameraModule__v0x180(BattleObjectModuleAccessor* a, u64 p1) { CM(a)->set_being_carried(p1); }

// v0x198 = is_clip_in
bool CameraModule__v0x198(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x198EPNS_26BattleObjectModuleAccessorEb");
bool CameraModule__v0x198(BattleObjectModuleAccessor* a, bool p1) { return CM(a)->is_clip_in(p1); }

// v0x1a0 = is_clip_in_all
bool CameraModule__v0x1a0(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x1a0EPNS_26BattleObjectModuleAccessorEb");
bool CameraModule__v0x1a0(BattleObjectModuleAccessor* a, bool p1) { return CM(a)->is_clip_in_all(p1); }

// v0x1f0 = set_camera_type
void CameraModule__v0x1f0(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x1f0EPNS_26BattleObjectModuleAccessorEy");
void CameraModule__v0x1f0(BattleObjectModuleAccessor* a, u64 p1) { CM(a)->set_camera_type(p1); }

// v0x200 = req_quake
void* CameraModule__v0x200(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x200EPNS_26BattleObjectModuleAccessorEy");
void* CameraModule__v0x200(BattleObjectModuleAccessor* a, u64 p1) { return CM(a)->req_quake(p1); }

// v0x210 = stop_quake
void* CameraModule__v0x210(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20CameraModule__v0x210EPNS_26BattleObjectModuleAccessorEy");
void* CameraModule__v0x210(BattleObjectModuleAccessor* a, u64 p1) { return CM(a)->stop_quake(p1); }

} // namespace app::lua_bind
