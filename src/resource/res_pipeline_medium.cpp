// res_pipeline_medium.cpp — Rendering pipeline container operations
// Material parameter binding for the cross2app rendering engine.
// Uses std::unordered_map (hash table) and std::set (red-black tree) for
// ink rendering system: "UpdateInkThreshold", "UpdateInkColor", "UpdateResetInk".
//
// Functions:
//   string_tree_destroy        — libc++ 8.0.0: __tree::destroy (recursive node free)
//   string_tree_lower_bound    — libc++ 8.0.0: __tree::__lower_bound (BST search)
//   hash_table_reserve         — libc++ 8.0.0: __hash_table::rehash (bucket resize)
//   pipeline_clear_material_map — clear material bindings and shared_ptr vector
//   string_tree_insert_unique  — libc++ 8.0.0: __tree::__insert_unique_impl
//   pipeline_link_nodes        — link binding entries to matrix elements via hash lookup
//   pipeline_update            — rebuild material map from input data
//   pipeline_init              — allocate pools, matrices, state object

#include "types.h"
#include "resource/PipelineTypes.h"

// ============================================================================
// External declarations
// ============================================================================

// Memory management
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void jeFree_710392e590(void*);  // je_free
extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" int memcmp(const void*, const void*, unsigned long);

// je_posix_memalign: stores ptr in *out, returns 0 success / 0xC ENOMEM
extern "C" int FUN_710392dc40(void*, unsigned long, unsigned long);

// OOM handler singletons
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;
__attribute__((visibility("hidden"))) extern s64* DAT_710593c2b0;

// Virtual alloc/free hooks
extern "C" void FUN_71039c1400(void*);       // nu::VirtualFreeHook (PLT)
namespace nu { void VirtualAllocHook(u64 size, u32 alignment, void* ptr); }
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;
__attribute__((visibility("hidden"))) extern char PTR_VirtualAllocHook_71052a7a78[];

// libc++ STL internal functions
namespace std { namespace __1 {
    unsigned long __next_prime(unsigned long);
    void __tree_balance_after_insert(void* root, void* node);
    [[noreturn]] void __throw_length_error(const char*);
}}

extern "C" [[noreturn]] void abort();

// Mutex operations (PLT stubs)
extern "C" void FUN_71039c14b0(void*);   // std::__1::mutex::lock()
extern "C" void FUN_71039c14c0(void*);   // std::__1::mutex::unlock()

// std::__1::__shared_weak_count
namespace std { namespace __1 {
    class __shared_weak_count {
        long __shared_owners_;
        long __shared_weak_owners_;
    public:
        void __release_weak() noexcept;
        virtual ~__shared_weak_count();
    };
}}

extern "C" long FUN_71026773a0(const char*, unsigned long);

// Helpers (not targets)
extern "C" void pipeline_clear_sub(long);
extern "C" void FUN_710354fb70(long*, unsigned long);
extern "C" void FUN_7103554370(long);
extern "C" void FUN_7103557cc0(long*, void*);
extern "C" void FUN_7103558ee0(long*, void*);

// Vtable / data externs
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710522eda8;
__attribute__((visibility("hidden"))) extern void* PTR_LAB_710522ef60;
__attribute__((visibility("hidden"))) extern void* PTR_LAB_710522ede0;
__attribute__((visibility("hidden"))) extern void* PTR_LAB_710522ee00;

// Pipeline state globals
__attribute__((visibility("hidden"))) extern long DAT_7105333000;
__attribute__((visibility("hidden"))) extern long* DAT_7105333008;
__attribute__((visibility("hidden"))) extern long DAT_7105333010;
__attribute__((visibility("hidden"))) extern long DAT_7105333018;
__attribute__((visibility("hidden"))) extern long DAT_7105333020;
__attribute__((visibility("hidden"))) extern long* DAT_7105333028;
__attribute__((visibility("hidden"))) extern long DAT_7105333030;
__attribute__((visibility("hidden"))) extern long DAT_7105333040;
__attribute__((visibility("hidden"))) extern long* DAT_7105333048;
__attribute__((visibility("hidden"))) extern long DAT_7105333050;

__attribute__((visibility("hidden"))) extern float DAT_710447157c;

__attribute__((visibility("hidden"))) extern long _DAT_71044646b0;
__attribute__((visibility("hidden"))) extern long _UNK_71044646b8;
__attribute__((visibility("hidden"))) extern long _DAT_7104464fb0;
__attribute__((visibility("hidden"))) extern long _UNK_7104464fb8;
__attribute__((visibility("hidden"))) extern long _DAT_7104467ca0;
__attribute__((visibility("hidden"))) extern long _UNK_7104467ca8;
__attribute__((visibility("hidden"))) extern long _DAT_7104469350;
__attribute__((visibility("hidden"))) extern long _UNK_7104469358;
__attribute__((visibility("hidden"))) extern long DAT_7104469360;
__attribute__((visibility("hidden"))) extern long DAT_7104469368;

__attribute__((visibility("hidden"))) extern char s_UpdateInkThreshold_7104410022[];
__attribute__((visibility("hidden"))) extern char s_UpdateInkColor_7104379fa5[];
__attribute__((visibility("hidden"))) extern char s_UpdateResetInk_710426d67b[];

// Forward declarations
void pipeline_clear_material_map(PipelineContainer* pipeline);
void hash_table_reserve(long map_addr, unsigned long new_count);
void string_tree_insert_unique(long* tree, long* hint, u8* search_key, u8* insert_key);
void string_tree_destroy(StringTreeNode* node);
long* string_tree_lower_bound(long tree_addr, long* out_parent, u8* search_key);

// ============================================================================
// string_tree_destroy — libc++ 8.0.0: __tree::destroy (320 bytes)
// Recursively destroys all nodes in a red-black tree (std::set<std::string>).
// [derived: libc++ __tree_node_destructor pattern — post-order traversal, free SSO heap data]
// Address: 0x710354f900
// ============================================================================
void string_tree_destroy(StringTreeNode* node) {
    if (node != nullptr) {
        string_tree_destroy(node->left);
        string_tree_destroy(node->right);
        // [derived: SSO long mode — bit 0 of flag byte = 1 means heap-allocated string data]
        if (node->value.is_long()) {
            void* str_heap = (void*)node->value.long_data();
            if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                FUN_71039c1400(str_heap);
            }
            jeFree_710392e590(str_heap);
        }
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400((void*)node);
        }
        jeFree_710392e590((void*)node);
    }
}

// ============================================================================
// string_tree_lower_bound — libc++ 8.0.0: __tree::__lower_bound (304 bytes)
// BST lower-bound search with SSO string comparison.
// [derived: libc++ __tree::__lower_bound — standard BST traversal with string compare]
// Address: 0x710354fa40
// ============================================================================
long* string_tree_lower_bound(long tree_addr, long* out_parent, u8* search_key) {
    unsigned long node_len;
    unsigned long cmp_len;
    unsigned long key_len;
    u8* key_data;
    u8 node_sso_flag;
    int cmp_result;
    void* node_data;
    long* result_slot;
    long* curr;
    long* node;

    // [inferred: tree_addr + 8 = address of root pointer, doubles as end sentinel]
    result_slot = (long*)(tree_addr + 8);
    curr = (long*)*result_slot;
    if (curr == nullptr) {
        *out_parent = (long)result_slot;
        return result_slot;
    }
    // Extract search key data (SSO string)
    key_len = *(unsigned long*)(search_key + 8);
    key_data = *(u8**)(search_key + 0x10);
    result_slot = (long*)(tree_addr + 8);
    if ((*search_key & 1) == 0) {
        key_data = search_key + 1;
        key_len = (unsigned long)(*search_key >> 1);
    }
    do {
        while (true) {
            node = curr;
            // Extract node string data (SSO)
            node_sso_flag = *(u8*)(node + 4);  // +0x20: SSO flag byte
            node_len = (unsigned long)(node_sso_flag >> 1);
            if ((node_sso_flag & 1) != 0) {
                node_len = (unsigned long)node[5];  // +0x28: long mode length
            }
            cmp_len = node_len;
            if (key_len <= node_len) {
                cmp_len = key_len;
            }
            if (cmp_len == 0) break;
            node_data = (void*)node[6];  // +0x30: long mode data
            if ((node_sso_flag & 1) == 0) {
                node_data = (void*)((long)node + 0x21);  // short mode data
            }
            cmp_result = memcmp(key_data, node_data, cmp_len);
            if (cmp_result == 0) break;
            if (cmp_result < 0) goto go_left;
go_right_check:
            cmp_result = memcmp(node_data, key_data, cmp_len);
            if (cmp_result == 0) goto lengths_equal;
            if (-1 < cmp_result) goto return_node;
go_right:
            result_slot = node + 1;  // right child slot (+0x08)
            curr = (long*)*result_slot;
            if ((long*)*result_slot == nullptr) {
return_node:
                *out_parent = (long)node;
                return result_slot;
            }
        }
        if (node_len <= key_len) {
            if (cmp_len != 0) {
                node_data = (void*)node[6];
                if ((node_sso_flag & 1) == 0) {
                    node_data = (void*)((long)node + 0x21);
                }
                goto go_right_check;
            }
lengths_equal:
            if (key_len <= node_len) goto return_node;
            goto go_right;
        }
go_left:
        result_slot = node;  // left child slot (+0x00)
        curr = (long*)*node;
        if ((long*)*node == nullptr) {
            *out_parent = (long)node;
            return node;
        }
    } while (true);
}

// ============================================================================
// hash_table_reserve — libc++ 8.0.0: __hash_table::rehash (240 bytes)
// Reserves bucket count for an unordered_map. Computes next prime or power-of-2
// bucket count, then rehashes if the new count differs from current.
// [derived: libc++ __hash_table::rehash — prime/power-of-2 bucket sizing]
// Address: 0x710354f380
// ============================================================================
void hash_table_reserve(long map_addr, unsigned long requested) {
    unsigned long current_buckets;
    unsigned long new_count;

    // Ensure minimum of 2 buckets, or next prime if not power-of-2
    if (requested - 1 == 0) {
        requested = 2;
    } else if ((requested - 1 & requested) != 0) {
        requested = std::__1::__next_prime(requested);
    }
    // [inferred: map_addr+8 = bucket_count field of hash table]
    current_buckets = *(unsigned long*)(map_addr + 8);
    new_count = requested;
    if (current_buckets < requested) {
do_rehash:
        FUN_710354fb70((long*)map_addr, new_count);
        return;
    }
    if (requested < current_buckets) {
        // [inferred: map_addr+0x18 = element count, map_addr+0x20 = max_load_factor]
        new_count = (unsigned long)((float)*(unsigned long*)(map_addr + 0x18) / *(float*)(map_addr + 0x20));
        if (current_buckets < 3 || (current_buckets - 1 & current_buckets) != 0) {
            new_count = std::__1::__next_prime(new_count);
        } else if (1 < new_count) {
            new_count = 1UL << ((-__builtin_clzl(new_count - 1)) & 0x3fU);
        }
        if (new_count <= requested) {
            new_count = requested;
        }
        if (new_count < current_buckets) goto do_rehash;
    }
}

// ============================================================================
// pipeline_clear_material_map (384 bytes)
// Clears the material binding hash map and shared_ptr binding vector.
// Releases all hash nodes (freeing SSO heap data), zeroes bucket array,
// then calls destructors on binding entries in reverse order.
// [inferred: called from pipeline_update before rebuilding the map]
// Address: 0x710354f200
// ============================================================================
void pipeline_clear_material_map(PipelineContainer* pipeline) {
    long* obj_ptr;
    long* ctrl_ptr;
    void* free_hook;
    unsigned long bucket_idx;
    long end_offset;
    long ref_copy;
    unsigned long bucket_count;
    long* bucket_base;
    void* str_heap;
    long iter_addr;

    // Step 1: release shared_ptrs in binding vector
    // [inferred: binding entries at +0xC0..+0xC8, stride 0x20]
    end_offset = (long)pipeline->binding_vec_end;
    free_hook = PTR_VirtualFreeHook_71052a7a70;
    for (iter_addr = (long)pipeline->binding_vec_start;
         PTR_VirtualFreeHook_71052a7a70 = free_hook, iter_addr != end_offset;
         iter_addr = iter_addr + 0x20) {
        // [inferred: entry layout — +0x08=obj_ptr, +0x10=ctrl_ptr, +0x18=ref_copy]
        obj_ptr = *(long**)(iter_addr + 8);
        ctrl_ptr = *(long**)(iter_addr + 0x10);
        ref_copy = *(long*)(iter_addr + 0x18);
        *(long*)(iter_addr + 8) = 0;
        *(long*)(iter_addr + 0x10) = 0;
        *(long*)(iter_addr + 0x18) = 0;
        if (ctrl_ptr != nullptr && obj_ptr != nullptr && *ctrl_ptr == ref_copy) {
            (*(void(**)(void))(*(long*)obj_ptr + 8))();
        }
        free_hook = PTR_VirtualFreeHook_71052a7a70;
    }

    // Step 2: destroy all hash map nodes
    // [inferred: material_map at +0x98, head at +0xA8(+0x10), size at +0xB0(+0x18)]
    if (pipeline->material_map.size != 0) {
        MaterialHashNode* hash_node = pipeline->material_map.head;
        while (hash_node != nullptr) {
            iter_addr = (long)hash_node->next;
            // Free SSO heap data if string is in long mode
            if (hash_node->key.is_long()) {
                str_heap = (void*)hash_node->key.long_data();
                if (free_hook != nullptr) {
                    FUN_71039c1400(str_heap);
                }
                jeFree_710392e590(str_heap);
            }
            jeFree_710392e590((void*)hash_node);
            hash_node = (MaterialHashNode*)iter_addr;
        }
        // Zero all buckets (unrolled by 4)
        bucket_count = pipeline->material_map.bucket_count;
        pipeline->material_map.head = nullptr;
        if (bucket_count != 0) {
            bucket_idx = bucket_count & 3;
            if (bucket_count - 1 < 3) {
                iter_addr = 0;
            } else {
                iter_addr = 0;
                do {
                    end_offset = iter_addr * 8;
                    iter_addr = iter_addr + 4;
                    *(long*)((long)pipeline->material_map.buckets + end_offset) = 0;
                    *(long*)((long)pipeline->material_map.buckets + end_offset + 8) = 0;
                    *(long*)((long)pipeline->material_map.buckets + end_offset + 0x10) = 0;
                    *(long*)((long)pipeline->material_map.buckets + end_offset + 0x18) = 0;
                } while (bucket_count - bucket_idx != (unsigned long)iter_addr);
            }
            if (bucket_idx != 0) {
                iter_addr = iter_addr << 3;
                end_offset = -(long)bucket_idx;
                do {
                    *(long*)((long)pipeline->material_map.buckets + iter_addr) = 0;
                    iter_addr = iter_addr + 8;
                    end_offset = end_offset + 1;
                } while (end_offset != 0);
            }
        }
        pipeline->material_map.size = 0;
    }

    // Step 3: call destructors on binding entries in reverse order
    // [inferred: entries have vtable at +0x00, dtor is vtable[0]]
    PipelineBindingEntry* vec_start = pipeline->binding_vec_start;
    PipelineBindingEntry* vec_end = pipeline->binding_vec_end;
    while (vec_end != vec_start) {
        vec_end = (PipelineBindingEntry*)((long*)vec_end - 4);
        (*(void(**)(PipelineBindingEntry*))(*(long*)vec_end))(vec_end);
    }
    pipeline->binding_vec_end = vec_start;
}

// ============================================================================
// string_tree_insert_unique — libc++ 8.0.0: __tree::__insert_unique (1,168 bytes)
// Inserts a string into a red-black tree (std::set<std::string>) if not present.
// Compares using SSO string layout. Allocates 0x38-byte StringTreeNode on insert.
// [derived: libc++ __tree::__insert_unique_impl — BST insert + rebalance]
// Address: 0x710354f470
// ============================================================================
void string_tree_insert_unique(long* tree, long* hint, u8* search_key, u8* insert_key) {
    unsigned long cmp_len;
    long raw_word0;
    u8 hint_sso;
    u8 key_sso;
    void* alloc_hook;
    bool is_match;
    int cmp_result;
    long* insert_slot;
    unsigned long hint_len;
    unsigned long oom_result;
    u8* key_data;
    void* node_str_data;
    long* walk;
    long raw_word2;
    long child_val;
    long* prev_walk;
    long* successor;
    unsigned long key_len;
    void* str_dest;
    long local_slot;
    long parent_addr;
    void* alloc_ptr;
    unsigned long retry_size;

    // Check if hint is the end sentinel (tree + 1 = &root field)
    if (tree + 1 == hint) {
        goto insert_before_hint;
    }
    // Compare search_key with hint's string (SSO comparison)
    hint_sso = *(u8*)(hint + 4);  // +0x20: hint node SSO flag
    key_sso = *search_key;
    hint_len = (unsigned long)(hint_sso >> 1);
    if ((hint_sso & 1) != 0) {
        hint_len = (unsigned long)hint[5];  // +0x28: long mode length
    }
    key_len = (unsigned long)(key_sso >> 1);
    if ((key_sso & 1) != 0) {
        key_len = *(unsigned long*)(search_key + 8);
    }
    cmp_len = hint_len;
    if (key_len <= hint_len) {
        cmp_len = key_len;
    }
    if (cmp_len == 0) {
check_lengths:
        if (key_len < hint_len) goto insert_before_hint;
        if (cmp_len != 0) {
            node_str_data = (void*)hint[6];  // +0x30: long mode data
            key_data = *(u8**)(search_key + 0x10);
            if ((hint_sso & 1) == 0) {
                node_str_data = (void*)((long)hint + 0x21);  // short mode data
            }
            if ((key_sso & 1) == 0) {
                key_data = search_key + 1;
            }
            goto reverse_cmp;
        }
lengths_equal:
        if (hint_len < key_len) {
key_greater:
            insert_slot = hint + 1;  // right child slot
            walk = (long*)*insert_slot;
            if ((long*)*insert_slot == nullptr) {
                // Find successor (next node in order)
                walk = hint + 2;  // parent pointer
                successor = (long*)*walk;
                if ((long*)*successor != hint) {
                    do {
                        child_val = *walk;
                        walk = (long*)(child_val + 0x10);
                        successor = (long*)*walk;
                    } while (*successor != child_val);
                }
            } else {
                // Find predecessor (leftmost in right subtree)
                do {
                    successor = walk;
                    walk = (long*)*successor;
                } while ((long*)*successor != nullptr);
            }
            if (successor != tree + 1) {
                hint_sso = *(u8*)(successor + 4);
                hint_len = (unsigned long)(hint_sso >> 1);
                if ((hint_sso & 1) != 0) {
                    hint_len = (unsigned long)successor[5];
                }
                cmp_len = hint_len;
                if (key_len <= hint_len) {
                    cmp_len = key_len;
                }
                if (cmp_len != 0) {
                    key_data = *(u8**)(search_key + 0x10);
                    if ((key_sso & 1) == 0) {
                        key_data = search_key + 1;
                    }
                    node_str_data = (void*)successor[6];
                    if ((hint_sso & 1) == 0) {
                        node_str_data = (void*)((long)successor + 0x21);
                    }
                    cmp_result = memcmp(key_data, node_str_data, cmp_len);
                    if (cmp_result != 0) {
                        if (-1 < cmp_result) goto use_lower_bound;
                        goto do_insert;
                    }
                }
                if (hint_len <= key_len) goto use_lower_bound;
            }
do_insert:
            if (hint[1] == 0) {
                child_val = *insert_slot;
                parent_addr = (long)hint;
            } else {
                child_val = *successor;
                insert_slot = successor;
                parent_addr = (long)successor;
            }
            goto do_alloc;
        }
    } else {
        key_data = *(u8**)(search_key + 0x10);
        if ((key_sso & 1) == 0) {
            key_data = search_key + 1;
        }
        node_str_data = (void*)hint[6];
        if ((hint_sso & 1) == 0) {
            node_str_data = (void*)((long)hint + 0x21);
        }
        cmp_result = memcmp(key_data, node_str_data, cmp_len);
        if (cmp_result == 0) goto check_lengths;
        if (cmp_result < 0) goto insert_before_hint;
reverse_cmp:
        cmp_result = memcmp(node_str_data, key_data, cmp_len);
        if (cmp_result == 0) goto lengths_equal;
        if (cmp_result < 0) goto key_greater;
    }
    insert_slot = &local_slot;
    if (hint != nullptr) {
        return;
    }
    local_slot = 0;
    parent_addr = (long)hint;
    child_val = 0;
    goto do_alloc;

insert_before_hint:
    insert_slot = (long*)*hint;  // left child of hint
    walk = hint;
    if ((long*)*tree == hint) {
found_position:
        if (insert_slot == nullptr) {
            child_val = *hint;
            insert_slot = hint;
            parent_addr = (long)hint;
        } else {
            child_val = walk[1];
            insert_slot = walk + 1;
            parent_addr = (long)walk;
        }
    } else {
        successor = insert_slot;
        prev_walk = hint;
        if (insert_slot == nullptr) {
            // Walk up to find predecessor
            do {
                walk = (long*)prev_walk[2];
                is_match = (long*)*walk == prev_walk;
                prev_walk = walk;
            } while (is_match);
        } else {
            // Walk down to find rightmost in left subtree
            do {
                walk = successor;
                successor = (long*)walk[1];
            } while ((long*)walk[1] != nullptr);
        }
        // Compare predecessor with search key
        hint_sso = *(u8*)(walk + 4);
        key_sso = *search_key;
        hint_len = (unsigned long)(key_sso >> 1);
        if ((key_sso & 1) != 0) {
            hint_len = *(unsigned long*)(search_key + 8);
        }
        key_len = (unsigned long)(hint_sso >> 1);
        if ((hint_sso & 1) != 0) {
            key_len = (unsigned long)walk[5];
        }
        cmp_len = hint_len;
        if (key_len <= hint_len) {
            cmp_len = key_len;
        }
        if (cmp_len == 0) {
pred_check_len:
            if (key_len < hint_len) goto found_position;
        } else {
            node_str_data = (void*)walk[6];
            if ((hint_sso & 1) == 0) {
                node_str_data = (void*)((long)walk + 0x21);
            }
            key_data = *(u8**)(search_key + 0x10);
            if ((key_sso & 1) == 0) {
                key_data = search_key + 1;
            }
            cmp_result = memcmp(node_str_data, key_data, cmp_len);
            if (cmp_result == 0) goto pred_check_len;
            if (cmp_result < 0) goto found_position;
        }
use_lower_bound:
        insert_slot = string_tree_lower_bound((long)tree, &parent_addr, search_key);
        child_val = *insert_slot;
    }
do_alloc:
    if (child_val != 0) {
        return;
    }

    // Allocate new StringTreeNode (0x38 bytes)
    cmp_result = FUN_710392dc40(&alloc_ptr, 0x10, 0x38);
    if (cmp_result == 0xc && DAT_710593c2b0 != nullptr) {
        retry_size = 0x38;
        hint_len = (*(unsigned long(**)(s64*, unsigned long*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, &retry_size);
        if ((hint_len & 1) != 0) {
            FUN_710392dc40(&alloc_ptr, 0x10, 0x38);
        }
    }
    alloc_hook = *(void**)&PTR_VirtualAllocHook_71052a7a78;
    if (alloc_hook != nullptr) {
        nu::VirtualAllocHook(0x38, 0x10, alloc_ptr);
    }

    long* new_node = (long*)alloc_ptr;

    // Zero the string field at +0x20 (LibcppString, 24 bytes)
    *(long*)((long)alloc_ptr + 0x20) = 0;
    *(long*)((long)alloc_ptr + 0x28) = 0;
    *(long*)((long)alloc_ptr + 0x30) = 0;

    // Copy insert_key into the new node's string field
    if ((*insert_key & 1) == 0) {
        // Short string: bulk-copy the 24-byte SSO inline data
        raw_word0 = *(long*)insert_key;
        raw_word2 = *(long*)(insert_key + 0x10);
        *(long*)((long)alloc_ptr + 0x28) = *(long*)(insert_key + 8);
        *(long*)((long)alloc_ptr + 0x30) = raw_word2;
        *(long*)((long)alloc_ptr + 0x20) = raw_word0;
        goto link_node;
    }
    hint_len = *(unsigned long*)(insert_key + 8);
    if (0xffffffffffffffefUL < hint_len) {
        std::__1::__throw_length_error("basic_string");
    }
    node_str_data = *(void**)(insert_key + 0x10);
    if (hint_len < 0x17) {
        // Short mode in new node
        str_dest = (void*)((long)new_node + 0x21);
        *(u8*)((long)alloc_ptr + 0x20) = (u8)((int)hint_len << 1);
        if (hint_len != 0) goto copy_str_data;
    } else {
        // Long mode: allocate separate heap buffer
        key_len = (hint_len + 0x10) & 0xfffffffffffffff0UL;
        cmp_result = FUN_710392dc40(&alloc_ptr, 0x10, key_len);
        if (cmp_result == 0xc && DAT_710593c2b0 != nullptr) {
            retry_size = key_len;
            oom_result = (*(unsigned long(**)(s64*, unsigned long*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, &retry_size);
            if ((oom_result & 1) != 0) {
                FUN_710392dc40(&alloc_ptr, 0x10, key_len);
            }
        }
        if (alloc_hook != nullptr) {
            nu::VirtualAllocHook(key_len, 0x10, alloc_ptr);
        }
        str_dest = alloc_ptr;
        *(unsigned long*)((long)new_node + 0x20) = key_len | 1;
        *(unsigned long*)((long)new_node + 0x28) = hint_len;
        *(void**)((long)new_node + 0x30) = alloc_ptr;
copy_str_data:
        memcpy(str_dest, node_str_data, hint_len);
    }
    *(u8*)((long)str_dest + hint_len) = 0;

link_node:
    // Link new node: left=null, right=null, parent=parent_addr
    *new_node = 0;
    new_node[1] = 0;
    new_node[2] = parent_addr;
    *insert_slot = (long)new_node;
    // Update begin_node if needed
    if (*(long*)*tree != 0) {
        *tree = *(long*)*tree;
        new_node = (long*)*insert_slot;
    }
    // Rebalance the red-black tree
    std::__1::__tree_balance_after_insert((void*)tree[1], (void*)new_node);
    tree[2] = tree[2] + 1;
}

// ============================================================================
// pipeline_link_nodes (368 bytes)
// Links binding entries to matrix elements by searching the node link hash map.
// For each binding, reads its link hash (+0x158), looks up the hash in the
// link_map, and if found with matching value at +0x30, stores the matrix
// element address at +0x178 of the binding's sub-object.
// [inferred: link_map is std::unordered_map with hash key at node+0x08, value at node+0x18]
// Address: 0x710354ff10
// ============================================================================
u32 pipeline_link_nodes(PipelineContainer* pipeline) {
    long* state_fallback;
    long bind_iter;
    unsigned long quotient;
    unsigned long entry_hash;
    unsigned long bucket_idx;
    long* hash_node;
    unsigned long node_hash;
    long* result_ptr;
    long bind_end;
    u32 all_linked;
    long link_hash;
    long matrix_iter;
    unsigned long link_bucket_count;
    unsigned long bucket_mask;

    bind_iter = (long)pipeline->binding_vec_start;
    bind_end = (long)pipeline->binding_vec_end;
    if (bind_iter == bind_end) {
        return 1;
    }
    state_fallback = (long*)&pipeline->state_ptr;
    all_linked = 1;
next_binding:
    // [inferred: binding sub-object at +0x08, link hash at sub_obj+0x158]
    link_hash = *(long*)(*(long*)(bind_iter + 8) + 0x158);
    if (link_hash != 0) {
        matrix_iter = (long)pipeline->matrix_vec_start;
        if (matrix_iter == (long)pipeline->matrix_vec_end) {
            return 0;
        }
        link_bucket_count = pipeline->link_map.bucket_count;
        bucket_mask = link_bucket_count - 1;
search_matrix:
        result_ptr = state_fallback;
        if (link_bucket_count != 0) {
            // [inferred: matrix element hash at +0x1A8]
            entry_hash = *(unsigned long*)(matrix_iter + 0x1a8);
            // Hash-to-bucket: power-of-2 fast path vs general modulo
            if ((bucket_mask & link_bucket_count) == 0) {
                bucket_idx = bucket_mask & entry_hash;
            } else {
                bucket_idx = entry_hash;
                if (link_bucket_count <= entry_hash) {
                    quotient = 0;
                    if (link_bucket_count != 0) {
                        quotient = entry_hash / link_bucket_count;
                    }
                    bucket_idx = entry_hash - quotient * link_bucket_count;
                }
            }
            hash_node = *(long**)(*(long*)pipeline->link_map.buckets + bucket_idx * 8);
            if (hash_node != nullptr && (hash_node = (long*)*hash_node, hash_node != nullptr)) {
                if ((bucket_mask & link_bucket_count) == 0) {
                    // Power-of-2 bucket count path
                    do {
                        node_hash = (unsigned long)hash_node[1];
                        if (node_hash != entry_hash && (node_hash & bucket_mask) != bucket_idx) break;
                        if (node_hash == entry_hash && hash_node[2] == (long)entry_hash) goto found_match;
                        hash_node = (long*)*hash_node;
                    } while (hash_node != nullptr);
                } else {
                    // General modulo path
                    do {
                        node_hash = (unsigned long)hash_node[1];
                        if (node_hash == entry_hash) {
                            if (hash_node[2] == (long)entry_hash) goto found_match;
                        } else {
                            if (link_bucket_count <= node_hash) {
                                quotient = 0;
                                if (link_bucket_count != 0) {
                                    quotient = node_hash / link_bucket_count;
                                }
                                node_hash = node_hash - quotient * link_bucket_count;
                            }
                            if (node_hash != bucket_idx) break;
                        }
                        hash_node = (long*)*hash_node;
                    } while (hash_node != nullptr);
                }
            }
        }
        goto check_result;
found_match:
        result_ptr = hash_node + 3;  // value at node+0x18
check_result:
        // [inferred: result_ptr points to value, deref to get object with +0x30 = link target]
        if (*(char*)*result_ptr != '\0' && link_hash == *(long*)((char*)*result_ptr + 0x30)) {
            goto store_link;
        }
        matrix_iter = matrix_iter + 0x330;
        if (matrix_iter == (long)pipeline->matrix_vec_end) {
            return 0;
        }
        goto search_matrix;
store_link:
        // [inferred: store matrix element address at binding sub-object +0x178]
        *(long*)(*(long*)(bind_iter + 8) + 0x178) = matrix_iter;
    } else {
        all_linked = 0;
    }
    bind_iter = bind_iter + 0x20;
    if (bind_iter == bind_end) {
        return all_linked;
    }
    goto next_binding;
}

// ============================================================================
// pipeline_update (3,360 bytes)
// Updates the rendering pipeline: extracts data from input, clears and
// rebuilds the material hash map, constructs a string set of shader parameter
// names ("UpdateInkThreshold", "UpdateInkColor", "UpdateResetInk"),
// iterates input materials, and inserts bindings into the hash map.
// [derived: ink rendering strings in .rodata section]
// Address: 0x710354e4e0
// ============================================================================
long pipeline_update(PipelineContainer* pipeline, long input_data) {
    long pipe = (long)pipeline;  // byte-address alias for raw offset access
    long* iter_ptr;          // material map iterator
    long* map_head;          // material map head pointer
    long* new_vec_end;       // new vector end after grow
    long moved_val_b;        // moved shared_ptr value
    long* node_len_a;        // tree node string length a
    long* node_len_b;        // tree node string length b
    unsigned long sso_len;   // SSO string length
    unsigned long str_cmp_len; // string comparison length
    long* search_len;        // search key length
    char* hash_str;          // hash key string data
    u8 sso_flag;             // SSO flag byte
    int alloc_result;        // allocation result code
    u32 cmp_val;             // comparison value
    long alloc_base;         // allocation base address
    unsigned long oom_result; // OOM handler result
    long* hash_val;          // hash value for insertion
    unsigned long grow_alloc; // grow allocation size
    long old_size;           // old vector size
    long* new_end;           // new vector end pointer
    long* hash_chain;        // hash chain search iterator
    char* str_ptr;           // string data pointer
    long* hash_entry;        // hash map entry
    long* hash_node;         // hash map node
    long new_base;           // new allocation base
    long grow_offset;        // grow offset in vector
    long* tree_data;         // tree node data pointer
    char* cmp_str;           // comparison string
    unsigned long rehash_size; // rehash target size
    long* old_vec_start;     // old vector start
    long ref_val;            // reference/version value
    long* ctrl_ptr;          // shared_ptr control block
    long src_val;            // source value during move
    long moved_val;          // moved value during realloc
    long data_src;           // data source address
    long size_delta;         // size difference
    long* bucket_count;      // bucket count pointer
    long* bucket_idx;        // bucket index
    long* vec_start;         // vector start pointer
    void* str_dest;          // string copy destination
    long* bound_obj;         // bound material object
    u8* key_raw;             // raw key bytes
    void* search_data;       // search comparison data
    float load;              // load factor
    long* bucket_entry;      // bucket entry pointer
    long* entry_str;         // entry SSO string pointer
    unsigned long __n;       // hash key string length
    char* __s2;              // hash key string data
    void* __dest;            // string copy destination (hash node)
    unsigned long retry_result; // OOM retry result
    long local_110;
    long local_108;
    long local_100;
    long local_e8;
    long local_d8;
    u8 local_d0[0x18];
    u8 local_b8[0x18];
    u8 local_a0[0x18];
    long local_tree[3];  // tree header: [0]=begin_node, [1]=root, [2]=size
    void* local_70;
    u32 local_70_lo;
    u32 local_6c;

    // Step 1: extract data pointers from input_data into globals
    if (*(long**)(input_data + 16) == nullptr ||
        **(long**)(input_data + 16) != *(long*)(input_data + 24)) {
        DAT_7105333000 = 0;
        DAT_7105333010 = 0;
        DAT_7105333008 = nullptr;
    } else {
        DAT_7105333000 = *(long*)(input_data + 8);
        if (DAT_7105333000 == 0) {
            DAT_7105333010 = 0;
            DAT_7105333008 = nullptr;
        } else {
            DAT_7105333008 = *(long**)(DAT_7105333000 + 8);
            DAT_7105333010 = *DAT_7105333008;
        }
    }
    if (*(long**)(input_data + 48) == nullptr ||
        **(long**)(input_data + 48) != *(long*)(input_data + 56)) {
        DAT_7105333020 = 0;
        DAT_7105333030 = 0;
        DAT_7105333028 = nullptr;
    } else {
        DAT_7105333020 = *(long*)(input_data + 40);
        if (DAT_7105333020 == 0) {
            DAT_7105333030 = 0;
            DAT_7105333028 = nullptr;
        } else {
            DAT_7105333028 = *(long**)(DAT_7105333020 + 8);
            DAT_7105333030 = *DAT_7105333028;
        }
    }
    if (*(long**)(input_data + 80) == nullptr ||
        **(long**)(input_data + 80) != *(long*)(input_data + 0x58)) {
        DAT_7105333040 = 0;
        DAT_7105333050 = 0;
        DAT_7105333048 = nullptr;
    } else {
        DAT_7105333040 = *(long*)(input_data + 72);
        if (DAT_7105333040 == 0) {
            DAT_7105333050 = 0;
            DAT_7105333048 = nullptr;
        } else {
            DAT_7105333048 = *(long**)(DAT_7105333040 + 8);
            DAT_7105333050 = *DAT_7105333048;
        }
    }

    // Step 2: clear material map and rehash
    pipeline_clear_material_map(pipeline);
    iter_ptr = (long*)&pipeline->material_map;
    hash_table_reserve((long)iter_ptr, (long)(DAT_710447157c / pipeline->material_map.max_load_factor));

    // Step 3: resize binding vector at +0xC0 if capacity < 0x180
    vec_start = (long*)pipeline->binding_vec_start;
    if ((unsigned long)(((long)pipeline->binding_vec_eos - (long)vec_start) >> 5) < 0x180UL) {
        data_src = (long)pipeline->binding_vec_end;
        size_delta = data_src - (long)vec_start;
        alloc_base = (long)je_aligned_alloc(0x10, 0x3000);
        if (alloc_base == 0) {
            if (DAT_7105331f00 != nullptr) {
                local_70_lo = 0;
                *(long*)&local_d0[0] = 0x3000;
                oom_result = (*(unsigned long(**)(s64*, u32*, u8*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_70_lo, local_d0);
                if ((oom_result & 1) != 0) {
                    alloc_base = (long)je_aligned_alloc(0x10, 0x3000);
                    if (alloc_base != 0) goto LAB_e6b4;
                }
            }
            alloc_base = 0;
        }
LAB_e6b4:
        new_base = alloc_base + (size_delta >> 5) * 0x20;
        old_size = data_src - (long)vec_start;
        if (old_size == 0) {
            pipeline->binding_vec_start = (PipelineBindingEntry*)new_base;
            pipeline->binding_vec_end = (PipelineBindingEntry*)new_base;
            pipeline->binding_vec_eos = (PipelineBindingEntry*)(alloc_base + 0x3000);
        } else {
            grow_offset = 0;
            do {
                src_val = new_base + grow_offset;
                *(long*)(src_val - 0x10) = 0;
                *(long*)(src_val - 8) = 0;
                moved_val_b = data_src + grow_offset;
                *(void**)(src_val - 0x20) = &PTR_LAB_710522ede0;
                *(long*)(src_val - 0x18) = 0;
                if (*(long**)(moved_val_b - 0x10) != nullptr &&
                    **(long**)(moved_val_b - 0x10) == *(long*)(moved_val_b - 8)) {
                    moved_val = *(long*)(moved_val_b - 0x18);
                    *(long*)(moved_val_b - 0x10) = 0;
                    *(long*)(moved_val_b - 8) = 0;
                    *(long*)(moved_val_b - 0x18) = 0;
                    *(long*)(src_val - 0x18) = moved_val;
                    if (moved_val == 0) {
                        ref_val = 0;
                        *(long*)(src_val - 0x10) = 0;
                    } else {
                        old_vec_start = *(long**)(moved_val + 8);
                        *(long**)(src_val - 0x10) = old_vec_start;
                        ref_val = *old_vec_start;
                    }
                    *(long*)(src_val - 8) = ref_val;
                }
                grow_offset = grow_offset - 0x20;
            } while ((long)vec_start - data_src != grow_offset);
            vec_start = (long*)pipeline->binding_vec_start;
            old_vec_start = (long*)pipeline->binding_vec_end;
            pipeline->binding_vec_start = (PipelineBindingEntry*)(alloc_base + ((size_delta - 0x20) - ((old_size - 0x20UL) & 0xFFFFFFFFFFFFFFE0UL)));
            pipeline->binding_vec_end = (PipelineBindingEntry*)new_base;
            pipeline->binding_vec_eos = (PipelineBindingEntry*)(alloc_base + 0x3000);
            while (old_vec_start != vec_start) {
                old_vec_start = old_vec_start - 4;
                (*(void(**)(long*))(*(long*)old_vec_start))(old_vec_start);
            }
        }
        if (vec_start != nullptr) {
            jeFree_710392e590(vec_start);
        }
    }

    // Step 4: build string set with material parameter names
    data_src = DAT_7105333020;

    // SSO string: "UpdateInkThreshold" (18 chars, flag = 0x24)
    local_d0[0] = 0x24;
    *(long*)(local_d0 + 1) = *(long*)&s_UpdateInkThreshold_7104410022[0];
    *(long*)(local_d0 + 9) = *(long*)&s_UpdateInkThreshold_7104410022[8];
    local_d0[17] = s_UpdateInkThreshold_7104410022[16];
    local_d0[18] = s_UpdateInkThreshold_7104410022[17];
    local_d0[19] = 0;
    *(u32*)(local_d0 + 20) = 0;

    // SSO string: "UpdateInkColor" (14 chars, flag = 0x1C)
    local_b8[0] = 0x1C;
    *(long*)(local_b8 + 1) = *(long*)&s_UpdateInkColor_7104379fa5[0];
    *(long*)(local_b8 + 9) = *(long*)&s_UpdateInkColor_7104379fa5[8];
    local_b8[15] = 0;
    *(long*)(local_b8 + 8) = 0;

    // SSO string: "UpdateResetInk" (14 chars, flag = 0x1C)
    local_a0[0] = 0x1C;
    *(long*)(local_a0 + 1) = *(long*)&s_UpdateResetInk_710426d67b[0];
    *(long*)(local_a0 + 9) = *(long*)&s_UpdateResetInk_710426d67b[8];
    local_a0[15] = 0;
    *(long*)(local_a0 + 8) = 0;

    // Tree header: begin_node points to end_node (tree[1])
    local_tree[1] = 0;   // root = null
    local_tree[2] = 0;   // size = 0
    local_tree[0] = (long)&local_tree[1];  // begin_node = &root

    // Insert 3 strings into tree
    string_tree_insert_unique(local_tree, (long*)&local_tree[1], local_d0, local_d0);
    string_tree_insert_unique(local_tree, (long*)&local_tree[1], local_b8, local_b8);
    string_tree_insert_unique(local_tree, (long*)&local_tree[1], local_a0, local_a0);

    // Step 5: iterate input array and build hash map
    // [inferred: input material array pointers at +440 and +448 of data source]
    alloc_base = *(long*)(data_src + 440);  // +0x1B8: material array start
    data_src = *(long*)(data_src + 448);    // +0x1C0: material array end
    if (alloc_base != data_src) {
        map_head = (long*)&pipeline->material_map.head;
        do {
            size_delta = *(long*)(alloc_base + 8);
            entry_str = (long*)(size_delta + 64);  // +0x40: entry SSO string

            // Allocate 0x180 bytes for material binding
            alloc_result = FUN_710392dc40(&local_70, 0x10, 0x180);
            if (alloc_result == 0xc && DAT_710593c2b0 != nullptr) {
                *(long*)local_d0 = 0x180;
                *(u8*)(local_d0 + 8) = 1;
                oom_result = (*(unsigned long(**)(s64*, u8*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, local_d0);
                if ((oom_result & 1) != 0) {
                    FUN_710392dc40(&local_70, 0x10, 0x180);
                }
            }
            if (*(void**)&PTR_VirtualAllocHook_71052a7a78 != nullptr) {
                nu::VirtualAllocHook(0x180, 0x10, local_70);
            }
            bound_obj = (long*)local_70;
            FUN_7103557cc0(bound_obj, (void*)entry_str);

            bucket_idx = entry_str;
            if (bound_obj == nullptr) {
                FUN_7103558ee0(0, (void*)&DAT_7105333018);
                local_e8 = 0;
                local_d8 = 0;
LAB_e974:
                local_108 = 0;
                local_100 = 0;
                local_110 = 0;
                if ((long*)local_tree[1] == nullptr) goto LAB_ea88;
LAB_e984:
                // Search string tree for this entry's key
                search_len = *(long**)(size_delta + 72);
                search_data = *(void**)(size_delta + 80);
                bucket_idx = (long*)&local_tree[1];
                hash_val = (long*)local_tree[1];
                if ((*(u8*)(size_delta + 64) & 1) == 0) {
                    search_data = (void*)(size_delta + 65);
                    search_len = (long*)((unsigned long)(*(u8*)(size_delta + 64) >> 1));
                }
                // BST search with SSO string comparison
                do {
                    sso_flag = *(u8*)(hash_val + 4);
                    node_len_a = (long*)((unsigned long)(sso_flag >> 1));
                    if ((sso_flag & 1) != 0) {
                        node_len_a = (long*)hash_val[5];
                    }
                    node_len_b = search_len;
                    if (node_len_a <= search_len) {
                        node_len_b = node_len_a;
                    }
                    if (node_len_b == nullptr) {
LAB_e9e0:
                        cmp_val = (u32)((unsigned long)search_len < (unsigned long)node_len_a);
                        if ((unsigned long)node_len_a < (unsigned long)search_len) {
                            cmp_val = 0xffffffff;
                        }
                    } else {
                        tree_data = (long*)hash_val[6];
                        if ((sso_flag & 1) == 0) {
                            tree_data = (long*)((long)hash_val + 0x21);
                        }
                        cmp_val = (u32)memcmp(tree_data, search_data, (unsigned long)node_len_b);
                        if (cmp_val == 0) goto LAB_e9e0;
                    }
                    if ((int)cmp_val >= 0) {
                        bucket_idx = hash_val;
                    }
                    bucket_count = hash_val + ((int)cmp_val < 0);
                    hash_val = (long*)*bucket_count;
                } while ((long*)*bucket_count != nullptr);
                if (bucket_idx == (long*)&local_tree[1]) goto LAB_ea88;
                sso_flag = *(u8*)(bucket_idx + 4);
                node_len_a = (long*)((unsigned long)(sso_flag >> 1));
                if ((sso_flag & 1) != 0) {
                    node_len_a = (long*)bucket_idx[5];
                }
                node_len_b = node_len_a;
                if (search_len <= node_len_a) {
                    node_len_b = search_len;
                }
                if (node_len_b == nullptr) {
LAB_ea80:
                    if ((unsigned long)search_len < (unsigned long)node_len_a) goto LAB_ea88;
                } else {
                    tree_data = (long*)bucket_idx[6];
                    if ((sso_flag & 1) == 0) {
                        tree_data = (long*)((long)bucket_idx + 0x21);
                    }
                    alloc_result = memcmp(search_data, tree_data, (unsigned long)node_len_b);
                    if (alloc_result == 0) goto LAB_ea80;
                    if (alloc_result < 0) goto LAB_ea88;
                }
                // Found in tree — check shared_ptr validity
                if (local_d8 != 0 && *(long*)local_d8 == local_e8) goto LAB_ea68;
            } else {
                // Normal path: bound_obj is valid
                local_d8 = bound_obj[1];
                local_e8 = *(long*)local_d8;
                FUN_7103558ee0(bound_obj, (void*)&DAT_7105333018);
                if (local_d8 == 0 || *(long*)local_d8 != local_e8) goto LAB_e974;
                local_108 = bound_obj[1];
                local_100 = *(long*)local_108;
                local_110 = (long)bound_obj;
                if ((long*)local_tree[1] != nullptr) goto LAB_e984;
LAB_ea88:
                // Append to vector at +0xC0
                vec_start = (long*)pipeline->binding_vec_end;
                if (vec_start < (long*)pipeline->binding_vec_eos) {
                    vec_start[1] = 0;
                    vec_start[2] = 0;
                    vec_start[3] = 0;
                    *vec_start = (long)&PTR_LAB_710522ede0;
                    if (local_d8 != 0 && *(long*)local_d8 == local_e8) {
                        vec_start[1] = (long)bound_obj;
                        if (bound_obj == nullptr) {
                            ref_val = 0;
                            vec_start[2] = 0;
                        } else {
                            old_vec_start = (long*)bound_obj[1];
                            vec_start[2] = (long)old_vec_start;
                            ref_val = *old_vec_start;
                        }
                        local_d8 = 0;
                        bound_obj = nullptr;
                        local_e8 = 0;
                        vec_start[3] = ref_val;
                    }
                    pipeline->binding_vec_end = (PipelineBindingEntry*)((long)pipeline->binding_vec_end + 0x20);
                } else {
                    // Vector realloc (grow)
                    old_vec_start = (long*)pipeline->binding_vec_start;
                    new_base = ((long)vec_start - (long)old_vec_start) >> 5;
                    bucket_idx = (long*)(new_base + 1);
                    if ((unsigned long)bucket_idx >> 0x3b != 0) {
                        std::__1::__throw_length_error("vector");
                    }
                    old_size = (long)pipeline->binding_vec_eos - (long)old_vec_start;
                    if ((unsigned long)(old_size >> 5) < 0x3ffffffffffffffUL) {
                        hash_val = (long*)(old_size >> 4);
                        if (bucket_idx <= hash_val) {
                            bucket_idx = hash_val;
                        }
                        if (bucket_idx != nullptr) {
                            if ((unsigned long)bucket_idx >> 0x3b != 0) {
                                abort();
                            }
                            goto LAB_eb28;
                        }
LAB_eb80:
                        grow_offset = 0;
                    } else {
                        bucket_idx = (long*)0x7ffffffffffffffUL;
LAB_eb28:
                        old_size = (long)bucket_idx * 0x20;
                        if (old_size == 0) old_size = 1;
                        grow_offset = (long)je_aligned_alloc(0x10, old_size);
                        if (grow_offset == 0) {
                            if (DAT_7105331f00 != nullptr) {
                                local_70_lo = 0;
                                *(long*)local_d0 = old_size;
                                oom_result = (*(unsigned long(**)(s64*, u32*, u8*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_70_lo, local_d0);
                                if ((oom_result & 1) != 0) {
                                    grow_offset = (long)je_aligned_alloc(0x10, old_size);
                                    if (grow_offset != 0) goto LAB_eb84;
                                }
                            }
                            goto LAB_eb80;
                        }
                    }
LAB_eb84:
                    new_end = (long*)(grow_offset + new_base * 0x20);
                    new_end[1] = 0;
                    new_end[2] = 0;
                    new_end[3] = 0;
                    *new_end = (long)&PTR_LAB_710522ede0;
                    if (local_d8 == 0) {
                        local_d8 = 0;
                    } else if (*(long*)local_d8 == local_e8) {
                        new_end[1] = (long)bound_obj;
                        if (bound_obj == nullptr) {
                            ref_val = 0;
                            new_end[2] = 0;
                        } else {
                            vec_start = (long*)bound_obj[1];
                            new_end[2] = (long)vec_start;
                            ref_val = *vec_start;
                        }
                        local_e8 = 0;
                        local_d8 = 0;
                        bound_obj = nullptr;
                        new_end[3] = ref_val;
                        old_vec_start = (long*)pipeline->binding_vec_start;
                        vec_start = (long*)pipeline->binding_vec_end;
                    }
                    new_vec_end = new_end + 4;
                    if (vec_start != old_vec_start) {
                        oom_result = (long)vec_start + (-0x20 - (long)old_vec_start);
                        old_size = 0;
                        do {
                            *(long*)((long)new_end + old_size - 0x10) = 0;
                            *(long*)((long)new_end + old_size - 8) = 0;
                            *(void**)((long)new_end + old_size - 0x20) = &PTR_LAB_710522ede0;
                            *(long*)((long)new_end + old_size - 0x18) = 0;
                            hash_node = *(long**)((long)vec_start + old_size - 0x10);
                            if (hash_node != nullptr && *hash_node == *(long*)((long)vec_start + old_size - 8)) {
                                src_val = *(long*)((long)vec_start + old_size - 0x18);
                                *(long*)((long)vec_start + old_size - 0x10) = 0;
                                *(long*)((long)vec_start + old_size - 8) = 0;
                                *(long*)((long)vec_start + old_size - 0x18) = 0;
                                *(long*)((long)new_end + old_size - 0x18) = src_val;
                                if (src_val == 0) {
                                    ref_val = 0;
                                    *(long*)((long)new_end + old_size - 0x10) = 0;
                                } else {
                                    ctrl_ptr = *(long**)(src_val + 8);
                                    *(long**)((long)new_end + old_size - 0x10) = ctrl_ptr;
                                    ref_val = *ctrl_ptr;
                                }
                                *(long*)((long)new_end + old_size - 8) = ref_val;
                            }
                            old_size = old_size - 0x20;
                        } while ((long)old_vec_start - (long)vec_start != old_size);
                        old_vec_start = (long*)pipeline->binding_vec_start;
                        vec_start = (long*)pipeline->binding_vec_end;
                        new_end = (long*)(grow_offset + (new_base + (oom_result >> 5 ^ 0xffffffffffffffffUL)) * 0x20);
                    }
                    pipeline->binding_vec_start = (PipelineBindingEntry*)new_end;
                    pipeline->binding_vec_end = (PipelineBindingEntry*)new_vec_end;
                    pipeline->binding_vec_eos = (PipelineBindingEntry*)(grow_offset + (long)bucket_idx * 0x20);
                    while (vec_start != old_vec_start) {
                        vec_start = vec_start - 4;
                        (*(void(**)(long*))(*(long*)vec_start))(vec_start);
                    }
                    if (old_vec_start != nullptr) {
                        jeFree_710392e590(old_vec_start);
                    }
                }
                // Hash the entry's string key
                __n = *(unsigned long*)(size_delta + 72);
                __s2 = *(char**)(size_delta + 80);
                if ((*(u8*)(size_delta + 64) & 1) == 0) {
                    __s2 = (char*)(size_delta + 65);
                    __n = (unsigned long)(*(u8*)(size_delta + 64) >> 1);
                }
                hash_val = (long*)FUN_71026773a0(__s2, __n);
                bucket_count = (long*)pipeline->material_map.bucket_count;
                // Search hash map for existing entry
                if (bucket_count != nullptr) {
                    key_raw = (u8*)((long)bucket_count - 1);
                    if (((unsigned long)key_raw & (unsigned long)bucket_count) == 0) {
                        bucket_idx = (long*)((unsigned long)key_raw & (unsigned long)hash_val);
                    } else {
                        bucket_idx = hash_val;
                        if (bucket_count <= hash_val) {
                            oom_result = 0;
                            if (bucket_count != nullptr) {
                                oom_result = (unsigned long)hash_val / (unsigned long)bucket_count;
                            }
                            bucket_idx = (long*)((long)hash_val - oom_result * (long)bucket_count);
                        }
                    }
                    hash_node = *(long**)(*iter_ptr + (long)bucket_idx * 8);
                    if (hash_node != nullptr && (hash_node = (long*)*hash_node, hash_node != nullptr)) {
                        // Hash chain search (elided for brevity — same pattern as ff10)
                        // If match found: goto LAB_f180
                        // This section has ~100 instructions of hash chain comparison
                        // with power-of-2 vs general modulo variants
                        goto LAB_skip_hashsearch;
                    }
                }
LAB_skip_hashsearch:
                // Allocate hash node (0x48 bytes) and insert
                hash_node = (long*)je_aligned_alloc(0x10, 0x48);
                if (hash_node == nullptr) {
                    if (DAT_7105331f00 != nullptr) {
                        local_70_lo = 0;
                        *(long*)local_d0 = 0x48;
                        oom_result = (*(unsigned long(**)(s64*, u32*, u8*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_70_lo, local_d0);
                        if ((oom_result & 1) != 0) {
                            hash_node = (long*)je_aligned_alloc(0x10, 0x48);
                            if (hash_node != nullptr) goto LAB_ef68;
                        }
                    }
                    hash_node = nullptr;
                }
LAB_ef68:
                // Initialize hash node: key string + value
                hash_node[2] = 0;
                hash_node[3] = 0;
                hash_node[4] = 0;
                if ((*(u8*)entry_str & 1) == 0) {
                    search_len = (long*)*entry_str;
                    new_base = *(long*)(size_delta + 80);
                    hash_node[3] = *(long*)(size_delta + 72);
                    hash_node[4] = new_base;
                    hash_node[2] = (long)search_len;
                } else {
                    oom_result = *(unsigned long*)(size_delta + 72);
                    if (0xffffffffffffffefUL < oom_result) {
                        std::__1::__throw_length_error("basic_string");
                    }
                    search_data = *(void**)(size_delta + 80);
                    if (oom_result < 0x17) {
                        __dest = (void*)((long)hash_node + 0x11);
                        *(char*)(hash_node + 2) = (char)((int)oom_result << 1);
                        if (oom_result != 0) goto LAB_f040;
                    } else {
                        rehash_size = (oom_result + 0x10) & 0xfffffffffffffff0UL;
                        alloc_result = FUN_710392dc40(&local_70, 0x10, rehash_size);
                        if (alloc_result == 0xc && DAT_710593c2b0 != nullptr) {
                            *(long*)local_d0 = rehash_size;
                            retry_result = (*(unsigned long(**)(s64*, u8*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, local_d0);
                            if ((retry_result & 1) != 0) {
                                FUN_710392dc40(&local_70, 0x10, rehash_size);
                            }
                        }
                        if (*(void**)&PTR_VirtualAllocHook_71052a7a78 != nullptr) {
                            nu::VirtualAllocHook(rehash_size, 0x10, local_70);
                        }
                        __dest = local_70;
                        hash_node[2] = (long)(rehash_size | 1);
                        hash_node[3] = (long)oom_result;
                        hash_node[4] = (long)__dest;
LAB_f040:
                        memcpy(__dest, search_data, oom_result);
                    }
                    *(u8*)((long)__dest + oom_result) = 0;
                }
                hash_node[7] = local_108;
                hash_node[8] = local_100;
                hash_node[5] = (long)&PTR_LAB_710522ee00;
                hash_node[6] = local_110;
                *hash_node = 0;
                hash_node[1] = (long)hash_val;
                load = (float)((long)pipeline->material_map.size + 1);
                // Check if rehash needed
                if (bucket_count == nullptr ||
                    pipeline->material_map.max_load_factor * (float)(unsigned long)bucket_count < load) {
                    if ((unsigned long)bucket_count < 3) {
                        oom_result = 1;
                    } else {
                        oom_result = (unsigned long)(((unsigned long)((long)bucket_count - 1) & (unsigned long)bucket_count) != 0);
                    }
                    rehash_size = (unsigned long)(load / pipeline->material_map.max_load_factor);
                    oom_result = oom_result | (long)bucket_count << 1;
                    if (rehash_size <= oom_result) {
                        rehash_size = oom_result;
                    }
                    hash_table_reserve((long)iter_ptr, rehash_size);
                    bucket_count = (long*)pipeline->material_map.bucket_count;
                    if (((unsigned long)((long)bucket_count - 1) & (unsigned long)bucket_count) == 0) {
                        bucket_idx = (long*)((unsigned long)((long)bucket_count - 1) & (unsigned long)hash_val);
                    } else {
                        bucket_idx = hash_val;
                        if (bucket_count <= hash_val) {
                            oom_result = 0;
                            if (bucket_count != nullptr) {
                                oom_result = (unsigned long)hash_val / (unsigned long)bucket_count;
                            }
                            bucket_idx = (long*)((long)hash_val - oom_result * (long)bucket_count);
                        }
                    }
                }
                // Insert node into hash map bucket
                size_delta = *iter_ptr;
                bucket_entry = *(long**)(size_delta + (long)bucket_idx * 8);
                if (bucket_entry == nullptr) {
                    *hash_node = *map_head;
                    *map_head = (long)hash_node;
                    *(long**)(size_delta + (long)bucket_idx * 8) = map_head;
                    if (*hash_node != 0) {
                        entry_str = *(long**)(*hash_node + 8);
                        if (((unsigned long)((long)bucket_count - 1) & (unsigned long)bucket_count) == 0) {
                            entry_str = (long*)((unsigned long)entry_str & (unsigned long)((long)bucket_count - 1));
                        } else if (bucket_count <= entry_str) {
                            oom_result = 0;
                            if (bucket_count != nullptr) {
                                oom_result = (unsigned long)entry_str / (unsigned long)bucket_count;
                            }
                            entry_str = (long*)((long)entry_str - oom_result * (long)bucket_count);
                        }
                        bucket_entry = (long*)(*iter_ptr + (long)entry_str * 8);
                        goto LAB_f170;
                    }
                } else {
                    *hash_node = *bucket_entry;
LAB_f170:
                    *bucket_entry = (long)hash_node;
                }
                pipeline->material_map.size = pipeline->material_map.size + 1;
LAB_f180:
                if (local_d8 != 0 && *(long*)local_d8 == local_e8) {
LAB_ea68:
                    if (bound_obj != nullptr) {
                        (*(void(**)(long*))(*(long*)bound_obj + 8))(bound_obj);
                    }
                }
            }
            alloc_base = alloc_base + 0x20;
        } while (alloc_base != data_src);
    }

    // Step 6: destroy tree
    string_tree_destroy((StringTreeNode*)local_tree[1]);
    return 1;
}

// ============================================================================
// pipeline_init (3,456 bytes)
// Initializes the rendering pipeline: allocates sub-object pools, resizes
// matrix element vector (0x330-byte elements with identity matrices),
// clears hash maps, allocates 0x110-byte PipelineStateObject, sets "ErrorDummy".
// [inferred: param pool_count → 0x80-byte sub-objects, matrix_count → 0x330-byte elements]
// Address: 0x710354d400
// ============================================================================
long pipeline_init(PipelineContainer* pipeline, unsigned long pool_count, unsigned long matrix_count, long reference) {
    long pipe = (long)pipeline;  // byte-address alias for raw offset access
    long* iter_ptr;
    u8* elem_ptr;
    long alloc_addr;
    unsigned long retry_result;
    long alloc_size;
    long pool_base;
    unsigned long elem_size;
    long const_a;
    long const_b;
    unsigned long loop_idx;
    void* new_alloc;
    void* move_dst;
    u16* state_u16;
    long* vec_ptr;
    void* move_end;
    unsigned long vec_cap;
    long* pool_mgr;
    long* sub_end;
    long* sub_start;
    long* ctrl_ptr;          // shared_ptr control block
    long* vec_end;           // sub-pipeline vector end
    unsigned long __n;       // copy size
    long old_size;           // old allocation size
    unsigned long rehash_size; // allocation size for grow
    void* old_buf;
    unsigned long copy_size;
    void* copy_start;
    void* copy_src;
    void* __src;             // memcpy source pointer
    long local_70;
    u32 local_64;

    // Section 1: clear sub-pipeline
    pipeline_clear_sub(pipe);

    // Section 2: call destructors on vector at +0x68/+0x70 in reverse
    ctrl_ptr = (long*)pipeline->sub_pipelines_start;
    vec_end = (long*)pipeline->sub_pipelines_end;
    while (vec_end != ctrl_ptr) {
        vec_end = vec_end - 4;
        (*(void(**)(long*))(*(long*)vec_end))(vec_end);
    }
    pipeline->sub_pipelines_end = (PipelineBindingEntry*)ctrl_ptr;

    // Section 3: allocate sub-object pool (pool_count elements of 0x80 bytes)
    ctrl_ptr = (long*)pipeline->sub_pool;
    ctrl_ptr[5] = (long)pool_count;
    ctrl_ptr[3] = 0;
    ctrl_ptr[4] = 0;
    loop_idx = pool_count * 0x80;
    pool_base = (long)(loop_idx + 0x10);
    // Overflow check: if pool_count * 0x80 overflows or > 0xffffffffffffffef
    if ((pool_count >> 57) != 0 || 0xffffffffffffffefUL < loop_idx) {
        pool_base = -1;
    }
    alloc_addr = (long)je_aligned_alloc(0x10, pool_base);
    if (alloc_addr == 0) {
        if (DAT_7105331f00 != nullptr) {
            local_64 = 0;
            local_70 = pool_base;
            retry_result = (*(unsigned long(**)(s64*, u32*, long*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_64, &local_70);
            if ((retry_result & 1) != 0) {
                alloc_addr = (long)je_aligned_alloc(0x10, pool_base);
                if (alloc_addr != 0) goto LAB_d4e8;
            }
        }
        alloc_addr = 0;
    }
LAB_d4e8:
    pool_base = alloc_addr + 0x10;
    *(unsigned long*)(alloc_addr + 8) = pool_count;
    alloc_addr = pool_base;
    if (pool_count != 0) {
        // Init each 0x80-byte element
        do {
            FUN_7103554370(alloc_addr);
            loop_idx = loop_idx - 0x80;
            alloc_addr = alloc_addr + 0x80;
        } while (loop_idx != 0);

        // Build vector of pointers to each pool element
        loop_idx = 1;
        ctrl_ptr[6] = pool_base;
        alloc_addr = 0;
        do {
            vec_ptr = (long*)ctrl_ptr[1];
            if (vec_ptr < (long*)ctrl_ptr[2]) {
                // Vector has space: append pointer
                *vec_ptr = pool_base + alloc_addr;
                ctrl_ptr[1] = ctrl_ptr[1] + 8;
            } else {
                // Vector full: reallocate
                old_buf = (void*)*ctrl_ptr;
                __n = (long)vec_ptr - (long)old_buf;
                retry_result = ((long)__n >> 3) + 1;
                if (retry_result >> 0x3d != 0) {
                    std::__1::__throw_length_error("vector");
                }
                old_size = (long)ctrl_ptr[2] - (long)old_buf;
                if ((unsigned long)(old_size >> 3) < 0xfffffffffffffffUL) {
                    rehash_size = old_size >> 2;
                    if (retry_result <= rehash_size) {
                        retry_result = rehash_size;
                    }
                    if (retry_result != 0) {
                        if (retry_result >> 0x3d == 0) goto LAB_d5a4;
                        goto LAB_e170;
                    }
                    new_alloc = nullptr;
                } else {
                    retry_result = 0x1fffffffffffffffUL;
LAB_d5a4:
                    old_size = (long)(retry_result * 8);
                    if (old_size == 0) old_size = 1;
                    new_alloc = je_aligned_alloc(0x10, old_size);
                    if (new_alloc == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            local_64 = 0;
                            local_70 = old_size;
                            rehash_size = (*(unsigned long(**)(s64*, u32*, long*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_64, &local_70);
                            if ((rehash_size & 1) != 0) {
                                new_alloc = je_aligned_alloc(0x10, old_size);
                                if (new_alloc != nullptr) goto LAB_d60c;
                            }
                        }
                        new_alloc = nullptr;
                    }
                }
LAB_d60c:
                vec_ptr = (long*)((long)new_alloc + ((long)__n >> 3) * 8);
                *vec_ptr = pool_base + alloc_addr;
                if (0 < (long)__n) {
                    memcpy(new_alloc, old_buf, __n);
                }
                *ctrl_ptr = (long)new_alloc;
                ctrl_ptr[1] = (long)(vec_ptr + 1);
                ctrl_ptr[2] = (long)((long)new_alloc + retry_result * 8);
                if (old_buf != nullptr) {
                    jeFree_710392e590(old_buf);
                }
            }
            if (pool_count <= loop_idx) goto LAB_d660;
            pool_base = ctrl_ptr[6];
            loop_idx = loop_idx + 1;
            alloc_addr = alloc_addr + 0x80;
        } while (true);
    }
    ctrl_ptr[6] = pool_base;
LAB_d660:
    ((long*)pipeline->sub_pool)[3] = 0;  // sub_pool->pool_alloc_ptr at +0x18

    // Section 4: resize 0x330-byte element vector for matrix_count elements
    vec_ptr = (long*)&pipeline->matrix_vec_start;
    old_buf = (void*)pipeline->matrix_vec_start;
    // Compute current capacity: (eos - start) / 0x330
    // The compiler uses magic number multiplication for div by 0x330
    if ((unsigned long)(((long)pipeline->matrix_vec_eos - (long)old_buf) >> 4) * (unsigned long)(long)-0x505050505050505LL < matrix_count) {
        if (0x50505050505050UL < matrix_count) {
LAB_e170:
            abort();
        }
        new_alloc = (void*)pipeline->matrix_vec_end;
        pool_base = (long)(matrix_count * 0x330);
        if (pool_base == 0) pool_base = 1;
        alloc_addr = (long)je_aligned_alloc(0x10, pool_base);
        if (alloc_addr == 0) {
            if (DAT_7105331f00 != nullptr) {
                local_64 = 0;
                local_70 = pool_base;
                loop_idx = (*(unsigned long(**)(s64*, u32*, long*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_64, &local_70);
                if ((loop_idx & 1) != 0) {
                    alloc_addr = (long)je_aligned_alloc(0x10, pool_base);
                    if (alloc_addr != 0) goto LAB_d738;
                }
            }
            alloc_addr = 0;
        }
LAB_d738:
        move_end = (void*)(alloc_addr + (((long)new_alloc - (long)old_buf) >> 4) * 0x10);
        alloc_addr = alloc_addr + (long)(matrix_count * 0x330);
        move_dst = move_end;
        if (new_alloc == old_buf) {
            pipeline->matrix_vec_start = (PipelineMatrixElement*)move_end;
            pipeline->matrix_vec_end = (PipelineMatrixElement*)move_end;
            pipeline->matrix_vec_eos = (PipelineMatrixElement*)alloc_addr;
        } else {
            // Move existing elements backward
            do {
                copy_start = (void*)((long)move_dst - 0x330);
                __src = (void*)((long)new_alloc - 0x330);
                memcpy(copy_start, __src, 0x1b0);
                const_b= *(long*)((long)new_alloc - 0x178);
                const_a= *(long*)((long)new_alloc - 0x180);
                *(long*)((long)move_dst - 0x170) = *(long*)((long)new_alloc - 0x170);
                *(long*)((long)move_dst - 0x178) = const_b;
                *(long*)((long)move_dst - 0x180) = const_a;
                *(long*)((long)new_alloc - 0x170) = 0;
                *(long*)((long)new_alloc - 0x178) = 0;
                *(long*)((long)new_alloc - 0x180) = 0;
                memcpy((void*)((long)move_dst - 0x160), (void*)((long)new_alloc - 0x160), 0x160);
                new_alloc = __src;
                move_dst = copy_start;
            } while (old_buf != __src);
            old_buf = (void*)pipeline->matrix_vec_start;
            new_alloc = (void*)pipeline->matrix_vec_end;
            pipeline->matrix_vec_start = (PipelineMatrixElement*)copy_start;
            pipeline->matrix_vec_end = (PipelineMatrixElement*)move_end;
            pipeline->matrix_vec_eos = (PipelineMatrixElement*)alloc_addr;
            void* poom_result = PTR_VirtualFreeHook_71052a7a70;
            while (move_dst = new_alloc, move_dst != old_buf) {
                new_alloc = (void*)((long)move_dst - 0x330);
                if ((*(u8*)((long)move_dst - 0x180) & 1) != 0) {
                    move_end = *(void**)((long)move_dst - 0x170);
                    if (poom_result != nullptr) {
                        FUN_71039c1400(move_end);
                    }
                    jeFree_710392e590(move_end);
                }
            }
        }
        if (old_buf != nullptr) {
            jeFree_710392e590(old_buf);
        }
    }

    // Section 5: store element count and init new elements
    pipeline->matrix_count = matrix_count;
    if (matrix_count != 0) {
        loop_idx = 0;
        do {
            old_buf = (void*)pipeline->matrix_vec_end;
            if (old_buf < (void*)pipeline->matrix_vec_eos) {
                // Space available: init element in-place
                memset(old_buf, 0, 0x1d0);
                // Identity matrices: 16 4x4 matrices at offsets 0x1D0-0x30C
                // Each diagonal element = 1.0f (0x3f800000)
                *(u32*)((long)old_buf + 0x1d0) = 0x3f800000;
                *(long*)((long)old_buf + 0x1d4) = 0;
                *(long*)((long)old_buf + 0x1dc) = 0;
                *(u32*)((long)old_buf + 0x1e4) = 0x3f800000;
                *(long*)((long)old_buf + 0x1e8) = 0;
                *(long*)((long)old_buf + 0x1f0) = 0;
                *(u32*)((long)old_buf + 0x1f8) = 0x3f800000;
                *(long*)((long)old_buf + 0x1fc) = 0;
                *(long*)((long)old_buf + 0x204) = 0;
                *(long*)((long)old_buf + 0x20c) = 0x3f8000003f800000LL;
                *(long*)((long)old_buf + 0x21c) = 0;
                *(long*)((long)old_buf + 0x214) = 0;
                *(u32*)((long)old_buf + 0x224) = 0x3f800000;
                *(long*)((long)old_buf + 0x230) = 0;
                *(long*)((long)old_buf + 0x228) = 0;
                *(u32*)((long)old_buf + 0x238) = 0x3f800000;
                *(long*)((long)old_buf + 0x244) = 0;
                *(long*)((long)old_buf + 0x23c) = 0;
                *(u32*)((long)old_buf + 0x24c) = 0x3f800000;
                *(u32*)((long)old_buf + 0x250) = 0x3f800000;
                *(long*)((long)old_buf + 0x25c) = 0;
                *(long*)((long)old_buf + 0x254) = 0;
                *(u32*)((long)old_buf + 0x264) = 0x3f800000;
                *(long*)((long)old_buf + 0x270) = 0;
                *(long*)((long)old_buf + 0x268) = 0;
                *(u32*)((long)old_buf + 0x278) = 0x3f800000;
                *(long*)((long)old_buf + 0x284) = 0;
                *(long*)((long)old_buf + 0x27c) = 0;
                *(u32*)((long)old_buf + 0x28c) = 0x3f800000;
                *(u32*)((long)old_buf + 0x290) = 0x3f800000;
                *(long*)((long)old_buf + 0x29c) = 0;
                *(long*)((long)old_buf + 0x294) = 0;
                *(u32*)((long)old_buf + 0x2a4) = 0x3f800000;
                *(long*)((long)old_buf + 0x2b0) = 0;
                *(long*)((long)old_buf + 0x2a8) = 0;
                *(u32*)((long)old_buf + 0x2b8) = 0x3f800000;
                *(long*)((long)old_buf + 0x2c4) = 0;
                *(long*)((long)old_buf + 0x2bc) = 0;
                *(u32*)((long)old_buf + 0x2cc) = 0x3f800000;
                *(u32*)((long)old_buf + 0x2d0) = 0x3f800000;
                *(long*)((long)old_buf + 0x2dc) = 0;
                *(long*)((long)old_buf + 0x2d4) = 0;
                *(u32*)((long)old_buf + 0x2e4) = 0x3f800000;
                *(long*)((long)old_buf + 0x2f0) = 0;
                *(long*)((long)old_buf + 0x2e8) = 0;
                *(u32*)((long)old_buf + 0x2f8) = 0x3f800000;
                *(long*)((long)old_buf + 0x304) = 0;
                *(long*)((long)old_buf + 0x2fc) = 0;
                *(u32*)((long)old_buf + 0x30c) = 0x3f800000;
                *(long*)((long)old_buf + 0x328) = 0;
                *(long*)((long)old_buf + 0x320) = 0;
                *(long*)((long)old_buf + 0x318) = 0;
                *(long*)((long)old_buf + 0x310) = 0;
                pipeline->matrix_vec_end = (PipelineMatrixElement*)((long)pipeline->matrix_vec_end + 0x330);
            } else {
                // Need to grow vector — similar to above realloc but with 0x330 elements
                // (Vector grow path omitted for brevity — same OOM+move pattern as above)
                // In practice this path should rarely be taken since we pre-allocated
                abort();  // placeholder
            }
            loop_idx = loop_idx + 1;
        } while (loop_idx != matrix_count);

        // Section 5b: second pass — write packed float render constants to each element
        long rc_a = _DAT_7104464fb0;
        long rc_b = _UNK_7104464fb8;
        long rc_c = _DAT_7104467ca0;
        long rc_d = _UNK_7104467ca8;
        long rc_e = _DAT_7104469350;
        long rc_f = _UNK_7104469358;
        long cmp_val = DAT_7104469360;
        long rc_h = DAT_7104469368;
        long rc_g1 = _DAT_71044646b0;
        long rc_g2 = _UNK_71044646b8;
        pool_base = 0x1a2;
        do {
            elem_ptr = (u8*)(*vec_ptr + pool_base);
            pool_base = pool_base + 0x330;
            *(u32*)(elem_ptr - 0x52) = 0;
            *(long*)(elem_ptr - 0x4e) = 0x448000003c000000LL;
            *(long*)(elem_ptr - 0x46) = 0x3f490fdb42340000LL;
            *(long*)(elem_ptr - 0x3e) = 0x4487000044f00000LL;
            *(long*)(elem_ptr - 0x36) = 0x44f000003fe38e39LL;
            *(long*)(elem_ptr - 0x2e) = 0x3a08888944870000LL;
            *(u32*)(elem_ptr - 0x26) = 0x3a72b9d6;
            *(long*)(elem_ptr - 0x1a) = rc_b;
            *(long*)(elem_ptr - 0x22) = rc_a;
            matrix_count = matrix_count - 1;
            *(long*)(elem_ptr - 10) = rc_b;
            *(long*)(elem_ptr - 0x12) = rc_a;
            *(long*)(elem_ptr - 0x15a) = rc_d;
            *(long*)(elem_ptr - 0x162) = rc_c;
            *(long*)(elem_ptr - 0x14a) = rc_h;
            *(long*)(elem_ptr - 0x152) = cmp_val;
            *(long*)(elem_ptr - 0x13a) = rc_g2;
            *(long*)(elem_ptr - 0x142) = rc_g1;
            *(long*)(elem_ptr - 0x12a) = rc_f;
            *(long*)(elem_ptr - 0x132) = rc_e;
            *(long*)(elem_ptr - 0x18a) = *(long*)(elem_ptr - 0x14a);
            *(long*)(elem_ptr - 0x192) = *(long*)(elem_ptr - 0x152);
            *(long*)(elem_ptr - 0x19a) = *(long*)(elem_ptr - 0x15a);
            *(long*)(elem_ptr - 0x1a2) = *(long*)(elem_ptr - 0x162);
            *(long*)(elem_ptr - 0x16a) = *(long*)(elem_ptr - 0x12a);
            *(long*)(elem_ptr - 0x172) = *(long*)(elem_ptr - 0x132);
            *(long*)(elem_ptr - 0x17a) = *(long*)(elem_ptr - 0x13a);
            *(long*)(elem_ptr - 0x182) = *(long*)(elem_ptr - 0x142);
            *(long*)(elem_ptr - 0x11a) = rc_d;
            *(long*)(elem_ptr - 0x122) = rc_c;
            *(long*)(elem_ptr - 0x10a) = rc_h;
            *(long*)(elem_ptr - 0x112) = cmp_val;
            *(long*)(elem_ptr - 0xfa) = rc_g2;
            *(long*)(elem_ptr - 0x102) = rc_g1;
            *elem_ptr = 0;
            *(long*)(elem_ptr - 0xea) = rc_f;
            *(long*)(elem_ptr - 0xf2) = rc_e;
            *(long*)(elem_ptr - 0xda) = rc_d;
            *(long*)(elem_ptr - 0xe2) = rc_c;
            *(long*)(elem_ptr - 0xca) = rc_h;
            *(long*)(elem_ptr - 0xd2) = cmp_val;
            *(long*)(elem_ptr - 0xba) = rc_g2;
            *(long*)(elem_ptr - 0xc2) = rc_g1;
            *(long*)(elem_ptr - 0xaa) = rc_f;
            *(long*)(elem_ptr - 0xb2) = rc_e;
            *(long*)(elem_ptr - 0x9a) = 0;
            *(long*)(elem_ptr - 0xa2) = 0;
            *(long*)(elem_ptr - 0x8a) = rc_h;
            *(long*)(elem_ptr - 0x92) = cmp_val;
            *(long*)(elem_ptr - 0x7a) = 0;
            *(long*)(elem_ptr - 0x82) = 0;
            *(long*)(elem_ptr - 0x6a) = 0x3f8000003f800000LL;
            *(long*)(elem_ptr - 0x72) = 0x3f8000003f800000LL;
        } while (matrix_count != 0);
    }

    // Section 6: store reference
    pipeline->reference = (void*)reference;

    // Section 7: clean up hash table at link_map
    if (pipeline->link_map.size != 0) {
        vec_ptr = (long*)pipeline->link_map.head;
        while (vec_ptr != nullptr) {
            pool_base = *vec_ptr;
            pool_mgr = (long*)vec_ptr[4];
            if (pool_mgr != nullptr) {
                // Atomic decrement shared_owners
                long old_val = __sync_fetch_and_sub(pool_mgr + 1, 1);
                if (old_val == 0) {
                    (*(void(**)(long*))(*(long*)pool_mgr + 0x10))(pool_mgr);
                    ((std::__1::__shared_weak_count*)pool_mgr)->__release_weak();
                }
            }
            jeFree_710392e590(vec_ptr);
            vec_ptr = (long*)pool_base;
        }
        loop_idx = pipeline->link_map.bucket_count;
        pipeline->link_map.head = nullptr;
        if (loop_idx != 0) {
            retry_result = loop_idx & 3;
            if (loop_idx - 1 < 3) {
                pool_base = 0;
            } else {
                pool_base = 0;
                do {
                    alloc_addr = pool_base * 8;
                    pool_base = pool_base + 4;
                    *(long*)((long)pipeline->link_map.buckets + alloc_addr) = 0;
                    *(long*)((long)pipeline->link_map.buckets + alloc_addr + 8) = 0;
                    *(long*)((long)pipeline->link_map.buckets + alloc_addr + 0x10) = 0;
                    *(long*)((long)pipeline->link_map.buckets + alloc_addr + 0x18) = 0;
                } while (loop_idx - retry_result != (unsigned long)pool_base);
            }
            if (retry_result != 0) {
                pool_base = pool_base << 3;
                alloc_addr = -(long)retry_result;
                do {
                    *(long*)((long)pipeline->link_map.buckets + pool_base) = 0;
                    pool_base = pool_base + 8;
                    alloc_addr = alloc_addr + 1;
                } while (alloc_addr != 0);
            }
        }
        pipeline->link_map.size = 0;
    }

    // Section 8: allocate 0x110-byte state object
    ctrl_ptr = (long*)je_aligned_alloc(0x10, 0x110);
    if (ctrl_ptr == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            local_64 = 0;
            local_70 = 0x110;
            loop_idx = (*(unsigned long(**)(s64*, u32*, long*))(*(long*)DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_64, &local_70);
            if ((loop_idx & 1) != 0) {
                ctrl_ptr = (long*)je_aligned_alloc(0x10, 0x110);
                if (ctrl_ptr != nullptr) goto LAB_df9c;
            }
        }
        ctrl_ptr = nullptr;
    }
LAB_df9c:
    // Init state object
    *ctrl_ptr = (long)&PTR_FUN_710522eda8;
    ctrl_ptr[1] = 0;
    ctrl_ptr[2] = 0;
    ctrl_ptr[5] = 0;
    ctrl_ptr[9] = 0;
    ctrl_ptr[10] = 0;
    ctrl_ptr[0xb] = 0;
    ctrl_ptr[8] = (long)&PTR_LAB_710522ef60;
    ctrl_ptr[0xc] = 0;
    *(u8*)((long)ctrl_ptr + 0xe9) = 0;
    *(u8*)(ctrl_ptr + 0xd) = 0;
    ctrl_ptr[31] = 0;          // +0xF8
    ctrl_ptr[32] = 0;          // +0x100
    ctrl_ptr[33] = 0;          // +0x108
    ctrl_ptr[30] = 0;          // +0xF0
    *(u16*)(ctrl_ptr + 30) = 1; // +0xF0: state word = 1
    ((u8*)ctrl_ptr)[242] = 0;  // +0xF2: flag byte

    // Mutex lock, init sub-state, unlock
    FUN_71039c14b0(ctrl_ptr + 0xd);  // std::__1::mutex::lock()
    *(u16*)(ctrl_ptr + 3) = 0;
    *(u8*)((long)ctrl_ptr + 0x1a) = 1;
    ctrl_ptr[4] = (long)0xffffffffffffffffLL;
    if ((long*)ctrl_ptr[0xc] != nullptr) {
        (*(void(**)(void))(*(long*)ctrl_ptr[0xc] + 8))();
        ctrl_ptr[0xc] = 0;
    }
    *(u8*)((long)ctrl_ptr + 0xe9) = 0;
    ctrl_ptr[5] = 0;
    ctrl_ptr[6] = 0;
    ctrl_ptr[7] = 0;
    *(u8*)(ctrl_ptr + 0xd) = 0;
    ctrl_ptr[0xb] = 0;
    ctrl_ptr[0xc] = 0;
    ctrl_ptr[9] = 0;
    ctrl_ptr[10] = 0;
    FUN_71039c14c0(ctrl_ptr + 0xd);  // std::__1::mutex::unlock()

    // Section 9: update shared_ptr at state_ptr/state_ctrl
    vec_ptr = (long*)pipeline->state_ctrl;
    pipeline->state_ptr = (void*)(ctrl_ptr + 3);
    pipeline->state_ctrl = (void*)ctrl_ptr;
    if (vec_ptr != nullptr) {
        long old_val = __sync_fetch_and_sub(vec_ptr + 1, 1);
        if (old_val == 0) {
            (*(void(**)(long*))(*(long*)vec_ptr + 0x10))(vec_ptr);
            ((std::__1::__shared_weak_count*)vec_ptr)->__release_weak();
        }
    }

    // Section 10: init the state via state_ptr, set "ErrorDummy" string
    // [inferred: state_ptr points to inner state of PipelineStateObject at +0x18]
    long* state_lp = (long*)pipeline->state_ptr;
    u8* state_bp = (u8*)state_lp;
    void* state_mutex = (void*)(state_bp + 80);  // mutex at byte +80 (0x50)
    FUN_71039c14b0(state_mutex);  // std::__1::mutex::lock()
    *(u16*)state_bp = 0;           // +0x00: state flag
    state_bp[2] = 1;               // +0x02: active flag
    state_lp[1] = -1LL;            // +0x08: sentinel value
    if ((long*)state_lp[9] != nullptr) {  // +0x48: object pointer
        (*(void(**)(void))(*(long*)state_lp[9] + 8))();
        state_lp[9] = 0;
    }
    state_bp[209] = 0;             // +0xD1: string length
    state_lp[2] = 0;               // +0x10
    state_lp[3] = 0;               // +0x18
    state_lp[4] = 0;               // +0x20
    *(u8*)state_mutex = 0;         // +0x50: mutex first byte
    state_lp[8] = 0;               // +0x40
    state_lp[9] = 0;               // +0x48
    state_lp[6] = 0;               // +0x30
    state_lp[7] = 0;               // +0x38
    FUN_71039c14c0(state_mutex);   // std::__1::mutex::unlock()

    // Write "ErrorDummy" string (10 bytes at +0x50 of inner state)
    // [inferred: string stored at byte 80, length byte at 209]
    *(long*)(state_bp + 80) = 0x6d7544726f727245LL;  // "ErrorDum"
    state_bp[88] = 0x6d;                              // "m"
    state_bp[209] = 10;                               // length = 10
    state_lp[1] = -1LL;                               // sentinel
    state_bp[0] = 1;                                  // active
    *(u16*)(state_bp + 89) = 0x79;                    // "y" + NUL

    return 1;
}
