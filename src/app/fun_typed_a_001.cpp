// fun_typed_a_001.cpp — HARD-tier destructors and utility functions
// Worker pool-a: 30 functions across 8 structural patterns

#include "types.h"

// --- External function declarations ---
extern "C" {
    void jeFree_710392e590(void*);     // free_default
    void FUN_71032ca770(void*);     // free_state_function
    void FUN_71013c66e0(void*);     // base destructor
    void FUN_71039c2140(void*);     // ~__shared_weak_count
    void FUN_71006307f0(void*, u32, void*, void*, u64);
    u64  FUN_71039bfac0(const char*); // strlen

    // Pattern A cleanup functions
    void FUN_710137c8e0(void*);
    void FUN_71013b9a90(void*);
    void FUN_710143ebe0(void*);
    void FUN_710149a8d0(void*);
    void FUN_7101465760(void*);

    // Pattern B1 cleanup functions
    void FUN_71013d0130(void*);
    void FUN_71013dd730(void*);
    void FUN_71013e0d90(void*);
    void FUN_71013e70c0(void*);

    // Pattern E cleanup functions
    void FUN_7101473f30(void*);
    void FUN_710146bd70(void*);
    void FUN_7101468040(void*);
    void FUN_710148ff30(void*);
    void FUN_71014a44c0(void*);

    // Pattern D extra cleanup
    void FUN_71015336e0(void*);
}

// --- Data symbols (hidden visibility for direct adrp+add, not GOT) ---
#define DATA_SYM(name) extern "C" __attribute__((visibility("hidden"))) char name[]

// Pattern A vtables
DATA_SYM(DAT_7105062450);  // FUN_710137c890
DATA_SYM(DAT_7105062970);  // FUN_710138a6c0
DATA_SYM(DAT_7105066c20);  // FUN_710143eb90
DATA_SYM(DAT_7105068cd0);  // FUN_710149c420
DATA_SYM(DAT_71050676d8);  // FUN_71014659e0
// Pattern B vtables
DATA_SYM(DAT_7105062d00);  // FUN_710138d100
DATA_SYM(DAT_7105062e80);  // FUN_710138f170
DATA_SYM(DAT_7105063260);  // FUN_7101397380
DATA_SYM(DAT_71050636e0);  // FUN_71013a4520
DATA_SYM(DAT_71050637a0);  // FUN_71013a4bd0
DATA_SYM(DAT_7105063860);  // FUN_71013a7fe0
DATA_SYM(DAT_71050641a8);  // FUN_71013cc370
DATA_SYM(DAT_7105064388);  // FUN_71013d0250
DATA_SYM(DAT_71050646e8);  // FUN_71013ddbc0
DATA_SYM(DAT_7105064868);  // FUN_71013e12b0
DATA_SYM(DAT_7105064b68);  // FUN_71013e7810
// Pattern C vtable
DATA_SYM(DAT_7105063a70);  // ~WorkModule, ~~WorkModule
// Pattern E vtables (dual per function)
DATA_SYM(DAT_71050674e8);  DATA_SYM(DAT_7105067da0);  // FUN_7101461660
DATA_SYM(DAT_7105067130);  DATA_SYM(DAT_7105067a20);  // FUN_71014621e0
DATA_SYM(DAT_71050670f8);  DATA_SYM(DAT_7105067800);  // FUN_71014622c0
DATA_SYM(DAT_7105067018);  DATA_SYM(DAT_71050686c0);  // FUN_7101462580
DATA_SYM(DAT_7105068e70);  DATA_SYM(DAT_7105068ee8);  // FUN_71014a3780
// Pattern F vtable
DATA_SYM(DAT_7105065db0);  // FUN_7101424f30
// Pattern H callback addresses
DATA_SYM(DAT_7100647a70);  DATA_SYM(DAT_710064b200);

namespace app::lua_bind {

// =====================================================================
// Pattern A: Destructor — vtable at [0], member at [1], cleanup + free
// =====================================================================

// 0x710137c890
void FUN_710137c890(u64* p) {
    u64 old = p[1];
    p[0] = (u64)DAT_7105062450;
    p[1] = 0;
    if (old) {
        FUN_710137c8e0((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// 0x710138a6c0
void FUN_710138a6c0(u64* p) {
    u64 old = p[1];
    p[0] = (u64)DAT_7105062970;
    p[1] = 0;
    if (old) {
        FUN_71013b9a90((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// 0x710143eb90
void FUN_710143eb90(u64* p) {
    u64 old = p[1];
    p[0] = (u64)DAT_7105066c20;
    p[1] = 0;
    if (old) {
        FUN_710143ebe0((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// 0x710149c420
void FUN_710149c420(u64* p) {
    u64 old = p[1];
    p[0] = (u64)DAT_7105068cd0;
    p[1] = 0;
    if (old) {
        FUN_710149a8d0((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// 0x71014659e0
void FUN_71014659e0(u64* p) {
    u64 old = p[1];
    p[0] = (u64)DAT_71050676d8;
    p[1] = 0;
    if (old) {
        FUN_7101465760((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// Pattern B1: Destructor — vtable at [0], member at [10], cleanup + base dtor
// =====================================================================

// 0x71013d0250
void FUN_71013d0250(u64* p) {
    u64 old = p[10];
    p[0] = (u64)DAT_7105064388;
    p[10] = 0;
    if (old) {
        FUN_71013d0130((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71013c66e0(p);
}

// 0x71013ddbc0
void FUN_71013ddbc0(u64* p) {
    u64 old = p[10];
    p[0] = (u64)DAT_71050646e8;
    p[10] = 0;
    if (old) {
        FUN_71013dd730((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71013c66e0(p);
}

// 0x71013e12b0
void FUN_71013e12b0(u64* p) {
    u64 old = p[10];
    p[0] = (u64)DAT_7105064868;
    p[10] = 0;
    if (old) {
        FUN_71013e0d90((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71013c66e0(p);
}

// 0x71013e7810
void FUN_71013e7810(u64* p) {
    u64 old = p[10];
    p[0] = (u64)DAT_7105064b68;
    p[10] = 0;
    if (old) {
        FUN_71013e70c0((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71013c66e0(p);
}

// =====================================================================
// Pattern B2: Destructor — nested ptr cleanup (old+8) + base dtor
// =====================================================================

// 0x710138d100
void FUN_710138d100(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_7105062d00;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x710138f170
void FUN_710138f170(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_7105062e80;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x7101397380
void FUN_7101397380(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_7105063260;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x71013a4520
void FUN_71013a4520(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_71050636e0;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x71013a4bd0
void FUN_71013a4bd0(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_71050637a0;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x71013a7fe0
void FUN_71013a7fe0(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_7105063860;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// 0x71013cc370
void FUN_71013cc370(u64* p) {
    void* old = (void*)p[10];
    p[0] = (u64)DAT_71050641a8;
    p[10] = 0;
    if (old) {
        void* nested = *(void**)((u8*)old + 8);
        *(u64*)((u8*)old + 8) = 0;
        if (nested) FUN_71032ca770(nested);
        jeFree_710392e590(old);
    }
    FUN_71013c66e0(p);
}

// =====================================================================
// Pattern C: Linked list walk destructor (~WorkModule)
// =====================================================================

// 0x71013aad40
void FUN_71013aad40(u64* p) {
    p[0] = (u64)DAT_7105063a70;
    u64* cur = (u64*)p[3];
    while (cur) {
        u64* next = (u64*)cur[0];
        jeFree_710392e590(cur);
        cur = next;
    }
    void* member = (void*)p[1];
    p[1] = 0;
    if (member) {
        jeFree_710392e590(member);
    }
}

// 0x71013aada0
void FUN_71013aada0(u64* p) {
    p[0] = (u64)DAT_7105063a70;
    u64* cur = (u64*)p[3];
    while (cur) {
        u64* next = (u64*)cur[0];
        jeFree_710392e590(cur);
        cur = next;
    }
    void* member = (void*)p[1];
    p[1] = 0;
    if (member) {
        jeFree_710392e590(member);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// Pattern D: Recursive binary tree delete
// =====================================================================

// 0x71014106f0
void FUN_71014106f0(u64* node) {
    if (!node) return;
    FUN_71014106f0((u64*)node[0]);
    FUN_71014106f0((u64*)node[1]);
    jeFree_710392e590(node);
}

// 0x7101468100
void FUN_7101468100(u64* node) {
    if (!node) return;
    FUN_7101468100((u64*)node[0]);
    FUN_7101468100((u64*)node[1]);
    jeFree_710392e590(node);
}

// 0x71014879e0
void FUN_71014879e0(u64* node) {
    if (!node) return;
    FUN_71014879e0((u64*)node[0]);
    FUN_71014879e0((u64*)node[1]);
    jeFree_710392e590(node);
}

// 0x71015336a0
void FUN_71015336a0(u64* node) {
    if (!node) return;
    FUN_71015336a0((u64*)node[0]);
    FUN_71015336a0((u64*)node[1]);
    FUN_71015336e0((void*)(node + 5));
    jeFree_710392e590(node);
}

// =====================================================================
// Pattern E: shared_ptr destructor (dual vtable + base ~__shared_weak_count)
// =====================================================================

// 0x7101461660
void FUN_7101461660(u64* p) {
    u64 old = p[5];
    p[0] = (u64)DAT_71050674e8;
    p[3] = (u64)DAT_7105067da0;
    p[5] = 0;
    if (old) {
        FUN_7101473f30((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71039c2140(p);
}

// 0x71014621e0
void FUN_71014621e0(u64* p) {
    u64 old = p[5];
    p[0] = (u64)DAT_7105067130;
    p[3] = (u64)DAT_7105067a20;
    p[5] = 0;
    if (old) {
        FUN_710146bd70((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71039c2140(p);
}

// 0x71014622c0
void FUN_71014622c0(u64* p) {
    u64 old = p[5];
    p[0] = (u64)DAT_71050670f8;
    p[3] = (u64)DAT_7105067800;
    p[5] = 0;
    if (old) {
        FUN_7101468040((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71039c2140(p);
}

// 0x7101462580
void FUN_7101462580(u64* p) {
    u64 old = p[5];
    p[0] = (u64)DAT_7105067018;
    p[3] = (u64)DAT_71050686c0;
    p[5] = 0;
    if (old) {
        FUN_710148ff30((void*)old);
        jeFree_710392e590((void*)old);
    }
    FUN_71039c2140(p);
}

// 0x71014a3780 (member at [4], vtable2+null merged via stp at [3]+[4])
void FUN_71014a3780(u64* p) {
    u64 old = p[4];
    p[0] = (u64)DAT_7105068e70;
    p[3] = (u64)DAT_7105068ee8;
    p[4] = 0;
    if (old) {
        FUN_71014a44c0((void*)(old + 8));
        jeFree_710392e590((void*)old);
    }
    FUN_71039c2140(p);
}

// =====================================================================
// Pattern F: Destructor with virtual call cleanup
// =====================================================================

// 0x7101424f30
void FUN_7101424f30(u64* p) {
    void* old = (void*)p[2];
    p[0] = (u64)DAT_7105065db0;
    p[2] = 0;
    if (old) {
        void* sub = *(void**)((u8*)old + 0x10);
        *(u64*)((u8*)old + 0x10) = 0;
        if (sub) {
            u64* vtbl = *(u64**)sub;
            ((void(*)(void*))vtbl[1])(sub);
        }
        jeFree_710392e590(old);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// Pattern G: String suffix counter
// =====================================================================

// 0x7101438b60 (non-matching: Clang 8 emits mov+eor+and instead of bic, plus shrink-wrapping)
void FUN_7101438b60(s64 param_1, s64 param_2, const char* param_3) {
    if (!param_1) return;
    if (param_3) {
        u64 len = FUN_71039bfac0(param_3);
        s32 idx = (s32)len - 1;
        u32 uidx = (u32)(idx & ~(idx >> 31));
        if (param_3[uidx] == 't') {
            *(s32*)(param_1 + 0x40) += 1;
            return;
        }
    }
    *(s32*)(param_1 + 0x44) += 1;
}

// =====================================================================
// Pattern H: Callback registration
// =====================================================================

// 0x7101224fa0
void FUN_7101224fa0(void* param_1, u64* param_2) {
    void* target = (void*)(param_2[4] + 0x10);
    FUN_71006307f0(target, 3, param_2, DAT_7100647a70, 0);
    FUN_71006307f0(target, 0x32, param_2, DAT_710064b200, 0);
}

} // namespace app::lua_bind
