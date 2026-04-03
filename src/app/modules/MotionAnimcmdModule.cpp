#include "app/BattleObjectModuleAccessor.h"
#define MA(a) (a->motion_animcmd_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void MotionAnimcmdModule__exec_motion_lines_impl(BattleObjectModuleAccessor* a) { auto* m=MA(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x58/8])(m); }
void MotionAnimcmdModule__change_script_motion_lines_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=MA(a); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VT(m)[0x68/8])(m,p1,p2,p3,p4); }
void* MotionAnimcmdModule__change_script_motion_partial_lines_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=a->motion_animcmd_module; return reinterpret_cast<void*(*)(void*,u64,bool,bool)>(VT(m)[0x70/8])(m,p1,p2,p3); }
void* MotionAnimcmdModule__call_script_single_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=a->motion_animcmd_module; return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x78/8])(m,p1,p2,p3); }
void* MotionAnimcmdModule__change_script_motion_line_single_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=a->motion_animcmd_module; return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x80/8])(m,p1,p2,p3); }
void MotionAnimcmdModule__exec_motion_lines_initialize_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x88/8])(m,p1); }
void MotionAnimcmdModule__flush_current_motion_impl(BattleObjectModuleAccessor* a) { auto* m=MA(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x90/8])(m); }
void MotionAnimcmdModule__flush_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x98/8])(m,p1); }
void MotionAnimcmdModule__set_sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa0/8])(m,p1); }
void MotionAnimcmdModule__set_sleep_game_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
void MotionAnimcmdModule__set_sleep_effect_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb0/8])(m,p1); }
void MotionAnimcmdModule__set_sleep_sound_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); }
bool MotionAnimcmdModule__is_sleep_impl(BattleObjectModuleAccessor* a) { auto* m=MA(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xc0/8])(m); }
void MotionAnimcmdModule__enable_skip_delay_update_impl(BattleObjectModuleAccessor* a) { auto* m=MA(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xc8/8])(m); }
void MotionAnimcmdModule__set_change_partial_immediate_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=MA(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xd0/8])(m,p1); }
} // namespace app::lua_bind
