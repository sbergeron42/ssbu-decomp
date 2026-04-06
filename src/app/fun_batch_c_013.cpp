// Batch C - 013: KineticModule energy flag operations (continued from _012)
// Functions: 29 — Same BattleObject → accessor → KineticModule → get_energy pattern.
// Includes disable/clear variants and vtable dispatch (clear_speed +0x48, clear_rot_speed +0x50).
// Final function FUN_71026515dc uses a different pattern (not KineticModule).

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/KineticModule.h"

#define VT(m) (*reinterpret_cast<void***>(m))

extern "C" void FUN_71036821e0();

// 0x710221c660
// KineticModule: disable energy 0
u32 FUN_710221c660(s64 param_1)
{
    // param_1-8 → BattleObject, +0x1a0 → accessor [derived: BattleObject layout in .dynsym ctors]
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    // +0x68 → item_kinetic_module [derived: KineticModule__*_impl (.dynsym) loads from accessor+0x68]
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    // vtable+0x60 → get_energy [derived: KineticModule__get_energy_impl at 0x7102043970]
    app::KineticEnergy *energy = kinetic->get_energy(0);
    // +0x30 → enabled [derived: KineticEnergy enable_impl/unable_impl at 0x71020f6560/0x71020f6570]
    energy->enabled = 0;
    return 0;
}

// 0x710221c740
// KineticModule: clear energy[0] field_0x31
u32 FUN_710221c740(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0);
    // +0x31 → field_0x31_u8 [inferred: set/cleared alongside enabled in 40+ functions, likely update flag]
    energy->field_0x31_u8 = 0;
    return 0;
}

// 0x710221c930
// KineticModule: clear_rot_speed on energy[0]
u32 FUN_710221c930(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    // vtable+0x60 → get_energy, returns KineticEnergy*
    app::KineticEnergy *energy = kinetic->get_energy(0);
    // vtable+0x50 → clear_rot_speed [derived: KineticEnergy__clear_rot_speed_impl at 0x71020f64f0]
    energy->clear_rot_speed();
    return 0;
}

// 0x710221e8a0
// KineticModule: clear_speed on energy[1]
u32 FUN_710221e8a0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(1);
    // vtable+0x48 → clear_speed [derived: KineticEnergy__clear_speed_impl at 0x71020f64e0]
    energy->clear_speed();
    return 0;
}

// 0x7102222120
// KineticModule: disable energy 3
u32 FUN_7102222120(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(3);
    energy->enabled = 0;
    return 0;
}

// 0x7102223f20
// KineticModule: disable energy 4
u32 FUN_7102223f20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(4);
    energy->enabled = 0;
    return 0;
}

// 0x7102225b20
// KineticModule: disable energy 5
u32 FUN_7102225b20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(5);
    energy->enabled = 0;
    return 0;
}

// 0x7102225c00
// KineticModule: clear energy[5] field_0x31
u32 FUN_7102225c00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(5);
    energy->field_0x31_u8 = 0;
    return 0;
}

// 0x7102225df0
// KineticModule: clear_rot_speed on energy[5]
u32 FUN_7102225df0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(5);
    energy->clear_rot_speed();
    return 0;
}

// 0x7102227c40
// KineticModule: disable energy 6
u32 FUN_7102227c40(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(6);
    energy->enabled = 0;
    return 0;
}

// 0x7102227d60
// KineticModule: clear_speed on energy[6]
u32 FUN_7102227d60(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(6);
    energy->clear_speed();
    return 0;
}

// 0x7102229de0
// KineticModule: disable energy 7
u32 FUN_7102229de0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(7);
    energy->enabled = 0;
    return 0;
}

// 0x7102229f00
// KineticModule: clear_speed on energy[7]
u32 FUN_7102229f00(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(7);
    energy->clear_speed();
    return 0;
}

// 0x710222be20
// KineticModule: disable energy 9
u32 FUN_710222be20(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(9);
    energy->enabled = 0;
    return 0;
}

// 0x710222bf40
// KineticModule: clear_speed on energy[9]
u32 FUN_710222bf40(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(9);
    energy->clear_speed();
    return 0;
}

// 0x710222cd40
// KineticModule: disable energy 0xA
u32 FUN_710222cd40(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xa);
    energy->enabled = 0;
    return 0;
}

// 0x710222ce60
// KineticModule: clear_speed on energy[0xA]
u32 FUN_710222ce60(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xa);
    energy->clear_speed();
    return 0;
}

// 0x710222dc60
// KineticModule: disable energy 8
u32 FUN_710222dc60(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(8);
    energy->enabled = 0;
    return 0;
}

// 0x710222dd80
// KineticModule: clear_speed on energy[8]
u32 FUN_710222dd80(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(8);
    energy->clear_speed();
    return 0;
}

// 0x710222fad0
// KineticModule: disable energy 0xB
u32 FUN_710222fad0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xb);
    energy->enabled = 0;
    return 0;
}

// 0x710222fbb0
// KineticModule: clear energy[0xB] field_0x31
u32 FUN_710222fbb0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xb);
    energy->field_0x31_u8 = 0;
    return 0;
}

// 0x7102230c80
// KineticModule: disable energy 0xC
u32 FUN_7102230c80(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xc);
    energy->enabled = 0;
    return 0;
}

// 0x7102230da0
// KineticModule: clear_speed on energy[0xC]
u32 FUN_7102230da0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xc);
    energy->clear_speed();
    return 0;
}

// 0x7102233bb0
// KineticModule: enable energy 0xD
u32 FUN_7102233bb0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xd);
    energy->enabled = 1;
    return 0;
}

// 0x7102233bf0
// KineticModule: disable energy 0xD
u32 FUN_7102233bf0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xd);
    energy->enabled = 0;
    return 0;
}

// 0x7102233c90
// KineticModule: set energy[0xD] field_0x31
u32 FUN_7102233c90(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xd);
    energy->field_0x31_u8 = 1;
    return 0;
}

// 0x7102233cd0
// KineticModule: clear energy[0xD] field_0x31
u32 FUN_7102233cd0(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xd);
    energy->field_0x31_u8 = 0;
    return 0;
}

// 0x7102233d10
// KineticModule: clear_speed on energy[0xD]
u32 FUN_7102233d10(s64 param_1)
{
    app::BattleObjectModuleAccessor *acc =
        reinterpret_cast<app::BattleObjectModuleAccessor*>(
            *(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0));
    app::KineticModule *kinetic = static_cast<app::KineticModule*>(acc->item_kinetic_module);
    app::KineticEnergy *energy = kinetic->get_energy(0xd);
    energy->clear_speed();
    return 0;
}

// 0x71026515dc
// Unknown dispatch: vtable+0x38 on *(param_1+8), then tail into FUN_71036821e0
void FUN_71026515dc(s64 param_1)
{
    // param_1+8 → unknown object pointer [unknown: no BattleObject/accessor pattern]
    // vtable+0x38 → unknown method [unknown]
    (**(void (**)(void))(**(s64 **)(param_1 + 8) + 0x38))();
    FUN_71036821e0();
}
