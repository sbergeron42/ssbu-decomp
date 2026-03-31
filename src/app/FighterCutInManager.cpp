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

// Skip: request_start_impl (ldr x0,[x0]; b to unknown target)
// Skip: request_end_impl (ldr x0,[x0]; b to unknown target)

} // namespace app::lua_bind
