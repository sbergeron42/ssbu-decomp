#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71039 address range, batch d-011
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int ffsl(long);
    int pthread_mutex_trylock(void*);
}

extern void FUN_7103928650(u64, u64);
extern u32  FUN_7103928220(u64);
extern void FUN_7103928590(u64);
extern s32  FUN_7103929710(u64);   // returns pointer as s64
extern u8  *FUN_71039291e0(u64);
extern void FUN_710392b420(u64);
extern void FUN_710392c130(u64);
extern s64  FUN_710392c680(u64);   // returns pointer as s64
extern s32  FUN_710392c630(u64);   // returns pointer as s32
extern s64  FUN_710392da60(s64);
extern void FUN_710392db30(u32);
extern void FUN_710392ed20(u64);
extern void FUN_710392ed50(void*);
extern u32  FUN_710392f0d0(void*, u32);
extern s32  FUN_710392fdb0(s64);   // also callable as ffsl wrapper
extern void FUN_710392fc50(u64);
extern void FUN_7103930b40(u64);
extern void FUN_7103930b80();
extern void FUN_7103930ea0(s64, u64);
extern void FUN_7103931b70(u64);
extern s64  FUN_7103932470(u64);
extern s32  FUN_7103932420(u64);
extern void FUN_7103933050(u64, u64);
extern u8  *FUN_71039337a0(u64);
extern void FUN_710392da20(u64);
extern s64  FUN_7103933750(u64);
extern s64  FUN_7103933700(u64);
extern void FUN_710381a6d0(u32, s64);

// External data
extern s64 DAT_7105293560;

// ---- Functions ---------------------------------------------------------------

// 0x71039280c0 -- wrapper: FUN_7103928650(p1, p2) (48 bytes)
void FUN_71039280c0(u64 param_1, u64 param_2) { FUN_7103928650(param_1, param_2); }

// 0x71039281f0 -- return FUN_7103928220(p1) & 1 (48 bytes)
u64 FUN_71039281f0(u64 param_1) { return FUN_7103928220(param_1) & 1; }

// 0x7103928450 -- wrapper: FUN_7103928590(p1) (48 bytes)
void FUN_7103928450(u64 param_1) { FUN_7103928590(param_1); }

// 0x7103928560 -- return ffsl(param_1) (48 bytes)
s32 FUN_7103928560(s64 param_1) { return ffsl(param_1); }

// 0x7103928530 -- wrapper: FUN_7103928560(p1) (48 bytes)
void FUN_7103928530(u64 param_1) { (void)FUN_7103928560(param_1); }

// 0x7103928860 -- deref u64 from FUN_7103929710(param_1) (48 bytes)
u64 FUN_7103928860(u64 param_1) { return *(u64*)(s64)FUN_7103929710(param_1); }

// 0x71039291b0 -- return *FUN_71039291e0(param_1) & 1 (48 bytes)
u8 FUN_71039291b0(u64 param_1) { return *FUN_71039291e0(param_1) & 1; }

// 0x7103929660 -- pthread_mutex_trylock at p+0x40, return non-zero test (48 bytes)
// +0x40 [inferred: embedded pthread_mutex_t, trylock returns non-zero on contention]
u8 FUN_7103929660(s64 param_1)
{
    return (u8)(pthread_mutex_trylock((void*)(param_1 + 0x40)) != 0);
}

// 0x710392b3f0 -- wrapper: FUN_710392b420(param_1) (48 bytes)
void FUN_710392b3f0(u64 param_1) { FUN_710392b420(param_1); }

// 0x710392b720 -- wrapper: FUN_710392c130(param_1) (48 bytes)
void FUN_710392b720(u64 param_1) { FUN_710392c130(param_1); }

// 0x710392c480 -- deref u64 from FUN_710392c680(param_1) (48 bytes)
u64 FUN_710392c480(u64 param_1) { return *(u64*)(s64)FUN_710392c680(param_1); }

// 0x710392c4b0 -- deref u32 from FUN_710392c630(param_1) (48 bytes)
u64 FUN_710392c4b0(u64 param_1) { return *(u32*)(s64)FUN_710392c630(param_1); }

// 0x710392d900 -- update DAT_7105293560 via FUN_710392da60 (48 bytes)
void FUN_710392d900(void) { DAT_7105293560 = FUN_710392da60(DAT_7105293560); }

// 0x710392d9f0 -- wrapper: FUN_710392da20(param_1) (48 bytes)
void FUN_710392d9f0(u64 param_1) { FUN_710392da20(param_1); }

// 0x710392db00 -- wrapper: FUN_710392db30(param_1) (48 bytes)
void FUN_710392db00(u32 param_1) { FUN_710392db30(param_1); }

// 0x710392ecf0 -- wrapper: FUN_710392ed20(param_1) (48 bytes)
void FUN_710392ecf0(u64 param_1) { FUN_710392ed20(param_1); }

// 0x710392ed20 -- FUN_710392ed50 at param_1 + 0xa0 (48 bytes)
// +0xa0 [inferred: embedded sub-object passed to FUN_710392ed50]
void FUN_710392ed20(u64 param_1) { FUN_710392ed50((void*)(param_1 + 0xa0)); }

// 0x710392f0a0 -- return FUN_710392f0d0(p+0x9c, 2) & 1 (48 bytes)
// +0x9c [inferred: embedded flag/state field passed to FUN_710392f0d0 with arg 2]
u64 FUN_710392f0a0(s64 param_1) { return FUN_710392f0d0((void*)(param_1 + 0x9c), 2) & 1; }

// 0x710392fcd0 -- wrapper: FUN_710392fdb0(param_1) (48 bytes)
void FUN_710392fcd0(u64 param_1) { FUN_710392fdb0(param_1); }

// 0x710392fdb0 -- return ffsl(param_1) (48 bytes)
s32 FUN_710392fdb0(s64 param_1) { return ffsl(param_1); }

// 0x710392fe20 -- pthread_mutex_trylock at p+0x40, return non-zero test (48 bytes)
// +0x40 [inferred: embedded pthread_mutex_t, same layout as FUN_7103929660's struct]
u8 FUN_710392fe20(s64 param_1)
{
    return (u8)(pthread_mutex_trylock((void*)(param_1 + 0x40)) != 0);
}

// 0x7103930810 -- wrapper: FUN_710392fc50(param_1) (48 bytes)
void FUN_7103930810(u64 param_1) { FUN_710392fc50(param_1); }

// 0x71039308f0 -- wrapper: FUN_710392fdb0(param_1) (48 bytes)
void FUN_71039308f0(u64 param_1) { FUN_710392fdb0(param_1); }

// 0x7103930b10 -- call FUN_7103930b40 then FUN_7103930b80 (48 bytes)
void FUN_7103930b10(u64 param_1)
{
    FUN_7103930b40(param_1);
    FUN_7103930b80();
}

// 0x7103930e70 -- FUN_7103930ea0(param_1+0xa0, param_2) (48 bytes)
// +0xa0 [inferred: embedded sub-object, same offset as FUN_710392ed20]
void FUN_7103930e70(s64 param_1, u64 param_2)
{
    FUN_7103930ea0(param_1 + 0xa0, param_2);
}

// 0x7103931350 -- wrapper: FUN_7103931b70(param_1) (48 bytes)
void FUN_7103931350(u64 param_1) { FUN_7103931b70(param_1); }

// 0x71039323c0 -- deref u64 from FUN_7103932470(param_1) (48 bytes)
u64 FUN_71039323c0(u64 param_1) { return *(u64*)(s64)FUN_7103932470(param_1); }

// 0x71039323f0 -- deref u32 from FUN_7103932420(param_1) (48 bytes)
u64 FUN_71039323f0(u64 param_1) { return *(u32*)(s64)FUN_7103932420(param_1); }

// 0x7103932ee0 -- wrapper: FUN_7103933050(p1, p2) (48 bytes)
void FUN_7103932ee0(u64 param_1, u64 param_2) { FUN_7103933050(param_1, param_2); }

// 0x7103933260 -- deref u8 from FUN_71039337a0(param_1) (48 bytes)
u8 FUN_7103933260(u64 param_1) { return *FUN_71039337a0(param_1); }

// 0x7103933320 -- deref u64 from FUN_7103933750(param_1) (48 bytes)
u64 FUN_7103933320(u64 param_1) { return *(u64*)(s64)FUN_7103933750(param_1); }

// 0x7103933350 -- deref u64 from FUN_7103933700(param_1) (48 bytes)
u64 FUN_7103933350(u64 param_1) { return *(u64*)(s64)FUN_7103933700(param_1); }

// 0x710381f7b0 -- call FUN_710381a6d0 with abs-xor of field (48 bytes)
// param_1 [inferred: struct with s32 value at +0x10 and data at +0x18]
//   +0x10 [inferred: s32 value, abs() computed via xor trick]
//   +0x18 [inferred: pointer/data passed as second arg to FUN_710381a6d0]
void FUN_710381f7b0(s64 param_1)
{
    FUN_710381a6d0(*(u32*)(param_1 + 0x10) ^ (s32)*(u32*)(param_1 + 0x10) >> 0x1f, param_1 + 0x18);
}
