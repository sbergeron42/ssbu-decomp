#include "types.h"

// FighterParamAccessor2 -- character-specific offset lookups
// Most functions are single-instruction `b` tail calls to the underlying implementation.
// Only hit_target_no has inline logic.

struct FighterParamAccessor2;

extern "C" void FUN_7100720f90(void*, s32, s32, s32);
extern "C" void FUN_71007210e0(void*, s32, s32);
extern "C" void FUN_71007211a0(void*, s32, s32);
extern "C" void FUN_7100721240(void*, s32);
extern "C" void FUN_71007212e0(void*, s32);
extern "C" void FUN_7100721380(void*, s32, s32);
extern "C" void FUN_7100721430(void*, s32);
extern "C" void FUN_71007214d0(void*, s32);

namespace app::lua_bind {

// 71020a8000 -- b external
void FighterParamAccessor2__thrown_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2, s32 p3) {
    FUN_7100720f90(pa, p1, p2, p3);
}

// 71020a8010 -- b external
void FighterParamAccessor2__donkey_thrown_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_71007210e0(pa, p1, p2);
}

// 71020a8020 -- b external
void FighterParamAccessor2__ridley_dragged_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_71007211a0(pa, p1, p2);
}

// 71020a8030 -- b external
void FighterParamAccessor2__diddy_special_s_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_7100721240(pa, p1);
}

// 71020a8040 -- b external
void FighterParamAccessor2__miifighter_suplex_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_71007212e0(pa, p1);
}

// 71020a8050 -- b external
void FighterParamAccessor2__gaogaen_final_offset_impl(FighterParamAccessor2* pa, s32 p1, s32 p2) {
    FUN_7100721380(pa, p1, p2);
}

// 71020a8060 -- b external
void FighterParamAccessor2__demon_command_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_7100721430(pa, p1);
}

// 71020a8070 -- b external
void FighterParamAccessor2__demon_special_lw_offset_impl(FighterParamAccessor2* pa, s32 p1) {
    FUN_71007214d0(pa, p1);
}

} // namespace app::lua_bind
