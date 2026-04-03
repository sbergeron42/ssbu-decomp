#include "app/BattleObjectModuleAccessor.h"
#define VM(a) (a->visibility_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void VisibilityModule__set_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x50/8])(m,p1,p2); }
void VisibilityModule__set_int64_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->visibility_module; reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x58/8])(m,p1,p2); }
void VisibilityModule__reset_status_default_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
void VisibilityModule__reset_status_default_int64_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x78/8])(m,p1); }
void VisibilityModule__reset_status_default_all_impl(BattleObjectModuleAccessor* a) { auto* m=VM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x80/8])(m); }
void VisibilityModule__set_default_all_impl(BattleObjectModuleAccessor* a) { auto* m=VM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x88/8])(m); }
void VisibilityModule__set_mesh_visibility_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x90/8])(m,p1,p2,p3); }
void VisibilityModule__set_mesh_visibility_int64_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x98/8])(m,p1,p2,p3); }
void VisibilityModule__set_material_anim_priority_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xA0/8])(m,p1,p2); }
u64 VisibilityModule__get_whole_impl(BattleObjectModuleAccessor* a) { auto* m=VM(a); return reinterpret_cast<u64(*)(void*)>(VT(m)[0xC8/8])(m); }
bool VisibilityModule__is_visible_impl(BattleObjectModuleAccessor* a) { auto* m=a->visibility_module; return reinterpret_cast<bool(*)(void*)>(VT(m)[0xd0/8])(m); }
void VisibilityModule__set_default_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xD8/8])(m,p1); }
void VisibilityModule__set_default_int64_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xE0/8])(m,p1); }
bool VisibilityModule__is_visible_mesh_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void VisibilityModule__set_model_visible_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x118/8])(m,p1); }
// 710208c000
void VisibilityModule__set_status_default_impl2(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x60/8])(m,p1,p2); }
// 710208c010
void VisibilityModule__set_status_default_int64_impl2(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x68/8])(m,p1,p2); }
void VisibilityModule__set_whole_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xc0/8])(m,p1); }
void VisibilityModule__set_visibility_mode_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=VM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void VisibilityModule__set_status_default_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->visibility_module; reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x60/8])(m,p1,p2); }
void VisibilityModule__set_status_default_int64_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->visibility_module; reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x68/8])(m,p1,p2); }
} // namespace app::lua_bind
