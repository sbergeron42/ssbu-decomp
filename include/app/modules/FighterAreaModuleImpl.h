#pragma once

#include "types.h"

namespace app {

struct FighterAreaModuleData {
    uint8_t pad[0x2a0];
    uint8_t jostle_enable;        // +0x2a0
    uint8_t jostle_enable_xy;     // +0x2a1
    uint8_t pad2[2];
    float jostle_area_x;          // +0x2a4
    float jostle_area_y;          // +0x2a8
    float jostle_area_width;      // +0x2ac
    float jostle_area_height;     // +0x2b0
};

struct BattleObjectModuleAccessor;

namespace lua_bind {
// All function names derived from .dynsym lua_bind::FighterAreaModuleImpl__*_impl dispatcher analysis.

void FighterAreaModuleImpl__enable_fix_jostle_area_impl(BattleObjectModuleAccessor* accessor, float x, float y);
void FighterAreaModuleImpl__enable_fix_jostle_area_xy_impl(BattleObjectModuleAccessor* accessor, float x, float y, float w, float h);
void FighterAreaModuleImpl__disable_fix_jostle_area_impl(BattleObjectModuleAccessor* accessor);

} // namespace lua_bind
} // namespace app
