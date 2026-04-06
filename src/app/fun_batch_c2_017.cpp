#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/PostureModule.h"
#include "app/modules/WorkModule.h"
#include "app/modules/KineticModule.h"

using app::BattleObjectModuleAccessor;
using app::PostureModule;
using app::WorkModule;
using app::KineticModule;
using app::KineticEnergy;

// Batch decompiled via Ghidra MCP -- pool-c, batch 017
// Range: 0x7102000000 -- 0x7102FFFFFF
// Contains: sv_system, sv_ground_collision_line, sv_information,
//           sv_battle_object, sv_module_access, FL_sv_module_access

// ______ External functions _____________________________________________________________________________________________________________________________________________________________________

extern "C" int  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

extern "C" u64  get_battle_object_from_id(u32);
extern "C" void FUN_71003a9ab0(void*, u32);
extern "C" void FUN_71003cb840(void*, void*);

// ______ External data ____________________________________________________________________________________________________________________________________________________________________________________

// FighterManager singleton (adrp 0x71052b8000, ldr #0x4f8)
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b84f8;

// Guard + static object for sv_battle_object null-fallback
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052b6100[];
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052b60f0[];
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052b60f8[];
extern "C" __attribute__((visibility("hidden"))) u8 PTR_LAB_7104f61078[];

#define VT(m) (*reinterpret_cast<void***>(m))

// ── 0x710227db20 -- app::sv_system::owner_id (16B) ───────────────────────────
// ldur x8, [x0, #-8]; ldr w0, [x8, #0x190]; ret
u32 owner_id_710227db20(void* p) {
    void* a = *reinterpret_cast<void**>(reinterpret_cast<u8*>(p) - 8);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a) + 0x190);
}

// ── 0x71022848d0 -- app::sv_ground_collision_line::is_floor (16B) ─────────────
// cbz x0, ret; ldrb w8, [x0, #0xc5]; ubfx w0, w8, #3, #1; ret
u32 is_floor_71022848d0(void* p) {
    if (!p) return 0;
    u8 b = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(p) + 0xc5);
    return (b >> 3) & 1;
}

// ── 0x710227ee10 -- app::sv_information::is_ready_go (32B) ────────────────────
// adrp x8, FighterManager singleton page; ldr x8,[x8,#off]; ldr x8,[x8]; ldrb w0,[x8,#0xd2]; ret
u8 is_ready_go_710227ee10() {
    void* mgr = *reinterpret_cast<void**>(DAT_71052b84f8);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(mgr) + 0xd2);
}

// ═══════════════════════════════════════════════════════════════════════════════
// sv_battle_object helpers -- all share the get_battle_object_from_id + guard
// variable fallback pattern
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

// Helper: resolve battle object, falling back to static sentinel if invalid
static inline void* resolve_battle_object(u32 id) {
    void* obj = reinterpret_cast<void*>(get_battle_object_from_id(id));
    if (obj && *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + 0x3a) >= 4) {
        return obj;
    }
    // static init fallback
    if ((*(u64*)DAT_71052b6100 & 1) == 0) {
        if (__cxa_guard_acquire(reinterpret_cast<u64*>(DAT_71052b6100))) {
            FUN_71003a9ab0(DAT_71052b60f0, 0);
            *reinterpret_cast<u8**>(DAT_71052b60f0) = PTR_LAB_7104f61078;
            __cxa_guard_release(reinterpret_cast<u64*>(DAT_71052b6100));
        }
    }
    return *reinterpret_cast<void**>(DAT_71052b60f8);
}

// ── 0x7102283540 -- app::sv_battle_object::kind (144B) ────────────────────────
u32 kind_7102283540(u32 id) {
    void* obj = resolve_battle_object(id);
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + 0xc);
}

// ── 0x71022839d0 -- app::sv_battle_object::is_active (144B) ──────────────────
bool is_active_71022839d0(u32 id) {
    void* obj = resolve_battle_object(id);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + 0x3a) > 3;
}

// ── 0x7102283660 -- app::sv_battle_object::pos (160B) ────────────────────────
void pos_7102283660(u32 id) {
    void* obj = resolve_battle_object(id);
    auto* inner = reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(obj) + 0x20));
    // [derived: PostureModule__pos_impl (.dynsym) -> vtable slot 0x60/8]
    auto* posture = static_cast<PostureModule*>(inner->posture_module);
    posture->pos();
}

// ── 0x7102283920 -- app::sv_battle_object::set_float (176B) ──────────────────
void set_float(u32 id, f32 val, s32 idx) {
    void* obj = resolve_battle_object(id);
    auto* inner = reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(obj) + 0x20));
    // [derived: WorkModule__set_float_impl (.dynsym) -> vtable slot 0x60/8]
    auto* work = static_cast<WorkModule*>(inner->work_module);
    work->set_float(idx, val);
}

// ═══════════════════════════════════════════════════════════════════════════════
// sv_module_access -- damage/link/search: check accessor[+0x1a0] != 0,
// then call FUN_71003cb840 with a module pointer and a stack struct
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

// ── 0x710227dfb0 -- app::sv_module_access::damage (192B) ─────────────────────
// accessor[+0x1a0] → accessor_data; uses module at +0xa8 (DamageModule)
u32 damage_710227dfb0(void* L) {
    void* a = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc_data = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x1a0);
    if (!acc_data) return 0;

    void* top = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x10);
    void* ci  = *reinterpret_cast<void**>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x20));
    void* base = reinterpret_cast<u8*>(ci) + 0x10;
    u32 nargs = (u32)(((u64)top - (u64)base) >> 4);

    // Build context struct on stack
    u64 ctx[6] = {};
    void** iter_ptr = reinterpret_cast<void**>(&ctx[2]);
    ctx[0] = reinterpret_cast<u64>(iter_ptr);  // iter -> &zero field
    ctx[1] = 0;                                 // result
    ctx[2] = 0;                                 // zero
    *reinterpret_cast<u32*>(&ctx[3]) = nargs;  // nargs
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20) = L;
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28) = 0;

    void* mod = reinterpret_cast<BattleObjectModuleAccessor*>(acc_data)->damage_module;
    FUN_71003cb840(mod, ctx);

    u8 done = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28);
    void* lua = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20);
    if (done && lua) {
        u64 ci2 = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(lua) + 0x20));
        u64 top2 = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(lua) + 0x10);
        u64 target = ci2 + 0x10;
        while (top2 < target) {
            *reinterpret_cast<u64*>(reinterpret_cast<u8*>(lua) + 0x10) = top2 + 0x10;
            *reinterpret_cast<u32*>(top2 + 8) = 0;
            top2 = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(lua) + 0x10);
        }
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(lua) + 0x10) = target;
    }
    return *reinterpret_cast<u32*>(&ctx[1]);
}

// ── 0x710227e070 -- app::sv_module_access::link (192B) ───────────────────────
// Same as damage but uses module at +0xd0 (LinkModule)
u32 link_710227e070(void* L) {
    void* a = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc_data = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x1a0);
    if (!acc_data) return 0;

    void* top = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x10);
    void* ci  = *reinterpret_cast<void**>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x20));
    void* base = reinterpret_cast<u8*>(ci) + 0x10;
    u32 nargs = (u32)(((u64)top - (u64)base) >> 4);

    u64 ctx[6] = {};
    void** iter_ptr = reinterpret_cast<void**>(&ctx[2]);
    ctx[0] = reinterpret_cast<u64>(iter_ptr);
    ctx[1] = 0;
    ctx[2] = 0;
    *reinterpret_cast<u32*>(&ctx[3]) = nargs;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20) = L;
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28) = 0;

    void* mod = reinterpret_cast<BattleObjectModuleAccessor*>(acc_data)->link_module;
    return *reinterpret_cast<u32*>(&ctx[1]);
}

// ── 0x710227e1f0 -- app::sv_module_access::search (192B) ─────────────────────
// Same as damage but uses module at +0xe0 (SearchModule)
u32 search_710227e1f0(void* L) {
    void* a = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc_data = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x1a0);
    if (!acc_data) return 0;

    void* top = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x10);
    void* ci  = *reinterpret_cast<void**>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x20));
    void* base = reinterpret_cast<u8*>(ci) + 0x10;
    u32 nargs = (u32)(((u64)top - (u64)base) >> 4);

    u64 ctx[6] = {};
    void** iter_ptr = reinterpret_cast<void**>(&ctx[2]);
    ctx[0] = reinterpret_cast<u64>(iter_ptr);
    ctx[1] = 0;
    ctx[2] = 0;
    *reinterpret_cast<u32*>(&ctx[3]) = nargs;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20) = L;
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28) = 0;

    void* mod = reinterpret_cast<BattleObjectModuleAccessor*>(acc_data)->search_module;
    return *reinterpret_cast<u32*>(&ctx[1]);
}

// ═══════════════════════════════════════════════════════════════════════════════
// sv_kinetic_energy -- enable/unable/clear_speed/get_speed
// These operate on lua_State* and dispatch to KineticModule via accessor
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

extern "C" u64 FUN_71038f4000(void*, s32, s32);

// Helper: Lua stack "pop all" -- clears stack down to ci->base
static inline void lua_pop_all(void* L) {
    if (!L) return;
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20));
    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 target = ci_base + 0x10;
    while (top < target) {
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = top + 0x10;
        *reinterpret_cast<u32*>(top + 8) = 0;
        top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    }
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10) = target;
}

// ── 0x7102276a40 -- app::sv_kinetic_energy::enable (192B) ────────────────────
void enable_7102276a40(void* L) {
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* km = static_cast<KineticModule*>(reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x1a0))->item_kinetic_module);

    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = (s32)((top - ci_base) >> 4);

    u64 kind = 0;
    if (L && nargs > 0) {
        kind = FUN_71038f4000(L, 1, 0);
    }

    // [derived: KineticModule__get_energy_impl (.dynsym) -> vtable slot 0x60/8]
    auto* energy = km->get_energy((int)kind);
    energy->enabled = 1;

    lua_pop_all(L);
}

// ── 0x7102276b00 -- app::sv_kinetic_energy::unable (192B) ────────────────────
void unable_7102276b00(void* L) {
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* km = static_cast<KineticModule*>(reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x1a0))->item_kinetic_module);

    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = (s32)((top - ci_base) >> 4);

    u64 kind = 0;
    if (L && nargs > 0) {
        kind = FUN_71038f4000(L, 1, 0);
    }

    // [derived: KineticModule__get_energy_impl (.dynsym) -> vtable slot 0x60/8]
    auto* energy = km->get_energy((int)kind);
    energy->enabled = 0;

    lua_pop_all(L);
}

// ── 0x7102276c90 -- app::sv_kinetic_energy::clear_speed (208B) ───────────────
void clear_speed_7102276c90(void* L) {
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* km = static_cast<KineticModule*>(reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x1a0))->item_kinetic_module);

    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = (s32)((top - ci_base) >> 4);

    u64 kind = 0;
    if (L && nargs > 0) {
        kind = FUN_71038f4000(L, 1, 0);
    }

    // [derived: KineticModule__get_energy_impl (.dynsym) -> vtable slot 0x60/8]
    auto* energy = km->get_energy((int)kind);
    // [derived: KineticEnergy__clear_speed_impl (.dynsym) -> vtable slot 0x48/8]
    energy->clear_speed();

    lua_pop_all(L);
}

// ── 0x7102277640 -- app::sv_kinetic_energy::get_speed (256B) ─────────────────
void get_speed_7102277640(void* L) {
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    auto* km = static_cast<KineticModule*>(reinterpret_cast<BattleObjectModuleAccessor*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x1a0))->item_kinetic_module);

    u64 top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x10);
    u64 ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(L) + 0x20)) + 0x10;
    s32 nargs = (s32)((top - ci_base) >> 4);

    u64 kind = 0;
    if (L && nargs > 0) {
        kind = FUN_71038f4000(L, 1, 0);
    }

    // [derived: KineticModule__get_energy_impl (.dynsym) -> vtable slot 0x60/8]
    auto* energy = km->get_energy((int)kind);
    // [derived: KineticEnergy__get_speed_impl (.dynsym) -> vtable slot 0x20/8]
    u64* speed = reinterpret_cast<u64*>(energy->get_speed());
    (void)*speed;

    lua_pop_all(L);
}

// ── 0x710227e930 -- app::FL_sv_module_access::link (320B) ────────────────────
u32 link_710227e930(void* L) {
    void* a = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) - 8);
    void* acc_data = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x1a0);
    if (!acc_data) return 0;

    void* top_v = *reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x10);
    void* ci  = *reinterpret_cast<void**>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(L) + 0x20));
    void* base = reinterpret_cast<u8*>(ci) + 0x10;
    u32 nargs = (u32)(((u64)top_v - (u64)base) >> 4);

    u64 ctx[6] = {};
    void** iter_ptr = reinterpret_cast<void**>(&ctx[2]);
    ctx[0] = reinterpret_cast<u64>(iter_ptr);
    ctx[1] = 0;
    ctx[2] = 0;
    *reinterpret_cast<u32*>(&ctx[3]) = nargs;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20) = L;
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28) = 0;

    void** link_mod = reinterpret_cast<void**>(reinterpret_cast<BattleObjectModuleAccessor*>(acc_data)->link_module);
    u32 result = reinterpret_cast<u32(*)(void**, void*)>(VT(link_mod)[0x20/8])(link_mod, ctx);

    void* inner_L = reinterpret_cast<void*>(iter_ptr[2]);
    if (inner_L) {
        // Clear inner stack
        u64 inner_ci_base = *reinterpret_cast<u64*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x20)) + 0x10;
        u64 inner_top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x10);
        while (inner_top < inner_ci_base) {
            *reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x10) = inner_top + 0x10;
            *reinterpret_cast<u32*>(inner_top + 8) = 0;
            inner_top = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x10);
        }
        *reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x10) = inner_ci_base;

        ctx[1] = 0;
        inner_L = reinterpret_cast<void*>(iter_ptr[2]);
        if (inner_L) {
            u32* slot = *reinterpret_cast<u32**>(reinterpret_cast<u8*>(inner_L) + 0x10);
            *slot = result;
            slot[2] = 3;
            *reinterpret_cast<u64*>(reinterpret_cast<u8*>(inner_L) + 0x10) += 0x10;
            *reinterpret_cast<u32*>(&ctx[1]) = 1;
        }
    }

    u8 done = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ctx) + 0x28);
    void* lua = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ctx) + 0x20);
    if (done && lua) {
        lua_pop_all(lua);
    }
    return *reinterpret_cast<u32*>(&ctx[1]);
}

// Note: mul_speed (896B) and frame (224B) are too complex for batch generation.
// They involve extensive Lua argument parsing (mul_speed) and coroutine yield
// mechanics (frame). Skipping for now -- these should be decompiled manually.
