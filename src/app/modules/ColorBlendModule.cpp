#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ColorBlendModule.h"
#define CB(a) static_cast<ColorBlendModule*>((a)->color_blend_module)

namespace app::lua_bind {

void ColorBlendModule__off_flash_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->off_flash(p1); }
void ColorBlendModule__set_enable_flash_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->set_enable_flash(p1); }
void ColorBlendModule__set_burn_color_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { CB(a)->set_burn_color(p1, p2); }
void ColorBlendModule__set_burn_color_frame_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { CB(a)->set_burn_color_frame(p1, p2); }
void ColorBlendModule__off_burn_color_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->off_burn_color(p1); }
void ColorBlendModule__set_burn_color_priority_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { CB(a)->set_burn_color_priority(p1, p2); }
void ColorBlendModule__set_priority_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { CB(a)->set_priority(p1, p2); }
void ColorBlendModule__set_shadow_bloom_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->set_shadow_bloom(p1); }
void ColorBlendModule__set_last_attack_direction_impl(BattleObjectModuleAccessor* a, u64 p1) { CB(a)->set_last_attack_direction(p1); }
void ColorBlendModule__set_main_color_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { CB(a)->set_main_color(p1, p2, p3, p4); }
void ColorBlendModule__cancel_main_color_impl(BattleObjectModuleAccessor* a, u64 p1) { CB(a)->cancel_main_color(p1); }
void ColorBlendModule__set_status_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->set_status(p1); }
s32 ColorBlendModule__get_status_impl(BattleObjectModuleAccessor* a) { return CB(a)->get_status(); }
void ColorBlendModule__set_disable_camera_depth_influence_impl(BattleObjectModuleAccessor* a, bool p1) { CB(a)->set_disable_camera_depth_influence(p1); }

} // namespace app::lua_bind
