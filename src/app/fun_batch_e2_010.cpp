#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-010
// Pool-e worker: auto-generated from Ghidra decompilation
// Pattern: WorkModule flag setters — *(*(*(param_1-8)+0x1a0)+0x68) vtable dispatch

// Macro helper for readability (not used, but documents the pattern):
// plVar1 = *(*(*(param_1-8)+0x1a0)+0x68); lVar2 = vtable[0x60](plVar1,idx); *(u8*)(lVar2+off)=val

