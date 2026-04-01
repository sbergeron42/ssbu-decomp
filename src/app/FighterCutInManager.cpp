#include "types.h"

// FighterCutInManager — operates on FighterCutInManager* directly
// Inner data pointer at [x0]. Fields accessed through that pointer.

struct FighterCutInManager;

namespace app::lua_bind {

// 71020a8cd0 — add_task: array append pattern
// ldr x8,[x0]; ldp x9,x10,[x8,#0x88]; str w1,[x10,x9,LSL#2];
// ldr x9,[x8,#0x88]; add x9,x9,#1; str x9,[x8,#0x88]; ret
void FighterCutInManager__add_task_impl(FighterCutInManager* mgr, u32 task_id) {
    auto* data = *reinterpret_cast<char**>(mgr);
    auto idx = *reinterpret_cast<u64*>(data + 0x88);
    auto* arr = *reinterpret_cast<u32**>(data + 0x90);
    arr[idx] = task_id;
    *reinterpret_cast<u64*>(data + 0x88) = *reinterpret_cast<u64*>(data + 0x88) + 1;
}

// 71020a8cf0 — ldr x8,[x0]; str s0,[x8,#0x2d0]; ret
void FighterCutInManager__set_throw_finish_zoom_rate_impl(FighterCutInManager* mgr, f32 rate) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    *reinterpret_cast<f32*>(data + 0x2d0) = rate;
}

// 71020a8b90 — ldr x0,[x0]; b external
extern "C" void FUN_71006a7100(void*);
void FighterCutInManager__request_start_impl(FighterCutInManager* mgr) {
    FUN_71006a7100(*reinterpret_cast<void**>(mgr));
}

// 71020a8ba0 — ldr x0,[x0]; b external
extern "C" void FUN_71006ab9d0(void*);
void FighterCutInManager__request_end_impl(FighterCutInManager* mgr) {
    FUN_71006ab9d0(*reinterpret_cast<void**>(mgr));
}

// 71020a8bb0 — check byte at data+0xb9, then word at data+0xbc == 6
bool FighterCutInManager__is_play_motion_camera_impl(FighterCutInManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    if (data[0xb9] == 0) return false;
    return *reinterpret_cast<u32*>(data + 0xbc) == 6;
}

// 71020a8be0 — unrolled check: compare 8 u32s at data[0..0x1c] against param2->field_8
bool FighterCutInManager__is_owner_impl(FighterCutInManager* mgr, void* entry_id_ptr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    u32 target = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry_id_ptr) + 8);
    u32* arr = reinterpret_cast<u32*>(data);
    if (arr[0] != target && arr[1] != target && arr[2] != target && arr[3] != target &&
        arr[4] != target && arr[5] != target && arr[6] != target && arr[7] != target) {
        return false;
    }
    return true;
}

// 71020a8c60 — check 3 conditions: byte +0xb9, byte +0x1e8, s32 at +0x398 > 0
bool FighterCutInManager__is_play_impl(FighterCutInManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    if (data[0xb9]) return true;
    if (data[0x1e8]) return true;
    return *reinterpret_cast<s32*>(data + 0x398) > 0;
}

// 71020a8ca0 — check byte +0xb9, then byte +0x1e8 != 0
bool FighterCutInManager__is_play_status_impl(FighterCutInManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    if (data[0xb9]) return true;
    return data[0x1e8] != 0;
}

// 71020a8d00 — set_throw_finish_offset: SIMD vec store with w-component zeroing + flag set
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterCutInManager__set_throw_finish_offset_impl(FighterCutInManager* mgr) {
    asm("fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "ldr x8, [x0]\n"
        "mov v2.s[1], v1.s[0]\n"
        "orr w9, wzr, #1\n"
        "strb w9, [x8, #0x2d4]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0x2e0]\n"
        "ret\n");
}
#endif

} // namespace app::lua_bind
