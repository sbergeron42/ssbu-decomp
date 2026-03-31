#include "types.h"

// FighterManager — operates on FighterManager* (not BattleObjectModuleAccessor)
// These access FighterManager->internal_data (first ldr x8,[x0]) then fields

struct FighterManager;

extern "C" [[noreturn]] void abort();

namespace app::lua_bind {

// 7102140d60 — entry_count (3 instructions)
u32 FighterManager__entry_count_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return *reinterpret_cast<u32*>(data + 0xa0);
}

// 7102141650 — enable_ko_camera (4 instructions)
void FighterManager__enable_ko_camera_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    data[0xee] = 1;
}

// 7102141660 — disable_ko_camera (3 instructions)
void FighterManager__disable_ko_camera_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    data[0xee] = 0;
}

// Simple field reads (3-5 instructions)
bool FighterManager__is_disable_ko_camera_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xee] == 0; // cmp #0, cset eq
}
bool FighterManager__is_melee_mode_homerun_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xc0] == 9; // cmp #9, cset eq
}
bool FighterManager__is_melee_mode_online_tournament_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xc0] == 0x18; // cmp #0x18, cset eq
}
u8 FighterManager__is_discretion_final_enabled_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xcc];
}
u8 FighterManager__is_ready_go_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xd2];
}
u8 FighterManager__is_result_mode_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return data[0xe9];
}
// 4-instruction setter with bool masking
void FighterManager__set_cursor_whole_impl(FighterManager* mgr, bool val) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    data[0xd6] = val & 1;
}
// 3-instruction getters
u32 FighterManager__get_no_discretion_final_beat_count_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return *reinterpret_cast<u32*>(data + 0xac);
}
u32 FighterManager__get_final_actor_entry_id_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return *reinterpret_cast<u32*>(data + 0xa8);
}

// 7102140f90 — get_fighter_entry (7 instructions, bounds check + indexed)
void* FighterManager__get_fighter_entry_impl(FighterManager* mgr, u32 index) {
    if (index >= 8) abort();
    auto* data = *reinterpret_cast<u8**>(mgr);
    u64 off = static_cast<u64>(index) << 3;
    return *reinterpret_cast<void**>(data + off + 0x20);
}

// 7102140fc0 — get_fighter_information (8 instructions, bounds check + offset)
void* FighterManager__get_fighter_information_impl(FighterManager* mgr, u32 index) {
    if (index >= 8) abort();
    auto* data = *reinterpret_cast<u8**>(mgr);
    u64 off = static_cast<u64>(index) << 3;
    auto* entry = *reinterpret_cast<u8**>(data + off + 0x20);
    return entry + 0xf0;
}

// 7102141910 — is_end_movie (7 instructions, pointer chain + cmp)
bool FighterManager__is_end_movie_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* p1 = *reinterpret_cast<u8**>(data + 0xb80);
    auto* p2 = *reinterpret_cast<u8**>(p1);
    return *reinterpret_cast<u32*>(p2 + 0x20) == 8;
}

// 71021418a0 — is_prepared_movie (7 instructions, pointer chain + cmp 4)
bool FighterManager__is_prepared_movie_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* p1 = *reinterpret_cast<u8**>(data + 0xb80);
    auto* p2 = *reinterpret_cast<u8**>(p1);
    return *reinterpret_cast<u32*>(p2 + 0x20) == 4;
}

// 71021418d0 — is_process_movie (7 instructions, pointer chain + cmp 0, ne)
bool FighterManager__is_process_movie_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* p1 = *reinterpret_cast<u8**>(data + 0xb80);
    auto* p2 = *reinterpret_cast<u8**>(p1);
    return *reinterpret_cast<u32*>(p2 + 0x20) != 0;
}

void FighterManager__reset_fighter_impl(FighterManager* obj) { }

// 71021410d0 — one_on_one_ratio (3 instructions, simple field read)
f32 FighterManager__one_on_one_ratio_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return *reinterpret_cast<f32*>(data + 0xf0);
}

} // namespace app::lua_bind
