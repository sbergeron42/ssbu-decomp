#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-018
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

namespace nn {
    namespace os {
        void WaitEvent(void *);
        void ClearEvent(void *);
        void SendMessageQueue(void *, u64);
        void JamMessageQueue(void *, u64);
    }
    namespace pia { namespace common {
        struct CriticalSection {
            static void Lock(void *);
            static void Unlock(void *);
        };
    } }
}

// ---- Functions ---------------------------------------------------------------
