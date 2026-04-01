#include "types.h"

struct GimmickEventPresenter;
struct GimmickEvent;

extern "C" void FUN_710315f230(u64);
// Pointer-to-pointer to StageManager at 0x71053299d8
// adrp x8,0x7105329000 + ldr x8,[x8,#0x9d8]  →  load P from 0x71053299d8
// then ldr x8,[x8] → load stage manager object from P
extern u8 DAT_71053299d8;

namespace app::lua_bind {

// 71021453e0: adrp x8; ldr x8,[x8,#0x9d8] (load ptr P from 0x71053299d8);
//             ldr x8,[x8] (load mgr M=*P); ldr x0,[x8,#0x1e0]; b FUN_710315f230
// Must use naked asm — fPIC would otherwise emit GOT indirection (6 insns vs 5)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void GimmickEventPresenter__dispatch_event_from_fighter_impl(GimmickEventPresenter*, GimmickEvent*) {
    asm(
        "adrp x8, DAT_71053299d8\n"
        "ldr x8, [x8, :lo12:DAT_71053299d8]\n"
        "ldr x8, [x8]\n"
        "ldr x0, [x8, #0x1e0]\n"
        "b FUN_710315f230\n"
    );
}
#endif

} // namespace app::lua_bind
