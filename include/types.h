#pragma once

// Basic types for AArch64 cross-compilation (no stdlib)
using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using s8  = signed char;
using s16 = signed short;
using s32 = signed int;
using s64 = signed long long;
using f32 = float;
using f64 = double;

using usize = u64;
using ssize = s64;

// nullptr is a keyword, no header needed
// bool is a keyword, no header needed
