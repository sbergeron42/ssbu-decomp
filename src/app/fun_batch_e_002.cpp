#include "types.h"

// Batch E - 002: allocator wrappers, vtable init, lock/unlock helpers (0x7100 range)

// ---- External declarations --------------------------------------------------

extern "C" {
    int strcmp(const char *, const char *);
}

// Called functions
extern u64  FUN_71000c9c60(s64);
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);
extern void FUN_71000d4b40(s64, u32);
extern void FUN_71000d4ee0(s64, u32);
extern void FUN_71001875f0(void);
extern void FUN_7100187f50(void);
extern void FUN_710003e230(s64, u32);
extern void FUN_7100078b00(u64, s64);
extern void FUN_71000c4d90(u64);
extern u32  FUN_7100251c80(u64);
extern void thunk_FUN_7100251e90(u64);

// Vtable/singleton pointers
extern u8 *PTR_DAT_71052a4010;
extern u8 *PTR_DAT_71052a4220;  // base for vtable init in FUN_71000d5ea0
extern u8 *PTR_DAT_71052a3d88;  // lock object for FUN_71000e8240

// ---- Functions --------------------------------------------------------------

// 0x71000c7460 — null check on field at +0x18 (always returns 0)
u64 FUN_71000c7460(s64 param_1)
{
    s64 field_0x18;

    if (*(s64 *)(param_1 + 0x18) != 0) {
    }
    return 0;
}

// 0x71000d46d0 — allocate 0x18-byte object, initialize with FUN_71000d4b40
s64 FUN_71000d46d0(u64 param_1, u32 param_2)
{
    u64 heap = FUN_71000b1b90();
    s64 obj = FUN_7100130810(0x18, heap);
    if (obj != 0) {
        FUN_71000d4b40(obj, param_2);
    }
    return obj;
}

// 0x71000d4aa0 — allocate 0x18-byte object, initialize with FUN_71000d4ee0
s64 FUN_71000d4aa0(u64 param_1, u32 param_2)
{
    u64 heap = FUN_71000b1b90();
    s64 obj = FUN_7100130810(0x18, heap);
    if (obj != 0) {
        FUN_71000d4ee0(obj, param_2);
    }
    return obj;
}

// 0x71000d5ea0 — vtable init: call base ctor, set vtable pointer
void FUN_71000d5ea0(s64 *param_1)
{
    FUN_7100187f50();
    *param_1 = (s64)(PTR_DAT_71052a4220 + 0x10);
}

// FUN_71000500a0 — TODO: decompile

// 0x71000e8240 — lock, call FUN_7100251c80, unlock
u32 FUN_71000e8240(u64 param_1, u64 param_2)
{
    u8 *lock_obj = PTR_DAT_71052a3d88;
    FUN_71000c4d90(*(u64 *)PTR_DAT_71052a3d88);
    u32 result = FUN_7100251c80(param_2);
    thunk_FUN_7100251e90(*(u64 *)lock_obj);
    return result;
}
