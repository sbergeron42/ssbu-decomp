#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-016
// Pool-d worker: dtor chains, mutex guard, memset, recursive tree dtors (80B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void *memset(void *s, int c, u64 n);
}

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a3500 HIDDEN;
extern u8 *PTR_DAT_71052a39e0 HIDDEN;
extern u8 *PTR_DAT_71052a3d80 HIDDEN;
extern u8 *PTR_DAT_71052a3d98 HIDDEN;
extern u8 *PTR_DAT_71052a5018 HIDDEN;
extern u8 *PTR_DAT_71052a5438 HIDDEN;
extern u8 *PTR_DAT_71052a5fb0 HIDDEN;
extern u8 *PTR_DAT_71052a6110 HIDDEN;
extern u8 *PTR_DAT_71052a62d8 HIDDEN;
extern u8 *PTR_DAT_71052a6318 HIDDEN;

// ---- External functions --------------------------------------------------

// Sub-dtor helpers (unnamed)
extern void FUN_7100042bf0(s64 *);
extern void FUN_7100044f70(s64 *);
extern void FUN_7100031870(s64 *);
extern void FUN_7100033910(s64 *);
extern void FUN_7100060b90(s64 *);
extern void FUN_7100064c30(s64 *);
extern void FUN_710015ff20(s64 *);
extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000b4140(s64);   // cleanup helper (takes s64 value, not pointer)
extern void FUN_71000b4760(s64 *);
extern void FUN_71001308d0(s64);
extern void FUN_71001545b0(void);
extern void FUN_7100154360(s64);
extern void FUN_71001af8a0(s64 *);
extern void FUN_71001b1870(void *);
extern void FUN_71001b17e0(s64 *);
extern void FUN_71001b3ef0(s64 *);
extern void FUN_71001b4910(s64 *);
extern void FUN_71001bef00(s64 *);

extern "C" {
    void operator_delete(void *);
}

namespace nn {
namespace os {
    void LockMutex(void *);
    void UnlockMutex(void *);
}
}

// ---- Functions ---------------------------------------------------------------

// 0x7100041660 — vtable + 4x sub-dtor (no delete) (80 bytes)
void FUN_7100041660(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3500 + 0x10);
    FUN_7100060b90(param_1 + 0x14);
    FUN_7100064c30(param_1 + 0x12);
    FUN_7100044f70(param_1 + 0x10);
    FUN_7100042bf0(param_1 + 1);
}

// 0x7100089030 — vtable + 2x sub-dtor + delete (80 bytes)
void FUN_7100089030(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a39e0 + 0x10);
    FUN_7100033910(param_1 + 10);
    FUN_7100031870(param_1 + 1);
    operator_delete(param_1);
}

// 0x71000c3330 — vtable + FUN_710015ff20 + 3x FUN_71000b4140 (80 bytes)
void FUN_71000c3330(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3d98 + 0x10);
    FUN_710015ff20(param_1 + 0x32);
    FUN_71000b4140(*(s64 *)(param_1 + 0x27));
    FUN_71000b4140(*(s64 *)(param_1 + 0x21));
    FUN_71000b4140(*(s64 *)(param_1 + 0x1b));
}

// 0x7100155610 — 3x conditional FUN_71001545b0 + zero field + FUN_7100154360 (80 bytes)
void FUN_7100155610(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa90) != 0) {
        FUN_71001545b0();
    }
    if (*(s64 *)(param_1 + 0xa88) != 0) {
        FUN_71001545b0();
    }
    if (*(s64 *)(param_1 + 0xa80) != 0) {
        FUN_71001545b0();
    }
    *(u64 *)(param_1 + 0x30) = 0;
    FUN_7100154360(param_1);
}

// 0x710015ff70 — vtable + 3x FUN_71000b1cf0 + delete (80 bytes)
void FUN_710015ff70(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5018 + 0x10);
    FUN_71000b1cf0(param_1 + 9);
    FUN_71000b1cf0(param_1 + 5);
    FUN_71000b1cf0(param_1 + 1);
    operator_delete(param_1);
}

// 0x710017e4a0 — LockMutex + vtable[0x78] dispatch (3 args) + UnlockMutex (80 bytes)
void FUN_710017e4a0(s64 *param_1)
{
    nn::os::LockMutex((void *)(param_1 + 0x5c));
    (*(void(**)(s64 *, s64, s64))(*param_1 + 0x78))(param_1, param_1[0x61], param_1[0x60]);
    nn::os::UnlockMutex((void *)(param_1 + 0x5c));
}

// 0x7100183870 — vtable + conditional 2x cleanup (FUN_71000b4140 + FUN_71001308d0) + FUN_71000b4760 (80 bytes)
void FUN_7100183870(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a5438 + 0x10);
    if (lVar1 != 0) {
        FUN_71000b4140(lVar1);
        FUN_71001308d0(lVar1);
    }
    param_1[0x11] = 0;
    FUN_71000b4760(param_1);
}

// 0x710019c3b0 — LockMutex + memset 0x100 bytes at +0x160 + UnlockMutex (80 bytes)
void FUN_710019c3b0(s64 param_1)
{
    nn::os::LockMutex((void *)(param_1 + 0x138));
    memset((void *)(param_1 + 0x160), 0, 0x100);
    nn::os::UnlockMutex((void *)(param_1 + 0x138));
}

// ---- vtable + set 2 fields to puVar1 + 2x FUN_71001b4910 (2 variants, 80 bytes each) ----

// 0x71001e6b00
void FUN_71001e6b00(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a3d80 + 0x10;
    *param_1 = (s64)(PTR_DAT_71052a5fb0 + 0x10);
    param_1[7] = (s64)puVar1;
    FUN_71001b4910((s64 *)(param_1 + 7));
    param_1[1] = (s64)puVar1;
    FUN_71001b4910(param_1 + 1);
}

// 0x71001e6b50 — same + FUN_71001af8a0 (deleting dtor variant)
void FUN_71001e6b50(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a3d80 + 0x10;
    *param_1 = (s64)(PTR_DAT_71052a5fb0 + 0x10);
    param_1[7] = (s64)puVar1;
    FUN_71001b4910((s64 *)(param_1 + 7));
    param_1[1] = (s64)puVar1;
    FUN_71001b4910(param_1 + 1);
    FUN_71001af8a0(param_1);
}

// 0x71001f4660 — vtable + 3x FUN_71001bef00 (80 bytes)
void FUN_71001f4660(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a6110 + 0x10);
    FUN_71001bef00(param_1 + 0x26);
    FUN_71001bef00(param_1 + 0x14);
    FUN_71001bef00(param_1 + 2);
}

// ---- vtable + FUN_71001b17e0 + FUN_71001b3ef0 + FUN_71001af8a0 (2 variants, 80 bytes each) ----

// 0x7100210550
void FUN_7100210550(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a62d8 + 0x10);
    FUN_71001b17e0(param_1 + 0x13b);
    FUN_71001b3ef0(param_1 + 1);
    FUN_71001af8a0(param_1);
}

// 0x7100212190
void FUN_7100212190(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a6318 + 0x10);
    FUN_71001b17e0(param_1 + 0x13b);
    FUN_71001b3ef0(param_1 + 1);
    FUN_71001af8a0(param_1);
}

// ---- Recursive binary tree dtors: FUN_71001bef00 + FUN_71001b1870 (2 identical instances, 80B each) ----

// 0x710021a4a0
void FUN_710021a4a0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a4a0(param_1, (u64 *)*param_2);
        FUN_710021a4a0(param_1, (u64 *)param_2[1]);
        FUN_71001bef00((s64 *)(param_2 + 4));
        FUN_71001b1870((void *)param_2);
    }
}

// 0x710021ac20 — identical pattern (separate instantiation)
void FUN_710021ac20(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ac20(param_1, (u64 *)*param_2);
        FUN_710021ac20(param_1, (u64 *)param_2[1]);
        FUN_71001bef00((s64 *)(param_2 + 4));
        FUN_71001b1870((void *)param_2);
    }
}
