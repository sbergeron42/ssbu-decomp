#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71039 address range, batch d-009
// Pool-d worker: auto-generated from Ghidra decompilation
// Mix of 32-byte one-liners and small wrappers

// ---- External declarations -----------------------------------------------

extern "C" {
    int* __errno_location(void);
}

namespace nn { namespace os {
    extern void sched_getcpu();
    extern void* GetCurrentThread();
}}

extern void FUN_71039295c0();
extern void FUN_71039294b0();
extern void FUN_710392abf0();
extern void FUN_710392ed50(void*);
extern void FUN_710393fb50(u32);
extern void FUN_7103944a60();
extern void FUN_7103949660();
extern void FUN_710395f750();
extern void FUN_71038d7000(u32, u32*);

// External data
extern u8 DAT_7106d4a668[];
extern u8 DAT_7106d4a670[];
extern u8 DAT_7106dd40b8[];

// ---- Functions ---------------------------------------------------------------

// 0x710395d360 -- return param_1 + 3 (32 bytes)
s64 FUN_710395d360(s64 param_1) { return param_1 + 3; }

// 0x710395d3b0 -- no-op (32 bytes)
void FUN_710395d3b0(void) { return; }

// 0x710395eaa0 -- return *param_1 < 2 (32 bytes)
u8 FUN_710395eaa0(u8 *param_1) { return (u8)(*param_1 < 2); }

// 0x710395eb50 -- return param_1 + 3 (32 bytes)
s64 FUN_710395eb50(s64 param_1) { return param_1 + 3; }

// 0x710395eba0 -- return param_1 + 1 (32 bytes)
s64 FUN_710395eba0(s64 param_1) { return param_1 + 1; }

// 0x710395ee90 -- return param_1 + 0x28 (32 bytes)
// +0x28 [inferred: sub-object/field address, returned as pointer]
s64 FUN_710395ee90(s64 param_1) { return param_1 + 0x28; }

// 0x710395eee0 -- return param_1 + 2 (32 bytes)
s64 FUN_710395eee0(s64 param_1) { return param_1 + 2; }

// 0x710395ef30 -- return param_1 + 8 (32 bytes)
// +0x08 [inferred: sub-object/field address, returned as pointer]
s64 FUN_710395ef30(s64 param_1) { return param_1 + 8; }

// 0x710395f440 -- return param_1 == 0 (32 bytes)
u8 FUN_710395f440(s64 param_1) { return (u8)(param_1 == 0); }

// 0x710395f4b0 -- return param_1 + 0x1800 (32 bytes)
// +0x1800 [inferred: large embedded sub-object, seen in multiple container classes]
s64 FUN_710395f4b0(s64 param_1) { return param_1 + 0x1800; }

// 0x710395fab0 -- return *param_1 == 0 (32 bytes)
u8 FUN_710395fab0(s32 *param_1) { return (u8)(*param_1 == 0); }

// 0x710395fad0 -- deref u32 (32 bytes)
u64 FUN_710395fad0(u32 *param_1) { return *param_1; }

// 0x710395fcf0 -- no-op (32 bytes)
void FUN_710395fcf0(void) { return; }

// 0x7103927ae0 -- identity u64 (32 bytes)
u64 FUN_7103927ae0(u64 param_1) { return param_1; }

// 0x710392feb0 -- zero out u64 field (32 bytes)
void FUN_710392feb0(u64 *param_1) { *param_1 = 0; }

// 0x71039302e0 -- identity u64 (32 bytes)
u64 FUN_71039302e0(u64 param_1) { return param_1; }

// 0x7103932870 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
u64 FUN_7103932870(s64 param_1) { return *(u64*)(param_1 + 8); }

// 0x7103932b40 -- return param_1 + 0x40 (32 bytes)
// +0x40 [inferred: sub-object/field address, returned as pointer]
s64 FUN_7103932b40(s64 param_1) { return param_1 + 0x40; }

// 0x7103935f80 -- no-op (32 bytes)
void FUN_7103935f80(void) { return; }

// 0x7103938910 -- identity u64 (32 bytes)
u64 FUN_7103938910(u64 param_1) { return param_1; }

// 0x7103939580 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
u64 FUN_7103939580(s64 param_1) { return *(u64*)(param_1 + 8); }

// 0x710393c150 -- zero out u64 field (32 bytes)
void FUN_710393c150(u64 *param_1) { *param_1 = 0; }

// 0x710393fc90 -- no-op (32 bytes)
void FUN_710393fc90(void) { return; }

// 0x7103944830 -- identity u64 (32 bytes)
u64 FUN_7103944830(u64 param_1) { return param_1; }

// 0x7103944a40 -- no-op (32 bytes)
void FUN_7103944a40(void) { return; }

// 0x7103944cf0 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
u64 FUN_7103944cf0(s64 param_1) { return *(u64*)(param_1 + 8); }

// 0x7103946080 -- zero out u64 field (32 bytes)
void FUN_7103946080(u64 *param_1) { *param_1 = 0; }

// 0x7103947060 -- identity u64 (32 bytes)
u64 FUN_7103947060(u64 param_1) { return param_1; }

// 0x71039497a0 -- no-op (32 bytes)
void FUN_71039497a0(void) { return; }

// 0x7103950e00 -- identity u64 (32 bytes)
u64 FUN_7103950e00(u64 param_1) { return param_1; }

// 0x7103929120 -- wrapper: nn::os::sched_getcpu() (32 bytes)
void FUN_7103929120(void) { nn::os::sched_getcpu(); }

// 0x7103933610 -- wrapper: nn::os::sched_getcpu() (32 bytes)
void FUN_7103933610(void) { nn::os::sched_getcpu(); }

// 0x7103951bb0 -- wrapper: nn::os::sched_getcpu() (32 bytes)
void FUN_7103951bb0(void) { nn::os::sched_getcpu(); }

// 0x710395d1c0 -- wrapper: nn::os::sched_getcpu() (32 bytes)
void FUN_710395d1c0(void) { nn::os::sched_getcpu(); }

// 0x710395fbe0 -- wrapper: nn::os::GetCurrentThread() (discards result) (32 bytes)
void FUN_710395fbe0(void) { nn::os::GetCurrentThread(); }

// 0x710395fb80 — store GetCurrentThread() result to global (32 bytes)
// DAT_7106dd40b8 [inferred: global pointer, stores current thread handle]
u32 FUN_710395fb80(void) { *(void**)DAT_7106dd40b8 = nn::os::GetCurrentThread(); }

// 0x7103929470 — wrapper: call FUN_71039295c0() (32 bytes)
u32 FUN_7103929470(void) { FUN_71039295c0(); }

// 0x7103929490 — wrapper: call FUN_71039294b0() (32 bytes)
u32 FUN_7103929490(void) { FUN_71039294b0(); }

// 0x710392abd0 — wrapper: call FUN_710392abf0() (32 bytes)
u32 FUN_710392abd0(void) { FUN_710392abf0(); }

// 0x71039353c0 -- wrapper: FUN_710392ed50(&DAT_7106d4a668) (32 bytes)
void FUN_71039353c0(void) { FUN_710392ed50(DAT_7106d4a668); }

// 0x7103935440 -- wrapper: FUN_710392ed50(&DAT_7106d4a670) (32 bytes)
void FUN_7103935440(void) { FUN_710392ed50(DAT_7106d4a670); }

// 0x710393fa80 — wrapper: FUN_710393fb50(1) (32 bytes)
u32 FUN_710393fa80(void) { FUN_710393fb50(1); }

// 0x7103944810 — wrapper: call FUN_7103944a60() (32 bytes)
u32 FUN_7103944810(void) { FUN_7103944a60(); }

// 0x7103949530 — wrapper: call FUN_7103949660() (32 bytes)
u32 FUN_7103949530(void) { FUN_7103949660(); }

// 0x710395f730 — wrapper: call FUN_710395f750() (32 bytes)
u32 FUN_710395f730(void) { FUN_710395f750(); }

// 0x710392b210 -- read errno via __errno_location (32 bytes)
s32 FUN_710392b210(void) { return *__errno_location(); }

// 0x71038d70c0 -- call FUN_71038d7000 with abs-xor of *param_1 (32 bytes)
void FUN_71038d70c0(u32 *param_1)
{
    FUN_71038d7000(*param_1 ^ (s32)*param_1 >> 0x1f, param_1 + 2);
}
