#include "app/FighterManager.h"
#include "app/FighterEntry.h"

using app::FighterManager;
using app::FighterManagerData;
using app::FighterEntry;

extern "C" [[noreturn]] void abort();
extern "C" [[noreturn]] void FUN_71039c20a0();
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7104464700[];
extern "C" __attribute__((visibility("hidden"))) u64* DAT_71053299d8;

namespace app::lua_bind {

// 7102140d60 -- entry_count (3 instructions)
u32 FighterManager__entry_count_impl(FighterManager* mgr) {
    return mgr->data->entry_count;
}

// 7102141650 -- enable_ko_camera (4 instructions)
void FighterManager__enable_ko_camera_impl(FighterManager* mgr) {
    mgr->data->ko_camera_enabled = 1;
}

// 7102141660 -- disable_ko_camera (3 instructions)
void FighterManager__disable_ko_camera_impl(FighterManager* mgr) {
    mgr->data->ko_camera_enabled = 0;
}

// Simple field reads (3-5 instructions)
bool FighterManager__is_disable_ko_camera_impl(FighterManager* mgr) {
    return mgr->data->ko_camera_enabled == 0; // cmp #0, cset eq
}
bool FighterManager__is_melee_mode_homerun_impl(FighterManager* mgr) {
    return mgr->data->melee_mode == 9; // cmp #9, cset eq
}
bool FighterManager__is_melee_mode_online_tournament_impl(FighterManager* mgr) {
    return mgr->data->melee_mode == 0x18; // cmp #0x18, cset eq
}
u8 FighterManager__is_discretion_final_enabled_impl(FighterManager* mgr) {
    return mgr->data->discretion_final_enabled;
}
u8 FighterManager__is_ready_go_impl(FighterManager* mgr) {
    return mgr->data->ready_go;
}
u8 FighterManager__is_result_mode_impl(FighterManager* mgr) {
    return mgr->data->result_mode;
}
// 4-instruction setter with bool masking
void FighterManager__set_cursor_whole_impl(FighterManager* mgr, bool val) {
    mgr->data->cursor_whole = val & 1;
}
// 3-instruction getters
u32 FighterManager__get_no_discretion_final_beat_count_impl(FighterManager* mgr) {
    return mgr->data->no_discretion_final_beat_count;
}
u32 FighterManager__get_final_actor_entry_id_impl(FighterManager* mgr) {
    return mgr->data->final_actor_entry_id;
}

// 7102140f90 -- get_fighter_entry (10 instructions, bounds check + indexed)
void* FighterManager__get_fighter_entry_impl(FighterManager* mgr, u32 index) {
    if (index >= 8) { FUN_71039c20a0(); }
    return mgr->data->entries[index];
}

// 7102140fc0 -- get_fighter_information (11 instructions, bounds check + offset)
void* FighterManager__get_fighter_information_impl(FighterManager* mgr, u32 index) {
    if (index >= 8) { FUN_71039c20a0(); }
    return reinterpret_cast<u8*>(mgr->data->entries[index]) + 0xf0;
}

// 7102141910 -- is_end_movie (7 instructions, pointer chain + cmp)
bool FighterManager__is_end_movie_impl(FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) == 8;
}

// 71021418a0 -- is_prepared_movie (7 instructions, pointer chain + cmp 4)
bool FighterManager__is_prepared_movie_impl(FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) == 4;
}

// 71021418d0 -- is_process_movie (7 instructions, pointer chain + cmp 0, ne)
bool FighterManager__is_process_movie_impl(FighterManager* mgr) {
    auto* movie = *reinterpret_cast<u8**>(mgr->data->movie_ptr);
    return *reinterpret_cast<u32*>(movie + 0x20) != 0;
}

void FighterManager__reset_fighter_impl(FighterManager* obj) { }

// 71021410d0 -- one_on_one_ratio (3 instructions, simple field read)
f32 FighterManager__one_on_one_ratio_impl(FighterManager* mgr) {
    return mgr->data->one_on_one_ratio;
}

// 7102140d70 -- total_fighter_num: sum fighter_num across 8 entry slots
u32 FighterManager__total_fighter_num_impl(FighterManager* mgr) {
    auto* d = mgr->data;
    u32 total = 0;
    for (s32 i = 0; i < 8; i++) {
        auto* entry = static_cast<FighterEntry*>(d->entries[i]);
        if (entry) {
            total += entry->fighter_num;
        }
    }
    return total;
}

// 7102140e10 -- get_entry_id: walk 8 slots (unrolled), decrement counter, return index
u64 FighterManager__get_entry_id_impl(FighterManager* mgr, s32 n) {
    auto* d = mgr->data;
#define CHECK_SLOT(I) \
    if (d->entries[I]) { \
        if (n == 0) return (I); \
        n--; \
    }
    CHECK_SLOT(0) CHECK_SLOT(1) CHECK_SLOT(2) CHECK_SLOT(3)
    CHECK_SLOT(4) CHECK_SLOT(5) CHECK_SLOT(6)
#undef CHECK_SLOT
    // Slot 7 -- merged compare pattern: movn w8,#0 first, then orr w9,#7, csel eq
    u64 result = 0xFFFFFFFF;
    if (d->entries[7] != nullptr && n == 0) {
        result = 7;
    }
    return result;
}

// 7102140ee0 -- get_entry_no: count non-null entries before index (unrolled cinc)
u32 FighterManager__get_entry_no_impl(FighterManager* mgr, u32 entry_id) {
    if (entry_id == 0) return 0;
    auto* d = mgr->data;
    u64 id = static_cast<u32>(entry_id);  // zero-extend to match original `and x9,x1,#0xffffffff`
    u32 count = d->entries[0] != nullptr;
    if (id == 1) return count;
    count += d->entries[1] != nullptr;
    if (id == 2) return count;
    count += d->entries[2] != nullptr;
    if (id == 3) return count;
    count += d->entries[3] != nullptr;
    if (id == 4) return count;
    count += d->entries[4] != nullptr;
    if (id == 5) return count;
    count += d->entries[5] != nullptr;
    if (id == 6) return count;
    count += d->entries[6] != nullptr;
    if (id == 7) return count;
    count += d->entries[7] != nullptr;
    return count;
}

// 7102141370 -- is_final: ldr x0,[x0]; b external
extern "C" void FUN_7100677240(void*);
void FighterManager__is_final_impl(FighterManager* mgr) {
    FUN_7100677240(mgr->data);
}

// 7102141440 -- get_beat_point_diff_from_top: ldr x0,[x0]; and x1; b external
extern "C" void FUN_7100679ed0(void*, u64);
void FighterManager__get_beat_point_diff_from_top_impl(FighterManager* mgr, u64 id) {
    FUN_7100679ed0(mgr->data, id & 0xFFFFFFFF);
}

// 7102141450 -- set_final_fear_face: reads/writes data+0x160, calls external
extern "C" void FUN_7100674d80(void*, u64, s32);
void FighterManager__set_final_fear_face_impl(FighterManager* mgr, u64 raw_entry_id, s32 enable) {
    auto* d = mgr->data;
    u64 entry_id = raw_entry_id & 0xFFFFFFFF;
    if (d->fear_face_entry_id >= 1) {
        FUN_7100674d80(d, (u32)-1, 0);
        d->fear_face_entry_id = 0;
    }
#ifdef MATCHING_HACK_NX_CLANG
    if (enable >= 1) {
        void* arg0 = d; u64 arg1 = entry_id;
        asm volatile("" : "+r"(arg0), "+r"(arg1));
        FUN_7100674d80(arg0, arg1, 1);
    } else {
        void* arg0 = d; u64 arg1 = entry_id;
        asm volatile("" : "+r"(arg0), "+r"(arg1));
        FUN_7100674d80(arg0, arg1, 0);
    }
#else
    FUN_7100674d80(d, entry_id, enable >= 1 ? 1 : 0);
#endif
    d->fear_face_entry_id = enable;
}

// 71021414d0 -- start_finalbg: search list for id, load SIMD const + global, call external
extern "C" void FUN_710260a560(void*, u32, void*);
void FighterManager__start_finalbg_impl(FighterManager* mgr, u32 id) {
    auto* d = mgr->data;
    auto* obj = *reinterpret_cast<u8**>(d->finalbg_ptr);
    u64* begin = *reinterpret_cast<u64**>(obj);
    u64* end = *reinterpret_cast<u64**>(obj + 0x8);
    for (u64* it = begin; it != end; it++) {
        if (*reinterpret_cast<u32*>(it) == id) {
            if (it == end) break;
            u8 buf[16];
            *reinterpret_cast<__uint128_t*>(buf) = *reinterpret_cast<__uint128_t*>(DAT_7104464700);
            FUN_710260a560(*reinterpret_cast<void**>(DAT_71053299d8), id, buf);
            obj[0x18] = 1;
            return;
        }
    }
}

// 7102141560 -- exit_finalbg: check active flag, call external, clear flag
extern "C" void FUN_710260b9b0(void*);
void FighterManager__exit_finalbg_impl(FighterManager* mgr) {
    auto* d = mgr->data;
    auto* ptr1 = *reinterpret_cast<u8**>(d->finalbg_ptr);
    auto* ptr2 = *reinterpret_cast<u8**>(ptr1);
    if (ptr2[0x18] != 0) {
        FUN_710260b9b0(*reinterpret_cast<void**>(DAT_71053299d8));
        ptr2[0x18] = 0;
    }
}

// 71021415a0 -- show_finalbg: global->deref, tail call
extern "C" void FUN_710260c900(void*);
void FighterManager__show_finalbg_impl(FighterManager*) {
    FUN_710260c900(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415b0 -- hide_finalbg: global->deref, tail call
extern "C" void FUN_710260c9e0(void*);
void FighterManager__hide_finalbg_impl(FighterManager*) {
    FUN_710260c9e0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415c0 -- pause_finalbg: global->deref, tail call
extern "C" void FUN_710260cac0(void*);
void FighterManager__pause_finalbg_impl(FighterManager*) {
    FUN_710260cac0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415d0 -- resume_finalbg: global->deref, tail call
extern "C" void FUN_710260cbd0(void*);
void FighterManager__resume_finalbg_impl(FighterManager*) {
    FUN_710260cbd0(*reinterpret_cast<void**>(DAT_71053299d8));
}

// 71021415e0 -- set_visible_finalbg: global->deref, mask bool, tail call
extern "C" void FUN_710260c800(void*, bool);
void FighterManager__set_visible_finalbg_impl(FighterManager*, bool val) {
    FUN_710260c800(*reinterpret_cast<void**>(DAT_71053299d8), val & 1);
}

// 7102141600 -- notify_log_event_collision_hit: ldr x0,[x0]; and w4; b external
extern "C" void FUN_710067a7b0(void*, u64, u64, u64, bool);
void FighterManager__notify_log_event_collision_hit_impl(FighterManager* mgr, u64 p1, u64 p2, u64 p3, bool p4) {
    FUN_710067a7b0(mgr->data, p1, p2, p3, p4 & 1);
}

// 7102141610 -- is_process_technique: ldr x0,[x0]; b external
extern "C" void FUN_710067bcf0(void*);
void FighterManager__is_process_technique_impl(FighterManager* mgr) {
    FUN_710067bcf0(mgr->data);
}

// 71021417b0 -- set_controller_rumble_all: ldr x0,[x0]; and w3; b external
extern "C" void FUN_710067de90(void*, u64, u64, bool);
void FighterManager__set_controller_rumble_all_impl(FighterManager* mgr, u64 p1, u64 p2, bool p3) {
    FUN_710067de90(mgr->data, p1, p2, p3 & 1);
}

// 71021417c0 -- is_rebirth_plate_line: NOTE: does NOT deref x0
extern "C" void FUN_710067ef30(void*, u64);
void FighterManager__is_rebirth_plate_line_impl(FighterManager* mgr, u64 id) {
    FUN_710067ef30(mgr, id & 0xFFFFFFFF);
}

// 7102141890 -- prepare_movie: ldr x8,[x0]; ldr x8,[x8,#0xb80]; ldr x0,[x8]; b external
extern "C" void FUN_710067f480(void*);
void FighterManager__prepare_movie_impl(FighterManager* mgr) {
    FUN_710067f480(*reinterpret_cast<void**>(mgr->data->movie_ptr));
}

// 71021418c0 -- exit_movie: same chain as prepare_movie, different target
extern "C" void FUN_710067f640(void*);
void FighterManager__exit_movie_impl(FighterManager* mgr) {
    FUN_710067f640(*reinterpret_cast<void**>(mgr->data->movie_ptr));
}

// 71021418f0 -- start_movie: ldr x0,[x0]; b external
extern "C" void FUN_710067f720(void*);
void FighterManager__start_movie_impl(FighterManager* mgr) {
    FUN_710067f720(mgr->data);
}

// 7102141900 -- start_movie_on_rendering_2d: ldr x0,[x0]; b external
extern "C" void FUN_710067f850(void*);
void FighterManager__start_movie_on_rendering_2d_impl(FighterManager* mgr) {
    FUN_710067f850(mgr->data);
}

// 7102141930 -- get_jack_final_cut_in: ldr x0,[x0]; b external
extern "C" void FUN_710067f970(void*);
void FighterManager__get_jack_final_cut_in_impl(FighterManager* mgr) {
    FUN_710067f970(mgr->data);
}

} // namespace app::lua_bind
