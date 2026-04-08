#include "types.h"

// EASY-tier FUN_* functions -- address range 0x7100xxxxxx
// Pool-b worker: manually decompiled from Ghidra

// External globals
extern u64  DAT_71052a90d8[2] __attribute__((visibility("hidden")));
extern u32  DAT_710446f378[] __attribute__((visibility("hidden")));
extern u32  DAT_7104470000[] __attribute__((visibility("hidden")));
extern u32  DAT_710446f3a0[] __attribute__((visibility("hidden")));
extern u32  DAT_710446f3b4[] __attribute__((visibility("hidden")));
extern u32  DAT_710446f400[] __attribute__((visibility("hidden")));
extern u32  DAT_710446f528[] __attribute__((visibility("hidden")));
extern u32  DAT_7104470580[] __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a22f8 __attribute__((visibility("hidden")));
extern u64  PTR_glslcCompilePreSpecialized_71052a32e8 __attribute__((visibility("hidden")));
extern u64  PTR_glslcCompileSpecialized_71052a32f0 __attribute__((visibility("hidden")));
extern u64  PTR_glslcInitialize_71052a32f8 __attribute__((visibility("hidden")));
extern u64  PTR_glslcFinalize_71052a3300 __attribute__((visibility("hidden")));
extern u64  PTR_glslcCompile_71052a3308 __attribute__((visibility("hidden")));
extern u64  PTR_glslcGetVersion_71052a3310 __attribute__((visibility("hidden")));
extern u64  PTR_glslcSetAllocator_71052a3318 __attribute__((visibility("hidden")));
extern u64  PTR_glslcGetDefaultOptions_71052a3320 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3578 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a36e8 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3910 __attribute__((visibility("hidden")));
extern u8   PTR_DAT_71052a3a68[] __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3c38 __attribute__((visibility("hidden")));
extern u8   DAT_71052aa9a0 __attribute__((visibility("hidden")));
extern u8   DAT_71052aa9a2 __attribute__((visibility("hidden")));
extern u64  DAT_7104f49398 __attribute__((visibility("hidden")));
extern u64  DAT_7104f49438 __attribute__((visibility("hidden")));
extern u8   DAT_71052abd8c __attribute__((visibility("hidden")));
extern u8   DAT_71052abd8d __attribute__((visibility("hidden")));
extern u8   PTR_DAT_71052a3d48[] __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3e28 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a4810 __attribute__((visibility("hidden")));
extern u8   DAT_71052abfc8 __attribute__((visibility("hidden")));
extern u8   DAT_71052abfc9 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a4820 __attribute__((visibility("hidden")));
extern u8   DAT_71052acb31 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a4bc0 __attribute__((visibility("hidden")));
extern s64  PTR_DAT_71052a4080 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a4ee0 __attribute__((visibility("hidden")));
extern u8   DAT_71052acb48 __attribute__((visibility("hidden")));
extern u8   DAT_71052acb49 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a4f80 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5060 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5088 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5270 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5388 __attribute__((visibility("hidden")));
extern u8   DAT_71052acd88 __attribute__((visibility("hidden")));
extern u8   DAT_71052acd89 __attribute__((visibility("hidden")));
extern u8   DAT_71052acfd3 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5970 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5c68 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a5fb8 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a6418 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a6838 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a6a18 __attribute__((visibility("hidden")));
extern u32  DAT_71052b4448 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2248 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2338 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2340 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2358 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2530 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2538 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2558 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2728 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2868 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2910 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2a98 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a2c80 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3630 __attribute__((visibility("hidden")));
extern u64  PTR_DAT_71052a3640 __attribute__((visibility("hidden")));

// External functions
extern "C" s64 FUN_7100017750(u64, u64, s64, u64);
extern "C" s64 FUN_7100045fe0(s64, s64);
extern "C" u64 FUN_7100045fd0(u64, u32);
extern "C" u64 FUN_7100070140(u32, void*);
extern "C" void FUN_7100031070(void*);
extern "C" void FUN_71000310a0(void*);
extern "C" u64 FUN_7100031720(u64, void*);
extern "C" u64 FUN_71000338d0(u64, void*);
extern "C" s64 FUN_71000338e0(u64, void*);
extern "C" void FUN_7100033920(void*, u64, void*);
extern "C" void FUN_7100031880(void*, u64, void*, void*, s64, u64);
extern "C" void FUN_7100005640(u64);
extern "C" void FUN_71000281d0(u64, u32, u64, u32);
extern "C" void FUN_710002a2f0(u64, u64, u32);
extern "C" void FUN_710002a6d0(u64, u64, u32);
extern "C" void FUN_7100045080(u64, u64, u64, u32);
extern "C" void FUN_7100044720(u64, u64, f32, f32);
extern "C" void FUN_7100047800(u64, u64, u16);

// Forward declarations (defined later in address order, called earlier)
u64 FUN_7100018910(u64, s32*, s32);
u32 FUN_710001ef40(u64, s32*, s32);
u32 FUN_710001ef60(u64, s32*, s32);
u32 FUN_7100026380(u64, s32*, s32);

// -- FUN_7100000220 ----------------------------------------------------------
// 7100000220
void FUN_7100000220(u64 param_1, u64 param_2)
{
    DAT_71052a90d8[0] = param_1;
    DAT_71052a90d8[1] = param_2;
}

// -- FUN_71000067e0 ----------------------------------------------------------
// 71000067e0
void FUN_71000067e0(u64 *param_1, u64 param_2)
{
    param_1[2] = param_2;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// -- FUN_710000bbe0 ----------------------------------------------------------
// 710000bbe0
s64 FUN_710000bbe0(s64 param_1)
{
    if (param_1 != 0) {
        param_1 = *(s64 *)(param_1 + 0x158);
    }
    return param_1;
}

// -- FUN_710000bbf0 ----------------------------------------------------------
// 710000bbf0
s64 FUN_710000bbf0(s64 param_1)
{
    if (param_1 != 0) {
        param_1 = *(s64 *)(param_1 + 0x160);
    }
    return param_1;
}

// -- FUN_710000bc00 ----------------------------------------------------------
// 710000bc00
s64 FUN_710000bc00(s64 param_1)
{
    if (param_1 != 0) {
        param_1 = *(s64 *)(param_1 + 0x170);
    }
    return param_1;
}

// -- FUN_710000bc10 ----------------------------------------------------------
// 710000bc10
s64 FUN_710000bc10(s64 param_1)
{
    if (param_1 != 0) {
        param_1 = *(s64 *)(param_1 + 0x178);
    }
    return param_1;
}

// -- FUN_7100012920 ----------------------------------------------------------
// 7100012920
void FUN_7100012920(s64 param_1)
{
    *(u64 *)(param_1 + 0x34) = 0;
    *(u64 *)(param_1 + 0x48) = 0;
}

// -- FUN_71000145e0 ----------------------------------------------------------
// 71000145e0
u32 FUN_71000145e0(s64 param_1, s64 param_2)
{
    if (*(u8 *)(param_2 + 0x82d) != 0) {
        return 1;
    }
    if (*(u8 *)(param_2 + 0x8c9) != 0) {
        return 0;
    }
    s64 ptr = *(s64 *)(param_2 + 0x8d0);
    if (ptr == 0) {
        return 0;
    }
    if (*(s64 *)ptr != param_1) {
        return 0;
    }
    *(u8 *)(param_2 + 0x8c9) = 1;
    return 1;
}

// -- FUN_7100014630 ----------------------------------------------------------
// 7100014630
u32 FUN_7100014630(s64 param_1, s64 param_2)
{
    if (*(u8 *)(param_2 + 0x82d) != 0) {
        return 1;
    }
    if (*(u8 *)(param_2 + 0x8c8) != 0) {
        return 0;
    }
    s64 ptr = *(s64 *)(param_2 + 0x8f0);
    if (ptr == 0) {
        return 0;
    }
    if (*(s64 *)ptr != param_1) {
        return 0;
    }
    *(u8 *)(param_2 + 0x8c8) = 1;
    return 1;
}

// -- FUN_7100015160 ----------------------------------------------------------
// 7100015160
s64 FUN_7100015160(s64 param_1, s64 param_2, s64 param_3, s64 param_4,
                   u64 param_5, u64 param_6, u64 param_7)
{
    if (param_4 == 0 && (s32)param_5 == 0) {
        return 0;
    }
    s64 diff = param_1 - param_2;
    if (diff < param_3) {
        return -1;
    }
    s64 lVar1 = (diff * 1000) / param_3;
    s64 lVar3 = FUN_7100017750(param_6, param_7, param_4, param_5);
    s64 result = lVar1 - lVar3;
    return (result > 0) ? result : 0;
}

// -- FUN_7100016cc0 ----------------------------------------------------------
// 7100016cc0
void FUN_7100016cc0(s64 param_1)
{
    *(u64 *)(param_1 + 0xb78) = 0;
    *(u64 *)(param_1 + 0xb70) = 0;
}

// -- FUN_71000177a0 ----------------------------------------------------------
// 71000177a0
s64 FUN_71000177a0(s64 param_1, s32 param_2, s64 param_3, s32 param_4)
{
    if (0x862 < param_1 - param_3) {
        return 0x7fffffff;
    }
    return (param_1 - param_3) * 1000000 + (s64)(param_2 - param_4);
}

// -- FUN_71000189d0 ----------------------------------------------------------
// 71000189d0
void FUN_71000189d0(s64 param_1)
{
    *(u64 *)(param_1 + 0x4fd0) = *(u64 *)(param_1 + 0x318);
    *(u64 *)(param_1 + 0x4fd8) = *(u64 *)(param_1 + 0x288);
}

// -- FUN_710002b7f0 ----------------------------------------------------------
// 710002b7f0
const char *FUN_710002b7f0(void)
{
    return "1.2.11.f-NINTENDO-SDK-v1";
}

// -- FUN_7100031080 ----------------------------------------------------------
// 7100031080
void FUN_7100031080(u8 *param_1)
{
    *param_1 = 0;
    *(u16 *)(param_1 + 2) = 7;
}

// -- FUN_7100031090 ----------------------------------------------------------
// 7100031090
void FUN_7100031090(u8 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 4) = 0;
}

// -- FUN_71000310b0 ----------------------------------------------------------
// 71000310b0
void FUN_71000310b0(u16 *param_1)
{
    *param_1 = 7;
}

// -- FUN_71000312e0 ----------------------------------------------------------
// 71000312e0
void FUN_71000312e0(u32 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 4) = 0;
}

// -- FUN_71000312f0 ----------------------------------------------------------
// 71000312f0
void FUN_71000312f0(u64 *param_1)
{
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0x3f80000000000000ULL;
}

// -- FUN_71000313d0 ----------------------------------------------------------
// 71000313d0
void FUN_71000313d0(u32 *param_1)
{
    *param_1 = 0x10000;
}

// -- FUN_71000313e0 ----------------------------------------------------------
// 71000313e0
void FUN_71000313e0(u16 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 2) = 0;
}

// -- FUN_7100031570 ----------------------------------------------------------
// 7100031570
bool FUN_7100031570(s32 param_1)
{
    return (u32)(param_1 - 0x1a) < 0x21;
}

// -- FUN_71000319e0 ----------------------------------------------------------
// 71000319e0
void FUN_71000319e0(s64 param_1)
{
    if (((*(u8 *)(param_1 + 1) >> 1) & 1) == 0) {
        return;
    }
    typedef void (*fn_t)(u64);
    fn_t fn = *(fn_t *)PTR_DAT_71052a22f8;
    fn(*(u64 *)(param_1 + 8));
}

// -- FUN_71000336b0 ----------------------------------------------------------
// 71000336b0
void FUN_71000336b0(u64 *param_1)
{
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// -- FUN_71000337f0 ----------------------------------------------------------
// 71000337f0
void FUN_71000337f0(u8 *param_1)
{
    *param_1 = 2;
}

// -- FUN_7100033800 ----------------------------------------------------------
// 7100033800
void FUN_7100033800(u8 *param_1)
{
    *param_1 = 1;
}

// -- FUN_71000338a0 ----------------------------------------------------------
// 71000338a0
s32 FUN_71000338a0(s64 param_1, s32 *param_2)
{
    if (*(u8 *)(param_1 + 1) != 0) {
        return *param_2;
    }
#ifdef MATCHING_HACK_NX_CLANG
    asm("" ::: "memory");
#endif
    s32 a = *(s32 *)(param_1 + 0x10);
    s32 b = *param_2;
    s32 iVar2 = b - a;
    s32 iVar1 = (iVar2 < 0) ? (iVar2 + 0xf) : iVar2;
    return iVar1 >> 4;
}

// -- FUN_71000373b0 ----------------------------------------------------------
// 71000373b0
u32 FUN_71000373b0(u64 param_1)
{
    return DAT_710446f378[(u32)param_1];
}

// -- FUN_71000373c0 ----------------------------------------------------------
// 71000373c0
u32 FUN_71000373c0(u64 param_1)
{
    return DAT_7104470000[(u32)param_1];
}

// -- FUN_71000373d0 ----------------------------------------------------------
// 71000373d0
u32 FUN_71000373d0(u64 param_1)
{
    return DAT_7104470000[(u32)param_1];
}

// -- FUN_71000373e0 ----------------------------------------------------------
// 71000373e0
u32 FUN_71000373e0(u64 param_1)
{
    return DAT_7104470000[(u32)param_1];
}

// -- FUN_71000373f0 ----------------------------------------------------------
// 71000373f0
u32 FUN_71000373f0(u64 param_1)
{
    return DAT_710446f3a0[(u32)param_1];
}

// -- FUN_7100037400 ----------------------------------------------------------
// 7100037400
u32 FUN_7100037400(u64 param_1)
{
    return DAT_710446f3b4[(u32)param_1];
}

// -- FUN_7100037410 ----------------------------------------------------------
// 7100037410
u32 FUN_7100037410(u64 param_1)
{
    return DAT_710446f400[(u32)param_1];
}

// -- FUN_7100037420 ----------------------------------------------------------
// 7100037420
u32 FUN_7100037420(u64 param_1)
{
    return DAT_710446f528[(u32)param_1];
}

// -- FUN_7100037430 ----------------------------------------------------------
// 7100037430
u32 FUN_7100037430(u64 param_1)
{
    return DAT_7104470580[(u32)param_1];
}

// -- FUN_71000374b0 ----------------------------------------------------------
// 71000374b0
u32 FUN_71000374b0(u64 param_1)
{
    return DAT_7104470580[(u32)param_1];
}

// -- FUN_7100039390 ----------------------------------------------------------
// 7100039390
void FUN_7100039390(u64 *param_1)
{
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// -- FUN_71000395a0 ----------------------------------------------------------
// 71000395a0
void FUN_71000395a0(u64 *param_1)
{
    param_1[3] = 0;
    param_1[4] = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// -- FUN_71000395c0 ----------------------------------------------------------
// 71000395c0
void FUN_71000395c0(u64 *param_1, u64 param_2, u32 param_3)
{
    *param_1 = param_2;
    *(u32 *)(param_1 + 4) = param_3;
}

// -- FUN_7100039800 ----------------------------------------------------------
// 7100039800
void FUN_7100039800(u64 *param_1)
{
    *(u32 *)(param_1 + 3) = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
}

// -- FUN_7100039a50 ----------------------------------------------------------
// 7100039a50
void FUN_7100039a50(u64 *param_1)
{
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// -- FUN_7100039a70 ----------------------------------------------------------
// 7100039a70
void FUN_7100039a70(s64 param_1, u64 param_2, u32 param_3)
{
    *(u64 *)(param_1 + 0x10) = param_2;
    *(u32 *)(param_1 + 0xc) = param_3;
}

// -- FUN_7100039e60 ----------------------------------------------------------
// 7100039e60
void FUN_7100039e60(u64 *param_1, u64 param_2, u32 param_3)
{
    *param_1 = param_2;
    *(u32 *)((s64)param_1 + 0xc) = param_3;
}

// -- FUN_710003a3b0 ----------------------------------------------------------
// 710003a3b0
void FUN_710003a3b0(u8 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x10) = 0;
}

// -- FUN_710003a4d0 ----------------------------------------------------------
// 710003a4d0
void FUN_710003a4d0(u8 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x10) = 0;
}

// -- FUN_710003a5d0 ----------------------------------------------------------
// 710003a5d0
void FUN_710003a5d0(u8 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x10) = 0;
}

// -- FUN_710003a6f0 ----------------------------------------------------------
// 710003a6f0
bool FUN_710003a6f0(s64 *param_1)
{
    return *param_1 != 0;
}

// -- FUN_710003a710 ----------------------------------------------------------
// 710003a710
u64 FUN_710003a710(void)
{
    return PTR_glslcCompilePreSpecialized_71052a32e8;
}

// -- FUN_710003a720 ----------------------------------------------------------
// 710003a720
u64 FUN_710003a720(void)
{
    return PTR_glslcCompileSpecialized_71052a32f0;
}

// -- FUN_710003a730 ----------------------------------------------------------
// 710003a730
u64 FUN_710003a730(void)
{
    return PTR_glslcInitialize_71052a32f8;
}

// -- FUN_710003a740 ----------------------------------------------------------
// 710003a740
u64 FUN_710003a740(void)
{
    return PTR_glslcFinalize_71052a3300;
}

// -- FUN_710003a750 ----------------------------------------------------------
// 710003a750
u64 FUN_710003a750(void)
{
    return PTR_glslcCompile_71052a3308;
}

// -- FUN_710003a760 ----------------------------------------------------------
// 710003a760
u64 FUN_710003a760(void)
{
    return PTR_glslcGetVersion_71052a3310;
}

// -- FUN_710003a770 ----------------------------------------------------------
// 710003a770
u64 FUN_710003a770(void)
{
    return PTR_glslcSetAllocator_71052a3318;
}

// -- FUN_710003a780 ----------------------------------------------------------
// 710003a780
u64 FUN_710003a780(void)
{
    return PTR_glslcGetDefaultOptions_71052a3320;
}

// -- FUN_710003a810 ----------------------------------------------------------
// 710003a810
void FUN_710003a810(s64 param_1, u64 param_2, u32 param_3)
{
    *(u64 *)(param_1 + 0xb0) = param_2;
    *(u32 *)(param_1 + 4) = param_3;
}

// -- FUN_710003a9a0 ----------------------------------------------------------
// 710003a9a0
void FUN_710003a9a0(u64 *param_1)
{
    param_1[5] = 0;
    param_1[6] = 0;
    *param_1 = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// -- FUN_710003ba60 ----------------------------------------------------------
// 710003ba60
u8 FUN_710003ba60(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x50) != 0) {
        return *(u8 *)(*(s64 *)(param_1 + 0x50) + 0x44) & 1;
    }
    return 1;
}

// -- FUN_71000443d0 ----------------------------------------------------------
// 71000443d0
void FUN_71000443d0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3578 + 0x10);
}

// -- FUN_71000446a0 ----------------------------------------------------------
// 71000446a0
s64 FUN_71000446a0(s64 param_1, u16 param_2)
{
    return *(s64 *)(param_1 + 0x10) +
           (u64)*(u32 *)(*(s64 *)(param_1 + 0x10) + (u64)param_2 * 4 + 0xc);
}

// -- FUN_7100044ca0 ----------------------------------------------------------
// 7100044ca0
void FUN_7100044ca0(s64 param_1)
{
    *(u64 *)(param_1 + 400) = 0;
    *(u16 *)(param_1 + 0x198) = 0;
}

// -- FUN_7100045030 ----------------------------------------------------------
// 7100045030
u64 FUN_7100045030(s64 param_1, s64 param_2)
{
    s64 lVar1;
    u64 uVar2;

    lVar1 = *(s64 *)(param_1 + 8);
    do {
        if (param_1 == lVar1) {
            return 0;
        }
        uVar2 = 0;
        while (*(s8 *)(param_2 + uVar2) == *(s8 *)(lVar1 + 0x10 + uVar2)) {
            if ((*(s8 *)(param_2 + uVar2) == 0) || (uVar2 = uVar2 + 1, 0x7f < uVar2)) {
                return *(u64 *)(lVar1 + 0x90);
            }
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (true);
}

// -- FUN_7100045fd0 ----------------------------------------------------------
// 7100045fd0
s64 FUN_7100045fd0(s64 param_1, u32 param_2)
{
    return param_1 + (u64)param_2 * 0x28 + 0x270;
}

// -- FUN_7100046e50 ----------------------------------------------------------
// 7100046e50
s64 FUN_7100046e50(s64 param_1, s32 param_2)
{
    return *(s64 *)(param_1 + 0x260) + (s64)param_2 * 8;
}

// -- FUN_71000472f0 ----------------------------------------------------------
// 71000472f0
void FUN_71000472f0(s64 param_1, s32 param_2)
{
    *(u32 *)(param_1 + 8) = *(u32 *)(param_1 + 8) & 0xffffff0f | (u32)param_2 << 4;
}

// -- FUN_7100047310 ----------------------------------------------------------
// 7100047310
void FUN_7100047310(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 8) = *(u32 *)(param_1 + 8) & 0xfffffff8 | param_2;
}

// -- FUN_7100047880 ----------------------------------------------------------
// 7100047880
u32 FUN_7100047880(s64 param_1)
{
    return *(u32 *)(param_1 + 8) >> 4 & 0xf;
}

// -- FUN_710004c5c0 ----------------------------------------------------------
// 710004c5c0
u64 FUN_710004c5c0(s64 *param_1, s32 param_2)
{
    return *(u64 *)(*param_1 + (s64)param_2 * 8);
}

// -- FUN_710004c5d0 ----------------------------------------------------------
// 710004c5d0
s32 FUN_710004c5d0(s64 param_1)
{
    return *(s32 *)(param_1 + 8) - 1;
}

// -- FUN_7100060ee0 ----------------------------------------------------------
// 7100060ee0
void FUN_7100060ee0(u8 *param_1, s64 param_2)
{
    if (param_2 != 0) {
        *(s64 *)(param_1 + 8) = param_2;
        *param_1 = 0x90;
    }
}

// -- FUN_71000650c0 ----------------------------------------------------------
// 71000650c0
u64 FUN_71000650c0(s64 param_1, s64 param_2)
{
    s64 lVar1;
    u64 uVar2;

    lVar1 = *(s64 *)(param_1 + 8);
    do {
        if (param_1 == lVar1) {
            return 0;
        }
        uVar2 = 0;
        while (*(s8 *)(param_2 + uVar2) == *(s8 *)(lVar1 + 0x10 + uVar2)) {
            if ((*(s8 *)(param_2 + uVar2) == 0) || (uVar2 = uVar2 + 1, 0x7f < uVar2)) {
                return *(u64 *)(lVar1 + 0x90);
            }
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (true);
}

// -- FUN_7100078f60 ----------------------------------------------------------
// 7100078f60
void FUN_7100078f60(s64 param_1)
{
    *(u32 *)(*(s64 *)(param_1 + 0x30) + 0x9c) = 0;
}

// -- FUN_7100078fd0 ----------------------------------------------------------
// 7100078fd0
u32 FUN_7100078fd0(s64 param_1, u64 param_2, s64 *param_3)
{
    s64 lVar1;

    if (0 < *(s32 *)(param_1 + 0x98)) {
        return 0;
    }
    if (0 < (s32)param_3[2]) {
        lVar1 = *param_3;
        if (lVar1 != 0) {
            *(s32 *)(param_1 + 0x98) = (s32)param_3[2];
            *(u32 *)(param_1 + 0x9c) = 0;
            *(s64 *)(param_1 + 0xa0) = lVar1;
            *(s64 *)(param_1 + 0xa8) = lVar1 + (s64)(s32)param_3[2] * 0x38;
            *(u8 *)(param_1 + 0xb8) = *(u8 *)((s64)param_3 + 0x14);
            *(u8 *)(param_1 + 0xb9) = *(u8 *)((s64)param_3 + 0x15);
            *(u8 *)(param_1 + 0xba) = *(u8 *)((s64)param_3 + 0x16);
            *(u8 *)(param_1 + 0xbb) = *(u8 *)((s64)param_3 + 0x17);
            *(s64 *)(param_1 + 0xb0) = param_3[1];
            return 1;
        }
        return 0;
    }
    return 0;
}

// -- FUN_710007d470 ----------------------------------------------------------
// 710007d470
void FUN_710007d470(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3910 + 0x10);
}

// -- FUN_7100098f70 ----------------------------------------------------------
// 7100098f70
u8 *FUN_7100098f70(void)
{
    return PTR_DAT_71052a3a68;
}

// -- FUN_71000b1480 ----------------------------------------------------------
// 71000b1480
u8 FUN_71000b1480(void)
{
    return DAT_71052aa9a0;
}

// -- FUN_71000b18a0 ----------------------------------------------------------
// 71000b18a0
u8 FUN_71000b18a0(void)
{
    return DAT_71052aa9a2;
}

// -- FUN_71000b30b0 ----------------------------------------------------------
// 71000b30b0
u64 FUN_71000b30b0(void)
{
    return *(u64 *)PTR_DAT_71052a3c38;
}

// -- FUN_71000b3870 ----------------------------------------------------------
// 71000b3870
void FUN_71000b3870(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x590) = param_2 & 1;
}

// -- FUN_71000b3ca0 ----------------------------------------------------------
// 71000b3ca0
u64 FUN_71000b3ca0(void)
{
    return DAT_7104f49398;
}

// -- FUN_71000b3d40 ----------------------------------------------------------
// 71000b3d40
u64 FUN_71000b3d40(void)
{
    return DAT_7104f49438;
}

// -- FUN_71000bb9c0 ----------------------------------------------------------
// 71000bb9c0
u32 FUN_71000bb9c0(u16 *param_1)
{
    u32 val = (u32)*param_1;
    val = __builtin_bswap32(val);
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(val));
#endif
    return val >> 16;
}

// -- FUN_71000bc710 ----------------------------------------------------------
// 71000bc710
s64 FUN_71000bc710(s64 param_1, u32 param_2)
{
    s64 result = param_1 + (s64)(s32)param_2 * 0x68;
    return (param_2 < 0xcu) ? result : 0;
}

// -- FUN_71000c0790 ----------------------------------------------------------
// 71000c0790
u8 FUN_71000c0790(void)
{
    return DAT_71052abd8c;
}

// -- FUN_71000c0850 ----------------------------------------------------------
// 71000c0850
u8 FUN_71000c0850(void)
{
    return DAT_71052abd8d;
}

// -- FUN_71000c0860 ----------------------------------------------------------
// 71000c0860
u8 *FUN_71000c0860(void)
{
    return PTR_DAT_71052a3d48;
}

// -- FUN_71000c75f0 ----------------------------------------------------------
// 71000c75f0
u16 FUN_71000c75f0(void)
{
    return *(u16 *)PTR_DAT_71052a3e28;
}

// -- FUN_71000cf210 ----------------------------------------------------------
// 71000cf210
void FUN_71000cf210(s64 param_1)
{
    *(u8 *)(param_1 + 0x1850) = 0;
}

// -- FUN_71001156e0 ----------------------------------------------------------
// 71001156e0
void FUN_71001156e0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4810 + 0x10);
}

// -- FUN_7100116880 ----------------------------------------------------------
// 7100116880
u8 FUN_7100116880(void)
{
    return DAT_71052abfc8;
}

// -- FUN_7100116940 ----------------------------------------------------------
// 7100116940
u8 FUN_7100116940(void)
{
    return DAT_71052abfc9;
}

// -- FUN_7100116f40 ----------------------------------------------------------
// 7100116f40
u64 FUN_7100116f40(void)
{
    return *(u64 *)PTR_DAT_71052a4820;
}

// -- FUN_710011bfe0 ----------------------------------------------------------
// 710011bfe0
u8 FUN_710011bfe0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x2000);
}

// -- FUN_7100121af0 ----------------------------------------------------------
// 7100121af0
void FUN_7100121af0(s64 param_1)
{
    *(u32 *)(param_1 + 0x2b0) = 3;
}

// -- FUN_7100125e30 ----------------------------------------------------------
// 7100125e30
bool FUN_7100125e30(s64 param_1)
{
    return *(s32 *)(param_1 + 0x134c) != 0;
}

// -- FUN_7100125f90 ----------------------------------------------------------
// 7100125f90
void FUN_7100125f90(s64 param_1)
{
    *(u8 *)(param_1 + 0x1362) = 1;
}

// -- FUN_7100129a90 ----------------------------------------------------------
// 7100129a90
u8 FUN_7100129a90(s64 param_1)
{
    return *(u8 *)(param_1 + 0x1361);
}

// -- FUN_71001309c0 ----------------------------------------------------------
// 71001309c0
void FUN_71001309c0(u64 param_1)
{
    *(u64 *)PTR_DAT_71052a4bc0 = param_1;
}

// -- FUN_710013c950 ----------------------------------------------------------
// 710013c950
u8 FUN_710013c950(void)
{
    return DAT_71052acb31;
}

// -- FUN_710013dac0 ----------------------------------------------------------
// 710013dac0
void FUN_710013dac0(u64 param_1, u32 param_2)
{
    *(u32 *)(*(s64 *)PTR_DAT_71052a4080 + 0xd4) = param_2;
}

// -- FUN_710013f6f0 ----------------------------------------------------------
// 710013f6f0
void FUN_710013f6f0(u64 param_1, u32 param_2)
{
    *(u32 *)(*(s64 *)PTR_DAT_71052a4080 + 0xd4) = param_2;
}

// -- FUN_7100143c60 ----------------------------------------------------------
// 7100143c60
void FUN_7100143c60(u64 param_1, u32 param_2)
{
    *(u32 *)(*(s64 *)PTR_DAT_71052a4080 + 0xd4) = param_2;
}

// -- FUN_7100147f30 ----------------------------------------------------------
// 7100147f30
void FUN_7100147f30(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x1e4) = param_2 & 1;
}

// -- FUN_7100149c40 ----------------------------------------------------------
// 7100149c40
void FUN_7100149c40(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4ee0 + 0x10);
}

// -- FUN_7100150440 ----------------------------------------------------------
// 7100150440
void FUN_7100150440(s64 param_1, s64 param_2, u32 param_3)
{
    s64 lVar1;
    u32 uVar2;

    lVar1 = *(s64 *)(param_1 + 0x10);
    while (true) {
        if (lVar1 == param_1 + 8) {
            return;
        }
        if (*(s64 *)(lVar1 + 0x20) == param_2) break;
        lVar1 = *(s64 *)(lVar1 + 8);
    }
    uVar2 = 1;
    if ((param_3 & 1) != 0) {
        uVar2 = 2;
    }
    *(u32 *)(lVar1 + 0x10) = uVar2;
}

// -- FUN_7100150da0 ----------------------------------------------------------
// 7100150da0
void FUN_7100150da0(s64 param_1, s64 param_2, u8 param_3)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    while (true) {
        if (lVar1 == param_1 + 8) {
            return;
        }
        if (*(s64 *)(lVar1 + 0x20) == param_2) break;
        lVar1 = *(s64 *)(lVar1 + 8);
    }
    *(u8 *)(lVar1 + 0x2d) = param_3;
}

// -- FUN_71001516e0 ----------------------------------------------------------
// 71001516e0
u8 FUN_71001516e0(void)
{
    return DAT_71052acb48;
}

// -- FUN_71001516f0 ----------------------------------------------------------
// 71001516f0
u8 FUN_71001516f0(void)
{
    return DAT_71052acb49;
}

// -- FUN_71001531c0 ----------------------------------------------------------
// 71001531c0
void FUN_71001531c0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4f80 + 0x10);
}

// -- FUN_7100154d50 ----------------------------------------------------------
// 7100154d50
void FUN_7100154d50(u64 *param_1)
{
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0xffffffffffffffffULL;
}

// -- FUN_7100155bd0 ----------------------------------------------------------
// 7100155bd0
u8 FUN_7100155bd0(s64 param_1, s64 param_2, u8 param_3, u32 param_4, u8 param_5)
{
    if (*(s8 *)(param_2 + 0x621) != 0) {
        return 0;
    }
    if ((*(s32 *)(param_1 + 0x18) != 0) && (((*(s8 *)(param_2 + 0x622) != 0) ^ param_3) & 1) != 0) {
        return 0;
    }
    if (param_4 < *(u32 *)(param_2 + 0x5e8)) {
        return 0;
    }
    return ((*(s8 *)(param_2 + 0x624) != 0) ^ param_5 ^ 1) & 1;
}

// -- FUN_7100156620 ----------------------------------------------------------
// 7100156620
void FUN_7100156620(s64 param_1)
{
    *(u64 *)(param_1 + 0x30) = 0;
    *(u64 *)(param_1 + 0x40) = 0;
    *(u8 *)(param_1 + 0x38) = 0xfd;
}

// -- FUN_710015fc10 ----------------------------------------------------------
// 710015fc10
void FUN_710015fc10(s64 param_1, u64 *param_2)
{
    *(u8 *)(param_1 + 0x18) = 1;
    *(u64 *)(param_1 + 0x10) = *param_2;
}

// -- FUN_7100160290 ----------------------------------------------------------
// 7100160290
u8 FUN_7100160290(s64 param_1)
{
    return *(u8 *)(param_1 + 0x78) >> 2 & 3;
}

// -- FUN_71001602a0 ----------------------------------------------------------
// 71001602a0
u8 FUN_71001602a0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x78) & 3;
}

// -- FUN_71001602b0 ----------------------------------------------------------
// 71001602b0
u8 FUN_71001602b0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x78) >> 4;
}

// -- FUN_7100160320 ----------------------------------------------------------
// 7100160320
bool FUN_7100160320(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x78) & 0xc) == 4;
}

// -- FUN_7100160340 ----------------------------------------------------------
// 7100160340
u8 FUN_7100160340(s64 param_1)
{
    return *(u8 *)(param_1 + 0x79) & 1;
}

// -- FUN_7100160350 ----------------------------------------------------------
// 7100160350
u8 FUN_7100160350(s64 param_1)
{
    return *(u8 *)(param_1 + 0x79) >> 1 & 1;
}

// -- FUN_7100160360 ----------------------------------------------------------
// 7100160360
bool FUN_7100160360(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x79) & 3) == 2;
}

// -- FUN_7100160430 ----------------------------------------------------------
// 7100160430
bool FUN_7100160430(s64 param_1)
{
    return *(s8 *)(param_1 + 0x7b) == 1;
}

// -- FUN_71001604c0 ----------------------------------------------------------
// 71001604c0
void FUN_71001604c0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x78) = (*(u8 *)(param_1 + 0x78) & 0xfc) | (param_2 & 3);
}

// -- FUN_71001604d0 ----------------------------------------------------------
// 71001604d0
void FUN_71001604d0(s64 param_1, s32 param_2)
{
    *(u8 *)(param_1 + 0x78) = (*(u8 *)(param_1 + 0x78) & 0xf) | (u8)(param_2 << 4);
}

// -- FUN_7100164430 ----------------------------------------------------------
// 7100164430
void FUN_7100164430(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5060 + 0x10);
}

// -- FUN_7100166760 ----------------------------------------------------------
// 7100166760
void FUN_7100166760(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5088 + 0x10);
}

// -- FUN_7100166790 ----------------------------------------------------------
// 7100166790
s64 FUN_7100166790(s64 *param_1)
{
    s64 lVar1;

    if (param_1[0x13] != 0) {
        return 0;
    }
    typedef s64 (*fn_t)(void);
    fn_t fn = *(fn_t *)(*param_1 + 0x20);
    lVar1 = fn();
    param_1[0x13] = lVar1;
    return lVar1;
}

// -- FUN_71001672c0 ----------------------------------------------------------
// 71001672c0
void FUN_71001672c0(u8 *param_1)
{
    *param_1 = 1;
}

// -- FUN_7100167560 ----------------------------------------------------------
// 7100167560
u8 FUN_7100167560(void)
{
    return DAT_71052acd88;
}

// -- FUN_7100167620 ----------------------------------------------------------
// 7100167620
u8 FUN_7100167620(void)
{
    return DAT_71052acd89;
}

// -- FUN_710016af60 ----------------------------------------------------------
// 710016af60
u32 FUN_710016af60(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x48) != 0) {
        return *(u32 *)(*(s64 *)(param_1 + 0x48) + 8);
    }
    return 0;
}

// -- FUN_71001770c0 ----------------------------------------------------------
// 71001770c0
void FUN_71001770c0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5270 + 0x10);
    param_1[1] = 0;
}

// -- FUN_71001770e0 ----------------------------------------------------------
// 71001770e0
void FUN_71001770e0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5270 + 0x10);
    param_1[1] = 0;
}

// -- FUN_710017c1c0 ----------------------------------------------------------
// 710017c1c0
void FUN_710017c1c0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5388 + 0x10);
    param_1[1] = 0;
}

// -- FUN_710017c1e0 ----------------------------------------------------------
// 710017c1e0
void FUN_710017c1e0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5388 + 0x10);
    param_1[1] = 0;
}

// -- FUN_710017f100 ----------------------------------------------------------
// 710017f100
void FUN_710017f100(s64 param_1)
{
    *(u64 *)(param_1 + 0x520) = 0;
    *(u64 *)(param_1 + 0x528) = 0;
}

// -- FUN_710017f1b0 ----------------------------------------------------------
// 710017f1b0
u8 FUN_710017f1b0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x1720);
}

// -- FUN_71001813d0 ----------------------------------------------------------
// 71001813d0
bool FUN_71001813d0(s64 param_1)
{
    return *(s32 *)(*(s64 *)(param_1 + 0x408) + 0x5c) != 0;
}

// -- FUN_7100182e70 ----------------------------------------------------------
// 7100182e70
void FUN_7100182e70(u64 *param_1, u64 param_2, u32 param_3)
{
    *param_1 = param_2;
    *(u32 *)(param_1 + 1) = param_3;
    *(u16 *)((s64)param_1 + 0xc) = 0;
    *(u32 *)(param_1 + 2) = 0;
}

// -- FUN_7100192f00 ----------------------------------------------------------
// 7100192f00
s32 FUN_7100192f00(s64 param_1)
{
    s32 iVar1;
    s32 iVar2;

    if (*(s32 *)(param_1 + 0xb0) == 1) {
        return 0;
    }
    iVar2 = *(s32 *)(param_1 + 0xb4);
    if ((iVar2 != 1) && (iVar1 = *(s32 *)(*(s64 *)(param_1 + 0x50) + 0x158), iVar1 != 0)) {
        if (iVar1 != 2) {
            iVar2 = 10;
            if (iVar1 != 3) {
                iVar2 = 5;
            }
            return iVar2;
        }
        iVar2 = 4;
    }
    return iVar2;
}

// -- FUN_71001931d0 ----------------------------------------------------------
// 71001931d0
bool FUN_71001931d0(s64 param_1)
{
    if (0x1f < *(u8 *)(param_1 + 0xac)) {
        return false;
    }
    return *(u8 *)(param_1 + 0xac) == *(u8 *)(param_1 + 0xab);
}

// -- FUN_71000001c0 ----------------------------------------------------------
// 71000001c0
s32 FUN_71000001c0(void)
{
    return 0;
}

// -- FUN_7100000230 ----------------------------------------------------------
// 7100000230
void FUN_7100000230(void)
{
    ((void (*)())(u64)DAT_71052a90d8[0])();
}

// -- FUN_7100004350 ----------------------------------------------------------
// 7100004350
void FUN_7100004350(u64 param_1)
{
    if (param_1)
        FUN_7100005640(param_1);
}

// -- FUN_7100004780 ----------------------------------------------------------
// 7100004780
void FUN_7100004780(void) {}

// -- FUN_7100004790 ----------------------------------------------------------
// 7100004790
s32 FUN_7100004790(void)
{
    return 0;
}

// -- FUN_7100004b70 ----------------------------------------------------------
// 7100004b70
u32 FUN_7100004b70(u64 param_1, s32 *param_2, s32 param_3)
{
    return 0;
}

// -- FUN_7100004dc0 ----------------------------------------------------------
// 7100004dc0
s32 FUN_7100004dc0(void)
{
    return 4;
}

// -- FUN_7100004dd0 ----------------------------------------------------------
// 7100004dd0
s32 FUN_7100004dd0(void)
{
    return 4;
}

// -- FUN_7100004de0 ----------------------------------------------------------
// 7100004de0
s32 FUN_7100004de0(void)
{
    return 4;
}

// -- FUN_7100004df0 ----------------------------------------------------------
// 7100004df0
s32 FUN_7100004df0(void)
{
    return 4;
}

// -- FUN_71000065d0 ----------------------------------------------------------
// 71000065d0
s32 FUN_71000065d0(void)
{
    return 0;
}

// -- FUN_71000065e0 ----------------------------------------------------------
// 71000065e0
s32 FUN_71000065e0(void)
{
    return 0;
}

// -- FUN_7100009420 ----------------------------------------------------------
// 7100009420
u64 FUN_7100009420(u64 param_1, s32 *param_2)
{
    if (*(u8 *)(param_1 + 0x4f69) != 0) {
        return 0;
    }
    if (*(u64 *)(param_1 + 0x10) == 0) {
        return 0;
    }
    s32 iVar5 = *(s32 *)(param_1 + 0x48);
    if ((u32)(iVar5 - 3) < 0xe) {
        *(u64 *)(*(u64 *)(param_1 + 0x10)) = param_1;
        iVar5 = *(s32 *)(param_1 + 0x48);
    }
    u64 uVar2 = 0;
    switch (iVar5) {
    case 3:
        return FUN_7100004b70(*(u64 *)(param_1 + 0x10), param_2, 5);
    case 4: {
        u64 lVar4 = *(u64 *)(param_1 + 0x10);
        if (*(s32 *)(lVar4 + 0x178) == 2 && *(u8 *)(lVar4 + 0x831) == 0) {
            return FUN_7100026380(lVar4, param_2, 5);
        }
        s32 iVar1 = *(s32 *)(lVar4 + 0x260);
        s32 iVar2;
        if (iVar1 == -1) {
            iVar2 = *(s32 *)(lVar4 + 0x264);
        } else {
            *param_2 = iVar1;
            uVar2 = 0x10000;
            iVar2 = *(s32 *)(lVar4 + 0x264);
        }
        u32 uVar3 = (u32)(iVar1 != -1);
        if (iVar2 != -1) {
            param_2[uVar3] = iVar2;
            return (u64)(1u << (u32)(uVar3 | 0x10) | (u32)uVar2);
        }
        break;
    }
    case 5: {
        u64 lVar4 = *(u64 *)(param_1 + 0x10);
        *param_2 = *(s32 *)(lVar4 + 600);
        u32 uVar3 = 0x10000;
        if (*(u64 *)(lVar4 + 0xb70) != 0) {
            uVar3 = 1;
        }
        uVar2 = (u64)uVar3;
        break;
    }
    case 6:
    case 7:
        return FUN_710001ef40(*(u64 *)(param_1 + 0x10), param_2, 5);
    case 9:
    case 10:
        return FUN_710001ef60(*(u64 *)(param_1 + 0x10), param_2, 5);
    case 0xb: {
        u64 uVar4 = *(u64 *)(param_1 + 0x10);
        if (uVar4 != 0) {
            typedef u64 (*fn_t)(u64, s32 *, s32);
            fn_t fn = (fn_t)(*(u64 *)(*(u64 *)(uVar4 + 0x858) + 0x50));
            if (fn) return fn(uVar4, param_2, 5);
            return 0;
        }
        break;
    }
    case 0xc:
    case 0xd:
    case 0xe:
        return FUN_7100018910(*(u64 *)(param_1 + 0x10), param_2, 5);
    }
    return uVar2;
}

// -- FUN_710000bc20 ----------------------------------------------------------
// 710000bc20
u64 FUN_710000bc20(u64 param_1)
{
    return param_1 + 0x180;
}

// -- FUN_710000bc30 ----------------------------------------------------------
// 710000bc30
u64 FUN_710000bc30(u64 param_1)
{
    return param_1 + 0x1a0;
}

// -- FUN_71000141c0 ----------------------------------------------------------
// 71000141c0
void FUN_71000141c0(u64 param_1)
{
    *(u8 *)(param_1 + 0x8c9) = 0;
}

// -- FUN_7100014680 ----------------------------------------------------------
// 7100014680
void FUN_7100014680(u64 param_1)
{
    *(u8 *)(param_1 + 0x8c8) = 0;
}

// -- FUN_7100015dd0 ----------------------------------------------------------
// 7100015dd0
s32 FUN_7100015dd0(void)
{
    return 0;
}
// -- FUN_7100018bb0 ----------------------------------------------------------
// 7100018bb0
s32 FUN_7100018bb0(void)
{
    return 0;
}

// -- FUN_710001ef40 ----------------------------------------------------------
// 710001ef40
u32 FUN_710001ef40(u64 param_1, s32 *param_2, s32 param_3)
{
    typedef u32 (*fn_t)(u64, s32 *, s32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)(param_1 + 0x858) + 0x40));
    if (!fn) return 0;
    return fn(param_1, param_2, param_3);
}

// -- FUN_710001ef60 ----------------------------------------------------------
// 710001ef60
u32 FUN_710001ef60(u64 param_1, s32 *param_2, s32 param_3)
{
    if (!param_1) return 0;
    typedef u32 (*fn_t)(u64, s32 *, s32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)(param_1 + 0x858) + 0x48));
    if (!fn) return 0;
    return fn(param_1, param_2, param_3);
}

// -- FUN_7100024760 ----------------------------------------------------------
// 7100024760
s32 FUN_7100024760(void)
{
    return 1;
}

// -- FUN_7100026380 ----------------------------------------------------------
// 7100026380
u32 FUN_7100026380(u64 param_1, s32 *param_2, s32 param_3)
{
    return 0;
}

// -- FUN_71000263a0 ----------------------------------------------------------
// 71000263a0
s32 FUN_71000263a0(void)
{
    return 4;
}

// -- FUN_71000263b0 ----------------------------------------------------------
// 71000263b0
s32 FUN_71000263b0(void)
{
    return 4;
}

// -- FUN_7100026e90 ----------------------------------------------------------
// 7100026e90
s32 FUN_7100026e90(void)
{
    return 0;
}

// -- FUN_7100026ea0 ----------------------------------------------------------
// 7100026ea0
s32 FUN_7100026ea0(void)
{
    return 0;
}

// -- FUN_7100027090 ----------------------------------------------------------
// 7100027090
void FUN_7100027090(void) {}

// -- FUN_71000270a0 ----------------------------------------------------------
// 71000270a0
void FUN_71000270a0(void) {}

// -- FUN_71000270b0 ----------------------------------------------------------
// 71000270b0
u32 FUN_71000270b0(u32 param_1)
{
    return param_1 & 0x7fffffff;
}

// -- FUN_71000270c0 ----------------------------------------------------------
// 71000270c0
void FUN_71000270c0(void) {}

// -- FUN_71000270e0 ----------------------------------------------------------
// 71000270e0
void FUN_71000270e0(void) {}

// -- FUN_71000270f0 ----------------------------------------------------------
// 71000270f0
void FUN_71000270f0(void) {}

// -- FUN_7100027100 ----------------------------------------------------------
// 7100027100
void FUN_7100027100(void) {}

// -- FUN_71000272b0 ----------------------------------------------------------
// 71000272b0
void FUN_71000272b0(void)
{
    ((void (*)())(*(u64 *)(PTR_DAT_71052a2248 + 0x10)))();
}

// -- FUN_71000281a0 ----------------------------------------------------------
// 71000281a0
void FUN_71000281a0(void) {}

// -- FUN_7100028410 ----------------------------------------------------------
// 7100028410
void FUN_7100028410(u64 param_1, u64 param_2, u32 param_3)
{
    FUN_71000281d0(param_1, 0xf, param_2, param_3);
}

// -- FUN_710002a6c0 ----------------------------------------------------------
// 710002a6c0
void FUN_710002a6c0(u64 param_1, u64 param_2, u32 param_3)
{
    FUN_710002a2f0(param_1, param_2, param_3);
}

// -- FUN_710002a9c0 ----------------------------------------------------------
// 710002a9c0
void FUN_710002a9c0(u64 param_1, u64 param_2, u32 param_3)
{
    FUN_710002a6d0(param_1, param_2, param_3);
}

// -- FUN_7100031290 ----------------------------------------------------------
// 7100031290
void FUN_7100031290(u32 *param_1)
{
    *param_1 = 0;
}

// -- FUN_71000312d0 ----------------------------------------------------------
// 71000312d0
void FUN_71000312d0(u64 *param_1)
{
    *param_1 = 0;
}

// -- FUN_7100031300 ----------------------------------------------------------
// 7100031300
void FUN_7100031300(u64 *param_1)
{
    param_1[0] = 0;
    param_1[1] = 0;
}

// -- FUN_71000319d0 ----------------------------------------------------------
// 71000319d0
void FUN_71000319d0(void) {}

// -- FUN_7100031b20 ----------------------------------------------------------
// 7100031b20
void FUN_7100031b20(void) {}

// -- FUN_7100031ca0 ----------------------------------------------------------
// 7100031ca0
void FUN_7100031ca0(u64 param_1, u64 *param_2)
{
    typedef void (*fn_t)(u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2338);
    fn(*(u64 *)(param_1 + 0xb8), *param_2);
}

// -- FUN_7100031cc0 ----------------------------------------------------------
// 7100031cc0
void FUN_7100031cc0(u64 param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2340);
    fn(*(u64 *)(param_1 + 0xb8));
}

// -- FUN_7100031ce0 ----------------------------------------------------------
// 7100031ce0
void FUN_7100031ce0(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0xd0) = param_2;
}

// -- FUN_7100031cf0 ----------------------------------------------------------
// 7100031cf0
void FUN_7100031cf0(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0xd8) = param_2;
}

// -- FUN_7100031d00 ----------------------------------------------------------
// 7100031d00
void FUN_7100031d00(void) {}

// -- FUN_7100031db0 ----------------------------------------------------------
// 7100031db0
void FUN_7100031db0(u64 param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2358);
    fn(*(u64 *)(param_1 + 0xb8));
}

// -- FUN_7100033810 ----------------------------------------------------------
// 7100033810
void FUN_7100033810(u64 param_1, u64 param_2, u64 param_3)
{
    typedef void (*fn_t)(u64, u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2530);
    fn(*(u64 *)(param_1 + 0x10), param_2, *(u64 *)(param_3 + 0x8));
}

// -- FUN_7100033830 ----------------------------------------------------------
// 7100033830
void FUN_7100033830(u64 param_1, u64 param_2, u64 param_3)
{
    typedef void (*fn_t)(u64, u64, u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2538);
    fn(*(u64 *)(param_1 + 0x10), param_2, *(u64 *)(param_3 + 0x8), *(u64 *)(param_3 + 0x10));
}

// -- FUN_71000339f0 ----------------------------------------------------------
// 71000339f0
void FUN_71000339f0(u64 param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2558);
    fn(*(u64 *)param_1);
}

// -- FUN_7100033a10 ----------------------------------------------------------
// 7100033a10
void FUN_7100033a10(void) {}

// -- FUN_7100037d40 ----------------------------------------------------------
// 7100037d40
void FUN_7100037d40(void) {}

// -- FUN_7100037ed0 ----------------------------------------------------------
// 7100037ed0
void FUN_7100037ed0(u64 param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2728);
    fn(*(u64 *)(param_1 + 0x8));
}

// -- FUN_7100038290 ----------------------------------------------------------
// 7100038290
void FUN_7100038290(void) {}

// -- FUN_71000393a0 ----------------------------------------------------------
// 71000393a0
void FUN_71000393a0(void) {}

// -- FUN_7100039580 ----------------------------------------------------------
// 7100039580
void FUN_7100039580(u64 param_1)
{
    *(u8 *)(param_1 + 0x2c) = 0;
}

// -- FUN_71000395b0 ----------------------------------------------------------
// 71000395b0
void FUN_71000395b0(void) {}

// -- FUN_71000395d0 ----------------------------------------------------------
// 71000395d0
u64 FUN_71000395d0(u64 param_1)
{
    return *(u64 *)param_1;
}

// -- FUN_71000397f0 ----------------------------------------------------------
// 71000397f0
void FUN_71000397f0(u64 param_1)
{
    *(u8 *)(param_1 + 0x24) = 0;
}

// -- FUN_7100039810 ----------------------------------------------------------
// 7100039810
void FUN_7100039810(void) {}

// -- FUN_71000399d0 ----------------------------------------------------------
// 71000399d0
void FUN_71000399d0(u64 param_1)
{
    *(u8 *)(param_1 + 0x18) = 0;
}

// -- FUN_7100039a80 ----------------------------------------------------------
// 7100039a80
u64 FUN_7100039a80(u64 param_1)
{
    return *(u64 *)(param_1 + 0x10);
}

// -- FUN_7100039dd0 ----------------------------------------------------------
// 7100039dd0
void FUN_7100039dd0(u64 param_1)
{
    *(u8 *)param_1 = 0;
}

// -- FUN_7100039e00 ----------------------------------------------------------
// 7100039e00
void FUN_7100039e00(u64 param_1)
{
    *(u8 *)param_1 = 0;
}

// -- FUN_7100039e50 ----------------------------------------------------------
// 7100039e50
void FUN_7100039e50(void) {}

// -- FUN_7100039e70 ----------------------------------------------------------
// 7100039e70
u64 FUN_7100039e70(u64 param_1)
{
    return *(u64 *)param_1;
}

// -- FUN_710003a010 ----------------------------------------------------------
// 710003a010
void FUN_710003a010(u64 param_1)
{
    *(u8 *)(param_1 + 0x40) = 0;
}

// -- FUN_710003a120 ----------------------------------------------------------
// 710003a120
void FUN_710003a120(void) {}

// -- FUN_710003a260 ----------------------------------------------------------
// 710003a260
void FUN_710003a260(void) {}

// -- FUN_710003a3e0 ----------------------------------------------------------
// 710003a3e0
void FUN_710003a3e0(void) {}

// -- FUN_710003a500 ----------------------------------------------------------
// 710003a500
void FUN_710003a500(void) {}

// -- FUN_710003a5e0 ----------------------------------------------------------
// 710003a5e0
void FUN_710003a5e0(void) {}

// -- FUN_710003a620 ----------------------------------------------------------
// 710003a620
void FUN_710003a620(u64 param_1, u64 param_2)
{
    typedef void (*fn_t)(u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2a98);
    fn(param_1, param_2);
}

// -- FUN_710003a700 ----------------------------------------------------------
// 710003a700
s32 FUN_710003a700(void)
{
    return 1;
}

// -- FUN_710003aaf0 ----------------------------------------------------------
// 710003aaf0
void FUN_710003aaf0(void) {}

// -- FUN_710003ab10 ----------------------------------------------------------
// 710003ab10
u64 FUN_710003ab10(u64 param_1)
{
    return *(u64 *)(param_1 + 0x8);
}

// -- FUN_710003ab20 ----------------------------------------------------------
// 710003ab20
u64 FUN_710003ab20(u64 param_1)
{
    return *(u64 *)(param_1 + 0x10);
}

// -- FUN_710003ab60 ----------------------------------------------------------
// 710003ab60
u64 FUN_710003ab60(u64 param_1)
{
    return *(u64 *)(param_1 + 0x30);
}

// -- FUN_710003ab70 ----------------------------------------------------------
// 710003ab70
u64 FUN_710003ab70(u64 param_1)
{
    return *(u64 *)(param_1 + 0x38);
}

// -- FUN_710003ab80 ----------------------------------------------------------
// 710003ab80
u32 FUN_710003ab80(u64 param_1)
{
    return *(u32 *)(param_1 + 0x18);
}

// -- FUN_710003ab90 ----------------------------------------------------------
// 710003ab90
u32 FUN_710003ab90(u64 param_1)
{
    return *(u32 *)(param_1 + 0x1c);
}

// -- FUN_710003aba0 ----------------------------------------------------------
// 710003aba0
u32 FUN_710003aba0(u64 param_1)
{
    return *(u32 *)(param_1 + 0x24);
}

// -- FUN_710003abb0 ----------------------------------------------------------
// 710003abb0
u32 FUN_710003abb0(u64 param_1)
{
    return *(u32 *)(param_1 + 0x28);
}

// -- FUN_710003abc0 ----------------------------------------------------------
// 710003abc0
void FUN_710003abc0(u64 param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)param_1 + 0x10));
    fn(param_1);
}

// -- FUN_710003abd0 ----------------------------------------------------------
// 710003abd0
void FUN_710003abd0(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x10) = param_2;
}

// -- FUN_710003abe0 ----------------------------------------------------------
// 710003abe0
void FUN_710003abe0(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x8) = param_2;
}

// -- FUN_710003abf0 ----------------------------------------------------------
// 710003abf0
void FUN_710003abf0(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x30) = param_2;
}

// -- FUN_710003ac00 ----------------------------------------------------------
// 710003ac00
void FUN_710003ac00(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x38) = param_2;
}

// -- FUN_710003ac10 ----------------------------------------------------------
// 710003ac10
void FUN_710003ac10(u64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x24) = param_2;
}

// -- FUN_710003b000 ----------------------------------------------------------
// 710003b000
void FUN_710003b000(u64 param_1, u64 param_2)
{
    typedef void (*fn_t)(u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2868);
    fn(*(u64 *)param_1, param_2);
}

// -- FUN_710003b020 ----------------------------------------------------------
// 710003b020
void FUN_710003b020(u64 param_1, u64 param_2)
{
    typedef void (*fn_t)(u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2910);
    fn(*(u64 *)(param_1 + 0x8), param_2);
}

// -- FUN_710003b040 ----------------------------------------------------------
// 710003b040
void FUN_710003b040(u64 param_1, u64 param_2)
{
    typedef void (*fn_t)(u64, u64);
    fn_t fn = (fn_t)(*(u64 *)PTR_DAT_71052a2c80);
    fn(*(u64 *)(param_1 + 0x8), param_2);
}

// -- FUN_710003b4f0 ----------------------------------------------------------
// 710003b4f0
void FUN_710003b4f0(u64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x38) = param_2;
    *(u64 *)(param_1 + 0x40) = param_3;
}

// -- FUN_710003bca0 ----------------------------------------------------------
// 710003bca0
void FUN_710003bca0(void) {}

// -- FUN_710003be40 ----------------------------------------------------------
// 710003be40
void FUN_710003be40(u64 param_1)
{
    *(u32 *)(param_1 + 0x20) = 0;
    typedef void (*fn_t)(u64, u32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)param_1 + 0xe0));
    fn(param_1, 0);
}

// -- FUN_710003be60 ----------------------------------------------------------
// 710003be60
void FUN_710003be60(u64 param_1)
{
    *(u32 *)(param_1 + 0x20) = 0;
    typedef void (*fn_t)(u64, u32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)param_1 + 0xe0));
    fn(param_1, 3);
}

// -- FUN_710003c5d0 ----------------------------------------------------------
// 710003c5d0
void FUN_710003c5d0(u64 param_1)
{
    typedef void (*fn_t)(u64, u32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)param_1 + 0xd8));
    fn(param_1, 3);
}

// -- FUN_710003c5e0 ----------------------------------------------------------
// 710003c5e0
void FUN_710003c5e0(u64 param_1)
{
    typedef void (*fn_t)(u64, u32);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)param_1 + 0xd8));
    fn(param_1, 0);
}

// -- FUN_710003c6c0 ----------------------------------------------------------
// 710003c6c0
void FUN_710003c6c0(void) {}

// -- FUN_71000425f0 ----------------------------------------------------------
// 71000425f0
void FUN_71000425f0(u64 param_1, u64 param_2, u64 param_3)
{
    FUN_7100045080(param_1 + 0xf8, param_2, param_3, 0);
}

// -- FUN_7100044320 ----------------------------------------------------------
// 7100044320
void FUN_7100044320(u64 *param_1)
{
    param_1[0] = 0;
    param_1[1] = 0;
}

// -- FUN_7100044710 ----------------------------------------------------------
// 7100044710
void FUN_7100044710(u64 param_1, u64 param_2)
{
    FUN_7100044720(param_1, param_2, 0.0f, 0.0f);
}

// -- FUN_7100044c50 ----------------------------------------------------------
// 7100044c50
void FUN_7100044c50(void) {}

// -- FUN_7100044c90 ----------------------------------------------------------
// 7100044c90
void FUN_7100044c90(u64 param_1)
{
    *(u64 *)(param_1 + 0xc0) = 0;
}

// -- FUN_7100044ef0 ----------------------------------------------------------
// 7100044ef0
u64 FUN_7100044ef0(u64 param_1)
{
    return *(u64 *)(param_1 + 0xe8);
}

// -- FUN_7100044f00 ----------------------------------------------------------
// 7100044f00
u64 FUN_7100044f00(u64 param_1)
{
    return *(u64 *)(param_1 + 0xf0);
}

// -- FUN_7100044f70 ----------------------------------------------------------
// 7100044f70
void FUN_7100044f70(void) {}

// -- FUN_7100048d90 ----------------------------------------------------------
// 7100048d90
void FUN_7100048d90(u64 param_1, u64 param_2)
{
    typedef void (*fn_t)(u64, u64, u64);
    u64 fn_val = *(u64 *)PTR_DAT_71052a3630;
    u64 arg2   = *(u64 *)PTR_DAT_71052a3640;
    fn_t fn = (fn_t)fn_val;
    fn(param_1, param_2, arg2);
}

// -- FUN_710004ba90 ----------------------------------------------------------
// 710004ba90
void FUN_710004ba90(u64 param_1, u64 param_2, u64 param_3)
{
    u64 obj = *(u64 *)(param_1 + 0x40);
    typedef void (*fn_t)(u64, u64, u64);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)obj + 0x88));
    fn(obj, param_2, param_3);
}

// -- FUN_710004baa0 ----------------------------------------------------------
// 710004baa0
void FUN_710004baa0(u64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    u64 obj = *(u64 *)(param_1 + 0x40);
    typedef void (*fn_t)(u64, u64, u64, u64, u64);
    fn_t fn = (fn_t)(*(u64 *)(*(u64 *)obj + 0x90));
    fn(obj, param_2, param_3, param_4, param_5);
}

// -- FUN_7100052ac0 ----------------------------------------------------------
// 7100052ac0
void FUN_7100052ac0(u64 param_1)
{
    if (*(u64 *)(param_1 + 0x40) != 0) return;
}

// -- FUN_7100056c10 ----------------------------------------------------------
// 7100056c10
void FUN_7100056c10(u64 param_1, u64 param_2)
{
    u64 obj = *(u64 *)(param_1 + 0x20);
    u16 w2  = *(u16 *)(param_1 + 0x4a);
    FUN_7100047800(obj, param_2, w2);
}

// -- FUN_7100056c40 ----------------------------------------------------------
// 7100056c40
void FUN_7100056c40(void) {}

// -- FUN_7100058660 ----------------------------------------------------------
// 7100058660
u32 FUN_7100058660(u64 param_1)
{
    if ((*(u8 *)(param_1 + 0x62) & 0x2) == 0) return 0;

    u64 base  = *(u64 *)(param_1 + 0xa8);
    u64 lVar3 = base + 0xc;
    u32 uVar1 = *(u32 *)(base + 0x10);

    // Hash table navigation
    u64 idx = (u64)(uVar1 + 4);
    u32 w11 = *(u32 *)(lVar3 + idx) + uVar1;
    s64 step = *(s8 *)((lVar3 + (u64)w11) + 0xc);
    idx += (u64)(step * 4);
    u32 slot_off = *(u32 *)(lVar3 + idx) + uVar1;
    u64 slot = lVar3 + (u64)slot_off;

    u64 entry = *(u64 *)(slot + 8);
    u64 uVar2 = *(u64 *)(entry + 0x58);

    u32 w8;
    if (uVar2 != 0 && ((*(u8 *)(uVar2 + 8) >> 5) & 1) != 0) {
        w8 = (*(u8 *)(entry + 0x98) == 0) ? 1u : 0u;
    } else {
        w8 = 0;
    }

    u64 lVar4 = *(u64 *)(entry + 8);
    if (lVar4 == 0) return w8;
    if (((*(u8 *)(lVar4 + 4) >> 1) & 1) != 0) {
        return w8 | (u32)(*(u8 *)(entry + 0x54) == 0);
    }
    return w8;
}

// -- FUN_71000607e0 ----------------------------------------------------------
// 71000607e0
void FUN_71000607e0(void) {}

// -- FUN_71000608e0 ----------------------------------------------------------
// 71000608e0
void FUN_71000608e0(void) {}

// -- FUN_7100060b90 ----------------------------------------------------------
// 7100060b90
void FUN_7100060b90(void) {}
// -- FUN_7100060f00 ----------------------------------------------------------
// 7100060f00
void FUN_7100060f00(void) {}

// -- FUN_7100060f10 ----------------------------------------------------------
// 7100060f10
void FUN_7100060f10(void) {}

// -- FUN_7100064c30 ----------------------------------------------------------
// 7100064c30
void FUN_7100064c30(void) {}
// -- FUN_71000662e0 ----------------------------------------------------------
// 71000662e0
f32 FUN_71000662e0(u64 param_1)
{
    return *(f32 *)(param_1 + 0x2c);
}

// -- FUN_7100078b50 ----------------------------------------------------------
// 7100078b50
void FUN_7100078b50(void) {}
// -- FUN_7100078f70 ----------------------------------------------------------
// 7100078f70
void FUN_7100078f70(void) {}

// -- FUN_7100078fc0 ----------------------------------------------------------
// 7100078fc0
void FUN_7100078fc0(void) {}
// -- FUN_7100079140 ----------------------------------------------------------
// 7100079140
void FUN_7100079140(u64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0xb0) = param_2;
}

// -- FUN_7100079e60 ----------------------------------------------------------
// 7100079e60
void FUN_7100079e60(u64 param_1, f32 param_2)
{
    *(f32 *)(param_1 + 0xbc) = param_2;
}

// -- FUN_710007a220 ----------------------------------------------------------
// 710007a220
void FUN_710007a220(void) {}

// -- FUN_710007a450 ----------------------------------------------------------
// 710007a450
extern u8 DAT_7104f40000[] __attribute__((visibility("hidden")));
extern "C" u64 FUN_71039c01e0(u8 *);

u64 FUN_710007a450(void)
{
    return FUN_71039c01e0(DAT_7104f40000);
}

// -- FUN_710007a9b0 ----------------------------------------------------------
// 710007a9b0
void FUN_710007a9b0(u64 param_1, void (*param_2)(u64, u64))
{
    param_2(param_1 + 0x408, param_1 + 0x390);
}

// -- FUN_710007bbe0 ----------------------------------------------------------
// 710007bbe0
void FUN_710007bbe0(u64 param_1, void (*param_2)(u64, u64))
{
    param_2(param_1 + 0x48, *(u64 *)(*(u64 *)(param_1 + 0x50) + 0x88));
}

// -- FUN_710007bc10 ----------------------------------------------------------
// 710007bc10
void FUN_710007bc10(u64 param_1, void (*param_2)(u64, u64))
{
    param_2(param_1 + 0x48, *(u64 *)(*(u64 *)(param_1 + 0x50) + 0x88));
}

// -- FUN_710007d470 ----------------------------------------------------------
// 710007d470
void FUN_710007d470(u64 *param_1)
{
    *param_1 = PTR_DAT_71052a3910 + 0x10;
}

// -- FUN_710007f4e0 ----------------------------------------------------------
// 710007f4e0
void FUN_710007f4e0(u64 param_1, void (*param_2)(u64, u64))
{
    param_2(param_1 + 0x1ec0, param_1 + 0x1d28);
}

// =========================================================================
// BATCH 8 -- remaining 0x7100 range functions
// =========================================================================

// SDK forward declarations
namespace nn { namespace os  { struct MutexType; void InitializeMutex(MutexType*, bool, int); } }
namespace nn { namespace crypto { void GenerateCryptographicallyRandomBytes(void*, u64); } }
namespace nn { namespace util   { void ReferSymbol(const void*); } }

// Additional external functions for batch 8
extern "C" void  FUN_7100089940(u64, u64, u32, u64);
extern "C" void  FUN_7100099520(u64);
extern "C" s32   FUN_71000b2850(u64);
extern "C" s32   FUN_71000b2b10(u64, u64);
extern "C" u64   FUN_71000c9b60(u64);
extern "C" u64   FUN_71000c7460(u64);
extern "C" u64   FUN_71000c7160(u64, u64);
extern "C" void *memset(void*, int, unsigned long);
extern "C" int   memset_s(void*, unsigned long, int, unsigned long);
extern u64       PTR_DAT_71052a3e30 __attribute__((visibility("hidden")));

// Forward declarations (called before defined in address order)
void FUN_71000b63c0(u64, u64);
u64  FUN_71000c7420(u64);

// -- FUN_71000338d0 ----------------------------------------------------------
// 71000338d0
extern "C" u64 FUN_71000338d0(u64, void *)
{
    return 0x1000;
}

// -- FUN_7100089bc0 ----------------------------------------------------------
// 7100089bc0
void FUN_7100089bc0(u64 param_1, u64 param_2, u64 param_3)
{
    FUN_7100089940(param_1, param_2, 0, param_3);
}

// -- FUN_7100098f80 ----------------------------------------------------------
// 7100098f80
void FUN_7100098f80(void (*param_1)(u8*, u8*, u64), u64 param_2)
{
    u64 base = *reinterpret_cast<u64 *>(PTR_DAT_71052a3a68);
    param_1((u8 *)base + 0x260, (u8 *)base + 0x120, param_2);
}

// -- FUN_71000a6c20 ----------------------------------------------------------
// 71000a6c20
void FUN_71000a6c20(u64 /*param_1*/, void (*param_2)(u8*, u8*, u64), u64 param_3)
{
    FUN_7100098f80(param_2, param_3);
}

// -- FUN_71000b2b70 ----------------------------------------------------------
// 71000b2b70
void FUN_71000b2b70(void) {}

// -- FUN_71000b3860 ----------------------------------------------------------
// 71000b3860
u8 FUN_71000b3860(u64 param_1)
{
    return *(u8 *)(param_1 + 0x568);
}

// -- FUN_71000b5de0 ----------------------------------------------------------
// 71000b5de0
void FUN_71000b5de0(u64 param_1)
{
    FUN_71000b63c0(param_1, 0xb0);
}
// -- FUN_71000b6400 ----------------------------------------------------------
// 71000b6400
void FUN_71000b6400(void *param_1, u32 param_2)
{
    nn::crypto::GenerateCryptographicallyRandomBytes(param_1, param_2);
}

// -- FUN_71000ba920 ----------------------------------------------------------
// 71000ba920
void FUN_71000ba920(void *param_1)
{
    memset(param_1, 0, 0x80);
}

// -- FUN_71000bec90 ----------------------------------------------------------
// 71000bec90
void FUN_71000bec90(void) {}

// -- FUN_71000bf820 ----------------------------------------------------------
// 71000bf820
void FUN_71000bf820(u64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x20) = param_2;
    *(u64 *)(param_1 + 0x28) = param_3;
}

// -- FUN_71000c0300 ----------------------------------------------------------
// 71000c0300
void FUN_71000c0300(void) {}

// -- FUN_71000c5260 ----------------------------------------------------------
// 71000c5260
void FUN_71000c5260(u64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x18c) = param_2;
}

// -- FUN_71000c5320 ----------------------------------------------------------
// 71000c5320
u64 FUN_71000c5320(u64 param_1)
{
    u64 x0 = *(u64 *)(param_1 + 0x90);
    if (x0 == 0) return 0;
    return FUN_71000c7420(x0);
}
// -- FUN_71000c5ac0 ----------------------------------------------------------
// 71000c5ac0
u64 FUN_71000c5ac0(u64 param_1)
{
    u64 x0 = *(u64 *)(param_1 + 0x90);
    if (x0 == 0) return 0;
    return FUN_71000c7160(x0, 0);
}

// -- FUN_71000c5b60 ----------------------------------------------------------
// 71000c5b60
void FUN_71000c5b60(u64 param_1)
{
    *(u64 *)(param_1 + 0x228) = 0;
}

// -- FUN_71000c7420 ----------------------------------------------------------
// 71000c7420
u64 FUN_71000c7420(u64 param_1)
{
    u64 obj = *(u64 *)(param_1 + 0x18);
    if (obj == 0) return 0;
    u64 lVar1 = FUN_71000c9b60(obj + 0x178);
    if (lVar1 == 0 || *(s32 *)(lVar1 + 0x9c) == -1) return 0;
    return 1;
}

// -- FUN_71000c74e0 ----------------------------------------------------------
// 71000c74e0
u64 FUN_71000c74e0(u64 param_1)
{
    return param_1 + 0x238;
}

// -- FUN_71000c7600 ----------------------------------------------------------
// 71000c7600
void FUN_71000c7600(s32 param_1, u16 param_2)
{
    if (param_1 != 0) return;
    *(u16 *)PTR_DAT_71052a3e30 = param_2;
}

// -- FUN_71000ca440 ----------------------------------------------------------
// 71000ca440
void FUN_71000ca440(void) {}

// -- FUN_71000cad60 ----------------------------------------------------------
// 71000cad60
void FUN_71000cad60(void) {}

// -- FUN_71000cf360 ----------------------------------------------------------
// 71000cf360
void FUN_71000cf360(u64 param_1)
{
    *(u64 *)(param_1 + 0x17b0) = 0;
}

// -- FUN_71000cf8f0 ----------------------------------------------------------
// 71000cf8f0
void FUN_71000cf8f0(void) {}

// -- FUN_71000eb6c0 ----------------------------------------------------------
// 71000eb6c0
u32 FUN_71000eb6c0(u64 param_1)
{
    return *(u32 *)(param_1 + 0x550);
}
