#include "types.h"

// Audio/BGM/SE functions -- pool-c assignment

extern "C" __attribute__((visibility("hidden"))) void* DAT_7105328f38;  // bgm system ptr
extern "C" __attribute__((visibility("hidden"))) float DAT_7104471e0c;  // volume divisor
extern "C" __attribute__((visibility("hidden"))) float DAT_7104471598;  // volume multiplier
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;  // StageManager/ParamAccessor2 singleton
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7ef8;  // BossManager singleton
extern "C" __attribute__((visibility("hidden"))) void* DAT_71053299d8;  // StageManager indirect ptr

extern "C" void FUN_71023ee610(void*, u32, u32);
extern "C" void FUN_7102608770(void*);
extern "C" void FUN_71004e9e30(void*, u32);
extern "C" void FUN_71015c1770(void*, u32, u64, u32, void*, u64, u32);

namespace app::kozukatasight {

// 7101647180 (48B) -- convert uint volume to normalized float, call bgm setter
// s0 (float param_1) is live, so ucvtf uses s1 not s0; scheduling differs too.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void set_bgm_volume(float, u32) {
    asm(
        "ucvtf s1, w0\n"
        "adrp x8, DAT_7104471e0c\n"
        "ldr s2, [x8, :lo12:DAT_7104471e0c]\n"
        "adrp x8, DAT_7104471598\n"
        "fdiv s1, s1, s2\n"
        "ldr s2, [x8, :lo12:DAT_7104471598]\n"
        "adrp x8, DAT_7105328f38\n"
        "ldr x0, [x8, :lo12:DAT_7105328f38]\n"
        "fmul s1, s1, s2\n"
        "fcvtzu w2, s1\n"
        "mov w1, #0x1\n"
        "b FUN_71023ee610\n"
    );
}
#endif

// 7101647200 (64B) -- stop and disable two sound effector vtable slots on SoundModule
// Non-leaf; NX Clang schedules add-x29 before the ldr x19 (prologue scheduling divergence).
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void end_sound_effector(void*, float) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x19, [x0, #0x148]\n"
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x2b8]\n"
        "mov x0, x19\n"
        "mov w1, wzr\n"
        "blr x8\n"
        "ldr x8, [x19]\n"
        "ldr x2, [x8, #0x2b0]\n"
        "mov x0, x19\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov w1, wzr\n"
        "ldr x19, [sp], #0x20\n"
        "br x2\n"
    );
}
#endif

} // namespace app::kozukatasight

namespace app::shiokarazu {

// 710164bd50 (16B) -- invalid_bgm_handle: sentinel for "no bgm handle"
u32 invalid_bgm_handle(void) { return 0xffffffff; }

} // namespace app::shiokarazu

namespace app::kiiladarzmanager {

// 71016538d0 (16B) -- stop_stage_sound: delegate via StageManager indirect
void stop_stage_sound(void) {
    FUN_7102608770(*reinterpret_cast<void**>(DAT_71053299d8));
}

} // namespace app::kiiladarzmanager

namespace app::buddybomb {

// 71016595c0 (32B) -- bound_se_speed_less: read float field from nested param accessor
float bound_se_speed_less(void) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<float*>(inner + 0x2b0);
}

} // namespace app::buddybomb

namespace app::item {

// 71015c1a10 (32B) -- request cut-in without BGM volume change; passes fixed Hash40 + false
void request_cut_in_from_param_with_target_no_bgm_volume_change(
        void* p1, u32 p2, u64 p3, u32 p4, void* p5) {
    FUN_71015c1770(p1, p2, p3, p4, p5, 0x7fb997a80ULL, 0u);
}

} // namespace app::item

namespace app::boss_private {

// 71015c85e0 (64B) -- notify boss bgm keyoff if BossManager singleton is live
// Conditional non-leaf: frame set up only in non-null path; upstream would tail-call, NX doesn't.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void send_event_on_boss_keyoff_bgm(void*) {
    asm(
        "adrp x8, DAT_71052b7ef8\n"
        "ldr x8, [x8, :lo12:DAT_71052b7ef8]\n"
        "cbz x8, 0f\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldur x9, [x0, #-0x8]\n"
        "ldr x0, [x8, #0x8]\n"
        "ldr x9, [x9, #0x1a0]\n"
        "ldr x9, [x9, #0x190]\n"
        "ldr x9, [x9, #0x220]\n"
        "ldr w1, [x9, #0xc]\n"
        "bl FUN_71004e9e30\n"
        "ldp x29, x30, [sp], #0x10\n"
        "0:\n"
        "ret\n"
    );
}
#endif

} // namespace app::boss_private
