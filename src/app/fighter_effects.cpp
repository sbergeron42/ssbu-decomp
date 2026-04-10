#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/WorkModule.h"
#include "app/modules/EffectModule.h"
#include "app/modules/SoundModule.h"
#include "app/modules/VisibilityModule.h"
#include "app/modules/ModelModule.h"

// Fighter effect/sound utility functions — pool-e
// Decompiled from Ghidra analysis of SSBU 13.0.4

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External declarations --------------------------------------------------

extern "C" void special_n_req_effect_dash_smoke(void*);
extern "C" void FUN_71015c1770(void*, u32, u64, u32, void*, u64, u32);
extern "C" void FUN_71015b08c0(u64);
extern "C" bool FUN_710068f7a0(void*);  // [inferred: checks damage module + dead effect eligibility, 1420 bytes]

// Global data pointers — HIDDEN avoids GOT indirection, matching original adrp+ldr
extern "C" void* DAT_71052b8450 HIDDEN;  // [inferred: Joker (Jack) specializer data ptr-to-ptr]
extern "C" void* DAT_71052b7710 HIDDEN;  // [inferred: Fox/Falco specializer data ptr]

// Lookup tables for audience sound labels — HIDDEN for adrp+add direct addressing
extern "C" u64 DAT_7104545590[] HIDDEN;  // [inferred: audience SE label table, type=0, 3 entries]
extern "C" u64 DAT_71045455b0[] HIDDEN;  // [inferred: audience SE label table, type=1, 3 entries]

using namespace app;

// ---- Functions --------------------------------------------------------------

// 0x7100ade7c0 (4 bytes) — FighterSpecializer_Gekkouga::set_effect_visible_group
// Stub/no-op virtual override: Greninja does not implement grouped effect visibility
extern "C" void set_effect_visible_group(bool) {}

// 0x7100ba33c0 (4 bytes) — FighterSpecializer_Kirby::purin_req_effect_dash_smoke
// Thunk: Kirby reuses Jigglypuff's copy-ability effect via special_n variant
// [derived: tail call target special_n_req_effect_dash_smoke at 0x7100fe07a0]
extern "C" void purin_req_effect_dash_smoke(void* acc) {
    special_n_req_effect_dash_smoke(acc);
}

// 0x71015c19f0 (20 bytes) — app::item::request_cut_in_from_param_with_effect_id
// Wrapper that inserts fixed param (0x50000000) and flag (true) before delegating
// [derived: target FUN_71015c1770 is the general cut-in request handler]
extern "C" void request_cut_in_from_param_with_effect_id(void* L, u32 kind, u64 hash, void* pos, u64 effect_id) {
    FUN_71015c1770(L, kind, hash, 0x50000000, pos, effect_id, 1);
}

// 0x71015c1f60 (36 bytes) — app::item::request_lost_effect_and_se
// Navigates pointer chain from lua_State to trigger lost item visual+audio
// Chain: *(L-8) → +0x1a0 → +0x190 → +0x220 [inferred: item battle object accessor chain]
extern "C" void request_lost_effect_and_se(u64 L) {
    FUN_71015b08c0(*(u64*)(*(u64*)(*(u64*)(*(u64*)(L - 8) + 0x1a0) + 0x190) + 0x220));
}

// 0x7100b34410 (64 bytes) — FighterSpecializer_Jack::set_cut_in_effect
// Reads work int 0x11000005 and stores in Joker specializer data at +0x4a8
// +0x50 [derived: WorkModule (.dynsym) at accessor+0x50]
// DAT_71052b8450 [inferred: Joker global data, ptr-to-ptr-to-struct]
extern "C" void set_cut_in_effect(BattleObjectModuleAccessor* acc) {
    void* saved = DAT_71052b8450;
    WorkModule* work = static_cast<WorkModule*>(acc->work_module);
    s32 val = work->get_int(0x11000005);
    // +0x4a8 [inferred: cut-in effect kind, s32]
    *(s32*)((u8*)*(void**)saved + 0x4a8) = val;
}

// 0x71016471b0 (68 bytes) — app::kozukatasight::start_sound_effector
// Calls SoundModule vtable[87] (0x2b8) then tail-calls vtable[85] (0x2a8)
// +0x148 [derived: SoundModule (.dynsym) at accessor+0x148]
// vtable[87] 0x2b8 [inferred: enable/set flag, called with 1]
// vtable[85] 0x2a8 [inferred: set parameter, called with (4, 0)]
extern "C" void start_sound_effector(void* acc, float) {
    void* sound = *(void**)((u8*)acc + 0x148);
    void** vt = *(void***)sound;
    reinterpret_cast<void(*)(void*, s32)>(vt[0x2b8 / 8])(sound, 1);
    vt = *(void***)sound;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x2a8 / 8])(sound, 4, 0);
}

// 0x7100a48030 (72 bytes) — FighterSpecializer_Falco::final_remove_screen_effect
// Clears screen effect state via vtable[62] (0x1f0) call + zeroing fields
// DAT_71052b7710 [inferred: Fox/Falco specializer singleton]
// *(DAT_71052b7710 + 8) [inferred: specializer instance data]
// +0x3a0 [inferred: screen effect module pointer]
// +0x438 [inferred: screen effect active flag, u8]
// +0x43c [inferred: screen effect handle/data, u64]
// +0x444 [inferred: screen effect extra param, u32]
extern "C" void final_remove_screen_effect() {
    u8* data = *(u8**)((u8*)DAT_71052b7710 + 8);
    void* mod = *(void**)(data + 0x3a0);
    void** vt = *(void***)mod;
    reinterpret_cast<void(*)(void*, s32)>(vt[0x1f0 / 8])(mod, 0);
    *(u8*)(data + 0x438) = 0;
    *(u64*)(data + 0x43c) = 0;
    *(u32*)(data + 0x444) = 0;
}

// 0x7100a65150 (72 bytes) — FighterSpecializer_Fox::final_remove_screen_effect
// Identical to Falco version — both share same specializer global and layout
extern "C" void final_remove_screen_effect_7100a65150() {
    u8* data = *(u8**)((u8*)DAT_71052b7710 + 8);
    void* mod = *(void**)(data + 0x3a0);
    void** vt = *(void***)mod;
    reinterpret_cast<void(*)(void*, s32)>(vt[0x1f0 / 8])(mod, 0);
    *(u8*)(data + 0x438) = 0;
    *(u64*)(data + 0x43c) = 0;
    *(u32*)(data + 0x444) = 0;
}

// 0x7101670030 (72 bytes) — app::sandbag::get_audience_sound_label
// Returns hash label for audience SE based on type (0=hit, 1=??) and level (0-2)
// Default return 0x7fb997a80 [inferred: hash for "no sound" / invalid label]
// DAT_7104545590 [inferred: audience SE table type 0, 3 entries]
// DAT_71045455b0 [inferred: audience SE table type 1, 3 entries]
extern "C" u64 get_audience_sound_label(s32 type, s32 level) {
    const u64* table;
    if (type != 1) {
        if (type != 0) return 0x7fb997a80ULL;
        if ((u32)level > 2) return 0x7fb997a80ULL;
        table = DAT_7104545590;
    } else {
        if ((u32)level > 2) return 0x7fb997a80ULL;
        table = DAT_71045455b0;
    }
    return table[level];
}

// ---- Batch 2: small effect/sound functions (88-196 bytes) -------------------

// lib::Singleton<lib::EffectManager>::instance_
extern "C" void* DAT_7105333920 HIDDEN;

// 0x710167d0f0 (88 bytes) — app::solgaleo::set_effect_pause
// Leaf function: validates effect handle, sets pause flag at +0x2d2 in effect entry
// Effect entries are 0x300 bytes each, indexed by handle >> 24
// +0x4 [inferred: handle validation field, u32]
// +0x2d2 [inferred: pause flag, u8]
// +0x2d7 [inferred: disabled/invalid flag, u8 — if set, skip]
extern "C" void set_effect_pause(s32 handle, bool pause) {
    if (handle <= 0) return;
    u8* base = *(u8**)DAT_7105333920;
    u32 index = (u32)handle >> 24;
    u8* entry = base + (u64)index * 0x300;
    if (entry == nullptr) return;
    if (*(u32*)(entry + 4) != (u32)handle) return;
    if (*(u8*)(base + (u64)index * 0x300 + 0x2d7) != 0) return;
    *(u8*)(base + (u64)index * 0x300 + 0x2d2) = (u8)(pause & 1);
}

// 0x710228fa50 (108 bytes) — app::sv_animcmd::EFFECT_STENCIL_ON
// ACMD function: enables stencil on EffectModule, then consumes remaining lua args
// *(L-8) → +0x1a0 [derived: BattleObjectModuleAccessor from lua_State extra]
// +0x140 [derived: EffectModule at accessor+0x140]
// vtable[0x488/8=145] [derived: enable_stencil from EffectModule.h]
extern "C" void EFFECT_STENCIL_ON(u64 L) {
    u64 wrapper = *(u64*)(L - 8);
    app::BattleObjectModuleAccessor* boma = *(app::BattleObjectModuleAccessor**)(wrapper + 0x1a0);
    boma->effect_module->enable_stencil(true);
    u64 end = **(u64**)(L + 0x20) + 0x10;
    u64 cur = *(u64*)(L + 0x10);
    if (cur < end) {
        do {
            *(u64*)(L + 0x10) = cur + 0x10;
            *(u32*)(cur + 8) = 0;
            cur = *(u64*)(L + 0x10);
        } while (cur < end);
    }
    *(u64*)(L + 0x10) = end;
}

// 0x710228fac0 (108 bytes) — app::sv_animcmd::EFFECT_STENCIL_OFF
// ACMD function: disables stencil on EffectModule, then consumes remaining lua args
extern "C" void EFFECT_STENCIL_OFF(u64 L) {
    u64 wrapper = *(u64*)(L - 8);
    app::BattleObjectModuleAccessor* boma = *(app::BattleObjectModuleAccessor**)(wrapper + 0x1a0);
    boma->effect_module->enable_stencil(false);
    u64 end = **(u64**)(L + 0x20) + 0x10;
    u64 cur = *(u64*)(L + 0x10);
    if (cur < end) {
        do {
            *(u64*)(L + 0x10) = cur + 0x10;
            *(u32*)(cur + 8) = 0;
            cur = *(u64*)(L + 0x10);
        } while (cur < end);
    }
    *(u64*)(L + 0x10) = end;
}

// ---- pickelobject hash functions (Steve/Minecraft item variant hashes) -------

extern "C" s32 FUN_71025f4560();

// Hash lookup tables for pickelobject effect/sound variants
extern "C" u64 DAT_7104542020[] HIDDEN;  // [inferred: born effect hashes by material, 3 entries]
extern "C" u64 DAT_7104542040[] HIDDEN;  // [inferred: damage sound hashes by material, 3 entries]
extern "C" u64 DAT_7104542060[] HIDDEN;  // [inferred: break sound hashes by material, 3 entries]

// 0x710166d760 (172 bytes) — app::pickelobject::get_born_effect_hash
// Returns hash for spawn visual effect based on pickel material type
// +0x50 [derived: WorkModule at accessor+0x50]
// WorkModule::get_int(0x10000001) [inferred: material variant index]
// FUN_71025f4560 [inferred: pickel tool variation getter]
extern "C" u64 get_born_effect_hash(void* acc) {
    void* work = *(void**)((u8*)acc + 0x50);
    void** wvt = *(void***)work;
    u64 result = 0x101896ee68ULL;
    u8 mat = reinterpret_cast<u8(*)(void*, s32)>(wvt[0x98 / 8])(work, 0x10000001);
    switch (mat) {
    case 0: {
        s32 var = FUN_71025f4560();
        if ((u32)(var - 1) < 3) {
            result = DAT_7104542020[var - 1];
        }
        break;
    }
    case 1:
        result = 0xf5f661936ULL;
        break;
    case 2:
        result = 0x11304120ceULL;
        break;
    case 3:
        result = 0x10c09c9ce5ULL;
        break;
    }
    return result;
}

// 0x710166d810 (168 bytes) — app::pickelobject::get_damage_sound_hash
// Returns hash for damage sound effect based on pickel material type
extern "C" u64 get_damage_sound_hash(void* acc) {
    void* work = *(void**)((u8*)acc + 0x50);
    void** wvt = *(void***)work;
    u64 result = 0x10664ef697ULL;
    u8 mat = reinterpret_cast<u8(*)(void*, s32)>(wvt[0x98 / 8])(work, 0x10000001);
    switch (mat) {
    case 0: {
        s32 var = FUN_71025f4560();
        if ((u32)(var - 1) < 3) {
            result = DAT_7104542040[var - 1];
        }
        break;
    }
    case 1:
        result = 0x1000000000ULL | 0xfaa97d8bULL;
        break;
    case 2:
        result = 0x111d3d175bULL;
        break;
    case 3:
        result = 0x1000000000ULL | 0xbe44841aULL;
        break;
    }
    return result;
}

// 0x710166d8c0 (168 bytes) — app::pickelobject::get_break_sound_hash
// Returns hash for break sound effect based on pickel material type
extern "C" u64 get_break_sound_hash(void* acc) {
    void* work = *(void**)((u8*)acc + 0x50);
    void** wvt = *(void***)work;
    u64 result = 0xf3d0b4b30ULL;
    u8 mat = reinterpret_cast<u8(*)(void*, s32)>(wvt[0x98 / 8])(work, 0x10000001);
    switch (mat) {
    case 0: {
        s32 var = FUN_71025f4560();
        if ((u32)(var - 1) < 3) {
            result = DAT_7104542060[var - 1];
        }
        break;
    }
    case 1:
        result = 0xf00000000ULL | 0xa1ecc02cULL;
        break;
    case 2:
        result = 0x1055d464adULL;
        break;
    case 3:
        result = 0xf00000000ULL | 0xe50139bdULL;
        break;
    }
    return result;
}

// ---- WeaponSpecializer_DemonBlaster effect management -----------------------
// Kazuya's blaster weapon: beam, shot, and head effects tracked via work ints.
// All three functions share the same pattern:
// 1. Get WorkModule (+0x50) and EffectModule (+0x140) via Weapon accessor (+0x20)
// 2. Read effect handle from work int
// 3. If handle != 0: detach or kill based on bool param
// 4. Clear the work int via set_int(0, work_var)

// 0x71033dbb00 (172 bytes) — WeaponSpecializer_DemonBlaster::remove_beam_effect
// work var: 0x1000000b [inferred: beam effect handle]
extern "C" void remove_beam_effect(void* weapon, bool detach_flag) {
    app::BattleObjectModuleAccessor* acc = *(app::BattleObjectModuleAccessor**)((u8*)weapon + 0x20);
    app::WorkModule* work = acc->work_module;
    app::EffectModule* effect = acc->effect_module;
    s32 handle = work->get_int(0x1000000b);
    if (handle != 0) {
        if (detach_flag) {
            effect->detach(handle, 5);
        } else {
            effect->kill(handle, true, true);
        }
        work->set_int(0, 0x1000000b);
    }
}

// 0x71033dbbb0 (172 bytes) — WeaponSpecializer_DemonBlaster::remove_shot_effect
// work var: 0x1000000c [inferred: shot effect handle]
extern "C" void remove_shot_effect(void* weapon, bool detach_flag) {
    app::BattleObjectModuleAccessor* acc = *(app::BattleObjectModuleAccessor**)((u8*)weapon + 0x20);
    app::WorkModule* work = acc->work_module;
    app::EffectModule* effect = acc->effect_module;
    s32 handle = work->get_int(0x1000000c);
    if (handle != 0) {
        if (detach_flag) {
            effect->detach(handle, 5);
        } else {
            effect->kill(handle, false, true);
        }
        work->set_int(0, 0x1000000c);
    }
}

// 0x71033dbc60 (172 bytes) — WeaponSpecializer_DemonBlaster::remove_head_effect
// work var: 0x1000000d [inferred: head effect handle]
extern "C" void remove_head_effect(void* weapon, bool detach_flag) {
    app::BattleObjectModuleAccessor* acc = *(app::BattleObjectModuleAccessor**)((u8*)weapon + 0x20);
    app::WorkModule* work = acc->work_module;
    app::EffectModule* effect = acc->effect_module;
    s32 handle = work->get_int(0x1000000d);
    if (handle != 0) {
        if (detach_flag) {
            effect->detach(handle, 5);
        } else {
            effect->kill(handle, true, true);
        }
        work->set_int(0, 0x1000000d);
    }
}

// ---- Remove effect flushing (Kirby copy / Jigglypuff specializers) ----------

// 0x7100ba32e0 (132 bytes) — FighterSpecializer_Kirby::purin_remove_effect_flushing
// Checks work flag 0x21000011, if set removes common effect and clears flag
// +0x50 [derived: WorkModule at accessor+0x50]
// +0x140 [derived: EffectModule at accessor+0x140]
// WorkModule::is_flag(0x21000011) [derived: vtable offset 0x108]
// EffectModule::remove_common(0x75da53379) [derived: vtable offset 0x238, slot 71]
// WorkModule::off_flag(0x21000011) [derived: vtable offset 0x120]
extern "C" void purin_remove_effect_flushing(BattleObjectModuleAccessor* acc) {
    WorkModule* work = static_cast<WorkModule*>(acc->work_module);
    EffectModule* effect = static_cast<EffectModule*>(acc->effect_module);
    if (work->is_flag(0x21000011)) {
        effect->remove_common(0x75da53379ULL);
        work->off_flag(0x21000011);
    }
}

// 0x7100fe0290 (132 bytes) — FighterSpecializer_Purin::special_n_remove_effect_flushing
// Identical logic to purin_remove_effect_flushing — Jigglypuff's own implementation
extern "C" void special_n_remove_effect_flushing(BattleObjectModuleAccessor* acc) {
    WorkModule* work = static_cast<WorkModule*>(acc->work_module);
    EffectModule* effect = static_cast<EffectModule*>(acc->effect_module);
    if (work->is_flag(0x21000011)) {
        effect->remove_common(0x75da53379ULL);
        work->off_flag(0x21000011);
    }
}

// ---- Item attack data functions (kiilalaser, kiilatorrent, marx) -----------
// All three follow an identical pattern via the item's AttackModule (+0xA0):
// 1. Read attack data from slot 0 via attack_data(0, false) [vtable slot 61, 0x1e8]
// 2. Set attack on target slot via set_attack(id, 0, data) [vtable slot 13, 0x68]

// 0x7101653be0 (80 bytes) — app::kiilalaser::copy_attack_data
// +0xA0 [derived: AttackModule at ItemModuleAccessor+0xA0, same offset as BattleObjectModuleAccessor]
// vtable[61] 0x1e8 [derived: attack_data from AttackModule.h]
// vtable[13] 0x68 [derived: set_attack from AttackModule.h]
extern "C" void copy_attack_data(u64 acc, s32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mod = *(void**)(acc + 0xA0);
    void** vt = *(void***)mod;
    u64 data = reinterpret_cast<u64(*)(void*, s32, s32)>(vt[0x1e8 / 8])(mod, 0, 0);
    mod = *(void**)(acc + 0xA0);
    vt = *(void***)mod;
    reinterpret_cast<void(*)(void*, s32, s32, u64)>(vt[0x68 / 8])(mod, id, 0, data);
}

// 0x7101653cf0 (80 bytes) — app::kiilatorrent::set_attack_data
extern "C" void set_attack_data(u64 acc, s32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mod = *(void**)(acc + 0xA0);
    void** vt = *(void***)mod;
    u64 data = reinterpret_cast<u64(*)(void*, s32, s32)>(vt[0x1e8 / 8])(mod, 0, 0);
    mod = *(void**)(acc + 0xA0);
    vt = *(void***)mod;
    reinterpret_cast<void(*)(void*, s32, s32, u64)>(vt[0x68 / 8])(mod, id, 0, data);
}

// 0x71016545a0 (80 bytes) — app::marx::set_capillary_attack_data
extern "C" void set_capillary_attack_data(u64 acc, s32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mod = *(void**)(acc + 0xA0);
    void** vt = *(void***)mod;
    u64 data = reinterpret_cast<u64(*)(void*, s32, s32)>(vt[0x1e8 / 8])(mod, 0, 0);
    mod = *(void**)(acc + 0xA0);
    vt = *(void***)mod;
    reinterpret_cast<void(*)(void*, s32, s32, u64)>(vt[0x68 / 8])(mod, id, 0, data);
}

// ---- Item WorkModule init functions ----------------------------------------

// 0x710165bd30 (80 bytes) — app::curryshot::init_log_attack_info
// Initializes attack log work ints for curryshot item
// +0x50 [derived: WorkModule at ItemModuleAccessor+0x50]
// WorkModule::set_int [derived: vtable offset 0xa0]
// 0x1000002c [inferred: attack log frame counter work var]
// 0x1000002b [inferred: attack log max frame work var]
extern "C" void init_log_attack_info(u64 acc) {
    void* work = *(void**)(acc + 0x50);
    void** vt = *(void***)work;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0xa0 / 8])(work, 0x65, 0x1000002c);
    vt = *(void***)work;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0xa0 / 8])(work, 0x7fffffff, 0x1000002b);
}

// homerun_contest_effect_no_pause @ 0x71016708e0: SKIPPED — EffectManager singleton
// access pattern and control flow don't match (12%), needs more analysis
// set_head_effect @ 0x71033dc010: SKIPPED — req_follow parameter passing and vector
// constant loading don't match (7%), needs req_follow signature investigation

// ---- Camera revert thunks (4 bytes each — single tail branch) -------------

extern "C" void FUN_710160dea0();

// 0x71016459c0 (4 bytes) — app::flyandhand::revert_camera
// Thunk: tail-branches to shared camera revert implementation
// [derived: target 0x710160dea0 is the actual revert_camera logic]
extern "C" void revert_camera() { FUN_710160dea0(); }

// 0x7101651d80 (4 bytes) — app::crazyhand::revert_camera
// Thunk: identical to flyandhand version
extern "C" void revert_camera_7101651d80() { FUN_710160dea0(); }

// ---- Dead effect check ----------------------------------------------------

// ---- Inkling fighter param singleton getters --------------------------------
// All three getters read from the Inkling-specific sub-struct at
// lib::Singleton<app::FighterParamAccessor2>::instance_ + 0xea8.
// These are trivial leaf functions and use raw offset access per CLAUDE.md
// exception for singleton getters.

// Reuse the FPA2 singleton symbol already referenced in fighter_core.cpp
namespace lib {
extern "C" void* Singleton_app_FighterParamAccessor2_instance_fe
    asm("_ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E") HIDDEN;
}
#define INKLING_PARAMS (*reinterpret_cast<u8**>(reinterpret_cast<u8*>(lib::Singleton_app_FighterParamAccessor2_instance_fe) + 0xea8))

// 0x7100b0cb10 (20 bytes) — FighterSpecializer_Inkling::get_ink_work_id
// Returns work variable id used to store ink amount for a given special kind.
// Special kind 6 (side/hi?) uses var 0x6b; everything else uses var 0x52.
// [inferred: constants 0x6b and 0x52 identified from csel pattern, branch on w0==6]
extern "C" s32 get_ink_work_id(u32 special_kind) {
    return special_kind == 6 ? 0x6b : 0x52;
}

// 0x7100b0cc40 (20 bytes) — FighterSpecializer_Inkling::get_ink_max
// Returns max ink capacity (f32) from Inkling-specific fighter param sub-struct.
// +0xc8 [inferred: ink_max offset into Inkling params, reads as f32 via ldr s0]
extern "C" f32 get_ink_max() {
    return *reinterpret_cast<f32*>(INKLING_PARAMS + 0xc8);
}

// 0x7100b0cc60 (20 bytes) — FighterSpecializer_Inkling::get_sub_ink_special_lw
// Ink cost for special_lw (down-special: sub weapon toss).
// +0xf0 [inferred: sub_ink_special_lw offset, reads as f32 via ldr s0]
extern "C" f32 get_sub_ink_special_lw() {
    return *reinterpret_cast<f32*>(INKLING_PARAMS + 0xf0);
}

// 0x7100b0ddb0 (20 bytes) — FighterSpecializer_Inkling::get_sub_ink_special_n
// Ink cost for special_n (neutral-special: splattershot).
// +0xec [inferred: sub_ink_special_n offset, reads as f32 via ldr s0]
extern "C" f32 get_sub_ink_special_n() {
    return *reinterpret_cast<f32*>(INKLING_PARAMS + 0xec);
}

// 0x7100b0cf70 (156 bytes) — FighterSpecializer_Inkling::is_body_visible
// Returns true if Inkling body should render this frame.
// Logic: body is hidden when painted flag is set and visible-override is clear,
// OR when whole-object visibility is off, OR when ModelModule says hidden.
// Fighter +0x20 [derived: standard Fighter layout — module accessor ptr]
// WorkModule flags:
//   0x20000023 [inferred: FIGHTER_INKLING_STATUS_WORK_IS_PAINTED]
//   0x20000024 [inferred: FIGHTER_INKLING_STATUS_WORK_FORCE_VISIBLE (= painted+1)]
extern "C" u32 is_body_visible(void* fighter) {
    BattleObjectModuleAccessor* acc = *reinterpret_cast<BattleObjectModuleAccessor**>(
        reinterpret_cast<u8*>(fighter) + 0x20);
    WorkModule* work = acc->work_module;
    u32 flag_result;
    if (work->is_flag(0x20000023)) {
        flag_result = work->is_flag(0x20000024);
    } else {
        flag_result = 1;
    }
    if (!(acc->visibility_module->get_whole() & 1)) return 0;
    return (flag_result & acc->model_module->is_visible()) & 1;
}

// 0x7100d295b0 (84 bytes) — FighterSpecializer_Mewtwo::save_shadowball_status
// Saves charging state (flag) and frame count (int) for Mewtwo's Shadow Ball.
// WorkModule +0x50 [derived: standard accessor layout]
// 0x200000e0 [inferred: shadow ball charged flag — Mewtwo extra flag range]
// 0x100000bd [inferred: shadow ball charge frame var — Mewtwo extra int range]
extern "C" void save_shadowball_status(BattleObjectModuleAccessor* acc, bool charged, s32 charge_frame) {
    WorkModule* work = acc->work_module;
    work->set_flag(charged, 0x200000e0);
    work->set_int(charge_frame, 0x100000bd);
}

// 0x71016708e0 (108 bytes) — app::sandbag::homerun_contest_effect_no_pause
// Flags the last-requested effect as not affected by global pause (home-run contest
// has a frozen-timer UI but still renders the sandbag hit sparkle).
// +0x140 [derived: EffectModule at accessor+0x140]
// EffectModule::get_last_handle() [derived: slot 116, vtable offset 0x3a0]
// Effect entry +0x26c [inferred: render flag bitmask; 0x800000 = ignore global pause]
// Reuses DAT_7105333920 (lib::Singleton<lib::EffectManager>::instance_) already
// declared above for set_effect_pause.
extern "C" void homerun_contest_effect_no_pause(BattleObjectModuleAccessor* acc) {
    EffectModule* effect = acc->effect_module;
    u8* base = *reinterpret_cast<u8**>(&DAT_7105333920);
    s32 handle = static_cast<s32>(effect->get_last_handle());
    if (handle > 0) {
        u8* entry = base + static_cast<u64>(static_cast<u32>(handle) >> 24) * 0x300;
        if (entry != nullptr && *reinterpret_cast<u32*>(entry + 4) == static_cast<u32>(handle)) {
            u32* flags = reinterpret_cast<u32*>(base + static_cast<u64>(static_cast<u32>(handle) >> 24) * 0x300 + 0x26c);
            *flags |= 0x800000u;
        }
    }
}

// 0x71006988b0 (128 bytes) — app::FighterUtil::check_hit_dead_effect
// Checks if a fighter should display a hit-dead visual effect.
// Calls FUN_710068f7a0 (damage module eligibility check), then tests 3 work flags.
// Returns true only if the eligibility check passes AND none of the 3 flags are set.
// +0x50 [derived: WorkModule at accessor+0x50]
// WorkModule::is_flag(0x108) [derived: vtable slot 33]
// 0x20000087 [inferred: work flag — blocks dead effect]
// 0x2000009d [inferred: work flag — blocks dead effect (= 0x20000087 + 0x16)]
// 0x200000c0 [inferred: work flag — blocks dead effect (= 0x20000087 + 0x39)]
extern "C" bool check_hit_dead_effect(BattleObjectModuleAccessor* acc) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    WorkModule* work = static_cast<WorkModule*>(acc->work_module);
    if (!FUN_710068f7a0(acc)) return false;
    if (work->is_flag(0x20000087)) return false;
    if (work->is_flag(0x2000009d)) return false;
    if (work->is_flag(0x200000c0)) return false;
    return true;
}
