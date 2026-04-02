#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7102-0x7103 address range, batch e2-011
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" void FUN_71032e47c0(u64, s32, s32, s32, s32, s32);
extern "C" u64  DAT_710532e7c8 HIDDEN;
extern "C" u32  FUN_7103300dd0();

// ---- WorkModule flag setters (continuation from e2-010) -----------------------------------------------

// FUN_710275d7ec, FUN_7102a66198, FUN_7102a66768, FUN_7102a667c8, FUN_7102a66828
// — compiled in fun_batch_c2_001.cpp

// ---- abort() wrappers (12-16 bytes each) -----------------------------------------------
// [[noreturn]] generates stp+mov+bl without epilogue


















// FUN_7103344c38 — compiled in fun_batch_d_016.cpp

// ---- simple wrappers -----------------------------------------------

