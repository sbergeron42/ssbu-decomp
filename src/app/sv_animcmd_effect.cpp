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

}} // namespace app::sv_animcmd
