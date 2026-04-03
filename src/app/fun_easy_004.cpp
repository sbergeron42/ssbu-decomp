#include "types.h"

// EASY-tier FUN_* functions -- address range 0x7100xxxxxx (batch 4)
// Pool-b worker: manually decompiled from Ghidra

// ── SDK forward declarations ─────────────────────────────────────────────────
namespace nn { namespace os {
    struct EventType;
    struct MutexType;
    struct ThreadType;
    void WaitEvent(EventType*);
    void ClearEvent(EventType*);
    void LockMutex(MutexType*);
    void UnlockMutex(MutexType*);
    void WaitThread(ThreadType*);
} }
namespace nn { namespace util { void ReferSymbol(const void*); } }

// ── External globals ─────────────────────────────────────────────────────────
extern u32 DAT_71052b4448;
extern u8  DAT_71052acfd3;

// ── External data (vtable bases / pointer tables) ───────────────────────────
extern u8  PTR_DAT_71052a5970[];
extern u8  PTR_DAT_71052a5c68[];
extern u8  PTR_DAT_71052a5fb8[];
extern u8  PTR_DAT_71052a6418[];
extern u8  PTR_DAT_71052a6a18[];
extern u8  PTR_DAT_71052a6838[];
extern u8  PTR_DAT_71052a6ab8[];
extern u8  PTR_DAT_71052a3df0[];

// ── External function declarations ───────────────────────────────────────────
extern "C" {
    void FUN_7100125d00(void);
    void FUN_7100126c70(void);
    void FUN_7100181270(u64);
    void FUN_7100145ae0(u64, u32);
    void FUN_7100155000(u64);
    void FUN_7100127500(u64);
    void FUN_710017f100(u64);
    void FUN_710017f1d0(u64);
    void FUN_7100196e50(u64);
    void FUN_71001d5110(u64);
    void FUN_71001efaf0(u64);
    void FUN_710023c4a0(void);
    void FUN_71002b8180(u64);
    void FUN_71002b82c0(u64);
    void FUN_7100033a10(u64);
    void FUN_71001808c0(u64, u32);
    void FUN_71001885c0(u64, u64);
    void FUN_71000b1cb0(u64);
    void FUN_71000b2820(u64, u64);
    void FUN_71001cf300(u64, u64, u64);
    void FUN_71001b76e0(void);
    void FUN_710015ffc0(u64);
    void FUN_710024b170(u64);
    void FUN_710022da00(u64);
    void FUN_710022dbf0(u64);
}

// ── Forward declarations (defined later in this file) ────────────────────────
static u32  FUN_710018da80(u64);
static void FUN_71001df8b0(u64);
static void FUN_71001936d0(u64);

// ── Noops ─────────────────────────────────────────────────────────────────────

// 7100042bf0
void FUN_7100042bf0(void) {}

// 7100128230
void FUN_7100128230(void) {}

// 71001282a0
void FUN_71001282a0(void) {}

// 710012fba0
void FUN_710012fba0(void) {}

// 71001305b0
void FUN_71001305b0(void) {}

// 710013d010
void FUN_710013d010(void) {}

// 710013f900
void FUN_710013f900(void) {}

// 7100154170
void FUN_7100154170(void) {}

// 7100155660
void FUN_7100155660(void) {}

// 710015f890
void FUN_710015f890(void) {}

// 7100164450
void FUN_7100164450(void) {}

// 71001798f0
void FUN_71001798f0(void) {}

// 7100179bc0
void FUN_7100179bc0(void) {}

// 7100186290
void FUN_7100186290(void) {}

// 7100186520
void FUN_7100186520(void) {}

// 71001b3830
void FUN_71001b3830(void) {}

// 7100228ed0
void FUN_7100228ed0(void) {}

// 710019ccf0
void FUN_710019ccf0(void) {}

// 71002b3500
void FUN_71002b3500(void) {}

// 71002b3660
void FUN_71002b3660(void) {}

// 71002b3f10
void FUN_71002b3f10(void) {}

// 71002b4080
void FUN_71002b4080(void) {}

// 71002b4230
void FUN_71002b4230(void) {}

// 71002b4970
void FUN_71002b4970(void) {}

// 71002b4b70
void FUN_71002b4b70(void) {}

// 71002b4d30
void FUN_71002b4d30(void) {}

// 71002b8e50
void FUN_71002b8e50(void) {}

// 71002bb340
void FUN_71002bb340(void) {}

// 71002bb530
void FUN_71002bb530(void) {}

// 71002c1f60
void FUN_71002c1f60(void) {}

// 71002c3280
void FUN_71002c3280(void) {}

// 71004eb640
void FUN_71004eb640(void) {}

// 71004eb670
void FUN_71004eb670(void) {}

// 71004eb680
void FUN_71004eb680(void) {}

// 71004eb690
void FUN_71004eb690(void) {}

// 710068d730
void FUN_710068d730(void) {}

// 71001726a0
u64 FUN_71001726a0(void) { return 8; }

// 71001793f0
u64 FUN_71001793f0(void) { return 400; }

// 7100179410
u32 FUN_7100179410(void) { return 0; }

// 7100179420
u32 FUN_7100179420(void) { return 0; }

// 7100179430
u64 FUN_7100179430(void) { return 1; }

// 7100179440
u64 FUN_7100179440(void) { return 1; }

// 7100179450
u32 FUN_7100179450(void) { return 0; }

// 7100179460
u32 FUN_7100179460(void) { return 0; }

// 7100179470
u32 FUN_7100179470(void) { return 0; }

// 71001798e0
u64 FUN_71001798e0(void) { return 0; }

// 7100179bb0
u64 FUN_7100179bb0(void) { return 0; }

// 71001bd600
u32 FUN_71001bd600(void) { return 0; }

// 71002b4870
u64 FUN_71002b4870(void) { return 8; }

// 71002b4d80
u64 FUN_71002b4d80(void) { return 0x28; }

// 71002b4d90
u64 FUN_71002b4d90(void) { return 8; }

// 71002b4fa0
u64 FUN_71002b4fa0(void) { return 8; }

// 71002bcda0
u64 FUN_71002bcda0(void) { return 8; }

// 71002c3290
u64 FUN_71002c3290(void) { return 8; }

// 71004eb5c0
u64 FUN_71004eb5c0(void) { return 1; }

// 71004eb5e0
u64 FUN_71004eb5e0(void) { return 1; }

// 71004eb600
u64 FUN_71004eb600(void) { return 0xffffffff; }

// 71004eb610
u32 FUN_71004eb610(void) { return 0; }

// 71004eb650
u64 FUN_71004eb650(void) { return 1; }

// 7100228170
u32 FUN_7100228170(void) { return DAT_71052b4448; }

// 7100193aa0
u8 FUN_7100193aa0(void) { return DAT_71052acfd3; }

// 710012d220
u64 FUN_710012d220(u64 p1) { return p1 + 0x3c; }

// 710012fda0
u64 FUN_710012fda0(u64 p1) { return p1 + 0x18; }

// 7100147f40
u64 FUN_7100147f40(u64 p1) { return p1 + 0x1e5; }

// 7100160220
u64 FUN_7100160220(u64 p1) { return p1 + 0x28; }

// 7100160380
u64 FUN_7100160380(u64 p1) { return p1 + 0x48; }

// 7100160390
u64 FUN_7100160390(u64 p1) { return p1 + 0x48; }

// 7100173e60
u64 FUN_7100173e60(u64 p1) { return p1 + 0x10; }

// 71002c31d0
u64 FUN_71002c31d0(u64 p1) { return p1 + 0xd8; }

// 71002c3200
u64 FUN_71002c3200(u64 p1) { return p1 + 0x120; }

// 71003b3540
u64 FUN_71003b3540(u64 p1) { return p1 + 0x10; }

// 710051d6a0
u64 FUN_710051d6a0(u64 p1) { return p1 + 0x10; }

// 71002bb540
u64 FUN_71002bb540(u64 p1, u32 p2) { return p1 + (u64)p2 * 0x18 + 0xc; }

// 71002c2800
u64 FUN_71002c2800(u32 *p1, u64 p2) { return (u64)*p1 + p2; }

// 7100114de0
u8 FUN_7100114de0(u64 p1) { return *(u8*)(p1 + 0x97f); }

// 710011be40
u32 FUN_710011be40(u64 p1) { return *(u32*)(p1 + 0x16c8); }

// 710011be70
u64 FUN_710011be70(u64 p1) { return *(u64*)(p1 + 0x16c0); }

// 710012cea0
u16 FUN_710012cea0(u64 p1) { return *(u16*)(p1 + 0x3a); }

// 7100147850
u64 FUN_7100147850(u64 p1) { return *(u64*)(p1 + 0x148); }

// 71001602c0
u64 FUN_71001602c0(u64 p1) { return *(u64*)(p1 + 0x68); }

// 71001602d0
u32 FUN_71001602d0(u64 p1) { return *(u32*)(p1 + 0x70); }

// 71001602e0
u32 FUN_71001602e0(u64 p1) { return *(u32*)(p1 + 0x74); }

// 71001602f0
u8 FUN_71001602f0(u64 p1) { return *(u8*)(p1 + 0x79); }

// 71001624a0
u64 FUN_71001624a0(u64 p1) { return *(u64*)(p1 + 0xa8); }

// 7100186370
u8 FUN_7100186370(u64 p1) { return *(u8*)(p1 + 10); }

// 710018da80
static u32 FUN_710018da80(u64 p1) { return *(u32*)(p1 + 0x98); }

// 7100190ca0
u64 FUN_7100190ca0(u64 p1) { return *(u64*)(p1 + 0x378); }

// 71001921a0
u8 FUN_71001921a0(u64 p1) { return *(u8*)(p1 + 0xbe); }

// 71001936e0
u8 FUN_71001936e0(u64 p1) { return *(u8*)(p1 + 0xbd); }

// 7100193770
u32 FUN_7100193770(u64 p1) { return *(u32*)(p1 + 0xb0); }

// 7100193790
u8 FUN_7100193790(u64 p1) { return *(u8*)(p1 + 0x12a); }

// 71001939a0
u8 FUN_71001939a0(u64 p1) { return *(u8*)(p1 + 299); }

// 71001939d0
u64 FUN_71001939d0(u64 p1) { return *(u64*)(p1 + 0x50); }

// 7100193a50
u64 FUN_7100193a50(u64 p1) { return *(u64*)(p1 + 0x370); }

// 71001df8c0
bool FUN_71001df8c0(u64 p1) { return *(int*)(p1 + 0x48) == 0x40; }

// 7100227680
u8 FUN_7100227680(u64 p1) { return *(u8*)(p1 + 0x11) >> 2 & 1; }

// 71003a4a60
u64 FUN_71003a4a60(u64 p1) { return *(u64*)*(u64*)(p1 + 8); }

// 71002b35a0
u32 FUN_71002b35a0(u32 *p1) { return *p1; }

// 71002b3f70
u32 FUN_71002b3f70(u32 *p1) { return *p1; }

// 71002b47a0
u32 FUN_71002b47a0(u32 *p1) { return *p1; }

// 71002b4e90
u32 FUN_71002b4e90(u32 *p1) { return *p1; }

// 71002b35b0
u32 FUN_71002b35b0(u64 p1) { return *(u32*)(p1 + 4); }

// 71002b47b0
u32 FUN_71002b47b0(u64 p1) { return *(u32*)(p1 + 4); }

// 71002b4ea0
u32 FUN_71002b4ea0(u64 p1) { return *(u32*)(p1 + 4); }

// 71002b35c0
u32 FUN_71002b35c0(u64 p1) { return *(u32*)(p1 + 8); }

// 71002c27f0
u32 FUN_71002c27f0(u64 p1) { return *(u32*)(p1 + 8); }

// 71002b35d0
u32 FUN_71002b35d0(u64 p1) { return *(u32*)(p1 + 0xc); }

// 71002b35e0
u32 FUN_71002b35e0(u64 p1) { return *(u32*)(p1 + 0x10); }

// 71002b35f0
u32 FUN_71002b35f0(u64 p1) { return *(u32*)(p1 + 0x14); }

// 71002b3600
u32 FUN_71002b3600(u64 p1) { return *(u32*)(p1 + 0x18); }

// 71002b3610
u32 FUN_71002b3610(u64 p1) { return *(u32*)(p1 + 0x1c); }

// 71002b3620
float FUN_71002b3620(u64 p1) { return *(float*)(p1 + 0x20); }

// 71002b3630
u32 FUN_71002b3630(u64 p1) { return *(u32*)(p1 + 0x24); }

// 71002b3640
u32 FUN_71002b3640(u64 p1) { return *(u32*)(p1 + 0x28); }

// 71002b3f60
u64 FUN_71002b3f60(u64 p1) { return *(u64*)(p1 + 0x68); }

// 71002b3f90
u64 FUN_71002b3f90(u64 p1) { return *(u64*)(p1 + 0x58); }

// 71002b3fa0
u32 FUN_71002b3fa0(u64 p1) { return *(u32*)(p1 + 0x60); }

// 71002b3fc0
u32 FUN_71002b3fc0(u64 p1) { return *(u32*)(p1 + 0x88); }

// FUN_71002b4e30 defined in fun_medium_007.cpp

// 71002b4eb0
u8 FUN_71002b4eb0(u64 p1) { return *(u8*)(p1 + 8); }

// 71002c1f90
u64 FUN_71002c1f90(u64 *p1) { return *p1; }

// 71002c1fa0
u64 FUN_71002c1fa0(u64 p1) { return *(u64*)(p1 + 0x10); }

// 71002c27e0
u32 FUN_71002c27e0(u64 p1) { return *(u32*)(p1 + 4); }

// 71002c2900
u32 FUN_71002c2900(u64 p1) { return *(u32*)(p1 + 0x20); }

// 710024d070
u32 FUN_710024d070(u64 p1) { return *(u32*)(p1 + 0x28); }

// ── Indexed getters ───────────────────────────────────────────────────────────

// 71002b3f20
bool FUN_71002b3f20(u64 p1, u32 p2) { return *(u64*)(p1 + (u64)p2 * 8 + 8) != 0; }

// 71002b3f40
u64 FUN_71002b3f40(u64 p1, u32 p2) { return *(u64*)(p1 + (u64)p2 * 8 + 8); }

// 71002b3f50
bool FUN_71002b3f50(u64 p1) { return *(u64*)(p1 + 0x68) != 0; }

// 71002b3f80
u64 FUN_71002b3f80(u64 p1, u32 p2) { return *(u64*)(p1 + (u64)p2 * 8 + 0x30); }

// 71002b3fb0
u64 FUN_71002b3fb0(u64 p1, int p2) { return *(u64*)(p1 + (long)p2 * 8 + 0x70); }

// 71002c2b80
u32 FUN_71002c2b80(u64 p1, u32 p2) { return *(u32*)(p1 + (u64)p2 * 4 + 0x14); }

// 71002c2bd0
u32 FUN_71002c2bd0(u64 p1, u32 p2) { return *(u32*)(p1 + (u64)p2 * 4 + 0xc); }

// 71002c2be0
u32 FUN_71002c2be0(u64 p1, u32 p2) { return *(u32*)(p1 + (u64)p2 * 4 + 0x3c); }

// 71002c2e30
u32 FUN_71002c2e30(u64 p1, u32 p2) { return *(u32*)(p1 + (u64)p2 * 4 + 0xc); }

// 71002c2e40
u32 FUN_71002c2e40(u64 p1, u32 p2) { return *(u32*)(p1 + (u64)p2 * 4 + 0x38); }

// 71001563f0
void FUN_71001563f0(u64 p1, u32 p2) { *(u32*)(p1 + 0x28) = p2; }

// 7100160470
void FUN_7100160470(u64 p1, u64 p2) { *(u64*)(p1 + 0x68) = p2; }

// 7100160490
void FUN_7100160490(u64 p1, u32 p2) { *(u32*)(p1 + 0x74) = p2; }

// 710017c210
void FUN_710017c210(u64 p1, u64 p2) { *(u64*)(p1 + 8) = p2; }

// 710017ddf0
void FUN_710017ddf0(u64 p1, u32 p2) { *(u32*)(p1 + 0x474) = p2; }

// 7100186390
void FUN_7100186390(u64 p1, u8 p2) { *(u8*)(p1 + 0xb) = p2; }

// 710019b560
void FUN_710019b560(u64 p1, u64 p2) { *(u64*)(p1 + 0x60) = p2; }

// 71001daff0
void FUN_71001daff0(u64 p1, u32 p2) { *(u32*)(p1 + 0x18) = p2; }

// 71002b3580
void FUN_71002b3580(u64 p1, u32 p2) { *(u32*)(p1 + 0x18) = p2; }

// 71002b3590
void FUN_71002b3590(u64 p1, u32 p2) { *(u32*)(p1 + 0x1c) = p2; }

// 71002b4010
void FUN_71002b4010(u32 *p1, u32 p2) { *p1 = p2; }

// 71002b4040
void FUN_71002b4040(u64 p1, u64 p2) { *(u64*)(p1 + 0x68) = p2; }

// 71002b4060
void FUN_71002b4060(u64 p1, u32 p2) { *(u32*)(p1 + 0x88) = p2; }

// 71002b4780
void FUN_71002b4780(u32 *p1, u32 p2) { *p1 = p2; }

// 71002b4790
void FUN_71002b4790(u64 p1, u32 p2) { *(u32*)(p1 + 4) = p2; }

// 71002b4d50
void FUN_71002b4d50(u64 p1, u32 p2) { *(u32*)(p1 + 0xc) = p2; }

// 71002b4e60
void FUN_71002b4e60(u32 *p1, u32 p2) { *p1 = p2; }

// 71002b4e70
void FUN_71002b4e70(u64 p1, u32 p2) { *(u32*)(p1 + 4) = p2; }

// 71002b4e80
void FUN_71002b4e80(u64 p1, u8 p2) { *(u8*)(p1 + 8) = p2 & 1; }

// ── Zero setters ──────────────────────────────────────────────────────────────

// 7100118770
void FUN_7100118770(u64 p1) { *(u64*)(p1 + 0xb0) = 0; }

// 71001510a0
void FUN_71001510a0(u64 p1) { *(u32*)(p1 + 8) = 0; }

// 710015e390
void FUN_710015e390(u64 p1) { *(u8*)(p1 + 0x12) = 0; }

// 7100177120
void FUN_7100177120(u64 p1) { *(u64*)(p1 + 8) = 0; }

// 710017c220
void FUN_710017c220(u64 p1) { *(u64*)(p1 + 8) = 0; }

// 71001932c0
void FUN_71001932c0(u64 p1) { *(u64*)(p1 + 0x70) = 0; }

// 7100190c90
void FUN_7100190c90(u64 p1) { *(u64*)(p1 + 0xc4) = 0; }

// 71002b3650
void FUN_71002b3650(u64 *p1) { *p1 = 0; }

// 71002b47c0
void FUN_71002b47c0(u64 *p1) { *p1 = 0; }

// 71002b4d60
void FUN_71002b4d60(u64 *p1) { *p1 = 0; }

// 71002b4ec0
void FUN_71002b4ec0(u64 *p1) { *p1 = 0; }

// 71002bcd80
void FUN_71002bcd80(u64 *p1) { *p1 = 0; }

// 71002b3550
void FUN_71002b3550(u32 *p1, u32 p2, u32 p3) { *p1 = p2; p1[1] = p3; }

// 71002b3560
void FUN_71002b3560(u64 p1, u32 p2, u32 p3) { *(u32*)(p1 + 8) = p2; *(u32*)(p1 + 0xc) = p3; }

// 71002b3570
void FUN_71002b3570(u64 p1, u32 p2, u32 p3) { *(u32*)(p1 + 0x10) = p2; *(u32*)(p1 + 0x14) = p3; }

// 71002b4030
void FUN_71002b4030(u64 p1, u64 p2, u32 p3) { *(u64*)(p1 + 0x58) = p2; *(u32*)(p1 + 0x60) = p3; }

// 71002b4020
void FUN_71002b4020(u64 p1, u32 p2, u64 p3, u64 p4) {
    p1 += (u64)p2 * 8;
    *(u64*)(p1 + 8) = p3;
    *(u64*)(p1 + 0x30) = p4;
}

// 71002b4050
void FUN_71002b4050(u64 p1, int p2, u64 p3) { *(u64*)(p1 + (long)p2 * 8 + 0x70) = p3; }

// 7100252cd0
void FUN_7100252cd0(u64 p1, u64 p2) {
    *(u8*)(p1 + 8) = *(u8*)(p2 + 8);
    *(u32*)(p1 + 0xc) = *(u32*)(p2 + 0xc);
}

// 71002bbb30
void FUN_71002bbb30(u64 p1, u64 *p2) {
    *(u64*)(p1 + 0x18) = p2[1];
    *(u64*)(p1 + 0x10) = *p2;
}

// 71001e1430
void FUN_71001e1430(u64 p1, float p2) { *(float*)(p1 + 0x24) = p2; }

// 7100193a10
void FUN_7100193a10(u64 p1, u64 *p2) {
    *(u64*)(p1 + 0xd8) = *p2;
    *(u8*)(p1 + 0xe0) = 1;
}

// 71002c1f50
void FUN_71002c1f50(u64 *p1, u64 p2, u64 p3, u64 p4) {
    p1[0] = p2; p1[1] = p3; p1[2] = p3; p1[3] = p4;
}

// 71002c2870
void FUN_71002c2870(u64 *p1) {
    p1[2] = 0; p1[3] = 0; *p1 = 0; p1[1] = 0;
    *(u32*)((u8*)p1 + 0x20) = 2;
}

// 71002c3270
void FUN_71002c3270(u64 *p1) { *p1 = 0; p1[4] = 0; }

// 71002b4d40
void FUN_71002b4d40(u64 *p1) { *p1 = 1; p1[1] = 0; }

// 71002b4e40
void FUN_71002b4e40(u64 *p1) { *(u8*)(p1 + 1) = 0; *p1 = 0; }

// ── Bool / comparison ─────────────────────────────────────────────────────────

// 7100128210
bool FUN_7100128210(u64 p1) { return (u32)(*(int*)(p1 + 0x12a0) - 2) < 3; }

// 71002c27d0
bool FUN_71002c27d0(u64 p1) { return *(int*)(p1 + 4) != 0; }

// 7100228310
bool FUN_7100228310(u64 *p1) { return *p1 == 0; }

// ── Call-if-nonzero ───────────────────────────────────────────────────────────

// 7100116fc0
void FUN_7100116fc0(u64 *p1) { if (*p1 != 0) FUN_7100125d00(); }

// 7100117060
void FUN_7100117060(u64 *p1) { if (*p1 != 0) FUN_7100126c70(); }

// 71001936d0
static void FUN_71001936d0(u64 p1) {
    u64 v = *(u64*)(p1 + 8);
    if (v != 0) FUN_710018da80(v);
}

// 7100231550
void FUN_7100231550(u64 p1) {
    u64 v = *(u64*)(p1 + 0x30);
    if (v != 0) FUN_71001df8b0(v);
}

// 7100239ae0
void FUN_7100239ae0(u64 p1) {
    u64 v = *(u64*)(p1 + 200);
    if (v != 0) FUN_710022da00(v);
}

// 7100239af0
void FUN_7100239af0(u64 p1) {
    u64 v = *(u64*)(p1 + 200);
    if (v != 0) FUN_710022dbf0(v);
}

// ── Passthrough calls ─────────────────────────────────────────────────────────

// 7100145ad0
void FUN_7100145ad0(u64 p1) { FUN_7100145ae0(p1, 1); }

// 7100146130
void FUN_7100146130(u64 p1) { FUN_7100145ae0(p1, 4); }

// 7100153b90
void FUN_7100153b90(u64 p1) { FUN_7100155000(*(u64*)(p1 + 0x38)); }

// 71001907f0
void FUN_71001907f0(u64 p1) { FUN_7100196e50(*(u64*)(p1 + 0x80)); }

// 71001df8b0
static void FUN_71001df8b0(u64 p1) { FUN_71001d5110(p1 + 0x10); }

// 710023c6d0
void FUN_710023c6d0(void) { FUN_710023c4a0(); }

// 71002b38c0
void FUN_71002b38c0(u64 *p1) { FUN_71002b8180(*p1); }

// 71002b38d0
void FUN_71002b38d0(u64 *p1) { FUN_71002b82c0(*p1); }

// 71002c2010
void FUN_71002c2010(u64 *p1) { FUN_7100033a10(*p1); }

// 7100181f30
void FUN_7100181f30(u64 p1) { FUN_71001808c0(p1, 2); }

// 7100188da0
void FUN_7100188da0(u64 p1) { FUN_71001885c0(p1, p1); }

// 7100160440
void FUN_7100160440(u64 p1) { FUN_71000b1cb0(p1 + 8); }

// 7100160450
void FUN_7100160450(u64 p1) { FUN_71000b1cb0(p1 + 0x28); }

// 7100160460
void FUN_7100160460(u64 p1) { FUN_71000b1cb0(p1 + 0x48); }

// 71001603a0
void FUN_71001603a0(u64 p1, u64 p2) { FUN_71000b2820(p1 + 8, p2 + 8); }

// 71001603b0
void FUN_71001603b0(u64 p1, u64 p2) { FUN_71000b2820(p1 + 0x28, p2 + 0x28); }

// 71001b76d0
void FUN_71001b76d0(u64 p1) { *(u32*)(p1 + 8) = 0; FUN_71001b76e0(); }

// 710024af30
void FUN_710024af30(void) { FUN_710024b170((u64)PTR_DAT_71052a6ab8); }

// 7100146fd0
void FUN_7100146fd0(void) { FUN_71001936d0(*(u64*)PTR_DAT_71052a3df0); }

// 710013c260
void FUN_710013c260(u64 p1) {
    if ((*(u32*)(p1 + 0xcc) | 4) == 4) return;
    nn::os::WaitThread(*(nn::os::ThreadType**)(p1 + 0xd0));
    *(u32*)(p1 + 0xcc) = 4;
}

// ── Vtable setters ────────────────────────────────────────────────────────────

// 71001d39a0
void FUN_71001d39a0(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a5970 + 0x10); }

// 71001d4550
void FUN_71001d4550(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a5c68 + 0x10); }

// 71001dca60
void FUN_71001dca60(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a5970 + 0x10); }

// 71001e6ba0
void FUN_71001e6ba0(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a5fb8 + 0x10); }

// 71002216e0
void FUN_71002216e0(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a6418 + 0x10); }

// 71002498e0
void FUN_71002498e0(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a6a18 + 0x10); }

// 710023c460
void FUN_710023c460(u64 *p1) { *p1 = (u64)(PTR_DAT_71052a6838 + 0x10); }

// 71002b92a0
int FUN_71002b92a0(u32 p1) { return (p1 & 0xff) != 0x80 ? -(int)p1 : 0x7f; }

// 71002babc0
u64 FUN_71002babc0(u64 p1) {
    return (-(p1 >> 0x1f & 1) & 0xfffffffe00000000) | ((p1 & 0xffffffff) << 1);
}

// 71002babd0
int FUN_71002babd0(int p1) { return p1 >> 8; }

// 71002babe0
u32 FUN_71002babe0(u32 p1) { return (u8)p1; }

// 71002babf0
u32 FUN_71002babf0(int p1, u32 p2) { return p2 | (u32)p1 << 8; }

// 71002c1fc0
u64 FUN_71002c1fc0(u64 p1) {
    return *(u64*)(p1 + 0x18) - *(u64*)(p1 + 0x10) + *(u64*)(p1 + 8);
}

// 71002c2d60
u32 FUN_71002c2d60(int p1, u32 p2) { return p1 != 9 ? p2 : 0; }

// 71002c2f60
int FUN_71002c2f60(int p1, int p2) { return p1 != 3 ? p2 : p2 - 4; }

// 710014f070
void FUN_710014f070(void) {}

// 7100122a10
void FUN_7100122a10(u64 p1) { *(u64*)(p1 + 0x220) = 0; }

// 71002c28a0
void FUN_71002c28a0(u64 *p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6) {
    *(u32*)((u8*)p1 + 0x20) = *(u32*)(p6 + 0xc);
    p1[0] = p3;
    p1[1] = p5;
    p1[2] = p2;
    p1[3] = p4;
}

// 71002c28c0
u32 FUN_71002c28c0(u64 p1, u32 p2) { return FUN_71002c2e30(*(u64*)(p1 + 0x10), p2); }

// 71002c28d0
u32 FUN_71002c28d0(u64 p1, u32 p2) { return FUN_71002c2e40(*(u64*)(p1 + 0x10), p2); }

// 71002c28e0
u32 FUN_71002c28e0(u64 p1, u32 p2) { return FUN_71002c2bd0(*(u64*)(p1 + 0x18), p2); }

// 71002c28f0
u32 FUN_71002c28f0(u64 p1, u32 p2) { return FUN_71002c2be0(*(u64*)(p1 + 0x18), p2); }
