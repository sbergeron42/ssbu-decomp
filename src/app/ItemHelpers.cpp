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
