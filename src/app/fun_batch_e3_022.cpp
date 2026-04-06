#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

// MotionModule lua_bind thunks — 0x710205ce20..0x710205d200
// All functions: accessor->motion_module (+0x88) -> vtable dispatch, 4/5-insn tail calls
// +0x88 -> motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
// Vtable slot indices [inferred: disassembly vtable offset / 8]

// ---- Module offset 0x88 (MotionModule) — continued -------------------------

// 0x710205ce20 (16 bytes) — MotionModule vtable[0x280/8] dispatch
u64 FUN_710205ce20(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64)>(VT(mod)[0x280 / 8])(mod, p1);
}

// 0x710205ce30 (16 bytes) — MotionModule vtable[0x288/8] dispatch
u64 FUN_710205ce30(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64)>(VT(mod)[0x288 / 8])(mod, p1);
}

// 0x710205ce40 (16 bytes) — MotionModule vtable[0x298/8] dispatch
u64 FUN_710205ce40(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x298 / 8])(mod);
}

// 0x710205ce50 (16 bytes) — MotionModule vtable[0x2a0/8] dispatch
float FUN_710205ce50(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x2a0 / 8])(mod);
}

// 0x710205ce60 (16 bytes) — MotionModule vtable[0x2b0/8] dispatch
u64 FUN_710205ce60(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x2b0 / 8])(mod);
}

// 0x710205ce70 (16 bytes) — MotionModule vtable[0x2b8/8] dispatch
void FUN_710205ce70(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2, u64 p3) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64, u64, u64)>(VT(mod)[0x2b8 / 8])(mod, p1, p2, p3);
}

// 0x710205ce80 (16 bytes) — MotionModule vtable[0x2c0/8] dispatch
void FUN_710205ce80(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**)>(VT(mod)[0x2c0 / 8])(mod);
}

// 0x710205ce90 (16 bytes) — MotionModule vtable[0x2d0/8] dispatch
u64 FUN_710205ce90(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64, u64)>(VT(mod)[0x2d0 / 8])(mod, p1, p2);
}

// 0x710205cea0 (16 bytes) — MotionModule vtable[0x2d8/8] dispatch
u64 FUN_710205cea0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64)>(VT(mod)[0x2d8 / 8])(mod, p1);
}

// 0x710205ceb0 (16 bytes) — MotionModule vtable[0x2e0/8] dispatch
float FUN_710205ceb0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x2e0 / 8])(mod);
}

// 0x710205cec0 (16 bytes) — MotionModule vtable[0x2e8/8] dispatch
u32 FUN_710205cec0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x2e8 / 8])(mod);
}

// 0x710205ced0 (16 bytes) — MotionModule vtable[0x2f0/8] dispatch
u64 FUN_710205ced0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x2f0 / 8])(mod);
}

// 0x710205cee0 (16 bytes) — MotionModule vtable[0x2f8/8] dispatch
u32 FUN_710205cee0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**, u64)>(VT(mod)[0x2f8 / 8])(mod, p1);
}

// 0x710205cef0 (16 bytes) — MotionModule vtable[0x300/8] dispatch
u32 FUN_710205cef0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**, u64)>(VT(mod)[0x300 / 8])(mod, p1);
}

// 0x710205cf00 (16 bytes) — MotionModule vtable[0x308/8] dispatch
u32 FUN_710205cf00(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x308 / 8])(mod);
}

// 0x710205cf10 (16 bytes) — MotionModule vtable[0x310/8] dispatch
u32 FUN_710205cf10(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x310 / 8])(mod);
}

// 0x710205cf20 (16 bytes) — MotionModule vtable[0x318/8] dispatch
u64 FUN_710205cf20(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64, u64)>(VT(mod)[0x318 / 8])(mod, p1, p2);
}

// 0x710205cf60 (20 bytes) — MotionModule vtable[0x328/8] dispatch, p2=bool masked
void FUN_710205cf60(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64, u32)>(VT(mod)[0x328 / 8])(mod, p1, p2 & 1);
}

// 0x710205cf80 (16 bytes) — MotionModule vtable[0x338/8] dispatch
void FUN_710205cf80(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x338 / 8])(mod, p1);
}

// 0x710205cf90 (16 bytes) — MotionModule vtable[0x340/8] dispatch
u64 FUN_710205cf90(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64)>(VT(mod)[0x340 / 8])(mod, p1);
}

// 0x710205cfa0 (16 bytes) — MotionModule vtable[0x348/8] dispatch
u32 FUN_710205cfa0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**, u64)>(VT(mod)[0x348 / 8])(mod, p1);
}

// 0x710205cfb0 (16 bytes) — MotionModule vtable[0x350/8] dispatch
float FUN_710205cfb0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**, u64)>(VT(mod)[0x350 / 8])(mod, p1);
}

// 0x710205cfc0 (16 bytes) — MotionModule vtable[0x358/8] dispatch
void FUN_710205cfc0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x358 / 8])(mod, p1);
}

// 0x710205cfd0 (16 bytes) — MotionModule vtable[0x360/8] dispatch
float FUN_710205cfd0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**, u64)>(VT(mod)[0x360 / 8])(mod, p1);
}

// 0x710205cfe0 (16 bytes) — MotionModule vtable[0x368/8] dispatch
float FUN_710205cfe0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**, u64)>(VT(mod)[0x368 / 8])(mod, p1);
}

// 0x710205cff0 (16 bytes) — MotionModule vtable[0x370/8] dispatch
float FUN_710205cff0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**, u64)>(VT(mod)[0x370 / 8])(mod, p1);
}

// 0x710205d000 (20 bytes) — MotionModule vtable[0x378/8] dispatch, p2=bool masked
void FUN_710205d000(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64, u32)>(VT(mod)[0x378 / 8])(mod, p1, p2 & 1);
}

// 0x710205d020 (20 bytes) — MotionModule vtable[0x380/8] dispatch, p2=bool masked
void FUN_710205d020(app::BattleObjectModuleAccessor* acc, u64 p1, u32 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64, u32)>(VT(mod)[0x380 / 8])(mod, p1, p2 & 1);
}

// 0x710205d040 (16 bytes) — MotionModule vtable[0x388/8] dispatch
u32 FUN_710205d040(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**, u64)>(VT(mod)[0x388 / 8])(mod, p1);
}

// 0x710205d050 (16 bytes) — MotionModule vtable[0x390/8] dispatch
u32 FUN_710205d050(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x390 / 8])(mod);
}

// 0x710205d080 (20 bytes) — MotionModule vtable[0x3a8/8] dispatch, p1=bool masked
void FUN_710205d080(app::BattleObjectModuleAccessor* acc, u32 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u32)>(VT(mod)[0x3a8 / 8])(mod, p1 & 1);
}

// 0x710205d0a0 (16 bytes) — MotionModule vtable[0x3b0/8] dispatch
void FUN_710205d0a0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x3b0 / 8])(mod, p1);
}

// 0x710205d0b0 (16 bytes) — MotionModule vtable[0x3b8/8] dispatch
void FUN_710205d0b0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x3b8 / 8])(mod, p1);
}

// 0x710205d0c0 (16 bytes) — MotionModule vtable[0x3c0/8] dispatch
void FUN_710205d0c0(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64, u64)>(VT(mod)[0x3c0 / 8])(mod, p1, p2);
}

// 0x710205d0d0 (16 bytes) — MotionModule vtable[0x3c8/8] dispatch
u64 FUN_710205d0d0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64)>(VT(mod)[0x3c8 / 8])(mod, p1);
}

// 0x710205d120 (16 bytes) — MotionModule vtable[0x3f0/8] dispatch
float FUN_710205d120(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x3f0 / 8])(mod);
}

// 0x710205d130 (16 bytes) — MotionModule vtable[0x3f8/8] dispatch
u32 FUN_710205d130(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x3f8 / 8])(mod);
}

// 0x710205d140 (16 bytes) — MotionModule vtable[0x410/8] dispatch
float FUN_710205d140(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x410 / 8])(mod);
}

// 0x710205d190 (16 bytes) — MotionModule vtable[0x440/8] dispatch
u32 FUN_710205d190(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x440 / 8])(mod);
}

// 0x710205d1a0 (16 bytes) — MotionModule vtable[0x448/8] dispatch
void FUN_710205d1a0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x448 / 8])(mod, p1);
}

// 0x710205d1d0 (16 bytes) — MotionModule vtable[0x470/8] dispatch
u64 FUN_710205d1d0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x470 / 8])(mod);
}

// 0x710205d200 (16 bytes) — MotionModule vtable[0x4a0/8] dispatch
u32 FUN_710205d200(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x4a0 / 8])(mod);
}
