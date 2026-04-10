#include "types.h"

// Item -- operates on Item* directly
// Vtable tail calls: ldr x8,[x0]; ldr xN,[x8,#off]; br xN
// Direct field reads: ldr wN,[x0,#off]; ret
// add-return-pointer: add x0,x0,#off; ret

// lib::Singleton<app::ItemParamAccessor>::instance_
extern "C" void* DAT_71052c31e0 __attribute__((visibility("hidden")));

struct Item {
    void** vtable;                   // +0x0
    u32 unk_0x08;                    // +0x08
    s32 item_kind_index;             // +0x0c [derived: common_param_float_impl (.dynsym) reads s32 from +0xc as param table index]
    u8  pad_0x10[0x88];
    u8  module_accessor_base[0x40];  // +0x98 (returned as void*)
    void* status_module;             // +0xD8
    u8  pad_0xE0[0x88];
    void* link_module;               // +0x168
    u8  pad_0x170[0xD8];
    void* spec_handler;              // +0x248
    u32 owner_id;                    // +0x250
};
struct LinkEventCaptureItem;
struct LinkEventTouchItem;

extern "C" u64 FUN_71015b4e40(Item*, u32);
extern "C" f32 FUN_71015b3de0(Item*, u32);
extern "C" bool FUN_71015b4fc0(Item*);
extern "C" void FUN_71015aba90(Item*, u32, u32);
extern "C" void FUN_71015b0590(Item*);

// LargeRet forces x8 reservation (indirect return), making vtable temp use x9
struct LargeRet { u64 a, b, c; };

#define VT(p) (*reinterpret_cast<void***>(p))

namespace app::lua_bind {

// 71020f4430 -- ldr x8,[x0]; ldr x1,[x8,#0x70]; br x1
void Item__start_inhaled_impl(Item* item) {
    reinterpret_cast<void(*)(Item*)>(VT(item)[0x70/8])(item);
}

// 71020f4440 -- ldr x8,[x0]; ldr x1,[x8,#0x108]; br x1
void Item__end_hooked_impl(Item* item) {
    reinterpret_cast<void(*)(Item*)>(VT(item)[0x108/8])(item);
}

// 71020f4450 -- ldr x8,[x0]; ldr x1,[x8,#0x528]; br x1
u32 Item__get_battle_object_id_impl(Item* item) {
    return reinterpret_cast<u32(*)(Item*)>(VT(item)[0x528/8])(item);
}

// 71020f4460 -- ldr x8,[x0]; ldr x2,[x8,#0x548]; br x2 (1 extra param)
void Item__action_impl(Item* item, u64 p1) {
    reinterpret_cast<void(*)(Item*, u64)>(VT(item)[0x548/8])(item, p1);
}

// 71020f4470 -- add x0,x0,#0x98; ret
void* Item__item_module_accessor_impl(Item* item) {
    return item->module_accessor_base;
}

// 71020f4670 -- ldr w0,[x0,#0x250]; ret
u32 Item__owner_id_impl(Item* item) {
    return item->owner_id;
}

// 71020f4600 -- if param_id > 2, return error hash; else tail-call FUN_71015b4e40
u64 Item__property_param_int_as_hash_impl(Item* item, u32 param_id) {
    if (param_id > 2) return 0x7fb997a80ULL;
    return FUN_71015b4e40(item, param_id);
}

// 71020f4620 -- pure tail call
f32 Item__specialized_param_float_impl(Item* item, u32 param_id) {
    return FUN_71015b3de0(item, param_id);
}

// 71020f4700 -- pure tail call
bool Item__is_eatable_impl(Item* item) {
    return FUN_71015b4fc0(item);
}

// 71020f4710 -- zero w2 then tail call
void Item__throw_attack_impl(Item* item, u32 p1) {
    FUN_71015aba90(item, p1, 0);
}

// --- LinkEventCaptureItem ---

// 71020b60e0 -- ldr x8,[x0]; ldr x2,[x8,#0x38]; br x2
void LinkEventCaptureItem__load_from_l2c_table_impl(LinkEventCaptureItem* ev, u64 p1) {
    reinterpret_cast<void(*)(LinkEventCaptureItem*, u64)>(VT(ev)[0x38/8])(ev, p1);
}

// 71020b60f0 -- ldr x9,[x0]; ldr x1,[x9,#0x28]; br x1
// LargeRet reserves x8 for indirect return → compiler uses x9 for vtable temp
LargeRet LinkEventCaptureItem__store_l2c_table_impl(LinkEventCaptureItem* ev) {
    return reinterpret_cast<LargeRet(*)(LinkEventCaptureItem*)>(VT(ev)[0x28/8])(ev);
}

// --- LinkEventTouchItem ---

// 71020f2e80 -- ldr x8,[x0]; ldr x2,[x8,#0x38]; br x2
void LinkEventTouchItem__load_from_l2c_table_impl(LinkEventTouchItem* ev, u64 p1) {
    reinterpret_cast<void(*)(LinkEventTouchItem*, u64)>(VT(ev)[0x38/8])(ev, p1);
}

// 71020f2e90 -- ldr x9,[x0]; ldr x1,[x9,#0x28]; br x1
LargeRet LinkEventTouchItem__store_l2c_table_impl(LinkEventTouchItem* ev) {
    return reinterpret_cast<LargeRet(*)(LinkEventTouchItem*)>(VT(ev)[0x28/8])(ev);
}

// 71020f4630 -- call vtable[0x18](item[0x248], item, param_id, &out); return out if ok else 0
u32 Item__specialized_param_int_impl(Item* item, u32 param_id) {
    u32 out;
    void* obj = item->spec_handler;
    bool ok = reinterpret_cast<bool(*)(void*, Item*, u32, u32*)>(VT(obj)[0x18/8])(obj, item, param_id, &out);
    return ok ? out : 0;
}

// 71020f4680 -- check item state via vtable[0x110] on +0xd8;
//   if state==2 or (allow_had && state==8) → return 1
//   else tail-call vtable[0x70](accessor+0x168, 4) as u32
bool Item__is_had_impl(Item* item, u32 allow_had) {
    void* obj = item->status_module;
    u32 state = reinterpret_cast<u32(*)(void*)>(VT(obj)[0x110/8])(obj);
    if (state == 2) return true;
    if (allow_had & 1) {
        void* obj2 = item->status_module;
        state = reinterpret_cast<u32(*)(void*)>(VT(obj2)[0x110/8])(obj2);
        if (state == 8) return true;
    }
    void* m = item->link_module;
    return reinterpret_cast<bool(*)(void*, u32)>(VT(m)[0x70/8])(m, 4);
}

// 71020f4720 -- b FUN_71015b0590 (pure tail call)
void Item__fall_impl(Item* item) {
    FUN_71015b0590(item);
}

// 71020f45a0 -- index into ItemParamAccessor float table
f32 Item__common_param_float_impl(Item* item, u32 param_id) {
    u8* params = *(u8**)DAT_71052c31e0;
    s64 kind = item->item_kind_index;
    return *reinterpret_cast<f32*>(params + kind * 0x284 + (u64)param_id * 4 + 0x3908);
}

// 71020f45d0 -- index into ItemParamAccessor int table
u32 Item__common_param_int_impl(Item* item, u32 param_id) {
    u8* params = *(u8**)DAT_71052c31e0;
    s64 kind = item->item_kind_index;
    return *reinterpret_cast<u32*>(params + kind * 0xac + (u64)param_id * 4 + 0x477c8);
}

// --- LinkEventCaptureItem store_l2c_table (256B) ---

// 71020b6100: vtable[0x30/8] tail call (original uses x9 for vtable temp)
void LinkEventCaptureItem__store_l2c_table_impl_71020b6100(void* ev, void* table) {
    reinterpret_cast<void(*)(void*, void*)>(VT(ev)[0x30/8])(ev, table);
}

// --- LinkEventTouchItem store_l2c_table (224B) ---

// 71020f2ea0: vtable[0x30/8] tail call (original uses x9 for vtable temp)
void LinkEventTouchItem__store_l2c_table_impl_71020f2ea0(void* ev, void* table) {
    reinterpret_cast<void(*)(void*, void*)>(VT(ev)[0x30/8])(ev, table);
}

} // namespace app::lua_bind

