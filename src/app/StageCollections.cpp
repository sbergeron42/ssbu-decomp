#include "types.h"

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
