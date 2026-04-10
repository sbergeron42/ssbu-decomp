#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/WorkModule.h"
#include "app/modules/GroundModule.h"
#include "app/modules/DamageModule.h"

using app::BattleObjectModuleAccessor;

#define VT(m) (*reinterpret_cast<void***>(m))

// ── External functions ────────────────────────────────────────────────────────
extern "C" void* FUN_71002f4830(void*);
extern "C" void* aiGetTargetById_7100314030(void*, void*);
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

// pointer to a 16-byte zero vector (adrp 0x71052a7000, ldr #0xa88)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052a7a88;

// NOTE: stat sub-struct readers (fighter_kind, copy_fighter_kind, etc.) moved to fun_batch_d5_043.cpp

// 7100361640
// Orig structure: b.eq to shared return-false tail; b.ne falls through to load+tbnz
bool check_stat_floor_damage(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* s = *reinterpret_cast<void**>((u8*)a + 0x168);
    if (*reinterpret_cast<s32*>((u8*)s + 0xd8) != 2) {
        void* ptr = *reinterpret_cast<void**>((u8*)s + 0xd0);
        if (*reinterpret_cast<u8*>((u8*)ptr + 0x5e) & 1) return true;
    }
    return false;
}

// NOTE: check_stat_unable_attack, catch_attack_cancel_frame, num_of_attack_123,
// has_attack_100 moved to fun_batch_d5_043.cpp

// ── Target-player lookup (aiGetTargetById_7100314030) ────────────────────────────────────

// 71003665f0
s32 target_fighter_kind(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x28);
}

// 7100366620
s32 target_copy_fighter_kind(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x1f4);
}

// 7100366650
s32 target_current_attack_start_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x120);
}

// 7100366680
s32 target_current_attack_combo_end_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x128);
}

// 71003666b0
s32 target_current_attack_cancel_frame(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x12c);
}

// 7100366880 -- bit 6 of r[0x55]
bool check_target_stat_attack_catch(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x55) >> 6) & 1;
}

// 7100366b30 -- r[0x74] == 5
bool check_target_stat_damage(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<s32*>((u8*)r + 0x74) == 5;
}

// 7100366bf0 -- r[0x74] in [0x15, 0x16]
bool check_target_stat_attack(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x15) < 2;
}

// 7100366c30 -- r[0x74] in [0x17, 0x18]
bool check_target_stat_attack_hold(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (u32)(*reinterpret_cast<s32*>((u8*)r + 0x74) - 0x17) < 2;
}

// 7100366ca0 -- bit 3 of r[0x59]
bool check_target_stat_unable_attack(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return (*reinterpret_cast<u8*>((u8*)r + 0x59) >> 3) & 1;
}

// 7100366f90 -- float r[0xe0]
float target_damage(void* p) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* r = aiGetTargetById_7100314030(DAT_71052b5fd8, (u8*)a + 0xc50);
    return *reinterpret_cast<float*>((u8*)r + 0xe0);
}

// ── Standalone kind checks (integer param, no pointer deref) ─────────────────

// 710068f790 -- kind in [0x4e, 0x50]
bool is_miienemy_fighter_kind(s32 kind) {
    return (u32)(kind - 0x4e) < 3;
}

// 7100f0a970 -- kind in [0x1e1, 0x1ea]
bool is_status_kind_attack(s32 kind) {
    return (u32)(kind - 0x1e1) < 0xa;
}

// 7101227750 -- kind in [0x1e1, 0x1f0]
bool is_status_kind_attack_7101227750(s32 kind) {
    return (u32)(kind - 0x1e1) < 0x10;
}

// ── Stubs ─────────────────────────────────────────────────────────────────────

// 7101670080 -- empty stub
void set_info_sandbag_damage() {}

// ── Tail-call dispatchers ─────────────────────────────────────────────────────

// 7100368d30 -- adjust accessor+0x180, tail call
void disable_command_attack_button_all(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    FUN_71002f4830((u8*)a + 0x180);
}

// 7100369720 -- forward with [accessor+0x168] and accessor+0xc50
void* predict_target_hit_in_attack(void* p, void* p2) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    return FUN_7100359180(
        *reinterpret_cast<void**>((u8*)a + 0x168),
        p2,
        (u8*)a + 0xc50);
}

// 71015c9fd0 -- direct tail call
void get_damage_mul_71015c9fd0() {
    FUN_710160fb20();
}

// 7101652f60 -- set type=2
void load_summon_fighter_light(s32 fighter_kind_arg, s32 player_no, s32 p2, s32 p3) {
    FUN_7101652f70(fighter_kind_arg, player_no, p2, p3, 2);
}

// 7101653150 -- set type=5
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

// 710036b060 -- return -1 on null
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

// ── final_module_hit_success -- vtable[1] dispatch on global singleton ─────────

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
void purin_clear_copy_attack_data(BattleObjectModuleAccessor* acc) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    s32 idx = acc->work_module->get_int(0x10000000);
    if (idx <= 7)
        DAT_71052c0fd0[(s64)idx * 0x110 + 0x100] = 0;
}

// 7100fe0760
void special_n_clear_copy_attack_data(BattleObjectModuleAccessor* acc) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    s32 idx = acc->work_module->get_int(0x10000000);
    if (idx <= 7)
        DAT_71052c0fd0[(s64)idx * 0x110 + 0x100] = 0;
}

// ── Misc vtable-chain functions ───────────────────────────────────────────────

// 7100148d80
bool IsPlayersCountedAsParticipants(void* p) {
    void* obj = *reinterpret_cast<void**>((u8*)p + 0x8);
    if (!obj) return false;
    return reinterpret_cast<bool(*)(void*)>(VT(obj)[0x88/8])(obj);
}

// 710069bf60
void set_pickelblock_mode_ignoreandattack(BattleObjectModuleAccessor* acc) {
    acc->ground_module->_vf257(2);
}

// ── status_kind range checks ──────────────────────────────────────────────────

// ── final_module_hit_success -- vtable[1] on 0x71052c1xxx singletons ──────────

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

// 71015c2720 -- accessor[-8]→[+0x1a0]→[+0x190]→[+0x220], call with (obj, x1, 0)
void throw_attack(void* p, void* other) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    FUN_71015aba90(d, other, 0);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 71015cb6e0 -- guard on [battle_obj+0x8]>>28==4, then same chain
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

// 71015c5b30 -- store bool to [+0x62]
void set_postponed_damage_check_on_process_hit(void* p, bool flag) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1a0);
    void* c = *reinterpret_cast<void**>((u8*)b + 0x190);
    void* d = *reinterpret_cast<void**>((u8*)c + 0x220);
    *reinterpret_cast<u8*>((u8*)d + 0x62) = flag & 1;
}

// ── apply_fighter_scale ───────────────────────────────────────────────────────

// ── FighterManager readers ────────────────────────────────────────────────────

// 71015ce4d0 -- FighterManager singleton → [+0xa0]
s32 get_fighter_entry_count() {
    void* m = *reinterpret_cast<void**>(DAT_71052b84f8);
    return *reinterpret_cast<s32*>((u8*)m + 0xa0);
}

// ── Fighter restart position ──────────────────────────────────────────────────

// ── Damage attacker ID ────────────────────────────────────────────────────────

// 7101651a20 -- damage_module → vtable[0x198/8]() → [result+0xc] or 0x50000000
s32 get_damage_attacker_id(BattleObjectModuleAccessor* acc) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    auto* obj = acc->damage_module;
    void* r = reinterpret_cast<void*(*)(void*)>(VT(obj)[0x198/8])(obj);
    if (!r) return 0x50000000;
    return *reinterpret_cast<s32*>((u8*)r + 0xc);
}

// ── Summon fighter helpers ────────────────────────────────────────────────────

// 7101652f40 -- call FUN_71004eb6a0 only if fighter_kind in [2..7]
void entry_summon_fighter(s32 fighter_kind) {
    if ((u32)(fighter_kind - 2) <= 5)
        FUN_71004eb6a0(fighter_kind);
}

// ── Light/dark fighter count ──────────────────────────────────────────────────

// 7101653710 -- (ptr_end - ptr_begin) / 8 for light fighter array
int get_light_fighter_kind_num() {
    void* g = DAT_7105329868;
    if (!g) return 0;
    void* p = *reinterpret_cast<void**>(g);
    u8* end   = *reinterpret_cast<u8**>((u8*)p + 0x238);
    u8* begin = *reinterpret_cast<u8**>((u8*)p + 0x230);
    return (int)((u64)(end - begin) >> 3);
}

// 71016537d0 -- same for dark fighter array
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

// 710165c5d0 -- DOLL hit data size
float DOLL_HIT_DATA_SIZE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xc08);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1d8);
    return *reinterpret_cast<float*>((u8*)b + 0x18);
}

// 710165d2a0 -- explosion bomb burst damage
float EXPLOSIONBOMB_BURST_DAMAGE() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x3f0);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x108);
    return *reinterpret_cast<float*>((u8*)b + 0x34);
}

// 710165e7c0 -- hit speed x
float hit_spd_x() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0xf88);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x1c8);
    return *reinterpret_cast<float*>((u8*)b + 0x14);
}

// 710165e7e0 -- hit speed y
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
    u8* base = (u8*)DAT_71052bb3b0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base), "+r"(fighter_kind));
#endif
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>(base + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x28);
}

// 7101671070
float HOLYWATER_HIT_HOP_SPEED_Y(s32 fighter_kind) {
    u8* base = (u8*)DAT_71052bb3b0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base), "+r"(fighter_kind));
#endif
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>(base + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x2c);
}

// 71016710a0
float HOLYWATER_HIT_SPEED_X_MUL(s32 fighter_kind) {
    u8* base = (u8*)DAT_71052bb3b0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base), "+r"(fighter_kind));
#endif
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>(base + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x30);
}

// 71016710d0
float HOLYWATER_HIT_HOP_AFTER_FALL_ACCEL(s32 fighter_kind) {
    u8* base = (u8*)DAT_71052bb3b0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base), "+r"(fighter_kind));
#endif
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>(base + off);
    void* b = *reinterpret_cast<void**>((u8*)a + 0x240);
    return *reinterpret_cast<float*>((u8*)b + 0x34);
}

// 7101671100
float HOLYWATER_HIT_HOP_AFTER_SPEED_Y_MAX(s32 fighter_kind) {
    u8* base = (u8*)DAT_71052bb3b0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base), "+r"(fighter_kind));
#endif
    u64 off = (fighter_kind == 0x44) ? 0xf50ull : 0xf18ull;
    void* a = *reinterpret_cast<void**>(base + off);
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

// 710227ec80 -- tail-call to dead-camera hit-count getter
void dead_up_camera_hit_count() {
    FUN_7100697570();
}

// 7102282350 -- DAT_71052bb3b0 → [0x50] → s0[0x48]
float get_default_fighter_param_ground_speed_limit() {
    void* a = *reinterpret_cast<void**>((u8*)DAT_71052bb3b0 + 0x50);
    return *reinterpret_cast<float*>((u8*)a + 0x48);
}

// 7102281a90 -- request camera rumble via FighterManager
void set_dead_camera_hit_rumble(void*) {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067de90(mgr, 0x001013dbb854ull, 0, 0, 0x50000000);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 7102281bc0 -- hash selector based on status_kind & ~1 == 0x3c
u64 get_attack_s3_s_motion(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    u32 sk = *reinterpret_cast<u32*>((u8*)a + 0x198) & ~1u;
    return (sk == 0x3c) ? 0x000decb03ce6ull : 0x000b7dd72b57ull;
}

// 7102281c70 -- same pattern, different hashes (lw3 motion)
u64 get_attack_lw3_motion(void* p) {
    void* a = *reinterpret_cast<void**>((u8*)p - 8);
    u32 sk = *reinterpret_cast<u32*>((u8*)a + 0x198) & ~1u;
    return (sk == 0x3c) ? 0x000c60464aa4ull : 0x000a18b4d5e5ull;
}

// NOTE: Module-level _impl dispatchers (AttackModule, CameraModule, ControlModule,
// DamageModule, FighterCutInManager, FighterStatusModuleImpl, FighterMotionModuleImpl)
// are now in their respective src/app/modules/*.cpp files.

