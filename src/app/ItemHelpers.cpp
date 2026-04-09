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
