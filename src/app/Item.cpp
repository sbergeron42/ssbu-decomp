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

// 71020f45a0 — common_param_float: loads from global singleton at 0x71052c3000 — won't match
f32 Item__common_param_float_impl(Item* item, u32 idx) {
    (void)item; (void)idx;
    return 0.0f;
}

// 71020f45d0 — common_param_int: loads from global singleton at 0x71052c3000 — won't match
u32 Item__common_param_int_impl(Item* item, u32 idx) {
    (void)item; (void)idx;
    return 0;
}

// 71020f4600 — if kind>2 return hash constant 0x7fb997a80, else tail call 0x71015b4e40
u64 Item__property_param_int_as_hash_impl(Item* item, u32 kind) {
    if (kind > 2) return 0x7fb997a80ull;
    (void)item;
    return 0;  // tail call to absolute address, won't match
}

// 71020f4620 — single instruction: b 0x71015b3de0 (tail call, won't match)
f32 Item__specialized_param_float_impl(Item* item, u32 idx) {
    (void)item; (void)idx;
    return 0.0f;
}

// 71020f4630 — prologue uses sub+stp (non-pre-indexed), fp setup at [2] — naked asm required
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
s32 Item__specialized_param_int_impl(Item* item, u32 idx) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w2, w1\n"
        "mov x1, x0\n"
        "ldr x0, [x0, #0x248]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x18]\n"
        "sub x3, x29, #0x4\n"
        "blr x8\n"
        "ldur w8, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "tst w0, #0x1\n"
        "csel w0, w8, wzr, ne\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 71020f4680 — register alloc: x19=item, x20=flags; reloads mod1 each call; TCO at end
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool Item__is_had_impl(Item* item, u32 flags) {
    asm(
        "stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov x19, x0\n"
        "ldr x0, [x0, #0xd8]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x110]\n"
        "mov w20, w1\n"
        "blr x8\n"
        "cmp w0, #0x2\n"
        "b.eq 1f\n"
        "tbz w20, #0x0, 2f\n"
        "ldr x0, [x19, #0xd8]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x110]\n"
        "blr x8\n"
        "cmp w0, #0x8\n"
        "b.ne 2f\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "orr w0, wzr, #0x1\n"
        "ldp x20, x19, [sp], #0x20\n"
        "ret\n"
        "2:\n"
        "ldr x0, [x19, #0x168]\n"
        "ldr x8, [x0]\n"
        "orr w1, wzr, #0x4\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x2, [x8, #0x70]\n"
        "ldp x20, x19, [sp], #0x20\n"
        "br x2\n"
    );
}
#endif

// 71020f4700 — single instruction: b 0x71015b4fc0 (tail call, won't match)
bool Item__is_eatable_impl(Item* item) {
    (void)item;
    return false;
}

// 71020f4710 — mov w2,wzr; b 0x71015aba90 (2-instruction tail call, won't match)
void Item__throw_attack_impl(Item* item, u64 p1) {
    (void)item; (void)p1;
}

// 71020f4720 — single instruction: b 0x71015b0590 (tail call, won't match)
void Item__fall_impl(Item* item) {
    (void)item;
}

// 71020f4480 — complex 72-instruction function with adrp global at 0x71050b3000 — won't match
bool Item__send_touch_message_impl(Item* item, u32 p1, void* p2, f32 p3) {
    (void)item; (void)p1; (void)p2; (void)p3;
    return false;
}

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

} // namespace app::lua_bind
