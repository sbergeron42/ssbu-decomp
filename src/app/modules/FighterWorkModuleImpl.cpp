#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {

// 71020adb50 — 6 instructions (vtable dispatcher with 2 bool masks)
void* FighterWorkModuleImpl__calc_param_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x50)); return reinterpret_cast<void*(*)(void*,bool,bool)>(VT(m)[0x280/8])(m,p1,p2); }

// 71020adb70 — calc_escape_air_slide_param_impl (896 bytes in CSV)
// NX prologue: d11:d10 saved first, fp/lr last.
// Uses FighterParamAccessor2 singleton (DAT_71052bb3b0), FUN_71003ca970 (work setter).
// Computes slide animation parameters (start velocity, step, num_steps) from param table.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterWorkModuleImpl__calc_escape_air_slide_param_impl(BattleObjectModuleAccessor* a, float t) {
    asm(
        // NX prologue
        "stp d11, d10, [sp, #-0x40]!\n"
        "stp d9, d8, [sp, #0x10]\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        // x19 = work module ptr (accessor+0x50)
        "ldr x19, [x0, #0x50]\n"
        // fighter kind normalization: 0x4c → 0x4b
        "ldr w8, [x19, #0x40]\n"
        "cmp w8, #0x4c\n"
        "mov w9, #0x4b\n"
        "csel w9, w9, w8, eq\n"
        // bounds check: if kind >= 0x5e, abort
        "cmp w9, #0x5e\n"
        "b.cs 2f\n"
        // load singleton: FighterParamAccessor2::instance_
        "adrp x8, DAT_71052bb3b0\n"
        "ldr x10, [x8, :lo12:DAT_71052bb3b0]\n"
        "ldr x8, [x10, #0x10]\n"
        // w11 = 12 (entry stride for kind index)
        "orr w11, wzr, #0xc\n"
        // x9 = &singleton->entries[kind] = x10 + kind*12
        "smaddl x9, w9, w11, x10\n"
        // x12 = magic multiplier for vector bounds check
        "mov x12, #0x4c6b\n"
        "movk x12, #0x7a4, lsl #16\n"
        "movk x12, #0x672a, lsl #32\n"
        "movk x12, #0xf0b7, lsl #48\n"
        // x9 = signed count from param entry at offset 0x14f4
        "ldrsw x9, [x9, #0x14f4]\n"
        // x10,x11 = begin,end pointers of param array
        "ldp x10, x11, [x8, #0x8]\n"
        // bounds check: if (end-begin)/8 * magic <= x9, throw_out_of_range
        "sub x11, x11, x10\n"
        "asr x11, x11, #0x3\n"
        "mul x11, x11, x12\n"
        "cmp x11, x9\n"
        "b.ls 3f\n"
        // x8 = &param_table[x9] = x10 + x9 * 0x218
        "mov w8, #0x218\n"
        "madd x8, x9, x8, x10\n"
        // s8 = 1.0 (callee-saved)
        "fmov s8, #1.0\n"
        // s1 = 1.0 - t  (s0 = t on entry)
        "fsub s1, s8, s0\n"
        // load 4 floats from param entry
        "ldp s2, s3, [x8, #0x84]\n"   // s2=param[0x84], s3=param[0x88]
        "ldp s4, s5, [x8, #0x7c]\n"   // s4=param[0x7c], s5=param[0x80]
        "ldr s9, [x8, #0x8c]\n"        // s9=param[0x8c] (target velocity, callee-saved)
        // load vtable fn for speed query: x8 = work->vtable[0x270/8]
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x270]\n"
        // x1 = hash 0x1dfb01ad43
        "mov x1, #0xad43\n"
        "movk x1, #0xfb01, lsl #16\n"
        "movk x1, #0x1d, lsl #32\n"
        "mov x0, x19\n"
        // interpolate: s2=param[0x84]*t, s0=param[0x88]*t
        "fmul s2, s2, s0\n"
        "fmul s0, s3, s0\n"
        // s3=(1-t)*param[0x7c], s1=(1-t)*param[0x80]
        "fmul s3, s1, s4\n"
        "fmul s1, s1, s5\n"
        "mov x2, xzr\n"
        // s10 = lerp(param[0x7c], param[0x84], t) = start velocity (callee-saved)
        "fadd s10, s3, s2\n"
        // s11 = lerp(param[0x80], param[0x88], t) = end velocity (callee-saved)
        "fadd s11, s1, s0\n"
        // call vtable fn → s0 = some speed factor
        "blr x8\n"
        // compute slide steps: fVar7 = (s9-s10) / ((s9^2-s10^2)*(1/(s11*s0))*0.5)
        "fmul s0, s11, s0\n"            // s0 = s11 * speed_factor
        "fdiv s0, s8, s0\n"             // s0 = 1.0 / (s11 * speed_factor)
        "fmul s1, s9, s9\n"             // s1 = s9^2
        "fmul s2, s10, s10\n"           // s2 = s10^2
        "fsub s1, s1, s2\n"             // s1 = s9^2 - s10^2
        "fmul s3, s1, s0\n"             // s3 = (s9^2-s10^2)/(s11*speed)
        "fmov s1, #0.5\n"
        "fmul s0, s3, s1\n"             // s0 = (s9^2-s10^2)/(s11*speed) * 0.5
        "fsub s1, s9, s10\n"            // s1 = s9 - s10
        "fdiv s8, s1, s0\n"             // s8 = (s9-s10) / above = num_steps (float)
        // load work data pointer: x8 = *(*(x19+0x38) + 0x8)
        "ldr x8, [x19, #0x38]\n"
        "ldr x8, [x8, #0x8]\n"
        // round num_steps to nearest int as float
        "frinta s0, s8\n"
        // w20 = work field offset 0x1b18
        "mov w20, #0x1b18\n"
        // hash1 = 0x166ed053cc
        "mov x1, #0x53cc\n"
        "movk x1, #0x6ed0, lsl #16\n"
        "add x0, x8, x20\n"
        "movk x1, #0x16, lsl #32\n"
        // s9 = (s9 - s10) / round(s8) = step_increment
        "fdiv s9, s1, s0\n"
        // store s10 (start velocity) at hash1
        "bl FUN_71003ca970\n"
        "str s10, [x0]\n"
        // load work data again for second store
        "ldr x8, [x19, #0x38]\n"
        "ldr x8, [x8, #0x8]\n"
        // hash2 = 0x163c0a9bdf
        "mov x1, #0x9bdf\n"
        "movk x1, #0x3c0a, lsl #16\n"
        "movk x1, #0x16, lsl #32\n"
        "add x0, x8, x20\n"
        "bl FUN_71003ca970\n"
        // round s8 to int then back to float
        "fcvtas w8, s8\n"
        // store s9 (step increment) at hash2
        "str s9, [x0]\n"
        "scvtf s8, w8\n"
        // load work data for third store
        "ldr x8, [x19, #0x38]\n"
        "ldr x8, [x8, #0x8]\n"
        // hash3 = 0x15f2c6719b
        "mov x1, #0x719b\n"
        "movk x1, #0xf2c6, lsl #16\n"
        "movk x1, #0x15, lsl #32\n"
        "add x0, x8, x20\n"
        "bl FUN_71003ca970\n"
        // store s8 (rounded num_steps) at hash3
        "str s8, [x0]\n"
        // normal epilogue
        "ldp d9, d8, [sp, #0x10]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "ldp d11, d10, [sp], #0x40\n"
        "ret\n"
        // abort path (kind >= 0x5e)
        "2:\n"
        "bl FUN_71039c20a0\n"
        // throw_out_of_range path (vector bounds check failed)
        "3:\n"
        "add x0, x8, #0x8\n"
        "bl FUN_71039c0d80\n"
    );
}
#endif

} // namespace app::lua_bind
