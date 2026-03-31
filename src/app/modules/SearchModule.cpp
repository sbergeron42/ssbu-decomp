#include "app/BattleObjectModuleAccessor.h"
#define SR(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xE0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void SearchModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void SearchModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
u32 SearchModule__active_part_num_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x78/8])(m); }
bool SearchModule__is_search_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
u32 SearchModule__get_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
// x1 scratch → body needs 1 param
bool SearchModule__is_inflict_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind29SearchModule__is_inflict_implEPNS_26BattleObjectModuleAccessorEy");
bool SearchModule__is_inflict_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xc8/8])(m); }
// x1 scratch → body needs 1 param
void* SearchModule__remove_log_attack_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36SearchModule__remove_log_attack_implEPNS_26BattleObjectModuleAccessorEy");
void* SearchModule__remove_log_attack_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xe0/8])(m); }
void SearchModule__relocate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xF8/8])(m,p1); }
// x1 scratch → body needs 1 param
void* SearchModule__invalid_attack_mask_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind38SearchModule__invalid_attack_mask_implEPNS_26BattleObjectModuleAccessorEy");
void* SearchModule__invalid_attack_mask_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x100/8])(m); }
// x1 scratch → body needs 1 param
void SearchModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34SearchModule__enable_safe_pos_implEPNS_26BattleObjectModuleAccessorEy");
void SearchModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x128/8])(m); }
// x3 scratch → body needs 3 params
void SearchModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind29SearchModule__set_offset_implEPNS_26BattleObjectModuleAccessorEy");
void SearchModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x68/8])(m,p1,p2); }
// x3 scratch → body needs 3 params
void SearchModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30SearchModule__set_offset2_implEPNS_26BattleObjectModuleAccessorEy");
void SearchModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x70/8])(m,p1,p2); }
void SearchModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
// x5 scratch → body needs 5 params
void SearchModule__set_target_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) asm("_ZN3app8lua_bind38SearchModule__set_target_opponent_implEPNS_26BattleObjectModuleAccessorEy");
void SearchModule__set_target_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64)>(VT(m)[0x98/8])(m,p1,p2,p3,p4); }
// x4 scratch → body needs 4 params
void SearchModule__set_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind26SearchModule__set_pos_implEPNS_26BattleObjectModuleAccessorEy");
void SearchModule__set_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0xa0/8])(m,p1,p2,p3); }
void SearchModule__set_check_interval_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd0/8])(m,p1); }
void SearchModule__set_remove_log_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xd8/8])(m,p1); }
void SearchModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xe8/8])(m,p1); }
void SearchModule__set_invalid_attack_mask_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void SearchModule__set_sync_situation_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x110/8])(m,p1); }
void SearchModule__set_sync_lr_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SR(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x118/8])(m,p1); }
u32 SearchModule__situation_impl(BattleObjectModuleAccessor* a) { auto* m=SR(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x120/8])(m); }
} // namespace app::lua_bind
