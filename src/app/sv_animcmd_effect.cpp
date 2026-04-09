#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/EffectModule.h"

// ACMD effect dispatcher functions — app::sv_animcmd namespace
// Pool-a worker: Effect template functions (68 targets in 0x71022xxxxx range)
//
// Lua stack TValue layout (0x10 bytes):
//   +0x00: value (u64/f32/s64/ptr)
//   +0x08: type tag u32 (0=nil, 1=bool, 3=float, 0x13=int)
//
// lua_State relevant offsets:
//   L - 0x08 → wrapper ptr, wrapper+0x1a0 = accessor
//   L + 0x10 → stack top
//   L + 0x20 → call info ptr, *call_info = frame base

#define HIDDEN __attribute__((visibility("hidden")))

struct lua_State;

extern "C" u64 FUN_71038f4000(lua_State*, s32, s32);
extern "C" u64 FUN_7103907950(u64, void*);
extern "C" u8 DAT_7104861960[] HIDDEN;
extern "C" u64 BattleObjectWorld_instance HIDDEN;  // lib::Singleton<app::BattleObjectWorld>::instance_
extern "C" void* DAT_71052b7710 HIDDEN;  // [inferred: screen effect manager data ptr]
extern "C" u32 FUN_710228ea70(u64, u64, u64, void*, s32);
extern "C" void FUN_7102288620(void*, void*, u64);
extern "C" u64 ConstantZero HIDDEN;  // PTR_ConstantZero_71052a7a88
extern "C" u32 DAT_71052381c0 HIDDEN;  // XOR-shift128 PRNG state[0]
extern "C" u32 DAT_71052381c4 HIDDEN;  // XOR-shift128 PRNG state[1]
extern "C" u32 DAT_71052381c8 HIDDEN;  // XOR-shift128 PRNG state[2]
extern "C" u32 DAT_71052381cc HIDDEN;  // XOR-shift128 PRNG state[3]
extern "C" f32 DAT_7104472710 HIDDEN;  // PRNG normalization ≈ 1/(2^32)
extern "C" void* PTR_FUN_7104f68c38[] HIDDEN;  // joint resolve function table (9 entries, indexed 0-8)
extern "C" void* DAT_71052b7f00 HIDDEN;  // [inferred: camera controller singleton]
extern "C" u8 DAT_71044646b0[] HIDDEN;  // [inferred: 4-float weight vector for camera interpolation]
extern "C" u8 DAT_7104464430[] HIDDEN;  // [inferred: 2-float target value for camera projection]
extern "C" [[noreturn]] void abort();

// Singletons for FOOT/LANDING/DOWN effects
namespace lib {
    template<typename T> struct Singleton { static T* instance_; };
}
namespace app {
    struct StageManager;
    struct FighterParamAccessor2;
    struct FighterCutInManager;
}
namespace lib {
    struct EffectManager;
}
// Explicit instantiation declarations (linker resolves these)
extern template app::StageManager* lib::Singleton<app::StageManager>::instance_;
extern template app::FighterParamAccessor2* lib::Singleton<app::FighterParamAccessor2>::instance_;
extern template app::FighterCutInManager* lib::Singleton<app::FighterCutInManager>::instance_;
extern template lib::EffectManager* lib::Singleton<lib::EffectManager>::instance_;

extern "C" u64 DAT_71052c2610 HIDDEN;   // [inferred: slow effect slot array base]
extern "C" void FUN_710260ccd0(u64);      // StageManager::reset_hiding (called on bg effect disable)
// DAT_71052b7f00 declared above as void*

// Control struct for FUN_7102288620 / FUN_710228ea70
// FUN_7102288620 reads nargs and L from this struct via the pointer passed as arg 2
struct acmd_effect_ctrl {
    u64 hash;         // +0x00
    u32 nargs;        // +0x08
    u32 _pad;         // +0x0c
    lua_State* L;     // +0x10
    u8 flag;          // +0x18
};

// Output struct from FUN_7102288620 — 16-arg EFFECT parsed data
// Laid out as 13 u64s (104 bytes). Vectors stored inline as {u32_x, u32_y, u64_z}.
struct acmd_effect_out {
    u64 hash1;           // [0] +0x00
    u64 hash2;           // [1] +0x08
    u64 pos_xy;          // [2] +0x10 = CONCAT44(pos_y, pos_x)
    u64 pos_z;           // [3] +0x18
    u64 rot_xy;          // [4] +0x20 = CONCAT44(rot_y, rot_x)
    u64 rot_z;           // [5] +0x28
    u32 rate_bits;       // [6] +0x30 (rate as raw f32 bits)
    u32 _pad1;           // +0x34
    u64 _reserved;       // [7] +0x38
    u64 scale_xy;        // [8] +0x40
    u64 scale_z;         // [9] +0x48
    u64 color_xy;        // [10] +0x50
    u64 color_z;         // [11] +0x58
    bool follow_flag;    // [12] +0x60
};

// ---------------------------------------------------------------------------
// Inline helpers for ACMD arg reading
// ---------------------------------------------------------------------------

// Read a float from ACMD lua stack entry at byte offset from base.
// Includes full type dispatch: tag 3 (float), 0x13 (int→float), (tag&0xf)==4 (string→float)
// Read a float from ACMD lua stack entry at byte offset from base.
// Includes full type dispatch: tag 3 (float), 0x13 (int→float), (tag&0xf)==4 (string→float)
// NOTE: upstream Clang CSEs the DAT_7104861960 address across inline expansions,
// making compiled output ~10% smaller than original (which has independent loads per read).
// This is a known NX Clang divergence — accept size mismatch for now.
static inline f32 acmd_read_float(u64 L, u64 entry_offset) {
    u8* entry = (u8*)(**(u64**)(L + 0x20) + entry_offset);
    u64 top = *(u64*)(L + 0x10);
    if (top <= (u64)entry) {
        entry = DAT_7104861960;
    }
    u32 tag = *(u32*)(entry + 8);
    if (tag == 3) {
        return *(f32*)entry;
    }
    if (tag == 0x13) {
        return (f32)*(s64*)entry;
    }
    if ((tag & 0xf) == 4) {
        struct { s64 val; u64 type; } out;
        u64 len = FUN_7103907950(*(u64*)entry + 0x18, &out);
        u64 str = *(u64*)entry;
        u64 slen;
        if (*(u8*)(str + 8) == 4) {
            slen = (u64)*(u8*)(str + 0xb);
        } else {
            slen = *(u64*)(str + 0x10);
        }
        if (len == slen + 1) {
            return (f32)out.val;
        }
    }
    return 0.0f;
}

// Read bool from ACMD lua stack entry at byte offset from base.
static inline bool acmd_read_bool(u64 L, u64 entry_offset) {
    u8* entry = (u8*)(**(u64**)(L + 0x20) + entry_offset);
    if (*(u64*)(L + 0x10) <= (u64)entry) {
        entry = DAT_7104861960;
    }
    u32 tag = *(u32*)(entry + 8);

    if (tag == 0) return false;
    if (tag == 0x13) {
        s64 ival = *(s64*)entry;
        if (ival == 0) return false;
        f32 fval = (f32)ival;
        if (fval == 0.0f) return false;
        if (tag != 3) return true;
        f32 v = *(f32*)entry;
        return !(v == 0.0f);
    }
    if (tag == 1) {
        u32 bval = *(u32*)entry;
        return (bval != 0);
    }
    if ((tag & 0xf) == 3) {
        f32 fval = *(f32*)entry;
        if (fval != 0.0f) {
            if (tag != 3) return true;
            f32 v = *(f32*)entry;
            return !(v == 0.0f);
        }
        return false;
    }
    if (tag != 3) return true;
    f32 v = *(f32*)entry;
    return !(v == 0.0f);
}

// Consume remaining ACMD args
static inline void acmd_consume(u64 L) {
    u64 end = **(u64**)(L + 0x20) + 0x10;
    u64 cur = *(u64*)(L + 0x10);
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(cur), "+r"(end));
#endif
    if (cur < end) {
        do {
            *(u64*)(L + 0x10) = cur + 0x10;
            *(u32*)(cur + 8) = 0;
            cur = *(u64*)(L + 0x10);
        } while (cur < end);
    }
    *(u64*)(L + 0x10) = end;
}

// Compute nargs from ACMD lua state
static inline int acmd_nargs(u64 L) {
    u64 base = **(u64**)(L + 0x20);
    base += 0x10;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base));
#endif
    return (int)((*(u64*)(L + 0x10) - base) >> 4);
}

// ---------------------------------------------------------------------------
// ACMD Effect Functions
// ---------------------------------------------------------------------------

namespace app { namespace sv_animcmd {

// 0x710228e9c0 (164 bytes) — EFFECT_GLOBAL
// Calls FUN_710228ea70 with constant args (hash=0, scale=1.0f, flag=0)
extern "C" void EFFECT_GLOBAL(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    struct { u64 hash; u32 nargs; u32 pad; lua_State* L; u8 flag; } ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    FUN_710228ea70(ConstantZero, 0x3f800000, acc, &ctrl, 0);

    acmd_consume(L);
}

// 0x71022927b0 (348 bytes) — EFFECT_OFF
// Args: 1=effect_hash, 2=bool_flag
// Calls EffectModule::kill_all (vtable slot 30, offset 0xF0)
extern "C" void EFFECT_OFF(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;
    bool flag;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
        flag = false;
    } else if (nargs < 1) {
        hash = 0;
        flag = false;
    } else {
        hash = FUN_71038f4000(param_1, 1, 0);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(nargs));
#endif
        if (nargs < 2) {
            flag = false;
        } else {
            flag = acmd_read_bool(L, 0x20);
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    eff->kill_all(hash, flag, true);

    acmd_consume(L);
}

// 0x710228be60 — EFFECT_WORK
// Args: 1=effect_hash, 2=bone_hash, 3-4=pos_xy, 5=joint_id, 6-7=rot_xy,
//       8=rate, 9=rot_z, 10-11=scale_xy, 12=scale_z, 13-14=extra_xy,
//       15=extra_z, 16=bool_flag
// Calls EffectModule::req_on_joint (vtable slot 14, offset 0x70)
extern "C" void EFFECT_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 a3 = 0, a4 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
    f32 a10 = 0, a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0;
    u64 a5_int = 0;
    bool a16 = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                a3 = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    a4 = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        // arg 5: float → cast to int
                        f32 a5f = acmd_read_float(L, 0x50);
                        a5_int = (u64)(u32)a5f;
                        if (nargs >= 6) {
                            a6 = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                a7 = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    a8 = acmd_read_float(L, 0x80);
                                    if (nargs >= 9) {
                                        a9 = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            a10 = acmd_read_float(L, 0xa0);
                                            if (nargs >= 11) {
                                                a11 = acmd_read_float(L, 0xb0);
                                                if (nargs >= 12) {
                                                    a12 = acmd_read_float(L, 0xc0);
                                                    if (nargs >= 13) {
                                                        a13 = acmd_read_float(L, 0xd0);
                                                        if (nargs >= 14) {
                                                            a14 = acmd_read_float(L, 0xe0);
                                                            if (nargs >= 15) {
                                                                a15 = acmd_read_float(L, 0xf0);
                                                                if (nargs >= 16) {
                                                                    a16 = acmd_read_bool(L, 0x100);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Pack args into 4 vector structs on stack
    // struct layout: { f32 x, f32 y, u64 z_or_id }
    struct { f32 x; f32 y; } pos_xy = { a3, a4 };
    u64 pos_z = a5_int;
    struct { f32 x; f32 y; } rot_xy = { a6, a7 };
    u64 rot_z = (u64)(u32)a9;
    struct { f32 x; f32 y; } scale_xy = { a10, a11 };
    u64 scale_z = (u64)(u32)a12;
    struct { f32 x; f32 y; } extra_xy = { a13, a14 };
    u64 extra_z = (u64)(u32)a15;

    // These must be contiguous on stack for the pointer args
    struct { f32 x; f32 y; u64 z; } vec_pos   = { a3, a4, a5_int };
    struct { f32 x; f32 y; u64 z; } vec_rot   = { a6, a7, (u64)(u32)a9 };
    struct { f32 x; f32 y; u64 z; } vec_scale  = { a10, a11, (u64)(u32)a12 };
    struct { f32 x; f32 y; u64 z; } vec_extra  = { a13, a14, (u64)(u32)a15 };

    // EffectModule::req_on_joint (vtable[14], offset 0x70)
    // Call signature: (this, hash1, hash2, &pos, &rot, &scale, &extra, bool, 0, 0, 0) + float rate in s0
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_extra, a16, 0, 0, 0, a8);

    acmd_consume(L);
}

// 0x710228cc90 — EFFECT_VARIATION
// Like EFFECT_WORK but calls get_variation_effect_kind first, then optionally set_offset_to_next
// Args: same as EFFECT_WORK (1-16), plus optional arg 17 for offset hash
extern "C" void EFFECT_VARIATION(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 a3 = 0, a4 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
    f32 a10 = 0, a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0;
    u64 a5_int = 0;
    bool a16 = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                a3 = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    a4 = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 a5f = acmd_read_float(L, 0x50);
                        a5_int = (u64)(u32)a5f;
                        if (nargs >= 6) {
                            a6 = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                a7 = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    a8 = acmd_read_float(L, 0x80);
                                    if (nargs >= 9) {
                                        a9 = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            a10 = acmd_read_float(L, 0xa0);
                                            if (nargs >= 11) {
                                                a11 = acmd_read_float(L, 0xb0);
                                                if (nargs >= 12) {
                                                    a12 = acmd_read_float(L, 0xc0);
                                                    if (nargs >= 13) {
                                                        a13 = acmd_read_float(L, 0xd0);
                                                        if (nargs >= 14) {
                                                            a14 = acmd_read_float(L, 0xe0);
                                                            if (nargs >= 15) {
                                                                a15 = acmd_read_float(L, 0xf0);
                                                                if (nargs >= 16) {
                                                                    a16 = acmd_read_bool(L, 0x100);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Pack into vectors
    struct { f32 x; f32 y; u64 z; } vec_pos   = { a3, a4, a5_int };
    struct { f32 x; f32 y; u64 z; } vec_rot   = { a6, a7, (u64)(u32)a9 };
    struct { f32 x; f32 y; u64 z; } vec_scale  = { a10, a11, (u64)(u32)a12 };
    struct { f32 x; f32 y; u64 z; } vec_extra  = { a13, a14, (u64)(u32)a15 };

    // Get variation effect kind via EffectModule vtable[88] (offset 0x2c0)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 kind = eff->get_variation_effect_kind(hash1, (u64)(s32)-1);

    // If nargs > 16: check if variation changed, and if not, apply offset
    if (nargs > 16) {
        u64 kind0 = eff->get_variation_effect_kind(hash1, 0);
        if (((kind0 ^ kind) & 0xFFFFFFFFFFULL) == 0) {
            u64 offset_hash = FUN_71038f4000(param_1, 0x11, 0);
            eff->set_offset_to_next(offset_hash);
        }
    }

    // EffectModule::req_on_joint (vtable[14], offset 0x70)

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, kind, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_extra, a16, 0, 0, 0, a8);

    acmd_consume(L);
}

// 0x710229cc80 (520 bytes) — EFFECT_OFF_KIND
// Args: 1=effect_hash, 2=is_trail(bool), 3=reset_flag(bool)
// Calls EffectModule::kill_kind (vtable slot 28, offset 0xE0)
extern "C" void EFFECT_OFF_KIND(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;
    bool flag1, flag2;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
        flag1 = false;
        flag2 = false;
    } else if (nargs < 1) {
        hash = 0;
        flag1 = false;
        flag2 = false;
    } else {
        hash = FUN_71038f4000(param_1, 1, 0);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(nargs));
#endif
        if (nargs < 2) {
            flag1 = false;
            flag2 = false;
        } else {
            flag1 = acmd_read_bool(L, 0x20);
            if (nargs < 3) {
                flag2 = false;
            } else {
                flag2 = acmd_read_bool(L, 0x30);
            }
        }
    }

    // EffectModule::kill_kind(hash, flag1, flag2)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    eff->kill_kind(hash, flag1, flag2);

    acmd_consume(L);
}

// 0x71022907c0 — EFFECT_FOLLOW
// Args: 1=effect_hash, 2=bone_hash, 3-5=offset(int xyz), 6-8=rot(int xyz),
//       9=scale(int), 10=follow_flag(bool)
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    // EFFECT_FOLLOW reads offsets/rotations as INTEGERS (not floats)
    u64 off_x = 0, off_y = 0, off_z = 0;
    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    f32 scale_f = 0;
    u64 scale_int = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                // Arg 3: offset_x as int
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                        if (nargs >= 6) {
                            f32 f6 = acmd_read_float(L, 0x60);
                            rot_x = (u64)(u32)f6;
                            if (nargs >= 7) {
                                f32 f7 = acmd_read_float(L, 0x70);
                                rot_y = (u64)(u32)f7;
                                if (nargs >= 8) {
                                    f32 f8 = acmd_read_float(L, 0x80);
                                    rot_z = (u64)(u32)f8;
                                    if (nargs >= 9) {
                                        scale_f = acmd_read_float(L, 0x90);
                                        scale_int = (u64)(u32)scale_f;
                                        if (nargs >= 10) {
                                            follow_flag = acmd_read_bool(L, 0xa0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Pack offset and rotation vectors
    // offset: {off_y(lo), off_x(hi)} at local_b0, off_z at uStack_a8
    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };
    // rotation: {rot_y(lo), rot_x(hi)} at local_a0, rot_z at uStack_98
    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    // Follow flag → 0xc000 (follow) or 0x8000 (no follow)
    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // EffectModule::req_follow (vtable[16], offset 0x80)
    // (scale_f, eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, -1, 0, 0, 0, 0)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x7102292910 (180 bytes) — EFFECT_REMOVE_ATTR
// Args: 1=effect_hash
// Calls EffectModule::remove_attr (vtable slot 26, offset 0xD0)
extern "C" void EFFECT_REMOVE_ATTR(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
    } else if (nargs >= 1) {
        hash = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash = 0;
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    eff->remove_all(hash, 0);

    acmd_consume(L);
}

// 0x710229ce90 (520 bytes) — EFFECT_OFF_KIND_WORK
// Args: 1=effect_hash, 2=is_trail(bool), 3=reset_flag(bool)
// Like EFFECT_OFF_KIND but with null check at start (WORK variant)
// Calls EffectModule::kill_kind (vtable slot 28, offset 0xE0)
extern "C" void EFFECT_OFF_KIND_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;
    bool flag1, flag2;

    if (nargs < 1) {
        hash = 0;
        flag1 = false;
        flag2 = false;
    } else {
        hash = FUN_71038f4000(param_1, 1, 0);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(nargs));
#endif
        if (nargs < 2) {
            flag1 = false;
            flag2 = false;
        } else {
            flag1 = acmd_read_bool(L, 0x20);
            if (nargs < 3) {
                flag2 = false;
            } else {
                flag2 = acmd_read_bool(L, 0x30);
            }
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    eff->kill_kind(hash, flag1, flag2);

    acmd_consume(L);
}

// 0x7102290f90 (2016 bytes) — EFFECT_FOLLOW_WORK
// Like EFFECT_FOLLOW but calls FUN_71038f4000(L,1,0) as side effect first,
// then again at end to get actual hash. Offsets nested inside arg2 block,
// rotations at top level.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    // Pack offset vector
    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    // Rotations: args 6-8 (top-level, not nested inside offset block)
    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    // Pack rotation vector
    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    // Scale: arg 9 (int via float)
    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    // Follow flag: arg 10
    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Get effect hash (arg 1, called again)
    u64 hash1;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash1 = 0;
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x7102291770 (2132 bytes) — EFFECT_FOLLOW_VARIATION
// Like EFFECT_FOLLOW_WORK + variation resolution via get_variation_effect_kind.
// Arg 9 is scale as FLOAT (not int). Up to 11 args.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW_VARIATION(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    // Pack offset vector
    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    // Rotations: args 6-8 (top-level)
    f32 scale_f = 0;
    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    // Pack rotation vector
    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    // Scale: arg 9 as FLOAT (kept as float, unlike EFFECT_FOLLOW_WORK)
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    // Follow flag: arg 10
    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Get effect hash (arg 1, called again)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 hash1;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash1 = 0;
    }

    // Variation resolution: get_variation_effect_kind (vtable[0x2c0])
    u64 var_kind = eff->get_variation_effect_kind(hash1, (u64)(s32)-1);

    u64 alt_hash;
    if (nargs >= 11) {
        // Re-read eff module and hash1 for second variation check
        app::EffectModule* eff2 = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        u64 hash1_again = FUN_71038f4000(param_1, 1, 0);
        u64 var_kind0 = eff2->get_variation_effect_kind(hash1_again, 0);
        if (((var_kind0 ^ var_kind) & 0xFFFFFFFFFFULL) == 0) {
            alt_hash = FUN_71038f4000(param_1, 0xb, 0);
        } else {
            alt_hash = 0;
        }
    } else {
        alt_hash = 0;
    }

    // EffectModule::req_follow (vtable[16], offset 0x80)
    app::EffectModule* eff3 = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff3->_vt[0x80 / 8])(eff3, var_kind, hash2, &off_vec, &rot_vec, 0, flags, alt_hash, (s32)-1, 0, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710228db30 (3716 bytes) — EFFECT_ATTR
// Args: 1=hash1, 2=hash2, 3-4=pos(float), 5=pos_z(int), 6-8=rot(float),
//       9=rate(float), 10-12=scale(float), 13-15=color(float), 16=bool, 17=attr_hash
// Calls EffectModule::req_on_joint with attr (vtable slot 14, offset 0x70)
extern "C" void EFFECT_ATTR(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 a3 = 0, a4 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
    f32 a10 = 0, a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0;
    u64 a5_int = 0;
    bool a16 = false;
    u64 attr_hash = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                a3 = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    a4 = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 a5f = acmd_read_float(L, 0x50);
                        a5_int = (u64)(u32)a5f;
                        if (nargs >= 6) {
                            a6 = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                a7 = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    a8 = acmd_read_float(L, 0x80);
                                    if (nargs >= 9) {
                                        a9 = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            a10 = acmd_read_float(L, 0xa0);
                                            if (nargs >= 11) {
                                                a11 = acmd_read_float(L, 0xb0);
                                                if (nargs >= 12) {
                                                    a12 = acmd_read_float(L, 0xc0);
                                                    if (nargs >= 13) {
                                                        a13 = acmd_read_float(L, 0xd0);
                                                        if (nargs >= 14) {
                                                            a14 = acmd_read_float(L, 0xe0);
                                                            if (nargs >= 15) {
                                                                a15 = acmd_read_float(L, 0xf0);
                                                                if (nargs >= 16) {
                                                                    a16 = acmd_read_bool(L, 0x100);
                                                                    if (nargs >= 17) {
                                                                        attr_hash = FUN_71038f4000(param_1, 0x11, 0);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Pack into 4 vector structs
    struct { f32 x; f32 y; u64 z; } vec_pos   = { a3, a4, a5_int };
    struct { f32 x; f32 y; u64 z; } vec_rot   = { a6, a7, (u64)(u32)a8 };
    struct { f32 x; f32 y; u64 z; } vec_scale  = { a10, a11, (u64)(u32)a12 };
    struct { f32 x; f32 y; u64 z; } vec_color  = { a13, a14, (u64)(u32)a15 };

    // EffectModule::req_on_joint with attr (vtable[14], offset 0x70)
    // rate (a9) in s0, attr_hash after bool on stack
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_color, a16, attr_hash, 0, 0, a9);

    acmd_consume(L);
}

// 0x71022a7f50 (180 bytes) — EFFECT_OFF_HANDLE
// Args: 1=handle_hash
// Calls EffectModule::kill_handle (vtable offset 0xC8)
extern "C" void EFFECT_OFF_HANDLE(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
    } else if (nargs >= 1) {
        hash = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash = 0;
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    eff->remove(hash, 0);

    acmd_consume(L);
}

// 0x71022a5780 (224 bytes) — EFFECT_DETACH_KIND
// Args: 1=effect_hash, 2=group_hash
// Calls EffectModule::detach_kind (vtable offset 0x100)
extern "C" void EFFECT_DETACH_KIND(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1, hash2;
    app::EffectModule* eff;

    if (nargs < 1) {
        eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        hash1 = 0;
        hash2 = 0;
    } else {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        if (nargs < 2) {
            hash2 = 0;
        } else {
            hash2 = FUN_71038f4000(param_1, 2, 0);
        }
    }

    eff->detach_kind(hash1, hash2);

    acmd_consume(L);
}

// 0x71022a5860 (224 bytes) — EFFECT_DETACH_KIND_WORK
// Args: 1=effect_hash, 2=group_hash
// Identical to EFFECT_DETACH_KIND (vtable offset 0x100)
extern "C" void EFFECT_DETACH_KIND_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1, hash2;
    app::EffectModule* eff;

    if (nargs < 1) {
        eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        hash1 = 0;
        hash2 = 0;
    } else {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        if (nargs < 2) {
            hash2 = 0;
        } else {
            hash2 = FUN_71038f4000(param_1, 2, 0);
        }
    }

    eff->detach_kind(hash1, hash2);

    acmd_consume(L);
}

// 0x7102297520 (224 bytes) — EFFECT_LIGHT_END
// Args: 1=light_hash(u32), 2=group_hash
// Calls EffectModule::end_light (vtable offset 0x2E0)
extern "C" void EFFECT_LIGHT_END(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1, hash2;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash1 = 0;
        hash2 = 0;
    } else if (nargs < 1) {
        hash1 = 0;
        hash2 = 0;
    } else {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs < 2) {
            hash2 = 0;
        } else {
            hash2 = FUN_71038f4000(param_1, 2, 0);
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64)>(eff->_vt[0x2e0 / 8])(eff, hash1, hash2);

    acmd_consume(L);
}

// 0x71022a49a0 (340 bytes) — LAST_EFFECT_SET_RATE
// Args: 1=rate(float)
// Calls EffectModule::set_rate (vtable offset 0x338)
extern "C" void LAST_EFFECT_SET_RATE(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    f32 rate;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        rate = 0.0f;
    } else {
        rate = 0.0f;
        if (nargs >= 1) {
            rate = acmd_read_float(L, 0x10);
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, f32)>(eff->_vt[0x338 / 8])(eff, rate);

    acmd_consume(L);
}

// 0x71022a4b00 (340 bytes) — LAST_EFFECT_SET_RATE_WORK
// Identical to LAST_EFFECT_SET_RATE (vtable offset 0x338)
extern "C" void LAST_EFFECT_SET_RATE_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    f32 rate;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        rate = 0.0f;
    } else {
        rate = 0.0f;
        if (nargs >= 1) {
            rate = acmd_read_float(L, 0x10);
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, f32)>(eff->_vt[0x338 / 8])(eff, rate);

    acmd_consume(L);
}

// 0x71022a52c0 (340 bytes) — LAST_EFFECT_SET_ALPHA
// Args: 1=alpha(float)
// Calls EffectModule::set_alpha (vtable offset 0x348)
extern "C" void LAST_EFFECT_SET_ALPHA(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    f32 alpha;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        alpha = 0.0f;
    } else {
        alpha = 0.0f;
        if (nargs >= 1) {
            alpha = acmd_read_float(L, 0x10);
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, f32)>(eff->_vt[0x348 / 8])(eff, alpha);

    acmd_consume(L);
}

// 0x71022a5420 (284 bytes) — LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW
// Args: 1=disable(bool)
// Calls EffectModule::set_disable_system_slow (vtable offset 0x350)
extern "C" void LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW(lua_State* param_1) {
    u64 L = (u64)param_1;
    int nargs = acmd_nargs(L);

    bool flag;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        flag = false;
    } else if (nargs >= 1) {
        flag = acmd_read_bool(L, 0x10);
    } else {
        flag = false;
    }

    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, bool)>(eff->_vt[0x350 / 8])(eff, flag);

    acmd_consume(L);
}

// 0x71022a56a0 (212 bytes) — LAST_EFFECT_SET_WORK_INT
// Args: 1=work_var_hash
// Gets last effect handle from EffectModule vtable[0x3A0], then
// sets work int via WorkModule vtable[0xA0]
extern "C" void LAST_EFFECT_SET_WORK_INT(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
    } else if (nargs >= 1) {
        hash = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash = 0;
    }

    // WorkModule at acc+0x50
    void** work = *(void***)(acc + 0x50);

    // EffectModule::get_last_handle (vtable[0x3A0])
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 handle = eff->get_last_handle();

    // WorkModule::set_int (vtable[0xA0])
    reinterpret_cast<void(*)(void*, u64, u64)>((*(void***)work)[0xa0 / 8])(work, handle, hash);

    acmd_consume(L);
}

// 0x71022a4c60 (804 bytes) — LAST_EFFECT_SET_SCALE_W
// Args: 1-3 = scale xyz (float→int)
// Packs into vec3 struct, calls EffectModule::set_scale (vtable offset 0x340)
extern "C" void LAST_EFFECT_SET_SCALE_W(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 a1 = 0, a2 = 0, a3 = 0;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
    } else if (nargs >= 1) {
        f32 f1 = acmd_read_float(L, 0x10);
        a1 = (u64)(u32)f1;
        if (nargs >= 2) {
            f32 f2 = acmd_read_float(L, 0x20);
            a2 = (u64)(u32)f2;
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                a3 = (u64)(u32)f3;
            }
        }
    }

    struct { u32 x; u32 y; u64 z; } scale_vec = { (u32)a1, (u32)a2, a3 };

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, void*)>(eff->_vt[0x340 / 8])(eff, &scale_vec);

    acmd_consume(L);
}

// 0x71022a4f90 (804 bytes) — LAST_EFFECT_SET_COLOR
// Args: 1-3 = RGB color (float)
// Gets last handle via vtable[0x3A0], then sets color via vtable[0x2F8]
extern "C" void LAST_EFFECT_SET_COLOR(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    f32 r = 0, g = 0, b = 0;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
    } else if (nargs >= 1) {
        r = acmd_read_float(L, 0x10);
        if (nargs >= 2) {
            g = acmd_read_float(L, 0x20);
            if (nargs >= 3) {
                b = acmd_read_float(L, 0x30);
            }
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    u64 handle = reinterpret_cast<u64(*)(void*)>(eff->_vt[0x3a0 / 8])(eff);
    reinterpret_cast<void(*)(void*, u64, f32, f32, f32)>(eff->_vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x7102299f40 (2004 bytes) — EFFECT_FOLLOW_NO_STOP
// Like EFFECT_FOLLOW but reads hashes in nested block, offsets nested,
// rotations top-level. Flags: follow=0x4000, default=0.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW_NO_STOP(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0x4000ULL : 0;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x000000710229bc20 (2052 bytes) — EFFECT_FOLLOW_arg11
// Like EFFECT_FOLLOW_NO_STOP but with arg11=alt_hash.
// Flags: follow=0xc000, default=0x8000.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_arg11(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    u64 alt_hash;
    if (nargs >= 11) {
        alt_hash = FUN_71038f4000(param_1, 0xb, 0);
    } else {
        alt_hash = 0;
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, alt_hash, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x00000071022a5c50 (1996 bytes) — EFFECT_FOLLOW_NO_SCALE
// Like EFFECT_FOLLOW but passes 1 as the no_scale flag (13th arg).
// Flags: follow=0xc000, default=0x8000.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW_NO_SCALE(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    // Note: 13th arg is 1 (no_scale flag), not 0
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 1, scale_f);

    acmd_consume(L);
}

// 0x7102291fd0 (2004 bytes) — EFFECT_FOLLOW_UNSYNC_VIS_WHOLE
// Like EFFECT_FOLLOW_NO_STOP but flags: follow=0x40c000, default=0x408000.
// The 0x40xxxx prefix marks unsync vis mode.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
extern "C" void EFFECT_FOLLOW_UNSYNC_VIS_WHOLE(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    // Flags: 0x408000 default, 0x40c000 for follow
    u64 flags = 0x408000ULL;
    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
        if (follow_flag) {
            flags = 0x40c000ULL;
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x71022929d0 (2052 bytes) — EFFECT_FLW_POS
// Args: 1=hash1, 2=hash2, 3-4=offset_xy(float), 5=offset_z(float→int),
//       6-7=rot_xy(float), 8=rot_z(float→int), 9=scale(float), 10=follow_flag(bool)
// Like EFFECT_FOLLOW but keeps offset/rot x,y as raw floats (position-based)
// Calls EffectModule::req_follow (vtable offset 0x80) with pos_mode=1
extern "C" void EFFECT_FLW_POS(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 off_x = 0, off_y = 0, rot_x = 0, rot_y = 0, scale = 0;
    u64 off_z = 0, rot_z = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                off_x = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    off_y = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                        if (nargs >= 6) {
                            rot_x = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                rot_y = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    f32 f8 = acmd_read_float(L, 0x80);
                                    rot_z = (u64)(u32)f8;
                                    if (nargs >= 9) {
                                        scale = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            follow_flag = acmd_read_bool(L, 0xa0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } off_vec = { off_x, off_y, off_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, rot_z };

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022931e0 (2048 bytes) — EFFECT_FLW_POS_NO_STOP
// Same as EFFECT_FLW_POS but flags: follow=0x4000, default=0
extern "C" void EFFECT_FLW_POS_NO_STOP(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 off_x = 0, off_y = 0, rot_x = 0, rot_y = 0, scale = 0;
    u64 off_z = 0, rot_z = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                off_x = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    off_y = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                        if (nargs >= 6) {
                            rot_x = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                rot_y = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    f32 f8 = acmd_read_float(L, 0x80);
                                    rot_z = (u64)(u32)f8;
                                    if (nargs >= 9) {
                                        scale = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            follow_flag = acmd_read_bool(L, 0xa0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } off_vec = { off_x, off_y, off_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, rot_z };

    u64 flags = follow_flag ? 0x4000ULL : 0;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022939e0 (2056 bytes) — EFFECT_FLW_POS_UNSYNC_VIS
// Same as EFFECT_FLW_POS but flags: follow=0x40c000, default=0x408000
extern "C" void EFFECT_FLW_POS_UNSYNC_VIS(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 off_x = 0, off_y = 0, rot_x = 0, rot_y = 0, scale = 0;
    u64 off_z = 0, rot_z = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                off_x = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    off_y = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                        if (nargs >= 6) {
                            rot_x = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                rot_y = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    f32 f8 = acmd_read_float(L, 0x80);
                                    rot_z = (u64)(u32)f8;
                                    if (nargs >= 9) {
                                        scale = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            follow_flag = acmd_read_bool(L, 0xa0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } off_vec = { off_x, off_y, off_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, rot_z };

    u64 flags = follow_flag ? 0x40c000ULL : 0x408000ULL;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022941f0 (2056 bytes) — EFFECT_FLW_UNSYNC_VIS
// Same as EFFECT_FLW_POS_UNSYNC_VIS but pos_mode=0 instead of 1
extern "C" void EFFECT_FLW_UNSYNC_VIS(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 off_x = 0, off_y = 0, rot_x = 0, rot_y = 0, scale = 0;
    u64 off_z = 0, rot_z = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                off_x = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    off_y = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                        if (nargs >= 6) {
                            rot_x = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                rot_y = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    f32 f8 = acmd_read_float(L, 0x80);
                                    rot_z = (u64)(u32)f8;
                                    if (nargs >= 9) {
                                        scale = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            follow_flag = acmd_read_bool(L, 0xa0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } off_vec = { off_x, off_y, off_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, rot_z };

    u64 flags = follow_flag ? 0x40c000ULL : 0x408000ULL;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022a5540 (352 bytes) — LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT
// Checks BattleObjectWorld singleton; if invalid, skip.
// Args: 1=offset(float)
// Calls EffectModule::set_offset_to_camera_flat (vtable offset 0x370)
extern "C" void LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT(lua_State* param_1) {
    u64 L = (u64)param_1;
    int nargs = acmd_nargs(L);

    // Check BattleObjectWorld singleton: skip if null, or flag at +0xc set, or speed at +0x8 == 1.0
    u64 instance = BattleObjectWorld_instance;
    if (instance != 0 && *(u8*)(instance + 0xc) == 0 && *(f32*)(instance + 8) != 1.0f) {
        u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

        f32 offset = 0.0f;
        if (nargs >= 1) {
            offset = acmd_read_float(L, 0x10);
        }

        app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    
        reinterpret_cast<void(*)(void*, f32)>(eff->_vt[0x370 / 8])(eff, offset);
    }

    acmd_consume(L);
}

// 0x71022a5940 (780 bytes) — LAST_PARTICLE_SET_COLOR
// Args: 1-3 = RGB color (float)
// Calls EffectModule::set_particle_color (vtable offset 0x300)
extern "C" void LAST_PARTICLE_SET_COLOR(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    f32 r = 0, g = 0, b = 0;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
    } else if (nargs >= 1) {
        r = acmd_read_float(L, 0x10);
        if (nargs >= 2) {
            g = acmd_read_float(L, 0x20);
            if (nargs >= 3) {
                b = acmd_read_float(L, 0x30);
            }
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, f32, f32, f32)>(eff->_vt[0x300 / 8])(eff, r, g, b);

    acmd_consume(L);
}

// 0x710229a720 (2620 bytes) — EFFECT_FOLLOW_COLOR
// Like EFFECT_FOLLOW but returns handle from req_follow, then reads 3 extra float
// args (11-13) for RGB and calls set_color (vtable offset 0x2F8)
extern "C" void EFFECT_FOLLOW_COLOR(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;
    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    f32 scale_f = 0;
    u64 scale_int = 0;
    bool follow_flag = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_xv = 0, rot_yv = 0, rot_zv = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_xv = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_yv = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_zv = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_yv, (u32)rot_xv, rot_zv };

    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
        scale_int = (u64)(u32)scale_f;
    }

    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // req_follow → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale_f);

    // Read RGB: args 11-13 (offsets 0xb0, 0xc0, 0xd0)
    f32 r = 0, g = 0, b = 0;
    if (nargs >= 11) {
        r = acmd_read_float(L, 0xb0);
        if (nargs >= 12) {
            g = acmd_read_float(L, 0xc0);
            if (nargs >= 13) {
                b = acmd_read_float(L, 0xd0);
            }
        }
    }

    // EffectModule::set_color (vtable offset 0x2F8)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>(eff->_vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d9e0 (2196 bytes) — EFFECT_FOLLOW_ALPHA
// Like EFFECT_FOLLOW but returns handle from req_follow, then reads 1 extra float
// arg (11) for alpha and calls set_alpha_last (vtable offset 0x308)
extern "C" void EFFECT_FOLLOW_ALPHA(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_xv = 0, rot_yv = 0, rot_zv = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_xv = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_yv = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_zv = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_yv, (u32)rot_xv, rot_zv };

    f32 scale_f = 0;
    if (nargs >= 9) {
        scale_f = acmd_read_float(L, 0x90);
    }

    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // req_follow → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale_f);

    // Read alpha: arg 11 (offset 0xb0)
    f32 alpha = 0.0f;
    if (nargs >= 11) {
        alpha = acmd_read_float(L, 0xb0);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32)>(eff->_vt[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x7102294a00 (2336 bytes) — EFFECT_FOLLOW_FLIP
// Like EFFECT_FOLLOW but checks MotionModule flip state and swaps hash args.
// Args: 1=hash_nf, 2=hash_flip, 3=bone_hash, 4-5=off_xy(float), 6=off_z(int),
//       7-8=rot_xy(float), 9=rot_z(int), 10=scale(float), 11=follow_flag(bool),
//       12=alt_hash(when flipped)
// Calls MotionModule vtable[0x390/8] for flip check, then req_follow (vtable 0x80)
extern "C" void EFFECT_FOLLOW_FLIP(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 bone_hash = 0;
    f32 off_x = 0, off_y = 0, rot_x = 0, rot_y = 0, scale = 0;
    u64 off_z = 0, rot_z = 0;
    bool follow_flag = false;

    if (param_1 == nullptr) {
        if (nargs >= 3) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
    } else if (nargs >= 3) {
        bone_hash = FUN_71038f4000(param_1, 3, 0);
        if (nargs >= 4) {
            off_x = acmd_read_float(L, 0x40);
            if (nargs >= 5) {
                off_y = acmd_read_float(L, 0x50);
                if (nargs >= 6) {
                    f32 f6 = acmd_read_float(L, 0x60);
                    off_z = (u64)(u32)f6;
                    if (nargs >= 7) {
                        rot_x = acmd_read_float(L, 0x70);
                        if (nargs >= 8) {
                            rot_y = acmd_read_float(L, 0x80);
                            if (nargs >= 9) {
                                f32 f9 = acmd_read_float(L, 0x90);
                                rot_z = (u64)(u32)f9;
                                if (nargs >= 10) {
                                    scale = acmd_read_float(L, 0xa0);
                                    if (nargs >= 11) {
                                        follow_flag = acmd_read_bool(L, 0xb0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } off_vec = { off_x, off_y, off_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, rot_z };

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Check MotionModule flip state (vtable[0x390/8] at acc+0x88)
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 effect_hash;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        // Not flipped: use arg 1
        if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        if (nargs >= 1) {
            effect_hash = FUN_71038f4000(param_1, 1, 0);
        } else {
            effect_hash = 0;
        }
    } else {
        // Flipped: use arg 2
        if (param_1 == nullptr) {
            effect_hash = 0;
        } else if (nargs >= 2) {
            effect_hash = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 12) {
                alt_hash = FUN_71038f4000(param_1, 0xc, 0);
            }
        } else {
            effect_hash = 0;
        }
    }

    // req_follow with flip
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x7102295bb0 (2144 bytes) — EFFECT_FOLLOW_NO_STOP_FLIP
// Like EFFECT_FOLLOW_FLIP but NO_STOP flags (follow=0x4000, default=0).
// Args: 1=hash_nf(discarded initially), 2=hash_flip, 3=bone_hash,
//       4-6=off_xyz(int), 7-9=rot_xyz(int), 10=scale(float),
//       11=follow_flag(bool), 12=alt_hash(when flipped)
extern "C" void EFFECT_FOLLOW_NO_STOP_FLIP(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 bone_hash = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 3) {
            bone_hash = FUN_71038f4000(param_1, 3, 0);
            if (nargs >= 4) {
                f32 f4 = acmd_read_float(L, 0x40);
                off_x = (u64)(u32)f4;
                if (nargs >= 5) {
                    f32 f5 = acmd_read_float(L, 0x50);
                    off_y = (u64)(u32)f5;
                    if (nargs >= 6) {
                        f32 f6 = acmd_read_float(L, 0x60);
                        off_z = (u64)(u32)f6;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 7) {
        f32 f7 = acmd_read_float(L, 0x70);
        rot_x = (u64)(u32)f7;
        if (nargs >= 8) {
            f32 f8 = acmd_read_float(L, 0x80);
            rot_y = (u64)(u32)f8;
            if (nargs >= 9) {
                f32 f9 = acmd_read_float(L, 0x90);
                rot_z = (u64)(u32)f9;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 10) {
        scale_f = acmd_read_float(L, 0xa0);
    }

    bool follow_flag = false;
    if (nargs >= 11) {
        follow_flag = acmd_read_bool(L, 0xb0);
    }

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 effect_hash;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        // Not flipped: use arg 1
        if (nargs >= 1) {
            effect_hash = FUN_71038f4000(param_1, 1, 0);
        } else {
            effect_hash = 0;
        }
    } else {
        // Flipped: use arg 2
        if (nargs >= 2) {
            effect_hash = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 12) {
                alt_hash = FUN_71038f4000(param_1, 0xc, 0);
            }
        } else {
            effect_hash = 0;
        }
    }

    u64 flags = follow_flag ? 0x4000ULL : 0;

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710229b160 (2752 bytes) — EFFECT_FOLLOW_FLIP_COLOR
// Combines FOLLOW_FLIP (motion flip + hash swap) with COLOR (3 RGB float args after req_follow).
// Args: 1=hash_nf, 2=hash_flip, 3=bone_hash, 4-6=off_xyz(int), 7-9=rot_xyz(int),
//       10=scale(float), 11=follow_flag(bool), 12=alt_hash(when flipped),
//       13-15=RGB(float)
extern "C" void EFFECT_FOLLOW_FLIP_COLOR(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 bone_hash = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 3) {
            bone_hash = FUN_71038f4000(param_1, 3, 0);
            if (nargs >= 4) {
                f32 f4 = acmd_read_float(L, 0x40);
                off_x = (u64)(u32)f4;
                if (nargs >= 5) {
                    f32 f5 = acmd_read_float(L, 0x50);
                    off_y = (u64)(u32)f5;
                    if (nargs >= 6) {
                        f32 f6 = acmd_read_float(L, 0x60);
                        off_z = (u64)(u32)f6;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 7) {
        f32 f7 = acmd_read_float(L, 0x70);
        rot_x = (u64)(u32)f7;
        if (nargs >= 8) {
            f32 f8 = acmd_read_float(L, 0x80);
            rot_y = (u64)(u32)f8;
            if (nargs >= 9) {
                f32 f9 = acmd_read_float(L, 0x90);
                rot_z = (u64)(u32)f9;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 10) {
        scale_f = acmd_read_float(L, 0xa0);
    }

    bool follow_flag = false;
    if (nargs >= 11) {
        follow_flag = acmd_read_bool(L, 0xb0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 effect_hash;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        if (nargs >= 1) {
            effect_hash = FUN_71038f4000(param_1, 1, 0);
        } else {
            effect_hash = 0;
        }
    } else {
        if (nargs >= 2) {
            effect_hash = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 12) {
                alt_hash = FUN_71038f4000(param_1, 0xc, 0);
            }
        } else {
            effect_hash = 0;
        }
    }

    // req_follow → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    // Read RGB: args 13-15 (offsets 0xd0, 0xe0, 0xf0)
    f32 r = 0, g = 0, b = 0;
    if (nargs >= 13) {
        r = acmd_read_float(L, 0xd0);
        if (nargs >= 14) {
            g = acmd_read_float(L, 0xe0);
            if (nargs >= 15) {
                b = acmd_read_float(L, 0xf0);
            }
        }
    }

    // EffectModule::set_color (vtable offset 0x2F8)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>(eff->_vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x71022a1100 (2328 bytes) — EFFECT_FOLLOW_FLIP_ALPHA
// Combines FOLLOW_FLIP (motion flip + hash swap) with ALPHA (1 float arg after req_follow).
// Same arg layout as EFFECT_FOLLOW_FLIP_COLOR but arg 13=alpha, calls vtable 0x308
extern "C" void EFFECT_FOLLOW_FLIP_ALPHA(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 bone_hash = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 3) {
            bone_hash = FUN_71038f4000(param_1, 3, 0);
            if (nargs >= 4) {
                f32 f4 = acmd_read_float(L, 0x40);
                off_x = (u64)(u32)f4;
                if (nargs >= 5) {
                    f32 f5 = acmd_read_float(L, 0x50);
                    off_y = (u64)(u32)f5;
                    if (nargs >= 6) {
                        f32 f6 = acmd_read_float(L, 0x60);
                        off_z = (u64)(u32)f6;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 7) {
        f32 f7 = acmd_read_float(L, 0x70);
        rot_x = (u64)(u32)f7;
        if (nargs >= 8) {
            f32 f8 = acmd_read_float(L, 0x80);
            rot_y = (u64)(u32)f8;
            if (nargs >= 9) {
                f32 f9 = acmd_read_float(L, 0x90);
                rot_z = (u64)(u32)f9;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 10) {
        scale_f = acmd_read_float(L, 0xa0);
    }

    bool follow_flag = false;
    if (nargs >= 11) {
        follow_flag = acmd_read_bool(L, 0xb0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 effect_hash;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        if (nargs >= 1) {
            effect_hash = FUN_71038f4000(param_1, 1, 0);
        } else {
            effect_hash = 0;
        }
    } else {
        if (nargs >= 2) {
            effect_hash = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 12) {
                alt_hash = FUN_71038f4000(param_1, 0xc, 0);
            }
        } else {
            effect_hash = 0;
        }
    }

    // req_follow → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    // Read alpha: arg 13 (offset 0xd0)
    f32 alpha = 0.0f;
    if (nargs >= 13) {
        alpha = acmd_read_float(L, 0xd0);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32)>(eff->_vt[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x7102295320 (2180 bytes) — EFFECT_FOLLOW_FLIP_arg13
// Like EFFECT_FOLLOW_FLIP but passes arg 13 as joint hash in req_follow position 8.
// Args: 1=hash_nf, 2=hash_flip, 3=bone_hash, 4-6=off_xyz(int), 7-9=rot_xyz(int),
//       10=scale(float), 11=follow_flag(bool), 12=alt_hash(when flipped), 13=joint_hash
void EFFECT_FOLLOW_FLIP_arg13(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 bone_hash = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        FUN_71038f4000(param_1, 1, 0);  // side effect, result discarded
        if (nargs >= 3) {
            bone_hash = FUN_71038f4000(param_1, 3, 0);
            if (nargs >= 4) {
                f32 f4 = acmd_read_float(L, 0x40);
                off_x = (u64)(u32)f4;
                if (nargs >= 5) {
                    f32 f5 = acmd_read_float(L, 0x50);
                    off_y = (u64)(u32)f5;
                    if (nargs >= 6) {
                        f32 f6 = acmd_read_float(L, 0x60);
                        off_z = (u64)(u32)f6;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 7) {
        f32 f7 = acmd_read_float(L, 0x70);
        rot_x = (u64)(u32)f7;
        if (nargs >= 8) {
            f32 f8 = acmd_read_float(L, 0x80);
            rot_y = (u64)(u32)f8;
            if (nargs >= 9) {
                f32 f9 = acmd_read_float(L, 0x90);
                rot_z = (u64)(u32)f9;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 scale_f = 0;
    if (nargs >= 10) {
        scale_f = acmd_read_float(L, 0xa0);
    }

    bool follow_flag = false;
    if (nargs >= 11) {
        follow_flag = acmd_read_bool(L, 0xb0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 effect_hash;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        if (nargs >= 1) {
            effect_hash = FUN_71038f4000(param_1, 1, 0);
        } else {
            effect_hash = 0;
        }
    } else {
        if (nargs >= 2) {
            effect_hash = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 12) {
                alt_hash = FUN_71038f4000(param_1, 0xc, 0);
            }
        } else {
            effect_hash = 0;
        }
    }

    // Read arg 13: joint hash
    u64 joint_hash = 0;
    if (nargs >= 13) {
        joint_hash = FUN_71038f4000(param_1, 0xd, 0);
    }

    // req_follow with joint_hash in position 8
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, joint_hash, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710229d0a0 (932 bytes) — EFFECT_COLOR
// Parses 16 EFFECT args via FUN_7102288620, calls req_on_joint, then reads 3 extra
// float args (17-19) for RGB and calls set_color (vtable offset 0x2F8)
extern "C" void EFFECT_COLOR(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 0);

    // req_on_joint → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    // Read RGB: args 17-19 (offsets 0x110, 0x120, 0x130)
    f32 r = 0, g = 0, b = 0;
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    if (param_1 == nullptr) {
        // null path — dead code
    } else if (nargs >= 17) {
        r = acmd_read_float(L, 0x110);
        if (nargs >= 18) {
            g = acmd_read_float(L, 0x120);
            if (nargs >= 19) {
                b = acmd_read_float(L, 0x130);
            }
        }
    }

    // EffectModule::set_color (vtable offset 0x2F8)
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>(eff->_vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d450 (932 bytes) — EFFECT_COLOR_WORK
// Identical to EFFECT_COLOR
extern "C" void EFFECT_COLOR_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 0);

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    f32 r = 0, g = 0, b = 0;
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    if (param_1 == nullptr) {
        // null path — dead code
    } else if (nargs >= 17) {
        r = acmd_read_float(L, 0x110);
        if (nargs >= 18) {
            g = acmd_read_float(L, 0x120);
            if (nargs >= 19) {
                b = acmd_read_float(L, 0x130);
            }
        }
    }

    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>(eff->_vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d800 (476 bytes) — EFFECT_ALPHA
// Parses 16 EFFECT args via FUN_7102288620, calls req_on_joint, then reads 1 extra
// float arg (17) for alpha and calls set_alpha_last (vtable offset 0x308)
extern "C" void EFFECT_ALPHA(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 0);

    // req_on_joint → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    // Read alpha: arg 17 (offset 0x110)
    f32 alpha = 0.0f;

    if (param_1 == nullptr) {
        // null path — dead code
    } else if (nargs >= 17) {
        alpha = acmd_read_float(L, 0x110);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32)>(eff->_vt[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x71022973a0 (380 bytes) — EFFECT_FLIP
// Calls FUN_7102288620 in flip mode (mode=1), checks MotionModule flip state,
// swaps hash arg, then calls req_on_joint (vtable 0x70)
extern "C" void EFFECT_FLIP(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 1);  // mode=1 for flip (shifts arg indices by 1)

    // Check MotionModule flip state (vtable[0x390/8] at acc+0x88)
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        // Not flipped: hash from arg 1
        if (nargs >= 1) {
            out.hash1 = FUN_71038f4000(param_1, 1, 0);
        } else {
            out.hash1 = 0;
        }
    } else {
        // Flipped: hash from arg 2, alt_hash from arg 18
        if (nargs >= 2) {
            out.hash1 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 18) {
                alt_hash = FUN_71038f4000(param_1, 0x12, 0);
            }
        } else {
            out.hash1 = 0;
        }
    }

    // req_on_joint with parsed args + alt_hash
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    f32 rate = *(f32*)&out.rate_bits;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);

    acmd_consume(L);
}

// 0x71022a0ea0 (596 bytes) — EFFECT_FLIP_ALPHA
// Like EFFECT_FLIP but reads alpha at arg 19 (offset 0x130) and calls set_alpha_last
extern "C" void EFFECT_FLIP_ALPHA(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 1);

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        if (nargs >= 1) {
            out.hash1 = FUN_71038f4000(param_1, 1, 0);
        } else {
            out.hash1 = 0;
        }
    } else {
        if (nargs >= 2) {
            out.hash1 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 18) {
                alt_hash = FUN_71038f4000(param_1, 0x12, 0);
            }
        } else {
            alt_hash = 0;
            out.hash1 = 0;
        }
    }

    // req_on_joint → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);

    // Read alpha: arg 19 (offset 0x130, since flip mode shifts by 1)
    f32 alpha = 0.0f;
    if (nargs >= 19) {
        alpha = acmd_read_float(L, 0x130);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    reinterpret_cast<void(*)(void*, u32, f32)>(eff->_vt[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x710228b030 — EFFECT
// 16-arg ACMD effect command: 2 hashes + pos + rot + rate + scale + color + follow
// Same as EFFECT_ATTR but without attr_hash (17th arg), passes 0 for attr position
extern "C" void EFFECT(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 a3 = 0, a4 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
    f32 a10 = 0, a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0;
    u64 a5_int = 0;
    bool a16 = false;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                a3 = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    a4 = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        f32 a5f = acmd_read_float(L, 0x50);
                        a5_int = (u64)(u32)a5f;
                        if (nargs >= 6) {
                            a6 = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                a7 = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    a8 = acmd_read_float(L, 0x80);
                                    if (nargs >= 9) {
                                        a9 = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            a10 = acmd_read_float(L, 0xa0);
                                            if (nargs >= 11) {
                                                a11 = acmd_read_float(L, 0xb0);
                                                if (nargs >= 12) {
                                                    a12 = acmd_read_float(L, 0xc0);
                                                    if (nargs >= 13) {
                                                        a13 = acmd_read_float(L, 0xd0);
                                                        if (nargs >= 14) {
                                                            a14 = acmd_read_float(L, 0xe0);
                                                            if (nargs >= 15) {
                                                                a15 = acmd_read_float(L, 0xf0);
                                                                if (nargs >= 16) {
                                                                    a16 = acmd_read_bool(L, 0x100);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } vec_pos   = { a3, a4, a5_int };
    struct { f32 x; f32 y; u64 z; } vec_rot   = { a6, a7, (u64)(u32)a8 };
    struct { f32 x; f32 y; u64 z; } vec_scale  = { a10, a11, (u64)(u32)a12 };
    struct { f32 x; f32 y; u64 z; } vec_color  = { a13, a14, (u64)(u32)a15 };

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_color, a16, 0, 0, 0, a9);

    acmd_consume(L);
}

// 0x710228fb30 — EFFECT_WORK_R
// Like EFFECT but all position/rotation/scale/color values are WorkModule indices (integers)
// Reads floats then truncates to u32 for all vector components
extern "C" void EFFECT_WORK_R(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    // Group 1: hashes + pos (args 1-5)
    u64 hash1 = 0, hash2 = 0;
    u64 a3 = 0, a4 = 0, a5 = 0;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                a3 = (u64)(u32)acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    a4 = (u64)(u32)acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        a5 = (u64)(u32)acmd_read_float(L, 0x50);
                    }
                }
            }
        }
    }
    struct { u32 x; u32 y; u64 z; } vec_pos = { (u32)a3, (u32)a4, a5 };

    // Group 2: rot (args 6-8)
    u64 a6 = 0, a7 = 0, a8 = 0;
    if (nargs >= 6) {
        a6 = (u64)(u32)acmd_read_float(L, 0x60);
        if (nargs >= 7) {
            a7 = (u64)(u32)acmd_read_float(L, 0x70);
            if (nargs >= 8) {
                a8 = (u64)(u32)acmd_read_float(L, 0x80);
            }
        }
    }
    struct { u32 x; u32 y; u64 z; } vec_rot = { (u32)a6, (u32)a7, a8 };

    // Group 3: rate + scale (args 9-12)
    u64 rate_int = 0;
    u64 a10 = 0, a11 = 0, a12 = 0;
    if (nargs >= 9) {
        rate_int = (u64)(u32)acmd_read_float(L, 0x90);
        if (nargs >= 10) {
            a10 = (u64)(u32)acmd_read_float(L, 0xa0);
            if (nargs >= 11) {
                a11 = (u64)(u32)acmd_read_float(L, 0xb0);
                if (nargs >= 12) {
                    a12 = (u64)(u32)acmd_read_float(L, 0xc0);
                }
            }
        }
    }
    struct { u32 x; u32 y; u64 z; } vec_scale = { (u32)a10, (u32)a11, a12 };

    // Group 4: color (args 13-15) + follow (arg 16)
    u64 a13 = 0, a14 = 0, a15 = 0;
    if (nargs >= 13) {
        a13 = (u64)(u32)acmd_read_float(L, 0xd0);
        if (nargs >= 14) {
            a14 = (u64)(u32)acmd_read_float(L, 0xe0);
            if (nargs >= 15) {
                a15 = (u64)(u32)acmd_read_float(L, 0xf0);
            }
        }
    }
    struct { u32 x; u32 y; u64 z; } vec_color = { (u32)a13, (u32)a14, a15 };

    bool follow = false;
    if (nargs >= 16) {
        follow = acmd_read_bool(L, 0x100);
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_color, follow, 0, 0, 0, (f32)(u32)rate_int);

    acmd_consume(L);
}

// 0x71022a1a20 — EFFECT_BRANCH_SITUATION
// Like EFFECT but selects hash based on ground/air situation
// Args: 1=ground_hash, 2=air_hash, 3=joint_hash, 4-17=pos/rot/rate/scale/color/follow
extern "C" void EFFECT_BRANCH_SITUATION(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    u64 saved_top = *(u64*)(L + 0x10);
    u64 saved_base = **(u64**)(L + 0x20);

    // Check situation via EffectModule vtable[125] (offset 0x3E8)
    app::EffectModule* eff_check = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 situation = reinterpret_cast<u32(*)(void*)>(eff_check->_vt[1000 / 8])(eff_check);

    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }

    int nargs = (int)((saved_top - (saved_base + 0x10)) >> 4);

    // Select hash based on situation bit 0:
    // Ground (bit0=0) → read arg 1; Air (bit0=1) → read arg 2
    u64 hash1 = 0;
    if ((s32)(situation & 1) < nargs) {
        s32 hash_arg = 1;
        if ((situation & 1) != 0) {
            hash_arg = 2;
        }
        hash1 = FUN_71038f4000(param_1, hash_arg, 0);
    }

    u64 hash2 = 0;
    f32 a4 = 0, a5 = 0, a7 = 0, a8 = 0, a9 = 0, a10 = 0;
    f32 a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0, a16 = 0;
    u64 a6_int = 0;
    bool a17 = false;

    if (nargs >= 3) {
        hash2 = FUN_71038f4000(param_1, 3, 0);
        if (nargs >= 4) {
            a4 = acmd_read_float(L, 0x40);
            if (nargs >= 5) {
                a5 = acmd_read_float(L, 0x50);
                if (nargs >= 6) {
                    f32 a6f = acmd_read_float(L, 0x60);
                    a6_int = (u64)(u32)a6f;
                    if (nargs >= 7) {
                        a7 = acmd_read_float(L, 0x70);
                        if (nargs >= 8) {
                            a8 = acmd_read_float(L, 0x80);
                            if (nargs >= 9) {
                                a9 = acmd_read_float(L, 0x90);
                                if (nargs >= 10) {
                                    a10 = acmd_read_float(L, 0xa0);
                                    if (nargs >= 11) {
                                        a11 = acmd_read_float(L, 0xb0);
                                        if (nargs >= 12) {
                                            a12 = acmd_read_float(L, 0xc0);
                                            if (nargs >= 13) {
                                                a13 = acmd_read_float(L, 0xd0);
                                                if (nargs >= 14) {
                                                    a14 = acmd_read_float(L, 0xe0);
                                                    if (nargs >= 15) {
                                                        a15 = acmd_read_float(L, 0xf0);
                                                        if (nargs >= 16) {
                                                            a16 = acmd_read_float(L, 0x100);
                                                            if (nargs >= 17) {
                                                                a17 = acmd_read_bool(L, 0x110);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    struct { f32 x; f32 y; u64 z; } vec_pos   = { a4, a5, a6_int };
    struct { f32 x; f32 y; u64 z; } vec_rot   = { a7, a8, (u64)(u32)a9 };
    struct { f32 x; f32 y; u64 z; } vec_scale  = { a11, a12, (u64)(u32)a13 };
    struct { f32 x; f32 y; u64 z; } vec_color  = { a14, a15, (u64)(u32)a16 };

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (eff->_vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_color, a17, 0, 0, 0, a10);

    acmd_consume(L);
}

// ---------------------------------------------------------------------------
// XOR-shift128 PRNG inline step
// Uses global state DAT_71052381c0-cc, returns new random u32
// ---------------------------------------------------------------------------
static inline u32 xorshift128_next() {
    u32 t = DAT_71052381c0 ^ (DAT_71052381c0 << 11);
    DAT_71052381c0 = DAT_71052381c4;
    DAT_71052381c4 = DAT_71052381c8;
    t = t ^ (t >> 8) ^ DAT_71052381cc ^ (DAT_71052381cc >> 19);
    DAT_71052381c8 = DAT_71052381cc;
    DAT_71052381cc = t;
    return t;
}

// Apply RNG offset: base + range * random * norm - range * 0.5
static inline f32 apply_rng(f32 base, f32 range, u32 rng) {
    return base + range * (f32)rng * DAT_7104472710 + range * -0.5f;
}

// 0x710229e280 — EFFECT_FOLLOW_RND
// Like EFFECT_FOLLOW but with XOR-shift128 random offsets on position and rotation
// Args: 1-2=hashes, 3-5=offset(int), 6-8=rot(float), 9=scale, 10-15=rng ranges, 16=follow
extern "C" void EFFECT_FOLLOW_RND(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    // Group 1: hashes + offset (args 1-5, offsets as integers)
    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                off_x = (u64)(u32)acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    off_y = (u64)(u32)acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        off_z = (u64)(u32)acmd_read_float(L, 0x50);
                    }
                }
            }
        }
    }
    // Pack offset: x as float (for later RNG math), y as int
    struct { f32 x; u32 y; u64 z; } off_vec = { (f32)(u32)off_x, (u32)off_y, off_z };

    // Group 2: rotation (args 6-8, as floats)
    f32 rot_x = 0.0f, rot_y = 0.0f, rot_z_f = 0.0f;
    if (nargs >= 6) {
        rot_x = acmd_read_float(L, 0x60);
        if (nargs >= 7) {
            rot_y = acmd_read_float(L, 0x70);
            if (nargs >= 8) {
                rot_z_f = acmd_read_float(L, 0x80);
            }
        }
    }
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, (u64)(u32)rot_z_f };

    // Arg 9: scale
    f32 scale = 0.0f;
    if (nargs >= 9) {
        scale = acmd_read_float(L, 0x90);
    }

    // Follow setup defaults
    u32 flags = 0x8000;

    // Arg 10: RNG range for offset_x
    f32 range = 0.0f;
    if (nargs >= 10) {
        range = acmd_read_float(L, 0xa0);
    }
    // PRNG step + apply to offset_x
    u32 rng = xorshift128_next();
    off_vec.x = apply_rng((f32)(u32)off_x, range, rng);

    // Arg 11: RNG range for offset_y
    range = 0.0f;
    if (nargs >= 11) {
        range = acmd_read_float(L, 0xb0);
    }
    rng = xorshift128_next();
    f32 off_y_f = (f32)(u32)off_y;
    off_vec.y = (u32)apply_rng(off_y_f, range, rng);

    // Arg 12: RNG range for offset_z
    range = 0.0f;
    if (nargs >= 12) {
        range = acmd_read_float(L, 0xc0);
    }
    rng = xorshift128_next();
    off_vec.z = (u64)(u32)apply_rng((f32)(u32)off_z, range, rng);

    // Arg 13: RNG range for rot_x
    range = 0.0f;
    if (nargs >= 13) {
        range = acmd_read_float(L, 0xd0);
    }
    rng = xorshift128_next();
    rot_vec.x = apply_rng(rot_x, range, rng);

    // Arg 14: RNG range for rot_y
    range = 0.0f;
    if (nargs >= 14) {
        range = acmd_read_float(L, 0xe0);
    }
    rng = xorshift128_next();
    rot_vec.y = apply_rng(rot_y, range, rng);

    // Arg 15: RNG range for rot_z
    range = 0.0f;
    if (nargs >= 15) {
        range = acmd_read_float(L, 0xf0);
    }
    rng = xorshift128_next();
    rot_vec.z = (u64)(u32)apply_rng(rot_z_f, range, rng);

    // Arg 16: follow flag
    if (nargs >= 16) {
        bool follow = acmd_read_bool(L, 0x100);
        if (follow) flags = 0xc000;
    }

    // EffectModule::req_follow (vtable[16], offset 0x80)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, (u64)flags, 0, (s32)-1, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x710229f0e0 — EFFECT_FOLLOW_RND_WORK
// Like EFFECT_FOLLOW_RND but all offsets/rotations as work indices (integers)
// Reads arg 1 hash twice (once to prime, once for the vtable call)
extern "C" void EFFECT_FOLLOW_RND_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    // Prime read of arg 1 (result discarded for WORK variant)
    if (nargs >= 1 && param_1 != nullptr) {
        FUN_71038f4000(param_1, 1, 0);
    }

    // Group 1: hash2 + offset (args 2-5, all as integers)
    u64 hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;
    if (nargs >= 2) {
        hash2 = FUN_71038f4000(param_1, 2, 0);
        if (nargs >= 3) {
            off_x = (u64)(u32)acmd_read_float(L, 0x30);
            if (nargs >= 4) {
                off_y = (u64)(u32)acmd_read_float(L, 0x40);
                if (nargs >= 5) {
                    off_z = (u64)(u32)acmd_read_float(L, 0x50);
                }
            }
        }
    }
    struct { f32 x; u32 y; u64 z; } off_vec = { (f32)(u32)off_x, (u32)off_y, off_z };

    // Group 2: rotation (args 6-8, as integers)
    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        rot_x = (u64)(u32)acmd_read_float(L, 0x60);
        if (nargs >= 7) {
            rot_y = (u64)(u32)acmd_read_float(L, 0x70);
            if (nargs >= 8) {
                rot_z = (u64)(u32)acmd_read_float(L, 0x80);
            }
        }
    }
    struct { u32 x; u32 y; u64 z; } rot_vec = { (u32)rot_x, (u32)rot_y, rot_z };

    // Arg 9: scale
    f32 scale = 0.0f;
    if (nargs >= 9) {
        scale = acmd_read_float(L, 0x90);
    }

    // Follow setup defaults
    u32 follow_flags = 0x8000;

    // Re-read hash1 from arg 1
    u64 hash1 = 0;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
    }

    // Arg 10: RNG range for offset_x
    f32 range = 0.0f;
    if (nargs >= 10) {
        range = acmd_read_float(L, 0xa0);
    }
    u32 rng = xorshift128_next();
    off_vec.x = apply_rng((f32)(u32)off_x, range, rng);

    // Arg 11: RNG range for offset_y
    range = 0.0f;
    if (nargs >= 11) {
        range = acmd_read_float(L, 0xb0);
    }
    rng = xorshift128_next();
    off_vec.y = (u32)apply_rng((f32)(u32)off_y, range, rng);

    // Arg 12: RNG range for offset_z
    range = 0.0f;
    if (nargs >= 12) {
        range = acmd_read_float(L, 0xc0);
    }
    rng = xorshift128_next();
    off_vec.z = (u64)(u32)apply_rng((f32)(u32)off_z, range, rng);

    // Arg 13: RNG range for rot_x
    range = 0.0f;
    if (nargs >= 13) {
        range = acmd_read_float(L, 0xd0);
    }
    rng = xorshift128_next();
    rot_vec.x = (u32)apply_rng((f32)(u32)rot_x, range, rng);

    // Arg 14: RNG range for rot_y
    range = 0.0f;
    if (nargs >= 14) {
        range = acmd_read_float(L, 0xe0);
    }
    rng = xorshift128_next();
    rot_vec.y = (u32)apply_rng((f32)(u32)rot_y, range, rng);

    // Arg 15: RNG range for rot_z
    range = 0.0f;
    if (nargs >= 15) {
        range = acmd_read_float(L, 0xf0);
    }
    rng = xorshift128_next();
    rot_vec.z = (u64)(u32)apply_rng((f32)(u32)rot_z, range, rng);

    // Arg 16: follow flag
    if (nargs >= 16) {
        bool follow = acmd_read_bool(L, 0x100);
        if (follow) follow_flags = 0xc000;
    }

    // EffectModule::req_follow (vtable[16], offset 0x80)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, (u64)follow_flags, 0, (s32)-1, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x710229ff20 — EFFECT_FOLLOW_FLIP_RND
// Like EFFECT_FOLLOW_RND but with MotionModule flip check + hash swap
// Args: 1=ground_hash, 2=air_hash, 3=joint_hash, 4-9=off/rot(float),
//       10=scale, 11-16=rng ranges, 17=follow
extern "C" void EFFECT_FOLLOW_FLIP_RND(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    // Read joint hash (arg 3)
    u64 joint_hash = 0;
    if (param_1 == nullptr) {
        // Null path: read from constant address
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    } else {
        if (nargs >= 3) {
            joint_hash = FUN_71038f4000(param_1, 3, 0);
        }
    }

    // Read offsets as floats (args 4-6)
    f32 off_x = 0.0f, off_y = 0.0f, off_z_f = 0.0f;
    if (nargs >= 4) {
        off_x = acmd_read_float(L, 0x40);
        if (nargs >= 5) {
            off_y = acmd_read_float(L, 0x50);
            if (nargs >= 6) {
                off_z_f = acmd_read_float(L, 0x60);
                if (nargs >= 7) {
                    // Read rotations as floats (args 7-9)
                    f32 rot_x_val = acmd_read_float(L, 0x70);
                    f32 rot_y_val = 0.0f;
                    f32 rot_z_val = 0.0f;
                    f32 scale_val = 0.0f;
                    if (nargs >= 8) {
                        rot_y_val = acmd_read_float(L, 0x80);
                        if (nargs >= 9) {
                            rot_z_val = acmd_read_float(L, 0x90);
                            if (nargs >= 10) {
                                scale_val = acmd_read_float(L, 0xa0);
                            }
                        }
                    }

                    // Pack rotation
                    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x_val, rot_y_val, (u64)(u32)rot_z_val };

                    // Arg 11: RNG range for off_x
                    f32 range_off_x = 0.0f;
                    if (nargs >= 11) {
                        range_off_x = acmd_read_float(L, 0xb0);
                    }

                    // PRNG step + apply offset_x
                    u32 rng = xorshift128_next();
                    f32 new_off_x = apply_rng(off_x, range_off_x, rng);

                    // Arg 12: RNG range for off_y
                    f32 range_off_y = 0.0f;
                    if (nargs >= 12) {
                        range_off_y = acmd_read_float(L, 0xc0);
                    }
                    rng = xorshift128_next();
                    f32 new_off_y = apply_rng(off_y, range_off_y, rng);

                    // Arg 13: RNG range for off_z
                    f32 range_off_z = 0.0f;
                    if (nargs >= 13) {
                        range_off_z = acmd_read_float(L, 0xd0);
                    }
                    rng = xorshift128_next();
                    f32 new_off_z_f = apply_rng(off_z_f, range_off_z, rng);

                    // Pack offset with randomization applied
                    struct { f32 x; f32 y; u64 z; } off_vec = { new_off_x, new_off_y, (u64)(u32)new_off_z_f };

                    // Arg 14: RNG range for rot_x
                    f32 range_rot_x = 0.0f;
                    if (nargs >= 14) {
                        range_rot_x = acmd_read_float(L, 0xe0);
                    }
                    rng = xorshift128_next();
                    rot_vec.x = apply_rng(rot_x_val, range_rot_x, rng);

                    // Arg 15: RNG range for rot_y
                    f32 range_rot_y = 0.0f;
                    if (nargs >= 15) {
                        range_rot_y = acmd_read_float(L, 0xf0);
                    }
                    rng = xorshift128_next();
                    rot_vec.y = apply_rng(rot_y_val, range_rot_y, rng);

                    // Arg 16: RNG range for rot_z
                    f32 range_rot_z = 0.0f;
                    if (nargs >= 16) {
                        range_rot_z = acmd_read_float(L, 0x100);
                    }
                    rng = xorshift128_next();
                    rot_vec.z = (u64)(u32)apply_rng(rot_z_val, range_rot_z, rng);

                    // Arg 17: follow flag
                    u32 follow_flags = 0x8000;
                    if (nargs >= 17) {
                        bool follow = acmd_read_bool(L, 0x110);
                        if (follow) follow_flags = 0xc000;
                    }

                    // Check MotionModule flip state (vtable offset 0x390)
                    void** motion = *(void***)(acc + 0x88);
                    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

                    // Select hash based on flip
                    u64 hash1;
                    u64 alt_hash = 0;
                    if ((is_flip & 1) == 0) {
                        // Not flipped: use arg 1
                        if (nargs >= 1) {
                            hash1 = FUN_71038f4000(param_1, 1, 0);
                        } else {
                            hash1 = 0;
                        }
                    } else {
                        // Flipped: use arg 2
                        if (nargs >= 2) {
                            hash1 = FUN_71038f4000(param_1, 2, 0);
                            if (nargs >= 18) {
                                alt_hash = FUN_71038f4000(param_1, 0x12, 0);
                            }
                        } else {
                            hash1 = 0;
                        }
                    }

                    // EffectModule::req_follow (vtable[16], offset 0x80)
                    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                
                    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, f32)>
                        (eff->_vt[0x80 / 8])(eff, hash1, joint_hash, &off_vec, &rot_vec, 0, (u64)follow_flags, 0, (s32)-1, alt_hash, 0, 0, scale_val);

                    acmd_consume(L);
                    return;
                }
            }
        }
    }

    // Fallback: not enough args - pack with defaults and call
    struct { f32 x; f32 y; u64 z; } off_vec_def = { off_x, off_y, (u64)(u32)off_z_f };
    struct { f32 x; f32 y; u64 z; } rot_vec_def = { 0.0f, 0.0f, 0 };
    u32 follow_flags = 0x8000;

    // Check MotionModule flip state
    void** motion = *(void***)(acc + 0x88);
    u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

    u64 hash1;
    u64 alt_hash = 0;
    if ((is_flip & 1) == 0) {
        if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        if (nargs >= 1) {
            hash1 = FUN_71038f4000(param_1, 1, 0);
        } else {
            hash1 = 0;
        }
    } else {
        if (nargs >= 2) {
            hash1 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 18) {
                alt_hash = FUN_71038f4000(param_1, 0x12, 0);
            }
        } else {
            hash1 = 0;
        }
    }

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, joint_hash, &off_vec_def, &rot_vec_def, 0, (u64)follow_flags, 0, (s32)-1, alt_hash, 0, 0, 0.0f);

    acmd_consume(L);
}

// 0x71022989b0 (688 bytes) — LANDING_EFFECT
// Uses FUN_7102288620 shared parser, checks landing enabled, terrain lookup via StageManager
extern "C" void LANDING_EFFECT(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.L = param_1;

    // Check EffectModule::is_landing_enabled (vtable[0x3d8/8])
    app::EffectModule* eff_check = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 enabled = reinterpret_cast<u64(*)(void*)>(eff_check->_vt[0x3d8 / 8])(eff_check);
    if ((enabled & 1) == 0) goto landing_consume;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 0);

    // GroundModule::get_terrain_kind (vtable[0x478/8]) with arg 8
    {
        void** ground = *(void***)(acc + 0x58);
        int terrain_kind = reinterpret_cast<int(*)(void*, int)>((*(void***)ground)[0x478 / 8])(ground, 8);

        u32 terrain_flag = 0;
        if (terrain_kind != 0) {
            u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this = stage_mgr + 0x128;
            u64 terrain_data = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this + 0x1f8))(terrain_this, terrain_kind);

            // Check terrain[0x40] flag — if false, disable effect
            if (*(u8*)(terrain_data + 0x40) == 0) {
                out.hash1 = 0x425cbfc4fULL;
            }

            terrain_flag = (terrain_kind == 10 || terrain_kind == 0x2b) ? 0x4000000u : 0u;
        }

        // First req_on_joint call with primary hash
        app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        u64 hash1_masked = out.hash1 & 0xffffffffffULL;
        if (hash1_masked == 0xe3c234564ULL || hash1_masked == 0x14a422ea56ULL || hash1_masked == 0x11b722b99fULL) {
            u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
            u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
            eff->preset_limit_num(param_val);
            eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        }
        f32 rate = *(f32*)&out.rate_bits;
        reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
            (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

        // Second req_on_joint with terrain's secondary hash (terrain_data[0x48])
        if (terrain_kind != 0) {
            u64 stage_mgr2 = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this2 = stage_mgr2 + 0x128;
            u64 terrain_data2 = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this2 + 0x1f8))(terrain_this2, terrain_kind);

            eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            u64 secondary_hash = *(u64*)(terrain_data2 + 0x48);
            u64 sec_masked = secondary_hash & 0xffffffffffULL;
            if (sec_masked == 0xe3c234564ULL || sec_masked == 0x14a422ea56ULL || sec_masked == 0x11b722b99fULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
                eff->preset_limit_num(param_val);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                secondary_hash = *(u64*)(terrain_data2 + 0x48);
            }
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, secondary_hash, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, terrain_flag, 0, 0, rate);
        }
    }

landing_consume:
    acmd_consume(L);
}

// 0x7102298c60 (828 bytes) — LANDING_EFFECT_FLIP
// Like LANDING_EFFECT but with MotionModule flip check for hash swap
extern "C" void LANDING_EFFECT_FLIP(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    int nargs = (int)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    // Check EffectModule::is_landing_enabled (vtable[0x3d8/8])
    app::EffectModule* eff_check = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 enabled = reinterpret_cast<u64(*)(void*)>(eff_check->_vt[0x3d8 / 8])(eff_check);
    if ((enabled & 1) == 0) goto landing_flip_consume;

    {
        acmd_effect_out out;
        FUN_7102288620(&out, &ctrl, 1);  // mode 1 = flip-aware parsing

        // MotionModule flip check (vtable[0x390/8])
        void** motion = *(void***)(acc + 0x88);
        u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

        u32 alt_hash = 0;
        if ((is_flip & 1) == 0) {
            // Not flipped: use arg 1
            if (nargs >= 1) {
                out.hash1 = FUN_71038f4000(param_1, 1, 0);
            } else {
                out.hash1 = 0;
            }
        } else {
            // Flipped: use arg 2
            if (nargs >= 2) {
                out.hash1 = FUN_71038f4000(param_1, 2, 0);
                if (nargs >= 18) {
                    alt_hash = (u32)FUN_71038f4000(param_1, 0x12, 0);
                }
            } else {
                out.hash1 = 0;
                alt_hash = 0;
            }
        }

        // GroundModule::get_terrain_kind
        void** ground = *(void***)(acc + 0x58);
        int terrain_kind = reinterpret_cast<int(*)(void*, int)>((*(void***)ground)[0x478 / 8])(ground, 8);

        u32 terrain_flag = 0;
        if (terrain_kind != 0) {
            u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this = stage_mgr + 0x128;
            u64 terrain_data = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this + 0x1f8))(terrain_this, terrain_kind);

            if (*(u8*)(terrain_data + 0x40) == 0) {
                out.hash1 = 0x425cbfc4fULL;
            }
            terrain_flag = (terrain_kind == 10 || terrain_kind == 0x2b) ? 0x4000000u : 0u;
        }

        // First req_on_joint
        app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        u64 hash1_masked = out.hash1 & 0xffffffffffULL;
        if (hash1_masked == 0xe3c234564ULL || hash1_masked == 0x14a422ea56ULL || hash1_masked == 0x11b722b99fULL) {
            u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
            u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
            eff->preset_limit_num(param_val);
            eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
        }
        f32 rate = *(f32*)&out.rate_bits;
        reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
            (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);

        // Second req_on_joint with terrain secondary hash
        if (terrain_kind != 0) {
            u64 stage_mgr2 = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this2 = stage_mgr2 + 0x128;
            u64 terrain_data2 = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this2 + 0x1f8))(terrain_this2, terrain_kind);

            eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            u64 secondary_hash = *(u64*)(terrain_data2 + 0x48);
            u64 sec_masked = secondary_hash & 0xffffffffffULL;
            if (sec_masked == 0xe3c234564ULL || sec_masked == 0x14a422ea56ULL || sec_masked == 0x11b722b99fULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
                eff->preset_limit_num(param_val);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                secondary_hash = *(u64*)(terrain_data2 + 0x48);
            }
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, secondary_hash, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, terrain_flag, alt_hash, 0, rate);
        }
    }

landing_flip_consume:
    acmd_consume(L);
}

// 0x7102298640 (880 bytes) — FOOT_EFFECT_FLIP
// Like LANDING_EFFECT_FLIP but for foot effects: vtable[0x3d0/8], terrain[0x18],
// plus special case for hash 0xe3c234564 with FighterParamAccessor2 position
extern "C" void FOOT_EFFECT_FLIP(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 wrapper = *(u64*)(L - 8);
    u64 acc = *(u64*)(wrapper + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    int nargs = (int)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    // Check EffectModule::is_foot_enabled (vtable[0x3d0/8])
    app::EffectModule* eff_check = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 enabled = reinterpret_cast<u64(*)(void*)>(eff_check->_vt[0x3d0 / 8])(eff_check);
    if ((enabled & 1) == 0) goto foot_flip_consume;

    {
        acmd_effect_out out;
        FUN_7102288620(&out, &ctrl, 1);

        // MotionModule flip check
        void** motion = *(void***)(acc + 0x88);
        u64 is_flip = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x390 / 8])(motion);

        u32 alt_hash = 0;
        if ((is_flip & 1) == 0) {
            if (nargs >= 1) {
                out.hash1 = FUN_71038f4000(param_1, 1, 0);
            } else {
                out.hash1 = 0;
            }
        } else {
            if (nargs >= 2) {
                out.hash1 = FUN_71038f4000(param_1, 2, 0);
                if (nargs >= 18) {
                    alt_hash = (u32)FUN_71038f4000(param_1, 0x12, 0);
                }
            } else {
                out.hash1 = 0;
                alt_hash = 0;
            }
        }

        // GroundModule::get_terrain_kind
        void** ground = *(void***)(acc + 0x58);
        int terrain_kind = reinterpret_cast<int(*)(void*, int)>((*(void***)ground)[0x478 / 8])(ground, 8);

        if (terrain_kind != 0) {
            u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this = stage_mgr + 0x128;
            u64 terrain_data = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this + 0x1f8))(terrain_this, terrain_kind);

            u32 terrain_flag = (terrain_kind == 10 || terrain_kind == 0x2b) ? 0x4000000u : 0u;

            u64 terrain_hash = *(u64*)(terrain_data + 0x18);
            u64 th_masked = terrain_hash & 0xffffffffffULL;

            app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            if (th_masked == 0xe3c234564ULL || th_masked == 0x14a422ea56ULL || th_masked == 0x11b722b99fULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
                eff->preset_limit_num(param_val);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                terrain_hash = *(u64*)(terrain_data + 0x18);
            }

            f32 rate = *(f32*)&out.rate_bits;
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, terrain_hash, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, terrain_flag, alt_hash, 0, rate);

            // Special case: hash 0xe3c234564 with FighterParamAccessor2 position
            if (*(u8*)(wrapper + 0x194) == 0 && (*(u64*)(terrain_data + 0x18) & 0xffffffffffULL) == 0xe3c234564ULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u64 param_base = *(u64*)(fpa2 + 0x50);
                // Read secondary position from param data
                u64 sec_pos_xy = *(u64*)(param_base + 0x1630);
                u64 sec_pos_z = (u64)*(u32*)(param_base + 0x1638);

                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                u32 param_val = *(u32*)(param_base + 0x162c);
                eff->preset_limit_num(param_val);

                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                struct { u64 xy; u64 z; } sec_pos = { sec_pos_xy, sec_pos_z };
                u64 sec_effect_hash = 0x14a422ea56ULL;
                reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                    (eff->_vt[0x70 / 8])(eff, sec_effect_hash, out.hash2, &sec_pos, &out.rot_xy, &out.scale_xy, &out.color_xy, false, terrain_flag, alt_hash, 0, rate);
            }

            // Check terrain[0x10] flag
            if (*(u8*)(terrain_data + 0x10) == 0) {
                out.hash1 = 0x425cbfc4fULL;
            }
        }

        // Fallback req_on_joint if hash != sentinel
        if ((out.hash1 & 0xffffffffffULL) != 0x425cbfc4fULL) {
            app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            f32 rate = *(f32*)&out.rate_bits;
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);
        }
    }

foot_flip_consume:
    acmd_consume(L);
}

// 0x710228af60 (196 bytes) — REMOVE_FINAL_SCREEN_EFFECT
// Args: 1=effect_hash
// Uses global screen effect manager (DAT_71052b7710), not accessor
// Calls vtable[0x1f0/8] on sub-object at +0x3a0, then clears state fields
extern "C" void REMOVE_FINAL_SCREEN_EFFECT(lua_State* param_1) {
    u64 L = (u64)param_1;
    int nargs = acmd_nargs(L);

    u64 hash;
    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        hash = 0;
    } else if (nargs >= 1) {
        hash = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash = 0;
    }

    // DAT_71052b7710 → offset +8 → screen effect manager instance
    // +0x3a0 = effect sub-object, vtable[0x1f0/8] = remove_screen_effect
    u64 mgr = *(u64*)((u8*)DAT_71052b7710 + 8);
    void** sub_obj = *(void***)(mgr + 0x3a0);
    reinterpret_cast<void(*)(void*, u64)>((*(void***)sub_obj)[0x1f0 / 8])(sub_obj, hash);

    // Clear screen effect state
    *(u8*)(mgr + 0x438) = 0;
    *(u64*)(mgr + 0x43c) = 0;
    *(u32*)(mgr + 0x444) = 0;

    acmd_consume(L);
}

// 0x71022b4690 (172 bytes) — PLAY_LANDING_SE
// Args: 1=se_hash
// Calls SoundModule vtable[0x120/8] (play_landing_se)
// +0x148 = SoundModule [derived: accessor offset map]
extern "C" void PLAY_LANDING_SE(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;
    if (nargs < 1) {
        hash = 0;
    } else {
        hash = FUN_71038f4000(param_1, 1, 0);
    }

    void** snd = *(void***)(acc + 0x148);  // SoundModule [derived: accessor offset map]
    reinterpret_cast<void(*)(void*, u64)>((*(void***)snd)[0x120 / 8])(snd, hash);

    acmd_consume(L);
}

// 0x71022b4bc0 (172 bytes) — REG_LANDING_SE
// Args: 1=se_hash
// Calls SoundModule vtable[0x1c8/8] (reg_landing_se)
// +0x148 = SoundModule [derived: accessor offset map]
extern "C" void REG_LANDING_SE(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash;
    if (nargs < 1) {
        hash = 0;
    } else {
        hash = FUN_71038f4000(param_1, 1, 0);
    }

    void** snd = *(void***)(acc + 0x148);  // SoundModule [derived: accessor offset map]
    reinterpret_cast<void(*)(void*, u64)>((*(void***)snd)[0x1c8 / 8])(snd, hash);

    acmd_consume(L);
}

// 0x710228f460 (420 bytes) — EFFECT_GLOBAL_BACK_GROUND
// Calls FUN_710228ea70 with ConstantZero pos, 1.0f rate, flag=0x2000000
// If nargs >= 10, reads bool arg 10 → sets/clears bit 0x1000000 on EffectManager entry
// EffectManager: *instance_ is entries base, each entry 0x300 bytes
//   entry+4 = handle validation, entry+0x26c = flags
extern "C" void EFFECT_GLOBAL_BACK_GROUND(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    int nargs = (int)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    u32 handle = FUN_710228ea70(ConstantZero, 0x3f800000, acc, &ctrl, 0x2000000);

    if (nargs >= 10) {
        bool bg_flag = acmd_read_bool(L, 0xa0);

        if ((s32)handle > 0) {
            u64 em = *(u64*)lib::Singleton<lib::EffectManager>::instance_;
            u64 entry = em + (u64)(handle >> 24) * 0x300;
            if (entry != 0 && *(u32*)(entry + 4) == handle) {
                entry = *(u64*)lib::Singleton<lib::EffectManager>::instance_ + (u64)(handle >> 24) * 0x300;
                u32 flags = *(u32*)(entry + 0x26c);
                u32 new_flags;
                if (bg_flag) {
                    new_flags = flags | 0x1000000;
                } else {
                    new_flags = flags & 0xfeffffff;
                }
                *(u32*)(entry + 0x26c) = new_flags;
            }
        }
    }

    acmd_consume(L);
}

// 0x710228f610 (644 bytes) — EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE
// Like EFFECT_GLOBAL_BACK_GROUND_CUT_IN_CENTER_POS but with camera interpolation.
// If camera mode (DAT_71052b7f00+4) is 4 or 7, computes weighted normalized direction
// from camera to cutin position, then interpolates along that direction.
// Uses NEON rsqrt approximation in original — scalar math here (size mismatch expected).
extern "C" void EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    int nargs = (int)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    u64 cam_ctrl = *(u64*)DAT_71052b7f00;
    u64 cutin = (u64)lib::Singleton<app::FighterCutInManager>::instance_;
    u64 cutin_data = *(u64*)cutin;

    u64 pos;
    s32 cam_mode = *(s32*)(cam_ctrl + 4);
    if (cam_mode == 4 || cam_mode == 7) {
        // Camera position
        f32 cam_x = *(f32*)(cam_ctrl + 0xd30);
        f32 cam_y = *((f32*)(cam_ctrl + 0xd30) + 1);
        f32 cam_z = *(f32*)(cam_ctrl + 0xd38);
        f32 cam_w = *((f32*)(cam_ctrl + 0xd38) + 1);

        // CutIn target position
        f32 tgt_x = *(f32*)(cutin_data + 0x300);
        f32 tgt_y = *((f32*)(cutin_data + 0x300) + 1);

        // Direction from camera to target
        f32 dx = tgt_x - cam_x;
        f32 dy = tgt_y - cam_y;
        f32 dz = 0.0f - cam_z;
        f32 dw = 0.0f - cam_w;

        // Weighted direction (DAT_71044646b0 = weight vector, 4 floats)
        f32* weights = (f32*)&DAT_71044646b0;
        f32 wx = dx * weights[0];
        f32 wy = dy * weights[1];
        f32 wz = dz * weights[2];
        f32 ww = dw * weights[3];

        // Squared length
        f32 dot = wx*wx + wy*wy + wz*wz + ww*ww;

        // Safe normalize (skip if zero)
        f32 inv_len = 0;
        if (dot != 0.0f) {
            inv_len = 1.0f / dot;
        }
        f32 nx = (dot != 0.0f) ? dx * inv_len : 0.0f;
        f32 ny = (dot != 0.0f) ? dy * inv_len : 0.0f;

        // Weighted normalized direction
        f32 wnx = nx * weights[0];
        f32 wny = ny * weights[1];

        // Camera projection
        f32 cam_proj = cam_x * weights[0] + cam_y * weights[1] + cam_z * weights[2] + cam_w * weights[3];

        // Target value from DAT_7104464430
        f32* target = (f32*)&DAT_7104464430;
        f32 target_val = target[0] + target[1];

        f32 remaining = target_val - cam_proj;
        f32 wn_dot = wnx + wny;  // simplified dot of weighted normals

        if (wn_dot != 0.0f) {
            f32 t = remaining / wn_dot;
            f32 result_x = cam_x + nx * t;
            f32 result_y = cam_y + ny * t;
            u32 rx = *(u32*)&result_x;
            u32 ry = *(u32*)&result_y;
            pos = ((u64)ry << 32) | rx;
        } else {
            pos = *(u64*)(cutin_data + 0x300);
        }
    } else {
        pos = *(u64*)(cutin_data + 0x300);
    }

    u32 rate = *(u32*)(cutin_data + 0x340);
    u32 handle = FUN_710228ea70(pos, rate, acc, &ctrl, 0x2000000);

    if (nargs >= 10) {
        bool bg_flag = acmd_read_bool(L, 0xa0);

        if ((s32)handle > 0) {
            u64 em = *(u64*)lib::Singleton<lib::EffectManager>::instance_;
            u64 entry = em + (u64)(handle >> 24) * 0x300;
            if (entry != 0 && *(u32*)(entry + 4) == handle) {
                entry = *(u64*)lib::Singleton<lib::EffectManager>::instance_ + (u64)(handle >> 24) * 0x300;
                u32 flags = *(u32*)(entry + 0x26c);
                u32 new_flags;
                if (bg_flag) {
                    new_flags = flags | 0x1000000;
                } else {
                    new_flags = flags & 0xfeffffff;
                }
                *(u32*)(entry + 0x26c) = new_flags;
            }
        }
    }

    acmd_consume(L);
}

// 0x710228f8a0 (432 bytes) — EFFECT_GLOBAL_BACK_GROUND_CUT_IN_CENTER_POS
// Like EFFECT_GLOBAL_BACK_GROUND but reads pos from FighterCutInManager+0x2f0
// and rate from FighterCutInManager+0x340
extern "C" void EFFECT_GLOBAL_BACK_GROUND_CUT_IN_CENTER_POS(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    int nargs = (int)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.nargs = (u32)nargs;
    ctrl.L = param_1;

    u64 cutin = (u64)lib::Singleton<app::FighterCutInManager>::instance_;
    u64 pos = *(u64*)(cutin + 0x2f0);
    u32 rate = *(u32*)(cutin + 0x340);
    u32 handle = FUN_710228ea70(pos, rate, acc, &ctrl, 0x2000000);

    if (nargs >= 10) {
        bool bg_flag = acmd_read_bool(L, 0xa0);

        if ((s32)handle > 0) {
            u64 em = *(u64*)lib::Singleton<lib::EffectManager>::instance_;
            u64 entry = em + (u64)(handle >> 24) * 0x300;
            if (entry != 0 && *(u32*)(entry + 4) == handle) {
                entry = *(u64*)lib::Singleton<lib::EffectManager>::instance_ + (u64)(handle >> 24) * 0x300;
                u32 flags = *(u32*)(entry + 0x26c);
                u32 new_flags;
                if (bg_flag) {
                    new_flags = flags | 0x1000000;
                } else {
                    new_flags = flags & 0xfeffffff;
                }
                *(u32*)(entry + 0x26c) = new_flags;
            }
        }
    }

    acmd_consume(L);
}

// 0x71022a82a0 (632 bytes) — LAST_EFFECT_SET_TOP_OFFSET
// Reads 2 float args (x,y offsets), gets posture position via PostureModule vtable[12],
// adds offsets, then sets effect position via EffectModule::set_pos(last_handle, pos)
// +0x38 = PostureModule [derived: accessor offset map]
// +0x140 = EffectModule [derived: accessor offset map]
extern "C" void LAST_EFFECT_SET_TOP_OFFSET(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    u64 base = **(u64**)(L + 0x20) + 0x10;
    int nargs = (int)((*(u64*)(L + 0x10) - base) >> 4);

    f32 offset_x, offset_y;
    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        offset_x = 0.0f;
        offset_y = 0.0f;
    } else if (nargs < 1) {
        offset_x = 0.0f;
        offset_y = 0.0f;
    } else {
        offset_x = acmd_read_float(L, 0x10);
        offset_y = 0.0f;
        if (nargs >= 2) {
            offset_y = acmd_read_float(L, 0x20);
        }
    }

    // PostureModule vtable[12] (offset 0x60) → get_pos() returns Vec3* (x,y,z)
    void** posture = *(void***)(acc + 0x38);
    u64* pos = reinterpret_cast<u64*(*)(void*)>((*(void***)posture)[0x60 / 8])(posture);

    // pos[0] = {f32 x, f32 y}, pos[1] = {f32 z, ...}
    f32 pos_x = *(f32*)pos;
    f32 pos_y = *((f32*)pos + 1);
    u64 pos_z_raw = pos[1];

    struct { f32 x; f32 y; u64 z; } out_pos;
    out_pos.x = offset_x + pos_x;
    out_pos.y = offset_y + pos_y;
    out_pos.z = pos_z_raw;

    // EffectModule: vtable[0x3a0/8] = get_last_handle(), vtable[0x150/8] = set_pos(handle, pos)
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u32 last_handle = (u32)eff->get_last_handle();
    reinterpret_cast<void(*)(void*, u32, void*)>(eff->_vt[0x150 / 8])(eff, last_handle, &out_pos);

    acmd_consume(L);
}

// 0x71022a8010 (648 bytes) — SCREEN_EFFECT_SLOW_WHOLE
// Reads 2 args: 1=slow_kind (u8), 2=frame_count (s32)
// Updates BattleObjectSlow max frame, allocates slot in slow effect array
// DAT_71052b7710+8 = BattleObjectSlow instance
// DAT_71052c2610 = slow effect slot array (16 slots × 2 bytes: {active, kind})
extern "C" void SCREEN_EFFECT_SLOW_WHOLE(lua_State* param_1) {
    u64 L = (u64)param_1;
    int nargs = acmd_nargs(L);

    u8 slow_kind;
    s32 frame_count;
    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
        slow_kind = 0;
        frame_count = 0;
    } else if (nargs < 1) {
        slow_kind = 0;
        frame_count = 0;
    } else {
        slow_kind = (u8)FUN_71038f4000(param_1, 1, 0);
        if (nargs < 2) {
            frame_count = 0;
        } else {
            frame_count = (s32)FUN_71038f4000(param_1, 2, 0);
        }
    }

    u64 slow = *(u64*)((u8*)DAT_71052b7710 + 8);  // BattleObjectSlow instance

    // Update max frame count
    if (*(s32*)(slow + 0x450) < frame_count) {
        *(s32*)(slow + 0x450) = frame_count;
    }

    // If no slot assigned yet (0xFF), find a free slot
    if (*(u8*)(slow + 0x454) == 0xFF) {
        u64 slots = DAT_71052c2610;
        u8 slot_id = 0xFF;

        // Search 16 slots for an empty one (active == 0)
        for (s32 i = 0; i < 16; i++) {
            u8* slot = (u8*)(slots + 0x20 + i * 2);
            if (*slot == 0) {
                *slot = 1;
                *(u8*)(slots + 0x20 + i * 2 + 1) = slow_kind;
                *(u8*)(slots + 0x40) = 1;
                slot_id = (u8)i;
                break;
            }
        }

        *(u8*)(slow + 0x454) = slot_id;
    }

    acmd_consume(L);
}

// 0x71022a7c90 (692 bytes) — BACK_GROUND_EFFECT_STAGE_SET_HIDING_FOR_DIRECTION
// Reads 2 bool args: arg1 = enable flag, arg2 = direction flag
// If enable: iterates StageManager stage objects, updates visibility state
// If disable: calls FUN_710260ccd0 to reset hiding
// DAT_71052b7710+8 = BattleObjectSlow, +0x448 = bg_hiding_active flag
extern "C" void BACK_GROUND_EFFECT_STAGE_SET_HIDING_FOR_DIRECTION(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 top = *(u64*)(L + 0x10);
    u64 base_entry = **(u64**)(L + 0x20) + 0x10;
    int nargs = (int)((top - base_entry) >> 4);

    bool enable = false;
    bool direction = false;

    if (param_1 == nullptr) {
        if (nargs >= 1) {
#ifdef MATCHING_HACK_NX_CLANG
            __builtin_trap();
#endif
        }
    } else if (nargs >= 1) {
        enable = acmd_read_bool(L, 0x10);
        if (enable) {
            if (nargs < 2) {
                direction = false;
            } else {
                direction = acmd_read_bool(L, 0x20);
            }

            u64 slow = *(u64*)((u8*)DAT_71052b7710 + 8);

            if (*(u8*)(slow + 0x448) == 0) {
                u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;

                // Iterate stage objects: +0x210 = begin ptr, +0x218 = end ptr
                u64* iter = *(u64**)(stage_mgr + 0x210);
                u64* end = *(u64**)(stage_mgr + 0x218);

                while (iter != end) {
                    u64 obj = *iter;
                    u32 old_state = *(u32*)(obj + 0x38);
                    u32 counter = *(u32*)(obj + 0x2c);
                    *(u32*)(obj + 0x2c) = counter + 1;

                    u32 new_state;
                    if (*(s32*)(obj + 0x34) >= 1) {
                        new_state = 3;
                    } else if (*(s32*)(obj + 0x30) >= 1) {
                        new_state = 2;
                    } else {
                        new_state = (counter >> 31) ^ 1;
                    }
                    *(u32*)(obj + 0x38) = new_state;

                    if (old_state != new_state) {
                        struct { u32 old_st; u32 new_st; u32 dir_inv; } cb_data;
                        cb_data.old_st = old_state;
                        cb_data.new_st = new_state;
                        cb_data.dir_inv = direction ^ 1;
                        reinterpret_cast<void(*)(u64, void*)>(*(u64*)(*(u64*)obj + 0x20))(obj, &cb_data);
                    }
                    iter++;
                }

                // Update stage hide counter and activate if first time
                s32 hide_count = *(s32*)(stage_mgr + 0x168);
                *(s32*)(stage_mgr + 0x168) = hide_count + 1;

                if (hide_count == 0) {
                    u64 active_stage = *(u64*)(stage_mgr + 0x148);
                    *(u64*)(stage_mgr + 0x160) = active_stage;
                    if (active_stage != 0 && *(u8*)(active_stage + 0x3c5) == 0) {
                        *(u8*)(active_stage + 0x3c5) = 1;
                        reinterpret_cast<void(*)(void)>(*(u64*)(*(u64*)active_stage + 0x5c0))();
                    }
                }

                *(u8*)(slow + 0x448) = 1;
            }

            goto bg_consume;
        }
    }

    // Disable path: reset hiding if active
    {
        u64 slow = *(u64*)((u8*)DAT_71052b7710 + 8);
        if (*(u8*)(slow + 0x448) != 0) {
            FUN_710260ccd0((u64)lib::Singleton<app::StageManager>::instance_);
            *(u8*)(slow + 0x448) = 0;
        }
    }

bg_consume:
    acmd_consume(L);
}

// 0x7102297600 (4148 bytes) — FOOT_EFFECT
// Like FOOT_EFFECT_FLIP but without MotionModule flip check.
// Original inlines 16-arg reader (4148B); we call FUN_7102288620 (size mismatch expected).
// EffectModule vtable[0x3d0/8] = is_foot_enabled, terrain hash at +0x18
// FPA2 secondary effect when wrapper+0x194==0 and terrain hash==0xe3c234564
extern "C" void FOOT_EFFECT(lua_State* param_1) {
    u64 L = (u64)param_1;
    u64 wrapper = *(u64*)(L - 8);
    u64 acc = *(u64*)(wrapper + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.L = param_1;

    // Check EffectModule::is_foot_enabled (vtable[0x3d0/8])
    app::EffectModule* eff_check = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    u64 enabled = reinterpret_cast<u64(*)(void*)>(eff_check->_vt[0x3d0 / 8])(eff_check);
    if ((enabled & 1) == 0) goto foot_consume;

    {
        acmd_effect_out out;
        FUN_7102288620(&out, &ctrl, 0);

        // GroundModule::get_terrain_kind (vtable[0x478/8]) with arg 8
        void** ground = *(void***)(acc + 0x58);
        int terrain_kind = reinterpret_cast<int(*)(void*, int)>((*(void***)ground)[0x478 / 8])(ground, 8);

        if (terrain_kind != 0) {
            u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;
            u64 terrain_this = stage_mgr + 0x128;
            u64 terrain_data = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this + 0x1f8))(terrain_this, terrain_kind);

            u32 terrain_flag = (terrain_kind == 10 || terrain_kind == 0x2b) ? 0x4000000u : 0u;

            u64 terrain_hash = *(u64*)(terrain_data + 0x18);
            u64 th_masked = terrain_hash & 0xffffffffffULL;

            app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            if (th_masked == 0xe3c234564ULL || th_masked == 0x14a422ea56ULL || th_masked == 0x11b722b99fULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
                eff->preset_limit_num(param_val);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                terrain_hash = *(u64*)(terrain_data + 0x18);
            }

            f32 rate = *(f32*)&out.rate_bits;
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, terrain_hash, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, terrain_flag, 0, 0, rate);

            // Special case: FPA2 secondary effect
            if (*(u8*)(wrapper + 0x194) == 0 && (*(u64*)(terrain_data + 0x18) & 0xffffffffffULL) == 0xe3c234564ULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u64 param_base = *(u64*)(fpa2 + 0x50);
                u64 sec_pos_xy = *(u64*)(param_base + 0x1630);
                u64 sec_pos_z = (u64)*(u32*)(param_base + 0x1638);

                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

                // Check MotionModule motion kind for negate
                void** motion = *(void***)(acc + 0x88);
                u64 motion_kind = reinterpret_cast<u64(*)(void*)>((*(void***)motion)[0x138 / 8])(motion);
                u64 mk_masked = motion_kind & 0xffffffffffULL;

                // If certain motion kinds, negate x position
                struct { u64 xy; u64 z; } sec_pos;
                if (mk_masked == 0x7ff5db516ULL || mk_masked == 0xb1de0f39dULL ||
                    mk_masked == 0xbaee2f27aULL || mk_masked == 0xdae4249e4ULL) {
                    f32 neg_x = -*(f32*)&sec_pos_xy;
                    u32 neg_x_bits = *(u32*)&neg_x;
                    sec_pos.xy = (sec_pos_xy & 0xFFFFFFFF00000000ULL) | neg_x_bits;
                    sec_pos.z = sec_pos_z;
                } else {
                    sec_pos.xy = sec_pos_xy;
                    sec_pos.z = sec_pos_z;
                }

                u32 param_val2 = *(u32*)(param_base + 0x162c);
                eff->preset_limit_num(param_val2);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
                u64 sec_effect_hash = 0x14a422ea56ULL;
                reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                    (eff->_vt[0x70 / 8])(eff, sec_effect_hash, out.hash2, &sec_pos, &out.rot_xy, &out.scale_xy, &out.color_xy, false, terrain_flag, 0, 0, rate);
            }

            // Check terrain[0x10] flag
            if (*(u8*)(terrain_data + 0x10) == 0) {
                out.hash1 = 0x425cbfc4fULL;
            }
        }

        // Fallback req_on_joint if hash != sentinel
        if ((out.hash1 & 0xffffffffffULL) != 0x425cbfc4fULL) {
            app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            u64 h1_masked = out.hash1 & 0xffffffffffULL;
            if (h1_masked == 0xe3c234564ULL || h1_masked == 0x14a422ea56ULL || h1_masked == 0x11b722b99fULL) {
                u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
                u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
                eff->preset_limit_num(param_val);
                eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
            }
            f32 rate = *(f32*)&out.rate_bits;
            reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
                (eff->_vt[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);
        }
    }

foot_consume:
    acmd_consume(L);
}

// 0x7102296410 (3976 bytes) — EFFECT_FOLLOW_LIGHT
// 17-arg inline reader + req_follow (vtable[0x80/8]) + light setup (vtable[0x2d8/8])
// Args 1-2: hashes, 3-5: pos, 6-8: rot, 9: rate, 10: follow_flag (bool),
//       11-12: scale (x,y), 13-14: color (r,g), 15-16: color_b + extra, 17: extra_z
// PostureModule vtable[0xb0/8] → lr direction, multiplied with color_b
extern "C" void EFFECT_FOLLOW_LIGHT(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    f32 pos_x = 0, pos_y = 0, pos_z = 0;
    f32 rot_x = 0, rot_y = 0, rot_z = 0;
    f32 rate = 0;
    bool follow = false;
    f32 scale_x = 0, scale_y = 0;
    f32 color_r = 0, color_g = 0, color_b = 0;
    f32 extra = 0;
    u64 extra_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                pos_x = acmd_read_float(L, 0x30);
                if (nargs >= 4) {
                    pos_y = acmd_read_float(L, 0x40);
                    if (nargs >= 5) {
                        pos_z = acmd_read_float(L, 0x50);
                        if (nargs >= 6) {
                            rot_x = acmd_read_float(L, 0x60);
                            if (nargs >= 7) {
                                rot_y = acmd_read_float(L, 0x70);
                                if (nargs >= 8) {
                                    rot_z = acmd_read_float(L, 0x80);
                                    if (nargs >= 9) {
                                        rate = acmd_read_float(L, 0x90);
                                        if (nargs >= 10) {
                                            follow = acmd_read_bool(L, 0xa0);
                                            if (nargs >= 11) {
                                                scale_x = acmd_read_float(L, 0xb0);
                                                if (nargs >= 12) {
                                                    scale_y = acmd_read_float(L, 0xc0);
                                                    if (nargs >= 13) {
                                                        color_r = acmd_read_float(L, 0xd0);
                                                        if (nargs >= 14) {
                                                            color_g = acmd_read_float(L, 0xe0);
                                                            if (nargs >= 15) {
                                                                color_b = acmd_read_float(L, 0xf0);
                                                                if (nargs >= 16) {
                                                                    extra = acmd_read_float(L, 0x100);
                                                                    if (nargs >= 17) {
                                                                        f32 ez = acmd_read_float(L, 0x110);
                                                                        extra_z = (u64)(u32)ez;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Pack position and rotation vectors
    struct { f32 x; f32 y; u64 z; } pos_vec = { pos_x, pos_y, (u64)(u32)pos_z };
    struct { f32 x; f32 y; u64 z; } rot_vec = { rot_x, rot_y, (u64)(u32)rot_z };

    u64 flags = follow ? 0xc000ULL : 0x8000ULL;

    // EffectModule::req_follow (vtable[0x80/8]) → returns handle
    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &pos_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, rate);

    // PostureModule vtable[0xb0/8] → get LR direction (float)
    void** posture = *(void***)(acc + 0x38);
    f32 lr = reinterpret_cast<f32(*)(void*)>((*(void***)posture)[0xb0 / 8])(posture);

    // Pack light color vector: {color_b * lr, extra, extra_z}
    struct { f32 cb_lr; f32 ex; u64 ez; } light_vec;
    light_vec.cb_lr = color_b * lr;
    light_vec.ex = extra;
    light_vec.ez = extra_z;

    // EffectModule::set_light_params (vtable[0x2d8/8])
    // (eff, handle, &light_vec, scale_x, scale_y, color_r, color_g)
    reinterpret_cast<void(*)(void*, u32, void*, f32, f32, f32, f32)>
        (eff->_vt[0x2d8 / 8])(eff, handle, &light_vec, scale_x, scale_y, color_r, color_g);

    acmd_consume(L);
}

// 0x7102298fa0 (3996 bytes) — DOWN_EFFECT
// Like FOOT_EFFECT but no enable check, terrain uses +0x78 for secondary hash,
// +0x70 for flag check. No FPA2 secondary effect. Original inlines 16-arg reader.
extern "C" void DOWN_EFFECT(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);

    acmd_effect_ctrl ctrl;
    ctrl.hash = 0;
    ctrl.flag = 0;
    ctrl.nargs = (u32)((*(u64*)(L + 0x10) - (**(u64**)(L + 0x20) + 0x10)) >> 4);
    ctrl.L = param_1;

    acmd_effect_out out;
    FUN_7102288620(&out, &ctrl, 0);

    // GroundModule::get_terrain_kind (vtable[0x478/8]) with arg 8
    void** ground = *(void***)(acc + 0x58);
    app::EffectModule* eff_mod = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;
    int terrain_kind = reinterpret_cast<int(*)(void*, int)>((*(void***)ground)[0x478 / 8])(ground, 8);

    if (terrain_kind != 0) {
        u32 terrain_flag = (terrain_kind == 10 || terrain_kind == 0x2b) ? 0x4000000u : 0u;

        u64 stage_mgr = (u64)lib::Singleton<app::StageManager>::instance_;
        u64 terrain_this = stage_mgr + 0x128;
        u64 terrain_data = reinterpret_cast<u64(*)(u64, int)>(*(u64*)(*(u64*)terrain_this + 0x1f8))(terrain_this, terrain_kind);

        // Secondary hash from terrain_data+0x78 (different from FOOT/LANDING which use +0x18/+0x48)
        u64 terrain_hash = *(u64*)(terrain_data + 0x78);
        u64 th_masked = terrain_hash & 0xffffffffffULL;

        app::EffectModule* eff = eff_mod;
        if (th_masked == 0xe3c234564ULL || th_masked == 0x14a422ea56ULL || th_masked == 0x11b722b99fULL) {
            u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
            u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
            eff->preset_limit_num(param_val);
            terrain_hash = *(u64*)(terrain_data + 0x78);
        }

        f32 rate = *(f32*)&out.rate_bits;
        reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
            (eff_mod->_vt[0x70 / 8])(eff_mod, terrain_hash, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, terrain_flag, 0, 0, rate);

        // Check terrain[0x70] flag (DOWN uses +0x70, not +0x10 like LANDING/FOOT)
        if (*(u8*)(terrain_data + 0x70) == 0) goto down_consume;
    }

    // Fallback req_on_joint if hash != sentinel
    if ((out.hash1 & 0xffffffffffULL) != 0x425cbfc4fULL) {
        u64 h1_masked = out.hash1 & 0xffffffffffULL;
        if (h1_masked == 0xe3c234564ULL || h1_masked == 0x14a422ea56ULL || h1_masked == 0x11b722b99fULL) {
            u64 fpa2 = (u64)lib::Singleton<app::FighterParamAccessor2>::instance_;
            u32 param_val = *(u32*)(*(u64*)(fpa2 + 0x50) + 0x162c);
            eff_mod->preset_limit_num(param_val);
        }
        f32 rate = *(f32*)&out.rate_bits;
        reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u32, u32, s32, f32)>
            (eff_mod->_vt[0x70 / 8])(eff_mod, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);
    }

down_consume:
    acmd_consume(L);
}

// 0x710229c430 (2116 bytes) — EFFECT_FOLLOW_arg12
// Like EFFECT_FOLLOW_arg11 but with arg12=joint_kind (indexes function pointer table).
// arg12 is bounded 0-8 (abort if >= 9). Calls PTR_FUN_7104f68c38[joint_kind](acc)
// to resolve joint id, which replaces the hardcoded -1 in EFFECT_FOLLOW_arg11.
// Flags: follow=0xc000, default=0x8000.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_arg12(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1 = 0, hash2 = 0;
    u64 off_x = 0, off_y = 0, off_z = 0;

    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        if (nargs >= 2) {
            hash2 = FUN_71038f4000(param_1, 2, 0);
            if (nargs >= 3) {
                f32 f3 = acmd_read_float(L, 0x30);
                off_x = (u64)(u32)f3;
                if (nargs >= 4) {
                    f32 f4 = acmd_read_float(L, 0x40);
                    off_y = (u64)(u32)f4;
                    if (nargs >= 5) {
                        f32 f5 = acmd_read_float(L, 0x50);
                        off_z = (u64)(u32)f5;
                    }
                }
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } off_vec = { (u32)off_y, (u32)off_x, off_z };

    u64 rot_x = 0, rot_y = 0, rot_z = 0;
    if (nargs >= 6) {
        f32 f6 = acmd_read_float(L, 0x60);
        rot_x = (u64)(u32)f6;
        if (nargs >= 7) {
            f32 f7 = acmd_read_float(L, 0x70);
            rot_y = (u64)(u32)f7;
            if (nargs >= 8) {
                f32 f8 = acmd_read_float(L, 0x80);
                rot_z = (u64)(u32)f8;
            }
        }
    }

    struct { u32 y; u32 x; u64 z; } rot_vec = { (u32)rot_y, (u32)rot_x, rot_z };

    f32 rate_f = 0;
    if (nargs >= 9) {
        rate_f = acmd_read_float(L, 0x90);
    }

    bool follow_flag = false;
    if (nargs >= 10) {
        follow_flag = acmd_read_bool(L, 0xa0);
    }

    u64 flags = follow_flag ? 0xc000ULL : 0x8000ULL;

    u64 alt_hash = 0;
    u32 joint_kind = 0;
    if (nargs >= 11) {
        alt_hash = FUN_71038f4000(param_1, 0xb, 0);
        if (nargs >= 12) {
            joint_kind = (u32)FUN_71038f4000(param_1, 0xc, 0);
            if (joint_kind >= 9) {
                abort();
            }
        }
    }

    // Resolve joint via function pointer table
    // PTR_FUN_7104f68c38[joint_kind](acc) → returns joint id
    u32 joint_result = reinterpret_cast<u32(*)(u64)>(PTR_FUN_7104f68c38[joint_kind])(acc);

    app::EffectModule* eff = reinterpret_cast<app::BattleObjectModuleAccessor*>(acc)->effect_module;

    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (eff->_vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, alt_hash, (s32)joint_result, 0, 0, 0, 0, rate_f);

    acmd_consume(L);
}

}} // namespace app::sv_animcmd
