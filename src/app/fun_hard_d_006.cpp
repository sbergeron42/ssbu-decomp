#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-006
// Pool-d worker: global-ptr init, virtual dtors, nn::os wrappers

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data declarations -------------------------------------------

// Vtable pointers stored in .data (loaded then +0x10 gives dispatch table)
extern u64 PTR_DAT_71052a5278 HIDDEN;
extern u64 PTR_DAT_71052a4d08 HIDDEN;

// Byte-pointer globals (the value stored there IS a pointer to bytes)
extern u8 *PTR_DAT_71052a3bf0 HIDDEN;  // flag byte (char)
extern u64 *PTR_DAT_71052a3c08 HIDDEN; // handle (u64)
extern u8 *PTR_DAT_71052a3d20 HIDDEN;  // vtable base
extern u8 *PTR_DAT_71052a4d60 HIDDEN;  // vtable base
extern u8 *PTR_DAT_71052a4d70 HIDDEN;  // vtable base
extern u8 *PTR_DAT_71052a4dc0 HIDDEN;  // vtable base
extern u8 *PTR_DAT_71052a53d0 HIDDEN;  // vtable base

// ---- External function declarations ----------------------------------------

extern void FUN_710013b7a0(u64);
extern void FUN_710013c500(void);
extern void FUN_7100134eb0(void);
extern void FUN_71000b1cf0(s64);
extern void FUN_710013f900(void);
extern void FUN_7100134c30(void);
extern void FUN_7100134c90(s64 *, u64, u32);
extern void FUN_71000baa20(void);
extern void FUN_71000b4050(s64 *);
extern void FUN_71001308d0(u64 *);
extern s64  FUN_71000b30b0(void);
extern void FUN_71000b3150(u64, u8);

namespace nn { namespace os {
    void InitializeMutex(void *, bool, u32);
}}

// ---- Functions ---------------------------------------------------------------

// 0x71000b1a10 — clear global flag and call 3 cleanup fns (64 bytes)
void FUN_71000b1a10(void)
{
    if (*(char *)PTR_DAT_71052a3bf0 != '\0') {
        *(char *)PTR_DAT_71052a3bf0 = 0;
        FUN_710013b7a0(*PTR_DAT_71052a3c08);
        FUN_710013c500();
        FUN_7100134eb0();
    }
}

// 0x71000bf2b0 — set vtable ptr at two offsets and call init fn twice (64 bytes)
void FUN_71000bf2b0(s64 param_1)
{
    u8 *puVar1 = PTR_DAT_71052a3d20 + 0x10;
    *(u8 **)(param_1 + 0x628) = puVar1;
    FUN_71000b1cf0(param_1 + 0x630);
    *(u8 **)(param_1 + 0x5f8) = puVar1;
    FUN_71000b1cf0(param_1 + 0x600);
}

// 0x71001772b0 — set vtable pointer and call init (48 bytes)
void FUN_71001772b0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5278 + 0x10);
    FUN_710013f900();
}

// 0x710013b930 — guard call + set vtable ptr + init mutex (64 bytes)
void FUN_710013b930(s64 *param_1)
{
    FUN_7100134c30();
    *param_1 = (s64)(PTR_DAT_71052a4d08 + 0x10);
    nn::os::InitializeMutex((void *)(param_1 + 4), true, 0);
}

// 0x710013b970 — init-with-arg + set vtable ptr + init mutex (64 bytes)
void FUN_710013b970(s64 *param_1, u64 param_2)
{
    FUN_7100134c90(param_1, param_2, 1);
    *param_1 = (s64)(PTR_DAT_71052a4d08 + 0x10);
    nn::os::InitializeMutex((void *)(param_1 + 4), true, 0);
}

// 0x710013ce70 — guard call + clear fields + set vtable + call init (80 bytes)
void FUN_710013ce70(s64 *param_1)
{
    FUN_71000baa20();
    u8 *puVar1 = PTR_DAT_71052a4d60;
    *(u32 *)(param_1 + 0xb) = 0;
    param_1[0xc] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    FUN_71000b4050(param_1 + 0xd);
}

// 0x710013d130 — guard call + clear field + set vtable + call init (80 bytes)
void FUN_710013d130(s64 *param_1)
{
    FUN_71000baa20();
    u8 *puVar1 = PTR_DAT_71052a4d70;
    param_1[0xb] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    FUN_71000b4050(param_1 + 0xc);
}

// 0x710013e400 — guard call + clear fields + set vtable + call init (80 bytes)
void FUN_710013e400(s64 *param_1)
{
    FUN_71000baa20();
    u8 *puVar1 = PTR_DAT_71052a4dc0;
    *(u32 *)(param_1 + 0xb) = 0;
    param_1[0xc] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    FUN_71000b4050(param_1 + 0xd);
}

// 0x7100182b50 — large struct initializer with 8 params (64 bytes)
void FUN_7100182b50(s64 *param_1, s64 param_2, u16 param_3, u32 param_4,
                    u32 param_5, u32 param_6, s64 param_7, s64 param_8)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *(u32 *)((s64)param_1 + 0x24) = param_5;
    *(u32 *)(param_1 + 5) = param_6;
    *param_1 = (s64)(PTR_DAT_71052a53d0 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((s64)param_1 + 0x12) = 0x11;
    param_1[6] = param_7;
    param_1[8] = param_8;
    *(u32 *)((s64)param_1 + 0x1c) = param_4;
    *(u32 *)(param_1 + 4) = 0;
    *(u8 *)(param_1 + 7) = 0;
    *(u32 *)((s64)param_1 + 0x14) = 0x30;
}

// 0x7100193330 — singleton guard then delegate (64 bytes)
void FUN_7100193330(u64 param_1, u8 param_2)
{
    s64 lVar1 = FUN_71000b30b0();
    if (lVar1 != 0) {
        u64 uVar2 = (u64)FUN_71000b30b0();
        FUN_71000b3150(uVar2, param_2);
    }
}

// 0x7100179950 — virtual dtor: call vtable[0], then free (64 bytes)
void FUN_7100179950(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001799e0 — virtual dtor: same pattern (64 bytes)
void FUN_71001799e0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179a70 — virtual dtor: same pattern (64 bytes)
void FUN_7100179a70(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179af0 — virtual dtor: same pattern (64 bytes)
void FUN_7100179af0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179b70 — virtual dtor: same pattern (64 bytes)
void FUN_7100179b70(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179c30 — virtual dtor: same pattern (64 bytes)
void FUN_7100179c30(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100194350 — virtual dtor: same pattern (64 bytes)
void FUN_7100194350(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001943d0 — virtual dtor: same pattern (64 bytes)
void FUN_71001943d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100194450 — virtual dtor: same pattern (64 bytes)
void FUN_7100194450(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001944d0 — virtual dtor: same pattern (64 bytes)
void FUN_71001944d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100194550 — virtual dtor: same pattern (64 bytes)
void FUN_7100194550(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}
