#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-009
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct Fighter;

extern "C" void FUN_71026084c0(u64);

namespace app {
    namespace FighterSpecializer_Rockman {
        void set_leafshield(BattleObjectModuleAccessor *, s64);
    }
    namespace WeaponSpecializer_ShizueFishingrod {
        void enable_search(BattleObjectModuleAccessor *, s64);
    }
    namespace FighterSpecializer_Brave {
        void special_lw_close_window(Fighter *, s64, s64, s64);
    }
}

// ---- lua_bind wrappers -----------------------------------------------

// 0x71021456d4 — ldr x0,[x8]; bl FUN_71026084c0; store x10 (32 bytes)
// 0x7102192724 — FighterSpecializer_Rockman::set_leafshield (32 bytes)
// 0x71021b67b0 — FighterSpecializer_Brave::special_lw_close_window (32 bytes)
// ---- ctor_dtor_small: WorkModule flag setters -----------------------------------------------
// Pattern: plVar1=*(*(*(param_1-8)+0x1a0)+0x68); lVar2=vtable[0x60](plVar1,idx);
//          *(u8*)(lVar2+off)=val; return 0
// Access: param_1 (x0) is lua state, *(x0-8) navigates to WorkModule via +0x1a0/+0x68

