#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 23
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int   __cxa_guard_acquire(u64*);
extern "C" void  __cxa_guard_release(u64*);
extern "C" void  Curl_infof(s64, const char*, ...);
extern "C" void  FUN_71000c5c20();
extern "C" void  FUN_7100189a10();

// External data
extern u8  PTR_DAT_71052a3f70[];   // vtable (FUN_71000d31d0)
extern u8  PTR_DAT_71052a3fa8[];   // vtable (FUN_71000d51e0)
extern u8  PTR_DAT_71052a28c0[];   // mid guard  (FUN_710007c720, FUN_710007b8d0)
extern u8  PTR_DAT_71052a28c8[];   // mid data   (FUN_710007c720, FUN_710007b8d0)
extern u8  PTR_DAT_71052a2890[];   // inner guard (shared)
extern u8  PTR_DAT_71052a2898[];   // inner data  (shared)
extern u8  PTR_DAT_71052a28b0[];   // outer guard (FUN_710007b8d0)
extern u8  PTR_DAT_71052a28b8[];   // outer data  (FUN_710007b8d0)

// ---- Constructor + vtable override ----------------------------------------

// 71000d31d0 -- call base ctor, zero field, set vtable 2f70
void FUN_71000d31d0(s64* param_1)
{
    FUN_71000c5c20();
    param_1[0x4b] = 0;
    *param_1 = (s64)(PTR_DAT_71052a3f70 + 0x10);
}

// 71000d51e0 -- call base ctor, set vtable 2fa8
void FUN_71000d51e0(s64* param_1)
{
    FUN_7100189a10();
    *param_1 = (s64)(PTR_DAT_71052a3fa8 + 0x10);
}

// ---- cxa_guard singletons ------------------------------------------------

// 710007c720 -- nested cxa_guard: outer 28c0/28c8, inner 2890/2898
u8* FUN_710007c720()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a28c0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a28c0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2890 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2890);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2898 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2890);
                }
            }
            *(u8**)PTR_DAT_71052a28c8 = PTR_DAT_71052a2898;
            __cxa_guard_release((u64*)PTR_DAT_71052a28c0);
        }
    }
    return PTR_DAT_71052a28c8;
}

// 710007b8d0 -- triple cxa_guard: outer 28b0/28b8 → mid 28c0/28c8 → inner 2890/2898
u8* FUN_710007b8d0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a28b0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a28b0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a28c0 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a28c0);
                if (iVar1 != 0) {
                    if ((*PTR_DAT_71052a2890 & 1) == 0) {
                        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2890);
                        if (iVar1 != 0) {
                            *(u64*)PTR_DAT_71052a2898 = 0;
                            __cxa_guard_release((u64*)PTR_DAT_71052a2890);
                        }
                    }
                    *(u8**)PTR_DAT_71052a28c8 = PTR_DAT_71052a2898;
                    __cxa_guard_release((u64*)PTR_DAT_71052a28c0);
                }
            }
            *(u8**)PTR_DAT_71052a28b8 = PTR_DAT_71052a28c8;
            __cxa_guard_release((u64*)PTR_DAT_71052a28b0);
        }
    }
    return PTR_DAT_71052a28b8;
}

// ---- Curl connection info log --------------------------------------------

// 710001eed0 -- log curl "Connected to" message with host/port details
void FUN_710001eed0(s64* param_1)
{
    if (*(s8*)(*param_1 + 0x6c8) == '\0') {
        return;
    }
    s64* plVar1;
    if (*(s8*)((s64)param_1 + 0x817) == '\0') {
        if (*(s8*)((s64)param_1 + 0x816) == '\0') {
            plVar1 = param_1 + 0x1c;
            if (*(s8*)((s64)param_1 + 0x813) != '\0') {
                plVar1 = param_1 + 0x21;
            }
        } else {
            plVar1 = param_1 + 0x2d;
        }
    } else {
        plVar1 = param_1 + 0x25;
    }
    Curl_infof(*param_1, "Connected to %s (%s) port %ld (#%ld)\n",
               *plVar1, param_1 + 0x12, param_1[0x32], param_1[0xd]);
}
