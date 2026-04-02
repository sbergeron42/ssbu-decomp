#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// Batch decompiled — pool-c, batch 018
// Range: 0x7102000000 — 0x7102FFFFFF
// Vtable dispatch thunks (16B/20B)

#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// 0x0000007102029910 Ground vt+0x88 (bool)
u64 GroundModule__v0x88(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x88/8])(m,p1); }
// 0x00000071020299d0 Ground vt+0x140 (u64)
u64 GroundModule__v0x140(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// 0x0000007102029a30 Ground vt+0x190 (bool)
u64 GroundModule__v0x190(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x190/8])(m,p1); }
// 0x0000007102029b50 Ground vt+0x228 (u64)
u64 GroundModule__v0x228(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x228/8])(m,p1); }
// 0x0000007102029c90 Ground vt+0x2d0 (bool)
u64 GroundModule__v0x2d0(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x2d0/8])(m,p1); }
// 0x0000007102029cb0 Ground vt+0x2d8 (bool)
u64 GroundModule__v0x2d8(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x2d8/8])(m,p1); }
// 0x0000007102029d70 Ground vt+0x348 (u64)
u64 GroundModule__v0x348(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x348/8])(m,p1); }
// 0x0000007102029db0 Ground vt+0x368 (u64)
u64 GroundModule__v0x368(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x368/8])(m,p1); }
// 0x0000007102029eb0 Ground vt+0x410 (u64)
u64 GroundModule__v0x410(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x410/8])(m,p1); }
// 0x0000007102029ec0 Ground vt+0x418 (u64)
u64 GroundModule__v0x418(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x418/8])(m,p1); }
// 0x0000007102029ee0 Ground vt+0x430 (u64)
u64 GroundModule__v0x430(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x430/8])(m,p1); }
// 0x0000007102029ef0 Ground vt+0x438 (u64)
u64 GroundModule__v0x438(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x438/8])(m,p1); }
// 0x000000710202a380 Ground vt+0x6e0 (bool)
u64 GroundModule__v0x6e0(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x6e0/8])(m,p1); }
// 0x000000710202a3d0 Ground vt+0x750 (bool)
u64 GroundModule__v0x750(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x750/8])(m,p1); }
// 0x000000710202a420 Ground vt+0x7a8 (bool)
u64 GroundModule__v0x7a8b(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x58); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x7a8/8])(m,p1); }
// 0x00000071020439b0 Kinetic vt+0xa0 (u64)
u64 KineticModule__v0xa0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0xa0/8])(m,p1); }
// 0x0000007102043a40 Kinetic vt+0xe8 (u64)
u64 KineticModule__v0xe8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
// 0x0000007102043ad0 Kinetic vt+0x128 (u64)
u64 KineticModule__v0x128(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
// 0x0000007102043ae0 Kinetic vt+0x130 (u64)
u64 KineticModule__v0x130(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
// 0x0000007102043b00 Kinetic vt+0x140 (u64)
u64 KineticModule__v0x140(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// 0x0000007102043b10 Kinetic vt+0x148 (u64)
u64 KineticModule__v0x148(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
// 0x0000007102043b20 Kinetic vt+0x150 (u64)
u64 KineticModule__v0x150(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
// 0x0000007102043b50 Kinetic vt+0x168 (bool)
u64 KineticModule__v0x168(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x68); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x168/8])(m,p1); }
// 0x0000007102048030 Link vt+0x58 (u64)
u64 LinkModule__v0x58(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
// 0x0000007102048050 Link vt+0x68 (u64)
u64 LinkModule__v0x68(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
// 0x0000007102048060 Link vt+0x70 (u64)
u64 LinkModule__v0x70(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
// 0x0000007102048070 Link vt+0x78 (u64)
u64 LinkModule__v0x78(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x78/8])(m,p1); }
// 0x00000071020480a0 Link vt+0x88 (u64)
u64 LinkModule__v0x88(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
// 0x00000071020480b0 Link vt+0x90 (u64)
u64 LinkModule__v0x90(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
// 0x00000071020480c0 Link vt+0x98 (u64)
u64 LinkModule__v0x98(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
// 0x0000007102048140 Link vt+0xd8 (u64)
u64 LinkModule__v0xd8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
// 0x0000007102048150 Link vt+0xe0 (u64)
u64 LinkModule__v0xe0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
// 0x00000071020481d0 Link vt+0x148 (u64)
u64 LinkModule__v0x148(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
// 0x0000007102048220 Link vt+0x178 (u64)
u64 LinkModule__v0x178(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x178/8])(m,p1); }
// 0x0000007102048230 Link vt+0x180 (u64)
u64 LinkModule__v0x180(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x180/8])(m,p1); }
// 0x0000007102048240 Link vt+0x188 (u64)
u64 LinkModule__v0x188(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x188/8])(m,p1); }
// 0x0000007102048250 Link vt+0x190 (u64)
u64 LinkModule__v0x190(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
// 0x0000007102048260 Link vt+0x198 (u64)
u64 LinkModule__v0x198(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x198/8])(m,p1); }
// 0x0000007102048270 Link vt+0x1a0 (u64)
u64 LinkModule__v0x1a0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
// 0x0000007102048280 Link vt+0x1a8 (u64)
u64 LinkModule__v0x1a8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1a8/8])(m,p1); }
// 0x00000071020482a0 Link vt+0x1b8 (u64)
u64 LinkModule__v0x1b8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1b8/8])(m,p1); }
// 0x00000071020482b0 Link vt+0x1c0 (u64)
u64 LinkModule__v0x1c0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1c0/8])(m,p1); }
// 0x0000007102048300 Link vt+0x1d8 (u64)
u64 LinkModule__v0x1d8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1d8/8])(m,p1); }
// 0x0000007102048310 Link vt+0x1e0 (u64)
u64 LinkModule__v0x1e0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1e0/8])(m,p1); }
// 0x0000007102048320 Link vt+0x1e8 (u64)
u64 LinkModule__v0x1e8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1e8/8])(m,p1); }
// 0x0000007102048330 Link vt+0x1f0 (u64)
u64 LinkModule__v0x1f0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
// 0x0000007102048340 Link vt+0x1f8 (u64)
u64 LinkModule__v0x1f8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1f8/8])(m,p1); }
// 0x0000007102048360 Link vt+0x208 (bool)
u64 LinkModule__v0x208(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x208/8])(m,p1); }
// 0x0000007102048380 Link vt+0x210 (u64)
u64 LinkModule__v0x210(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
// 0x0000007102048390 Link vt+0x218 (u64)
u64 LinkModule__v0x218(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
// 0x00000071020483a0 Link vt+0x220 (u64)
u64 LinkModule__v0x220(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x220/8])(m,p1); }
// 0x00000071020483c0 Link vt+0x230 (u64)
u64 LinkModule__v0x230(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x230/8])(m,p1); }
// 0x00000071020483e0 Link vt+0x270 (u64)
u64 LinkModule__v0x270(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x270/8])(m,p1); }
// 0x00000071020484d0 Link vt+0x310 (u64)
u64 LinkModule__v0x310(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x310/8])(m,p1); }
// 0x00000071020484e0 Link vt+0x318 (u64)
u64 LinkModule__v0x318(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x318/8])(m,p1); }
// 0x00000071020484f0 Link vt+0x320 (u64)
u64 LinkModule__v0x320(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x320/8])(m,p1); }
// 0x0000007102048520 Link vt+0x338 (u64)
u64 LinkModule__v0x338(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x338/8])(m,p1); }
// 0x0000007102048550 Link vt+0x348 (u64)
u64 LinkModule__v0x348(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x348/8])(m,p1); }
// 0x00000071020485c0 Link vt+0x370 (u64)
u64 LinkModule__v0x370(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x370/8])(m,p1); }
// 0x00000071020485d0 Link vt+0x378 (u64)
u64 LinkModule__v0x378(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x378/8])(m,p1); }
// 0x0000007102048600 Link vt+0x390 (u64)
u64 LinkModule__v0x390(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x390/8])(m,p1); }
// 0x0000007102048610 Link vt+0x398 (u64)
u64 LinkModule__v0x398(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x398/8])(m,p1); }
// 0x0000007102048620 Link vt+0x3a0 (u64)
u64 LinkModule__v0x3a0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x3a0/8])(m,p1); }
// 0x0000007102048650 Link vt+0x3c0 (bool)
u64 LinkModule__v0x3c0(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x3c0/8])(m,p1); }
// 0x0000007102048750 Link vt+0x460 (u64)
u64 LinkModule__v0x460(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x460/8])(m,p1); }
// 0x0000007102048760 Link vt+0x480 (u64)
u64 LinkModule__v0x480(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x480/8])(m,p1); }
// 0x0000007102048770 Link vt+0x488 (u64)
u64 LinkModule__v0x488(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x488/8])(m,p1); }
// 0x0000007102048780 Link vt+0x4a0 (u64)
u64 LinkModule__v0x4a0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x4a0/8])(m,p1); }
// 0x00000071020487a0 Link vt+0x4c0 (u64)
u64 LinkModule__v0x4c0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x4c0/8])(m,p1); }
// 0x00000071020487b0 Link vt+0x4c8 (u64)
u64 LinkModule__v0x4c8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x4c8/8])(m,p1); }
// 0x00000071020487f0 Link vt+0x4e8 (u64)
u64 LinkModule__v0x4e8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x4e8/8])(m,p1); }
// 0x0000007102048800 Link vt+0x4f0 (u64)
u64 LinkModule__v0x4f0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0xd0); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x4f0/8])(m,p1); }
// 0x0000007102080520 Slow vt+0xa8
u64 SlowModule__rate_impl2(BattleObjectModuleAccessor* a) { auto* m=*(void**)((u8*)a+0x170); return reinterpret_cast<u64(*)(void*)>(VT(m)[0xa8/8])(m); }
// 0x000000710208dcf0 Work vt+0x148 (u64)
u64 WorkModule__enable_transition_term_group_impl_2(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x50); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
// 0x000000710208dda0 Work vt+0x1a0 (u64)
u64 WorkModule__v0x1a0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x50); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
// 0x000000710208ddc0 Work vt+0x1b0 (u64)
u64 WorkModule__v0x1b0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x50); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
// 0x000000710208dde0 Work vt+0x1c0 (u64)
u64 WorkModule__v0x1c0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x50); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1c0/8])(m,p1); }
// 0x000000710208de10 Work vt+0x200 (u64)
u64 WorkModule__v0x200(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x50); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
// 0x000000710209f8c0 Physics vt+0xa8 (bool)
u64 PhysicsModule__v0xa8(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
// 0x000000710209f900 Physics vt+0xc8 (bool)
u64 PhysicsModule__v0xc8(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0xc8/8])(m,p1); }
// 0x000000710209f930 Physics vt+0xf8 (bool)
u64 PhysicsModule__v0xf8(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0xf8/8])(m,p1); }
// 0x000000710209f960 Physics vt+0x110 (u64)
u64 PhysicsModule__v0x110(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
// 0x000000710209fa00 Physics vt+0x180 (bool)
u64 PhysicsModule__v0x180(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x180/8])(m,p1); }
// 0x000000710209fa30 Physics vt+0x198 (bool)
u64 PhysicsModule__v0x198(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
// 0x000000710209fa60 Physics vt+0x1d0 (u64)
u64 PhysicsModule__v0x1d0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1d0/8])(m,p1); }
// 0x000000710209fa90 Physics vt+0x1f0 (u64)
u64 PhysicsModule__v0x1f0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
// 0x000000710209fac0 Physics vt+0x218 (u64)
u64 PhysicsModule__v0x218(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
// 0x000000710209fb10 Physics vt+0x258 (u64)
u64 PhysicsModule__v0x258(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x258/8])(m,p1); }
// 0x000000710209fb20 Physics vt+0x268 (u64)
u64 PhysicsModule__v0x268(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
// 0x000000710209fba0 Physics vt+0x2a0 (u64)
u64 PhysicsModule__v0x2a0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x2a0/8])(m,p1); }
// 0x000000710209fbf0 Physics vt+0x2e0 (u64)
u64 PhysicsModule__v0x2e0(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x2e0/8])(m,p1); }
// 0x000000710209fc10 Physics vt+0x2f0 (bool)
u64 PhysicsModule__v0x2f0(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x2f0/8])(m,p1); }
// 0x000000710209fc30 Physics vt+0x300 (bool)
u64 PhysicsModule__v0x300(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x300/8])(m,p1); }
// 0x000000710209fc70 Physics vt+0x318 (u64)
u64 PhysicsModule__v0x318(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x318/8])(m,p1); }
// 0x000000710209fc80 Physics vt+0x320 (u64)
u64 PhysicsModule__v0x320(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x320/8])(m,p1); }
// 0x000000710209fcb0 Physics vt+0x358 (u64)
u64 PhysicsModule__v0x358(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x358/8])(m,p1); }
// 0x000000710209fcc0 Physics vt+0x3a8 (u64)
u64 PhysicsModule__v0x3a8(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x3a8/8])(m,p1); }
// 0x000000710209fcd0 Physics vt+0x3b8 (bool)
u64 PhysicsModule__v0x3b8(BattleObjectModuleAccessor* a, bool p1) { auto* m=*(void**)((u8*)a+0x80); return reinterpret_cast<u64(*)(void*,bool)>(VT(m)[0x3b8/8])(m,p1); }
// 0x00000071020aec60 Control vt+0x450 (u64,u64)
u64 FighterControlModuleImpl__delete_reserve_turn_lr_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { auto* m=*(void**)((u8*)a+0x48); return reinterpret_cast<u64(*)(void*,u64,u64)>(VT(m)[0x450/8])(m,p1,p2); }
// 0x00000071020aec90 Control vt+0x470 (u64)
u64 FighterControlModuleImpl__get_special_command_lr_impl(BattleObjectModuleAccessor* a, u64 p1) { auto* m=*(void**)((u8*)a+0x48); return reinterpret_cast<u64(*)(void*,u64)>(VT(m)[0x470/8])(m,p1); }

} // namespace app::lua_bind
