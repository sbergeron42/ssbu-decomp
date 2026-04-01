#include "types.h"

// MEDIUM-tier FUN_* functions — mixed address range, batch 9
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memset(void*, int, u64);
extern "C" void* memcpy(void*, const void*, u64);

// nn::os / nn::mem forward declarations
namespace nn {
namespace mem {
    void NumberLineAllocator_Free(s32);  // best-effort signature
}
namespace util {
    s32 SNPrintf(char*, s64, const char*, ...);
    void ReferSymbol(const char*);
}
namespace detail {
    [[noreturn]] void UnexpectedDefaultImpl(const char*, const char*, int);
}
}

// External C functions — forward declarations
extern "C" void  FUN_71002b94a0();
extern "C" void  FUN_7100248160();
extern "C" void  FUN_71001b1270();
extern "C" u64   FUN_71002b4e30(u64*);
extern "C" void  FUN_71002c28d0(s64, s32);    // x1 pass-through
extern "C" void  FUN_7100031e90(u64, s32, s32, s64, s32, s32);
extern "C" void  FUN_7100046380(s64, u64);
extern "C" void  FUN_71000325b0(u64, s32, s64, s32, s32);
extern "C" void  FUN_71000afae0(s64, u64, u32, u64);
extern "C" void  FUN_71000b1cf0(s64);
extern "C" void  FUN_710013baa0(s64*);
extern "C" void  FUN_71000bb5d0(u32*);
extern "C" void  FUN_71000c73f0(s64, u64, u32);
extern "C" void  FUN_71000cf250(s64, u64, u32);
extern "C" void  FUN_710014ebb0(u64, s32, u32, u64, u32, u64, u64, u32);
extern "C" u64   FUN_7100181380();
extern "C" void  FUN_71001808c0(u64, s32);
extern "C" void  FUN_71001aff70(s64, void*, u32);
extern "C" void  FUN_71001b4e00(u64, const char*);
extern "C" u64   FUN_71001df8c0();
extern "C" void  FUN_71002b8120(s64);
extern "C" void  FUN_71002b8140(s64);
extern "C" s64   FUN_71002b8160(s64, u32, u32);
extern "C" void  FUN_71002b8450(s64, u32, s32);
extern "C" void  FUN_71002c3200(void*);
extern "C" void  FUN_71002c2e40(u64);
extern "C" [[noreturn]] void FUN_71039c0d80(u64);
extern "C" u64   FUN_7101717b00(u64);
extern "C" void  nnsocketFcntl(u64, s32, u32);
extern "C" void* malloc(u64);

// External data
extern u8   PTR_DAT_71052a3d20[];
extern u8   PTR_DAT_71052a5068[];
extern u8   DAT_71043ab5ee;
extern u8   DAT_710427eedd;
extern u8   DAT_71052add48;
extern u8   DAT_71052b4278[];
extern u8*  DAT_71052b4270;         // pointer variable (byte ptr for arithmetic)
extern u8   PTR_DAT_71052a3da8[];   // deref'd as flag byte
extern u64  PTR_DAT_71052a3db8;     // deref'd as u64 pointer

// ---- Functions -----------------------------------------------------------

// 71002b9480 — call sub then return 0
u64 FUN_71002b9480()
{
    FUN_71002b94a0();
    return 0;
}

// 7100248210 — call FUN_7100248160, then tail-call FUN_71001b1270
void FUN_7100248210()
{
    FUN_7100248160();
    FUN_71001b1270();
}

// 71002b5f90 — deref param, call FUN_71002c28d0(result, 0)
void FUN_71002b5f90(u64* param_1)
{
    u64 uVar1 = FUN_71002b4e30(param_1);
    FUN_71002c28d0((s64)uVar1, 0);
}

// 710006fcc0 — store 4 fields at offsets +0x24,+0x28,+0x30,+0x34 in param_4
void FUN_710006fcc0(u32 param_1, u32 param_2, u64 /*param_3*/, s64 param_4)
{
    *(u32*)(param_4 + 0x24) = param_1;
    *(u32*)(param_4 + 0x28) = param_2;
    *(u32*)(param_4 + 0x30) = 0;
    *(u8*)(param_4 + 0x34) = 1;
}

// 71002b8c80 — dereference u32 pointer
u32 FUN_71002b8c80(u32* param_1)
{
    return *param_1;
}

// 7100013730 — set socket nonblocking flag via fcntl
void FUN_7100013730(u64 param_1, s32 param_2)
{
    u32 uVar1 = 2;
    if (param_2 != 0)
        uVar1 = 0x802;
    nnsocketFcntl(param_1, 4, uVar1);
}

// 710002b800 — allocate param_2*param_3 bytes (result discarded)
void FUN_710002b800(u64 /*param_1*/, s32 param_2, s32 param_3)
{
    malloc((u64)(u32)(param_3 * param_2));
}

// 710003aaa0 — conditional Free (skip if param_2 == -1)
void FUN_710003aaa0(s32 param_1, s32 param_2)
{
    if (param_2 != -1) {
        nn::mem::NumberLineAllocator_Free(param_1);
    }
}

// 7100044970 — dispatch with hardcoded args
void FUN_7100044970(u64 param_1, s64 param_2)
{
    FUN_7100031e90(param_1, 3, 1, *(s64*)(param_2 + 0xb8) + 0x248, 6, 0);
}

// 7100044db0 — if flag set, call FUN_7100046380 then clear flag
void FUN_7100044db0(s64 param_1)
{
    if (*(s8*)(param_1 + 0x18c) != 0) {
        *(u8*)(param_1 + 0x18c) = 0;
        FUN_7100046380(*(s64*)(param_1 + 0xb8), 0);
    }
}

// 7100046380 — forward to FUN_71000325b0 at offset +0x1f0
void FUN_7100046380(s64 param_1, u64 param_2)
{
    FUN_71000325b0(param_2, 0, param_1 + 0x1f0, 8, 0x20);
}

// 7100077eb0 — SNPrintf "%s_%d" with counter field
void FUN_7100077eb0(char* param_1, s32 param_2, u64 param_3, s64 param_4)
{
    nn::util::SNPrintf(param_1, (s64)param_2, "%s_%d", param_3,
                       (u64)*(u32*)(param_4 + 4));
}

// 71000880e0 — call FUN_71000afae0 with two cached fields
void FUN_71000880e0(s64 param_1, u32 param_2, u64 param_3)
{
    FUN_71000afae0(param_1 + 0x7a8, *(u64*)(param_1 + 0x700), param_2, param_3);
}

// 71000b1940 — SDK presence marker
void FUN_71000b1940()
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaCommon-5_19_1");
}

// 71000b65e0 — initialize struct: set id=-1, zero ptr, set flag, init sub
void FUN_71000b65e0(u32* param_1)
{
    *param_1 = 0xffffffff;
    *(u64*)(param_1 + 2) = 0;
    *(u8*)(param_1 + 4) = 1;
    FUN_71000bb5d0(param_1 + 2);
}

// 71000c5ad0 — conditional: if field@+0x90 non-null, call FUN_71000c73f0
void FUN_71000c5ad0(s64 param_1, u64 param_2, u32 param_3)
{
    if (*(s64*)(param_1 + 0x90) != 0)
        FUN_71000c73f0(*(s64*)(param_1 + 0x90), param_2, param_3 & 1);
}

// 71000c73f0 — conditional: if field@+0x18 non-null, call FUN_71000cf250
void FUN_71000c73f0(s64 param_1, u64 param_2, u32 param_3)
{
    if (*(s64*)(param_1 + 0x18) != 0)
        FUN_71000cf250(*(s64*)(param_1 + 0x18), param_2, param_3 & 1);
}

// 710014efa0 — forward 8-arg call to FUN_710014ebb0 with hardcoded arg[1]=6
void FUN_710014efa0(u64 param_1, u32 param_2, u64 param_3, u32 param_4,
                    u64 param_5, u64 param_6, u32 param_7)
{
    FUN_710014ebb0(param_1, 6, param_2, param_3, param_4, param_5, param_6, param_7);
}

// 71001579a0 — set vtable field and init sub-object
void FUN_71001579a0(s64 param_1)
{
    *(u8**)(param_1 + 0x50) = PTR_DAT_71052a3d20 + 0x10;
    FUN_71000b1cf0(param_1 + 0x58);
}

// 7100164dd0 — set vtable field and init sub-object (variant)
void FUN_7100164dd0(s64* param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5068 + 0x10);
    FUN_710013baa0(param_1 + 0xb);
}

// 7100175220 — return FUN_7100181380() if both inner fields are set, else 0
u64 FUN_7100175220(s64 param_1)
{
    if (*(s64*)(param_1 + 0x18) != 0 && *(s8*)(param_1 + 8) != 0)
        return FUN_7100181380();
    return 0;
}

// 71001822e0 — call FUN_71001808c0 with fixed second arg 4
void FUN_71001822e0(u64 param_1)
{
    FUN_71001808c0(param_1, 4);
}

// 7100182b30 — memcpy with base+offset+param_3, limited to lower 16 bits of param_4
void FUN_7100182b30(s64 param_1, void* param_2, s32 param_3, u64 param_4)
{
    memcpy(param_2,
           (void*)(*(s64*)(param_1 + 8) + (u64)*(u16*)(param_1 + 0x14) + (s64)param_3),
           param_4 & 0xffff);
}

// 71001bd330 — zero 0x10 bytes of global DAT_71052add48
void FUN_71001bd330()
{
    memset(&DAT_71052add48, 0, 0x10);
}

// 710022b360 — call FUN_71001b4e00 with inner pointer and data address
void FUN_710022b360(u64 /*param_1*/, s64 param_2)
{
    FUN_71001b4e00(*(u64*)(param_2 + 0x18), (const char*)&DAT_71043ab5ee);
}

// 7100231560 — return FUN_71001df8c0() if field@+0x30 set, else 1
u64 FUN_7100231560(s64 param_1)
{
    if (*(s64*)(param_1 + 0x30) != 0)
        return FUN_71001df8c0();
    return 1;
}

// 710024cc10 — call FUN_71001b4e00 with "Gathering"
void FUN_710024cc10(u64 /*param_1*/, s64 param_2)
{
    FUN_71001b4e00(*(u64*)(param_2 + 0x18), "Gathering");
}

// 71002558e0 — FUN_71001aff70 on sub-object at +0x28
void FUN_71002558e0(s64 param_1, u32 param_2)
{
    FUN_71001aff70(param_1 + 0x28, &DAT_710427eedd, param_2);
}

// 7100255900 — FUN_71001aff70 on sub-object at +0xa0
void FUN_7100255900(s64 param_1, u32 param_2)
{
    FUN_71001aff70(param_1 + 0xa0, &DAT_710427eedd, param_2);
}

// 7100255920 — FUN_71001aff70 on sub-object at +0x50
void FUN_7100255920(s64 param_1, u16 param_2)
{
    FUN_71001aff70(param_1 + 0x50, &DAT_710427eedd, (u32)param_2);
}

// 710058b1d0 — vtable dispatch: call vt[0xc0/8](this)
void FUN_710058b1d0(s64* param_1)
{
    (*(void(**)(s64*))(*(s64*)param_1 + 0xc0))(param_1);
}

// ---- Register-passthrough wrappers (x0 = *param_1, x1/x2 pass-through) ----

// 71002b3860
void FUN_71002b3860(u64* param_1)
{
    FUN_71002b8120((s64)*param_1);
}

// 71002b3880
void FUN_71002b3880(u64* param_1)
{
    FUN_71002b8140((s64)*param_1);
}

// 71002b38a0 — passes x1,x2 from caller as-is to FUN_71002b8160
void FUN_71002b38a0(u64* param_1, u32 param_2, u32 param_3)
{
    FUN_71002b8160((s64)*param_1, param_2, param_3);
}

// 71002b38e0 — passes x1,x2 from caller as-is to FUN_71002b8450
void FUN_71002b38e0(u64* param_1, u32 param_2, s32 param_3)
{
    FUN_71002b8450((s64)*param_1, param_2, param_3);
}

// ---- __throw_out_of_range thunks -----------------------------------------

// 71005071d0 — move x1 to x0, call FUN_71039c0d80
[[noreturn]] void FUN_71005071d0(u64 /*x0_ignored*/, u64 param_x1)
{
    FUN_71039c0d80(param_x1);
}

// 71004af3f0 — forward x0 to FUN_71039c0d80
[[noreturn]] void FUN_71004af3f0(u64 param_1)
{
    FUN_71039c0d80(param_1);
}

// ---- Complex lookup ---------------------------------------------------------

// 71001e0900 — language/locale lookup: check flag, index into array or return default
u16 FUN_71001e0900()
{
    if (*(u8*)PTR_DAT_71052a3da8 == 0)
        return *(u16*)DAT_71052b4278;
    u32* puVar1 = (u32*)FUN_7101717b00(*(u64*)PTR_DAT_71052a3db8);
    if (*puVar1 != 0)
        return *(u16*)(DAT_71052b4270 + (u64)*puVar1 * 2);
    return *(u16*)DAT_71052b4278;
}
