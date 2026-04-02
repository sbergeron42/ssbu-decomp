#include "types.h"

// FighterPitBFinalModule -- operates on FighterPitBFinalModule* directly
// Contains 5 arrays of hit data, each array entry is 0x18 bytes (pointer pair + data)
// Each hit record is 0xc bytes: {object_id(u32), group(u32), no(u32)}

struct FighterPitBFinalModule;

namespace app::lua_bind {

// 7102182260 -- copies 5 pointer fields: [n*0x18] -> [n*0x18+8] for n=0..4
void FighterPitBFinalModule__init_impl(FighterPitBFinalModule* m) {
    auto* p = reinterpret_cast<u8*>(m);
    *reinterpret_cast<u64*>(p + 0x08) = *reinterpret_cast<u64*>(p + 0x00);
    *reinterpret_cast<u64*>(p + 0x20) = *reinterpret_cast<u64*>(p + 0x18);
    *reinterpret_cast<u64*>(p + 0x38) = *reinterpret_cast<u64*>(p + 0x30);
    *reinterpret_cast<u64*>(p + 0x50) = *reinterpret_cast<u64*>(p + 0x48);
    *reinterpret_cast<u64*>(p + 0x68) = *reinterpret_cast<u64*>(p + 0x60);
}

// 7102182290 -- get_hit_num: (end - begin) / 12 via multiply trick
s32 FighterPitBFinalModule__get_hit_num_impl(FighterPitBFinalModule* m, u8 idx) {
    auto* p = reinterpret_cast<u8*>(m);
    u64 begin = *reinterpret_cast<u64*>(p + static_cast<u64>(idx) * 0x18);
    u64 end   = *reinterpret_cast<u64*>(p + static_cast<u64>(idx) * 0x18 + 8);
    return static_cast<s32>((end - begin) >> 2) * static_cast<s32>(0xAAAAAAABu);
}

// 71021822c0 -- get_hit_object_id
u32 FighterPitBFinalModule__get_hit_object_id_impl(FighterPitBFinalModule* m, u8 idx, s32 entry) {
    auto* p = reinterpret_cast<u8*>(m);
    auto* arr = *reinterpret_cast<u8**>(p + static_cast<u64>(idx) * 0x18);
    return *reinterpret_cast<u32*>(arr + static_cast<s64>(entry) * 0xc);
}

// 71021822e0 -- get_hit_group
u32 FighterPitBFinalModule__get_hit_group_impl(FighterPitBFinalModule* m, u8 idx, s32 entry) {
    auto* p = reinterpret_cast<u8*>(m);
    auto* arr = *reinterpret_cast<u8**>(p + static_cast<u64>(idx) * 0x18);
    return *reinterpret_cast<u32*>(arr + static_cast<s64>(entry) * 0xc + 4);
}

// 7102182300 -- get_hit_no
u32 FighterPitBFinalModule__get_hit_no_impl(FighterPitBFinalModule* m, u8 idx, s32 entry) {
    auto* p = reinterpret_cast<u8*>(m);
    auto* arr = *reinterpret_cast<u8**>(p + static_cast<u64>(idx) * 0x18);
    return *reinterpret_cast<u32*>(arr + static_cast<s64>(entry) * 0xc + 8);
}

} // namespace app::lua_bind
