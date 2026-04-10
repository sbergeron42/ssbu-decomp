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
