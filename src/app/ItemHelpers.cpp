#include "types.h"

// Item helper functions — small wrappers, tail-calls, and field accessors
// Most load a singleton (ItemParamAccessor, ItemManager, etc.) then tail-call

// ============================================================
// Singleton pointers (hidden visibility = direct adrp+ldr)
// ============================================================

// lib::Singleton<app::ItemParamAccessor>::instance_ (page 0x71052c3000 + 0x1e0)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c31e0;

// ItemManager singleton (page 0x71052c3000 + 0x70)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c3070;

// StageManager singleton (page 0x71052b8000 + 0x4f8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b84f8;

// ============================================================
// Target functions (tail-call destinations)
// ============================================================

extern "C" void FUN_7101604220(void*);
extern "C" void FUN_7101602a30(void*, u32, u64);
extern "C" void FUN_7101602b90(void*, u32, u64);
extern "C" void FUN_7101602da0(void*, u32, u64);
extern "C" void FUN_7101602f50(void*, u32, u64, u64);
extern "C" void FUN_71016031d0(void*, u32, u64, u64);
extern "C" void FUN_7101603500(void*, u32, u64, u64);
extern "C" void FUN_71016037e0(void*, u32, u64, u64, u64);
extern "C" void FUN_7101603af0(void*, u32, u64, u64, u64);
extern "C" void FUN_7101603eb0(void*, u32, u64, u64, u64);
extern "C" void FUN_71015dab40(void*, u32, u32);
extern "C" void FUN_710067a3a0(void*, u32);
extern "C" void FUN_710067a5c0(void*);

// ============================================================
// ItemParamAccessor wrappers (singleton at DAT_71052c31e0)
// Pattern: load singleton, shuffle args, tail-call
// ============================================================

// 71015c4d30 — self_param_array_size (12B)
void self_param_array_size_71015c4d30() {
    FUN_7101604220(DAT_71052c31e0);
}

// 71015c4c10 — self_param_float (20B)
void self_param_float_71015c4c10(u32 kind, u64 hash) {
    FUN_7101602a30(DAT_71052c31e0, kind, hash);
}

// 71015c4c30 — self_param_int (20B)
void self_param_int_71015c4c30(u32 kind, u64 hash) {
    FUN_7101602b90(DAT_71052c31e0, kind, hash);
}

// 71015c4c50 — self_param_hash (20B)
void self_param_hash_71015c4c50(u32 kind, u64 hash) {
    FUN_7101602da0(DAT_71052c31e0, kind, hash);
}

// 71015c4c70 — self_struct_param_float (24B)
void self_struct_param_float_71015c4c70(u32 kind, u64 hash, u64 field) {
    FUN_7101602f50(DAT_71052c31e0, kind, hash, field);
}

// 71015c4c90 — self_struct_param_int (24B)
void self_struct_param_int_71015c4c90(u32 kind, u64 hash, u64 field) {
    FUN_71016031d0(DAT_71052c31e0, kind, hash, field);
}

// 71015c4cb0 — self_struct_param_hash (24B)
void self_struct_param_hash_71015c4cb0(u32 kind, u64 hash, u64 field) {
    FUN_7101603500(DAT_71052c31e0, kind, hash, field);
}

// 71015c4cd0 — self_struct_array_param_float (28B)
void self_struct_array_param_float_71015c4cd0(u32 kind, u64 hash, u64 field, u64 index) {
    FUN_71016037e0(DAT_71052c31e0, kind, hash, field, index);
}

// 71015c4cf0 — self_struct_array_param_int (28B)
void self_struct_array_param_int_71015c4cf0(u32 kind, u64 hash, u64 field, u64 index) {
    FUN_7101603af0(DAT_71052c31e0, kind, hash, field, index);
}

// 71015c4d10 — self_struct_array_param_hash (28B)
void self_struct_array_param_hash_71015c4d10(u32 kind, u64 hash, u64 field, u64 index) {
    FUN_7101603eb0(DAT_71052c31e0, kind, hash, field, index);
}

// ============================================================
// ItemManager wrappers (singleton at DAT_71052c3070)
// ============================================================

// 71015ca8f0 — get_num_of_ownered_active_item (20B)
void get_num_of_ownered_active_item_71015ca8f0(u32 owner_id, u32 item_kind) {
    FUN_71015dab40(DAT_71052c3070, owner_id, item_kind);
}

// 71015ca910 — get_num_of_active_item: array lookup (20B, leaf)
void* get_num_of_active_item_71015ca910(s32 index) {
    void** table = *reinterpret_cast<void***>(reinterpret_cast<u8*>(DAT_71052c3070) + 0x70);
    return table[index];
}

// ============================================================
// StageManager wrappers (singleton at DAT_71052b84f8)
// ============================================================

// 71015cd4d0 — is_final_status_or_standby (20B)
void is_final_status_or_standby_71015cd4d0() {
    void* obj = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067a3a0(obj, 1);
}

// 71015cd530 — is_absolutely_final_status (16B)
void is_absolutely_final_status_71015cd530() {
    void* obj = *reinterpret_cast<void**>(DAT_71052b84f8);
    FUN_710067a5c0(obj);
}

// ============================================================
// Item lua_bind trampolines (36B each, Pattern A)
// Chain: *(item-8) → +0x1a0 → +0x190 → field_0x220 → bl target
// ============================================================

extern "C" void FUN_71015b5a40(void*);
extern "C" void FUN_71015b57c0(void*);
extern "C" void FUN_71015b58e0(void*);
extern "C" void FUN_71015b5ec0(void*);
extern "C" void FUN_71015aacb0(void*);
extern "C" void FUN_71015b3de0(void*);
extern "C" void FUN_71015b3a40(void*);

static inline void* item_trampoline_field(void* item) {
    u8* p1 = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(item) - 8);
    u8* p2 = *reinterpret_cast<u8**>(p1 + 0x1a0);
    u8* p3 = *reinterpret_cast<u8**>(p2 + 0x190);
    return *reinterpret_cast<void**>(p3 + 0x220);
}

// 71015c0890 — create_item (36B)
void create_item_71015c0890(void* item) {
    FUN_71015b5a40(item_trampoline_field(item));
    asm volatile("");
}

// 71015c1170 — begin_scale_animation_simple (36B)
void begin_scale_animation_simple_71015c1170(void* item) {
    FUN_71015b57c0(item_trampoline_field(item));
    asm volatile("");
}

// 71015c11e0 — begin_scale_animation_with_param (36B)
void begin_scale_animation_with_param_71015c11e0(void* item) {
    FUN_71015b58e0(item_trampoline_field(item));
    asm volatile("");
}

// 71015c1690 — set_slow_whole (36B)
void set_slow_whole_71015c1690(void* item) {
    FUN_71015b5ec0(item_trampoline_field(item));
    asm volatile("");
}

// 71015c2080 — link_as_team_owner (36B)
void link_as_team_owner_71015c2080(void* item) {
    FUN_71015aacb0(item_trampoline_field(item));
    asm volatile("");
}

// 71015c4e80 — specialized_param_float (36B)
void specialized_param_float_71015c4e80(void* item) {
    FUN_71015b3de0(item_trampoline_field(item));
    asm volatile("");
}

// 71015c5880 — setup_ground_collision (36B)
void setup_ground_collision_71015c5880(void* item) {
    FUN_71015b3a40(item_trampoline_field(item));
    asm volatile("");
}

// ============================================================
// Item accessor trampolines — module vtable dispatch (44-48B)
// Pattern: *(item-8)+0x1a0 → module at +off → vtable[slot](mod, arg)
// ============================================================

// Helper: get accessor from item base
static inline u8* item_accessor(void* item) {
    return *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(item) - 8) + 0x1a0);
}

#define VT(p) (*reinterpret_cast<void***>(p))

// 71015c6ce0 — pos_z: module(+0x50) vtable[0x58/8](mod, 0xd) (44B)
void pos_z_71015c6ce0(void* item) {
    void* mod = *reinterpret_cast<void**>(item_accessor(item) + 0x50);
    reinterpret_cast<void(*)(void*, int)>(VT(mod)[0x58/8])(mod, 0xd);
    asm volatile("");
}

// 71015c8d50 — set_stage_sh: module(+0x78) vtable[0x330/8](mod, 1) (44B)
void set_stage_sh_71015c8d50(void* item) {
    void* mod = *reinterpret_cast<void**>(item_accessor(item) + 0x78);
    reinterpret_cast<void(*)(void*, int)>(VT(mod)[0x330/8])(mod, 1);
    asm volatile("");
}

// 71015c1210 — set_countdown: module(+0x50) vtable[0xa0/8](mod, w1, 0x10000012) (48B)
void set_countdown_71015c1210(void* item, u32 p1) {
    void* mod = *reinterpret_cast<void**>(item_accessor(item) + 0x50);
    reinterpret_cast<void(*)(void*, u32, u32)>(VT(mod)[0xa0/8])(mod, p1, 0x10000012u);
    asm volatile("");
}

// 71015c1240 — set_countdown2: module(+0x50) vtable[0xa0/8](mod, w1, 0x10000013) (48B)
void set_countdown2_71015c1240(void* item, u32 p1) {
    void* mod = *reinterpret_cast<void**>(item_accessor(item) + 0x50);
    reinterpret_cast<void(*)(void*, u32, u32)>(VT(mod)[0xa0/8])(mod, p1, 0x10000013u);
    asm volatile("");
}

// 71015c1270 — set_countdown3: module(+0x50) vtable[0xa0/8](mod, w1, 0x10000014) (48B)
void set_countdown3_71015c1270(void* item, u32 p1) {
    void* mod = *reinterpret_cast<void**>(item_accessor(item) + 0x50);
    reinterpret_cast<void(*)(void*, u32, u32)>(VT(mod)[0xa0/8])(mod, p1, 0x10000014u);
    asm volatile("");
}

// ============================================================
// Item field accessors — leaf functions (no calls)
// ============================================================

// 71015c1f90 — set_appear_child_speed: write struct fields (44B, leaf)
// item[-8]→+0x1a0→+0x190→+0x220 → write +0x280, +0x288, +0x29e
void set_appear_child_speed_71015c1f90(void* item, u64* vec, u32 flag) {
    u8* p = reinterpret_cast<u8*>(item_trampoline_field(item));
    *reinterpret_cast<u64*>(p + 0x280) = vec[0];
    *reinterpret_cast<u64*>(p + 0x288) = vec[1];
    p[0x29e] = flag & 1;
}

// 71015bfb40 — is_same_create_frame: compare field vs global (44B, leaf)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c3070;
u32 is_same_create_frame_71015bfb40(void* item) {
    u8* p3 = *reinterpret_cast<u8**>(item_accessor(item) + 0x190);
    u8* obj = *reinterpret_cast<u8**>(p3 + 0x220);
    u32 val = *reinterpret_cast<u32*>(obj + 0x290);
    u8* mgr = reinterpret_cast<u8*>(DAT_71052c3070);
    u32 global_val = *reinterpret_cast<u32*>(mgr + 0xd0);
    return val == global_val ? 1 : 0;
}

// ============================================================
// Deep chain trampolines — +0xe8 sub-object vtable calls (52B)
// ============================================================

// 71015c1fe0 — set_hp: item→0x1a0→0x190→0x220→+0xe8, vtable[0x60/8](sub, 9) (52B)
void set_hp_71015c1fe0(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    void* sub = *reinterpret_cast<void**>(obj + 0xe8);
    reinterpret_cast<void(*)(void*, int)>(VT(sub)[0x60/8])(sub, 9);
    asm volatile("");
}

// 71015c2020 — get_hp: item→0x1a0→0x190→0x220→+0xe8, vtable[0x58/8](sub, 9) (52B)
void get_hp_71015c2020(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    void* sub = *reinterpret_cast<void**>(obj + 0xe8);
    reinterpret_cast<void(*)(void*, int)>(VT(sub)[0x58/8])(sub, 9);
    asm volatile("");
}

// ============================================================
// Guarded trampolines — float check before call (44B)
// ============================================================

extern "C" void FUN_71015b8290(void*);
extern "C" void FUN_71015b8600(void*);

// ============================================================
// Accessor chain → +0x90 sub-object → call (40B)
// ============================================================

extern "C" void FUN_71015b8970(void*);
extern "C" void FUN_71015b8a50(void*);

// 71015c95a0 — get_action_probability_mul (40B)
void get_action_probability_mul_71015c95a0(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    FUN_71015b8970(*reinterpret_cast<void**>(obj + 0x90));
    asm volatile("");
}

// 71015c95d0 — get_action_probability_mul_2nd (40B)
void get_action_probability_mul_2nd_71015c95d0(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    FUN_71015b8a50(*reinterpret_cast<void**>(obj + 0x90));
    asm volatile("");
}

// ============================================================
// Accessor chain → +0x220, bool mask, call (40B)
// ============================================================

extern "C" void FUN_71015ac050(void*, u32, u32);

// 71015c4aa0 — remove_model_constraint (40B)
void remove_model_constraint_71015c4aa0(void* item, u32 p1, u32 flag) {
    FUN_71015ac050(item_trampoline_field(item), p1, flag & 1);
    asm volatile("");
}

// ============================================================
// Deep chain → +0xe8 vtable[0x98/8] with hash (56B)
// ============================================================

// 71015c26e0 — have_count: item→+0x1a0→+0x190→+0x220→+0xe8, vt[0x98/8](sub, 0x10002d) (56B)
void have_count_71015c26e0(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    void* sub = *reinterpret_cast<void**>(obj + 0xe8);
    reinterpret_cast<void(*)(void*, u32)>(VT(sub)[0x98/8])(sub, 0x10002du);
    asm volatile("");
}

// ============================================================
// Conditional flag clear + global counter decrement (60B, leaf)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7f00;

// 71015c49b0 — set_disabled_camera_user_operation (60B, leaf)
void set_disabled_camera_user_operation_71015c49b0(void* item) {
    u8* obj = reinterpret_cast<u8*>(item_trampoline_field(item));
    u8* sub = *reinterpret_cast<u8**>(obj + 0x90);
    if (sub[0x168] == 0) return;
    sub[0x168] = 0;
    u8* global = *reinterpret_cast<u8**>(DAT_71052b7f00);
    u32 count = *reinterpret_cast<u32*>(global + 0xc9c);
    *reinterpret_cast<u32*>(global + 0xc9c) = count - 1;
}

// ============================================================
// Bounds-guarded getter (52B)
// ============================================================

extern "C" u64 FUN_71015b4e40(void*, u32);

// 71015c4e40 — property_param_int: if w1 >= 3 return 0, else call (52B)
u64 property_param_int_71015c4e40(void* item, u32 param_id) {
    if (param_id < 3) return 0;
    return FUN_71015b4e40(item_trampoline_field(item), param_id);
}

// ============================================================
// Indexed array lookups (common_param style, leaf)
// ============================================================

// 71015c4d40 — common_param_float: global table[idx*0x284 + w1*4 + 0x3908] (52B, leaf)
f32 common_param_float_71015c4d40(void* item, u32 param_id) {
    u8* acc = item_accessor(item);
    u8* p3 = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    s64 idx = *reinterpret_cast<s32*>(p3 + 0xc);
    u8* base = *reinterpret_cast<u8**>(DAT_71052c31e0);
    u8* entry = base + idx * 0x284 + (u64)param_id * 4;
    return *reinterpret_cast<f32*>(entry + 0x3908);
}

// 71015c4d80 — common_param_int: global table[idx*0xac + w1*4 + 0x477c8] (60B, leaf)
u32 common_param_int_71015c4d80(void* item, u32 param_id) {
    u8* acc = item_accessor(item);
    u8* p3 = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    s64 idx = *reinterpret_cast<s32*>(p3 + 0xc);
    u8* base = *reinterpret_cast<u8**>(DAT_71052c31e0);
    u8* entry = base + idx * 0xac + (u64)param_id * 4;
    return *reinterpret_cast<u32*>(entry + 0x477c8);
}

// 71015c9540 — set_action_probability_mul: if (s0 >= 0) call (44B)
void set_action_probability_mul_71015c9540(void* item, f32 val) {
    if (val < 0.0f) return;
    FUN_71015b8290(item_trampoline_field(item));
    asm volatile("");
}

// 71015c9570 — set_action_probability_mul_2nd: if (s0 >= 0) call (44B)
void set_action_probability_mul_2nd_71015c9570(void* item, f32 val) {
    if (val < 0.0f) return;
    FUN_71015b8600(item_trampoline_field(item));
    asm volatile("");
}

// ============================================================
// have_no_set_team — accessor chain + FUN_71015aa610 (52B)
// ============================================================

extern "C" void FUN_71015aa610(void*, u32, u64, u32, u32, u32, u32);

// 71015c26a0 — have_no_set_team: forward to FUN_71015aa610 with flags
void have_no_set_team_71015c26a0(void* item, u32 p1, u64 p2) {
    u8* acc = item_accessor(item);
    void* obj = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    FUN_71015aa610(obj, p1, p2, 0, 0, 1, 0);
    asm volatile("");
}

// ============================================================
// common_param_int (boss variant) — guarded singleton read (60B)
// ============================================================

// 71015c7a20 — common_param_int: check guard, then read from param table
u32 common_param_int_71015c7a20(s32 item_kind, u32 param_id) {
    u8* base = *reinterpret_cast<u8**>(DAT_71052c31e0);
    if (*reinterpret_cast<u64*>(base + (s64)item_kind * 8 + 0xef8) == 0) return 0;
    return *reinterpret_cast<u32*>(base + (s64)item_kind * 0x20 + (u64)param_id * 4 + 0x7da48);
}

// ============================================================
// common_param_hash — indexed hash lookup from global param table
// ============================================================

// 71015c4dc0 — common_param_hash: stride 0xf0, offset 0x59a08, u64 (60B, leaf)
u64 common_param_hash_71015c4dc0(void* item, u32 param_id) {
    u8* acc = item_accessor(item);
    u8* p3 = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    s64 idx = *reinterpret_cast<s32*>(p3 + 0xc);
    u8* base = *reinterpret_cast<u8**>(DAT_71052c31e0);
    u8* entry = base + idx * 0xf0 + (u64)param_id * 8;
    return *reinterpret_cast<u64*>(entry + 0x59a08);
}

// ============================================================
// Energy-from-param forwarders — call FUN_71015c7aa0 with constants
// FUN_71015c7aa0(ls, kind, hash, speed[s0], inherit, copy_all,
//                energy_idx, enable, enable2, no_boss[stack])
// ============================================================

extern "C" void FUN_71015c7aa0(void*, u32, u64, f32, u32, u32, u32, u32, u32, u8);

// 71015c7a60 — main_energy_from_param: idx=0xC, inherit=0, no_boss=0 (52B)
void main_energy_from_param_71015c7a60(void* ls, u32 kind, u64 hash, f32 speed) {
    FUN_71015c7aa0(ls, kind, hash, speed, 0, 0, 0xc, 1, 1, 0);
}

// 71015c8040 — sub1_energy_from_param: idx=0xD, inherit=0, no_boss=0 (52B)
void sub1_energy_from_param_71015c8040(void* ls, u32 kind, u64 hash, f32 speed) {
    FUN_71015c7aa0(ls, kind, hash, speed, 0, 0, 0xd, 1, 1, 0);
}

// 71015c8080 — main_energy_from_param_inherit: idx=0xC, s0=0, inherit=1 (56B)
void main_energy_from_param_inherit_71015c8080(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 0, 0xc, 1, 1, 0);
}

// 71015c80c0 — sub1_energy_from_param_inherit: idx=0xD, s0=0, inherit=1 (56B)
void sub1_energy_from_param_inherit_71015c80c0(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 0, 0xd, 1, 1, 0);
}

// 71015c8100 — sub1_energy_from_param_inherit_all: idx=0xD, s0=0, inherit=1, copy_all=1 (56B)
void sub1_energy_from_param_inherit_all_71015c8100(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 1, 0xd, 1, 1, 0);
}

// 71015c8140 — main_energy_from_param_no_boss: idx=0xC, enable=0, no_boss=1 (56B)
void main_energy_from_param_no_boss_71015c8140(void* ls, u32 kind, u64 hash, f32 speed) {
    FUN_71015c7aa0(ls, kind, hash, speed, 0, 0, 0xc, 0, 0, 1);
}

// 71015c8180 — sub1_energy_from_param_no_boss: idx=0xD, enable=0, no_boss=1 (56B)
void sub1_energy_from_param_no_boss_71015c8180(void* ls, u32 kind, u64 hash, f32 speed) {
    FUN_71015c7aa0(ls, kind, hash, speed, 0, 0, 0xd, 0, 0, 1);
}

// ============================================================
// Small leaf functions — singletons, byte checks, accessor chains
// ============================================================

// BattleObjectWorld singleton (page 0x71052b7000 + 0x558)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b7558;

// ItemCollisionManager singleton — (*DAT_71052c2958)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c2958;

extern "C" void FUN_71015b8f40(void*, void*);
extern "C" void FUN_71015b3c70(void*);

// 71015ce6d0 — is_normal_gravity: check 2 byte fields on BattleObjectWorld (40B, leaf)
u32 is_normal_gravity_71015ce6d0() {
    u8* world = reinterpret_cast<u8*>(DAT_71052b7558);
    if (world[0x5c] != 0) return 1;
    return world[0x59] != 0 ? 1 : 0;
}

// 71015cafe0 — remove_ground_collision: singleton + accessor chain (48B)
void remove_ground_collision_71015cafe0(void* item) {
    u8* acc = item_accessor(item);
    void* p3 = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    void* mgr = *reinterpret_cast<void**>(DAT_71052c2958);
    FUN_71015b8f40(mgr, p3);
    asm volatile("");
}

// 71015bfa60 — regist_life_status_ignore_lost: accessor chain → +0x90 → +0x110, call (44B)
void regist_life_status_ignore_lost_71015bfa60(void* item) {
    u8* acc = item_accessor(item);
    u8* p3 = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(acc + 0x190) + 0x220);
    u8* sub = *reinterpret_cast<u8**>(p3 + 0x90);
    FUN_71015b3c70(sub + 0x110);
    asm volatile("");
}

// 71015c81c0 — main_energy_from_param_inherit_no_boss: s0=0, inherit=1, no_boss=1 (60B)
void main_energy_from_param_inherit_no_boss_71015c81c0(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 0, 0xc, 0, 0, 1);
}

// 71015c8200 — sub1_energy_from_param_inherit_no_boss: s0=0, inherit=1, no_boss=1 (60B)
void sub1_energy_from_param_inherit_no_boss_71015c8200(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 0, 0xd, 0, 0, 1);
}

// 71015c8240 — sub1_energy_from_param_inherit_all_no_boss: all flags (60B)
void sub1_energy_from_param_inherit_all_no_boss_71015c8240(void* ls, u32 kind, u64 hash) {
    FUN_71015c7aa0(ls, kind, hash, 0.0f, 1, 1, 0xd, 0, 0, 1);
}
