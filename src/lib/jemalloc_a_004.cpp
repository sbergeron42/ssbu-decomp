// jemalloc 5.1.0 — malloc/free entry points, memalign, mallctl
// Nintendo Switch build: SDK 8.2.1
// Source: jemalloc.c (malloc_default, free_default, imalloc, memalign, mallctl)

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions defined in other jemalloc batch files
extern "C" {
u8    FUN_71039277b0(void);             // malloc_initialized check
u8    malloc_init(void);                // 0x710392ca70
void  set_errno(u32);                   // 0x710392b1e0
void* tsd_fetch(void);                  // 0x710392cac0
u8    tsd_fast(void*);                  // 0x710392cae0
void  tsd_assert_fast(void*);           // 0x710392ae10
void* tsd_fetch_min(void);              // 0x710392e670
void* tsd_tsdn(void*);                  // 0x71039280f0
void  check_entry_exit_locking(void*);  // 0x710392acb0
u64   isalloc(void*, void*);            // 0x710392e920
void* tsdn_fetch(void);                 // 0x710392ac60
}

// External functions not yet defined (FUN_ stubs)
extern "C" {
u32   FUN_710392cb30(void*, void*, void*); // imalloc_body
void  FUN_710392df20(void*, void*, void*, u32); // ifree
u32   FUN_710392dba0(void);             // je_mallctl helper (inner)
u8    FUN_7103946160(void);             // je_mallctl bool check
u32   FUN_71039461c0(void*, void*, void*, void*, void*, void*); // ctl_byname
u32   FUN_71039508b0(void*, void*, void*, void*, void*, void*, void*); // ctl_bymib
u64   FUN_7103928da0(u64);              // conditional return value (extern "C")
}

// C++ linkage external functions (need mangled names in asm)
u64 FUN_7103929160(u64);                // thunk wrapper
u8  FUN_7103927b00(u64);                // deref byte helper

// External data symbols (hidden visibility — linker-resolved, not GOT)
extern "C" {
__attribute__((visibility("hidden"))) extern u8  DAT_7104866c2e;  // string: used by static_opts_init
__attribute__((visibility("hidden"))) extern u8  DAT_71042c2a57;  // string: used by malloc_default
__attribute__((visibility("hidden"))) extern u8  DAT_71043590be;  // string: used by je_posix_memalign/je_aligned_alloc
__attribute__((visibility("hidden"))) extern u8  DAT_7104369fd2;  // string: used by je_posix_memalign/je_aligned_alloc
__attribute__((visibility("hidden"))) extern u32 DAT_71052934c0;  // flag: used by je_mallctl@d610
__attribute__((visibility("hidden"))) extern u32 DAT_7106d424a0;  // result storage: used by je_mallctl@d610
}

// Forward declarations for functions defined in this file
extern "C" {
void static_opts_init(void*);
void dynamic_opts_init(void*);
u32  imalloc(void*, void*);
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — static_opts_init
// 0x710392c8f0 (96 bytes, leaf, -O0)
// Zeroes all fields and sets two string pointers in static_opts struct
// =========================================================================
extern "C" __attribute__((naked))
void static_opts_init(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x1]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x2]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x3]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x4]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "adrp x9, DAT_7104866c2e\n"
        "add x9, x9, :lo12:DAT_7104866c2e\n"
        "str x9, [x8, #0x10]\n"
        "ldr x8, [sp, #0x8]\n"
        "str x9, [x8, #0x18]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x20]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — dynamic_opts_init
// 0x710392c950 (80 bytes, leaf, -O0)
// Zeroes dynamic_opts struct and sets arena_index fields to -2 and -1
// =========================================================================
extern "C" __attribute__((naked))
void dynamic_opts_init(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8, #0x10]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8, #0x18]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8, #0x20]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr w9, wzr, #0xfffffffe\n"
        "str w9, [x8, #0x24]\n"
        "ldr x8, [sp, #0x8]\n"
        "mov w9, #0xffffffff\n"
        "str w9, [x8, #0x28]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — imalloc
// 0x710392c9a0 (208 bytes, -O0)
// Core allocation dispatcher: checks init, gets tsd, calls imalloc_body
// Calls: FUN_71039277b0, malloc_init, set_errno, tsd_fetch, tsd_fast,
//        tsd_assert_fast, FUN_710392cb30 (imalloc_body)
// =========================================================================
extern "C" __attribute__((naked))
u32 imalloc(void*, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        // if (malloc_initialized()) skip init
        "bl FUN_71039277b0\n"
        "tbnz w0, #0, 1f\n"
        "b 2f\n"
        // malloc_init() failed
        "2:\n"
        "bl malloc_init\n"
        "tbz w0, #0, 1f\n"
        "b 3f\n"
        "3:\n"
        "orr w19, wzr, #0xc\n"
        "orr w0, wzr, #0xc\n"
        "bl set_errno\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x8, [x8]\n"
        "str xzr, [x8]\n"
        "stur w19, [x29, #-0x4]\n"
        "b 0f\n"
        // tsd = tsd_fetch()
        "1:\n"
        "bl tsd_fetch\n"
        "str x0, [sp, #0x8]\n"
        "b 4f\n"
        "4: b 5f\n"
        "5:\n"
        // if (tsd_fast(tsd)) — fast path
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_fast\n"
        "tbz w0, #0, 6f\n"
        "b 7f\n"
        "7:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_assert_fast\n"
        "ldr x8, [sp, #0x18]\n"
        "strb wzr, [x8, #0x20]\n"
        "ldr x0, [sp, #0x18]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_710392cb30\n"
        "stur w0, [x29, #-0x4]\n"
        "b 0f\n"
        // slow path
        "6:\n"
        "ldr x8, [sp, #0x18]\n"
        "mov w9, #0x1\n"
        "strb w9, [x8, #0x20]\n"
        "ldr x0, [sp, #0x18]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_710392cb30\n"
        "stur w0, [x29, #-0x4]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldr x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — malloc_default (je_malloc)
// 0x710392c870 (128 bytes, -O0)
// Sets up static_opts + dynamic_opts on stack, calls imalloc
// Calls: static_opts_init, dynamic_opts_init, imalloc
// =========================================================================
extern "C" __attribute__((naked))
void* malloc_default(void*) {
    asm(
        "sub sp, sp, #0x80\n"
        "stp x29, x30, [sp, #0x70]\n"
        "add x29, sp, #0x70\n"
        "stur x0, [x29, #-0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "add x0, sp, #0x38\n"
        "bl static_opts_init\n"
        "add x0, sp, #0x8\n"
        "bl dynamic_opts_init\n"
        // Set static_opts fields
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x39]\n"       // sopts->null_out_result_on_error = true
        "strb w8, [sp, #0x3b]\n"       // sopts->oom_string = true
        "strb w8, [sp, #0x3c]\n"       // sopts->may_overflow = true
        // Set static_opts string pointer
        "adrp x9, DAT_71042c2a57\n"
        "add x9, x9, :lo12:DAT_71042c2a57\n"
        "str x9, [sp, #0x48]\n"
        // Set dynamic_opts fields
        "sub x9, x29, #0x10\n"
        "str x9, [sp, #0x8]\n"         // dopts->result = &result
        "str x8, [sp, #0x10]\n"        // dopts->num_items = 1
        "ldur x8, [x29, #-0x8]\n"
        "str x8, [sp, #0x18]\n"        // dopts->item_size = size
        // Call imalloc
        "add x0, sp, #0x38\n"
        "add x1, sp, #0x8\n"
        "bl imalloc\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldur x0, [x29, #-0x10]\n"     // return result
        "ldp x29, x30, [sp, #0x70]\n"
        "add sp, sp, #0x80\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — je_mallctl (variant at 0x710392d610)
// 0x710392d610 (96 bytes, -O0)
// Sets a global flag, calls FUN_710392dba0, stores result, calls FUN_7103946160
// =========================================================================
extern "C" __attribute__((naked))
u8 je_mallctl_d610(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        // Set flag to 1
        "adrp x8, DAT_71052934c0\n"
        "mov w9, #0x1\n"
        "str w9, [x8, :lo12:DAT_71052934c0]\n"
        // Call inner function, store result
        "bl FUN_710392dba0\n"
        "adrp x8, DAT_7106d424a0\n"
        "str w0, [x8, :lo12:DAT_7106d424a0]\n"
        // Check bool
        "bl FUN_7103946160\n"
        "tbz w0, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 0f\n"
        "1:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 0f\n"
        "0:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — je_posix_memalign
// 0x710392dc40 (160 bytes, -O0)
// Sets up static_opts + dynamic_opts on stack with alignment params, calls imalloc
// Calls: static_opts_init, dynamic_opts_init, imalloc
// =========================================================================
extern "C" __attribute__((naked))
u32 je_posix_memalign(void*, void*, void*) {
    asm(
        "sub sp, sp, #0x90\n"
        "stp x29, x30, [sp, #0x80]\n"
        "add x29, sp, #0x80\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "add x0, sp, #0x38\n"
        "bl static_opts_init\n"
        "add x0, sp, #0x8\n"
        "bl dynamic_opts_init\n"
        // sopts->bump_empty_aligned_alloc = true
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x39]\n"
        // sopts->min_alignment = 8 (sizeof(void*))
        "mov w9, #0x8\n"
        "str x9, [sp, #0x40]\n"
        // sopts->oom_string (first)
        "adrp x9, DAT_71043590be\n"
        "add x9, x9, :lo12:DAT_71043590be\n"
        "str x9, [sp, #0x48]\n"
        // sopts->invalid_alignment_string
        "adrp x9, DAT_7104369fd2\n"
        "add x9, x9, :lo12:DAT_7104369fd2\n"
        "str x9, [sp, #0x50]\n"
        // dopts->result = memptr (param 1)
        "ldur x9, [x29, #-0x8]\n"
        "str x9, [sp, #0x8]\n"
        // dopts->num_items = 1
        "str x8, [sp, #0x10]\n"
        // dopts->item_size = size (param 3)
        "ldur x8, [x29, #-0x18]\n"
        "str x8, [sp, #0x18]\n"
        // dopts->alignment = alignment (param 2)
        "ldur x8, [x29, #-0x10]\n"
        "str x8, [sp, #0x20]\n"
        // Call imalloc
        "add x0, sp, #0x38\n"
        "add x1, sp, #0x8\n"
        "bl imalloc\n"
        "stur w0, [x29, #-0x1c]\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldur w0, [x29, #-0x1c]\n"
        "ldp x29, x30, [sp, #0x80]\n"
        "add sp, sp, #0x90\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — je_aligned_alloc
// 0x710392dce0 (160 bytes, -O0)
// Sets up static_opts + dynamic_opts on stack with alignment, calls imalloc
// Calls: static_opts_init, dynamic_opts_init, imalloc
// =========================================================================
extern "C" __attribute__((naked))
void* je_aligned_alloc(void*, void*) {
    asm(
        "sub sp, sp, #0x80\n"
        "stp x29, x30, [sp, #0x70]\n"
        "add x29, sp, #0x70\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "add x0, sp, #0x30\n"
        "bl static_opts_init\n"
        "mov x0, sp\n"
        "bl dynamic_opts_init\n"
        // sopts fields
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x31]\n"       // sopts->bump_empty_aligned_alloc
        "strb w8, [sp, #0x33]\n"       // sopts->oom_string
        "strb w8, [sp, #0x34]\n"       // sopts->may_overflow
        // sopts->min_alignment = 1
        "str x8, [sp, #0x38]\n"
        // sopts->oom_string_ptr
        "adrp x9, DAT_71043590be\n"
        "add x9, x9, :lo12:DAT_71043590be\n"
        "str x9, [sp, #0x40]\n"
        // sopts->invalid_alignment_string
        "adrp x9, DAT_7104369fd2\n"
        "add x9, x9, :lo12:DAT_7104369fd2\n"
        "str x9, [sp, #0x48]\n"
        // dopts->result = &local_result (on stack)
        "sub x9, x29, #0x18\n"
        "str x9, [sp]\n"
        // dopts->num_items = 1
        "str x8, [sp, #0x8]\n"
        // dopts->item_size = size (param 2)
        "ldur x8, [x29, #-0x10]\n"
        "str x8, [sp, #0x10]\n"
        // dopts->alignment = alignment (param 1)
        "ldur x8, [x29, #-0x8]\n"
        "str x8, [sp, #0x18]\n"
        // Call imalloc
        "add x0, sp, #0x30\n"
        "mov x1, sp\n"
        "bl imalloc\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldur x0, [x29, #-0x18]\n"     // return result
        "ldp x29, x30, [sp, #0x70]\n"
        "add sp, sp, #0x80\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — free_default (je_free)
// 0x710392e590 (224 bytes, -O0)
// Calls: tsd_fetch_min, tsd_tsdn, check_entry_exit_locking, tsd_fast,
//        tsd_assert_fast, FUN_7103929160, FUN_710392df20, FUN_7103927b00,
//        FUN_7103928da0
// =========================================================================
extern "C" __attribute__((naked))
void free_default(void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        // if (ptr == NULL) goto end
        "ldur x8, [x29, #-0x8]\n"
        "cbz x8, 8f\n"
        "b 3f\n"
        // tsd = tsd_fetch_min()
        "3:\n"
        "bl tsd_fetch_min\n"
        "str x0, [sp, #0x10]\n"
        // check_entry_exit_locking(tsd_tsdn(tsd))
        "ldr x0, [sp, #0x10]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        // if (tsd_fast(tsd)) — fast path
        "ldr x0, [sp, #0x10]\n"
        "bl tsd_fast\n"
        "tbz w0, #0, 6f\n"
        "b 4f\n"
        // Fast path
        "4:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl tsd_assert_fast\n"
        "ldr x0, [sp, #0x10]\n"
        "bl _Z14FUN_7103929160y\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "ldur x1, [x29, #-0x8]\n"
        "ldr x2, [sp, #0x8]\n"
        "mov w3, wzr\n"
        "bl FUN_710392df20\n"
        "b 9f\n"
        // Slow path
        "6:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl _Z14FUN_7103927b00y\n"
        "and w8, w0, #0xff\n"
        "cbnz w8, 7f\n"
        "b 10f\n"
        "10:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103928da0\n"
        "str x0, [sp, #0x8]\n"
        "b 11f\n"
        "7:\n"
        "str xzr, [sp, #0x8]\n"
        "b 11f\n"
        "11:\n"
        "ldr x0, [sp, #0x10]\n"
        "ldur x1, [x29, #-0x8]\n"
        "ldr x2, [sp, #0x8]\n"
        "mov w3, #0x1\n"
        "bl FUN_710392df20\n"
        "b 9f\n"
        // Epilogue: check_entry_exit_locking(tsd_tsdn(tsd))
        "9:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        "b 8f\n"
        // End
        "8:\n"
        "b 12f\n"
        "12: b 13f\n"
        "13:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — je_malloc_size
// 0x710392e8a0 (128 bytes, -O0)
// Calls: tsdn_fetch, check_entry_exit_locking, isalloc
// =========================================================================
extern "C" __attribute__((naked))
usize je_malloc_size(void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4:\n"
        // tsdn = tsdn_fetch()
        "bl tsdn_fetch\n"
        "str x0, [sp, #0x8]\n"
        // check_entry_exit_locking(tsdn)
        "ldr x0, [sp, #0x8]\n"
        "bl check_entry_exit_locking\n"
        // if (ptr == NULL) return 0
        "ldur x8, [x29, #-0x8]\n"
        "cbnz x8, 5f\n"
        "b 6f\n"
        "6:\n"
        "str xzr, [sp, #0x10]\n"
        "b 0f\n"
        // return isalloc(tsdn, ptr)
        "5:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldur x1, [x29, #-0x8]\n"
        "bl isalloc\n"
        "str x0, [sp, #0x10]\n"
        "b 0f\n"
        // check_entry_exit_locking again
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl check_entry_exit_locking\n"
        "b 7f\n"
        "7: b 8f\n"
        "8:\n"
        "ldr x0, [sp, #0x10]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: ctl.c — je_mallctl (main entry point)
// 0x710392e690 (176 bytes, -O0)
// Calls: malloc_init, tsd_fetch, tsd_tsdn, check_entry_exit_locking,
//        FUN_71039461c0 (ctl_byname)
// =========================================================================
extern "C" __attribute__((naked))
u32 je_mallctl(void*, void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "str x4, [sp, #0x10]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        // if (malloc_init()) return EAGAIN
        "bl malloc_init\n"
        "tbz w0, #0, 3f\n"
        "b 4f\n"
        "4: b 5f\n"
        "5: b 6f\n"
        "6:\n"
        "mov w8, #0xb\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // tsd = tsd_fetch()
        "3:\n"
        "bl tsd_fetch\n"
        "str x0, [sp]\n"
        // check_entry_exit_locking(tsd_tsdn(tsd))
        "ldr x0, [sp]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        // ret = ctl_byname(tsd, name, oldp, oldlenp, newp, newlen)
        "ldr x0, [sp]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldur x2, [x29, #-0x18]\n"
        "ldr x3, [sp, #0x20]\n"
        "ldr x4, [sp, #0x18]\n"
        "ldr x5, [sp, #0x10]\n"
        "bl FUN_71039461c0\n"
        "str w0, [sp, #0xc]\n"
        // check_entry_exit_locking(tsd_tsdn(tsd))
        "ldr x0, [sp]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        "b 7f\n"
        "7: b 8f\n"
        "8:\n"
        "ldr w8, [sp, #0xc]\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: ctl.c — je_mallctlbymib
// 0x710392e7e0 (192 bytes, -O0)
// Calls: malloc_init, tsd_fetch, tsd_tsdn, check_entry_exit_locking,
//        FUN_71039508b0 (ctl_bymib)
// =========================================================================
extern "C" __attribute__((naked))
u32 je_mallctlbymib(void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "stur x2, [x29, #-0x20]\n"
        "str x3, [sp, #0x28]\n"
        "str xzr, [sp, #0x20]\n"
        "str xzr, [sp, #0x18]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        // if (malloc_init()) return EAGAIN
        "bl malloc_init\n"
        "tbz w0, #0, 3f\n"
        "b 4f\n"
        "4: b 5f\n"
        "5: b 6f\n"
        "6:\n"
        "mov w8, #0xb\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // tsd = tsd_fetch()
        "3:\n"
        "bl tsd_fetch\n"
        "str x0, [sp, #0x8]\n"
        // check_entry_exit_locking(tsd_tsdn(tsd))
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        // ret = ctl_bymib(tsd, mib, miblen, oldp, oldlenp, newp, newlen)
        "ldr x0, [sp, #0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldur x2, [x29, #-0x18]\n"
        "ldur x3, [x29, #-0x20]\n"
        "ldr x4, [sp, #0x28]\n"
        "ldr x5, [sp, #0x20]\n"
        "ldr x6, [sp, #0x18]\n"
        "bl FUN_71039508b0\n"
        "str w0, [sp, #0x14]\n"
        // check_entry_exit_locking(tsd_tsdn(tsd))
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_tsdn\n"
        "bl check_entry_exit_locking\n"
        "b 7f\n"
        "7: b 8f\n"
        "8:\n"
        "ldr w8, [sp, #0x14]\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
