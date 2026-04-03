#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-007
// Pool-d worker: virtual dtors, binary tree traversals, misc init

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a56d0 HIDDEN;
extern u8 *PTR_DAT_71052a5898 HIDDEN;
extern u8 *PTR_DAT_71052a5e08 HIDDEN;
extern u8 *PTR_DAT_71052a65e0 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_71001308d0(u64 *);
extern void FUN_7100153310(void);
extern void FUN_71001672c0(s64);
extern void FUN_71001b1970(void);
extern void FUN_71001d6020(s64 *);
extern void FUN_71001b1870(u64 *);
extern void FUN_71001beb30(u64);
extern void FUN_71001f2180(s64);
extern void FUN_71001becd0(u64, u64);
extern void FUN_7100228130(void);
extern void FUN_7100228130(s64 *);
extern u64  FUN_71001e69b0(void);
extern void FUN_71001cb870(u64, s64, u64, s64);
extern void FUN_71001e04b0(void);
extern void FUN_71002193d0(u64, u64 *);
extern void FUN_71001ce550(s64);
extern void FUN_71001cdd40(s64, u64);
extern void FUN_71001cd830(s64, u64);
extern void FUN_71001d6a00(s64 *);
extern void FUN_71001afba0(s64 *);

// ---- Virtual dtor pattern — 5 more instances (64 bytes each) -------

// 0x71001945d0
void FUN_71001945d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100194650
void FUN_7100194650(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001946d0
void FUN_71001946d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100194750
void FUN_7100194750(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001947d0
void FUN_71001947d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// ---- Misc init functions -------------------------------------------------

// 0x7100194810 — guard + set vtable + clear field + sub-init (64 bytes)
void FUN_7100194810(s64 *param_1)
{
    FUN_7100153310();
    u8 *puVar1 = PTR_DAT_71052a56d0;
    *(u8 *)((s64)param_1 + 0x10c) = 0xfd;
    *param_1 = (s64)(puVar1 + 0x10);
    *(u32 *)(param_1 + 0x22) = 0;
    FUN_71001672c0((s64)param_1 + 0x114);
}

// 0x71001b1930 — set vtable + clear field + 2 calls (64 bytes)
void FUN_71001b1930(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a5898;
    param_1[8] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    FUN_71001b1970();
    FUN_71001d6020(param_1);
}

// 0x71001dcfd0 — binary tree post-order traversal: recurse then free (64 bytes)
void FUN_71001dcfd0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71001dcfd0(param_1, (u64 *)*param_2);
        FUN_71001dcfd0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x71001e0470 — set vtable + 2 calls (64 bytes)
void FUN_71001e0470(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5e08 + 0x10);
    FUN_71001e04b0();
    FUN_71002193d0(param_1[5], (u64 *)(param_1 + 6));
}

// 0x71001e5d60 — conditional chain: if not flag, call extra init (64 bytes)
void FUN_71001e5d60(s64 param_1)
{
    if (*(char *)(param_1 + 0x68) != '\0') {
        FUN_71001beb30(*(u64 *)(param_1 + 8));
        return;
    }
    FUN_71001f2180(param_1);
    FUN_71001beb30(*(u64 *)(param_1 + 8));
}

// 0x71001f2a40 — conditional init + clear flag + call (64 bytes)
void FUN_71001f2a40(s64 param_1, u64 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {
        FUN_71001f2180(param_1);
    }
    *(u8 *)(param_1 + 0x69) = 0;
    FUN_71001becd0(*(u64 *)(param_1 + 8), param_2);
}

// ---- Binary tree post-order traversal variants (64 bytes each) ----------

// 0x71002193d0
void FUN_71002193d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71002193d0(param_1, (u64 *)*param_2);
        FUN_71002193d0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021a3e0
void FUN_710021a3e0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a3e0(param_1, (u64 *)*param_2);
        FUN_710021a3e0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021a420
void FUN_710021a420(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a420(param_1, (u64 *)*param_2);
        FUN_710021a420(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021a460
void FUN_710021a460(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a460(param_1, (u64 *)*param_2);
        FUN_710021a460(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021ab20
void FUN_710021ab20(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ab20(param_1, (u64 *)*param_2);
        FUN_710021ab20(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021ab60
void FUN_710021ab60(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ab60(param_1, (u64 *)*param_2);
        FUN_710021ab60(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021aba0
void FUN_710021aba0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021aba0(param_1, (u64 *)*param_2);
        FUN_710021aba0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x710021abe0
void FUN_710021abe0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021abe0(param_1, (u64 *)*param_2);
        FUN_710021abe0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// ---- Misc functions -------------------------------------------------------

// 0x71002281a0 — drain linked list: walk then free all (64 bytes)
void FUN_71002281a0(s64 *param_1)
{
    if (param_1 == nullptr) {
        return;
    }
    s64 lVar1 = *param_1;
    while (lVar1 != 0) {
        lVar1 = *(s64 *)(lVar1 + 8);
        FUN_7100228130();
    }
    FUN_7100228130(param_1);
}

// 0x7100228de0 — guard check + compute offset + call (64 bytes)
void FUN_7100228de0(u64 param_1, s64 param_2)
{
    if (*(s64 *)(param_2 + 0x18) != 0) {
        u64 uVar1 = FUN_71001e69b0();
        FUN_71001cb870(uVar1,
                       *(s64 *)(param_2 + 0x10) + *(s64 *)(param_2 + 0x28),
                       *(u64 *)(param_2 + 0x18),
                       (s64)-1);
    }
}

// 0x710022bac0 — call 3 init fns at struct offsets with param (64 bytes)
void FUN_710022bac0(s64 param_1, u64 param_2)
{
    FUN_71001ce550(param_1 + 8);
    FUN_71001cdd40(param_1 + 0x2a0, param_2);
    FUN_71001cd830(param_1 + 0x378, param_2);
}

// 0x710022ecf0 — set vtable + call two sub-inits (64 bytes)
void FUN_710022ecf0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a65e0 + 0x10);
    FUN_71001d6a00(param_1 + 10);
    FUN_71001afba0(param_1 + 1);
}
