#include "app/BattleObjectModuleAccessor.h"

// EffectModule — accessor+0x140 (accessed via raw offset)
#define EFFECT_MODULE(acc) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x140))
#define VTABLE(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 71020178c0 — detach_all [vtable+0xf8]
void EffectModule__detach_all_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0xf8 / 8])(m, p1);
}

// 71020178d0 — detach_kind [vtable+0x100]
void EffectModule__detach_kind_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x100 / 8])(m, p1);
}

// 71020178e0 — detach [vtable+0x108]
void EffectModule__detach_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x108 / 8])(m, p1);
}

// 71020178f0 — end_kind [vtable+0x110]
void EffectModule__end_kind_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x110 / 8])(m, p1);
}

// 71020179a0 — clear_all_after_image [vtable+0x130]
void EffectModule__clear_all_after_image_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*)>(VTABLE(m)[0x130 / 8])(m);
}

// 7102017ac0 — fill_screen [vtable+0x1d0]
void EffectModule__fill_screen_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x1d0 / 8])(m, p1);
}

// 7102017ad0 — fill_screen_2 [vtable+0x1d8]
void EffectModule__fill_screen_2_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x1d8 / 8])(m, p1);
}

// 7102017ae0 — color_collection [vtable+0x1e0]
void EffectModule__color_collection_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x1e0 / 8])(m, p1);
}

// 7102017af0 — clear_screen [vtable+0x1e8]
void EffectModule__clear_screen_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x1e8 / 8])(m, p1);
}

// 7102017b10 — get_dead_effect_rot_z (bool param, and w2 #1) [vtable+0x210]
f32 EffectModule__get_dead_effect_rot_z_impl(BattleObjectModuleAccessor* accessor, u64 p1, bool p2) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<f32 (*)(void*, u64, bool)>(VTABLE(m)[0x210 / 8])(m, p1, p2);
}

// 7102017b30 — get_dead_effect_scale (bool param) [vtable+0x218]
f32 EffectModule__get_dead_effect_scale_impl(BattleObjectModuleAccessor* accessor, u64 p1, bool p2) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<f32 (*)(void*, u64, bool)>(VTABLE(m)[0x218 / 8])(m, p1, p2);
}

// 7102017b50 — is_dead_effect_slant [vtable+0x220]
bool EffectModule__is_dead_effect_slant_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<bool (*)(void*, u64)>(VTABLE(m)[0x220 / 8])(m, p1);
}

// 7102017b90 — is_end_common [vtable+0x248]
bool EffectModule__is_end_common_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<bool (*)(void*, u64)>(VTABLE(m)[0x248 / 8])(m, p1);
}

// 7102017c60 — get_variation_effect_kind [vtable+0x2c0]
s32 EffectModule__get_variation_effect_kind_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<s32 (*)(void*, u64)>(VTABLE(m)[0x2c0 / 8])(m, p1);
}

// 7102017d80 — get_last_handle [vtable+0x3a0]
u64 EffectModule__get_last_handle_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<u64 (*)(void*)>(VTABLE(m)[0x3a0 / 8])(m);
}

// 7102017d90 — is_enable_ground_effect [vtable+0x3e8]
bool EffectModule__is_enable_ground_effect_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<bool (*)(void*)>(VTABLE(m)[0x3e8 / 8])(m);
}

// 7102017e30 — enable_sync_init_pos_last [vtable+0x440]
void EffectModule__enable_sync_init_pos_last_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x440 / 8])(m, p1);
}

// 7102017ed0 — enable_stencil (bool param) [vtable+0x488]
void EffectModule__enable_stencil_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x488 / 8])(m, p1);
}

// 7102017ef0 — force_update_common_effect [vtable+0x490]
void EffectModule__force_update_common_effect_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*)>(VTABLE(m)[0x490 / 8])(m);
}

} // namespace app::lua_bind
