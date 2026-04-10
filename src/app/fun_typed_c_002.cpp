#include "types.h"

// External functions
extern "C" void FUN_71032ca770(void*);
extern "C" void jeFree_710392e590(void*);
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
// Pattern E cleanup functions
extern "C" void FUN_710171d040(void*);
extern "C" void FUN_7101813d70(void*);
extern "C" void FUN_710181e8a0(void*);
extern "C" void FUN_710186fbb0(void*);
extern "C" void FUN_71018e2d40(void*);
extern "C" void FUN_71018f7490(void*);
extern "C" void FUN_710196dde0(void*);
extern "C" void FUN_71019f0e30(void*);
extern "C" void FUN_7101aef260(void*);
extern "C" void FUN_7101cbb160(void*);
extern "C" void FUN_7101ccc180(void*);
extern "C" void FUN_7101cd2ae0(void*);
extern "C" void FUN_7101ce9eb0(void*);
extern "C" void FUN_7101f314f0(void*);
extern "C" void FUN_7101f35910(void*);
extern "C" void FUN_7101f43ae0(void*);
extern "C" void FUN_71037a2400(void*);
// Pattern D2/D3/H utility functions
extern "C" void FUN_71001af8a0(void*);
extern "C" void FUN_71001b1870(void*);
extern "C" void stdFunctionCleanup_71001b4910(void*);
extern "C" void FUN_71001b78a0(void*);
extern "C" void FUN_71015336e0(void*);
extern "C" void FUN_7101711810(void*, void*);
// Pattern F cleanup functions
extern "C" void FUN_71039c2140(void*);
extern "C" void FUN_7101473f30(void*);
extern "C" void FUN_710146bd70(void*);
extern "C" void FUN_7101468040(void*);
extern "C" void FUN_710148ff30(void*);
extern "C" void FUN_71014a44c0(void*);
extern "C" void FUN_7101ce1520(void*);
extern "C" void FUN_71032d6180(void*);

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
// Pattern E vtables
VTABLE_EXTERN(PTR_LAB_710509cad8);
VTABLE_EXTERN(PTR_LAB_71050a0d00);
VTABLE_EXTERN(PTR_LAB_71050a1208);
VTABLE_EXTERN(PTR_LAB_71050a2b78);
VTABLE_EXTERN(PTR_LAB_71050a4588);
VTABLE_EXTERN(PTR_LAB_71050a4730);
VTABLE_EXTERN(PTR_LAB_71050a5ad0);
VTABLE_EXTERN(PTR_LAB_71050a7278);
VTABLE_EXTERN(PTR_LAB_71050a9148);
VTABLE_EXTERN(PTR_LAB_71050ad1f0);
VTABLE_EXTERN(PTR_LAB_71050ad2e0);
VTABLE_EXTERN(PTR_LAB_71050ad3b0);
VTABLE_EXTERN(PTR_LAB_71050ad500);
VTABLE_EXTERN(PTR_LAB_71050b2ff0);
VTABLE_EXTERN(PTR_LAB_71050b3090);
VTABLE_EXTERN(PTR_LAB_71050b3358);
VTABLE_EXTERN(PTR_LAB_71052404c0);
// Pattern G vtables
VTABLE_EXTERN(PTR_FUN_7104f6d4c0);
VTABLE_EXTERN(PTR_FUN_7105063a70);
// Pattern F vtables
VTABLE_EXTERN(PTR_FUN_7105067018);
VTABLE_EXTERN(PTR_FUN_71050670f8);
VTABLE_EXTERN(PTR_FUN_7105067130);
VTABLE_EXTERN(PTR_FUN_71050674e8);
VTABLE_EXTERN(PTR_FUN_7105068e70);
VTABLE_EXTERN(PTR_LAB_7105067800);
VTABLE_EXTERN(PTR_LAB_7105067a20);
VTABLE_EXTERN(PTR_LAB_7105067da0);
VTABLE_EXTERN(PTR_LAB_71050686c0);
VTABLE_EXTERN(PTR_LAB_7105068ee8);
// Additional Pattern E vtables
VTABLE_EXTERN(PTR_LAB_71050adb00);
VTABLE_EXTERN(PTR_FUN_71050ad470);
// Pattern H vtables
VTABLE_EXTERN(PTR_FUN_710509c190);
VTABLE_EXTERN(PTR_FUN_710509c210);
VTABLE_EXTERN(PTR_FUN_710509c230);
VTABLE_EXTERN(PTR_FUN_710509c2e8);
VTABLE_EXTERN(PTR_FUN_710509c3e8);
VTABLE_EXTERN(PTR_FUN_710509c638);
VTABLE_EXTERN(PTR_LAB_710509bc08);
VTABLE_EXTERN(PTR_LAB_710509cce0);

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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
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
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x710138a6c0
void FUN_710138a6c0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105062970;
    self[1] = nullptr;
    if (sub) {
        FUN_71013b9a90(sub);
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x710143eb90
void FUN_710143eb90(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105066c20;
    self[1] = nullptr;
    if (sub) {
        FUN_710143ebe0(sub);
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x71014659e0
void FUN_71014659e0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050676d8;
    self[1] = nullptr;
    if (sub) {
        FUN_7101465760(sub);
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x710149c420
void FUN_710149c420(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_7105068cd0;
    self[1] = nullptr;
    if (sub) {
        FUN_710149a8d0(sub);
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
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
    jeFree_710392e590(node);
}

// 0x7101468100
void FUN_7101468100(void** node) {
    if (!node) return;
    FUN_7101468100(static_cast<void**>(node[0]));
    FUN_7101468100(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71014879e0
void FUN_71014879e0(void** node) {
    if (!node) return;
    FUN_71014879e0(static_cast<void**>(node[0]));
    FUN_71014879e0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x710160a610
void FUN_710160a610(void** node) {
    if (!node) return;
    FUN_710160a610(static_cast<void**>(node[0]));
    FUN_710160a610(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71016b4870
void FUN_71016b4870(void** node) {
    if (!node) return;
    FUN_71016b4870(static_cast<void**>(node[0]));
    FUN_71016b4870(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71016bd520
void FUN_71016bd520(void** node) {
    if (!node) return;
    FUN_71016bd520(static_cast<void**>(node[0]));
    FUN_71016bd520(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x710175cd20
void FUN_710175cd20(void** node) {
    if (!node) return;
    FUN_710175cd20(static_cast<void**>(node[0]));
    FUN_710175cd20(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71017626c0
void FUN_71017626c0(void** node) {
    if (!node) return;
    FUN_71017626c0(static_cast<void**>(node[0]));
    FUN_71017626c0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101aef220
void FUN_7101aef220(void** node) {
    if (!node) return;
    FUN_7101aef220(static_cast<void**>(node[0]));
    FUN_7101aef220(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71017a91b0
void FUN_71017a91b0(void** node) {
    if (!node) return;
    FUN_71017a91b0(static_cast<void**>(node[0]));
    FUN_71017a91b0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x71017c4f20
void FUN_71017c4f20(void** node) {
    if (!node) return;
    FUN_71017c4f20(static_cast<void**>(node[0]));
    FUN_71017c4f20(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x710184c5f0
void FUN_710184c5f0(void** node) {
    if (!node) return;
    FUN_710184c5f0(static_cast<void**>(node[0]));
    FUN_710184c5f0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x710187cc40
void FUN_710187cc40(void** node) {
    if (!node) return;
    FUN_710187cc40(static_cast<void**>(node[0]));
    FUN_710187cc40(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101b1d1e0
void FUN_7101b1d1e0(void** node) {
    if (!node) return;
    FUN_7101b1d1e0(static_cast<void**>(node[0]));
    FUN_7101b1d1e0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101d11020
void FUN_7101d11020(void** node) {
    if (!node) return;
    FUN_7101d11020(static_cast<void**>(node[0]));
    FUN_7101d11020(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101ed2180
void FUN_7101ed2180(void** node) {
    if (!node) return;
    FUN_7101ed2180(static_cast<void**>(node[0]));
    FUN_7101ed2180(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101f22470
void FUN_7101f22470(void** node) {
    if (!node) return;
    FUN_7101f22470(static_cast<void**>(node[0]));
    FUN_7101f22470(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101d88350
void FUN_7101d88350(void** node) {
    if (!node) return;
    FUN_7101d88350(static_cast<void**>(node[0]));
    FUN_7101d88350(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// 0x7101f455e0
void FUN_7101f455e0(void** node) {
    if (!node) return;
    FUN_7101f455e0(static_cast<void**>(node[0]));
    FUN_7101f455e0(static_cast<void**>(node[1]));
    jeFree_710392e590(node);
}

// ============================================================
// Pattern E: Simple vtable dtor + cleanup sub + tail-call delete self
// ============================================================

// --- sub at [1] (+0x8), uses stp for adjacent vtable+field ---

// 0x71019f0de0
void FUN_71019f0de0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050a7278;
    self[1] = nullptr;
    if (sub) { FUN_71019f0e30(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101af06f0
void FUN_7101af06f0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050a9148;
    self[1] = nullptr;
    if (sub) { FUN_7101aef260(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101cbd5e0
void FUN_7101cbd5e0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050ad1f0;
    self[1] = nullptr;
    if (sub) { FUN_7101cbb160(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101cccde0
void FUN_7101cccde0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050ad2e0;
    self[1] = nullptr;
    if (sub) { FUN_7101ccc180(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101ce9e60
void FUN_7101ce9e60(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050ad500;
    self[1] = nullptr;
    if (sub) { FUN_7101ce9eb0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101f314a0
void FUN_7101f314a0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050b2ff0;
    self[1] = nullptr;
    if (sub) { FUN_7101f314f0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101f358c0
void FUN_7101f358c0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050b3090;
    self[1] = nullptr;
    if (sub) { FUN_7101f35910(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x7101f43a90
void FUN_7101f43a90(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050b3358;
    self[1] = nullptr;
    if (sub) { FUN_7101f43ae0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x71037a2f10
void FUN_71037a2f10(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71052404c0;
    self[1] = nullptr;
    if (sub) { FUN_71037a2400(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// --- sub at [0xb] (+0x58), uses separate str for remote field ---

// 0x7101813f80
void FUN_7101813f80(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a0d00;
    self[0xb] = nullptr;
    if (sub) { FUN_7101813d70(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x710181e9a0
void FUN_710181e9a0(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a1208;
    self[0xb] = nullptr;
    if (sub) { FUN_710181e8a0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x710186fca0
void FUN_710186fca0(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a2b78;
    self[0xb] = nullptr;
    if (sub) { FUN_710186fbb0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x71018e9150
void FUN_71018e9150(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a4588;
    self[0xb] = nullptr;
    if (sub) { FUN_71018e2d40(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x71018f75d0
void FUN_71018f75d0(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a4730;
    self[0xb] = nullptr;
    if (sub) { FUN_71018f7490(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// 0x710196df70
void FUN_710196df70(void** self) {
    void* sub = self[0xb];
    self[0] = PTR_LAB_71050a5ad0;
    self[0xb] = nullptr;
    if (sub) { FUN_710196dde0(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// --- sub at [2] (+0x10), uses separate str ---

// 0x710171cff0
void FUN_710171cff0(void** self) {
    void* sub = self[2];
    self[0] = PTR_LAB_710509cad8;
    self[2] = nullptr;
    if (sub) { FUN_710171d040(sub); jeFree_710392e590(sub); }
    jeFree_710392e590(self);
}

// --- sub at [1] for 7101cd2cc0 (96B, has extra cleanup) ---
// Skipping 7101cd2cc0 as it's 96B and may have a different structure

// ============================================================
// Pattern D2: Binary tree recursive delete with 2 params (64 bytes)
// Check 2nd param for null; recurse left/right; tail-call FUN_71001b1870
// ============================================================

// 0x7101710390
void FUN_7101710390(void* ctx, void** node) {
    if (!node) return;
    FUN_7101710390(ctx, static_cast<void**>(node[0]));
    FUN_7101710390(ctx, static_cast<void**>(node[1]));
    FUN_71001b1870(node);
}

// 0x7101713160
void FUN_7101713160(void* ctx, void** node) {
    if (!node) return;
    FUN_7101713160(ctx, static_cast<void**>(node[0]));
    FUN_7101713160(ctx, static_cast<void**>(node[1]));
    FUN_71001b1870(node);
}

// ============================================================
// Pattern D3: Tree delete with extra cleanup before free
// ============================================================

// 0x71015336a0 (64 bytes, 1 param, cleanup at node+5)
void FUN_71015336a0(void** node) {
    if (!node) return;
    FUN_71015336a0(static_cast<void**>(node[0]));
    FUN_71015336a0(static_cast<void**>(node[1]));
    FUN_71015336e0(&node[5]);
    jeFree_710392e590(node);
}

// 0x710170e0f0 (96 bytes, 2 params, cleanup + sub-vtable set + free)
void FUN_710170e0f0(void* ctx, void** node) {
    if (!node) return;
    FUN_710170e0f0(ctx, static_cast<void**>(node[0]));
    FUN_710170e0f0(ctx, static_cast<void**>(node[1]));
    FUN_71001b78a0(&node[9]);
    node[4] = PTR_LAB_710509bc08;
    stdFunctionCleanup_71001b4910(&node[4]);
    FUN_71001b1870(node);
}

// ============================================================
// Pattern G: Linked list walk destructor
// Set vtable, walk linked list freeing nodes, null+free cleanup field
// ============================================================

// 0x71013aad40 (88 bytes, base dtor, list at [3], cleanup [1])
void FUN_71013aad40(void** self) {
    self[0] = PTR_FUN_7105063a70;
    void** node = static_cast<void**>(self[3]);
    while (node) {
        void** next = static_cast<void**>(node[0]);
        jeFree_710392e590(node);
        node = next;
    }
    void* sub = self[1];
    self[1] = nullptr;
    if (!sub) return;
    jeFree_710392e590(sub);
}

// 0x71013aada0 (84 bytes, deleting dtor, list at [3], cleanup [1], free self)
void FUN_71013aada0(void** self) {
    self[0] = PTR_FUN_7105063a70;
    void** node = static_cast<void**>(self[3]);
    while (node) {
        void** next = static_cast<void**>(node[0]);
        jeFree_710392e590(node);
        node = next;
    }
    void* sub = self[1];
    self[1] = nullptr;
    if (sub) {
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x7101611e90 (88 bytes, base dtor, list at [4], cleanup [2])
void FUN_7101611e90(void** self) {
    self[0] = PTR_FUN_7104f6d4c0;
    void** node = static_cast<void**>(self[4]);
    while (node) {
        void** next = static_cast<void**>(node[0]);
        jeFree_710392e590(node);
        node = next;
    }
    void* sub = self[2];
    self[2] = nullptr;
    if (!sub) return;
    jeFree_710392e590(sub);
}

// ============================================================
// Pattern F: shared_ptr destructor
// Set 2 vtable ptrs, null+cleanup inner field, tail-call ~__shared_weak_count
// ============================================================

// 0x7101461660
void FUN_7101461660(void** self) {
    void* sub = self[5];
    self[0] = PTR_FUN_71050674e8;
    self[3] = PTR_LAB_7105067da0;
    self[5] = nullptr;
    if (sub) {
        FUN_7101473f30(sub);
        jeFree_710392e590(sub);
    }
    FUN_71039c2140(self);
}

// 0x71014621e0
void FUN_71014621e0(void** self) {
    void* sub = self[5];
    self[0] = PTR_FUN_7105067130;
    self[3] = PTR_LAB_7105067a20;
    self[5] = nullptr;
    if (sub) {
        FUN_710146bd70(sub);
        jeFree_710392e590(sub);
    }
    FUN_71039c2140(self);
}

// 0x71014622c0
void FUN_71014622c0(void** self) {
    void* sub = self[5];
    self[0] = PTR_FUN_71050670f8;
    self[3] = PTR_LAB_7105067800;
    self[5] = nullptr;
    if (sub) {
        FUN_7101468040(sub);
        jeFree_710392e590(sub);
    }
    FUN_71039c2140(self);
}

// 0x7101462580
void FUN_7101462580(void** self) {
    void* sub = self[5];
    self[0] = PTR_FUN_7105067018;
    self[3] = PTR_LAB_71050686c0;
    self[5] = nullptr;
    if (sub) {
        FUN_710148ff30(sub);
        jeFree_710392e590(sub);
    }
    FUN_71039c2140(self);
}

// 0x71014a3780 (field at [4], adjacent vtable2+zero merged into STP)
void FUN_71014a3780(void** self) {
    void* sub = self[4];
    self[0] = PTR_FUN_7105068e70;
    self[3] = PTR_LAB_7105068ee8;
    self[4] = nullptr;
    if (sub) {
        FUN_71014a44c0((char*)sub + 8);
        jeFree_710392e590(sub);
    }
    FUN_71039c2140(self);
}

// 0x710171d680 (92 bytes, 2 params, tree delete + vtable set + conditional field free)
void FUN_710171d680(void* ctx, void** node) {
    if (!node) return;
    FUN_710171d680(ctx, static_cast<void**>(node[0]));
    FUN_710171d680(ctx, static_cast<void**>(node[1]));
    void* sub = node[8];
    node[5] = PTR_LAB_710509cce0;
    if (sub) {
        node[9] = sub;
        FUN_71001b1870(sub);
    }
    FUN_71001b1870(node);
}

// ============================================================
// Pattern E continued: vtable dtor variants
// ============================================================

// 0x7101cd2cc0 (Pattern E, STP for vtable+zero at [0]/[1])
void FUN_7101cd2cc0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050ad3b0;
    self[1] = nullptr;
    if (sub) {
        FUN_7101cd2ae0(sub);
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x7101d10fd0 (Pattern E variant, inner tree deletes before freeing sub)
void FUN_7101d10fd0(void** self) {
    void* sub = self[1];
    self[0] = PTR_LAB_71050adb00;
    self[1] = nullptr;
    if (sub) {
        void** s = static_cast<void**>(sub);
        FUN_7101d11020(static_cast<void**>(s[0x8d]));
        FUN_7101d11020(static_cast<void**>(s[0x8a]));
        jeFree_710392e590(sub);
    }
    jeFree_710392e590(self);
}

// 0x7101ce7ce0 (Pattern E, field at [4], tail-call FUN_71032d6180)
void FUN_7101ce7ce0(void** self) {
    void* sub = self[4];
    self[0] = PTR_FUN_71050ad470;
    self[4] = nullptr;
    if (sub) {
        FUN_7101ce1520(sub);
        jeFree_710392e590(sub);
    }
    FUN_71032d6180(self);
}

// 0x7101ce7d30 (deleting variant: call parent dtor + free self)
void FUN_7101ce7d30(void** self) {
    void* sub = self[4];
    self[0] = PTR_FUN_71050ad470;
    self[4] = nullptr;
    if (sub) {
        FUN_7101ce1520(sub);
        jeFree_710392e590(sub);
    }
    FUN_71032d6180(self);
    jeFree_710392e590(self);
}

// ============================================================
// Pattern G continued: linked list walk destructors
// ============================================================

// 0x71033bff10 (base dtor, same pattern as FUN_7101611e90)
void FUN_71033bff10(void** self) {
    self[0] = PTR_FUN_7104f6d4c0;
    void** node = static_cast<void**>(self[4]);
    while (node) {
        void** next = static_cast<void**>(node[0]);
        jeFree_710392e590(node);
        node = next;
    }
    void* sub = self[2];
    self[2] = nullptr;
    if (!sub) return;
    jeFree_710392e590(sub);
}

// NOTE: Pattern H (multi-sub-vtable destructors) not included — code logic is
// correct but upstream Clang 8 hoists ADRP+ADD before stp x29,x30 in prologue.
// Needs fix_prologue_sched.py enhancement to move stp x29,x30+add x29 pair
// before ADRP+ADD sequences. Affects ~20 functions in 0x710171* range.
