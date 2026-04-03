#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-045
// Pool-d worker: kinetic_energy_* lua wrappers (0x71015d0030-0x71015d1060)
// These are all in the app::kinetic_energy_* namespaces and share a common pattern:
//   plVar1 = *(long **)(*(long *)(*(long *)(param_1 - 8) + 0x1a0) + 0x68)
//   idx is the energy type index passed to vtable[0x60/8]
// Tracking markers for named functions:
// FUN_71015d0030 FUN_71015d0070 FUN_71015d00a0 FUN_71015d0170 FUN_71015d01c0
// FUN_71015d0200 FUN_71015d0230 FUN_71015d02c0 FUN_71015d0310 FUN_71015d0350
// FUN_71015d03f0 FUN_71015d0420 FUN_71015d04f0 FUN_71015d0590 FUN_71015d05d0
// FUN_71015d0670 FUN_71015d06c0 FUN_71015d0700 FUN_71015d07a0 FUN_71015d0870
// FUN_71015d08b0 FUN_71015d0940 FUN_71015d0990 FUN_71015d09d0 FUN_71015d0a70
// FUN_71015d0ab0 FUN_71015d0ae0 FUN_71015d0b70 FUN_71015d0bb0 FUN_71015d0c20
// FUN_71015d0c70 FUN_71015d0d40 FUN_71015d0d80 FUN_71015d0db0 FUN_71015d0e80
// FUN_71015d0ec0 FUN_71015d0f20 FUN_71015d0f60 FUN_71015d0fa0 FUN_71015d0fe0
// FUN_71015d1020 FUN_71015d1060

// Helper macro for the kinetic_energy pattern
#define KE_BASE(p) (*(s64**)(*(s64*)(*(s64*)((u8*)(p) - 8) + 0x1a0) + 0x68))

// enable/unable (idx, 1=enable 0=unable)
// get_speed returns a vec (u64 pair)
// mul_speed calls vtable[0x58/8] with vec param
// clear_speed calls vtable[0x48/8]

namespace app::kinetic_energy_rot {
// 0x71015cffe0 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d0030 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0070 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_rot

namespace app::kinetic_energy_outer {
// 0x71015d00a0 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 1);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0170 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 1);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d01c0 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 1);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0200 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 1);
    *(u8*)(lVar2 + 0x30) = 0;
}
// 0x71015d0f20 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 1);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_outer

namespace app::kinetic_energy_gravity {
// 0x71015d0230 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 2);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d02c0 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 2);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d0310 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 2);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0350 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 2);
    *(u8*)(lVar2 + 0x30) = 0;
}
// 0x71015d0f60 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 2);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_gravity

namespace app::kinetic_energy_ground {
// 0x71015d03f0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 3);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_ground

namespace app::kinetic_energy_control {
// 0x71015d0420 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 4);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d04f0 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 4);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d0590 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 4);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d05d0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 4);
    *(u8*)(lVar2 + 0x30) = 0;
}
// 0x71015d0fa0 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 4);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_control

namespace app::kinetic_energy_control_rot {
// 0x71015d0670 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 5);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d06c0 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 5);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0700 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 5);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_control_rot

namespace app::kinetic_energy_motion {
// 0x71015d07a0 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 6);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0870 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 6);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0fe0 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 6);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_motion

namespace app::kinetic_energy_stop {
// 0x71015d08b0 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 7);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0940 — mul_speed
void mul_speed(void *param_1, void *param_2) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 7);
    reinterpret_cast<void(*)(void*,void*)>((*reinterpret_cast<void***>(plVar1))[0x58/8])(plVar1, param_2);
}
// 0x71015d0990 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 7);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d09d0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 7);
    *(u8*)(lVar2 + 0x30) = 0;
}
// 0x71015d1020 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 7);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_stop

namespace app::kinetic_energy_jostle {
// 0x71015d0a70 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 9);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0ab0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 9);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_jostle

namespace app::kinetic_energy_ground_movement {
// 0x71015d0ae0 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 10);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0b70 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 10);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0bb0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 10);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_ground_movement

namespace app::kinetic_energy_wind {
// 0x71015d0c20 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xb);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
} // namespace app::kinetic_energy_wind

namespace app::kinetic_energy_motion_linked_main {
// 0x71015d0c70 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xc);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0d40 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xc);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0d80 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xc);
    *(u8*)(lVar2 + 0x30) = 0;
}
} // namespace app::kinetic_energy_motion_linked_main

namespace app::kinetic_energy_motion_linked_sub1 {
// 0x71015d0db0 — get_speed
u64 get_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xd);
    return *(u64*)(*reinterpret_cast<void*(*)(s64*)>((*reinterpret_cast<void***>(plVar1))[0x20/8]))(plVar1);
}
// 0x71015d0e80 — enable
void enable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xd);
    *(u8*)(lVar2 + 0x30) = 1;
}
// 0x71015d0ec0 — unable
void unable(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    s64 lVar2 = (*reinterpret_cast<s64(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xd);
    *(u8*)(lVar2 + 0x30) = 0;
}
// 0x71015d1060 — clear_speed
void clear_speed(void *param_1) {
    auto *plVar1 = KE_BASE(param_1);
    plVar1 = (s64*)(*reinterpret_cast<void*(*)(s64*,s64)>((*reinterpret_cast<void***>(plVar1))[0x60/8]))(plVar1, 0xd);
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(plVar1))[0x48/8])(plVar1);
}
} // namespace app::kinetic_energy_motion_linked_sub1
