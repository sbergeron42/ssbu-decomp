#include "types.h"

// pool-d: OS threading / mutex / fiber stub functions (<=64B, EASY tier)
// Most 16B nnos-dispatch stubs call through PTR_ function pointer tables.
// The auto-generable and clearly-decompilable ones are below.

#define VT(m) (*reinterpret_cast<void***>(m))
struct LargeRet { u64 a, b, c; };

// ---------------------------------------------------------------------------
// app::lua_bind -- GimmickEvent l2c table dispatchers
// ---------------------------------------------------------------------------
// These were already decompiled in their own files; included here only if
// the standalone files are absent from the build.  Compilation is guarded by
// their existing files, so this block is empty intentionally.

// ---------------------------------------------------------------------------
// nn::pia::common::Crypto::GetBlockSize
// 0x71000b5090  48B  -- return 16 if param==1 (AES block), else 0
// ---------------------------------------------------------------------------
u32 GetBlockSize_b5090(int p) {
    return (u32)(p == 1) << 4;
}

// ---------------------------------------------------------------------------
// nn::nex::MatchmakeSessionSearchCriteria::SetExcludeLocked
// 0x7100255b10  16B  -- store low bit of param_2 at +0xc9
// ---------------------------------------------------------------------------
void SetExcludeLocked_255b10(long obj, u8 val) {
    *reinterpret_cast<u8*>(obj + 0xc9) = val & 1u;
}

// ---------------------------------------------------------------------------
// phx::Fiber::Fiber() — zero the vtable pointer
// 0x710353c200  8B
// ---------------------------------------------------------------------------
void Fiber_353c200(void* p) { *(u64*)p = 0; }

// ---------------------------------------------------------------------------
// nn::os::Mutex::~Mutex() — tail call to FinalizeMutex
// 0x71037c9250  4B
// ---------------------------------------------------------------------------
extern "C" void FUN_71039c0460();
void dtor_Mutex_37c9250(void*) { FUN_71039c0460(); }
