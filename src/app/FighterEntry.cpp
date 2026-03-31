#include "types.h"

// FighterEntry — operates on FighterEntry* directly

struct FighterEntry;

namespace app::lua_bind {

// 71020cbc40 — fighter_num (2 instructions)
u32 FighterEntry__fighter_num_impl(FighterEntry* entry) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0x14);
}

// 71020cbc50 — get_fighter_id: bounds check + optional active check via vtable
u32 FighterEntry__get_fighter_id_impl(FighterEntry* entry, s32 index, bool check_active) {
    auto* p = reinterpret_cast<u8*>(entry);
    u64 count = *reinterpret_cast<u64*>(p + 0x4150);
    if (static_cast<u64>(index) >= count)
        return 0x50000000;
    auto* fighter = *reinterpret_cast<u8**>(p + static_cast<u64>(index) * 8 + 0x4160);
    if (!fighter)
        return 0x50000000;
    if (check_active) {
        auto* vtable = *reinterpret_cast<void***>(fighter);
        auto fn = reinterpret_cast<u64 (*)(void*)>(vtable[0x518 / 8]);
        if ((fn(fighter) & 1) == 0)
            return 0x50000000;
        fighter = *reinterpret_cast<u8**>(p + static_cast<u64>(index) * 8 + 0x4160);
    }
    return *reinterpret_cast<u32*>(fighter + 8);
}

// 71020cbcb0 — current_fighter_id: use current index at +0x5918
u32 FighterEntry__current_fighter_id_impl(FighterEntry* entry) {
    auto* p = reinterpret_cast<u8*>(entry);
    u64 idx = static_cast<u64>(p[0x5918]);
    u64 count = *reinterpret_cast<u64*>(p + 0x4150);
    if (idx >= count)
        return 0x50000000;
    auto* fighter = *reinterpret_cast<u8**>(p + idx * 8 + 0x4160);
    if (!fighter)
        return 0x50000000;
    auto* vtable = *reinterpret_cast<void***>(fighter);
    auto fn = reinterpret_cast<u64 (*)(void*)>(vtable[0x518 / 8]);
    if ((fn(fighter) & 1) == 0)
        return 0x50000000;
    return *reinterpret_cast<u32*>(*reinterpret_cast<u8**>(p + idx * 8 + 0x4160) + 8);
}

// 71020cbd10 — heal: applies damage to one or all fighters via external function
extern "C" void FUN_71006645d0(f32, u64, bool, s32, u64);
void FighterEntry__heal_impl(FighterEntry* entry, f32 damage, bool param3, s32 target, u64 hash) {
    auto* p = reinterpret_cast<u8*>(entry);
    u64 count = *reinterpret_cast<u64*>(p + 0x4150);
    if (target == 3) {
        for (u64 i = 0; i < count; i++) {
            auto* fighter = *reinterpret_cast<u8**>(p + i * 8 + 0x4160);
            if (fighter) {
                auto* vtable = *reinterpret_cast<void***>(fighter);
                auto fn = reinterpret_cast<u64 (*)(void*)>(vtable[0x518 / 8]);
                if (fn(fighter) & 1) {
                    FUN_71006645d0(-damage, *reinterpret_cast<u64*>(p + i * 8 + 0x4160), param3, 0, hash);
                }
            }
        }
    } else {
        u64 idx = static_cast<u64>(target);
        if (idx < count) {
            auto* fighter = *reinterpret_cast<u8**>(p + idx * 8 + 0x4160);
            if (fighter) {
                auto* vtable = *reinterpret_cast<void***>(fighter);
                auto fn = reinterpret_cast<u64 (*)(void*)>(vtable[0x518 / 8]);
                if (fn(fighter) & 1) {
                    FUN_71006645d0(-damage, *reinterpret_cast<u64*>(p + idx * 8 + 0x4160), param3, 0, hash);
                }
            }
        }
    }
}

// 71020cbe30 — eat_item: tail call to external function
extern "C" void FUN_710065d530(void*, void*, bool);
void FighterEntry__eat_item_impl(FighterEntry* entry, void* touch_event, bool param3) {
    FUN_710065d530(entry, touch_event, param3);
}

} // namespace app::lua_bind
