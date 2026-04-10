#include "types.h"
#include "app/BossManager.h"

// MEDIUM-tier FUN_* functions — batch d5-047
// Pool-d worker: ai, item, target, random, math misc (0x71003611c0-0x71015cf5a0)
// Rewritten: pool-e — boma/module naming, Ghidra variable cleanup

// ---- app::ai ----

// 0x71003611c0 — target_id (48B)
extern s64 aiGetTargetById_7100314030(s64*, s64);
extern s64 DAT_71052b5fd8 __attribute__((visibility("hidden")));
u32 FUN_71003611c0(void *boma) {
    s64 target = aiGetTargetById_7100314030((s64*)&DAT_71052b5fd8, *(s64*)((u8*)boma - 8) + 0xc50);
    return *(u32*)(*(s64*)(target + 0x10) + 8);
}

// 0x7100368d30 — disable_command_attack_button_all (16B)
extern void FUN_71002f4830(s64);
void FUN_7100368d30(void *boma) {
    FUN_71002f4830(*(s64*)((u8*)boma - 8) + 0x180);
}

// 0x7100369720 — predict_target_hit_in_attack (16B)
extern void FUN_7100359180(u64, u32, s64);
void FUN_7100369720(void *boma, u32 attack_id, float p3, float p4, float p5, float p6) {
    FUN_7100359180(*(u64*)(*(s64*)((u8*)boma - 8) + 0x168), attack_id,
                   *(s64*)((u8*)boma - 8) + 0xc50);
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

// 0x7100376770 — ai_random::get_float (96B) — xorshift128 PRNG
extern s64 *DAT_71052c25b0;
extern float DAT_7104472710;
float FUN_7100376770(void) {
    s64 rng = *(s64*)*DAT_71052c25b0;
    u32 state3 = *(u32*)(rng + 0x5c);
    *(int*)(rng + 0x60) = *(int*)(rng + 0x60) + 1;  // increment counter
    u32 t = *(u32*)(rng + 0x50) ^ *(u32*)(rng + 0x50) << 0xb;
    t = t ^ t >> 8 ^ state3 ^ state3 >> 0x13;
    // Shift state: s0=s1, s1=s2, s2=s3, s3=t
    *(u32*)(rng + 0x50) = *(u32*)(rng + 0x54);
    *(u32*)(rng + 0x54) = *(u32*)(rng + 0x58);
    *(u32*)(rng + 0x58) = state3;
    *(u32*)(rng + 0x5c) = t;
    return (float)t * DAT_7104472710;
}

// 0x7100376960 — analyst::change_status (128B)
void FUN_7100376960(void *boma, u32 new_status) {
    u32 slot_idx = *(u32*)(*(s64*)((u8*)boma - 8) + 0x160);
    s64 table_base, slot_offset;
    table_base = *reinterpret_cast<s64*>(&DAT_71052b5fd8);
    slot_offset = 0x10;
    if ((int)slot_idx >= 0 && slot_idx < 0x10) {
        slot_offset = (s64)(int)slot_idx;
    }
    s64 *slot = (s64*)(*(s64*)(table_base + 0x98) + slot_offset * 8);
    if ((slot != (s64*)0) && (table_base = *slot, *(char*)(table_base + 8) == '\0')) {
        *(u32*)(table_base + 0x10) = *(u32*)(table_base + 0xc);
        *(u32*)(*slot + 0xc) = new_status;
        *(u32*)(*slot + 0x18) = *(u32*)(*slot + 0x14);
        *(u32*)(*slot + 0x14) = 0;
    }
}

// 0x7100f121d0 — FighterSpecializer_Pickel::generate_article (128B)
extern s64 *FUN_71009e22d0_vt[];
u64 FUN_7100f121d0(s64 *self, int article_id) {
    s64 *article_module = *(s64**)(*(s64*)((u8*)self + 0x20) + 0x98);
    s64 *article = (s64*)(*reinterpret_cast<void*(*)(s64*,int,int,int,u32)>((*reinterpret_cast<void***>(article_module))[0x70/8]))(article_module, article_id, 0, 0, 0xffffffff);
    if (article != (s64*)0) {
        (*reinterpret_cast<void(*)(s64*,s64*)>((*reinterpret_cast<void***>(article_module))[0x1a0/8]))(article_module, article);
        return reinterpret_cast<u64(*)(void*)>((*reinterpret_cast<void***>(article))[0x30/8])(article);
    }
    return 0x50000000;
}

// 0x71011b8760 — FighterSnakeFinalModule::start (112B)
extern u32 *DAT_71052c1a00;
void FUN_71011b8760(void *boma) {
    u32 *state = DAT_71052c1a00;
    if ((DAT_71052c1a00 != (u32*)0) && (DAT_71052c1a00[0x3e] == 0x50000000)) {
        u32 object_id = *(u32*)((u8*)boma + 8);
        state[8] = 0x50000000;
        *(u64*)(state + 6) = 0;
        *(u64*)(state + 4) = 0;
        *(u64*)(state + 0x12) = 0;
        *(u64*)(state + 0x10) = 0;
        state[0x14] = 0x50000000;
        state[0x20] = 0x50000000;
        state[0x2c] = 0x50000000;
        state[0x3e] = object_id;
        *state = 0xffffffff;
        state[0xc] = 0xffffffff;
        state[0x18] = 0xffffffff;
        state[0x24] = 0xffffffff;
        state[0x30] = 0xffffffff;
        state[0x38] = 0x50000000;
        *(u64*)(state + 0x3c) = 0;
        *(u64*)(state + 0x1e) = 0;
        *(u64*)(state + 0x1c) = 0;
        *(u64*)(state + 0x2a) = 0;
        *(u64*)(state + 0x28) = 0;
        *(u64*)(state + 0x36) = 0;
        *(u64*)(state + 0x34) = 0;
    }
}

// ---- app::item lua wrappers ----

// Helper: get item module from boma (accessor→battle_object→+400→+0x220)
#define ITEM_PTR(boma) (*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)(boma) - 8) + 0x1a0) + 400) + 0x220))

// 0x71015bfa90 — item::set_life (48B)
void FUN_71015bfa90(void *boma, int life) {
    s64 item = ITEM_PTR(boma);
    int clamped = 900;
    if (-1 < life) clamped = life;
    s64 *work = *(s64**)(item + 0xe8);
    int existing = (*reinterpret_cast<int(*)(s64*,s64)>((*reinterpret_cast<void***>(work))[0x98/8]))(work, 0x1000000c);
    if (existing < 0) {
        (*reinterpret_cast<void(*)(s64*,int,s64)>((*reinterpret_cast<void***>(work))[0xa0/8]))(work, clamped, 0x1000000c);
    }
    (*reinterpret_cast<void(*)(s64*,int,s64)>((*reinterpret_cast<void***>(work))[0xa0/8]))(work, clamped, 0x1000000b);
}

// 0x71015c0730 — item::action (128B)
void FUN_71015c0730(void *boma, int action_id, float param_3) {
    s64 *item = (s64*)ITEM_PTR(boma);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(item))[0x548/8]))(item, action_id);
}

// 0x71015c2140 — item::set_visibility_whole (48B)
void FUN_71015c2140(void *boma, bool visible) {
    s64 *item = (s64*)ITEM_PTR(boma);
    (*reinterpret_cast<void(*)(s64*,bool)>((*reinterpret_cast<void***>(item))[0x540/8]))(item, visible);
}

// 0x71015c2670 — item::have (48B)
void FUN_71015c2670(void *boma, u32 have_id, u64 param) {
    s64 *item = (s64*)ITEM_PTR(boma);
    (*reinterpret_cast<void(*)(s64*,u32,u64)>((*reinterpret_cast<void***>(item))[0x598/8]))(item, have_id, param);
}

// 0x71015c2770 — item::hop (48B)
extern void FUN_71015b0a00(u64, bool);
void FUN_71015c2770(void *boma, bool do_hop) {
    FUN_71015b0a00((u64)ITEM_PTR(boma), do_hop);
}

// ---- app::target ----

// Helper: get work module from boma (accessor→battle_object→+0x50)
#define WORK_MODULE(boma) (*(s64**)(*(s64*)(*(s64*)((u8*)(boma) - 8) + 0x1a0) + 0x50))

// 0x71015c5be0 — target::search (96B)
extern void FUN_71015b7ce0(u64, u32);
u32 FUN_71015c5be0(void *boma, u32 search_id, float param_3, float param_4) {
    FUN_71015b7ce0((u64)ITEM_PTR(boma), search_id);
    s64 *work = WORK_MODULE(boma);
    return (*reinterpret_cast<u32(*)(s64*,s64)>((*reinterpret_cast<void***>(work))[0x108/8]))(work, 0x2000000a) & 1;
}

// 0x71015c6940 — target::update (96B)
extern void FUN_71015b7ce0_4(u64, u32, u64, u32);
u32 FUN_71015c6940(void *boma) {
    s64 item = ITEM_PTR(boma);
    FUN_71015b7ce0_4(0, 0, (u64)item, 0x12);
    s64 *work = WORK_MODULE(boma);
    return (*reinterpret_cast<u32(*)(s64*,s64)>((*reinterpret_cast<void***>(work))[0x108/8]))(work, 0x2000000a) & 1;
}

// 0x71015c69a0 — target::id (48B)
void FUN_71015c69a0(void *boma) {
    s64 *work = WORK_MODULE(boma);
    (*reinterpret_cast<void(*)(s64*,s64)>((*reinterpret_cast<void***>(work))[0x98/8]))(work, 0x10000021);
}

// 0x71015c6b80 — target::pos (144B) — returns vec, complex; skip

// 0x71015c6c80 — target::pos_x (48B)
void FUN_71015c6c80(void *boma) {
    s64 *work = WORK_MODULE(boma);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(work))[0x58/8]))(work, 0xb);
}

// 0x71015c6cb0 — target::pos_y (48B)
void FUN_71015c6cb0(void *boma) {
    s64 *work = WORK_MODULE(boma);
    (*reinterpret_cast<void(*)(s64*,int)>((*reinterpret_cast<void***>(work))[0x58/8]))(work, 0xc);
}

// 0x71015c85e0 — boss_private::send_event_on_boss_keyoff_bgm (64B)
// [derived: Ghidra — checks singleton, calls FUN_71004e9e30(inner, battle_object_id)]
extern "C" app::BossManager* lib_Singleton_BossManager_instance_
    asm("_ZN3lib9SingletonIN3app11BossManagerEE9instance_E")
    __attribute__((visibility("hidden")));
extern void FUN_71004e9e30(void*, u32);
void FUN_71015c85e0(void *boma) {
    app::BossManager* bm = lib_Singleton_BossManager_instance_;
    if (bm != nullptr) {
        FUN_71004e9e30(bm->inner,
                       *(u32*)(ITEM_PTR(boma) + 0xc));
    }
}

// 0x71015cb2f0 — item_other::kind (64B)
u32 FUN_71015cb2f0(void *boma) {
    if (boma == (void*)0) return 10;
    if (*(u32*)((u8*)boma + 8) >> 0x1c == 4) {
        return *(u32*)(*(s64*)(*(s64*)((u8*)boma + 400) + 0x220) + 0xc);
    }
    return 10;
}

// 0x71015cf230 — random::get_float (96B) — xorshift128 PRNG (different state offset)
float FUN_71015cf230(void) {
    s64 rng = *(s64*)*DAT_71052c25b0;
    u32 state3 = *(u32*)(rng + 0x84);
    *(int*)(rng + 0x88) = *(int*)(rng + 0x88) + 1;  // increment counter
    u32 t = *(u32*)(rng + 0x78) ^ *(u32*)(rng + 0x78) << 0xb;
    t = t ^ t >> 8 ^ state3 ^ state3 >> 0x13;
    *(u32*)(rng + 0x78) = *(u32*)(rng + 0x7c);
    *(u32*)(rng + 0x7c) = *(u32*)(rng + 0x80);
    *(u32*)(rng + 0x80) = state3;
    *(u32*)(rng + 0x84) = t;
    return (float)t * DAT_7104472710;
}

// 0x71015cf5a0 — math2::rotate (160B) — NEON intrinsics; skip (too complex)

// 0x71015bf7c0 — item::set_area (144B) — complex struct arg; skip

// 0x71015cb600 — item_other::shoot (176B) — complex, skip
