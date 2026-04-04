#pragma once

#include "types.h"

namespace app {

struct FighterManagerData {
    u8    pad_0x00[0x20];
    void* entries[8];                        // +0x20 — FighterEntry* pointers
    u8    pad_0x60[0x40];
    u32   entry_count;                       // +0xA0
    u8    pad_0xA4[0x04];
    u32   final_actor_entry_id;              // +0xA8
    u32   no_discretion_final_beat_count;    // +0xAC
    u8    pad_0xB0[0x10];
    u8    melee_mode;                        // +0xC0
    u8    pad_0xC1[0x0B];
    u8    discretion_final_enabled;          // +0xCC
    u8    pad_0xCD[0x05];
    u8    ready_go;                          // +0xD2
    u8    pad_0xD3[0x03];
    u8    cursor_whole;                      // +0xD6
    u8    pad_0xD7[0x12];
    u8    result_mode;                       // +0xE9
    u8    pad_0xEA[0x04];
    u8    ko_camera_enabled;                 // +0xEE
    u8    pad_0xEF[0x01];
    f32   one_on_one_ratio;                  // +0xF0
    u8    pad_0xF4[0x6C];
    s32   fear_face_entry_id;                // +0x160
    u8    pad_0x164[0xA14];
    void* finalbg_ptr;                       // +0xB78
    void* movie_ptr;                         // +0xB80
};

struct FighterManager {
    FighterManagerData* data;                // +0x0
};

} // namespace app
