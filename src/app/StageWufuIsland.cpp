#include "types.h"
#include "app/placeholders/StageBase.h"

// StageWufuIsland constructor and destructor
// StageWufuIsland : StageBase (inherits, adds fields from ~0x734 onward)
// Object total size: at least 0x1ca * 8 = 0xE50 bytes
// [derived: StageBase size is 0x728, WufuIsland-specific fields start at +0x734]

#define HIDDEN __attribute__((visibility("hidden")))

// External vtables
extern "C" u8 PTR_LAB_710515f3b0;    // [derived: StageWufuIsland vtable]
extern "C" u8 PTR_LAB_71051618a0;    // [derived: sub-object vtable at +0x748]
extern "C" u8 PTR_LAB_7105161860;    // [derived: sub-object vtable at +0x7D8]

// Constant data from .rodata
extern "C" u64 PTR_ConstantZero_71052a7a88 HIDDEN;  // [derived: zero constant pair, used for init]
extern "C" u64 _DAT_7104467ca0 HIDDEN;
extern "C" u64 _UNK_7104467ca8 HIDDEN;
extern "C" u64 DAT_7104469360 HIDDEN;
extern "C" u64 DAT_7104469368 HIDDEN;
extern "C" u64 _DAT_71044646b0 HIDDEN;
extern "C" u64 _UNK_71044646b8 HIDDEN;
extern "C" u64 _DAT_7104469350 HIDDEN;
extern "C" u64 _UNK_7104469358 HIDDEN;
extern "C" u64 _DAT_7104469cd0 HIDDEN;
extern "C" u64 _UNK_7104469cd8 HIDDEN;
extern "C" u64 _DAT_71044648b0 HIDDEN;
extern "C" u64 _UNK_71044648b8 HIDDEN;
extern "C" u64 _DAT_71044648c0 HIDDEN;
extern "C" u64 _UNK_71044648c8 HIDDEN;
extern "C" u64 _DAT_7104468a50 HIDDEN;
extern "C" u64 _UNK_7104468a58 HIDDEN;
extern "C" u64 _DAT_7104464ee0 HIDDEN;
extern "C" u64 _UNK_7104464ee8 HIDDEN;
extern "C" u64 _DAT_7104464bf0 HIDDEN;
extern "C" u64 _UNK_7104464bf8 HIDDEN;
extern "C" u64 _DAT_7104467390 HIDDEN;
extern "C" u64 _UNK_7104467398 HIDDEN;
extern "C" u64 _DAT_7104466020 HIDDEN;
extern "C" u64 _UNK_7104466028 HIDDEN;

// Singletons
namespace lib {
    extern "C" u64 Singleton_app_StageManager_instance_
        asm("_ZN3lib9SingletonIN3app12StageManagerEE9instance_E") HIDDEN;
}
#define SM_INSTANCE lib::Singleton_app_StageManager_instance_

// External functions
extern "C" void FUN_71025d2dc0(u64*);            // StageBase constructor
extern "C" u8   FUN_7103167000(u64, u64*, u64*);  // Event listener register
extern "C" void FUN_71030080c0(u64);              // StageWufuIsland helper (clear list)

// WufuIsland singleton
extern "C" u64* DAT_710532de20 HIDDEN;

// 0x7103007a30 (1,676 bytes) — StageWufuIsland constructor
// [derived: Ghidra decompilation at 0x7103007a30]
// Calls StageBase ctor, sets WufuIsland vtable, initializes all fields,
// registers 5 event listeners with the stage manager.
extern "C" void FUN_7103007a30(u64* p)
{
    // Call base class constructor
    FUN_71025d2dc0(p);

    // Set WufuIsland vtable
    *p = (u64)&PTR_LAB_710515f3b0;

    // Clear WufuIsland-specific padding/fields
    *(u64*)((char*)p + 0x739) = 0;
    *(u64*)((char*)p + 0x734) = 0;

    // Initialize float constants (hex representations of float values)
    // +0x830: 10.0f (0x41200000)
    *(u32*)(p + 0x106) = 0x41200000;
    *(u32*)((char*)p + 0x93c) = 0x41200000;
    // +0x974: 0.5f
    *(u32*)((char*)p + 0x974) = 0x3f000000;
    *(u32*)((char*)p + 0x99c) = 0x3f000000;
    // +0x9a0: -0.5f
    *(u32*)(p + 0x134) = 0xbf000000;
    // +0x9a4: 300.0f
    *(u32*)((char*)p + 0x9a4) = 0x43960000;
    // +0x9ac: 60.0f
    *(u32*)((char*)p + 0x9ac) = 0x42700000;

    // Sub-object vtable at +0x748
    p[0xe9] = (u64)&PTR_LAB_71051618a0;

    // More float constants
    *(u32*)(p + 0x136) = 0x3e99999a;  // 0.3f
    *(u32*)(p + 0xf7) = 0x40833333;  // 4.1f
    *(u32*)(p + 0x10c) = 0x3cf5c28f;  // 0.03f
    *(u32*)((char*)p + 0x8b4) = 0x42c80000; // 100.0f
    *(u32*)(p + 0x117) = 0x42c80000;
    *(u32*)(p + 0x12e) = 0x42c80000;
    *(u32*)((char*)p + 0x9d4) = 0xc2b40000; // -90.0f

    // Sub-object vtable at +0x7D8
    p[0xfb] = (u64)&PTR_LAB_7105161860;

    // More initialization
    *(u32*)((char*)p + 0x864) = 0x3f99999a; // 1.2f
    *(u32*)(p + 0x12f) = 0x3d4ccccd;  // 0.05f
    *(u32*)(p + 0x130) = 0x3d4ccccd;
    *(u32*)((char*)p + 0x9dc) = 0x3dcccccd; // 0.1f
    *(u32*)((char*)p + 0x834) = 0x3c;  // 60
    *(u32*)(p + 0x116) = 0x1e;        // 30
    *(u32*)(p + 0x122) = 0x1e;
    *(u32*)((char*)p + 0x984) = 0x3f7d70a4; // 0.99f
    *(u32*)((char*)p + 0x9fc) = 0x3d0f5c29; // 0.035f
    *(u32*)(p + 0x107) = 0x46;        // 70
    *(u32*)(p + 0x108) = 0x46;
    *(u32*)(p + 0x126) = 0x42480000;  // 50.0f
    *(u32*)(p + 0x132) = 8;
    *(u32*)((char*)p + 0xa04) = 0x42b40000; // 90.0f
    *(u32*)((char*)p + 0x844) = 0x3f800000; // 1.0f
    *(u32*)(p + 0x11e) = 0xc4934000;  // -1178.0f
    *(u32*)((char*)p + 0x934) = 0x43340000; // 180.0f
    *(u32*)((char*)p + 0x994) = 0xe;  // 14

    // Linked list init (self-referential)
    p[0x15e] = (u64)(p + 0x15e);
    p[0x15f] = (u64)(p + 0x15e);

    // Scale/position init (1.0f constants)
    *(u32*)(p + 0x167) = 0x3f800000;
    *(u32*)(p + 0x16c) = 0x3f800000;
    *(u32*)(p + 0x171) = 0x3f800000;
    *(u32*)(p + 0x179) = 0x3f800000;
    *(u32*)(p + 0x17f) = 0x3f800000;

    // Zero-init large range of fields
    p[0xfa] = 0; p[0xf9] = 0; p[0xf8] = 0; p[0xf6] = 0;
    p[0xf5] = 0; p[0xf4] = 0; p[0xf3] = 0; p[0xf2] = 0;
    p[0xf1] = 0; p[0xf0] = 0; p[0xef] = 0; p[0xee] = 0;
    p[0xed] = 0; p[0xec] = 0; p[0xeb] = 0;
    *(u32*)(p + 0xea) = 1;
    p[0x121] = 0; p[0x120] = 0; p[0x11f] = 0;
    p[0x125] = 0; p[0x124] = 0; p[0x123] = 0;
    p[0x131] = 0;
    p[0x139] = 0; p[0x138] = 0; p[0x137] = 0;
    p[0x13e] = 0; p[0x13d] = 0; p[0x13c] = 0;
    p[0x105] = 0; p[0x104] = 0; p[0x103] = 0;
    p[0x102] = 0; p[0x101] = 0; p[0x100] = 0;
    p[0xff] = 0; p[0xfe] = 0; p[0xfd] = 0;
    p[0x115] = 0; p[0x114] = 0; p[0x113] = 0;
    p[0x112] = 0; p[0x111] = 0; p[0x110] = 0;
    p[0x10f] = 0; p[0x10e] = 0; p[0x10d] = 0;
    p[0x11d] = 0; p[0x11c] = 0; p[0x11b] = 0;
    p[0x11a] = 0; p[0x119] = 0; p[0x118] = 0;
    p[0x12d] = 0; p[300] = 0; p[299] = 0;
    p[0x12a] = 0; p[0x129] = 0; p[0x128] = 0;
    p[0x150] = 0; p[0x14f] = 0; p[0x14e] = 0;
    p[0x14d] = 0; p[0x14c] = 0; p[0x14b] = 0;
    p[0x14a] = 0; p[0x149] = 0; p[0x148] = 0;
    p[0x147] = 0; p[0x146] = 0; p[0x145] = 0;
    p[0x144] = 0; p[0x143] = 0; p[0x142] = 0;
    *(u32*)(p + 0xfc) = 1;
    *(u32*)((char*)p + 0x83c) = 0;
    *(u32*)(p + 0x109) = 0;
    *(u16*)(p + 0x10a) = 0;
    *(u8*)(p + 0x10b) = 0;
    *(u8*)((char*)p + 0x859) = 1;
    *(u32*)((char*)p + 0x85c) = 0;
    *(u32*)(p + 0x127) = 0x41f00000;  // 30.0f
    *(u32*)((char*)p + 0x97c) = 0x3c23d70a; // 0.01f
    *(u32*)(p + 0x133) = 0x3e4ccccd;  // 0.2f
    *(u32*)(p + 0x135) = 0;
    *(u32*)(p + 0x13a) = 0;
    *(u32*)(p + 0x13b) = 0;
    *(u32*)(p + 0x13f) = 0;
    *(u32*)(p + 0x140) = 0;
    *(u32*)(p + 0x141) = 0x41f00000;  // 30.0f

    // Zero-init more fields
    p[0x166] = 0; p[0x165] = 0; p[0x164] = 0;
    p[0x163] = 0; p[0x162] = 0; p[0x161] = 0; p[0x160] = 0;
    p[0x16b] = 0; p[0x16a] = 0; p[0x169] = 0; p[0x168] = 0;
    p[0x170] = 0; p[0x16f] = 0; p[0x16e] = 0; p[0x16d] = 0;
    p[0x174] = 0; p[0x173] = 0;
    p[0x172] = (u64)(p + 0x173);  // self-referential list head
    p[0x178] = 0; p[0x177] = 0; p[0x176] = 0; p[0x175] = 0;
    p[0x17e] = 0; p[0x17d] = 0; p[0x17c] = 0;
    p[0x17b] = 0; p[0x17a] = 0;
    p[0x182] = 0; p[0x181] = 0;
    p[0x180] = (u64)(p + 0x181);  // self-referential list head
    p[0x189] = 0; p[0x188] = 0; p[0x187] = 0;
    p[0x186] = 0; p[0x185] = 0; p[0x184] = 0; p[0x183] = 0;

    // Linked list init
    p[0x18a] = (u64)(p + 0x18a);
    p[0x18b] = (u64)(p + 0x18a);
    p[0x18c] = 0;

    // Load constant zero pair
    u64 constZeroHi = *(u64*)((char*)&PTR_ConstantZero_71052a7a88 + 8);
    u64 constZeroLo = *(u64*)&PTR_ConstantZero_71052a7a88;

    // Initialize more fields with constants
    p[0x191] = 0x3f80000000000000ULL;  // { 0.0f, 1.0f } packed
    p[0x197] = (u64)(p + 0x197);
    p[0x198] = (u64)(p + 0x197);

    u64 dat_ca8 = _UNK_7104467ca8;
    u64 dat_ca0 = _DAT_7104467ca0;

    p[400] = 0;
    p[0x192] = 0;
    *(u32*)(p + 0x193) = 0;
    p[0x196] = 0; p[0x195] = 0; p[0x194] = 0;
    p[0x19d] = 0; p[0x19c] = 0; p[0x19b] = 0;
    p[0x19a] = 0; p[0x199] = 0;
    *(u32*)((char*)p + 0xd44) = 0;
    *(u8*)(p + 0x1a9) = 0;
    *(u8*)(p + 0x1a8) = 0;
    p[0x1a7] = 0; p[0x1a6] = 0;
    p[0x1ac] = 0; p[0x1ab] = 0; p[0x1aa] = 0;
    *(u16*)(p + 0x1b0) = 0;
    *(u16*)(p + 0x1c1) = 0;
    p[0x1c0] = 0; p[0x1bf] = 0; p[0x1be] = 0;
    p[0x1bd] = 0; p[0x1bc] = 0; p[0x1bb] = 0;
    p[0x1ba] = 0; p[0x1b9] = 0; p[0x1b8] = 0;
    p[0x1b7] = 0; p[0x1b6] = 0; p[0x1b5] = 0;
    p[0x1b4] = 0; p[0x1b3] = 0; p[0x1b2] = 0; p[0x1b1] = 0;

    // Event listener block setup
    *(u16*)((char*)p + 0xe0a) = 1;
    *(u32*)((char*)p + 0xe0c) = 0;
    p[0x1c2] = (u64)p;  // owner = this
    *(u16*)(p + 0x1c3) = 1;
    *(u8*)((char*)p + 0xe1a) = 0;
    *(u32*)((char*)p + 0xe1c) = 0xffffffff;
    *(u32*)(p + 0x1ca) = 1;

    // Set rodata constant pairs
    p[0x19f] = dat_ca8;
    p[0x19e] = dat_ca0;
    u64 tmp = DAT_7104469360;
    p[0x1a1] = DAT_7104469368;
    p[0x1a0] = tmp;
    tmp = _DAT_71044646b0;
    p[0x1a3] = _UNK_71044646b8;
    p[0x1a2] = tmp;

    u64 v358 = _UNK_7104469358;
    u64 v350 = _DAT_7104469350;
    p[399] = constZeroHi;
    p[0x18e] = constZeroLo;
    p[0x1af] = constZeroHi;
    p[0x1ae] = constZeroLo;

    tmp = _DAT_7104469cd0;
    p[0x1c5] = _UNK_7104469cd8;
    p[0x1c4] = tmp;

    u64 v8b8 = _UNK_71044648b8;
    u64 v8b0 = _DAT_71044648b0;
    p[0x1a5] = v358;
    p[0x1a4] = v350;
    p[0x1c7] = v8b8;
    p[0x1c6] = v8b0;

    p[0x1c9] = 0;
    p[0x1c8] = 0;

    // Register event listener 1
    u8 res = FUN_7103167000(
        *(u64*)(*(u64*)SM_INSTANCE + 0x1c8),
        p, p + 0x1c2);
    *(u8*)(p + 0x1c3) = res & 1;

    // Event listener 2 setup
    u64 vc8 = _UNK_71044648c8;
    u64 vc0 = _DAT_71044648c0;
    p[0x1cc] = (u64)p;
    p[0x1cf] = vc8;
    p[0x1ce] = vc0;

    u64 va58 = _UNK_7104468a58;
    u64 va50 = _DAT_7104468a50;
    *(u16*)(p + 0x1cd) = 1;
    *(u8*)((char*)p + 0xe6a) = 0;
    p[0x1d1] = va58;
    p[0x1d0] = va50;
    *(u32*)((char*)p + 0xe6c) = 0xffffffff;
    *(u32*)(p + 0x1d4) = 1;
    p[0x1d3] = 0;
    p[0x1d2] = 0;

    res = FUN_7103167000(
        *(u64*)(*(u64*)SM_INSTANCE + 0x1c8),
        p, p + 0x1cc);
    *(u8*)(p + 0x1cd) = res & 1;

    // Event listener 3 setup
    u64 vee8 = _UNK_7104464ee8;
    u64 vee0 = _DAT_7104464ee0;
    p[0x1d6] = (u64)p;
    p[0x1d9] = vee8;
    p[0x1d8] = vee0;

    u64 vbf8 = _UNK_7104464bf8;
    u64 vbf0 = _DAT_7104464bf0;
    *(u16*)(p + 0x1d7) = 1;
    *(u8*)((char*)p + 0xeba) = 0;
    p[0x1db] = vbf8;
    p[0x1da] = vbf0;
    *(u32*)((char*)p + 0xebc) = 0xffffffff;
    *(u32*)(p + 0x1de) = 1;
    p[0x1dd] = 0;
    p[0x1dc] = 0;

    res = FUN_7103167000(
        *(u64*)(*(u64*)SM_INSTANCE + 0x1c8),
        p, p + 0x1d6);
    *(u8*)(p + 0x1d7) = res & 1;

    // Event listener 4 setup (same hashes as listener 3)
    p[0x1e3] = vee8;
    p[0x1e2] = vee0;
    p[0x1e0] = (u64)p;
    *(u16*)(p + 0x1e1) = 1;
    p[0x1e5] = vbf8;
    p[0x1e4] = vbf0;
    *(u8*)((char*)p + 0xf0a) = 0;
    *(u32*)((char*)p + 0xf0c) = 0xffffffff;
    *(u32*)(p + 0x1e8) = 1;
    p[0x1e7] = 0;
    p[0x1e6] = 0;

    res = FUN_7103167000(
        *(u64*)(*(u64*)SM_INSTANCE + 0x1c8),
        p, p + 0x1e0);
    u64 v398 = _UNK_7104467398;
    u64 v390 = _DAT_7104467390;
    *(u8*)(p + 0x1e1) = res & 1;

    // Event listener 5 setup
    p[0x1ea] = (u64)p;
    p[0x1ed] = v398;
    p[0x1ec] = v390;

    u64 v028 = _UNK_7104466028;
    u64 v020 = _DAT_7104466020;
    *(u16*)(p + 0x1eb) = 1;
    *(u8*)((char*)p + 0xf5a) = 0;
    p[0x1ef] = v028;
    p[0x1ee] = v020;
    *(u32*)((char*)p + 0xf5c) = 0xffffffff;
    *(u32*)(p + 0x1f2) = 1;
    p[0x1f1] = 0;
    p[0x1f0] = 0;

    res = FUN_7103167000(
        *(u64*)(*(u64*)SM_INSTANCE + 0x1c8),
        p, p + 0x1ea);
    *(u8*)(p + 0x1eb) = res & 1;

    // Final fields
    *(u16*)(p + 0x1f5) = 0;
    p[500] = 0;

    // Set WufuIsland singleton
    DAT_710532de20 = p;

    // Clear internal list
    FUN_71030080c0(p[0x181]);
    p[0x182] = 0;
    p[0x180] = (u64)(p + 0x181);
    p[0x181] = 0;
    p[0x185] = p[0x184];
}
