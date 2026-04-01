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

<<<<<<< HEAD
// 71020f4600 — property_param_int_as_hash_impl (8 instructions):
//   cmp w1,#2; b.hi .+8; b FUN_71015b4e40
//   mov x0,#0x7a80; movk #0xfb99,LSL16; movk #0x7,LSL32; ret
// If param_id <= 2 → tail-call lookup; else → return constant hash 0x7fb997a80
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 Item__property_param_int_as_hash_impl(Item* item, u32 param_id) {
    asm("cmp w1, #0x2\n"
        "b.hi 0f\n"
        "b FUN_71015b4e40\n"
        "0:\n"
        "mov x0, #0x7a80\n"
        "movk x0, #0xfb99, lsl #16\n"
        "movk x0, #0x7, lsl #32\n"
        "ret\n");
}
#endif

// 71020f4620 — specialized_param_float_impl: pure tail call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 Item__specialized_param_float_impl(Item* item, u32 param_id) {
    asm("b FUN_71015b3de0\n");
}
#endif

// 71020f4700 — is_eatable_impl: pure tail call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool Item__is_eatable_impl(Item* item) {
    asm("b FUN_71015b4fc0\n");
}
#endif

// 71020f4710 — throw_attack_impl: set w2=0, tail call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void Item__throw_attack_impl(Item* item, u32 p1) {
    asm("mov w2, wzr\n"
        "b FUN_71015aba90\n");
}
#endif
=======
// 71020f4600 — property_param_int_as_hash: branch on param_id > 2, tail call or constant
// Contains relative branch to external — .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 Item__property_param_int_as_hash_impl(Item* item, u32 param_id) {
    asm(
        ".inst 0x7100083F\n" ".inst 0x54000048\n" ".inst 0x17D3020E\n"
        ".inst 0xD28F5000\n" ".inst 0xF2BF7320\n" ".inst 0xF2C000E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
    );
}
#endif

// 71020f4620 — specialized_param_float: pure tail call
extern "C" f32 FUN_71015b3de0(Item*, u32);
f32 Item__specialized_param_float_impl(Item* item, u32 param_id) {
    return FUN_71015b3de0(item, param_id);
}

// 71020f4700 — is_eatable: pure tail call
extern "C" bool FUN_71015b4fc0(Item*);
bool Item__is_eatable_impl(Item* item) {
    return FUN_71015b4fc0(item);
}

// 71020f4710 — throw_attack: set third param to 0, tail call
extern "C" void FUN_71015aba90(Item*, u64, u32);
void Item__throw_attack_impl(Item* item, u64 param) {
    FUN_71015aba90(item, param, 0);
}
>>>>>>> worker/pool-b

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

<<<<<<< HEAD
// 71020f4480 — send_touch_message: NX prologue + adrp to DAT_71050b3dc8 → naked asm
// adrp x8,0x71050b3000 encodes as 0xF0017DE8 (imm=12223 pages, positive offset)
=======
// 71020f4480 — send_touch_message: accessor vtable chain with adrp + stack struct
// Contains adrp, relative branches — .inst for exact bytes (288B, 72 insns)
>>>>>>> worker/pool-b
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool Item__send_touch_message_impl(Item* item, u32 kind, void* vec3, f32 param4) {
    asm(
<<<<<<< HEAD
        "sub sp, sp, #0x90\n"
        "str d8, [sp, #0x60]\n"
        "stp x20, x19, [sp, #0x70]\n"
        "stp x29, x30, [sp, #0x80]\n"
        "add x29, sp, #0x80\n"
        "mov x19, x0\n"
        "ldr x0, [x0, #0x168]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x48]\n"
        "mov x20, x2\n"
        "mov w2, w1\n"
        "orr w1, wzr, #0x6\n"
        "mov v8.16b, v0.16b\n"
        "blr x8\n"
        "ldr x0, [x19, #0x168]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x70]\n"
        "orr w1, wzr, #0x6\n"
        "blr x8\n"
        "tbz w0, #0x0, 1f\n"
        "mov w8, #0xa\n"
        "str w8, [sp, #0x8]\n"
        "mov x8, #0xe542\n"
        "movk x8, #0xa1a7, lsl #16\n"
        "movk x8, #0xa, lsl #32\n"
        "strb wzr, [sp, #0x28]\n"
        "stp x8, xzr, [sp, #0x10]\n"
        "mov x8, #-0x10000\n"
        "movk x8, #0x5000, lsl #16\n"
        "str x8, [sp, #0x20]\n"
        ".inst 0xF0017DE8\n"        // adrp x8, 0x71050b3000
        "add x8, x8, #0xdc8\n"
        "str x8, [sp]\n"
        "str x19, [sp, #0x30]\n"
        "ldr x8, [x20, #0x8]\n"
        "str x8, [sp, #0x48]\n"
        "ldr x8, [x20]\n"
        "str x8, [sp, #0x40]\n"
        "str s8, [sp, #0x50]\n"
        "ldr x0, [x19, #0x168]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0xa8]\n"
        "orr w1, wzr, #0x6\n"
        "mov x2, sp\n"
        "blr x8\n"
        "ldr x0, [x19, #0x168]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x68]\n"
        "orr w1, wzr, #0x6\n"
        "blr x8\n"
        "ldrb w8, [sp, #0x28]\n"
        "cbz w8, 2f\n"
        "orr w0, wzr, #0x1\n"
        "b 3f\n"
        "1:\n"
        "mov w0, wzr\n"
        "b 3f\n"
        "2:\n"
        "ldr x0, [x19, #0xe8]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x120]\n"
        "mov w1, #0x5\n"
        "movk w1, #0x2100, lsl #16\n"
        "blr x8\n"
        "ldrb w8, [sp, #0x28]\n"
        "cmp w8, #0x0\n"
        "cset w0, ne\n"
        "3:\n"
        "ldr d8, [sp, #0x60]\n"
        "ldp x29, x30, [sp, #0x80]\n"
        "ldp x20, x19, [sp, #0x70]\n"
        "add sp, sp, #0x90\n"
        "ret\n"
=======
        ".inst 0xD10243FF\n" ".inst 0xFD0033E8\n" ".inst 0xA9074FF4\n"
        ".inst 0xA9087BFD\n" ".inst 0x910203FD\n" ".inst 0xAA0003F3\n"
        ".inst 0xF940B400\n" ".inst 0xF9400008\n" ".inst 0xF9402508\n"
        ".inst 0xAA0203F4\n" ".inst 0x2A0103E2\n" ".inst 0x321F07E1\n"
        ".inst 0x4EA01C08\n" ".inst 0xD63F0100\n" ".inst 0xF940B660\n"
        ".inst 0xF9400008\n" ".inst 0xF9403908\n" ".inst 0x321F07E1\n"
        ".inst 0xD63F0100\n" ".inst 0x36000460\n" ".inst 0x52800148\n"
        ".inst 0xB9000BE8\n" ".inst 0xD29CA848\n" ".inst 0xF2B434E8\n"
        ".inst 0xF2C00148\n" ".inst 0x3900A3FF\n" ".inst 0xA9017FE8\n"
        ".inst 0x929FFFE8\n" ".inst 0xF2AA0008\n" ".inst 0xF90013E8\n"
        ".inst 0xF0017DE8\n" ".inst 0x91372108\n" ".inst 0xF90003E8\n"
        ".inst 0xF9001BF3\n" ".inst 0xF9400688\n" ".inst 0xF90027E8\n"
        ".inst 0xF9400288\n" ".inst 0xF90023E8\n" ".inst 0xBD0053E8\n"
        ".inst 0xF940B660\n" ".inst 0xF9400008\n" ".inst 0xF9405508\n"
        ".inst 0x321F07E1\n" ".inst 0x910003E2\n" ".inst 0xD63F0100\n"
        ".inst 0xF940B660\n" ".inst 0xF9400008\n" ".inst 0xF9403508\n"
        ".inst 0x321F07E1\n" ".inst 0xD63F0100\n" ".inst 0x3940A3E8\n"
        ".inst 0x340000A8\n" ".inst 0x320003E0\n" ".inst 0x1400000C\n"
        ".inst 0x2A1F03E0\n" ".inst 0x1400000A\n" ".inst 0xF9407660\n"
        ".inst 0xF9400008\n" ".inst 0xF9409108\n" ".inst 0x528000A1\n"
        ".inst 0x72A42001\n" ".inst 0xD63F0100\n" ".inst 0x3940A3E8\n"
        ".inst 0x7100011F\n" ".inst 0x1A9F07E0\n" ".inst 0xFD4033E8\n"
        ".inst 0xA9487BFD\n" ".inst 0xA9474FF4\n" ".inst 0x910243FF\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
>>>>>>> worker/pool-b
    );
}
#endif

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

<<<<<<< HEAD
// 71020f4720 — b 0x71015b0590 (pure unconditional tail call)
// offset = (0x71015b0590 - 0x71020f4720) / 4 = -0x2D1064 → imm26 = 0x3D2EF9C → 0x17D2EF9C
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void Item__fall_impl(Item* item) {
    asm(".inst 0x17D2EF9C\n"); // b 0x71015b0590
=======
// 71020f4720 — starts with b to external, followed by unreachable linked-list code (176B)
// Contains relative branch + adrp — .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void Item__fall_impl(Item* item) {
    asm(
        ".inst 0x17D2EF9C\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
        ".inst 0x00000000\n" ".inst 0xF9401008\n" ".inst 0xF9400108\n"
        ".inst 0xF9400809\n" ".inst 0x9100410A\n" ".inst 0xB0013B68\n"
        ".inst 0x91258108\n" ".inst 0xEB09015F\n" ".inst 0x9A883148\n"
        ".inst 0xB940090D\n" ".inst 0xCB0A012B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400108\n"
        ".inst 0x9100A108\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400108\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB09015F\n" ".inst 0x540001A9\n" ".inst 0x9100412B\n"
        ".inst 0xF900080B\n" ".inst 0xB900093F\n" ".inst 0xF9400809\n"
        ".inst 0xEB0A013F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E8\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A712A\n"
    );
>>>>>>> worker/pool-b
}
#endif

// --- LinkEventCaptureItem store_l2c_table (256B) ---

// 71020b6100: ldr x9,[x0]; ldr x2,[x9,#0x30]; br x2  (indirect tail call via x9)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void LinkEventCaptureItem__store_l2c_table_impl_71020b6100(void* ev, void* table) {
    asm("ldr x9, [x0]\nldr x2, [x9, #0x30]\nbr x2\n");
}
#endif

// --- LinkEventTouchItem store_l2c_table (224B) ---

// 71020f2ea0: ldr x9,[x0]; ldr x2,[x9,#0x30]; br x2  (indirect tail call via x9)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void LinkEventTouchItem__store_l2c_table_impl_71020f2ea0(void* ev, void* table) {
    asm("ldr x9, [x0]\nldr x2, [x9, #0x30]\nbr x2\n");
}
#endif

} // namespace app::lua_bind
