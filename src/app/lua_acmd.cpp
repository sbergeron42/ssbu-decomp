#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "lib/L2CValue.h"

using app::BattleObjectModuleAccessor;

// Math library declarations (bare metal — no <math.h>)
extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" float tanf(float);
extern "C" float acosf(float);
extern "C" float sqrtf(float);

namespace app::lua_bind {

// ============================================================
// lib::L2CValue constructors
// All are leaf functions: no stack frame, no ADRP, no branches
// ============================================================

// lib::L2CValue::L2CValue() — default constructor, type = 0 (void/nil)
// 0x7103733fd0 (8 bytes)
void L2CValue(u32* this_) {
    *this_ = 0;
}

// lib::L2CValue::L2CValue(long) — integer constructor
// 0x7103734120 (16 bytes)
void L2CValue_7103734120(u32* this_, s64 val) {
    *this_ = 2;
    *reinterpret_cast<s64*>(reinterpret_cast<u8*>(this_) + 8) = val;
}

// lib::L2CValue::L2CValue(unsigned long) — integer constructor (same bytes as signed)
// 0x7103734130 (16 bytes)
void L2CValue_7103734130(u32* this_, u64 val) {
    *this_ = 2;
    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(this_) + 8) = val;
}

// lib::L2CValue::L2CValue(float) — float constructor
// 0x7103734140 (16 bytes)
void L2CValue_7103734140(u32* this_, f32 val) {
    *this_ = 3;
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(this_) + 8) = val;
}

// lib::L2CValue::L2CValue(void*) — pointer constructor
// 0x7103734150 (16 bytes)
void L2CValue_7103734150(u32* this_, void* val) {
    *this_ = 4;
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(this_) + 8) = val;
}

// lib::L2CValue::L2CValue(bool) — bool constructor
// 0x71037340c0 (20 bytes)
void L2CValue_71037340c0(u32* this_, u32 val) {
    *this_ = 1;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this_) + 8) = val & 1;
}

// ============================================================
// SetLuaStateAccessor — copies module pointers from accessor to lua state
// 0x71003ab220 (364 bytes)
// Leaf function: 45 ldr/str pairs + ret, no stack frame
// Copies all module pointers from BattleObjectModuleAccessor (src+0x38..+0x198)
// into a LuaStateAccessor struct (dst+0x18..+0x180)
// ============================================================
void SetLuaStateAccessor(u8* dst, BattleObjectModuleAccessor* src) {
    // Main sequential block: src+0x38..+0x100 → dst+0x18..+0xe8
    *reinterpret_cast<void**>(dst + 0x18) = src->posture_module;
    *reinterpret_cast<void**>(dst + 0x28) = src->status_module;
    *reinterpret_cast<void**>(dst + 0x30) = src->fighter_control_module;
    *reinterpret_cast<void**>(dst + 0x38) = src->work_module;
    *reinterpret_cast<void**>(dst + 0x40) = src->ground_module;
    *reinterpret_cast<void**>(dst + 0x48) = src->camera_module;
    *reinterpret_cast<void**>(dst + 0x50) = src->item_kinetic_module;
    *reinterpret_cast<void**>(dst + 0x58) = src->color_blend_module;
    *reinterpret_cast<void**>(dst + 0x60) = src->model_module;
    *reinterpret_cast<void**>(dst + 0x68) = src->physics_module;
    *reinterpret_cast<void**>(dst + 0x70) = src->motion_module;
    *reinterpret_cast<void**>(dst + 0x78) = src->stop_module;
    *reinterpret_cast<void**>(dst + 0x80) = src->article_module;
    *reinterpret_cast<void**>(dst + 0x88) = src->attack_module;
    *reinterpret_cast<void**>(dst + 0x90) = src->damage_module;
    *reinterpret_cast<void**>(dst + 0x98) = src->hit_module;
    *reinterpret_cast<void**>(dst + 0xa0) = src->combo_module;
    *reinterpret_cast<void**>(dst + 0xa8) = src->fighter_area_module;
    *reinterpret_cast<void**>(dst + 0xb0) = src->item_module;
    *reinterpret_cast<void**>(dst + 0xb8) = src->link_module;
    *reinterpret_cast<void**>(dst + 0xc0) = src->team_module;
    *reinterpret_cast<void**>(dst + 0xc8) = src->search_module;
    *reinterpret_cast<void**>(dst + 0xd0) = src->pad_0xE8;
    *reinterpret_cast<void**>(dst + 0xd8) = src->turn_module;
    *reinterpret_cast<void**>(dst + 0xe0) = src->reflect_module;
    *reinterpret_cast<void**>(dst + 0xe8) = src->shield_module;
    // Second block: src+0x118..+0x198 → dst+0x100..+0x180
    *reinterpret_cast<void**>(dst + 0x100) = src->jostle_module;
    *reinterpret_cast<void**>(dst + 0x108) = src->catch_module;
    *reinterpret_cast<void**>(dst + 0x110) = src->cancel_module;
    *reinterpret_cast<void**>(dst + 0x118) = src->pad_0x130;
    *reinterpret_cast<void**>(dst + 0x120) = src->capture_module;
    *reinterpret_cast<void**>(dst + 0x128) = src->effect_module;
    *reinterpret_cast<void**>(dst + 0x130) = src->sound_module;
    *reinterpret_cast<void**>(dst + 0x138) = src->visibility_module;
    *reinterpret_cast<void**>(dst + 0x140) = src->grab_module;
    *reinterpret_cast<void**>(dst + 0x148) = src->pad_0x160;
    *reinterpret_cast<void**>(dst + 0x150) = src->shake_module;
    *reinterpret_cast<void**>(dst + 0x158) = src->slow_module;
    *reinterpret_cast<void**>(dst + 0x160) = src->pad_0x178;
    *reinterpret_cast<void**>(dst + 0x168) = src->shadow_module;
    *reinterpret_cast<void**>(dst + 0x170) = src->motion_animcmd_module;
    *reinterpret_cast<void**>(dst + 0x178) = src->pad_0x190;
    *reinterpret_cast<void**>(dst + 0x180) = src->ink_paint_module;
    // Out-of-order tail: absorber and reflector
    *reinterpret_cast<void**>(dst + 0xf0) = src->absorber_module;
    *reinterpret_cast<void**>(dst + 0xf8) = src->reflector_module;
}

// ============================================================
// lib::L2CAgent::clear_lua_stack() — resets Lua stack to base
// 0x710372e2e0 (60 bytes)
// Leaf function with internal loop, no external calls
// Iterates L2CValue-sized (0x10) slots, clearing type tags to 0 (nil)
// lua_state layout: +0x10 = stack top, +0x20 = ptr to call info
// ============================================================
void clear_lua_stack(u8* this_) {
    u8* ls = *reinterpret_cast<u8**>(this_ + 8);
    u8* base = *reinterpret_cast<u8**>(*reinterpret_cast<u8**>(ls + 0x20));
    u8* top = *reinterpret_cast<u8**>(ls + 0x10);
    u8* target = base + 0x10;
    if (top < target) {
        do {
            *reinterpret_cast<u8**>(ls + 0x10) = top + 0x10;
            *reinterpret_cast<u32*>(top + 8) = 0;
            top = *reinterpret_cast<u8**>(ls + 0x10);
        } while (top < target);
    }
    *reinterpret_cast<u8**>(ls + 0x10) = target;
}

// ============================================================
// is_enable_couple_tech_for_lua — tail call through work_module
// 0x7100fbf7c0 (8 bytes)
// Loads work_module (+0x50) from accessor, tail-calls FUN_7100fbd1a0
// ============================================================
extern "C" void FUN_7100fbd1a0(void*);
void is_enable_couple_tech_for_lua(BattleObjectModuleAccessor* a) {
    FUN_7100fbd1a0(a->work_module);
}


// ============================================================
// Binary tree node destructors — used by Lua hash table internals
// Pattern: if null return; recurse(left); recurse(right); free(self)
// All 56 bytes, same structure with different function addresses
// ============================================================
extern "C" void FUN_710392e590(void*);  // je_aligned_free

// 0x7103716100 (56 bytes)
void FUN_7103716100(u8** node) {
    if (!node) return;
    FUN_7103716100(reinterpret_cast<u8**>(*node));
    FUN_7103716100(reinterpret_cast<u8**>(node[1]));
    FUN_710392e590(node);
}

// 0x710376a190 (56 bytes)
void FUN_710376a190(u8** node) {
    if (!node) return;
    FUN_710376a190(reinterpret_cast<u8**>(*node));
    FUN_710376a190(reinterpret_cast<u8**>(node[1]));
    FUN_710392e590(node);
}

// ============================================================
// L2CAgent constructor — stores vtable + lua_state, zeros fields
// 0x710372da00 (32 bytes)
// ============================================================

// L2CAgent vtable at 0x710523be40
extern "C" __attribute__((visibility("hidden"))) void* DAT_710523be40;

// lib::L2CAgent::L2CAgent(lua_State*)
void L2CAgent_710372da00(u8* this_, void* ls) {
    *reinterpret_cast<void**>(this_) = &DAT_710523be40;
    *reinterpret_cast<void**>(this_ + 8) = ls;
    *reinterpret_cast<u64*>(this_ + 0x10) = 0;
    *reinterpret_cast<u64*>(this_ + 0x18) = 0;
    *reinterpret_cast<u64*>(this_ + 0x20) = 0;
    *reinterpret_cast<u64*>(this_ + 0x28) = 0;
    *reinterpret_cast<u32*>(this_ + 0x30) = 0x3f800000u;  // 1.0f as raw bits
}

// ============================================================
// L2CValue type accessors — check type tag, return converted value
// ============================================================

// 0x7103734b80 (56 bytes) — as_integer: type 7/2 → raw, type 3 → fcvtzs
s64 as_integer_7103734b80(u32* this_) {
    u32 type = *this_;
    if (type == 7 || type == 2) {
        return *reinterpret_cast<s64*>(reinterpret_cast<u8*>(this_) + 8);
    }
    if (type == 3) {
        return (s64)*reinterpret_cast<f32*>(reinterpret_cast<u8*>(this_) + 8);
    }
    return 0;
}

// 0x7103734f10 (56 bytes) — as_number: type 7/2 → scvtf, type 3 → raw float
f32 as_number_7103734f10(u32* this_) {
    u32 type = *this_;
    if (type == 7 || type == 2) {
        return (f32)*reinterpret_cast<s64*>(reinterpret_cast<u8*>(this_) + 8);
    }
    if (type == 3) {
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(this_) + 8);
    }
    return 0.0f;
}

// 0x7103735ff0 (52 bytes) — as_string: type 8 → check SSO, return ptr
// SSO string: byte[0] & 1 ? heap (ptr at +0x10) : inline (data at +0x1)
extern "C" __attribute__((visibility("hidden"))) char DAT_7104866c2e;  // empty string ""

const char* as_string_7103735ff0(u32* this_) {
    if (*this_ != 8) return &DAT_7104866c2e;
    u8* str = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(this_) + 8);
    if (str[0] & 1) {
        return *reinterpret_cast<const char**>(str + 0x10);
    }
    return reinterpret_cast<const char*>(str + 1);
}

// ============================================================
// operator[] — L2CValue table index access (shrink-wrapped)
// 0x7103735d80 (48 bytes)
// Prologue is inside the type==5 branch (compiler shrink-wraps)
// ============================================================

extern "C" void* FUN_71037339f0(void*, int);
extern "C" __attribute__((visibility("hidden"))) u8 DAT_710593a3a8;

void* operator_index_7103735d80(u32* this_, int index) {
    if (*this_ != 5) return &DAT_710593a3a8;
    void* table = *reinterpret_cast<void**>(reinterpret_cast<u8*>(this_) + 8);
    void* result = FUN_71037339f0(table, index);
    asm volatile("");
    return result;
}

// ============================================================
// sort — wrapper for L2CAgent lua sort
// 0x710372e9f0 (32 bytes)
// ============================================================

extern "C" void FUN_710372ea10(void*, void*);

void sort_710372e9f0(void* this_, void* p1) {
    u8* ls = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(p1) + 8);
    u8* base = *reinterpret_cast<u8**>(ls + 8);
    void* count = *reinterpret_cast<void**>(ls + 0x10);
    FUN_710372ea10(base + 0x10, count);
    asm volatile("");
}

// ============================================================
// L2CValue math functions — return L2CValue via x8 (struct return)
// All follow: extract value from input, apply math op, return result
// ============================================================

// 0x7103733090 (68 bytes) — math_toint: convert to integer
// as_integer pattern → return type=2
lib::L2CValue math_toint_7103733090(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    s64 val;
    if (type == 7 || type == 2) {
        val = param->int_val;
    } else if (type == 3) {
        val = (s64)param->float_val;
    } else {
        val = 0;
    }
    ret.type = 2;
    ret.int_val = val;
    return ret;
}

// 0x7103732e20 (88 bytes) — math_abs: absolute value
// int path: cmp+cneg; float path: fabs
lib::L2CValue math_abs_7103732e20(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    if (type == 7 || type == 2) {
        s64 v = param->int_val;
        s64 abs_v = v < 0 ? -v : v;
        ret.type = 2;
        ret.int_val = abs_v;
        return ret;
    }
    f32 fv;
    if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    ret.type = 3;
    ret.float_val = __builtin_fabsf(fv);
    return ret;
}

// L2CValue copy constructor (extern for explicit calls)
extern "C" void FUN_7103733fe0(lib::L2CValue*, const lib::L2CValue*);

// 0x71037330e0 (72 bytes) — math_floor: floor
// int path: copy (identity); float path: frintm
lib::L2CValue math_floor_71037330e0(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    if (type == 7 || type == 2) {
        FUN_7103733fe0(&ret, param);
        return ret;
    }
    f32 fv = (type == 3) ? param->float_val : 0.0f;
    ret.type = 3;
    ret.float_val = __builtin_floorf(fv);
    return ret;
}

// 0x7103733130 (72 bytes) — math_ceil: ceiling
// int path: copy (identity); float path: frintp
lib::L2CValue math_ceil_7103733130(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    if (type == 7 || type == 2) {
        FUN_7103733fe0(&ret, param);
        return ret;
    }
    f32 fv = (type == 3) ? param->float_val : 0.0f;
    ret.type = 3;
    ret.float_val = __builtin_ceilf(fv);
    return ret;
}

// 0x7103732e80 (96 bytes) — math_sin: sine
lib::L2CValue math_sin_7103732e80(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    f32 fv;
    if (type == 7 || type == 2) {
        fv = (f32)param->int_val;
    } else if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    f32 result = sinf(fv);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x7103732ee0 (96 bytes) — math_cos: cosine
lib::L2CValue math_cos_7103732ee0(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    f32 fv;
    if (type == 7 || type == 2) {
        fv = (f32)param->int_val;
    } else if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    f32 result = cosf(fv);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x7103732f40 (96 bytes) — math_tan: tangent
lib::L2CValue math_tan_7103732f40(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    f32 fv;
    if (type == 7 || type == 2) {
        fv = (f32)param->int_val;
    } else if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    f32 result = tanf(fv);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x7103732fa0 (96 bytes) — math_acos: arc cosine
lib::L2CValue math_acos_7103732fa0(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    f32 fv;
    if (type == 7 || type == 2) {
        fv = (f32)param->int_val;
    } else if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    f32 result = acosf(fv);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x71037332a0 (112 bytes) — math_sqrt: square root
// Uses fsqrt first, falls back to sqrtf if NaN (negative input)
lib::L2CValue math_sqrt_71037332a0(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    f32 fv;
    if (type == 7 || type == 2) {
        fv = (f32)param->int_val;
    } else if (type == 3) {
        fv = param->float_val;
    } else {
        fv = 0.0f;
    }
    f32 result = sqrtf(fv);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x7103734f50 (72 bytes) — operator~: bitwise NOT
// as_integer pattern → mvn → return type=2
lib::L2CValue operator_not_7103734f50(lib::L2CValue* param) {
    lib::L2CValue ret;
    u32 type = param->type;
    u64 val;
    if (type == 7 || type == 2) {
        val = param->uint_val;
    } else if (type == 3) {
        val = (u64)(s64)param->float_val;
    } else {
        val = 0;
    }
    ret.type = 2;
    ret.raw = ~val;
    return ret;
}

// ============================================================
// operator[](Hash40) — table lookup by hash key
// 0x7103735db0 (64 bytes)
// ============================================================

extern "C" void* FUN_7103733d50(void*, u64*);

void* operator_index_hash_7103735db0(u32* this_, u64 hash) {
    u64 local_hash = hash;
    if (*this_ != 5) return &DAT_710593a3a8;
    void* table = *reinterpret_cast<void**>(reinterpret_cast<u8*>(this_) + 8);
    return FUN_7103733d50(table, &local_hash);
}

// ============================================================
// L2CAgent sort — 2-arg sort with comparator
// 0x71037301b0 (52 bytes)
// ============================================================

extern "C" void FUN_71037301f0(void*, void*, void*);

void sort_71037301b0(void* this_, void* p1, void* p2) {
    u8* table = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(p1) + 8);
    void* base = *reinterpret_cast<void**>(table + 8);
    void* count = *reinterpret_cast<void**>(table + 0x10);
    void* stack_args[2] = {p2, this_};
    FUN_71037301f0(reinterpret_cast<u8*>(base) + 0x10, count, stack_args);
}

// ============================================================
// L2CAgent lifecycle — destructor, lock/unlock
// ============================================================

extern "C" void FUN_71039c1490(void*);  // std::recursive_mutex::lock
extern "C" void FUN_71039c14a0(void*);  // std::recursive_mutex::unlock

// 0x710372c200 (12 bytes) — LuaManager::lock
void lock_710372c200(u8* this_) {
    u8* p = *reinterpret_cast<u8**>(this_);
    FUN_71039c1490(p + 0x70);
}

// 0x710372c210 (12 bytes) — LuaManager::unlock
void unlock_710372c210(u8* this_) {
    u8* p = *reinterpret_cast<u8**>(this_);
    FUN_71039c14a0(p + 0x70);
}

// 0x710372da20 (88 bytes) — ~L2CAgent [D1 in-charge destructor]
// Reset vtable, free linked list at +0x20, free alloc at +0x10
void dtor_L2CAgent_710372da20(u8* this_) {
    *reinterpret_cast<void**>(this_) = &DAT_710523be40;
    u8* node = *reinterpret_cast<u8**>(this_ + 0x20);
    while (node) {
        u8* next = *reinterpret_cast<u8**>(node);
        FUN_710392e590(node);
        node = next;
    }
    void* p = *reinterpret_cast<void**>(this_ + 0x10);
    *reinterpret_cast<u64*>(this_ + 0x10) = 0;
    if (p) {
        FUN_710392e590(p);
    }
}

// 0x710372da80 (84 bytes) — ~L2CAgent [D0 deleting destructor]
// Same as D1 but also frees this
void dtor_D0_L2CAgent_710372da80(u8* this_) {
    *reinterpret_cast<void**>(this_) = &DAT_710523be40;
    u8* node = *reinterpret_cast<u8**>(this_ + 0x20);
    while (node) {
        u8* next = *reinterpret_cast<u8**>(node);
        FUN_710392e590(node);
        node = next;
    }
    void* p = *reinterpret_cast<void**>(this_ + 0x10);
    *reinterpret_cast<u64*>(this_ + 0x10) = 0;
    if (p) {
        FUN_710392e590(p);
    }
    FUN_710392e590(this_);
}

// ============================================================
// L2CTable::find_metatable — binary tree lookup by Hash40 key
// 0x7103733ea0 (120 bytes)
// Red-black tree lower_bound search with 40-bit hash mask
// ============================================================

void* find_metatable_7103733ea0(u8* this_, u64* hash) {
    u8* field = *reinterpret_cast<u8**>(this_ + 0x40);
    if (!field) return nullptr;
    u8** sentinel = reinterpret_cast<u8**>(field + 0x28);
    u8* node = *sentinel;
    if (!node) return nullptr;
    u64 target = *hash & 0xFFFFFFFFFFULL;
    u8* best = reinterpret_cast<u8*>(sentinel);
    do {
        u64 nk = *reinterpret_cast<u64*>(node + 0x20) & 0xFFFFFFFFFFULL;
        bool less = nk < target;
        if (!less) best = node;
        node = reinterpret_cast<u8**>(node)[less];
    } while (node);
    if (best == reinterpret_cast<u8*>(sentinel)) return nullptr;
    u64 bk = *reinterpret_cast<u64*>(best + 0x20) & 0xFFFFFFFFFFULL;
    if (target < bk) return nullptr;
    return best + 0x28;
}

} // namespace app::lua_bind
