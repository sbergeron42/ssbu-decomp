#include "types.h"

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
extern "C" void FUN_710228ea70(u64, u64, u64, void*, s32);
extern "C" void FUN_7102288620(void*, void*, u64);
extern "C" u64 ConstantZero HIDDEN;  // PTR_ConstantZero_71052a7a88

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
void EFFECT_GLOBAL(lua_State* param_1) {
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
void EFFECT_OFF(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, bool, s32)>(vt[0xf0 / 8])(eff, hash, flag, 1);

    acmd_consume(L);
}

// 0x710228be60 — EFFECT_WORK
// Args: 1=effect_hash, 2=bone_hash, 3-4=pos_xy, 5=joint_id, 6-7=rot_xy,
//       8=rate, 9=rot_z, 10-11=scale_xy, 12=scale_z, 13-14=extra_xy,
//       15=extra_z, 16=bool_flag
// Calls EffectModule::req_on_joint (vtable slot 14, offset 0x70)
void EFFECT_WORK(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_extra, a16, 0, 0, 0, a8);

    acmd_consume(L);
}

// 0x710228cc90 — EFFECT_VARIATION
// Like EFFECT_WORK but calls get_variation_effect_kind first, then optionally set_offset_to_next
// Args: same as EFFECT_WORK (1-16), plus optional arg 17 for offset hash
void EFFECT_VARIATION(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u64 kind = reinterpret_cast<u64(*)(void*, u64, s32)>((*(void***)eff)[0x2c0 / 8])(eff, hash1, -1);

    // If nargs > 16: check if variation changed, and if not, apply offset
    if (nargs > 16) {
        u64 kind0 = reinterpret_cast<u64(*)(void*, u64, s32)>((*(void***)eff)[0x2c0 / 8])(eff, hash1, 0);
        if (((kind0 ^ kind) & 0xFFFFFFFFFFULL) == 0) {
            u64 offset_hash = FUN_71038f4000(param_1, 0x11, 0);
            reinterpret_cast<void(*)(void*, u64)>((*(void***)eff)[0x418 / 8])(eff, offset_hash);
        }
    }

    // EffectModule::req_on_joint (vtable[14], offset 0x70)
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, s32, s32, s32, f32)>
        (vt[0x70 / 8])(eff, kind, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_extra, a16, 0, 0, 0, a8);

    acmd_consume(L);
}

// 0x710229cc80 (520 bytes) — EFFECT_OFF_KIND
// Args: 1=effect_hash, 2=is_trail(bool), 3=reset_flag(bool)
// Calls EffectModule::kill_kind (vtable slot 28, offset 0xE0)
void EFFECT_OFF_KIND(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, bool, bool)>(vt[0xe0 / 8])(eff, hash, flag1, flag2);

    acmd_consume(L);
}

// 0x71022907c0 — EFFECT_FOLLOW
// Args: 1=effect_hash, 2=bone_hash, 3-5=offset(int xyz), 6-8=rot(int xyz),
//       9=scale(int), 10=follow_flag(bool)
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x7102292910 (180 bytes) — EFFECT_REMOVE_ATTR
// Args: 1=effect_hash
// Calls EffectModule::remove_attr (vtable slot 26, offset 0xD0)
void EFFECT_REMOVE_ATTR(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, s32)>(vt[0xd0 / 8])(eff, hash, 0);

    acmd_consume(L);
}

// 0x710229ce90 (520 bytes) — EFFECT_OFF_KIND_WORK
// Args: 1=effect_hash, 2=is_trail(bool), 3=reset_flag(bool)
// Like EFFECT_OFF_KIND but with null check at start (WORK variant)
// Calls EffectModule::kill_kind (vtable slot 28, offset 0xE0)
void EFFECT_OFF_KIND_WORK(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, bool, bool)>(vt[0xe0 / 8])(eff, hash, flag1, flag2);

    acmd_consume(L);
}

// 0x7102290f90 (2016 bytes) — EFFECT_FOLLOW_WORK
// Like EFFECT_FOLLOW but calls FUN_71038f4000(L,1,0) as side effect first,
// then again at end to get actual hash. Offsets nested inside arg2 block,
// rotations at top level.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_WORK(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x7102291770 (2132 bytes) — EFFECT_FOLLOW_VARIATION
// Like EFFECT_FOLLOW_WORK + variation resolution via get_variation_effect_kind.
// Arg 9 is scale as FLOAT (not int). Up to 11 args.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_VARIATION(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u64 hash1;
    if (nargs >= 1) {
        hash1 = FUN_71038f4000(param_1, 1, 0);
    } else {
        hash1 = 0;
    }

    // Variation resolution: get_variation_effect_kind (vtable[0x2c0])
    u64 var_kind = reinterpret_cast<u64(*)(void*, u64, s32)>((*(void***)eff)[0x2c0 / 8])(eff, hash1, -1);

    u64 alt_hash;
    if (nargs >= 11) {
        // Re-read eff module and hash1 for second variation check
        void** eff2 = *(void***)(acc + 0x140);
        u64 hash1_again = FUN_71038f4000(param_1, 1, 0);
        u64 var_kind0 = reinterpret_cast<u64(*)(void*, u64, s32)>((*(void***)eff2)[0x2c0 / 8])(eff2, hash1_again, 0);
        if (((var_kind0 ^ var_kind) & 0xFFFFFFFFFFULL) == 0) {
            alt_hash = FUN_71038f4000(param_1, 0xb, 0);
        } else {
            alt_hash = 0;
        }
    } else {
        alt_hash = 0;
    }

    // EffectModule::req_follow (vtable[16], offset 0x80)
    void** eff3 = *(void***)(acc + 0x140);
    void** vt = *(void***)eff3;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff3, var_kind, hash2, &off_vec, &rot_vec, 0, flags, alt_hash, (s32)-1, 0, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710228db30 (3716 bytes) — EFFECT_ATTR
// Args: 1=hash1, 2=hash2, 3-4=pos(float), 5=pos_z(int), 6-8=rot(float),
//       9=rate(float), 10-12=scale(float), 13-15=color(float), 16=bool, 17=attr_hash
// Calls EffectModule::req_on_joint with attr (vtable slot 14, offset 0x70)
void EFFECT_ATTR(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, s32, s32, f32)>
        (vt[0x70 / 8])(eff, hash1, hash2, &vec_pos, &vec_rot, &vec_scale, &vec_color, a16, attr_hash, 0, 0, a9);

    acmd_consume(L);
}

// 0x71022a7f50 (180 bytes) — EFFECT_OFF_HANDLE
// Args: 1=handle_hash
// Calls EffectModule::kill_handle (vtable offset 0xC8)
void EFFECT_OFF_HANDLE(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, s32)>(vt[0xc8 / 8])(eff, hash, 0);

    acmd_consume(L);
}

// 0x71022a5780 (224 bytes) — EFFECT_DETACH_KIND
// Args: 1=effect_hash, 2=group_hash
// Calls EffectModule::detach_kind (vtable offset 0x100)
void EFFECT_DETACH_KIND(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1, hash2;
    void** eff;

    if (nargs < 1) {
        eff = *(void***)(acc + 0x140);
        hash1 = 0;
        hash2 = 0;
    } else {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        eff = *(void***)(acc + 0x140);
        if (nargs < 2) {
            hash2 = 0;
        } else {
            hash2 = FUN_71038f4000(param_1, 2, 0);
        }
    }

    reinterpret_cast<void(*)(void*, u64, u64)>((*(void***)eff)[0x100 / 8])(eff, hash1, hash2);

    acmd_consume(L);
}

// 0x71022a5860 (224 bytes) — EFFECT_DETACH_KIND_WORK
// Args: 1=effect_hash, 2=group_hash
// Identical to EFFECT_DETACH_KIND (vtable offset 0x100)
void EFFECT_DETACH_KIND_WORK(lua_State* param_1) {
    u64 L = (u64)param_1;
    if (param_1 == nullptr) {
#ifdef MATCHING_HACK_NX_CLANG
        __builtin_trap();
#endif
    }
    u64 acc = *(u64*)(*(u64*)(L - 8) + 0x1a0);
    int nargs = acmd_nargs(L);

    u64 hash1, hash2;
    void** eff;

    if (nargs < 1) {
        eff = *(void***)(acc + 0x140);
        hash1 = 0;
        hash2 = 0;
    } else {
        hash1 = FUN_71038f4000(param_1, 1, 0);
        eff = *(void***)(acc + 0x140);
        if (nargs < 2) {
            hash2 = 0;
        } else {
            hash2 = FUN_71038f4000(param_1, 2, 0);
        }
    }

    reinterpret_cast<void(*)(void*, u64, u64)>((*(void***)eff)[0x100 / 8])(eff, hash1, hash2);

    acmd_consume(L);
}

// 0x7102297520 (224 bytes) — EFFECT_LIGHT_END
// Args: 1=light_hash(u32), 2=group_hash
// Calls EffectModule::end_light (vtable offset 0x2E0)
void EFFECT_LIGHT_END(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64)>(vt[0x2e0 / 8])(eff, hash1, hash2);

    acmd_consume(L);
}

// 0x71022a49a0 (340 bytes) — LAST_EFFECT_SET_RATE
// Args: 1=rate(float)
// Calls EffectModule::set_rate (vtable offset 0x338)
void LAST_EFFECT_SET_RATE(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, f32)>(vt[0x338 / 8])(eff, rate);

    acmd_consume(L);
}

// 0x71022a4b00 (340 bytes) — LAST_EFFECT_SET_RATE_WORK
// Identical to LAST_EFFECT_SET_RATE (vtable offset 0x338)
void LAST_EFFECT_SET_RATE_WORK(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, f32)>(vt[0x338 / 8])(eff, rate);

    acmd_consume(L);
}

// 0x71022a52c0 (340 bytes) — LAST_EFFECT_SET_ALPHA
// Args: 1=alpha(float)
// Calls EffectModule::set_alpha (vtable offset 0x348)
void LAST_EFFECT_SET_ALPHA(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, f32)>(vt[0x348 / 8])(eff, alpha);

    acmd_consume(L);
}

// 0x71022a5420 (284 bytes) — LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW
// Args: 1=disable(bool)
// Calls EffectModule::set_disable_system_slow (vtable offset 0x350)
void LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, bool)>(vt[0x350 / 8])(eff, flag);

    acmd_consume(L);
}

// 0x71022a56a0 (212 bytes) — LAST_EFFECT_SET_WORK_INT
// Args: 1=work_var_hash
// Gets last effect handle from EffectModule vtable[0x3A0], then
// sets work int via WorkModule vtable[0xA0]
void LAST_EFFECT_SET_WORK_INT(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u64 handle = reinterpret_cast<u64(*)(void*)>((*(void***)eff)[0x3a0 / 8])(eff);

    // WorkModule::set_int (vtable[0xA0])
    reinterpret_cast<void(*)(void*, u64, u64)>((*(void***)work)[0xa0 / 8])(work, handle, hash);

    acmd_consume(L);
}

// 0x71022a4c60 (804 bytes) — LAST_EFFECT_SET_SCALE_W
// Args: 1-3 = scale xyz (float→int)
// Packs into vec3 struct, calls EffectModule::set_scale (vtable offset 0x340)
void LAST_EFFECT_SET_SCALE_W(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, void*)>(vt[0x340 / 8])(eff, &scale_vec);

    acmd_consume(L);
}

// 0x71022a4f90 (804 bytes) — LAST_EFFECT_SET_COLOR
// Args: 1-3 = RGB color (float)
// Gets last handle via vtable[0x3A0], then sets color via vtable[0x2F8]
void LAST_EFFECT_SET_COLOR(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    u64 handle = reinterpret_cast<u64(*)(void*)>(vt[0x3a0 / 8])(eff);
    reinterpret_cast<void(*)(void*, u64, f32, f32, f32)>(vt[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x7102299f40 (2004 bytes) — EFFECT_FOLLOW_NO_STOP
// Like EFFECT_FOLLOW but reads hashes in nested block, offsets nested,
// rotations top-level. Flags: follow=0x4000, default=0.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_NO_STOP(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, alt_hash, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x00000071022a5c50 (1996 bytes) — EFFECT_FOLLOW_NO_SCALE
// Like EFFECT_FOLLOW but passes 1 as the no_scale flag (13th arg).
// Flags: follow=0xc000, default=0x8000.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_NO_SCALE(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    // Note: 13th arg is 1 (no_scale flag), not 0
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 1, scale_f);

    acmd_consume(L);
}

// 0x7102291fd0 (2004 bytes) — EFFECT_FOLLOW_UNSYNC_VIS_WHOLE
// Like EFFECT_FOLLOW_NO_STOP but flags: follow=0x40c000, default=0x408000.
// The 0x40xxxx prefix marks unsync vis mode.
// Calls EffectModule::req_follow (vtable slot 16, offset 0x80)
void EFFECT_FOLLOW_UNSYNC_VIS_WHOLE(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x71022929d0 (2052 bytes) — EFFECT_FLW_POS
// Args: 1=hash1, 2=hash2, 3-4=offset_xy(float), 5=offset_z(float→int),
//       6-7=rot_xy(float), 8=rot_z(float→int), 9=scale(float), 10=follow_flag(bool)
// Like EFFECT_FOLLOW but keeps offset/rot x,y as raw floats (position-based)
// Calls EffectModule::req_follow (vtable offset 0x80) with pos_mode=1
void EFFECT_FLW_POS(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022931e0 (2048 bytes) — EFFECT_FLW_POS_NO_STOP
// Same as EFFECT_FLW_POS but flags: follow=0x4000, default=0
void EFFECT_FLW_POS_NO_STOP(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022939e0 (2056 bytes) — EFFECT_FLW_POS_UNSYNC_VIS
// Same as EFFECT_FLW_POS but flags: follow=0x40c000, default=0x408000
void EFFECT_FLW_POS_UNSYNC_VIS(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 1, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022941f0 (2056 bytes) — EFFECT_FLW_UNSYNC_VIS
// Same as EFFECT_FLW_POS_UNSYNC_VIS but pos_mode=0 instead of 1
void EFFECT_FLW_UNSYNC_VIS(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x71022a5540 (352 bytes) — LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT
// Checks BattleObjectWorld singleton; if invalid, skip.
// Args: 1=offset(float)
// Calls EffectModule::set_offset_to_camera_flat (vtable offset 0x370)
void LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT(lua_State* param_1) {
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

        void** eff = *(void***)(acc + 0x140);
        void** vt = *(void***)eff;
        reinterpret_cast<void(*)(void*, f32)>(vt[0x370 / 8])(eff, offset);
    }

    acmd_consume(L);
}

// 0x71022a5940 (780 bytes) — LAST_PARTICLE_SET_COLOR
// Args: 1-3 = RGB color (float)
// Calls EffectModule::set_particle_color (vtable offset 0x300)
void LAST_PARTICLE_SET_COLOR(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, f32, f32, f32)>(vt[0x300 / 8])(eff, r, g, b);

    acmd_consume(L);
}

// 0x710229a720 (2620 bytes) — EFFECT_FOLLOW_COLOR
// Like EFFECT_FOLLOW but returns handle from req_follow, then reads 3 extra float
// args (11-13) for RGB and calls set_color (vtable offset 0x2F8)
void EFFECT_FOLLOW_COLOR(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        ((*(void***)eff)[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale_f);

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
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>((*(void***)eff)[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d9e0 (2196 bytes) — EFFECT_FOLLOW_ALPHA
// Like EFFECT_FOLLOW but returns handle from req_follow, then reads 1 extra float
// arg (11) for alpha and calls set_alpha_last (vtable offset 0x308)
void EFFECT_FOLLOW_ALPHA(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, s32, s32, s32, s32, f32)>
        ((*(void***)eff)[0x80 / 8])(eff, hash1, hash2, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, 0, 0, 0, 0, scale_f);

    // Read alpha: arg 11 (offset 0xb0)
    f32 alpha = 0.0f;
    if (nargs >= 11) {
        alpha = acmd_read_float(L, 0xb0);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32)>((*(void***)eff)[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x7102294a00 (2336 bytes) — EFFECT_FOLLOW_FLIP
// Like EFFECT_FOLLOW but checks MotionModule flip state and swaps hash args.
// Args: 1=hash_nf, 2=hash_flip, 3=bone_hash, 4-5=off_xy(float), 6=off_z(int),
//       7-8=rot_xy(float), 9=rot_z(int), 10=scale(float), 11=follow_flag(bool),
//       12=alt_hash(when flipped)
// Calls MotionModule vtable[0x390/8] for flip check, then req_follow (vtable 0x80)
void EFFECT_FOLLOW_FLIP(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale);

    acmd_consume(L);
}

// 0x7102295bb0 (2144 bytes) — EFFECT_FOLLOW_NO_STOP_FLIP
// Like EFFECT_FOLLOW_FLIP but NO_STOP flags (follow=0x4000, default=0).
// Args: 1=hash_nf(discarded initially), 2=hash_flip, 3=bone_hash,
//       4-6=off_xyz(int), 7-9=rot_xyz(int), 10=scale(float),
//       11=follow_flag(bool), 12=alt_hash(when flipped)
void EFFECT_FOLLOW_NO_STOP_FLIP(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710229b160 (2752 bytes) — EFFECT_FOLLOW_FLIP_COLOR
// Combines FOLLOW_FLIP (motion flip + hash swap) with COLOR (3 RGB float args after req_follow).
// Args: 1=hash_nf, 2=hash_flip, 3=bone_hash, 4-6=off_xyz(int), 7-9=rot_xyz(int),
//       10=scale(float), 11=follow_flag(bool), 12=alt_hash(when flipped),
//       13-15=RGB(float)
void EFFECT_FOLLOW_FLIP_COLOR(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        ((*(void***)eff)[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

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
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>((*(void***)eff)[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x71022a1100 (2328 bytes) — EFFECT_FOLLOW_FLIP_ALPHA
// Combines FOLLOW_FLIP (motion flip + hash swap) with ALPHA (1 float arg after req_follow).
// Same arg layout as EFFECT_FOLLOW_FLIP_COLOR but arg 13=alpha, calls vtable 0x308
void EFFECT_FOLLOW_FLIP_ALPHA(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        ((*(void***)eff)[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, 0, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    // Read alpha: arg 13 (offset 0xd0)
    f32 alpha = 0.0f;
    if (nargs >= 13) {
        alpha = acmd_read_float(L, 0xd0);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32)>((*(void***)eff)[0x308 / 8])(eff, handle, alpha);

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
    void** eff = *(void***)(acc + 0x140);
    void** vt = *(void***)eff;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, u64, u64, u64, s32, u64, s32, s32, s32, f32)>
        (vt[0x80 / 8])(eff, effect_hash, bone_hash, &off_vec, &rot_vec, 0, flags, joint_hash, (s32)-1, alt_hash, 0, 0, 0, scale_f);

    acmd_consume(L);
}

// 0x710229d0a0 (932 bytes) — EFFECT_COLOR
// Parses 16 EFFECT args via FUN_7102288620, calls req_on_joint, then reads 3 extra
// float args (17-19) for RGB and calls set_color (vtable offset 0x2F8)
void EFFECT_COLOR(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        ((*(void***)eff)[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    // Read RGB: args 17-19 (offsets 0x110, 0x120, 0x130)
    f32 r = 0, g = 0, b = 0;
    eff = *(void***)(acc + 0x140);

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
    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>((*(void***)eff)[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d450 (932 bytes) — EFFECT_COLOR_WORK
// Identical to EFFECT_COLOR
void EFFECT_COLOR_WORK(lua_State* param_1) {
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

    void** eff = *(void***)(acc + 0x140);
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        ((*(void***)eff)[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    f32 r = 0, g = 0, b = 0;
    eff = *(void***)(acc + 0x140);

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

    reinterpret_cast<void(*)(void*, u32, f32, f32, f32)>((*(void***)eff)[0x2f8 / 8])(eff, handle, r, g, b);

    acmd_consume(L);
}

// 0x710229d800 (476 bytes) — EFFECT_ALPHA
// Parses 16 EFFECT args via FUN_7102288620, calls req_on_joint, then reads 1 extra
// float arg (17) for alpha and calls set_alpha_last (vtable offset 0x308)
void EFFECT_ALPHA(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        ((*(void***)eff)[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, 0, 0, rate);

    // Read alpha: arg 17 (offset 0x110)
    f32 alpha = 0.0f;

    if (param_1 == nullptr) {
        // null path — dead code
    } else if (nargs >= 17) {
        alpha = acmd_read_float(L, 0x110);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32)>((*(void***)eff)[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

// 0x71022973a0 (380 bytes) — EFFECT_FLIP
// Calls FUN_7102288620 in flip mode (mode=1), checks MotionModule flip state,
// swaps hash arg, then calls req_on_joint (vtable 0x70)
void EFFECT_FLIP(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    f32 rate = *(f32*)&out.rate_bits;
    reinterpret_cast<void(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        ((*(void***)eff)[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);

    acmd_consume(L);
}

// 0x71022a0ea0 (596 bytes) — EFFECT_FLIP_ALPHA
// Like EFFECT_FLIP but reads alpha at arg 19 (offset 0x130) and calls set_alpha_last
void EFFECT_FLIP_ALPHA(lua_State* param_1) {
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
    void** eff = *(void***)(acc + 0x140);
    f32 rate = *(f32*)&out.rate_bits;
    u32 handle = reinterpret_cast<u32(*)(void*, u64, u64, void*, void*, void*, void*, bool, u64, u64, s32, f32)>
        ((*(void***)eff)[0x70 / 8])(eff, out.hash1, out.hash2, &out.pos_xy, &out.rot_xy, &out.scale_xy, &out.color_xy, out.follow_flag, 0, alt_hash, 0, rate);

    // Read alpha: arg 19 (offset 0x130, since flip mode shifts by 1)
    f32 alpha = 0.0f;
    if (nargs >= 19) {
        alpha = acmd_read_float(L, 0x130);
    }

    // EffectModule::set_alpha_last (vtable offset 0x308)
    eff = *(void***)(acc + 0x140);
    reinterpret_cast<void(*)(void*, u32, f32)>((*(void***)eff)[0x308 / 8])(eff, handle, alpha);

    acmd_consume(L);
}

}} // namespace app::sv_animcmd
