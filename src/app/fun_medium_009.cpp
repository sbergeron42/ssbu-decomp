#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 10
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" s32  memcmp(const void*, const void*, u64);
extern "C" [[noreturn]] void abort();

// nn forward declarations
namespace nn {
namespace detail {
    [[noreturn]] void UnexpectedDefaultImpl(const char*, const char*, int);
}
namespace util {
    void ReferSymbol(const char*);
}
}

// External C functions -- forward declarations
extern "C" void  FUN_71001aff70(s64, const char*, ...);
extern "C" u64   FUN_71002ba540(u8*, u32);
extern "C" char* FUN_71002c1790(s64, u32);
extern "C" u64   FUN_71000c74a0();
extern "C" s64   FUN_7100161fb0(u64);
extern "C" void  FUN_71001602c0(s64);
extern "C" s64   FUN_71000b30b0();
extern "C" void  FUN_71000b3860();
extern "C" void  FUN_71000b3150(u64, s32);
extern "C" u64   FUN_71000bb680();
extern "C" s64   FUN_71001f2ba0(u64, const char*, s32);
extern "C" void  FUN_710020f2b0();
extern "C" [[noreturn]] void FUN_71039c0d80(u64);

// External data
extern u8   DAT_710427eedd;
extern u8   DAT_710439b8ee;  // used by FUN_7100255af0 ("%u,%u" at different offset)
extern u8   DAT_710449be79;
extern u64  PTR_DAT_71052a3dc8;
extern u64  PTR_DAT_71052a5800;
extern u8   DAT_71044929c4[];
extern void* PTR_s_Too_long_hexadecimal_number_7104f16260[];
extern u8   DAT_710437a4bc;

// ---- Functions -----------------------------------------------------------

// 7100255940 -- FUN_71001aff70 with "%u,%u" on sub-object at +0x50
void FUN_7100255940(s64 param_1, u16 param_2, u16 param_3)
{
    FUN_71001aff70(param_1 + 0x50, "%u,%u", (u32)param_2, (u32)param_3);
}

// 7100255960 -- FUN_71001aff70 with &DAT on sub-object at +0x78
void FUN_7100255960(s64 param_1, u16 param_2)
{
    FUN_71001aff70(param_1 + 0x78, (const char*)&DAT_710427eedd, (u32)param_2);
}

// 7100255980 -- FUN_71001aff70 with "%u,%u" on sub-object at +0x78
void FUN_7100255980(s64 param_1, u16 param_2, u16 param_3)
{
    FUN_71001aff70(param_1 + 0x78, "%u,%u", (u32)param_2, (u32)param_3);
}

// 71002559a0 -- FUN_71001aff70 at computed array offset (element size 0x28)
void FUN_71002559a0(s64 param_1, u32 param_2)
{
    FUN_71001aff70(*(s64*)(param_1 + 0x10) + (u64)param_2 * 0x28,
                   (const char*)&DAT_710427eedd);
}

// 7100255af0 -- FUN_71001aff70 at computed offset, "%u,%u" format
void FUN_7100255af0(s64 param_1, u32 param_2)
{
    FUN_71001aff70(*(s64*)(param_1 + 0x10) + (u64)param_2 * 0x28, "%u,%u");
}

// 71002b41d0 -- tail-call passthrough: *param_1 → FUN_71002ba540
void FUN_71002b41d0(u64* param_1, u32 param_2)
{
    FUN_71002ba540((u8*)*param_1, param_2);
}

// 71002b4b10 -- tail-call passthrough: *param_1 → FUN_71002c1790
void FUN_71002b4b10(u64* param_1, u32 param_2)
{
    FUN_71002c1790((s64)*param_1, param_2);
}

// 71000c4cd0 -- return field@+0x90 or field from FUN_71000c74a0+0x28
u64 FUN_71000c4cd0(s64 param_1)
{
    u64 uVar1 = *(u64*)(param_1 + 0x90);
    if (uVar1 != 0) {
        s64 lVar2 = FUN_71000c74a0();
        uVar1 = (u64)*(u32*)(lVar2 + 0x28);
    }
    return uVar1;
}

// 71000c5368 -- vtable dispatch: call vt[0x70/8](this)
void FUN_71000c5368(s64* param_1)
{
    (*(void(**)(s64*))(*(s64*)param_1 + 0x70))(param_1);
}

// 710022e4b8 -- double-deref vtable at +0x28, call(inner, param_1), return 1
u64 FUN_710022e4b8(s64 param_1)
{
    s64* inner = *(s64**)(param_1 + 0x58);
    (*(void(**)(s64*, s64))(*(s64*)inner + 0x28))(inner, param_1);
    return 1;
}

// 710022e4e8 -- double-deref vtable at +0x30, call(inner, param_1), return 1
u64 FUN_710022e4e8(s64 param_1)
{
    s64* inner = *(s64**)(param_1 + 0x58);
    (*(void(**)(s64*, s64))(*(s64*)inner + 0x30))(inner, param_1);
    return 1;
}

// 71003cb460 -- double-deref vtable at +0x198, return u8
u8 FUN_71003cb460(s64 param_1)
{
    s64* inner = *(s64**)(param_1 + 0x48);
    return (*(u8(**)(s64*))(*(s64*)inner + 0x198))(inner);
}

// 71002b3fe8 -- unconditional UnexpectedDefaultImpl
[[noreturn]] void FUN_71002b3fe8()
{
    nn::detail::UnexpectedDefaultImpl("", "", 0);
}

// 710065f87c
[[noreturn]] void FUN_710065f87c()
{
    abort();
}

// 710065f96c
[[noreturn]] void FUN_710065f96c()
{
    abort();
}

// 7100798104 -- forward x0 to FUN_71039c0d80
[[noreturn]] void FUN_7100798104(u64 param_1)
{
    FUN_71039c0d80(param_1);
}

// 7100012dc0 -- string table lookup by 1-indexed category (1..6)
void* FUN_7100012dc0(s32 param_1)
{
    if ((u32)(param_1 - 1) < 6)
        return PTR_s_Too_long_hexadecimal_number_7104f16260[(s32)(param_1 - 1)];
    return (void*)&DAT_710437a4bc;
}

// 71002c2b50 -- address calculation: base + idx*0x24 + 0x14c24
s64 FUN_71002c2b50(s64 param_1, u32 param_2)
{
    return *(s64*)(param_1 + 0x18) + (u64)param_2 * 0x24 + 0x14c24;
}

// ---- Large switch tables (fighter animation ID lookups) -------------------

// 7100b30fd0 -- return 1 if param_1 is one of ~50 known IDs, else 0
u64 FUN_7100b30fd0(u32 param_1)
{
    switch (param_1) {
    case 0x41: case 200: case 0xcb: case 0xe6: case 0xed: case 0xf3: case 0xf5:
    case 0xff: case 0x109: case 0x10a: case 0x10b: case 0x10c: case 0x10d:
    case 0x10e: case 0x110: case 0x124: case 0x128: case 300: case 0x137:
    case 0x13a: case 0x13d: case 0x140: case 0x143: case 0x14d: case 0x151:
    case 0x157: case 0x15a: case 0x15d: case 0x160: case 0x163: case 0x166:
    case 0x169: case 0x16c: case 0x16f: case 0x171: case 0x176: case 0x17f:
    case 0x182: case 0x185: case 0x186: case 0x18a: case 0x18b: case 0x193:
    case 0x19d: case 0x1a0: case 0x1ab: case 0x1b0: case 0x1b5: case 0x1b8:
    case 0x1be: case 0x1bf: case 0x1c1: case 0x1c4: case 0x1cb: case 0x1ce:
    case 0x1d2:
        return 1;
    default:
        return 0;
    }
}

// 7100b31000 -- return 1 if param_1 is one of ~40 known IDs, else 0
u64 FUN_7100b31000(u32 param_1)
{
    switch (param_1) {
    case 0x46: case 199: case 0xef: case 0x118: case 0x123: case 0x127:
    case 0x12a: case 0x12d: case 0x13c: case 0x13f: case 0x142: case 0x145:
    case 0x14f: case 0x155: case 0x159: case 0x15c: case 0x15f: case 0x162:
    case 0x165: case 0x168: case 0x16b: case 0x16e: case 0x172: case 0x17a:
    case 0x17b: case 0x180: case 0x188: case 0x191: case 0x195: case 0x19f:
    case 0x1a2: case 0x1ad: case 0x1b2: case 0x1b7: case 0x1ba: case 0x1c3:
    case 0x1c6: case 0x1cd: case 0x1d0: case 0x1d5:
        return 1;
    default:
        return 0;
    }
}

// 7100b31030 -- return 1 if param_1 is one of ~60 known IDs, else 0
u64 FUN_7100b31030(u32 param_1)
{
    switch (param_1) {
    case 0x42: case 0x43: case 0xc0: case 0xc1: case 0xc5: case 0xc6: case 0xc9:
    case 0xe9: case 0xea: case 0xeb: case 0xec: case 0xee: case 0xf1: case 0xf4:
    case 0xf6: case 0xf7: case 0x11f: case 0x121: case 0x122: case 0x125:
    case 0x126: case 0x129: case 0x131: case 0x132: case 0x138: case 0x139:
    case 0x13b: case 0x13e: case 0x141: case 0x144: case 0x14e: case 0x152:
    case 0x154: case 0x158: case 0x15b: case 0x15e: case 0x161: case 0x164:
    case 0x167: case 0x16a: case 0x16d: case 0x174: case 0x177: case 0x178:
    case 0x179: case 0x187: case 0x18c: case 400: case 0x194: case 0x19e:
    case 0x1a1: case 0x1ac: case 0x1b1: case 0x1b6: case 0x1b9: case 0x1c2:
    case 0x1c5: case 0x1cc: case 0x1cf: case 0x1d4:
        return 1;
    default:
        return 0;
    }
}

// ---- Vtable + local buffer patterns --------------------------------------

// 7100c2cd80 -- stack-alloc 72-byte buffer, zero, vtable call at +0x50, return 1
u64 FUN_7100c2cd80(s64* param_1)
{
    u32 local_58[18];
    local_58[0] = 0;
    (*(void(**)(s64*, u32*))(*(s64*)param_1 + 0x50))(param_1, local_58);
    return 1;
}

// 7100dc1450 -- same as 7100c2cd80 but returns 0
u64 FUN_7100dc1450(s64* param_1)
{
    u32 local_58[18];
    local_58[0] = 0;
    (*(void(**)(s64*, u32*))(*(s64*)param_1 + 0x50))(param_1, local_58);
    return 0;
}

// ---- Misc helpers --------------------------------------------------------

// 7100127500 -- call FUN_7100161fb0 with stored ptr, then init at +8
void FUN_7100127500()
{
    s64 lVar1 = FUN_7100161fb0(*(u64*)PTR_DAT_71052a3dc8);
    FUN_71001602c0(lVar1 + 8);
}

// 7100127530 -- call FUN_7100161fb0 with stored ptr, return ptr+8
s64 FUN_7100127530()
{
    s64 lVar1 = FUN_7100161fb0(*(u64*)PTR_DAT_71052a3dc8);
    return lVar1 + 8;
}

// 7100193710 -- conditional: if FUN_71000b30b0 non-null, call b30b0 + b3860
void FUN_7100193710()
{
    s64 lVar1 = FUN_71000b30b0();
    if (lVar1 != 0) {
        FUN_71000b30b0();
        FUN_71000b3860();
    }
}

// 7100193390 -- conditional: if flag clear and FUN_71000b30b0 non-null, call b3150
void FUN_7100193390(s64 param_1)
{
    s64 lVar1;
    if (*(s8*)(param_1 + 0x128) == 0 && (lVar1 = FUN_71000b30b0(), lVar1 != 0)) {
        u64 uVar2 = FUN_71000b30b0();
        FUN_71000b3150(uVar2, 0);
    }
}

// 71001ae0a0 -- store tick_freq * 500 to global
void FUN_71001ae0a0()
{
    s64* plVar1 = (s64*)FUN_71000bb680();
    *(s64*)PTR_DAT_71052a5800 = *plVar1 * 500;
}

// 71001e7a10 -- bool: FUN_71001f2ba0("probeinit") returns non-null
bool FUN_71001e7a10(u64 param_1)
{
    s64 lVar1 = FUN_71001f2ba0(param_1, "probeinit", 0);
    return lVar1 != 0;
}

// 71001e88e0 -- bool: FUN_71001f2ba0(&DAT) returns non-null
bool FUN_71001e88e0(u64 param_1)
{
    s64 lVar1 = FUN_71001f2ba0(param_1, (const char*)&DAT_710449be79, 0);
    return lVar1 != 0;
}

// 710020f860 -- calls FUN_710020f2b0, returns 1
u64 FUN_710020f860()
{
    FUN_710020f2b0();
    return 1;
}

// 71000b1f20 -- compare 16 bytes at param_1+8 against constant, return non-zero
bool FUN_71000b1f20(s64 param_1)
{
    s32 iVar1 = memcmp((void*)(param_1 + 8), &DAT_71044929c4, 0x10);
    return iVar1 != 0;
}

// 71000b2820 -- compare 16 bytes at param_1+8 vs param_2+8, return equal
bool FUN_71000b2820(s64 param_1, s64 param_2)
{
    s32 iVar1 = memcmp((void*)(param_1 + 8), (void*)(param_2 + 8), 0x10);
    return iVar1 == 0;
}
