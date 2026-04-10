#include "types.h"

// BossManager -- operates on BossManager* directly
// Inner struct at [bm + 0x8]; entity list begin/end at [inner + 0x110/0x118]
// Each list entry is 16 bytes (stride 0x10), first 8 bytes = entity handle pointer
// Default entity singleton loaded via adrp 0x7104f73000 + 0xb70

struct BossManagerData {
    u8   pad_0x00[0x110];
    u8** list_begin;            // +0x110
    u8** list_end;              // +0x118
};

struct BossManager {
    u8   pad_0x00[0x8];
    BossManagerData* inner;     // +0x8
};

extern "C" void FUN_71004e9e30(void*, s32);
extern "C" bool FUN_71004e5780(void*);
extern "C" void FUN_71039c20c0(void*);  // std::__1::__shared_weak_count::__release_weak

// Default entity singleton at 0x7104f73b70 (adrp 0x7104f73000 + #0xb70)
extern "C" u8 DAT_7104f73b70 __attribute__((visibility("hidden")));

namespace app::lua_bind {

#define BVTCALL(obj, off, ...) \
    reinterpret_cast<void(*)(void*, ##__VA_ARGS__)>((*reinterpret_cast<void***>(obj))[(off)/8])(obj, ##__VA_ARGS__)

// 7102145890 -- framed loop: notify boss defeat for entries with hash 0x18e
void BossManager__notify_on_boss_defeat_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    auto* inner = reinterpret_cast<u8*>(bm->inner);
    u8** begin = *reinterpret_cast<u8***>(inner + 0x110);
    u8** end = *reinterpret_cast<u8***>(inner + 0x118);
    for (u8** it = begin; it != end; it = reinterpret_cast<u8**>(reinterpret_cast<u8*>(it) + 0x10)) {
        // Resolve entity: if null or expired, use default singleton
        void* entity;
        void* handle = *reinterpret_cast<void**>(it);
        if (handle && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle))[0x10/8])(handle)) {
            entity = *reinterpret_cast<void**>(it);
        } else {
            entity = &DAT_7104f73b70;
        }
        // Check hash == 0x18e
        u32 hash = reinterpret_cast<u32(*)(void*)>((*reinterpret_cast<void***>(entity))[0x30/8])(entity);
        if (hash != 0x18e) continue;
        // Resolve again for action
        void* entity2;
        void* handle2 = *reinterpret_cast<void**>(it);
        if (handle2 && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle2))[0x10/8])(handle2)) {
            entity2 = *reinterpret_cast<void**>(it);
        } else {
            entity2 = &DAT_7104f73b70;
        }
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(entity2))[0x50/8])(entity2);
    }
}

// 7102145950 -- cmp w1,#0x4d; b.ne ret; ldr x0,[x0,#8]; mov w1,#0x18e; b external
void BossManager__notify_on_boss_keyoff_bgm_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    FUN_71004e9e30(bm->inner, 0x18e);
}

} // namespace app::lua_bind
