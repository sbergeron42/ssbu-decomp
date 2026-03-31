#include "app/BattleObjectModuleAccessor.h"
#define SR(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xE0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void SearchModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void SearchModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
u32 SearchModule__active_part_num_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x78/8])(m); }
bool SearchModule__is_search_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
u32 SearchModule__get_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
bool SearchModule__is_inflict_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xC8/8])(m,p1); }
void SearchModule__remove_log_attack_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xE0/8])(m,p1); }
void SearchModule__relocate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xF8/8])(m,p1); }
void SearchModule__invalid_attack_mask_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void SearchModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
void SearchModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
void SearchModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
void SearchModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
void SearchModule__set_target_opponent_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
void SearchModule__set_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xa0/8])(m,p1); }
void SearchModule__set_check_interval_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd0/8])(m,p1); }
void SearchModule__set_remove_log_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xd8/8])(m,p1); }
void SearchModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xe8/8])(m,p1); }
void SearchModule__set_invalid_attack_mask_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void SearchModule__set_sync_situation_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x110/8])(m,p1); }
void SearchModule__set_sync_lr_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x118/8])(m,p1); }
u32 SearchModule__situation_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x120/8])(m); }
} // namespace app::lua_bind
