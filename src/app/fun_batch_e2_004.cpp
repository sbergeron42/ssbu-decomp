#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e2-004
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_710347cff0(u64);
extern "C" void FUN_710348cc70(u64);
extern "C" u64  FUN_71037223f0(s64);
extern "C" u64  FUN_7103721ea0(s64, u8);

namespace nn {
    namespace nfp {
        struct DeviceHandle;
        struct ApplicationAreaCreateInfo;
        s64 StartDetection(DeviceHandle *);
        s64 StopDetection(DeviceHandle *);
        s64 Mount(DeviceHandle *, s32);
        s64 Unmount(DeviceHandle *);
        s64 Flush(DeviceHandle *);
        s64 Restore(DeviceHandle *);
        s64 CreateApplicationArea(DeviceHandle *, ApplicationAreaCreateInfo *);
    }
}

// ---- nn::nfp wrappers -----------------------------------------------
// Pattern: add x0,x0,#0x84; bl nn::nfp::XXX; and x0,x0,#0xffffffff; ldp; ret

// ---- simple forwarders -----------------------------------------------

// ---- struct getters (stack-spill pattern, 24-28 bytes each) -----------------------------------------------
// Note: original uses sub/str/ldr/add stack spill — compiles correctly, may not verify

