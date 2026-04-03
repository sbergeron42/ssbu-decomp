#include "types.h"

// FighterEntry — operates on FighterEntry* directly

struct FighterEntry {
    u8    pad_0x00[0x14];
    u32   fighter_num;           // +0x14
    u8    pad_0x18[0x4138];
    u64   slot_count;            // +0x4150
    u8    pad_0x4158[0x08];
    void* slots[759];            // +0x4160
    u8    current_index;         // +0x5918
};

namespace app::lua_bind {

// 71020cbc40 — fighter_num (2 instructions)
u32 FighterEntry__fighter_num_impl(FighterEntry* entry) {
    return entry->fighter_num;
}

// 71020cbc50 — get_fighter_id: bounds check + optional active check via vtable
u32 FighterEntry__get_fighter_id_impl(FighterEntry* entry, s32 index, bool check_active) {
    u32 result = 0x50000000u;
    s64 idx = static_cast<s64>(index);
    if (static_cast<u64>(idx) >= entry->slot_count) return result;
    auto* slot = reinterpret_cast<u8*>(entry->slots[idx]);
    if (!slot) return result;
    if (check_active) {
        bool active = reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(slot))[0x518/8])(slot);
        if (!active) return result;
        slot = reinterpret_cast<u8*>(entry->slots[idx]);
    }
    return *reinterpret_cast<u32*>(slot + 0x8);
}

// 71020cbcb0 — current_fighter_id: use current index at +0x5918
u32 FighterEntry__current_fighter_id_impl(FighterEntry* entry) {
    u32 result = 0x50000000u;
    u64 idx = entry->current_index;
    if (idx >= entry->slot_count) return result;
    auto* slot = reinterpret_cast<u8*>(entry->slots[idx]);
    if (!slot) return result;
    bool active = reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(slot))[0x518/8])(slot);
    if (!active) return result;
    auto* slot2 = reinterpret_cast<u8*>(entry->slots[idx]);
    return *reinterpret_cast<u32*>(slot2 + 0x8);
}

// 71020cbd10 — heal: applies damage to one or all fighters via external function
extern "C" void FUN_71006645d0(void*, bool, s32, u64);
void FighterEntry__heal_impl(FighterEntry* entry, f32 damage, bool param3, s32 target, u64 hash) {
    auto* p = reinterpret_cast<u8*>(entry);
    u64 count = *reinterpret_cast<u64*>(p + 0x4150);
    if (target == 3) {
        // Heal all fighters
        if (count == 0) return;
        f32 neg_damage = -damage;
        for (u64 i = 0; i < count; i++) {
            auto* slot = *reinterpret_cast<u8**>(p + i * 8 + 0x4160);
            if (!slot) continue;
            bool active = reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(slot))[0x518/8])(slot);
            if (!active) continue;
            auto* fighter = *reinterpret_cast<void**>(p + i * 8 + 0x4160);
            *reinterpret_cast<f32*>(&fighter) = neg_damage;  // s0 = neg_damage via ABI
            FUN_71006645d0(fighter, param3 & 1, 0, hash);
        }
    } else {
        // Heal specific fighter
        s64 idx = static_cast<s64>(target);
        if (static_cast<u64>(idx) >= count) return;
        auto* slot = *reinterpret_cast<u8**>(p + idx * 8 + 0x4160);
        if (!slot) return;
        bool active = reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(slot))[0x518/8])(slot);
        if (!active) return;
        auto* fighter = *reinterpret_cast<void**>(p + idx * 8 + 0x4160);
        FUN_71006645d0(fighter, param3 & 1, 0, hash);
    }
}

// 71020cbe30 — eat_item: tail call to external function
extern "C" void FUN_710065d530(void*, void*, bool);
void FighterEntry__eat_item_impl(FighterEntry* entry, void* touch_event, bool param3) {
    FUN_710065d530(entry, touch_event, param3);
}

} // namespace app::lua_bind
