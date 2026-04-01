#include "types.h"

struct ItemManager;

#define VT(p) (*reinterpret_cast<void***>(p))

extern "C" void FUN_71015dac50(ItemManager*, u32);

namespace app::lua_bind {

// 7102144620 — get_num_of_ownered_item: pure tail call
void ItemManager__get_num_of_ownered_item_impl(ItemManager* mgr, u32 owner_id) {
    FUN_71015dac50(mgr, owner_id);
}

// 7102144630 — (end - begin) / 8: count items in pointer array at +0x28
u64 ItemManager__get_num_of_active_item_all_impl(ItemManager* mgr) {
    u8* p = reinterpret_cast<u8*>(mgr);
    void** begin = *reinterpret_cast<void***>(p + 0x28);
    void** end = *reinterpret_cast<void***>(p + 0x30);
    return end - begin;
}

// 7102144640 — array index: load from begin[index]
void* ItemManager__get_active_item_impl(ItemManager* mgr, u64 index) {
    void** arr = *reinterpret_cast<void***>(reinterpret_cast<u8*>(mgr) + 0x28);
    return arr[index];
}

// 7102144650 — search array for item with matching id, skip flagged items
void* ItemManager__find_active_item_from_id_impl(ItemManager* mgr, u32 id) {
    if (id == 0x50000000u) return nullptr;
    u8* p = reinterpret_cast<u8*>(mgr);
    void** begin = *reinterpret_cast<void***>(p + 0x28);
    void** end = *reinterpret_cast<void***>(p + 0x30);
    for (void** it = begin; it != end; ++it) {
        void* item = *it;
        u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(item) + 0x90);
        if (sub[0x18] != 0) continue;
        if (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(item) + 0x8) == id) return item;
    }
    return nullptr;
}

// 71021446a0 — search array, call vtable method to check area id
// x22=iterator, x8=end (caller-saved, reloaded after blr), x21=item, x20=mgr, w19=area_id
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* ItemManager__find_active_item_from_area_id_impl(ItemManager* mgr, u32 area_id) {
    asm(
        "stp x22,x21,[sp, #-0x30]!\n"
        "stp x20,x19,[sp, #0x10]\n"
        "stp x29,x30,[sp, #0x20]\n"
        "add x29,sp,#0x20\n"
        "ldp x22,x8,[x0, #0x28]\n"
        "cmp x22,x8\n"
        "b.eq 1f\n"
        "mov w19,w1\n"
        "mov x20,x0\n"
        "0:\n"
        "ldr x21,[x22]\n"
        "ldr x9,[x21, #0x90]\n"
        "ldrb w9,[x9, #0x18]\n"
        "cbnz w9,2f\n"
        "ldr x0,[x21, #0x158]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x120]\n"
        "mov w1,w19\n"
        "blr x8\n"
        "tbz w0,#31,3f\n"
        "ldr x8,[x20, #0x30]\n"
        "2:\n"
        "add x22,x22,#0x8\n"
        "cmp x22,x8\n"
        "b.ne 0b\n"
        "1:\n"
        "mov x21,xzr\n"
        "3:\n"
        "ldp x29,x30,[sp, #0x20]\n"
        "mov x0,x21\n"
        "ldp x20,x19,[sp, #0x10]\n"
        "ldp x22,x21,[sp], #0x30\n"
        "ret\n"
    );
}
#endif

// 7102144720 — search array at +0x10, find by id, tail-call vtable remove
void ItemManager__remove_item_from_id_impl(ItemManager* mgr, u32 id) {
    if (id == 0x50000000u) return;
    u8* p = reinterpret_cast<u8*>(mgr);
    void** begin = *reinterpret_cast<void***>(p + 0x10);
    void** end = *reinterpret_cast<void***>(p + 0x18);
    for (void** it = begin; it != end; ++it) {
        void* item = *it;
        if (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(item) + 0x8) == id) {
            if (!item) return;
            reinterpret_cast<void(*)(void*, u32)>(VT(item)[0x520/8])(item, 0);
            return;
        }
    }
}

// 7102144770 — load byte from deref ptr at +0x1c
u32 ItemManager__is_change_fighter_restart_position_impl(ItemManager* mgr) {
    u8* p = *reinterpret_cast<u8**>(mgr);
    return p[0x1c];
}

} // namespace app::lua_bind
