#include "types.h"

// StageManager -- operates on StageManager* directly

struct StageManager;

extern "C" void FUN_71026084c0(void*, bool);
extern "C" void FUN_71039c20a0(void*);

namespace app::lua_bind {

// 71021455a0 -- ldr x0,[x0]; and w1,w1,#0x1; b external
void StageManager__stage_all_stop_impl(StageManager* sm, bool val) {
    FUN_71026084c0(*reinterpret_cast<void**>(sm), val);
}

// 71021455b0 -- load inner, check mode field at +0x17c
// mode == -1 → return true
// mode >= 3 (unsigned) → abort
// mode 0..2 → vtable call at index 0x4a0/8 of entry at inner + mode*8 + 0x110
bool StageManager__is_discretion_final_enabled_impl(StageManager* sm) {
    auto* inner = *reinterpret_cast<u8**>(sm);
    s32 mode = *reinterpret_cast<s32*>(inner + 0x17c);
    if (mode == -1) return true;
    if ((u32)mode >= 3u) {
        FUN_71039c20a0(sm);
        __builtin_unreachable();
    }
    auto* entry = *reinterpret_cast<void**>(inner + (u64)(u32)mode * 8 + 0x110);
    auto fn = reinterpret_cast<bool (*)(void*)>((*reinterpret_cast<void***>(entry))[0x4a0/8]);
    return fn(entry);
}

} // namespace app::lua_bind
