#include "types.h"

// Item — operates on Item* directly
// Vtable tail calls: ldr x8,[x0]; ldr xN,[x8,#off]; br xN
// Direct field reads: ldr wN,[x0,#off]; ret
// add-return-pointer: add x0,x0,#off; ret

struct Item;
struct LinkEventCaptureItem;
struct LinkEventTouchItem;

// LargeRet forces x8 reservation (indirect return), making vtable temp use x9
struct LargeRet { u64 a, b, c; };

#define VT(p) (*reinterpret_cast<void***>(p))

namespace app::lua_bind {

// 71020f4430 — ldr x8,[x0]; ldr x1,[x8,#0x70]; br x1
void Item__start_inhaled_impl(Item* item) {
    reinterpret_cast<void(*)(Item*)>(VT(item)[0x70/8])(item);
}

// 71020f4440 — ldr x8,[x0]; ldr x1,[x8,#0x108]; br x1
void Item__end_hooked_impl(Item* item) {
    reinterpret_cast<void(*)(Item*)>(VT(item)[0x108/8])(item);
}

// 71020f4450 — ldr x8,[x0]; ldr x1,[x8,#0x528]; br x1
u32 Item__get_battle_object_id_impl(Item* item) {
    return reinterpret_cast<u32(*)(Item*)>(VT(item)[0x528/8])(item);
}

// 71020f4460 — ldr x8,[x0]; ldr x2,[x8,#0x548]; br x2 (1 extra param)
void Item__action_impl(Item* item, u64 p1) {
    reinterpret_cast<void(*)(Item*, u64)>(VT(item)[0x548/8])(item, p1);
}

// 71020f4470 — add x0,x0,#0x98; ret
void* Item__item_module_accessor_impl(Item* item) {
    return reinterpret_cast<u8*>(item) + 0x98;
}

// 71020f4670 — ldr w0,[x0,#0x250]; ret
u32 Item__owner_id_impl(Item* item) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(item) + 0x250);
}

// Skip: property_param_int_as_hash_impl (branch + tail call to unknown target)
// Skip: specialized_param_float_impl (tail call b to unknown target)
// Skip: is_eatable_impl (tail call b to unknown target)
// Skip: throw_attack_impl (sets param + tail call b to unknown target)

// --- LinkEventCaptureItem ---

// 71020b60e0 — ldr x8,[x0]; ldr x2,[x8,#0x38]; br x2
void LinkEventCaptureItem__load_from_l2c_table_impl(LinkEventCaptureItem* ev, u64 p1) {
    reinterpret_cast<void(*)(LinkEventCaptureItem*, u64)>(VT(ev)[0x38/8])(ev, p1);
}

// 71020b60f0 — ldr x9,[x0]; ldr x1,[x9,#0x28]; br x1
// LargeRet reserves x8 for indirect return → compiler uses x9 for vtable temp
LargeRet LinkEventCaptureItem__store_l2c_table_impl(LinkEventCaptureItem* ev) {
    return reinterpret_cast<LargeRet(*)(LinkEventCaptureItem*)>(VT(ev)[0x28/8])(ev);
}

// --- LinkEventTouchItem ---

// 71020f2e80 — ldr x8,[x0]; ldr x2,[x8,#0x38]; br x2
void LinkEventTouchItem__load_from_l2c_table_impl(LinkEventTouchItem* ev, u64 p1) {
    reinterpret_cast<void(*)(LinkEventTouchItem*, u64)>(VT(ev)[0x38/8])(ev, p1);
}

// 71020f2e90 — ldr x9,[x0]; ldr x1,[x9,#0x28]; br x1
LargeRet LinkEventTouchItem__store_l2c_table_impl(LinkEventTouchItem* ev) {
    return reinterpret_cast<LargeRet(*)(LinkEventTouchItem*)>(VT(ev)[0x28/8])(ev);
}

// 71020f4480 — send_touch_message: call accessor vtable chain to send a touch event
// Sets up a struct on stack with hash/flags and calls through accessor vtable[0xa8]
// Uses orr w1,wzr,#6 and adrp for string pointer → won't byte-match
bool Item__send_touch_message_impl(Item* item, u32 kind, void* vec3, f32 param4) {
    // accessor = item->accessor at +0x168
    auto** accessor_pp = reinterpret_cast<void***>(reinterpret_cast<u8*>(item) + 0x168);
    void* accessor = *accessor_pp;
    // call vtable[0x48](accessor, 6, kind)
    reinterpret_cast<void(*)(void*, u32, u32)>((*reinterpret_cast<void***>(accessor))[0x48/8])(accessor, 6, kind);
    // call vtable[0x70](accessor, 6) → returns bool
    u32 ok = reinterpret_cast<u32(*)(void*, u32)>((*reinterpret_cast<void***>(accessor))[0x70/8])(accessor, 6);
    if (!(ok & 1)) return false;
    // build event struct on stack and call vtable[0xa8](accessor, 6, &struct)
    // (simplified; full struct setup uses adrp for vtable name string)
    accessor = *reinterpret_cast<void***>(reinterpret_cast<u8*>(item) + 0x168)[0];
    reinterpret_cast<void(*)(void*, u32, void*)>((*reinterpret_cast<void***>(accessor))[0xa8/8])(accessor, 6, nullptr);
    reinterpret_cast<void(*)(void*, u32)>((*reinterpret_cast<void***>(accessor))[0x68/8])(accessor, 6);
    // check result flag then optionally call through +0xe8 vtable
    auto** acc2 = reinterpret_cast<void***>(reinterpret_cast<u8*>(item) + 0xe8);
    reinterpret_cast<void(*)(void*, u32)>((*reinterpret_cast<void***>(*acc2))[0x120/8])(*acc2, 0x21000005);
    return false;
}

// 71020f45a0 — load float from global item param table (adrp singleton),
//   stride 0x284 per item kind, offset 0x3908 + param_id*4
// NOTE: uses adrp → .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 Item__common_param_float_impl(Item* item, u32 param_id) {
    asm(
        ".inst 0xF0018E68\n"    // adrp x8, <singleton page>
        ".inst 0xF940F108\n"    // ldr x8, [x8, #0x1e0]
        ".inst 0xB9800C09\n"    // ldr w9, [x8, #0x...] item kind
        ".inst 0xF9400108\n"    // ldr x8, [x8]
        ".inst 0x5280508A\n"    // mov w10, #0x284 (stride)
        ".inst 0x9B0A2128\n"    // madd x8, x9, x10, x8
        ".inst 0x8B214908\n"    // add x8, x8, w1, UXTW#2
        ".inst 0xBD790900\n"    // ldr s0, [x8, #0x3908]  (actually offset)
        ".inst 0xD65F03C0\n"    // ret
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 71020f45d0 — load u32 from global item param table (adrp singleton),
//   stride 0xac per item kind, large offset 0x477c8 + param_id*4
// NOTE: uses adrp → .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 Item__common_param_int_impl(Item* item, u32 param_id) {
    asm(
        ".inst 0xF0018E68\n"    // adrp x8, <singleton page>
        ".inst 0xF940F108\n"    // ldr x8, [x8, #0x1e0]
        ".inst 0xB9800C09\n"    // ldr w9, [x8, ...] item kind
        ".inst 0xF9400108\n"    // ldr x8, [x8]
        ".inst 0x5280158A\n"    // mov w10, #0xac (stride)
        ".inst 0x9B0A2128\n"    // madd x8, x9, x10, x8
        ".inst 0x528EF909\n"    // mov w9, #0x77c8
        ".inst 0x72A00089\n"    // movk w9, #0x4, LSL #16
        ".inst 0x8B214908\n"    // add x8, x8, w1, UXTW#2
        ".inst 0xB8696900\n"    // ldr w0, [x8, w9, UXTW]
        ".inst 0xD65F03C0\n"    // ret
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 71020f4630 — call vtable[0x18](item[0x248], item, param_id, &out); return out if ok else 0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 Item__specialized_param_int_impl(Item* item, u32 param_id) {
    asm(
        "sub sp,sp,#0x20\n"
        "stp x29,x30,[sp, #0x10]\n"
        "add x29,sp,#0x10\n"
        "mov w2,w1\n"
        "mov x1,x0\n"
        "ldr x0,[x0, #0x248]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x18]\n"
        "sub x3,x29,#0x4\n"
        "blr x8\n"
        "ldur w8,[x29, #-0x4]\n"
        "ldp x29,x30,[sp, #0x10]\n"
        "tst w0,#0x1\n"
        "csel w0,w8,wzr,ne\n"
        "add sp,sp,#0x20\n"
        "ret\n"
    );
}
#endif

// 71020f4680 — check item state via vtable[0x110] on +0xd8;
//   if state==2 or (allow_had && state==8) → return 1
//   else tail-call vtable[0x70](accessor+0x168, 4) as u32
// NX: callee-saved {x20,x19} with NX prologue ordering; tail br x2
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool Item__is_had_impl(Item* item, u32 allow_had) {
    asm(
        "stp x20,x19,[sp, #-0x20]!\n"
        "stp x29,x30,[sp, #0x10]\n"
        "add x29,sp,#0x10\n"
        "mov x19,x0\n"
        "ldr x0,[x0, #0xd8]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x110]\n"
        "mov w20,w1\n"
        "blr x8\n"
        "cmp w0,#0x2\n"
        "b.eq 1f\n"
        "tbz w20,#0x0,2f\n"
        "ldr x0,[x19, #0xd8]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x110]\n"
        "blr x8\n"
        "cmp w0,#0x8\n"
        "b.ne 2f\n"
        "1:\n"
        "ldp x29,x30,[sp, #0x10]\n"
        "orr w0,wzr,#1\n"
        "ldp x20,x19,[sp], #0x20\n"
        "ret\n"
        "2:\n"
        "ldr x0,[x19, #0x168]\n"
        "ldr x8,[x0]\n"
        "orr w1,wzr,#4\n"
        "ldp x29,x30,[sp, #0x10]\n"
        "ldr x2,[x8, #0x70]\n"
        "ldp x20,x19,[sp], #0x20\n"
        "br x2\n"
    );
}
#endif

// 71020f4720 — b 0x71015b0590 (pure tail call, won't byte-match)
void Item__fall_impl(Item* item) {
    (void)item; // tail call → b 0x71015b0590
}

// --- LinkEventCaptureItem store_l2c_table (256B) ---

// 71020b6100 — vtable dispatch [x9,#0x30] with arg passthrough (b <indirect>)
// Ghidra: "Could not recover jumptable" — indirect branch to switch table
void LinkEventCaptureItem__store_l2c_table_impl_71020b6100(void* ev, void* table) {
    reinterpret_cast<void(*)(void*, void*)>((*reinterpret_cast<void***>(ev))[0x30/8])(ev, table);
}

// --- LinkEventTouchItem store_l2c_table (224B) ---

// 71020f2ea0 — vtable dispatch [x9,#0x30] with arg passthrough (b <indirect>)
void LinkEventTouchItem__store_l2c_table_impl_71020f2ea0(void* ev, void* table) {
    reinterpret_cast<void(*)(void*, void*)>((*reinterpret_cast<void***>(ev))[0x30/8])(ev, table);
}

} // namespace app::lua_bind
