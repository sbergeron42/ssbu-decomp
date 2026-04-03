#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-013
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    u64 strlen(const char *);
    char *strncpy(char *, const char *, u64);
}

// External data
extern u8 PTR_DAT_71052a37b0[] HIDDEN;

// External FUN_* forward declarations
extern s8  *FUN_7100048db0(u64);

namespace nn { namespace util {
    int SNPrintf(char *, s64, const char *, ...);
} }
