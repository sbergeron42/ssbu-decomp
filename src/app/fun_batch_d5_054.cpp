#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-054
// Pool-d worker: 0x71039* medium-size functions (jemalloc/arena, 80-256B)
// Rewritten: pool-e — meaningful param names

extern "C" {
    __attribute__((noreturn)) void abort(void);
    int pthread_mutex_unlock(void *mutex);
}

// ---- External declarations ----

extern void   FUN_71039292b0(int, void *);
extern u8     FUN_7103929ac0(void);
extern s32    FUN_71039293e0(u64, s64);
extern void   FUN_710392ba50(u64, void *);
extern void   FUN_710392bab0(u64, u64, u64);
extern void   FUN_710392bc80(u64);
extern void   FUN_710392c0f0(u64);
extern void   FUN_7103929830(u64, u32);
extern u64    FUN_7103930160(u64);
extern void   FUN_7103930970(u64, u64);
extern void   FUN_71039316d0(u64, u32);
extern u64    FUN_7103932890(u64);
extern u64    FUN_7103932870(u64);
extern void   FUN_7103934770(u64, void *);
extern void   FUN_71039347d0(u64, u64, u64);
extern void   FUN_71039348c0(u64);
extern u64    FUN_7103936cb0(u64);
extern u64    FUN_71039395a0(u64);
extern u64    FUN_7103939580(u64);
extern void   FUN_710393ede0(u64, u64);
extern void   FUN_710393dc80(u64, u32);
extern u32    FUN_710393ea90(u64, u64, u64, u64, u64, int);
extern void   FUN_7103945810(s64);
extern void   FUN_7103944130(s64, u64, int);
extern u64    FUN_7103946fc0(u64);
extern void   FUN_7103947020(u64, void *);
extern void   FUN_7103951d40(u64, u32);
extern void   FUN_7103952a90(u64, void *);
extern void   FUN_7103953d80(u64, u64, u64);
extern void   FUN_7103952e10(u64);
extern u64    FUN_71039526e0(u64);
extern void   FUN_7103953b10(u64, u64, u64, int);
extern void   FUN_7103953c10(u64, u64, u64);
extern u64    FUN_7103943c00(void);
extern void   FUN_7103945900(u64, u64, u64, u64);
extern void   FUN_710395a780(u64, u64, u64, u32, u64, int, int, int);
extern void   FUN_710395bd70(u64, void *);
extern void   FUN_710395bdd0(u64, u64, u64);
extern void   FUN_710395bfa0(u64);
extern void   FUN_710395bd00(u64, u32);
extern void   FUN_710395ee40(u8 *);
extern void   FUN_710395ed30(u8 *);

extern void *DAT_7106dd3f80;
extern void *DAT_7106dd3f60;

// Forward declarations
void FUN_710392bc30(u64 arena, u64 bin, u64 slab, u8 flag);
void FUN_710395bf50(u64 arena, u64 bin, u64 slab, u8 flag);
extern void FUN_710395f620(u8 *state);

// ---- 0x71039* jemalloc medium functions ----

// 0x7103929a70 — init mutex + call + unlock (80B)
u8 FUN_7103929a70(void) {
    FUN_71039292b0(0, &DAT_7106dd3f80);
    u8 result = FUN_7103929ac0();
    FUN_71039293e0(0, (s64)&DAT_7106dd3f80);
    return result & 1;
}

// 0x710392ba00 — stack-alloc call + second call (80B)
void FUN_710392ba00(u64 arena, u64 config) {
    u8 buf[384];
    u64 saved_config = config;
    u64 result;
    FUN_710392ba50(arena, buf);
    result = *(u64 *)buf;
    FUN_710392bab0(arena, result, saved_config);
}

// 0x710392bbe0 — call bc30 + mask (80B)
void FUN_710392bbe0(u64 arena, u64 bin, u64 slab, u8 flag) {
    u64 result;
    FUN_710392bc30(arena, bin, slab, flag & 1);
    result = *(u64 *)&slab;
    FUN_710392bc80(result);
}

// 0x710392bc30 — conditional set mode (80B)
void FUN_710392bc30(u64 arena, u64 bin, u64 slab, u8 flag) {
    u32 mode = 0;
    if ((flag & 1) == 0) {
        mode = 2;
    }
    FUN_7103929830(slab, mode);
}

// 0x710392ea70 — call bc30 + c0f0 (80B)
void FUN_710392ea70(u64 arena, u64 bin, u64 slab, u8 flag) {
    u64 result;
    FUN_710392bc30(arena, bin, slab, flag & 1);
    result = *(u64 *)&slab;
    FUN_710392c0f0(result);
}

// 0x7103930920 — shift/pass sub-result (80B)
void FUN_7103930920(u64 arena, u64 dst, u64 src) {
    u64 raw = FUN_7103930160(src);
    FUN_7103930970(dst, raw >> 0x10);
}

// 0x7103931640 — conditional set mode (80B)
void FUN_7103931640(u64 arena, u64 bin, u64 slab, u8 flag) {
    u32 mode = 0;
    if ((flag & 1) == 0) {
        mode = 2;
    }
    FUN_71039316d0(slab, mode);
}

// 0x71039327d0 — three-way compare (80B)
s32 FUN_71039327d0(u64 a, u64 b) {
    u64 key_a = FUN_7103932890(a);
    u64 key_b = FUN_7103932890(b);
    return (u32)(key_b < key_a) - (u32)(key_a < key_b);
}

// 0x7103932820 — three-way compare (80B)
s32 FUN_7103932820(u64 a, u64 b) {
    u64 key_a = FUN_7103932870(a);
    u64 key_b = FUN_7103932870(b);
    return (u32)(key_b < key_a) - (u32)(key_a < key_b);
}

// 0x7103934650 — stack-alloc call + second call (80B)
void FUN_7103934650(u64 arena, u64 config) {
    u8 buf[384];
    u64 saved_config = config;
    u64 result;
    FUN_7103934770(arena, buf);
    result = *(u64 *)buf;
    FUN_71039347d0(arena, result, saved_config);
}

// 0x7103934870 — call 1640 + mask (80B)
void FUN_7103934870(u64 arena, u64 bin, u64 slab, u8 flag) {
    FUN_7103931640(arena, bin, slab, flag & 1);
    FUN_71039348c0(slab);
}

// 0x7103936c20 — three-way compare (80B)
s32 FUN_7103936c20(u64 a, u64 b) {
    u64 key_a = FUN_7103936cb0(a);
    u64 key_b = FUN_7103936cb0(b);
    return (u32)(key_b < key_a) - (u32)(key_a < key_b);
}

// 0x71039394e0 — three-way compare (80B)
s32 FUN_71039394e0(u64 a, u64 b) {
    u64 key_a = FUN_71039395a0(a);
    u64 key_b = FUN_71039395a0(b);
    return (u32)(key_b < key_a) - (u32)(key_a < key_b);
}

// 0x7103939530 — three-way compare (80B)
s32 FUN_7103939530(u64 a, u64 b) {
    u64 key_a = FUN_7103939580(a);
    u64 key_b = FUN_7103939580(b);
    return (u32)(key_b < key_a) - (u32)(key_a < key_b);
}

// 0x71039401e0 — call two params, return 0 (80B)
u64 FUN_71039401e0(u64 unused1, u64 src, u64 unused3, u64 dst) {
    FUN_710393ede0(src, dst);
    return 0;
}

// 0x71039409d0 — conditional set mode (80B)
void FUN_71039409d0(u64 arena, u64 bin, u64 slab, u8 flag) {
    u32 mode = 0;
    if ((flag & 1) == 0) {
        mode = 2;
    }
    FUN_710393dc80(slab, mode);
}

// 0x7103943b50 — call with 6 args adding 0 (80B)
u32 FUN_7103943b50(u64 arena, u64 bin, u64 slab, u64 extent, u64 npages) {
    u32 result = FUN_710393ea90(arena, bin, slab, extent, npages, 0);
    return result & 1;
}

// 0x71039458b0 — call + set flags (80B)
u64 FUN_71039458b0(s64 self, u64 value) {
    FUN_7103945810(self);
    FUN_7103944130(self + 8, value, 3);
    return 0;
}

// 0x7103946f70 — call + mutex_unlock on globals (80B)
s32 FUN_7103946f70(u64 tsd) {
    u64 arena = FUN_7103946fc0(tsd);
    FUN_7103947020(arena, &DAT_7106dd3f80);
    return pthread_mutex_unlock((void *)&DAT_7106dd3f60);
}

// 0x7103952dc0 — conditional set mode (80B)
void FUN_7103952dc0(u64 arena, u64 bin, u64 slab, u8 flag) {
    u32 mode = 0;
    if ((flag & 1) == 0) {
        mode = 2;
    }
    FUN_7103951d40(slab, mode);
}

// 0x7103953a60 — stack-alloc call + second call (80B)
void FUN_7103953a60(u64 arena, u64 config) {
    u8 buf[384];
    u64 saved_config = config;
    u64 result;
    FUN_7103952a90(arena, buf);
    result = *(u64 *)buf;
    FUN_7103953d80(arena, result, saved_config);
}

// 0x7103953e20 — call 52dc + mask (80B)
void FUN_7103953e20(u64 arena, u64 bin, u64 slab, u8 flag) {
    FUN_7103952dc0(arena, bin, slab, flag & 1);
    FUN_7103952e10(slab);
}

// 0x7103953f60 — two-call with sub-result (80B)
void FUN_7103953f60(u64 arena, u64 extent) {
    u64 key = FUN_71039526e0(extent);
    FUN_7103953b10(arena, key, extent, 1);
}

// 0x7103953fb0 — two-call with sub-result (80B)
void FUN_7103953fb0(u64 arena, u64 extent) {
    u64 key = FUN_71039526e0(extent);
    FUN_7103953c10(arena, key, extent);
}

// 0x7103958760 — call 3c00 + pass shifted (80B)
void FUN_7103958760(u64 arena, u64 bin, s64 count) {
    u64 base = FUN_7103943c00();
    FUN_7103945900(arena, base, (u64)(count << 3), 0x40);
}

// 0x710395a6a0 — 5-arg wrapper adding 0,0,0 (80B)
void FUN_710395a6a0(u64 arena, u64 bin, u64 slab, u32 npages, u64 extent) {
    FUN_710395a780(arena, bin, slab, npages, extent, 0, 0, 0);
}

// 0x710395b640 — stack-alloc call + second call (80B)
void FUN_710395b640(u64 arena, u64 config) {
    u8 buf[384];
    u64 saved_config = config;
    u64 result;
    FUN_710395bd70(arena, buf);
    result = *(u64 *)buf;
    FUN_710395bdd0(arena, result, saved_config);
}

// 0x710395bf00 — call bf50 + mask (80B)
void FUN_710395bf00(u64 arena, u64 bin, u64 slab, u8 flag) {
    FUN_710395bf50(arena, bin, slab, flag & 1);
    FUN_710395bfa0(slab);
}

// 0x710395bf50 — conditional set mode (80B)
void FUN_710395bf50(u64 arena, u64 bin, u64 slab, u8 flag) {
    u32 mode = 0;
    if ((flag & 1) == 0) {
        mode = 2;
    }
    FUN_710395bd00(slab, mode);
}

// 0x710395f590 — state machine with switch (144B)
void FUN_710395f590(u8 *state) {
    switch (*state) {
    case 2:
    case 4:
        FUN_710395ee40(state);
        // fallthrough
    case 0:
    case 1:
        FUN_710395f620(state);
        *state = 3;
        FUN_710395ed30(state);
        break;
    case 3:
        break;
    case 5:
        break;
    default:
        abort();
    }
}
