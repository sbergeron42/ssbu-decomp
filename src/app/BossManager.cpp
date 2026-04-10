#include "types.h"
#include "app/BossManager.h"

// BossManager — operates on BossManager* directly
// Singleton at lib::Singleton<app::BossManager>::instance_ (0x71052b7ef8)
// Entity list entries are 0x10-stride shared_ptr<BossEntity>:
//   [+0x0] = managed pointer, [+0x8] = control block pointer
// Default entity singleton loaded via adrp 0x7104f73000 + 0xb70

extern "C" void FUN_71004e9e30(void*, s32);
extern "C" bool FUN_71004e5780(void*);
extern "C" void FUN_71039c20c0(void*);  // std::__1::__shared_weak_count::__release_weak

// Default entity singleton at 0x7104f73b70 (adrp 0x7104f73000 + #0xb70)
extern "C" u8 DAT_7104f73b70 __attribute__((visibility("hidden")));

namespace app::lua_bind {

// Helper: resolve entity from shared_ptr slot, falling back to default singleton
static inline void* resolve_entity(void** slot) {
    void* handle = *slot;
    if (handle && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle))[0x10/8])(handle)) {
        return *slot;
    }
    return &DAT_7104f73b70;
}

// 7102145890 (224B) — framed loop: notify boss defeat for entries with hash 0x18e
// [derived: Ghidra — iterates entity list, checks vtable[0x30]==0x18e, calls vtable[0x50]]
void BossManager__notify_on_boss_defeat_impl(app::BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    app::BossManagerInner* inner = bm->inner;
    void** begin = inner->entity_list_begin;
    void** end   = inner->entity_list_end;
    for (void** it = begin; it != end; it = reinterpret_cast<void**>(reinterpret_cast<u8*>(it) + 0x10)) {
        void* entity = resolve_entity(it);
        // Check hash == 0x18e via vtable[0x30/8]
        u32 hash = reinterpret_cast<u32(*)(void*)>((*reinterpret_cast<void***>(entity))[0x30/8])(entity);
        if (hash != 0x18e) continue;
        // Resolve again for action dispatch
        void* entity2 = resolve_entity(it);
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(entity2))[0x50/8])(entity2);
    }
}

// 7102145950 (28B) — cmp w1,#0x4d; b.ne ret; ldr x0,[x0,#8]; mov w1,#0x18e; b external
// [derived: Ghidra — guards on id==0x4d, then tail-calls FUN_71004e9e30(inner, 0x18e)]
void BossManager__notify_on_boss_keyoff_bgm_impl(app::BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    FUN_71004e9e30(bm->inner, 0x18e);
}

// NOTE: BossManager__is_stoppable_se_impl (71021457a0, 212B) and
//       BossManager__notify_on_boss_dead_impl (7102145970, 232B)
// were previously implemented as __attribute__((naked)) which is BANNED.
// Both have complex control flow with NX-specific prologue scheduling that
// does not match in C++ after 3 attempts. SKIPPED per worker rules.

} // namespace app::lua_bind

// ════════════════════════════════════════════════════════════════════
// boss_private dispatcher functions
// ════════════════════════════════════════════════════════════════════

// BossManager singleton
extern "C" app::BossManager* DAT_71052b7ef8_bm2
    __attribute__((visibility("hidden")));
asm(".set DAT_71052b7ef8_bm2, _ZN3lib9SingletonIN3app11BossManagerEE9instance_E");

namespace app::boss_private {

// Helper: resolve entity from shared_ptr slot (same pattern as lua_bind version)
static inline void* resolve_entity(void** slot) {
    void* handle = *slot;
    if (handle && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle))[0x10/8])(handle)) {
        return *slot;
    }
    return &DAT_7104f73b70;
}

// 0x71015c8510 (116B) — send_event_on_boss_defeat
// [derived: Ghidra — checks singleton, iterates entity list, matches entity hash
//  against battle_object_id from lua context, calls vtable[0x50] on match]
void send_event_on_boss_defeat(u8* lua_state) {
    app::BossManager* bm = DAT_71052b7ef8_bm2;
    if (bm == nullptr) return;
    app::BossManagerInner* inner = bm->inner;
    void** begin = inner->entity_list_begin;
    void** end   = inner->entity_list_end;
    if (begin == end) return;
    // Get battle_object_id from lua context chain:
    // *(*(*(*(*(L-8) + 0x1a0) + 400) + 0x220) + 0xc)
    u8* ctx = *reinterpret_cast<u8**>(lua_state - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    u8* p1  = *reinterpret_cast<u8**>(acc + 400);
    u8* p2  = *reinterpret_cast<u8**>(p1 + 0x220);
    s32 target_id = *reinterpret_cast<s32*>(p2 + 0xc);
    for (void** it = begin; it != end; it = reinterpret_cast<void**>(reinterpret_cast<u8*>(it) + 0x10)) {
        void* entity = resolve_entity(it);
        s32 hash = reinterpret_cast<s32(*)(void*)>((*reinterpret_cast<void***>(entity))[0x30/8])(entity);
        if (hash != target_id) continue;
        void* entity2 = resolve_entity(it);
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(entity2))[0x50/8])(entity2);
    }
}

// 0x71015c8450 (76B) — send_event_on_start_boss_entry
// [derived: Ghidra — iterates ItemManager active list, finds item by battle_object_id,
//  calls FUN_71015b52c0. Does NOT use BossManager struct — pure ItemManager iteration.]
// Decomped in ItemHelpers.cpp or fun_batch_d5_047.cpp (different TU).

} // namespace app::boss_private
