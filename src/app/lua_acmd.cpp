#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "lib/L2CValue.h"
#include "lib/L2CAgent.h"
#include "lib/LuaStateAccessor.h"

using app::BattleObjectModuleAccessor;

// Math library declarations (bare metal — no <math.h>)
extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" float tanf(float);
extern "C" float acosf(float);
extern "C" float sqrtf(float);
extern "C" float atan2f(float, float);
extern "C" float fmodf(float, float);
extern "C" float logf(float);
extern "C" float log10f(float);

// nn::err — ShowError takes u64 internally despite Ghidra showing undefined4
// [derived: binary emits AND X0,X0,#0xFFFFFFFF before tail call, proving callee expects u64]
namespace nn { namespace err {
extern "C" void ShowError(u64);
}}

// OOM retry handler — global pointer
// [derived: used by L2CValue copy ctor, alloc helpers, L2CTable ctor]
extern "C" __attribute__((visibility("hidden"))) long* DAT_7105331f00;

// je_aligned_alloc (jemalloc 5.1.0 Nintendo fork)
extern "C" void* je_aligned_alloc(unsigned long align, unsigned long size);

namespace app::lua_bind {

// ============================================================
// lib::L2CValue constructors
// All are leaf functions: no stack frame, no ADRP, no branches
// ============================================================

// lib::L2CValue::L2CValue() — default constructor, type = 0 (void/nil)
// 0x7103733fd0 (8 bytes)
void L2CValue(lib::L2CValue* this_) {
    this_->type = 0;
}

// lib::L2CValue::L2CValue(long) — integer constructor
// 0x7103734120 (16 bytes)
void L2CValue_7103734120(lib::L2CValue* this_, s64 val) {
    this_->type = 2;
    this_->int_val = val;
}

// lib::L2CValue::L2CValue(unsigned long) — integer constructor (same bytes as signed)
// 0x7103734130 (16 bytes)
void L2CValue_7103734130(lib::L2CValue* this_, u64 val) {
    this_->type = 2;
    this_->uint_val = val;
}

// lib::L2CValue::L2CValue(float) — float constructor
// 0x7103734140 (16 bytes)
void L2CValue_7103734140(lib::L2CValue* this_, f32 val) {
    this_->type = 3;
    this_->float_val = val;
}

// lib::L2CValue::L2CValue(void*) — pointer constructor
// 0x7103734150 (16 bytes)
void L2CValue_7103734150(lib::L2CValue* this_, void* val) {
    this_->type = 4;
    this_->ptr_val = val;
}

// lib::L2CValue::L2CValue(bool) — bool constructor
// 0x71037340c0 (20 bytes)
void L2CValue_71037340c0(lib::L2CValue* this_, u32 val) {
    this_->type = 1;
    this_->bool_val = val & 1;
}

// lib::L2CValue::L2CValue(int) — signed int constructor
// 0x71037340e0 (20 bytes)
// [derived: Ghidra type signature L2CValue(int), sign-extends w1 to x8]
void L2CValue_71037340e0(lib::L2CValue* this_, s32 val) {
    this_->type = 2;
    this_->int_val = (s64)val;
}

// lib::L2CValue::L2CValue(unsigned int) — unsigned int constructor
// 0x7103734100 (20 bytes)
// [derived: Ghidra type signature L2CValue(uint), zero-extends w1 to x8]
void L2CValue_7103734100(lib::L2CValue* this_, u32 val) {
    this_->type = 2;
    this_->uint_val = (u64)val;
}

// lib::L2CValue::L2CValue(L2CTable*) — table constructor, increments refcount
// 0x7103734160 (28 bytes)
// [derived: type=5, refcount at table+0x0]
void L2CValue_7103734160(lib::L2CValue* this_, u8* table) {
    this_->type = 5;
    this_->ptr_val = table;
    *reinterpret_cast<s32*>(table) += 1;
}

// lib::L2CValue::L2CValue(L2CInnerFunctionBase*) — inner function constructor, increments refcount
// 0x7103734180 (28 bytes)
// [derived: type=6, refcount at func+0x8]
void L2CValue_7103734180(lib::L2CValue* this_, u8* func) {
    this_->type = 6;
    this_->ptr_val = func;
    *reinterpret_cast<s32*>(func + 8) += 1;
}

// lib::L2CValue::L2CValue(Hash40) — hash constructor
// 0x71037341a0 (16 bytes)
// [derived: type=7, stores raw hash value]
void L2CValue_71037341a0(lib::L2CValue* this_, u64 hash) {
    this_->type = 7;
    this_->raw = hash & 0xFFFFFFFFFFULL;
}

// String functions (bare metal — no <string.h>)
extern "C" unsigned long strlen(const char*);
extern "C" void* memcpy(void* dst, const void* src, unsigned long n);
extern "C" int memcmp(const void*, const void*, unsigned long);

// lib::L2CValue::L2CValue(const char*) — string constructor
// 0x71037341c0 (368 bytes)
// [derived: Ghidra shows SSO string alloc (je_aligned_alloc 0x18) + OOM retry,
//  then strlen + short/long string construction (libc++ basic_string layout)]
// SSO layout: short (<0x17): byte[0] = len<<1, data at +1
//             long: [0]=cap|1, [8]=len, [16]=heap_ptr
void L2CValue_71037341c0(lib::L2CValue* this_, const char* str) {
    this_->type = 8;
    u64* sso = reinterpret_cast<u64*>(je_aligned_alloc(0x10, 0x18));
    if (sso == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 local_44 = 0;
            u64 local_58 = 0x18;
            u64 rv = reinterpret_cast<u64 (*)(long*, u32*, u64*)>(
                *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
            )(DAT_7105331f00, &local_44, &local_58);
            if ((rv & 1) != 0) {
                sso = reinterpret_cast<u64*>(je_aligned_alloc(0x10, 0x18));
                if (sso != nullptr) goto init_string;
            }
        }
        sso = nullptr;
    }
init_string:
    sso[1] = 0;
    sso[2] = 0;
    sso[0] = 0;
    unsigned long len = strlen(str);
    void* dest;
    if (len < 0x17) {
        // Short string: store in-place
        dest = reinterpret_cast<void*>(reinterpret_cast<u8*>(sso) + 1);
        *reinterpret_cast<u8*>(sso) = (u8)(len << 1);
        if (len == 0) goto null_terminate;
    } else {
        // Long string: allocate heap buffer
        u64 cap = (len + 0x10) & 0xFFFFFFFFFFFFFFF0ULL;
        u64 alloc_size = cap;
        if (cap == 0) alloc_size = 1;
        dest = je_aligned_alloc(0x10, alloc_size);
        if (dest == nullptr) {
            if (DAT_7105331f00 != nullptr) {
                u32 local_44b = 0;
                u64 local_58b = alloc_size;
                u64 rv2 = reinterpret_cast<u64 (*)(long*, u32*, u64*)>(
                    *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
                )(DAT_7105331f00, &local_44b, &local_58b);
                if ((rv2 & 1) != 0) {
                    dest = je_aligned_alloc(0x10, alloc_size);
                    if (dest != nullptr) goto store_long;
                }
            }
            dest = nullptr;
        }
    store_long:
        sso[1] = len;
        sso[2] = reinterpret_cast<u64>(dest);
        sso[0] = cap | 1;
    }
    memcpy(dest, str, len);
null_terminate:
    reinterpret_cast<u8*>(dest)[len] = 0;
    this_->ptr_val = sso;
}

// ============================================================
// SetLuaStateAccessor — copies module pointers from accessor to lua state
// 0x71003ab220 (364 bytes)
// Leaf function: 45 ldr/str pairs + ret, no stack frame
// Copies all module pointers from BattleObjectModuleAccessor (src+0x38..+0x198)
// into a LuaStateAccessor struct (dst+0x18..+0x180)
// ============================================================
void SetLuaStateAccessor(lib::LuaStateAccessor* dst, BattleObjectModuleAccessor* src) {
    // Main sequential block: src+0x38..+0x100 → dst+0x18..+0xe8
    dst->posture_module = src->posture_module;
    dst->status_module = src->status_module;
    dst->fighter_control_module = src->fighter_control_module;
    dst->work_module = src->work_module;
    dst->ground_module = src->ground_module;
    dst->camera_module = src->camera_module;
    dst->item_kinetic_module = src->item_kinetic_module;
    dst->color_blend_module = src->color_blend_module;
    dst->model_module = src->model_module;
    dst->physics_module = src->physics_module;
    dst->motion_module = src->motion_module;
    dst->stop_module = src->stop_module;
    dst->article_module = src->article_module;
    dst->attack_module = src->attack_module;
    dst->damage_module = src->damage_module;
    dst->hit_module = src->hit_module;
    dst->combo_module = src->combo_module;
    dst->fighter_area_module = src->fighter_area_module;
    dst->item_module = src->item_module;
    dst->link_module = src->link_module;
    dst->team_module = src->team_module;
    dst->search_module = src->search_module;
    dst->pad_0xD0 = src->pad_0xE8;
    dst->turn_module = src->turn_module;
    dst->reflect_module = src->reflect_module;
    dst->shield_module = src->shield_module;
    // Second block: src+0x118..+0x198 → dst+0x100..+0x180
    dst->jostle_module = src->jostle_module;
    dst->catch_module = src->catch_module;
    dst->cancel_module = src->cancel_module;
    dst->pad_0x118 = src->pad_0x130;
    dst->capture_module = src->capture_module;
    dst->effect_module = src->effect_module;
    dst->sound_module = src->sound_module;
    dst->visibility_module = src->visibility_module;
    dst->grab_module = src->grab_module;
    dst->pad_0x148 = src->pad_0x160;
    dst->shake_module = src->shake_module;
    dst->slow_module = src->slow_module;
    dst->pad_0x160 = src->pad_0x178;
    dst->shadow_module = src->shadow_module;
    dst->motion_animcmd_module = src->motion_animcmd_module;
    dst->pad_0x178 = src->pad_0x190;
    dst->ink_paint_module = src->ink_paint_module;
    // Out-of-order tail: absorber and reflector
    dst->absorber_module = src->absorber_module;
    dst->reflector_module = src->reflector_module;
}

// ============================================================
// lib::L2CAgent::clear_lua_stack() — resets Lua stack to base
// 0x710372e2e0 (60 bytes)
// Leaf function with internal loop, no external calls
// Iterates L2CValue-sized (0x10) slots, clearing type tags to 0 (nil)
// lua_state layout: +0x10 = stack top, +0x20 = ptr to call info
// ============================================================
void clear_lua_stack(lib::L2CAgent* this_) {
    u8* ls = reinterpret_cast<u8*>(this_->lua_state);
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
extern "C" void jeFree_710392e590(void*);  // je_aligned_free

// 0x7103716100 (56 bytes)
void FUN_7103716100(u8** node) {
    if (!node) return;
    FUN_7103716100(reinterpret_cast<u8**>(*node));
    FUN_7103716100(reinterpret_cast<u8**>(node[1]));
    jeFree_710392e590(node);
}

// 0x710376a190 (56 bytes)
void FUN_710376a190(u8** node) {
    if (!node) return;
    FUN_710376a190(reinterpret_cast<u8**>(*node));
    FUN_710376a190(reinterpret_cast<u8**>(node[1]));
    jeFree_710392e590(node);
}

// ============================================================
// L2CAgent constructor — stores vtable + lua_state, zeros fields
// 0x710372da00 (32 bytes)
// ============================================================

// L2CAgent vtable at 0x710523be40
extern "C" __attribute__((visibility("hidden"))) void* DAT_710523be40;

// lib::L2CAgent::L2CAgent(lua_State*)
void L2CAgent_710372da00(lib::L2CAgent* this_, void* ls) {
    this_->_vt = reinterpret_cast<void**>(&DAT_710523be40);
    this_->lua_state = ls;
    this_->alloc_ptr = nullptr;
    this_->unk_0x18 = 0;
    this_->linked_list_head = nullptr;
    this_->unk_0x28 = 0;
    this_->rate_raw = 0x3f800000u;  // 1.0f as raw bits
}

// ============================================================
// L2CValue type accessors — check type tag, return converted value
// ============================================================

// 0x7103734b80 (56 bytes) — as_integer: type 7/2 → raw, type 3 → fcvtzs
s64 as_integer_7103734b80(lib::L2CValue* this_) {
    u32 type = this_->type;
    if (type == 7 || type == 2) {
        return this_->int_val;
    }
    if (type == 3) {
        return (s64)this_->float_val;
    }
    return 0;
}

// 0x7103734f10 (56 bytes) — as_number: type 7/2 → scvtf, type 3 → raw float
f32 as_number_7103734f10(lib::L2CValue* this_) {
    u32 type = this_->type;
    if (type == 7 || type == 2) {
        return (f32)this_->int_val;
    }
    if (type == 3) {
        return this_->float_val;
    }
    return 0.0f;
}

// 0x7103735ff0 (52 bytes) — as_string: type 8 → check SSO, return ptr
// SSO string: byte[0] & 1 ? heap (ptr at +0x10) : inline (data at +0x1)
extern "C" __attribute__((visibility("hidden"))) char DAT_7104866c2e;  // empty string ""

const char* as_string_7103735ff0(lib::L2CValue* this_) {
    if (this_->type != 8) return &DAT_7104866c2e;
    u8* str = reinterpret_cast<u8*>(this_->ptr_val);
    if (str[0] & 1) {
        return *reinterpret_cast<const char**>(str + 0x10);
    }
    return reinterpret_cast<const char*>(str + 1);
}

// ============================================================
// ~L2CValue destructor — handles refcounting and freeing for types 5/6/8
// 0x7103733f20 (164 bytes)
// Type 5 (table): decrement refcount at +0, if zero call table cleanup + free
// Type 6 (inner func): decrement refcount at +8, if zero free
// Type 8 (inner string): free heap buffer if SSO, then free string struct
// ============================================================

void FUN_7103733900(u8*);  // L2CTable cleanup, defined below

void dtor_L2CValue_7103733f20(lib::L2CValue* this_) {
    u32 type = this_->type;
    u8* ptr;
    if (type == 8) goto handle_8;
    if (type == 6) goto handle_6;
    if (type != 5) return;
    // type 5: table — decrement refcount at +0, cleanup + free if zero
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    {
        s32 rc = --*reinterpret_cast<s32*>(ptr);
        if (!ptr || rc > 0) return;
    }
    FUN_7103733900(ptr);
    asm volatile("");
    jeFree_710392e590(ptr);
    return;
handle_8:
    // type 8: inner string — free heap buffer if SSO, then free struct
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    if (!ptr) return;
    if ((ptr[0] & 1) != 0) {
        void* heap = *reinterpret_cast<void**>(ptr + 0x10);
        if (heap) jeFree_710392e590(heap);
    }
    jeFree_710392e590(ptr);
    return;
handle_6:
    // type 6: inner function — decrement refcount at +8, free if zero
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    {
        s32 rc = --*reinterpret_cast<s32*>(ptr + 8);
        if (!ptr || rc > 0) return;
    }
    jeFree_710392e590(ptr);
}

// ============================================================
// operator<(L2CValue const&) — less-than comparison
// 0x7103734bc0 (172 bytes)
// Same-type int: signed compare; same-type float: ordered compare
// Cross-type int/float: convert int to float then compare
// ============================================================

u8 operator_lt_7103734bc0(lib::L2CValue* this_, lib::L2CValue* other) {
    u32 t1 = this_->type;
    u32 t2 = other->type;
    if (t1 == t2) {
        if (t1 == 3) {
            return this_->float_val < other->float_val;
        }
        if (t1 == 2) {
            return this_->int_val < other->int_val;
        }
        return 0;
    }
    if (t1 == 2 && t2 == 3) {
        f32 a = (f32)this_->int_val;
        f32 b = other->float_val;
        return b > a;
    }
    u8 result = 0;
    if (t1 == 3 && t2 == 2) {
        f32 a = this_->float_val;
        f32 b = (f32)other->int_val;
        result = a < b;
    }
    return result;
}

// ============================================================
// operator<=(L2CValue const&) — less-than-or-equal comparison
// 0x7103734c70 (172 bytes)
// Same pattern as operator< with le/ge/ls condition codes
// ============================================================

u8 operator_le_7103734c70(lib::L2CValue* this_, lib::L2CValue* other) {
    u32 t1 = this_->type;
    u32 t2 = other->type;
    if (t1 == t2) {
        if (t1 == 3) {
            return this_->float_val <= other->float_val;
        }
        if (t1 == 2) {
            return this_->int_val <= other->int_val;
        }
        return 0;
    }
    if (t1 == 2 && t2 == 3) {
        f32 a = (f32)this_->int_val;
        f32 b = other->float_val;
        return b >= a;
    }
    u8 result = 0;
    if (t1 == 3 && t2 == 2) {
        f32 a = this_->float_val;
        f32 b = (f32)other->int_val;
        result = a <= b;
    }
    return result;
}

// ============================================================
// operator==(L2CValue const&) — equality comparison
// 0x7103734520 (680 bytes)
// [derived: Ghidra shows same-type comparison per type tag,
//  cross-type int/float promotion, table metamethod __eq,
//  string SSO-aware length + byte comparison]
// ============================================================

extern "C" void FUN_71037347d0(lib::L2CValue*, lib::L2CValue*, u64, lib::L2CValue*);

u8 operator_eq_7103734520(lib::L2CValue* this_, lib::L2CValue* other) {
    s32 t1 = (s32)this_->type;
    s32 t2 = (s32)other->type;
    if (t1 != t2) {
        // Different types
        if (t1 == 0) {
            // this is nil
            if (t2 != 7 && t2 != 2) return 0;
            s64 val = other->int_val;
            return val == 0;
        }
        if (t1 == 7 || t1 == 2) {
            // this is int/hash
            if (t2 == 0) {
                s64 val = this_->int_val;
                return val == 0;
            }
            if (t2 == 7 || t2 == 2) return this_->raw == other->raw;
        } else if (t2 == 0) {
            // other is nil, this is something else
            if (t1 != 7 && t1 != 2) return 0;
            s64 val = this_->int_val;
            return val == 0;
        }
        // Cross-type int/float promotion
        if (t1 == 7 || t1 == 2) {
            if (t2 == 3) {
                f32 fv = other->float_val;
                s64 iv = this_->int_val;
                return iv == (s64)fv;
            }
            if (t1 != 3) return 0;
        } else if (t1 != 3) {
            if (t1 != 2) return 0;
            // t1 == 2 handled above (int/hash check)
            if (t2 == 3) {
                f32 fv = other->float_val;
                s64 iv = this_->int_val;
                return iv == (s64)fv;
            }
            return 0;
        }
        // t1 == 3 (float), need t2 to be int/hash
        if (t2 != 7 && t2 != 2) return 0;
        f32 fv = this_->float_val;
        s64 iv = other->int_val;
        return iv == (s64)fv;
    }

    // Same types
    u8 result = 1;
    switch (t1) {
    case 0:
        break;
    case 1:
        result = (this_->bool_val == other->bool_val);
        break;
    case 3:
        result = (this_->float_val == other->float_val);
        break;
    case 5: {
        // Table: pointer equality or metamethod
        if (this_->raw == other->raw) return 1;
        lib::L2CValue temp;
        FUN_71037347d0(&temp, this_, 0x4ea42772dULL, other);
        // Inline as_bool on temp
        result = 0;
        u32 rt = temp.type;
        if (rt == 0) {
            // nil → false
        } else if (rt == 1) {
            result = ((s32)temp.bool_val > 0);
        } else if (rt == 2 || rt == 7) {
            result = (temp.raw != 0);
        } else if (rt == 3) {
            result = (temp.float_val != 0.0f);
        } else if (rt == 8) {
            // string length check
            u8* str = reinterpret_cast<u8*>(temp.ptr_val);
            u64 len;
            if ((str[0] & 1) == 0) {
                len = (u64)(str[0] >> 1);
            } else {
                len = *reinterpret_cast<u64*>(str + 8);
            }
            result = (len != 0);
        } else {
            result = 1;
        }
        dtor_L2CValue_7103733f20(&temp);
        break;
    }
    case 8: {
        // String: SSO-aware comparison
        u8* s1 = reinterpret_cast<u8*>(this_->ptr_val);
        u8* s2 = reinterpret_cast<u8*>(other->ptr_val);
        u8 b1 = s1[0];
        u8 b2 = s2[0];
        // Get lengths
        u64 len1 = (b1 & 1) == 0 ? (u64)(b1 >> 1) : *reinterpret_cast<u64*>(s1 + 8);
        u64 len2 = (b2 & 1) == 0 ? (u64)(b2 >> 1) : *reinterpret_cast<u64*>(s2 + 8);
        if (len1 != len2) return 0;
        // Get data pointers
        u8* d1 = (b1 & 1) == 0 ? s1 + 1 : *reinterpret_cast<u8**>(s1 + 0x10);
        u8* d2 = (b2 & 1) == 0 ? s2 + 1 : *reinterpret_cast<u8**>(s2 + 0x10);
        if ((b1 & 1) == 0) {
            // Short string: byte-by-byte
            if (len1 == 0) return 1;
            s64 i = -(s64)(u64)(b1 >> 1);
            u8* p = s1;
            do {
                p++;
                if (*p != *d2) return 0;
                d2++;
                i++;
            } while (i != 0);
            return 1;
        }
        // Long string: memcmp
        if (len1 != 0) {
            return memcmp(d1, d2, len1) == 0;
        }
        return 1;
    }
    default:
        result = (this_->raw == other->raw);
        break;
    }
    return result;
}

// ============================================================
// operator[] — L2CValue table index access (shrink-wrapped)
// 0x7103735d80 (48 bytes)
// Prologue is inside the type==5 branch (compiler shrink-wraps)
// ============================================================

extern "C" void* FUN_71037339f0(void*, int);
extern "C" __attribute__((visibility("hidden"))) u8 DAT_710593a3a8;

void* operator_index_7103735d80(lib::L2CValue* this_, int index) {
    if (this_->type != 5) return &DAT_710593a3a8;
    void* table = this_->ptr_val;
    void* result = FUN_71037339f0(table, index);
    asm volatile("");
    return result;
}

// ============================================================
// sort — wrapper for L2CAgent lua sort
// 0x710372e9f0 (32 bytes)
// ============================================================

extern "C" void FUN_710372ea10(void*, void*);

void sort_710372e9f0(void* this_, lib::L2CValue* p1) {
    u8* ls = reinterpret_cast<u8*>(p1->ptr_val);
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

// 0x7103733000 (140 bytes) — math_atan: arc tangent (2-arg, uses atan2f)
// [derived: Ghidra shows atan2f(__y, __x) with two as_number extractions]
lib::L2CValue math_atan_7103733000(lib::L2CValue* p1, lib::L2CValue* p2) {
    lib::L2CValue ret;
    u32 t1 = p1->type;
    f32 y;
    if (t1 == 7 || t1 == 2) {
        y = (f32)p1->int_val;
    } else if (t1 == 3) {
        y = p1->float_val;
    } else {
        y = 0.0f;
    }
    u32 t2 = p2->type;
    f32 x = 0.0f;
    if (t2 == 7 || t2 == 2) {
        x = (f32)p2->int_val;
    } else if (t2 == 3) {
        x = p2->float_val;
    }
    f32 result = atan2f(y, x);
    asm volatile("");
    ret.type = 3;
    ret.float_val = result;
    return ret;
}

// 0x7103733310 (184 bytes) — math_log: logarithm with base
// [derived: Ghidra shows log10f special case when base==10.0, else logf(val)/logf(base)]
lib::L2CValue math_log_7103733310(lib::L2CValue* p1, lib::L2CValue* p2) {
    lib::L2CValue ret;
    u32 t1 = p1->type;
    f32 value = 0.0f;
    if (t1 == 7 || t1 == 2) {
        value = (f32)p1->int_val;
    } else if (t1 == 3) {
        value = p1->float_val;
    }
    u32 t2 = p2->type;
    f32 base = 0.0f;
    if (t2 == 7 || t2 == 2) {
        base = (f32)p2->int_val;
    } else if (t2 == 3) {
        base = p2->float_val;
    }
    if (base == 10.0f) {
        value = log10f(value);
    } else {
        value = logf(value) / logf(base);
    }
    asm volatile("");
    ret.type = 3;
    ret.float_val = value;
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
// Binary arithmetic operators — mixed int/float with table metamethod fallback
// ============================================================

// 0x7103735a50 (168 bytes) — operator/: division (always float)
// [derived: Ghidra + disasm, if either table → metamethod, else as_number/as_number → fdiv]
lib::L2CValue operator_div_7103735a50(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    u32 t1 = this_->type;
    if (t1 == 5) {
        FUN_71037347d0(&ret, this_, 0x5ad88d7e8ULL, other);
        return ret;
    }
    u32 t2 = other->type;
    if (t2 == 5) {
        FUN_71037347d0(&ret, this_, 0x5ad88d7e8ULL, other);
        return ret;
    }
    f32 b = 0.0f;
    f32 a;
    if (t1 == 7 || t1 == 2) {
        a = (f32)this_->int_val;
    } else if (t1 == 3) {
        a = this_->float_val;
    } else {
        a = 0.0f;
    }
    if (t2 == 7 || t2 == 2) {
        b = (f32)other->int_val;
    } else if (t2 == 3) {
        b = other->float_val;
    }
    ret.type = 3;
    ret.float_val = a / b;
    return ret;
}

// 0x7103735730 (240 bytes) — operator-: subtraction
// [derived: Ghidra shows same-type int→sub, same-type float→fsub,
//  cross-type int/float→scvtf+fsub, table→metamethod dispatch]
lib::L2CValue operator_sub_7103735730(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    s32 t1 = this_->type;
    s32 t2 = other->type;
    if (t1 == t2) {
        if (t1 == 5) goto metamethod;
        if (t1 != 3) {
            if (t1 == 2) {
                s64 a = this_->int_val;
                s64 b = other->int_val;
                ret.type = 2;
                ret.int_val = a - b;
                return ret;
            }
            ret.type = 2;
            ret.raw = 0;
            return ret;
        }
        f32 result = this_->float_val - other->float_val;
        ret.type = 3;
        ret.float_val = result;
        return ret;
    }
    {
        f32 a, b;
        if (t1 == 2 && t2 == 3) {
            a = (f32)this_->int_val;
            b = other->float_val;
        } else if (t1 == 3 && t2 == 2) {
            a = this_->float_val;
            b = (f32)other->int_val;
        } else {
            if (t1 != 5 && t2 != 5) {
                ret.type = 3;
                ret.float_val = 0.0f;
                return ret;
            }
metamethod:
            FUN_71037347d0(&ret, this_, 0x5b58a6ff4ULL, other);
            return ret;
        }
        ret.type = 3;
        ret.float_val = a - b;
        return ret;
    }
}

// 0x7103735820 (244 bytes) — operator*: multiplication
// [derived: Ghidra shows same-type int→mul, same-type float→fmul,
//  cross-type int/float→scvtf+fmul, table→metamethod dispatch]
lib::L2CValue operator_mul_7103735820(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    s32 t1 = this_->type;
    s32 t2 = other->type;
    if (t1 == t2) {
        if (t1 == 5) goto metamethod;
        if (t1 != 3) {
            if (t1 != 2) {
                ret.type = 2;
                ret.raw = 0;
                return ret;
            }
            s64 a = this_->int_val;
            s64 b = other->int_val;
            ret.type = 2;
            ret.int_val = b * a;
            return ret;
        }
        f32 result = this_->float_val * other->float_val;
        ret.type = 3;
        ret.float_val = result;
        return ret;
    }
    if (t1 == 2 && t2 == 3) {
        f32 result = other->float_val * (f32)this_->int_val;
        ret.type = 3;
        ret.float_val = result;
        return ret;
    }
    if (t1 == 3 && t2 == 2) {
        f32 result = this_->float_val * (f32)other->int_val;
        ret.type = 3;
        ret.float_val = result;
        return ret;
    }
    if (t1 != 5 && t2 != 5) {
        ret.type = 3;
        ret.float_val = 0.0f;
        return ret;
    }
metamethod:
    FUN_71037347d0(&ret, this_, 0x5ad88d0e8ULL, other);
    return ret;
}

// ============================================================
// Binary bitwise operators — all follow as_integer(a) OP as_integer(b) → type 2
// as_integer pattern: type 7/2 → raw u64, type 3 → (u64)(s64)float, else 0
// ============================================================

// 0x7103735b00 (124 bytes) — operator&: bitwise AND
lib::L2CValue operator_and_7103735b00(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    u64 a, b;
    u32 t1 = this_->type;
    if (t1 == 7 || t1 == 2) {
        a = this_->uint_val;
    } else if (t1 == 3) {
        a = (u64)(s64)this_->float_val;
    } else {
        a = 0;
    }
    u32 t2 = other->type;
    if (t2 == 7 || t2 == 2) {
        b = other->uint_val;
    } else if (t2 == 3) {
        b = (u64)(s64)other->float_val;
    } else {
        b = 0;
    }
    u64 result = b & a;
    asm volatile("");
    ret.type = 2;
    ret.raw = result;
    return ret;
}

// 0x7103735b80 (124 bytes) — operator|: bitwise OR
lib::L2CValue operator_or_7103735b80(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    u64 a, b;
    u32 t1 = this_->type;
    if (t1 == 7 || t1 == 2) {
        a = this_->uint_val;
    } else if (t1 == 3) {
        a = (u64)(s64)this_->float_val;
    } else {
        a = 0;
    }
    u32 t2 = other->type;
    if (t2 == 7 || t2 == 2) {
        b = other->uint_val;
    } else if (t2 == 3) {
        b = (u64)(s64)other->float_val;
    } else {
        b = 0;
    }
    u64 result = b | a;
    asm volatile("");
    ret.type = 2;
    ret.raw = result;
    return ret;
}

// 0x7103735c00 (124 bytes) — operator^: bitwise XOR
lib::L2CValue operator_xor_7103735c00(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    u64 a, b;
    u32 t1 = this_->type;
    if (t1 == 7 || t1 == 2) {
        a = this_->uint_val;
    } else if (t1 == 3) {
        a = (u64)(s64)this_->float_val;
    } else {
        a = 0;
    }
    u32 t2 = other->type;
    if (t2 == 7 || t2 == 2) {
        b = other->uint_val;
    } else if (t2 == 3) {
        b = (u64)(s64)other->float_val;
    } else {
        b = 0;
    }
    u64 result = b ^ a;
    asm volatile("");
    ret.type = 2;
    ret.raw = result;
    return ret;
}

// 0x7103735c80 (124 bytes) — operator<<: left shift
// [derived: Ghidra shows (long)lVar2 << (ulong & 0x3f)]
lib::L2CValue operator_lsh_7103735c80(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    s64 a;
    u64 b;
    u32 t1 = this_->type;
    if (t1 == 7 || t1 == 2) {
        a = this_->int_val;
    } else if (t1 == 3) {
        a = (s64)this_->float_val;
    } else {
        a = 0;
    }
    u32 t2 = other->type;
    if (t2 == 7 || t2 == 2) {
        b = other->uint_val;
    } else if (t2 == 3) {
        b = (u64)(s64)other->float_val;
    } else {
        b = 0;
    }
    s64 result = a << (b & 0x3f);
    asm volatile("");
    ret.type = 2;
    ret.int_val = result;
    return ret;
}

// 0x7103735d00 (124 bytes) — operator>>: arithmetic right shift
// [derived: Ghidra shows (long)lVar2 >> (ulong & 0x3f)]
lib::L2CValue operator_rsh_7103735d00(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    s64 a;
    u64 b;
    u32 t1 = this_->type;
    if (t1 == 7 || t1 == 2) {
        a = this_->int_val;
    } else if (t1 == 3) {
        a = (s64)this_->float_val;
    } else {
        a = 0;
    }
    u32 t2 = other->type;
    if (t2 == 7 || t2 == 2) {
        b = other->uint_val;
    } else if (t2 == 3) {
        b = (u64)(s64)other->float_val;
    } else {
        b = 0;
    }
    s64 result = a >> (b & 0x3f);
    asm volatile("");
    ret.type = 2;
    ret.int_val = result;
    return ret;
}

// ============================================================
// operator[](Hash40) — table lookup by hash key
// 0x7103735db0 (64 bytes)
// ============================================================

extern "C" void* treeMapFindOrInsert_7103733d50(void*, u64*);

void* operator_index_hash_7103735db0(lib::L2CValue* this_, u64 hash) {
    u64 local_hash = hash;
    if (this_->type != 5) return &DAT_710593a3a8;
    void* table = this_->ptr_val;
    return treeMapFindOrInsert_7103733d50(table, &local_hash);
}

// ============================================================
// L2CAgent sort — 2-arg sort with comparator
// 0x71037301b0 (52 bytes)
// ============================================================

extern "C" void FUN_71037301f0(void*, void*, void*);

void sort_71037301b0(void* this_, lib::L2CValue* p1, void* p2) {
    u8* table = reinterpret_cast<u8*>(p1->ptr_val);
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
void dtor_L2CAgent_710372da20(lib::L2CAgent* this_) {
    this_->_vt = reinterpret_cast<void**>(&DAT_710523be40);
    u8* node = this_->linked_list_head;
    while (node) {
        u8* next = *reinterpret_cast<u8**>(node);
        jeFree_710392e590(node);
        node = next;
    }
    void* p = this_->alloc_ptr;
    this_->alloc_ptr = nullptr;
    if (p) {
        jeFree_710392e590(p);
    }
}

// 0x710372da80 (84 bytes) — ~L2CAgent [D0 deleting destructor]
// Same as D1 but also frees this
void dtor_D0_L2CAgent_710372da80(lib::L2CAgent* this_) {
    this_->_vt = reinterpret_cast<void**>(&DAT_710523be40);
    u8* node = this_->linked_list_head;
    while (node) {
        u8* next = *reinterpret_cast<u8**>(node);
        jeFree_710392e590(node);
        node = next;
    }
    void* p = this_->alloc_ptr;
    this_->alloc_ptr = nullptr;
    if (p) {
        jeFree_710392e590(p);
    }
    jeFree_710392e590(this_);
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

// ============================================================
// nn::err::ShowError wrapper
// 0x7103754e50 (8 bytes)
// Tail call to nn::err::ShowError
// ============================================================
void ShowError_wrapper_7103754e50(u32 error_code) {
    nn::err::ShowError(error_code);
}

// ============================================================
// L2CValue::as_bool() — type-dependent truthiness check
// 0x7103735f30 (96 bytes)
// [derived: Ghidra shows switch on type tag with per-type truthiness]
// type 0 (nil): false
// type 1 (bool): val > 0
// type 2/7 (int/hash): val != 0
// type 3 (float): val != 0.0f
// default (ptr/table/func/string): true
// ============================================================
u8 as_bool_7103735f30(lib::L2CValue* this_) {
    u8 result = 0;
    switch (this_->type) {
    case 0:
        break;
    case 1:
        return (u8)((s32)this_->bool_val > 0);
    case 2:
    case 7:
        return this_->int_val != 0;
    case 3:
        return this_->float_val != 0.0f;
    default:
        result = 1;
        break;
    }
    return result;
}

// ============================================================
// math_fmod — modulo with integer fast-path
// 0x7103733180 (288 bytes)
// [derived: Ghidra shows integer sdiv/msub path when both are int/hash
//  with divisor > 0; otherwise float path via fmodf]
// Integer modulo: result = a - (a / b) * b (Python-style: b must be > 0)
// Float modulo: fmodf(a_float, b_float)
// ============================================================
lib::L2CValue math_fmod_7103733180(lib::L2CValue* p1, lib::L2CValue* p2) {
    lib::L2CValue ret;
    s32 t1 = p1->type;
    f32 fval2 = 0.0f;
    if (t1 == 7) goto check_int_path;
    if (t1 == 3) goto float_p1;
    if (t1 != 2) goto float_path_default;
check_int_path:
    {
        s32 t2 = p2->type;
        if (t2 == 7 || t2 == 2) {
            s64 b = p2->int_val;
            if (b < 1) {
                ret.type = 2;
                ret.raw = 0;
                return ret;
            }
            s64 a;
            if (t1 == 7 || t1 == 2) {
                a = p1->int_val;
            } else if (t1 == 3) {
                a = (s64)p1->float_val;
            } else {
                a = 0;
            }
            s64 q = 0;
            if (b != 0) {
                q = a / b;
            }
            ret.type = 2;
            ret.int_val = a - q * b;
            return ret;
        }
    }
    // Float path: extract p1 as float
    {
        f32 fval1;
        if (t1 == 7 || t1 == 2) {
            fval1 = (f32)p1->int_val;
        } else if (t1 == 3) {
float_p1:
            fval1 = p1->float_val;
        } else {
float_path_default:
            fval1 = 0.0f;
        }
        // Extract p2 as float
        {
            s32 t2 = p2->type;
            if (t2 == 7 || t2 == 2) {
                fval2 = (f32)p2->int_val;
            } else if (t2 == 3) {
                fval2 = p2->float_val;
            }
        }
        fval2 = fmodf(fval1, fval2);
        asm volatile("");
        ret.type = 3;
        ret.float_val = fval2;
        return ret;
    }
}

// ============================================================
// operator% — Python-style modulo (result has same sign as divisor)
// 0x7103735920 (292 bytes)
// [derived: Ghidra shows integer path with sign correction: if signs differ
//  and remainder != 0, add divisor to get Python semantics. Float path
//  uses fmodf with same sign correction.]
// ============================================================
lib::L2CValue operator_mod_7103735920(lib::L2CValue* this_, lib::L2CValue* other) {
    lib::L2CValue ret;
    s32 t1 = this_->type;
    f32 fval2 = 0.0f;
    if (t1 == 7) goto check_int_path;
    if (t1 == 3) goto float_p1;
    if (t1 != 2) goto float_path_default;
check_int_path:
    {
        s32 t2 = other->type;
        if (t2 == 7 || t2 == 2) {
            u64 b = other->uint_val;
            if ((s64)b > 0) {
                u64 a = this_->uint_val;
                s64 q = 0;
                if (b != 0) {
                    q = (s64)a / (s64)b;
                }
                s64 rem = (s64)a - q * (s64)b;
                ret.type = 2;
                // Python-style sign correction: result has same sign as divisor
                // [derived: ccmp+csel pattern in binary — conditional zero of divisor]
                u64 adj = ((s64)(a ^ b) < 0 && rem != 0) ? b : 0;
                ret.int_val = (s64)adj + rem;
                return ret;
            }
            ret.type = 2;
            ret.raw = 0;
            return ret;
        }
    }
    // Float path
    {
        f32 fval1;
        if (t1 == 7 || t1 == 2) {
            fval1 = (f32)this_->int_val;
        } else if (t1 == 3) {
float_p1:
            fval1 = this_->float_val;
        } else {
float_path_default:
            fval1 = 0.0f;
        }
        {
            s32 t2 = other->type;
            if (t2 == 7 || t2 == 2) {
                fval2 = (f32)other->int_val;
            } else if (t2 == 3) {
                fval2 = other->float_val;
            }
        }
        f32 fmod_result = fmodf(fval1, fval2);
        f32 adjusted = fval2 + fmod_result;
        if (fval2 * fmod_result >= 0.0f) {
            adjusted = fmod_result;
        }
        asm volatile("");
        ret.type = 3;
        ret.float_val = adjusted;
        return ret;
    }
}

// ============================================================
// OOM retry allocators — used by L2CValue copy ctor, L2CTable ctor, etc.
// Pattern: alloc(); if (!ptr && OOM_handler) { handler->retry(); alloc(); }
// ============================================================

// 0x710373df50 (120 bytes) — alloc_with_oom_retry, fixed 0x10 alignment
// [derived: Ghidra shows je_aligned_alloc(0x10, param_1)]
void* alloc_aligned16_710373df50(long size) {
    long result = size;
    if (size != 0) {
        result = (long)je_aligned_alloc(0x10, size);
        if (result == 0) {
            if (DAT_7105331f00 != nullptr) {
                u32 local_14 = 0;
                long local_28 = size;
                u64 rv = reinterpret_cast<u64 (*)(long*, u32*, long*)>(
                    *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
                )(DAT_7105331f00, &local_14, &local_28);
                if ((rv & 1) != 0) {
                    result = (long)je_aligned_alloc(0x10, size);
                    if (result != 0) return reinterpret_cast<void*>(result);
                }
            }
            result = 0;
        }
    }
    return reinterpret_cast<void*>(result);
}

// 0x710373dfd0 (116 bytes) — alloc_with_oom_retry, caller-specified alignment
// [derived: Ghidra shows je_aligned_alloc(param_1, param_2)]
void* alloc_with_retry_710373dfd0(unsigned long align, long size) {
    if (size != 0) {
        long result = (long)je_aligned_alloc(align, size);
        if (result != 0) return reinterpret_cast<void*>(result);
        if (DAT_7105331f00 != nullptr) {
            u32 local_24 = 0;
            long local_30 = size;
            u64 rv = reinterpret_cast<u64 (*)(long*, u32*, long*)>(
                *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
            )(DAT_7105331f00, &local_24, &local_30);
            if ((rv & 1) != 0) {
                result = (long)je_aligned_alloc(align, size);
                if (result != 0) return reinterpret_cast<void*>(result);
            }
        }
    }
    return nullptr;
}

// ============================================================
// RB tree node destructor — recursive
// 0x71037339b0 (matches FUN_7103716100/FUN_710376a190 pattern but calls ~L2CValue)
// [derived: Ghidra shows recurse(left), recurse(right), ~L2CValue(node+5), free(node)]
// ============================================================

void FUN_71037339b0(u8** node) {
    if (!node) return;
    FUN_71037339b0(reinterpret_cast<u8**>(node[0]));
    FUN_71037339b0(reinterpret_cast<u8**>(node[1]));
    dtor_L2CValue_7103733f20(reinterpret_cast<lib::L2CValue*>(node + 5));
    jeFree_710392e590(node);
}

// ============================================================
// L2CTable::cleanup — destroys metatable, tree, and vector contents
// 0x7103733900 (164 bytes)
// [derived: Ghidra shows metatable refcount at +0x40, tree at +0x28,
//  vector at +0x08/+0x10, each element 0x10 bytes (L2CValue)]
// ============================================================

void FUN_7103733900(u8* this_) {
    // Release metatable at +0x40
    s32* meta = *reinterpret_cast<s32**>(this_ + 0x40);
    if (meta != nullptr) {
        s32 old = *meta;
        s32 rc = old - 1;
        *meta = rc;
        if (rc == 0 || old < 1) {
            FUN_7103733900(reinterpret_cast<u8*>(meta));
            jeFree_710392e590(meta);
        }
    }
    // Destroy RB tree nodes at +0x28
    FUN_71037339b0(*reinterpret_cast<u8***>(this_ + 0x28));
    // Reverse-iterate vector, destroy each L2CValue
    u8* begin = *reinterpret_cast<u8**>(this_ + 0x08);
    if (begin != nullptr) {
        u8* end = *reinterpret_cast<u8**>(this_ + 0x10);
        if (end == begin) {
            *reinterpret_cast<u8**>(this_ + 0x10) = begin;
        } else {
            do {
                end -= 0x10;
                dtor_L2CValue_7103733f20(reinterpret_cast<lib::L2CValue*>(end));
            } while (begin != end);
            end = *reinterpret_cast<u8**>(this_ + 0x08);
            *reinterpret_cast<u8**>(this_ + 0x10) = begin;
        }
        if (end != nullptr) {
            jeFree_710392e590(end);
        }
    }
}

// ============================================================
// L2CValue copy constructor — L2CValue(const L2CValue&)
// 0x7103733fe0 (224 bytes)
// [derived: Ghidra shows type!=8 path copies raw + bumps refcount,
//  type==8 path allocates 0x18 bytes + basic_string copy ctor]
// ============================================================

// basic_string copy ctor (libc++)
extern "C" void _ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_(void* dst, void* src);

void FUN_7103733fe0(lib::L2CValue* this_, const lib::L2CValue* src) {
    s32 type = src->type;
    this_->type = type;
    u8* ptr;
    if (type != 8) {
        ptr = reinterpret_cast<u8*>(src->ptr_val);
        goto store_and_refcount;
    }
    // type 8: allocate new string struct
    ptr = reinterpret_cast<u8*>(je_aligned_alloc(0x10, 0x18));
    if (ptr == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 local_24 = 0;
            u64 local_38 = 0x18;
            u64 rv = reinterpret_cast<u64 (*)(long*, u32*, u64*)>(
                *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
            )(DAT_7105331f00, &local_24, &local_38);
            if ((rv & 1) != 0) {
                ptr = reinterpret_cast<u8*>(je_aligned_alloc(0x10, 0x18));
                if (ptr != nullptr) goto do_string_copy;
            }
        }
        ptr = nullptr;
    }
do_string_copy:
    _ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_(
        ptr, src->ptr_val);
    type = this_->type;
store_and_refcount:
    this_->ptr_val = ptr;
    if (type == 6) {
        ptr += 8;
    } else if (type != 5) {
        return;
    }
    *reinterpret_cast<s32*>(ptr) += 1;
}

// ============================================================
// L2CValue::operator=(const L2CValue&) — copy assignment
// 0x7103734330 (356 bytes)
// [derived: Ghidra shows inlined ~L2CValue + inlined copy ctor, returns this]
// Phase 1: destroy old value (types 8/6/5 have cleanup)
// Phase 2: copy from source (type 8 allocates new string, others raw copy + refcount)
// ============================================================

void* operator_assign_7103734330(lib::L2CValue* this_, const lib::L2CValue* src) {
    u32 type = this_->type;
    u8* ptr;
    if (type == 8) goto handle_8;
    if (type == 6) goto handle_6;
    if (type != 5) goto phase2;
    // type 5: table — decrement refcount at +0, cleanup + free if zero
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    {
        s32 old = *reinterpret_cast<s32*>(ptr);
        s32 rc = old - 1;
        *reinterpret_cast<s32*>(ptr) = rc;
        if (!ptr || (rc != 0 && old >= 1)) goto phase2;
    }
    FUN_7103733900(ptr);
    goto free_old;
handle_8:
    // type 8: free SSO heap buffer if large, then free string struct
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    if (!ptr) goto phase2;
    if ((ptr[0] & 1) != 0) {
        void* heap = *reinterpret_cast<void**>(ptr + 0x10);
        if (heap) jeFree_710392e590(heap);
    }
    goto free_old;
handle_6:
    // type 6: inner function — decrement refcount at +8, free if zero
    ptr = reinterpret_cast<u8*>(this_->ptr_val);
    {
        s32 old = *reinterpret_cast<s32*>(ptr + 8);
        s32 rc = old - 1;
        *reinterpret_cast<s32*>(ptr + 8) = rc;
        if (!ptr || (rc != 0 && old >= 1)) goto phase2;
    }
free_old:
    jeFree_710392e590(ptr);
phase2:
    // Phase 2: Copy from source (inlined copy ctor)
    type = src->type;
    this_->type = type;
    u8* new_ptr;
    if (type != 8) {
        new_ptr = reinterpret_cast<u8*>(src->ptr_val);
        goto store_and_refcount;
    }
    // type 8: allocate new string struct + copy
    new_ptr = reinterpret_cast<u8*>(je_aligned_alloc(0x10, 0x18));
    if (new_ptr == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 local_24 = 0;
            u64 local_38 = 0x18;
            u64 rv = reinterpret_cast<u64 (*)(long*, u32*, u64*)>(
                *reinterpret_cast<void**>(*DAT_7105331f00 + 0x30)
            )(DAT_7105331f00, &local_24, &local_38);
            if ((rv & 1) != 0) {
                new_ptr = reinterpret_cast<u8*>(je_aligned_alloc(0x10, 0x18));
                if (new_ptr != nullptr) goto do_string_copy;
            }
        }
        new_ptr = nullptr;
    }
do_string_copy:
    _ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_(
        new_ptr, src->ptr_val);
    type = this_->type;
store_and_refcount:
    this_->ptr_val = new_ptr;
    if (type == 6) {
        new_ptr += 8;
    } else if (type != 5) {
        return this_;
    }
    *reinterpret_cast<s32*>(new_ptr) += 1;
    return this_;
}

// ============================================================
// L2CValue::length() — returns string length or table size
// 0x7103735ea0 (136 bytes)
// [derived: Ghidra shows SSO string check + table vector reverse scan]
// ============================================================

u64 length_7103735ea0(lib::L2CValue* this_) {
    u32 type = this_->type;
    if (__builtin_expect(type == 8, 0)) {
        // String length: SSO check
        u8* str = reinterpret_cast<u8*>(this_->ptr_val);
        u8 b = str[0];
        if ((b & 1) == 0) {
            return (u64)(b >> 1);
        }
        return *reinterpret_cast<u64*>(str + 8);
    }
    if (type != 5) return 0;
    // Table length: reverse-scan for last non-nil element
    u8* table = reinterpret_cast<u8*>(this_->ptr_val);
    long base;
    long end_ptr;
    // ldp loads base and end together
    base = *reinterpret_cast<long*>(table + 8);
    end_ptr = *reinterpret_cast<long*>(table + 0x10);
    u64 diff = (u64)(end_ptr - base);
    s64 count = (s64)(s32)(diff >> 4);
    if (count < 2) return 0;
    u32* p = reinterpret_cast<u32*>(base + (count << 4));
    u64 n = (u64)count;
    do {
        p -= 4;  // back one L2CValue (0x10 bytes)
        if ((s64)n < 2) return 0;
        n -= 1;
    } while (*p == 0);
    return n;
}

// ============================================================
// operator[](L2CValue const&) — table index with L2CValue key
// 0x7103735df0 (144 bytes)
// [derived: Ghidra shows int/float → FUN_71037339f0, hash → treeMapFindOrInsert_7103733d50]
// ============================================================

void* operator_index_lv_7103735df0(lib::L2CValue* this_, lib::L2CValue* key) {
    if (this_->type != 5) return &DAT_710593a3a8;
    s32 key_type = key->type;
    if ((u32)(key_type - 2) < 2) {
        long index;
        if (key_type == 3) {
            index = (long)key->float_val;
        } else if (key_type == 2) {
            index = key->int_val;
        } else {
            index = 0;
        }
        void* table = this_->ptr_val;
        return FUN_71037339f0(table, (int)index);
    }
    if (key_type == 7) {
        u64 hash = key->raw;
        void* table = this_->ptr_val;
        return treeMapFindOrInsert_7103733d50(table, &hash);
    }
    return &DAT_710593a3a8;
}

// ============================================================
// L2CAgent::setmetatable — assigns metatable to a table
// 0x710372e950 (152 bytes)
// [derived: Ghidra shows param_4's table stored at +0x38 of param_3's table,
//  with refcount management on old/new metatable]
// ============================================================

void setmetatable_710372e950(lib::L2CValue* ret, u8* this_, lib::L2CValue* table_val, lib::L2CValue* meta_val) {
    // Store agent pointer in meta_val's inner ptr+0x38
    u8* meta_inner = reinterpret_cast<u8*>(meta_val->ptr_val);
    *reinterpret_cast<u8**>(meta_inner + 0x38) = this_;
    // Only assign if both are table type (5)
    if (table_val->type == 5 && meta_val->type == 5) {
        u8* tbl = reinterpret_cast<u8*>(table_val->ptr_val);
        s32* new_meta = reinterpret_cast<s32*>(meta_val->ptr_val);
        // Release old metatable at tbl+0x40
        s32* old_meta = *reinterpret_cast<s32**>(tbl + 0x40);
        if (old_meta != nullptr) {
            s32 old_val = *old_meta;
            s32 new_rc = old_val - 1;
            *old_meta = new_rc;
            if (new_rc == 0 || old_val < 1) {
                FUN_7103733900(reinterpret_cast<u8*>(old_meta));
                jeFree_710392e590(old_meta);
            }
        }
        // Increment refcount on new metatable
        if (new_meta != nullptr) {
            *new_meta += 1;
        }
        // Store new metatable
        *reinterpret_cast<s32**>(tbl + 0x40) = new_meta;
    }
    // Copy-construct return value from table_val
    FUN_7103733fe0(ret, table_val);
}

// ============================================================
// Linked list dual-cleanup destructor
// 0x7103728a40 (116 bytes)
// [derived: Ghidra shows two linked list walks (+0x40/+0x18) with free,
//  plus clearing alloc ptrs at +0x30 and +0x8]
// ============================================================

void FUN_7103728a40(u8* this_) {
    // Walk and free linked list at +0x40
    u8** node = *reinterpret_cast<u8***>(this_ + 0x40);
    while (node != nullptr) {
        u8** next = reinterpret_cast<u8**>(*node);
        jeFree_710392e590(node);
        node = next;
    }
    // Free alloc at +0x30
    void* p = *reinterpret_cast<void**>(this_ + 0x30);
    *reinterpret_cast<u64*>(this_ + 0x30) = 0;
    if (p != nullptr) {
        jeFree_710392e590(p);
    }
    // Walk and free linked list at +0x18
    node = *reinterpret_cast<u8***>(this_ + 0x18);
    while (node != nullptr) {
        u8** next = reinterpret_cast<u8**>(*node);
        jeFree_710392e590(node);
        node = next;
    }
    // Free alloc at +0x8
    void* p2 = *reinterpret_cast<void**>(this_ + 0x08);
    *reinterpret_cast<u64*>(this_ + 0x08) = 0;
    if (p2 != nullptr) {
        jeFree_710392e590(p2);
    }
}

// ============================================================
// Recursive tree visit — calls action on node, then recurses on children
// 0x7103729440 (88 bytes)
// [derived: Ghidra shows FUN_71037294a0 on node, then loop over children]
// ============================================================

extern "C" void FUN_71037294a0(u8*, u8*);

void FUN_7103729440(u8* agent, u8* node) {
    s32 count = *reinterpret_cast<s32*>(node + 0x20);
    FUN_71037294a0(agent, node);
    if (count > 0) {
        long i = 0;
        do {
            u8** children = *reinterpret_cast<u8***>(node + 0x40);
            FUN_7103729440(agent, children[i]);
            i++;
        } while (count != i);
    }
}

// ============================================================
// Recursive tree check — validates node, then recurses on children
// 0x71037293d0 (108 bytes)
// [derived: Ghidra shows FUN_710372aa60 check, then recursive child validation]
// ============================================================

extern "C" u64 FUN_710372aa60(u8*, u8*);

u32 FUN_71037293d0(u8* agent, u8* node) {
    s64 count = (s64)*reinterpret_cast<s32*>(node + 0x20);
    u32 r = (u32)FUN_710372aa60(agent, node);
    if ((r & 1) == 0) return 0;
    if (count > 0) {
        s64 i = 0;
        do {
            u8** children = *reinterpret_cast<u8***>(node + 0x40);
            r = FUN_71037293d0(agent, children[i]);
            if ((r & 1) == 0) return 0;
            asm volatile("");
            i++;
        } while (i < count);
    }
    return 1;
}

// ============================================================
// L2CValue simple type-check accessors
// All are leaf functions returning raw union value if type matches
// ============================================================

// lib::L2CValue::as_hash() const — 0x7103735e80 (32 bytes)
// [derived: Ghidra prototype. Accepts type 7 (hash) OR 2 (integer).
//  Uses ccmp (compare-then-conditional-compare) for dual check.]
u64 as_hash_7103735e80(lib::L2CValue* this_) {
    u32 type = this_->type;
    if (type == 7 || type == 2) {
        return this_->raw;
    }
    return 0;
}

// lib::L2CValue::as_pointer() const — 0x7103735f90 (28 bytes)
// [derived: Ghidra prototype. Type 4 = pointer.]
void* as_pointer_7103735f90(lib::L2CValue* this_) {
    if (this_->type == 4) {
        return this_->ptr_val;
    }
    return nullptr;
}

// lib::L2CValue::as_table() const — 0x7103735fb0 (28 bytes)
// [derived: Ghidra prototype. Type 5 = table (returns L2CTable* as untyped void*).]
void* as_table_7103735fb0(lib::L2CValue* this_) {
    if (this_->type == 5) {
        return this_->ptr_val;
    }
    return nullptr;
}

// lib::L2CValue::as_inner_function() const — 0x7103735fd0 (28 bytes)
// [derived: Ghidra prototype. Type 6 = L2CInnerFunctionBase*.]
void* as_inner_function_7103735fd0(lib::L2CValue* this_) {
    if (this_->type == 6) {
        return this_->ptr_val;
    }
    return nullptr;
}

// ============================================================
// lib::utility::Variadic::Variadic() — default ctor — 0x71037ae490 (8 bytes)
// [derived: Ghidra prototype. Stores xzr to [this] — single 64-bit zero init.]
// Variadic is the va_list-like helper used by L2CValue::push_variadic and
// pop_variadic; layout is { void* table_ptr; ... } with +0x00 as the only
// field the ctor touches.
// ============================================================
void Variadic_ctor_71037ae490(u64* this_) {
    *this_ = 0;
}


} // namespace app::lua_bind
