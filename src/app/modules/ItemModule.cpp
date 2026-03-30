#include "app/BattleObjectModuleAccessor.h"
#define IM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xC8))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 ItemModule__get_have_item_size_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xD0/8])(m); }
u32 ItemModule__get_have_item_kind_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xD8/8])(m); }
u32 ItemModule__get_have_item_hold_kind_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xE8/8])(m); }
u32 ItemModule__get_have_item_id_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x108/8])(m); }
void ItemModule__drop_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
void ItemModule__born_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x188/8])(m,p1); }
void ItemModule__attach_item_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x1F0/8])(m,p1,p2); }
void ItemModule__attach_item_2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x200/8])(m,p1,p2); }
u32 ItemModule__get_attach_item_count_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
void ItemModule__drop_attach_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
void ItemModule__drop_attach_group_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x270/8])(m,p1); }
} // namespace app::lua_bind
