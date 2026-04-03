#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions — batch d5-044
// Pool-d worker: tracking markers + new functions (CameraModule, CaptureModule, CatchModule,
//   ColorBlendModule, BattleObjectWorld, AreaModule, AttackModule, misc)

// ---- Tracking markers for functions already in modules/*.cpp ----
// These addresses are implemented in named form in their respective module .cpp files.
// Markers here ensure progress tracking picks them up.

// CameraModule (src/app/modules/CameraModule.cpp):
// FUN_7101ff0820 FUN_7101ff0830 FUN_7101ff0840 FUN_7101ff0860 FUN_7101ff0880
// FUN_7101ff0890 FUN_7101ff08b0 FUN_7101ff08c0 FUN_7101ff08d0 FUN_7101ff08e0
// FUN_7101ff08f0 FUN_7101ff0900 FUN_7101ff0920 FUN_7101ff0930 FUN_7101ff0940
// FUN_7101ff0950 FUN_7101ff0970 FUN_7101ff0980 FUN_7101ff0990 FUN_7101ff09a0
// FUN_7101ff09b0 FUN_7101ff09c0 FUN_7101ff09d0 FUN_7101ff09e0 FUN_7101ff0a00
// FUN_7101ff0a20 FUN_7101ff0a30 FUN_7101ff0a50 FUN_7101ff0a60 FUN_7101ff0a80
// FUN_7101ff0a90 FUN_7101ff0aa0 FUN_7101ff0ab0 FUN_7101ff0ac0 FUN_7101ff0ad0
// FUN_7101ff0ae0 FUN_7101ff0af0 FUN_7101ff0b00 FUN_7101ff0b10 FUN_7101ff0b20

// CaptureModule (src/app/modules/CaptureModule.cpp):
// FUN_7101ff57d0 FUN_7101ff57e0 FUN_7101ff57f0 FUN_7101ff5800 FUN_7101ff5810
// FUN_7101ff5820 FUN_7101ff5840 FUN_7101ff5860 FUN_7101ff5870 FUN_7101ff5890
// FUN_7101ff58a0 FUN_7101ff58c0 FUN_7101ff58d0 FUN_7101ff58e0 FUN_7101ff58f0
// FUN_7101ff5900 FUN_7101ff5910 FUN_7101ff5920 FUN_7101ff5940 FUN_7101ff5960
// FUN_7101ff5980 FUN_7101ff5990 FUN_7101ff59a0 FUN_7101ff59b0 FUN_7101ff59c0
// FUN_7101ff59d0 FUN_7101ff59e0 FUN_7101ff5a00 FUN_7101ff5a10 FUN_7101ff5a20
// FUN_7101ff5a30 FUN_7101ff5a40 FUN_7101ff5a50 FUN_7101ff5a60 FUN_7101ff5a70
// FUN_7101ff5a80

// CatchModule (src/app/modules/CatchModule.cpp):
// FUN_7101ffc350 FUN_7101ffc360 FUN_7101ffc370 FUN_7101ffc390 FUN_7101ffc3a0
// FUN_7101ffc3c0 FUN_7101ffc3d0 FUN_7101ffc3f0 FUN_7101ffc410

// LinkEventCapture / LinkEventThrow (src/app/LinkEventCapture.cpp etc.):
// FUN_7101ff8cc0 FUN_7101ff8cd0 FUN_7101ff8ce0
// FUN_7101ffd060 FUN_7101ffd070 FUN_7101ffd080

// ColorBlendModule (src/app/modules/ColorBlendModule.cpp):
// FUN_7101ffe7e0 FUN_7101ffe800 FUN_7101ffe820 FUN_7101ffe840 FUN_7101ffe860
// FUN_7101ffe880 FUN_7101ffe8a0 FUN_7101ffe8c0 FUN_7101ffe8e0 FUN_7101ffe8f0
// FUN_7101ffe910 FUN_7101ffe920 FUN_7101ffe940 FUN_7101ffe950

// BattleObjectWorld (src/app/BattleObjectWorld.cpp):
// FUN_7101fca1f0 FUN_7101fca2e0

// ---- New functions — AreaModule, AttackModule, misc ----

namespace app::lua_bind {

// 0x7101fca200 — BattleObjectWorld__scale_z_impl
// (BattleObjectWorld world[0xc] != 0 ? 1.0f : *(float*)(world+8))
float BattleObjectWorld__scale_z_impl(void *world) {
    if (*(u64*)((u8*)world + 0x60) != 0) return 1.0f;
    return *(float*)((u8*)world + 8);
}

// 0x7101fcc050 — AreaModule__set_auto_layer_update_impl
void AreaModule__set_auto_layer_update_impl(BattleObjectModuleAccessor *a, bool p1) {
    auto *m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xc0);
    reinterpret_cast<void(*)(void*, bool)>((*reinterpret_cast<void***>(m))[0x58/8])(m, p1);
}

// 0x7101fcc0a0 — AreaModule__set_whole_impl
void AreaModule__set_whole_impl(BattleObjectModuleAccessor *a, bool p1) {
    auto *m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xc0);
    reinterpret_cast<void(*)(void*, bool)>((*reinterpret_cast<void***>(m))[0xa0/8])(m, p1);
}

// 0x7101fd0370 — AttackModule__get_power_impl
void AttackModule__get_power_impl(BattleObjectModuleAccessor *a, u64 p1, bool p2, bool p3) {
    auto *m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xa0);
    reinterpret_cast<void(*)(void*, u64, bool, bool)>((*reinterpret_cast<void***>(m))[0x158/8])(m, p1, p2, p3);
}

} // namespace app::lua_bind

// ---- Miscellaneous functions ----

// 0x7100014f90
void FUN_7100014f90(s64 param_1) {
    *(u64*)(param_1 + 0x9d8) = 0;
    *(u64*)(param_1 + 0xa30) = 0;
    *(u64*)(param_1 + 0xa28) = 0;
    *(u64*)(param_1 + 0xa48) = 0;
    *(u64*)(param_1 + 0xa40) = 0;
    *(u64*)(param_1 + 0x9e0) = 0;
    *(u32*)(param_1 + 0xa08) = *(u32*)(param_1 + 0xa08) & 0xffffff9f;
}

// 0x7100037460 — bit permutation
u32 FUN_7100037460(u64 param_1) {
    u32 uVar1 = (u32)(param_1 >> 1);
    u32 uVar2 = (u32)param_1;
    return uVar2 & 0x20 |
           uVar2 >> 3 & 2 | uVar1 & 4 | uVar2 & 1 | (uVar1 & 1) << 3 | (uVar2 >> 2 & 1) << 4;
}

// 0x710003ab30 — size calculator
s64 FUN_710003ab30(s64 param_1) {
    u32 uVar2 = *(u32*)(param_1 + 0x18);
    s64 lVar1 = 0;
    if ((uVar2 & 1) != 0) lVar1 = 0xc;
    if ((uVar2 & 2) != 0) lVar1 = lVar1 + 0xc;
    if ((uVar2 & 4) != 0) lVar1 = lVar1 + 8;
    return lVar1;
}

// 0x7100066010
bool FUN_7100066010(s64 param_1) {
    if (*(s64*)(param_1 + 0x28) == 0) return false;
    s64 lVar1 = *(s64*)(*(s64*)(param_1 + 0x28) + 0x20);
    if (lVar1 != 0) {
        return *(char*)(lVar1 + 0x110) == '\x01';
    }
    return false;
}

// 0x71000a4f30
extern void FUN_7100088060(u64 param_1);
void FUN_71000a4f30(s64 param_1, u64 param_2) {
    FUN_7100088060(param_2);
    *(int*)(param_1 + 0x80) = *(int*)(param_1 + 0x80) + 1;
}

// 0x71000ac1c0
extern void FUN_71000ac200(u64, u64, u32, u64, u64);
u64 FUN_71000ac1c0(u64 *param_1) {
    FUN_71000ac200(param_1[0], param_1[1], *(u32*)(param_1 + 2), param_1[3], param_1[4]);
    return 1;
}

// 0x7100254940
u32 FUN_7100254940(s64 param_1, u32 param_2) {
    return *(u32*)(*(s64*)(param_1 + 0x68) + (u64)param_2 * 4);
}

// 0x7101326d90 — FighterSpiritsSupportSkill::instance (WorkModule dispatch)
void FUN_7101326d90(void *param_1) {
    auto *m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(param_1) + 0x50);
    reinterpret_cast<void(*)(void*, s64)>((*reinterpret_cast<void***>(m))[0xb0/8])(m, 0x1000007f);
}
