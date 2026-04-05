// pool-e: Shield/Damage/Hit module functions — batch 3
// Types-first HARD decomp targeting ShieldModule, DamageModule, HitModule

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

// External functions used by AI attack info / predict_hit functions
extern "C" void* FUN_710033ba50(u32);
extern "C" s32 FUN_71002f2820(u32, u32);
extern "C" void* FUN_7100314030(void*, void*);
extern "C" void* FUN_710033c360(void*, u32);
extern "C" void* FUN_710033c510(u32, u64);
extern "C" u32 FUN_710033e5c0(void*, u64);
extern "C" u64 FUN_7100358e00(void*, void*, void*, u32, f32, f32);

// External global: BattleObjectWorld pointer for target lookups
extern "C" void* DAT_71052b5fd8;

// ---------------------------------------------------------------------------
// 0x7100690a30  12B  get_shield_type_of_guard  [VERIFIED 100%]
// Returns true if the guard type is not 5 (just shield).
// ---------------------------------------------------------------------------
bool FUN_7100690a30_690a30(int guard_type) {
    return guard_type != 5;
}

// ---------------------------------------------------------------------------
// 0x710200b690  32B  DamageModule__sleep_impl  [VERIFIED 100%]
// lua_bind thunk: DamageModule vtable slot 10 (offset 0x50).
// ---------------------------------------------------------------------------
void FUN_710200b690_200b690(app::BattleObjectModuleAccessor* acc, bool enable) {
    void** dm = reinterpret_cast<void**>(acc->damage_module);
    reinterpret_cast<void(*)(void**, bool)>(VT(dm)[0x50 / 8])(dm, enable);
}

// ---------------------------------------------------------------------------
// 0x7100361640  48B  check_stat_floor_damage  [92% — 1 byte return width diff]
// AI stat: true if not airborne (situation != 2) and floor damage flag set.
// ---------------------------------------------------------------------------
u64 FUN_7100361640_361640(void* lua_state) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(lua_state) - 8);
    u8* obj = *reinterpret_cast<u8**>(ctx + 0x168);
    if (*reinterpret_cast<s32*>(obj + 0xd8) != 2) {
        u8* sub = *reinterpret_cast<u8**>(obj + 0xd0);
        if (sub[0x5e] & 1) {
            return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100694bc0  176B  is_valid_just_shield  [70% — prologue/epilogue scheduling]
// Checks WorkModule int param count and param object for just shield validity.
// ---------------------------------------------------------------------------
u64 FUN_7100694bc0_694bc0(app::BattleObjectModuleAccessor* acc) {
    void** wm;

    wm = reinterpret_cast<void**>(acc->work_module);
    s32 count = reinterpret_cast<s32(*)(void**, u32)>(VT(wm)[0x98 / 8])(wm, 0x10000094);
    if (count > 0) {
        return 0;
    }

    wm = reinterpret_cast<void**>(acc->work_module);
    void** param_obj = reinterpret_cast<void**(*)(void**, u32)>(VT(wm)[0xb0 / 8])(wm, 0x1000007f);
    if (param_obj != nullptr) {
        struct { u16 kind; u64 hash; u32 flags; } local;
        local.kind = 0x73;
        local.hash = 0x47f9000cfULL;
        local.flags = 0;

        u64 result = reinterpret_cast<u64(*)(void**, void*, u32)>(VT(param_obj)[0x100 / 8])(param_obj, &local, 1);
        if (result & 1) {
            return 0;
        }
    }

    return 1;
}

// ---------------------------------------------------------------------------
// 0x710069a650  144B  is_exist_past_log_for_back_shield  [12% — instruction scheduling]
// Queries item_module for past log entries, checks sub-module for back shield.
// ---------------------------------------------------------------------------
u8 FUN_710069a650_69a650(u32 param_1, app::BattleObjectModuleAccessor* acc) {
    struct {
        s32 initial;
        void* result;
        u64 flags;
        u16 count;
        u32 range;
    } query;
    query.initial = -1;
    query.result = nullptr;
    query.flags = 0x200000000ULL;
    query.count = 1;
    query.range = 0xfe;

    void** mod = reinterpret_cast<void**>(acc->item_module);
    u8 found = reinterpret_cast<u8(*)(void**, u32, void*)>(VT(mod)[0x210 / 8])(mod, 100, &query);
    if (found & 1) {
        u8* ptr = reinterpret_cast<u8*>(query.result);
        void** sub = *reinterpret_cast<void***>(ptr + 0x198);
        return reinterpret_cast<u8(*)(void**, u32, u32)>(VT(sub)[0x1c8 / 8])(sub, param_1, 1) & 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100369e10  160B  attack_info_no_shield  [24% — csel chain regalloc/scheduling]
// AI: looks up attack entry by status range, returns no_shield byte.
// ---------------------------------------------------------------------------
u8 FUN_7100369e10_369e10(void* lua_state, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(lua_state) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 idx_a = (s64)(s32)(status - 0x603b);
    s64 idx_b = (s64)(s32)(status - 0x6034);
    s64 idx_c = (s64)(s32)((u32)status - 0x6031u);
    s64 index = 0;
    if ((u32)(status - 0x6051) < 0x18u)
        index = idx_a;
    if ((u32)(status - 0x6041) < 0xfu)
        index = idx_b;
    if ((u32)(status - 0x6031) < 0xfu)
        index = idx_c;

    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 0x24];
}

// ---------------------------------------------------------------------------
// 0x710036a220  224B  target_attack_info_no_shield  [4% — csel chain + target resolution]
// AI: like attack_info_no_shield but resolves target first.
// ---------------------------------------------------------------------------
bool FUN_710036a220_36a220(void* lua_state, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(lua_state) - 8);
    void* target = FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50);

    if (*reinterpret_cast<u32*>(ctx + 0xc50) >= 0x10u)
        return false;

    u8* target_obj = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(target) + 0x20);
    if (!target_obj)
        return false;

    u32 obj_id = *reinterpret_cast<u32*>(target_obj + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 idx_a = (s64)(s32)(status - 0x603b);
    s64 idx_b = (s64)(s32)(status - 0x6034);
    s64 idx_c = (s64)(s32)((u32)status - 0x6031u);
    s64 index = 0;
    if ((u32)(status - 0x6051) < 0x18u)
        index = idx_a;
    if ((u32)(status - 0x6041) < 0xfu)
        index = idx_b;
    if ((u32)(status - 0x6031) < 0xfu)
        index = idx_c;

    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 0x24] != 0;
}

// ---------------------------------------------------------------------------
// 0x7100369560  208B  predict_hit_in_target_attack  [12% — instruction scheduling]
// AI: checks target validity, resolves attack entry, tail-calls predict helper.
// ---------------------------------------------------------------------------
u64 FUN_7100369560_369560(void* lua_state, u32 cmd_id, f32 param3, f32 param4) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(lua_state) - 8);
    u8* obj = *reinterpret_cast<u8**>(ctx + 0x168);

    if (!*reinterpret_cast<void**>(obj + 0x20))
        return 0;

    u32* target_ptr = reinterpret_cast<u32*>(ctx + 0xc50);
    if (*reinterpret_cast<u32*>(obj) == *target_ptr || *target_ptr >= 0x10u)
        return 0;

    void* target = FUN_7100314030(DAT_71052b5fd8, target_ptr);

    if ((*reinterpret_cast<u32*>(reinterpret_cast<u8*>(target) + 0x54) & 0x84000000u) != 0x80000000u)
        return 0;

    u8* target_obj = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(target) + 0x20);
    void* entry = FUN_710033c360(target_obj + 0x988, cmd_id);
    if (!entry)
        return 0;

    return FUN_7100358e00(obj, entry, target_ptr, cmd_id, param3, param4);
}

// ---------------------------------------------------------------------------
// 0x7100369630  240B  predict_hit_in_target_attack_from_motion  [12% — instruction scheduling]
// AI: variant using motion Hash40 instead of CmdId.
// ---------------------------------------------------------------------------
u64 FUN_7100369630_369630(void* lua_state, u64 motion_hash, f32 param3, f32 param4) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(lua_state) - 8);
    u8* obj = *reinterpret_cast<u8**>(ctx + 0x168);

    if (!*reinterpret_cast<void**>(obj + 0x20))
        return 0;

    u32* target_ptr = reinterpret_cast<u32*>(ctx + 0xc50);
    if (*reinterpret_cast<u32*>(obj) == *target_ptr || *target_ptr >= 0x10u)
        return 0;

    void* target = FUN_7100314030(DAT_71052b5fd8, target_ptr);

    if ((*reinterpret_cast<u32*>(reinterpret_cast<u8*>(target) + 0x54) & 0x84000000u) != 0x80000000u)
        return 0;

    u8* target_obj = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(target) + 0x20);
    void* entry = FUN_710033c510(*reinterpret_cast<u32*>(target_obj + 0x988), motion_hash);
    if (!entry)
        return 0;

    u32 resolved_cmd = FUN_710033e5c0(target_obj + 0x988, motion_hash);
    return FUN_7100358e00(obj, entry, target_ptr, resolved_cmd, param3, param4);
}
