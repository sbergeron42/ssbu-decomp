#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/WorkModule.h"

// pool-a: sv_information / sv_fighter_util readers
// Functions that read FighterInformation fields via WorkModule → FighterManager chain,
// and FighterParamAccessor2 param readers.
// [derived: Ghidra decompilation + disassembly verification for each address]

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" [[noreturn]] void abort();

// lib::Singleton<app::FighterManager>::instance_
// [derived: GOT at 0x71052b84f8, used in all sv_information functions]
namespace lib { extern "C" void* Singleton_app_FighterManager_instance_ asm("_ZN3lib9SingletonIN3app14FighterManagerEE9instance_E") HIDDEN; }
#define FM_INSTANCE lib::Singleton_app_FighterManager_instance_

// lib::Singleton<app::FighterParamAccessor2>::instance_
// [derived: GOT at 0x71052bb3b0, used in get_default_fighter_param_* functions]
namespace lib { extern "C" void* Singleton_app_FighterParamAccessor2_instance_ asm("_ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E") HIDDEN; }
#define FPA2_INSTANCE lib::Singleton_app_FighterParamAccessor2_instance_

// ---- Helper: get BattleObjectModuleAccessor from lua_State ----
// [derived: *(*(L - 8) + 0x1a0) pattern in all sv_* functions]
static inline app::BattleObjectModuleAccessor* lua_acc(u64 L) {
    return reinterpret_cast<app::BattleObjectModuleAccessor*>(
        *(u64*)(*(u64*)(L - 8) + 0x1a0));
}

// ---- Helper: get FighterInformation data pointer from entry_id ----
// Chain: *FM_INSTANCE → +entry_id*8+0x20 → +0xf8 → FighterInformation data
// [derived: identical chain in is_dead_up_force_crush, sleep_time_mul, get_dead_up_star_fall_prob]
static inline u8* fi_data_for_entry(u32 entry_id) {
    u8* fm = *(u8**)FM_INSTANCE;
    u8* entry = *(u8**)(fm + (s64)(s32)entry_id * 8 + 0x20);
    return *(u8**)(entry + 0xf8);
}

namespace app::sv_information {

// 0x710227ed00 (84 bytes) — is_dead_up_force_crush
// Reads FighterInformation field at +0x6e (bool/u8).
// [derived: disassembly at 0x710227ed00 — ldrb w0,[x8,#0x6e]]
extern "C" u8 is_dead_up_force_crush(u64 L) {
    app::BattleObjectModuleAccessor* acc = lua_acc(L);
    app::WorkModule* work = static_cast<app::WorkModule*>(acc->work_module);
    u32 entry_id = (u32)work->get_int(0x10000000);
    if (entry_id >= 8) abort();
    return *(u8*)(fi_data_for_entry(entry_id) + 0x6e);
}

// 0x710227ef00 (84 bytes) — sleep_time_mul
// Reads FighterInformation field at +0x384 (f32).
// [derived: disassembly at 0x710227ef00 — ldr s0,[x8,#0x384]]
extern "C" f32 sleep_time_mul(u64 L) {
    app::BattleObjectModuleAccessor* acc = lua_acc(L);
    app::WorkModule* work = static_cast<app::WorkModule*>(acc->work_module);
    u32 entry_id = (u32)work->get_int(0x10000000);
    if (entry_id >= 8) abort();
    return *(f32*)(fi_data_for_entry(entry_id) + 0x384);
}

} // namespace app::sv_information

namespace app::sv_fighter_util {

// 0x7102281890 (84 bytes) — get_dead_up_star_fall_prob
// Reads FighterInformation field at +0x7c (u32/s32).
// [derived: disassembly at 0x7102281890 — ldr w0,[x8,#0x7c]]
extern "C" u32 get_dead_up_star_fall_prob(u64 L) {
    app::BattleObjectModuleAccessor* acc = lua_acc(L);
    app::WorkModule* work = static_cast<app::WorkModule*>(acc->work_module);
    u32 entry_id = (u32)work->get_int(0x10000000);
    if (entry_id >= 8) abort();
    return *(u32*)(fi_data_for_entry(entry_id) + 0x7c);
}

// 0x71022822b0 (72 bytes) — get_default_fighter_param_walk_speed_max
// Reads fighter param via FPA2 index table. Leaf on fast path, abort on OOB.
// [derived: disassembly at 0x71022822b0 — ldrsw fighter_kind, FPA2 index → param entry + 0x10]
extern "C" f32 get_default_fighter_param_walk_speed_max(u64 L) {
    s32 kind = *(s32*)(*(u64*)(L - 8) + 0x198);
    if ((u32)kind >= 0x5eu) abort();
    u8* fpa2 = (u8*)FPA2_INSTANCE;
    u8* data0 = *(u8**)fpa2;
    u8* params_base = *(u8**)(data0 + 8);
    s32 idx = *(s32*)(fpa2 + (s64)kind * 12 + 0x14f0);
    return *(f32*)(params_base + (s64)idx * 0x628 + 0x10);
}

// 0x7102282300 (72 bytes) — get_default_fighter_param_ground_brake
// Same pattern as walk_speed_max, reads param entry + 0x20.
// [derived: disassembly at 0x7102282300]
extern "C" f32 get_default_fighter_param_ground_brake(u64 L) {
    s32 kind = *(s32*)(*(u64*)(L - 8) + 0x198);
    if ((u32)kind >= 0x5eu) abort();
    u8* fpa2 = (u8*)FPA2_INSTANCE;
    u8* data0 = *(u8**)fpa2;
    u8* params_base = *(u8**)(data0 + 8);
    s32 idx = *(s32*)(fpa2 + (s64)kind * 12 + 0x14f0);
    return *(f32*)(params_base + (s64)idx * 0x628 + 0x20);
}

// 0x7102282370 (72 bytes) — get_default_fighter_param_air_brake_x
// Same pattern, reads param entry + 0x64.
// [derived: disassembly at 0x7102282370]
extern "C" f32 get_default_fighter_param_air_brake_x(u64 L) {
    s32 kind = *(s32*)(*(u64*)(L - 8) + 0x198);
    if ((u32)kind >= 0x5eu) abort();
    u8* fpa2 = (u8*)FPA2_INSTANCE;
    u8* data0 = *(u8**)fpa2;
    u8* params_base = *(u8**)(data0 + 8);
    s32 idx = *(s32*)(fpa2 + (s64)kind * 12 + 0x14f0);
    return *(f32*)(params_base + (s64)idx * 0x628 + 0x64);
}

} // namespace app::sv_fighter_util
