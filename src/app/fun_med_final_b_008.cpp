// SSBU 13.0.4 — MEDIUM-tier decompilation batch 008
// Address range: 0x71002b3fe8 – 0x71002c2bf0
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// Forward declarations
extern "C" {
    [[noreturn]] void nn_detail_UnexpectedDefaultImpl(const char *, const char *, int);
    void  FUN_71002ba4d0(void *p);
    void  FUN_71002b9b20(void *p);
    void  FUN_71002ba540_v(void *p);    // addr-collision guard
    void  FUN_71002ba5e0_v(void *p);
    void  FUN_71002b9660(void *p);
    void  FUN_71002b9360(void *p);
    void  FUN_71002bbb30(void *p, void *q);
    void  FUN_71002c1480(void *p);
    void  FUN_71002bf040(void *p);
    void  FUN_71002c1790_v(void *p);
    void  FUN_71002c1d20_v(void *p);
    void  FUN_71002be4e0(void *p);
    void  FUN_71002be0b0(void *p);
    void *FUN_71002b4e30();
    void  FUN_71002c28d0(void *p, int v);
    void  FUN_71002b8740();
    void  FUN_71002b8ab0(long p, float *v, int flag);
    void  FUN_71002bb530(void *p);
    void  FUN_71002bb540(void *p);
    void  FUN_71002c31e0(void *dst, void *src);
    void *FUN_71002c3200(void *p);
    void  FUN_71002b4040(void *p, void *q);
    void  FUN_7100031070();
    void  FUN_71002b94a0();
    void *FUN_71002c31d0(void *p);
    void  FUN_71000339f0(void *p);
    u32   FUN_71002c2f60(void *a, void *b);
    void  FUN_71002c2df0(void *p);
    void  FUN_71002c2e50(void *a, void *b, u32 c);
    u32   FUN_71002c2d60(void *a, void *b);
    void  FUN_71002c2bf0_clear(void *p);   // clear variant (not the lookup below)
    void  FUN_71002c2c30(void *a, void *b, u32 c);
    float powf(float base, float exp);
}

// FUN_71002b3fe8 — noreturn: call UnexpectedDefaultImpl (reached unreachable default)
[[noreturn]] void FUN_71002b3fe8() {
    nn_detail_UnexpectedDefaultImpl("", "", 0);
}

// FUN_71002b41a0 — shutdown handle: destroy + close, clear slot
void FUN_71002b41a0(u64 *param_1) {
    FUN_71002ba4d0((void *)*param_1);
    FUN_71002b9b20((void *)*param_1);
    *param_1 = 0;
}

// FUN_71002b41d0 — thin wrapper: forward to FUN_71002ba540
void FUN_71002b41d0(u64 *param_1) {
    FUN_71002ba540_v((void *)*param_1);
}

// FUN_71002b41f0 — thin wrapper: forward to FUN_71002ba5e0
void FUN_71002b41f0(u64 *param_1) {
    FUN_71002ba5e0_v((void *)*param_1);
}

// FUN_71002b4340 — shutdown: stop + close, clear slot
void FUN_71002b4340(u64 *param_1) {
    FUN_71002b9660((void *)*param_1);
    FUN_71002b9360((void *)*param_1);
    *param_1 = 0;
}

// FUN_71002b46c0 — copy two u64 from param_2, pass to FUN_71002bbb30
void FUN_71002b46c0(u64 *param_1, u64 *param_2) {
    u64 tmp[2];
    tmp[1] = param_2[1];
    tmp[0] = param_2[0];
    FUN_71002bbb30((void *)*param_1, tmp);
}

// FUN_71002b4ae0 — shutdown: FUN_71002c1480 + FUN_71002bf040, clear slot
void FUN_71002b4ae0(u64 *param_1) {
    FUN_71002c1480((void *)*param_1);
    FUN_71002bf040((void *)*param_1);
    *param_1 = 0;
}

// FUN_71002b4b10 — thin wrapper to FUN_71002c1790
void FUN_71002b4b10(u64 *param_1) {
    FUN_71002c1790_v((void *)*param_1);
}

// FUN_71002b4b30 — thin wrapper to FUN_71002c1d20
void FUN_71002b4b30(u64 *param_1) {
    FUN_71002c1d20_v((void *)*param_1);
}

// FUN_71002b4c70 — shutdown: FUN_71002be4e0 + FUN_71002be0b0, clear slot
void FUN_71002b4c70(u64 *param_1) {
    FUN_71002be4e0((void *)*param_1);
    FUN_71002be0b0((void *)*param_1);
    *param_1 = 0;
}

// FUN_71002b5f90 — get context ptr, dispatch with flag 0
void FUN_71002b5f90() {
    void *ctx = FUN_71002b4e30();
    FUN_71002c28d0(ctx, 0);
}

// FUN_71002b7b60 — bounding-box accumulator for animation states
// Updates min/max AABB fields at fixed offsets based on state type:
//   even cases (2,4,6): left-hand bounds at 0x480c–0x4838
//   odd cases (3,5,7): right-hand bounds at 0x483c–0x4868
//   cases 8,10: FUN_71002b8ab0(p, v, 0)
//   cases 9,11: FUN_71002b8ab0(p, v, 1)
//   case 12: no-op
void FUN_71002b7b60(long param_1, float *param_2, u32 param_3) {
    switch (param_3) {
    case 0: case 1:
        FUN_71002b8740();
        return;
    case 2: case 4: case 6: {
        // Update min (0x480c–0x4814) and max (0x4818–0x4820) for first AABB
        float *base = (float *)(param_1 + 0x480c);
        for (int i = 0; i < 3; i++) {
            if (param_2[i] <= base[i]) base[i] = param_2[i];
        }
        float *maxb = (float *)(param_1 + 0x4818);
        for (int i = 0; i < 3; i++) {
            if (maxb[i] <= param_2[3 + i]) maxb[i] = param_2[3 + i];
        }
        // Second AABB min at 0x4824, max at 0x4830
        float *base2 = (float *)(param_1 + 0x4824);
        for (int i = 0; i < 3; i++) {
            if (param_2[i] <= base2[i]) base2[i] = param_2[i];
        }
        float *maxb2 = (float *)(param_1 + 0x4830);
        for (int i = 0; i < 3; i++) {
            if (maxb2[i] <= param_2[3 + i]) maxb2[i] = param_2[3 + i];
        }
        // Final float: max of last component
        float *fin = (float *)(param_1 + 0x4838);
        float v5 = param_2[5];
        if (*fin <= v5) *fin = v5;
        return;
    }
    case 3: case 5: case 7: {
        float *base = (float *)(param_1 + 0x483c);
        for (int i = 0; i < 3; i++) {
            if (param_2[i] <= base[i]) base[i] = param_2[i];
        }
        float *maxb = (float *)(param_1 + 0x4848);
        for (int i = 0; i < 3; i++) {
            if (maxb[i] <= param_2[3 + i]) maxb[i] = param_2[3 + i];
        }
        float *base2 = (float *)(param_1 + 0x4854);
        for (int i = 0; i < 3; i++) {
            if (param_2[i] <= base2[i]) base2[i] = param_2[i];
        }
        float *maxb2 = (float *)(param_1 + 0x4860);
        for (int i = 0; i < 3; i++) {
            if (maxb2[i] <= param_2[3 + i]) maxb2[i] = param_2[3 + i];
        }
        float *fin = (float *)(param_1 + 0x4868);
        float v5 = param_2[5];
        if (*fin <= v5) *fin = v5;
        return;
    }
    case 8: case 10:
        FUN_71002b8ab0(param_1, param_2, 0);
        return;
    case 9: case 11:
        FUN_71002b8ab0(param_1, param_2, 1);
        return;
    case 12:
        return;
    default:
        nn_detail_UnexpectedDefaultImpl("", "", 0);
    }
}

// FUN_71002b8120 — release audio handle at param_1+0x47a0 via FUN_71002bb530
void FUN_71002b8120(long param_1) {
    FUN_71002bb530((void *)(param_1 + 0x47a0));
}

// FUN_71002b8140 — release audio handle at param_1+0x47a0 via FUN_71002bb540
void FUN_71002b8140(long param_1) {
    FUN_71002bb540((void *)(param_1 + 0x47a0));
}

// FUN_71002b8160 — compute element address: param_1 + param_2*0x30 + param_3*0x18 + 0x480c
long FUN_71002b8160(long param_1, u32 param_2, u32 param_3) {
    return param_1 + (u64)param_2 * 0x30 + (u64)param_3 * 0x18 + 0x480c;
}

// FUN_71002b82c0 — audio/animation layer param setter (cases 0-4)
// Sets layer-specific source data and triggers derived value computation
void FUN_71002b82c0(long param_1, u32 param_2, void *param_3, int param_4) {
    void *src_ptr;
    void *out_ptr;
    void *computed;

    switch (param_2) {
    case 0:
        src_ptr = (void *)(param_1 + 0x28);
        FUN_71002c31e0(src_ptr, param_3);
        out_ptr = (void *)(param_1 + 0x918);
        computed = FUN_71002c3200(src_ptr);
        FUN_71002b4040(out_ptr, computed);
        return;
    case 1:
        FUN_71002c31e0((void *)(param_1 + 0x150), param_3);
        computed = FUN_71002c3200((void *)(param_1 + 0x150));
        if (*(s8 *)(param_1 + 0x247e)) {
            FUN_71002b4040((void *)(param_1 + 0x1548), computed);
        }
        if (*(s8 *)(param_1 + 0x247f)) {
            FUN_71002b4040((void *)(param_1 + 0x17b8), computed);
        }
        return;
    case 2:
        src_ptr = (void *)(param_1 + 0x2488 + (long)param_4 * 0x128);
        FUN_71002c31e0(src_ptr, param_3);
        out_ptr = (void *)(param_1 + 0x3cf0 + (long)param_4 * 0x90);
        computed = FUN_71002c3200(src_ptr);
        FUN_71002b4040(out_ptr, computed);
        return;
    case 3:
        FUN_71002c31e0((void *)(param_1 + 0x278), param_3);
        computed = FUN_71002c3200((void *)(param_1 + 0x278));
        if (*(s8 *)(param_1 + 0x2482)) {
            FUN_71002b4040((void *)(param_1 + 0x1f08), computed);
        }
        if (*(s8 *)(param_1 + 0x2483)) {
            FUN_71002b4040((void *)(param_1 + 0x2178), computed);
        }
        return;
    case 4:
        src_ptr = (void *)(param_1 + 0x3a0);
        FUN_71002c31e0(src_ptr, param_3);
        out_ptr = (void *)(param_1 + 0x23e8);
        computed = FUN_71002c3200(src_ptr);
        FUN_71002b4040(out_ptr, computed);
        return;
    default:
        nn_detail_UnexpectedDefaultImpl("", "", 0);
    }
}

// FUN_71002b8450 — audio source clear by channel type (cases 0-4)
void FUN_71002b8450(long param_1, u32 param_2, int param_3) {
    long offset = 0;
    switch (param_2) {
    case 0: break;
    case 1: offset = 1; break;
    case 2:
        FUN_71002c3200((void *)(param_1 + 0x2488 + (long)param_3 * 0x128));
        return;
    case 3: offset = 2; break;
    case 4: offset = 3; break;
    default:
        nn_detail_UnexpectedDefaultImpl("", "", 0);
    }
    FUN_71002c3200((void *)(param_1 + offset * 0x128 + 0x28));
}

// FUN_71002b8c80 — trivial getter: return u32 at *param_1
u32 FUN_71002b8c80(u32 *param_1) {
    return *param_1;
}

// FUN_71002b8ca0 — empty stub (no-op)
void FUN_71002b8ca0() {
}

// FUN_71002b8ce0 — trivial getter: return u32 at *param_1 (second instance)
u32 FUN_71002b8ce0(u32 *param_1) {
    return *param_1;
}

// FUN_71002b8d10 — linear float map: return param_1 * scale + offset
// scale = DAT_7104470ba0, offset = DAT_71044723d0
extern float DAT_7104470ba0;
extern float DAT_71044723d0;
float FUN_71002b8d10(int param_1) {
    return (float)param_1 * DAT_7104470ba0 + DAT_71044723d0;
}

// FUN_71002b92c0 — 10-bit twos-complement negate with special case for 0x1ff
// If low 10 bits == 0x1ff: set to 0x200; if == 0x200: set to 0x1ff; else: negate
void FUN_71002b92c0(u32 *param_1) {
    u32 val  = *param_1;
    u32 low10 = val & 0x3ff;
    u32 neg  = (-val) & 0x3ff;
    if (low10 == 0x1ff) neg = 0x200;
    u32 result = (low10 != 0x200) ? neg : 0x1ff;
    *param_1 = (val & 0xfffffc00) | result;
}

// FUN_71002b9480 — init helper: call FUN_71002b94a0, return 0
u64 FUN_71002b9480() {
    FUN_71002b94a0();
    return 0;
}

// FUN_71002ba540 — get channel string if flag byte at +0x919+param_2 is set
u64 FUN_71002ba540(long param_1, u32 param_2) {
    if (*(s8 *)(param_1 + (u64)(param_2 + 1) + 0x918)) {
        return (u64)FUN_71002c31d0((void *)(param_1 + (u64)param_2 * 0x128 + 0x5a0));
    }
    return 0;
}

// FUN_71002ba5e0 — clear channel string slot param_2
void FUN_71002ba5e0(long param_1, u32 param_2) {
    FUN_71002c3200((void *)(param_1 + (u64)param_2 * 0x128 + 0x5a0));
}

// FUN_71002bad40 — frequency/brightness power-law correction
// Only active for certain param_1 channel indices (bit test against 0x61c0 mask)
extern float DAT_71044a1540;
extern long  DAT_71044a1570;
extern float DAT_7104471898;
extern float DAT_7104470d04;
extern float DAT_7104470f64;
extern float DAT_7104471090;
extern float DAT_71044725f8;
void FUN_71002bad40(u32 param_1, float *param_2, int param_3) {
    if (param_3 == 1 || param_1 >= 0xf) return;
    if (!((1u << (param_1 & 0x1f)) & 0x61c0u)) return;
    u32 chan_idx = param_1 - 6;
    float base_val = 1.0f;
    if (chan_idx < 9 && ((0x187u >> (chan_idx & 0x1f)) & 1)) {
        base_val = *(float *)(&DAT_71044a1540 +
                              *(long *)(&DAT_71044a1570 + (long)(int)chan_idx * 8) * 8);
    }
    float exp_val = (param_2[0] * DAT_7104471898 +
                     param_2[1] * DAT_7104470d04 +
                     param_2[2] * DAT_7104470f64) * DAT_7104471090 + DAT_71044725f8 - 1.0f;
    powf(base_val, exp_val);
}

// FUN_71002bae40 — init: call FUN_7100031070, set two packed u32 fields
void FUN_71002bae40(u64 *param_1) {
    FUN_7100031070();
    *param_1 = 0x1000000040ULL;
}

// FUN_71002bb310 — zero-init 14-slot u64 struct (+ u32 at +0xd*8+4)
void FUN_71002bb310(u64 *param_1) {
    *(u32 *)(param_1 + 0xd) = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0]   = 0;
    param_1[9]   = 0;
    param_1[10]  = 0;
    param_1[7]   = 0;
    param_1[8]   = 0;
    param_1[5]   = 0;
    param_1[6]   = 0;
    param_1[3]   = 0;
    param_1[4]   = 0;
    param_1[1]   = 0;
    param_1[2]   = 0;
}

// FUN_71002c1790 — get channel name ptr, return null if empty string
char *FUN_71002c1790(long param_1, u32 param_2) {
    char *str = (char *)FUN_71002c31d0((void *)(param_1 + (u64)param_2 * 0x128 + 8));
    if (*str != '\0') return str;
    return 0;
}

// FUN_71002c1d20 — clear channel name string slot
void FUN_71002c1d20(long param_1, u32 param_2) {
    FUN_71002c3200((void *)(param_1 + (u64)param_2 * 0x128 + 8));
}

// FUN_71002c1f70 — align ptr up: (ptr + align - 1) & ~(align - 1)
void FUN_71002c1f70(long param_1, long param_2) {
    *(u64 *)(param_1 + 0x10) =
        (u64)((*(long *)(param_1 + 0x10) + param_2) - 1) & (u64)(-param_2);
}

// FUN_71002c1fe0 — total size: FUN_71000339f0(*param_1) + param_1[2]
long FUN_71002c1fe0(u64 *param_1) {
    extern long FUN_71000339f0_ret(void *);
    long base = FUN_71000339f0_ret((void *)*param_1);
    return base + (long)param_1[2];
}

// FUN_71002c2810 — table lookup (< 3): return DAT_71044a7c80[param_1]
extern u64 DAT_71044a7c80;
u64 FUN_71002c2810(u32 param_1) {
    if (param_1 < 3) {
        return *(u64 *)(&DAT_71044a7c80 + (long)(int)param_1 * 8);
    }
    nn_detail_UnexpectedDefaultImpl("", "", 0);
}

// FUN_71002c2910 — compute slot 0 value and dispatch to FUN_71002c2e50
void FUN_71002c2910(long param_1, void *param_2, void *param_3) {
    u32 val = FUN_71002c2f60(param_2, param_3);
    FUN_71002c2df0(param_2);
    FUN_71002c2e50(*(void **)(param_1 + 0x10), param_2, val);
}

// FUN_71002c2960 — compute slot 1 value and dispatch to FUN_71002c2c30
void FUN_71002c2960(long param_1, void *param_2, void *param_3) {
    u32 val = FUN_71002c2d60(param_2, param_3);
    FUN_71002c2bf0_clear(param_2);
    FUN_71002c2c30(*(void **)(param_1 + 0x18), param_2, val);
}

// FUN_71002c2b30 — compute slot address: base+0x18 + param_2*0x48 + 0x12704
long FUN_71002c2b30(long param_1, u32 param_2) {
    return *(long *)(param_1 + 0x18) + (u64)param_2 * 0x48 + 0x12704;
}

// FUN_71002c2b50 — compute slot address: base+0x18 + param_2*0x24 + 0x14c24
long FUN_71002c2b50(long param_1, u32 param_2) {
    return *(long *)(param_1 + 0x18) + (u64)param_2 * 0x24 + 0x14c24;
}

// FUN_71002c2ba0 — divide u32 at +0x2c by table[1]
u64 FUN_71002c2ba0(long param_1) {
    u32 val   = *(u32 *)(param_1 + 0x2c);
    u64 denom = FUN_71002c2810(1);
    if (!denom) return 0;
    return (u64)(val / (u32)denom);
}

// FUN_71002c2bf0 — table lookup (< 12): return DAT_71044a7cd0[param_1]
extern u32 DAT_71044a7cd0;
u32 FUN_71002c2bf0(u32 param_1) {
    if (param_1 < 0xc) {
        return *(u32 *)(&DAT_71044a7cd0 + (long)(int)param_1 * 4);
    }
    nn_detail_UnexpectedDefaultImpl("", "", 0);
}

} // namespace lua_bind
} // namespace app
