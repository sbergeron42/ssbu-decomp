#include "types.h"

// placement new
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

// MEDIUM-tier FUN_* functions -- mixed address range, batch 21
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// nn::err types
namespace nn {
namespace err {
    struct Result { u32 m_Value; };
    struct ErrorResultVariant {
        ErrorResultVariant();
        ErrorResultVariant& operator=(const Result&);
    };
}
}

// pead::ThreadMgr
namespace pead {
namespace ThreadMgr {
    void initMainThread_(u64, u64);
}
}

// External C functions
extern "C" void FUN_7100134e10(u8*);
extern "C" void FUN_710013c400(u64);
extern "C" void FUN_71000bce50(u32*, u32*);

// External data
extern u8  PTR_s_Initialized_71052a2bf0[];
extern u8  PTR_DAT_71052a2bf8[];
extern u8  PTR_sRootHeaps_71052a2c00[];
extern u8  PTR_sInstance_71052a2c08[];
extern u8  PTR_s_CurrentHeapId_71052a2c10[];

// ---- nn::err dispatch helpers (switch → ErrorResultVariant) ---------------

// 71000b9d40 -- map curl/socket error code → nn::err result variant
void FUN_71000b9d40(u64 param_1, u32 param_2)
{
    u32 local_38[4];
    nn::err::Result local_28[2];

    switch (param_2) {
    default:
        local_38[0] = 0x10c08;
        break;
    case 4:
    case 0xb:
    case 0xc:
    case 0x10:
    case 0x69:
        local_38[0] = 0x4c0d;
        break;
    case 9:
    case 0x16:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5f:
    case 0x61:
    case 99:
        local_38[0] = 0x10c07;
        break;
    case 0x20:
    case 100:
    case 0x65:
    case 0x68:
    case 0x6b:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
        local_38[0] = 0xc406;
    }
    new ((void*)((u64)local_38 | 4)) nn::err::ErrorResultVariant();
    local_28[0].m_Value = 0;
    ((nn::err::ErrorResultVariant*)((u64)local_38 | 4))->operator=(local_28[0]);
    FUN_71000bce50((u32*)&param_1, local_38);
}

// 71000b9de0 -- smaller case set variant of FUN_71000b9d40
void FUN_71000b9de0(u64 param_1, u32 param_2)
{
    u32 local_38[4];
    nn::err::Result local_28[2];

    switch (param_2) {
    case 4:
    case 0xb:
    case 0xc:
    case 0x10:
        local_38[0] = 0x2c09;
        break;
    default:
        local_38[0] = 0x10c08;
        break;
    case 9:
    case 0x16:
    case 0x58:
    case 0x5a:
    case 0x5f:
    case 0x61:
        local_38[0] = 0x10c07;
        break;
    case 100:
    case 0x68:
    case 0x6b:
    case 0x6e:
        local_38[0] = 0xc406;
    }
    new ((void*)((u64)local_38 | 4)) nn::err::ErrorResultVariant();
    local_28[0].m_Value = 0;
    ((nn::err::ErrorResultVariant*)((u64)local_38 | 4))->operator=(local_28[0]);
    FUN_71000bce50((u32*)&param_1, local_38);
}

// 71000b9e80 -- alternate case set variant (adds 0x62/0x5c/0x5d)
void FUN_71000b9e80(u64 param_1, u32 param_2)
{
    u32 local_38[4];
    nn::err::Result local_28[2];

    switch (param_2) {
    default:
        local_38[0] = 0x10c08;
        break;
    case 9:
    case 0x16:
    case 0x58:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5f:
    case 0x61:
    case 99:
        local_38[0] = 0x10c07;
        break;
    case 0x10:
        local_38[0] = 0x4c0d;
        break;
    case 0x62:
        local_38[0] = 0xc35;
        break;
    case 100:
    case 0x68:
    case 0x6b:
    case 0x6e:
        local_38[0] = 0xc406;
    }
    new ((void*)((u64)local_38 | 4)) nn::err::ErrorResultVariant();
    local_28[0].m_Value = 0;
    ((nn::err::ErrorResultVariant*)((u64)local_38 | 4))->operator=(local_28[0]);
    FUN_71000bce50((u32*)&param_1, local_38);
}

// ---- ErrorResultVariant constructor + comparison helper ------------------

// 71000bce50 -- construct variant, compare against two known codes, copy or clear
void FUN_71000bce50(u32* param_1, u32* param_2)
{
    nn::err::Result local_58[4];
    nn::err::Result local_48[4];
    nn::err::Result local_38[2];

    nn::err::ErrorResultVariant* erv = (nn::err::ErrorResultVariant*)(param_1 + 1);
    *param_1 = *param_2;
    new (erv) nn::err::ErrorResultVariant();
    local_48[0].m_Value = 0xe437;
    new ((void*)((u64)local_48 | 4)) nn::err::ErrorResultVariant();
    local_58[0].m_Value = 0;
    ((nn::err::ErrorResultVariant*)((u64)local_48 | 4))->operator=(local_58[0]);
    if (*param_2 != local_48[0].m_Value) {
        local_58[0].m_Value = 0xa46e;
        new ((void*)((u64)local_58 | 4)) nn::err::ErrorResultVariant();
        local_38[0].m_Value = 0;
        ((nn::err::ErrorResultVariant*)((u64)local_58 | 4))->operator=(local_38[0]);
        if (*param_2 != local_58[0].m_Value) {
            local_48[0].m_Value = 0;
            erv->operator=(local_48[0]);
            return;
        }
    }
    u64 uVar1 = *(u64*)(param_2 + 1);
    param_1[3] = param_2[3];
    *(u64*)erv = uVar1;
}

// ---- pead system init ----------------------------------------------------

// 71000b1960 -- one-shot init: store params, init heap chain, set flags
u64 FUN_71000b1960(u64 param_1, u64 param_2)
{
    u8* puVar2 = PTR_DAT_71052a2bf8;
    u8* puVar1 = PTR_s_Initialized_71052a2bf0;
    if (*PTR_s_Initialized_71052a2bf0 != '\0') {
        return 0;
    }
    *(u64*)PTR_DAT_71052a2bf8 = param_1;
    *(u64*)(puVar2 + 8) = param_2 & 0xffffffff;
    FUN_7100134e10(puVar2);
    u64 uVar3;
    if (*(s32*)PTR_sRootHeaps_71052a2c00 == 0) {
        uVar3 = 0;
    } else {
        uVar3 = **(u64**)(PTR_sRootHeaps_71052a2c00 + 8);
    }
    FUN_710013c400(uVar3);
    pead::ThreadMgr::initMainThread_(*(u64*)PTR_sInstance_71052a2c08, uVar3);
    *puVar1 = 1;
    *(u32*)PTR_s_CurrentHeapId_71052a2c10 = 0x19;
    return 1;
}
