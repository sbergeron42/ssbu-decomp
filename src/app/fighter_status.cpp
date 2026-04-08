#include "types.h"

// Fighter status and scripting utility functions — pool-c
// Range: 0x7102275xxx -- 0x7102284xxx
// Contains: sv_system, sv_information, sv_fighter_util,
//           sv_ground_collision_line, sv_camera_manager, sv_math

// ______ External functions ________________________________________

extern "C" double pow(double, double);
extern "C" float powf(float, float);

// ______ External data ____________________________________________

// BattleObjectSlow singleton (adrp 0x71052b7000 + 0x550)
// [derived: slow_rate_impl reads *(instance + 4) as f32]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7550;

// BattleObjectWorld singleton (adrp 0x71052b7000 + 0x558)
// [derived: get_world_move_seed reads *(instance + 0x20) as u64]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7558;

// Battle scene manager pointer-to-pointer (adrp 0x71052b7000 + 0xf00)
// [inferred: double-deref gives object with camera (+0xd20/d30),
//  dead range (+0xc20/c30), lock-down (+0xc95), fov (+0xdac)]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7f00;

// Global frame counter (adrp 0x710523c000 + 0x4)
// [derived: get_delta_frame loads u32 and ucvtf to float]
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710523c004;

// ______ Struct returns ___________________________________________

// 4-float HFA for dead_range / camera_range returns
// [derived: disassembly returns in s0-s3 (HFA calling convention)]
struct Float4 {
    f32 a, b, c, d;
};

// ════════════════════════════════════════════════════════════════════
// sv_math — scalar math utilities
// ════════════════════════════════════════════════════════════════════

// ── 0x7102276130 -- app::sv_math::powf (4B) ────────────────────────
// b powf — direct tail-call thunk
float powf_7102276130(float base, float exp) {
    return powf(base, exp);
}

// ── 0x7102276350 -- app::sv_math::pow (32B) ────────────────────────
// scvtf d1,w0; fcvt d0,s0; bl pow; fcvt s0,d0
// [derived: converts float base + int exponent to doubles, calls libm pow]
float pow_7102276350(float base, s32 exp) {
    return (float)pow((double)base, (double)exp);
}

// ════════════════════════════════════════════════════════════════════
// sv_system — lua state field accessors
// These read fields from the scripting context struct at *(L - 8)
// ════════════════════════════════════════════════════════════════════

// ── 0x710227dae0 -- app::sv_system::battle_object (12B) ────────────
// ldur x8,[x0,#-8]; ldr x0,[x8,#0x1a8]; ret
// [derived: +0x1a8 in scripting context = BattleObject pointer]
u64 battle_object_710227dae0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(ctx) + 0x1a8);
}

// ── 0x710227daf0 -- app::sv_system::battle_object_module_accessor (12B)
// ldur x8,[x0,#-8]; ldr x0,[x8,#0x1a0]; ret
// [derived: +0x1a0 in scripting context = BattleObjectModuleAccessor*]
u64 battle_object_module_accessor_710227daf0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(ctx) + 0x1a0);
}

// ── 0x710227db00 -- app::sv_system::battle_object_category (12B) ───
// ldur x8,[x0,#-8]; ldrb w0,[x8,#0x194]; ret
// [derived: +0x194 byte = object category enum]
u8 battle_object_category_710227db00(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x194);
}

// ── 0x710227db10 -- app::sv_system::battle_object_kind (12B) ───────
// ldur x8,[x0,#-8]; ldr w0,[x8,#0x198]; ret
// [derived: +0x198 u32 = object kind (fighter/item/weapon ID)]
u32 battle_object_kind_710227db10(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x198);
}

// ════════════════════════════════════════════════════════════════════
// sv_information — global state accessors
// ════════════════════════════════════════════════════════════════════

// ── 0x710227ec90 -- app::sv_information::dead_up_type (8B) ─────────
// mov w0,wzr; ret — always returns 0 (stub/default)
s32 dead_up_type_710227ec90() {
    return 0;
}

// ── 0x710227ef60 -- app::sv_information::slow_rate (16B) ──────────
// [derived: BattleObjectSlow singleton, f32 at offset +4 is the slow rate]
f32 slow_rate_710227ef60() {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(DAT_71052b7550) + 4);
}

// ── 0x710227ef70 -- app::sv_information::get_delta_frame (16B) ────
// [derived: global u32 frame counter converted to float via ucvtf]
f32 get_delta_frame_710227ef70() {
    return (f32)DAT_710523c004;
}

// ── 0x710227ed60 -- app::sv_information::is_disable_lock_down (20B)─
// [derived: double-deref global → byte at offset +0xc95]
u8 is_disable_lock_down_710227ed60() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(mgr) + 0xc95);
}

// ════════════════════════════════════════════════════════════════════
// sv_fighter_util — stub/legacy functions
// ════════════════════════════════════════════════════════════════════

// ── 0x71022821a0 -- app::sv_fighter_util::get_walk_speed_mul (8B) ──
// fmov s0,#1.0; ret — always returns 1.0 (no walk speed modifier)
f32 get_walk_speed_mul_71022821a0() {
    return 1.0f;
}

// ── 0x7102282800 -- app::sv_fighter_util::is_free_move_rot_legacy (8B)
// mov w0,wzr; ret — always returns false (legacy path disabled)
s32 is_free_move_rot_legacy_7102282800() {
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// sv_ground_collision_line — collision line property accessors
// ════════════════════════════════════════════════════════════════════

// ── 0x7102284ad0 -- app::sv_ground_collision_line::get_attribute_flags (12B)
// cbz x0,ret; ldr w0,[x0,#0xc4]; ret
// [derived: GroundCollisionLine+0xc4 holds attribute bitmask]
u32 get_attribute_flags_7102284ad0(void* line) {
    if (!line) return 0;
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(line) + 0xc4);
}

// ── 0x7102284a30 -- app::sv_ground_collision_line::is_floor_passable (24B)
// [derived: bit 11 (0x800) = has passable flag, bit 13 = passable value]
u32 is_floor_passable_7102284a30(void* line) {
    if (!line) return 0;
    u32 flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(line) + 0xc4);
    u32 passable = (flags >> 13) & 1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(passable));
    asm("" : "+r"(flags));
#endif
    return (flags & 0x800) ? passable : 0;
}

// ════════════════════════════════════════════════════════════════════
// sv_item — item utility functions
// ════════════════════════════════════════════════════════════════════

// BossManager singleton (adrp 0x71052b7000 + 0xef8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7ef8;

// ── 0x7102284580 -- app::sv_item::is_boss_stop (40B) ──────────────
// [derived: BossManager singleton → inner ptr at +8 → s32 at +0x164 > 0]
bool is_boss_stop_7102284580() {
    void* boss = DAT_71052b7ef8;
    if (!boss) return false;
    void* inner = *reinterpret_cast<void**>(reinterpret_cast<u8*>(boss) + 8);
    s32 val = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(inner) + 0x164);
    return val > 0;
}

// ════════════════════════════════════════════════════════════════════
// FighterManager lua_bind impls
// ════════════════════════════════════════════════════════════════════

// ── 0x7102141200 -- FighterManager::set_cursor_whole_impl (16B) ───
// ldr x8,[x0]; and w9,w1,#1; strb w9,[x8,#0xd6]; ret
// [derived: writes masked bool to FighterManager inner object +0xd6]
void set_cursor_whole_impl_7102141200(void* mgr, u32 val) {
    void* inner = *reinterpret_cast<void**>(mgr);
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(inner) + 0xd6) = (u8)(val & 1);
}

// ════════════════════════════════════════════════════════════════════
// FighterMotionModuleImpl lua_bind impls
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_71006e27f0(void*, u64, s32, s32);

// ── 0x71020aa100 -- FighterMotionModuleImpl::change_motion_inherit_frame_keep_rate_kirby_copy_impl (16B)
// ldr x0,[x0,#0x88]; mov w3,#1; mov w2,wzr; b FUN_71006e27f0
// [derived: accessor+0x88 = MotionModule, tail-calls change_motion variant with (mod, param, 0, 1)]
void change_motion_impl_71020aa100(void* acc, u64 param) {
    void* mod = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x88);
    FUN_71006e27f0(mod, param, 0, 1);
}

// ════════════════════════════════════════════════════════════════════
// ACMD scripting utilities
// ════════════════════════════════════════════════════════════════════

// ── 0x71022b5150 -- app::sv_animcmd::is_excute (48B) ──────────────
// Pushes a boolean (byte at script_ctx+0x1b8 → +8) onto the Lua stack
// [derived: reads ACMD execution flag from scripting context]
s32 is_excute_71022b5150(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* script = *reinterpret_cast<u8**>(ctx + 0x1b8);
    u32 val = *reinterpret_cast<u8*>(script + 8);

    u8* top = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) + 0x10);
    *reinterpret_cast<u32*>(top) = val;
    *reinterpret_cast<u32*>(top + 8) = 1;

    top = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) + 0x10);
    *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;

    return 1;
}

// ── 0x71022b5360 -- app::sv_animcmd::execute (48B) ────────────────
// Sets the ACMD execution flag if the current frame (rounded up to 16) >= threshold
// [derived: reads frame from anim_info+0x20, compares with float param]
void execute_71022b5360(void* L, f32 frame) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* anim = *reinterpret_cast<u8**>(ctx + 0x1b0);
    s32 cur = *reinterpret_cast<s32*>(anim + 0x20);
    s32 rounded = (cur + 15) & ~15;
    // [derived: fmov s1,w9 — raw bitcast, not scvtf conversion]
    f32 rounded_f;
    __builtin_memcpy(&rounded_f, &rounded, sizeof(f32));
    if (rounded_f >= frame) {
        u8* script = *reinterpret_cast<u8**>(ctx + 0x1b8);
        *reinterpret_cast<u8*>(script + 8) = 1;
    }
}

// ── 0x71022b5390 -- app::sv_animcmd::frame_clear (16B) ────────────
// [derived: clears frame counter at anim_info+0x20]
void frame_clear_71022b5390(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* anim = *reinterpret_cast<u8**>(ctx + 0x1b0);
    *reinterpret_cast<u32*>(anim + 0x20) = 0;
}

// ── 0x71022b0190 -- app::sv_animcmd::RUMBLE_DUMMY (56B) ──────────
// Clears the Lua stack down to ci->base (pop all arguments)
// [derived: standard Lua stack cleanup pattern seen across ACMD functions]
void RUMBLE_DUMMY_71022b0190(void* L) {
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 target = ci_base + 0x10;
    while (top < target) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = target;
}

// ════════════════════════════════════════════════════════════════════
// sv_camera_manager — camera/dead range accessors
// These return 4-float HFA structs from the battle scene manager
// ════════════════════════════════════════════════════════════════════

// ── 0x7102282810 -- app::sv_camera_manager::dead_range (32B) ──────
// [derived: offsets +0xc30..+0xc3c are dead zone boundaries (4 floats)]
Float4 dead_range_7102282810() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    u8* base = reinterpret_cast<u8*>(mgr);
    Float4 r;
    r.a = *reinterpret_cast<f32*>(base + 0xc30);
    r.b = *reinterpret_cast<f32*>(base + 0xc34);
    r.c = *reinterpret_cast<f32*>(base + 0xc38);
    r.d = *reinterpret_cast<f32*>(base + 0xc3c);
    return r;
}

// ── 0x7102282ea0 -- app::sv_camera_manager::camera_range (32B) ────
// [derived: offsets +0xc20..+0xc2c are camera boundary limits (4 floats)]
Float4 camera_range_7102282ea0() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    u8* base = reinterpret_cast<u8*>(mgr);
    Float4 r;
    r.a = *reinterpret_cast<f32*>(base + 0xc20);
    r.b = *reinterpret_cast<f32*>(base + 0xc24);
    r.c = *reinterpret_cast<f32*>(base + 0xc28);
    r.d = *reinterpret_cast<f32*>(base + 0xc2c);
    return r;
}
