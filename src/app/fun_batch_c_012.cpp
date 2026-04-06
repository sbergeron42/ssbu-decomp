// Batch C - 012: KineticModule energy flag operations
// All 40 functions: navigate BattleObject → accessor → item_kinetic_module,
// call get_energy(index) via vtable+0x60, then set/clear flags on KineticEnergy entry.
// One function (FUN_7102222240) dispatches clear_speed via energy vtable+0x48.

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

// 0x7102208730
// KineticModule: disable energy 0xC
u32 FUN_7102208730(s64 param_1)
{
    // param_1-8 → BattleObject, +0x1a0 → accessor [derived: BattleObject layout in .dynsym ctors]
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    // +0x68 → item_kinetic_module [derived: KineticModule__*_impl (.dynsym) loads from accessor+0x68]
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    // vtable+0x60 → get_energy [derived: KineticModule__get_energy_impl at 0x7102043970]
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x30 → enabled [derived: KineticEnergy struct in KineticEnergy.cpp, field at +0x30]
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102208770
// KineticModule: disable energy 0xD
u32 FUN_7102208770(s64 param_1)
{
    // param_1-8 → BattleObject, +0x1a0 → accessor [derived: .dynsym ctors]
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    // +0x68 → item_kinetic_module [derived: KineticModule__*_impl .dynsym]
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    // vtable+0x60 → get_energy [derived: get_energy_impl 0x7102043970]
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xd);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102208810
// KineticModule: enable energy 0xC
u32 FUN_7102208810(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102208850
// KineticModule: enable energy 0xD
u32 FUN_7102208850(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xd);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710221c620
// KineticModule: enable energy 0
u32 FUN_710221c620(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    // note: index passed as s32 (not s64) for energy 0
    s64 entry = reinterpret_cast<s64 (*)(s64*, s32)>(VT(kinetic)[0x60/8])(kinetic, 0);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710221c700
// KineticModule: set energy[0] field_0x31
u32 FUN_710221c700(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    // note: index passed as s32 for energy 0
    s64 entry = reinterpret_cast<s64 (*)(s64*, s32)>(VT(kinetic)[0x60/8])(kinetic, 0);
    // +0x31 → field_0x31_u8 [inferred: set/cleared alongside enabled in 40+ functions, likely update flag]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710221e780
// KineticModule: disable energy 1
u32 FUN_710221e780(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 1);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x710221e860
// KineticModule: clear energy[1] field_0x31
u32 FUN_710221e860(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 1);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x71022208e0
// KineticModule: enable energy 2
u32 FUN_71022208e0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 2);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x71022209c0
// KineticModule: set energy[2] field_0x31
u32 FUN_71022209c0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 2);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102220a00
// KineticModule: clear energy[2] field_0x31
u32 FUN_7102220a00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 2);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x71022220e0
// KineticModule: enable energy 3
u32 FUN_71022220e0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 3);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x71022221c0
// KineticModule: set energy[3] field_0x31
u32 FUN_71022221c0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 3);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102222200
// KineticModule: clear energy[3] field_0x31
u32 FUN_7102222200(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 3);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102222240
// KineticModule: clear_speed on energy[3]
u32 FUN_7102222240(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    // vtable+0x60 → get_energy, returns KineticEnergy*
    s64 *energy = (s64 *)reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 3);
    // vtable+0x48 → clear_speed [derived: KineticEnergy__clear_speed_impl at 0x71020f64e0]
    reinterpret_cast<void(*)()>(VT(energy)[0x48/8])();
    return 0;
}

// 0x7102223ee0
// KineticModule: enable energy 4
u32 FUN_7102223ee0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 4);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102223fc0
// KineticModule: set energy[4] field_0x31
u32 FUN_7102223fc0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 4);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102224000
// KineticModule: clear energy[4] field_0x31
u32 FUN_7102224000(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 4);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102225ae0
// KineticModule: enable energy 5
u32 FUN_7102225ae0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 5);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102225bc0
// KineticModule: set energy[5] field_0x31
u32 FUN_7102225bc0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 5);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102227c00
// KineticModule: enable energy 6
u32 FUN_7102227c00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 6);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102227ce0
// KineticModule: set energy[6] field_0x31
u32 FUN_7102227ce0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 6);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102227d20
// KineticModule: clear energy[6] field_0x31
u32 FUN_7102227d20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 6);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x7102229da0
// KineticModule: enable energy 7
u32 FUN_7102229da0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 7);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102229e80
// KineticModule: set energy[7] field_0x31
u32 FUN_7102229e80(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 7);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102229ec0
// KineticModule: clear energy[7] field_0x31
u32 FUN_7102229ec0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 7);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222bde0
// KineticModule: enable energy 9
u32 FUN_710222bde0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 9);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222bec0
// KineticModule: set energy[9] field_0x31
u32 FUN_710222bec0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 9);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222bf00
// KineticModule: clear energy[9] field_0x31
u32 FUN_710222bf00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 9);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222cd00
// KineticModule: enable energy 0xA
u32 FUN_710222cd00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xa);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222cde0
// KineticModule: set energy[0xA] field_0x31
u32 FUN_710222cde0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xa);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222ce20
// KineticModule: clear energy[0xA] field_0x31
u32 FUN_710222ce20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xa);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222dc20
// KineticModule: enable energy 8
u32 FUN_710222dc20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 8);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222dd00
// KineticModule: set energy[8] field_0x31
u32 FUN_710222dd00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 8);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x710222dd40
// KineticModule: clear energy[8] field_0x31
u32 FUN_710222dd40(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 8);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}

// 0x710222fa90
// KineticModule: enable energy 0xB
u32 FUN_710222fa90(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xb);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x710222fb70
// KineticModule: set energy[0xB] field_0x31
u32 FUN_710222fb70(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xb);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102230c40
// KineticModule: enable energy 0xC
u32 FUN_7102230c40(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x30 → enabled [derived: KineticEnergy +0x30]
    *(u8 *)(entry + 0x30) = 1;
    return 0;
}

// 0x7102230d20
// KineticModule: set energy[0xC] field_0x31
u32 FUN_7102230d20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 1;
    return 0;
}

// 0x7102230d60
// KineticModule: clear energy[0xC] field_0x31
u32 FUN_7102230d60(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    s64 *kinetic = reinterpret_cast<s64*>(acc->item_kinetic_module);
    s64 entry = reinterpret_cast<s64 (*)(s64*, s64)>(VT(kinetic)[0x60/8])(kinetic, 0xc);
    // +0x31 → field_0x31_u8 [inferred: update flag alongside enabled]
    *(u8 *)(entry + 0x31) = 0;
    return 0;
}
