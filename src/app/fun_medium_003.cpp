#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100b000-0x71001500000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3d28;
extern void* PTR_DAT_71052a3ee8;

// SDK thread type (opaque)
struct ThreadType;
namespace nn { namespace os { void StartThread(ThreadType**); } }

extern "C" void FUN_71000bce50(u64, u32*);
