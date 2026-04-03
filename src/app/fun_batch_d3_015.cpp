#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-015
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void *memset(void *, int, u64);

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
    namespace os {
        void InitializeMutex(void *, bool, int);
    }
    namespace pia { namespace common {
        struct Time { static void SetNow(void *); };
    } }
}

// ---- Functions ---------------------------------------------------------------
// 0x71000b4140 — empty dtor: ~CallContext (16 bytes)
void FUN_71000b4140(void)
{
}
// 0x71000b4160 — InitiateCall: set result=1, clear pending byte, return 1 (32 bytes)
u64 FUN_71000b4160(u32 *param_1)
{
    *param_1 = 1;
    *(u8 *)(param_1 + 10) = 0;
    return 1;
}
// FUN_71000b71c0 — deduped to fun_medium_003.cpp

// 0x71000b7080 — ListBase::Init: self-referential circular list init (16 bytes)
void FUN_71000b7080(s64 param_1)
{
    *(s64 *)param_1 = param_1;
    *(s64 *)(param_1 + 8) = param_1;
    *(u32 *)(param_1 + 0x10) = 0;
}

// 0x71000b8870 — GetSerializedSize: return 0x10 (16 bytes)
u64 FUN_71000b8870(void)
{
    return 0x10;
}

// 0x71000b8bc0 — GetSerializedSize: return 0x10 (16 bytes)
u64 FUN_71000b8bc0(void)
{
    return 0x10;
}
// 0x71000b9f50 — empty dtor: ~Socket (16 bytes)
void FUN_71000b9f50(void)
{
}
// 0x71000bae40 — GetBuffer: return ptr at +8 (16 bytes)
u64 FUN_71000bae40(s64 param_1)
{
    return *(u64 *)(param_1 + 8);
}
