#include "types.h"

// External functions
extern "C" void FUN_71032ca770(void*);
extern "C" void FUN_710392e590(void*);
extern "C" void FUN_71013c66e0(void*);
extern "C" void FUN_710137c8e0(void*);
extern "C" void FUN_71013b9a90(void*);
extern "C" void FUN_71013d0130(void*);
extern "C" void FUN_71013dd730(void*);
extern "C" void FUN_71013e0d90(void*);
extern "C" void FUN_71013e70c0(void*);
extern "C" void FUN_710143ebe0(void*);
extern "C" void FUN_7101465760(void*);
extern "C" void FUN_710149a8d0(void*);

// Vtable symbols — hidden visibility to get ADRP+ADD (not GOT)
#define VTABLE_EXTERN(name) extern "C" __attribute__((visibility("hidden"))) char name[]
VTABLE_EXTERN(PTR_FUN_7105062d00);
VTABLE_EXTERN(PTR_FUN_7105062e80);
VTABLE_EXTERN(PTR_FUN_7105063260);
VTABLE_EXTERN(PTR_FUN_71050636e0);
VTABLE_EXTERN(PTR_FUN_71050637a0);
VTABLE_EXTERN(PTR_FUN_7105063860);
VTABLE_EXTERN(PTR_FUN_71050641a8);
VTABLE_EXTERN(PTR_FUN_7105064388);
VTABLE_EXTERN(PTR_FUN_71050646e8);
VTABLE_EXTERN(PTR_FUN_7105064868);
VTABLE_EXTERN(PTR_FUN_7105064b68);
VTABLE_EXTERN(PTR_LAB_7105062450);
VTABLE_EXTERN(PTR_LAB_7105062970);
VTABLE_EXTERN(PTR_LAB_7105066c20);
VTABLE_EXTERN(PTR_LAB_71050676d8);
VTABLE_EXTERN(PTR_LAB_7105068cd0);

// ============================================================
// Destructor Pattern: sub at +0x50, inner cleanup at sub+0x8,
// tail-call parent dtor FUN_71013c66e0
// All 80 bytes, identical structure, different vtable addresses
// ============================================================

// 0x710138d100
void FUN_710138d100(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105062d00;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x710138f170
void FUN_710138f170(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105062e80;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x7101397380
void FUN_7101397380(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105063260;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013a4520
void FUN_71013a4520(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_71050636e0;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013a4bd0
void FUN_71013a4bd0(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_71050637a0;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013a7fe0
void FUN_71013a7fe0(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105063860;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013cc370
void FUN_71013cc370(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_71050641a8;
    self[10] = nullptr;
    if (sub) {
        void** sub_p = static_cast<void**>(sub);
        void* inner = sub_p[1];
        sub_p[1] = nullptr;
        if (inner) {
            FUN_71032ca770(inner);
        }
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// ============================================================
// Pattern C: sub at +0x50, direct cleanup call, tail-call parent
// ============================================================

// 0x71013d0250
void FUN_71013d0250(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105064388;
    self[10] = nullptr;
    if (sub) {
        FUN_71013d0130(sub);
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013ddbc0
void FUN_71013ddbc0(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_71050646e8;
    self[10] = nullptr;
    if (sub) {
        FUN_71013dd730(sub);
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013e12b0
void FUN_71013e12b0(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105064868;
    self[10] = nullptr;
    if (sub) {
        FUN_71013e0d90(sub);
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// 0x71013e7810
void FUN_71013e7810(void** self) {
    void* sub = self[10];
    self[0] = PTR_FUN_7105064b68;
    self[10] = nullptr;
    if (sub) {
        FUN_71013e70c0(sub);
        FUN_710392e590(sub);
    }
    FUN_71013c66e0(self);
}

// ============================================================
// Pattern A: sub at +0x8, stp vtable+zero, cleanup, tail-delete
// ============================================================

// 0x710137c890
void FUN_710137c890(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105062450;
    self[1] = nullptr;
    if (sub) {
        FUN_710137c8e0(sub);
        FUN_710392e590(sub);
    }
    FUN_710392e590(self);
}

// 0x710138a6c0
void FUN_710138a6c0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105062970;
    self[1] = nullptr;
    if (sub) {
        FUN_71013b9a90(sub);
        FUN_710392e590(sub);
    }
    FUN_710392e590(self);
}

// 0x710143eb90
void FUN_710143eb90(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105066c20;
    self[1] = nullptr;
    if (sub) {
        FUN_710143ebe0(sub);
        FUN_710392e590(sub);
    }
    FUN_710392e590(self);
}

// 0x71014659e0
void FUN_71014659e0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050676d8;
    self[1] = nullptr;
    if (sub) {
        FUN_7101465760(sub);
        FUN_710392e590(sub);
    }
    FUN_710392e590(self);
}

// 0x710149c420
void FUN_710149c420(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105068cd0;
    self[1] = nullptr;
    if (sub) {
        FUN_710149a8d0(sub);
        FUN_710392e590(sub);
    }
    FUN_710392e590(self);
}

// ============================================================
// Pattern D: Binary tree recursive delete (64 bytes)
// if null return; recurse left; recurse right; free self
// ============================================================

// 0x71014106f0
void FUN_71014106f0(void** node) {
    if (!node) return;
    FUN_71014106f0(static_cast<void**>(node[0]));
    FUN_71014106f0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101468100
void FUN_7101468100(void** node) {
    if (!node) return;
    FUN_7101468100(static_cast<void**>(node[0]));
    FUN_7101468100(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71014879e0
void FUN_71014879e0(void** node) {
    if (!node) return;
    FUN_71014879e0(static_cast<void**>(node[0]));
    FUN_71014879e0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x710160a610
void FUN_710160a610(void** node) {
    if (!node) return;
    FUN_710160a610(static_cast<void**>(node[0]));
    FUN_710160a610(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71016b4870
void FUN_71016b4870(void** node) {
    if (!node) return;
    FUN_71016b4870(static_cast<void**>(node[0]));
    FUN_71016b4870(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71016bd520
void FUN_71016bd520(void** node) {
    if (!node) return;
    FUN_71016bd520(static_cast<void**>(node[0]));
    FUN_71016bd520(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x710175cd20
void FUN_710175cd20(void** node) {
    if (!node) return;
    FUN_710175cd20(static_cast<void**>(node[0]));
    FUN_710175cd20(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71017626c0
void FUN_71017626c0(void** node) {
    if (!node) return;
    FUN_71017626c0(static_cast<void**>(node[0]));
    FUN_71017626c0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101aef220
void FUN_7101aef220(void** node) {
    if (!node) return;
    FUN_7101aef220(static_cast<void**>(node[0]));
    FUN_7101aef220(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71017a91b0
void FUN_71017a91b0(void** node) {
    if (!node) return;
    FUN_71017a91b0(static_cast<void**>(node[0]));
    FUN_71017a91b0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71017c4f20
void FUN_71017c4f20(void** node) {
    if (!node) return;
    FUN_71017c4f20(static_cast<void**>(node[0]));
    FUN_71017c4f20(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x710184c5f0
void FUN_710184c5f0(void** node) {
    if (!node) return;
    FUN_710184c5f0(static_cast<void**>(node[0]));
    FUN_710184c5f0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x710187cc40
void FUN_710187cc40(void** node) {
    if (!node) return;
    FUN_710187cc40(static_cast<void**>(node[0]));
    FUN_710187cc40(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101b1d1e0
void FUN_7101b1d1e0(void** node) {
    if (!node) return;
    FUN_7101b1d1e0(static_cast<void**>(node[0]));
    FUN_7101b1d1e0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101d11020
void FUN_7101d11020(void** node) {
    if (!node) return;
    FUN_7101d11020(static_cast<void**>(node[0]));
    FUN_7101d11020(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101ed2180
void FUN_7101ed2180(void** node) {
    if (!node) return;
    FUN_7101ed2180(static_cast<void**>(node[0]));
    FUN_7101ed2180(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101f22470
void FUN_7101f22470(void** node) {
    if (!node) return;
    FUN_7101f22470(static_cast<void**>(node[0]));
    FUN_7101f22470(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101d88350
void FUN_7101d88350(void** node) {
    if (!node) return;
    FUN_7101d88350(static_cast<void**>(node[0]));
    FUN_7101d88350(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101f455e0
void FUN_7101f455e0(void** node) {
    if (!node) return;
    FUN_7101f455e0(static_cast<void**>(node[0]));
    FUN_7101f455e0(static_cast<void**>(node[1]));
    FUN_710392e590(node);
}
