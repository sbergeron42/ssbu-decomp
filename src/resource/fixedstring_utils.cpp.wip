// res_large_funcs.cpp — Resource service large functions + FixedString utilities
//
// ASSIGNED TARGETS — IDENTIFICATION RESULTS:
//   FUN_710374d270 (8,432 bytes) — SKIP: scene/render update loop (iterates
//     5 vectors of render objects via DAT_710593aa90, calls FUN_710378eb90 per object)
//   FUN_7103757290 (7,056 bytes) — SKIP: Mii renderer init (nn::mii::Database::Initialize,
//     BuildDefault x6, creates MiiModelRenderer with named render passes)
//   FUN_7103758f50 (5,520 bytes) — SKIP: Mii model creation (allocates 0x388-byte model,
//     sets up 4 render passes with shadow/outline, shared_ptr pattern)
//
// REPLACEMENT TARGETS — FixedString<512> utilities (resource service infrastructure):
//   FUN_71037c3f20 (240 bytes) — FixedString<512>::assign from const char*
//   FUN_71037c4550 (224 bytes) — FixedString<512>::assign from buffer + length
//   FUN_71037c4630 (672 bytes) — FixedString<512>::append
//
// NOTE: These functions throw std::out_of_range. Must compile with -fexceptions.
//   Build command:
//   /c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17
//     -fexceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums
//     -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize
//     -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include
//     -Ilib/NintendoSDK/include/stubs -c src/resource/res_large_funcs.cpp
//     -o build/res_large_funcs.o

#include "types.h"
#include <stdexcept>

extern "C" unsigned long strlen(const char*);

// FixedString<512> layout: char data[514] at +0x000, u16 length at +0x202
// [derived: Ghidra 13.0.4 decompilation, error strings at FUN_71037c3f20/4550/4630]

// ============================================================================
// FUN_71037c3f20 — FixedString<512>::assign from null-terminated string
// Address: 0x71037c3f20 (240 bytes)
// [derived: Ghidra 13.0.4 decompilation]
// Copies src char-by-char into data[], tracks length at +0x202.
// Throws std::out_of_range if strlen(src) > 512 or length exceeds 512 during copy.
// Returns pointer to self.
// ============================================================================
extern "C" char* FUN_71037c3f20_37c3f20(char* self, const char* src) {
    u64 slen = strlen(src);
    if (slen > 512) {
        throw std::out_of_range("FixedString<>: size is over NUM_CHAR");
    }
    u16* len_ptr = reinterpret_cast<u16*>(self + 0x202);
    *len_ptr = 0;
    if (slen == 0) {
        *(self) = '\0';
        return self;
    }
    // [NX divergence: NX Clang emits ldrb w9,[x20],#1 (post-index),
    //  upstream Clang 8.0.0 emits ldrb w9,[x20] + add x20,x20,#1]
    // [NX divergence: NX Clang emits and x8,x8,#0xffff before strb,
    //  upstream Clang 8.0.0 omits this (ldrh already zero-extends)]
    u64 idx = 0;
    do {
        char c = *src++;
        *len_ptr = (u16)(idx + 1);
        self[(u16)idx] = c;
        idx = (u64)*len_ptr;
        if (idx > 512) {
            throw std::out_of_range("FixedString<>: size is over NUM_CHAR");
        }
        slen--;
    } while (slen != 0);
    self[idx] = '\0';
    return self;
}

// ============================================================================
// FUN_71037c4550 — FixedString<512>::assign from buffer with explicit length
// Address: 0x71037c4550 (224 bytes)
// [derived: Ghidra 13.0.4 decompilation]
// Same as above but takes explicit length instead of strlen.
// ============================================================================
extern "C" void FUN_71037c4550_37c4550(char* self, const u8* src, u64 len) {
    if (len > 512) {
        throw std::out_of_range("FixedString<>: size is over NUM_CHAR");
    }
    u16* len_ptr = (u16*)(self + 0x202);
    *len_ptr = 0;
    u64 idx = 0;
    if (len != 0) {
        do {
            u8 c = *src;
            *len_ptr = (u16)(idx + 1);
            self[idx] = (char)c;
            idx = (u64)*len_ptr;
            if (idx > 512) {
                throw std::out_of_range("FixedString<>: size is over NUM_CHAR");
            }
            len--;
            src++;
        } while (len != 0);
    }
    self[idx] = '\0';
}

// ============================================================================
// FUN_71037c4630 — FixedString<512>::append
// Address: 0x71037c4630 (672 bytes)
// [derived: Ghidra 13.0.4 decompilation]
// Appends src to current content. Pre-validates total length.
// No per-char overflow check (pre-validated).
// Loop unrolled by compiler (2 chars per iteration).
// ============================================================================
extern "C" char* FUN_71037c4630_37c4630(char* self, const char* src) {
    u64 slen = strlen(src);
    u16* len_ptr = (u16*)(self + 0x202);
    u64 cur = (u64)*len_ptr;
    if (slen + cur > 512) {
        throw std::out_of_range("FixedString append : OutOfRange");
    }
    if (slen != 0) {
        for (u64 i = 0; i < slen; i++) {
            u16 pos = *len_ptr;
            *len_ptr = pos + 1;
            self[pos] = src[i];
        }
    }
    u64 final_len = (u64)*len_ptr;
    self[final_len] = '\0';
    return self;
}
