#include "types.h"
#include "app/placeholders/StageVt71051624a8.h"

// Stage collection cleanup helpers
//
// These are generic recursive destructors used by stage-class constructors
// and destructors to clean up dynamically-allocated node collections
// (BSTs and intrusive linked lists). They share a signature: take a node
// pointer (or null), recursively free children, then operator-delete self.
//
// Both appear in the StageWufuIsland constructor/destructor and other
// stage classes in the 0x71030xxxx range.

extern "C" void jeFree_710392e590(void*);
extern "C" void StageBase_dtor_71025d7310(void*);
// Sub-object cleanup helper at 0x710303be40. Defined (as FUN_710303be40) in
// fun_hard_c_010.cpp; we refer to it under a named alias here.
extern "C" void stage_vt71051624a8_cleanup_710303be40(void*) asm("FUN_710303be40");
extern "C" u64 DAT_71051624a8 __attribute__((visibility("hidden"))); // stage subclass vtable
extern "C" u64 DAT_7105162e58 __attribute__((visibility("hidden"))); // stage sub-obj vtable (vt_e58)
extern "C" u64 DAT_7105163290 __attribute__((visibility("hidden"))); // stage sub-obj vtable (vt_290)
extern "C" u64 DAT_71051635b8 __attribute__((visibility("hidden"))); // stage sub-obj vtable (vt_5b8)
extern "C" u64 DAT_7105163910 __attribute__((visibility("hidden"))); // stage sub-obj vtable (vt_910)

// Cleanup helpers for the two small D0 destructors below. Both are tail-called
// with the owned inner pointer's +0x28 field or the raw pointer.
extern "C" void stage_vt7105162e58_inner_cleanup_710303cf20(void*) asm("FUN_710303cf20");
extern "C" void stage_vt7105163290_inner_cleanup_7103047c00(void*) asm("FUN_7103047c00");

// Node layout for the BST helper: { Node* left; Node* right; ...payload }
// Only the first 16 bytes (left + right) are touched; payload is opaque.
// [derived: disasm at 0x71030080c0 — ldr x0,[x0]; bl self; ldr x0,[x19, #0x8]; bl self; b delete]
struct StageTreeNode {
    StageTreeNode* left;    // +0x00
    StageTreeNode* right;   // +0x08
};

// Node layout for the linked-list helper: { Node* next; ...payload }
// [derived: disasm at 0x710301bcb0 — ldr x20,[x0]; bl delete; mov x0,x20; cbnz loop]
struct StageListNode {
    StageListNode* next;    // +0x00
};

// 0x71030080c0 (56 bytes) — recursively free a StageWufuIsland BST
// Post-order tree walk: free left subtree, free right subtree, delete self.
// Called from the StageWufuIsland ctor to reset p[0x181] (embedded sub-object root).
// [derived: disasm at 0x71030080c0 — cbz guard, two recursive calls, tail-call delete]
extern "C" void free_stage_tree_71030080c0(StageTreeNode* node)
{
    if (node == nullptr) return;
    free_stage_tree_71030080c0(node->left);
    free_stage_tree_71030080c0(node->right);
    jeFree_710392e590(node);
}

// 0x710301bcb0 (60 bytes) — clear an intrusive linked list owned by a stage sub-object
// Walks the list at (owner + 0x10), deleting each node; then clears the head ptr
// at (owner + 0x00) and deletes it if non-null.
// [derived: disasm at 0x710301bcb0 — ldr x19,[x0, #0x10]; walk; str xzr; tail-call delete]
struct StageListOwner {
    StageListNode* head;    // +0x00 [derived: cleared and tail-call deleted]
    u8 unk_0x08[0x8];       // +0x08
    StageListNode* list;    // +0x10 [derived: walked and freed]
};

extern "C" void free_stage_list_710301bcb0(StageListOwner* owner)
{
    StageListNode* cur = owner->list;
    while (cur != nullptr) {
        StageListNode* next = cur->next;
        jeFree_710392e590(cur);
        cur = next;
    }
    StageListNode* head = owner->head;
    owner->head = nullptr;
    if (head == nullptr) return;
    jeFree_710392e590(head);
}

// 0x7103036770 (80 bytes) — D0 destructor for stage class with vtable DAT_71051624a8
// The corresponding D1 destructor (FUN_7103036720) lives in fun_hard_c_010.cpp; this
// D0 variant inlines the same cleanup, tail-calls ~StageBase, then deletes self.
// Field layout is documented in include/app/placeholders/StageVt71051624a8.h.
// [derived: disasm at 0x7103036770; paired with D1 at 0x7103036720 in fun_hard_c_010.cpp]
// 0x7103088730 (56 bytes) — second BST recursive free helper, identical to
// free_stage_tree_71030080c0 but at a different address. Used by a different
// stage sub-object tree. Keeping both as distinct symbols because they are
// distinct addresses in the shipping binary.
// [derived: disasm at 0x7103088730 — cbz x0; save x19; recurse left; recurse right; tail-call delete]
extern "C" void free_stage_tree_7103088730(StageTreeNode* node)
{
    if (node == nullptr) return;
    free_stage_tree_7103088730(node->left);
    free_stage_tree_7103088730(node->right);
    jeFree_710392e590(node);
}

// Node layout for the small-object D0 destructors below.
// Both classes have the same 2-field shape: { vtable@+0x00, owned@+0x08 }.
// [derived: disasm at 0x710303ceb0 and 0x7103047b20 — ldr x20,[x0, #0x8]; stp x8,xzr,[x0]]
struct StageSubObjVt {
    void* vtable;     // +0x00
    void* owned_inner;  // +0x08 [derived: cleaned via class-specific inner_cleanup then jeFree]
};

// 0x710303ceb0 (68 bytes) — D0 destructor for stage sub-object with vtable DAT_7105162e58.
// Not a StageBase descendant — just a 2-field polymorphic owner.
// NOTE: the inner cleanup helper is called with inner->+0x28 (not inner itself).
// [derived: disasm at 0x710303ceb0 — ldr x0,[x20, #0x28]; bl cleanup; bl delete]
extern "C" void stage_vt7105162e58_D0_dtor_710303ceb0(StageSubObjVt* self)
{
    void* inner = self->owned_inner;
    self->vtable = &DAT_7105162e58;
    self->owned_inner = nullptr;
    if (inner != nullptr) {
        // The cleanup helper expects the payload at inner+0x28, not inner itself
        stage_vt7105162e58_inner_cleanup_710303cf20(*reinterpret_cast<void**>(
            reinterpret_cast<u8*>(inner) + 0x28));
        jeFree_710392e590(inner);
    }
    jeFree_710392e590(self);
}

// 0x7103047b20 (68 bytes) — D0 destructor for stage sub-object with vtable DAT_7105163290.
// Same shape as stage_vt7105162e58_D0_dtor_710303ceb0 but different class. Here the
// inner cleanup helper takes the inner pointer directly (no +0x28 dereference).
// [derived: disasm at 0x7103047b20 — mov x0,x20; bl cleanup; bl delete]
extern "C" void stage_vt7105163290_D0_dtor_7103047b20(StageSubObjVt* self)
{
    void* inner = self->owned_inner;
    self->vtable = &DAT_7105163290;
    self->owned_inner = nullptr;
    if (inner != nullptr) {
        stage_vt7105163290_inner_cleanup_7103047c00(inner);
        jeFree_710392e590(inner);
    }
    jeFree_710392e590(self);
}

// Polymorphic destroyable with virtual destructor at vt[1]. The inner object
// of the stage sub-object classes below owns one such nested polymorphic.
// vt[1] is the standard Itanium ABI slot for ~Class().
struct NestedPoly {
    void** _vtable;   // +0x00 [derived: loaded, vt[1] called as destroy-in-place]

    void destroy() {
        // vt[1] is the Itanium ABI complete-object destructor slot.
        auto fn = reinterpret_cast<void(*)(NestedPoly*)>(_vtable[1]);
        fn(this);
    }
};

// Inner object for stage_vt71051635b8: nested poly slot at byte offset 32.
struct StageInner_NestedAt20 {
    u8 head[32];            // padding before the nested pointer
    NestedPoly* nested;     // [derived: cleared + destroy() in D0 dtor]
};

// Inner object for stage_vt7105163910: nested poly slot at byte offset 8.
struct StageInner_NestedAt08 {
    u8 head[8];             // padding before the nested pointer
    NestedPoly* nested;     // [derived: cleared + destroy() in D0 dtor]
};

// 0x710304de30 (84 bytes) — D0 destructor for stage sub-object with vtable
// DAT_71051635b8. Pattern: clear inner->nested@+0x20 via nested's vt[1],
// then delete inner, then delete self.
// [derived: disasm at 0x710304de30]
extern "C" void stage_vt71051635b8_D0_dtor_710304de30(StageSubObjVt* self)
{
    auto* inner = static_cast<StageInner_NestedAt20*>(self->owned_inner);
    self->vtable = &DAT_71051635b8;
    self->owned_inner = nullptr;
    if (inner != nullptr) {
        NestedPoly* nested = inner->nested;
        inner->nested = nullptr;
        if (nested != nullptr) nested->destroy();
        jeFree_710392e590(inner);
    }
    jeFree_710392e590(self);
}

// 0x7103054870 (84 bytes) — D0 destructor for stage sub-object with vtable
// DAT_7105163910. Same shape as stage_vt71051635b8_D0_dtor_710304de30 but the
// nested slot is at inner+0x8 instead of inner+0x20.
// [derived: disasm at 0x7103054870]
extern "C" void stage_vt7105163910_D0_dtor_7103054870(StageSubObjVt* self)
{
    auto* inner = static_cast<StageInner_NestedAt08*>(self->owned_inner);
    self->vtable = &DAT_7105163910;
    self->owned_inner = nullptr;
    if (inner != nullptr) {
        NestedPoly* nested = inner->nested;
        inner->nested = nullptr;
        if (nested != nullptr) nested->destroy();
        jeFree_710392e590(inner);
    }
    jeFree_710392e590(self);
}

extern "C" void stage_D0_dtor_7103036770(StageVt71051624a8* self)
{
    void* sub = self->owned_sub_0x738;
    self->vtable = &DAT_71051624a8;
    self->owned_sub_0x738 = nullptr;
    if (sub != nullptr) {
        stage_vt71051624a8_cleanup_710303be40(sub);
        jeFree_710392e590(sub);
    }
    StageBase_dtor_71025d7310(self);
    jeFree_710392e590(self);
}
