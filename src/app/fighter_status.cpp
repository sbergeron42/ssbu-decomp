#include "types.h"

// Fighter status and scripting utility functions — pool-c
// Range: 0x7102275xxx -- 0x7102284xxx
// Contains: sv_system, sv_information, sv_fighter_util,
//           sv_ground_collision_line, sv_camera_manager, sv_math

// ______ External functions ________________________________________

extern "C" double pow(double, double);
extern "C" float powf(float, float);
extern "C" void FUN_710067de90(void*, u64, s32, s32, u32);
extern "C" void FUN_710068e1c0(void*);  // get_item_lift_motion_rate_mul helper
extern "C" u64 FUN_71006798f0(void*, u32);  // owner_rank lookup on FighterManager
extern "C" [[noreturn]] void abort();
extern "C" void FUN_7100695b10(void*);  // FighterUtil::flash_eye_info
extern "C" void FUN_7100695070();       // curry face disable helper

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

// FighterManager singleton (adrp 0x71052b8000 + 0x4f8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b84f8;

// .rodata float constants for is_zero epsilon check
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104470f68;
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104471970;

// StageManager singleton (adrp 0x7105329000 + 0x9d8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_710532999d8;  // intentionally wrong name for unique symbol

// FighterParamAccessor2 singleton (adrp 0x71052bb000 + 0x3b0)
// [derived: get_default_fighter_param functions index into this]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;

// .rodata float constants for get_fov calculation
// [derived: get_fov multiplies by DAT_7104471fbc and divides by DAT_7104470d10]
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104471fbc;
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104470d10;

// GroundCollisionLine zero-constant pointer (adrp 0x71052a7000 + 0xa80)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052a7a80;

// ______ Struct/vector returns _____________________________________

// 4-float HFA for dead_range / camera_range returns
// [derived: disassembly returns in s0-s3 (HFA calling convention)]
struct Float4 {
    f32 a, b, c, d;
};

// 128-bit SIMD vector for functions that return via q0 register
// [derived: ldr q0,[x8,#offset]; ret pattern in camera accessors]
typedef float float4 __attribute__((vector_size(16)));

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
// Fighter status queries (FighterManager tail calls)
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_710067a5c0(void*);
extern "C" void FUN_710067a3a0(void*, s32);

// ── 0x71015cd530 -- app::fighter::is_absolutely_final_status (16B) ─
// [derived: tail call through FighterManager singleton to impl]
void is_absolutely_final_status_71015cd530() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067a5c0(mgr);
}

// ── 0x71015cd4d0 -- app::fighter::is_final_status_or_standby (20B) ─
// [derived: tail call with extra param w1=1]
void is_final_status_or_standby_71015cd4d0() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067a3a0(mgr, 1);
}

// ── 0x71015cdfe0 -- app::fighter::get_category (8B) ───────────────
// lsr w0,w0,#0x1c; ret — extracts top 4 bits (category nibble) from object ID
u32 get_category_71015cdfe0(u32 id) {
    return id >> 28;
}

// ════════════════════════════════════════════════════════════════════
// self_param accessors — dispatch through FighterParamAccessor singleton
// ════════════════════════════════════════════════════════════════════

// FighterParamAccessor singleton (adrp 0x71052c3000 + 0x1e0)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c31e0;

extern "C" f32 FUN_7101602a30(void*, s32, u64);
extern "C" s32 FUN_7101602b90(void*, s32, u64);
extern "C" u64 FUN_7101602da0(void*, s32, u64);

// ── 0x71015c4c10 -- self_param_float (20B) ────────────────────────
// [derived: loads singleton, shuffles params, tail calls float accessor]
f32 self_param_float_71015c4c10(s32 kind, u64 hash) {
    return FUN_7101602a30(DAT_71052c31e0, kind, hash);
}

// ── 0x71015c4c30 -- self_param_int (20B) ──────────────────────────
s32 self_param_int_71015c4c30(s32 kind, u64 hash) {
    return FUN_7101602b90(DAT_71052c31e0, kind, hash);
}

// ── 0x71015c4c50 -- self_param_hash (20B) ─────────────────────────
u64 self_param_hash_71015c4c50(s32 kind, u64 hash) {
    return FUN_7101602da0(DAT_71052c31e0, kind, hash);
}

// ════════════════════════════════════════════════════════════════════
// Bound/physics param accessors — all read from ParamAccessor+0x12d0 sub-object
// [derived: adrp+ldr DAT_71052bb3b0 → +0x12d0 → field offset]
// ════════════════════════════════════════════════════════════════════

// ParamAccessor singleton (adrp 0x71052bb000 + 0x3b0)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;

// ── 0x71016593a0 -- init_bound_frame (20B) ────────────────────────
u32 init_bound_frame_71016593a0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<u32*>(sub + 0x230);
}

// ── 0x71016593c0 -- special_lw_gravity (20B) ─────────────────────
f32 special_lw_gravity_71016593c0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x234);
}

// ── 0x71016593e0 -- special_lw_speed_y_max (20B) ─────────────────
f32 special_lw_speed_y_max_71016593e0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x238);
}

// ── 0x7101659400 -- length_gravity (20B) ──────────────────────────
f32 length_gravity_7101659400() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x240);
}

// ── 0x7101659420 -- length_speed_y_max (20B) ─────────────────────
f32 length_speed_y_max_7101659420() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x244);
}

// ── 0x7101659440 -- length_angle_x_velocity (20B) ────────────────
f32 length_angle_x_velocity_7101659440() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x260);
}

// ── 0x7101659460 -- length_angle_y_velocity (20B) ────────────────
f32 length_angle_y_velocity_7101659460() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x264);
}

// ── 0x7101659480 -- length_angle_z_velocity (20B) ────────────────
f32 length_angle_z_velocity_7101659480() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x268);
}

// ── 0x71016594a0 -- side_gravity (20B) ───────────────────────────
f32 side_gravity_71016594a0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x26c);
}

// ── 0x71016594c0 -- side_speed_y_max (20B) ───────────────────────
f32 side_speed_y_max_71016594c0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x270);
}

// ── 0x71016594e0 -- side_angle_x_velocity (20B) ──────────────────
f32 side_angle_x_velocity_71016594e0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x28c);
}

// ── 0x7101659500 -- side_angle_y_velocity (20B) ──────────────────
f32 side_angle_y_velocity_7101659500() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x290);
}

// ── 0x7101659520 -- side_angle_z_velocity (20B) ──────────────────
f32 side_angle_z_velocity_7101659520() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x294);
}

// ── 0x7101659560 -- flashing_frame_before_life_over (20B) ────────
u32 flashing_frame_before_life_over_7101659560() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<u32*>(sub + 0x2a4);
}

// ── 0x7101659580 -- rebound_speed_x_add (20B) ───────────────────
f32 rebound_speed_x_add_7101659580() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x2a8);
}

// ── 0x71016595a0 -- rebound_speed_y_add (20B) ───────────────────
f32 rebound_speed_y_add_71016595a0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<f32*>(sub + 0x2ac);
}

// ════════════════════════════════════════════════════════════════════
// Additional simple accessors (FighterManager / ItemManager)
// ════════════════════════════════════════════════════════════════════

// ── 0x71015ce620 -- is_ready_go (20B) ─────────────────────────────
// [derived: FighterManager deref → byte at +0xd2]
u8 is_ready_go_71015ce620() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(mgr) + 0xd2);
}

// ItemManager singleton (adrp 0x71052c3000 + 0x70)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c3070;

// ── 0x71015ca910 -- get_num_of_active_item (20B) ──────────────────
// [derived: ItemManager → inner array at +0x70 → indexed load by item kind]
u64 get_num_of_active_item_71015ca910(s32 idx) {
    u8* mgr = reinterpret_cast<u8*>(DAT_71052c3070);
    u64* arr = *reinterpret_cast<u64**>(mgr + 0x70);
    return arr[idx];
}

// ── 0x71015ca8f0 -- get_num_of_ownered_active_item (20B) ─────────
// [derived: param shuffle through ItemManager singleton, tail call]
extern "C" u64 FUN_71015dab40(void*, s32, u64);

u64 get_num_of_ownered_active_item_71015ca8f0(s32 kind, u64 param) {
    return FUN_71015dab40(DAT_71052c3070, kind, param);
}

// ════════════════════════════════════════════════════════════════════
// Tail-call thunks (8B each — set extra param and forward)
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_710160e690(void*, u64, s32);
extern "C" void FUN_71015c8ee0(void*, u64, s32);

// ── 0x71015c3060 -- get_assist_respawn_position (8B) ──────────────
// mov w2,#1; b target
void get_assist_respawn_position_71015c3060(void* p0, u64 p1) {
    FUN_710160e690(p0, p1, 1);
}

// ── 0x71015c8ed0 -- create_weapon (8B) ────────────────────────────
// mov w2,#-1; b target
void create_weapon_71015c8ed0(void* p0, u64 p1) {
    FUN_71015c8ee0(p0, p1, -1);
}

// ════════════════════════════════════════════════════════════════════
// Item/weapon param accessors — ParamAccessor+0x13b0 sub-object
// [derived: adrp+ldr DAT_71052bb3b0 → +0x13b0 → field at offset]
// ════════════════════════════════════════════════════════════════════

// ── 0x7101669000 -- ignition (20B) ───────────────────────────────
f32 ignition_7101669000() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x75c);
}

// ── 0x7101669020 -- flashing_frame_before_life_over (20B) ────────
u32 flashing_frame_before_life_over_7101669020(void) {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x760);
}

// ── 0x7101669060 -- lost (20B) ───────────────────────────────────
u32 lost_7101669060() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x768);
}

// ── 0x71016690a0 -- gravity_accel (20B) ──────────────────────────
f32 gravity_accel_71016690a0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x770);
}

// ── 0x71016690c0 -- gravity_accel_max (20B) ──────────────────────
f32 gravity_accel_max_71016690c0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x774);
}

// ── 0x71016690e0 -- gravity_frame (20B) ──────────────────────────
u32 gravity_frame_71016690e0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x778);
}

// ── 0x7101669100 -- flashing_frame_before_life (20B) ─────────────
u32 flashing_frame_before_life_7101669100() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x77c);
}

// ── 0x710166e110 -- flash_start_frame (20B) ──────────────────────
u32 flash_start_frame_710166e110() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x51c);
}

// ── 0x710166e190 -- camera_range_damag_mul_start_rate (20B) ──────
f32 camera_range_damag_mul_start_rate_710166e190() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x530);
}

// ── 0x710166e1b0 -- camera_range_damag_mul_end_rate (20B) ────────
f32 camera_range_damag_mul_end_rate_710166e1b0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x534);
}

// ── 0x710166e1d0 -- camera_range_damag_mul_min (20B) ─────────────
f32 camera_range_damag_mul_min_710166e1d0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x538);
}

// ── 0x710166e1f0 -- camera_range_damag_mul_max (20B) ─────────────
f32 camera_range_damag_mul_max_710166e1f0() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<f32*>(sub + 0x53c);
}

// ── 0x710166e210 -- generate_continuous_forbid_frame (20B) ───────
u32 generate_continuous_forbid_frame_710166e210() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x540);
}

// ── 0x710166e250 -- jostle_touch_ground_frame (20B) ──────────────
u32 jostle_touch_ground_frame_710166e250() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x554);
}

// ── 0x710166e270 -- jostle_up_touch_ground_frame (20B) ───────────
u32 jostle_up_touch_ground_frame_710166e270() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x13b0);
    return *reinterpret_cast<u32*>(sub + 0x55c);
}

// ── Other ParamAccessor sub-objects ──────────────────────────────

// ── 0x710166f720 -- POWERESA_SHAPE_TYPE (20B) ───────────────────
// [derived: ParamAccessor+0xc78 sub-object → u32 at +0x3a0]
u32 POWERESA_SHAPE_TYPE_710166f720() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0xc78);
    return *reinterpret_cast<u32*>(sub + 0x3a0);
}

// ── 0x710166fc60 -- get_energy_max_frame (20B) ──────────────────
// [derived: ParamAccessor+0x50 sub-object → f32 at +0xefc]
f32 get_energy_max_frame_710166fc60() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x50);
    return *reinterpret_cast<f32*>(sub + 0xefc);
}

// ── 0x710165d480 -- EXPLOSIONBOMB_WIRE_ROT_SPEED (20B) ──────────
// [derived: ParamAccessor+0x3f0 sub-object → u32 at +0x120]
u32 EXPLOSIONBOMB_WIRE_ROT_SPEED_710165d480() {
    u8* sub = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x3f0);
    return *reinterpret_cast<u32*>(sub + 0x120);
}

// ════════════════════════════════════════════════════════════════════
// check_stat_* — AI/item status bit-field accessors
// All read from scripting context *(L-8)+0x168, then extract a single
// bit from a flags byte. [derived: consistent pattern across 28 functions]
// ════════════════════════════════════════════════════════════════════

// Helper: read the AI stat module from lua state
#define STAT_MODULE(L) \
    (*reinterpret_cast<u8**>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8) + 0x168))

// -- Flags byte at +0x54 --

// ── 0x71003612f0 -- check_stat_air (20B) ─────────────────────────
// ldr w8,[x8,#0x54]; and w0,w8,#1 — bit 0 via 32-bit load
u32 check_stat_air_71003612f0(void* L) {
    u8* mod = STAT_MODULE(L);
    return *reinterpret_cast<u32*>(mod + 0x54) & 1;
}

// ── 0x7100361310 -- check_stat_build_max (20B) ───────────────────
u32 check_stat_build_max_7100361310(void* L) {
    return (STAT_MODULE(L)[0x54] >> 2) & 1;
}

// ── 0x7100361330 -- check_stat_build_up (20B) ────────────────────
u32 check_stat_build_up_7100361330(void* L) {
    return (STAT_MODULE(L)[0x54] >> 3) & 1;
}

// ── 0x7100361370 -- check_stat_attention (20B) ───────────────────
u32 check_stat_attention_7100361370(void* L) {
    return (STAT_MODULE(L)[0x54] >> 6) & 1;
}

// -- Flags byte at +0x55 --

// ── 0x71003613b0 -- check_stat_final_act (20B) ──────────────────
u32 check_stat_final_act_71003613b0(void* L) {
    return (STAT_MODULE(L)[0x55] >> 1) & 1;
}

// ── 0x71003613d0 -- check_stat_invincible (20B) ─────────────────
u32 check_stat_invincible_71003613d0(void* L) {
    return (STAT_MODULE(L)[0x55] >> 5) & 1;
}

// -- Flags byte at +0x56 --

// ── 0x7100361470 -- check_stat_sp_dir (20B) ─────────────────────
u32 check_stat_sp_dir_7100361470(void* L) {
    return (STAT_MODULE(L)[0x56] >> 4) & 1;
}

// ── 0x7100361490 -- check_stat_unguarded_hind (20B) ─────────────
u32 check_stat_unguarded_hind_7100361490(void* L) {
    return (STAT_MODULE(L)[0x56] >> 5) & 1;
}

// ── 0x71003614b0 -- check_stat_unguarded (20B) ──────────────────
u32 check_stat_unguarded_71003614b0(void* L) {
    return (STAT_MODULE(L)[0x56] >> 6) & 1;
}

// -- Flags word/byte at +0x58 --

// ── 0x71003617a0 -- check_stat_touch_u (20B) ────────────────────
u32 check_stat_touch_u_71003617a0(void* L) {
    return (STAT_MODULE(L)[0x58] >> 2) & 1;
}

// ── 0x71003617c0 -- check_stat_touch_l (20B) ────────────────────
// ldr w8,[x8,#0x58]; and w0,w8,#1 — bit 0 via 32-bit load
u32 check_stat_touch_l_71003617c0(void* L) {
    u8* mod = STAT_MODULE(L);
    return *reinterpret_cast<u32*>(mod + 0x58) & 1;
}

// ── 0x71003617e0 -- check_stat_touch_r (20B) ────────────────────
u32 check_stat_touch_r_71003617e0(void* L) {
    return (STAT_MODULE(L)[0x58] >> 1) & 1;
}

// ── 0x7100361800 -- check_stat_cannot_catch_cliff (20B) ──────────
u32 check_stat_cannot_catch_cliff_7100361800(void* L) {
    return (STAT_MODULE(L)[0x58] >> 4) & 1;
}

// ── 0x7100361820 -- check_stat_dive (20B) ────────────────────────
u32 check_stat_dive_7100361820(void* L) {
    return (STAT_MODULE(L)[0x58] >> 5) & 1;
}

// -- Flags byte at +0x59 --

// ── 0x7100361840 -- check_stat_unable_cliff_xlu (20B) ───────────
u32 check_stat_unable_cliff_xlu_7100361840(void* L) {
    return (STAT_MODULE(L)[0x59] >> 1) & 1;
}

// ── 0x7100361860 -- check_stat_unable_escape_air (20B) ──────────
u32 check_stat_unable_escape_air_7100361860(void* L) {
    return (STAT_MODULE(L)[0x59] >> 2) & 1;
}

// ── 0x71003618a0 -- check_stat_unable_special (20B) ─────────────
u32 check_stat_unable_special_71003618a0(void* L) {
    return (STAT_MODULE(L)[0x59] >> 4) & 1;
}

// ── 0x71003618c0 -- check_stat_unable_jump (20B) ────────────────
u32 check_stat_unable_jump_71003618c0(void* L) {
    return (STAT_MODULE(L)[0x59] >> 5) & 1;
}

// ── 0x71003618e0 -- check_stat_unable_shield (20B) ──────────────
u32 check_stat_unable_shield_71003618e0(void* L) {
    return (STAT_MODULE(L)[0x59] >> 6) & 1;
}

// -- Flags word/byte at +0x5c --

// ── 0x7100361900 -- check_stat_have (20B) ────────────────────────
// ldr w8,[x8,#0x5c]; and w0,w8,#1 — bit 0 via 32-bit load
u32 check_stat_have_7100361900(void* L) {
    u8* mod = STAT_MODULE(L);
    return *reinterpret_cast<u32*>(mod + 0x5c) & 1;
}

// ── 0x7100361920 -- check_stat_put_bomb (20B) ───────────────────
u32 check_stat_put_bomb_7100361920(void* L) {
    return (STAT_MODULE(L)[0x5c] >> 1) & 1;
}

// ── 0x7100361940 -- check_stat_can_use_superleaf (20B) ──────────
u32 check_stat_can_use_superleaf_7100361940(void* L) {
    return (STAT_MODULE(L)[0x5c] >> 4) & 1;
}

// ── 0x7100361960 -- check_stat_can_use_rocketbelt (20B) ─────────
u32 check_stat_can_use_rocketbelt_7100361960(void* L) {
    return (STAT_MODULE(L)[0x5c] >> 5) & 1;
}

// -- Flags byte at +0x5d --

// ── 0x7100361980 -- check_stat_have_throw (20B) ─────────────────
u32 check_stat_have_throw_7100361980(void* L) {
    return (STAT_MODULE(L)[0x5d] >> 4) & 1;
}

// ── 0x71003619a0 -- check_stat_have_shoot (20B) ─────────────────
u32 check_stat_have_shoot_71003619a0(void* L) {
    return (STAT_MODULE(L)[0x5d] >> 5) & 1;
}

// ── 0x71003619c0 -- check_stat_have_swing (20B) ─────────────────
u32 check_stat_have_swing_71003619c0(void* L) {
    return (STAT_MODULE(L)[0x5d] >> 6) & 1;
}

// -- Flags byte at +0x60 --

// ── 0x71003619e0 -- check_stat_dogs_blind_own (20B) ─────────────
u32 check_stat_dogs_blind_own_71003619e0(void* L) {
    return (STAT_MODULE(L)[0x60] >> 4) & 1;
}

// ── 0x7100361a00 -- check_stat_target_invisible (20B) ───────────
u32 check_stat_target_invisible_7100361a00(void* L) {
    return (STAT_MODULE(L)[0x60] >> 6) & 1;
}

// -- Float accessor --

// ── 0x7100361b70 -- shield_rate (20B) ────────────────────────────
// ldp s0,s1,[x8,#0xe8]; fdiv s0,s0,s1 — ratio of two floats
// [derived: current shield / max shield from AI stat module]
f32 shield_rate_7100361b70(void* L) {
    u8* mod = STAT_MODULE(L);
    f32 cur = *reinterpret_cast<f32*>(mod + 0xe8);
    f32 max = *reinterpret_cast<f32*>(mod + 0xec);
    return cur / max;
}

// ════════════════════════════════════════════════════════════════════
// AI stat module — simple float/int field reads (16B each)
// Same *(L-8)+0x168 module, but direct field loads (no bit extraction)
// ════════════════════════════════════════════════════════════════════

// ── 0x7100361b90 -- damage_reaction_mul (16B) ────────────────────
f32 damage_reaction_mul_7100361b90(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xfc); }

// ── 0x7100361bb0 -- height (16B) ────────────────────────────────
f32 height_7100361bb0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xc8); }

// ── 0x7100361bc0 -- pos_x (16B) ─────────────────────────────────
f32 pos_x_7100361bc0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x80); }

// ── 0x7100361bd0 -- pos_y (16B) ─────────────────────────────────
f32 pos_y_7100361bd0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x84); }

// ── 0x7100361be0 -- speed_x (16B) ───────────────────────────────
f32 speed_x_7100361be0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xa0); }

// ── 0x7100361bf0 -- speed_y (16B) ───────────────────────────────
f32 speed_y_7100361bf0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xa4); }

// ── 0x7100361c00 -- scale (16B) ─────────────────────────────────
f32 scale_7100361c00(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xc0); }

// ── 0x7100361c50 -- motion_rate (16B) ───────────────────────────
f32 motion_rate_7100361c50(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x50); }

// ── 0x7100361d00 -- damage (16B) ────────────────────────────────
f32 damage_7100361d00(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xe0); }

// ── 0x7100361d10 -- hp (16B) ────────────────────────────────────
f32 hp_7100361d10(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xe4); }

// ── 0x7100361d20 -- lr (16B) ────────────────────────────────────
f32 lr_7100361d20(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0xc4); }

// ════════════════════════════════════════════════════════════════════
// AI stat module — tail-call dispatchers (20B each)
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_7100358c20(void*, s32);

// ── 0x7100361ce0 -- is_sp_u_available (20B) ─────────────────────
// [derived: loads stat module, tail-calls with param 0]
void is_sp_u_available_7100361ce0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    void* mod = *reinterpret_cast<void**>(ctx + 0x168);
    FUN_7100358c20(mod, 0);
}

// ── 0x7100361cf0 -- is_sp_u_weaken_available (20B) ──────────────
void is_sp_u_weaken_available_7100361cf0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    void* mod = *reinterpret_cast<void**>(ctx + 0x168);
    FUN_7100358c20(mod, 1);
}

// ════════════════════════════════════════════════════════════════════
// More stat module accessors (fighter param reads)
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b9e0 -- jump_g_mul (16B) ────────────────────────────
f32 jump_g_mul_710036b9e0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x204); }

// ── 0x710036b9f0 -- jump_g (16B) ───────────────────────────────
f32 jump_g_710036b9f0(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x218); }

// ── 0x710036ba00 -- fall_speed_y_max (16B) ──────────────────────
f32 fall_speed_y_max_710036ba00(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x228); }

// ── 0x710036ba10 -- dive_speed_y_max (16B) ──────────────────────
f32 dive_speed_y_max_710036ba10(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x22c); }

// ── 0x710036ba70 -- escape_air_cancel_frame (16B) ───────────────
f32 escape_air_cancel_frame_710036ba70(void* L) { return *reinterpret_cast<f32*>(STAT_MODULE(L) + 0x234); }

#undef STAT_MODULE

// ════════════════════════════════════════════════════════════════════
// Global singleton reads / misc 16B accessors
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b3d0 -- scroll_x (16B) ─────────────────────────────
// [derived: BattleObjectWorld singleton → f32 at +0x20]
f32 scroll_x_710036b3d0() {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(DAT_71052b7558) + 0x20);
}

// ── 0x71003681d0 -- set_no_return_frame (16B) ───────────────────
// ldur x8,[x0,#-8]; neg w9,w1; strh w9,[x8,#0xc7c]; ret
// [derived: writes negated value as s16 to scripting context +0xc7c]
void set_no_return_frame_71003681d0(void* L, s32 val) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    *reinterpret_cast<s16*>(ctx + 0xc7c) = (s16)(-val);
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
// sv_camera_manager — q0-return accessors (128-bit SIMD vector return)
// ════════════════════════════════════════════════════════════════════

// ── 0x7102283240 -- app::sv_camera_manager::get_pos (20B) ─────────
// [derived: returns camera position as 128-bit vector from manager+0xd30]
float4 get_pos_7102283240() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(mgr) + 0xd30);
}

// ── 0x7102283260 -- app::sv_camera_manager::get_target (20B) ──────
// [derived: returns camera target as 128-bit vector from manager+0xd20]
float4 get_target_7102283260() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(mgr) + 0xd20);
}

// ── 0x7102283280 -- app::sv_camera_manager::get_internal_pos (20B) ─
// [derived: returns internal camera position from manager+0xec0]
float4 get_internal_pos_7102283280() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(mgr) + 0xec0);
}

// ── 0x71022832a0 -- app::sv_camera_manager::get_internal_target (20B)
// [derived: returns internal camera target from manager+0xeb0]
float4 get_internal_target_71022832a0() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(mgr) + 0xeb0);
}

// ════════════════════════════════════════════════════════════════════
// sv_camera_manager — HFA struct accessors (s0-s3 return)
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

// ════════════════════════════════════════════════════════════════════
// sv_math — vector math utilities (NEON-accelerated by compiler)
// ════════════════════════════════════════════════════════════════════

// ── 0x7102275a20 -- app::sv_math::is_zero (40B) ───────────────────
// fcmp s0,epsilon_neg; cset gt; fcmp s0,epsilon_pos; cset mi; and
// [derived: returns true if value is between negative and positive epsilon]
bool is_zero_7102275a20(f32 v) {
    return (v > DAT_7104470f68) & (v < DAT_7104471970);
}

// ── 0x7102275ad0 -- app::sv_math::vec2_length_square (24B) ────────
// movi v2,#0; mov lanes; fmul v0.4S; faddp v0.2S
// [derived: squared magnitude of 2D vector]
f32 vec2_length_square_7102275ad0(f32 x, f32 y) {
    float4 v = {x, y, 0.0f, 0.0f};
    v = v * v;
    return v[0] + v[1];
}

// ── 0x7102275a50 -- app::sv_math::vec2_is_zero (44B) ──────────────
// fcmeq v0.4S,v2.4S,#0; ext; and; tst; cset
// [derived: true if both x and y are exactly 0.0]
bool vec2_is_zero_7102275a50(f32 x, f32 y) {
    float4 v = {x, y, 0.0f, 0.0f};
    float4 zero = {0.0f, 0.0f, 0.0f, 0.0f};
    return v[0] == zero[0] && v[1] == zero[1];
}

// ── 0x7102275d10 -- app::sv_math::vec2_dot (36B) ──────────────────
// movi; mov lanes; fmul v0.4S; faddp v0.2S
// [derived: dot product of two 2D vectors]
f32 vec2_dot_7102275d10(f32 x, f32 y, f32 a, f32 b) {
    float4 v1 = {x, y, 0.0f, 0.0f};
    float4 v2 = {a, b, 0.0f, 0.0f};
    float4 m = v1 * v2;
    return m[0] + m[1];
}

// ── 0x7102275da0 -- app::sv_math::vec3_is_zero (48B) ──────────────
// fcmeq v0.4S,v3.4S,#0; ext; and; tst; cset
// [derived: true if all three components are exactly 0.0]
bool vec3_is_zero_7102275da0(f32 x, f32 y, f32 z) {
    float4 v = {x, y, z, 0.0f};
    float4 zero = {0.0f, 0.0f, 0.0f, 0.0f};
    return v[0] == zero[0] && v[1] == zero[1] && v[2] == zero[2];
}

// ── 0x7102275dd0 -- app::sv_math::vec3_length (44B) ───────────────
// fmul v0.4S; ext; fadd; faddp; fsqrt v0.4S
// [derived: magnitude of 3D vector]
f32 vec3_length_7102275dd0(f32 x, f32 y, f32 z) {
    float4 v = {x, y, z, 0.0f};
    float4 sq = v * v;
    f32 sum = sq[0] + sq[1] + sq[2];
    return __builtin_sqrtf(sum);
}

// ── 0x7102275e00 -- app::sv_math::vec3_length_square (36B) ────────
// fmul v0.4S; ext; fadd; faddp
// [derived: squared magnitude of 3D vector]
f32 vec3_length_square_7102275e00(f32 x, f32 y, f32 z) {
    float4 v = {x, y, z, 0.0f};
    float4 sq = v * v;
    return sq[0] + sq[1] + sq[2];
}

// ── 0x7102275e30 -- app::sv_math::vec3_dot (52B) ──────────────────
// fmul; ext; fadd; faddp (same pattern as vec3_length_square but with two vectors)
// [derived: dot product of two 3D vectors]
f32 vec3_dot_7102275e30(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    float4 a = {x1, y1, z1, 0.0f};
    float4 b = {x2, y2, z2, 0.0f};
    float4 m = a * b;
    return m[0] + m[1] + m[2];
}

// ── 0x7102275f50 -- app::sv_math::vec3_distance (64B) ─────────────
// fsub; fmul; ext; fadd; faddp; fsqrt
// [derived: Euclidean distance between two 3D points]
f32 vec3_distance_7102275f50(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    float4 a = {x1, y1, z1, 0.0f};
    float4 b = {x2, y2, z2, 0.0f};
    float4 d = a - b;
    float4 sq = d * d;
    return __builtin_sqrtf(sq[0] + sq[1] + sq[2]);
}

// ── 0x7102275f90 -- app::sv_math::vec3_lerp (44B) ─────────────────
// fsub v1.4S; fmla v0.4S,v1.4S,v6.S[0]
// [derived: linear interpolation between two 3D points by factor t]
float4 vec3_lerp_7102275f90(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 t) {
    float4 a = {x1, y1, z1, 0.0f};
    float4 b = {x2, y2, z2, 0.0f};
    return a + (b - a) * t;
}

// ── 0x7102275cd0 -- app::sv_math::vec2_reflection (52B) ───────────
// fmul; faddp (dot); fmla pattern
// [derived: reflects direction vector across normal: N - 2*dot(D,N)*D]
float4 vec2_reflection_7102275cd0(f32 dx, f32 dy, f32 nx, f32 ny) {
    f32 dot = dx * nx + dy * ny;
    f32 scale = dot + dot;
    float4 r = {nx - dx * scale, ny - dy * scale, 0.0f - 0.0f * scale, 0.0f - 0.0f * scale};
    return r;
}

// ── 0x7102275a80 -- app::sv_math::vec2_length (68B) ───────────────
// fmul; faddp; frsqrte; frsqrts (x2 Newton-Raphson); fcmeq; bic
// [derived: length of 2D vector using reciprocal sqrt approximation]
f32 vec2_length_7102275a80(f32 x, f32 y) {
    float4 v = {x, y, 0.0f, 0.0f};
    float4 sq = v * v;
    return __builtin_sqrtf(sq[0] + sq[1]);
}

// ════════════════════════════════════════════════════════════════════
// sv_information — stage and game state queries
// ════════════════════════════════════════════════════════════════════

// ── 0x7102282290 -- app::sv_fighter_util::get_world_move_seed (24B) ─
// ldr d0,[BattleObjectWorld+0x20]; movi d1,#0; mov v0.D[1],v1.D[0]
// [derived: returns u64 seed from BattleObjectWorld singleton at +0x20]
u64 get_world_move_seed_7102282290() {
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(DAT_71052b7558) + 0x20);
}

// ── 0x710227ece0 -- app::sv_information::is_stage_can_dead_back (28B)
// [derived: tail-calls vtable[0x31] on StageManager sub-object at +0x128]
u64 is_stage_can_dead_back_710227ece0() {
    void* instance = *reinterpret_cast<void**>(DAT_710532999d8);
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*)>(vt[0x188 / 8])(sub);
}

// ── 0x710227eca0 -- app::sv_information::is_stage_can_dead_front (60B)
// [derived: checks FighterManager+0xc0 != 0x20 first, then vtable[0x30] on stage]
u64 is_stage_can_dead_front_710227eca0() {
    void* fm = *reinterpret_cast<void**>(DAT_71052b84f8);
    if (*reinterpret_cast<s8*>(reinterpret_cast<u8*>(fm) + 0xc0) == 0x20) {
        return 0;
    }
    void* instance = *reinterpret_cast<void**>(DAT_710532999d8);
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*)>(vt[0x180 / 8])(sub);
}

// ── 0x71022846d0 -- app::sv_stage::is_horizontal_reverse_enabled (28B)
// [derived: tail-calls vtable[0x33] on StageManager sub-object at +0x128]
u64 is_horizontal_reverse_enabled_71022846d0() {
    void* instance = *reinterpret_cast<void**>(DAT_710532999d8);
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*)>(vt[0x198 / 8])(sub);
}

// ── 0x71022846f0 -- app::sv_stage::is_vertical_reverse_enabled (28B)
// [derived: tail-calls vtable[0x34] on StageManager sub-object at +0x128]
u64 is_vertical_reverse_enabled_71022846f0() {
    void* instance = *reinterpret_cast<void**>(DAT_710532999d8);
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*)>(vt[0x1a0 / 8])(sub);
}

// ── 0x710227ebb0 -- app::sv_information::stage_id (52B) ───────────
// [derived: checks StageManager not null, +0x17c != -1, then vtable[0] on +0x128]
u64 stage_id_710227ebb0() {
    void** mgr_ptr = reinterpret_cast<void**>(DAT_710532999d8);
    if (mgr_ptr == nullptr) return 0xffffffff;
    void* instance = *mgr_ptr;
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(instance) + 0x17c) == -1) {
        return 0xffffffff;
    }
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*)>(vt[0])(sub);
}

// ════════════════════════════════════════════════════════════════════
// sv_fighter_util — fighter parameter queries
// ════════════════════════════════════════════════════════════════════

// ── 0x71022820f0 -- app::sv_fighter_util::get_item_lift_motion_rate_mul (28B)
// ldur x8,[x0,#-8]; ldr x0,[x8,#0x1a0]; bl FUN_710068e1c0
// [derived: gets module accessor from lua state, calls helper]
void get_item_lift_motion_rate_mul_71022820f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    FUN_710068e1c0(acc);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// ── 0x7102282700 -- app::sv_fighter_util::get_kirifuda_position (28B)
// [derived: tail-calls vtable[0xF] on StageManager sub-object at +0x128]
u64 get_kirifuda_position_7102282700(void* L, s32 param) {
    void* instance = *reinterpret_cast<void**>(DAT_710532999d8);
    void* sub = reinterpret_cast<void*>(reinterpret_cast<u8*>(instance) + 0x128);
    void** vt = *reinterpret_cast<void***>(sub);
    return reinterpret_cast<u64(*)(void*, s32)>(vt[0x78 / 8])(sub, param);
}

// ════════════════════════════════════════════════════════════════════
// sv_camera_manager — FOV accessor
// ════════════════════════════════════════════════════════════════════

// ── 0x7102282ec0 -- app::sv_camera_manager::get_fov (44B) ────────
// ldr s0,[mgr+0xdac]; fmul s0,s0,rodata; fdiv s0,s0,rodata
// [derived: camera FOV converted from internal units]
f32 get_fov_7102282ec0() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b7f00);
    f32 raw = *reinterpret_cast<f32*>(reinterpret_cast<u8*>(mgr) + 0xdac);
    return (raw * DAT_7104471fbc) / DAT_7104470d10;
}

// ════════════════════════════════════════════════════════════════════
// sv_ground_collision_line — collision geometry accessors
// ════════════════════════════════════════════════════════════════════

// ── 0x7102284910 -- app::sv_ground_collision_line::get_normal (28B) ─
// [derived: returns float4 normal vector from collision line+0xa0, or zero]
float4 get_normal_7102284910(void* line) {
    float4* zero = reinterpret_cast<float4*>(DAT_71052a7a80);
    if (line != nullptr) {
        return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(line) + 0xa0);
    }
    return *zero;
}

// ── 0x7102284a50 -- app::sv_ground_collision_line::get_left_pos (52B)
// [derived: returns position from left vertex pointer at +0x88, offset +0x10]
float4 get_left_pos_7102284a50(void* line) {
    if (line != nullptr) {
        void* left = *reinterpret_cast<void**>(reinterpret_cast<u8*>(line) + 0x88);
        if (left != nullptr) {
            return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(left) + 0x10);
        }
    }
    return *reinterpret_cast<float4*>(DAT_71052a7a80);
}

// ── 0x7102284a90 -- app::sv_ground_collision_line::get_right_pos (52B)
// [derived: returns position from right vertex pointer at +0x90, offset +0x10]
float4 get_right_pos_7102284a90(void* line) {
    if (line != nullptr) {
        void* right = *reinterpret_cast<void**>(reinterpret_cast<u8*>(line) + 0x90);
        if (right != nullptr) {
            return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(right) + 0x10);
        }
    }
    return *reinterpret_cast<float4*>(DAT_71052a7a80);
}

// ════════════════════════════════════════════════════════════════════
// Helper: get entry_id from lua state via WorkModule vtable
// Pattern: acc->work_module->vt[0x13](wm, 0x10000000)
// ════════════════════════════════════════════════════════════════════

static inline u32 get_entry_id_from_lua(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* wm = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x50);
    void** vt = *reinterpret_cast<void***>(wm);
    return reinterpret_cast<u32(*)(void*, u32)>(vt[0x98 / 8])(wm, 0x10000000);
}

// Helper: get FighterInformation sub-struct from entry_id
static inline void* get_fighter_info(u32 entry_id) {
    void* fm = *reinterpret_cast<void**>(DAT_71052b84f8);
    void* fi = *reinterpret_cast<void**>(
        reinterpret_cast<u8*>(fm) + static_cast<s32>(entry_id) * 8 + 0x20);
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(fi) + 0xf8);
}

// ════════════════════════════════════════════════════════════════════
// sv_information / sv_fighter_util — FighterInformation field accessors
// All follow: get_entry_id → bounds check → FighterManager lookup → read field
// ════════════════════════════════════════════════════════════════════

// ── 0x710227ed00 -- app::sv_information::is_dead_up_force_crush (84B)
// [derived: reads byte at FighterInformation+0xf8 sub-struct +0x6e]
u8 is_dead_up_force_crush_710227ed00(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    if (eid >= 8) abort();
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(get_fighter_info(eid)) + 0x6e);
}

// ── 0x710227ef00 -- app::sv_information::sleep_time_mul (84B) ─────
// [derived: reads f32 at FighterInformation sub-struct +0x384]
f32 sleep_time_mul_710227ef00(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    if (eid >= 8) abort();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(get_fighter_info(eid)) + 0x384);
}

// ── 0x7102281890 -- app::sv_fighter_util::get_dead_up_star_fall_prob (84B)
// [derived: reads u32 at FighterInformation sub-struct +0x7c]
u32 get_dead_up_star_fall_prob_7102281890(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    if (eid >= 8) abort();
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(get_fighter_info(eid)) + 0x7c);
}

// ── 0x71022818f0 -- app::sv_fighter_util::get_dead_up_camera_hit_prob (84B)
// [derived: reads u32 at FighterInformation sub-struct +0x80]
u32 get_dead_up_camera_hit_prob_71022818f0(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    if (eid >= 8) abort();
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(get_fighter_info(eid)) + 0x80);
}

// ── 0x710227eea0 -- app::sv_information::owner_rank (88B) ────────
// [derived: checks FighterManager+0xcd flag, calls FUN_71006798f0 if set]
u64 owner_rank_710227eea0(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    void* fm = *reinterpret_cast<void**>(DAT_71052b84f8);
    if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(fm) + 0xcd) != 0) {
        return FUN_71006798f0(fm, eid);
    }
    return 0;
}

// ── 0x710227ee30 -- app::sv_information::owner_handi (104B) ──────
// [derived: bounds check + FM flag check, reads f32 at +0x370]
f32 owner_handi_710227ee30(void* L) {
    u32 eid = get_entry_id_from_lua(L);
    if (eid >= 8) abort();
    void* fm = *reinterpret_cast<void**>(DAT_71052b84f8);
    if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(fm) + 0xcd) != 0) {
        void* info = *reinterpret_cast<void**>(
            reinterpret_cast<u8*>(fm) + static_cast<s32>(eid) * 8 + 0x20);
        void* sub = *reinterpret_cast<void**>(reinterpret_cast<u8*>(info) + 0xf8);
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(sub) + 0x370);
    }
    return 0.0f;
}

// ════════════════════════════════════════════════════════════════════
// sv_fighter_util — default fighter param accessors
// Pattern: kind < 0x5e → index through FighterParamAccessor2
// ════════════════════════════════════════════════════════════════════

// ── 0x71022822b0 -- get_default_fighter_param_walk_speed_max (72B) ─
// [derived: reads f32 at param_base + index*0x628 + 0x10]
f32 get_default_fighter_param_walk_speed_max_71022822b0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 kind = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x198);
    if (kind >= 0x5e) abort();
    u8* accessor = reinterpret_cast<u8*>(DAT_71052bb3b0);
    s32 idx = *reinterpret_cast<s32*>(accessor + static_cast<s32>(kind) * 0xc + 0x14f0);
    void* data_ptr = *reinterpret_cast<void**>(accessor);
    void* param_base = *reinterpret_cast<void**>(reinterpret_cast<u8*>(data_ptr) + 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(param_base) + idx * 0x628 + 0x10);
}

// ── 0x7102282300 -- get_default_fighter_param_ground_brake (72B) ──
// [derived: reads f32 at param_base + index*0x628 + 0x20]
f32 get_default_fighter_param_ground_brake_7102282300(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 kind = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x198);
    if (kind >= 0x5e) abort();
    u8* accessor = reinterpret_cast<u8*>(DAT_71052bb3b0);
    s32 idx = *reinterpret_cast<s32*>(accessor + static_cast<s32>(kind) * 0xc + 0x14f0);
    void* data_ptr = *reinterpret_cast<void**>(accessor);
    void* param_base = *reinterpret_cast<void**>(reinterpret_cast<u8*>(data_ptr) + 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(param_base) + idx * 0x628 + 0x20);
}

// ── 0x7102282370 -- get_default_fighter_param_air_brake_x (72B) ──
// [derived: reads f32 at param_base + index*0x628 + 0x64]
f32 get_default_fighter_param_air_brake_x_7102282370(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 kind = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x198);
    if (kind >= 0x5e) abort();
    u8* accessor = reinterpret_cast<u8*>(DAT_71052bb3b0);
    s32 idx = *reinterpret_cast<s32*>(accessor + static_cast<s32>(kind) * 0xc + 0x14f0);
    void* data_ptr = *reinterpret_cast<void**>(accessor);
    void* param_base = *reinterpret_cast<void**>(reinterpret_cast<u8*>(data_ptr) + 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(param_base) + idx * 0x628 + 0x64);
}

// ════════════════════════════════════════════════════════════════════
// sv_animcmd — ACMD command functions
// Pattern: module vtable call + lua stack pop
// ════════════════════════════════════════════════════════════════════

// ── 0x71022a9a00 -- app::sv_animcmd::REVERSE_LR (104B) ──────────
// [derived: PostureModule->vt[0x18](posture) — flips facing direction]
void REVERSE_LR_71022a9a00(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* posture = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x38);
    void** vt = *reinterpret_cast<void***>(posture);
    reinterpret_cast<void(*)(void*)>(vt[0xc0 / 8])(posture);
    // pop lua stack
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022a9ae0 -- app::sv_animcmd::UPDATE_ROT (104B) ──────────
// [derived: PostureModule->vt[0x20](posture) — updates rotation]
void UPDATE_ROT_71022a9ae0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* posture = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x38);
    void** vt = *reinterpret_cast<void***>(posture);
    reinterpret_cast<void(*)(void*)>(vt[0x100 / 8])(posture);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022a9a70 -- app::sv_animcmd::STICK_LR (108B) ────────────
// [derived: PostureModule->vt[0x2f](posture, 0) — stick-based LR]
void STICK_LR_71022a9a70(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* posture = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x38);
    void** vt = *reinterpret_cast<void***>(posture);
    reinterpret_cast<void(*)(void*, s32)>(vt[0x178 / 8])(posture, 0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022aa4e0 -- app::sv_animcmd::HIT_RESET_ALL (108B) ───────
// [derived: CollisionModule(+0xb0)->vt[0x11](collision, 0) — resets all hitboxes]
void HIT_RESET_ALL_71022aa4e0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* collision = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0xb0);
    void** vt = *reinterpret_cast<void***>(collision);
    reinterpret_cast<void(*)(void*, s32)>(vt[0x88 / 8])(collision, 0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022ac050 -- app::sv_animcmd::CAM_ZOOM_OUT (108B) ─────────
// [derived: CameraModule(+0x60)->vt[0x1f](camera, 0) — zoom out camera]
void CAM_ZOOM_OUT_71022ac050(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* camera = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60);
    void** vt = *reinterpret_cast<void***>(camera);
    reinterpret_cast<void(*)(void*, s32)>(vt[0xf8 / 8])(camera, 0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022a2870 -- app::sv_animcmd::COL_NORMAL (128B) ──────────
// [derived: ColorBlendModule(+0x70) → get flag via vt[0x2e], set via vt[0xc]]
void COL_NORMAL_71022a2870(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* cb = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x70);
    void** vt = *reinterpret_cast<void***>(cb);
    u32 flag = reinterpret_cast<u32(*)(void*)>(vt[0x170 / 8])(cb);
    reinterpret_cast<void(*)(void*, u32)>(vt[0x60 / 8])(cb, flag & 1);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022a28f0 -- app::sv_animcmd::BURN_COLOR_NORMAL (128B) ───
// [derived: ColorBlendModule(+0x70) → get flag via vt[0x2e], set burn via vt[0x14]]
void BURN_COLOR_NORMAL_71022a28f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* cb = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x70);
    void** vt = *reinterpret_cast<void***>(cb);
    u32 flag = reinterpret_cast<u32(*)(void*)>(vt[0x170 / 8])(cb);
    reinterpret_cast<void(*)(void*, u32)>(vt[0xa0 / 8])(cb, flag & 1);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022a9b50 -- app::sv_animcmd::SET_AIR (132B) ─────────────
// [derived: StatusModule(+0x40)->vt[0x2f](status,2,0); GroundModule(+0x58)->vt[0x2a](ground,5)]
void SET_AIR_71022a9b50(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* status = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x40);
    void** svt = *reinterpret_cast<void***>(status);
    reinterpret_cast<void(*)(void*, s32, s32)>(svt[0x178 / 8])(status, 2, 0);
    void* ground = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x58);
    void** gvt = *reinterpret_cast<void***>(ground);
    reinterpret_cast<void(*)(void*, s32)>(gvt[0x150 / 8])(ground, 5);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022b0f80 -- app::sv_animcmd::START_INFO_FLASH_EYE (92B) ─
// [derived: calls FighterUtil::flash_eye_info(acc) + pop lua stack]
void START_INFO_FLASH_EYE_71022b0f80(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    FUN_7100695b10(acc);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022b4e10 -- app::sv_animcmd::GET_VOICE_REGION (92B) ─────
// [derived: pop lua stack, then SoundModule(+0x148)->vt[0x52](sound)]
void GET_VOICE_REGION_71022b4e10(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    void* sound = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x148);
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x290 / 8])(sound);
}

// ── 0x71022b4e70 -- app::sv_animcmd::GET_VOICE_REGION_NEW (92B) ──
// [derived: pop lua stack, then SoundModule(+0x148)->vt[0x53](sound)]
void GET_VOICE_REGION_NEW_71022b4e70(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    void* sound = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x148);
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x298 / 8])(sound);
}

// ── 0x71022b4ed0 -- app::sv_animcmd::GET_VOICE_VARIATION (92B) ───
// [derived: pop lua stack, then SoundModule(+0x148)->vt[0x54](sound)]
void GET_VOICE_VARIATION_71022b4ed0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    void* sound = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x148);
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x2a0 / 8])(sound);
}

// ── 0x71022b3490 -- app::sv_animcmd::FT_DISABLE_CURRY_FACE (104B) ─
// [derived: sets StatusModule(+0x40)+0x11a = 1, calls helper, pop stack]
void FT_DISABLE_CURRY_FACE_71022b3490(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0);
    void* status = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x40);
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(status) + 0x11a) = 1;
    FUN_7100695070();
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
}

// ── 0x71022ad810 -- app::sv_animcmd::IS_MENU (140B) ─────────────
// [derived: pop stack, check ctx+0x19c for player entry, look up fighter info]
u32 IS_MENU_71022ad810(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    u32 entry = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x19c);
    if (entry != 0xffffffff) {
        if (entry >= 8) abort();
        void* fm = *reinterpret_cast<void**>(DAT_71052b84f8);
        void* fi = *reinterpret_cast<void**>(
            reinterpret_cast<u8*>(fm) + static_cast<s32>(entry) * 8 + 0x20);
        if (fi != nullptr) {
            void* sub = *reinterpret_cast<void**>(reinterpret_cast<u8*>(fi) + 0xf8);
            if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(sub) + 0x94) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
