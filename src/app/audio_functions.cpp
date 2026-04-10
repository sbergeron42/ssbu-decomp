#include "types.h"

// Audio/BGM/SE functions -- pool-c assignment

extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;  // StageManager/ParamAccessor2 singleton
extern "C" __attribute__((visibility("hidden"))) void* DAT_71053299d8;  // StageManager indirect ptr

extern "C" void FUN_7102608770(void*);
extern "C" void FUN_71015c1770(void*, u32, u64, u32, void*, u64, u32);

namespace app::shiokarazu {

// 710164bd50 (16B) -- invalid_bgm_handle: sentinel for "no bgm handle"
u32 invalid_bgm_handle(void) { return 0xffffffff; }

} // namespace app::shiokarazu

namespace app::kiiladarzmanager {

// 71016538d0 (16B) -- stop_stage_sound: delegate via StageManager indirect
void stop_stage_sound(void) {
    FUN_7102608770(*reinterpret_cast<void**>(DAT_71053299d8));
}

} // namespace app::kiiladarzmanager

namespace app::buddybomb {

// 71016595c0 (32B) -- bound_se_speed_less: read float field from nested param accessor
float bound_se_speed_less(void) {
    u8* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_71052bb3b0) + 0x12d0);
    return *reinterpret_cast<float*>(inner + 0x2b0);
}

} // namespace app::buddybomb

namespace app::item {

// 71015c1a10 (32B) -- request cut-in without BGM volume change; passes fixed Hash40 + false
void request_cut_in_from_param_with_target_no_bgm_volume_change(
        void* p1, u32 p2, u64 p3, u32 p4, void* p5) {
    FUN_71015c1770(p1, p2, p3, p4, p5, 0x7fb997a80ULL, 0u);
}

} // namespace app::item
