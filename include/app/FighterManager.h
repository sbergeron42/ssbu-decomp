#pragma once

#include "types.h"

namespace app {

// FighterManager — operates on its own pointer (not BattleObjectModuleAccessor)
// Access pattern: ldr x8,[x0] gets internal FighterManagerData*, then field reads
// Known internal data fields (via FighterManagerData*):
//   +0x20..+0x58  FighterEntry* entries[8]
//   +0xA0         u32 entry_count
//   +0xA8         u32 final_actor_entry_id
//   +0xAC         u32 no_discretion_final_beat_count
//   +0xC0         u8  melee_mode
//   +0xCC         u8  discretion_final_enabled
//   +0xD2         u8  ready_go
//   +0xD6         u8  cursor_whole
//   +0xE9         u8  result_mode
//   +0xEE         u8  ko_camera_enabled
//   +0xF0         f32 one_on_one_ratio
//   +0xB80        void* movie_ptr
struct FighterManager;

} // namespace app
