#pragma once
#include "types.h"

namespace app {

// SearchModule — accessed at BattleObjectModuleAccessor+0xE0
// Manages search/grab hitbox areas for detecting opponents.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0x128).
struct SearchModule {
    void** _vt;

    // -- Clear (0x50-0x58) -- [confirmed: lua_bind API names]
    void clear_all() { ((void(*)(SearchModule*))_vt[0x50/8])(this); }
    void clear(u64 p1) { ((void(*)(SearchModule*,u64))_vt[0x58/8])(this,p1); }

    // -- Offset/size (0x68-0x90) --
    void set_offset(u64 p1, u64 p2) { ((void(*)(SearchModule*,u64,u64))_vt[0x68/8])(this,p1,p2); }
    void set_offset2(u64 p1, u64 p2) { ((void(*)(SearchModule*,u64,u64))_vt[0x70/8])(this,p1,p2); }
    u32 active_part_num() { return ((u32(*)(SearchModule*))_vt[0x78/8])(this); }
    bool is_search(u64 p1) { return ((bool(*)(SearchModule*,u64))_vt[0x80/8])(this,p1); }
    u32 get_size(u64 p1) { return ((u32(*)(SearchModule*,u64))_vt[0x88/8])(this,p1); }
    void set_size(u64 p1) { ((void(*)(SearchModule*,u64))_vt[0x90/8])(this,p1); }

    // -- Target/position (0x98-0xa0) --
    void set_target_opponent(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(SearchModule*,u64,u64,u64,u64))_vt[0x98/8])(this,p1,p2,p3,p4); }
    void set_pos(u64 p1, u64 p2, u64 p3) { ((void(*)(SearchModule*,u64,u64,u64))_vt[0xa0/8])(this,p1,p2,p3); }

    // -- Inflict/log (0xc8-0xe0) --
    bool is_inflict() { return ((bool(*)(SearchModule*))_vt[0xc8/8])(this); }
    void set_check_interval(u64 p1) { ((void(*)(SearchModule*,u64))_vt[0xd0/8])(this,p1); }
    void set_remove_log_attack(bool p1) { ((void(*)(SearchModule*,bool))_vt[0xd8/8])(this,p1); }
    void* remove_log_attack() { return ((void*(*)(SearchModule*))_vt[0xe0/8])(this); }

    // -- Sleep/sync (0xe8-0x128) --
    void sleep(bool p1) { ((void(*)(SearchModule*,bool))_vt[0xe8/8])(this,p1); }
    void relocate(u64 p1) { ((void(*)(SearchModule*,u64))_vt[0xf8/8])(this,p1); }
    void* invalid_attack_mask() { return ((void*(*)(SearchModule*))_vt[0x100/8])(this); }
    void set_invalid_attack_mask(u64 p1) { ((void(*)(SearchModule*,u64))_vt[0x108/8])(this,p1); }
    void set_sync_situation(bool p1) { ((void(*)(SearchModule*,bool))_vt[0x110/8])(this,p1); }
    void set_sync_lr(bool p1) { ((void(*)(SearchModule*,bool))_vt[0x118/8])(this,p1); }
    u32 situation() { return ((u32(*)(SearchModule*))_vt[0x120/8])(this); }
    void enable_safe_pos() { ((void(*)(SearchModule*))_vt[0x128/8])(this); }
};

} // namespace app
