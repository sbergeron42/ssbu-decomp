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

// 7102140d70 — total_fighter_num: sum fighter_num across 8 entry slots
u32 FighterManager__total_fighter_num_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    u32 total = 0;
    for (s32 i = 0; i < 8; i++) {
        auto* entry = *reinterpret_cast<u8**>(data + 0x20 + static_cast<u64>(i) * 8);
        if (entry) {
            total += *reinterpret_cast<u32*>(entry + 0x14);
        }
    }
    return total;
}

// 7102140e10 — get_entry_id: walk 8 slots (unrolled), decrement counter, return index
u64 FighterManager__get_entry_id_impl(FighterManager* mgr, s32 n) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    s32 count = n;
#define CHECK_SLOT(I) \
    if (*reinterpret_cast<void**>(data + 0x20 + (I) * 8)) { \
        if (count == 0) return (I); \
        count--; \
    }
    CHECK_SLOT(0) CHECK_SLOT(1) CHECK_SLOT(2) CHECK_SLOT(3)
    CHECK_SLOT(4) CHECK_SLOT(5) CHECK_SLOT(6)
    if (*reinterpret_cast<void**>(data + 0x58) && count == 0) return 7;
    return static_cast<u64>(-1);
#undef CHECK_SLOT
}

// 7102140ee0 — get_entry_no: count non-null entries before index
u32 FighterManager__get_entry_no_impl(FighterManager* mgr, u32 entry_id) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    u32 count = 0;
    for (u32 i = 0; i < entry_id; i++) {
        auto* entry = *reinterpret_cast<void**>(data + 0x20 + static_cast<u64>(i) * 8);
        if (entry) count++;
    }
    return count;
}

// 7102141010 — is_homerun_versus: global data, static init guard (tail call, won't match)
extern "C" bool FUN_7102141010_is_homerun_versus(FighterManager*);
// Skipping due to static init guard pattern — would need __cxa_guard_acquire

// 7102141160 — get_top_rank_player: global data, static init guard (tail call, won't match)
// Skipping due to static init guard pattern

// 7102141210 — get_fighter_pos: complex vtable calls + bounds checks (may not match)
// Skipping due to complexity (54 instructions, multiple vtable calls, SIMD return)

// 71021412f0 — is_available_discretion_final: global pointer chain + function call
// Skipping due to global pointer chain complexity

// 7102141370 — is_final: ldr x0,[x0]; b external
extern "C" void FUN_7100677240(void*);
void FighterManager__is_final_impl(FighterManager* mgr) {
    FUN_7100677240(*reinterpret_cast<void**>(mgr));
}

// 7102141380 — set_final: complex cross-entry lookup (42 instructions)
// Skipping due to complexity (bounds check + cross-entry vtable + conditional global store)

// 7102141440 — get_beat_point_diff_from_top: ldr x0,[x0]; and x1; b external
extern "C" void FUN_7100679ed0(void*, u64);
void FighterManager__get_beat_point_diff_from_top_impl(FighterManager* mgr, u64 id) {
    FUN_7100679ed0(*reinterpret_cast<void**>(mgr), id & 0xFFFFFFFF);
}

// 7102141450 — set_final_fear_face: reads/writes data+0x160, calls external
extern "C" void FUN_7100674d80(void*, s32, s32);
void FighterManager__set_final_fear_face_impl(FighterManager* mgr, s32 entry_id, s32 enable) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    s32 cur = *reinterpret_cast<s32*>(data + 0x160);
    if (cur >= 1) {
        FUN_7100674d80(data, -1, 0);
        *reinterpret_cast<s32*>(data + 0x160) = 0;
    }
    if (enable >= 1) {
        FUN_7100674d80(data, entry_id, 1);
    } else {
        FUN_7100674d80(data, entry_id, 0);
    }
    *reinterpret_cast<s32*>(data + 0x160) = enable;
}

// 71021414d0 — start_finalbg: search array via data+0xB78, call external
extern "C" void FUN_710260a560(void*, void*, void*);
void FighterManager__start_finalbg_impl(FighterManager* mgr, u32 id) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* ctrl = *reinterpret_cast<u8**>(data + 0xb78);
    auto* obj = *reinterpret_cast<u8**>(ctrl);
    auto* begin = *reinterpret_cast<u8**>(obj);
    auto* end = *reinterpret_cast<u8**>(obj + 8);
    while (begin != end) {
        if (*reinterpret_cast<u32*>(begin) == id) break;
        begin += 8;
    }
    // Simplified — complex SIMD constant + global access follows
    // Won't byte-match due to global + SIMD constant load
    ctrl[0x18] = 1;
}

// 7102141560 — exit_finalbg: check active flag, call external, clear flag
extern "C" void FUN_710260b9b0(void*);
extern "C" __attribute__((visibility("hidden"))) u64* DAT_71053299d8;
void FighterManager__exit_finalbg_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* ctrl = *reinterpret_cast<u8**>(data + 0xb78);
    auto* obj = *reinterpret_cast<u8**>(ctrl);
    if (obj[0x18] != 0) {
        FUN_710260b9b0(*reinterpret_cast<void**>(DAT_71053299d8));
        obj[0x18] = 0;
    }
}

// 71021415a0 — show_finalbg: global->deref, tail call
extern "C" void FUN_710260c900(void*);
void FighterManager__show_finalbg_impl(FighterManager*) {
    FUN_710260c900(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415b0 — hide_finalbg: global->deref, tail call
extern "C" void FUN_710260c9e0(void*);
void FighterManager__hide_finalbg_impl(FighterManager*) {
    FUN_710260c9e0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415c0 — pause_finalbg: global->deref, tail call
extern "C" void FUN_710260cac0(void*);
void FighterManager__pause_finalbg_impl(FighterManager*) {
    FUN_710260cac0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415d0 — resume_finalbg: global->deref, tail call
extern "C" void FUN_710260cbd0(void*);
void FighterManager__resume_finalbg_impl(FighterManager*) {
    FUN_710260cbd0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415e0 — set_visible_finalbg: global->deref, mask bool, tail call
extern "C" void FUN_710260c800(void*, bool);
void FighterManager__set_visible_finalbg_impl(FighterManager*, bool val) {
    FUN_710260c800(*reinterpret_cast<void**>(DAT_71053299d8), val & 1);
}

// 7102141600 — notify_log_event_collision_hit: ldr x0,[x0]; and w4; b external
extern "C" void FUN_710067a7b0(void*, u64, u64, u64, bool);
void FighterManager__notify_log_event_collision_hit_impl(FighterManager* mgr, u64 p1, u64 p2, u64 p3, bool p4) {
    FUN_710067a7b0(*reinterpret_cast<void**>(mgr), p1, p2, p3, p4 & 1);
}

// 7102141610 — is_process_technique: ldr x0,[x0]; b external
extern "C" void FUN_710067bcf0(void*);
void FighterManager__is_process_technique_impl(FighterManager* mgr) {
    FUN_710067bcf0(*reinterpret_cast<void**>(mgr));
}

// 7102141650 — set_dead_up_camera_hit_cursor_status: complex refcount + vtable (54 insns)
// Skipping due to extreme complexity (deep pointer chains, dual vtable calls, refcount)

// 71021417b0 — set_controller_rumble_all: ldr x0,[x0]; and w3; b external
extern "C" void FUN_710067de90(void*, u64, u64, bool);
void FighterManager__set_controller_rumble_all_impl(FighterManager* mgr, u64 p1, u64 p2, bool p3) {
    FUN_710067de90(*reinterpret_cast<void**>(mgr), p1, p2, p3 & 1);
}

// 71021417c0 — is_rebirth_plate_line: NOTE: does NOT deref x0
extern "C" void FUN_710067ef30(void*, u64);
void FighterManager__is_rebirth_plate_line_impl(FighterManager* mgr, u64 id) {
    FUN_710067ef30(mgr, id & 0xFFFFFFFF);
}

// 71021417d0 — set_position_lock: loop over fighters, vtable calls (43 insns)
// Skipping due to complexity (bounds check + loop + two vtable calls per element)

// 7102141890 — prepare_movie: ldr x8,[x0]; ldr x8,[x8,#0xb80]; ldr x0,[x8]; b external
extern "C" void FUN_710067f480(void*);
void FighterManager__prepare_movie_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* movie_ctrl = *reinterpret_cast<u8**>(data + 0xb80);
    FUN_710067f480(*reinterpret_cast<void**>(movie_ctrl));
}

// 71021418c0 — exit_movie: same chain as prepare_movie, different target
extern "C" void FUN_710067f640(void*);
void FighterManager__exit_movie_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    auto* movie_ctrl = *reinterpret_cast<u8**>(data + 0xb80);
    FUN_710067f640(*reinterpret_cast<void**>(movie_ctrl));
}

// 71021418f0 — start_movie: ldr x0,[x0]; b external
extern "C" void FUN_710067f720(void*);
void FighterManager__start_movie_impl(FighterManager* mgr) {
    FUN_710067f720(*reinterpret_cast<void**>(mgr));
}

// 7102141900 — start_movie_on_rendering_2d: ldr x0,[x0]; b external
extern "C" void FUN_710067f850(void*);
void FighterManager__start_movie_on_rendering_2d_impl(FighterManager* mgr) {
    FUN_710067f850(*reinterpret_cast<void**>(mgr));
}

// 7102141930 — get_jack_final_cut_in: ldr x0,[x0]; b external
extern "C" void FUN_710067f970(void*);
void FighterManager__get_jack_final_cut_in_impl(FighterManager* mgr) {
    FUN_710067f970(*reinterpret_cast<void**>(mgr));
}

} // namespace app::lua_bind
