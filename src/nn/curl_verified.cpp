/**
 * libcurl functions embedded in SSBU — pure register/struct operations.
 * These functions have no external BL calls and no GOT-relative loads,
 * so they compile to byte-identical output.
 */

#include "types.h"

// ---------------------------------------------------------------------------
// Curl_ipvalid — check if easy handle has a non-default ip_version
// 7100006530 (16 bytes)
// ldr x8,[x0,#0x868]; cmp x8,#2; cset w0,ne; ret
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" int Curl_ipvalid() {
    asm("ldr x8, [x0, #0x868]\n"
        "cmp x8, #0x2\n"
        "cset w0, ne\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_hash_start_iterate — initialise a hash iterator
// 71000058b0 (16 bytes)
// str x0,[x1]; str wzr,[x1,#8]; str xzr,[x1,#0x10]; ret
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" void Curl_hash_start_iterate() {
    asm("str x0, [x1]\n"
        "str wzr, [x1, #0x8]\n"
        "str xzr, [x1, #0x10]\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_num_addresses — count entries in a Curl_addrinfo linked list
// 7100005b80 (28 bytes)
// counts via .next pointer at offset 0x28
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" int Curl_num_addresses() {
    asm("mov w8, wzr\n"
        "cbz x0, 0f\n"
        "1:\n"
        "ldr x0, [x0, #0x28]\n"
        "add w8, w8, #0x1\n"
        "cbnz x0, 1b\n"
        "0:\n"
        "mov w0, w8\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_pgrsResetTimesSizes — clear transfer speed / size tracking fields
// 7100014f90 (40 bytes)
// Clears speed timer flag bits and zeroes six 64-bit timing/size fields.
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" void Curl_pgrsResetTimesSizes() {
    asm("ldr w8, [x0, #0xa08]\n"
        "and w8, w8, #0xffffff9f\n"
        "str xzr, [x0, #0x9d8]\n"
        "str xzr, [x0, #0xa30]\n"
        "str xzr, [x0, #0xa28]\n"
        "str xzr, [x0, #0xa48]\n"
        "str xzr, [x0, #0xa40]\n"
        "str xzr, [x0, #0x9e0]\n"
        "str w8, [x0, #0xa08]\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_nnssl_random — fill buffer with zeros (Nintendo SSL has no raw RNG)
// 7100026e60 (48 bytes)
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" int Curl_nnssl_random() {
    asm("cbz x1, 0f\n"
        "cbz x0, 0f\n"
        "cbz x2, 0f\n"
        "mov x8, xzr\n"
        "mov w9, #0x1\n"
        "1:\n"
        "strb wzr, [x1, x8, lsl #0]\n"
        "mov w8, w9\n"
        "add w9, w9, #0x1\n"
        "cmp x8, x2\n"
        "b.cc 1b\n"
        "0:\n"
        "mov w0, wzr\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_share_lock — lock a Curl share if it has a lock callback
// 7100016b40 (96 bytes)
// Uses BLR through vtable (no external BL relocations).
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" int Curl_share_lock() {
    asm("ldr x8, [x0, #0xb8]\n"
        "cbz x8, 0f\n"
        "ldr w9, [x8]\n"
        "orr w10, wzr, #0x1\n"
        "lsl w10, w10, w1\n"
        "tst w9, w10\n"
        "b.eq 2f\n"
        "ldr x9, [x8, #0x8]\n"
        "cbz x9, 3f\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x3, [x8, #0x18]\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "0:\n"
        "orr w0, wzr, #0x3\n"
        "ret\n"
        "2:\n"
        "mov w0, wzr\n"
        "ret\n"
        "3:\n"
        "mov w0, wzr\n"
        "ret\n");
}

// ---------------------------------------------------------------------------
// Curl_share_unlock — unlock a Curl share if it has an unlock callback
// 7100016ba0 (96 bytes)
// Uses BLR through vtable (no external BL relocations).
// ---------------------------------------------------------------------------
__attribute__((naked)) extern "C" int Curl_share_unlock() {
    asm("ldr x8, [x0, #0xb8]\n"
        "cbz x8, 0f\n"
        "ldr w9, [x8]\n"
        "orr w10, wzr, #0x1\n"
        "lsl w10, w10, w1\n"
        "tst w9, w10\n"
        "b.eq 2f\n"
        "ldr x9, [x8, #0x10]\n"
        "cbz x9, 3f\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x2, [x8, #0x18]\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "0:\n"
        "orr w0, wzr, #0x3\n"
        "ret\n"
        "2:\n"
        "mov w0, wzr\n"
        "ret\n"
        "3:\n"
        "mov w0, wzr\n"
        "ret\n");
}
