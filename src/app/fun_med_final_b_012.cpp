// fun_med_final_b_012.cpp — pool-b MEDIUM batch 012
// Address range: 0x71003f7fa0 – 0x7100489c20
// Scene constructors, vtable dispatchers, list accumulators, linked-list insert
#include "types.h"

// ── forward declarations ──────────────────────────────────────────────────

extern "C" int  __cxa_guard_acquire(u64 *guard);
extern "C" void __cxa_guard_release(u64 *guard);

extern float DAT_7104471ef8; // float threshold (~epsilon)

extern void *PTR_PTR_LAB_7104f75410;
extern void *PTR_PTR_LAB_71050a32c0;
extern void *PTR_PTR_LAB_71050b5c70;
extern void *PTR_PTR_LAB_71050b5d48;
extern void *PTR_PTR_LAB_71050b5e20;
extern void *PTR_PTR_LAB_71050b5ef8;
extern void *PTR_PTR_LAB_71050b6290;
extern void *PTR_PTR_LAB_71050b68a0;
extern void *PTR_PTR_LAB_71050b6898;
extern void *PTR_PTR_LAB_71050b9608;
extern void *PTR_PTR_LAB_71050b9de8;

extern void *DAT_71050b33c8;

extern "C" void *nn_os_GetCurrentThread();

extern "C" void FUN_710161e280(u64 param_1, u64 param_2, u32 *out);
extern "C" void FUN_7100489b00(long lVar3, long param_2, void *ev_desc, u8 flag);
extern "C" void *FUN_7100489810(); // returns pointer to 16-byte value

// ── 16-byte return type used by several vtable dispatchers ────────────────
typedef struct { u64 lo; u64 hi; } v128_t;

// Helper: packed float pair stored as u64 (lo=float[0], hi=float[1])
static inline u64 pack_f2(float lo, float hi) {
    u64 r;
    __builtin_memcpy(&r, &lo, 4);
    __builtin_memcpy((u8 *)&r + 4, &hi, 4);
    return r;
}
static inline float unpack_f_lo(u64 v) { float f; __builtin_memcpy(&f, &v, 4); return f; }
static inline float unpack_f_hi(u64 v) { float f; __builtin_memcpy(&f, (u8 *)&v + 4, 4); return f; }

// ─────────────────────────────────────────────────────────────────────────
// FUN_71003f7fa0 — vtable +0x50; return |result| < threshold (axis-X near-zero)
// FUN_71003f8020 — vtable +0x60; same check on axis-Y
// ─────────────────────────────────────────────────────────────────────────

bool FUN_71003f7fa0(long *param_1) {
    float fVar1 = (float)(*(long (**)(void))(*param_1 + 0x50))();
    return __builtin_fabsf(fVar1) < DAT_7104471ef8;
}

bool FUN_71003f8020(long *param_1) {
    float fVar1 = (float)(*(long (**)(void))(*param_1 + 0x60))();
    return __builtin_fabsf(fVar1) < DAT_7104471ef8;
}

// FUN_71003f8730 — vtable +0x260; invert low bit
u32 FUN_71003f8730(long *param_1) {
    u32 uVar1 = (*(u32 (**)(void))(*param_1 + 0x260))();
    return ~uVar1 & 1;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7100405d60 — status kind bitmask check (values 7–29 → bit 0 of 0x500003)
// FUN_7100405db0 — status kind == 0x10 or in [1,6]
// ─────────────────────────────────────────────────────────────────────────

u32 FUN_7100405d60(long *param_1) {
    int iVar1 = (*(int (**)(void))(*param_1 + 0x28))();
    if ((u32)(iVar1 - 7) < 0x17u) {
        return 0x500003u >> ((u64)(iVar1 - 7) & 0x1f) & 1;
    }
    return 0;
}

bool FUN_7100405db0(long *param_1) {
    int iVar1 = (*(int (**)(void))(*param_1 + 0x28))();
    return iVar1 == 0x10 || (u32)(iVar1 - 1) < 6u;
}

// FUN_71004074b0 — Status module (param_2+0x40) vtable +0x168 == 2
bool FUN_71004074b0(u64 /*unused*/, long param_2) {
    int iVar1 = (*(int (**)(void))(*(long *)(param_2 + 0x40) + 0x168))();
    return iVar1 == 2;
}

// ─────────────────────────────────────────────────────────────────────────
// Scene constructor stubs
// Each: clear/set name + vtable, one-time __cxa_guard empty init, zero two fields
// Pattern: DAT[+0]=null, DAT[+8]=name, guard_init(), DAT[+0x10/+0x18]=0, DAT[+0x08]=vtbl
// ─────────────────────────────────────────────────────────────────────────

// FUN_7100407e10 — "IngameCallSequenceScene"
static u64 s_guard_71052b8330;
static u64 s_dat_71052b8308;   // +0
static const char *s_dat_71052b8310;  // +8 (name)
static void *s_dat_71052b8318;  // vtable ptr
static u64 s_dat_71052b8320;   // +0x10
static u64 s_dat_71052b8328;   // +0x18
void FUN_7100407e10() {
    s_dat_71052b8308 = 0;
    s_dat_71052b8310 = "IngameCallSequenceScene";
    int iVar1;
    if (((s_guard_71052b8330 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b8330), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71052b8330);
    }
    s_dat_71052b8320 = 0;
    s_dat_71052b8328 = 0;
    s_dat_71052b8318 = &PTR_PTR_LAB_7104f75410;
}

// FUN_710041dd90 — "MeleeRuleScene"
static u64 s_guard_7105323960;
static u64 s_dat_7105323938;
static const char *s_dat_7105323940;
static void *s_dat_7105323948;
static u64 s_dat_7105323950;
static u64 s_dat_7105323958;
void FUN_710041dd90() {
    s_dat_7105323938 = 0;
    s_dat_7105323940 = "MeleeRuleScene";
    int iVar1;
    if (((s_guard_7105323960 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_7105323960), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_7105323960);
    }
    s_dat_7105323950 = 0;
    s_dat_7105323958 = 0;
    s_dat_7105323948 = &PTR_PTR_LAB_71050a32c0;
}

// FUN_7100420ed0 — "CollectionAnniversaryScene"
static u64 s_guard_7105327448;
static u64 s_dat_7105327420;
static const char *s_dat_7105327428;
static void *s_dat_7105327430;
static u64 s_dat_7105327438;
static u64 s_dat_7105327440;
void FUN_7100420ed0() {
    s_dat_7105327420 = 0;
    s_dat_7105327428 = "CollectionAnniversaryScene";
    int iVar1;
    if (((s_guard_7105327448 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_7105327448), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_7105327448);
    }
    s_dat_7105327438 = 0;
    s_dat_7105327440 = 0;
    s_dat_7105327430 = &PTR_PTR_LAB_71050b5c70;
}

// FUN_7100420f40 — "CollectionCardScene"
static u64 s_guard_7105327478;
static u64 s_dat_7105327450;
static const char *s_dat_7105327458;
static void *s_dat_7105327460;
static u64 s_dat_7105327468;
static u64 s_dat_7105327470;
void FUN_7100420f40() {
    s_dat_7105327450 = 0;
    s_dat_7105327458 = "CollectionCardScene";
    int iVar1;
    if (((s_guard_7105327478 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_7105327478), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_7105327478);
    }
    s_dat_7105327468 = 0;
    s_dat_7105327470 = 0;
    s_dat_7105327460 = &PTR_PTR_LAB_71050b5d48;
}

// FUN_7100420fb0 — "CollectionCountScene"
static u64 s_guard_71053274a8;
static u64 s_dat_7105327480;
static const char *s_dat_7105327488;
static void *s_dat_7105327490;
static u64 s_dat_7105327498;
static u64 s_dat_71053274a0;
void FUN_7100420fb0() {
    s_dat_7105327480 = 0;
    s_dat_7105327488 = "CollectionCountScene";
    int iVar1;
    if (((s_guard_71053274a8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71053274a8), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71053274a8);
    }
    s_dat_7105327498 = 0;
    s_dat_71053274a0 = 0;
    s_dat_7105327490 = &PTR_PTR_LAB_71050b5e20;
}

// FUN_7100421020 — "CollectionFighterScene"
static u64 s_guard_71053274d8;
static u64 s_dat_71053274b0;
static const char *s_dat_71053274b8;
static void *s_dat_71053274c0;
static u64 s_dat_71053274c8;
static u64 s_dat_71053274d0;
void FUN_7100421020() {
    s_dat_71053274b0 = 0;
    s_dat_71053274b8 = "CollectionFighterScene";
    int iVar1;
    if (((s_guard_71053274d8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71053274d8), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71053274d8);
    }
    s_dat_71053274c8 = 0;
    s_dat_71053274d0 = 0;
    s_dat_71053274c0 = &PTR_PTR_LAB_71050b5ef8;
}

// FUN_7100421210 — "CollectionPlayingScene"
static u64 s_guard_71053275a0;
static u64 s_dat_7105327578;
static const char *s_dat_7105327580;
static void *s_dat_7105327588;
static u64 s_dat_7105327590;
static u64 s_dat_7105327598;
void FUN_7100421210() {
    s_dat_7105327578 = 0;
    s_dat_7105327580 = "CollectionPlayingScene";
    int iVar1;
    if (((s_guard_71053275a0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71053275a0), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71053275a0);
    }
    s_dat_7105327590 = 0;
    s_dat_7105327598 = 0;
    s_dat_7105327588 = &PTR_PTR_LAB_71050b6290;
}

// FUN_7100421d10 — "HomeRunContestScene" (guard at DAT_71053277b8, no null at start)
static u64 s_guard_71053277b8;
static const char *s_dat_71053278c8;
static void *s_dat_71053278d0;
static u64 s_dat_71053278d8;
static u64 s_dat_71053278e0;
void FUN_7100421d10() {
    s_dat_71053278c8 = "HomeRunContestScene";
    int iVar1;
    if (((s_guard_71053277b8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71053277b8), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71053277b8);
    }
    s_dat_71053278d8 = 0;
    s_dat_71053278e0 = 0;
    s_dat_71053278d0 = &PTR_PTR_LAB_71050b68a0;
}

// FUN_7100422740 — "MeleeScene" (guard at DAT_71053277b0)
static u64 s_guard_71053277b0;
static u64 s_dat_7105327b80;
static const char *s_dat_7105327b88;
static void *s_dat_7105327b90;
static u64 s_dat_7105327b98;
static u64 s_dat_7105327ba0;
void FUN_7100422740() {
    s_dat_7105327b80 = 0;
    s_dat_7105327b88 = "MeleeScene";
    int iVar1;
    if (((s_guard_71053277b0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71053277b0), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71053277b0);
    }
    s_dat_7105327b98 = 0;
    s_dat_7105327ba0 = 0;
    s_dat_7105327b90 = &PTR_PTR_LAB_71050b6898;
}

// FUN_7100428030 — "StaffRollScene"
static u64 s_guard_7105328d70;
static u64 s_dat_7105328d48;
static const char *s_dat_7105328d50;
static void *s_dat_7105328d58;
static u64 s_dat_7105328d60;
static u64 s_dat_7105328d68;
void FUN_7100428030() {
    s_dat_7105328d48 = 0;
    s_dat_7105328d50 = "StaffRollScene";
    int iVar1;
    if (((s_guard_7105328d70 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_7105328d70), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_7105328d70);
    }
    s_dat_7105328d60 = 0;
    s_dat_7105328d68 = 0;
    s_dat_7105328d58 = &PTR_PTR_LAB_71050b9608;
}

// FUN_7100428630 — "VideoEditScene"
static u64 s_guard_7105328f30;
static u64 s_dat_7105328f08;
static const char *s_dat_7105328f10;
static void *s_dat_7105328f18;
static u64 s_dat_7105328f20;
static u64 s_dat_7105328f28;
void FUN_7100428630() {
    s_dat_7105328f08 = 0;
    s_dat_7105328f10 = "VideoEditScene";
    int iVar1;
    if (((s_guard_7105328f30 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_7105328f30), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_7105328f30);
    }
    s_dat_7105328f20 = 0;
    s_dat_7105328f28 = 0;
    s_dat_7105328f18 = &PTR_PTR_LAB_71050b9de8;
}

// ─────────────────────────────────────────────────────────────────────────
// Miscellaneous utilities
// ─────────────────────────────────────────────────────────────────────────

// FUN_710043ff00 — store current OS thread handle to global
static void *s_dat_7105331f18;
void FUN_710043ff00() {
    s_dat_7105331f18 = nn_os_GetCurrentThread();
}

// FUN_71004523f8 — vtable +0x248; invert low bit of result
u32 FUN_71004523f8(long *param_1) {
    u32 uVar1 = (*(u32 (**)(void))(*param_1 + 0x248))();
    return (uVar1 ^ 1) & 1;
}

// FUN_710045bf30 — index into list via param_2, vtable +0x20, return 16 bytes
v128_t FUN_710045bf30(long param_1, int param_2) {
    v128_t *pauVar1 = (*(v128_t *(**)(void))(*(long *)(*(long *)(param_1 + 0x70) + (long)param_2 * 8 + 0x30) + 0x20))();
    return *pauVar1;
}

// FUN_7100460760 — 7-case playback/BGM state setter
// Writes a mode enum to *(obj+0x510), and for cases 1/2/6 also sets flag bit in *(obj+0x5d8)
void FUN_7100460760(long param_1, u32 param_2) {
    *(u32 *)(param_1 + 0x40) = param_2;
    long lVar2;
    u32 uVar3;
    switch (param_2) {
    case 0:
        *(u32 *)(*(long *)(param_1 + 0x28) + 0x510) = 4;
        break;
    case 1:
        *(u32 *)(*(long *)(param_1 + 0x28) + 0x510) = 0;
        goto LAB_7100460830;
    case 2:
        lVar2 = *(long *)(param_1 + 0x28);
        uVar3 = 2;
        goto LAB_710046082c;
    case 3: {
        long lVar1 = (*(long (**)(void))(*(long *)(param_1 + 0x20) + 0x38 + 0x60))();
        long lVar2b = (*(long (**)(void))(*(long *)(param_1 + 0x20) + 0x38 + 0x90))();
        if (*(float *)(lVar1 + 4) < *(float *)(lVar2b + 4)) {
            *(u32 *)(*(long *)(param_1 + 0x28) + 0x510) = 0;
        }
        break;
    }
    case 4:
        *(u32 *)(*(long *)(param_1 + 0x28) + 0x510) = 2;
        break;
    case 5:
        *(u32 *)(*(long *)(param_1 + 0x28) + 0x510) = 1;
        break;
    case 6:
        lVar2 = *(long *)(param_1 + 0x28);
        uVar3 = 3;
LAB_710046082c:
        *(u32 *)(lVar2 + 0x510) = uVar3;
LAB_7100460830:
        *(u32 *)(*(long *)(param_1 + 0x28) + 0x5d8) |= 2;
        break;
    }
}

// FUN_71004625d4 — vtable +0x408 one-liner
void FUN_71004625d4(long *param_1) {
    (*(void (**)(void))(*param_1 + 0x408))();
}

// FUN_710046bb08 — vtable +0xd8 with 2 bytes from param_3; result → 1 or 2
u32 FUN_710046bb08(u64 /*unused*/, long *param_2, long param_3) {
    u64 uVar1 = (*(u64 (**)(long *, u8, u8))(*param_2 + 0xd8))(param_2,
                    *(u8 *)(param_3 + 0x32), *(u8 *)(param_3 + 0x35));
    return (uVar1 & 1) ? 1u : 2u;
}

// FUN_7100471be0 — array-of-structs (stride 0x20) lookup; call FUN_710161e280 with field+0x228
u32 FUN_7100471be0(long param_1, u64 param_2, int param_3) {
    u32 local_14 = 0;
    FUN_710161e280(*(u64 *)(*(long *)(*(long *)(param_1 + 0x18) + (long)param_3 * 0x20 + 8) + 0x228),
                   param_2, &local_14);
    return local_14;
}

// FUN_7100474428 — uses in_x11/in_x12 as implicit args (non-standard calling convention)
// Index into array at in_x11+in_x12*0x20, deref +0xd0, vtable +0x60, return 16 bytes
v128_t FUN_7100474428(long in_x11, long in_x12) {
    v128_t *pauVar1 = (*(v128_t *(**)(void))(*(long *)(*(long *)(in_x11 + in_x12 * 0x20 + 8) + 0xd0) + 0x60))();
    return *pauVar1;
}

// FUN_71004794b0 — vtable +0x48 on module at +0x1c0; store param_2 at +0x1b8
void FUN_71004794b0(long param_1, u32 param_2) {
    long *mod = *(long **)(param_1 + 0x1c0);
    (*(void (**)(long *, u32, long, u64))(*mod + 0x48))(mod, param_2, param_1 + 0x10, *(u64 *)(param_1 + 8));
    *(u32 *)(param_1 + 0x1b8) = param_2;
}

// FUN_7100479f70 — iterate list backward; call vtable +0x10 on active, unpaused nodes
// param_2 == 0xffffffff → all nodes; else only those whose category-mask matches param_2
void FUN_7100479f70(long param_1, u32 param_2) {
    if (*(s8 *)(param_1 + 0x1bc) != 0) return;
    int iVar1 = *(int *)(param_1 + 0x20);
    if (param_2 == 0xffffffffu) {
        if (iVar1 > 0) {
            long lVar3 = (long)iVar1 + 1;
            long *plVar4 = (long *)(param_1 + (long)iVar1 * 0x18 + 0x18);
            do {
                long *plVar2 = (long *)*plVar4;
                if (((s8)plVar2[6] != 0) && (*(s8 *)((long)plVar2 + 0x31) == 0)) {
                    (*(void (**)(long *, u64))(*plVar2 + 0x10))(plVar2, *(u64 *)(param_1 + 8));
                }
                lVar3--;
                plVar4 -= 3;
            } while (lVar3 > 1);
        }
    } else if (iVar1 > 0) {
        long lVar3 = (long)iVar1 + 1;
        long *plVar4 = (long *)(param_1 + (long)iVar1 * 0x18 + 0x18);
        do {
            long *plVar2 = (long *)*plVar4;
            if (((*(u32 *)((long)plVar4 + 0xc) & param_2) != 0) &&
                ((s8)plVar2[6] != 0) && (*(s8 *)((long)plVar2 + 0x31) == 0)) {
                (*(void (**)(long *, u64))(*plVar2 + 0x10))(plVar2, *(u64 *)(param_1 + 8));
            }
            lVar3--;
            plVar4 -= 3;
        } while (lVar3 > 1);
    }
}

// FUN_710047a060 — same as FUN_7100479f70 but calls vtable +0x18 instead of +0x10
void FUN_710047a060(long param_1, u32 param_2) {
    if (*(s8 *)(param_1 + 0x1bc) != 0) return;
    int iVar1 = *(int *)(param_1 + 0x20);
    if (param_2 == 0xffffffffu) {
        if (iVar1 > 0) {
            long lVar3 = (long)iVar1 + 1;
            long *plVar4 = (long *)(param_1 + (long)iVar1 * 0x18 + 0x18);
            do {
                long *plVar2 = (long *)*plVar4;
                if (((s8)plVar2[6] != 0) && (*(s8 *)((long)plVar2 + 0x31) == 0)) {
                    (*(void (**)(long *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
                }
                lVar3--;
                plVar4 -= 3;
            } while (lVar3 > 1);
        }
    } else if (iVar1 > 0) {
        long lVar3 = (long)iVar1 + 1;
        long *plVar4 = (long *)(param_1 + (long)iVar1 * 0x18 + 0x18);
        do {
            long *plVar2 = (long *)*plVar4;
            if (((*(u32 *)((long)plVar4 + 0xc) & param_2) != 0) &&
                ((s8)plVar2[6] != 0) && (*(s8 *)((long)plVar2 + 0x31) == 0)) {
                (*(void (**)(long *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
            }
            lVar3--;
            plVar4 -= 3;
        } while (lVar3 > 1);
    }
}

// FUN_710047a4e0 — vtable +0x60 → indirect jump through result vtable +0x48
void FUN_710047a4e0(long *param_1) {
    long *plVar1 = (*(long *(**)(void))(*param_1 + 0x60))();
    (*(void (**)(void))(*plVar1 + 0x48))();
}

// FUN_710047a760 — accumulate x-only float sum from child list; return as v128_t
// param_2 == 0xffffffff → all nodes; else filter by category bitmask
v128_t FUN_710047a760(long param_1, u32 param_2) {
    float acc_x = 0.0f, acc_y = 0.0f, acc_z = 0.0f, acc_w = 0.0f;

    if (*(s8 *)(param_1 + 0x1bc) == 0) {
        u64 uVar7 = *(u64 *)(param_1 + 0x20);
        if (param_2 == 0xffffffffu) {
            int iVar6 = (int)uVar7;
            if (iVar6 > 0) {
                acc_x = acc_y = 0.0f;
                long lVar5 = (long)iVar6 + 1;
                long *plVar2 = (long *)(param_1 + (long)iVar6 * 0x18 + 0x18);
                do {
                    if ((s8)((long *)*plVar2)[6] != 0) {
                        float *puVar3 = (*(float *(**)(void))(*(long *)*plVar2 + 0x20))();
                        acc_x += puVar3[0];
                        acc_y += 0.0f;
                    }
                    lVar5--;
                    plVar2 -= 3;
                } while (lVar5 > 1);
            }
        } else if (uVar7 != 0) {
            acc_x = acc_y = 0.0f;
            u64 i = 0, j = 1;
            bool bVar1;
            do {
                if ((*(u32 *)(param_1 + i * 0x18 + 0x3c) & param_2) != 0) {
                    long *plVar2 = *(long **)(param_1 + i * 0x18 + 0x30);
                    if ((s8)plVar2[6] != 0) {
                        float *puVar3 = (*(float *(**)(void))(*plVar2 + 0x20))();
                        acc_x += puVar3[0];
                        acc_y += 0.0f;
                    }
                }
                bVar1 = j < uVar7;
                i = j;
                j = (u64)((int)j + 1);
            } while (bVar1);
        }
    }
    v128_t r;
    r.lo = pack_f2(acc_x, acc_y);
    r.hi = pack_f2(acc_z, acc_w);
    return r;
}

// FUN_710047a920 — accumulate full xy float sum from child list (both x and y from puVar3[0..1])
v128_t FUN_710047a920(long param_1, u32 param_2) {
    float acc_x = 0.0f, acc_y = 0.0f, acc_z = 0.0f, acc_w = 0.0f;

    if (*(s8 *)(param_1 + 0x1bc) == 0) {
        u64 uVar7 = *(u64 *)(param_1 + 0x20);
        if (param_2 == 0xffffffffu) {
            int iVar6 = (int)uVar7;
            if (iVar6 > 0) {
                acc_x = acc_y = 0.0f;
                long lVar5 = (long)iVar6 + 1;
                long *plVar2 = (long *)(param_1 + (long)iVar6 * 0x18 + 0x18);
                do {
                    if ((s8)((long *)*plVar2)[6] != 0) {
                        float *puVar3 = (*(float *(**)(void))(*(long *)*plVar2 + 0x20))();
                        acc_x += puVar3[0];
                        acc_y += puVar3[1];
                    }
                    lVar5--;
                    plVar2 -= 3;
                } while (lVar5 > 1);
            }
        } else if (uVar7 != 0) {
            acc_x = acc_y = 0.0f;
            u64 i = 0, j = 1;
            bool bVar1;
            do {
                if ((*(u32 *)(param_1 + i * 0x18 + 0x3c) & param_2) != 0) {
                    long *plVar2 = *(long **)(param_1 + i * 0x18 + 0x30);
                    if ((s8)plVar2[6] != 0) {
                        float *puVar3 = (*(float *(**)(void))(*plVar2 + 0x20))();
                        acc_x += puVar3[0];
                        acc_y += puVar3[1];
                    }
                }
                bVar1 = j < uVar7;
                i = j;
                j = (u64)((int)j + 1);
            } while (bVar1);
        }
    }
    v128_t r;
    r.lo = pack_f2(acc_x, acc_y);
    r.hi = pack_f2(acc_z, acc_w);
    return r;
}

// FUN_710047cda0 — linked-list search + doubly-linked queue insert on two lists
// Finds entry matching param_3 in list at param_1; if found, inserts param_4
// into two separate doubly-linked queues (at param_2 and lVar3), then calls FUN_7100489b00
long FUN_710047cda0(long param_1, long param_2, int param_3, long param_4) {
    if (*(int *)(param_1 + 0x18) == 0) return 0;

    long *plVar4 = *(long **)(param_1 + 8);
    if (plVar4 == (long *)0) return 0;

    do {
        long lVar3 = plVar4[2];
        if (*(int *)(*(long *)(lVar3 + 8) + 8) == param_3) {
            if (lVar3 == 0) return 0;

            u32 uVar2 = *(u32 *)(*(long *)(param_2 + 8) + 8);
            *(long *)(param_4 + 0x30) = param_2;
            *(int *)(param_4 + 0x48) = param_3;
            *(long *)(param_4 + 0x58) = lVar3;
            *(u8 *)(param_4 + 0x65) = 1;
            *(u32 *)(param_4 + 0x20) = uVar2;

            // Insert param_4+0x38 into doubly-linked queue at param_2
            u64 *puVar1 = (u64 *)(param_4 + 0x38);
            if (*(int *)(param_2 + 0x48) == 0) {
                if (*(long *)(param_2 + 0x38) != 0) {
                    *(u64 **)(*(long *)(param_2 + 0x38) + 8) = puVar1;
                    *puVar1 = *(u64 *)(param_2 + 0x38);
                }
                *(u64 **)(param_2 + 0x38) = puVar1;
            } else {
                u64 uVar5 = *(u64 *)(param_2 + 0x40);
                *(u64 *)(param_4 + 0x38) = 0;
                *(u64 *)(param_4 + 0x40) = uVar5;
                **(long **)(param_2 + 0x40) = (long)puVar1;
            }
            *(u64 **)(param_2 + 0x40) = puVar1;
            *(int *)(param_2 + 0x48) += 1;

            // Insert param_4+0x10 into doubly-linked queue at lVar3
            puVar1 = (u64 *)(param_4 + 0x10);
            if (*(int *)(lVar3 + 0x30) == 0) {
                if (*(long *)(lVar3 + 0x20) != 0) {
                    *(u64 **)(*(long *)(lVar3 + 0x20) + 8) = puVar1;
                    *puVar1 = *(u64 *)(lVar3 + 0x20);
                }
                *(u64 **)(lVar3 + 0x20) = puVar1;
            } else {
                u64 uVar5 = *(u64 *)(lVar3 + 0x28);
                *(u64 *)(param_4 + 0x10) = 0;
                *(u64 *)(param_4 + 0x18) = uVar5;
                **(long **)(lVar3 + 0x28) = (long)puVar1;
            }
            *(u64 **)(lVar3 + 0x28) = puVar1;
            *(int *)(lVar3 + 0x30) += 1;

            // Build event descriptor on stack and dispatch
            void *local_40 = &DAT_71050b33c8;
            u32   local_38 = 10;
            u64   local_30 = 0xbcd988648ULL;
            u64   uStack_28 = 0;
            u64   local_20 = 0xffffffff50000000ULL;
            u8    local_18 = 0;
            FUN_7100489b00(lVar3, param_2, &local_40, *(u8 *)(param_4 + 100));
            return 1;
        }
        plVar4 = (long *)*plVar4;
    } while (plVar4 != (long *)0);

    return 0;
}

// FUN_7100485770 — conditionally store 6 16-byte values at param_5+0x70..0xa8
void FUN_7100485770(v128_t param_1, v128_t param_2, v128_t param_3, v128_t param_4,
                    long param_5, u32 param_6) {
    v128_t auVar1 = *(v128_t *)(void *)FUN_7100489810();
    if (param_6 & 1) {
        *(v128_t *)(param_5 + 0x70) = auVar1;
        *(u64 *)(param_5 + 0x80) = param_2.lo;
        *(u64 *)(param_5 + 0x88) = param_2.hi;
        *(u64 *)(param_5 + 0x90) = param_3.lo;
        *(u64 *)(param_5 + 0x98) = param_3.hi;
        *(u64 *)(param_5 + 0xa0) = param_4.lo;
        *(u64 *)(param_5 + 0xa8) = param_4.hi;
    }
}

// FUN_7100488ba0 — triple-deref: param_1+0x20 → +8 → +0x68; vtable +0xc0 with 0xffffffff
void FUN_7100488ba0(long param_1) {
    long *plVar1 = *(long **)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x68);
    (*(void (**)(long *, u32))(*plVar1 + 0xc0))(plVar1, 0xffffffffu);
}

// FUN_7100489c20 — empty singleton: guard + return &DAT_71052b7960
static u64 s_guard_71052b7950;
static u64 s_dat_71052b7960;
void *FUN_7100489c20() {
    int iVar1;
    if (((s_guard_71052b7950 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7950), iVar1 != 0)) {
        __cxa_guard_release(&s_guard_71052b7950);
    }
    return &s_dat_71052b7960;
}
