#include "types.h"

// StageManager -- operates on StageManager* directly

#define HIDDEN __attribute__((visibility("hidden")))

// lib::Singleton<app::StageManager>::instance_ — holds StageManager*
// adrp 0x7105329000 + 0x9d8
extern "C" void* DAT_71053299d8 HIDDEN;

struct StageManagerData {
    u8   pad_0x00[0x110];
    void* entries[3];           // +0x110 (0x110, 0x118, 0x120)
    // +0x128: embedded stage info sub-object with own vtable
    // vtable[0] [inferred: get_stage_kind() → s32, used by multiple utility functions]
    // vtable[53] (0x1a8) [inferred: reverse screen enable/related]
    // vtable[54] (0x1b0) [inferred: reverse screen disable/related]
    void** stage_info_vt;       // +0x128 [derived: vtable ptr, proven by set_stage_disable_reverse_screen + check_ignore_geometry_move_power_stage]
    u8   pad_0x130[0x4c];       // +0x130 to +0x17c
    s32  mode;                  // +0x17c [derived: used in is_discretion_final_enabled_impl]
};

struct StageManager {
    StageManagerData* inner;    // +0x0
};

extern "C" void FUN_71026084c0(void*, bool);
extern "C" void FUN_71039c20a0(void*);

namespace app::lua_bind {

// 71021455a0 -- ldr x0,[x0]; and w1,w1,#0x1; b external
void StageManager__stage_all_stop_impl(StageManager* sm, bool val) {
    FUN_71026084c0(sm->inner, val);
}

// 71021455b0 -- load inner, check mode field at +0x17c
// mode == -1 → return true
// mode >= 3 (unsigned) → abort
// mode 0..2 → vtable call at index 0x4a0/8 of entry at inner + mode*8 + 0x110
bool StageManager__is_discretion_final_enabled_impl(StageManager* sm) {
    auto* inner = sm->inner;
    s32 mode = inner->mode;
    if (mode == -1) return true;
    if ((u32)mode >= 3u) {
        FUN_71039c20a0(sm);
        __builtin_unreachable();
    }
    auto* entry = inner->entries[(u32)mode];
    auto fn = reinterpret_cast<bool (*)(void*)>((*reinterpret_cast<void***>(entry))[0x4a0/8]);
    return fn(entry);
}

} // namespace app::lua_bind

// ---- Stage utility functions (non-lua_bind) --------------------------------

namespace app::FighterUtil {

// 0x710069a600 (44 bytes) — app::FighterUtil::set_stage_disable_reverse_screen
// Reads StageManager singleton, dispatches to stage info sub-object at +0x128.
// If disable=true: tail-calls vtable[54] (0x1b0); if false: vtable[53] (0x1a8)
// DAT_71053299d8 [derived: lib::Singleton<app::StageManager>::instance_, adrp+ldr at 0x7105329000+0x9d8]
// +0x128 [derived: embedded stage info vtable ptr, proven by disasm of this func + check_ignore_geometry_move_power_stage]
extern "C" void set_stage_disable_reverse_screen(bool disable) {
    u8* inner = *(u8**)DAT_71053299d8;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    if (disable) {
        reinterpret_cast<void(*)(void*)>(vt[0x1b0 / 8])(stage_info);
    } else {
        reinterpret_cast<void(*)(void*)>(vt[0x1a8 / 8])(stage_info);
    }
}

} // namespace app::FighterUtil

namespace app::GroundUtility {

// 0x71004681c0 (88 bytes) — app::GroundUtility::check_ignore_geometry_move_power_stage
// Checks if current stage kind is one that ignores geometry move power.
// Returns true for stage kinds 0xd1 and 0x113.
// DAT_71053299d8 [derived: StageManager singleton]
// +0x17c [derived: mode field, -1 = invalid, proven by is_discretion_final_enabled_impl]
// +0x128 vtable[0] [inferred: get_stage_kind() → s32]
extern "C" bool check_ignore_geometry_move_power_stage(void) {
    u8* sm = (u8*)DAT_71053299d8;
    if (!sm) return false;
    u8* inner = *(u8**)sm;
    if (*(s32*)(inner + 0x17c) == -1) return false;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    s32 kind = reinterpret_cast<s32(*)(void*)>(vt[0])(stage_info);
    if (kind == 0xd1) return true;
    if (kind == 0x113) return true;
    return false;
}

} // namespace app::GroundUtility

// ---- Stage query functions (leaf, no prologue) ----------------------------

// DAT_71052b7558 [inferred: stage geometry parameter singleton, holds flat-stage threshold]
extern "C" void* DAT_71052b7558 HIDDEN;
// DAT_7104471590 [inferred: .rodata float constant, flat-stage threshold angle or slope limit]
extern "C" float DAT_7104471590 HIDDEN;
// DAT_71052b7f00 [derived: camera/stage parameter singleton, holds camera range rects]
// Offsets: +0xc00 camera_range, +0xc20 camera_limit_range, +0xc40 shrinked_camera_range
extern "C" void* DAT_71052b7f00 HIDDEN;

// HFA return type for camera range (4 floats → s0-s3 in ABI)
struct CameraRect {
    float x0, y0, x1, y1;
};

namespace app::sv_information {

// 0x710227ebb0 (52 bytes) — app::sv_information::stage_id
// Leaf tail-call: reads StageManager singleton, gets stage kind via vtable[0].
// Returns -1 if singleton is null or mode is invalid.
// DAT_71053299d8 [derived: StageManager singleton]
// +0x17c [derived: mode field], +0x128 vtable[0] [inferred: get_stage_kind]
extern "C" s32 stage_id(void) {
    u8* sm = (u8*)DAT_71053299d8;
    if (!sm) return -1;
    u8* inner = *(u8**)sm;
    if (*(s32*)(inner + 0x17c) == -1) return -1;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    return reinterpret_cast<s32(*)(void*)>(vt[0])(stage_info);
}

} // namespace app::sv_information

namespace app::stage {

// 0x71015ce660 (48 bytes) — app::stage::is_flat_stage
// Leaf function: checks byte flag at singleton+0xc, then compares float at +0x8.
// DAT_71052b7558 [inferred: stage geometry parameter singleton]
// +0xc [inferred: non-flat override flag, u8 — if set, always return false]
// +0x8 [inferred: stage slope angle or geometry metric, float]
// DAT_7104471590 [inferred: flat threshold constant, float]
extern "C" bool is_flat_stage(void) {
    u8* p = (u8*)DAT_71052b7558;
    if (*(u8*)(p + 0xc) != 0) return false;
    float val = *(float*)(p + 0x8);
    return val < DAT_7104471590;
}

} // namespace app::stage

// ---- Camera range getters (leaf, HFA return) -------------------------------

namespace app::sv_information {

// 0x7102282ea0 (32 bytes) — app::sv_information::camera_range
// Leaf: returns 4 floats from camera parameter data at +0xc20..+0xc2c.
// DAT_71052b7f00 [derived: camera/stage parameter singleton]
// +0xc20..+0xc2c [inferred: camera limit range rect (left, top, right, bottom)]
extern "C" CameraRect camera_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    CameraRect r;
    r.x0 = *(float*)(inner + 0xc20);
    r.y0 = *(float*)(inner + 0xc24);
    r.x1 = *(float*)(inner + 0xc28);
    r.y1 = *(float*)(inner + 0xc2c);
    return r;
}

} // namespace app::sv_information

// ---- Camera range getters (leaf, NEON vector return in v0) -----------------
// NEON vector return type — 4 floats packed in v0
typedef float float4 __attribute__((vector_size(16)));

// 0x7101645a20 (44 bytes) — get_camera_range (flyandhand variant)
// Leaf: returns camera range rect as NEON float4 from +0xc00..+0xc0c
extern "C" float4 get_camera_range_7101645a20(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc00);
    r[1] = *(float*)(inner + 0xc04);
    r[2] = *(float*)(inner + 0xc08);
    r[3] = *(float*)(inner + 0xc0c);
    return r;
}

// 0x710164c1a0 (44 bytes) — get_camera_range (masterhand variant)
// Identical to flyandhand variant
extern "C" float4 get_camera_range_710164c1a0(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc00);
    r[1] = *(float*)(inner + 0xc04);
    r[2] = *(float*)(inner + 0xc08);
    r[3] = *(float*)(inner + 0xc0c);
    return r;
}

// 0x71015cb9b0 (44 bytes) — get_camera_limit_range
// Leaf: returns camera limit range rect from +0xc20..+0xc2c
extern "C" float4 get_camera_limit_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc20);
    r[1] = *(float*)(inner + 0xc24);
    r[2] = *(float*)(inner + 0xc28);
    r[3] = *(float*)(inner + 0xc2c);
    return r;
}

// 0x710164c200 (44 bytes) — get_shrinked_camera_range
// Leaf: returns shrinked camera range rect from +0xc40..+0xc4c
extern "C" float4 get_shrinked_camera_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc40);
    r[1] = *(float*)(inner + 0xc44);
    r[2] = *(float*)(inner + 0xc48);
    r[3] = *(float*)(inner + 0xc4c);
    return r;
}

// 0x7101651ad0 (44 bytes) — get_camera_range (crazyhand variant)
extern "C" float4 get_camera_range_7101651ad0(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc00);
    r[1] = *(float*)(inner + 0xc04);
    r[2] = *(float*)(inner + 0xc08);
    r[3] = *(float*)(inner + 0xc0c);
    return r;
}

// 0x7101651b30 (44 bytes) — get_shrinked_camera_range (crazyhand variant)
extern "C" float4 get_shrinked_camera_range_7101651b30(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc40);
    r[1] = *(float*)(inner + 0xc44);
    r[2] = *(float*)(inner + 0xc48);
    r[3] = *(float*)(inner + 0xc4c);
    return r;
}

// 0x71016545f0 (44 bytes) — get_camera_range (marx variant)
extern "C" float4 get_camera_range_71016545f0(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc00);
    r[1] = *(float*)(inner + 0xc04);
    r[2] = *(float*)(inner + 0xc08);
    r[3] = *(float*)(inner + 0xc0c);
    return r;
}

// 0x7101679050 (44 bytes) — get_camera_limit_range (solgaleo variant)
extern "C" float4 get_camera_limit_range_7101679050(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc20);
    r[1] = *(float*)(inner + 0xc24);
    r[2] = *(float*)(inner + 0xc28);
    r[3] = *(float*)(inner + 0xc2c);
    return r;
}
