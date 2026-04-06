#pragma once
#include "types.h"

// FixedString<N> — fixed-capacity string used throughout resource service
// [derived: error string "FixedString<>: size is over NUM_CHAR" at FUN_71037c3f20, FUN_71037c4550]
// [derived: error string "FixedString append : OutOfRange" at FUN_71037c4630]
// [derived: Ghidra 13.0.4 shows char[N+2] + u16 length layout]
// Layout: char data[N+2] at +0x000, u16 length at offset (N+2)
// Total size: N + 4 bytes (N+2 data + 2 length)

extern "C" unsigned long strlen(const char*);

namespace resource {

template<int NUM_CHAR>
struct FixedString {
    char data[NUM_CHAR + 2];  // +0x000 — string data + null terminator + pad
    u16 length;               // +(NUM_CHAR+2) — current string length

    // FUN_71037c3f20 — assign from null-terminated string
    // [derived: Ghidra 13.0.4 decompilation, 240 bytes]
    FixedString* assign_str(const char* src);

    // FUN_71037c4550 — assign from buffer with explicit length
    // [derived: Ghidra 13.0.4 decompilation, 224 bytes]
    void assign_buf(const u8* src, u64 len);

    // FUN_71037c4630 — append null-terminated string
    // [derived: Ghidra 13.0.4 decompilation, 672 bytes]
    FixedString* append(const char* src);
};

} // namespace resource
