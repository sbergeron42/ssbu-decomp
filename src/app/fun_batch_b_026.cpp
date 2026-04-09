#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/WorkModule.h"
#include "app/FighterInformation.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 026
// sv_information / sv_fighter_util functions — FighterInformation field readers
// Range: 0x710227e-0x7102285

#define VT(m) (*reinterpret_cast<void***>(m))
#define HIDDEN __attribute__((visibility("hidden")))

[[noreturn]] extern "C" void abort();
extern "C" void FUN_710067de90(void*, u64, s32, s32, u32);
extern "C" u64 FUN_71006798f0(void*, u32);
extern "C" void FUN_71003ab390(u8*, u32);
extern "C" void FUN_71004eb4b0(u64, u32, u32, u64);
extern "C" u32 FUN_710067a3a0(void*, s32);

// Singletons — hidden visibility for ADRP+LDR codegen
namespace lib {
    extern "C" void* Singleton_app_FighterManager_instance_
        asm("_ZN3lib9SingletonIN3app14FighterManagerEE9instance_E") HIDDEN;
    extern "C" void* Singleton_app_BossManager_instance_
        asm("_ZN3lib9SingletonIN3app11BossManagerEE9instance_E") HIDDEN;
}
// *instance_ dereferences the FM pointer to get FighterManagerData* (at +0x0)
#define FM_DATA (*reinterpret_cast<u8**>(lib::Singleton_app_FighterManager_instance_))
#define FM_RAW  (lib::Singleton_app_FighterManager_instance_)
#define BM_INST (reinterpret_cast<u8*>(lib::Singleton_app_BossManager_instance_))

// ════════════════════════════════════════════════════════════════════
// sv_information — FighterInformation field readers
// ════════════════════════════════════════════════════════════════════

// ── 0x710227ed00 (84B) — is_dead_up_force_crush ────────────────────
// Returns byte at FighterInfo+0x6e (death animation force crush flag).
// [derived: Ghidra app::sv_information::is_dead_up_force_crush — reads
//  work_module→vt[0x98/8](work, 0x10000000) → entry ID, bounds check <8,
//  FM→entries[id]+0xf8→+0x6e]
u8 FUN_710227ed00(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    if (id < 8) {
        u8* fm = FM_DATA;
        u8* entry = *reinterpret_cast<u8**>(fm + (long)(s32)id * 8 + 0x20);
        app::FighterInformationData* fi = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
        return fi->dead_up_force_crush;
    }
    abort();
}

// ── 0x710227ef00 (84B) — sleep_time_mul ────────────────────────────
// Returns float at FighterInfo+0x384 (sleep time multiplier).
// [derived: Ghidra app::sv_information::sleep_time_mul — same pattern,
//  reads +0x384 (=900 decimal) as u32]
u32 FUN_710227ef00(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    if (id < 8) {
        u8* fm = FM_DATA;
        u8* entry = *reinterpret_cast<u8**>(fm + (long)(s32)id * 8 + 0x20);
        app::FighterInformationData* fi = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
        return fi->sleep_time_mul;
    }
    abort();
}

// ── 0x7102281890 (84B) — get_dead_up_star_fall_prob ────────────────
// Returns u32 at FighterInfo+0x7c (star fall probability on death up).
// [derived: Ghidra app::sv_fighter_util::get_dead_up_star_fall_prob —
//  same pattern, reads +0x7c as u32]
u32 FUN_7102281890(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    if (id < 8) {
        u8* fm = FM_DATA;
        u8* entry = *reinterpret_cast<u8**>(fm + (long)(s32)id * 8 + 0x20);
        app::FighterInformationData* fi = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
        return fi->star_fall_prob;
    }
    abort();
}

// ── 0x710227eea0 (88B) — owner_rank ────────────────────────────────
// Returns the owner's rank from FighterManager, or 0 if disabled.
// [derived: Ghidra app::sv_information::owner_rank — checks FM+0xcd,
//  if set calls FUN_71006798f0(FM, id)]
u64 FUN_710227eea0(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    u8* fm = FM_DATA;
    if (*(fm + 0xcd) != 0) {
        return FUN_71006798f0(FM_RAW, id);
    }
    return 0;
}

// ── 0x710227ee30 (104B) — owner_handi ──────────────────────────────
// Returns handicap value from FighterInfo+0x370, or 0 if disabled.
// [derived: Ghidra app::sv_information::owner_handi — bounds check >=8
//  → abort, check FM+0xcd, read +0x370 from FighterInfo]
u32 FUN_710227ee30(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    if (id >= 8) {
        abort();
    }
    u8* fm = FM_DATA;
    if (*(fm + 0xcd) != 0) {
        u8* entry = *reinterpret_cast<u8**>(fm + (long)(s32)id * 8 + 0x20);
        app::FighterInformationData* fi = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
        return fi->handi;
    }
    return 0;
}

// ── 0x71022819a0 (116B) — set_on_rebirth ───────────────────────────
// Sets on_rebirth flag at FighterInfo+0x38C and clears +0xA42 if false.
// [derived: Ghidra app::sv_fighter_util::set_on_rebirth — writes param_2
//  to +0x38C (on_rebirth in FighterInformationData), if false clears +0xA42]
void FUN_71022819a0(u8* L, u8 param_2) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    u32 id = (u32)acc->work_module->get_int(0x10000000);
    if (id < 8) {
        u8* fm = FM_DATA;
        u8* entry = *reinterpret_cast<u8**>(fm + (long)(s32)id * 8 + 0x20);
        app::FighterInformationData* fi = *reinterpret_cast<app::FighterInformationData**>(entry + 0xf8);
        fi->on_rebirth = param_2;
        if (!fi->on_rebirth) {
            *reinterpret_cast<u8*>(reinterpret_cast<u8*>(fi) + 0xa42) = 0;
        }
        return;
    }
    abort();
}

// ── 0x7102281a20 (112B) — set_dead_rumble ──────────────────────────
// Triggers a dead rumble effect via FighterManager and ControlModule.
// [derived: Ghidra app::sv_fighter_util::set_dead_rumble — calls
//  FUN_710067de90(FM, hash, 0, 0, 0x50000000), then
//  control_module(+0x48)→vtable[0x2e0/8](ctl, hash, 0x50000000)]
void FUN_7102281a20(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    app::BattleObjectModuleAccessor* acc = *reinterpret_cast<app::BattleObjectModuleAccessor**>(ctx + 0x1a0);
    FUN_710067de90(FM_RAW,
                   0x10456d7c11ULL, 0, 0, 0x50000000);
    u8* control = reinterpret_cast<u8*>(acc->fighter_control_module);
    reinterpret_cast<void(*)(u8*, u64, u32)>(VT(control)[0x2e0/8])(
        control, 0x10456d7c11ULL, 0x50000000);
}

// ── 0x7102283d10 (92B) — set_power_mul_region_attr_info ────────────
// Copies region attr info between two battle objects via attack modules.
// [derived: Ghidra app::sv_battle_object::set_power_mul_region_attr_info
//  — attack_module (+0xA0) vtable[0x318/8] read, vtable[0x320/8] write.
//  Uses 18-byte stack buffer (u64+u64+u8+u8 padded)]
void FUN_7102283d10(app::BattleObjectModuleAccessor* param_1, app::BattleObjectModuleAccessor* param_2) {
    u64 local_40 = 0;
    u8 local_38 = 0;
    u64 local_30 = 0;
    u8 local_28 = 0;
    u8* atk2 = reinterpret_cast<u8*>(param_2->attack_module);
    reinterpret_cast<void(*)(u8*, void*)>(VT(atk2)[0x318/8])(atk2, &local_40);
    u8* atk1 = reinterpret_cast<u8*>(param_1->attack_module);
    reinterpret_cast<void(*)(u8*, void*)>(VT(atk1)[0x320/8])(atk1, &local_40);
}

// ── 0x7102284520 (92B) — start_boss_finish ─────────────────────────
// Triggers boss finish event via BossManager.
// [derived: Ghidra app::sv_item::start_boss_finish — calls FUN_71003ab390
//  to get battle object, checks BossManager singleton, calls FUN_71004eb4b0]
void FUN_7102284520(u8* L, u32 param_2, u64 param_3) {
    u8 stack_buf[16];
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    FUN_71003ab390(stack_buf, *reinterpret_cast<u32*>(ctx + 400));
    u8* bm = BM_INST;
    if (bm != nullptr) {
        u64 boss_data = *reinterpret_cast<u64*>(bm + 8);
        long local_28 = *reinterpret_cast<long*>(stack_buf + 8);
        FUN_71004eb4b0(boss_data,
                       *reinterpret_cast<u32*>(local_28 + 8),
                       param_2, param_3);
    }
}

// ── 0x7102211600 (84B) — Pac_Land ──────────────────────────────────
// Checks a FighterManager condition and pushes result to lua stack.
// [derived: Ghidra FUN_7102211600 — calls FUN_710067a3a0(FM, 1),
//  pushes result&1 with type tag 1 (bool). Returns 1]
u64 FUN_7102211600(u8* L) {
    u32 result = FUN_710067a3a0(FM_RAW, 1);
    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[0] = result & 1;
    stack[2] = 1;  // type tag: bool
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 1;
}
