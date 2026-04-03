#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71036-0x71037 address range, batch d-014
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void  FUN_710356bb20(void);
extern void  FUN_710392e590(void);
extern void  FUN_71037af2c0(u64);
extern void  FUN_71037aeec0(u64);
extern void  FUN_71037b2b70(u64);
extern void  FUN_71037b36d0(u64);
extern void  FUN_71037b2870(u64, s64*, u64);

// ---- Functions ---------------------------------------------------------------

// 0x71036de518 -- vtable call at *param_1+0x38, compare result to 0xffffffff (56 bytes)
u8 FUN_71036de518(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0x38)))();
    return (u8)(lVar1 == 0xffffffff);
}

// 0x710373e054 -- call FUN_710392e590, return 0 (44 bytes)
u32 FUN_710373e054(void) { FUN_710392e590(); return 0; }

// 0x71037b7b30 -- wrapper: FUN_71037b36d0(param_1) (48 bytes)
void FUN_71037b7b30(u64 param_1) { FUN_71037b36d0(param_1); }

// 0x71037b9760 -- init four sub-objects at fixed offsets (64 bytes)
void FUN_71037b9760(s64 param_1)
{
    FUN_71037af2c0(param_1);
    FUN_71037af2c0(param_1 + 0x20);
    FUN_71037b2b70(param_1 + 0x40);
    FUN_71037b2b70(param_1 + 0x64);
}

// 0x71037bb640 -- init four sub-objects at fixed offsets (64 bytes)
void FUN_71037bb640(s64 param_1)
{
    FUN_71037b2b70(param_1 + 0x10);
    FUN_71037b2b70(param_1 + 0x34);
    FUN_71037aeec0(param_1 + 0x5c);
    FUN_71037aeec0(param_1 + 0x64);
}

// 0x71037bc700 -- wrapper: FUN_71037aeec0(param_1) (48 bytes)
void FUN_71037bc700(u64 param_1) { FUN_71037aeec0(param_1); }

// 0x71037bcc60 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037bcc60(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037bf4f0 -- wrapper: FUN_71037aeec0(param_1) (48 bytes)
void FUN_71037bf4f0(u64 param_1) { FUN_71037aeec0(param_1); }

// 0x71037bf920 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037bf920(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037bfd80 -- return param_1 + 0x78 (32 bytes)
s64 FUN_71037bfd80(s64 param_1) { return param_1 + 0x78; }

// 0x71037bfda0 -- clear four u32 fields (48 bytes)
void FUN_71037bfda0(u32 *param_1)
{
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
    param_1[3] = 0;
}

// 0x71037c0660 -- call FUN_71037aeec0 at +0 and +8 (48 bytes)
void FUN_71037c0660(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
}

// 0x71037c1bf0 -- call FUN_71037aeec0 at +0 and +8 (48 bytes)
void FUN_71037c1bf0(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
}

// 0x71037c24c0 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037c24c0(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037c2690 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037c2690(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037c2860 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037c2860(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037c2a30 -- vtable call at *param_1+8, then FUN_71037b2870 (64 bytes)
void FUN_71037c2a30(s64 *param_1, u64 param_2)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    FUN_71037b2870(param_2, param_1, 0xd0);
}

// 0x71037f7ad0 — abort wrapper (16 bytes)
u32 FUN_71037f7ad0(void) { FUN_710356bb20(); }

// 0x71037f7ae0 — abort wrapper (16 bytes)
u32 FUN_71037f7ae0(void) { FUN_710356bb20(); }
