#pragma once
// Minimal nn types — replaces the vapours-dependent version
#include <stdint.h>
#include <stddef.h>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using f32 = float;
using f64 = double;
using size_t = ::size_t;
using u128 = __uint128_t;

namespace nn {
using Result = u32;
}

#define NN_NO_COPY(cls) cls(const cls&) = delete; cls& operator=(const cls&) = delete
using ulong = unsigned long;
namespace std {
template<class T> struct is_trivial { static constexpr bool value = true; };
template<class T> struct is_trivially_destructible { static constexpr bool value = true; };
template<class T> inline constexpr bool is_trivial_v = is_trivial<T>::value;
}
