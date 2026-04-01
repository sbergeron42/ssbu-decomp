#include "types.h"

struct ItemManager;

#define VT(p) (*reinterpret_cast<void***>(p))

namespace app::lua_bind {

// 7102144620 — single instruction: b 0x71015dac50 (tail call, won't match)
void* ItemManager__get_num_of_ownered_item_impl(ItemManager* mgr) {
    (void)mgr;
    return nullptr;
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

// 71021446a0 — search array, call vtable[0x120/8] to check area id
// Saves {x22,x21,x20,x19}: it=x22, item=x21, mgr=x20, area_id=w19
// Reloads end from mgr+0x30 after each vtable call (compiler can't alias-prove safety)
// tbz w0,#0x1f — checks sign bit (result >= 0 means found)
void* ItemManager__find_active_item_from_area_id_impl(ItemManager* mgr, u32 area_id) {
    u8* p = reinterpret_cast<u8*>(mgr);
    u8** it = *reinterpret_cast<u8***>(p + 0x28);
    u8** end = *reinterpret_cast<u8***>(p + 0x30);
    void* result = nullptr;
    if (it == end) return result;
    do {
        void* item = *reinterpret_cast<void**>(it);
        u8* sub = *reinterpret_cast<u8**>(static_cast<u8*>(item) + 0x90);
        if (!sub[0x18]) {
            void* obj = *reinterpret_cast<void**>(static_cast<u8*>(item) + 0x158);
            s32 r = reinterpret_cast<s32(*)(void*, u32)>(VT(obj)[0x120/8])(obj, area_id);
            if (r >= 0) { result = item; break; }
            end = *reinterpret_cast<u8***>(p + 0x30);
        }
        ++it;
    } while (it != end);
    return result;
}

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
