#include "types.h"

// BossManager — operates on BossManager* directly
// Inner struct at [bm + 0x8]; entity list begin/end at [inner + 0x110/0x118]
// Each list entry is 16 bytes (stride 0x10), first 8 bytes = entity handle pointer
// Default entity singleton loaded via adrp 0x7104f73000 + 0xb70

struct BossManager;

extern "C" void FUN_71004e9e30(void*, s32);
extern "C" bool FUN_71004e5780(void*);

// Global default entity reference (adrp pattern, won't byte-match but needed for logic)
extern u8 g_BossDefaultEntity[];

namespace app::lua_bind {

#define BVTCALL(obj, off, ...) \
    reinterpret_cast<void(*)(void*, ##__VA_ARGS__)>((*reinterpret_cast<void***>(obj))[(off)/8])(obj, ##__VA_ARGS__)

// 7102145890 — framed loop: notify boss defeat for entries with hash 0x18e
// Prologue saves x19,x20,x21 (+ x29,x30); id check; iterate boss list
void BossManager__notify_on_boss_defeat_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(bm) + 0x8);
    auto** begin = *reinterpret_cast<void***>(inner + 0x110);
    auto** end   = *reinterpret_cast<void***>(inner + 0x118);
    if (begin == end) return;

    void* default_obj = reinterpret_cast<void*>(g_BossDefaultEntity);

    for (auto** item = begin; item != end;
         item = reinterpret_cast<void**>(reinterpret_cast<u8*>(item) + 0x10)) {
        // Resolve effective object: if *item is null or vtable[2] returns true,
        // use default singleton; otherwise use *item
        void* raw = *item;
        void* obj;
        if (!raw) {
            obj = default_obj;
        } else {
            bool use_default = reinterpret_cast<bool(*)(void*)>(
                (*reinterpret_cast<void***>(raw))[0x10/8])(raw);
            obj = use_default ? default_obj : *item;
        }

        // Get hash from vtable[6]
        s32 hash = reinterpret_cast<s32(*)(void*)>((*reinterpret_cast<void***>(obj))[0x30/8])(obj);
        if (hash != 0x18e) continue;

        // Resolve effective object again for the action call
        void* raw2 = *item;
        void* obj2;
        if (!raw2) {
            obj2 = default_obj;
        } else {
            bool use_default2 = reinterpret_cast<bool(*)(void*)>(
                (*reinterpret_cast<void***>(raw2))[0x10/8])(raw2);
            obj2 = use_default2 ? default_obj : *item;
        }

        // Notify defeat via vtable[10]
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj2))[0x50/8])(obj2);
    }
}

// 7102145950 — cmp w1,#0x4d; b.ne ret; ldr x0,[x0,#8]; mov w1,#0x18e; b external
void BossManager__notify_on_boss_keyoff_bgm_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    FUN_71004e9e30(*reinterpret_cast<void**>(reinterpret_cast<u8*>(bm) + 0x8), 0x18e);
}

// 71021457a0 — framed loop: check if any boss SE is stoppable
// First loop: if any item is not stoppable OR has hash 0x175, fail.
// Second loop: return true if FUN_71004e5780 says so for any item.
bool BossManager__is_stoppable_se_impl(BossManager* bm, s32 id) {
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(bm) + 0x8);
    if (*reinterpret_cast<s32*>(inner + 0x100) != 4) return false;

    void** begin1 = *reinterpret_cast<void***>(inner + 0x110);
    void** end1   = *reinterpret_cast<void***>(inner + 0x118);
    if (begin1 == end1) return false;

    void* default_obj = reinterpret_cast<void*>(g_BossDefaultEntity);

    for (void** item = begin1; item != end1;
         item = reinterpret_cast<void**>(reinterpret_cast<u8*>(item) + 0x10)) {
        void* raw = *item;
        void* obj;
        if (!raw) {
            obj = default_obj;
        } else {
            bool use_def = reinterpret_cast<bool(*)(void*)>(
                (*reinterpret_cast<void***>(raw))[0x10/8])(raw);
            obj = use_def ? default_obj : *item;
        }

        bool stoppable = reinterpret_cast<bool(*)(void*)>(
            (*reinterpret_cast<void***>(obj))[0x58/8])(obj);
        if (!stoppable) return false;

        void* raw2 = *item;
        void* obj2;
        if (!raw2) {
            obj2 = default_obj;
        } else {
            bool use_def2 = reinterpret_cast<bool(*)(void*)>(
                (*reinterpret_cast<void***>(raw2))[0x10/8])(raw2);
            obj2 = use_def2 ? default_obj : *item;
        }

        s32 hash = reinterpret_cast<s32(*)(void*)>(
            (*reinterpret_cast<void***>(obj2))[0x30/8])(obj2);
        if (hash == 0x175) return false;
    }

    // Second loop: check via external function
    void** begin2 = *reinterpret_cast<void***>(inner + 0x110);
    void** end2   = *reinterpret_cast<void***>(inner + 0x118);
    if (begin2 == end2) return false;

    for (void** item = begin2; item != end2;
         item = reinterpret_cast<void**>(reinterpret_cast<u8*>(item) + 0x10)) {
        if (FUN_71004e5780(item)) return true;
    }
    return false;
}

} // namespace app::lua_bind
