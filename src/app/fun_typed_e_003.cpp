#include "types.h"

// pool-e: HARD tier — more recursive tree node deletion functions

extern "C" void jeFree_710392e590(void*);  // operator delete
extern "C" void FUN_71001b1870(void*);  // alternate delete
extern "C" void FUN_7103733f20(void*);  // cleanup helper

// ---------------------------------------------------------------------------
// Pattern A: cbz null check, recurse left/right, tail-call delete
// ---------------------------------------------------------------------------

// 0x7101468100  64B
void FUN_7101468100_1468100(void** n) {
    if (!n) return;
    FUN_7101468100_1468100(reinterpret_cast<void**>(n[0]));
    FUN_7101468100_1468100(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x71014879e0  64B
void FUN_71014879e0_14879e0(void** n) {
    if (!n) return;
    FUN_71014879e0_14879e0(reinterpret_cast<void**>(n[0]));
    FUN_71014879e0_14879e0(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x710160a610  64B
void FUN_710160a610_160a610(void** n) {
    if (!n) return;
    FUN_710160a610_160a610(reinterpret_cast<void**>(n[0]));
    FUN_710160a610_160a610(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x71016b4870  64B
void FUN_71016b4870_16b4870(void** n) {
    if (!n) return;
    FUN_71016b4870_16b4870(reinterpret_cast<void**>(n[0]));
    FUN_71016b4870_16b4870(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x71016bd520  64B
void FUN_71016bd520_16bd520(void** n) {
    if (!n) return;
    FUN_71016bd520_16bd520(reinterpret_cast<void**>(n[0]));
    FUN_71016bd520_16bd520(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x71017a91b0  64B
void FUN_71017a91b0_17a91b0(void** n) {
    if (!n) return;
    FUN_71017a91b0_17a91b0(reinterpret_cast<void**>(n[0]));
    FUN_71017a91b0_17a91b0(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x71017c4f20  64B
void FUN_71017c4f20_17c4f20(void** n) {
    if (!n) return;
    FUN_71017c4f20_17c4f20(reinterpret_cast<void**>(n[0]));
    FUN_71017c4f20_17c4f20(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x710187cc40  64B
void FUN_710187cc40_187cc40(void** n) {
    if (!n) return;
    FUN_710187cc40_187cc40(reinterpret_cast<void**>(n[0]));
    FUN_710187cc40_187cc40(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101aef220  64B
void FUN_7101aef220_1aef220(void** n) {
    if (!n) return;
    FUN_7101aef220_1aef220(reinterpret_cast<void**>(n[0]));
    FUN_7101aef220_1aef220(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101b1d1e0  64B
void FUN_7101b1d1e0_1b1d1e0(void** n) {
    if (!n) return;
    FUN_7101b1d1e0_1b1d1e0(reinterpret_cast<void**>(n[0]));
    FUN_7101b1d1e0_1b1d1e0(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101d11020  64B
void FUN_7101d11020_1d11020(void** n) {
    if (!n) return;
    FUN_7101d11020_1d11020(reinterpret_cast<void**>(n[0]));
    FUN_7101d11020_1d11020(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101d20770  64B
void FUN_7101d20770_1d20770(void** n) {
    if (!n) return;
    FUN_7101d20770_1d20770(reinterpret_cast<void**>(n[0]));
    FUN_7101d20770_1d20770(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101d207b0  64B
void FUN_7101d207b0_1d207b0(void** n) {
    if (!n) return;
    FUN_7101d207b0_1d207b0(reinterpret_cast<void**>(n[0]));
    FUN_7101d207b0_1d207b0(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101d88350  64B
void FUN_7101d88350_1d88350(void** n) {
    if (!n) return;
    FUN_7101d88350_1d88350(reinterpret_cast<void**>(n[0]));
    FUN_7101d88350_1d88350(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101ed2180  64B
void FUN_7101ed2180_1ed2180(void** n) {
    if (!n) return;
    FUN_7101ed2180_1ed2180(reinterpret_cast<void**>(n[0]));
    FUN_7101ed2180_1ed2180(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101f22470  64B
void FUN_7101f22470_1f22470(void** n) {
    if (!n) return;
    FUN_7101f22470_1f22470(reinterpret_cast<void**>(n[0]));
    FUN_7101f22470_1f22470(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7101f455e0  64B
void FUN_7101f455e0_1f455e0(void** n) {
    if (!n) return;
    FUN_7101f455e0_1f455e0(reinterpret_cast<void**>(n[0]));
    FUN_7101f455e0_1f455e0(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// 0x7103795c90  64B
void FUN_7103795c90_3795c90(void** n) {
    if (!n) return;
    FUN_7103795c90_3795c90(reinterpret_cast<void**>(n[0]));
    FUN_7103795c90_3795c90(reinterpret_cast<void**>(n[1]));
    jeFree_710392e590(n);
}

// ---------------------------------------------------------------------------
// Pattern B: recurse left/right, cleanup(node+0x28), delete
// ---------------------------------------------------------------------------

// 0x71037339b0  64B
void FUN_71037339b0_37339b0(void** n) {
    if (!n) return;
    FUN_71037339b0_37339b0(reinterpret_cast<void**>(n[0]));
    FUN_71037339b0_37339b0(reinterpret_cast<void**>(n[1]));
    FUN_7103733f20(reinterpret_cast<u8*>(n) + 0x28);
    jeFree_710392e590(n);
}

// ---------------------------------------------------------------------------
// Pattern D: two-param (ctx, node), recurse on node tree, delete via alt func
// ---------------------------------------------------------------------------

// 0x7101710390  64B
void FUN_7101710390_1710390(void* ctx, void** n) {
    if (!n) return;
    FUN_7101710390_1710390(ctx, reinterpret_cast<void**>(n[0]));
    FUN_7101710390_1710390(ctx, reinterpret_cast<void**>(n[1]));
    FUN_71001b1870(n);
}

// 0x7101713160  64B
void FUN_7101713160_1713160(void* ctx, void** n) {
    if (!n) return;
    FUN_7101713160_1713160(ctx, reinterpret_cast<void**>(n[0]));
    FUN_7101713160_1713160(ctx, reinterpret_cast<void**>(n[1]));
    FUN_71001b1870(n);
}

// 0x71036fdb10  64B
void FUN_71036fdb10_36fdb10(void* ctx, void** n) {
    if (!n) return;
    FUN_71036fdb10_36fdb10(ctx, reinterpret_cast<void**>(n[0]));
    FUN_71036fdb10_36fdb10(ctx, reinterpret_cast<void**>(n[1]));
    FUN_71001b1870(n);
}
