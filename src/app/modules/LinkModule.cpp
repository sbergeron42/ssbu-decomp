#include "app/BattleObjectModuleAccessor.h"
#define LM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xD0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void* LinkModule__get_node_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xD0/8])(m,p1); }
void* LinkModule__chk_link_stop_impl(BattleObjectModuleAccessor* a) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xE8/8])(m); }
void* LinkModule__chk_link_visibility_impl(BattleObjectModuleAccessor* a) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x118/8])(m); }
void* LinkModule__get_link_scale_impl(BattleObjectModuleAccessor* a) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x128/8])(m); }
void* LinkModule__get_link_speed_impl(BattleObjectModuleAccessor* a) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x140/8])(m); }
u32 LinkModule__get_model_constraint_flag_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x368/8])(m,p1); }
void* LinkModule__get_model_constraint_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x380/8])(m,p1); }
void* LinkModule__get_model_constraint_target_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x388/8])(m,p1); }
u32 LinkModule__get_model_constraint_no_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x3A8/8])(m,p1); }
void LinkModule__adjust_model_constraint_posture_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3B0/8])(m,p1); }
void* LinkModule__get_model_constraint_joint_global_position_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x3E8/8])(m,p1); }
void* LinkModule__get_model_constraint_joint_global_position_recursive_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x3F0/8])(m,p1); }
void* LinkModule__get_model_constraint_target_joint_rotation_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x3F8/8])(m,p1); }
void* LinkModule__get_node_rotation_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x400/8])(m,p1); }
void* LinkModule__get_constraint_model_scale_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x408/8])(m,p1); }
void* LinkModule__get_constraint_translate_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x410/8])(m,p1); }
bool LinkModule__chk_attribute_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x430/8])(m,p1); }
bool LinkModule__chk_linked_attribute_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x438/8])(m,p1); }
void* LinkModule__get_node_catprue_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=LM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x4B8/8])(m,p1); }
} // namespace app::lua_bind
