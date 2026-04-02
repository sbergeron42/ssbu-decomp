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
extern "C" void  FUN_71004eb6a0(s32);
extern "C" void  FUN_71015aba90(void*, void*, s32);
extern "C" void  FUN_71015b4d40(void*, void*);
extern "C" void  FUN_7100697570();
extern "C" void  FUN_710067de90(void*, u64, s32, s32, s32);
extern "C" void  FUN_71006a7100(void*);
extern "C" void  FUN_71006ab9d0(void*);
extern "C" void  FUN_71006e1b90(void*, u32);
extern "C" void  FUN_71006eb6c0(void*, u32, u32, u32, u32, u32, u32);
extern "C" void  FUN_71006eb8c0(void*);

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

// FighterManager singleton ptr (adrp 0x71052b8000, ldr #0x4f8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b84f8;

// FighterManager global for light/dark fighter arrays (adrp 0x7105329000, ldr #0x868)
extern "C" __attribute__((visibility("hidden"))) void* DAT_7105329868;

// singleton base for hit_spd / DOLL_HIT_DATA / EXPLOSIONBOMB (adrp 0x71052bb000, ldr #0x3b0)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;

// final_module singletons in 0x71052c1000 page (single-indirected: *global = object)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c1a48;
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c1af8;

// fighter restart-position manager (adrp 0x71052c3000, ldr #0x70)
extern "C" __attribute__((visibility("hidden"))) void** DAT_71052c3070;

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
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x28);
}

// 7100366620
s32 target_copy_fighter_kind(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x1f4);
}

// 7100366650
s32 target_current_attack_start_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x120);
}

// 7100366680
s32 target_current_attack_combo_end_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x128);
}

// 71003666b0
s32 target_current_attack_cancel_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x12c);
}

// 7100366880 — bit 6 of r[0x55]
bool check_target_stat_attack_catch(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x55) >> 6) & 1;
}

// 7100366b30 — r[0x74] == 5
bool check_target_stat_damage(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x74) == 5;
}

// 7100366bf0 — r[0x74] in [0x15, 0x16]
bool check_target_stat_attack(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x15) < 2;
}

// 7100366c30 — r[0x74] in [0x17, 0x18]
bool check_target_stat_attack_hold(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x17) < 2;
}

// 7100366ca0 — bit 3 of r[0x59]
bool check_target_stat_unable_attack(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x59) >> 3) & 1;
}

// 7100366f90 — float r[0xe0]
float target_damage(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
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
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_710033c360((u8*)a + 0x988);
    if (r) return *reinterpret_cast<s32*>((u8*)r + 0x8);
    return 0;
}

// 7100369b70
s32 attack_end_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = FUN_710033c360((u8*)a + 0x988);
    if (r) return *reinterpret_cast<s32*>((u8*)r + 0xc);
    return 0;
}

// 7100369c10
float attack_data_x0(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x18);
    return 0.0f;
}

// 7100369c40
float attack_data_x1(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x1c);
    return 0.0f;
}

// 7100369c70
float attack_data_y0(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x20);
    return 0.0f;
}

// 7100369ca0
float attack_data_y1(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    s32 id = *reinterpret_cast<s32*>((u8*)a + 0x988);
    void* r = FUN_710033c510(id);
    if (r) return *reinterpret_cast<float*>((u8*)r + 0x24);
    return 0.0f;
}

// 710036b060 — return -1 on null
s32 most_earliest_hit_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
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
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* work = *reinterpret_cast<void**>((u8*)p + 0x50);
    s32 idx = reinterpret_cast<s32(*)(void*, s32)>(VT(work)[0x98/8])(work, 0x10000000);
    if (idx <= 7)
        DAT_71052c0fd0[(s64)idx * 0x110 + 0x100] = 0;
}

// 7100fe0760
void special_n_clear_copy_attack_data(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
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

// ── status_kind range checks ──────────────────────────────────────────────────

// 7101227760 — true if kind in [0x47..0x4c] or [0x86..0x88]
bool is_status_kind_attack_remain_arm(s32 kind) {
    return (u32)(kind - 0x86) < 3 || (u32)(kind - 0x47) < 6;
}

// ── final_module_hit_success — vtable[1] on 0x71052c1xxx singletons ──────────

// 71012281a0
void final_module_hit_success_71012281a0() {
    void* obj = DAT_71052c1a48;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// 7101289c80
void final_module_hit_success_7101289c80() {
    void* obj = DAT_71052c1af8;
    reinterpret_cast<void(*)(void*)>(VT(obj)[0x8/8])(obj);
}

// ── Throw attack helpers ──────────────────────────────────────────────────────

// 71015c2720 — accessor[-8]→[+0x1a0]→[+0x190]→[+0x220], call with (obj, x1, 0)
void throw_attack(void* p, void* other) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    FUN_71015aba90(d, other, 0);
}

// 71015cb6e0 — guard on [battle_obj+0x8]>>28==4, then same chain
void throw_attack_71015cb6e0(void* battle_obj, void* other) {
    if (!battle_obj) return;
    if ((*reinterpret_cast<u32*>((u8*)battle_obj + 0x8) >> 28) != 4) return;
    void* c = *reinterpret_cast<void**>((u8*)battle_obj + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    FUN_71015aba90(d, other, 0);
}

// ── Explosion/hit object readers ─────────────────────────────────────────────
// Chain: acc[-8]→[+0x1a0]→[+0x190]→[+0x220]→[+0x90]→field

// 71015c5560
s32 get_pre_explosion_hit_object_id(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    void* e = *reinterpret_cast<void**>((u8*)d + 0x90);
    return *reinterpret_cast<s32*>((u8*)e + 0x58);
}

// 71015c5580
s32 get_pre_explosion_attack_object_id(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    void* e = *reinterpret_cast<void**>((u8*)d + 0x90);
    return *reinterpret_cast<s32*>((u8*)e + 0x5c);
}

// 71015c5b30 — store bool to [+0x62]
void set_postponed_damage_check_on_process_hit(void* p, bool flag) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    *reinterpret_cast<u8*>((u8*)d + 0x62) = flag & 1;
}

// ── apply_fighter_scale ───────────────────────────────────────────────────────

// 71015cb3a0 — guard on other[+0x8]>>28==4, then call scale helper
void apply_fighter_scale(void* p, void* other) {
    if (!other) return;
    if ((*reinterpret_cast<u32*>((u8*)other + 0x8) >> 28) != 4) return;
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* e = *reinterpret_cast<void**>((u8*)other + 0x190);
    void* x0 = *reinterpret_cast<void**>((u8*)e + 0x220);
    void* x1 = *reinterpret_cast<void**>((u8*)c + 0x220);
    FUN_71015b4d40(x0, x1);
}

// ── FighterManager readers ────────────────────────────────────────────────────

// 71015ce4d0 — FighterManager singleton → [+0xa0]
s32 get_fighter_entry_count() {
    void* m = *reinterpret_cast<void**>(DAT_71052b84f8);
    return *reinterpret_cast<s32*>((u8*)m + 0xa0);
}

// ── Fighter restart position ──────────────────────────────────────────────────

// 710164c130 — store (x, y, 0, 0) as q at [mgr+0x20], set flag [mgr+0x1c]=1
void set_change_fighter_restart_position(float x, float y) {
    void* mgr = *DAT_71052c3070;
    float buf[4] = { x, y, 0.0f, 0.0f };
    __builtin_memcpy((u8*)mgr + 0x20, buf, 16);
    *reinterpret_cast<u8*>((u8*)mgr + 0x1c) = 1;
}

// 710164c160 — clear flag and zero position vector at [mgr+0x20]
void cancel_change_fighter_restart_position() {
    void* mgr = *DAT_71052c3070;
    *reinterpret_cast<u8*>((u8*)mgr + 0x1c) = 0;
    float zero[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    __builtin_memcpy((u8*)mgr + 0x20, zero, 16);
}

// ── Damage attacker ID ────────────────────────────────────────────────────────

// 7101651a20 — [p+0xa8] obj → vtable[0x198/8]() → [result+0xc] or 0x50000000
s32 get_damage_attacker_id(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* obj = *reinterpret_cast<void**>((u8*)p + 0xa8);
    void* r = reinterpret_cast<void*(*)(void*)>(VT(obj)[0x198/8])(obj);
    if (!r) return 0x50000000;
    return *reinterpret_cast<s32*>((u8*)r + 0xc);
}

// ── Summon fighter helpers ────────────────────────────────────────────────────

// 7101652f40 — call FUN_71004eb6a0 only if fighter_kind in [2..7]
void entry_summon_fighter(s32 fighter_kind) {
    if ((u32)(fighter_kind - 2) <= 5)
        FUN_71004eb6a0(fighter_kind);
}

// ── Light/dark fighter count ──────────────────────────────────────────────────

// 7101653710 — (ptr_end - ptr_begin) / 8 for light fighter array
int get_light_fighter_kind_num() {
    void* g = DAT_7105329868;
    if (!g) return 0;
    void* p = *reinterpret_cast<void**>(g);
    u8* end   = *reinterpret_cast<u8**>((u8*)p + 0x238);
    u8* begin = *reinterpret_cast<u8**>((u8*)p + 0x230);
    return (int)((u64)(end - begin) >> 3);
}

// 71016537d0 — same for dark fighter array
int get_dark_fighter_kind_num() {
    void* g = DAT_7105329868;
    if (!g) return 0;
    void* p = *reinterpret_cast<void**>(g);
    u8* end   = *reinterpret_cast<u8**>((u8*)p + 0x250);
    u8* begin = *reinterpret_cast<u8**>((u8*)p + 0x248);
    return (int)((u64)(end - begin) >> 3);
}

// ── Global singleton float getters ────────────────────────────────────────────
// All use: DAT_71052bb3b0 → [+offset] → [+offset2] → float at [+field]

// 710165c5d0 — DOLL hit data size
float DOLL_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc08);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1d8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 710165d2a0 — explosion bomb burst damage
float EXPLOSIONBOMB_BURST_DAMAGE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x3f0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x108);
    return *reinterpret_cast<float*>((u8*)b + 0x34);
}

// 710165e7c0 — hit speed x
float hit_spd_x() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xf88);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1c8);
    return *reinterpret_cast<float*>((u8*)b + 0x14);
}

// 710165e7e0 — hit speed y
float hit_spd_y() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xf88);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1c8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// ── LINK linkbomb getters (guarded: return 0.0 unless fighter_kind==0x78) ─────
// Chain: DAT_71052bb3b0 → [0xe0] → [0x1a8] → float

// 710165ed10
float LINK_LINKBOMB_LINKBOMB_MIN_DAMAGE(s32 fighter_kind) {
    if (fighter_kind != 0x78) return 0.0f;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xe0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 710165ed40
float LINK_LINKBOMB_LINKBOMB_MAX_DAMAGE(s32 fighter_kind) {
    if (fighter_kind != 0x78) return 0.0f;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xe0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a8);
    return *reinterpret_cast<float*>((u8*)b + 0x1c);
}

// 710165ed70
float LINK_LINKBOMB_LINKBOMB_MIN_DAMAGE_SPEED(s32 fighter_kind) {
    if (fighter_kind != 0x78) return 0.0f;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xe0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a8);
    return *reinterpret_cast<float*>((u8*)b + 0x20);
}

// 710165eda0
float LINK_LINKBOMB_LINKBOMB_MAX_DAMAGE_SPEED(s32 fighter_kind) {
    if (fighter_kind != 0x78) return 0.0f;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xe0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a8);
    return *reinterpret_cast<float*>((u8*)b + 0x24);
}

// ── LOG hit data getters ──────────────────────────────────────────────────────

// 710165f320
float LOG_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc08);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// ── MECHAKOOPA hit data getters ───────────────────────────────────────────────
// Chain: DAT_71052bb3b0 → [0xd20] → [0x1b0 or 0x198] → field

// 7101661340
float MECHAKOOPA_DAMAGE_SPEED_MUL() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xd20);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x198);
    return *reinterpret_cast<float*>((u8*)b + 0xc);
}

// 71016614a0
float MECHAKOOPA_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xd20);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1b0);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 71016614c0
void* MECHAKOOPA_HIT_DATA_JOINT() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xd20);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1b0);
    return *reinterpret_cast<void**>((u8*)b + 0x20);
}

// 71016614e0
s32 MECHAKOOPA_HIT_DATA_PART() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xd20);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1b0);
    return *reinterpret_cast<s32*>((u8*)b + 0x28);
}

// 7101661500
s32 MECHAKOOPA_HIT_DATA_HEIGHT() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xd20);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1b0);
    return *reinterpret_cast<s32*>((u8*)b + 0x2c);
}

// ── PACMAN hit data getters ───────────────────────────────────────────────────
// Chain: DAT_71052bb3b0 → [0xc78] → [sub_off] → field

// 7101661fe0
float PACMAN_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1f8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101662cb0
float PACMAN_HIT_DATA_SIZE_7101662cb0() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101663a80
float PACMAN_HIT_DATA_SIZE_7101663a80() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x228);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101664af0
float PACMAN_HIT_DATA_SIZE_7101664af0() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1b0);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101665780
s32 PACMAN_HIT_LIFE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0xd8);
    return *reinterpret_cast<s32*>((u8*)b + 0x10);
}

// 7101665800
float PACMAN_HIT_DATA_SIZE_7101665800() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x258);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101666500
float PACMAN_HIT_DATA_SIZE_7101666500() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x210);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 71016671d0
float PACMAN_HIT_DATA_SIZE_71016671d0() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1e0);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 7101667eb0
float PACMAN_HIT_DATA_SIZE_7101667eb0() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1c8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// ── Damage/fighter field getters (2-hop: DAT_71052bb3b0 → [0x13b0] → field) ──

// 710166e130
float auto_damage() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x13b0);
    return *reinterpret_cast<float*>((u8*)a + 0x520);
}

// 710166e150
float fighter_landing_damage_mul() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x13b0);
    return *reinterpret_cast<float*>((u8*)a + 0x524);
}

// 710166e170
s32 fighter_landing_damage_mul_frame() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x13b0);
    return *reinterpret_cast<s32*>((u8*)a + 0x528);
}

// 710166e230
s32 damage_attack_stop_frame() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x13b0);
    return *reinterpret_cast<s32*>((u8*)a + 0x550);
}

// ── POWERESA hit getters (DAT_71052bb3b0 → [0xc78] → [sub] → field) ──────────

// 710166f6a0
float POWERESA_HIT_SPEED_Y() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x360);
    return *reinterpret_cast<float*>(b);
}

// 710166f700
float POWERESA_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc78);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x378);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// ── HOLYWATER hit getters (fighter_kind selects 0xf18 vs 0xf50) ──────────────
// Chain: DAT_71052bb3b0 → [0xf18 or 0xf50] → [0x240] → float

// 7101670e90
float HOLYWATER_HIT_DEC_HP(s32 fighter_kind) {
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x28);
}

// 7101671070
float HOLYWATER_HIT_HOP_SPEED_Y(s32 fighter_kind) {
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x2c);
}

// 71016710a0
float HOLYWATER_HIT_SPEED_X_MUL(s32 fighter_kind) {
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x30);
}

// 71016710d0
float HOLYWATER_HIT_HOP_AFTER_FALL_ACCEL(s32 fighter_kind) {
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x34);
}

// 7101671100
float HOLYWATER_HIT_HOP_AFTER_SPEED_Y_MAX(s32 fighter_kind) {
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x38);
}

// ── Duplicate getter (same impl as get_fighter_entry_count) ───────────────────

// 7101673cc0
s32 get_fighter_entry_count_7101673cc0() {
    void* m = *reinterpret_cast<void**>(DAT_71052b84f8);
    return *reinterpret_cast<s32*>((u8*)m + 0xa0);
}

// ── WARIO / WIIFITBALL singleton float getters ────────────────────────────────

// 7101677de0
float WARIO_WARIOBIKE_BIKE_HP_DAMAGE_EFFECT() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x7a8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x110);
    return *reinterpret_cast<float*>((u8*)b + 0xbc);
}

// 71016781b0
float WIIFITBALL_ATTACK_START_SPEED() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xb60);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x120);
    return *reinterpret_cast<float*>((u8*)b + 0x34);
}

// 71016781d0
float WIIFITBALL_ATTACK_POWER_MAX() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xb60);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x120);
    return *reinterpret_cast<float*>((u8*)b + 0x3c);
}

// 7101678450
float WIIFITBALL_HIT_STOP_FRAME_MUL() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xb60);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x120);
    return *reinterpret_cast<float*>((u8*)b + 0x4c);
}

// ── Misc getters (other pages / patterns) ────────────────────────────────────

// 710227ec80 — tail-call to dead-camera hit-count getter
void dead_up_camera_hit_count() {
    FUN_7100697570();
}

// 7102282350 — DAT_71052bb3b0 → [0x50] → s0[0x48]
float get_default_fighter_param_ground_speed_limit() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x50);
    return *reinterpret_cast<float*>((u8*)a + 0x48);
}

// 7102281a90 — request camera rumble via FighterManager
void set_dead_camera_hit_rumble() {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067de90(mgr, 0x001013dbb854ull, 0, 0, 0x50000000);
}

// 7102281bc0 — hash selector based on status_kind & ~1 == 0x3c
u64 get_attack_s3_s_motion(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    u32 sk = *reinterpret_cast<u32*>((u8*)a + 0x198) & ~1u;
    return (sk == 0x3c) ? 0x000decb03ce6ull : 0x000b7dd72b57ull;
}

// 7102281c70 — same pattern, different hashes (lw3 motion)
u64 get_attack_lw3_motion(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    u32 sk = *reinterpret_cast<u32*>((u8*)a + 0x198) & ~1u;
    return (sk == 0x3c) ? 0x000c60464aa4ull : 0x000a18b4d5e5ull;
}

// ── AttackModule _impl dispatchers ───────────────────────────────────────────

// 7101fd04f0 — acc[+0xa0] → vtable[0x1d8/8]
float AttackModule__speed_impl(void* acc) {
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0xa0);
    return reinterpret_cast<float(*)(void*)>(VT(mod)[0x1d8 / 8])(mod);
}

// 7101fd0930 — acc[+0xa0] → vtable[0x4a0/8], forward part index
float AttackModule__attack_part_speed_impl(void* acc, s32 part) {
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0xa0);
    return reinterpret_cast<float(*)(void*, s32)>(VT(mod)[0x4a0 / 8])(mod, part);
}

// ── CameraModule _impl dispatchers ───────────────────────────────────────────

// 7101ff0960 — acc[+0x60] → vtable[0x140/8], tail call (no frame)
void CameraModule__set_player_no_impl(void* acc, s32 player_no) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0x60);
    reinterpret_cast<void(*)(void*, s32)>(VT(mod)[0x140 / 8])(mod, player_no);
}

// ── ControlModule _impl dispatchers ──────────────────────────────────────────

// 7102001500 — acc[+0x48] → vtable[0x2c0/8], no-arg tail call
void ControlModule__request_rumble_hit_impl(void* acc) {
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0x48);
    reinterpret_cast<void(*)(void*)>(VT(mod)[0x2c0 / 8])(mod);
}

// ── DamageModule _impl dispatchers ───────────────────────────────────────────

// 710200b690 — acc[+0xa8] → vtable[0x50/8], bool param (and w1,w1,#1)
void DamageModule__sleep_impl(void* acc, s32 enable) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0xa8);
    reinterpret_cast<void(*)(void*, bool)>(VT(mod)[0x50 / 8])(mod, (bool)enable);
}

// 710200b8c0 — acc[+0xa8] → vtable[0x290/8], no-arg tail call
void DamageModule__start_damage_info_log_impl(void* acc) {
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0xa8);
    reinterpret_cast<void(*)(void*)>(VT(mod)[0x290 / 8])(mod);
}

// ── FighterCutInManager _impl functions ──────────────────────────────────────

// 71020a8b90 — deref first field, tail call
void FighterCutInManager__request_start_impl(void* p) {
    FUN_71006a7100(*reinterpret_cast<void**>(p));
}

// 71020a8ba0 — deref first field, tail call
void FighterCutInManager__request_end_impl(void* p) {
    FUN_71006ab9d0(*reinterpret_cast<void**>(p));
}

// 71020a8bb0 — [*p+0xb9] && [*p+0xbc]==6
bool FighterCutInManager__is_play_motion_camera_impl(void* p) {
    void* s = *reinterpret_cast<void**>(p);
    if (!*reinterpret_cast<u8*>((u8*)s + 0xb9)) return false;
    return *reinterpret_cast<s32*>((u8*)s + 0xbc) == 6;
}

// 71020a8c60 — [*p+0xb9] || [*p+0x1e8] || [*p+0x398]>0
bool FighterCutInManager__is_play_impl(void* p) {
    void* s = *reinterpret_cast<void**>(p);
    if (*reinterpret_cast<u8*>((u8*)s + 0xb9)) return true;
    if (*reinterpret_cast<u8*>((u8*)s + 0x1e8)) return true;
    return *reinterpret_cast<s32*>((u8*)s + 0x398) > 0;
}

// 71020a8ca0 — [*p+0xb9] || [*p+0x1e8]!=0
bool FighterCutInManager__is_play_status_impl(void* p) {
    void* s = *reinterpret_cast<void**>(p);
    if (*reinterpret_cast<u8*>((u8*)s + 0xb9)) return true;
    return *reinterpret_cast<u8*>((u8*)s + 0x1e8) != 0;
}

// 71020a8cd0 — append s32 to counted array: count=[*p+0x88], arr=[*p+0x90]
void FighterCutInManager__add_task_impl(void* p, s32 task) {
    void* s = *reinterpret_cast<void**>(p);
    u64 idx = *reinterpret_cast<u64*>((u8*)s + 0x88);
    s32* arr = *reinterpret_cast<s32**>((u8*)s + 0x90);
    arr[idx] = task;
    (*reinterpret_cast<u64*>((u8*)s + 0x88))++;
}

// 71020a8cf0 — store float to [*p+0x2d0]
void FighterCutInManager__set_throw_finish_zoom_rate_impl(void* p, float rate) {
    void* s = *reinterpret_cast<void**>(p);
    *reinterpret_cast<float*>((u8*)s + 0x2d0) = rate;
}

// ── FighterStatusModuleImpl _impl functions ───────────────────────────────────

// 71020a99f0 — acc[+0x40], bool params masked with &1, tail call
void FighterStatusModuleImpl__set_fighter_status_data_impl(
        void* acc, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6) {
    void* mod = *reinterpret_cast<void**>((u8*)acc + 0x40);
    FUN_71006eb6c0(mod, a1 & 1, a2, a3 & 1, a4 & 1, a5 & 1, a6);
}

// 71020a9a10 — acc[+0x40] → tail call FUN_71006eb8c0
void FighterStatusModuleImpl__reset_log_action_info_impl(void* acc) {
    FUN_71006eb8c0(*reinterpret_cast<void**>((u8*)acc + 0x40));
}

// ── FighterMotionModuleImpl _impl functions ───────────────────────────────────

// 71020aa000 — drop x0, forward (x1→x0, x2→x1) to FUN_71006e1b90
void FighterMotionModuleImpl__add_body_type_hash_impl(void*, void* obj, u32 hash) {
    FUN_71006e1b90(obj, hash);
}
