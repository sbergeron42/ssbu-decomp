// fun_typed_d_009.cpp — GroundModule v0xNN alias dispatchers (30 functions)
// Binary has both named and v0xNN symbols for certain GroundModule functions.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/GroundModule.h"

using app::BattleObjectModuleAccessor;
using app::GroundModule;
#define GM(a) static_cast<GroundModule*>((a)->ground_module)

namespace app::lua_bind {

void GroundModule__v0x88(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind19GroundModule__v0x88EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x88(BattleObjectModuleAccessor* a, bool p1) { GM(a)->update_shape(p1); }

void GroundModule__v0x140(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x140EPNS_26BattleObjectModuleAccessorEy");
void GroundModule__v0x140(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->set_rhombus_offset(p1); }

void GroundModule__v0x190(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x190EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x190(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_passable_check(p1); }

void GroundModule__v0x228(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x228EPNS_26BattleObjectModuleAccessorEy");
void GroundModule__v0x228(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->select_cliff_hangdata(p1); }

void GroundModule__v0x2d0(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x2d0EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x2d0(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_test_coll_stop(p1); }

void GroundModule__v0x2d8(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x2d8EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x2d8(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_test_coll_stop_status(p1); }

void GroundModule__v0x338(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind20GroundModule__v0x338EPNS_26BattleObjectModuleAccessorEyb");
void GroundModule__v0x338(BattleObjectModuleAccessor* a, u64 p1, bool p2) { GM(a)->set_shape_flag(p1, p2); }

void GroundModule__v0x348(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x348EPNS_26BattleObjectModuleAccessorEy");
void GroundModule__v0x348(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->set_shape_safe_pos(p1); }

void GroundModule__v0x368(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x368EPNS_26BattleObjectModuleAccessorEy");
void GroundModule__v0x368(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->set_shape_kind(p1); }

void* GroundModule__v0x410(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x410EPNS_26BattleObjectModuleAccessorEy");
void* GroundModule__v0x410(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->get_touch_normal_x(p1); }

void* GroundModule__v0x418(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x418EPNS_26BattleObjectModuleAccessorEy");
void* GroundModule__v0x418(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->get_touch_normal_y(p1); }

void* GroundModule__v0x430(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x430EPNS_26BattleObjectModuleAccessorEy");
void* GroundModule__v0x430(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->get_touch_normal_x_consider_gravity(p1); }

void* GroundModule__v0x438(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x438EPNS_26BattleObjectModuleAccessorEy");
void* GroundModule__v0x438(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->get_touch_normal_y_consider_gravity(p1); }

// --- Ray check family ---

void GroundModule__v0x618(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3)
    asm("_ZN3app8lua_bind20GroundModule__v0x618EPNS_26BattleObjectModuleAccessorEyyb");
void GroundModule__v0x618(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { GM(a)->ray_check(p1, p2, p3); }

void* GroundModule__v0x620(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x620EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x620(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_hit_pos(p1, p2, p3, p4); }

void* GroundModule__v0x628(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x628EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x628(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_hit_normal(p1, p2, p3, p4); }

void* GroundModule__v0x630(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind20GroundModule__v0x630EPNS_26BattleObjectModuleAccessorEyyyyb");
void* GroundModule__v0x630(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return GM(a)->ray_check_hit_pos_normal(p1, p2, p3, p4, p5); }

void* GroundModule__v0x638(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind20GroundModule__v0x638EPNS_26BattleObjectModuleAccessorEyyyyb");
void* GroundModule__v0x638(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return GM(a)->ray_check_hit_pos_normal_no_culling(p1, p2, p3, p4, p5); }

void* GroundModule__v0x640(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind20GroundModule__v0x640EPNS_26BattleObjectModuleAccessorEyyyyb");
void* GroundModule__v0x640(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return GM(a)->ray_check_hit_pos_target(p1, p2, p3, p4, p5); }

bool GroundModule__v0x648(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3)
    asm("_ZN3app8lua_bind20GroundModule__v0x648EPNS_26BattleObjectModuleAccessorEyyb");
bool GroundModule__v0x648(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return GM(a)->ray_check_get_line(p1, p2, p3); }

bool GroundModule__v0x650(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3)
    asm("_ZN3app8lua_bind20GroundModule__v0x650EPNS_26BattleObjectModuleAccessorEyyb");
bool GroundModule__v0x650(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return GM(a)->ray_check_get_line_no_culling(p1, p2, p3); }

void* GroundModule__v0x658(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x658EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x658(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_get_line_hit_pos(p1, p2, p3, p4); }

void* GroundModule__v0x668(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x668EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x668(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_get_line_hit_pos_no_culling(p1, p2, p3, p4); }

void* GroundModule__v0x670(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x670EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x670(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_get_line_target_any(p1, p2, p3, p4); }

void* GroundModule__v0x678(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4)
    asm("_ZN3app8lua_bind20GroundModule__v0x678EPNS_26BattleObjectModuleAccessorEyyyb");
void* GroundModule__v0x678(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return GM(a)->ray_check_get_line_target_any_no_culling(p1, p2, p3, p4); }

void* GroundModule__v0x6a0(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind20GroundModule__v0x6a0EPNS_26BattleObjectModuleAccessorEyyyyb");
void* GroundModule__v0x6a0(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return GM(a)->ray_check_get_line_hit_pos_target_any(p1, p2, p3, p4, p5); }

void* GroundModule__v0x6a8(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind20GroundModule__v0x6a8EPNS_26BattleObjectModuleAccessorEyyyyb");
void* GroundModule__v0x6a8(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return GM(a)->line_segment_check(p1, p2, p3, p4, p5); }

void GroundModule__v0x6e0(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x6e0EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x6e0(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_update_shape(p1); }

void GroundModule__v0x750(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind20GroundModule__v0x750EPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x750(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_auto_detach(p1); }

void GroundModule__v0x7a8b(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind21GroundModule__v0x7a8bEPNS_26BattleObjectModuleAccessorEb");
void GroundModule__v0x7a8b(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_gr_collision_mode(p1); }

} // namespace app::lua_bind
