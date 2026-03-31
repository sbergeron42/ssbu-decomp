#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// 7102087720 — status_kind
s32 StatusModule__status_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x110 / 8])(module);
}

// 7102087730 — status_kind_next
s32 StatusModule__status_kind_next_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x118 / 8])(module);
}

// 7102087740 — set_status_kind_interrupt
void StatusModule__set_status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor, s32 kind) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x120 / 8])(module, kind);
}

// 7102087750 — status_kind_interrupt
s32 StatusModule__status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x128 / 8])(module);
}

// 7102087760 — is_changing
bool StatusModule__is_changing_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x140 / 8])(module);
}

// 7102087770 — prev_status_kind
void* StatusModule__prev_status_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x40)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }

// 71020877a0 — situation_kind
s32 StatusModule__situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x168 / 8])(module);
}

// 71020877b0 — prev_situation_kind
s32 StatusModule__prev_situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x170 / 8])(module);
}

// 71020876c0 [vtable+0x48] — change_status_request
void StatusModule__change_status_request_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,s32,bool)>(vt[0x48/8])(m,kind,p2);
}
// 71020876e0 [vtable+0x50] — change_status_request_from_script
void StatusModule__change_status_request_from_script_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,s32,bool)>(vt[0x50/8])(m,kind,p2);
}
// 7102087700 [vtable+0x58] — delete_status_request_from_script
void StatusModule__delete_status_request_from_script_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*)>(vt[0x58/8])(m);
}
// 7102087780 [vtable+0x158] — change_status_force
void StatusModule__change_status_force_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,s32,bool)>(vt[0x158/8])(m,kind,p2);
}
// 7102087810 [vtable+0x178] — set_situation_kind
void StatusModule__set_situation_kind_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,s32,bool)>(vt[0x178/8])(m,kind,p2);
}
// 7102087830 [vtable+0x188] — set_keep_situation_air
void StatusModule__set_keep_situation_air_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,bool)>(vt[0x188/8])(m,p1);
}
// 7102087850 [vtable+0x1a8] — set_succeeds_bit
void StatusModule__set_succeeds_bit_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->status_module; auto* vt = *reinterpret_cast<void***>(m);
    reinterpret_cast<void(*)(void*,u64)>(vt[0x1a8/8])(m,p1);
}

void* StatusModule__status_kind_que_from_script_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x40)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x60/8])(m); }
} // namespace app::lua_bind
