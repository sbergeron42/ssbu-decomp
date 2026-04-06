// jemalloc 5.1.0 — larger functions batch 3 (pool-d)
// Address range: 0x710392xxxx — conf parser, atomic_fetch_add, overflow check
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void FUN_7103954000(const char*, ...);  // malloc_write / abort_on_error
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_7106d42540;  // narenas_auto
}

// External jump tables (from .rodata)
extern "C" {
__attribute__((visibility("hidden"))) extern const s32 switchD_710392affc[];  // conf_next switch at 0x7104536188
__attribute__((visibility("hidden"))) extern const s32 switchD_71039294fc[];  // atomic_fetch_add switch at 0x7104536164
}

// String literals referenced by adrp+add
extern "C" {
extern const char STR_7104358ff0[];  // "<jemalloc>: Conf string ends with key\n"
extern const char STR_710438a653[];  // "<jemalloc>: Malformed conf string\n"
extern const char STR_7104452666[];  // "<jemalloc>: Conf string ends with comma\n" (approx)
}

// =========================================================================
// 0x710392ce50 (272 bytes, leaf, -O0) — safe_size_t_mul overflow check
// jemalloc 5.1.0: util.h — safe multiply with overflow detection
// param_1: is_mul (bool), param_2: struct{+0x0: unused, +0x8: a, +0x10: b}
// param_3: *result = a*b (or just b if !is_mul)
// Returns true if overflow, false if ok.
// [derived: mul+overflow check pattern, switch on param_1 bool]
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_710392ce50(u32, void*, u64*) {
    asm(
        "sub sp, sp, #0x20\n"
        "and w8, w0, #0x1\n"
        "strb w8, [sp, #0x1c]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x1c]\n"
        "tbnz w8, #0, 10f\n"
        "b 1f\n"
        // !is_mul: just copy b to result
        "1: b 2f\n"
        "2: b 3f\n"
        "3: ldr x8, [sp, #0x10]\n"
        "ldr x8, [x8, #0x10]\n"
        "ldr x9, [sp, #0x8]\n"
        "str x8, [x9]\n"
        "strb wzr, [sp, #0x1f]\n"
        "b 99f\n"
        // is_mul path
        "10: ldr x8, [sp, #0x10]\n"
        "ldr x9, [x8, #0x10]\n"
        "ldr x8, [x8, #0x8]\n"
        "mul x8, x9, x8\n"
        "ldr x9, [sp, #0x8]\n"
        "str x8, [x9]\n"
        // check if result == 0
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "cbnz x8, 30f\n"
        "b 20f\n"
        // result == 0: overflow iff both a and b are nonzero
        "20: ldr x8, [sp, #0x10]\n"
        "ldr x9, [x8, #0x8]\n"
        "mov w8, wzr\n"
        "cbz x9, 25f\n"
        "b 22f\n"
        "22: ldr x8, [sp, #0x10]\n"
        "ldr x8, [x8, #0x10]\n"
        "subs x8, x8, #0x0\n"
        "cset w8, ne\n"
        "b 25f\n"
        "25: and w8, w8, #0x1\n"
        "strb w8, [sp, #0x1f]\n"
        "b 99f\n"
        // result != 0: check if high bits of a|b set
        "30: ldr x8, [sp, #0x10]\n"
        "ldr x9, [x8, #0x8]\n"
        "ldr x8, [x8, #0x10]\n"
        "orr x8, x9, x8\n"
        "and x8, x8, #0xffffffff00000000\n"
        "cbnz x8, 40f\n"
        "b 35f\n"
        // no high bits set: no overflow possible
        "35: strb wzr, [sp, #0x1f]\n"
        "b 99f\n"
        // high bits set: verify with division
        "40: ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "ldr x10, [x9, #0x10]\n"
        "udiv x8, x8, x10\n"
        "ldr x9, [x9, #0x8]\n"
        "subs x8, x8, x9\n"
        "b.ne 50f\n"
        "b 45f\n"
        // division matches: no overflow
        "45: strb wzr, [sp, #0x1f]\n"
        "b 99f\n"
        // division mismatch: overflow!
        "50: mov w8, #0x1\n"
        "strb w8, [sp, #0x1f]\n"
        "b 99f\n"
        "99: ldrb w0, [sp, #0x1f]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392af90 (496 bytes, -O0) — malloc_conf_next (conf string parser)
// jemalloc 5.1.0: jemalloc.c:749 — static bool malloc_conf_next(...)
// Parses "key:value,key:value..." format config strings.
// Has jump table at 0x7104536188 for character classification (a-z, A-Z, 0-9, _)
// FUN_7103954000 = malloc_write (error message print)
// STR_7104358ff0 = "<jemalloc>: Conf string ends with key\n"
// STR_710438a653 = "<jemalloc>: Malformed conf string\n"
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_710392af90(void**, void**, u64*, void**, u64*) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "str x4, [sp, #0x10]\n"
        // local_50 = *param_1
        "ldur x8, [x29, #-0x10]\n"
        "ldr x8, [x8]\n"
        "str x8, [sp]\n"
        // *param_2 = local_50
        "ldr x8, [sp]\n"
        "ldur x9, [x29, #-0x18]\n"
        "str x8, [x9]\n"
        // bVar1 = false
        "strb wzr, [sp, #0xc]\n"
        // while (!bVar1) — key scan loop
        "b .Lkey_check\n"
        ".Lkey_check:\n"
        "ldrb w8, [sp, #0xc]\n"
        "tbnz w8, #0, .Lkey_done\n"
        "b .Lkey_body\n"
        ".Lkey_body:\n"
        "ldr x8, [sp]\n"
        "ldrb w8, [x8]\n"
        // switch on character (jump table for a-z, A-Z, 0-9, _, :, \\0, default)
        "subs w9, w8, #0x7a\n"
        "b.hi .Lkey_default\n"
        "adrp x9, switchD_710392affc\n"
        "add x9, x9, :lo12:switchD_710392affc\n"
        "ldrsw x8, [x9, x8, lsl #2]\n"
        "add x8, x8, x9\n"
        "br x8\n"

        // case alphanumeric/_: advance pointer
        // (jump table targets here for valid key chars)
        ".Lkey_alpha:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        "b .Lkey_continue\n"

        // case ':': found delimiter
        ".Lkey_colon:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        // *param_3 = local_50 - 1 - *param_2
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1\n"
        "ldur x9, [x29, #-0x18]\n"
        "ldr x9, [x9]\n"
        "subs x8, x8, x9\n"
        "ldr x9, [sp, #0x20]\n"
        "str x8, [x9]\n"
        // *param_4 = local_50
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x18]\n"
        "str x8, [x9]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "b .Lkey_continue\n"

        // case '\\0': ends with key error
        ".Lkey_null:\n"
        "ldr x8, [sp]\n"
        "ldur x9, [x29, #-0x10]\n"
        "ldr x9, [x9]\n"
        "subs x8, x8, x9\n"
        "b.eq .Lkey_null_skip\n"
        "b .Lkey_null_err\n"
        ".Lkey_null_err:\n"
        "adrp x0, STR_7104358ff0\n"
        "add x0, x0, :lo12:STR_7104358ff0\n"
        "bl FUN_7103954000\n"
        "b .Lkey_null_skip\n"
        ".Lkey_null_skip:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b .Lconf_exit\n"

        // default: malformed
        ".Lkey_default:\n"
        "adrp x0, STR_710438a653\n"
        "add x0, x0, :lo12:STR_710438a653\n"
        "bl FUN_7103954000\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b .Lconf_exit\n"

        ".Lkey_continue:\n"
        "b .Lkey_check\n"

        // value scan loop
        ".Lkey_done:\n"
        "strb wzr, [sp, #0xc]\n"
        "b .Lval_check\n"
        ".Lval_check:\n"
        "ldrb w8, [sp, #0xc]\n"
        "tbnz w8, #0, .Lval_done\n"
        "b .Lval_body\n"
        ".Lval_body:\n"
        "ldr x8, [sp]\n"
        "ldrb w8, [x8]\n"
        "cbz w8, .Lval_null\n"
        "b .Lval_notnull\n"
        ".Lval_notnull:\n"
        "subs w8, w8, #0x2c\n"
        "b.ne .Lval_other\n"
        "b .Lval_comma\n"

        // comma case
        ".Lval_comma:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        // check if next char is null (trailing comma)
        "ldr x8, [sp]\n"
        "ldrb w8, [x8]\n"
        "cbnz w8, .Lval_comma_ok\n"
        "b .Lval_comma_err\n"
        ".Lval_comma_err:\n"
        "adrp x0, STR_7104452666\n"
        "add x0, x0, :lo12:STR_7104452666\n"
        "bl FUN_7103954000\n"
        "b .Lval_comma_ok\n"
        ".Lval_comma_ok:\n"
        // *param_5 = (local_50 - 1) - *param_4
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1\n"
        "ldr x9, [sp, #0x18]\n"
        "ldr x9, [x9]\n"
        "subs x8, x8, x9\n"
        "ldr x9, [sp, #0x10]\n"
        "str x8, [x9]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "b .Lval_continue\n"

        // null terminator case
        ".Lval_null:\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x18]\n"
        "ldr x9, [x9]\n"
        "subs x8, x8, x9\n"
        "ldr x9, [sp, #0x10]\n"
        "str x8, [x9]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "b .Lval_continue\n"

        // other char: advance
        ".Lval_other:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        "b .Lval_continue\n"

        ".Lval_continue:\n"
        "b .Lval_check\n"

        // done: *param_1 = local_50
        ".Lval_done:\n"
        "ldr x8, [sp]\n"
        "ldur x9, [x29, #-0x10]\n"
        "str x8, [x9]\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b .Lconf_exit\n"

        ".Lconf_exit:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039294b0 (272 bytes, leaf, -O0) — atomic_fetch_add_u32 to narenas_auto
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_fetch_add_u32(&narenas_auto, 1, RELEASE)
// Has jump table at 0x7104536164 for memory order dispatch (5 entries: mo 1-5).
// Uses ldxr/ldaxr + stxr/stlxr loop per memory order.
// DAT_7106d42540 = narenas_auto
// Case layout: default/relaxed, acquire, release, acq_rel, seq_cst
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039294b0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "adrp x8, DAT_7106d42540\n"
        "add x8, x8, :lo12:DAT_7106d42540\n"
        "str x8, [sp, #0x18]\n"
        "mov w8, #0x1\n"
        "str w8, [sp, #0x14]\n"
        "orr w8, wzr, #0x3\n"
        "str w8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0x10]\n"
        "ldr w10, [sp, #0x14]\n"
        "str w10, [sp, #0xc]\n"
        // switch on mo-1 (jump table)
        "subs w9, w9, #0x1\n"
        "subs w10, w9, #0x4\n"
        "b.hi .Lfa_default\n"
        "adrp x10, switchD_71039294fc\n"
        "add x10, x10, :lo12:switchD_71039294fc\n"
        "ldrsw x9, [x10, x9, lsl #2]\n"
        "add x9, x9, x10\n"
        "br x9\n"

        // case default / case 0 (relaxed/consume): ldxr/stxr
        ".Lfa_default:\n"
        "ldr w9, [sp, #0xc]\n"
        "b .Lfa_relax_loop\n"
        ".Lfa_relax_loop:\n"
        "ldxr w10, [x8]\n"
        "add w11, w10, w9\n"
        "stxr w12, w11, [x8]\n"
        "cbnz w12, .Lfa_relax_loop\n"
        "b .Lfa_relax_done\n"
        ".Lfa_relax_done:\n"
        "str w10, [sp, #0x8]\n"
        "b .Lfa_exit\n"

        // case 1 (acquire): ldaxr/stxr
        ".Lfa_acquire:\n"
        "ldr w9, [sp, #0xc]\n"
        "b .Lfa_acq_loop\n"
        ".Lfa_acq_loop:\n"
        "ldaxr w10, [x8]\n"
        "add w11, w10, w9\n"
        "stxr w12, w11, [x8]\n"
        "cbnz w12, .Lfa_acq_loop\n"
        "b .Lfa_acq_done\n"
        ".Lfa_acq_done:\n"
        "str w10, [sp, #0x8]\n"
        "b .Lfa_exit\n"

        // case 2 (release): ldxr/stlxr
        ".Lfa_release:\n"
        "ldr w9, [sp, #0xc]\n"
        "b .Lfa_rel_loop\n"
        ".Lfa_rel_loop:\n"
        "ldxr w10, [x8]\n"
        "add w11, w10, w9\n"
        "stlxr w12, w11, [x8]\n"
        "cbnz w12, .Lfa_rel_loop\n"
        "b .Lfa_rel_done\n"
        ".Lfa_rel_done:\n"
        "str w10, [sp, #0x8]\n"
        "b .Lfa_exit\n"

        // case 3 (acq_rel): ldaxr/stlxr
        ".Lfa_acqrel:\n"
        "ldr w9, [sp, #0xc]\n"
        "b .Lfa_ar_loop\n"
        ".Lfa_ar_loop:\n"
        "ldaxr w10, [x8]\n"
        "add w11, w10, w9\n"
        "stlxr w12, w11, [x8]\n"
        "cbnz w12, .Lfa_ar_loop\n"
        "b .Lfa_ar_done\n"
        ".Lfa_ar_done:\n"
        "str w10, [sp, #0x8]\n"
        "b .Lfa_exit\n"

        // case 4 (seq_cst): ldaxr/stlxr
        ".Lfa_seqcst:\n"
        "ldr w9, [sp, #0xc]\n"
        "b .Lfa_sc_loop\n"
        ".Lfa_sc_loop:\n"
        "ldaxr w10, [x8]\n"
        "add w11, w10, w9\n"
        "stlxr w12, w11, [x8]\n"
        "cbnz w12, .Lfa_sc_loop\n"
        "b .Lfa_sc_done\n"
        ".Lfa_sc_done:\n"
        "str w10, [sp, #0x8]\n"
        "b .Lfa_exit\n"

        ".Lfa_exit:\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
