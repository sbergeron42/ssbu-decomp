#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// pool-b: Types-first HARD tier — CaptureModule/CatchModule/GrabModule related functions
// and AI accessor functions in the same domain.

using app::BattleObjectModuleAccessor;

// ---------------------------------------------------------------------------
// 0x7101658cc0  8B  is_enable_capture_bossgalaga — always enabled
// ---------------------------------------------------------------------------
u32 is_enable_capture_bossgalaga_1658cc0(BattleObjectModuleAccessor* acc) {
    return 1;
}

// ---------------------------------------------------------------------------
// 0x7100361570  24B  check_stat_catch — AI: status kind == 0xc (catch)
// Pointer chain: *(L - 8) → +0x168 → +0x74 == 12
// ---------------------------------------------------------------------------
bool check_stat_catch_361570(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x74) == 0xc;
}

// ---------------------------------------------------------------------------
// 0x7100361800  20B  check_stat_cannot_catch_cliff — AI: cliff catch flag bit 4
// Pointer chain: *(L - 8) → +0x168 → byte[0x58] bit 4
// ---------------------------------------------------------------------------
u8 check_stat_cannot_catch_cliff_361800(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return (obj[0x58] >> 4) & 1;
}

// ---------------------------------------------------------------------------
// 0x7100375f20  40B  has_air_catch — bitmask check for tether grab fighters
// Bitmask 0x82020100043 indexed by (FighterKind - 3)
// ---------------------------------------------------------------------------
u32 has_air_catch_375f20(u32 kind) {
    u32 idx = kind - 3;
    u32 bit = (u32)(0x82020100043ULL >> idx) & 1;
    return (idx < 0x2c) ? bit : 0;
}

// ---------------------------------------------------------------------------
// 0x71016433a0  44B  is_enable_capture_baitocrane — posture check <= 1.0
// Uses PostureModule (+0x38) vtable[0x118/8] which returns float
// ---------------------------------------------------------------------------
bool is_enable_capture_baitocrane_16433a0(BattleObjectModuleAccessor* acc) {
    void** vt = *reinterpret_cast<void***>(acc->posture_module);
    f32 val = reinterpret_cast<f32(*)(void*)>(vt[0x118 / 8])(acc->posture_module);
    return val <= 1.0f;
}

// ---------------------------------------------------------------------------
// 0x710164b0b0  96B  is_enable_capture — WorkModule flag check
// If flag 0x20000028 set → 0; else → !flag(0x20000029)
// Uses WorkModule (+0x50) vtable[0x108/8] (is_flag)
// ---------------------------------------------------------------------------
u32 is_enable_capture_164b0b0(BattleObjectModuleAccessor* acc) {
    void* wm = acc->work_module;
    void** vt = *reinterpret_cast<void***>(wm);
    u32 flag = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000028);
    u32 result;
#ifdef MATCHING_HACK_NX_CLANG
    if (!(flag & 1)) goto do_else;
    result = 0;
    goto done;
do_else:
    vt = *reinterpret_cast<void***>(wm);
    result = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000029);
    result = result ^ 1;
done:
#else
    if (flag & 1) {
        result = 0;
    } else {
        vt = *reinterpret_cast<void***>(wm);
        result = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000029);
        result = result ^ 1;
    }
#endif
    return result & 1;
}

// ---------------------------------------------------------------------------
// 0x7101655fb0  96B  is_enable_capture_beetle — same logic as is_enable_capture
// Uses WorkModule (+0x50) vtable[0x108/8] (is_flag)
// ---------------------------------------------------------------------------
u32 is_enable_capture_beetle_1655fb0(BattleObjectModuleAccessor* acc) {
    void* wm = acc->work_module;
    void** vt = *reinterpret_cast<void***>(wm);
    u32 flag = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000028);
    u32 result;
#ifdef MATCHING_HACK_NX_CLANG
    if (!(flag & 1)) goto do_else2;
    result = 0;
    goto done2;
do_else2:
    vt = *reinterpret_cast<void***>(wm);
    result = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000029);
    result = result ^ 1;
done2:
#else
    if (flag & 1) {
        result = 0;
    } else {
        vt = *reinterpret_cast<void***>(wm);
        result = reinterpret_cast<u32(*)(void*, u32)>(vt[0x108 / 8])(wm, 0x20000029);
        result = result ^ 1;
    }
#endif
    return result & 1;
}

// ===== AI accessor functions (leaf, pointer-chain field reads) =====
// Pattern: *(L - 8) → field or *(L - 8) → +0x168 → field
// All are lua_State* callbacks that read FighterInformation state.

// ---------------------------------------------------------------------------
// 0x7100361280  12B  cp_type — read byte field at +0xc08
// ---------------------------------------------------------------------------
u8 cp_type_361280(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0xc08];
}

// ---------------------------------------------------------------------------
// 0x7100361290  12B  cp_flag — read u16 field at +0xc12
// ---------------------------------------------------------------------------
u16 cp_flag_361290(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u16*>(inner + 0xc12);
}

// ---------------------------------------------------------------------------
// 0x71003612a0  12B  cp_slide_type — read byte field at +0xc10
// ---------------------------------------------------------------------------
u8 cp_slide_type_3612a0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0xc10];
}

// ---------------------------------------------------------------------------
// 0x71003612b0  12B  act_id — read u16 field at +0x198
// ---------------------------------------------------------------------------
u16 act_id_3612b0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u16*>(inner + 0x198);
}

// ---------------------------------------------------------------------------
// 0x71003612d0  16B  uniq_stat — read s32 via chain +0x168 → +0x74
// ---------------------------------------------------------------------------
s32 uniq_stat_3612d0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x74);
}

// ---------------------------------------------------------------------------
// 0x7100361c20  16B  prev_status_kind — read s32 via chain +0x168 → +0x30
// ---------------------------------------------------------------------------
s32 prev_status_kind_361c20(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x30);
}

// ---------------------------------------------------------------------------
// 0x7100361c40  16B  motion_frame — read f32 via chain +0x168 → +0x48
// ---------------------------------------------------------------------------
f32 motion_frame_361c40(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x48);
}

// ---------------------------------------------------------------------------
// 0x7100361c60  16B  motion_cancel_frame — read f32 via chain +0x168 → +0x4c
// ---------------------------------------------------------------------------
f32 motion_cancel_frame_361c60(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x4c);
}

// ---------------------------------------------------------------------------
// 0x71003665b0  16B  weapon_pos_x — read f32 via chain +0x168 → +0x1d0
// ---------------------------------------------------------------------------
f32 weapon_pos_x_3665b0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x1d0);
}

// ---------------------------------------------------------------------------
// 0x71003665c0  16B  weapon_pos_y — read f32 via chain +0x168 → +0x1d4
// ---------------------------------------------------------------------------
f32 weapon_pos_y_3665c0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x1d4);
}

// ---------------------------------------------------------------------------
// 0x71003665d0  16B  weapon_speed_x — read f32 via chain +0x168 → +0x1e0
// ---------------------------------------------------------------------------
f32 weapon_speed_x_3665d0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x1e0);
}

// ---------------------------------------------------------------------------
// 0x71003665e0  16B  weapon_speed_y — read f32 via chain +0x168 → +0x1e4
// ---------------------------------------------------------------------------
f32 weapon_speed_y_3665e0(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<f32*>(obj + 0x1e4);
}

// ---------------------------------------------------------------------------
// 0x7100361270  16B  rank — read s32 at +0xc0c, convert to float
// ---------------------------------------------------------------------------
f32 rank_361270(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return static_cast<f32>(*reinterpret_cast<s32*>(inner + 0xc0c));
}

// ---------------------------------------------------------------------------
// 0x7100361d40  16B  customize_s — read s32 via chain +0x168 → +0x23c
// ---------------------------------------------------------------------------
s32 customize_s_361d40(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x23c);
}

// ---------------------------------------------------------------------------
// 0x7100361d50  16B  customize_hi — read s32 via chain +0x168 → +0x240
// ---------------------------------------------------------------------------
s32 customize_hi_361d50(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x240);
}

// ---------------------------------------------------------------------------
// 0x7100361d60  16B  customize_lw — read s32 via chain +0x168 → +0x244
// ---------------------------------------------------------------------------
s32 customize_lw_361d60(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* obj = *reinterpret_cast<u8**>(inner + 0x168);
    return *reinterpret_cast<s32*>(obj + 0x244);
}

// ---------------------------------------------------------------------------
// 0x7100368100  12B  is_offensive_on_strategy — read byte at +0xcb9
// ---------------------------------------------------------------------------
u8 is_offensive_on_strategy_368100(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0xcb9];
}

// ---------------------------------------------------------------------------
// 0x7100368110  12B  is_defensive_on_strategy — read byte at +0xcba
// ---------------------------------------------------------------------------
u8 is_defensive_on_strategy_368110(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0xcba];
}

// ---------------------------------------------------------------------------
// 0x7100368120  12B  press_frame — read byte at +0x2b8
// ---------------------------------------------------------------------------
u8 press_frame_368120(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0x2b8];
}

// ---------------------------------------------------------------------------
// 0x7100368130  12B  push_wait — read byte at +0x2b9
// ---------------------------------------------------------------------------
u8 push_wait_368130(void* L) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    return inner[0x2b9];
}
