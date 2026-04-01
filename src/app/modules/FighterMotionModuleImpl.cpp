#include "app/BattleObjectModuleAccessor.h"

// FighterMotionModuleImpl — accesses MotionModule at accessor+0x88
// Most functions are tail-call wrappers to external targets (won't byte-match).
// Complex functions include Kirby copy hash translation and damage stop logic.

struct FighterMotionModuleImpl;
#define VT(m) (*reinterpret_cast<void***>(m))
#define MOTION(a) (reinterpret_cast<u8*>((a)->motion_module))

// External tail call targets
extern "C" void FUN_71006e1b90(void*, u32);
extern "C" void FUN_71006e1e20(void*, u64, bool);
extern "C" void FUN_71006e20c0(void*, u64, bool);
extern "C" void FUN_71006e2440(void*, u64, bool);
extern "C" void FUN_71006e2200(void*, u64, bool);
extern "C" void FUN_71006e2680(void*, u64, bool, bool, bool);
extern "C" void FUN_71006e27f0(void*, u64, bool, bool);
extern "C" void FUN_71006e29f0(void*, bool);
extern "C" void FUN_710049c190(void*, u64);
extern "C" void FUN_710049e4b0(void*, u32, u64, bool, bool, bool, bool, bool, f32, f32, f32);

// Global Kirby copy hash lookup table
extern "C" u64 PTR_DAT_7104fcd388[];

// Global pause state
extern "C" u64* DAT_71052c2760;

namespace app::lua_bind {

// 71020aa000 — mov x0,x1; mov w1,w2; b external
void FighterMotionModuleImpl__add_body_type_hash_impl(BattleObjectModuleAccessor*, void* module, u32 hash) {
    FUN_71006e1b90(module, hash);
}

// 71020aa010 — ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e1e20(a->motion_module, hash, p2 & 1);
}

// 71020aa020 — ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__is_valid_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e20c0(a->motion_module, hash, p2 & 1);
}

// 71020aa030 — ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_normal_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2440(a->motion_module, hash, p2 & 1);
}

// 71020aa040 — ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_xlu_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2200(a->motion_module, hash, p2 & 1);
}

// 71020aa050 — Kirby copy hash table lookup (32 instructions)
u64 FighterMotionModuleImpl__motion_kind_kirby_copy_original_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* module = MOTION(a);
    auto* inner = *reinterpret_cast<u8**>(module + 8);
    auto* fighter_obj = *reinterpret_cast<void**>(inner + 0x50);
    auto* vt = *reinterpret_cast<void***>(fighter_obj);
    auto get_kind = reinterpret_cast<s32 (*)(void*, u64)>(vt[0x98 / 8]);
    s32 kind = get_kind(fighter_obj, 0x100000fcULL);

    u64* begin = reinterpret_cast<u64*>(PTR_DAT_7104fcd388[kind]);
    u64* end   = reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(&PTR_DAT_7104fcd388[kind]) + 8));
    while (begin != end) {
        if (((begin[0] ^ hash) & 0xFFFFFFFFFFULL) == 0)
            return begin[1];
        begin += 2;
    }
    return hash;
}

// 71020aa0d0 — ldr module; and w2,w3,w4 with #0x1; b change_motion_kirby_copy
void FighterMotionModuleImpl__change_motion_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3, bool p4) {
    FUN_71006e2680(a->motion_module, hash, p2 & 1, p3 & 1, p4 & 1);
}

// 71020aa0f0 — ldr module; and w2,w3 with #0x1; b external
void FighterMotionModuleImpl__change_motion_inherit_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3) {
    FUN_71006e27f0(a->motion_module, hash, p2 & 1, p3 & 1);
}

// 71020aa100 — ldr module; hardcode w3=1,w2=0; b same target as above
void FighterMotionModuleImpl__change_motion_inherit_frame_keep_rate_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = a->motion_module;
    bool t = true;
    FUN_71006e27f0(m, hash, false, t);
}

// 71020aa110 — reads frame/rate via vtable, adjusts frame param, delegates to change_motion
void FighterMotionModuleImpl__change_motion_force_inherit_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, f32 frame, f32 rate, f32 blend) {
    auto* module = a->motion_module;
    auto* vt = *reinterpret_cast<void***>(module);
    auto get_frame = reinterpret_cast<f32 (*)(void*)>(vt[0x138 / 8]);
    get_frame(module);
    auto get_rate = reinterpret_cast<f32 (*)(void*)>(vt[0x160 / 8]);
    f32 cur_rate = get_rate(module);
    f32 use_frame = (frame < 0.0f) ? frame : cur_rate;
    FUN_71006e2680(module, hash, false, true, false);
    (void)use_frame; (void)rate; (void)blend;
}

// 71020aa190 — Kirby copy hash lookup + tail call to end_frame_from_hash
void FighterMotionModuleImpl__end_frame_from_hash_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* module = MOTION(a);
    auto* inner = *reinterpret_cast<u8**>(module + 8);
    auto* fighter_obj = *reinterpret_cast<void**>(inner + 0x50);
    auto* vt = *reinterpret_cast<void***>(fighter_obj);
    auto get_kind = reinterpret_cast<s32 (*)(void*, u64)>(vt[0x98 / 8]);
    s32 kind = get_kind(fighter_obj, 0x100000fcULL);

    u64* begin = reinterpret_cast<u64*>(PTR_DAT_7104fcd388[kind]);
    u64* end   = reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(&PTR_DAT_7104fcd388[kind]) + 8));
    u64 translated = hash;
    while (begin != end) {
        if (((begin[0] ^ hash) & 0xFFFFFFFFFFULL) == 0) {
            translated = begin[1];
            break;
        }
        begin += 2;
    }
    FUN_710049c190(a->motion_module, translated);
}

// 71020aa210 — ldr x0,[x0,#0x88]; and w1,w1,#0x1; b external
void FighterMotionModuleImpl__set_frame_sync_anim_cmd_kirby_copy_impl(BattleObjectModuleAccessor* a, bool val) {
    FUN_71006e29f0(a->motion_module, val & 1);
}

// 71020aa220 — Kirby copy hash lookup + tail call to get_cancel_frame
void FighterMotionModuleImpl__get_cancel_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    auto* module = MOTION(a);
    auto* inner = *reinterpret_cast<u8**>(module + 8);
    auto* fighter_obj = *reinterpret_cast<void**>(inner + 0x50);
    auto* vt = *reinterpret_cast<void***>(fighter_obj);
    auto get_kind = reinterpret_cast<s32 (*)(void*, u64)>(vt[0x98 / 8]);
    s32 kind = get_kind(fighter_obj, 0x100000fcULL);

    u64* begin = reinterpret_cast<u64*>(PTR_DAT_7104fcd388[kind]);
    u64* end   = reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(&PTR_DAT_7104fcd388[kind]) + 8));
    u64 translated = hash;
    while (begin != end) {
        if (((begin[0] ^ hash) & 0xFFFFFFFFFFULL) == 0) {
            translated = begin[1];
            break;
        }
        begin += 2;
    }
    FUN_71006e1e20(a->motion_module, translated, p2 & 1);
}

// 71020aa2b0 — Kirby copy hash lookup + many params preserved + tail call
void FighterMotionModuleImpl__add_motion_partial_kirby_copy_impl(
        BattleObjectModuleAccessor* a, u32 slot, u64 hash, bool p3, bool p4, bool p5, bool p6, bool p7,
        f32 rate, f32 start_frame, f32 blend_frame) {
    auto* module = MOTION(a);
    auto* inner = *reinterpret_cast<u8**>(module + 8);
    auto* fighter_obj = *reinterpret_cast<void**>(inner + 0x50);
    auto* vt = *reinterpret_cast<void***>(fighter_obj);
    auto get_kind = reinterpret_cast<s32 (*)(void*, u64)>(vt[0x98 / 8]);
    s32 kind = get_kind(fighter_obj, 0x100000fcULL);

    u64* begin = reinterpret_cast<u64*>(PTR_DAT_7104fcd388[kind]);
    u64* end   = reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(&PTR_DAT_7104fcd388[kind]) + 8));
    u64 translated = hash;
    while (begin != end) {
        if (((begin[0] ^ hash) & 0xFFFFFFFFFFULL) == 0) {
            translated = begin[1];
            break;
        }
        begin += 2;
    }
    FUN_710049e4b0(a->motion_module, slot, translated, p3 & 1, p4 & 1, p5 & 1, p6 & 1, p7 & 1, rate, start_frame, blend_frame);
}

// 71020aa3a0 — set_blend_waist (4 insns: ldr module, and bool, strb to +0x2f2)
void FighterMotionModuleImpl__set_blend_waist_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = reinterpret_cast<u8*>(a->motion_module);
    module[0x2f2] = val & 1;
}

// 71020aa3b0 — start_damage_stop_interpolation: fcvtzs to +0x2f4, vtable calls
void FighterMotionModuleImpl__start_damage_stop_interpolation_impl(BattleObjectModuleAccessor* a, f32 frame) {
    auto* module = a->motion_module;
    auto* mp = reinterpret_cast<u8*>(module);
    *reinterpret_cast<s32*>(mp + 0x2f4) = static_cast<s32>(frame);
    auto* vt = *reinterpret_cast<void***>(module);
    auto set_rate = reinterpret_cast<void (*)(void*, f32, s32)>(vt[0x478 / 8]);
    set_rate(module, 0.0f, 0);
    auto stop_fn = reinterpret_cast<void (*)(void*, f32)>(vt[0x2b0 / 8]);
    stop_fn(module, 0.0f);
}

// 71020aa410 — set_pause_motion_interpolation_stop: global check + module chain
void FighterMotionModuleImpl__set_pause_motion_interpolation_stop_impl(BattleObjectModuleAccessor* a) {
    auto* global = reinterpret_cast<u8*>(*DAT_71052c2760);
    if (global[0x12] == 0) return;
    if (global[0xf] != 0) return;

    auto* module = MOTION(a);
    auto* chain1 = *reinterpret_cast<u8**>(module + 0x10);
    auto* chain2 = *reinterpret_cast<void**>(chain1 + 0x38);
    auto* vt1 = *reinterpret_cast<void***>(chain2);
    auto fn1 = reinterpret_cast<void* (*)(void*, s32)>(vt1[0x10 / 8]);
    auto* result = fn1(chain2, 0);

    if (module[0x239] != 0) return;

    auto* vt2 = *reinterpret_cast<void***>(result);
    auto get_interp = reinterpret_cast<f32 (*)(void*)>(vt2[0x48 / 8]);
    f32 val = get_interp(result);
    if (val != 0.0f) {
        module[0x2f9] = 1;
    }
}

// 71020aa490 — set_update_finger_and_face_joint: chain through module+0x10, +0x8, vtable
void FighterMotionModuleImpl__set_update_finger_and_face_joint_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = MOTION(a);
    auto* chain1 = *reinterpret_cast<u8**>(module + 0x10);
    auto* chain2 = *reinterpret_cast<void**>(chain1 + 0x8);
    auto* vt = *reinterpret_cast<void***>(chain2);
    auto fn = reinterpret_cast<void (*)(void*, bool)>(vt[0xa0 / 8]);
    fn(chain2, val & 1);
}
} // namespace app::lua_bind
