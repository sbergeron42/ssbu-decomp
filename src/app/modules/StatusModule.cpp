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

// 71020877c0 — x19=status_module, x20=first call result; reloads vtable each call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool StatusModule__is_situation_changed_impl(BattleObjectModuleAccessor* a) {
    asm(
        "stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x19, [x0, #0x40]\n"
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x168]\n"
        "mov x0, x19\n"
        "blr x8\n"
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x170]\n"
        "mov w20, w0\n"
        "mov x0, x19\n"
        "blr x8\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "cmp w20, w0\n"
        "cset w0, ne\n"
        "ldp x20, x19, [sp], #0x20\n"
        "ret\n"
    );
}
#endif

// 7102087860 — TCO dispatch: x10=vtable, passes p7/p8 on stack as-is
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void StatusModule__init_settings_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5, u64 p6, u32 p7, u32 p8) {
    asm(
        "ldr x0, [x0, #0x40]\n"
        "ldr x10, [x0]\n"
        "ldr w8, [sp]\n"
        "ldr w9, [sp, #0x8]\n"
        "and w5, w5, #0x1\n"
        "ldr x10, [x10, #0x1c8]\n"
        "str w9, [sp, #0x8]\n"
        "str w8, [sp]\n"
        "br x10\n"
    );
}
#endif

} // namespace app::lua_bind
