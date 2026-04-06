#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-023
// MotionModule thunks 0x710205d0e0–0x710205d3a0
// MotionAnimcmdModule thunks 0x7102069040–0x71020691a0
// Pattern: accessor->module → vtable dispatch, 4/5-insn tail calls

// ---- MotionModule (accessor+0x88) — bool-setter variants ---------------

// 0x710205d0e0 (20 bytes) — void, p1=bool, vtable[0x3d0]
// MotionModule bool setter via vtable slot 0x3d0/8 = 122
void FUN_710205d0e0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x3d0))(mod, p1 & 1);
}

// 0x710205d100 (20 bytes) — void, p1=bool, vtable[0x3d8]
// MotionModule bool setter via vtable slot 0x3d8/8 = 123
void FUN_710205d100(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x3d8))(mod, p1 & 1);
}

// 0x710205d150 (20 bytes) — void, p1=bool, vtable[0x420]
// MotionModule bool setter via vtable slot 0x420/8 = 132
void FUN_710205d150(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x420))(mod, p1 & 1);
}

// 0x710205d170 (20 bytes) — void, p1=bool, vtable[0x438]
// MotionModule bool setter via vtable slot 0x438/8 = 135
void FUN_710205d170(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x438))(mod, p1 & 1);
}

// 0x710205d1b0 (20 bytes) — void, p1=bool, vtable[0x468]
// MotionModule bool setter via vtable slot 0x468/8 = 141
void FUN_710205d1b0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x468))(mod, p1 & 1);
}

// 0x710205d1e0 (20 bytes) — void, p1=bool, vtable[0x478]
// MotionModule bool setter via vtable slot 0x478/8 = 143
void FUN_710205d1e0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x478))(mod, p1 & 1);
}

// 0x710205d210 (20 bytes) — void, p1=bool, vtable[0x4c0]
// MotionModule bool setter via vtable slot 0x4c0/8 = 152
void FUN_710205d210(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x4c0))(mod, p1 & 1);
}

// 0x710205d230 (20 bytes) — void, p1=bool, vtable[0x4f8]
// MotionModule bool setter via vtable slot 0x4f8/8 = 159
void FUN_710205d230(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x4f8))(mod, p1 & 1);
}

// 0x710205d250 (16 bytes) — void, 1 int arg, vtable[0x500]
// MotionModule dispatch with int arg via vtable slot 0x500/8 = 160
void FUN_710205d250(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x500))(mod, p1);
}

// 0x710205d280 (20 bytes) — void, p1=bool, vtable[0x588]
// MotionModule bool setter via vtable slot 0x588/8 = 177
void FUN_710205d280(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x588))(mod, p1 & 1);
}

// 0x710205d2a0 (16 bytes) — void, 0 int args, vtable[0x590]
// MotionModule no-arg dispatch via vtable slot 0x590/8 = 178
void FUN_710205d2a0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64))(*(u64*)mod + 0x590))(mod);
}

// 0x710205d2b0 (16 bytes) — void, 1 int arg, vtable[0x598]
// MotionModule dispatch with int arg via vtable slot 0x598/8 = 179
void FUN_710205d2b0(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x598))(mod, p1);
}

// 0x710205d2c0 (20 bytes) — void, p1=bool, vtable[0x5a0]
// MotionModule bool setter via vtable slot 0x5a0/8 = 180
void FUN_710205d2c0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5a0))(mod, p1 & 1);
}

// 0x710205d2e0 (20 bytes) — void, p1=bool, vtable[0x5b8]
// MotionModule bool setter via vtable slot 0x5b8/8 = 183
void FUN_710205d2e0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5b8))(mod, p1 & 1);
}

// 0x710205d300 (20 bytes) — void, 2 int args, p2=bool, vtable[0x5c0]
// MotionModule dispatch with int + bool via vtable slot 0x5c0/8 = 184
void FUN_710205d300(u64 a, u64 p1, u32 p2) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x5c0))(mod, p1, p2 & 1);
}

// 0x710205d320 (20 bytes) — void, 2 int args, p2=bool, vtable[0x5c8]
// MotionModule dispatch with int + bool via vtable slot 0x5c8/8 = 185
void FUN_710205d320(u64 a, u64 p1, u32 p2) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x5c8))(mod, p1, p2 & 1);
}

// 0x710205d340 (20 bytes) — void, p1=bool, vtable[0x5d0]
// MotionModule bool setter via vtable slot 0x5d0/8 = 186
void FUN_710205d340(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5d0))(mod, p1 & 1);
}

// 0x710205d360 (20 bytes) — void, p1=bool, vtable[0x5e0]
// MotionModule bool setter via vtable slot 0x5e0/8 = 188
void FUN_710205d360(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5e0))(mod, p1 & 1);
}

// 0x710205d380 (20 bytes) — void, p1=bool, vtable[0x5f8]
// MotionModule bool setter via vtable slot 0x5f8/8 = 191
void FUN_710205d380(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5f8))(mod, p1 & 1);
}

// 0x710205d3a0 (16 bytes) — void, 1 int arg, vtable[0x600]
// MotionModule dispatch with int arg via vtable slot 0x600/8 = 192
void FUN_710205d3a0(u64 a, u64 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x88 → motion_module [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    u64 mod = reinterpret_cast<u64>(acc->motion_module);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x600))(mod, p1);
}

// ---- MotionAnimcmdModule (accessor+0x188) ----------------------------------

// 0x7102069040 (16 bytes) — void, 0 int args, vtable[0x58]
// MotionAnimcmdModule no-arg dispatch via vtable slot 0x58/8 = 11
void FUN_7102069040(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64))(*(u64*)mod + 0x58))(mod);
}

// 0x7102069090 (16 bytes) — void, 3 int args, vtable[0x78]
// MotionAnimcmdModule dispatch with 3 args via vtable slot 0x78/8 = 15
void FUN_7102069090(u64 a, u64 p1, u64 p2, u64 p3) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x78))(mod, p1, p2, p3);
}

// 0x71020690a0 (16 bytes) — void, 3 int args, vtable[0x80]
// MotionAnimcmdModule dispatch with 3 args via vtable slot 0x80/8 = 16
void FUN_71020690a0(u64 a, u64 p1, u64 p2, u64 p3) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x80))(mod, p1, p2, p3);
}

// 0x71020690b0 (20 bytes) — void, p1=bool, vtable[0x88]
// MotionAnimcmdModule bool setter via vtable slot 0x88/8 = 17
void FUN_71020690b0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x88))(mod, p1 & 1);
}

// 0x71020690d0 (16 bytes) — void, 0 int args, vtable[0x90]
// MotionAnimcmdModule no-arg dispatch via vtable slot 0x90/8 = 18
void FUN_71020690d0(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64))(*(u64*)mod + 0x90))(mod);
}

// 0x71020690e0 (20 bytes) — void, p1=bool, vtable[0x98]
// MotionAnimcmdModule bool setter via vtable slot 0x98/8 = 19
void FUN_71020690e0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x98))(mod, p1 & 1);
}

// 0x7102069100 (20 bytes) — void, p1=bool, vtable[0xa0]
// MotionAnimcmdModule bool setter via vtable slot 0xa0/8 = 20
void FUN_7102069100(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xa0))(mod, p1 & 1);
}

// 0x7102069120 (20 bytes) — void, p1=bool, vtable[0xa8]
// MotionAnimcmdModule bool setter via vtable slot 0xa8/8 = 21
void FUN_7102069120(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xa8))(mod, p1 & 1);
}

// 0x7102069140 (20 bytes) — void, p1=bool, vtable[0xb0]
// MotionAnimcmdModule bool setter via vtable slot 0xb0/8 = 22
void FUN_7102069140(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb0))(mod, p1 & 1);
}

// 0x7102069160 (20 bytes) — void, p1=bool, vtable[0xb8]
// MotionAnimcmdModule bool setter via vtable slot 0xb8/8 = 23
void FUN_7102069160(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb8))(mod, p1 & 1);
}

// 0x7102069180 (16 bytes) — bool return, 0 int args, vtable[0xc0]
// MotionAnimcmdModule bool query via vtable slot 0xc0/8 = 24
u32 FUN_7102069180(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    return (**(u32(**)(u64))(*(u64*)mod + 0xc0))(mod);
}

// 0x7102069190 (16 bytes) — void, 0 int args, vtable[0xc8]
// MotionAnimcmdModule no-arg dispatch via vtable slot 0xc8/8 = 25
void FUN_7102069190(u64 a) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64))(*(u64*)mod + 0xc8))(mod);
}

// 0x71020691a0 (20 bytes) — void, p1=bool, vtable[0xd0]
// MotionAnimcmdModule bool setter via vtable slot 0xd0/8 = 26
void FUN_71020691a0(u64 a, u32 p1) {
    app::BattleObjectModuleAccessor* acc = reinterpret_cast<app::BattleObjectModuleAccessor*>(a);
    // +0x188 → motion_animcmd_module [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    u64 mod = reinterpret_cast<u64>(acc->motion_animcmd_module);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xd0))(mod, p1 & 1);
}
