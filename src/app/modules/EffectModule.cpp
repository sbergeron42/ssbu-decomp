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
void EffectModule__detach_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x100/8])(m,p1,p2); }

// 71020178e0 — detach [vtable+0x108]
void EffectModule__detach_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x108/8])(m,p1,p2); }

// 71020178f0 — end_kind [vtable+0x110]
void EffectModule__end_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x110/8])(m,p1,p2); }

// 71020179a0 — clear_all_after_image [vtable+0x130]
void EffectModule__clear_all_after_image_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x130/8])(m,p1); }

// 7102017ac0 — fill_screen [vtable+0x1d0]
void* EffectModule__fill_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64,u64)>(VTABLE(m)[0x1d0/8])(m,p1,p2,p3,p4,p5,p6); }

// 7102017ad0 — fill_screen_2 [vtable+0x1d8]
void* EffectModule__fill_screen_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64,u64)>(VTABLE(m)[0x1d8/8])(m,p1,p2,p3,p4,p5,p6); }

// 7102017ae0 — color_collection [vtable+0x1e0]
void* EffectModule__color_collection_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64,u64)>(VTABLE(m)[0x1e0/8])(m,p1,p2,p3,p4,p5,p6); }

// 7102017af0 — clear_screen [vtable+0x1e8]
void EffectModule__clear_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x1e8/8])(m,p1,p2); }

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
bool EffectModule__is_end_common_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<bool(*)(void*)>(VTABLE(m)[0x248/8])(m); }

// 7102017c60 — get_variation_effect_kind [vtable+0x2c0]
u32 EffectModule__get_variation_effect_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<u32(*)(void*,u64,u64)>(VTABLE(m)[0x2c0/8])(m,p1,p2); }

// 7102017d80 — get_last_handle [vtable+0x3a0]
u64 EffectModule__get_last_handle_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<u64 (*)(void*)>(VTABLE(m)[0x3a0 / 8])(m);
}

// 7102017d90 — is_enable_ground_effect [vtable+0x3e8]
bool EffectModule__is_enable_ground_effect_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); return reinterpret_cast<bool (*)(void*)>(VTABLE(m)[0x3e8 / 8])(m);
}

// 7102017e30 — enable_sync_init_pos_last [vtable+0x440]
void EffectModule__enable_sync_init_pos_last_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x440/8])(m); }

// 7102017ed0 — enable_stencil (bool param) [vtable+0x488]
void EffectModule__enable_stencil_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x488 / 8])(m, p1);
}

// 7102017ef0 — force_update_common_effect [vtable+0x490]
void EffectModule__force_update_common_effect_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = EFFECT_MODULE(accessor); reinterpret_cast<void (*)(void*)>(VTABLE(m)[0x490 / 8])(m);
}

// Expanded EffectModule dispatchers
void EffectModule__req_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,u64,bool,u64)>(VTABLE(m)[0x68/8])(m,p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_attach_ground_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6,u64 p7) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,u64,u64,u64)>(VTABLE(m)[0x78/8])(m,p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_continual_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64)>(VTABLE(m)[0x88/8])(m,p1,p2,p3,p4); }
void EffectModule__remove_continual_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x90/8])(m,p1); }
void EffectModule__remove_all_continual_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x98/8])(m); }
void EffectModule__req_time_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,bool p7) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,u64,bool,bool)>(VTABLE(m)[0xa0/8])(m,p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_time_follow_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,u64,bool,u64)>(VTABLE(m)[0xa8/8])(m,p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__remove_time_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0xb0/8])(m,p1); }
void EffectModule__remove_all_time_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0xb8/8])(m); }
void EffectModule__req_emit_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0xc0/8])(m,p1,p2); }
void EffectModule__remove_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0xc8/8])(m,p1,p2); }
void EffectModule__remove_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0xd0/8])(m,p1,p2); }
void EffectModule__kill_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xd8/8])(m,p1,p2,p3); }
void EffectModule__kill_kind_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xe0/8])(m,p1,p2,p3); }
void EffectModule__kill_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xe8/8])(m,p1,p2,p3); }
void EffectModule__kill_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xf0/8])(m,p1,p2,p3); }
void EffectModule__remove_after_image_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x138/8])(m,p1,p2); }
void EffectModule__remove_all_after_image_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x140/8])(m,p1,p2); }
void EffectModule__set_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x150/8])(m,p1,p2); }
void EffectModule__set_rot_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x158/8])(m,p1,p2); }
void EffectModule__set_scale_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x160/8])(m,p1,p2); }
bool EffectModule__is_exist_effect_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); return reinterpret_cast<bool(*)(void*,u64)>(VTABLE(m)[0x188/8])(m,p1); }
void EffectModule__set_visible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x190/8])(m,p1,p2); }
void EffectModule__set_visible_kind_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x198/8])(m,p1,p2); }
void EffectModule__set_whole_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x1a8/8])(m,p1); }
bool EffectModule__is_whole_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VTABLE(m)[0x1b0/8])(m); }
void EffectModule__set_whole_attr_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,bool,u64)>(VTABLE(m)[0x1b8/8])(m,p1,p2); }
void EffectModule__reset_screen_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x1f8/8])(m,p1); }
void EffectModule__req_common_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x228/8])(m,p1); }
void EffectModule__remove_common_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x238/8])(m,p1); }
void EffectModule__reset_common_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x240/8])(m); }
bool EffectModule__is_exist_common_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); return reinterpret_cast<bool(*)(void*,u64)>(VTABLE(m)[0x250/8])(m,p1); }
void EffectModule__req_screen_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VTABLE(m)[0x260/8])(m,p1,p2,p3,p4); }
void EffectModule__req_screen_system_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0x270/8])(m,p1,p2,p3); }
void EffectModule__remove_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x280/8])(m,p1,p2); }
void EffectModule__set_sync_visibility_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x288/8])(m,p1); }
bool EffectModule__is_sync_visibility_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VTABLE(m)[0x290/8])(m); }
void EffectModule__set_sync_scale_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x298/8])(m,p1); }
bool EffectModule__is_sync_scale_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VTABLE(m)[0x2a0/8])(m); }
void EffectModule__set_rgb_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x2f8/8])(m,p1); }
void EffectModule__set_rgb_partial_last_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x300/8])(m); }
void EffectModule__set_alpha_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x308/8])(m,p1); }
void EffectModule__set_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x310/8])(m,p1); }
void EffectModule__set_billboard_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x328/8])(m,p1,p2); }
void EffectModule__set_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x330/8])(m,p1); }
void EffectModule__set_rate_last_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x338/8])(m); }
void EffectModule__set_scale_last_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x340/8])(m,p1); }
void EffectModule__set_alpha_last_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x348/8])(m); }
void EffectModule__set_disable_system_slow_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x350/8])(m,p1); }
void EffectModule__set_slow_rate_mul_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x378/8])(m); }
void EffectModule__set_slow_rate_no_stop_mul_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x380/8])(m); }
void EffectModule__set_add_vel_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x388/8])(m,p1,p2); }
void EffectModule__set_material_anim_last_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x390/8])(m,p1); }
void EffectModule__set_disable_render_offset_last_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x398/8])(m); }
void EffectModule__kill_status_effect_impl(BattleObjectModuleAccessor* a) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x3f8/8])(m); }
void* EffectModule__unsync_vis_whole_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64)>(VTABLE(m)[0x400/8])(m,p1); }
void EffectModule__sync_visibility_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x408/8])(m,p1); }
void EffectModule__set_offset_to_next_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x418/8])(m,p1); }
void* EffectModule__make_offset_hash_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VTABLE(m)[0x420/8])(m,p1,p2); }
void* EffectModule__preset_lifetime_rate_partial_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*)>(VTABLE(m)[0x428/8])(m); }
void* EffectModule__preset_curtail_emitter_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*)>(VTABLE(m)[0x430/8])(m); }
void EffectModule__preset_limit_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=EFFECT_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x438/8])(m,p1); }
void EffectModule__set_custom_uv_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VTABLE(m)[0x448/8])(m,p1,p2,p3); }
void EffectModule__remove_post_effect_line_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x450/8])(m,p1,p2); }
void* EffectModule__request_post_effect_line_circle_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VTABLE(m)[0x460/8])(m,p1,p2,p3); }
void EffectModule__set_post_effect_line_circle_target_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x468/8])(m,p1,p2); }
void* EffectModule__request_post_effect_line_parallel_2d_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); return reinterpret_cast<void*(*)(void*,u64,bool)>(VTABLE(m)[0x470/8])(m,p1,p2); }
void EffectModule__req_2d_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p6) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x140)); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,u32,u32,u32)>(VTABLE(m)[0x68/8])(m,p1,p2,p3,p4,static_cast<u32>(-1),1u,0u); }
} // namespace app::lua_bind
