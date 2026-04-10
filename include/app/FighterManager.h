#pragma once

#include "types.h"

namespace app {

// All field names derived from .dynsym FighterManager__*_impl functions.
// Access pattern: mgr->data at +0x0; impl reads *(mgr)+OFFSET.
struct FighterManagerData {
    u8    pad_0x00[0x20];
    void* entries[8];                        // +0x20 [derived: get_fighter_entry_impl (.dynsym) indexes +0x20 with entry_id*8, max 8]
    u8    pad_0x60[0x40];
    u32   entry_count;                       // +0xA0 [derived: entry_count_impl (.dynsym) reads +0xA0 as u32]
    u8    pad_0xA4[0x04];
    u32   final_actor_entry_id;              // +0xA8 [derived: get_final_actor_entry_id_impl (.dynsym) reads +0xA8 as u32]
    u32   no_discretion_final_beat_count;    // +0xAC [derived: get_no_discretion_final_beat_count_impl (.dynsym) reads +0xAC as u32]
    u8    pad_0xB0[0x10];
    u8    melee_mode;                        // +0xC0 [derived: is_melee_mode_homerun_impl (.dynsym) compares +0xC0 == 9]
    u8    pad_0xC1[0x02];
    u8    hp_mode_global;                    // +0xC3 [derived: is_hp_mode (0x7100693df0) checks +0xC3 != 0 as global HP mode flag]
    u8    pad_0xC4[0x08];
    u8    discretion_final_enabled;          // +0xCC [derived: is_discretion_final_enabled_impl (.dynsym) reads +0xCC as u8]
    u8    handi_enabled;                     // +0xCD [derived: get_handi (0x71006937e0) checks +0xCD != 0 to enable handicap lookup]
    u8    pad_0xCE[0x04];
    u8    ready_go;                          // +0xD2 [derived: is_ready_go_impl (.dynsym) reads +0xD2 as u8]
    u8    pad_0xD3[0x03];
    u8    cursor_whole;                      // +0xD6 [derived: set_cursor_whole_impl (.dynsym) writes +0xD6 as bool]
    u8    pad_0xD7[0x12];
    u8    result_mode;                       // +0xE9 [derived: is_result_mode_impl (.dynsym) reads +0xE9 as u8]
    u8    pad_0xEA[0x04];
    u8    ko_camera_enabled;                 // +0xEE [derived: is_disable_ko_camera_impl (.dynsym) checks +0xEE == 0; enable/disable write here]
    u8    pad_0xEF[0x01];
    f32   one_on_one_ratio;                  // +0xF0 [derived: one_on_one_ratio_impl (.dynsym) reads +0xF0 as f32]
    u8    pad_0xF4[0x6C];
    s32   fear_face_entry_id;                // +0x160 [derived: set_final_fear_face_impl (.dynsym) reads/writes +0x160 as s32 entry_id]
    u8    pad_0x164[0xA14];
    void* finalbg_ptr;                       // +0xB78 [derived: exit_finalbg_impl (.dynsym) dereferences +0xB78 as pointer to finalbg object]
    void* movie_ptr;                         // +0xB80 [derived: exit_movie_impl (.dynsym) dereferences +0xB80 as pointer to movie object]
};

struct FighterManager {
    FighterManagerData* data;                // +0x0 [derived: all FighterManager__*_impl (.dynsym) dereference mgr+0 to reach data]
};

} // namespace app
