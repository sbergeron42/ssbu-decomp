#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions — batch d5-043
// Pool-d worker: misc small functions (nop, ai, FighterUtil, FighterSpecializer)

// ---- No-op stubs ----

// 0x71000047a0
void FUN_71000047a0(void) { return; }

// 0x7100031870
void FUN_7100031870(void) { return; }

// 0x7100033910
void FUN_7100033910(void) { return; }

// 0x71000374c0
void FUN_71000374c0(void) { return; }

// 0x7100038150
void FUN_7100038150(void) { return; }

// 0x7100039a60
void FUN_7100039a60(void) { return; }

// 0x710003a610
void FUN_710003a610(void) { return; }

// 0x71002b4760
void FUN_71002b4760(void) { return; }

// ---- Simple field access / utility ----

// 0x7100006530
bool FUN_7100006530(s64 param_1) {
    return *(s64*)(param_1 + 0x868) != 2;
}

// 0x7100031170
void FUN_7100031170(u8 *param_1) {
    *param_1 = 1;
    *(u32*)(param_1 + 4) = 0xffffffff;
    *(u16*)(param_1 + 2) = *(u16*)(param_1 + 2) & 0xfffe;
}

// 0x7100031240
void FUN_7100031240(u32 *param_1) {
    *param_1 = 0x7000000;
    *(u8*)(param_1 + 1) = 0;
}

// 0x71000312a0
void FUN_71000312a0(u8 *param_1) {
    *(u32*)(param_1 + 4) = 0;
    *(u64*)(param_1 + 8) = 0;
    *param_1 = 0;
}

// 0x7100037440 — table lookup
u32 FUN_7100037440(u64 param_1) {
    extern u32 DAT_710446f530;
    return *(u32*)((u8*)&DAT_710446f530 + (u32)param_1 * 4);
}

// 0x7100037450 — table lookup
u32 FUN_7100037450(u64 param_1) {
    extern u32 DAT_710446f56c;
    return *(u32*)((u8*)&DAT_710446f56c + (u32)param_1 * 4);
}

// 0x7100038100 — indexed table load
u64 FUN_7100038100(s64 param_1, u32 param_2) {
    extern s64 DAT_7104470aa8 __attribute__((visibility("hidden")));
    return *(u64*)(param_1 + *(s64*)((u8*)&DAT_7104470aa8 + (u64)param_2 * 8));
}

// 0x7100039de0
void FUN_7100039de0(u8 *param_1, u64 param_2, u16 *param_3) {
    *(u32*)(param_1 + 4) = (u32)*param_3;
    *param_1 = 1;
}

// 0x7100039e10
s64 FUN_7100039e10(s64 param_1) {
    return (s64)(u64)*(u16*)(param_1 + 2) * 0x28 + -0x28;
}

// 0x71000408d0
u16 FUN_71000408d0(s64 param_1) {
    if (*(s64*)(param_1 + 0x10) != 0) {
        return *(u16*)(*(s64*)(param_1 + 0x10) + 10);
    }
    return 0;
}

// 0x71000408f0
s64 FUN_71000408f0(s64 param_1) {
    s64 node = *(s64*)(param_1 + 0x10);
    if (node != 0) {
        return node + (u64)*(u32*)(node + 0x10);
    }
    return 0;
}

// 0x7100040960
u16 FUN_7100040960(s64 param_1) {
    if (*(s64*)(param_1 + 0x18) != 0) {
        return *(u16*)(*(s64*)(param_1 + 0x18) + 0xc);
    }
    return 0;
}

// 0x7100040980
s64 FUN_7100040980(s64 param_1) {
    s64 node = *(s64*)(param_1 + 0x18);
    if (node != 0) {
        return node + (u64)*(u32*)(node + 8);
    }
    return 0;
}

// 0x71000441f0
void FUN_71000441f0(u32 *param_1) {
    *(u16*)(param_1 + 1) = 0;
    *param_1 = 0;
    *(u64*)(param_1 + 2) = 0;
    param_1[4] = 0;
}

// 0x7100044470
void FUN_7100044470(u16 *param_1) {
    *param_1 = 0;
    *(u64*)(param_1 + 4) = 0;
}

// 0x71000446c0
s64 FUN_71000446c0(s64 param_1, u32 param_2) {
    s64 base = *(s64*)(param_1 + 0x18);
    return base + (u64)*(u32*)(base + (u64)param_2 * 4 + 0xc);
}

// 0x7100044d40
void FUN_7100044d40(s64 param_1, u32 param_2) {
    if (*(s64*)(param_1 + 200) != 0) {
        *(u32*)(*(s64*)(param_1 + 200) + 0x30) = param_2;
    }
    if (*(s64*)(param_1 + 0xd0) != 0) {
        *(u32*)(*(s64*)(param_1 + 0xd0) + 0x30) = param_2;
    }
}

// 0x7100046e30
s64 FUN_7100046e30(s64 param_1, int param_2, int param_3, int param_4, int param_5) {
    return *(s64*)(param_1 + 0x260) +
           (s64)(param_2 * 0xc + param_3 * 4 + param_4 + param_5 * 2) * 8;
}

// 0x7100054150
s64 FUN_7100054150(s64 param_1, s64 param_2) {
    s64 base = *(s64*)(*(s64*)(param_2 + 200) + 0x38);
    if (base != 0) {
        return base + (u64)*(u32*)(param_1 + 0x30);
    }
    return 0;
}

// 0x7100079050
void FUN_7100079050(s64 param_1) {
    if (0 < *(int*)(param_1 + 0x98)) {
        *(u32*)(param_1 + 0x98) = 0;
    }
}

// 0x7100079070
s64 FUN_7100079070(s64 param_1) {
    return (s64)*(int*)(param_1 + 0x10) * 0x39;
}

// 0x71000a51a0
extern void FUN_71000a4f60(void);
void FUN_71000a51a0(void) {
    FUN_71000a4f60();
}

// 0x7100146c10 — vtable dispatch
void FUN_7100146c10(s64 param_1) {
    if (*(s64**)(param_1 + 8) != (s64*)0) {
        auto *m = *(s64**)(param_1 + 8);
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x58/8])(m);
    }
}

// 0x7100146e00 — vtable dispatch
void FUN_7100146e00(s64 param_1) {
    if (*(s64**)(param_1 + 8) != (s64*)0) {
        auto *m = *(s64**)(param_1 + 8);
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x50/8])(m);
    }
}

// 0x7100148d80 — vtable dispatch
void FUN_7100148d80(s64 param_1) {
    if (*(s64**)(param_1 + 8) != (s64*)0) {
        auto *m = *(s64**)(param_1 + 8);
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x88/8])(m);
    }
}

// 0x71001a1220
void FUN_71001a1220(s64 param_1) {
    *(u8*)(param_1 + 100) = 0;
}

// ---- app::ai namespace ----
// Tracking markers for named functions (not prefixed FUN_):
// FUN_7100361250 FUN_7100361260 FUN_71003612c0 FUN_71003612e0
// FUN_7100361450 FUN_7100361590 FUN_71003615d0 FUN_7100361880
// FUN_7100361b90 FUN_7100361ba0 FUN_7100361bb0 FUN_7100361bc0
// FUN_7100361bd0 FUN_7100361be0 FUN_7100361bf0 FUN_7100361c00
// FUN_7100361c10 FUN_7100361c30 FUN_7100361c50
// FUN_7100361d00 FUN_7100361d10 FUN_7100361d20 FUN_7100361d30
// FUN_710036a570 FUN_710036a590
// FUN_710036b020 FUN_710036b090 FUN_710036b0b0 FUN_710036b0d0
// FUN_710036b0f0 FUN_710036b110
// FUN_710036b490 FUN_710036b9d0 FUN_710036ba80 FUN_710036ba90
// FUN_7100376380 FUN_71003769e0

namespace app::ai {

// 0x7100361250 — fighter_kind
u32 fighter_kind(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x28);
}

// 0x7100361260 — copy_fighter_kind
u32 copy_fighter_kind(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 500);
}

// 0x71003612c0 — current_attack_cancel_frame
u32 current_attack_cancel_frame(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 300);
}

// 0x71003612e0 — attack_phase
u32 attack_phase(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x130);
}

// 0x7100361450 — check_stat_damage_elec
u8 check_stat_damage_elec(void *param_1) {
    return *(u8*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x56) >> 1 & 1;
}

// 0x7100361590 — check_stat_damage
bool check_stat_damage(void *param_1) {
    return *(int*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x74) == 5;
}

// 0x71003615d0 — check_stat_attack_hold
bool check_stat_attack_hold(void *param_1) {
    return (u32)(*(int*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x74) - 0x17) < 2;
}

// 0x7100361880 — check_stat_unable_attack
u8 check_stat_unable_attack(void *param_1) {
    return *(u8*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x59) >> 3 & 1;
}

// 0x7100361b90 — damage_reaction_mul
u32 damage_reaction_mul(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xfc);
}

// 0x7100361ba0 — stop_frame
u32 stop_frame(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x25c);
}

// 0x7100361bb0 — height
u32 height(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 200);
}

// 0x7100361bc0 — pos_x
u32 pos_x(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x80);
}

// 0x7100361bd0 — pos_y
u32 pos_y(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x84);
}

// 0x7100361be0 — speed_x
u32 speed_x(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xa0);
}

// 0x7100361bf0 — speed_y
u32 speed_y(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xa4);
}

// 0x7100361c00 — scale
u32 scale(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xc0);
}

// 0x7100361c10 — status_kind
u32 status_kind(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x2c);
}

// 0x7100361c30 — motion_kind
u64 motion_kind(void *param_1) {
    return *(u64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x38);
}

// 0x7100361c50 — motion_rate
u32 motion_rate(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x50);
}

// 0x7100361d00 — damage
u32 damage(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xe0);
}

// 0x7100361d10 — hp
u32 hp(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xe4);
}

// 0x7100361d20 — lr
u32 lr(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0xc4);
}

// 0x7100361d30 — customize_n
u32 customize_n(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x238);
}

} // namespace app::ai

// ---- app::ai_notify_event vtable dispatches ----

// 0x710036a570 — status_kind
void FUN_710036a570(void *param_1) {
    s64 p = *(s64*)((u8*)param_1 - 8);
    auto *m = *(s64**)(*(s64*)(*(s64*)(*(s64*)(p + 0x168) + 0x10) + 0x20) + 0x40);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x110/8])(m);
}

// 0x710036a590 — motion_kind
void FUN_710036a590(void *param_1) {
    s64 p = *(s64*)((u8*)param_1 - 8);
    auto *m = *(s64**)(*(s64*)(*(s64*)(*(s64*)(p + 0x168) + 0x10) + 0x20) + 0x88);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x138/8])(m);
}

// ---- app::ai_weapon namespace ----

namespace app::ai_weapon {

// 0x710036b020 — have_item_kind
u32 have_item_kind(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x168) + 0x108);
}

// 0x710036b090 — type
s64 type(void *param_1, void *param_2) {
    if (param_2 != (void*)0) {
        return (s64)(char)*((u8*)param_2 + 0xc);
    }
    return (s64)(u64)0xffffffff;
}

// 0x710036b0b0 — kind
u32 kind(void *param_1, void *param_2) {
    if (param_2 != (void*)0) {
        return *(u32*)((u8*)param_2 + 4);
    }
    return 0xffffffff;
}

// 0x710036b0d0 — flag
u16 flag(void *param_1, void *param_2) {
    if (param_2 != (void*)0) {
        return *(u16*)((u8*)param_2 + 8);
    }
    return 0;
}

// 0x710036b0f0 — pos_x
u32 pos_x(void *param_1, void *param_2) {
    if (param_2 != (void*)0) {
        return *(u32*)((u8*)param_2 + 0x40);
    }
    return 0;
}

// 0x710036b110 — speed_x
u32 speed_x(void *param_1, void *param_2) {
    if (param_2 != (void*)0) {
        return *(u32*)((u8*)param_2 + 0x50);
    }
    return 0;
}

} // namespace app::ai_weapon

// 0x710036b490 — ai_dangerzone::is_exist
extern s64 DAT_71052b5fd8 __attribute__((visibility("hidden")));
bool FUN_710036b490(void) {
    return **(int**)(*reinterpret_cast<s64*>(&DAT_71052b5fd8) + 0xc0) != 0;
}

// ---- app::ai_param namespace ----

namespace app::ai_param {

// 0x710036b9d0 — catch_attack_cancel_frame
u8 catch_attack_cancel_frame(void *param_1) {
    return *(u8*)(*(s64*)((u8*)param_1 - 8) + 0xbaa);
}

// 0x710036ba80 — num_of_attack_123
u32 num_of_attack_123(void *param_1) {
    return *(u32*)(*(s64*)((u8*)param_1 - 8) + 0xb14);
}

// 0x710036ba90 — has_attack_100
u8 has_attack_100(void *param_1) {
    return *(u8*)(*(s64*)((u8*)param_1 - 8) + 0xb18);
}

} // namespace app::ai_param

// 0x7100376380 — ai_system::mode
u32 FUN_7100376380(void *param_1) {
    return *(u32*)(*(s64*)((u8*)param_1 - 8) + 0xc64);
}

// 0x71003769e0 — analyst::status
u32 FUN_71003769e0(void *param_1) {
    return *(u32*)(**(s64**)(*(s64*)((u8*)param_1 - 8) + 0x170) + 0xc);
}

// ---- app::ai_debug stubs (all no-op) ----

// 0x7100376c00
void FUN_7100376c00(void *param_1, void *param_2) { return; }
// 0x7100376c10
void FUN_7100376c10(void *param_1, void *param_2, int param_3) { return; }
// 0x7100376c20
void FUN_7100376c20(void *param_1, void *param_2, int param_3) { return; }
// 0x7100376c30
void FUN_7100376c30(void *param_1, float param_2, int param_3) { return; }
// 0x7100376c40
void FUN_7100376c40(void *param_1, float param_2, int param_3) { return; }

// ---- app::FighterUtil ----

// 0x710068f790 — is_miienemy_fighter_kind
bool FUN_710068f790(int param_1) {
    return (u32)(param_1 - 0x4e) < 3;
}

// 0x7100694560 — exec_free_move (stub)
void FUN_7100694560(void *param_1) { return; }

// 0x7100694dc0 — renderer_get_color_rate
extern s64 DAT_7105336ce8 __attribute__((visibility("hidden")));
u32 FUN_7100694dc0(void) {
    s64 ptr = *(s64*)(&DAT_7105336ce8);
    return *(u32*)(*(s64*)(ptr + 8) + 0x10);
}

// 0x710069bf60 — set_pickelblock_mode_ignoreandattack (GroundModule +0x58)
void FUN_710069bf60(void *param_1) {
    auto *m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(param_1) + 0x58);
    reinterpret_cast<void(*)(void*, s64)>((*reinterpret_cast<void***>(m))[0x808/8])(m, 2);
}

// ---- FighterSpecializer final_module_hit_success — vtable[1] on global singleton ----

// 0x7100936fa0 — Demon
extern s64 DAT_71052bb550 __attribute__((visibility("hidden")));
void FUN_7100936fa0(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052bb550);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100974650 — Dolly
extern s64 DAT_71052bb578 __attribute__((visibility("hidden")));
void FUN_7100974650(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052bb578);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100a0d230 — EFlame
extern s64 DAT_71052bb630 __attribute__((visibility("hidden")));
void FUN_7100a0d230(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052bb630);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100a2a6d0 — ELight
extern s64 DAT_71052bb638 __attribute__((visibility("hidden")));
void FUN_7100a2a6d0(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052bb638);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100b35c20 — Jack
extern s64 DAT_71052bb6a8 __attribute__((visibility("hidden")));
void FUN_7100b35c20(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052bb6a8);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100cec9c0 — Master
extern s64 DAT_71052c0de0 __attribute__((visibility("hidden")));
void FUN_7100cec9c0(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052c0de0);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7100f0a970 — is_status_kind_attack (Pickel)
bool FUN_7100f0a970(int param_1) {
    return (u32)(param_1 - 0x1e1) < 10;
}

// 0x7100f11e50 — Pickel
extern s64 DAT_71052c0f48 __attribute__((visibility("hidden")));
void FUN_7100f11e50(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052c0f48);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7101197690 — Simon
extern s64 DAT_71052c19f8 __attribute__((visibility("hidden")));
void FUN_7101197690(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052c19f8);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7101227750 — is_status_kind_attack (Tantan)
bool FUN_7101227750(int param_1) {
    return (u32)(param_1 - 0x1e1) < 0x10;
}

// 0x71012281a0 — Tantan
extern s64 DAT_71052c1a48 __attribute__((visibility("hidden")));
void FUN_71012281a0(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052c1a48);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}

// 0x7101289c80 — Wario
extern s64 DAT_71052c1af8 __attribute__((visibility("hidden")));
void FUN_7101289c80(void) {
    s64 obj = *reinterpret_cast<s64*>(&DAT_71052c1af8);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(obj))[8/8])((void*)obj);
}
