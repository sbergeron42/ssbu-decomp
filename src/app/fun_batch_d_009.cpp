#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71039 address range, batch d-009
// Pool-e worker: optnone for -O0 stubs, asm barriers for nop generation

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

// External data — hidden visibility for direct ADRP+ADD access (no GOT)
extern __attribute__((visibility("hidden"))) u8 DAT_7106d4a668[];
extern __attribute__((visibility("hidden"))) u8 DAT_7106d4a670[];
extern __attribute__((visibility("hidden"))) void* DAT_7106dd40b8;

// ===========================================================================
// Group 1: Framed -O0 functions (optnone, no nops)
// ===========================================================================

// 0x710395d360 -- return param_1 + 3 (24 bytes)
__attribute__((optnone))
s64 FUN_710395d360(s64 param_1) { return param_1 + 3; }

// 0x710395eb50 -- return param_1 + 3 (24 bytes)
__attribute__((optnone))
s64 FUN_710395eb50(s64 param_1) { return param_1 + 3; }

// 0x710395eba0 -- return param_1 + 1 (24 bytes)
__attribute__((optnone))
s64 FUN_710395eba0(s64 param_1) { return param_1 + 1; }

// 0x710395ee90 -- return param_1 + 0x28 (24 bytes)
// +0x28 [inferred: sub-object/field address, returned as pointer]
__attribute__((optnone))
s64 FUN_710395ee90(s64 param_1) { return param_1 + 0x28; }

// 0x710395eee0 -- return param_1 + 2 (24 bytes)
__attribute__((optnone))
s64 FUN_710395eee0(s64 param_1) { return param_1 + 2; }

// 0x710395ef30 -- return param_1 + 8 (24 bytes)
// +0x08 [inferred: sub-object/field address, returned as pointer]
__attribute__((optnone))
s64 FUN_710395ef30(s64 param_1) { return param_1 + 8; }

// 0x710395f4b0 -- return param_1 + 0x1800 (28 bytes)
// +0x1800 [inferred: large embedded sub-object, seen in multiple container classes]
__attribute__((optnone))
s64 FUN_710395f4b0(s64 param_1) { return param_1 + 0x1800; }

// 0x710395eaa0 -- return *param_1 < 2 (32 bytes)
__attribute__((optnone))
u8 FUN_710395eaa0(u8 *param_1) { return (u8)(*param_1 < 2); }

// 0x710395f440 -- return param_1 == 0 (28 bytes)
__attribute__((optnone))
u8 FUN_710395f440(s64 param_1) { return (u8)(param_1 == 0); }

// 0x710395fab0 -- return *param_1 == 0 (32 bytes)
__attribute__((optnone))
u8 FUN_710395fab0(s32 *param_1) { return (u8)(*param_1 == 0); }

// 0x710395fad0 -- deref u32 (24 bytes)
__attribute__((optnone))
u64 FUN_710395fad0(u32 *param_1) { return *param_1; }

// ===========================================================================
// Group 2: Framed -O0 functions with 2 nops before body
// ===========================================================================

// 0x7103927ae0 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_7103927ae0(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x71039302e0 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_71039302e0(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x7103938910 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_7103938910(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x7103944830 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_7103944830(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x7103947060 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_7103947060(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x7103950e00 -- identity u64 (28 bytes)
__attribute__((optnone))
u64 FUN_7103950e00(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1; }

// 0x7103935f80 -- no-op with param (24 bytes)
__attribute__((optnone))
void FUN_7103935f80(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); }

// 0x7103944a40 -- no-op with param (24 bytes)
__attribute__((optnone))
void FUN_7103944a40(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); }

// 0x71039497a0 -- no-op with param (24 bytes)
__attribute__((optnone))
void FUN_71039497a0(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); }

// 0x710393fc90 -- no-op with param (24 bytes)
__attribute__((optnone))
void FUN_710393fc90(u64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); }

// 0x7103932870 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
__attribute__((optnone))
u64 FUN_7103932870(s64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return *(u64*)(param_1 + 8); }

// 0x7103939580 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
__attribute__((optnone))
u64 FUN_7103939580(s64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return *(u64*)(param_1 + 8); }

// 0x7103944cf0 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned]
__attribute__((optnone))
u64 FUN_7103944cf0(s64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return *(u64*)(param_1 + 8); }

// 0x7103932b40 -- return param_1 + 0x40 (32 bytes)
// +0x40 [inferred: sub-object/field address, returned as pointer]
__attribute__((optnone))
s64 FUN_7103932b40(s64 param_1) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); return param_1 + 0x40; }

// ===========================================================================
// Group 3: Framed -O0 functions with nop before + after body
// ===========================================================================

// 0x710392feb0 -- zero out u64 field (32 bytes)
__attribute__((optnone))
void FUN_710392feb0(u64 *param_1) { asm volatile("b 1f\n1:"); *param_1 = 0; asm volatile("b 1f\n1:"); }

// 0x710393c150 -- zero out u64 field (32 bytes)
__attribute__((optnone))
void FUN_710393c150(u64 *param_1) { asm volatile("b 1f\n1:"); *param_1 = 0; asm volatile("b 1f\n1:"); }

// 0x7103946080 -- zero out u64 field (32 bytes)
__attribute__((optnone))
void FUN_7103946080(u64 *param_1) { asm volatile("b 1f\n1:"); *param_1 = 0; asm volatile("b 1f\n1:"); }

// ===========================================================================
// Group 4: Framed -O0 with larger frame (48 bytes)
// ===========================================================================

// 0x710395d3b0 -- no-op with 3 params (24 bytes, frame=48)
__attribute__((optnone))
void FUN_710395d3b0(u64 param_1, u32 param_2, u32 param_3) {
    u64 pad1, pad2, pad3, pad4;
}

// 0x710395fcf0 -- no-op with local=1 (28 bytes, frame=48)
// Takes (u64, u32), initializes a u32 local to 1
__attribute__((optnone))
void FUN_710395fcf0(u64 param_1, u32 param_2) {
    u32 local = 1;
    u64 pad1, pad2, pad3;
}

// ===========================================================================
// Group 5: Non-leaf wrappers with nops (stp x29,x30 prologue)
// ===========================================================================

// 0x7103929120 -- wrapper: nn::os::sched_getcpu() (28 bytes)
__attribute__((optnone))
void FUN_7103929120(void) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); nn::os::sched_getcpu(); asm volatile(""); }

// 0x7103933610 -- wrapper: nn::os::sched_getcpu() (28 bytes)
__attribute__((optnone))
void FUN_7103933610(void) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); nn::os::sched_getcpu(); asm volatile(""); }

// 0x7103951bb0 -- wrapper: nn::os::sched_getcpu() (28 bytes)
__attribute__((optnone))
void FUN_7103951bb0(void) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); nn::os::sched_getcpu(); asm volatile(""); }

// 0x710395d1c0 -- wrapper: nn::os::sched_getcpu() (28 bytes)
__attribute__((optnone))
void FUN_710395d1c0(void) { asm volatile("b 1f\n1:"); asm volatile("b 1f\n1:"); nn::os::sched_getcpu(); asm volatile(""); }

// ===========================================================================
// Group 6: Non-leaf wrappers without nops (stp x29,x30 prologue)
// ===========================================================================

// 0x710395fbe0 -- wrapper: nn::os::GetCurrentThread() (discards result) (20 bytes)
__attribute__((optnone))
void FUN_710395fbe0(void) { nn::os::GetCurrentThread(); asm volatile(""); }

// 0x710395fb80 -- store GetCurrentThread() result to global (28 bytes)
// DAT_7106dd40b8 [inferred: global pointer, stores current thread handle]
void FUN_710395fb80(void) { DAT_7106dd40b8 = nn::os::GetCurrentThread(); asm volatile(""); }

// 0x7103929470 -- wrapper: call FUN_71039295c0() (20 bytes)
__attribute__((optnone))
void FUN_7103929470(void) { FUN_71039295c0(); asm volatile(""); }

// 0x7103929490 -- wrapper: call FUN_71039294b0() (20 bytes)
__attribute__((optnone))
void FUN_7103929490(void) { FUN_71039294b0(); asm volatile(""); }

// 0x710392abd0 -- wrapper: call FUN_710392abf0() (20 bytes)
__attribute__((optnone))
void FUN_710392abd0(void) { FUN_710392abf0(); asm volatile(""); }

// 0x71039353c0 -- wrapper: FUN_710392ed50(&DAT_7106d4a668) (24 bytes)
__attribute__((optnone))
void FUN_71039353c0(void) { FUN_710392ed50(DAT_7106d4a668); asm volatile(""); }

// 0x7103935440 -- wrapper: FUN_710392ed50(&DAT_7106d4a670) (24 bytes)
__attribute__((optnone))
void FUN_7103935440(void) { FUN_710392ed50(DAT_7106d4a670); asm volatile(""); }

// 0x710393fa80 -- wrapper: FUN_710393fb50(1) (24 bytes)
__attribute__((optnone))
void FUN_710393fa80(void) { FUN_710393fb50(1); asm volatile(""); }

// 0x7103944810 -- wrapper: call FUN_7103944a60() (20 bytes)
__attribute__((optnone))
void FUN_7103944810(void) { FUN_7103944a60(); asm volatile(""); }

// 0x7103949530 -- wrapper: call FUN_7103949660() (20 bytes)
__attribute__((optnone))
void FUN_7103949530(void) { FUN_7103949660(); asm volatile(""); }

// 0x710395f730 -- wrapper: call FUN_710395f750() (20 bytes)
__attribute__((optnone))
void FUN_710395f730(void) { FUN_710395f750(); asm volatile(""); }

// 0x710392b210 -- read errno via __errno_location (24 bytes)
__attribute__((optnone))
s32 FUN_710392b210(void) { return *__errno_location(); }

// 0x71038d70c0 -- call FUN_71038d7000 with abs() of *param_1 (32 bytes)
// param_1: struct with s32 value at +0x00 and data at +0x08
//   +0x00 [inferred: s32 value, abs() computed via xor-with-sign trick]
//   +0x08 [inferred: data pointer passed as second arg to FUN_71038d7000 (param_1+2 = +8 bytes)]
void FUN_71038d70c0(u32 *param_1)
{
    FUN_71038d7000(*param_1 ^ (s32)*param_1 >> 0x1f, param_1 + 2);
    asm volatile("");
}
