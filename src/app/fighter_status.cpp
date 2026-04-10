#include "types.h"
#include "app/BossManager.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/FighterManager.h"
#include "app/FighterInformation.h"
#include "app/modules/StatusModule.h"
#include "app/modules/WorkModule.h"
#include "app/modules/MotionModule.h"
#include "app/modules/PostureModule.h"
#include "app/modules/GroundModule.h"
#include "app/modules/CameraModule.h"
#include "app/modules/ColorBlendModule.h"
#include "app/modules/SoundModule.h"
#include "app/modules/HitModule.h"
#include "app/modules/KineticModule.h"
#include "app/modules/AttackModule.h"
#include "app/modules/ControlModule.h"
#include "app/placeholders/FighterAI.h"

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
extern "C" [[noreturn]] void abortWrapper_71039c20a0();
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

// ── 0x7102276140 -- app::sv_math::bezier_curve (80B) ────────────────
// [derived: cubic Bezier B(t) = (1-t)³p0 + 3(1-t)²t·p1 + 3(1-t)t²·p2 + t³·p3]
float bezier_curve_7102276140(float p0, float p1, float p2, float p3, float t) {
    float u = 1.0f - t;
    return u * u * u * p0 +
           u * t * 3.0f * u * p1 +
           t * t * t * p3 +
           u * t * 3.0f * t * p2;
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

// ── 0x7100361350 -- check_stat_gorogoro (32B) ───────────────────
// [derived: bits 5+17 of +0x54 u32 — gorogoro (rolling) multi-flag check]
bool check_stat_gorogoro_7100361350(void* L) {
    u8* mod = STAT_MODULE(L);
    return (*reinterpret_cast<u32*>(mod + 0x54) & 0x80020) != 0;
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

// ── 0x71003613f0 -- check_stat_invincible_l (92B) ───────────────
// [derived: extended invincible check — invincible flag + level/status checks]
// +0x55 bit5: invincible base flag
// +0x5e bit4: invincible-L override flag
// +0x11c (s32): invincible level counter
// +0x74 (s32): status kind — 0x11/0x12 = special invincible, 0xb = another
bool check_stat_invincible_l_71003613f0(void* L) {
    u8* mod = STAT_MODULE(L);
    if (((mod[0x55] >> 5) & 1) == 0) return false;
    if (((mod[0x5e] >> 4) & 1) != 0) return true;
    if (*reinterpret_cast<s32*>(mod + 0x11c) > 0) return true;
    s32 status = *reinterpret_cast<s32*>(mod + 0x74);
    return (u32)(status - 0x11) < 2 || status == 0xb;
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

// ════════════════════════════════════════════════════════════════════
// ai::line_segment_check family — ground/wall ray casts for AI pathing
// All load stat_module base pos, compute start + rel vector,
// call FUN_71003029b0 with a collision-type bitmask.
// FighterAIManager singleton +0xc8 = collision scene data
// [derived: line_segment_check (.dynsym) loads *(mgr+0xc8), reads stat_module+0x90 as Vector4]
// ════════════════════════════════════════════════════════════════════

extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b5fd8;

extern "C" void* lineSegmentCheckRaw_71003029b0(
    void* scene, const float4* start, const float4* end,
    u32 mask, void* excluded, void* out_hit, u32 flag);

// Helper: FighterAIManager → inner → +0xc8 (scene/collision context)
static inline void* get_ai_collision_scene() {
    u8* mgr_inner = *reinterpret_cast<u8**>(DAT_71052b5fd8);
    return *reinterpret_cast<void**>(mgr_inner + 0xc8);
}

// [derived: stat_module+0x90 = Vector4 position, arg1 = relative offset]
// 0x7100366380 -- app::ai::line_segment_check (100B)
bool line_segment_check_7100366380(void* L, const float4* rel) {
    u8* mod = STAT_MODULE(L);
    void* scene = get_ai_collision_scene();
    auto* base = reinterpret_cast<float4*>(mod + 0x90);
    float4 end = *base + *rel;
    return lineSegmentCheckRaw_71003029b0(
        scene, base, &end, 0xff, nullptr, nullptr, 0) != nullptr;
}

// [derived: reads stat_module+0x80, computes 2-vector offset chain]
// 0x71003663f0 -- app::ai::line_segment_check_from_top_n (112B)
bool line_segment_check_from_top_n_71003663f0(void* L, const float4* v1, const float4* v2) {
    u8* mod = STAT_MODULE(L);
    float4 start = *reinterpret_cast<float4*>(mod + 0x80) + *v1;
    float4 end = start + *v2;
    void* scene = get_ai_collision_scene();
    return lineSegmentCheckRaw_71003029b0(
        scene, &start, &end, 0xff, nullptr, nullptr, 0) != nullptr;
}

// [derived: same as line_segment_check but mask = 0x4 (ceiling-only)]
// 0x7100366460 -- app::ai::line_segment_check_only_roof (100B)
bool line_segment_check_only_roof_7100366460(void* L, const float4* rel) {
    u8* mod = STAT_MODULE(L);
    auto* base = reinterpret_cast<float4*>(mod + 0x90);
    float4 end = *base + *rel;
    void* scene = get_ai_collision_scene();
    return lineSegmentCheckRaw_71003029b0(
        scene, base, &end, 0x4, nullptr, nullptr, 0) != nullptr;
}

// [derived: same as line_segment_check but mask = 0x2 (floor-only)]
// 0x71003664d0 -- app::ai::line_segment_check_only_floor (100B)
bool line_segment_check_only_floor_71003664d0(void* L, const float4* rel) {
    u8* mod = STAT_MODULE(L);
    auto* base = reinterpret_cast<float4*>(mod + 0x90);
    float4 end = *base + *rel;
    void* scene = get_ai_collision_scene();
    return lineSegmentCheckRaw_71003029b0(
        scene, base, &end, 0x2, nullptr, nullptr, 0) != nullptr;
}

// [derived: same as line_segment_check but mask = 0x18 (wall L|R bits)]
// 0x7100366540 -- app::ai::line_segment_check_only_wall (100B)
bool line_segment_check_only_wall_7100366540(void* L, const float4* rel) {
    u8* mod = STAT_MODULE(L);
    auto* base = reinterpret_cast<float4*>(mod + 0x90);
    float4 end = *base + *rel;
    void* scene = get_ai_collision_scene();
    return lineSegmentCheckRaw_71003029b0(
        scene, base, &end, 0x18, nullptr, nullptr, 0) != nullptr;
}

// Returns a command-input category based on stat_module motion_kind and
// ctx motion hash. 1 = basic QCF/QCB range, 2 = forward-smash analog,
// 1 = explicit QCF via hash 0x6038/0x6046, 0 = none.
// [derived: stat_module+0x28 motion_kind, stat_module+0x1f4 command bits,
//  ctx+0x198 u16 motion hash]
// 0x7100361dd0 -- app::ai::check_use_command_type (104B)
u32 check_use_command_type_7100361dd0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    s32 motion = *reinterpret_cast<s32*>(mod + 0x28);
    if (static_cast<u32>(motion - 0x3c) < 2) return 1;
    if (motion == 0x55) return 2;
    s32 cmd = *reinterpret_cast<s32*>(mod + 0x1f4) & ~1;
    if (cmd != 0x3c) return 0;
    u16 hash = *reinterpret_cast<u16*>(ctx + 0x198);
    if (hash == 0x6038) return 1;
    if (hash == 0x6046) return 1;
    return 0;
}

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
extern "C" __attribute__((visibility("hidden"))) app::BossManager* DAT_71052b7ef8;

// ── 0x7102284580 -- app::sv_item::is_boss_stop (40B) ──────────────
// [derived: BossManager singleton → inner→stop_count > 0]
bool is_boss_stop_7102284580() {
    app::BossManager* bm = DAT_71052b7ef8;
    if (!bm) return false;
    return bm->inner->stop_count > 0;
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
    auto* a = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc);
    FUN_71006e27f0(a->motion_module, param, 0, 1);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    return static_cast<u32>(acc->work_module->get_int(0x10000000));
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    acc->posture_module->reverse_lr();
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    acc->posture_module->update_rot_y_lr();
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    auto* posture = acc->posture_module;
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    acc->hit_module->reset_status_all(0);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    acc->camera_module->zoom_out(0);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    auto* cb = acc->color_blend_module;
    s32 flag = cb->get_status();
    // vtable slot 0x60/8 (set_normal) — not yet in ColorBlendModule header
    reinterpret_cast<void(*)(app::ColorBlendModule*, u32)>(cb->_vt[0x60 / 8])(cb, flag & 1);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    auto* cb = acc->color_blend_module;
    s32 flag = cb->get_status();
    cb->off_burn_color(flag & 1);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    auto* sm = acc->status_module;
    sm->vtbl->SetSituationKind(sm, 2, false);
    acc->ground_module->set_correct(5);
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
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    auto* sound = acc->sound_module;
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x290 / 8])(sound);
}

// ── 0x71022b4e70 -- app::sv_animcmd::GET_VOICE_REGION_NEW (92B) ──
// [derived: pop lua stack, then SoundModule(+0x148)->vt[0x53](sound)]
void GET_VOICE_REGION_NEW_71022b4e70(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    auto* sound = acc->sound_module;
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x298 / 8])(sound);
}

// ── 0x71022b4ed0 -- app::sv_animcmd::GET_VOICE_VARIATION (92B) ───
// [derived: pop lua stack, then SoundModule(+0x148)->vt[0x54](sound)]
void GET_VOICE_VARIATION_71022b4ed0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    u64 base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    while (top < base + 0x10) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base + 0x10;
    auto* sound = acc->sound_module;
    void** vt = *reinterpret_cast<void***>(sound);
    reinterpret_cast<void(*)(void*)>(vt[0x2a0 / 8])(sound);
}

// ── 0x71022b3490 -- app::sv_animcmd::FT_DISABLE_CURRY_FACE (104B) ─
// [derived: sets StatusModule(+0x40)+0x11a = 1, calls helper, pop stack]
void FT_DISABLE_CURRY_FACE_71022b3490(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    auto* status = acc->status_module;
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

// ════════════════════════════════════════════════════════════════════
// AI misc — predict_landing_frame
// ════════════════════════════════════════════════════════════════════

// ── 0x71003694f0 -- app::ai::predict_landing_frame (20B) ──────────
// [derived: s32->f32 conversion of predicted frames until landing at +0x274]
f32 predict_landing_frame_71003694f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (f32)*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x274);
}

// ════════════════════════════════════════════════════════════════════
// analyst — status_prev, status_count, target_status variants
// ════════════════════════════════════════════════════════════════════

// ── 0x7100376a00 -- app::analyst::status_prev (20B) ───────────────
// [derived: reads prev status_kind from ctx->battle_object(+0x170)->+0x10]
u32 status_prev_7100376a00(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* bo = *reinterpret_cast<void**>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x170));
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(bo) + 0x10);
}

// ── 0x7100376ac0 -- app::analyst::status_count (20B) ──────────────
// [derived: reads status frame count from ctx->battle_object(+0x170)->+0x14]
u32 status_count_7100376ac0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* bo = *reinterpret_cast<void**>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x170));
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(bo) + 0x14);
}

// ── 0x7100376a20 -- app::analyst::target_status (80B) ─────────────
// [derived: looks up target entry from ctx+0xc50, validates against self
//  entry (+0x160), clamps to 0x10, reads status_kind from global table]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b5fd8;

u32 target_status_7100376a20(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 target = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0xc50);
    if (static_cast<s32>(target) < 0) return 0;
    if (target == *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x160)) return 0;
    if (target > 0xf) target = 0x10;
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* table = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0x98);
    void* entry = *reinterpret_cast<void**>(reinterpret_cast<u8*>(table) + static_cast<u64>(target) * 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0xc);
}

// ── 0x7100376a70 -- app::analyst::target_status_prev (80B) ────────
// [derived: same as target_status but reads +0x10 (prev status kind)]
u32 target_status_prev_7100376a70(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 target = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0xc50);
    if (static_cast<s32>(target) < 0) return 0;
    if (target == *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x160)) return 0;
    if (target > 0xf) target = 0x10;
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* table = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0x98);
    void* entry = *reinterpret_cast<void**>(reinterpret_cast<u8*>(table) + static_cast<u64>(target) * 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0x10);
}

// ── 0x7100376ae0 -- app::analyst::target_status_count (80B) ───────
// [derived: same as target_status but reads +0x14 (status frame count)]
u32 target_status_count_7100376ae0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 target = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0xc50);
    if (static_cast<s32>(target) < 0) return 0;
    if (target == *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x160)) return 0;
    if (target > 0xf) target = 0x10;
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* table = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0x98);
    void* entry = *reinterpret_cast<void**>(reinterpret_cast<u8*>(table) + static_cast<u64>(target) * 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0x14);
}

// ════════════════════════════════════════════════════════════════════
// AI target — target_status_kind (uses aiGetTargetById_7100314030 lookup)
// ════════════════════════════════════════════════════════════════════

extern "C" void* aiGetTargetById_7100314030(void*, void*);

// ── 0x7100366ff0 -- app::ai::target_status_kind (40B) ─────────────
// [derived: looks up target via aiGetTargetById_7100314030, reads status_kind at +0x2c]
u32 target_status_kind_7100366ff0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(target) + 0x2c);
}

// ════════════════════════════════════════════════════════════════════
// ai_stage — stage property queries
// ════════════════════════════════════════════════════════════════════

extern "C" u8 FUN_7100314d50(u32);
extern "C" u8 FUN_7100314dc0(u32);

// ── 0x710036b200 -- app::ai_stage::current_id (20B) ───────────────
// [derived: reads stage ID from global at *DAT_71052b5fd8 + 0x150]
u32 current_id_710036b200() {
    return *reinterpret_cast<u32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b5fd8)) + 0x150);
}

// ── 0x710036b220 -- app::ai_stage::is_small (20B) ─────────────────
// [derived: tail-calls FUN_7100314d50 with current stage ID]
u8 is_small_710036b220() {
    u32 id = *reinterpret_cast<u32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b5fd8)) + 0x150);
    return FUN_7100314d50(id);
}

// ── 0x710036b380 -- app::ai_stage::is_1on1 (20B) ─────────────────
// [derived: tail-calls FUN_7100314dc0 with current stage ID]
u8 is_1on1_710036b380() {
    u32 id = *reinterpret_cast<u32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b5fd8)) + 0x150);
    return FUN_7100314dc0(id);
}

// ════════════════════════════════════════════════════════════════════
// ai_rule — rule property queries
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b680 -- app::ai_rule::is_hp (20B) ─────────────────────
// [derived: reads byte at FighterManager singleton + 0xc3]
u8 is_hp_710036b680() {
    return *reinterpret_cast<u8*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b84f8)) + 0xc3);
}

// ════════════════════════════════════════════════════════════════════
// ai_param — AI parameter queries from global param struct
// ════════════════════════════════════════════════════════════════════

extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b60e8;

// ── 0x710036c140 -- app::ai_param::zako2_search_range (20B) ───────
// [derived: reads f32 at *DAT_71052b60e8 + 0x78 — uses ldr s0 (float return)]
f32 zako2_search_range_710036c140(void* L) {
    return *reinterpret_cast<f32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b60e8)) + 0x78);
}

// ── 0x710036c160 -- app::ai_param::training_smash_interval (20B) ──
// [derived: reads u32 at *DAT_71052b60e8 + 0x7c]
u32 training_smash_interval_710036c160(void* L) {
    return *reinterpret_cast<u32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b60e8)) + 0x7c);
}

// ── 0x710036c180 -- app::ai_param::training_special_interval (20B)─
// [derived: reads u32 at *DAT_71052b60e8 + 0x80]
u32 training_special_interval_710036c180(void* L) {
    return *reinterpret_cast<u32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b60e8)) + 0x80);
}

// ════════════════════════════════════════════════════════════════════
// sv_animcmd — IS_FIGHTER_STATUS_KIND / IS_STATUS_KIND
// Pop stack arg, compare against StatusModule::get_status_kind vtable call
// ════════════════════════════════════════════════════════════════════

extern "C" u64 l2cParamResolve_71038f4000(void*, s32, s32);

// ── 0x71022ad5a0 -- app::sv_animcmd::IS_FIGHTER_STATUS_KIND (200B)─
// [derived: pops 1 int arg from lua stack, calls StatusModule(+0x40)->vt[0x110/8]
//  (get_status_kind), returns true if current status == arg]
u32 IS_FIGHTER_STATUS_KIND_71022ad5a0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 base = *reinterpret_cast<u64*>(
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = static_cast<s32>((top - base) >> 4);
    s32 kind;
    if (nargs < 1) {
        kind = 0;
    } else {
        kind = static_cast<s32>(l2cParamResolve_71038f4000(L, 1, 0));
    }
    // pop stack
    top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    base = *reinterpret_cast<u64*>(
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    while (top < base) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base;
    // get current status kind via StatusModule vtable
    auto* status_mod = acc->status_module;
    s32 current = status_mod->vtbl->StatusKind(status_mod);
    return current == kind;
}

// ── 0x71022ad670 -- app::sv_animcmd::IS_STATUS_KIND (200B) ────────
// [derived: identical to IS_FIGHTER_STATUS_KIND — same vtable slot,
//  same stack cleanup pattern; exported under different symbol]
u32 IS_STATUS_KIND_71022ad670(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x1a0));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 base = *reinterpret_cast<u64*>(
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = static_cast<s32>((top - base) >> 4);
    s32 kind;
    if (nargs < 1) {
        kind = 0;
    } else {
        kind = static_cast<s32>(l2cParamResolve_71038f4000(L, 1, 0));
    }
    // pop stack
    top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    base = *reinterpret_cast<u64*>(
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    while (top < base) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = base;
    // get current status kind via StatusModule vtable
    auto* status_mod = acc->status_module;
    s32 current = status_mod->vtbl->StatusKind(status_mod);
    return current == kind;
}

// ════════════════════════════════════════════════════════════════════
// AI — simple field reads/writes from scripting context
// ════════════════════════════════════════════════════════════════════

// ── 0x7100368180 -- app::ai::update_count (12B) ──────────────────
// [derived: reads u32 at ctx+0x2fc — AI update frame counter]
u32 update_count_7100368180(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x2fc);
}

// ── 0x7100368170 -- app::ai::set_auto_stop (12B) ─────────────────
// [derived: writes s32 param to ctx+0x2bc — auto stop flag]
void set_auto_stop_7100368170(void* L, s32 val) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ctx) + 0x2bc) = val;
}

// ── 0x71003681c0 -- app::ai::reset_return_count (12B) ────────────
// [derived: zeroes u16 at ctx+0xc7c — return count reset]
void reset_return_count_71003681c0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ctx) + 0xc7c) = 0;
}

// ── 0x7100376350 -- app::ai_system::set_update_count (12B) ───────
// [derived: writes s32 param to ctx+0x2fc — set update frame counter]
void set_update_count_7100376350(void* L, s32 val) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ctx) + 0x2fc) = val;
}

// ── 0x7100376390 -- app::ai_system::prev_mode (12B) ──────────────
// [derived: reads u32 at ctx+0xc68 — previous AI mode]
u32 prev_mode_7100376390(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0xc68);
}

// ── 0x7100375f10 -- app::nfp::is_enabled (12B) ──────────────────
// [derived: reads u8 at ctx+0xc24 — amiibo/NFC enabled flag]
u8 is_enabled_7100375f10(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0xc24);
}

// ════════════════════════════════════════════════════════════════════
// AI — tail-call dispatchers (12B each)
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_7100359e30(void*);
extern "C" void FUN_71002f5770(void*, u64);
extern "C" void FUN_71002f46a0(void*, u64);
extern "C" void FUN_71002f43c0(void*);
extern "C" void FUN_71002f4590(void*);
extern "C" void FUN_710033e5c0(void*, u64);
extern "C" void FUN_710036a5c0(void*, s32, s32);

// ── 0x71003680f0 -- app::ai::check_away_floor (12B) ─────────────
// [derived: tail-calls FUN_7100359e30 with ctx->ai_data(+0x168)]
void check_away_floor_71003680f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_7100359e30(*reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168));
}

// ── 0x7100368cf0 -- app::ai::enable_command (12B) ────────────────
// [derived: tail-calls FUN_71002f5770 with ctx->cmd_module(+0x180), cmd_id]
void enable_command_7100368cf0(void* L, u64 cmd_id) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002f5770(reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x180), cmd_id);
}

// ── 0x7100368d00 -- app::ai::disable_command (12B) ───────────────
// [derived: tail-calls FUN_71002f46a0 with ctx->cmd_module(+0x180), cmd_id]
void disable_command_7100368d00(void* L, u64 cmd_id) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002f46a0(reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x180), cmd_id);
}

// ── 0x7100368d10 -- app::ai::disable_command_ground_all (12B) ────
// [derived: tail-calls FUN_71002f43c0 with ctx->cmd_module(+0x180)]
void disable_command_ground_all_7100368d10(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002f43c0(reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x180));
}

// ── 0x7100368d20 -- app::ai::disable_command_air_all (12B) ──────
// [derived: tail-calls FUN_71002f4590 with ctx->cmd_module(+0x180)]
void disable_command_air_all_7100368d20(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002f4590(reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x180));
}

// ── 0x710036a130 -- app::ai::motion_to_cmd_id (12B) ─────────────
// [derived: tail-calls FUN_710033e5c0 with ctx+0x988, hash40 param]
void motion_to_cmd_id_710036a130(void* L, u64 hash) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_710033e5c0(reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x988), hash);
}

// ── 0x710036a5b0 -- app::ai_deprecated::range_in (12B) ──────────
// [derived: tail-calls FUN_710036a5c0 with L, 1, 0]
void range_in_710036a5b0(void* L, f32 a, f32 b) {
    FUN_710036a5c0(L, 1, 0);
}

// ── 0x710036acf0 -- app::ai_deprecated::distance_in (12B) ───────
// [derived: tail-calls FUN_710036a5c0 with L, 0, 0]
void distance_in_710036acf0(void* L, f32 a, f32 b) {
    FUN_710036a5c0(L, 0, 0);
}

// ── 0x710036ad00 -- app::ai_deprecated::other_in (12B) ──────────
// [derived: tail-calls FUN_710036a5c0 with L, 0, 1]
void other_in_710036ad00(void* L, f32 a, f32 b) {
    FUN_710036a5c0(L, 0, 1);
}

// ════════════════════════════════════════════════════════════════════
// ai_param — more parameter field reads from scripting context
// ════════════════════════════════════════════════════════════════════

// ── 0x710036baa0 -- app::ai_param::closed_mul (12B) ─────────────
// [derived: reads f32 at ctx+0xbf0 — uses ldr s0 (float return)]
f32 closed_mul_710036baa0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xbf0);
}

// ── 0x710036bab0 -- app::ai_param::my_range_mul (12B) ───────────
// [derived: reads f32 at ctx+0xbf4 — uses ldr s0 (float return)]
f32 my_range_mul_710036bab0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xbf4);
}

// ── 0x710036bac0 -- app::ai_param::safe_range_mul (12B) ─────────
// [derived: reads f32 at ctx+0xbf8 — uses ldr s0 (float return)]
f32 safe_range_mul_710036bac0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xbf8);
}

// ── 0x710036bad0 -- app::ai_param::opened_mul (12B) ─────────────
// [derived: reads f32 at ctx+0xbfc — uses ldr s0 (float return)]
f32 opened_mul_710036bad0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xbfc);
}

// ── 0x710036bae0 -- app::ai_param::meteor_action_probability (12B)
// [derived: reads f32 at ctx+0xc00 — uses ldr s0 (float return)]
f32 meteor_action_probability_710036bae0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xc00);
}

// ── 0x710036baf0 -- app::ai_param::range_middle (12B) ───────────
// [derived: reads f32 at ctx+0xab8 — uses ldr s0 (float return)]
f32 range_middle_710036baf0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xab8);
}

// ── 0x710036bb00 -- app::ai_param::range_long (12B) ─────────────
// [derived: reads f32 at ctx+0xab4 — uses ldr s0 (float return)]
f32 range_long_710036bb00(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xab4);
}

// ════════════════════════════════════════════════════════════════════
// AI — check_stat comparison functions (24B each)
// Read stat_type from ai_data(+0x168)+0x74 and compare to a constant
// ════════════════════════════════════════════════════════════════════

// ── 0x7100361390 -- app::ai::check_stat_final (24B) ─────────────
// [derived: tests bits 0-1 of u8 at +0x55 — final smash active or pending]
u32 check_stat_final_7100361390(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(ai) + 0x55) & 3) != 0;
}

// ── 0x71003614d0 -- app::ai::check_stat_dash (24B) ──────────────
// [derived: compares stat_type(+0x74) == 3 — dashing state]
u32 check_stat_dash_71003614d0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 3;
}

// ── 0x71003614f0 -- app::ai::check_stat_down (24B) ──────────────
// [derived: compares stat_type(+0x74) == 4 — downed state]
u32 check_stat_down_71003614f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 4;
}

// ── 0x7100361510 -- app::ai::check_stat_piyo (28B) ──────────────
// [derived: compares stat_type(+0x74) in range [9,11] — dizzy/stunned states]
bool check_stat_piyo_7100361510(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (u32)(*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) - 9) < 3;
}

// ── 0x7100361530 -- app::ai::check_stat_dragoon (24B) ───────────
// [derived: compares stat_type(+0x74) == 0x11 — using dragoon item]
u32 check_stat_dragoon_7100361530(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 0x11;
}

// ── 0x7100361550 -- app::ai::check_stat_genesis (24B) ───────────
// [derived: compares stat_type(+0x74) == 0x12 — using daybreak/genesis item]
u32 check_stat_genesis_7100361550(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 0x12;
}

// ── 0x7100361570 -- app::ai::check_stat_catch (24B) ─────────────
// [derived: compares stat_type(+0x74) == 0xc — catching/grabbing state]
u32 check_stat_catch_7100361570(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 0xc;
}

// ── 0x71003615b0 -- app::ai::check_stat_guard (24B) ─────────────
// [derived: compares stat_type(+0x74) == 0x1a — guarding/shielding state]
u32 check_stat_guard_71003615b0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x74) == 0x1a;
}

// ── 0x71003615f0 -- app::ai::check_stat_floor_pass (80B) ────────
// [derived: +0xd8 (s32): ground state, +0xd0->+0x5c bit5: passable flag,
//  +0x10->+0x3a (u8): sub-type, +0x10->+0x20->+0x58->vtable[0x4f8/8] dispatch]
u32 check_stat_floor_pass_71003615f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if (*reinterpret_cast<s32*>(mod + 0xd8) == 0) {
        if ((*reinterpret_cast<u8*>(*reinterpret_cast<u64*>(mod + 0xd0) + 0x5c) >> 5) & 1) {
            return 1;
        }
    }
    u8* sub = reinterpret_cast<u8*>(*reinterpret_cast<u64*>(mod + 0x10));
    if (sub[0x3a] > 3) {
        u64 obj = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(*reinterpret_cast<u64*>(sub + 0x20) + 0x58) + 0x4f8);
        return reinterpret_cast<u64(*)(void)>(obj)();
    }
    return 0;
}

// ── 0x7100361670 -- app::ai::check_stat_ground_free (88B) ───────
// [derived: composite ground-free check — statue flag, status kind, inverted bitmask, air+sign check]
// +0x54 bit30: statue/frozen flag, +0x74: status kind (1=ground),
// +0x64: inverted flags (0x99 mask), +0x54 bit0: air, +0x58 bit7: sign bit
u32 check_stat_ground_free_7100361670(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if ((*reinterpret_cast<u32*>(mod + 0x54) >> 30) & 1) return 0;
    if (*reinterpret_cast<s32*>(mod + 0x74) == 1) return 1;
    if ((~*reinterpret_cast<u32*>(mod + 0x64) & 0x99) == 0) return 1;
    if ((*reinterpret_cast<u32*>(mod + 0x54) & 1) == 0 && (mod[0x58] >> 7))
        return 1;
    return 0;
}

// ── 0x71003616d0 -- app::ai::check_stat_ground_free2 (100B) ────
// [derived: like ground_free but with additional status!=0x17 check for status kind 1]
u32 check_stat_ground_free2_71003616d0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if ((*reinterpret_cast<u32*>(mod + 0x54) >> 30) & 1) return 0;
    if (*reinterpret_cast<s32*>(mod + 0x74) == 1 && *reinterpret_cast<s32*>(mod + 0x2c) != 0x17)
        return 1;
    if ((~*reinterpret_cast<u32*>(mod + 0x64) & 0x99) == 0) return 1;
    if ((*reinterpret_cast<u32*>(mod + 0x54) & 1) == 0 && (mod[0x58] >> 7))
        return 1;
    return 0;
}

// ── 0x7100361740 -- app::ai::check_stat_air_free (88B) ──────────
// [derived: like ground_free but for air — status kind 2, inverted mask 0xe00, air+sign]
u32 check_stat_air_free_7100361740(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if ((*reinterpret_cast<u32*>(mod + 0x54) >> 30) & 1) return 0;
    if (*reinterpret_cast<s32*>(mod + 0x74) == 2) return 1;
    if ((~*reinterpret_cast<u32*>(mod + 0x64) & 0xe00) == 0) return 1;
    if ((*reinterpret_cast<u32*>(mod + 0x54) & 1) != 0 && (mod[0x58] >> 7))
        return 1;
    return 0;
}

// ── 0x7100361a20 -- app::ai::check_skill_stat (24B) ─────────────
// [derived: tests bitmask of u32 at ai_data+0x6c against param]
u32 check_skill_stat_7100361a20(void* L, u32 mask) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(ai) + 0x6c) & mask) != 0;
}

// ── 0x7100361a40 -- app::ai::check_spirits_event_stat (24B) ─────
// [derived: tests bitmask of u32 at ai_data+0x70 against param]
u32 check_spirits_event_stat_7100361a40(void* L, u32 mask) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(ai) + 0x70) & mask) != 0;
}

// ── 0x7100361b50 -- app::ai::check_passable (24B) ───────────────
// [derived: bit 5 of u8 at ai_data(+0x168)->sub(+0xd0)+0x5c — passable flag]
u32 check_passable_7100361b50(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* sub = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0xd0);
    return (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(sub) + 0x5c) >> 5) & 1;
}

// ════════════════════════════════════════════════════════════════════
// ai_camera — dead zone boundaries (24B each, read from global)
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b180 -- app::ai_camera::dead_top (24B) ──────────────
// [derived: reads f32 from *(*DAT_71052b5fd8+0xc8)+0x10]
f32 dead_top_710036b180() {
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* cam = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0xc8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(cam) + 0x10);
}

// ── 0x710036b1a0 -- app::ai_camera::dead_bottom (24B) ───────────
// [derived: reads f32 from *(*DAT_71052b5fd8+0xc8)+0x14]
f32 dead_bottom_710036b1a0() {
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* cam = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0xc8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(cam) + 0x14);
}

// ── 0x710036b1c0 -- app::ai_camera::dead_left (24B) ────────────
// [derived: reads f32 from *(*DAT_71052b5fd8+0xc8)+0x8]
f32 dead_left_710036b1c0() {
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* cam = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0xc8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(cam) + 0x8);
}

// ── 0x710036b1e0 -- app::ai_camera::dead_right (24B) ───────────
// [derived: reads f32 from *(*DAT_71052b5fd8+0xc8)+0xc]
f32 dead_right_710036b1e0() {
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* cam = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0xc8);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(cam) + 0xc);
}

// ════════════════════════════════════════════════════════════════════
// ai_param — indexed parameter lookups (24B each)
// Pattern: ctx->ai_data(+0x168)->index(+0x240) * 4 + base_offset
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b8f0 -- app::ai_param::sp_u_high (24B) ─────────────
// [derived: indexed f32 read at ctx + ai_index*4 + 0xad0]
f32 sp_u_high_710036b8f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xad0);
}

// ── 0x710036b910 -- app::ai_param::sp_u_length (24B) ────────────
// [derived: indexed f32 read at ctx + ai_index*4 + 0xae0]
f32 sp_u_length_710036b910(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xae0);
}

// ── 0x710036b930 -- app::ai_param::return_sp_u_cliff_x (24B) ────
// [derived: indexed f32 read at ctx + ai_index*4 + 0xb34]
f32 return_sp_u_cliff_x_710036b930(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xb34);
}

// ── 0x710036b950 -- app::ai_param::return_sp_u_cliff_y (24B) ────
// [derived: indexed f32 read at ctx + ai_index*4 + 0xb44]
f32 return_sp_u_cliff_y_710036b950(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xb44);
}

// ── 0x710036b970 -- app::ai_param::return_goal_x (24B) ──────────
// [derived: indexed f32 read at ctx + ai_index*4 + 0xb54]
f32 return_goal_x_710036b970(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xb54);
}

// ── 0x710036b990 -- app::ai_param::return_goal_x_strict (24B) ───
// [derived: indexed f32 read at ctx + ai_index*4 + 0xb64]
f32 return_goal_x_strict_710036b990(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xb64);
}

// ── 0x710036b9b0 -- app::ai_param::return_goal_pad_x_strict (24B)
// [derived: indexed f32 read at ctx + ai_index*4 + 0xb74]
f32 return_goal_pad_x_strict_710036b9b0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    s32 idx = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x240);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + static_cast<s64>(idx) * 4 + 0xb74);
}

// ════════════════════════════════════════════════════════════════════
// ai_param — challenger_guard_rate, analyst::chanced_frame
// ════════════════════════════════════════════════════════════════════

// ── 0x710036c1a0 -- app::ai_param::challenger_guard_rate (20B) ──
// [derived: reads f32 from *DAT_71052b60e8 + 0x84]
f32 challenger_guard_rate_710036c1a0(void* L) {
    return *reinterpret_cast<f32*>(
        reinterpret_cast<u8*>(*reinterpret_cast<void**>(DAT_71052b60e8)) + 0x84);
}

// ── 0x7100376b90 -- app::analyst::chanced_frame (20B) ───────────
// [derived: reads u32 from ctx->battle_object(+0x170)->+0x1c]
u32 chanced_frame_7100376b90(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* bo = *reinterpret_cast<void**>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x170));
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(bo) + 0x1c);
}

// ════════════════════════════════════════════════════════════════════
// AI system — stick/action controls
// ════════════════════════════════════════════════════════════════════

// ── 0x7100376330 -- app::ai_system::set_action_id_none (24B) ────
// [derived: saves current action_id(+0x198) to prev(+0x19a) if nonzero, then clears it]
void set_action_id_none_7100376330(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    s16 cur = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(ctx) + 0x198);
    if (cur != 0) {
        *reinterpret_cast<s16*>(reinterpret_cast<u8*>(ctx) + 0x19a) = cur;
    }
    *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ctx) + 0x198) = 0;
}

// ── 0x71003762f0 -- app::ai_system::reset_stick (24B) ───────────
// [derived: zeroes stick vectors at ctx+0xc30 and ctx+0xc38 from zero constant]
void reset_stick_71003762f0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u64 z0 = *reinterpret_cast<u64*>(DAT_71052a7a80);
    u64 z1 = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(DAT_71052a7a80) + 8);
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(ctx) + 0xc38) = z1;
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(ctx) + 0xc30) = z0;
}

// [derived: ldr q0 from ctx+0xc30, vec add from arg, str q0 back]
// 0x7100376240 -- app::ai_system::add_stick_abs (24B)
void add_stick_abs_7100376240(void* L, const float4* v) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* slot = reinterpret_cast<float4*>(ctx + 0xc30);
    *slot = *slot + *v;
}

// [derived: multiplies v.x by stat_module->lr (+0xc4), preserves v.y,
//  zeroes high lanes, adds to ctx+0xc30 stick accumulator]
// 0x7100376210 -- app::ai_system::add_stick (48B)
void add_stick_7100376210(void* L, const float4* v) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    float4 in = *v;
    f32 lr = *reinterpret_cast<f32*>(mod + 0xc4);
    float4 scaled = {lr * in[0], in[1], 0.0f, 0.0f};
    auto* slot = reinterpret_cast<float4*>(ctx + 0xc30);
    *slot = *slot + scaled;
}

// AI personality table (+0xc24 = enabled flag, +0x988 = table base)
extern "C" f32 personalityTableLookup_710033fec0(void* table);

// [derived: checks ctx+0xc24 (enabled), tail-calls FUN_710033fec0 with ctx+0x988,
//  or returns 0.0f if disabled]
// 0x7100376010 -- app::ai::personality_up_rate (40B)
f32 personality_up_rate_7100376010(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    if (ctx[0xc24] == 0) return 0.0f;
    return personalityTableLookup_710033fec0(ctx + 0x988);
}

// [derived: ctx+0xc24 enabled, ctx+0x98c is f32 array indexed by arg*4,
//  clamped to 0x47 max — return 1.0f if arg > 0x47]
// 0x71003760e0 -- app::ai::personality_probability (48B)
f32 personality_probability_71003760e0(void* L, s32 idx) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    if (ctx[0xc24] == 0) return 0.0f;
    if (static_cast<u32>(idx) > 0x47) return 1.0f;
    return *reinterpret_cast<f32*>(ctx + 0x98c + static_cast<s64>(idx) * 4);
}

// [derived: stat_module+0x80 is Vector4 position. Saves self x into d8
//  (callee-saved) across aiGetTargetById call, returns |self.x - target.x|]
// 0x7100367230 -- app::ai::distance_x_to_target (60B)
f32 distance_x_to_target_7100367230(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    f32 self_x = *reinterpret_cast<f32*>(mod + 0x80);
    u8* target = reinterpret_cast<u8*>(aiGetTargetById_7100314030(
        DAT_71052b5fd8, reinterpret_cast<void*>(ctx + 0xc50)));
    f32 target_x = *reinterpret_cast<f32*>(target + 0x80);
    return __builtin_fabsf(self_x - target_x);
}

// [derived: same as distance_x_to_target but reads +0x84 (y component)]
// 0x7100367270 -- app::ai::distance_y_to_target (60B)
f32 distance_y_to_target_7100367270(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    f32 self_y = *reinterpret_cast<f32*>(mod + 0x84);
    u8* target = reinterpret_cast<u8*>(aiGetTargetById_7100314030(
        DAT_71052b5fd8, reinterpret_cast<void*>(ctx + 0xc50)));
    f32 target_y = *reinterpret_cast<f32*>(target + 0x84);
    return __builtin_fabsf(self_y - target_y);
}

// [derived: stat_module+0x54 bit0 = air flag, floor+0x5e bit1 = over-ground
//  flag, stat_module+0x74 & ~1 == 6 is another pass condition.
//  First 11/16 insns match — Clang merges the last two return paths into
//  a branchless BIC where the original has two branches. Semantically
//  equivalent; tail scheduling differs.]
// 0x7100367a90 -- app::ai::check_over_ground (72B)
bool check_over_ground_7100367a90(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    u32 flags = *reinterpret_cast<u32*>(mod + 0x54);
    if ((flags & 1) == 0) {
        u8* floor = *reinterpret_cast<u8**>(mod + 0xd0);
        if ((floor[0x5e] & 2) == 0) {
            return true;
        }
    }
    s32 kind = *reinterpret_cast<s32*>(mod + 0x74);
    if ((kind & ~1) == 6) return true;
    return (flags & 2) == 0;
}

// [derived: compares floor_data pointer (at stat_module+0xd0) between self
//  and target — both must reference the same ground collision line]
// 0x71003672b0 -- app::ai::is_target_on_same_floor (64B)
bool is_target_on_same_floor_71003672b0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(aiGetTargetById_7100314030(
        DAT_71052b5fd8, reinterpret_cast<void*>(ctx + 0xc50)));
    u8* mod = *reinterpret_cast<u8**>(ctx + 0x168);
    void* self_floor = *reinterpret_cast<void**>(mod + 0xd0);
    void* target_floor = *reinterpret_cast<void**>(target + 0xd0);
    return self_floor == target_floor;
}

// [derived: tail-call to aiGetTargetById, read 4 f32 values individually
//  (rect bounds: xmin, xmax, ymin, ymax). Target+0x264 is not 16-byte
//  aligned so Clang emits ldr s0 + ld1 inserts rather than ldr q0]
// 0x7100367080 -- app::ai::target_hit_collision_rect (64B)
float4 target_hit_collision_rect_7100367080(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(aiGetTargetById_7100314030(
        DAT_71052b5fd8, reinterpret_cast<void*>(ctx + 0xc50)));
    float4 r;
    r[0] = *reinterpret_cast<f32*>(target + 0x264);
    r[1] = *reinterpret_cast<f32*>(target + 0x268);
    r[2] = *reinterpret_cast<f32*>(target + 0x26c);
    r[3] = *reinterpret_cast<f32*>(target + 0x270);
    return r;
}

// [derived: computes DAT_71044791c - personality_probability value.
//  DAT_71044791c is a global f32 constant (probably 1.0f or similar)]
// 0x7100376110 -- app::ai::personality_probability_inverse (60B)
extern "C" __attribute__((visibility("hidden"))) f32 DAT_710447291c;
f32 personality_probability_inverse_7100376110(void* L, s32 idx) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    if (ctx[0xc24] == 0) return 0.0f;
    f32 val;
    if (static_cast<u32>(idx) > 0x47) {
        val = 1.0f;
    } else {
        val = *reinterpret_cast<f32*>(ctx + 0x98c + static_cast<s64>(idx) * 4);
    }
    return DAT_710447291c - val;
}

// ── 0x710036b810 -- app::ai_param::width (24B) ─────────────────
// [derived: multiplies ctx+0xb2c (base_width) by ai_data+0xc0 (scale factor)]
f32 width_710036b810(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xb2c) *
           *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ai) + 0xc0);
}

// ════════════════════════════════════════════════════════════════════
// AI check_stat — additional bitfield tests
// ════════════════════════════════════════════════════════════════════

// check_stat_gorogoro: see line ~552 (pool-a version with STAT_MODULE macro)
// check_stat_piyo: see line ~584 (pool-a version)

// ════════════════════════════════════════════════════════════════════
// AI command step checks — fighting game input checks
// ════════════════════════════════════════════════════════════════════

// ── 0x7100361fe0 -- app::ai::check_command_236236_step (44B) ──────
// [derived: ai_data+0x28 == 0x55 && sign bit of +0x68 set]
u64 check_command_236236_step_7100361fe0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x28) == 0x55 &&
        *reinterpret_cast<s8*>(reinterpret_cast<u8*>(ai) + 0x68) < 0) {
        return 1;
    }
    return static_cast<u64>(0);
}

// ── 0x7100362010 -- app::ai::check_command_21416_step (44B) ───────
// [derived: ai_data+0x28 == 0x55 && bit0 of +0x69 set]
u64 check_command_21416_step_7100362010(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x28) == 0x55 &&
        (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(ai) + 0x69) & 1) != 0) {
        return 1;
    }
    return static_cast<u64>(0);
}

// ── 0x7100362040 -- app::ai::check_command_214214_step (44B) ──────
// [derived: ai_data+0x28 == 0x55 && bit1 of +0x69 set]
u64 check_command_214214_step_7100362040(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x28) == 0x55 &&
        (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(ai) + 0x69) >> 1 & 1) != 0) {
        return 1;
    }
    return static_cast<u64>(0);
}

// ── 0x7100362070 -- app::ai::check_command_23634_step (44B) ───────
// [derived: ai_data+0x28 == 0x55 && bit2 of +0x69 set]
u64 check_command_23634_step_7100362070(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    if (*reinterpret_cast<s32*>(reinterpret_cast<u8*>(ai) + 0x28) == 0x55 &&
        (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(ai) + 0x69) >> 2 & 1) != 0) {
        return 1;
    }
    return static_cast<u64>(0);
}

// ── 0x7100361b20 -- app::ai::check_cliffable_floor_lr (44B) ───────
// [derived: checks bit6 or bit7 of floor_data(+0xd0)->+0x5c based on lr sign]
u32 check_cliffable_floor_lr_7100361b20(void* L, f32 lr) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* floor = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0xd0);
    u32 mask = 0x40;
    if (lr == 0.0f || lr < 0.0f) {
        mask = 0x80;
    }
    return (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(floor) + 0x5c) & mask) != 0;
}

// ════════════════════════════════════════════════════════════════════
// AI target queries — aiGetTargetById_7100314030 lookup family
// ════════════════════════════════════════════════════════════════════

// ── 0x7100366de0 -- app::ai::target_height (40B) ──────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0xc8 (height)]
f32 target_height_7100366de0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0xc8);
}

// ── 0x7100366e10 -- app::ai::target_pos_x (40B) ──────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0x80 (pos.x)]
f32 target_pos_x_7100366e10(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0x80);
}

// ── 0x7100366e40 -- app::ai::target_pos_y (40B) ──────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0x84 (pos.y)]
f32 target_pos_y_7100366e40(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0x84);
}

// ── 0x7100366e70 -- app::ai::target_speed_x (40B) ────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0xa0 (speed.x)]
f32 target_speed_x_7100366e70(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0xa0);
}

// ── 0x7100366ea0 -- app::ai::target_speed_y (40B) ────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0xa4 (speed.y)]
f32 target_speed_y_7100366ea0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0xa4);
}

// ── 0x7100366ed0 -- app::ai::target_scale (40B) ──────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0xc0 (scale)]
f32 target_scale_7100366ed0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0xc0);
}

// ── 0x7100366fc0 -- app::ai::target_lr (40B) ─────────────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0xc4 (lr direction)]
f32 target_lr_7100366fc0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0xc4);
}

// ── 0x7100367020 -- app::ai::target_motion_kind (40B) ─────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0x38 (motion kind hash)]
u64 target_motion_kind_7100367020(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(target) + 0x38);
}

// ── 0x7100367050 -- app::ai::target_motion_frame (40B) ────────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → +0x48 (motion frame)]
f32 target_motion_frame_7100367050(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(target) + 0x48);
}

// ── 0x71003666e0 -- app::ai::check_target_stat_air (44B) ──────────
// [derived: aiGetTargetById_7100314030(global, ctx+0xc50) → bit0 of +0x54]
u32 check_target_stat_air_71003666e0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* target = aiGetTargetById_7100314030(DAT_71052b5fd8,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(target) + 0x54) & 1;
}

// ════════════════════════════════════════════════════════════════════
// AI floor/platform queries
// ════════════════════════════════════════════════════════════════════

// ── 0x7100367910 -- app::ai::floor_width (28B) ───────────────────
// [derived: |floor_data(+0xd0)->+0x30 - floor_data(+0xd0)->+0x20| (right - left edge)]
f32 floor_width_7100367910(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* floor = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0xd0);
    return __builtin_fabsf(*reinterpret_cast<f32*>(reinterpret_cast<u8*>(floor) + 0x30) -
                           *reinterpret_cast<f32*>(reinterpret_cast<u8*>(floor) + 0x20));
}

// ── 0x7100367930 -- app::ai::floor_center (36B) ──────────────────
// [derived: average of floor_data(+0xd0)->+0x30 and +0x20 (midpoint of floor)]
f32 floor_center_7100367930(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* floor = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0xd0);
    return (*reinterpret_cast<f32*>(reinterpret_cast<u8*>(floor) + 0x30) +
            *reinterpret_cast<f32*>(reinterpret_cast<u8*>(floor) + 0x20)) * 0.5f;
}

// ── 0x7100367e90 -- app::ai::floor_moves (20B) ──────────────────
// [derived: returns 128-bit vector from floor_data(+0xd0)->+0x10]
float4 floor_moves_7100367e90(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* floor = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0xd0);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(floor) + 0x10);
}

// ── 0x71003680e0 -- app::ai::goal_pos (12B) ─────────────────────
// [derived: returns 128-bit vector from ctx+0x270]
float4 goal_pos_71003680e0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    return *reinterpret_cast<float4*>(reinterpret_cast<u8*>(ctx) + 0x270);
}

// ════════════════════════════════════════════════════════════════════
// AI param — air movement
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b8b0 -- app::ai_param::air_high (32B) ────────────────
// [derived: (ctx+0xb04 - 3.0) * ai_data(+0x168)->+0x200]
f32 air_high_710036b8b0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (*reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xb04) - 3.0f) *
           *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ai) + 0x200);
}

// ── 0x710036b8d0 -- app::ai_param::air_length (32B) ──────────────
// [derived: (ctx+0xb08 - 3.0) * ai_data(+0x168)->+0x1fc]
f32 air_length_710036b8d0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    return (*reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xb08) - 3.0f) *
           *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ai) + 0x1fc);
}

// ════════════════════════════════════════════════════════════════════
// AI stage queries
// ════════════════════════════════════════════════════════════════════

// ── 0x710036b470 -- app::ai_stage::is_in_transition (28B) ─────────
// [derived: checks StageManager+0xbc != 0]
u32 is_in_transition_710036b470(void* L) {
    void* mgr = *reinterpret_cast<void**>(DAT_710532999d8);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(mgr) + 0xbc) != 0;
}

// ════════════════════════════════════════════════════════════════════
// AI danger zone / line segment
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_71002f9ca0(void*, void*, void*, u32);

// ── 0x710036b4b0 -- app::ai_dangerzone::check_line_segment (32B) ──
// [derived: calls FUN_71002f9ca0 on *DAT_71052b5fd8+0xc0 danger zone data]
void check_line_segment_710036b4b0(void* L, void* p1, void* p2) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* global = *reinterpret_cast<void**>(DAT_71052b5fd8);
    void* dz = *reinterpret_cast<void**>(reinterpret_cast<u8*>(global) + 0xc0);
    u32 id = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ai) + 0xf0);
    FUN_71002f9ca0(dz, p1, p2, id);
}

// ════════════════════════════════════════════════════════════════════
// AI system — mode/button/target
// ════════════════════════════════════════════════════════════════════

extern "C" __attribute__((visibility("hidden"))) u32 DAT_7104538fec[];

// ── 0x7100376310 -- app::ai_system::add_button (32B) ──────────────
// [derived: ORs button bitmask from DAT_7104538fec[kind] into ctx+0xc40]
void add_button_7100376310(void* L, s32 kind) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0xc40) |= DAT_7104538fec[kind];
}

// ── 0x7100376360 -- app::ai_system::change_mode_action (32B) ──────
// [derived: if **ctx->+0x38 is true, sets **ctx->+0x39 = 1]
void change_mode_action_7100376360(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* p = *reinterpret_cast<void**>(ctx);
    void* q = *reinterpret_cast<void**>(p);
    if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(q) + 0x38) != 0) {
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(q) + 0x39) = 1;
    }
}

extern "C" void FUN_71002d8ef0(void*, s32, s32, s32);

// ── 0x71003763a0 -- app::ai_system::change_mode (32B) ─────────────
// [derived: calls FUN_71002d8ef0(ctx, mode, -1, 0)]
void change_mode_71003763a0(void* L, s32 mode) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002d8ef0(ctx, mode, -1, 0);
}

extern "C" void FUN_71002ec1a0(void*);

// ── 0x71003763c0 -- app::ai_system::change_target (8B) ────────────
// [derived: tail-calls FUN_71002ec1a0(ctx)]
void change_target_71003763c0(void* L) {
    FUN_71002ec1a0(*reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8));
}

// ════════════════════════════════════════════════════════════════════
// AI deprecated — distance helpers
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_7100358a80(f32, void*, void*);

// ── 0x710036ad10 -- app::ai_deprecated::get_target_vector (24B) ───
// [derived: calls FUN_7100358a80(ctx+0xc20 * param, ai_data, ctx+0xc50)]
void get_target_vector_710036ad10(void* L, f32 param) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    f32 val = *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ctx) + 0xc20);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    FUN_7100358a80(val * param, ai, reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0xc50));
}

// ════════════════════════════════════════════════════════════════════
// AI ground check
// ════════════════════════════════════════════════════════════════════

extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104471e0c;
extern "C" void FUN_71002eeb20(f32, f32, void*, s32);

// ── 0x7100367ae0 -- app::ai::check_over_ground_distance_current_lr (24B)
// [derived: calls FUN_71002eeb20(param, DAT_7104471e0c, ctx+0x180, 1)]
void check_over_ground_distance_current_lr_7100367ae0(void* L, f32 dist) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    FUN_71002eeb20(dist, DAT_7104471e0c,
        reinterpret_cast<void*>(reinterpret_cast<u8*>(ctx) + 0x180), 1);
}

// ════════════════════════════════════════════════════════════════════
// AI weapon
// ════════════════════════════════════════════════════════════════════

extern "C" void* FUN_71003596f0(void*);

// ── 0x710036b030 -- app::ai_weapon::most_earliest_weapon (36B) ────
// [derived: looks up earliest weapon via FUN_71003596f0, returns +8 or 0]
u64 most_earliest_weapon_710036b030(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* result = FUN_71003596f0(ai);
    if (result != nullptr) {
        return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(result) + 8);
    }
    return 0;
}

extern "C" void* FUN_710033ba50(u32);
extern "C" s32 FUN_71002f2820(u64, u32);

// ── 0x7100369ff0 -- app::ai::attack_is_as_weapon (160B) ───────────
// [derived: resolves cmd_id to action index, then reads weapon flag at attack_data+lVar*0xb8+6]
u8 attack_is_as_weapon_7100369ff0(void* L, u64 cmd_id) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    u32 fighter_kind = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x988);
    void* attack_data = FUN_710033ba50(fighter_kind);
    s32 action = FUN_71002f2820(cmd_id, fighter_kind);
    s64 idx = 0;
    if (static_cast<u32>(action - 0x6051) < 0x18) {
        idx = static_cast<s64>(action - 0x603b);
    }
    if (static_cast<u32>(action - 0x6041) < 0xf) {
        idx = static_cast<s64>(action - 0x6034);
    }
    if (static_cast<u32>(action - 0x6031) < 0xf) {
        idx = static_cast<s64>(static_cast<u32>(action - 0x6031));
    }
    return *reinterpret_cast<u8*>(
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(attack_data) + 8) +
        idx * 0xb8 + 6);
}

// ════════════════════════════════════════════════════════════════════
// NFP (amiibo) helpers
// ════════════════════════════════════════════════════════════════════

// ── 0x7100375f20 -- app::nfp::has_air_catch (40B) ─────────────────
// [derived: bitmask lookup — checks if fighter kind supports air catch (tether grabs)]
u32 has_air_catch_7100375f20(u32 kind) {
    u32 result = 0;
    if (kind - 3 < 0x2c) {
        result = static_cast<u32>(0x82020100043ULL >> (static_cast<u64>(kind - 3) & 0x3f)) & 1;
    }
    return result;
}

// ════════════════════════════════════════════════════════════════════
// AI air lasso count
// ════════════════════════════════════════════════════════════════════

// ── 0x7100361aa0 -- app::ai::air_lasso_count (40B) ────────────────
// [derived: reads WorkModule int at hash 0x10000049 via vtable[0x13] from fighter's accessor]
void air_lasso_count_7100361aa0(void* L) {
    void* ctx = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* ai = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x168);
    void* fighter = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ai) + 0x10);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(fighter) + 0x20));
    acc->work_module->get_int(0x10000049);
}

// ════════════════════════════════════════════════════════════════════
// AI stage — calc_offset_with_gravity
// ════════════════════════════════════════════════════════════════════

extern "C" void FUN_710160e340(void*);

// ── 0x710036b3e0 -- app::ai_stage::calc_offset_with_gravity (8B) ──
// [derived: tail-calls FUN_710160e340 with param_2 (Vector3f)]
void calc_offset_with_gravity_710036b3e0(void* p1, void* p2) {
    FUN_710160e340(p2);
}

// ════════════════════════════════════════════════════════════════════
// Misc — zero hash return
// ════════════════════════════════════════════════════════════════════

// ── 0x71003a4820 -- get_hash (8B) ─────────────────────────────────
// [derived: returns 128-bit zero]
float4 get_hash_71003a4820() {
    float4 zero = {0.0f, 0.0f, 0.0f, 0.0f};
    return zero;
}

// ════════════════════════════════════════════════════════════════════
// Item utility functions — pool-b additions
// Pure vtable-chain functions (no global references)
// ════════════════════════════════════════════════════════════════════

// ── 0x71015c12a0 -- app::item::set_bomb_countdown (100B) ─────────
// [derived: Ghidra FUN_71015c12a0 — lua_State + WorkModule set_int]
// Writes param_2 to two work int variables (0x10000015, 0x10000016)
// via WorkModule vtable[0x14] (offset 0xa0 = set_int).
void set_bomb_countdown_71015c12a0(void* L, s32 param_2) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* work = acc->work_module;
    // WorkModule::set_int — vtable[0x14] at +0xa0
    // [derived: vtable slot confirmed by cross-ref with WorkModule__set_int_impl (.dynsym)]
    // NOTE: param order may be (value, hash) — keeping raw dispatch for matching safety
    reinterpret_cast<void(*)(app::WorkModule*, s32, u32)>(work->_vt[0x14])(work, param_2, 0x10000015U);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent vtable caching across call
#endif
    reinterpret_cast<void(*)(app::WorkModule*, s32, u32)>(work->_vt[0x14])(work, param_2, 0x10000016U);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail call — original uses blr+ret, not br
#endif
}

// ── 0x71015c6c10 -- app::target::pos_2d (108B) ──────────────────
// [derived: Ghidra FUN_71015c6c10 — lua_State + WorkModule get_float]
// Returns float4{x, y, 0, 0} from WorkModule floats at indices 0xb and 0xc.
// WorkModule vtable[0x0B] (offset 0x58 = get_float).
float4 pos_2d_71015c6c10(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* work = acc->work_module;
    f32 x = work->get_float(0xb);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent vtable caching across call
#endif
    f32 y = work->get_float(0xc);
    float4 result = {x, y, 0.0f, 0.0f};
    return result;
}

// ── 0x71015cb330 -- app::item_other::change_status_lost (108B) ───
// [derived: Ghidra FUN_71015cb330 — BattleObject type check + StatusModule]
// Checks if object is an item (kind >> 28 == 4), gets item data,
// reads current status via StatusModule vtable[0x22] (+0x110 = get_status_kind),
// changes to status 6 (lost) via StatusModule vtable[0x09] (+0x48 = change_status).
void change_status_lost_71015cb330(void* param_1) {
    if (param_1 == nullptr) return;
    u32 kind = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(param_1) + 8);
    if ((kind >> 0x1c) != 4) return;

    // +0x190 → +0x220 = item sub-object
    // [derived: all item lua_bind functions use this double-deref chain]
    u8* ptr = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(param_1) + 0x190);
    u8* item_data = reinterpret_cast<u8*>(*reinterpret_cast<u64*>(ptr + 0x220));

    // StatusModule at item_data + 0xD8
    // [derived: confirmed by StatusModule dispatch in change_status_lost, Ghidra lVar3+0xd8]
    auto* status_mod = reinterpret_cast<app::StatusModule*>(
        *reinterpret_cast<void**>(item_data + 0xd8));

    s32 status = status_mod->vtbl->StatusKind(status_mod);
    if (status == 6) return;

    // reload for matching (binary reloads pointer before tail call)
    status_mod = reinterpret_cast<app::StatusModule*>(
        *reinterpret_cast<void**>(item_data + 0xd8));
    status_mod->vtbl->ChangeStatusRequest(status_mod, 6, false);
}

// ── 0x71015c1600 -- app::item::add_damage (132B) ────────────────
// [derived: Ghidra FUN_71015c1600 — lua_State + item HP subtract]
// Reads current HP from module at item_data+0xe8 (get_float index 9),
// subtracts param_2. If HP <= 0, triggers status event 0x21000002 and clamps to 0.
// Writes back via set_float (index 9).
// Module at +0xe8: vtable[0x0B](+0x58)=get_float, vtable[0x0C](+0x60)=set_float,
//   vtable[0x22](+0x110)=notify_status_event
void add_damage_71015c1600(void* L, f32 damage) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    u8* ptr = *reinterpret_cast<u8**>(acc + 0x190);
    u8* item_data = reinterpret_cast<u8*>(*reinterpret_cast<u64*>(ptr + 0x220));

    // Module at item_data+0xe8 — used for HP read/write
    // [derived: Ghidra shows lVar1+0xe8 consistently for item HP operations]
    void* mod = *reinterpret_cast<void**>(item_data + 0xe8);
    void** vt = *reinterpret_cast<void***>(mod);

    // get_float(mod, 9) — read current HP
    f32 hp = reinterpret_cast<f32(*)(void*, s32)>(vt[0x0B])(mod, 9);
    hp = hp - damage;
    if (hp <= 0.0f) {
        // notify_status_event — vtable[0x22] at +0x110
        mod = *reinterpret_cast<void**>(item_data + 0xe8);
        vt = *reinterpret_cast<void***>(mod);
        reinterpret_cast<void(*)(void*, u32)>(vt[0x22])(mod, 0x21000002U);
        hp = 0.0f;
    }
    // set_float(hp, mod, 9) — write back HP
    // [derived: s0=hp value, x0=module, w1=index; float doesn't consume integer slot in ABI]
    mod = *reinterpret_cast<void**>(item_data + 0xe8);
    vt = *reinterpret_cast<void***>(mod);
    reinterpret_cast<void(*)(f32, void*, s32)>(vt[0x0C])(hp, mod, 9);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail call — original uses blr+ret, not br
#endif
}

// ── 0x71015c29f0 -- app::item::set_force_flashing (124B) ────────
// [derived: Ghidra FUN_71015c29f0 — lua_State + item byte field writes]
// Sets the "force flashing" flag at plVar2[0x12]+0x152, and if transitioning
// from on→off, resets the flash state and calls vtable[0xa8](+0x540) to disable.
// plVar2[0x12] is the item's flash/visual state sub-object.
void set_force_flashing_71015c29f0(void* L, bool enable) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    u8* ptr = *reinterpret_cast<u8**>(acc + 0x190);
    u64* item_data = reinterpret_cast<u64*>(*reinterpret_cast<u64*>(ptr + 0x220));

    // item_data[0x12] = sub-object for flash state
    // [derived: Ghidra plVar2[0x12] = *(item_data + 0x90)]
    u8* flash_state = reinterpret_cast<u8*>(item_data[0x12]);

    if (*(flash_state + 0x151) == 0) {
        char old_val = *(flash_state + 0x152);
        *(flash_state + 0x152) = enable ? 1 : 0;
        if (old_val == 0) {
            return;
        }
    } else {
        *(flash_state + 0x152) = enable ? 1 : 0;
    }

    flash_state = reinterpret_cast<u8*>(item_data[0x12]);
    if (*(flash_state + 0x151) == 0 && *(flash_state + 0x152) == 0) {
        *reinterpret_cast<u16*>(flash_state + 0x150) = 1;
        *(flash_state + 0x152) = 0;
        void** vt = *reinterpret_cast<void***>(item_data);
        // vtable[0xa8] at +0x540 — disable flashing visual
        reinterpret_cast<void(*)(u64*, u32)>(vt[0xa8])(item_data, 1);
#ifdef MATCHING_HACK_NX_CLANG
        asm("");  // prevent tail call — original uses blr+ret with shrink-wrapped frame
#endif
    }
}

// ── 0x71015c4ad0 -- app::item::init_status_data (84B) ───────────
// [derived: Ghidra FUN_71015c4ad0 — lua_State + StatusModule init_status_data]
// Gets StatusModule at acc+0x40, calls vtable[0x39] (+0x1c8) with 10 args.
// Note: param reordering — situation_kind and kinetic_type are swapped in the call.
void init_status_data_71015c4ad0(void* L, s32 kinetic_type, s32 situation, s32 ground_correct, bool enable) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* sm = acc->status_module;
    // StatusModule::InitSettings — vtable[0x39] at +0x1c8
    // [derived: confirmed by parameter count (10) and StatusModule offset (+0x40)]
    sm->vtbl->InitSettings(sm, situation, kinetic_type, ground_correct, 0, enable, 0, 0, 0, 0);
}

// ── 0x71015c1d80 -- app::item::set_scale_speed_mul (80B) ────────
// [derived: Ghidra FUN_71015c1d80 — lua_State + item data write + conditional vtable]
// Writes scale_speed_mul float at item_data+0x27c, then calls either vtable[0x22]
// (+0x110, set event) or vtable[0x24] (+0x120, clear event) depending on whether
// the value equals 1.0. Event hash = 0x20000014.
void set_scale_speed_mul_71015c1d80(void* L, f32 mul) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    u8* ptr = *reinterpret_cast<u8**>(acc + 0x190);
    u8* item_data = reinterpret_cast<u8*>(*reinterpret_cast<u64*>(ptr + 0x220));

    void* mod = *reinterpret_cast<void**>(item_data + 0xe8);
    *reinterpret_cast<f32*>(item_data + 0x27c) = mul;
    void** vt = *reinterpret_cast<void***>(mod);

    void(*fn)(void*, u32);
    if (mul == 1.0f) {
        fn = reinterpret_cast<void(*)(void*, u32)>(vt[0x24]);  // clear event
    } else {
        fn = reinterpret_cast<void(*)(void*, u32)>(vt[0x22]);  // set event
    }
    fn(mod, 0x20000014U);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail call — original uses blr+ret
#endif
}

// NOTE: Link event functions (send_link_event_disable_clatter, send_catch_cut_event)
// need proper LinkEvent struct layout investigation. Skipped for now — struct
// alignment and vtable pointer layout don't match with naive u8[] approach.

// ════════════════════════════════════════════════════════════════════
// Item field readers — pure leaf functions, chain deref from lua state
// Pattern: lua[-8]→+0x1a0→+0x190→+0x220→+OFFSET → return u32
// [derived: Ghidra — item data accessed via module accessor +0x190 (item module)
//  →+0x220 (item data base). Community-named fields.]
// ════════════════════════════════════════════════════════════════════

// Helper: get item data base pointer from lua state
#define ITEM_DATA(L) (*reinterpret_cast<u8**>( \
    *reinterpret_cast<u8**>( \
        *reinterpret_cast<u8**>( \
            *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8) + 0x1a0 \
        ) + 0x190 \
    ) + 0x220 \
))

// 0x71015c1dd0 (24B) — app::item::variation — leaf, returns item variant index
// [derived: Ghidra — item_data + 0x258 (600 decimal). Also labeled as 'variation' in decompile]
extern "C" u32 variation_71015c1dd0(void* L) {
    return *reinterpret_cast<u32*>(ITEM_DATA(L) + 0x258);
}

// 0x71015c1f40 (24B) — app::item::owner_id — returns ID of owner fighter
// [derived: Ghidra — item_data + 0x250]
extern "C" u32 owner_id_71015c1f40(void* L) {
    return *reinterpret_cast<u32*>(ITEM_DATA(L) + 0x250);
}

// 0x71015c2060 (28B) — app::item::enable_lost_flashing — stores bool at item_data+0x29f
// [derived: Ghidra — pure leaf store: *(item_data + 0x29f) = param_2]
extern "C" void enable_lost_flashing_71015c2060(void* L, bool val) {
    *(ITEM_DATA(L) + 0x29f) = val;
}

// 0x71015c1fc0 (28B) — app::item::set_effect_sync_visibility_default
// [derived: Ghidra — pure leaf store: *(item_data + 0x29b) = param_2]
extern "C" void set_effect_sync_visibility_default_71015c1fc0(void* L, bool val) {
    *(ITEM_DATA(L) + 0x29b) = val;
}

#undef ITEM_DATA

// NOTE: DAISY/DOLL/EXPLOSIONBOMB param functions (0x710165xxxx) need non-hidden
// FPA2 singleton access (GOT-style double deref). They belong in a separate TU

// ── 0x71015c55c0 -- app::item::init_explosion_no_damage (144B) ──
// [derived: init_explosion_no_damage (community name) — 3 vtable calls:
//  work_module->set_int(item_param_accessor[0x72ffc], 0x10000010),
//  attack_module->clear_all(2, 0),
//  work_module->on_flag(0x20000017)]
void init_explosion_no_damage_71015c55c0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));

    auto* work_mod = acc->work_module;
    u8* ipa = *reinterpret_cast<u8**>(DAT_71052c31e0);
    u32 param_val = *reinterpret_cast<u32*>(ipa + 0x72ffc);
    work_mod->set_int(param_val, 0x10000010);

    ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    acc->hit_module->set_whole(2, 0);

    work_mod->on_flag(0x20000017);
}

// ── 0x71015c1570 -- app::item::disable_area (136B) ──────────────
// [derived: disable_area (community name) — if kind==3, checks sub-module count
//  via vtable chain from [item_data+0x90]; if count>=4, clears byte and calls
//  area disable. Otherwise uses [item_data+0x158] directly.]
void disable_area_71015c1570(void* L, s32 param_2) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    u8* ptr = *reinterpret_cast<u8**>(acc + 0x190);
    u8* item_data = *reinterpret_cast<u8**>(ptr + 0x220);

    if (param_2 != 3) {
        void* area_mod = *reinterpret_cast<void**>(item_data + 0x158);
        void** vt = *reinterpret_cast<void***>(area_mod);
        reinterpret_cast<void(*)(void*, s32, s32, s32)>(vt[0xc0/8])(area_mod, param_2, 0, -1);
        return;
    }
    u8* mod = *reinterpret_cast<u8**>(item_data + 0x90);
    void* sub = *reinterpret_cast<void**>(*reinterpret_cast<u64*>(mod) + 0xc0);
    void** sub_vt = *reinterpret_cast<void***>(sub);
    s32 count = reinterpret_cast<s32(*)(void*)>(sub_vt[0xb8/8])(sub);
    if (count < 4) return;
    *(u8*)(mod + 0x1c) = 0;
    sub = *reinterpret_cast<void**>(*reinterpret_cast<u64*>(mod) + 0xc0);
    sub_vt = *reinterpret_cast<void***>(sub);
    reinterpret_cast<void(*)(void*, s32, s32, s32)>(sub_vt[0xc0/8])(sub, 3, 0, -1);
}

// ── 0x71015c6ea0 -- app::target::distance_x (92B) ──────────────
// [derived: distance_x (community name) — gets target x from work_module(0xb),
//  self x from posture_module->get_pos(), returns absolute difference]
f32 distance_x_71015c6ea0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));

    f32 target_x = acc->work_module->get_float(0xb);
    f32* pos = acc->posture_module->pos();

    return __builtin_fabsf(target_x - pos[0]);
}

// ── 0x71015c6f00 -- app::target::distance_y (92B) ──────────────
// [derived: distance_y (community name) — same as distance_x but reads
//  work_module(0xc) for target y and pos[1] for self y]
f32 distance_y_71015c6f00(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));

    f32 target_y = acc->work_module->get_float(0xc);
    f32* pos = acc->posture_module->pos();

    return __builtin_fabsf(target_y - pos[1]);
}
// where DAT_71052bb3b0 is declared without __attribute__((visibility("hidden"))).

// ════════════════════════════════════════════════════════════════════
// sv_fighter_util — item motion rate lookups
// ════════════════════════════════════════════════════════════════════

// FighterParamAccessor2 singleton (via C++ mangled name)
// [derived: lib::Singleton<app::FighterParamAccessor2>::instance_ for sv_fighter_util functions]
namespace lib_sv {
    extern "C" void* Singleton_app_FighterParamAccessor2_instance_sv
        asm("_ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E")
        __attribute__((visibility("hidden")));
}
#define FPA2_SV (reinterpret_cast<u8*>(lib_sv::Singleton_app_FighterParamAccessor2_instance_sv))

// ── 0x7102282110 -- app::sv_fighter_util::get_item_swing_motion_rate (140B) ──
// Returns motion rate float for item swing animation based on fighter param index
// and swing type (0-4). Each fighter has a 0x14-byte entry with 5 floats.
// Returns 1.0f if swing_type >= 5.
// [derived: Ghidra FUN_7102282110 — FPA2+0x50→+4000 (0xFA0) base table,
//  indexed by fighter_param_idx * 0x14 + swing_type * 4. Switch on swing_type.]
f32 get_item_swing_motion_rate_7102282110(void* L, s32 fighter_param_idx, s32 swing_type) {
    // Target uses ldrsw jump table (NX Clang), upstream uses ldrb — can't match jump table encoding.
    // Code is structurally correct.
    if ((u32)swing_type > 4) return 1.0f;
    u8* fpa2 = FPA2_SV;
    u8* table = reinterpret_cast<u8*>(*reinterpret_cast<u64*>(*reinterpret_cast<u64*>(fpa2 + 0x50) + 0xfa0));
    f32* entry = reinterpret_cast<f32*>(table + (s64)fighter_param_idx * 20);
    switch (swing_type) {
    case 0: return entry[0];
    case 1: return entry[1];
    case 2: return entry[2];
    case 3: return entry[3];
    case 4: return entry[4];
    }
    __builtin_unreachable();
}

#undef FPA2_SV

// ════════════════════════════════════════════════════════════════════
// sv_kinetic — energy enable/disable/clear via KineticModule vtable
// ════════════════════════════════════════════════════════════════════

// ── 0x71022087b0 -- sv_kinetic::disable_energy_pair (96B) ────────
// Disables kinetic energy for entries 0xc and 0xd by clearing flag at +0x30.
// [derived: Ghidra FUN_71022087b0 — kinetic_module (+0x68) → vtable[0x60/8=12]
//  with params 0xc, 0xd → strb wzr at result+0x30. Returns 0]
u64 FUN_71022087b0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* kinetic = acc->item_kinetic_module;

    auto* e1 = kinetic->get_energy(0xc);
    auto* e2 = kinetic->get_energy(0xd);

    e1->enabled = 0;  // disable flag
    e2->enabled = 0;
    return 0;
}

// ── 0x7102208890 -- sv_kinetic::enable_energy_pair (96B) ─────────
// Enables kinetic energy for entries 0xc and 0xd by setting flag at +0x30 to 1.
// [derived: Ghidra FUN_7102208890 — identical to 71022087b0 but stores 1]
u64 FUN_7102208890(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* kinetic = acc->item_kinetic_module;

    auto* e1 = kinetic->get_energy(0xc);
    auto* e2 = kinetic->get_energy(0xd);

    e1->enabled = 1;  // enable flag
    e2->enabled = 1;
    return 0;
}

// ── 0x71022086b0 -- sv_kinetic::clear_energy_pair (128B) ─────────
// Clears kinetic energy controllers 0xc and 0xd via vtable[9] call.
// [derived: Ghidra FUN_71022086b0 — kinetic_module → vtable[12](0xc,0xd)
//  → then result→vtable[0x48/8=9]() clear call on each. Returns 0]
u64 FUN_71022086b0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* kinetic = acc->item_kinetic_module;

    auto* e1 = kinetic->get_energy(0xc);
    auto* e2 = kinetic->get_energy(0xd);

    e1->clear_speed();
    e2->clear_speed();
    return 0;
}

// ── 0x710221e7c0 -- sv_kinetic::get_energy_flag (160B) ───────────
// Gets the enable flag from kinetic energy controller 1 and pushes to lua stack.
// [derived: Ghidra FUN_710221e7c0 — kinetic_module → vtable[12](kinetic,1)
//  → ldrb result+0x30 → store (uint)byte to lua stack, advance stack ptr. Returns 1]
u64 FUN_710221e7c0(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    auto* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *reinterpret_cast<void**>(ctx + 0x1a0));
    auto* kinetic = acc->item_kinetic_module;

    auto* energy = kinetic->get_energy(1);

    // Read enable flag at +0x30
    u32 flag = energy->enabled;

    // Push to lua stack: [param+0x10] points to stack slot
    u32* stack = *reinterpret_cast<u32**>(reinterpret_cast<u8*>(L) + 0x10);
    stack[0] = flag;
    stack[2] = 1;  // type tag
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) += 0x10;
    return 1;
}

// ────────────────────────────────────────────────────────────
// Fighter utility functions — status-related helpers
// ────────────────────────────────────────────────────────────

// ── 0x71006937e0 -- FighterUtil::get_handi (72B) ────────────
// Returns handicap value for a fighter entry. Returns 0.0 if handi mode is disabled.
// [derived: loads FighterManager singleton → checks +0xCD (handi_enabled),
//  then entries[entry_id] → FighterInformationData (+0xF8) → handi (+0x370)]
f32 get_handi_71006937e0(u32 entry_id) {
    if (entry_id >= 8) { abortWrapper_71039c20a0(); }
    auto* mgr_data = reinterpret_cast<app::FighterManagerData*>(
        *reinterpret_cast<void**>(DAT_71052b84f8));
    if (!mgr_data->handi_enabled) return 0.0f;
    auto* entry = reinterpret_cast<u8*>(mgr_data->entries[entry_id]);
    auto* fi_data = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
    return static_cast<f32>(fi_data->handi);
}

// ── 0x7100693da0 -- FighterUtil::yoshi_egg_time_mul (76B) ───
// Returns the Yoshi egg time multiplier for the fighter owning this accessor.
// [derived: work_module→get_int(0x10000000) to get entry_id,
//  then entries[entry_id] → FighterInformationData (+0xF8) → +0x380 (yoshi_egg_time_mul)]
f32 yoshi_egg_time_mul_7100693da0(app::BattleObjectModuleAccessor* acc) {
    u32 entry_id = acc->work_module->get_int(0x10000000);
    if (entry_id >= 8) { abortWrapper_71039c20a0(); }
    auto* mgr_data = reinterpret_cast<app::FighterManagerData*>(
        *reinterpret_cast<void**>(DAT_71052b84f8));
    auto* entry = reinterpret_cast<u8*>(mgr_data->entries[entry_id]);
    auto* fi_data = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
    return fi_data->yoshi_egg_time_mul;
}

// ── 0x7100693df0 -- FighterUtil::is_hp_mode (96B) ───────────
// Returns whether HP mode is enabled for the fighter.
// [derived: work_module→get_int(0x10000000) = entry_id,
//  mgr_data+0xC3 is global hp_mode flag,
//  then entries[entry_id]+0xF8→+0x90 is per-fighter hp flag]
// Note: FighterManagerData+0xC3 is currently unmapped — raw access required for this byte.
u8 is_hp_mode_7100693df0(app::BattleObjectModuleAccessor* acc) {
    u32 entry_id = acc->work_module->get_int(0x10000000);
    auto* mgr_data = reinterpret_cast<app::FighterManagerData*>(
        *reinterpret_cast<void**>(DAT_71052b84f8));
    // Check global HP mode flag
    // [derived: is_hp_mode disasm checks ldrb [x8, #0xC3] != 0]
    if (mgr_data->hp_mode_global != 0) return 1;
    if (entry_id >= 8) { abortWrapper_71039c20a0(); }
    auto* entry = reinterpret_cast<u8*>(mgr_data->entries[entry_id]);
    // entry+0xF8 = FighterInformationData->data, +0x90 = per-fighter hp flag
    // [derived: is_hp_mode disasm loads ldrb [x8, #0x90] from FighterInformationData]
    auto* fi_data = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
    return fi_data->hp_mode_fighter;
}

// ────────────────────────────────────────────────────────────
// AI status accessors — used by CPU AI scripts
// ────────────────────────────────────────────────────────────

// ── 0x7100361c10 -- app::ai::status_kind (12B) ─────────────
// Returns the current status_kind of the AI's own fighter.
// [derived: FighterAI→state→status_kind]
u32 ai_status_kind_7100361c10(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    return ai->state->status_kind;
}

// ── 0x7100361c20 -- app::ai::prev_status_kind (12B) ────────
// Returns the previous status_kind of the AI's own fighter.
// [derived: FighterAI→state→prev_status_kind]
u32 ai_prev_status_kind_7100361c20(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    return ai->state->prev_status_kind;
}

// ── 0x710036a570 -- app::ai_notify_event::status_kind (40B) ─
// Helper: get BattleObjectModuleAccessor from AI event notify chain
// [derived: FighterAI→state→accessor_chain→+0x20 = BattleObjectModuleAccessor*]
struct AIEventChain {
    u8 pad_0x00[0x20];
    app::BattleObjectModuleAccessor* accessor;  // +0x20 [derived: notify_event functions deref +0x20]
};
static inline app::BattleObjectModuleAccessor* get_ai_event_accessor(FighterAI* ai) {
    auto* chain = static_cast<AIEventChain*>(ai->state->accessor_chain);
    return chain->accessor;
}

// Returns status_kind of the BattleObject associated with an AI notify event.
// [derived: FighterAI→state→accessor_chain→+0x20 = BattleObjectModuleAccessor,
//  then acc→status_module→vtable→StatusKind()]
void ai_notify_event_status_kind_710036a570(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    auto* acc = get_ai_event_accessor(ai);
    auto* status_mod = static_cast<app::StatusModule*>(acc->status_module);
    status_mod->vtbl->StatusKind(status_mod);
}

// ────────────────────────────────────────────────────────────
// Ground/position utility functions
// ────────────────────────────────────────────────────────────

// ── 0x710069bf80 -- FighterUtil::get_pos_on_line (44B) ──────
// Computes position on a ground collision line. Tail call to internal helper.
// [derived: disasm shows 1 instruction: b FUN_710069bfb0]
extern "C" void get_pos_on_line_impl_710069bfb0(
    app::BattleObjectModuleAccessor*, void*, f32, f32, void*);

void get_pos_on_line_710069bf80(
    app::BattleObjectModuleAccessor* acc, void* line, f32 p2, f32 p3, void* out_vec) {
    get_pos_on_line_impl_710069bfb0(acc, line, p2, p3, out_vec);
}

// ── 0x710069cc40 -- FighterUtil::is_neighbor_floor_line (72B)
// Checks if two ground collision lines are neighbors (bidirectional check).
// [derived: calls FUN_710069cc90 both ways, returns true only if both succeed]
extern "C" bool check_line_neighbor_710069cc90(void* line_a, void* line_b, bool flag);

bool is_neighbor_floor_line_710069cc40(void* line_a, void* line_b) {
    if (!check_line_neighbor_710069cc90(line_a, line_b, true)) return false;
    return check_line_neighbor_710069cc90(line_b, line_a, true);
}

// get_cliff_trans (0x7100694190, 80B) — deferred: needs Vector3f struct for reviewer compliance

// ────────────────────────────────────────────────────────────
// AI weapon accessors — used by CPU AI for projectile tracking
// ────────────────────────────────────────────────────────────

// ── 0x710036b0f0 -- ai_weapon::pos_x (20B) ─────────────────
// Returns X position of an AI weapon target, or 0.0 if null.
// Uses FighterAIWeapon (see include/app/placeholders/FighterAI.h for related types)
// [derived: null check param_2, then ldr s0 at +0x40]
f32 ai_weapon_pos_x_710036b0f0(void* L, void* weapon) {
    if (!weapon) return 0.0f;
    return *reinterpret_cast<f32*>(static_cast<u8*>(weapon) + 0x40);
}

// ── 0x710036b110 -- ai_weapon::speed_x (20B) ────────────────
// Returns X speed of an AI weapon target, or 0.0 if null.
// [derived: null check param_2, then ldr s0 at +0x50]
f32 ai_weapon_speed_x_710036b110(void* L, void* weapon) {
    if (!weapon) return 0.0f;
    return *reinterpret_cast<f32*>(static_cast<u8*>(weapon) + 0x50);
}

// ── 0x710036a590 -- ai_notify_event::motion_kind (32B) ──────
// Returns motion_kind of the BattleObject in an AI notify event.
// [derived: FighterAI→state→accessor_chain→+0x20 = accessor,
//  accessor→motion_module→vtable→motion_kind() = vtable+0x138]
void ai_notify_event_motion_kind_710036a590(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    auto* acc = get_ai_event_accessor(ai);
    auto* motion = acc->motion_module;
    reinterpret_cast<u64(*)(app::MotionModule*)>(motion->_vt[0x138 / 8])(motion);
}

// ── 0x7100376730 -- ai_system::is_input_available_for_entry (56B)
// Returns true if input is available for the fighter (inverts ControlModule check).
// [derived: FighterAI→state→accessor_chain→+0x20 = accessor,
//  accessor→control_module→vtable+0x288 (is_disable_input), inverted result]
u32 is_input_available_for_entry_7100376730(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    auto* acc = get_ai_event_accessor(ai);
    auto* ctrl = acc->fighter_control_module;
    u32 disabled = reinterpret_cast<u32(*)(app::ControlModule*)>(
        ctrl->_vt[0x288 / 8])(ctrl);
    return (~disabled) & 1;
}

// ────────────────────────────────────────────────────────────
// AI rule/param functions — decision-making helpers
// ────────────────────────────────────────────────────────────

// Helper: get FighterAIManager singleton
// [derived: DAT_71052b5fd8 = lib::Singleton<FighterAIManager>::instance_]
static inline FighterAIManager* get_ai_manager() {
    return static_cast<FighterAIManager*>(*static_cast<void**>(DAT_71052b5fd8));
}

// ── 0x710036b580 -- ai_rule::is_1on1 (64B) ─────────────────
// Returns true if this is a 1v1 match for the AI's fighter.
// Checks FighterAIManager→player_count == 2, then whether this fighter's
// player slot is alive.
// [derived: FighterAIManager→player_count==2, then player_alive[player_index]==1]
bool ai_rule_is_1on1_710036b580(void* L) {
    auto* ai = get_ai_context(reinterpret_cast<u64>(L));
    auto* mgr = get_ai_manager();
    if (mgr->player_count != 2) return false;
    s32 player_idx = ai->state->player_index;
    return mgr->player_alive[player_idx] == 1;
}

// target_chanced_frame (0x7100376bb0) and escape_air_slide_move_distance (0x710036ba20)
// deferred: need typed FighterAIManager analyst array struct to meet cast density limit
