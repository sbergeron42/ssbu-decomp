#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-047
// Pool-d worker: ai, item, target, random, math misc (0x71003611c0-0x71015cf5a0)
// Named function tracking markers:
// FUN_71003611c0 FUN_7100368d30 FUN_7100369720
// FUN_710036b130 FUN_710036b3a0 FUN_710036b4d0
// FUN_7100376150 FUN_7100376770 FUN_7100376960
// FUN_7100f121d0 FUN_71011b8760
// FUN_71015bf7c0 FUN_71015bfa90 FUN_71015c0730
// FUN_71015c2140 FUN_71015c2670 FUN_71015c2770
// FUN_71015c5be0 FUN_71015c6940 FUN_71015c69a0
// FUN_71015c6b80 FUN_71015c6c80 FUN_71015c6cb0
// FUN_71015c85e0 FUN_71015cb2f0 FUN_71015cb600
// FUN_71015cf230 FUN_71015cf5a0

// ---- app::ai ----

// 0x71003611c0 — target_id (48B)
extern s64 FUN_7100314030(s64*, s64);
extern s64 DAT_71052b5fd8 __attribute__((visibility("hidden")));
u32 FUN_71003611c0(void *param_1) {
    s64 lVar1 = FUN_7100314030((s64*)&DAT_71052b5fd8, *(s64*)((u8*)param_1 - 8) + 0xc50);
    return *(u32*)(*(s64*)(lVar1 + 0x10) + 8);
}

// 0x7100368d30 — disable_command_attack_button_all (16B)
extern void FUN_71002f4830(s64);
void FUN_7100368d30(void *param_1) {
    FUN_71002f4830(*(s64*)((u8*)param_1 - 8) + 0x180);
}

// 0x7100369720 — predict_target_hit_in_attack (16B)
extern void FUN_7100359180(u64, u32, s64);
void FUN_7100369720(void *param_1, u32 param_2, float p3, float p4, float p5, float p6) {
    FUN_7100359180(*(u64*)(*(s64*)((u8*)param_1 - 8) + 0x168), param_2,
                   *(s64*)((u8*)param_1 - 8) + 0xc50);
}

// 0x710036b130 — ai_weapon::speed_length (80B) — NEON path, skip to simple fallback
// Complex NEON intrinsics; skipped (too complex)

// 0x710036b3a0 — ai_stage::is_gravity (48B)
extern u8 lib_Singleton_BattleObjectWorld_instance_ __attribute__((visibility("hidden")));
bool FUN_710036b3a0(void) {
    if (*(char*)(&lib_Singleton_BattleObjectWorld_instance_ + 0x5c) != '\0') return false;
    return *(char*)(&lib_Singleton_BattleObjectWorld_instance_ + 0x59) == '\0';
}

// 0x710036b4d0 — ai_dangerzone::center_pos (112B) — returns vector, complex; skip

// 0x7100376150 — nfp::param_float (192B) — complex binary search; skip

// 0x7100376770 — ai_random::get_float (96B)
extern s64 *DAT_71052c25b0;
extern float DAT_7104472710;
float FUN_7100376770(void) {
    s64 lVar3 = *(s64*)*DAT_71052c25b0;
    u32 uVar2 = *(u32*)(lVar3 + 0x5c);
    *(int*)(lVar3 + 0x60) = *(int*)(lVar3 + 0x60) + 1;
    u32 uVar1 = *(u32*)(lVar3 + 0x50) ^ *(u32*)(lVar3 + 0x50) << 0xb;
    uVar1 = uVar1 ^ uVar1 >> 8 ^ uVar2 ^ uVar2 >> 0x13;
    *(u32*)(lVar3 + 0x50) = *(u32*)(lVar3 + 0x54);
    *(u32*)(lVar3 + 0x54) = *(u32*)(lVar3 + 0x58);
    *(u32*)(lVar3 + 0x58) = uVar2;
    *(u32*)(lVar3 + 0x5c) = uVar1;
    return (float)uVar1 * DAT_7104472710;
}

// 0x7100376960 — analyst::change_status (128B)
void FUN_7100376960(void *param_1, u32 param_2) {
    u32 uVar2 = *(u32*)(*(s64*)((u8*)param_1 - 8) + 0x160);
    s64 lVar3, lVar4;
    lVar4 = *reinterpret_cast<s64*>(&DAT_71052b5fd8);
    lVar3 = 0x10;
    if ((int)uVar2 >= 0 && uVar2 < 0x10) {
        lVar3 = (s64)(int)uVar2;
    }
    s64 *plVar1 = (s64*)(*(s64*)(lVar4 + 0x98) + lVar3 * 8);
    if ((plVar1 != (s64*)0) && (lVar4 = *plVar1, *(char*)(lVar4 + 8) == '\0')) {
        *(u32*)(lVar4 + 0x10) = *(u32*)(lVar4 + 0xc);
        *(u32*)(*plVar1 + 0xc) = param_2;
        *(u32*)(*plVar1 + 0x18) = *(u32*)(*plVar1 + 0x14);
        *(u32*)(*plVar1 + 0x14) = 0;
    }
}

// 0x7100f121d0 — FighterSpecializer_Pickel::generate_article (128B)
extern s64 *FUN_71009e22d0_vt[];
u64 FUN_7100f121d0(s64 *param_1, int param_2) {
    s64 *plVar3 = *(s64**)(*(s64*)((u8*)param_1 + 0x20) + 0x98);
    s64 *plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,int,int,int,u32)>((*reinterpret_cast<void***>(plVar3))[0x70/8]))(plVar3, param_2, 0, 0, 0xffffffff);
    if (plVar1 != (s64*)0) {
        (*reinterpret_cast<void(*)(s64*,s64*)>((*reinterpret_cast<void***>(plVar3))[0x1a0/8]))(plVar3, plVar1);
        return reinterpret_cast<u64(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x30/8])(plVar1);
    }
    return 0x50000000;
}

// 0x71011b8760 — FighterSnakeFinalModule::start (112B)
extern u32 *DAT_71052c1a00;
void FUN_71011b8760(void *param_1) {
    u32 *puVar2 = DAT_71052c1a00;
    if ((DAT_71052c1a00 != (u32*)0) && (DAT_71052c1a00[0x3e] == 0x50000000)) {
        u32 uVar1 = *(u32*)((u8*)param_1 + 8);
        puVar2[8] = 0x50000000;
        *(u64*)(puVar2 + 6) = 0;
        *(u64*)(puVar2 + 4) = 0;
        *(u64*)(puVar2 + 0x12) = 0;
        *(u64*)(puVar2 + 0x10) = 0;
        puVar2[0x14] = 0x50000000;
        puVar2[0x20] = 0x50000000;
        puVar2[0x2c] = 0x50000000;
        puVar2[0x3e] = uVar1;
        *puVar2 = 0xffffffff;
        puVar2[0xc] = 0xffffffff;
        puVar2[0x18] = 0xffffffff;
        puVar2[0x24] = 0xffffffff;
        puVar2[0x30] = 0xffffffff;
        puVar2[0x38] = 0x50000000;
        *(u64*)(puVar2 + 0x3c) = 0;
        *(u64*)(puVar2 + 0x1e) = 0;
        *(u64*)(puVar2 + 0x1c) = 0;
        *(u64*)(puVar2 + 0x2a) = 0;
        *(u64*)(puVar2 + 0x28) = 0;
        *(u64*)(puVar2 + 0x36) = 0;
        *(u64*)(puVar2 + 0x34) = 0;
    }
}

// ---- app::item lua wrappers ----

// 0x71015bfa90 — item::set_life (48B)
void FUN_71015bfa90(void *param_1, int param_2) {
    s64 lVar3 = *(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220);
    int iVar1 = 900;
    if (-1 < param_2) iVar1 = param_2;
    s64 *m = *(s64**)(lVar3 + 0xe8);
    int iVar2 = (*reinterpret_cast<int(*)(s64*,s64)>((*reinterpret_cast<void***>(m))[0x98/8]))(m, 0x1000000c);
    if (iVar2 < 0) {
        (*reinterpret_cast<void(*)(s64*,int,s64)>((*reinterpret_cast<void***>(m))[0xa0/8]))(m, iVar1, 0x1000000c);
    }
    (*reinterpret_cast<void(*)(s64*,int,s64)>((*reinterpret_cast<void***>(m))[0xa0/8]))(m, iVar1, 0x1000000b);
}

// 0x71015c0730 — item::action (128B)
void FUN_71015c0730(void *param_1, int param_2, float param_3) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(plVar1))[0x548/8]))(plVar1, param_2);
}

// 0x71015c2140 — item::set_visibility_whole (48B)
void FUN_71015c2140(void *param_1, bool param_2) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220);
    (*reinterpret_cast<void(*)(s64*,bool)>((*reinterpret_cast<void***>(plVar1))[0x540/8]))(plVar1, param_2);
}

// 0x71015c2670 — item::have (48B)
void FUN_71015c2670(void *param_1, u32 param_2, u64 param_3) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220);
    (*reinterpret_cast<void(*)(s64*,u32,u64)>((*reinterpret_cast<void***>(plVar1))[0x598/8]))(plVar1, param_2, param_3);
}

// 0x71015c2770 — item::hop (48B)
extern void FUN_71015b0a00(u64, bool);
void FUN_71015c2770(void *param_1, bool param_2) {
    FUN_71015b0a00(*(u64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220), param_2);
}

// ---- app::target ----

// 0x71015c5be0 — target::search (96B)
extern void FUN_71015b7ce0(u64, u32);
u32 FUN_71015c5be0(void *param_1, u32 param_2, float param_3, float param_4) {
    FUN_71015b7ce0(*(u64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220), param_2);
    s64 *plVar2 = *(s64**)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 0x50);
    return (*reinterpret_cast<u32(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar2))[0x108/8]))(plVar2, 0x2000000a) & 1;
}

// 0x71015c6940 — target::update (96B)
extern void FUN_71015b7ce0_4(u64, u32, u64, u32);
u32 FUN_71015c6940(void *param_1) {
    // calls FUN_71015b7ce0(0,0, item_ptr, 0x12)
    s64 item_ptr = *(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220);
    FUN_71015b7ce0_4(0, 0, (u64)item_ptr, 0x12);
    s64 *plVar2 = *(s64**)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 0x50);
    return (*reinterpret_cast<u32(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar2))[0x108/8]))(plVar2, 0x2000000a) & 1;
}

// 0x71015c69a0 — target::id (48B)
void FUN_71015c69a0(void *param_1) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 0x50);
    (*reinterpret_cast<void(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x98/8]))(plVar1, 0x10000021);
}

// 0x71015c6b80 — target::pos (144B) — returns vec, complex; skip

// 0x71015c6c80 — target::pos_x (48B)
void FUN_71015c6c80(void *param_1) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 0x50);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(plVar1))[0x58/8]))(plVar1, 0xb);
}

// 0x71015c6cb0 — target::pos_y (48B)
void FUN_71015c6cb0(void *param_1) {
    s64 *plVar1 = *(s64**)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 0x50);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(plVar1))[0x58/8]))(plVar1, 0xc);
}

// 0x71015c85e0 — boss_private::send_event_on_boss_keyoff_bgm (64B)
extern s64 lib_Singleton_BossManager_instance_;
extern void FUN_71004e9e30(u64, u32);
void FUN_71015c85e0(void *param_1) {
    if (lib_Singleton_BossManager_instance_ != 0) {
        FUN_71004e9e30(*(u64*)(lib_Singleton_BossManager_instance_ + 8),
                       *(u32*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 0xc));
    }
}

// 0x71015cb2f0 — item_other::kind (64B)
u32 FUN_71015cb2f0(void *param_1) {
    if (param_1 == (void*)0) return 10;
    if (*(u32*)((u8*)param_1 + 8) >> 0x1c == 4) {
        return *(u32*)(*(s64*)(*(s64*)((u8*)param_1 + 400) + 0x220) + 0xc);
    }
    return 10;
}

// 0x71015cf230 — random::get_float (96B)
float FUN_71015cf230(void) {
    s64 lVar3 = *(s64*)*DAT_71052c25b0;
    u32 uVar2 = *(u32*)(lVar3 + 0x84);
    *(int*)(lVar3 + 0x88) = *(int*)(lVar3 + 0x88) + 1;
    u32 uVar1 = *(u32*)(lVar3 + 0x78) ^ *(u32*)(lVar3 + 0x78) << 0xb;
    uVar1 = uVar1 ^ uVar1 >> 8 ^ uVar2 ^ uVar2 >> 0x13;
    *(u32*)(lVar3 + 0x78) = *(u32*)(lVar3 + 0x7c);
    *(u32*)(lVar3 + 0x7c) = *(u32*)(lVar3 + 0x80);
    *(u32*)(lVar3 + 0x80) = uVar2;
    *(u32*)(lVar3 + 0x84) = uVar1;
    return (float)uVar1 * DAT_7104472710;
}

// 0x71015cf5a0 — math2::rotate (160B) — NEON intrinsics; skip (too complex)

// 0x71015bf7c0 — item::set_area (144B) — complex struct arg; skip

// 0x71015cb600 — item_other::shoot (176B) — complex, skip
