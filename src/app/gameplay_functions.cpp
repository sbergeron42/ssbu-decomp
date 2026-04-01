#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

// ── External functions ────────────────────────────────────────────────────────
extern "C" void* FUN_71002f4830(void*);
extern "C" void* FUN_7100314030(void*, void*);
extern "C" void* FUN_710033c360(void*);
extern "C" void* FUN_710033c510(s32);
extern "C" void* FUN_71003596f0(void*);
extern "C" void* FUN_7100359180(void*, void*, void*);
extern "C" void  FUN_710160fb20();
extern "C" void  FUN_7101652f70(s32, s32, s32, s32, s32);

// ── External data ─────────────────────────────────────────────────────────────
// singleton for target-player lookup (adrp 0x71052b5000, ldr #0xfd8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b5fd8;

// per-character final-module singletons in 0x71052bb000 page
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb550;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb578;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb630;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb638;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb6a8;

// per-character final-module singletons in 0x71052c0000 / 0x71052c1000 pages
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c0de0;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c0f48;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c19f8;

// attack-data table (struct size 0x110, field_0x100 is the clear target)
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052c0fd0[];

// ── Stat sub-struct readers (pattern: [p-8] → accessor, [accessor+0x168] → stat) ──

// 7100361250
s32 fighter_kind(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return *reinterpret_cast<s32*>((u8*)s + 0x28);
}

// 7100361260
s32 copy_fighter_kind(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return *reinterpret_cast<s32*>((u8*)s + 0x1f4);
}

// 71003612c0
s32 current_attack_cancel_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return *reinterpret_cast<s32*>((u8*)s + 0x12c);
}

// 71003612e0
s32 attack_phase(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return *reinterpret_cast<s32*>((u8*)s + 0x130);
}

// 7100361450 — bit 1 of stat[0x56]
bool check_stat_damage_elec(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return (*reinterpret_cast<u8*>((u8*)s + 0x56) >> 1) & 1;
}

// 7100361590 — stat[0x74] == 5
bool check_stat_damage(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return *reinterpret_cast<s32*>((u8*)s + 0x74) == 5;
}

// 71003615d0 — stat[0x74] in [0x17, 0x18]
bool check_stat_attack_hold(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return (u32)(*reinterpret_cast<s32*>((u8*)s + 0x74) - 0x17) < 2;
}

// 7100361640
bool check_stat_floor_damage(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    if (*reinterpret_cast<s32*>((u8*)s + 0xd8) == 2) return false;
    void* ptr = *reinterpret_cast<void**>((u8*)s + 0xd0);
    return (*reinterpret_cast<u8*>((u8*)ptr + 0x5e) & 1) != 0;
}

// 7100361880 — bit 3 of stat[0x59]
bool check_stat_unable_attack(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    return (*reinterpret_cast<u8*>((u8*)s + 0x59) >> 3) & 1;
}

// ── Direct accessor field reads ───────────────────────────────────────────────

// 710036b9d0
u8 catch_attack_cancel_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    return *reinterpret_cast<u8*>((u8*)a + 0xbaa);
}

// 710036ba80
s32 num_of_attack_123(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    return *reinterpret_cast<s32*>((u8*)a + 0xb14);
}

// 710036ba90
u8 has_attack_100(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    return *reinterpret_cast<u8*>((u8*)a + 0xb18);
}

// ── Target-player lookup (FUN_7100314030) ────────────────────────────────────

// 71003665f0
s32 target_fighter_kind(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x28);
}

// 7100366620
s32 target_copy_fighter_kind(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x1f4);
}

// 7100366650
s32 target_current_attack_start_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x120);
}

// 7100366680
s32 target_current_attack_combo_end_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x128);
}

// 71003666b0
s32 target_current_attack_cancel_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x12c);
}

// 7100366880 — bit 6 of r[0x55]
bool check_target_stat_attack_catch(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x55) >> 6) & 1;
}

// 7100366b30 — r[0x74] == 5
bool check_target_stat_damage(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x74) == 5;
}

// 7100366bf0 — r[0x74] in [0x15, 0x16]
bool check_target_stat_attack(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x15) < 2;
}

// 7100366c30 — r[0x74] in [0x17, 0x18]
bool check_target_stat_attack_hold(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x17) < 2;
}

// 7100366ca0 — bit 3 of r[0x59]
bool check_target_stat_unable_attack(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x59) >> 3) & 1;
}

// 7100366f90 — float r[0xe0]
float target_damage(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<float*>((u8*)r + 0xe0);
}

// ── Standalone kind checks (integer param, no pointer deref) ─────────────────

// 710068f790 — kind in [0x4e, 0x50]
bool is_miienemy_fighter_kind(s32 kind) {
    return (u32)(kind - 0x4e) < 3;
}

// 7100f0a970 — kind in [0x1e1, 0x1ea]
bool is_status_kind_attack(s32 kind) {
    return (u32)(kind - 0x1e1) < 0xa;
}

// 7101227750 — kind in [0x1e1, 0x1f0]
bool is_status_kind_attack_7101227750(s32 kind) {
    return (u32)(kind - 0x1e1) < 0x10;
}

// ── Stubs ─────────────────────────────────────────────────────────────────────

// 7101670080 — empty stub
void set_info_sandbag_damage() {}

// ── Tail-call dispatchers ─────────────────────────────────────────────────────

// 7100368d30 — adjust accessor+0x180, tail call
void disable_command_attack_button_all(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    FUN_71002f4830((u8*)a + 0x180);
}

// 7100369720 — forward with [accessor+0x168] and accessor+0xc50
void* predict_target_hit_in_attack(void* p, void* p2) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    return FUN_7100359180(
        *reinterpret_cast<void**>((u8*)a + 0x168),
        p2,
        (u8*)a + 0xc50);
}

// 71015c9fd0 — direct tail call
void get_damage_mul_71015c9fd0() {
    FUN_710160fb20();
}

// 7101652f60 — set type=2
void load_summon_fighter_light(s32 fighter_kind_arg, s32 player_no, s32 p2, s32 p3) {
    FUN_7101652f70(fighter_kind_arg, player_no, p2, p3, 2);
}

// 7101653150 — set type=5
void load_summon_fighter_dark(s32 fighter_kind_arg, s32 player_no, s32 p2, s32 p3) {
    FUN_7101652f70(fighter_kind_arg, player_no, p2, p3, 5);
}

// ── Attack data lookups (FUN_710033c360 / FUN_710033c510) ────────────────────

// 7100369ad0
s32 attack_start_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_710033c360((u8*)a + 0x988);
    if (r) return *reinterpret_cast<s32*>((u8*)r + 0x8);
    return 0;
}

// 7100369b70
s32 attack_end_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_710033c360((u8*)a + 0x988);
    if (r) return *reinterpret_cast<s32*>((u8*)r + 0xc);
    return 0;
}

// 7100369c10
float attack_data_x0(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x18);
    return 0.0f;
}

// 7100369c40
float attack_data_x1(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x1c);
    return 0.0f;
}

// 7100369c70
float attack_data_y0(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x20);
    return 0.0f;
}

// 7100369ca0
float attack_data_y1(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x24);
    return 0.0f;
}

// 710036b060 — return -1 on null
s32 most_earliest_hit_frame(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* sub = *reinterpret_cast<void**>((u8*)a + 0x168);
    void* r = FUN_71003596f0(sub);
    if (!r) return -1;
    return *reinterpret_cast<s32*>((u8*)r + 0x10);
}

// ── final_module_hit_success — vtable[1] dispatch on global singleton ─────────

// 7100936fa0
void final_module_hit_success_7100936fa0() {
    auto* obj = DAT_71052bb550;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100974650
void final_module_hit_success_7100974650() {
    auto* obj = DAT_71052bb578;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100a0d230
void final_module_hit_success_7100a0d230() {
    auto* obj = DAT_71052bb630;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100a2a6d0
void final_module_hit_success_7100a2a6d0() {
    auto* obj = DAT_71052bb638;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100b35c20
void final_module_hit_success_7100b35c20() {
    auto* obj = DAT_71052bb6a8;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100cec9c0
void final_module_hit_success_7100cec9c0() {
    auto* obj = DAT_71052c0de0;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7100f11e50
void final_module_hit_success_7100f11e50() {
    auto* obj = DAT_71052c0f48;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7101197690
void final_module_hit_success_7101197690() {
    auto* obj = DAT_71052c19f8;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// ── Work-module vtable dispatch with attack-data table clear ──────────────────
// Pattern: call WorkModule vtable[0x98/8] with flag 0x10000000,
// then clear entry in DAT_71052c0fd0 if result <= 7.

// 7100ba3380
void purin_clear_copy_attack_data(void* p) {
    void* work = *reinterpret_cast<void**>((u8*)p + 0x50);
    s32 idx = reinterpret_cast<s32(*)(void*, s32)>(VT(work)[0x98/8])(work, 0x10000000);
    if (idx <= 7)
        DAT_71052c0fd0[(s64)idx * 0x110 + 0x100] = 0;
}

// 7100fe0760
void special_n_clear_copy_attack_data(void* p) {
    void* work = *reinterpret_cast<void**>((u8*)p + 0x50);
    s32 idx = reinterpret_cast<s32(*)(void*, s32)>(VT(work)[0x98/8])(work, 0x10000000);
    if (idx <= 7)
        DAT_71052c0fd0[(s64)idx * 0x110 + 0x100] = 0;
}

// ── Misc vtable-chain functions ───────────────────────────────────────────────

// 7100fc0110 — shrink-wrapped prologue (early return -1 before frame save)
// asm("") prevents tail-call optimisation; original uses blr+ldp+ret, not br
s32 get_main_fighter_status_kind(void* p) {
    if (!*reinterpret_cast<u8*>((u8*)p + 0x80)) return -1;
    void* a = *reinterpret_cast<void**>((u8*)p + 0x78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x20);
    void* obj = *reinterpret_cast<void**>((u8*)b + 0x40);
    s32 r = reinterpret_cast<s32(*)(void*)>(VT(obj)[0x110/8])(obj);
    asm("");
    return r;
}

// 7100148d80
bool IsPlayersCountedAsParticipants(void* p) {
    void* obj = *reinterpret_cast<void**>((u8*)p + 0x8);
    if (!obj) return false;
    return reinterpret_cast<bool(*)(void*)>(VT(obj)[0x88/8])(obj);
}

// 710069bf60
void set_pickelblock_mode_ignoreandattack(void* p) {
    void* obj = *reinterpret_cast<void**>((u8*)p + 0x58);
    reinterpret_cast<void(*)(void*, s32)>(VT(obj)[0x808/8])(obj, 2);
}
