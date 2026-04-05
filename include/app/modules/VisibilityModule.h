#pragma once
#include "types.h"

namespace app {

// VisibilityModule — accessed at BattleObjectModuleAccessor+0x150
// Manages mesh/model visibility, material animation priority, and visibility modes.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0x118).
// All method names derived from .dynsym lua_bind::VisibilityModule__*_impl dispatcher analysis.
struct VisibilityModule {
    void** _vt;

    // -- Set visibility (0x50-0x58) -- [confirmed: lua_bind API names]
    void set(u64 p1, u64 p2) { ((void(*)(VisibilityModule*,u64,u64))_vt[0x50/8])(this,p1,p2); }
    void set_int64(u64 p1, u64 p2) { ((void(*)(VisibilityModule*,u64,u64))_vt[0x58/8])(this,p1,p2); }

    // -- Status default (0x60-0x88) --
    void set_status_default(u64 p1, u64 p2) { ((void(*)(VisibilityModule*,u64,u64))_vt[0x60/8])(this,p1,p2); }
    void set_status_default_int64(u64 p1, u64 p2) { ((void(*)(VisibilityModule*,u64,u64))_vt[0x68/8])(this,p1,p2); }
    void reset_status_default(u64 p1) { ((void(*)(VisibilityModule*,u64))_vt[0x70/8])(this,p1); }
    void reset_status_default_int64(u64 p1) { ((void(*)(VisibilityModule*,u64))_vt[0x78/8])(this,p1); }
    void reset_status_default_all() { ((void(*)(VisibilityModule*))_vt[0x80/8])(this); }
    void set_default_all() { ((void(*)(VisibilityModule*))_vt[0x88/8])(this); }

    // -- Mesh visibility (0x90-0xa0) --
    void set_mesh_visibility(u64 p1, u64 p2, bool p3) { ((void(*)(VisibilityModule*,u64,u64,bool))_vt[0x90/8])(this,p1,p2,p3); }
    void set_mesh_visibility_int64(u64 p1, u64 p2, bool p3) { ((void(*)(VisibilityModule*,u64,u64,bool))_vt[0x98/8])(this,p1,p2,p3); }
    void set_material_anim_priority(u64 p1, bool p2) { ((void(*)(VisibilityModule*,u64,bool))_vt[0xa0/8])(this,p1,p2); }

    // -- Whole visibility (0xc0-0xd0) --
    void set_whole(bool p1) { ((void(*)(VisibilityModule*,bool))_vt[0xc0/8])(this,p1); }
    u64 get_whole() { return ((u64(*)(VisibilityModule*))_vt[0xc8/8])(this); }
    bool is_visible() { return ((bool(*)(VisibilityModule*))_vt[0xd0/8])(this); }

    // -- Default (0xd8-0xe0) --
    void set_default(u64 p1) { ((void(*)(VisibilityModule*,u64))_vt[0xd8/8])(this,p1); }
    void set_default_int64(u64 p1) { ((void(*)(VisibilityModule*,u64))_vt[0xe0/8])(this,p1); }

    // -- Mesh query/mode (0x100-0x118) --
    bool is_visible_mesh(u64 p1) { return ((bool(*)(VisibilityModule*,u64))_vt[0x100/8])(this,p1); }
    void set_visibility_mode(u64 p1) { ((void(*)(VisibilityModule*,u64))_vt[0x110/8])(this,p1); }
    void set_model_visible(bool p1) { ((void(*)(VisibilityModule*,bool))_vt[0x118/8])(this,p1); }
};

} // namespace app
