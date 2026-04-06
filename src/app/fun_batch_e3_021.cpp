#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

// MotionModule lua_bind thunks — 0x710205cb70..0x710205ce10
// All functions: accessor->motion_module (+0x88) -> vtable dispatch, 4/5-insn tail calls
// +0x88 -> motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
// Vtable slot indices [inferred: disassembly vtable offset / 8]

// ---- Module offset 0x88 (MotionModule) -------------------------------------

// 0x710205cb70 (16 bytes) — MotionModule vtable[0xf0/8] dispatch
void FUN_710205cb70(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0xf0 / 8])(mod, p1);
}

// 0x710205cb80 (16 bytes) — MotionModule vtable[0xf8/8] dispatch
void FUN_710205cb80(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0xf8 / 8])(mod, p1);
}

// 0x710205cb90 (16 bytes) — MotionModule vtable[0x100/8] dispatch
void FUN_710205cb90(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0x100 / 8])(mod, p1);
}

// 0x710205cbe0 (16 bytes) — MotionModule vtable[0x118/8] dispatch
float FUN_710205cbe0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x118 / 8])(mod);
}

// 0x710205cbf0 (16 bytes) — MotionModule vtable[0x120/8] dispatch
float FUN_710205cbf0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x120 / 8])(mod);
}

// 0x710205cc00 (16 bytes) — MotionModule vtable[0x128/8] dispatch
u32 FUN_710205cc00(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x128 / 8])(mod);
}

// 0x710205cc10 (16 bytes) — MotionModule vtable[0x130/8] dispatch
u32 FUN_710205cc10(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x130 / 8])(mod);
}

// 0x710205cc20 (16 bytes) — MotionModule vtable[0x138/8] dispatch
u64 FUN_710205cc20(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x138 / 8])(mod);
}

// 0x710205cc30 (16 bytes) — MotionModule vtable[0x140/8] dispatch
float FUN_710205cc30(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x140 / 8])(mod);
}

// 0x710205cc40 (16 bytes) — MotionModule vtable[0x148/8] dispatch
u32 FUN_710205cc40(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x148 / 8])(mod);
}

// 0x710205cc50 (16 bytes) — MotionModule vtable[0x150/8] dispatch
float FUN_710205cc50(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x150 / 8])(mod);
}

// 0x710205cc60 (16 bytes) — MotionModule vtable[0x158/8] dispatch
u64 FUN_710205cc60(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**)>(VT(mod)[0x158 / 8])(mod);
}

// 0x710205cc70 (16 bytes) — MotionModule vtable[0x160/8] dispatch
float FUN_710205cc70(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x160 / 8])(mod);
}

// 0x710205cc80 (16 bytes) — MotionModule vtable[0x168/8] dispatch
float FUN_710205cc80(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x168 / 8])(mod);
}

// 0x710205ccd0 (16 bytes) — MotionModule vtable[0x180/8] dispatch
float FUN_710205ccd0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x180 / 8])(mod);
}

// 0x710205cce0 (16 bytes) — MotionModule vtable[0x188/8] dispatch
float FUN_710205cce0(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**, u64)>(VT(mod)[0x188 / 8])(mod, p1);
}

// 0x710205ccf0 (20 bytes) — MotionModule vtable[0x190/8] dispatch, p1=bool masked
void FUN_710205ccf0(app::BattleObjectModuleAccessor* acc, u32 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u32)>(VT(mod)[0x190 / 8])(mod, p1 & 1);
}

// 0x710205cd10 (16 bytes) — MotionModule vtable[0x198/8] dispatch
float FUN_710205cd10(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<float(*)(void**)>(VT(mod)[0x198 / 8])(mod);
}

// 0x710205cd80 (16 bytes) — MotionModule vtable[0x1c0/8] dispatch
u64 FUN_710205cd80(app::BattleObjectModuleAccessor* acc, u64 p1, u64 p2) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u64(*)(void**, u64, u64)>(VT(mod)[0x1c0 / 8])(mod, p1, p2);
}

// 0x710205cd90 (16 bytes) — MotionModule vtable[0x1c8/8] dispatch
u32 FUN_710205cd90(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x1c8 / 8])(mod);
}

// 0x710205cda0 (16 bytes) — MotionModule vtable[0x1d0/8] dispatch
u32 FUN_710205cda0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x1d0 / 8])(mod);
}

// 0x710205cdb0 (16 bytes) — MotionModule vtable[0x1f8/8] dispatch
u32 FUN_710205cdb0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x1f8 / 8])(mod);
}

// 0x710205cdc0 (16 bytes) — MotionModule vtable[0x218/8] dispatch
u32 FUN_710205cdc0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x218 / 8])(mod);
}

// 0x710205cdd0 (16 bytes) — MotionModule vtable[0x228/8] dispatch
u32 FUN_710205cdd0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x228 / 8])(mod);
}

// 0x710205cde0 (16 bytes) — MotionModule vtable[0x238/8] dispatch
u32 FUN_710205cde0(app::BattleObjectModuleAccessor* acc) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**)>(VT(mod)[0x238 / 8])(mod);
}

// 0x710205ce10 (16 bytes) — MotionModule vtable[0x270/8] dispatch
u32 FUN_710205ce10(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    return reinterpret_cast<u32(*)(void**, u64)>(VT(mod)[0x270 / 8])(mod, p1);
}
