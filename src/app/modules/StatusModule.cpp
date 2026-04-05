#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/StatusModule.h"

namespace app::lua_bind {

static inline StatusModule* get_status(BattleObjectModuleAccessor* a) {
    return static_cast<StatusModule*>(a->status_module);
}

// 7102087720 -- status_kind
s32 StatusModule__status_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->StatusKind(m);
}

// 7102087730 -- status_kind_next
s32 StatusModule__status_kind_next_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->StatusKindNext(m);
}

// 7102087740 -- set_status_kind_interrupt
void StatusModule__set_status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor, s32 kind) {
    auto* m = get_status(accessor);
    m->vtbl->SetStatusKindInterrupt(m, kind);
}

// 7102087750 -- status_kind_interrupt
s32 StatusModule__status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->StatusKindInterrupt(m);
}

// 7102087760 -- is_changing
bool StatusModule__is_changing_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->IsChanging(m);
}

// 7102087770 -- prev_status_kind
void* StatusModule__prev_status_kind_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = get_status(a);
    return reinterpret_cast<void*(*)(StatusModule*, u64)>(m->vtbl->PrevStatusKind)(m, p1);
}

// 71020877a0 -- situation_kind
s32 StatusModule__situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->SituationKind(m);
}

// 71020877b0 -- prev_situation_kind
s32 StatusModule__prev_situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = get_status(accessor);
    return m->vtbl->PrevSituationKind(m);
}

// 71020876c0 -- change_status_request
void StatusModule__change_status_request_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = get_status(a);
    m->vtbl->ChangeStatusRequest(m, kind, p2);
}

// 71020876e0 -- change_status_request_from_script
void StatusModule__change_status_request_from_script_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = get_status(a);
    m->vtbl->ChangeStatusRequestFromScript(m, kind, p2);
}

// 7102087700 -- delete_status_request_from_script
void StatusModule__delete_status_request_from_script_impl(BattleObjectModuleAccessor* a) {
    auto* m = get_status(a);
    m->vtbl->DeleteStatusRequestFromScript(m);
}

// 7102087780 -- change_status_force
void StatusModule__change_status_force_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = get_status(a);
    m->vtbl->ChangeStatusForce(m, kind, p2);
}

// 7102087810 -- set_situation_kind
void StatusModule__set_situation_kind_impl(BattleObjectModuleAccessor* a, s32 kind, bool p2) {
    auto* m = get_status(a);
    m->vtbl->SetSituationKind(m, kind, p2);
}

// 7102087830 -- set_keep_situation_air
void StatusModule__set_keep_situation_air_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = get_status(a);
    m->vtbl->SetKeepSituationAir(m, p1);
}

// 7102087850 -- set_succeeds_bit
void StatusModule__set_succeeds_bit_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = get_status(a);
    m->vtbl->SetSucceedsBit(m, p1);
}

// 7102087710 -- status_kind_que_from_script
void* StatusModule__status_kind_que_from_script_impl(BattleObjectModuleAccessor* a) {
    auto* m = get_status(a);
    return m->vtbl->StatusKindQueFromScript(m);
}

// 71020877c0 -- is_situation_changed: compare situation_kind vs prev_situation_kind
bool StatusModule__is_situation_changed_impl(BattleObjectModuleAccessor* a) {
    auto* m = get_status(a);
    s32 cur  = m->vtbl->SituationKind(m);
    s32 prev = m->vtbl->PrevSituationKind(m);
    return cur != prev;
}

// 7102087860 -- init_settings: tail call vtable[57] w/ 10 params
void StatusModule__init_settings_impl(BattleObjectModuleAccessor* a, s32 p1, s32 p2, u32 p3, s32 p4, bool p5, s32 p6, s32 p7, s32 p8, s32 p9) {
    auto* m = get_status(a);
    m->vtbl->InitSettings(m, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

} // namespace app::lua_bind
