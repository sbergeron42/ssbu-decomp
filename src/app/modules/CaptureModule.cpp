#include "app/BattleObjectModuleAccessor.h"
#define CP(a) ((a)->capture_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
bool CaptureModule__is_thrown_finish_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x50/8])(m); }
bool CaptureModule__is_capture_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x68/8])(m); }
u32 CaptureModule__catch_object_id_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x70/8])(m); }
void* CaptureModule__capture_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4) asm("_ZN3app8lua_bind27CaptureModule__capture_implEPNS_26BattleObjectModuleAccessorEyyb");
void* CaptureModule__capture_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool,u64)>(VT(m)[0x78/8])(m,p1,p2,p3,p4); }
void* CaptureModule__capture_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4,u64 p5) asm("_ZN3app8lua_bind29CaptureModule__capture_2_implEPNS_26BattleObjectModuleAccessorEyyyb");
void* CaptureModule__capture_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4,u64 p5) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool,u64)>(VT(m)[0x80/8])(m,p1,p2,p3,p4,p5); }
bool CaptureModule__is_catch_hit_stop_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x88/8])(m); }
f32 CaptureModule__catch_pos_y_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x98/8])(m); }
void CaptureModule__capture_cut_impl(BattleObjectModuleAccessor* a,bool p1,bool p2,bool p3) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool,bool,bool)>(VT(m)[0xa0/8])(m,p1,p2,p3); }
void* CaptureModule__check_damage_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32CaptureModule__check_damage_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__check_damage_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
void CaptureModule__check_damage_thrown_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xb0/8])(m); }
bool CaptureModule__is_thrown_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xc0/8])(m); }
void CaptureModule__update_pos_thrown_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xc8/8])(m); }
void CaptureModule__update_lr_thrown_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xd0/8])(m); }
void CaptureModule__thrown_cut_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0xd8/8])(m,p1,p2); }
void CaptureModule__set_send_cut_event_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xe8/8])(m,p1); }
void CaptureModule__set_update_pos_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xf8/8])(m,p1); }
bool CaptureModule__is_reaction_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x100/8])(m); }
u32 CaptureModule__motion_offset_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x108/8])(m); }
u32 CaptureModule__motion_offset_lw_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x110/8])(m); }
void* CaptureModule__motion_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind26CaptureModule__motion_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x118/8])(m,p1,p2); }
void* CaptureModule__motion_lw_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind29CaptureModule__motion_lw_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_lw_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x120/8])(m,p1,p2); }
void* CaptureModule__motion_offset_lw_2_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind38CaptureModule__motion_offset_lw_2_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_offset_lw_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
void CaptureModule__set_ignore_catching_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x130/8])(m,p1); }
bool CaptureModule__is_ignore_catching_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x138/8])(m); }
bool CaptureModule__is_motion_hi_lw_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x140/8])(m); }
bool CaptureModule__is_ignore_distance_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x148/8])(m); }
u32 CaptureModule__capture_node_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
u32 CaptureModule__capture_node_value_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x160/8])(m); }
f32 CaptureModule__catch_node_pos_y_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x170/8])(m); }
f32 CaptureModule__capture_to_catch_node_pos_diff_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x178/8])(m); }
void CaptureModule__set_nodes_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind29CaptureModule__set_nodes_implEPNS_26BattleObjectModuleAccessorEy");
void CaptureModule__set_nodes_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CP(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x48/8])(m,p1,p2); }
void CaptureModule__set_ignore_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
void CaptureModule__node_offset_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x90/8])(m,p1); }
void* CaptureModule__thrown_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26CaptureModule__thrown_implEPNS_26BattleObjectModuleAccessorEy");
void* CaptureModule__thrown_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xb8/8])(m); }
void CaptureModule__set_capture_node_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x158/8])(m,p1); }
void CaptureModule__update_node_pos_impl(BattleObjectModuleAccessor* a) { auto* m=CP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x168/8])(m); }
} // namespace app::lua_bind
