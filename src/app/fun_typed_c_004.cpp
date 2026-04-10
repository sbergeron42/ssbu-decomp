#include "types.h"

// L2C dispatch + small functions for Search/Reflect/Reflector modules

extern "C" u64 l2cParamResolve_71038f4000(u64, int, int);
extern "C" u64 FUN_7103907950(u64, u64*);
extern u32 DAT_7104861960[];

// ============================================================
// Small matchable functions
// ============================================================

// 0x71015c55a0 (28 bytes) — get_pre_explosion_search_object_id
// Pointer chain: *(L-8)+0x1A0 → +0x190 → +0x220 → +0x90 → +0x60 (u32)
u32 FUN_71015c55a0(u64 L) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    u64 e = *(u64*)(d + 0x90);
    return *(u32*)(e + 0x60);
}

// 0x71015c5c40 (16 bytes) — search_range
// Tail-calls FUN_71015c5c50(L, 5, bool_arg & 1, 1), floats pass through
extern "C" void FUN_71015c5c50(void*, int, int, int);
void FUN_71015c5c40(void* L, float, float, float, float, bool p6) {
    FUN_71015c5c50(L, 5, p6, 1);
}

// 0x71015c6850 (16 bytes) — search_range_ignore_lr
// Tail-calls FUN_71015c5c50(L, 5, 0, 0), floats pass through
void FUN_71015c6850(void* L, float, float, float, float) {
    FUN_71015c5c50(L, 5, 0, 0);
}

// 0x71015c3060 (8 bytes) — get_assist_respawn_position
// Tail-calls FUN_710160e690(param_1, param_2, 1)
extern "C" void FUN_710160e690(void*, int, int);
void FUN_71015c3060(void* p1, int p2) {
    FUN_710160e690(p1, p2, 1);
}

// 0x71015bfa40 (28 bytes) — set_life_type
// Same chain as get_pre_explosion_search_object_id but stores w1 at +0x118
void FUN_71015bfa40(u64 L, u32 val) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    u64 e = *(u64*)(d + 0x90);
    *(u32*)(e + 0x118) = val;
}

// 0x71015c1dd0 (24 bytes) — variation
// Pointer chain: *(L-8)+0x1A0 → +0x190 → +0x220 → +0x258 (u32)
u32 FUN_71015c1dd0(u64 L) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    return *(u32*)(d + 0x258);
}

// 0x71015c2a70 (28 bytes) — is_force_flashing
// Pointer chain: *(L-8)+0x1A0 → +0x190 → +0x220 → +0x90 → +0x152 (u8)
u32 FUN_71015c2a70(u64 L) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    u64 e = *(u64*)(d + 0x90);
    return *(u8*)(e + 0x152);
}

// 0x71015c1fc0 (28 bytes) — set_effect_sync_visibility_default
// Pointer chain + bool store at +0x29B
void FUN_71015c1fc0(u64 L, u32 val) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    *(u8*)(d + 0x29B) = (u8)(val & 1);
}

// 0x71015c2060 (28 bytes) — enable_lost_flashing
// Pointer chain + bool store at +0x29F
void FUN_71015c2060(u64 L, u32 val) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    *(u8*)(d + 0x29F) = (u8)(val & 1);
}

// 0x71015c2750 (24 bytes) — set_throw_power_speed_mul
// Pointer chain + float store at +0x294
void FUN_71015c2750(u64 L, float val) {
    u64 a = *(u64*)(L - 8);
    u64 b = *(u64*)(a + 0x1A0);
    u64 c = *(u64*)(b + 0x190);
    u64 d = *(u64*)(c + 0x220);
    *(float*)(d + 0x294) = val;
}

// 0x71015c8ed0 (8 bytes) — create_weapon
// Tail-calls FUN_71015c8ee0(p1, p2, -1)
extern "C" void FUN_71015c8ee0(void*, void*, u32);
void FUN_71015c8ed0(void* p1, void* p2) {
    FUN_71015c8ee0(p1, p2, 0xFFFFFFFF);
}

// 0x71015ce860 (8 bytes) — item_generate_position_nearest
// Tail-calls FUN_710160e690(p1, p2, 0)
void FUN_71015ce860(void* p1, int p2) {
    FUN_710160e690(p1, p2, 0);
}

// 0x71015cf3c0 (4 bytes) — get_module_accessor
// Pure forwarding tail call to FUN_710160e2a0
extern "C" void* FUN_710160e2a0(void*);
void* FUN_71015cf3c0(void* p) {
    return FUN_710160e2a0(p);
}

// 0x71016459c0 (4 bytes) — revert_camera
// Pure forwarding tail call to FUN_710160dea0
extern "C" void FUN_710160dea0(void*);
void FUN_71016459c0(void* p) {
    FUN_710160dea0(p);
}

// 0x710164c450 (4 bytes) — revert_camera (variant)
// Same target as above
void FUN_710164c450(void* p) {
    FUN_710160dea0(p);
}

// 0x71015cbc30 (16 bytes) — is_pickel_block
// Returns (p != null) ? (*(u8*)(p + 0xC7) & 1) : 0
u64 FUN_71015cbc30(u64 p) {
    if (!p) return 0;
    u64 val = *(u8*)(p + 0xC7);
    return val & 1;
}

// 0x71015cbe00 (12 bytes) — get_material_type
// Returns (p != null) ? *(u32*)(p + 0xD0) : 0
u64 FUN_71015cbe00(u64 p) {
    if (!p) return 0;
    return *(u32*)(p + 0xD0);
}

// ============================================================
// Pattern B: l2cParamResolve_71038f4000 arg extract + optional redirect + float return
// Module at *(acc+0xF0), redirect at *(obj+0x110)
// ============================================================

// 0x710207bbe0 (544 bytes) — internal dispatch, vtable[0x1A0], float return
u64 FUN_710207bbe0(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xF0);
    if (!mod) return 0;

    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    s64 diff = (s64)(top - base);
    s32 argc = (s32)((u64)diff >> 4);
    u64 arg1;

    if (argc >= 1) {
        arg1 = l2cParamResolve_71038f4000(L, 1, 0);
        if (argc != 1) goto resolve;
        top = *(u64*)(L + 0x10);
        goto adjust;
    }
    if (argc < 0) goto fill;
    arg1 = 0;
    goto adjust;

fill: {
        u64 target = base + (s64)((diff << 28) ^ (u64)(-0x100000000LL)) >> 28;
        while (top < target) {
            *(u64*)(L + 0x10) = top + 0x10;
            *(u32*)(top + 8) = 0;
            top = *(u64*)(L + 0x10);
        }
        arg1 = 0;
        goto call_site;
    }

resolve: {
        u64 base2 = **(u64**)(L + 0x20) + 0x20;
        top = *(u64*)(L + 0x10);
        u32* slot = (base2 < top) ? (u32*)base2 : DAT_7104861960;
        u32 tag = slot[2] & 0xF;
        u64 obj;
        if (tag == 2) {
            obj = *(u64*)slot;
        } else if (tag == 7) {
            obj = *(u64*)slot + 0x28;
        } else {
            obj = 0;
        }
        mod = *(u64*)(obj + 0x110);
    }

adjust:
    top = top + ((u64)(-(s64)diff << 28) >> 28);

call_site:
    *(u64*)(L + 0x10) = top;
    float r = (**(float(**)(u64, u64))(*(u64*)mod + 0x1A0))(mod, arg1);
    u32* s = *(u32**)(L + 0x10);
    *(float*)s = r;
    s[2] = 3;
    *(u64*)(L + 0x10) = *(u64*)(L + 0x10) + 0x10;
    return 1;
}

// 0x710207be00 (1344 bytes) — internal dispatch, vtable[0x1B0], float return
u64 FUN_710207be00(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xF0);
    if (!mod) return 0;

    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    s64 diff = (s64)(top - base);
    s32 argc = (s32)((u64)diff >> 4);
    u64 arg1;

    if (argc >= 1) {
        arg1 = l2cParamResolve_71038f4000(L, 1, 0);
        if (argc != 1) goto resolve;
        top = *(u64*)(L + 0x10);
        goto adjust;
    }
    if (argc < 0) goto fill;
    arg1 = 0;
    goto adjust;

fill: {
        u64 target = base + (s64)((diff << 28) ^ (u64)(-0x100000000LL)) >> 28;
        while (top < target) {
            *(u64*)(L + 0x10) = top + 0x10;
            *(u32*)(top + 8) = 0;
            top = *(u64*)(L + 0x10);
        }
        arg1 = 0;
        goto call_site;
    }

resolve: {
        u64 base2 = **(u64**)(L + 0x20) + 0x20;
        top = *(u64*)(L + 0x10);
        u32* slot = (base2 < top) ? (u32*)base2 : DAT_7104861960;
        u32 tag = slot[2] & 0xF;
        u64 obj;
        if (tag == 2) {
            obj = *(u64*)slot;
        } else if (tag == 7) {
            obj = *(u64*)slot + 0x28;
        } else {
            obj = 0;
        }
        mod = *(u64*)(obj + 0x110);
    }

adjust:
    top = top + ((u64)(-(s64)diff << 28) >> 28);

call_site:
    *(u64*)(L + 0x10) = top;
    float r = (**(float(**)(u64, u64))(*(u64*)mod + 0x1B0))(mod, arg1);
    u32* s = *(u32**)(L + 0x10);
    *(float*)s = r;
    s[2] = 3;
    *(u64*)(L + 0x10) = *(u64*)(L + 0x10) + 0x10;
    return 1;
}

// ============================================================
// Pattern A: Inline L2CValue float extraction + redirect + void vtable call
// ============================================================

// 0x710206de70 (592 bytes) — ReflectModule set_attack_mul
// Module: *(acc+0x18), Redirect: *(obj+0x38), Vtable: 0x130
u64 FUN_710206de70(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x18);
    if (!mod) return 0;

    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    u32* arg0 = (base < top) ? (u32*)base : DAT_7104861960;
    s64 diff = (s64)(top - base);
    u32 tag = arg0[2];
    s32 argc = (s32)((u64)diff >> 4);
    float val;

    if (tag == 3) {
        val = *(float*)arg0;
    got_float:
        if (argc >= 2) goto resolve2;
    check_sign:
        if (argc < 0) {
            u64 target = **(u64**)(L + 0x20) + (s64)((diff << 28) ^ (u64)(-0x100000000LL)) / (1 << 28) + 0x10;
            u64 sp = *(u64*)(L + 0x10);
            while (sp < target) {
                *(u64*)(L + 0x10) = sp + 0x10;
                *(u32*)(sp + 8) = 0;
                sp = *(u64*)(L + 0x10);
            }
            goto call_site;
        }
        top = *(u64*)(L + 0x10);
        goto do_adjust;
    } else if (tag == 0x13) {
        val = (float)(s64)*(u64*)arg0;
        goto got_float;
    } else if ((tag & 0xF) == 4) {
        u64 local[2];
        u64 r = FUN_7103907950(*(u64*)arg0 + 0x18, local);
        u64 obj = *(u64*)arg0;
        u64 cnt;
        if (*(u8*)(obj + 8) == 4) {
            cnt = *(u8*)(obj + 0xB);
        } else {
            cnt = *(u64*)(obj + 0x10);
        }
        if (r == cnt + 1) {
            float f_scvtf = (float)(s64)local[0];
            float f_fmov = *(float*)&local[0];
            val = (*(u32*)&local[1] == 0x13) ? f_scvtf : f_fmov;
            goto got_float;
        }
        val = 0.0f;
        goto got_float;
    } else {
        val = 0.0f;
        goto got_float;
    }

resolve2: {
        u64 base2 = **(u64**)(L + 0x20) + 0x20;
        top = *(u64*)(L + 0x10);
        u32* slot = (base2 < top) ? (u32*)base2 : DAT_7104861960;
        u32 tag2 = slot[2] & 0xF;
        u64 obj;
        if (tag2 == 2) {
            obj = *(u64*)slot;
        } else if (tag2 == 7) {
            obj = *(u64*)slot + 0x28;
        } else {
            obj = 0;
        }
        mod = *(u64*)(obj + 0x38);
    }

do_adjust:
    top = top + ((u64)(-(s64)diff << 28) >> 28);

call_site:
    *(u64*)(L + 0x10) = top;
    (**(void(**)(u64, float))(*(u64*)mod + 0x130))(mod, val);
    return 0;
}

// 0x710206e1c0 — ReflectModule reset_info (same pattern, vtable 0x148)
u64 FUN_710206e1c0(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x18);
    if (!mod) return 0;
    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    u32* arg0 = (base < top) ? (u32*)base : DAT_7104861960;
    s64 diff = (s64)(top - base);
    u32 tag = arg0[2]; s32 argc = (s32)((u64)diff >> 4); float val;
    if (tag == 3) { val = *(float*)arg0;
    gf: if (argc >= 2) goto r2;
    cs: if (argc < 0) { u64 t = **(u64**)(L+0x20)+(s64)((diff<<28)^(u64)(-0x100000000LL))/(1<<28)+0x10; u64 sp=*(u64*)(L+0x10); while(sp<t){*(u64*)(L+0x10)=sp+0x10;*(u32*)(sp+8)=0;sp=*(u64*)(L+0x10);} goto cc; }
        top = *(u64*)(L + 0x10); goto da;
    } else if (tag == 0x13) { val = (float)(s64)*(u64*)arg0; goto gf;
    } else if ((tag & 0xF) == 4) { u64 lc[2]; u64 r=FUN_7103907950(*(u64*)arg0+0x18,lc); u64 o=*(u64*)arg0; u64 cn; if(*(u8*)(o+8)==4) cn=*(u8*)(o+0xB); else cn=*(u64*)(o+0x10); if(r==cn+1){float fs=(float)(s64)lc[0];float ff=*(float*)&lc[0];val=(*(u32*)&lc[1]==0x13)?fs:ff;goto gf;} val=0.0f;goto gf;
    } else { val = 0.0f; goto gf; }
r2: { u64 b2=**(u64**)(L+0x20)+0x20; top=*(u64*)(L+0x10); u32* sl=(b2<top)?(u32*)b2:DAT_7104861960; u32 t2=sl[2]&0xF; u64 ob; if(t2==2) ob=*(u64*)sl; else if(t2==7) ob=*(u64*)sl+0x28; else ob=0; mod=*(u64*)(ob+0x38); }
da: top = top + ((u64)(-(s64)diff << 28) >> 28);
cc: *(u64*)(L + 0x10) = top;
    (**(void(**)(u64, float))(*(u64*)mod + 0x148))(mod, val);
    return 0;
}

// 0x710206f3d0 — SearchModule set_offset (acc+0xE0, redir +0xF8, vt 0x80)
u64 FUN_710206f3d0(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xE0);
    if (!mod) return 0;
    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    u32* arg0 = (base < top) ? (u32*)base : DAT_7104861960;
    s64 diff = (s64)(top - base);
    u32 tag = arg0[2]; s32 argc = (s32)((u64)diff >> 4); float val;
    if (tag == 3) { val = *(float*)arg0;
    gf: if (argc >= 2) goto r2;
    cs: if (argc < 0) { u64 t = **(u64**)(L+0x20)+(s64)((diff<<28)^(u64)(-0x100000000LL))/(1<<28)+0x10; u64 sp=*(u64*)(L+0x10); while(sp<t){*(u64*)(L+0x10)=sp+0x10;*(u32*)(sp+8)=0;sp=*(u64*)(L+0x10);} goto cc; }
        top = *(u64*)(L + 0x10); goto da;
    } else if (tag == 0x13) { val = (float)(s64)*(u64*)arg0; goto gf;
    } else if ((tag & 0xF) == 4) { u64 lc[2]; u64 r=FUN_7103907950(*(u64*)arg0+0x18,lc); u64 o=*(u64*)arg0; u64 cn; if(*(u8*)(o+8)==4) cn=*(u8*)(o+0xB); else cn=*(u64*)(o+0x10); if(r==cn+1){float fs=(float)(s64)lc[0];float ff=*(float*)&lc[0];val=(*(u32*)&lc[1]==0x13)?fs:ff;goto gf;} val=0.0f;goto gf;
    } else { val = 0.0f; goto gf; }
r2: { u64 b2=**(u64**)(L+0x20)+0x20; top=*(u64*)(L+0x10); u32* sl=(b2<top)?(u32*)b2:DAT_7104861960; u32 t2=sl[2]&0xF; u64 ob; if(t2==2) ob=*(u64*)sl; else if(t2==7) ob=*(u64*)sl+0x28; else ob=0; mod=*(u64*)(ob+0xF8); }
da: top = top + ((u64)(-(s64)diff << 28) >> 28);
cc: *(u64*)(L + 0x10) = top;
    (**(void(**)(u64, float))(*(u64*)mod + 0x80))(mod, val);
    return 0;
}

// 0x710206f670 — SearchModule set_remove_log_attack (acc+0xE0, redir +0xF8, vt 0x90)
u64 FUN_710206f670(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xE0);
    if (!mod) return 0;
    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    u32* arg0 = (base < top) ? (u32*)base : DAT_7104861960;
    s64 diff = (s64)(top - base);
    u32 tag = arg0[2]; s32 argc = (s32)((u64)diff >> 4); float val;
    if (tag == 3) { val = *(float*)arg0;
    gf: if (argc >= 2) goto r2;
    cs: if (argc < 0) { u64 t = **(u64**)(L+0x20)+(s64)((diff<<28)^(u64)(-0x100000000LL))/(1<<28)+0x10; u64 sp=*(u64*)(L+0x10); while(sp<t){*(u64*)(L+0x10)=sp+0x10;*(u32*)(sp+8)=0;sp=*(u64*)(L+0x10);} goto cc; }
        top = *(u64*)(L + 0x10); goto da;
    } else if (tag == 0x13) { val = (float)(s64)*(u64*)arg0; goto gf;
    } else if ((tag & 0xF) == 4) { u64 lc[2]; u64 r=FUN_7103907950(*(u64*)arg0+0x18,lc); u64 o=*(u64*)arg0; u64 cn; if(*(u8*)(o+8)==4) cn=*(u8*)(o+0xB); else cn=*(u64*)(o+0x10); if(r==cn+1){float fs=(float)(s64)lc[0];float ff=*(float*)&lc[0];val=(*(u32*)&lc[1]==0x13)?fs:ff;goto gf;} val=0.0f;goto gf;
    } else { val = 0.0f; goto gf; }
r2: { u64 b2=**(u64**)(L+0x20)+0x20; top=*(u64*)(L+0x10); u32* sl=(b2<top)?(u32*)b2:DAT_7104861960; u32 t2=sl[2]&0xF; u64 ob; if(t2==2) ob=*(u64*)sl; else if(t2==7) ob=*(u64*)sl+0x28; else ob=0; mod=*(u64*)(ob+0xF8); }
da: top = top + ((u64)(-(s64)diff << 28) >> 28);
cc: *(u64*)(L + 0x10) = top;
    (**(void(**)(u64, float))(*(u64*)mod + 0x90))(mod, val);
    return 0;
}

// 0x710206f910 — SearchModule set_sync_lr (acc+0xE0, redir +0xF8, vt 0xA0)
u64 FUN_710206f910(u64 L) {
    u64 acc = *(u64*)(L - 8);
    if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xE0);
    if (!mod) return 0;
    u64 base = **(u64**)(L + 0x20) + 0x10;
    u64 top = *(u64*)(L + 0x10);
    u32* arg0 = (base < top) ? (u32*)base : DAT_7104861960;
    s64 diff = (s64)(top - base);
    u32 tag = arg0[2]; s32 argc = (s32)((u64)diff >> 4); float val;
    if (tag == 3) { val = *(float*)arg0;
    gf: if (argc >= 2) goto r2;
    cs: if (argc < 0) { u64 t = **(u64**)(L+0x20)+(s64)((diff<<28)^(u64)(-0x100000000LL))/(1<<28)+0x10; u64 sp=*(u64*)(L+0x10); while(sp<t){*(u64*)(L+0x10)=sp+0x10;*(u32*)(sp+8)=0;sp=*(u64*)(L+0x10);} goto cc; }
        top = *(u64*)(L + 0x10); goto da;
    } else if (tag == 0x13) { val = (float)(s64)*(u64*)arg0; goto gf;
    } else if ((tag & 0xF) == 4) { u64 lc[2]; u64 r=FUN_7103907950(*(u64*)arg0+0x18,lc); u64 o=*(u64*)arg0; u64 cn; if(*(u8*)(o+8)==4) cn=*(u8*)(o+0xB); else cn=*(u64*)(o+0x10); if(r==cn+1){float fs=(float)(s64)lc[0];float ff=*(float*)&lc[0];val=(*(u32*)&lc[1]==0x13)?fs:ff;goto gf;} val=0.0f;goto gf;
    } else { val = 0.0f; goto gf; }
r2: { u64 b2=**(u64**)(L+0x20)+0x20; top=*(u64*)(L+0x10); u32* sl=(b2<top)?(u32*)b2:DAT_7104861960; u32 t2=sl[2]&0xF; u64 ob; if(t2==2) ob=*(u64*)sl; else if(t2==7) ob=*(u64*)sl+0x28; else ob=0; mod=*(u64*)(ob+0xF8); }
da: top = top + ((u64)(-(s64)diff << 28) >> 28);
cc: *(u64*)(L + 0x10) = top;
    (**(void(**)(u64, float))(*(u64*)mod + 0xA0))(mod, val);
    return 0;
}
