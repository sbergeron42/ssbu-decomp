#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-011
// Pool-d worker: dispatch/fn-ptr patterns, string ops, bytecode checkers (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    int   strcmp(const char *a, const char *b);
    u64   strlen(const char *s);
    // Curl (libcurl internal)
    void  Curl_llist_insert_next(void *list, void *e, void *data, void *node);
}

// ---- External data -------------------------------------------------------

// Function pointer globals (globals that store callable code pointers)
extern u64 PTR_DAT_71052a1328 HIDDEN; // fn-ptr
extern u64 PTR_DAT_71052a1330 HIDDEN; // fn-ptr
extern u64 PTR_DAT_71052a1348 HIDDEN; // fn-ptr
extern u64 PTR_DAT_71052a1670 HIDDEN; // fn-ptr (guard)
extern u64 PTR_DAT_71052a1688 HIDDEN; // fn-ptr (dispatch)
extern u64 PTR_DAT_71052a1830 HIDDEN; // fn-ptr (guard)
extern u64 PTR_DAT_71052a1838 HIDDEN; // fn-ptr
extern u64 PTR_DAT_71052a1840 HIDDEN; // fn-ptr
extern u64 PTR_DAT_71052a1938 HIDDEN; // ctor fn-ptr
extern u64 PTR_DAT_71052a19b0 HIDDEN; // dtor fn-ptr
extern u64 PTR_DAT_71052a19b8 HIDDEN; // dtor fn-ptr

// Vtable entry pointers
extern u8 *PTR_DAT_71052a2358 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_710000086c0(u64, u64, u64);
extern void FUN_710003bc80(void);
extern void FUN_7100037870(void *, u64);
extern u64  FUN_7100044dd0(u64, u64, u32);
extern void FUN_7100044db0(u64, u64);
extern void FUN_7100047800(u64, u64, u32);
extern void FUN_710007bc10(u64, u64, u64);

// nn::util::SNPrintf
namespace nn { namespace util {
    int SNPrintf(char *buf, u64 sz, const char *fmt, ...);
}}

// ---- Functions ---------------------------------------------------------------

// 0x7100014160 — Curl_llist_insert_next + conditional head-change callback (96 bytes)
u64 FUN_7100014160(s64 param_1, s64 param_2)
{
    void *puVar1 = *(void **)(param_2 + 0x8d0);
    Curl_llist_insert_next((void *)(param_2 + 0x8d0),
                           *(void **)(param_2 + 0x8d8),
                           (void *)param_1,
                           (void *)(param_1 + 0x30));
    if (puVar1 != *(void **)(param_2 + 0x8d0)) {
        *(u8 *)(param_2 + 0x8c9) = 0;
        FUN_710000086c0(**(u64 **)(param_2 + 0x8d0), 0, 6);
    }
    return 0;
}

// ---- fn-ptr dispatch with conditional clear (2 variants, 96 bytes each) --------

// 0x7100031c40 — clear slot if set, then dispatch to fn-ptr[2], clear flag byte
void FUN_7100031c40(u8 *param_1)
{
    if (*(s64 *)(param_1 + 0xc0) != 0) {
        ((void(*)(u64))PTR_DAT_71052a1328)(**(u64 **)(param_1 + 8));
        *(u64 *)(param_1 + 0xc0) = 0;
    }
    ((void(*)(u64))PTR_DAT_71052a1330)(*(u64 *)(param_1 + 0xb8));
    *param_1 = 0;
}

// 0x7100031d10 — same pattern, different dispatch fn and output flag value
void FUN_7100031d10(u8 *param_1)
{
    if (*(s64 *)(param_1 + 0xc0) != 0) {
        ((void(*)(u64))PTR_DAT_71052a1328)(**(u64 **)(param_1 + 8));
        *(u64 *)(param_1 + 0xc0) = 0;
    }
    ((void(*)(u64))PTR_DAT_71052a1348)(*(u64 *)(param_1 + 0xb8));
    *param_1 = 2;
}

// ---- guard + conditional bit-check + fn-ptr dispatch (96 bytes each) -----------

// 0x71000377b0 — guard call + check bit 1 of byte + dispatch fn-ptr
void FUN_71000377b0(u64 param_1, u8 *param_2)
{
    ((void(*)(void))PTR_DAT_71052a1670)();
    if ((*param_2 >> 1 & 1) == 0) {
        ((void(*)(u64, u64))PTR_DAT_71052a1688)(param_1, 0);
    }
}

// 0x7100037810 — guard + 2x fn-ptr dispatches (jump table variant)
void FUN_7100037810(u64 param_1, u32 *param_2)
{
    ((void(*)(void))PTR_DAT_71052a1830)();
    ((void(*)(u64, u32))PTR_DAT_71052a1840)(param_1, *param_2);
    ((void(*)(u64, u64, u32))PTR_DAT_71052a1838)(param_1, *(u64 *)(param_2 + 2), param_2[1]);
}

// ---- stack-alloc local + ctor + call + dtor (96 bytes each) -------------------

// 0x710003a020 — construct 128B local from *param_1, call, then dtor via PTR_19b8
void FUN_710003a020(u64 *param_1, u64 param_2)
{
    u8 local[128];
    ((void(*)(u8 *, u64))PTR_DAT_71052a1938)(local, *param_1);
    FUN_7100037870(local, param_2);
    ((void(*)(u8 *))PTR_DAT_71052a19b8)(local);
}

// 0x710003a080 — same but uses PTR_19b0 for dtor
void FUN_710003a080(u64 *param_1, u64 param_2)
{
    u8 local[128];
    ((void(*)(u8 *, u64))PTR_DAT_71052a1938)(local, *param_1);
    FUN_7100037870(local, param_2);
    ((void(*)(u8 *))PTR_DAT_71052a19b0)(local);
}

// 0x710003b060 — guard + linked-list init + vtable + zero many fields (96 bytes)
void FUN_710003b060(s64 *param_1)
{
    FUN_710003bc80();
    param_1[5] = (s64)(param_1 + 5);
    param_1[6] = (s64)(param_1 + 5);
    param_1[0x11] = 0;
    *(u32 *)(param_1 + 0x10) = 0;
    param_1[7] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    *param_1 = (s64)(PTR_DAT_71052a2358 + 0x10);
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
}

// 0x710003c630 — check type flag or linear scan for value 2 in array (96 bytes)
u64 FUN_710003c630(s64 param_1)
{
    if ((*(u32 *)(param_1 + 8) & 0xfffffffe) != 4) {
        if (*(s32 *)(param_1 + 0x20) < 1) {
            return 0;
        }
        s64 lVar1 = 0;
        while (*(s32 *)(param_1 + 0x10 + lVar1 * 4) != 2) {
            lVar1 = lVar1 + 1;
            if (*(s32 *)(param_1 + 0x20) <= lVar1) {
                return 0;
            }
        }
    }
    return 1;
}

// 0x710004aeb0 — SNPrintf format "%s_%s.bflan" then vtable[0xa](obj,fourcc,name) (96 bytes)
void FUN_710004aeb0(s64 param_1, u64 param_2)
{
    char buf[136];
    nn::util::SNPrintf(buf, 0x88, "%s_%s.bflan",
                       *(u64 *)(param_1 + 0x30), param_2);
    (*(void (**)(void *, u32, char *))(*(u64 *)(*(s64 **)(param_1 + 0x40)) + 0x50))
        (*(void **)(param_1 + 0x40), 0x616e696d, buf);
}

// 0x7100045210 — linked list walk: call FUN_710007bc10 on flagged nodes (96 bytes)
void FUN_7100045210(s64 param_1, u64 param_2, u64 param_3)
{
    for (s64 lVar1 = *(s64 *)(param_1 + 8);
         param_1 != lVar1;
         lVar1 = *(s64 *)(lVar1 + 8))
    {
        if (*(u8 *)(lVar1 + 0x98) != '\0') {
            FUN_710007bc10(*(u64 *)(lVar1 + 0x90), param_2, param_3);
        }
    }
}

// ---- Bytecode flag checker triple (96 bytes each) —
// All 3 share: check bit 2 of param_1+0x60, walk bytecode at param_1+0xa8,
//              look for opcode 0x15 and check a bit in a child descriptor.

// 0x7100059fe0 — check bit (child_flags >> 1 & 1) of bytecode child descriptor
u64 FUN_7100059fe0(s64 param_1)
{
    if ((*(u8 *)(param_1 + 0x60) >> 2 & 1) != 0) {
        s64 lVar1 = *(s64 *)(param_1 + 0xa8) + 0xc;
        u32 uVar3 = *(u32 *)(*(s64 *)(param_1 + 0xa8) + 0x10);
        s32 *piVar2 = (s32 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4) + (s32)uVar3));
        if (*piVar2 == 0x15) {
            s64 lVar4 = (s64)*(s8 *)((s64)piVar2 + 6);
            if (lVar4 >= 0 &&
                ((*(u8 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4 + lVar4 * 4) + (s32)uVar3) + 4) >> 1 & 1) != 0))
            {
                return 1;
            }
        }
    }
    return 0;
}

// 0x710005a040 — check bit (child_flags & 1) of bytecode child descriptor
u64 FUN_710005a040(s64 param_1)
{
    if ((*(u8 *)(param_1 + 0x60) >> 2 & 1) != 0) {
        s64 lVar1 = *(s64 *)(param_1 + 0xa8) + 0xc;
        u32 uVar3 = *(u32 *)(*(s64 *)(param_1 + 0xa8) + 0x10);
        s32 *piVar2 = (s32 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4) + (s32)uVar3));
        if (*piVar2 == 0x15) {
            s64 lVar4 = (s64)*(s8 *)((s64)piVar2 + 6);
            if (lVar4 >= 0 &&
                ((*(u8 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4 + lVar4 * 4) + (s32)uVar3) + 4) & 1) != 0))
            {
                return 1;
            }
        }
    }
    return 0;
}

// 0x710005a0a0 — check bit (child_flags >> 2 & 1) of bytecode child descriptor
u64 FUN_710005a0a0(s64 param_1)
{
    if ((*(u8 *)(param_1 + 0x60) >> 2 & 1) != 0) {
        s64 lVar1 = *(s64 *)(param_1 + 0xa8) + 0xc;
        u32 uVar3 = *(u32 *)(*(s64 *)(param_1 + 0xa8) + 0x10);
        s32 *piVar2 = (s32 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4) + (s32)uVar3));
        if (*piVar2 == 0x15) {
            s64 lVar4 = (s64)*(s8 *)((s64)piVar2 + 6);
            if (lVar4 >= 0 &&
                ((*(u8 *)(lVar1 + (u64)(u32)(*(s32 *)(lVar1 + (u64)uVar3 + 4 + lVar4 * 4) + (s32)uVar3) + 4) >> 2 & 1) != 0))
            {
                return 1;
            }
        }
    }
    return 0;
}

// 0x7100066060 — compute total strlen+1 for param_2 string pointers (96 bytes)
s64 FUN_7100066060(s64 param_1, u32 param_2)
{
    if ((s32)param_2 < 1) {
        return 0;
    }
    s64 lVar2 = 0;
    u64 uVar3 = (u64)param_2;
    u64 *puVar4 = (u64 *)(param_1 + 0x50);
    do {
        lVar2 = lVar2 + strlen((char *)*puVar4) + 1;
        uVar3 = uVar3 - 1;
        puVar4 = puVar4 + 1;
    } while (uVar3 != 0);
    return lVar2;
}

// 0x7100066600 — conditional FUN_7100047800 then unconditional FUN_7100044db0 (96 bytes)
void FUN_7100066600(u64 param_1, u64 param_2, u64 param_3, u32 param_4)
{
    u64 uVar1 = FUN_7100044dd0(param_1, param_3, (u32)(param_4 & 0xff));
    if ((uVar1 & 1) != 0) {
        FUN_7100047800(param_3, param_2, param_4);
    }
    FUN_7100044db0(param_1, param_2);
}

// ---- strcmp-based linked-list search (2 identical instances, 96 bytes each) ----

// 0x710006fc60 — search list starting at param_1+0x18 for node whose string == param_2
s64 FUN_710006fc60(s64 param_1, char *param_2)
{
    s64 lVar2 = *(s64 *)(param_1 + 0x18);
    while (true) {
        if (param_1 + 0x10 == lVar2) {
            return 0;
        }
        if (strcmp((char *)(lVar2 + 0x10), param_2) == 0) break;
        lVar2 = *(s64 *)(lVar2 + 8);
    }
    return lVar2;
}

// 0x710006fce0 — identical pattern (separate instantiation)
s64 FUN_710006fce0(s64 param_1, char *param_2)
{
    s64 lVar2 = *(s64 *)(param_1 + 0x18);
    while (true) {
        if (param_1 + 0x10 == lVar2) {
            return 0;
        }
        if (strcmp((char *)(lVar2 + 0x10), param_2) == 0) break;
        lVar2 = *(s64 *)(lVar2 + 8);
    }
    return lVar2;
}
