#include "types.h"

// pool-d: heap / allocator stub functions (<=64B, EASY tier)
// Functions that access global heap pointers (SetStaticHeap, GetDynamicHeap, etc.)
// require linker-placed globals and are left for a later pass.

// ---------------------------------------------------------------------------
// nn::gfx::detail::MemoryPoolImpl dtor noop
// 0x7100033910  16B
// ---------------------------------------------------------------------------
void dtor_MemoryPoolImpl_33910(void*) { }

// ---------------------------------------------------------------------------
// GetRequiredMemorySize noop stubs
// 0x7100039590  16B
// 0x000000710003a610  16B
// ---------------------------------------------------------------------------
// 0x7100039590  16B  BlendStateImpl::GetRequiredMemorySize — byte field << 3
u64 GetRequiredMemorySize_39590(u8* p) {
    return (u64)*p << 3;
}

// 0x7100039e10  32B  ViewportScissorStateImpl::GetRequiredMemorySize — (viewport_count - 1) * 0x28
long GetRequiredMemorySize_39e10(long p) {
    return (u64)*reinterpret_cast<u16*>(p + 2) * 0x28 - 0x28;
}

// 0x000000710003a610  16B  (other GetRequiredMemorySize stub)
// 710003a610
void GetRequiredMemorySize_3a610(void*) { }

// ---------------------------------------------------------------------------
// nn::gfx::detail::MemoryPoolImpl::GetPoolMemorySizeGranularity
// 0x71000338e0  16B  — always returns 0x1000 (4 KiB page granularity)
// ---------------------------------------------------------------------------
u64 GetPoolMemorySizeGranularity_338e0(void*) {
    return 0x1000;
}
