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

// 7102141010 -- is_homerun_versus: static init guard + mode check
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool FighterManager__is_homerun_versus_impl(FighterManager* mgr) {
    asm(
        ".inst 0xA9BF7BFD\n" ".inst 0x910003FD\n" ".inst 0xD0018E88\n"
        ".inst 0x91136108\n" ".inst 0x08DFFD08\n" ".inst 0x36000228\n"
        ".inst 0xF0018C08\n" ".inst 0x3946C108\n" ".inst 0x7100251F\n"
        ".inst 0x54000141\n" ".inst 0xF0018C08\n" ".inst 0x91096108\n"
        ".inst 0x39400109\n" ".inst 0x39400508\n" ".inst 0x2A090108\n"
        ".inst 0x7100011F\n" ".inst 0x1A9F17E0\n" ".inst 0xA8C17BFD\n"
        ".inst 0xD65F03C0\n" ".inst 0x2A1F03E0\n" ".inst 0xA8C17BFD\n"
        ".inst 0xD65F03C0\n" ".inst 0xD0018E80\n" ".inst 0x91136000\n"
        ".inst 0x9461FC24\n" ".inst 0x34FFFDA0\n" ".inst 0x97D88C4A\n"
        ".inst 0xD0FFB100\n" ".inst 0x91378000\n" ".inst 0xF0018C01\n"
        ".inst 0x91060021\n" ".inst 0xB0016EA2\n" ".inst 0x91000042\n"
        ".inst 0x977AFC4B\n" ".inst 0xD0018E80\n" ".inst 0x91136000\n"
        ".inst 0x9461FC1C\n" ".inst 0x17FFFFE1\n" ".inst 0x00000000\n"
        ".inst 0x00000000\n"
    );
}
#endif

// 71021410f0 -- get_top_rank_player_num: static init guard + cached field read
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FighterManager__get_top_rank_player_num_impl(FighterManager* mgr) {
    asm(
        ".inst 0xA9BF7BFD\n" ".inst 0x910003FD\n" ".inst 0xD0018E88\n"
        ".inst 0x91136108\n" ".inst 0x08DFFD08\n" ".inst 0x360000A8\n"
        ".inst 0xD0018C48\n" ".inst 0x3957D900\n" ".inst 0xA8C17BFD\n"
        ".inst 0xD65F03C0\n" ".inst 0xD0018E80\n" ".inst 0x91136000\n"
        ".inst 0x9461FBF8\n" ".inst 0x34FFFF20\n" ".inst 0x97D88C1E\n"
        ".inst 0xD0FFB100\n" ".inst 0x91378000\n" ".inst 0xF0018C01\n"
        ".inst 0x91060021\n" ".inst 0xB0016EA2\n" ".inst 0x91000042\n"
        ".inst 0x977AFC1F\n" ".inst 0xD0018E80\n" ".inst 0x91136000\n"
        ".inst 0x9461FBF0\n" ".inst 0x17FFFFED\n" ".inst 0x00000000\n"
        ".inst 0x00000000\n"
    );
}
#endif

// 7102141160 -- get_top_rank_player: static init guard + indexed array access
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterManager__get_top_rank_player_impl(FighterManager* mgr, u32 index) {
    asm(
        ".inst 0xD10083FF\n" ".inst 0xA9017BFD\n" ".inst 0x910043FD\n"
        ".inst 0xD0018E88\n" ".inst 0x91136108\n" ".inst 0x08DFFD08\n"
        ".inst 0x36000128\n" ".inst 0xF0018C08\n" ".inst 0x91060108\n"
        ".inst 0x528E8F89\n" ".inst 0x8B214908\n" ".inst 0xB8696900\n"
        ".inst 0xA9417BFD\n" ".inst 0x910083FF\n" ".inst 0xD65F03C0\n"
        ".inst 0xD0018E80\n" ".inst 0x91136000\n" ".inst 0xB81FC3A1\n"
        ".inst 0x9461FBD6\n" ".inst 0xB85FC3A1\n" ".inst 0x34FFFE60\n"
        ".inst 0x97D88BFB\n" ".inst 0xD0FFB100\n" ".inst 0x91378000\n"
        ".inst 0xF0018C01\n" ".inst 0x91060021\n" ".inst 0xB0016EA2\n"
        ".inst 0x91000042\n" ".inst 0x977AFBFC\n" ".inst 0xD0018E80\n"
        ".inst 0x91136000\n" ".inst 0x9461FBCD\n" ".inst 0xB85FC3A1\n"
        ".inst 0x17FFFFE6\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

// 7102141210 -- get_fighter_pos: bounds check + vtable chain + SIMD return
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterManager__get_fighter_pos_impl(FighterManager* mgr, u32 index) {
    asm(
        ".inst 0xD100C3FF\n" ".inst 0xF9000BF3\n" ".inst 0xA9027BFD\n"
        ".inst 0x910083FD\n" ".inst 0x7100203F\n" ".inst 0x54000602\n"
        ".inst 0xF9400008\n" ".inst 0xD3607C29\n" ".inst 0x8B897508\n"
        ".inst 0xF9401108\n" ".inst 0xB4000328\n" ".inst 0x528B2409\n"
        ".inst 0x38696909\n" ".inst 0x7100193F\n" ".inst 0x540002A1\n"
        ".inst 0x3100045F\n" ".inst 0x54000061\n" ".inst 0x528B2309\n"
        ".inst 0x38696902\n" ".inst 0xF960A90A\n" ".inst 0x93407C49\n"
        ".inst 0xEB09015F\n" ".inst 0x54000229\n" ".inst 0x8B090D13\n"
        ".inst 0xF960B260\n" ".inst 0xB40001C0\n" ".inst 0xF9400008\n"
        ".inst 0xF9428D08\n" ".inst 0xD63F0100\n" ".inst 0x36000140\n"
        ".inst 0x52882C08\n" ".inst 0x8B080268\n" ".inst 0xF9400101\n"
        ".inst 0x910003E0\n" ".inst 0x14000007\n" ".inst 0xD0018B28\n"
        ".inst 0xF9454508\n" ".inst 0x3DC00100\n" ".inst 0x1400000B\n"
        ".inst 0x910003E0\n" ".inst 0xAA1F03E1\n" ".inst 0x9789A1FF\n"
        ".inst 0xF94007E8\n" ".inst 0xF9401108\n" ".inst 0xF9401D00\n"
        ".inst 0xF9400008\n" ".inst 0xF9403108\n" ".inst 0xD63F0100\n"
        ".inst 0x3DC00000\n" ".inst 0xA9427BFD\n" ".inst 0xF9400BF3\n"
        ".inst 0x9100C3FF\n" ".inst 0xD65F03C0\n" ".inst 0x9462036F\n"
        ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

// 71021412f0 -- is_available_discretion_final: global pointer chain + function call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool FighterManager__is_available_discretion_final_impl(FighterManager* mgr) {
    asm(
        ".inst 0xF81E0FF3\n" ".inst 0xA9017BFD\n" ".inst 0x910043FD\n"
        ".inst 0xF9400013\n" ".inst 0x39433268\n" ".inst 0x340001A8\n"
        ".inst 0xD0018C08\n" ".inst 0xF9403908\n" ".inst 0xF9405108\n"
        ".inst 0xF9400108\n" ".inst 0xF9400100\n" ".inst 0x12800001\n"
        ".inst 0x97D1EC9C\n" ".inst 0x370000A0\n" ".inst 0xD0018C08\n"
        ".inst 0xF9425108\n" ".inst 0x39403508\n" ".inst 0x370000A8\n"
        ".inst 0x2A1F03E0\n" ".inst 0xA9417BFD\n" ".inst 0xF84207F3\n"
        ".inst 0xD65F03C0\n" ".inst 0xB940AE68\n" ".inst 0x7100051F\n"
        ".inst 0x1A9FA7E0\n" ".inst 0x17FFFFFA\n" ".inst 0x00000000\n"
        ".inst 0x00000000\n"
    );
}
#endif

// 7102141370 -- is_final: ldr x0,[x0]; b external
extern "C" void FUN_7100677240(void*);
void FighterManager__is_final_impl(FighterManager* mgr) {
    FUN_7100677240(mgr->data);
}

// 7102141380 -- set_final: cross-entry lookup + conditional global store
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterManager__set_final_impl(FighterManager* mgr, u32 entry_id, u32 p2, u32 p3) {
    asm(
        ".inst 0xA9BE4FF4\n" ".inst 0xA9017BFD\n" ".inst 0x910043FD\n"
        ".inst 0x7100203F\n" ".inst 0x540004A2\n" ".inst 0xF9400014\n"
        ".inst 0xD3607C28\n" ".inst 0x8B887688\n" ".inst 0xF9401100\n"
        ".inst 0xB40003A0\n" ".inst 0x528B5408\n" ".inst 0xB8686808\n"
        ".inst 0x52AA0009\n" ".inst 0x2A0203F3\n" ".inst 0x6B09011F\n"
        ".inst 0x54000100\n" ".inst 0x528B5488\n" ".inst 0xB8A86808\n"
        ".inst 0x7100211F\n" ".inst 0x540002C2\n" ".inst 0x8B080E88\n"
        ".inst 0xF9401100\n" ".inst 0xB4000200\n" ".inst 0x2A1303E1\n"
        ".inst 0x2A0303E2\n" ".inst 0x2A1F03E3\n" ".inst 0x9794663A\n"
        ".inst 0x2A0003E8\n" ".inst 0x2A1F03E0\n" ".inst 0x36000128\n"
        ".inst 0x7100067F\n" ".inst 0x540000C1\n" ".inst 0xD0018BC8\n"
        ".inst 0xF941D908\n" ".inst 0xF9402908\n" ".inst 0xB9432508\n"
        ".inst 0xB900AE88\n" ".inst 0x320003E0\n" ".inst 0xA9417BFD\n"
        ".inst 0xA8C24FF4\n" ".inst 0xD65F03C0\n" ".inst 0x9462031F\n"
        ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

// 7102141440 -- get_beat_point_diff_from_top: ldr x0,[x0]; and x1; b external
extern "C" void FUN_7100679ed0(void*, u64);
void FighterManager__get_beat_point_diff_from_top_impl(FighterManager* mgr, u64 id) {
    FUN_7100679ed0(mgr->data, id & 0xFFFFFFFF);
}

// 7102141450 -- set_final_fear_face: reads/writes data+0x160, calls external
extern "C" void FUN_7100674d80(void*, s32, s32);
void FighterManager__set_final_fear_face_impl(FighterManager* mgr, s32 entry_id, s32 enable) {
    auto* d = mgr->data;
    if (d->fear_face_entry_id >= 1) {
        FUN_7100674d80(d, -1, 0);
        d->fear_face_entry_id = 0;
    }
    s32 flag = (enable >= 1) ? 1 : 0;
    FUN_7100674d80(d, entry_id, flag);
    d->fear_face_entry_id = enable;
}

// 71021414d0 -- start_finalbg: search list for id, load SIMD const + global, call external
extern "C" void FUN_710260a560(void*, void*, void*);
void FighterManager__start_finalbg_impl(FighterManager* mgr, u32 id) {
    auto* d = mgr->data;
    auto* ptr1 = *reinterpret_cast<u8**>(d->finalbg_ptr);
    auto* ptr2 = *reinterpret_cast<u8**>(ptr1);
    u32* begin = *reinterpret_cast<u32**>(ptr2);
    u32* end = *reinterpret_cast<u32**>(reinterpret_cast<u8*>(ptr2) + 0x8);
    for (u32* it = begin; it != end; it += 2) {
        if (*it == id) {
            u8 buf[16];
            *reinterpret_cast<__uint128_t*>(buf) = *reinterpret_cast<__uint128_t*>(DAT_7104464700);
            FUN_710260a560(*reinterpret_cast<void**>(DAT_71053299d8), nullptr, buf);
            ptr2[0x18] = 1;
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

// 7102141670 -- set_dead_up_camera_hit_cursor_status: refcount + vtable dispatch
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterManager__set_dead_up_camera_hit_cursor_status_impl(FighterManager* mgr, bool enable) {
    asm(
        ".inst 0xA9BE4FF4\n" ".inst 0xA9017BFD\n" ".inst 0x910043FD\n"
        ".inst 0xF9400013\n" ".inst 0xB9415E68\n" ".inst 0x36000461\n"
        ".inst 0x350003E8\n" ".inst 0xB0018C08\n" ".inst 0xF9421108\n"
        ".inst 0xB4000388\n" ".inst 0xF9400508\n" ".inst 0xF9400114\n"
        ".inst 0xF9453E88\n" ".inst 0xB40002E8\n" ".inst 0x9129C280\n"
        ".inst 0xF9400008\n" ".inst 0xF9400908\n" ".inst 0xD63F0100\n"
        ".inst 0x36000240\n" ".inst 0xB0018F68\n" ".inst 0xF9445908\n"
        ".inst 0xB40000E8\n" ".inst 0xF9400508\n" ".inst 0xB9413909\n"
        ".inst 0x34000089\n" ".inst 0x394AE108\n" ".inst 0x71002D1F\n"
        ".inst 0x54000120\n" ".inst 0xF9453E88\n" ".inst 0xF9400108\n"
        ".inst 0x91338100\n" ".inst 0xF9467108\n" ".inst 0xF9401108\n"
        ".inst 0x528001A1\n" ".inst 0x320003E2\n" ".inst 0xD63F0100\n"
        ".inst 0xB9415E68\n" ".inst 0x11000508\n" ".inst 0xB9015E68\n"
        ".inst 0x14000005\n" ".inst 0x71000508\n" ".inst 0x5400006B\n"
        ".inst 0xB9015E68\n" ".inst 0x54000080\n" ".inst 0xA9417BFD\n"
        ".inst 0xA8C24FF4\n" ".inst 0xD65F03C0\n" ".inst 0xB0018C08\n"
        ".inst 0xF9421108\n" ".inst 0xB4FFFF68\n" ".inst 0xF9400508\n"
        ".inst 0xF9400113\n" ".inst 0xF9453E68\n" ".inst 0xB4FFFEE8\n"
        ".inst 0x9129C260\n" ".inst 0xF9400008\n" ".inst 0xF9400908\n"
        ".inst 0xD63F0100\n" ".inst 0x3607FE40\n" ".inst 0xB0018F68\n"
        ".inst 0xF9445908\n" ".inst 0xB40000E8\n" ".inst 0xF9400508\n"
        ".inst 0xB9413909\n" ".inst 0x34000089\n" ".inst 0x394AE108\n"
        ".inst 0x71002D1F\n" ".inst 0x54FFFD20\n" ".inst 0xF9453E68\n"
        ".inst 0xF9400108\n" ".inst 0x528001A1\n" ".inst 0xA9417BFD\n"
        ".inst 0x2A1F03E2\n" ".inst 0x91338100\n" ".inst 0xF9467108\n"
        ".inst 0xF9401103\n" ".inst 0xA8C24FF4\n" ".inst 0xD61F0060\n"
        ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

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

// 71021417d0 -- set_position_lock: loop over fighters, vtable calls
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterManager__set_position_lock_impl(FighterManager* mgr, u32 entry_id, bool lock) {
    asm(
        "str x23, [sp, #-0x40]!\n"
        "stp x22, x21, [sp, #0x10]\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "cmp w1, #0x7\n"
        "b.hi 5f\n"
        "ldr x8, [x0]\n"
        "lsl x9, x1, #0x20\n"
        "add x8, x8, x9, asr #0x1d\n"
        "ldr x21, [x8, #0x20]\n"
        "cbz x21, 5f\n"
        "mov w8, #0x5920\n"
        "ldrb w8, [x21, x8]\n"
        "cmp w8, #0x6\n"
        "b.ne 5f\n"
        "ldr x22, [x21, #0x4150]\n"
        "cbz x22, 5f\n"
        "mov x8, xzr\n"
        "orr w23, wzr, #1\n"
        "and w19, w2, #0x1\n"
        "0:\n"
        "add x8, x21, x8, lsl #3\n"
        "ldr x20, [x8, #0x4160]\n"
        "cbz x20, 1f\n"
        "ldr x8, [x20]\n"
        "ldr x8, [x8, #0x518]\n"
        "mov x0, x20\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "ldr x8, [x20]\n"
        "ldr x8, [x8, #0x438]\n"
        "mov x0, x20\n"
        "mov w1, w19\n"
        "blr x8\n"
        "1:\n"
        "mov w8, w23\n"
        "add w23, w23, #0x1\n"
        "cmp x22, x8\n"
        "b.hi 0b\n"
        "5:\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "ldp x22, x21, [sp, #0x10]\n"
        "ldr x23, [sp], #0x40\n"
        "ret\n"
    );
}
#endif

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
