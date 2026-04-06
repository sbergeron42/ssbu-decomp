#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-025
// PostureModule 0x710206af80–0x710206b120, ReflectModule 0x710206ed10–0x710206ed80

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- PostureModule (accessor+0x38) — rot_x/y/z component extractors -------

// 0x710206af80 (36 bytes) — float return (rot.x), vtable[0xd8]
// PostureModule rot() → extract x-component: blr + ldr s0,[x0]
float FUN_710206af80(u64 a) {
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    // Note: inline cast required — local acc variable shifts prologue scheduling in non-leaf functions
    u64 mod = reinterpret_cast<u64>(reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    u64 rot = (**(u64(**)(u64))(*(u64*)mod + 0xd8))(mod);
    return *(float*)rot;
}

// 0x710206afb0 (36 bytes) — float return (rot.y), vtable[0xd8]
// PostureModule rot() → extract y-component: blr + ldr s0,[x0,#4]
float FUN_710206afb0(u64 a) {
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    u64 rot = (**(u64(**)(u64))(*(u64*)mod + 0xd8))(mod);
    return *((float*)rot + 1);
}

// 0x710206afe0 (36 bytes) — float return (rot.z), vtable[0xd8]
// PostureModule rot() → extract z-component: blr + ldr s0,[x0,#8]
float FUN_710206afe0(u64 a) {
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(reinterpret_cast<app::BattleObjectModuleAccessor*>(a)->posture_module);
    u64 rot = (**(u64(**)(u64))(*(u64*)mod + 0xd8))(mod);
    return *((float*)rot + 2);
}

// ---- PostureModule (accessor+0x38) — continued ----------------------------

// 0x710206b010 (16 bytes) — void, 2 int args, vtable[0xe0]
// PostureModule dispatch with 2 args via vtable slot 0xe0/8 = 28
void FUN_710206b010(u64 a, u64 p1, u64 p2) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0xe0))(mod, p1, p2);
}

// 0x710206b020 (16 bytes) — void, 0 int args, vtable[0xe8]
// PostureModule no-arg dispatch via vtable slot 0xe8/8 = 29
void FUN_710206b020(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0xe8))(mod);
}

// 0x710206b030 (16 bytes) — bool return, 0 int args, vtable[0xf0]
// PostureModule bool query via vtable slot 0xf0/8 = 30
u32 FUN_710206b030(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    return (**(u32(**)(u64))(*(u64*)mod + 0xf0))(mod);
}

// 0x710206b040 (16 bytes) — float return, 0 int args, vtable[0xf8]
// PostureModule float query via vtable slot 0xf8/8 = 31
float FUN_710206b040(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    return (**(float(**)(u64))(*(u64*)mod + 0xf8))(mod);
}

// 0x710206b050 (16 bytes) — void, 0 int args, vtable[0x100]
// PostureModule no-arg dispatch via vtable slot 0x100/8 = 32
void FUN_710206b050(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x100))(mod);
}

// 0x710206b060 (16 bytes) — void, 0 int args, vtable[0x108]
// PostureModule no-arg dispatch via vtable slot 0x108/8 = 33
void FUN_710206b060(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x108))(mod);
}

// 0x710206b070 (16 bytes) — float return, 0 int args, vtable[0x110]
// PostureModule float query via vtable slot 0x110/8 = 34
float FUN_710206b070(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x110))(mod);
}

// 0x710206b080 (16 bytes) — float return, 0 int args, vtable[0x118]
// PostureModule float query via vtable slot 0x118/8 = 35
float FUN_710206b080(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x118))(mod);
}

// 0x710206b090 (20 bytes) — void, p1=bool, vtable[0x120]
// PostureModule bool setter via vtable slot 0x120/8 = 36
void FUN_710206b090(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x120))(mod, p1 & 1);
}

// 0x710206b0b0 (16 bytes) — void, 0 int args (hash via other regs), vtable[0x130]
// PostureModule no-arg dispatch via vtable slot 0x130/8 = 38
void FUN_710206b0b0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x130))(mod);
}

// 0x710206b0c0 (16 bytes) — void, 0 int args, vtable[0x138]
// PostureModule no-arg dispatch via vtable slot 0x138/8 = 39
void FUN_710206b0c0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x138))(mod);
}

// 0x710206b0d0 (16 bytes) — float return, 0 int args, vtable[0x140]
// PostureModule float query via vtable slot 0x140/8 = 40
float FUN_710206b0d0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x140))(mod);
}

// 0x710206b0e0 (16 bytes) — void, 0 int args, vtable[0x148]
// PostureModule no-arg dispatch via vtable slot 0x148/8 = 41
void FUN_710206b0e0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x148))(mod);
}

// 0x710206b0f0 (20 bytes) — void, p1=bool, vtable[0x150]
// PostureModule bool setter via vtable slot 0x150/8 = 42
void FUN_710206b0f0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x150))(mod, p1 & 1);
}

// 0x710206b110 (16 bytes) — void, 0 int args, vtable[0x178]
// PostureModule no-arg dispatch via vtable slot 0x178/8 = 47
void FUN_710206b110(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64))(*(u64*)mod + 0x178))(mod);
}

// 0x710206b120 (16 bytes) — void, 1 int arg, vtable[0x180]
// PostureModule dispatch with int arg via vtable slot 0x180/8 = 48
void FUN_710206b120(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x38 → posture_module [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    u64 mod = reinterpret_cast<u64>(acc->posture_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x180))(mod, p1);
}

// ---- ReflectModule (accessor+0xf8) ----------------------------------------

// 0x710206ed10 (16 bytes) — void, 0 int args, vtable[0x50]
// ReflectModule no-arg dispatch via vtable slot 0x50/8 = 10
void FUN_710206ed10(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
}

// 0x710206ed20 (16 bytes) — u64 return, 0 int args, vtable[0x58]
// ReflectModule u64 query via vtable slot 0x58/8 = 11
u64 FUN_710206ed20(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(u64(**)(u64))(*(u64*)mod + 0x58))(mod);
}

// 0x710206ed30 (16 bytes) — void, 1 int arg (hash), vtable[0x60]
// ReflectModule dispatch with hash arg via vtable slot 0x60/8 = 12
void FUN_710206ed30(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x60))(mod, p1);
}

// 0x710206ed40 (16 bytes) — u64 return, 0 int args, vtable[0x68]
// ReflectModule u64 query via vtable slot 0x68/8 = 13
u64 FUN_710206ed40(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(u64(**)(u64))(*(u64*)mod + 0x68))(mod);
}

// 0x710206ed50 (16 bytes) — void, 1 int arg, vtable[0x70]
// ReflectModule dispatch with int arg via vtable slot 0x70/8 = 14
void FUN_710206ed50(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x70))(mod, p1);
}

// 0x710206ed60 (16 bytes) — float return, 0 int args, vtable[0x78]
// ReflectModule float query via vtable slot 0x78/8 = 15
float FUN_710206ed60(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x78))(mod);
}

// 0x710206ed70 (16 bytes) — void, 0 int args (float via SIMD), vtable[0x80]
// ReflectModule no-arg dispatch via vtable slot 0x80/8 = 16
void FUN_710206ed70(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    (**(void(**)(u64))(*(u64*)mod + 0x80))(mod);
}

// 0x710206ed80 (16 bytes) — float return, 0 int args, vtable[0x88]
// ReflectModule float query via vtable slot 0x88/8 = 17
float FUN_710206ed80(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0xf8 → reflect_module [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xf8]
    u64 mod = reinterpret_cast<u64>(acc->reflect_module);
    return (**(float(**)(u64))(*(u64*)mod + 0x88))(mod);
}
