#include "types.h"
#include "app/FighterManager.h"
#include "app/FighterEntry.h"

// Fighter core utility functions — pool-b
// Contains param lookups, fighter kind mappings, and core fighter helpers

// ============================================================================
// get_fighter_id_from_fighter_kind
// Address: 0x710066cd40 | Size: 3,604 bytes
// Maps a 40-bit fighter_kind hash to a fighter ID (0–117).
// Returns 0xFFFFFFFF if the hash is not recognized.
// [derived: Ghidra FUN_710066cd40 — binary search over 100 fighter_kind hashes]
// ============================================================================

extern "C" u64 FUN_710066cd40(u64 param_1) {
    param_1 = param_1 & 0xFFFFFFFFFFULL;

    switch (param_1) {
    case 0x1254206ce1ULL: return 0;    // fighter_kind_mario
    case 0x135719effdULL: return 1;    // fighter_kind_donkey
    case 0x114f87b213ULL: return 2;    // fighter_kind_link
    case 0x126efca05dULL: return 3;    // fighter_kind_samus
    case 0x138d699b25ULL: return 4;    // fighter_kind_yoshi
    case 0x12d025d4d3ULL: return 5;    // fighter_kind_kirby
    case 0x1209f4dd34ULL: return 6;    // fighter_kind_fox
    case 0x10f833a6efULL: return 7;    // fighter_kind_pikachu
    case 0x1484f79606ULL: return 8;    // fighter_kind_luigi
    case 0x12d1a841b3ULL: return 9;    // fighter_kind_ness
    case 0x11009477b6ULL: return 10;   // fighter_kind_captain
    case 0x14de9fbfc5ULL: return 11;   // fighter_kind_purin
    case 0x12642ccf8cULL: return 12;   // fighter_kind_peach
    case 0x1239d9c885ULL: return 13;   // fighter_kind_koopa
    case 0x120dba0d8bULL: return 14;   // fighter_kind_zelda
    case 0x1253f95a4eULL: return 15;   // fighter_kind_sheik
    case 0x12e8fc7b64ULL: return 16;   // fighter_kind_mariod
    case 0x124d2c6d14ULL: return 17;   // fighter_kind_pichu
    case 0x134f84b84eULL: return 18;   // fighter_kind_falco
    case 0x12f0791641ULL: return 19;   // fighter_kind_marth
    case 0x12cfa73b00ULL: return 20;   // fighter_kind_younglink
    case 0x123528955eULL: return 21;   // fighter_kind_ganon
    case 0x13906caf9dULL: return 22;   // fighter_kind_mewtwo
    case 0x16ec54781fULL: return 23;   // fighter_kind_roy
    case 0x122af1b944ULL: return 24;   // fighter_kind_gamewatch
    case 0x138ced9f4eULL: return 25;   // fighter_kind_metaknight
    case 0x10941b9dd5ULL: return 26;   // fighter_kind_pit
    case 0x122e4c5ba0ULL: return 27;   // fighter_kind_szerosuit
    case 0x1609f9812fULL: return 28;   // fighter_kind_wario
    case 0x17a0f92309ULL: return 29;   // fighter_kind_snake
    case 0x10bf749280ULL: return 30;   // fighter_kind_ike
    case 0x119cb9184bULL: return 31;   // fighter_kind_pzenigame
    case 0x16b1945eceULL: return 32;   // fighter_kind_pfushigisou
    case 0x127e70e3c2ULL: return 33;   // fighter_kind_plizardon
    case 0x121f10c3e1ULL: return 34;   // fighter_kind_diddy
    case 0x10f405480fULL: return 35;   // fighter_kind_lucas
    case 0x16b9c57bd9ULL: return 36;   // fighter_kind_sonic
    case 0x18e6e65f1fULL: return 37;   // fighter_kind_dedede
    case 0x16a86efc01ULL: return 38;   // fighter_kind_pikmin
    case 0x12c55532a1ULL: return 39;   // fighter_kind_lucario
    case 0x1277079a99ULL: return 40;   // fighter_kind_robot
    case 0x1277a5240eULL: return 41;   // fighter_kind_toonlink
    case 0x137590573cULL: return 42;   // fighter_kind_wolf
    case 0x135c2b1c9bULL: return 43;   // fighter_kind_murabito
    case 0x149970e8e1ULL: return 44;   // fighter_kind_rockman
    case 0x129656d69bULL: return 45;   // fighter_kind_wiifit
    case 0x15ef495a02ULL: return 46;   // fighter_kind_rosetta
    case 0x1180950000ULL: return 47;   // fighter_kind_littlemac
    case 0x1525947ce7ULL: return 48;   // fighter_kind_gekkouga
    case 0x14cbc59038ULL: return 49;   // fighter_kind_palutena
    case 0x131a10f233ULL: return 50;   // fighter_kind_pacman
    case 0x14ff0713f3ULL: return 51;   // fighter_kind_reflet
    case 0x164cc41e55ULL: return 52;   // fighter_kind_shulk
    case 0x15dce2594fULL: return 53;   // fighter_kind_koopajr
    case 0x15d6fa9492ULL: return 54;   // fighter_kind_duckhunt
    case 0x136136f5bdULL: return 55;   // fighter_kind_ryu
    case 0x13766c540dULL: return 56;   // fighter_kind_cloud
    case 0x1289ad2c51ULL: return 57;   // fighter_kind_kamui
    case 0x148584085aULL: return 58;   // fighter_kind_bayonetta
    case 0x15f8282714ULL: return 59;   // fighter_kind_inkling
    case 0x1081356429ULL: return 60;   // fighter_kind_ridley
    case 0x10fed06867ULL: return 61;   // fighter_kind_simon
    case 0x127c21beabULL: return 62;   // fighter_kind_krool
    case 0x12c30e8564ULL: return 63;   // fighter_kind_shizue
    case 0x16efa9014dULL: return 64;   // fighter_kind_gaogaen
    case 0x1431aaf466ULL: return 65;   // fighter_kind_chrom
    case 0x1367240d3aULL: return 66;   // fighter_kind_daisy
    case 0x1278631eb0ULL: return 67;   // fighter_kind_packun
    case 0x146cb3dd7fULL: return 68;   // fighter_kind_jack
    case 0x124261a72fULL: return 69;   // fighter_kind_brave
    case 0x13251abe2eULL: return 70;   // fighter_kind_buddy
    case 0x1426792cf8ULL: return 71;   // fighter_kind_dolly
    case 0x17de1da827ULL: return 72;   // fighter_kind_master
    case 0x1989d173d5ULL: return 73;   // fighter_kind_tantan
    case 0x166e9fae70ULL: return 74;   // fighter_kind_pickel
    case 0x1182e9dd40ULL: return 75;   // fighter_kind_edge
    case 0x110b48c23eULL: return 76;   // fighter_kind_eflame
    case 0x1390e38ebbULL: return 77;   // fighter_kind_elight
    case 0x161d8d1990ULL: return 78;   // fighter_kind_demon
    case 0x167050fd7bULL: return 79;   // fighter_kind_trail
    case 0x166a8a2906ULL: return 80;   // fighter_kind_miifighter
    case 0x134b155e5aULL: return 81;   // fighter_kind_miiswordsman
    case 0x11d151c23aULL: return 82;   // fighter_kind_miigunner
    case 0x12a733f9e8ULL: return 83;   // fighter_kind_richter
    case 0x1250da2f26ULL: return 84;   // fighter_kind_darkpit
    case 0x1226f4b6cdULL: return 85;   // fighter_kind_lucina
    case 0x13edfdb2d3ULL: return 86;   // fighter_kind_ken
    case 0x131b3af789ULL: return 87;   // fighter_kind_dark_samus
    case 0x13dfa966e6ULL: return 88;   // fighter_kind_kroolshipcannon (?)
    case 0x110c2df884ULL: return 89;   // fighter_kind_89
    case 0x13ea13c533ULL: return 90;   // fighter_kind_90
    case 0x13843785a5ULL: return 91;   // fighter_kind_91
    case 0x12e075ea9aULL: return 92;   // fighter_kind_92
    case 0x12fc152df0ULL: return 93;   // fighter_kind_93
    case 0x18cc9a036cULL: return 110;  // fighter_kind_110
    case 0x153248b0b6ULL: return 111;  // fighter_kind_111
    case 0x170835b8c2ULL: return 112;  // fighter_kind_112
    case 0x1523e3376eULL: return 113;  // fighter_kind_113
    case 0x1586cc8de4ULL: return 114;  // fighter_kind_114
    case 0x124b43b41eULL: return 115;  // fighter_kind_115
    case 0x122567f488ULL: return 116;  // fighter_kind_116
    case 0x1431ea5ea7ULL: return 117;  // fighter_kind_117
    default: return 0xFFFFFFFF;
    }
}

// ============================================================================
// get_entry_in_fighter_param_kind_struct
// Address: 0x71006f3b00 | Size: 15,848 bytes
// Maps a 40-bit param hash to a (type_info, field_ptr) pair in a fighter param struct.
// Returns (&PTR_LAB_710523bba0, nullptr) if hash is not recognized.
// The struct spans ~0x628 bytes; 292 f32 fields, 26+25 int fields, 19 bool/u8 fields.
// [derived: Ghidra FUN_71006f3b00 � binary search over 369 param hash values]
// ============================================================================

struct ParamEntry {
    const void* type_info;
    void* field_ptr;
};

// Param type descriptor pointers (.rodata)
#define HIDDEN __attribute__((visibility("hidden")))
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f61460;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f613d8;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f68490;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f689e0;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f79298;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f89758;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f897e0;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f89868;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f898f0;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_7104f89978;
extern "C" __attribute__((visibility("hidden"))) void* PTR_LAB_710523bba0;  // default/not-found type
#undef HIDDEN

extern "C" ParamEntry FUN_71006f3b00(char* param_1, u64 param_2) {
    ParamEntry result;
    result.type_info = &PTR_LAB_710523bba0;
    result.field_ptr = nullptr;
    char* base = param_1;
    param_2 = param_2 & 0xFFFFFFFFFFULL;

    switch (param_2) {
    case 0x4f7c0246aULL: result.type_info = &PTR_LAB_7104f89758; result.field_ptr = base + 0x60c; return result;
    case 0x5ec462584ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xa8; return result;
    case 0x607cd5541ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x80; return result;
    case 0x6a0d82dadULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4c; return result;
    case 0x6f54de50fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x178; return result;
    case 0x85699c32bULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x4b0; return result;
    case 0x92eb50b90ULL: result.type_info = &PTR_LAB_7104f897e0; result.field_ptr = base + 0x610; return result;
    case 0x9b37e6337ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x218; return result;
    case 0xa6cbe02d5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4c0; return result;
    case 0xadec47ea3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x24; return result;
    case 0xae3b1cda8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x210; return result;
    case 0xb42b7b19fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x50; return result;
    case 0xb888983a8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x45c; return result;
    case 0xb96c232a6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1fc; return result;
    case 0xb99cc3fbcULL: result.type_info = &PTR_LAB_7104f89978; result.field_ptr = base + 0x624; break;
    case 0xba18057d9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x68; return result;
    case 0xbba2bb330ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x64; return result;
    case 0xbcd2c83a6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x78; return result;
    case 0xbfac2be9eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xbc; return result;
    case 0xc28b70a0bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x478; return result;
    case 0xc516675c5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xb8; return result;
    case 0xc541ef0b2ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x0; return result;
    case 0xc57b5d372ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4b8; return result;
    case 0xc6cc4e8a9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x474; return result;
    case 0xc8cc9db76ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x20; return result;
    case 0xc9ecb437bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x434; return result;
    case 0xcae5f1790ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xc8; return result;
    case 0xcc9d2f2daULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x38; return result;
    case 0xcca113a7fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x7c; return result;
    case 0xccebc82c8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4bc; return result;
    case 0xcd1eef8c1ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xd4; return result;
    case 0xcf8d5ed42ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xd0; return result;
    case 0xcfe4b9b7eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1d4; return result;
    case 0xd07d69a9bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xa0; return result;
    case 0xd1964cc31ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2c; return result;
    case 0xd279d915cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x158; return result;
    case 0xd320020f6ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x5f4; return result;
    case 0xd4d7c9e77ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x28; return result;
    case 0xd5aaabf9bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x30; return result;
    case 0xd86798caeULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x54; return result;
    case 0xd8b96a1e1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xac; return result;
    case 0xdaa959ca9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x154; return result;
    case 0xdaffbccfdULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x17c; return result;
    case 0xdb8b2a940ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xc0; return result;
    case 0xdc9a6e1baULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x4a8; return result;
    case 0xdd82b4e30ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x548; return result;
    case 0xe02c8a989ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x588; return result;
    case 0xe0b4b30acULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5b8; return result;
    case 0xe199c6a2aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xb0; return result;
    case 0xe1a7373c0ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0xec; return result;
    case 0xe35ca3d82ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x12c; return result;
    case 0xe37b007cdULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x203; return result;
    case 0xe6992ff2fULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x131; return result;
    case 0xe8fc0a47cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x584; return result;
    case 0xe9d9eaed5ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5ec; return result;
    case 0xea1225bcaULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xc; return result;
    case 0xecc9bae0fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1d8; return result;
    case 0xed1f9fdb8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x48; return result;
    case 0xee2ec2860ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x10; return result;
    case 0xef53a098cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x8; return result;
    case 0xefbdfb1dbULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x138; return result;
    case 0xf0ab7d261ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x198; return result;
    case 0xf1425f55bULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x130; return result;
    case 0xf17104c94ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1c; return result;
    case 0xf25ec86beULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5c; return result;
    case 0xf35d3204cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x168; return result;
    case 0xf5c75804bULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x388; return result;
    case 0xf71f4d4f8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x58; return result;
    case 0xf95da83edULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x470; return result;
    case 0xfb53839e9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x170; return result;
    case 0xfb784e2d7ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x174; return result;
    case 0xfc21f9804ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x430; return result;
    case 0xfc61dd2ffULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x190; return result;
    case 0xfce095390ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5e8; return result;
    case 0xfeae16f39ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4fc; return result;
    case 0x10059dd0d2ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x19c; return result;
    case 0x104184d2b9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x428; return result;
    case 0x104a761b91ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3c; return result;
    case 0x107e0218b9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x40; return result;
    case 0x1086aaf4efULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x132; return result;
    case 0x108eef6d31ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x180; return result;
    case 0x1095b52773ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x34; return result;
    case 0x109a712db9ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xcc; return result;
    case 0x10b21eb5e9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x440; return result;
    case 0x10cf41d023ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4c8; return result;
    case 0x10d35302b0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x204; return result;
    case 0x10fee65b16ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x530; return result;
    case 0x111d967c16ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x164; return result;
    case 0x1125bbd2b8ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x214; return result;
    case 0x112d83771bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x18; return result;
    case 0x1138633820ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x15c; return result;
    case 0x113a636747ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x16c; return result;
    case 0x114a6894beULL: result.type_info = &PTR_LAB_7104f89868; result.field_ptr = base + 0x614; return result;
    case 0x116b253e56ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xb4; return result;
    case 0x11893de439ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x590; return result;
    case 0x119943e3b9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1a8; return result;
    case 0x11a49f3b9cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x484; return result;
    case 0x11a7fb7eb4ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x500; return result;
    case 0x11aa00608aULL: result.type_info = &PTR_LAB_7104f898f0; result.field_ptr = base + 0x620; return result;
    case 0x11ac774cb3ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x188; return result;
    case 0x11b56b35d5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x160; return result;
    case 0x11b9282bf8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x47c; return result;
    case 0x11d4f5cf13ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x480; return result;
    case 0x11d6ca2fb8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4f8; return result;
    case 0x11e69673b4ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x39c; return result;
    case 0x11f89a4b7eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1ac; return result;
    case 0x120a28f3bdULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4e8; return result;
    case 0x1220fc2660ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x60; return result;
    case 0x12326f1f2aULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5ef; return result;
    case 0x1236fe6c04ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x578; return result;
    case 0x123b20d484ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x424; return result;
    case 0x123c4d109dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x420; return result;
    case 0x123edf1e63ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5b4; return result;
    case 0x124c60d24cULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x5a0; return result;
    case 0x124ef433deULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1a4; return result;
    case 0x126b8ac031ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5dc; return result;
    case 0x127b932d22ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x44c; return result;
    case 0x128347f8a9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4f4; return result;
    case 0x128fe2057dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x234; return result;
    case 0x12959d4c0eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x444; return result;
    case 0x12a4a49162ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1e4; return result;
    case 0x12ac472b91ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xc4; return result;
    case 0x12aff73dbeULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x570; return result;
    case 0x12e29a7c98ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x448; return result;
    case 0x12ebd00c2fULL: result.type_info = &PTR_LAB_7104f79298; result.field_ptr = base + 0x618; return result;
    case 0x12ec5626feULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x6c; return result;
    case 0x12f882f962ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x544; return result;
    case 0x13042acb2dULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5ee; return result;
    case 0x1308ed8724ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x128; return result;
    case 0x1309f7ccf9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x46c; return result;
    case 0x130a4c3190ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xe4; return result;
    case 0x130b45999aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x9c; return result;
    case 0x130c514216ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x394; return result;
    case 0x13147ff0beULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x404; return result;
    case 0x1319e6e040ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1a0; return result;
    case 0x132a292898ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xe8; return result;
    case 0x1335c61a7fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x14; return result;
    case 0x13372c1820ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xe0; return result;
    case 0x134067a2f8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x400; return result;
    case 0x134784909bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xdc; return result;
    case 0x1357b18314ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x408; return result;
    case 0x137ae4b92bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xd8; return result;
    case 0x137b567280ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x390; return result;
    case 0x1388d794d6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x43c; return result;
    case 0x13955813acULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x398; return result;
    case 0x13c30c93f0ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xa4; return result;
    case 0x13cf982a55ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5f1; return result;
    case 0x13dafe5c9eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x468; return result;
    case 0x13db8c9720ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x270; return result;
    case 0x13e3bcfb18ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x200; return result;
    case 0x13f0132510ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x604; return result;
    case 0x13f432cb80ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x510; return result;
    case 0x13fadfb7bbULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x464; return result;
    case 0x13fba2a06aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x460; return result;
    case 0x1400169d6cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1c0; return result;
    case 0x1404be856eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4c4; return result;
    case 0x1408832504ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x202; return result;
    case 0x14089ff819ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x418; return result;
    case 0x140ca0f097ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1e8; return result;
    case 0x141bbc85feULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x40c; return result;
    case 0x142913a94dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x438; return result;
    case 0x1441c971d1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1cc; return result;
    case 0x144b518bb3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x41c; return result;
    case 0x144f57051fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x540; return result;
    case 0x145620fd97ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5ed; return result;
    case 0x1459f8f329ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1b0; return result;
    case 0x145baa5961ULL: result.type_info = &PTR_LAB_7104f79298; result.field_ptr = base + 0x61c; return result;
    case 0x145c87aa5fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x414; return result;
    case 0x14605ef774ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x42c; return result;
    case 0x1472d6a45dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x150; return result;
    case 0x148eaba016ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x25c; return result;
    case 0x14984b7579ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x410; return result;
    case 0x14a1596433ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x538; return result;
    case 0x14afc710fdULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1c4; return result;
    case 0x14b47f37ddULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x528; return result;
    case 0x14d0bef17aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1ec; return result;
    case 0x14d34d14d0ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x108; return result;
    case 0x14d65e54a5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x53c; return result;
    case 0x14d8c0206bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1c8; return result;
    case 0x14fefd6a53ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x264; return result;
    case 0x15041b12c8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x580; return result;
    case 0x150ad6505aULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xf0; return result;
    case 0x15206d7cfcULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x488; return result;
    case 0x15293a80ecULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x598; return result;
    case 0x152c88b901ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3bc; return result;
    case 0x153276436bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x50c; return result;
    case 0x1543471267ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x514; return result;
    case 0x1572b3703dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x194; return result;
    case 0x1596802767ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x120; return result;
    case 0x15bb516057ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x58c; return result;
    case 0x15bd8af49dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4f0; return result;
    case 0x15c1cd0216ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x114; return result;
    case 0x15ea6cf481ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1dc; return result;
    case 0x1607b4d17cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3a4; return result;
    case 0x160b6fa9d6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x458; return result;
    case 0x161eafe03dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3a0; return result;
    case 0x163fab98bfULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x1f4; return result;
    case 0x164db527bbULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5b0; return result;
    case 0x1682a194a7ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x84; return result;
    case 0x1683c01d48ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1f0; return result;
    case 0x1687a6b187ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3a8; return result;
    case 0x1689689e08ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x524; return result;
    case 0x16901c3105ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x144; return result;
    case 0x169266f86cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x454; return result;
    case 0x169c79c7abULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x508; return result;
    case 0x169ebd80c6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3ac; return result;
    case 0x16a1ef489cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x560; return result;
    case 0x16a3bb4697ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5a8; return result;
    case 0x16d4bc7601ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5ac; return result;
    case 0x16e561c8faULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x450; return result;
    case 0x16f859cf04ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x52c; return result;
    case 0x170c3e372eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x268; return result;
    case 0x1722e8dbedULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1e0; return result;
    case 0x1738bafb00ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x278; return result;
    case 0x174879e994ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x520; return result;
    case 0x174fbdcb96ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x27c; return result;
    case 0x176fc57222ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x29c; return result;
    case 0x1790aeb0ffULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x208; return result;
    case 0x179814dd89ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x44; return result;
    case 0x17d6b49a2cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x280; return result;
    case 0x17e07e58aeULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x608; return result;
    case 0x17e10662a4ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5e4; return result;
    case 0x17e2f4bcceULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2a0; return result;
    case 0x1800b91901ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x100; return result;
    case 0x1814e136c5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x21c; return result;
    case 0x1816a7889cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x228; return result;
    case 0x185125a3a8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1bc; return result;
    case 0x185b017b48ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x5e0; return result;
    case 0x1861a0b80aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x22c; return result;
    case 0x1863e60653ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x220; return result;
    case 0x187367db00ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x3d8; return result;
    case 0x18744ee6c1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4ec; return result;
    case 0x187608007bULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x5f0; return result;
    case 0x189aea226cULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0xf8; return result;
    case 0x18c081a573ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2bc; return result;
    case 0x18cde09792ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x1f8; return result;
    case 0x18f0607a99ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x201; return result;
    case 0x18f8a9e9b0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x230; return result;
    case 0x18faef57e9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x224; return result;
    case 0x19020dd9edULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x54c; return result;
    case 0x1902ebb538ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x14c; return result;
    case 0x19080c77a2ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x288; return result;
    case 0x1927b1177bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x504; return result;
    case 0x192bdc7824ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x10c; return result;
    case 0x19327d6d0aULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x374; return result;
    case 0x19373c12d3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x370; return result;
    case 0x1946449e01ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1b4; return result;
    case 0x199c852b59ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x490; return result;
    case 0x19dbfd0fa8ULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x1d0; return result;
    case 0x19e03395b5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x1b8; return result;
    case 0x19eb821bcfULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x494; return result;
    case 0x19f190006aULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x384; return result;
    case 0x1a0381bc2eULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x518; return result;
    case 0x1a0ac3b7cfULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3b8; return result;
    case 0x1a3a0acd2aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3c0; return result;
    case 0x1a4262b54fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x90; return result;
    case 0x1a450f7156ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x8c; return result;
    case 0x1a4bd4f964ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x88; return result;
    case 0x1a4e9ff7ccULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x378; return result;
    case 0x1a58828323ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x70; return result;
    case 0x1a605a6019ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x498; return result;
    case 0x1a71149713ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3d4; return result;
    case 0x1a786b5238ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x4d0; return result;
    case 0x1a7fdc453cULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x124; return result;
    case 0x1a860c75c8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x550; return result;
    case 0x1aa13a064fULL: result.type_info = &PTR_LAB_7104f68490; result.field_ptr = base + 0x118; return result;
    case 0x1aba014a91ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x554; return result;
    case 0x1ac9af3db1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x290; return result;
    case 0x1b12a1b428ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x260; return result;
    case 0x1b14a4ad3cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xfc; return result;
    case 0x1b21a28766ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2b4; return result;
    case 0x1b3650250cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3f8; return result;
    case 0x1b4157159aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3f4; return result;
    case 0x1b41fc7f20ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x55c; return result;
    case 0x1b467ce4f2ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3b4; return result;
    case 0x1b56a5b7f0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2b0; return result;
    case 0x1b64c11828ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x98; return result;
    case 0x1b901912f0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x148; return result;
    case 0x1b9a7b1aa3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0xf4; return result;
    case 0x1baf5974b6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3fc; return result;
    case 0x1bb8abd6dcULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2b8; return result;
    case 0x1bdbd2b750ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x3c8; return result;
    case 0x1bf2c4c8e6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x558; return result;
    case 0x1bfaa2e04fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x94; return result;
    case 0x1c08c51661ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x3e8; return result;
    case 0x1c217c1142ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3d0; return result;
    case 0x1c50883ec7ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x304; return result;
    case 0x1cba8b77b5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x350; return result;
    case 0x1cbe865febULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2fc; return result;
    case 0x1cc9816f7dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x300; return result;
    case 0x1cf8de091eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x568; return result;
    case 0x1d4e010623ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2c8; return result;
    case 0x1d633fc2ebULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x134; return result;
    case 0x1d71e21b0bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x74; return result;
    case 0x1d9d223c70ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x380; return result;
    case 0x1da00f670fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2c0; return result;
    case 0x1dadf9c838ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x564; return result;
    case 0x1dd6c7c89cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x28c; return result;
    case 0x1dd7085799ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2c4; return result;
    case 0x1dea250ce6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x37c; return result;
    case 0x1e029a4305ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x104; return result;
    case 0x1e780404ddULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x238; return result;
    case 0x1e8ec321e3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4a0; return result;
    case 0x1ec3673eddULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x308; return result;
    case 0x1ef9c41175ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x4a4; return result;
    case 0x1f079d8bd3ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x284; return result;
    case 0x1f0b9b0e25ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x110; return result;
    case 0x1f1ee4e2c9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5f8; return result;
    case 0x1f69e3d25fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5fc; return result;
    case 0x1f7e5272d7ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x34c; return result;
    case 0x1f897884d1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5bc; return result;
    case 0x1f8e9c276aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x11c; return result;
    case 0x1f905c13fbULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x344; return result;
    case 0x1fc14378faULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x3e0; return result;
    case 0x1fe35e38aeULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x240; return result;
    case 0x1fe75b236dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x348; return result;
    case 0x1ff0ea83e5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x600; return result;
    case 0x1ffe7fb447ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5c0; return result;
    case 0x201f91f51dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x20c; return result;
    case 0x204850f761ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x4e0; return result;
    case 0x2080da265fULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x4d8; return result;
    case 0x213c5d9f30ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2a4; return result;
    case 0x214b5aafa6ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2a8; return result;
    case 0x21d253fe1cULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2ac; return result;
    case 0x2234f9e1e4ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x310; return result;
    case 0x223ce059e4ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x338; return result;
    case 0x2243fed172ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x314; return result;
    case 0x228658238eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5c4; return result;
    case 0x22daf780c8ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x318; return result;
    case 0x22eeb7dc16ULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x248; return result;
    case 0x22f15f1318ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5c8; return result;
    case 0x23206aa8c9ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2e8; return result;
    case 0x23576d985fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2e4; return result;
    case 0x235bbfe20aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2e0; return result;
    case 0x23b5b18326ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2d8; return result;
    case 0x23b963f973ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2ec; return result;
    case 0x23c2b6b3b0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2dc; return result;
    case 0x23ca50df2bULL: result.type_info = &PTR_LAB_7104f613d8; result.field_ptr = base + 0x358; return result;
    case 0x23ed975439ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x340; return result;
    case 0x241281fa6fULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5d4; return result;
    case 0x2421d88056ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x320; return result;
    case 0x24306ba249ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2d4; return result;
    case 0x2456dfb0c0ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x31c; return result;
    case 0x245713bad2ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x330; return result;
    case 0x24724ea534ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2cc; return result;
    case 0x24b8d1d1ecULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x324; return result;
    case 0x24b91ddbfeULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x328; return result;
    case 0x24bee4a5aaULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2d0; return result;
    case 0x24ce1aeb68ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x32c; return result;
    case 0x24dea774abULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x364; return result;
    case 0x259b7edbffULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5cc; return result;
    case 0x25ec79eb69ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5d0; return result;
    case 0x26153a746bULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x258; return result;
    case 0x268c3325d1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x254; return result;
    case 0x26fb341547ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x250; return result;
    case 0x271984ee09ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x13c; return result;
    case 0x281b06d9e5ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3f0; return result;
    case 0x293cf74337ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2f4; return result;
    case 0x294bf073a1ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2f0; return result;
    case 0x295785c851ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x360; return result;
    case 0x29a5fe128dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x2f8; return result;
    case 0x2a23dea6e7ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x5d8; return result;
    case 0x2a3504f64eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x298; return result;
    case 0x2ab2a23d0dULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x294; return result;
    case 0x2b7e124128ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x36c; return result;
    case 0x2be31da05eULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x368; return result;
    case 0x2bf4bef265ULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x140; return result;
    case 0x2c816b267aULL: result.type_info = &PTR_LAB_7104f61460; result.field_ptr = base + 0x3b0; return result;
    case 0x2ea659cf56ULL: result.type_info = &PTR_LAB_7104f689e0; result.field_ptr = base + 0x139; return result;
    }
    return result;
}

// ============================================================================
// FighterManager utility functions
// ============================================================================

#define HIDDEN2 __attribute__((visibility("hidden")))

// FighterManager singleton
// [derived: all FighterManager:: functions dereference this global]
namespace lib { extern "C" void* Singleton_app_FighterManager_instance_ asm("_ZN3lib9SingletonIN3app14FighterManagerEE9instance_E") HIDDEN2; }
#define FM_INSTANCE (reinterpret_cast<app::FighterManager*>(lib::Singleton_app_FighterManager_instance_))

extern "C" [[noreturn]] void abort();
extern "C" void FUN_7100653490(void* entry, s32 param);  // deactivate entry helper [HARD, simd_complex]
extern "C" void FUN_7100649540(u64 battle_object, s32 enable, s32 rate, s32 duration, s32 param_5);  // slow control [HARD, complex_tail_call]
extern "C" u64 FUN_710160e2a0(u32 object_id);  // get fighter battle object helper [derived: wraps get_battle_object_from_id + null fallback]

// ============================================================================
// is_loaded_fighter
// Address: 0x7101653310 | Size: 68 bytes
// Returns 1 if the fighter at entry_id is loaded and not flagged as unloaded.
// [derived: Ghidra FUN_7101653310 — checks singleton, bounds, entry ptr, unload flag]
// ============================================================================

// NOTE: Upstream Clang 8 reorders the param check before the singleton load.
// NX Clang checks singleton first. Structurally correct, ordering mismatch only.
extern "C" u64 FUN_7101653310(s32 entry_id) {
    using namespace app;
    if (FM_INSTANCE != nullptr && (u32)entry_id < 8) {
        FighterEntry* entry = reinterpret_cast<FighterEntry*>(FM_INSTANCE->data->entries[entry_id]);
        if (entry != nullptr && entry->is_unloaded != 1) {
            return 1;
        }
    }
    return 0;
}

// ============================================================================
// is_activate_fighter
// Address: 0x7101653500 | Size: 72 bytes
// Returns true if the fighter entry at entry_id exists and has entry_type == 6 (active).
// [derived: Ghidra FUN_7101653500 — aborts on OOB, checks entry_type]
// ============================================================================

extern "C" bool FUN_7101653500(s32 entry_id) {
    using namespace app;
    if ((u32)entry_id >= 8) {
        abort();
    }
    FighterEntry* entry = reinterpret_cast<FighterEntry*>(FM_INSTANCE->data->entries[entry_id]);
    if (entry != nullptr) {
        return entry->entry_type == 6;
    }
    return false;
}

// ============================================================================
// deactivate_fighter
// Address: 0x7101653550 | Size: 68 bytes
// Deactivates a fighter entry if it is currently active (entry_type == 6).
// [derived: Ghidra FUN_7101653550 — calls FUN_7100653490 to perform deactivation]
// ============================================================================

extern "C" void FUN_7101653550(s32 entry_id) {
    using namespace app;
    if ((u32)entry_id >= 8) {
        abort();
    }
    FighterEntry* entry = reinterpret_cast<FighterEntry*>(FM_INSTANCE->data->entries[entry_id]);
    if (entry->entry_type == 6) {
        FUN_7100653490(entry, 1);
    }
}

// ============================================================================
// set_fighter_slow
// Address: 0x7101652920 | Size: 184 bytes
// Sets slow-motion on a fighter (and its partner if present).
// [derived: Ghidra FUN_7101652920 — reads current_index to pick active slot,
//  calls FUN_7100649540 to apply slow, checks partner_flags bit 1 for partner]
// ============================================================================

extern "C" void FUN_7101652920(s32 entry_id, s32 rate, s32 duration) {
    using namespace app;
    if (entry_id == -1) return;
    if ((u32)entry_id >= 8) {
        abort();
    }
    FighterEntry* entry = reinterpret_cast<FighterEntry*>(FM_INSTANCE->data->entries[entry_id]);
    if (entry != nullptr && entry->entry_type == 6) {
        u64 battle_object = reinterpret_cast<u64>(entry->slots[entry->current_index]);
        FUN_7100649540(battle_object, 1, rate, duration, 0);
        if ((entry->partner_flags >> 1) & 1) {
            u64 partner = reinterpret_cast<u64>(entry->slots[1]);
            FUN_7100649540(partner, 1, rate, duration, 0);
        }
    }
}

// ============================================================================
// cancel_fighter_slow
// Address: 0x71016529e0 | Size: 164 bytes
// Cancels slow-motion on a fighter (and its partner if present).
// [derived: Ghidra FUN_71016529e0 — same structure as set_fighter_slow but
//  passes (0,0,0,0) to FUN_7100649540 instead of (1,rate,duration,0)]
// ============================================================================

extern "C" void FUN_71016529e0(s32 entry_id) {
    using namespace app;
    if (entry_id == -1) return;
    if ((u32)entry_id >= 8) {
        abort();
    }
    FighterEntry* entry = reinterpret_cast<FighterEntry*>(FM_INSTANCE->data->entries[entry_id]);
    if (entry != nullptr && entry->entry_type == 6) {
        u64 battle_object = reinterpret_cast<u64>(entry->slots[entry->current_index]);
        FUN_7100649540(battle_object, 0, 0, 0, 0);
        if ((entry->partner_flags >> 1) & 1) {
            u64 partner = reinterpret_cast<u64>(entry->slots[1]);
            FUN_7100649540(partner, 0, 0, 0, 0);
        }
    }
}

// ============================================================================
// is_fighter_enabled
// Address: 0x71015ce5c0 | Size: 88 bytes
// Returns 1 if the fighter's status is not dead (0xb5) or entry (0x1d6).
// [derived: is_fighter_enabled (community name) — calls FUN_710160e2a0
//  to get battle object, reads StatusModule vtable[0x110/8] for status_kind,
//  0xb5 = STATUS_KIND_DEAD, 0x1d6 = STATUS_KIND_ENTRY]
// ============================================================================

extern "C" u32 FUN_71015ce5c0(u32 object_id) {
    if (__builtin_expect((object_id >> 28) != 0, 0)) {
        return 0;
    }
    u64 obj = FUN_710160e2a0(object_id);
    if (obj == 0) {
        return 0;
    }
    // StatusModule at +0x40 [derived: BattleObjectModuleAccessor +0x40 = StatusModule]
    u64* status_mod = *reinterpret_cast<u64**>(obj + 0x40);
    // vtable[0x110/8] = get_status_kind [derived: returns int status kind]
    s32 kind = reinterpret_cast<s32(*)(u64*)>(*reinterpret_cast<void**>(*status_mod + 0x110))(status_mod);
    if (kind == 0xb5 || kind == 0x1d6) {
        return 0;
    }
    return 1;
}

// ============================================================================
// ItemManager utility functions
// ============================================================================

// ItemManager singleton
// [derived: all ItemManager:: functions dereference this global]
namespace lib { extern "C" void* Singleton_app_ItemManager_instance_ asm("_ZN3lib9SingletonIN3app11ItemManagerEE9instance_E") HIDDEN2; }
#define IM_INSTANCE (reinterpret_cast<u8*>(lib::Singleton_app_ItemManager_instance_))

// FighterParamAccessor2 singleton
// [derived: init_bound_frame/special_lw_gravity load params through this]
namespace lib { extern "C" void* Singleton_app_FighterParamAccessor2_instance_ asm("_ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E") HIDDEN2; }
#define FPA2_INSTANCE (reinterpret_cast<u8*>(lib::Singleton_app_FighterParamAccessor2_instance_))

// Misc globals
extern "C" void* DAT_7105328f50 HIDDEN2;  // item se controller [derived: used in stop_ingame_se]

// Invalid item battle object ID
#define INVALID_ITEM_ID 0x50000000u

// ============================================================================
// find_active_item_from_id
// Address: 0x71015ca930 | Size: 92 bytes
// Finds an active item by battle object ID. Returns module accessor ptr (+0x98)
// or nullptr if not found.
// [derived: Ghidra FUN_71015ca930 — iterates active item list at IM+0x28..+0x30,
//  checks item+0x90->+0x18 == 0 (alive) and item+8 == id]
// ============================================================================

extern "C" u64 FUN_71015ca930(u32 object_id) {
    u64 found = 0;
    if (object_id != INVALID_ITEM_ID) {
        u64* begin = *reinterpret_cast<u64**>(IM_INSTANCE + 0x28);
        u64* end   = *reinterpret_cast<u64**>(IM_INSTANCE + 0x30);
        for (u64* it = begin; it != end; ++it) {
            u64 item = *it;
            // Check alive: *(item+0x90)->+0x18 == 0
            if (*(u8*)(*(u64*)(item + 0x90) + 0x18) == 0 &&
                *(u32*)(item + 0x8) == object_id) {
                found = item;
                break;
            }
        }
    }
    // [derived: original uses csel for branchless return]
    u64 addr = found + 0x98;
    return (found != 0) ? addr : 0;
}

// ============================================================================
// remove_item_from_id
// Address: 0x71015ca990 | Size: 88 bytes
// Removes an item by battle object ID via vtable call at +0x520.
// [derived: Ghidra FUN_71015ca990 — iterates item list at IM+0x10..+0x18,
//  finds matching item+8, calls vtable[0x520/8] to remove]
// ============================================================================

extern "C" void FUN_71015ca990(u32 object_id) {
    if (object_id == INVALID_ITEM_ID) return;
    u64* begin = *reinterpret_cast<u64**>(IM_INSTANCE + 0x10);
    u64* end   = *reinterpret_cast<u64**>(IM_INSTANCE + 0x18);
    for (u64* it = begin; it != end; ++it) {
        u64 item = *it;
        if (*(u32*)(item + 0x8) == object_id) {
            if (item != 0) {
                auto fn = *reinterpret_cast<void(**)(u64, s32)>(*(u64*)item + 0x520);
                fn(item, 0);
            }
            return;
        }
    }
}

// ============================================================================
// get_item_kind
// Address: 0x71015cf3d0 | Size: 140 bytes
// Gets the item kind for a given battle object ID. Returns -1 if not found.
// [derived: Ghidra FUN_71015cf3d0 — iterates active items, checks category
//  nibble at +0xa0 >> 28 == 4 for deep deref, else returns 10]
// ============================================================================

extern "C" s32 FUN_71015cf3d0(u32 object_id) {
    if (object_id == INVALID_ITEM_ID) return -1;
    u64* begin = *reinterpret_cast<u64**>(IM_INSTANCE + 0x28);
    u64* end   = *reinterpret_cast<u64**>(IM_INSTANCE + 0x30);
    for (u64* it = begin; it != end; ++it) {
        u64 item = *it;
        // Check alive and matching ID
        if (*(u8*)(*(u64*)(item + 0x90) + 0x18) != 0) continue;
        if (*(u32*)(item + 0x8) != object_id) continue;
        // Found matching active item
        if ((*(u32*)(item + 0xa0) >> 28) == 4) {
            // Category 4: read item kind from deep deref chain
            // item+0x228 -> +0x220 -> +0xc
            u64 p1 = *(u64*)(item + 0x228);
            u64 p2 = *(u64*)(p1 + 0x220);
            return *(s32*)(p2 + 0xc);
        }
        return 10;
    }
    return -1;
}

// ============================================================================
// is_enable_capture
// Address: 0x710164b0b0 | Size: 96 bytes
// Checks if an item can be captured by testing WorkModule flags.
// Returns 0 if flag 0x20000028 is set, else returns !flag(0x20000029).
// [derived: Ghidra FUN_710164b0b0 — WorkModule::is_flag vtable[0x108/8=33]]
// ============================================================================

extern "C" u32 FUN_710164b0b0(u8* acc) {
    u64* work = *reinterpret_cast<u64**>(acc + 0x50);
    // WorkModule::is_flag at vtable offset 0x108
    u64 flag1 = reinterpret_cast<u64(*)(u64*, u32)>(*reinterpret_cast<void**>(*work + 0x108))(work, 0x20000028);
    u32 result;
    if ((flag1 & 1) == 0) {
#ifdef MATCHING_HACK_NX_CLANG
        asm("" ::: "memory");  // force vtable reload — original doesn't cache fn ptr
#endif
        u32 flag2 = reinterpret_cast<u32(*)(u64*, u32)>(*reinterpret_cast<void**>(*work + 0x108))(work, 0x20000029);
        result = flag2 ^ 1u;
    } else {
        result = 0;
    }
    return result & 1;
}

// ============================================================================
// is_enable_capture_beetle
// Address: 0x7101655fb0 | Size: 96 bytes
// Identical logic to is_enable_capture — beetle variant.
// [derived: Ghidra FUN_7101655fb0 — same WorkModule flag check pattern]
// ============================================================================

extern "C" u32 FUN_7101655fb0(u8* acc) {
    u64* work = *reinterpret_cast<u64**>(acc + 0x50);
    u64 flag1 = reinterpret_cast<u64(*)(u64*, u32)>(*reinterpret_cast<void**>(*work + 0x108))(work, 0x20000028);
    u32 result;
    if ((flag1 & 1) == 0) {
#ifdef MATCHING_HACK_NX_CLANG
        asm("" ::: "memory");
#endif
        u32 flag2 = reinterpret_cast<u32(*)(u64*, u32)>(*reinterpret_cast<void**>(*work + 0x108))(work, 0x20000029);
        result = flag2 ^ 1u;
    } else {
        result = 0;
    }
    return result & 1;
}

// ============================================================================
// can_exist (shiokarazu)
// Address: 0x710164bb20 | Size: 28 bytes
// Returns true if the shiokarazu (splatoon ink) slot is empty.
// [derived: can_exist (community name) — checks ItemManager+0x58->+0x708 == 0]
// ============================================================================

extern "C" bool FUN_710164bb20() {
    u64 sub = *reinterpret_cast<u64*>(IM_INSTANCE + 0x58);
    return *reinterpret_cast<u64*>(sub + 0x708) == 0;
}

// ============================================================================
// can_exist (darz)
// Address: 0x71016523a0 | Size: 28 bytes
// Returns true if the darz (assist trophy) slot is empty.
// [derived: can_exist_71016523a0 (community name) — checks ItemManager+0x58->+0xcd0 == 0]
// ============================================================================

extern "C" bool FUN_71016523a0() {
    u64 sub = *reinterpret_cast<u64*>(IM_INSTANCE + 0x58);
    return *reinterpret_cast<u64*>(sub + 0xcd0) == 0;
}

// ============================================================================
// can_exist (kiila)
// Address: 0x7101652f20 | Size: 28 bytes
// Returns true if the kiila (Killer Eye) slot is empty.
// [derived: can_exist_7101652f20 (community name) — checks ItemManager+0x58->+0xc78 == 0]
// ============================================================================

extern "C" bool FUN_7101652f20() {
    u64 sub = *reinterpret_cast<u64*>(IM_INSTANCE + 0x58);
    return *reinterpret_cast<u64*>(sub + 0xc78) == 0;
}

// ============================================================================
// send_event_on_start_boss_entry
// Address: 0x71015c8450 | Size: 84 bytes
// Finds an active item by object_id and sends boss entry start event.
// [derived: send_event_on_start_boss_entry (community name) — iterates
//  active items at IM+0x28..+0x30, tail-calls FUN_71015b52c0 on match]
// ============================================================================

extern "C" void FUN_71015b52c0(u64 item);  // send boss entry event helper
extern "C" void FUN_71015c8450(u32 object_id) {
    if (object_id == INVALID_ITEM_ID) return;
    u64* begin = *reinterpret_cast<u64**>(IM_INSTANCE + 0x28);
    u64* end   = *reinterpret_cast<u64**>(IM_INSTANCE + 0x30);
    for (u64* it = begin; it != end; ++it) {
        u64 item = *it;
        if (*(u8*)(*(u64*)(item + 0x90) + 0x18) == 0 &&
            *(u32*)(item + 0x8) == object_id) {
            FUN_71015b52c0(item);
            return;
        }
    }
}

// ============================================================================
// stop_ingame_se
// Address: 0x71016538e0 | Size: 24 bytes
// Stops in-game sound effect by setting a flag byte.
// [derived: stop_ingame_se (community name) — loads global ptr, deref, sets byte +1 to 1]
// ============================================================================

extern "C" void FUN_71016538e0() {
    u64 ptr = *reinterpret_cast<u64*>(DAT_7105328f50);
    *reinterpret_cast<u8*>(ptr + 1) = 1;
}

// ============================================================================
// init_bound_frame
// Address: 0x71016593a0 | Size: 20 bytes
// Returns the bound frame count from FighterParamAccessor2.
// [derived: init_bound_frame (community name) — FPA2+0x12d0->+0x230, returns u32]
// ============================================================================

extern "C" u32 FUN_71016593a0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<u32*>(sub + 0x230);
}

// ============================================================================
// special_lw_gravity
// Address: 0x71016593c0 | Size: 20 bytes
// Returns the special low gravity float from FighterParamAccessor2.
// [derived: special_lw_gravity (community name) — FPA2+0x12d0->+0x234, returns float]
// ============================================================================

extern "C" float FUN_71016593c0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x234);
}

// ============================================================================
// buddybomb param getters (batch)
// All use FPA2+0x12d0 deref chain with varying final offsets.
// [derived: community names, FPA2 singleton deref pattern]
// ============================================================================

// length_gravity — Address: 0x7101659400 | Size: 20 bytes | +0x240
extern "C" float FUN_7101659400() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x240);
}

// length_speed_y_max — Address: 0x7101659420 | Size: 20 bytes | +0x244
extern "C" float FUN_7101659420() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x244);
}

// length_angle_x_velocity — Address: 0x7101659440 | Size: 20 bytes | +0x260
extern "C" float FUN_7101659440() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x260);
}

// length_angle_y_velocity — Address: 0x7101659460 | Size: 20 bytes | +0x264
extern "C" float FUN_7101659460() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x264);
}

// length_angle_z_velocity — Address: 0x7101659480 | Size: 20 bytes | +0x268
extern "C" float FUN_7101659480() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x268);
}

// side_gravity — Address: 0x71016594a0 | Size: 20 bytes | +0x26c
extern "C" float FUN_71016594a0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x26c);
}

// side_speed_y_max — Address: 0x71016594c0 | Size: 20 bytes | +0x270
extern "C" float FUN_71016594c0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x270);
}

// side_angle_x_velocity — Address: 0x71016594e0 | Size: 20 bytes | +0x28c
extern "C" float FUN_71016594e0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x28c);
}

// side_angle_y_velocity — Address: 0x7101659500 | Size: 20 bytes | +0x290
extern "C" float FUN_7101659500() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x290);
}

// side_angle_z_velocity — Address: 0x7101659520 | Size: 20 bytes | +0x294
extern "C" float FUN_7101659520() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x294);
}

// flashing_frame_before_life_over — Address: 0x7101659560 | Size: 20 bytes | +0x2a4
extern "C" u32 FUN_7101659560() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<u32*>(sub + 0x2a4);
}

// rebound_speed_x_add — Address: 0x7101659580 | Size: 20 bytes | +0x2a8
extern "C" float FUN_7101659580() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x2a8);
}

// rebound_speed_y_add — Address: 0x71016595a0 | Size: 20 bytes | +0x2ac
extern "C" float FUN_71016595a0() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x12d0);
    return *reinterpret_cast<float*>(sub + 0x2ac);
}

// ============================================================================
// EXPLOSIONBOMB_WIRE_ROT_SPEED — Address: 0x710165d480 | Size: 20 bytes
// [derived: FPA2+0x3f0->+0x120, returns u32]
extern "C" u32 FUN_710165d480() {
    u64 sub = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x3f0);
    return *reinterpret_cast<u32*>(sub + 0x120);
}

// ============================================================================
// DAISY_DAISYDAIKON param getters (batch) — all 24 bytes
// Chain: FPA2+0x380->+0x158->offset, returns float
// [derived: community names from modding scene]
// ============================================================================

#define DAISY_PARAM(name, addr, off) \
extern "C" float FUN_##addr() { \
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0x380); \
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x158); \
    return *reinterpret_cast<float*>(s2 + off); \
}

DAISY_PARAM(PROB_1, 710165be40, 0x40)
DAISY_PARAM(PROB_2, 710165be60, 0x44)
DAISY_PARAM(PROB_3, 710165be80, 0x48)
DAISY_PARAM(PROB_4, 710165bea0, 0x4c)
DAISY_PARAM(PROB_5, 710165bec0, 0x50)
DAISY_PARAM(PROB_6, 710165bee0, 0x54)
DAISY_PARAM(PROB_7, 710165bf00, 0x58)
DAISY_PARAM(PROB_8, 710165bf20, 0x5c)
DAISY_PARAM(POWER_1, 710165bf40, 0x20)
DAISY_PARAM(POWER_2, 710165bf60, 0x24)
DAISY_PARAM(POWER_3, 710165bf80, 0x28)
DAISY_PARAM(POWER_4, 710165bfa0, 0x2c)
DAISY_PARAM(POWER_5, 710165bfc0, 0x30)
DAISY_PARAM(POWER_6, 710165bfe0, 0x34)
DAISY_PARAM(POWER_7, 710165c000, 0x38)
DAISY_PARAM(POWER_8, 710165c020, 0x3c)

#undef DAISY_PARAM

// ============================================================================
// spawn_frame family (batch) — all 24 bytes
// Chain: FPA2+0xf88->+0x1c8->offset, returns u32
// [derived: community names]
// ============================================================================

#define SPAWN_PARAM_U32(name, addr, off) \
extern "C" u32 FUN_##addr() { \
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0xf88); \
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x1c8); \
    return *reinterpret_cast<u32*>(s2 + off); \
}

SPAWN_PARAM_U32(spawn_frame, 710165e800, 0x1c)
SPAWN_PARAM_U32(spawn_frame_add, 710165e820, 0x20)
SPAWN_PARAM_U32(spawn_frame_max, 710165e840, 0x24)
SPAWN_PARAM_U32(spawn_frame_get_krool_only, 710165e860, 0x2c)
SPAWN_PARAM_U32(delete_frame, 710165e880, 0x34)
SPAWN_PARAM_U32(delete_flash_frame, 710165e8a0, 0x38)

#undef SPAWN_PARAM_U32

// ============================================================================
// LOG param family (batch) — all 24 bytes
// Chain: FPA2+0xc08->+0x178->offset
// [derived: community names]
// ============================================================================

extern "C" u32 FUN_710165f120() {  // LOG_LIFE — returns u32
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0xc08);
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x178);
    return *reinterpret_cast<u32*>(s2 + 0x34);
}

extern "C" float FUN_710165f140() {  // LOG_REACTION_MUL — returns float
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0xc08);
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x178);
    return *reinterpret_cast<float*>(s2 + 0xc);
}

extern "C" float FUN_710165f160() {  // LOG_LIFE_DEC_MUL — returns float
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0xc08);
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x178);
    return *reinterpret_cast<float*>(s2 + 0x38);
}

extern "C" float FUN_710165f180() {  // LOG_SMASH_ACCEL_Y — returns float
    u64 s1 = *reinterpret_cast<u64*>(FPA2_INSTANCE + 0xc08);
    u64 s2 = *reinterpret_cast<u64*>(s1 + 0x178);
    return *reinterpret_cast<float*>(s2 + 0x20);
}

// ============================================================================
// adjust_model_constraint_posture (variant 2)
// Address: 0x7101655110 | Size: 24 bytes
// Same pattern as first variant — different item type.
// [derived: identical vtable tail call at accessor+0xd0, vtable[0x3b0/8]]
// ============================================================================

extern "C" void FUN_7101655110(u8* acc) {
    u64* mod = *reinterpret_cast<u64**>(acc + 0xd0);
    auto fn = reinterpret_cast<void(*)(u64*, u64, u64)>(
        *reinterpret_cast<void**>(*mod + 0x3b0));
    fn(mod, 0, 0);
}

// ============================================================================
// adjust_model_constraint_posture
// Address: 0x7101654bf0 | Size: 24 bytes
// Adjusts model constraint posture via vtable tail call.
// [derived: adjust_model_constraint_posture (community name) — loads module at
//  accessor+0xd0, vtable[0x3b0/8], tail-calls with (module, 0, 0)]
// ============================================================================

extern "C" void FUN_7101654bf0(u8* acc) {
    u64* mod = *reinterpret_cast<u64**>(acc + 0xd0);
    auto fn = reinterpret_cast<void(*)(u64*, u64, u64)>(
        *reinterpret_cast<void**>(*mod + 0x3b0));
    fn(mod, 0, 0);
}

#undef HIDDEN2
#undef FM_INSTANCE
#undef IM_INSTANCE
#undef FPA2_INSTANCE
#undef INVALID_ITEM_ID

