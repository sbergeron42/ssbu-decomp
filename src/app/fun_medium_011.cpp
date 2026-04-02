#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 12
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" char* strncpy(char*, const char*, u64);

// nn namespaces
namespace nn {
namespace ldn {
    u32 OpenStation();
}
}

// External C functions
extern "C" void  FUN_71001531c0(s64*);
extern "C" void  FUN_7100156390(s64*);
extern "C" void  FUN_710014c900(s64*);
extern "C" void  FUN_71001b4200(u64, u32*);
extern "C" void  FUN_71001b4940(u64, u64, u64);
extern "C" void  FUN_71001b2f70(s64);
extern "C" void  FUN_71000be960(u64*);
extern "C" void  FUN_71001f2a80(void*, u64, const char*, u64);
extern "C" void  FUN_710016b2f0(u64, u32, u32*);
extern "C" u32   FUN_710024fb10(s64, u64, u32*);
extern "C" u32   FUN_710024ff60(s64, u64, u32*);
extern "C" u32   FUN_7100250180(s64, u64, u64*);
extern "C" u32   FUN_7100250a20(s64, u64, u32*);
extern "C" u32   FUN_7100251f10(s64, u64, u32*);
extern "C" u32   FUN_7100252330(s64, u64, u32*);

// External data
extern u8  PTR_DAT_71052a4fc8[];
extern u8  PTR_DAT_71052a50a8[];
extern u8  PTR_DAT_71052a5288[];
extern u8  PTR_DAT_71052a56c8[];
extern u8  DAT_710449be27;
extern u8  DAT_710449be2b;
extern u8  DAT_710449be2f;
extern u8  DAT_710449be3e;
extern u8  DAT_710449be43;
extern u8  DAT_710449be52;
extern u8  DAT_710449be57;
extern u8  DAT_710449be5b;
extern u8  DAT_710449be6f;
extern u8  DAT_710449be76;
extern u8  DAT_710449be79;

// ---- Vtable init helpers (save x0, call sub, overwrite *param_1) ----------

// 71001941b0 -- call FUN_71001531c0(param_1), set *param_1 = PTR+0x10
void FUN_71001941b0(s64* param_1)
{
    FUN_71001531c0(param_1);
    *param_1 = (s64)(PTR_DAT_71052a56c8 + 0x10);
}

// 71001793a0 -- call FUN_710014c900(param_1), set *param_1 = PTR+0x10
__attribute__((noinline)) void FUN_71001793a0(s64* param_1)
{
    FUN_710014c900(param_1);
    *param_1 = (s64)(PTR_DAT_71052a5288 + 0x10);
}

// 7100167c50 -- call FUN_71001793a0(param_1), set *param_1 = PTR+0x10
void FUN_7100167c50(s64* param_1)
{
    FUN_71001793a0(param_1);
    *param_1 = (s64)(PTR_DAT_71052a50a8 + 0x10);
}

// 7100159ae0 -- call FUN_7100156390(param_1), set *param_1 = PTR+0x10
void FUN_7100159ae0(s64* param_1)
{
    FUN_7100156390(param_1);
    *param_1 = (s64)(PTR_DAT_71052a4fc8 + 0x10);
}

// ---- FUN_71001b4200 wrappers (push local constant, call with &local) ------

// 71001e0870 -- signal event 0x80010002
void FUN_71001e0870(u64 param_1)
{
    u32 local_14 = 0x80010002;
    FUN_71001b4200(param_1, &local_14);
}

// 71001e08a0 -- same body as FUN_71001e0870
void FUN_71001e08a0(u64 param_1)
{
    u32 local_14 = 0x80010002;
    FUN_71001b4200(param_1, &local_14);
}

// 71001e08d0 -- same body as FUN_71001e0870
void FUN_71001e08d0(u64 param_1)
{
    u32 local_14 = 0x80010002;
    FUN_71001b4200(param_1, &local_14);
}

// 710023bd10 -- same body as FUN_71001e0870
void FUN_710023bd10(u64 param_1)
{
    u32 local_14 = 0x80010002;
    FUN_71001b4200(param_1, &local_14);
}

// 710023bd40 -- same body as FUN_71001e0870
void FUN_710023bd40(u64 param_1)
{
    u32 local_14 = 0x80010002;
    FUN_71001b4200(param_1, &local_14);
}

// 7100246560 -- signal event 0x80050001
void FUN_7100246560(u64 param_1)
{
    u32 local_14 = 0x80050001;
    FUN_71001b4200(param_1, &local_14);
}

// 7100246590 -- same body as FUN_7100246560
void FUN_7100246590(u64 param_1)
{
    u32 local_14 = 0x80050001;
    FUN_71001b4200(param_1, &local_14);
}

// ---- FUN_71001f4480/44b0 -- store field + signal 0x10001 ------------------

// 71001f4480 -- store param_3 to param_2+0xb0, then signal 0x10001
void FUN_71001f4480(u64 param_1, s64 param_2, u32 param_3)
{
    u32 local_14 = 0x10001;
    *(u32*)(param_2 + 0xb0) = param_3;
    FUN_71001b4200(param_1, &local_14);
}

// 71001f44b0 -- store param_3 to param_2+0xb8, then signal 0x10001
void FUN_71001f44b0(u64 param_1, s64 param_2, u32 param_3)
{
    u32 local_14 = 0x10001;
    *(u32*)(param_2 + 0xb8) = param_3;
    FUN_71001b4200(param_1, &local_14);
}

// ---- FUN_71001f2a80 wrappers (24-byte stack buf + key/value) --------------

// 71001e78c0
void FUN_71001e78c0(u64 param_1, u64 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be79, param_2 & 1);
}

// 71001e79e0
void FUN_71001e79e0(u64 param_1, u16 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be6f, (u64)param_2);
}

// 71001e8160
void FUN_71001e8160(u64 param_1, u32 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, "RVCID", (u64)param_2);
}

// 71001ebd60
void FUN_71001ebd60(u64 param_1, u64 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, "probeinit", param_2 & 1);
}

// 71001ebe80
void FUN_71001ebe80(u64 param_1, u16 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be76, (u64)param_2);
}

// 71001ee9d0
void FUN_71001ee9d0(u64 param_1, u32 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, "stream", (u64)param_2);
}

// 71001eea00
void FUN_71001eea00(u64 param_1, u8 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be27, (u64)param_2);
}

// 71001f1c60
void FUN_71001f1c60(u64 param_1, u64 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be2b, param_2);
}

// 71001f2d30
void FUN_71001f2d30(u64 param_1, u32 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be2f, (u64)param_2);
}

// 71001f2d60
void FUN_71001f2d60(u64 param_1, u32 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be3e, (u64)param_2);
}

// 71001f2e00
void FUN_71001f2e00(u64 param_1, u64 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be52, param_2 & 1);
}

// 71001f2e30
void FUN_71001f2e30(u64 param_1, u64 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be57, param_2 & 1);
}

// 71001f2e60
void FUN_71001f2e60(u64 param_1, u32 param_2)
{
    u8 auStack_28[24];
    FUN_71001f2a80(auStack_28, param_1, (const char*)&DAT_710449be5b, (u64)param_2);
}

// ---- FUN_710024*_param_1+0x140 wrappers -----------------------------------
// Pattern: store param_3 to stack-local, call fn(param_1+0x140, param_2, &local)

// 710024dfc0
u32 FUN_710024dfc0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 local_14 = param_3;
    return FUN_710024fb10(param_1 + 0x140, param_2, &local_14) & 1;
}

// 710024ff30
u32 FUN_710024ff30(s64 param_1, u64 param_2, u32 param_3)
{
    u32 local_14 = param_3;
    return FUN_710024ff60(param_1 + 0x140, param_2, &local_14) & 1;
}

// 7100250150 -- u64 local variant
u32 FUN_7100250150(s64 param_1, u64 param_2, u64 param_3)
{
    u64 local_18 = param_3;
    return FUN_7100250180(param_1 + 0x140, param_2, &local_18) & 1;
}

// 71002509f0
u32 FUN_71002509f0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 local_14 = param_3;
    return FUN_7100250a20(param_1 + 0x140, param_2, &local_14) & 1;
}

// 7100251ee0
u32 FUN_7100251ee0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 local_14 = param_3;
    return FUN_7100251f10(param_1 + 0x140, param_2, &local_14) & 1;
}

// 7100252300
u32 FUN_7100252300(s64 param_1, u64 param_2, u32 param_3)
{
    u32 local_14 = param_3;
    return FUN_7100252330(param_1 + 0x140, param_2, &local_14) & 1;
}

// ---- Misc -----------------------------------------------------------------

// 7100157cc0 -- zero first field, init sub-object, zero byte at offset
void FUN_7100157cc0(u64* param_1)
{
    *param_1 = 0;
    FUN_71000be960(param_1 + 10);
    *(u8*)(param_1 + 0xf) = 0;
}

// 71001b4dd0 -- call FUN_71001b4940 with -1 sentinel, return param_1
u64 FUN_71001b4dd0(u64 param_1, u64 param_2)
{
    FUN_71001b4940(param_1, param_2, (u64)-1);
    return param_1;
}

// 71001b5de0 -- safe strncpy with guaranteed null termination
void FUN_71001b5de0(char* param_1, char* param_2, u64 param_3)
{
    strncpy(param_2, param_1, param_3);
    param_2[param_3 - 1] = '\0';
}

// 71001dec40 -- init sub-object at +0x80, store param_3 at +0xa8
void FUN_71001dec40(s64 param_1, u64 /*param_2*/, u32 param_3)
{
    FUN_71001b2f70(param_1 + 0x80);
    *(u32*)(param_1 + 0xa8) = param_3;
}

// 710016c060 -- open LDN station, call FUN_710016b2f0
void FUN_710016c060(u64 param_1)
{
    u32 local_18[2];
    local_18[0] = nn::ldn::OpenStation();
    FUN_710016b2f0(param_1, local_18[0], local_18);
}
