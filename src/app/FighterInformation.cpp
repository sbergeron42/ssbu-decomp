#include "types.h"

// FighterInformation — operates on FighterInformation* directly
// Pattern: ldr x8,[x0,#0x8] gets internal data, then field reads

struct FighterInformation;

namespace app::lua_bind {

// Simple 3-instruction struct reads (ldr data ptr, ldr/ldrb field, ret)
u8 FighterInformation__fighter_color_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x51];
}
bool FighterInformation__is_rabbit_cap_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x59];
}
bool FighterInformation__is_reflector_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5a];
}
bool FighterInformation__is_superleaf_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5b];
}
bool FighterInformation__is_rocketbelt_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5c];
}
bool FighterInformation__is_screw_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5d];
}
bool FighterInformation__is_backshield_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5e];
}
bool FighterInformation__is_operation_cpu_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5f];
}
u32 FighterInformation__stock_count_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<u32*>(data + 0xd8);
}
u8 FighterInformation__fighter_category_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x3ac];
}

} // namespace app::lua_bind
