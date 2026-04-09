#include "types.h"

// global_param_init_sets_team_flag @ 0x71017641a0 (6,796 bytes)
//
// Massive initialization function that resets all match/CSS global parameters
// to default values before a match starts. Called from CSS transitions.
// Sets g_is_team_battle flag, initializes player slots, allocates buffers,
// and calls numerous subsystem init functions.
//
// This is a NON-MATCHING stub. The function is too large (~300 globals)
// to byte-match without extensive manual effort. The structural elements
// (memset calls, subsystem inits, OOM alloc pattern, loop) are preserved.

// ============================================================
// External function declarations
// ============================================================

extern "C" void* memset(void*, int, u64);
extern "C" void* je_aligned_alloc(u64 alignment, u64 size);

// Subsystem init functions (called sequentially)
extern "C" void FUN_71017a79f0(void*);   // Initializes 0x71052c4730 region
extern "C" void FUN_7101765c30(void*);   // Player slot init (called twice: 0x71052c9dc8, 0x71052ca9d0)
extern "C" void FUN_71017a86b0(void*);   // Extended region init (called twice: 0x71052cb5d8, 0x71052e7b60)
extern "C" void FUN_71017ab8f0(void*);   // Online state init at 0x7105305970
extern "C" void FUN_71017bd350(void*);   // Init at 0x7105306b78
extern "C" void FUN_710179b9e0(void*);   // Init at 0x7105306d50
extern "C" void FUN_7103351390(void*);   // Init at 0x7105307428
extern "C" void FUN_71017abc60(void*);   // Init at 0x7105307570
extern "C" void FUN_71017abd40(void*);   // Player deep-copy init (called 8+9 times for player slots)
extern "C" void FUN_710179bbd0(void*);   // Init at 0x71053099c8
extern "C" void FUN_71017ac230(void*);   // Init at 0x710530c568
extern "C" void FUN_710179a0c0(void*);   // Init at 0x710530c7d8
extern "C" void FUN_710179d180(void*);   // Init at 0x710530d398
extern "C" void FUN_71017ac210(void*);   // Called 3 times for DAT_71053098d8/9908/9938

// Hash lookup functions (for DLC bitmask computation)
extern "C" u64 FUN_71032b1e30(u64, u64); // hash40 combine
extern "C" s32 FUN_71032b1890(void*, u64); // hash40 lookup, returns index or -1

// ============================================================
// Sentinel value
// ============================================================
// Ghidra shows &DAT_c1ffff0000000000 — this is actually the 64-bit
// immediate 0xc1ffff0000000000 stored as a pointer-width value.
// It represents a NaN-boxed sentinel (float: -0x1.fffe00000000p+67 = invalid).
static const u64 SENTINEL = 0xc1ffff0000000000ULL;

// ============================================================
// BSS Region 1: Team/match param globals (0x71052c4180 - 0x71052c45c8)
// ============================================================

// Zero-initialized u64 block (0x71052c4180 - 0x71052c41b0)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4180; // overlaps smaller syms
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4188;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4190;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4198;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41b0;

// More zero-init globals (0x71052c41b8 - 0x71052c41d8)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41d0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71052c41d7;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41d8;

// Team battle / match config (0x71052c41e0 - 0x71052c4260)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41e8; // g_is_team_battle_flag
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c41f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4200;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4208; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4210; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4218; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4220; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4228; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4230; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4238; // set to 0xffffffffffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4240;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4248;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4250;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4258;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4260;

// Sentinel pointer block 2 (0x71052c4278 - 0x71052c4380)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4278;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4280;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4298;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c42f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4300;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4308;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4310;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4318;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4320;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4328;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4330;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4338;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4340;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4348;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4350;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4358;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4360;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4368;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4370;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4378;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4380;

// Sentinel pointer block 1 (0x71052c4388 - 0x71052c45a8)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4388;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4390;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4398;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c43f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4400;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4408;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4410;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4418;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4420;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4428;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4430;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4438;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4440;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4448;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4450;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4458;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4460;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4468;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4470;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4478;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4480;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4488;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4490;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4498;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c44f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4500;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4508;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4510;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4518;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4520;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4528;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4530;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4538;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4540;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4548;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4550;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4558;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4560;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4568;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4570;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4578;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4580;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4588;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4590;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4598;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45a8;

// End of sentinel region
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45c8;

// ============================================================
// BSS Region 2: Match config struct (0x71052c45d0 - 0x71052c472c)
// memset zeroed first, then individual fields set
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8  DAT_71052c45d0_region[0x160];
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c45d0; // set to 0xffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c45f8; // 0xd9ffff0000000000
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4600;

// Match config stride-8 fields (0x71052c4604 - 0x71052c4674)
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4604;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c460c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4614;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c461c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4624;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c462c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4634;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c463c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4644;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c464c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4654;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c465c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4664;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c466c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4674;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c467c;

// Second match config block (0x71052c4680 - 0x71052c472c)
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4680; // 0xffffffff
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4688;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4690;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c4698;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c46a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c46a8; // 0xd9ffff0000000000
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c46b0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46b4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46bc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46c4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46cc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46d4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46dc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46e4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46ec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c46fc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4704;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c470c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4714;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c471c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c4724;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71052c472c;

// ============================================================
// BSS Region 3: FUN_71017a79f0 region (0x71052c4730)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052c4730;

// ============================================================
// BSS Region 4: 0x4018-byte zeroed region + 0x40-byte entry loop (0x71052c5c98)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052c5c98;

// Loop initializes 0x100 entries of 0x40 bytes each starting at 0x71052c5c98
// Each 0x40-byte entry has fields cleared at specific offsets

// ============================================================
// BSS Region 5: Pre-player-slot data (0x71052c9cb0 - 0x71052c9db8)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cb0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cb8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cc0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cc8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cd0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cd8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9ce0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9ce8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cf0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9cf8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d00;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d08;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d10;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d18;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d20;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d28;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d30;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d38;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d40;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d48;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d50;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d58;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d60;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d68;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d70;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71052c9d75[8]; // partial overlap
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d80;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d88;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d90;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9d98;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9da0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9da8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9db0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71052c9db8;

// ============================================================
// BSS Region 6: Player slot data — memset 0x1818 bytes (0x71052c9dc0)
// Then FUN_7101765c30 called twice, FUN_71017a86b0 called twice
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052c9dc0;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052c9dc8;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052ca9d0;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052cb5d8;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_71052e7b60;

// ============================================================
// BSS Region 7: Match configuration (0x71053040f0 - 0x710530459c)
// Param data pointer, game mode config, DLC bitmask setup
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_710532e730; // global param data pointer

extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053040f0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053040f4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053040f8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304100;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304104;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105304109[8]; // partial overlap
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304150;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304158;

// Player slot config 1 (0x71052c4558 - 0x710530459e)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304558;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530455c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304564;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530456c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530459c;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530459e;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053045a0;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053045a4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053045a6;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045a7; // multi-byte packed
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053045af; // Ghidra: 0x10300, wider than u16
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053045b3;

// DLC bitmask region
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045c8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053045d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045d4;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053045d6;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053045de;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053045e0[4]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053045e3[2]; // partial
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053045f0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053045f5[8]; // partial overlap
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530463c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304644;

// Player slot configs 2-5 (repeated pattern, ~0x4D8 stride)
// Slot 2 (0x7105304a44 - 0x7105304abc)
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304a44;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304a48;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304a50;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304a58;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304a88;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105304a8a;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304a8c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304a8e; // packed, Ghidra: 0x200000503
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304a96; // packed
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105304a9e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105304aa0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304aa4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304aac;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304ab4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304abc;

// Slot 2 continued
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304ac0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304ac8;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105304acd[8];
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304b14;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304b1c;

// Slot 3 (0x7105304f1c - 0x7105304f94)
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304f1c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f20;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f28;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f30;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304f60;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105304f62;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304f64;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f66; // packed, Ghidra: 0x200000503
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f6e;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105304f76;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105304f78;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f7c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f84;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f8c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304f94;

// Slot 3 continued
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304f98;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105304fa0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105304fa5[8];
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304fec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105304ff4;

// Slot 4 (0x71053053f4 - 0x710530546c)
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053053f4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053053f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305400;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305408;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305438;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530543a;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530543c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530543e; // packed, Ghidra: 0x200000503
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305446;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530544e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105305450;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305454;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530545c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305464;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530546c;

// Slot 5 base (0x7105305470 - 0x71052c595c)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305470;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305478;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305480;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530547c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305488;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530548c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105305491[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053054d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053054e0;

extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053058e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053058e4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053058ec;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053058f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305924;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105305926;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305928;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530592a;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530592b;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305933;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530593b;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305940;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305948;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105305950;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305958;

extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530595c;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530595e;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105305966;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105305968;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530596c;

// ============================================================
// BSS Region 8: Online state (0x7105305970)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105305970;

// ============================================================
// BSS Region 9: Additional state (0x7105306b68 - 0x7105306d50)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105306b68;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306b70;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105306b78;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306c88;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306c90;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306ca8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306cb0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306cb8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105306cbc;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306d18;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306d28[2]; // 6 + 2 bytes partial
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306d30;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306d38;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105306d40;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105306d50;

// ============================================================
// BSS Region 10: Match result / score data (0x7105307130 - 0x71053073d0)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307130;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307134;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307138; // memset 0x18c
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053072c4;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053072c6;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053072c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053072d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053072d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053072e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053072e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053072ec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053072f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307300;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307308;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307310;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307318;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307320;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307330;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307338;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307340;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307348;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307350;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307358;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307360;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307364;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530736c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530739c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073a4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073a8;

// Allocated vector buffer
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053073b0; // alloc base ptr
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053073b8; // current ptr
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053073c0; // end ptr (base + 0xc6)
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053073c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053073d0; // second alloc ptr

extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073d8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073dc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073e4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073ec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053073fc;

// ============================================================
// BSS Region 11: FUN_7103351390 region (0x7105307428)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307428;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307434;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074a4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053074f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307500;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307508;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307510;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307518;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307520;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307528;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307530;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307534;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307538;

// FNV hash init values
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530742c; // 0x811c9dc5
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530749c; // 0x811c9dc5

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307408;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307410;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307418;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307420;

// memset 0x210 region
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105307540;

// FUN_71017abc60 region
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105307570;

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307750;

// ============================================================
// BSS Region 12: CSS player slot data (8 player slots)
// Each slot: header at +0x00, FUN_71017abd40 at +0x38 offset
// Stride: 0x1C8 per slot
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307760;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105307768;
extern "C" __attribute__((visibility("hidden"))) u8  BSS_CSS_DATA_ARRAY; // 0xe40 bytes zeroed
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307774;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530777c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307794;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307798;

// Player slot 1
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307938;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530793c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307944;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530795c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307960;

// Player slot 2
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307b00;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307b04;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307b0c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307b24;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307b28;

// Player slot 3
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307cc8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307ccc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307cd4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307cec;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307cf0;

// Player slot 4
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307e90;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307e94;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307e9c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105307eb4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105307eb8;

// Player slot 5
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308058;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530805c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308064;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530807c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308080;

// Player slot 6
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308220;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308224;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530822c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308244;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308248;

// Player slot 7
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053083e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053083ec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053083f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530840c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308410;

// ============================================================
// BSS Region 13: CSS second data array + extended player data
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8  BSS_CSS_SECOND_ARRAY; // 0x1200 bytes zeroed
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085cc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053085d4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053085e0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308610;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308614;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308615[8]; // partial
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308620;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308628;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308630;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308638;

// Extended player structs (8 slots, stride ~0x240)
// Each has: flag byte, magic 0xb95d0753f, 0xff, various -1 fields, f32 1.0f pairs, FUN_71017abd40
// Slot 0: 0x71053087d8 - 0x7105308878
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053087d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053087e0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053087e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053087f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053087f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308800;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308808;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530880c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308814;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308818;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308820;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308850;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308854;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308855[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308860;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308868;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308870;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308878;

// Slot 1: 0x7105308a18 - 0x7105308ab8
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308a18;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a20;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308a28;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308a30;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a38;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a40;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a48;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a4c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308a54;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a58;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308a60;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308a90;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308a94;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308a95[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308aa0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308aa8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ab0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308ab8;

// Slot 2: 0x7105308c58 - 0x7105308cf8
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308c58;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c60;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308c68;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308c70;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c78;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c80;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c88;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c8c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308c94;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308c98;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ca0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308cd0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308cd4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308cd5[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ce0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ce8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308cf0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308cf8;

// Slot 3: 0x7105308e98 - 0x7105308f38
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308e98;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ea0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308ea8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308eb0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308eb8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ec0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ec8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ecc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308ed4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ed8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308ee0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308f10;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105308f14;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308f15[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308f20;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308f28;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105308f30;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105308f38;

// Slot 4: 0x71053090d8 - 0x7105309178
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053090d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053090e0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053090e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053090f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053090f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309100;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309108;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530910c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309114;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309118;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309120;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309150;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309154;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309155[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309160;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309168;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309170;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309178;

// Slot 5: 0x7105309318 - 0x71053093b8
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309318;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309320;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309328;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309330;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309338;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309340;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309348;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530934c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309354;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309358;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309360;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309390;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309394;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309395[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053093a0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053093a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053093b0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053093b8;

// Slot 6: 0x7105309558 - 0x71053095f8
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309558;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309560;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309568;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309570;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309578;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309580;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309588;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530958c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309594;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309598;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053095a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053095d0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053095d4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053095d5[8];
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053095e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053095e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053095f0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053095f8;

// Slot 7: 0x7105309798 - 0x7105309810 (last slot, different pattern)
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105309798;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053097a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053097f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309800;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309808;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309810;

// memset 0x150 region
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105309818;

// ============================================================
// BSS Region 14: FUN_71017ac210 regions + CSS config
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u8 DAT_71053098d8;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105309908;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7105309938;

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309968;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530996c[8]; // partial overlap
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309974;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105309976;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105309978;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530997a[2]; // packed
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309980[1]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105309988;

// CSS named globals
extern "C" __attribute__((visibility("hidden"))) u16 CSS_MODE_FLAGS;        // 0x710530998e region
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710530998e;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105309996;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105309998[1]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530999b[2]; // partial
extern "C" __attribute__((visibility("hidden"))) u8  CSS_MAX_PLAYER_COUNT;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053099b0;       // DLC bitmask base
extern "C" __attribute__((visibility("hidden"))) u64 CSS_INITIAL_PLAYER_BITMASK;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053099b4[1]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053099b8[1]; // partial _4_4_
extern "C" __attribute__((visibility("hidden"))) u64 CSS_MAX_SLOTS_VARIANT;

// ============================================================
// BSS Region 15: CSS state + team config (0x71053099c0 - 0x710530d398)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053099c0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053099c8;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530c568;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530c7d0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530c7d8;

extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710530d2a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2b0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2f0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d2f8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d300;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d308;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d310;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d318;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d320;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d328;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d330;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d338;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d340;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d348;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d350;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d358;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d360;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d368;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d370;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d378;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d380;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530d38c[4]; // partial
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d388[1]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710530d390[1]; // ram0x..
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710530d398;

// ============================================================
// BSS Region 16: Final state (0x7105312f00 - 0x71053134c8)
// ============================================================

extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f00;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105312f08_region; // memset 0x5c8
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105312f08;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f0c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f10;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f18;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f38;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105312f40;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f5c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f60;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f68;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f70;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f78;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f80;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f84;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f88;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f8c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312f90;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312f98;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105312f9c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312fb4;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105312fb8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105312fbc;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312fc0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312fc8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105312fe8;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_7105312ff0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531300c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313010;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313018;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313020;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313028;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313030;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313034;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313038;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531303c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313040;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313044;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313048;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531304c;

// Repeated config slots (stride ~0xB0)
// Config slot 2
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313064;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313068;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313069;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531306c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313070;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313078;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313098;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531309c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130a0;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053130bc;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053130be;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053130bf;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053130c8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053130d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053130d8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130e0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130e4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130ec;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130f0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130f8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053130fc;

// Config slot 3
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313114;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313118;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313119;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531311c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313120;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313128;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313148;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531314c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313150;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710531316c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531316e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531316f;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313170;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313178;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313180;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313188;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313190;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313194;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313198;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531319c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131a4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131a8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131ac;

// Config slot 4
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131c4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053131c8;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053131c9;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131cc;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053131d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053131d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053131f8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053131fc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313200;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710531321c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531321e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531321f;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313220;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313228;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313230;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313238;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313240;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313244;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313248;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531324c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313250;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313254;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313258;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531325c;

// Config slot 5
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313274;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313278;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313279;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531327c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313280;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313288;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053132a8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132ac;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132b0;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_71053132cc;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053132ce;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053132cf;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132d0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053132d8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053132e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053132e8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132f0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132f4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132f8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053132fc;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313300;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313304;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313308;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531330c;

// Config slot 6
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313324;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313328;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_7105313329;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531332c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313330;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313338;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313358;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531335c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313360;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710531337c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531337e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531337f;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313380;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313388;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313390;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313398;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133a4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133a8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133ac;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133b0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133b4;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133b8;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133bc;

// Config slot 7
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133d4;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053133d8;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053133d9;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053133dc;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053133e0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053133e8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313408;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531340c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313410;
extern "C" __attribute__((visibility("hidden"))) u16 DAT_710531342c;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531342e;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_710531342f;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313430;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313438;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313440;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313448;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313450;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313454;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313458;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531345c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313460;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313464;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_7105313468;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531346c;

// Final tail fields
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313484;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_710531348c;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7105313494;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710531349c;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053134a0;
extern "C" __attribute__((visibility("hidden"))) u32 DAT_71053134a4;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053134a8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053134b0;
extern "C" __attribute__((visibility("hidden"))) u8  DAT_71053134bc[4]; // partial
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053134b8;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053134c0;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71053134c8;

// OOM handler singleton
extern "C" __attribute__((visibility("hidden"))) u64* DAT_7105331f00; // vtable at [0]+0x30

// ============================================================
// The function
// ============================================================

extern "C" void global_param_init_sets_team_flag(void) {
    // ================================================================
    // Phase 1: Zero out team/match param globals (0x71052c4180 - 0x71052c41b0)
    // ================================================================
    DAT_71052c41a8 = 0;
    DAT_71052c4180 = 0;
    DAT_71052c41d8 = 0;
    DAT_71052c4198 = 0;
    DAT_71052c41a0 = 0;
    DAT_71052c4188 = 0;
    DAT_71052c4190 = 0;
    DAT_71052c41b0 = 0;
    DAT_71052c4250 = 0;

    // ================================================================
    // Phase 2: Set ~70 pointers to sentinel value 0xc1ffff0000000000
    // These are NaN-boxed floats used as "invalid/uninitialized" markers
    // ================================================================
    DAT_71052c4388 = SENTINEL;
    DAT_71052c4390 = SENTINEL;
    DAT_71052c4398 = SENTINEL;
    DAT_71052c43a0 = SENTINEL;
    DAT_71052c43a8 = SENTINEL;
    DAT_71052c43b0 = SENTINEL;
    DAT_71052c43b8 = SENTINEL;
    DAT_71052c43c0 = SENTINEL;
    DAT_71052c43c8 = SENTINEL;
    DAT_71052c43d0 = SENTINEL;
    DAT_71052c43d8 = SENTINEL;
    DAT_71052c43e0 = SENTINEL;
    DAT_71052c43e8 = SENTINEL;
    DAT_71052c43f0 = SENTINEL;
    DAT_71052c43f8 = SENTINEL;
    DAT_71052c4400 = SENTINEL;
    DAT_71052c4408 = SENTINEL;
    DAT_71052c4410 = SENTINEL;
    DAT_71052c4418 = SENTINEL;
    DAT_71052c4420 = SENTINEL;
    DAT_71052c4428 = SENTINEL;
    DAT_71052c4430 = SENTINEL;
    DAT_71052c4438 = SENTINEL;
    DAT_71052c4440 = SENTINEL;
    DAT_71052c4448 = SENTINEL;
    DAT_71052c4450 = SENTINEL;
    DAT_71052c4458 = SENTINEL;
    DAT_71052c4460 = SENTINEL;
    DAT_71052c4468 = SENTINEL;
    DAT_71052c4470 = SENTINEL;
    DAT_71052c4478 = SENTINEL;
    DAT_71052c4480 = SENTINEL;
    DAT_71052c4488 = SENTINEL;
    DAT_71052c4490 = SENTINEL;
    DAT_71052c4498 = SENTINEL;
    DAT_71052c44a0 = SENTINEL;
    DAT_71052c44a8 = SENTINEL;
    DAT_71052c44b0 = SENTINEL;
    DAT_71052c44b8 = SENTINEL;
    DAT_71052c44c0 = SENTINEL;
    DAT_71052c44c8 = SENTINEL;
    DAT_71052c44d0 = SENTINEL;
    DAT_71052c44d8 = SENTINEL;
    DAT_71052c44e0 = SENTINEL;
    DAT_71052c44e8 = SENTINEL;
    DAT_71052c44f0 = SENTINEL;
    DAT_71052c44f8 = SENTINEL;
    DAT_71052c4500 = SENTINEL;
    DAT_71052c4508 = SENTINEL;
    DAT_71052c4510 = SENTINEL;
    DAT_71052c4518 = SENTINEL;
    DAT_71052c4520 = SENTINEL;
    DAT_71052c4528 = SENTINEL;
    DAT_71052c4530 = SENTINEL;
    DAT_71052c4538 = SENTINEL;
    DAT_71052c4540 = SENTINEL;
    DAT_71052c4548 = SENTINEL;
    DAT_71052c4550 = SENTINEL;
    DAT_71052c4558 = SENTINEL;
    DAT_71052c4560 = SENTINEL;
    DAT_71052c4568 = SENTINEL;
    DAT_71052c4570 = SENTINEL;
    DAT_71052c4578 = SENTINEL;
    DAT_71052c4580 = SENTINEL;
    DAT_71052c4588 = SENTINEL;
    DAT_71052c4590 = SENTINEL;
    DAT_71052c4598 = SENTINEL;
    DAT_71052c45a0 = SENTINEL;
    DAT_71052c45a8 = SENTINEL;

    // ================================================================
    // Phase 3: Zero more counters + set -1 invalid indices
    // ================================================================
    DAT_71052c45c0 = 0;
    DAT_71052c45c8 = 0;
    DAT_71052c41c8 = 0;
    DAT_71052c41d0 = 0;
    DAT_71052c41d7 = 0;
    DAT_71052c41b8 = 0;
    DAT_71052c41c0 = 0;
    DAT_71052c4240 = 0;
    DAT_71052c4248 = 0;
    DAT_71052c4200 = 0;
    DAT_71052c4208 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c41f0 = 0;
    DAT_71052c41f8 = 0;
    DAT_71052c41e0 = 0;
    DAT_71052c41e8 = 0; // g_is_team_battle_flag = 0

    // Six u64s set to -1 (invalid player/team indices)
    DAT_71052c4230 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c4238 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c4220 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c4228 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c4210 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71052c4218 = 0xFFFFFFFFFFFFFFFFULL;

    DAT_71052c4258 = 0;
    DAT_71052c4260 = 0;

    // More sentinel pointers
    DAT_71052c4278 = SENTINEL;
    DAT_71052c4280 = 0;
    DAT_71052c4298 = SENTINEL;
    DAT_71052c42a0 = SENTINEL;
    DAT_71052c42a8 = SENTINEL;
    DAT_71052c42b0 = SENTINEL;
    DAT_71052c42b8 = SENTINEL;
    DAT_71052c42c0 = SENTINEL;
    DAT_71052c42c8 = SENTINEL;
    DAT_71052c42d0 = SENTINEL;
    DAT_71052c42d8 = SENTINEL;
    DAT_71052c42e0 = SENTINEL;
    DAT_71052c42e8 = SENTINEL;
    DAT_71052c42f0 = SENTINEL;
    DAT_71052c42f8 = SENTINEL;
    DAT_71052c4300 = SENTINEL;
    DAT_71052c4308 = SENTINEL;
    DAT_71052c4310 = SENTINEL;
    DAT_71052c4318 = SENTINEL;
    DAT_71052c4320 = SENTINEL;
    DAT_71052c4328 = SENTINEL;
    DAT_71052c4330 = SENTINEL;
    DAT_71052c4338 = SENTINEL;
    DAT_71052c4340 = SENTINEL;
    DAT_71052c4348 = SENTINEL;
    DAT_71052c4350 = SENTINEL;
    DAT_71052c4358 = SENTINEL;
    DAT_71052c4360 = SENTINEL;
    DAT_71052c4368 = SENTINEL;
    DAT_71052c4370 = SENTINEL;
    DAT_71052c4378 = SENTINEL;
    DAT_71052c4380 = SENTINEL;

    // ================================================================
    // Phase 4: Match config struct init
    // ================================================================
    memset(&DAT_71052c45d0_region, 0, 0x160);

    DAT_71052c45d0 = 0xFFFFFFFF;
    DAT_71052c45d8 = 0;
    DAT_71052c45e0 = 1;
    DAT_71052c45e8 = 0;
    DAT_71052c45f0 = 0;
    DAT_71052c45f8 = 0xd9ffff0000000000ULL;
    DAT_71052c4600 = 0;

    // Zero 15 stride-8 fields
    DAT_71052c4674 = 0;
    DAT_71052c466c = 0;
    DAT_71052c4664 = 0;
    DAT_71052c465c = 0;
    DAT_71052c4654 = 0;
    DAT_71052c464c = 0;
    DAT_71052c4644 = 0;
    DAT_71052c463c = 0;
    DAT_71052c4634 = 0;
    DAT_71052c462c = 0;
    DAT_71052c4624 = 0;
    DAT_71052c461c = 0;
    DAT_71052c4614 = 0;
    DAT_71052c460c = 0;
    DAT_71052c4604 = 0;

    // Second match config block
    DAT_71052c4690 = 1;
    DAT_71052c467c = 0;
    DAT_71052c4680 = 0xFFFFFFFF;
    DAT_71052c4688 = 0;
    DAT_71052c4698 = 0;
    DAT_71052c46a0 = 0;
    DAT_71052c46a8 = 0xd9ffff0000000000ULL;
    DAT_71052c46b0 = 0;

    DAT_71052c4724 = 0;
    DAT_71052c471c = 0;
    DAT_71052c4714 = 0;
    DAT_71052c470c = 0;
    DAT_71052c4704 = 0;
    DAT_71052c46fc = 0;
    DAT_71052c46f4 = 0;
    DAT_71052c46ec = 0;
    DAT_71052c46e4 = 0;
    DAT_71052c46dc = 0;
    DAT_71052c46d4 = 0;
    DAT_71052c46cc = 0;
    DAT_71052c46c4 = 0;
    DAT_71052c46bc = 0;
    DAT_71052c472c = 0;
    DAT_71052c46b4 = 0;

    // ================================================================
    // Phase 5: FUN_71017a79f0 region init
    // ================================================================
    FUN_71017a79f0(&DAT_71052c4730);

    // ================================================================
    // Phase 6: Zero 0x4018-byte region + loop init 0x100 entries of 0x40 bytes
    // ================================================================
    memset(&DAT_71052c5c98, 0, 0x4018);

    // Initialize 0x100 entries of 0x40 bytes each
    // Each entry: clear fields at offsets within the 0x40-byte struct
    {
        u8* ptr = reinterpret_cast<u8*>(&DAT_71052c5c98) + 0x106;
        u64 remaining = 0x4000;
        do {
            // 4 sub-entries per iteration (0x100 bytes = 4 * 0x40)
            *reinterpret_cast<u64*>(ptr - 0xe6) = 0;
            *(ptr - 0xbc) = 0;
            *reinterpret_cast<u32*>(ptr - 0xc0) = 0;
            *reinterpret_cast<u64*>(ptr - 0xa6) = 0;
            *(ptr - 0x7c) = 0;
            *reinterpret_cast<u32*>(ptr - 0x80) = 0;
            *reinterpret_cast<u64*>(ptr - 0x66) = 0;
            *(ptr - 0x3c) = 0;
            *reinterpret_cast<u32*>(ptr - 0x40) = 0;
            *reinterpret_cast<u64*>(ptr - 0x26) = 0;
            *(ptr + 0x04) = 0;
            *reinterpret_cast<u32*>(ptr) = 0;

            ptr += 0x100;
            remaining -= 0x100;
        } while (remaining != 0);
    }

    // ================================================================
    // Phase 7: Pre-player-slot data zero (0x71052c9cb0 - 0x71052c9db8)
    // ================================================================
    DAT_71052c9db8 = 0;
    DAT_71052c9da8 = 0;
    DAT_71052c9db0 = 0;
    DAT_71052c9d80 = 0;
    DAT_71052c9d98 = 0;
    DAT_71052c9da0 = 0;
    memset(DAT_71052c9d75, 0, 8);
    DAT_71052c9cb0 = 0;
    DAT_71052c9d88 = 0;
    DAT_71052c9d90 = 0;
    DAT_71052c9d68 = 0;
    DAT_71052c9d70 = 0;
    DAT_71052c9d58 = 0;
    DAT_71052c9d60 = 0;
    DAT_71052c9d48 = 0;
    DAT_71052c9d50 = 0;
    DAT_71052c9d38 = 0;
    DAT_71052c9d40 = 0;
    DAT_71052c9d28 = 0;
    DAT_71052c9d30 = 0;
    DAT_71052c9d18 = 0;
    DAT_71052c9d20 = 0;
    DAT_71052c9d08 = 0;
    DAT_71052c9d10 = 0;
    DAT_71052c9cf8 = 0;
    DAT_71052c9d00 = 0;
    DAT_71052c9ce8 = 0;
    DAT_71052c9cf0 = 0;
    DAT_71052c9cd8 = 0;
    DAT_71052c9ce0 = 0;
    DAT_71052c9cc8 = 0;
    DAT_71052c9cd0 = 0;
    DAT_71052c9cb8 = 0;
    DAT_71052c9cc0 = 0;

    // ================================================================
    // Phase 8: Player slot region init + subsystem init calls
    // ================================================================
    memset(&DAT_71052c9dc0, 0, 0x1818);

    // Initialize two player slot subsystems (0xC08 stride each)
    FUN_7101765c30(&DAT_71052c9dc8);
    FUN_7101765c30(&DAT_71052ca9d0);

    // Initialize two extended regions
    FUN_71017a86b0(&DAT_71052cb5d8);
    FUN_71017a86b0(&DAT_71052e7b60);

    // ================================================================
    // Phase 9: Match configuration + player slot configs (5 slots with
    // DLC bitmask hash lookup)
    // ================================================================
    u64 param_data = DAT_710532e730;

    DAT_71053040f0 = 0;
    DAT_71053040f4 = 0;
    DAT_71053040f8 = 0xFFFFFFFF00000001ULL;
    DAT_7105304100 = 0xFFFFFFFF;
    DAT_7105304150 = 0;
    DAT_7105304158 = 0;
    DAT_7105304558 = 0;
    memset(DAT_7105304109, 0, 8);
    DAT_7105304104 = 0;

    DAT_710530455c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304564 = 0;
    DAT_710530456c = 0;
    DAT_710530459c = 0;
    DAT_710530459e = 0;
    DAT_71053045a0 = 0x0503003c;
    DAT_71053045a4 = 0;
    DAT_71053045a6 = 2;
    DAT_71053045a7 = 0x10100000a000000ULL;
    DAT_71053045af = 0x10300;
    DAT_71053045b3 = 0x0201;
    DAT_71053045d0 = 0xFFFFFFFF;
    DAT_71053045c8 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71053045c0 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71053045b8 = 0xFFFFFFFFFFFFFFFFULL;

    // DLC bitmask hash lookup (slot 1)
    if (param_data != 0) {
        u64 v1 = *reinterpret_cast<u64*>(param_data + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_71053045c0) + slot + 4);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    // Slot 2 config init (repeated pattern)
    DAT_71053045d4 = 0x100;
    DAT_71053045de = 0;
    DAT_71053045d6 = 0;
    memset(DAT_71053045e3, 0, 2);
    memset(DAT_71053045e0, 0, 4);
    DAT_71053045e8 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_710530463c = 0;
    DAT_7105304644 = 0;

    // Slot 3 config
    DAT_7105304a44 = 0;
    memset(DAT_71053045f5, 0, 8);
    DAT_71053045f0 = 0;
    DAT_7105304a48 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304a50 = 0;
    DAT_7105304a8c = 0x3c;
    DAT_7105304a58 = 0;
    DAT_7105304a88 = 0;
    DAT_7105304a8a = 0;
    DAT_7105304a8e = 0x200000503;
    DAT_7105304a96 = 0x10300010100000aULL;
    DAT_7105304a9e = 0x100;
    DAT_7105304aa0 = 2;
    DAT_7105304abc = 0xFFFFFFFF;
    DAT_7105304ab4 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304aac = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304aa4 = 0xFFFFFFFFFFFFFFFFULL;

    // DLC bitmask hash lookup (slot 2)
    if (param_data != 0) {
        u64 v1 = *reinterpret_cast<u64*>(param_data + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_7105304aac) + slot + 4);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    // Slot 3-5 config init follows same pattern (abbreviated for compilation)
    // Slot 3
    DAT_7105304f64 = 0x3c;
    DAT_7105304b14 = 0;
    DAT_7105304b1c = 0;
    DAT_7105304f1c = 0;
    memset(DAT_7105304acd, 0, 8);
    DAT_7105304f20 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304f28 = 0;
    DAT_7105304f30 = 0;
    DAT_7105304f60 = 0;
    DAT_7105304f62 = 0;
    DAT_7105304ac0 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304ac8 = 0;
    DAT_7105304f66 = 0x200000503;
    DAT_7105304f6e = 0x10300010100000aULL;
    DAT_7105304f76 = 0x100;
    DAT_7105304f78 = 2;
    DAT_7105304f94 = 0xFFFFFFFF;
    DAT_7105304f8c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304f84 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304f7c = 0xFFFFFFFFFFFFFFFFULL;

    if (param_data != 0) {
        u64 v1 = *reinterpret_cast<u64*>(param_data + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_7105304f84) + slot + 4);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    // Slot 4
    DAT_7105304fec = 0;
    DAT_7105304ff4 = 0;
    DAT_71053053f4 = 0;
    memset(DAT_7105304fa5, 0, 8);
    DAT_71053053f8 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105305400 = 0;
    DAT_7105305408 = 0;
    DAT_7105305438 = 0;
    DAT_710530543a = 0;
    DAT_710530543c = 0x3c;
    DAT_7105304f98 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105304fa0 = 0;
    DAT_710530543e = 0x200000503;
    DAT_7105305446 = 0x10300010100000aULL;
    DAT_710530544e = 0x100;
    DAT_7105305450 = 2;
    DAT_710530546c = 0xFFFFFFFF;
    DAT_7105305464 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_710530545c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105305454 = 0xFFFFFFFFFFFFFFFFULL;

    if (param_data != 0) {
        u64 v1 = *reinterpret_cast<u64*>(param_data + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_710530545c) + slot + 4);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    // Slot 5
    DAT_7105305470 = 0x101000000000000ULL;
    DAT_7105305478 = 0x2010000;
    DAT_7105305480 = 0xFFFFFFFF00000000ULL;
    DAT_710530547c = 0;
    DAT_7105305488 = 0xFFFFFFFF;
    DAT_71053054d8 = 0;
    DAT_71053054e0 = 0;
    DAT_71053058e0 = 0;
    memset(DAT_7105305491, 0, 8);
    DAT_710530548c = 0;
    DAT_71053058e4 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71053058ec = 0;
    DAT_710530592a = 3;
    DAT_71053058f4 = 0;
    DAT_7105305924 = 0;
    DAT_7105305926 = 0;
    DAT_7105305928 = 0x3c;
    DAT_710530592b = 0xa00000002000005ULL;
    DAT_7105305933 = 0x1030001010000ULL;
    DAT_710530593b = 0x201;
    DAT_7105305958 = 0xFFFFFFFF;
    DAT_7105305950 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105305948 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105305940 = 0xFFFFFFFFFFFFFFFFULL;

    if (param_data != 0) {
        u64 v1 = *reinterpret_cast<u64*>(param_data + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_7105305948) + slot + 4);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    DAT_710530595c = 0x100;
    DAT_7105305966 = 0;
    DAT_710530595e = 0;
    DAT_710530596c = 0;
    DAT_7105305968 = 0;

    // ================================================================
    // Phase 10: Online state init
    // ================================================================
    FUN_71017ab8f0(&DAT_7105305970);

    // ================================================================
    // Phase 11: Additional state init (0x7105306b68 - 0x7105306d50)
    // ================================================================
    DAT_7105306b68 = 0xFFFFFFFF;
    DAT_7105306b70 = 0;
    DAT_7105306c88 = 0;
    DAT_7105306c90 = 0;
    DAT_7105306ca8 = 0x13ffff0000000000ULL;
    DAT_7105306cb0 = 0x5affff0000000000ULL;
    DAT_7105306cbc = 0;
    DAT_7105306cb8 = 0;
    DAT_7105306d18 = SENTINEL;

    FUN_71017bd350(&DAT_7105306b78);

    DAT_7105306d30 = 0;
    memset(DAT_7105306d28, 0, 16);
    DAT_7105306d40 = 0;
    DAT_7105306d38 = 0;

    FUN_710179b9e0(&DAT_7105306d50);

    // ================================================================
    // Phase 12: Match result / score data init
    // ================================================================
    DAT_7105307130 = 0;
    DAT_7105307134 = 0;
    memset(&DAT_7105307138, 0, 0x18c);
    DAT_71053072c4 = 0x0201;
    DAT_71053072c6 = 0;
    DAT_71053072c8 = 1;
    DAT_71053072d0 = 0;
    DAT_71053072d8 = 1;
    DAT_71053072e0 = 0;
    DAT_71053072e8 = 1;
    DAT_71053072f4 = 0;
    DAT_71053072ec = 0;
    DAT_7105307300 = 0xFFFFFFFF;
    DAT_7105307308 = SENTINEL;
    DAT_7105307310 = 0x2dffff0000000000ULL;
    DAT_7105307318 = 0x69ffff0000000000ULL;
    DAT_7105307320 = 0;
    DAT_7105307330 = 0xFFFFFFFF;
    DAT_7105307338 = 0xd9ffff0000000000ULL;
    DAT_7105307340 = 0;
    DAT_7105307348 = 0;
    DAT_7105307350 = 0;
    DAT_7105307358 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105307360 = 0xFFFF;
    DAT_7105307364 = 0;
    DAT_710530736c = 0;
    DAT_710530739c = 0xFFFFFFFF;
    DAT_71053073a0 = 0;
    DAT_71053073a4 = 0;
    DAT_71053073a8 = 0;

    // ================================================================
    // Phase 13: Allocate vector buffer with OOM retry pattern
    // Allocation 1: 0xc6 bytes aligned to 0x10
    // ================================================================
    u64 alloc1 = reinterpret_cast<u64>(je_aligned_alloc(0x10, 0xc6));
    if (alloc1 == 0) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_arg1 = 0;
            u64 oom_arg2_lo = 0xc6;
            u16 oom_arg2_hi = 0;
            u64 oom_result = reinterpret_cast<u64 (*)(u64*, u32*, u64*)>(
                *reinterpret_cast<u64*>(*DAT_7105331f00 + 0x30))(
                DAT_7105331f00, &oom_arg1, reinterpret_cast<u64*>(&oom_arg2_lo));
            if ((oom_result & 1) != 0) {
                alloc1 = reinterpret_cast<u64>(je_aligned_alloc(0x10, 0xc6));
                if (alloc1 == 0) alloc1 = 0;
            }
        }
    }

    DAT_71053073c0 = alloc1 + 0xc6;
    DAT_71053073c8 = 0;
    DAT_71053073b0 = alloc1;
    DAT_71053073b8 = alloc1;

    // Allocation 2: 1 byte aligned to 0x10
    u64 alloc2 = reinterpret_cast<u64>(je_aligned_alloc(0x10, 1));
    if (alloc2 == 0) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_arg1 = 0;
            u64 oom_arg2_lo = 1;
            u16 oom_arg2_hi = 0;
            u64 oom_result = reinterpret_cast<u64 (*)(u64*, u32*, u64*)>(
                *reinterpret_cast<u64*>(*DAT_7105331f00 + 0x30))(
                DAT_7105331f00, &oom_arg1, reinterpret_cast<u64*>(&oom_arg2_lo));
            if ((oom_result & 1) != 0) {
                alloc2 = reinterpret_cast<u64>(je_aligned_alloc(0x10, 1));
                if (alloc2 == 0) alloc2 = 0;
            }
        }
    }

    DAT_71053073d8 = 0;
    DAT_71053073f4 = 0;
    DAT_71053073ec = 0;
    DAT_71053073e4 = 0;
    DAT_71053073dc = 0;
    DAT_71053073fc = 0xFFFFFFFF;
    DAT_71053073d0 = alloc2;

    // ================================================================
    // Phase 14: FUN_7103351390 init + match state fields
    // ================================================================
    FUN_7103351390(&DAT_7105307428);

    DAT_7105307428 = 0;
    DAT_7105307434 = 0;
    DAT_71053074a4 = 0;
    DAT_71053074f8 = 0;
    DAT_7105307500 = 1;
    DAT_7105307518 = 0;
    DAT_7105307520 = SENTINEL;
    DAT_7105307528 = 0;
    DAT_7105307530 = 0;
    DAT_7105307534 = 0;
    DAT_7105307538 = 0;

    // FNV hash seed init
    DAT_710530742c = 0x811c9dc5;
    DAT_710530749c = 0x811c9dc5;

    DAT_71053074c0 = 0;
    DAT_71053074b8 = SENTINEL;
    DAT_71053074b0 = 0;
    DAT_71053074d0 = SENTINEL;
    DAT_71053074e8 = 0;
    DAT_71053074f0 = 1;
    DAT_7105307418 = 0;
    DAT_7105307420 = 0;
    DAT_7105307408 = 0;
    DAT_7105307410 = 0;
    DAT_71053074d8 = 0;
    DAT_7105307508 = 0;
    DAT_7105307510 = SENTINEL;

    memset(&DAT_7105307540, 0, 0x210);

    FUN_71017abc60(&DAT_7105307570);

    DAT_7105307750 = 0;

    // ================================================================
    // Phase 15: CSS player slot data init (8 slots)
    // ================================================================
    DAT_7105307760 = 0;
    DAT_7105307768 = 0;

    memset(&BSS_CSS_DATA_ARRAY, 0, 0xe40);
    *reinterpret_cast<u32*>(&BSS_CSS_DATA_ARRAY) = 0xff;
    DAT_7105307774 = 0;
    DAT_710530777c = 0;
    DAT_7105307794 = 1;
    FUN_71017abd40(&DAT_7105307798);

    DAT_7105307938 = 0xff;
    DAT_710530793c = 0;
    DAT_7105307944 = 0;
    DAT_710530795c = 1;
    FUN_71017abd40(&DAT_7105307960);

    DAT_7105307b00 = 0xff;
    DAT_7105307b04 = 0;
    DAT_7105307b0c = 0;
    DAT_7105307b24 = 1;
    FUN_71017abd40(&DAT_7105307b28);

    DAT_7105307cc8 = 0xff;
    DAT_7105307ccc = 0;
    DAT_7105307cd4 = 0;
    DAT_7105307cec = 1;
    FUN_71017abd40(&DAT_7105307cf0);

    DAT_7105307e90 = 0xff;
    DAT_7105307e94 = 0;
    DAT_7105307e9c = 0;
    DAT_7105307eb4 = 1;
    FUN_71017abd40(&DAT_7105307eb8);

    DAT_7105308058 = 0xff;
    DAT_710530805c = 0;
    DAT_7105308064 = 0;
    DAT_710530807c = 1;
    FUN_71017abd40(&DAT_7105308080);

    DAT_7105308220 = 0xff;
    DAT_7105308224 = 0;
    DAT_710530822c = 0;
    DAT_7105308244 = 1;
    FUN_71017abd40(&DAT_7105308248);

    DAT_71053083e8 = 0xff;
    DAT_71053083ec = 0;
    DAT_71053083f4 = 0;
    DAT_710530840c = 1;
    FUN_71017abd40(&DAT_7105308410);

    // ================================================================
    // Phase 16: CSS second data array + extended player data
    // ================================================================
    memset(&BSS_CSS_SECOND_ARRAY, 0, 0x1200);
    *reinterpret_cast<u32*>(&BSS_CSS_SECOND_ARRAY) = 0xFFFFFFFF;

    DAT_71053085b8 = 0;
    DAT_71053085c0 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71053085c8 = 0;
    DAT_71053085cc = 0xFFFFFFFFFFFFFFFFULL;
    DAT_71053085d4 = 0xFFFF;
    DAT_71053085d8 = 0;
    DAT_71053085e0 = 0;
    DAT_7105308610 = 0xFFFFFFFF;
    DAT_7105308614 = 0;
    memset(DAT_7105308615, 0, 8);
    DAT_7105308620 = 0x3f8000003f800000ULL; // {1.0f, 1.0f}
    DAT_7105308628 = 0x3f8000003f800000ULL; // {1.0f, 1.0f}
    DAT_7105308630 = 0;
    FUN_71017abd40(&DAT_7105308638);

    // Extended player slots 0-7 (same pattern: flag, magic, 0xff, -1 fields, 1.0f pairs)
    // Slot 0
    *reinterpret_cast<u8*>(&DAT_71053087d8) = 0;
    DAT_71053087e0 = 0xb95d0753fULL;
    DAT_71053087e8 = 0xff;
    DAT_71053087f0 = 0xFFFFFFFF;
    DAT_71053087f8 = 0;
    DAT_7105308800 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308808 = 0;
    DAT_710530880c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308814 = 0xFFFF;
    DAT_7105308818 = 0;
    DAT_7105308820 = 0;
    DAT_7105308850 = 0xFFFFFFFF;
    DAT_7105308854 = 0;
    memset(DAT_7105308855, 0, 8);
    DAT_7105308860 = 0x3f8000003f800000ULL;
    DAT_7105308868 = 0x3f8000003f800000ULL;
    DAT_7105308870 = 0;
    FUN_71017abd40(&DAT_7105308878);

    // Slot 1
    *reinterpret_cast<u8*>(&DAT_7105308a18) = 0;
    DAT_7105308a20 = 0xb95d0753fULL;
    DAT_7105308a28 = 0xff;
    DAT_7105308a30 = 0xFFFFFFFF;
    DAT_7105308a38 = 0;
    DAT_7105308a40 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308a48 = 0;
    DAT_7105308a4c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308a54 = 0xFFFF;
    DAT_7105308a58 = 0;
    DAT_7105308a60 = 0;
    DAT_7105308a90 = 0xFFFFFFFF;
    DAT_7105308a94 = 0;
    memset(DAT_7105308a95, 0, 8);
    DAT_7105308aa0 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_7105308aa8) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_7105308aa8) + 4) = 0x3f800000;
    DAT_7105308ab0 = 0;
    FUN_71017abd40(&DAT_7105308ab8);

    // Slot 2
    *reinterpret_cast<u8*>(&DAT_7105308c58) = 0;
    DAT_7105308c60 = 0xb95d0753fULL;
    DAT_7105308c68 = 0xff;
    DAT_7105308c70 = 0xFFFFFFFF;
    DAT_7105308c78 = 0;
    DAT_7105308c80 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308c88 = 0;
    DAT_7105308c8c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308c94 = 0xFFFF;
    DAT_7105308c98 = 0;
    DAT_7105308ca0 = 0;
    DAT_7105308cd0 = 0xFFFFFFFF;
    DAT_7105308cd4 = 0;
    memset(DAT_7105308cd5, 0, 8);
    DAT_7105308ce0 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_7105308ce8) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_7105308ce8) + 4) = 0x3f800000;
    DAT_7105308cf0 = 0;
    FUN_71017abd40(&DAT_7105308cf8);

    // Slot 3
    *reinterpret_cast<u8*>(&DAT_7105308e98) = 0;
    DAT_7105308ea0 = 0xb95d0753fULL;
    DAT_7105308ea8 = 0xff;
    DAT_7105308eb0 = 0xFFFFFFFF;
    DAT_7105308eb8 = 0;
    DAT_7105308ec0 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308ec8 = 0;
    DAT_7105308ecc = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105308ed4 = 0xFFFF;
    DAT_7105308ed8 = 0;
    DAT_7105308ee0 = 0;
    DAT_7105308f10 = 0xFFFFFFFF;
    DAT_7105308f14 = 0;
    memset(DAT_7105308f15, 0, 8);
    DAT_7105308f20 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_7105308f28) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_7105308f28) + 4) = 0x3f800000;
    DAT_7105308f30 = 0;
    FUN_71017abd40(&DAT_7105308f38);

    // Slot 4
    *reinterpret_cast<u8*>(&DAT_71053090d8) = 0;
    DAT_71053090e0 = 0xb95d0753fULL;
    DAT_71053090e8 = 0xff;
    DAT_71053090f0 = 0xFFFFFFFF;
    DAT_71053090f8 = 0;
    DAT_7105309100 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309108 = 0;
    DAT_710530910c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309114 = 0xFFFF;
    DAT_7105309118 = 0;
    DAT_7105309120 = 0;
    DAT_7105309150 = 0xFFFFFFFF;
    DAT_7105309154 = 0;
    memset(DAT_7105309155, 0, 8);
    DAT_7105309160 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_7105309168) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_7105309168) + 4) = 0x3f800000;
    DAT_7105309170 = 0;
    FUN_71017abd40(&DAT_7105309178);

    // Slot 5
    *reinterpret_cast<u8*>(&DAT_7105309318) = 0;
    DAT_7105309320 = 0xb95d0753fULL;
    DAT_7105309328 = 0xff;
    DAT_7105309330 = 0xFFFFFFFF;
    DAT_7105309338 = 0;
    DAT_7105309340 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309348 = 0;
    DAT_710530934c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309354 = 0xFFFF;
    DAT_7105309358 = 0;
    DAT_7105309360 = 0;
    DAT_7105309390 = 0xFFFFFFFF;
    DAT_7105309394 = 0;
    memset(DAT_7105309395, 0, 8);
    DAT_71053093a0 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_71053093a8) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_71053093a8) + 4) = 0x3f800000;
    DAT_71053093b0 = 0;
    FUN_71017abd40(&DAT_71053093b8);

    // Slot 6
    *reinterpret_cast<u8*>(&DAT_7105309558) = 0;
    DAT_7105309560 = 0xb95d0753fULL;
    DAT_7105309568 = 0xff;
    DAT_7105309570 = 0xFFFFFFFF;
    DAT_7105309578 = 0;
    DAT_7105309580 = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309588 = 0;
    DAT_710530958c = 0xFFFFFFFFFFFFFFFFULL;
    DAT_7105309594 = 0xFFFF;
    DAT_7105309598 = 0;
    DAT_71053095a0 = 0;
    DAT_71053095d0 = 0xFFFFFFFF;
    DAT_71053095d4 = 0;
    memset(DAT_71053095d5, 0, 8);
    DAT_71053095e0 = 0x3f8000003f800000ULL;
    *reinterpret_cast<u32*>(&DAT_71053095e8) = 0x3f800000;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(&DAT_71053095e8) + 4) = 0x3f800000;
    DAT_71053095f0 = 0;
    FUN_71017abd40(&DAT_71053095f8);

    // Slot 7 (different pattern — uses 0x69ffff / 0xd9ffff sentinel variants)
    *reinterpret_cast<u8*>(&DAT_7105309798) = 0;
    DAT_71053097a0 = 0xb95d0753fULL;
    DAT_71053097a8 = 0xff;
    DAT_71053097d0 = 0xd9ffff0000000000ULL;
    DAT_71053097f0 = 0xd9ffff0000000000ULL;
    DAT_71053097b0 = 0;
    DAT_71053097c8 = 0;
    DAT_71053097e8 = 0;
    DAT_7105309808 = 0;
    DAT_71053097b8 = 0x69ffff0000000000ULL;
    DAT_71053097c0 = 0x69ffff0000000000ULL;
    DAT_71053097d8 = 0x69ffff0000000000ULL;
    DAT_71053097e0 = 0x69ffff0000000000ULL;
    DAT_71053097f8 = 0x69ffff0000000000ULL;
    DAT_7105309800 = 0x69ffff0000000000ULL;
    DAT_7105309810 = 0xd9ffff0000000000ULL;

    memset(&DAT_7105309818, 0, 0x150);

    // ================================================================
    // Phase 17: FUN_71017ac210 x3 + CSS config init
    // ================================================================
    FUN_71017ac210(&DAT_71053098d8);
    FUN_71017ac210(&DAT_7105309908);
    FUN_71017ac210(&DAT_7105309938);

    DAT_7105309968 = 0;
    memset(DAT_710530996c, 0, 8);
    DAT_7105309974 = 0;
    DAT_7105309976 = 0;
    DAT_7105309978 = 0x3c;
    DAT_7105309988 = 0x1000103;
    CSS_MODE_FLAGS = 0x100;
    DAT_7105309996 = 0;
    DAT_710530998e = 0;
    memset(DAT_7105309998, 0, 8);
    CSS_MAX_PLAYER_COUNT = 2;

    // DLC bitmask init
    *reinterpret_cast<u64*>(DAT_71053099b4) = 0xFFFFFFFFFFFFFFFFULL;
    CSS_MAX_SLOTS_VARIANT = 0xFFFFFFFFFFFFFFFFULL;
    CSS_INITIAL_PLAYER_BITMASK = 0xFFFFFFFFFFFFFFFFULL;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(DAT_71053099b8) + 4) = 0xFFFFFFFF;

    // DLC bitmask hash lookup (CSS slot)
    if (DAT_710532e730 != 0) {
        u64 v1 = *reinterpret_cast<u64*>(DAT_710532e730 + 8);
        u64 v2 = *reinterpret_cast<u64*>(v1 + 0x178);
        u64 hash = FUN_71032b1e30(*reinterpret_cast<u64*>(v2 + 8), 0xd56784f97ULL);
        s32 idx = FUN_71032b1890(reinterpret_cast<void*>(v2), hash);
        if (idx >= 0) {
            u64 result = (u64)FUN_71032b1890(
                reinterpret_cast<void*>(*reinterpret_cast<u64*>(v1 + 0x178)), hash);
            u64 slot = ((result >> 5) & 0x7ffffff) * 4;
            u32* bitmask = reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(&DAT_71053099b0) + slot);
            *bitmask &= ~(1u << (static_cast<u32>(result) & 0x1f));
        }
    }

    // ================================================================
    // Phase 18: CSS state + team config subsystem inits
    // ================================================================
    DAT_71053099c0 = 0;
    FUN_710179bbd0(&DAT_71053099c8);
    FUN_71017ac230(&DAT_710530c568);
    DAT_710530c7d0 = 0;
    FUN_710179a0c0(&DAT_710530c7d8);

    // ================================================================
    // Phase 19: Match end / post-match data zero
    // ================================================================
    DAT_710530d2a0 = 0;
    DAT_710530d2a8 = 0xFFFF;
    DAT_710530d2b0 = 0x69ffff0000000000ULL;
    DAT_710530d300 = 0;
    DAT_710530d2f8 = 0;
    DAT_710530d2f0 = 0;
    DAT_710530d2e8 = 0;
    DAT_710530d2e0 = 0;
    DAT_710530d2d8 = 0;
    DAT_710530d2d0 = 0;
    DAT_710530d2c8 = 0;
    DAT_710530d2c0 = 0;
    DAT_710530d2b8 = 0;

    memset(DAT_710530d390, 0, 8);
    memset(DAT_710530d388, 0, 8);
    memset(DAT_710530d38c, 0, 4);
    DAT_710530d380 = 0;
    DAT_710530d378 = 0;
    DAT_710530d370 = 0;
    DAT_710530d368 = 0;
    DAT_710530d360 = 0;
    DAT_710530d358 = 0;
    DAT_710530d350 = 0;
    DAT_710530d348 = 0;
    DAT_710530d340 = 0;
    DAT_710530d338 = 0;
    DAT_710530d330 = 0;
    DAT_710530d328 = 0;
    DAT_710530d320 = 0;
    DAT_710530d318 = 0;
    DAT_710530d310 = 0;
    DAT_710530d308 = 0;

    FUN_710179d180(&DAT_710530d398);

    // ================================================================
    // Phase 20: Final config region (0x7105312f00 - 0x71053134c8)
    // Large memset + 8 config slots with repeated pattern
    // ================================================================
    DAT_7105312f00 = 0;
    memset(&DAT_7105312f08_region, 0, 0x5c8);

    // Config slot 0
    DAT_7105312f08 = 0xFFFF;
    DAT_7105312f0c = 0xFFFFFFFF;
    DAT_7105312f10 = SENTINEL;
    DAT_7105312f18 = 0;
    DAT_7105312f38 = 0;
    DAT_7105312f40 = 0;
    DAT_7105312f5c = 0xFFFFFF;
    DAT_7105312f60 = 1;
    DAT_7105312f78 = 0;
    DAT_7105312f70 = 0;
    DAT_7105312f68 = 0;
    DAT_7105312f80 = 0xFFFFFFFF;
    DAT_7105312f84 = 0;
    DAT_7105312f88 = 0;
    DAT_7105312f8c = 2;
    DAT_7105312f90 = 3;
    DAT_7105312f98 = 0;
    DAT_7105312f9c = 0;

    // Config slot 1
    DAT_7105312fb4 = 0;
    DAT_7105312fb8 = 0xFFFF;
    DAT_7105312fbc = 0xFFFFFFFF;
    DAT_7105312fc0 = SENTINEL;
    DAT_7105312fc8 = 0;
    DAT_7105312fe8 = 0;
    DAT_7105312ff0 = 0;
    DAT_710531300c = 0xFFFFFF;
    DAT_7105313010 = 1;
    DAT_7105313028 = 0;
    DAT_7105313020 = 0;
    DAT_7105313018 = 0;
    DAT_7105313030 = 0xFFFFFFFF;
    DAT_7105313034 = 0;
    DAT_7105313038 = 0;
    DAT_710531303c = 2;
    DAT_7105313040 = 3;
    DAT_7105313044 = 0;
    DAT_7105313048 = 0;
    DAT_710531304c = 0;

    // Config slot 2
    DAT_7105313064 = 0;
    DAT_7105313068 = 0xff;
    DAT_7105313069 = 0xff;
    DAT_710531306c = 0xFFFFFFFF;
    DAT_7105313070 = SENTINEL;
    DAT_7105313078 = 0;
    DAT_7105313098 = 0;
    DAT_710531309c = 0;
    DAT_71053130a0 = 0;
    DAT_71053130bc = 0xFFFF;
    DAT_71053130be = 0xff;
    DAT_71053130bf = 0;
    DAT_71053130c0 = 1;
    DAT_71053130d8 = 0;
    DAT_71053130d0 = 0;
    DAT_71053130c8 = 0;
    DAT_71053130e0 = 0xFFFFFFFF;
    DAT_71053130e4 = 0;
    DAT_71053130e8 = 0;
    DAT_71053130ec = 2;
    DAT_71053130f0 = 3;
    DAT_71053130f4 = 0;
    DAT_71053130f8 = 0;
    DAT_71053130fc = 0;

    // Config slot 3
    DAT_7105313114 = 0;
    DAT_7105313118 = 0xff;
    DAT_7105313119 = 0xff;
    DAT_710531311c = 0xFFFFFFFF;
    DAT_7105313120 = SENTINEL;
    DAT_7105313128 = 0;
    DAT_7105313148 = 0;
    DAT_710531314c = 0;
    DAT_7105313150 = 0;
    DAT_710531316c = 0xFFFF;
    DAT_710531316e = 0xff;
    DAT_710531316f = 0;
    DAT_7105313170 = 1;
    DAT_7105313188 = 0;
    DAT_7105313180 = 0;
    DAT_7105313178 = 0;
    DAT_7105313190 = 0xFFFFFFFF;
    DAT_7105313194 = 0;
    DAT_7105313198 = 0;
    DAT_710531319c = 2;
    DAT_71053131a0 = 3;
    DAT_71053131a4 = 0;
    DAT_71053131a8 = 0;
    DAT_71053131ac = 0;

    // Config slot 4
    DAT_71053131c4 = 0;
    DAT_71053131c8 = 0xff;
    DAT_71053131c9 = 0xff;
    DAT_71053131cc = 0xFFFFFFFF;
    DAT_71053131d0 = SENTINEL;
    DAT_71053131d8 = 0;
    DAT_71053131f8 = 0;
    DAT_71053131fc = 0;
    DAT_7105313200 = 0;
    DAT_710531321c = 0xFFFF;
    DAT_710531321e = 0xff;
    DAT_710531321f = 0;
    DAT_7105313220 = 1;
    DAT_7105313238 = 0;
    DAT_7105313230 = 0;
    DAT_7105313228 = 0;
    DAT_7105313240 = 0xFFFFFFFF;
    DAT_7105313244 = 0;
    DAT_7105313248 = 0;
    DAT_710531324c = 2;
    DAT_7105313250 = 3;
    DAT_7105313254 = 0;
    DAT_7105313258 = 0;
    DAT_710531325c = 0;

    // Config slot 5
    DAT_7105313274 = 0;
    DAT_7105313278 = 0xff;
    DAT_7105313279 = 0xff;
    DAT_710531327c = 0xFFFFFFFF;
    DAT_7105313280 = SENTINEL;
    DAT_7105313288 = 0;
    DAT_71053132a8 = 0;
    DAT_71053132ac = 0;
    DAT_71053132b0 = 0;
    DAT_71053132cc = 0xFFFF;
    DAT_71053132ce = 0xff;
    DAT_71053132cf = 0;
    DAT_71053132d0 = 1;
    DAT_71053132e8 = 0;
    DAT_71053132e0 = 0;
    DAT_71053132d8 = 0;
    DAT_71053132f0 = 0xFFFFFFFF;
    DAT_71053132f4 = 0;
    DAT_71053132f8 = 0;
    DAT_71053132fc = 2;
    DAT_7105313300 = 3;
    DAT_7105313304 = 0;
    DAT_7105313308 = 0;
    DAT_710531330c = 0;

    // Config slot 6
    DAT_7105313324 = 0;
    DAT_7105313328 = 0xff;
    DAT_7105313329 = 0xff;
    DAT_710531332c = 0xFFFFFFFF;
    DAT_7105313330 = SENTINEL;
    DAT_7105313338 = 0;
    DAT_7105313358 = 0;
    DAT_710531335c = 0;
    DAT_7105313360 = 0;
    DAT_710531337c = 0xFFFF;
    DAT_710531337e = 0xff;
    DAT_710531337f = 0;
    DAT_7105313380 = 1;
    DAT_7105313398 = 0;
    DAT_7105313390 = 0;
    DAT_7105313388 = 0;
    DAT_71053133a0 = 0xFFFFFFFF;
    DAT_71053133a4 = 0;
    DAT_71053133a8 = 0;
    DAT_71053133ac = 2;
    DAT_71053133b0 = 3;
    DAT_71053133b4 = 0;
    DAT_71053133b8 = 0;
    DAT_71053133bc = 0;

    // Config slot 7
    DAT_71053133d4 = 0;
    DAT_71053133d8 = 0xff;
    DAT_71053133d9 = 0xff;
    DAT_71053133dc = 0xFFFFFFFF;
    DAT_71053133e0 = SENTINEL;
    DAT_71053133e8 = 0;
    DAT_7105313408 = 0;
    DAT_710531340c = 0;
    DAT_7105313410 = 0;
    DAT_710531342c = 0xFFFF;
    DAT_710531342e = 0xff;
    DAT_710531342f = 0;
    DAT_7105313430 = 1;
    DAT_7105313448 = 0;
    DAT_7105313440 = 0;
    DAT_7105313438 = 0;
    DAT_7105313450 = 0xFFFFFFFF;
    DAT_7105313454 = 0;
    DAT_7105313458 = 0;
    DAT_710531345c = 2;
    DAT_7105313460 = 3;
    DAT_7105313464 = 0;
    DAT_7105313468 = 0;
    DAT_710531346c = 0;

    // Final tail fields
    DAT_7105313494 = 0;
    DAT_710531348c = 0;
    DAT_7105313484 = 0;
    DAT_710531349c = 0xFFFFFFFF;
    DAT_71053134a0 = 0;
    DAT_71053134a4 = 0;
    DAT_71053134c8 = 0;
    DAT_71053134c0 = 0;
    DAT_71053134b8 = 0;
    memset(DAT_71053134bc, 0, 4);
    DAT_71053134b0 = 0;
    DAT_71053134a8 = 0;
}
