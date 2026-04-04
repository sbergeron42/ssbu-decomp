#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/CaptureModule.h"
#define CP(a) static_cast<CaptureModule*>((a)->capture_module)

namespace app::lua_bind {

void CaptureModule__set_nodes_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind29CaptureModule__set_nodes_implEPNS_26BattleObjectModuleAccessorEy");
void CaptureModule__set_nodes_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { CP(a)->set_nodes(p1, p2); }
bool CaptureModule__is_thrown_finish_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_thrown_finish(); }
void CaptureModule__set_ignore_object_id_impl(BattleObjectModuleAccessor* a, u64 p1) { CP(a)->set_ignore_object_id(p1); }
bool CaptureModule__is_capture_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_capture(); }
u32 CaptureModule__catch_object_id_impl(BattleObjectModuleAccessor* a) { return CP(a)->catch_object_id(); }
void* CaptureModule__capture_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4) asm("_ZN3app8lua_bind27CaptureModule__capture_implEPNS_26BattleObjectModuleAccessorEyyb");
void* CaptureModule__capture_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, u64 p4) { return CP(a)->capture(p1, p2, p3, p4); }
void* CaptureModule__capture_2_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5) asm("_ZN3app8lua_bind29CaptureModule__capture_2_implEPNS_26BattleObjectModuleAccessorEyyyb");
void* CaptureModule__capture_2_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5) { return CP(a)->capture_2(p1, p2, p3, p4, p5); }
bool CaptureModule__is_catch_hit_stop_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_catch_hit_stop(); }
void CaptureModule__node_offset_impl(BattleObjectModuleAccessor* a, bool p1) { CP(a)->node_offset(p1); }
f32 CaptureModule__catch_pos_y_impl(BattleObjectModuleAccessor* a) { return CP(a)->catch_pos_y(); }
void CaptureModule__capture_cut_impl(BattleObjectModuleAccessor* a, bool p1, bool p2, bool p3) { CP(a)->capture_cut(p1, p2, p3); }
void* CaptureModule__check_damage_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind32CaptureModule__check_damage_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__check_damage_impl(BattleObjectModuleAccessor* a, u64 p1) { return CP(a)->check_damage(p1); }
void CaptureModule__check_damage_thrown_impl(BattleObjectModuleAccessor* a) { CP(a)->check_damage_thrown(); }
void* CaptureModule__thrown_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26CaptureModule__thrown_implEPNS_26BattleObjectModuleAccessorEy");
void* CaptureModule__thrown_impl(BattleObjectModuleAccessor* a) { return CP(a)->thrown(); }
bool CaptureModule__is_thrown_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_thrown(); }
void CaptureModule__update_pos_thrown_impl(BattleObjectModuleAccessor* a) { CP(a)->update_pos_thrown(); }
void CaptureModule__update_lr_thrown_impl(BattleObjectModuleAccessor* a) { CP(a)->update_lr_thrown(); }
void CaptureModule__thrown_cut_impl(BattleObjectModuleAccessor* a, bool p1, bool p2) { CP(a)->thrown_cut(p1, p2); }
void CaptureModule__set_send_cut_event_impl(BattleObjectModuleAccessor* a, bool p1) { CP(a)->set_send_cut_event(p1); }
void CaptureModule__set_update_pos_impl(BattleObjectModuleAccessor* a, bool p1) { CP(a)->set_update_pos(p1); }
bool CaptureModule__is_reaction_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_reaction(); }
u32 CaptureModule__motion_offset_impl(BattleObjectModuleAccessor* a) { return CP(a)->motion_offset(); }
u32 CaptureModule__motion_offset_lw_impl(BattleObjectModuleAccessor* a) { return CP(a)->motion_offset_lw(); }
void* CaptureModule__motion_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind26CaptureModule__motion_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return CP(a)->motion(p1, p2); }
void* CaptureModule__motion_lw_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind29CaptureModule__motion_lw_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_lw_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return CP(a)->motion_lw(p1, p2); }
void* CaptureModule__motion_offset_lw_2_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind38CaptureModule__motion_offset_lw_2_implEPNS_26BattleObjectModuleAccessorE");
void* CaptureModule__motion_offset_lw_2_impl(BattleObjectModuleAccessor* a, u64 p1) { return CP(a)->motion_offset_lw_2(p1); }
void CaptureModule__set_ignore_catching_impl(BattleObjectModuleAccessor* a, bool p1) { CP(a)->set_ignore_catching(p1); }
bool CaptureModule__is_ignore_catching_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_ignore_catching(); }
bool CaptureModule__is_motion_hi_lw_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_motion_hi_lw(); }
bool CaptureModule__is_ignore_distance_impl(BattleObjectModuleAccessor* a) { return CP(a)->is_ignore_distance(); }
u32 CaptureModule__capture_node_impl(BattleObjectModuleAccessor* a) { return CP(a)->capture_node(); }
void CaptureModule__set_capture_node_offset_impl(BattleObjectModuleAccessor* a, u64 p1) { CP(a)->set_capture_node_offset(p1); }
u32 CaptureModule__capture_node_value_impl(BattleObjectModuleAccessor* a) { return CP(a)->capture_node_value(); }
void CaptureModule__update_node_pos_impl(BattleObjectModuleAccessor* a) { CP(a)->update_node_pos(); }
f32 CaptureModule__catch_node_pos_y_impl(BattleObjectModuleAccessor* a) { return CP(a)->catch_node_pos_y(); }
f32 CaptureModule__capture_to_catch_node_pos_diff_impl(BattleObjectModuleAccessor* a) { return CP(a)->capture_to_catch_node_pos_diff(); }

} // namespace app::lua_bind
