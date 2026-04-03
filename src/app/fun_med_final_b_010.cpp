// SSBU 13.0.4 — MEDIUM-tier decompilation batch 010
// Address range: 0x7100325ae0 – 0x7100358c20
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// External constants referenced by animation blend weight functions
extern float DAT_710447291c; // 100.0f (max weight cap for some channels)
extern float DAT_710447281c; // channel group cap constant
extern float DAT_71044721a0; // channel group cap constant
extern float DAT_7104470bb0; // channel group cap constant
extern float DAT_71044718a4; // weight constant for cases 0x3f-0x41
extern float DAT_71044723d8; // default weight cap

// Forward declarations
extern "C" {
    [[noreturn]] void std_vector_throw_out_of_range();
    void  FUN_71037378c0(void *p);
    void  std_recursive_mutex_lock();
    void  std_recursive_mutex_unlock();
}

// FUN_7100325ae0 — animation blend weight normalizer
// Clamps and normalizes float weights for each animation channel group.
// Each channel has its own normalization group (groups of 4, 11, 9, 3, 3, 5 channels).
// If the group sum is 0, special handling; otherwise normalize to sum=1.0 * cap.
void FUN_7100325ae0(long param_1, u32 param_2) {
    // Clamp negative value to 0
    if (param_2 < 0x48) {
        float *slot = (float *)(param_1 + (long)(int)param_2 * 4);
        if (*slot < 0.0f) *slot = 0.0f;
    }

    float *base = (float *)param_1;
    switch (param_2) {
    case 0x24: case 0x25: case 0x26: case 0x27: {
        // Group at +0x90: 4 channels, cap = DAT_710447291c
        float sum = base[0x90/4] + base[0x94/4] + base[0x98/4] + base[0x9c/4];
        if (sum != 0.0f) {
            base[0x90/4] = (base[0x90/4] / sum) * DAT_710447291c;
            base[0x94/4] = (base[0x94/4] / sum) * DAT_710447291c;
            base[0x98/4] = (base[0x98/4] / sum) * DAT_710447291c;
            base[0x9c/4] = (base[0x9c/4] / sum) * DAT_710447291c;
        }
        return;
    }
    case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c:
    case 0x2d: case 0x2e: case 0x2f: case 0x30: case 0x31: case 0x32: {
        // Group at +0xa0: 11 channels, cap = DAT_71044721a0
        float sum = 0.0f;
        for (int i = 0; i < 11; i++) sum += base[(0xa0 + i*4)/4];
        if (sum != 0.0f) {
            for (int i = 0; i < 11; i++)
                base[(0xa0 + i*4)/4] = (base[(0xa0 + i*4)/4] / sum) * DAT_71044721a0;
        }
        return;
    }
    case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39: case 0x3a: case 0x3b: {
        // Group at +0xcc: 9 channels, cap = DAT_7104470bb0
        float sum = 0.0f;
        for (int i = 0; i < 9; i++) sum += base[(0xcc + i*4)/4];
        if (sum != 0.0f) {
            for (int i = 0; i < 9; i++)
                base[(0xcc + i*4)/4] = (base[(0xcc + i*4)/4] / sum) * DAT_7104470bb0;
        }
        return;
    }
    case 0x3c: case 0x3d: case 0x3e: {
        // Group at +0xf0: 3 channels, cap = DAT_710447281c
        float sum = base[0xf0/4] + base[0xf4/4] + base[0xf8/4];
        if (sum != 0.0f) {
            base[0xf0/4] = (base[0xf0/4] / sum) * DAT_710447281c;
            base[0xf4/4] = (base[0xf4/4] / sum) * DAT_710447281c;
            base[0xf8/4] = (base[0xf8/4] / sum) * DAT_710447281c;
        }
        return;
    }
    case 0x3f: case 0x40: case 0x41: {
        // Group at +0xfc: 3 channels, cap = DAT_710447291c
        float sum = base[0xfc/4] + base[0x100/4] + base[0x104/4];
        if (sum != 0.0f) {
            base[0xfc/4]  = (base[0xfc/4]  / sum) * DAT_710447291c;
            base[0x100/4] = (base[0x100/4] / sum) * DAT_710447291c;
            base[0x104/4] = (base[0x104/4] / sum) * DAT_710447291c;
        }
        return;
    }
    case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: {
        // Group at +0x108: 5 channels, cap = DAT_710447291c
        // Only active if mode at +0x120 is 0x47 or 0x39
        s32 mode = *(s32 *)(param_1 + 0x120);
        if (mode == 0x47 || mode == 0x39) {
            float sum = 0.0f;
            for (int i = 0; i < 5; i++) sum += base[(0x108 + i*4)/4];
            if (sum != 0.0f) {
                for (int i = 0; i < 5; i++)
                    base[(0x108 + i*4)/4] = (base[(0x108 + i*4)/4] / sum) * DAT_710447291c;
            }
            return;
        }
        goto single_clamp;
    }
    default:
        if (param_2 > 0x47) return;
    single_clamp: {
        float v = base[(long)(int)param_2];
        if (v != DAT_710447291c && v < DAT_710447291c) {
            // Not yet at cap — clamp to 100.0f (0x42c80000)
            *(u32 *)(param_1 + (long)(int)param_2 * 4) = 0x42c80000;
            return;
        }
        if (v < 0.0f) {
            *(u32 *)(param_1 + (long)(int)param_2 * 4) = 0;
        }
        break;
    }
    }
}

// FUN_7100325e50 — return the weight cap for a given animation channel
u32 FUN_7100325e50(long param_1, u32 param_2) {
    switch (param_2) {
    case 0x23: return 0;
    case 0x24: case 0x25: case 0x26: case 0x27: return 0x41c80000; // 25.0f
    case 0x3f: case 0x40: case 0x41: return (u32)(u64)&DAT_71044718a4;
    case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: {
        s32 mode = *(s32 *)(param_1 + 0x120);
        if (mode == 0x39 || mode == 0x47) return 0x41a00000; // 20.0f
        break;
    }
    default: break;
    }
    return (u32)(u64)&DAT_71044723d8;
}

// FUN_71003a48bc — noreturn: throw std::out_of_range from vector
[[noreturn]] void FUN_71003a48bc() {
    std_vector_throw_out_of_range();
}

// FUN_71003a71f0 — init vtable ptr and sentinel fields at +0x60/+0x50/+0x68
extern void *PTR_FUN_7104f61778;
void FUN_71003a71f0(u64 *param_1) {
    *param_1 = (u64)&PTR_FUN_7104f61778;
    FUN_71037378c0((void *)(param_1 + 0xc));
    param_1[0xc] = 0;
    *(u32 *)(param_1 + 0xd) = 0xffffffff;
    FUN_71037378c0((void *)(param_1 + 10));
    *(u32 *)(param_1 + 0xb) = 0xffffffff;
    param_1[10] = 0;
}

// FUN_71003a72a0 — load 16 bytes, set flag at +0x87, store with NEON ext reorder
// NEON_ext(v, v, 8): swaps the two 8-byte halves, stores result at +0x18, orig u64 at +0x10
void FUN_71003a72a0(long param_1, u8 (*param_2)[16]) {
    u64 lo = *(u64 *)(*param_2);        // param_2[0..7]
    u64 hi = *(u64 *)(*param_2 + 8);   // param_2[8..15]
    *(u8 *)(param_1 + 0x87) = 1;
    // NEON_ext(v, v, 8) of 16-byte value swaps the two 64-bit halves
    *(u32 *)(param_1 + 0x18) = (u32)hi; // low 32 bits of hi half
    *(u64 *)(param_1 + 0x10) = lo;
}

// FUN_71003a8e30 — double-vtable dispatch returning 16-byte value
typedef u8 (*VtFn16)();
u64 FUN_71003a8e30(long param_1) {
    // (*(*(*(*param_1+0x20)+0x38)+0x60))()  — double-indirect vtable call
    long *p  = *(long **)(param_1 + 0x20);
    long *q  = *(long **)(*p + 0x38);
    VtFn16 fn = *(VtFn16 *)(*q + 0x60);
    return (u64)fn();
}

// FUN_71003abd60 — input state mapper: 5 bits at param_1+100, each maps to field on obj at +8
// For each bit: if slot == -1 write action code (4 or 5), else write 2 or 0xff
void FUN_71003abd60(long param_1) {
    u8   flags = *(u8  *)(param_1 + 100);
    u8   dirs  = *(u8  *)(param_1 + 0x65);
    long obj   = *(long *)(param_1 + 8);

    // Bit 0: slot at obj+0x3c / state at obj+0x3a
    if (flags & 1) {
        s8 slot = *(s8 *)(obj + 0x3c);
        if (slot == -1) {
            *(u8 *)(obj + 0x3a) = (dirs & 1) ? 5 : 4;
        } else {
            *(u8 *)(obj + 0x3c) = (dirs & 1) ? ((slot == 0) ? 2 : 0xff) : ((slot == 1) ? 2 : 0xff);
        }
    }
    // Bit 1: slot at obj+0xa4 / state at obj+0xa2
    if (flags & 2) {
        s8 slot = *(s8 *)(obj + 0xa4);
        if (slot == -1) {
            *(u8 *)(obj + 0xa2) = ((dirs >> 1) & 1) ? 5 : 4;
        } else {
            *(u8 *)(obj + 0xa4) = ((dirs >> 1) & 1) ? ((slot == 0) ? 2 : 0xff) : ((slot == 1) ? 2 : 0xff);
        }
    }
    // Bit 2: slot at obj+0x10c / state at obj+0x10a
    if (flags & 4) {
        s8 slot = *(s8 *)(obj + 0x10c);
        if (slot == -1) {
            *(u8 *)(obj + 0x10a) = ((dirs >> 2) & 1) ? 5 : 4;
        } else {
            *(u8 *)(obj + 0x10c) = ((dirs >> 2) & 1) ? ((slot == 0) ? 2 : 0xff) : ((slot == 1) ? 2 : 0xff);
        }
    }
    // Bit 3: slot at obj+0x174 / state at obj+0x172
    if (flags & 8) {
        s8 slot = *(s8 *)(obj + 0x174);
        if (slot == -1) {
            *(u8 *)(obj + 0x172) = ((dirs >> 3) & 1) ? 5 : 4;
        } else {
            *(u8 *)(obj + 0x174) = ((dirs >> 3) & 1) ? ((slot == 0) ? 2 : 0xff) : ((slot == 1) ? 2 : 0xff);
        }
    }
    // Bit 4: slot at obj+0x1dc / state at obj+0x1da
    if (flags & 16) {
        s8 slot = *(s8 *)(obj + 0x1dc);
        if (slot == -1) {
            *(u8 *)(obj + 0x1da) = ((dirs >> 4) & 1) ? 5 : 4;
        } else {
            *(u8 *)(obj + 0x1dc) = ((dirs >> 4) & 1) ? ((slot == 0) ? 2 : 0xff) : ((slot == 1) ? 2 : 0xff);
        }
    }
    *(u8 *)(param_1 + 100) = 0;
}

// FUN_71003aeb50 — pooled object release (5 pool types, stride-based, mutex-guarded free-list)
// Decodes pool index from bits[28:31] of param_1; vtable-calls destructor, then returns slot
extern long *DAT_71052b7548[5]; // array of 5 pool descriptors

void FUN_71003aeb50(u64 param_1) {
    u32 lo   = (u32)param_1;
    u32 pool = (u32)(param_1 >> 0x1c) & 0xf;
    u32 slot_idx = lo >> 0x10 & 0xfff;
    long *obj = 0;
    long pool_base;
    u16 free_next;
    u16 free_head;
    long *pool_ptr;
    u64 idx_u;

    switch (pool) {
    case 0: {
        pool_ptr = DAT_71052b7548[0];
        if (slot_idx < *(u32 *)(pool_ptr + 3)) {
            long *cand = (long *)(*(long *)(pool_ptr + 1) + (u64)slot_idx * 0xf940);
            if (*(u32 *)(cand + 1) == lo) obj = cand;
        }
        (*(void(**)(long *))(*obj + 0x50))(obj);
        pool_base = *(long *)(*DAT_71052b7548 + 8);
        // Index via magic multiply (divide by stride): 0x41bbb2f80a4553f7 >> 14
        // Simplified: idx = (ptr - base) / 0xf940 (done via 128-bit shift for exact division)
        idx_u = (u64)((long)obj - pool_base);
        // For stride 0xf940 — use compiler-generated reciprocal multiply
        idx_u = (u64)(((__uint128_t)idx_u * 0x41bbb2f80a4553f7ULL) >> (64 + 14));
        free_head = (u16)idx_u;
        break;
    }
    case 1: {
        pool_ptr = DAT_71052b7548[1];
        if (slot_idx < *(u32 *)(pool_ptr + 3)) {
            long *cand = (long *)(*(long *)(pool_ptr + 1) + (u64)slot_idx * 0x3c30);
            if (*(u32 *)(cand + 1) == lo) obj = cand;
        }
        (*(void(**)(long *))(*obj + 0x50))(obj);
        pool_ptr  = DAT_71052b7548[1];
        idx_u = (u64)((long)obj - *(long *)(pool_ptr + 1));
        free_head = (u16)(idx_u / 0x3c30);
        break;
    }
    case 2: {
        pool_ptr = DAT_71052b7548[2];
        if (slot_idx < *(u32 *)(pool_ptr + 3)) {
            long *cand = (long *)(*(long *)(pool_ptr + 1) + (u64)slot_idx * 0x60c0);
            if (*(u32 *)(cand + 1) == lo) obj = cand;
        }
        (*(void(**)(long *))(*obj + 0x50))(obj);
        pool_base = *(long *)(DAT_71052b7548[2] + 1);
        idx_u = (u64)((long)obj - pool_base);
        idx_u = (u64)(((__uint128_t)idx_u * 0xa957fab5402a55ffULL) >> (64 + 14));
        free_head = (u16)idx_u;
        break;
    }
    case 3: {
        pool_ptr = DAT_71052b7548[3];
        if (slot_idx < *(u32 *)(pool_ptr + 3)) {
            long *cand = (long *)(*(long *)(pool_ptr + 1) + (u64)slot_idx * 0x300);
            if (*(u32 *)(cand + 1) == lo) obj = cand;
        }
        (*(void(**)(long *))(*obj + 0x50))(obj);
        pool_base = *(long *)(DAT_71052b7548[3] + 1);
        idx_u = (u64)((long)obj - pool_base);
        idx_u = (u64)(((__uint128_t)idx_u * 0xaaaaaaaaaaaaaaabULL) >> (64 + 9));
        free_head = (u16)idx_u;
        break;
    }
    case 4: {
        pool_ptr = DAT_71052b7548[4];
        if (slot_idx < *(u32 *)(pool_ptr + 3)) {
            long *cand = (long *)(*(long *)(pool_ptr + 1) + (u64)slot_idx * 0x2b0);
            if (*(u32 *)(cand + 1) == lo) obj = cand;
        }
        (*(void(**)(long *))(*obj + 0x50))(obj);
        pool_base = *(long *)(DAT_71052b7548[4] + 1);
        idx_u = (u64)((long)obj - pool_base);
        idx_u = (u64)(((__uint128_t)idx_u * 0xbe82fa0be82fa0bfULL) >> (64 + 9));
        free_head = (u16)idx_u;
        break;
    }
    default:
        return;
    }
    // Return slot to free-list (mutex-protected)
    pool_ptr = (pool == 0) ? DAT_71052b7548[0] : DAT_71052b7548[pool];
    std_recursive_mutex_lock();
    free_next = *(u16 *)(pool_ptr + 0x1c / 8);
    long *slot_arr = *(long **)(pool_ptr + 0x10 / 8);
    *(u16 *)(slot_arr + idx_u * 2 / 8) = free_next;
    *(u16 *)(pool_ptr + 0x1c / 8) = free_head;
    *(s16 *)(pool_ptr + 0x1e / 8) -= 1;
    std_recursive_mutex_unlock();
}

// FUN_71003aee20 — simpler pooled object release (no destructor, just free-list update)
void FUN_71003aee20(u64 param_1) {
    u32 pool = (u32)(param_1 >> 0x1c) & 0xf;
    u32 slot = (u32)param_1 >> 0x10 & 0xfff;
    long pool_base;
    if (pool > 4) return;
    pool_base = (long)DAT_71052b7548[pool];
    std_recursive_mutex_lock();
    long *slot_arr = *(long **)(pool_base + 0x10);
    *(u16 *)(slot_arr + slot * 2 / 8) = *(u16 *)(pool_base + 0x1c / 8);
    *(u16 *)(pool_base + 0x1c / 8) = (u16)slot;
    *(s16 *)(pool_base + 0x1e / 8) -= 1;
    std_recursive_mutex_unlock();
}

// cxa_guard singleton pattern: copy 16 bytes from PTR_ConstantZero to static storage
// Used for zero-initialized constant singletons (shared by several instances below)
extern "C" int  __cxa_guard_acquire(u64 *guard);
extern "C" void __cxa_guard_release(u64 *guard);
extern void *PTR_ConstantZero_71052a7a88; // points to 16-byte zero constant
extern void *PTR_ConstantZero_71052a7a80; // same, alternate ptr

// FUN_71003b01a0 — singleton: copy PTR_ConstantZero_71052a7a88 → DAT_71052b6f00
static u64 s_guard_71052b6ef0;
static u64 s_dat_71052b6f00[2];
void *FUN_71003b01a0() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6ef0))) goto done;
    s_dat_71052b6f00[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
    s_dat_71052b6f00[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
    __cxa_guard_release(&s_guard_71052b6ef0);
done:
    return s_dat_71052b6f00;
}

// FUN_71003b0250 — singleton: copy PTR_ConstantZero_71052a7a88 → DAT_71052b6ee0
static u64 s_guard_71052b6ed0;
static u64 s_dat_71052b6ee0[2];
void *FUN_71003b0250() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6ed0))) goto done;
    s_dat_71052b6ee0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
    s_dat_71052b6ee0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
    __cxa_guard_release(&s_guard_71052b6ed0);
done:
    return s_dat_71052b6ee0;
}

// FUN_71003b02c0 — singleton: copy PTR_ConstantZero_71052a7a88 → DAT_71052b6ec0
static u64 s_guard_71052b6eb0;
static u64 s_dat_71052b6ec0[2];
void *FUN_71003b02c0() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6eb0))) goto done;
    s_dat_71052b6ec0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
    s_dat_71052b6ec0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
    __cxa_guard_release(&s_guard_71052b6eb0);
done:
    return s_dat_71052b6ec0;
}

// FUN_71003b18a0 — singleton: zero-init 8 u64 values at DAT_71052b7040–0x7078
static u64 s_guard_71052b7030;
static u64 s_dat_71052b7040[8];
u64 *FUN_71003b18a0() {
    if (!(__cxa_guard_acquire(&s_guard_71052b7030))) goto done;
    s_dat_71052b7040[7] = 0;
    s_dat_71052b7040[6] = 0;
    s_dat_71052b7040[5] = 0;
    s_dat_71052b7040[4] = 0;
    s_dat_71052b7040[3] = 0;
    s_dat_71052b7040[2] = 0;
    s_dat_71052b7040[1] = 0;
    s_dat_71052b7040[0] = 0;
    __cxa_guard_release(&s_guard_71052b7030);
done:
    return s_dat_71052b7040;
}

// FUN_71003b1c10 — singleton: copy PTR_ConstantZero_71052a7a80 → DAT_71052b7020
static u64 s_guard_71052b7010;
static u64 s_dat_71052b7020[2];
void *FUN_71003b1c10() {
    if (!(__cxa_guard_acquire(&s_guard_71052b7010))) goto done;
    s_dat_71052b7020[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b7020[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b7010);
done:
    return s_dat_71052b7020;
}

// FUN_71003b1ce0 — singleton: copy PTR_ConstantZero_71052a7a80 → DAT_71052b7000
static u64 s_guard_71052b6ff0;
static u64 s_dat_71052b7000[2];
void *FUN_71003b1ce0() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6ff0))) goto done;
    s_dat_71052b7000[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b7000[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b6ff0);
done:
    return s_dat_71052b7000;
}

// FUN_71003b1d50 — singleton: copy PTR_ConstantZero_71052a7a80 → DAT_71052b6fe0
static u64 s_guard_71052b6fd0;
static u64 s_dat_71052b6fe0[2];
void *FUN_71003b1d50() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6fd0))) goto done;
    s_dat_71052b6fe0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b6fe0[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b6fd0);
done:
    return s_dat_71052b6fe0;
}

// FUN_71003b1f70 — singleton: copy PTR_ConstantZero_71052a7a80 → DAT_71052b6fc0
static u64 s_guard_71052b6fb0;
static u64 s_dat_71052b6fc0[2];
void *FUN_71003b1f70() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6fb0))) goto done;
    s_dat_71052b6fc0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b6fc0[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b6fb0);
done:
    return s_dat_71052b6fc0;
}

// FUN_71003b21a0 — singleton returning 16-byte value from PTR_ConstantZero_71052a7a80
static u64 s_guard_71052b6f90;
static u64 s_dat_71052b6fa0[2];
u64 FUN_71003b21a0() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6f90))) goto done;
    s_dat_71052b6fa0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b6fa0[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b6f90);
done:
    return s_dat_71052b6fa0[0]; // low 64 bits (high stored separately)
}

// FUN_71003b2260 — singleton: copy PTR_ConstantZero_71052a7a80 → DAT_71052b6f80
static u64 s_guard_71052b6f70;
static u64 s_dat_71052b6f80[2];
void *FUN_71003b2260() {
    if (!(__cxa_guard_acquire(&s_guard_71052b6f70))) goto done;
    s_dat_71052b6f80[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
    s_dat_71052b6f80[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
    __cxa_guard_release(&s_guard_71052b6f70);
done:
    return s_dat_71052b6f80;
}

// FUN_710033ba50 — fighter module table lookup (0x5e modules, 0x50-byte stride each)
// Returns ptr to module vtable entry within main struct at *DAT_71052b60e8
// Falls back to +0x6e8 if module slot is null or unrecognized
extern long *DAT_71052b60e8;
extern u8 DAT_00001038, DAT_00001088, DAT_000010d8, DAT_00001128, DAT_00001178;
extern u8 DAT_000011c8, DAT_00001218, DAT_00001268, DAT_000012b8, DAT_00001308;
extern u8 DAT_00001358, DAT_000013a8, DAT_000013f8, DAT_00001448, DAT_00001498;
extern u8 DAT_000014e8, DAT_00001538, DAT_00001588, DAT_000015d8, DAT_00001628;
extern u8 DAT_00001678, DAT_000016c8, DAT_00001718, DAT_00001768, DAT_000017b8;
extern u8 DAT_00001808, DAT_00001858, DAT_000018a8, DAT_000018f8, DAT_00001948;
extern u8 DAT_00001998, DAT_000019e8, DAT_00001a38, DAT_00001a88, DAT_00001ad8;
extern u8 DAT_00001b28, DAT_00001b78, DAT_00001bc8, DAT_00001c18, DAT_00001c68;
extern u8 DAT_00001cb8, DAT_00001d08, DAT_00001d58, DAT_00001da8, DAT_00001df8;
extern u8 DAT_00001e48, DAT_00001e98, DAT_00001ee8, DAT_00001f38, DAT_00001f88;
extern u8 DAT_00001fd8, DAT_00002028, DAT_00002078, DAT_000020c8, DAT_00002118;
extern u8 DAT_00002168, DAT_000021b8, DAT_00002208, DAT_00002258, DAT_000022a8;
extern u8 DAT_000022f8, DAT_00002348, DAT_00002398, DAT_000023e8, DAT_00002438;

long FUN_710033ba50(u32 param_1) {
    // Offsets into the main struct for each module type
    static const long module_offsets[] = {
        0x728, 0x778, 0x7c8, 0x818, 0x868, 0x8b8, 0x908, 0x958, 0x9a8, 0x9f8,
        0xa48, 0xa98, 0xae8, 0xb38, 0xb88, 0xbd8, 0xc28, 0xc78, 0xcc8, 0xd18,
        0xd68, 0xdb8, 0xe08, 0xe58, 0xea8, 0xef8, 0xf48, 0xf98, 0xfe8,
    };
    long base = *DAT_71052b60e8;
    long slot = 0;

    // First 0x1d entries use fixed-offset table
    if (param_1 < 0x1d) {
        slot = *(long *)(base + module_offsets[param_1]);
        if (slot == 0 || param_1 <= 1) {
            if (slot != 0) return slot;
            goto fallback;
        }
        if (slot != 0) return slot;
        goto fallback;
    }

    // Entries 0x1d–0x5d use address-arithmetic offsets
    if (param_1 <= 0x5d) {
        static const u32 late_offsets[] = {
            0x1038, 0x1088, 0x10d8, 0x1128, 0x1178, 0x11c8, 0x1218, 0x1268,
            0x12b8, 0x1308, 0x1358, 0x13a8, 0x13f8, 0x1448, 0x1498, 0x14e8,
            0x1538, 0x1588, 0x15d8, 0x1628, 0x1678, 0x16c8, 0x1718, 0x1768,
            0x17b8, 0x1808, 0x1858, 0x18a8, 0x18f8, 0x1948, 0x1998, 0x19e8,
            0x1a38, 0x1a88, 0x1ad8, 0x1b28, 0x1b78, 0x1bc8, 0x1c18, 0x1c68,
            0x1cb8, 0x1d08, 0x1d58, 0x1da8, 0x1df8, 0x1e48, 0x1e98, 0x1ee8,
            0x1f38, 0x1f88, 0x1fd8, 0x2028, 0x2078, 0x20c8, 0x2118, 0x2168,
            0x21b8, 0x2208, 0x2258, 0x22a8, 0x22f8, 0x2348, 0x2398, 0x23e8,
            0x2438,
        };
        slot = *(long *)(base + late_offsets[param_1 - 0x1d]);
        if (slot != 0) return slot;
    }

fallback:
    return base + 0x6e8;
}

// FUN_7100358c20 — fighter state eligibility check
// Returns 1 if fighter can transition based on its current state_type and flag bits
u32 FUN_7100358c20(long param_1, u32 param_2) {
    u32 flags    = *(u32 *)(param_1 + 0x58);
    u32 state_type = *(u32 *)(param_1 + 0x28);
    u8  state_flags = *(u8  *)(param_1 + 0x68);

    // Bit 12 of flags: use alternate check
    if (flags >> 0xc & 1) {
        if (param_2 & 1) return (flags & 0x400) == 0 ? 1 : 0;
        return 0;
    }

    switch (state_type) {
    case 5:
        return state_flags & 1 ? 0 : 1;
    case 0xc: goto fallthrough_c;
    case 0x1c: return (state_flags & 1) ? 0 : 1;
    case 0x22: return ((state_flags >> 2) & 1) ? 1 : 0;
    case 0x25: return (flags >> 4 & 1) ? 0 : 1;
    case 0x27: return ((state_flags >> 2) & 1) ? 0 : 1;
    case 0x29: return (state_flags & 1) ? 0 : 1;
    case 0x2b: case 0x30: case 0x46: return ((state_flags >> 3) & 1) ? param_2 & 1 : 1;
    case 0x2d: return ((state_flags >> 2) & 1) ? param_2 & 1 : 1;
    case 0x31: return ((state_flags >> 1) & 1) ? 0 : 1;
    case 0x37: return ((state_flags >> 3) & 1) ? 0 : 1;
    case 0x38: return ((state_flags >> 2) & 1) ? 1 : 0;
    case 0x3a: return ((state_flags >> 2) & 1) ? 0 : 1;
    case 0x40: {
        if ((state_flags >> 1) & 1) return 1;
        if (!((flags >> 0xd) & 1) && *(s32 *)(param_1 + 0x74) != 0x10) {
            if (*(s16 *)(param_1 + 0xcc) != 0) return 1;
        }
        goto fallthrough_c;
    }
    case 0x4b: return ((state_flags >> 1) & 1) ? param_2 & 1 : 1;
    case 0x52:
        if ((flags >> 4 & 1) && !(state_flags & 1)) return 0;
        break;
    case 0x53:
        if ((s8)state_flags < 0) return 1;
        goto fallthrough_c;
    case 0x54: return ((state_flags >> 3) & 1) ? param_2 & 1 : 1;
    case 0x56: case 0x57: return (flags >> 4 & 1) ? 0 : 1;
    case 0x5a:
        if ((state_flags >> 1) & 1) {
            if (param_2 & 1) return (flags & 0x400) == 0 ? 1 : 0;
            return 0;
        }
        break;
    case 0x5c: {
        u32 bit = (state_flags >> 2) & 1;
        if (!bit) {
            if (param_2 & 1) return (flags & 0x400) == 0 ? 1 : 0;
            return 0;
        }
        goto fallthrough_c;
    }
    default: break;
    }
    return 1;
fallthrough_c:
    return param_2 & 1;
}

} // namespace lua_bind
} // namespace app
