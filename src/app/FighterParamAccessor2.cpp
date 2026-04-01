#include "types.h"

// FighterParamAccessor2 — character-specific offset lookups
// Most functions are single-instruction `b` tail calls to the underlying implementation.
// Only hit_target_no has inline logic.

struct FighterParamAccessor2;

extern "C" void FUN_7100720f90(void*, s32, s32, s32);
extern "C" void FUN_71007210e0(void*, s32, s32);
extern "C" void FUN_71007211a0(void*, s32, s32);
extern "C" void FUN_7100721240(void*, s32);
extern "C" void FUN_71007212e0(void*, s32);
extern "C" void FUN_7100721380(void*, s32, s32);
extern "C" void FUN_7100721430(void*, s32);
extern "C" void FUN_71007214d0(void*, s32);

namespace app::lua_bind {

// 71020a8000 — b external
void FighterParamAccessor2__thrown_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2, s32 p3) {
    FUN_7100720f90(pa, p1, p2, p3);
}

// 71020a8010 — b external
void FighterParamAccessor2__donkey_thrown_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_71007210e0(pa, p1, p2);
}

// 71020a8020 — b external
void FighterParamAccessor2__ridley_dragged_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_71007211a0(pa, p1, p2);
}

// 71020a8030 — b external
void FighterParamAccessor2__diddy_special_s_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_7100721240(pa, p1);
}

// 71020a8040 — b external
void FighterParamAccessor2__miifighter_suplex_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_71007212e0(pa, p1);
}

// 71020a8050 — b external
void FighterParamAccessor2__gaogaen_final_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_7100721380(pa, p1, p2);
}

// 71020a8060 — b external
void FighterParamAccessor2__demon_command_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_7100721430(pa, p1);
}

// 71020a8070 — b external
void FighterParamAccessor2__demon_special_lw_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_71007214d0(pa, p1);
}

// 71020a8080 — vtable call to get param data, then indexed read
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FighterParamAccessor2__hit_target_no_impl(FighterParamAccessor2* pa, s32 char_id, s32 entry) {
    asm("str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "cmp w1, #0x4c\n"
        "mov w8, #0x4b\n"
        "csel w8, w8, w1, eq\n"
        "orr w9, wzr, #0x38\n"
        "smaddl x8, w8, w9, x0\n"
        "ldr x0, [x8, #0x70]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "mov x1, #0x9366\n"
        "movk x1, #0xdb50, lsl #16\n"
        "movk x1, #0xa, lsl #32\n"
        "mov w19, w2\n"
        "blr x8\n"
        "ldr x8, [x1]\n"
        "ldr w0, [x8, w19, sxtw #2]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n");
}
#endif

} // namespace app::lua_bind
