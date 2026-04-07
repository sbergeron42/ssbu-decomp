// res_pipeline_medium.cpp — Rendering pipeline container operations
// Pool-d assignment: material binding hash map, string tree ops, pipeline init/update
// These functions manage material parameter binding for the cross2app rendering engine,
// using std::unordered_map (hash table) and std::set (red-black tree) containers.
// Strings: "UpdateInkThreshold", "UpdateInkColor", "UpdateResetInk" — ink rendering system.
// See WORKER.md for full target list.

#include "types.h"

// ============================================================================
// External declarations
// ============================================================================

// Memory management
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
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
extern "C" void FUN_710354e180(long);
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
void FUN_710354f200(long param_1);
void FUN_710354f380(long param_1, unsigned long param_2);
void FUN_710354f470(long* param_1, long* param_2, u8* param_3, u8* param_4);
void FUN_710354f900(long* param_1);
long* FUN_710354fa40(long param_1, long* param_2, u8* param_3);

// ============================================================================
// FUN_710354f900 — tree_destroy_recursive (320 bytes)
// Recursively destroys all nodes in a red-black tree (std::set<std::string>).
// ============================================================================
void FUN_710354f900(long* param_1) {
    void* pvVar1;
    if (param_1 != nullptr) {
        FUN_710354f900((long*)*param_1);
        FUN_710354f900((long*)param_1[1]);
        if ((*(u8*)(param_1 + 4) & 1) != 0) {
            pvVar1 = (void*)param_1[6];
            if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                FUN_71039c1400(pvVar1);
            }
            FUN_710392e590(pvVar1);
        }
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400((void*)param_1);
        }
        FUN_710392e590((void*)param_1);
    }
}

// ============================================================================
// FUN_710354fa40 — tree_lower_bound (304 bytes)
// Finds lower bound position in red-black tree with string keys.
// ============================================================================
long* FUN_710354fa40(long param_1, long* param_2, u8* param_3) {
    unsigned long uVar1;
    unsigned long __n;
    unsigned long uVar2;
    u8* __s1;
    u8 bVar3;
    int iVar4;
    void* __s2;
    long* plVar5;
    long* plVar6;
    long* plVar7;

    plVar5 = (long*)(param_1 + 8);
    plVar6 = (long*)*plVar5;
    if (plVar6 == nullptr) {
        *param_2 = (long)plVar5;
        return plVar5;
    }
    uVar2 = *(unsigned long*)(param_3 + 8);
    __s1 = *(u8**)(param_3 + 0x10);
    plVar5 = (long*)(param_1 + 8);
    if ((*param_3 & 1) == 0) {
        __s1 = param_3 + 1;
        uVar2 = (unsigned long)(*param_3 >> 1);
    }
    do {
        while (true) {
            plVar7 = plVar6;
            bVar3 = *(u8*)(plVar7 + 4);
            uVar1 = (unsigned long)(bVar3 >> 1);
            if ((bVar3 & 1) != 0) {
                uVar1 = (unsigned long)plVar7[5];
            }
            __n = uVar1;
            if (uVar2 <= uVar1) {
                __n = uVar2;
            }
            if (__n == 0) break;
            __s2 = (void*)plVar7[6];
            if ((bVar3 & 1) == 0) {
                __s2 = (void*)((long)plVar7 + 0x21);
            }
            iVar4 = memcmp(__s1, __s2, __n);
            if (iVar4 == 0) break;
            if (iVar4 < 0) goto LAB_fae4;
LAB_fb04:
            iVar4 = memcmp(__s2, __s1, __n);
            if (iVar4 == 0) goto LAB_fb20;
            if (-1 < iVar4) goto LAB_fb34;
LAB_fb28:
            plVar5 = plVar7 + 1;
            plVar6 = (long*)*plVar5;
            if ((long*)*plVar5 == nullptr) {
LAB_fb34:
                *param_2 = (long)plVar7;
                return plVar5;
            }
        }
        if (uVar1 <= uVar2) {
            if (__n != 0) {
                __s2 = (void*)plVar7[6];
                if ((bVar3 & 1) == 0) {
                    __s2 = (void*)((long)plVar7 + 0x21);
                }
                goto LAB_fb04;
            }
LAB_fb20:
            if (uVar2 <= uVar1) goto LAB_fb34;
            goto LAB_fb28;
        }
LAB_fae4:
        plVar5 = plVar7;
        plVar6 = (long*)*plVar7;
        if ((long*)*plVar7 == nullptr) {
            *param_2 = (long)plVar7;
            return plVar7;
        }
    } while (true);
}

// ============================================================================
// FUN_710354f380 — hash_table_reserve (240 bytes)
// ============================================================================
void FUN_710354f380(long param_1, unsigned long param_2) {
    unsigned long uVar1;
    unsigned long uVar2;

    if (param_2 - 1 == 0) {
        param_2 = 2;
    } else if ((param_2 - 1 & param_2) != 0) {
        param_2 = std::__1::__next_prime(param_2);
    }
    uVar2 = *(unsigned long*)(param_1 + 8);
    uVar1 = param_2;
    if (uVar2 < param_2) {
LAB_f444:
        FUN_710354fb70((long*)param_1, uVar1);
        return;
    }
    if (param_2 < uVar2) {
        uVar1 = (unsigned long)((float)*(unsigned long*)(param_1 + 0x18) / *(float*)(param_1 + 0x20));
        if (uVar2 < 3 || (uVar2 - 1 & uVar2) != 0) {
            uVar1 = std::__1::__next_prime(uVar1);
        } else if (1 < uVar1) {
            uVar1 = 1UL << ((-__builtin_clzl(uVar1 - 1)) & 0x3fU);
        }
        if (uVar1 <= param_2) {
            uVar1 = param_2;
        }
        if (uVar1 < uVar2) goto LAB_f444;
    }
}

// ============================================================================
// FUN_710354f200 — pipeline_clear_material_map (384 bytes)
// ============================================================================
void FUN_710354f200(long param_1) {
    long* plVar1;
    long* puVar2;
    long* plVar3;
    void* puVar4;
    unsigned long uVar5;
    long lVar6;
    long lVar7;
    unsigned long uVar8;
    long* puVar9;
    void* pvVar10;
    long lVar11;

    lVar6 = *(long*)(param_1 + 0xC8);
    puVar4 = PTR_VirtualFreeHook_71052a7a70;
    for (lVar11 = *(long*)(param_1 + 0xC0); PTR_VirtualFreeHook_71052a7a70 = puVar4, lVar11 != lVar6;
         lVar11 = lVar11 + 0x20) {
        plVar1 = *(long**)(lVar11 + 8);
        plVar3 = *(long**)(lVar11 + 0x10);
        lVar7 = *(long*)(lVar11 + 0x18);
        *(long*)(lVar11 + 8) = 0;
        *(long*)(lVar11 + 0x10) = 0;
        *(long*)(lVar11 + 0x18) = 0;
        if (plVar3 != nullptr && plVar1 != nullptr && *plVar3 == lVar7) {
            (*(void(**)(void))(*(long*)plVar1 + 8))();
        }
        puVar4 = PTR_VirtualFreeHook_71052a7a70;
    }
    if (*(long*)(param_1 + 0xB0) != 0) {
        plVar1 = (long*)*(long*)(param_1 + 0xA8);
        while (plVar1 != nullptr) {
            lVar11 = *plVar1;
            if ((*(u8*)(plVar1 + 2) & 1) != 0) {
                pvVar10 = (void*)plVar1[4];
                if (puVar4 != nullptr) {
                    FUN_71039c1400(pvVar10);
                }
                FUN_710392e590(pvVar10);
            }
            FUN_710392e590((void*)plVar1);
            plVar1 = (long*)lVar11;
        }
        uVar8 = *(unsigned long*)(param_1 + 0xA0);
        *(long*)(param_1 + 0xA8) = 0;
        if (uVar8 != 0) {
            uVar5 = uVar8 & 3;
            if (uVar8 - 1 < 3) {
                lVar11 = 0;
            } else {
                lVar11 = 0;
                do {
                    lVar6 = lVar11 * 8;
                    lVar11 = lVar11 + 4;
                    *(long*)(*(long*)(param_1 + 0x98) + lVar6) = 0;
                    *(long*)(*(long*)(param_1 + 0x98) + lVar6 + 8) = 0;
                    *(long*)(*(long*)(param_1 + 0x98) + lVar6 + 0x10) = 0;
                    *(long*)(*(long*)(param_1 + 0x98) + lVar6 + 0x18) = 0;
                } while (uVar8 - uVar5 != (unsigned long)lVar11);
            }
            if (uVar5 != 0) {
                lVar11 = lVar11 << 3;
                lVar6 = -(long)uVar5;
                do {
                    *(long*)(*(long*)(param_1 + 0x98) + lVar11) = 0;
                    lVar11 = lVar11 + 8;
                    lVar6 = lVar6 + 1;
                } while (lVar6 != 0);
            }
        }
        *(long*)(param_1 + 0xB0) = 0;
    }
    puVar2 = *(long**)(param_1 + 0xC0);
    puVar9 = *(long**)(param_1 + 0xC8);
    while (puVar9 != puVar2) {
        puVar9 = puVar9 - 4;
        (*(void(**)(long*))(*(long*)puVar9))(puVar9);
    }
    *(long**)(param_1 + 0xC8) = puVar2;
}

// ============================================================================
// FUN_710354f470 — tree_insert_unique (1,168 bytes)
// ============================================================================
void FUN_710354f470(long* param_1, long* param_2, u8* param_3, u8* param_4) {
    unsigned long sVar1;
    long uVar2;
    u8 bVar3;
    u8 bVar4;
    void* puVar5;
    bool bVar6;
    int iVar7;
    long* plVar8;
    unsigned long uVar9;
    unsigned long uVar10;
    u8* pbVar11;
    void* pvVar12;
    long* plVar13;
    long uVar14;
    long lVar15;
    long* plVar17;
    long* plVar18;
    unsigned long uVar19;
    void* __dest;
    long local_80;
    long local_78;
    void* local_70;
    unsigned long local_68;

    if (param_1 + 1 == param_2) {
        goto LAB_f520;
    }
    bVar3 = *(u8*)(param_2 + 4);
    bVar4 = *param_3;
    uVar9 = (unsigned long)(bVar3 >> 1);
    if ((bVar3 & 1) != 0) {
        uVar9 = (unsigned long)param_2[5];
    }
    uVar19 = (unsigned long)(bVar4 >> 1);
    if ((bVar4 & 1) != 0) {
        uVar19 = *(unsigned long*)(param_3 + 8);
    }
    sVar1 = uVar9;
    if (uVar19 <= uVar9) {
        sVar1 = uVar19;
    }
    if (sVar1 == 0) {
LAB_f518:
        if (uVar19 < uVar9) goto LAB_f520;
        if (sVar1 != 0) {
            pvVar12 = (void*)param_2[6];
            pbVar11 = *(u8**)(param_3 + 0x10);
            if ((bVar3 & 1) == 0) {
                pvVar12 = (void*)((long)param_2 + 0x21);
            }
            if ((bVar4 & 1) == 0) {
                pbVar11 = param_3 + 1;
            }
            goto LAB_f56c;
        }
LAB_f598:
        if (uVar9 < uVar19) {
LAB_f5a0:
            plVar8 = param_2 + 1;
            plVar13 = (long*)*plVar8;
            if ((long*)*plVar8 == nullptr) {
                plVar13 = param_2 + 2;
                plVar18 = (long*)*plVar13;
                if ((long*)*plVar18 != param_2) {
                    do {
                        lVar15 = *plVar13;
                        plVar13 = (long*)(lVar15 + 0x10);
                        plVar18 = (long*)*plVar13;
                    } while (*plVar18 != lVar15);
                }
            } else {
                do {
                    plVar18 = plVar13;
                    plVar13 = (long*)*plVar18;
                } while ((long*)*plVar18 != nullptr);
            }
            if (plVar18 != param_1 + 1) {
                bVar3 = *(u8*)(plVar18 + 4);
                uVar9 = (unsigned long)(bVar3 >> 1);
                if ((bVar3 & 1) != 0) {
                    uVar9 = (unsigned long)plVar18[5];
                }
                sVar1 = uVar9;
                if (uVar19 <= uVar9) {
                    sVar1 = uVar19;
                }
                if (sVar1 != 0) {
                    pbVar11 = *(u8**)(param_3 + 0x10);
                    if ((bVar4 & 1) == 0) {
                        pbVar11 = param_3 + 1;
                    }
                    pvVar12 = (void*)plVar18[6];
                    if ((bVar3 & 1) == 0) {
                        pvVar12 = (void*)((long)plVar18 + 0x21);
                    }
                    iVar7 = memcmp(pbVar11, pvVar12, sVar1);
                    if (iVar7 != 0) {
                        if (-1 < iVar7) goto LAB_f6f0;
                        goto LAB_f718;
                    }
                }
                if (uVar9 <= uVar19) goto LAB_f6f0;
            }
LAB_f718:
            if (param_2[1] == 0) {
                lVar15 = *plVar8;
                local_78 = (long)param_2;
            } else {
                lVar15 = *plVar18;
                plVar8 = plVar18;
                local_78 = (long)plVar18;
            }
            goto joined;
        }
    } else {
        pbVar11 = *(u8**)(param_3 + 0x10);
        if ((bVar4 & 1) == 0) {
            pbVar11 = param_3 + 1;
        }
        pvVar12 = (void*)param_2[6];
        if ((bVar3 & 1) == 0) {
            pvVar12 = (void*)((long)param_2 + 0x21);
        }
        iVar7 = memcmp(pbVar11, pvVar12, sVar1);
        if (iVar7 == 0) goto LAB_f518;
        if (iVar7 < 0) goto LAB_f520;
LAB_f56c:
        iVar7 = memcmp(pvVar12, pbVar11, sVar1);
        if (iVar7 == 0) goto LAB_f598;
        if (iVar7 < 0) goto LAB_f5a0;
    }
    plVar8 = &local_80;
    if (param_2 != nullptr) {
        return;
    }
    local_80 = 0;
    local_78 = (long)param_2;
    lVar15 = 0;
    goto joined;

LAB_f520:
    plVar8 = (long*)*param_2;
    plVar13 = param_2;
    if ((long*)*param_1 == param_2) {
LAB_f634:
        if (plVar8 == nullptr) {
            lVar15 = *param_2;
            plVar8 = param_2;
            local_78 = (long)param_2;
        } else {
            lVar15 = plVar13[1];
            plVar8 = plVar13 + 1;
            local_78 = (long)plVar13;
        }
    } else {
        plVar18 = plVar8;
        plVar17 = param_2;
        if (plVar8 == nullptr) {
            do {
                plVar13 = (long*)plVar17[2];
                bVar6 = (long*)*plVar13 == plVar17;
                plVar17 = plVar13;
            } while (bVar6);
        } else {
            do {
                plVar13 = plVar18;
                plVar18 = (long*)plVar13[1];
            } while ((long*)plVar13[1] != nullptr);
        }
        bVar3 = *(u8*)(plVar13 + 4);
        bVar4 = *param_3;
        uVar9 = (unsigned long)(bVar4 >> 1);
        if ((bVar4 & 1) != 0) {
            uVar9 = *(unsigned long*)(param_3 + 8);
        }
        uVar19 = (unsigned long)(bVar3 >> 1);
        if ((bVar3 & 1) != 0) {
            uVar19 = (unsigned long)plVar13[5];
        }
        sVar1 = uVar9;
        if (uVar19 <= uVar9) {
            sVar1 = uVar19;
        }
        if (sVar1 == 0) {
LAB_f64c:
            if (uVar19 < uVar9) goto LAB_f634;
        } else {
            pvVar12 = (void*)plVar13[6];
            if ((bVar3 & 1) == 0) {
                pvVar12 = (void*)((long)plVar13 + 0x21);
            }
            pbVar11 = *(u8**)(param_3 + 0x10);
            if ((bVar4 & 1) == 0) {
                pbVar11 = param_3 + 1;
            }
            iVar7 = memcmp(pvVar12, pbVar11, sVar1);
            if (iVar7 == 0) goto LAB_f64c;
            if (iVar7 < 0) goto LAB_f634;
        }
LAB_f6f0:
        plVar8 = FUN_710354fa40((long)param_1, &local_78, param_3);
        lVar15 = *plVar8;
    }
joined:
    if (lVar15 != 0) {
        return;
    }

    // Allocate new tree node (0x38 bytes)
    iVar7 = FUN_710392dc40(&local_70, 0x10, 0x38);
    if (iVar7 == 0xc && DAT_710593c2b0 != nullptr) {
        local_68 = 0x38;
        uVar9 = (*(unsigned long(**)(s64*, unsigned long*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, &local_68);
        if ((uVar9 & 1) != 0) {
            FUN_710392dc40(&local_70, 0x10, 0x38);
        }
    }
    puVar5 = *(void**)&PTR_VirtualAllocHook_71052a7a78;
    if (puVar5 != nullptr) {
        nu::VirtualAllocHook(0x38, 0x10, local_70);
    }

    long* p_Var16 = (long*)local_70;

    // Initialize string in new node
    *(long*)((long)local_70 + 0x20) = 0;
    *(long*)((long)local_70 + 0x28) = 0;
    *(long*)((long)local_70 + 0x30) = 0;

    if ((*param_4 & 1) == 0) {
        uVar2 = *(long*)param_4;
        uVar14 = *(long*)(param_4 + 0x10);
        *(long*)((long)local_70 + 0x28) = *(long*)(param_4 + 8);
        *(long*)((long)local_70 + 0x30) = uVar14;
        *(long*)((long)local_70 + 0x20) = uVar2;
        goto LAB_f89c;
    }
    uVar9 = *(unsigned long*)(param_4 + 8);
    if (0xffffffffffffffefUL < uVar9) {
        std::__1::__throw_length_error("basic_string");
    }
    pvVar12 = *(void**)(param_4 + 0x10);
    if (uVar9 < 0x17) {
        __dest = (void*)((long)p_Var16 + 0x21);
        *(u8*)((long)local_70 + 0x20) = (u8)((int)uVar9 << 1);
        if (uVar9 != 0) goto LAB_f888;
    } else {
        uVar19 = (uVar9 + 0x10) & 0xfffffffffffffff0UL;
        iVar7 = FUN_710392dc40(&local_70, 0x10, uVar19);
        if (iVar7 == 0xc && DAT_710593c2b0 != nullptr) {
            local_68 = uVar19;
            uVar10 = (*(unsigned long(**)(s64*, unsigned long*))(*(long*)DAT_710593c2b0 + 0x30))(DAT_710593c2b0, &local_68);
            if ((uVar10 & 1) != 0) {
                FUN_710392dc40(&local_70, 0x10, uVar19);
            }
        }
        if (puVar5 != nullptr) {
            nu::VirtualAllocHook(uVar19, 0x10, local_70);
        }
        __dest = local_70;
        *(unsigned long*)((long)p_Var16 + 0x20) = uVar19 | 1;
        *(unsigned long*)((long)p_Var16 + 0x28) = uVar9;
        *(void**)((long)p_Var16 + 0x30) = local_70;
LAB_f888:
        memcpy(__dest, pvVar12, uVar9);
    }
    *(u8*)((long)__dest + uVar9) = 0;

LAB_f89c:
    *p_Var16 = 0;
    p_Var16[1] = 0;
    p_Var16[2] = local_78;
    *plVar8 = (long)p_Var16;
    if (*(long*)*param_1 != 0) {
        *param_1 = *(long*)*param_1;
        p_Var16 = (long*)*plVar8;
    }
    std::__1::__tree_balance_after_insert((void*)param_1[1], (void*)p_Var16);
    param_1[2] = param_1[2] + 1;
}

// ============================================================================
// FUN_710354ff10 — pipeline_link_nodes (368 bytes)
// ============================================================================
u32 FUN_710354ff10(long param_1) {
    long* plVar1;
    long lVar2;
    unsigned long uVar3;
    unsigned long uVar4;
    unsigned long uVar5;
    long* plVar6;
    unsigned long uVar7;
    long* plVar8;
    long lVar9;
    u32 uVar10;
    long lVar11;
    long lVar12;
    unsigned long uVar13;
    unsigned long uVar14;

    lVar9 = *(long*)(param_1 + 0xC0);
    lVar2 = *(long*)(param_1 + 0xC8);
    if (lVar9 == lVar2) {
        return 1;
    }
    plVar1 = (long*)(param_1 + 0x130);
    uVar10 = 1;
LAB_ff24:
    lVar11 = *(long*)(*(long*)(lVar9 + 8) + 0x158);
    if (lVar11 != 0) {
        lVar12 = *(long*)(param_1 + 0xE0);
        if (lVar12 == *(long*)(param_1 + 0xE8)) {
            return 0;
        }
        uVar13 = *(unsigned long*)(param_1 + 0x110);
        uVar14 = uVar13 - 1;
LAB_ff48:
        plVar8 = plVar1;
        if (uVar13 != 0) {
            uVar4 = *(unsigned long*)(lVar12 + 0x1a8);
            if ((uVar14 & uVar13) == 0) {
                uVar5 = uVar14 & uVar4;
            } else {
                uVar5 = uVar4;
                if (uVar13 <= uVar4) {
                    uVar3 = 0;
                    if (uVar13 != 0) {
                        uVar3 = uVar4 / uVar13;
                    }
                    uVar5 = uVar4 - uVar3 * uVar13;
                }
            }
            plVar6 = *(long**)(*(long*)(param_1 + 0x108) + uVar5 * 8);
            if (plVar6 != nullptr && (plVar6 = (long*)*plVar6, plVar6 != nullptr)) {
                if ((uVar14 & uVar13) == 0) {
                    do {
                        uVar7 = (unsigned long)plVar6[1];
                        if (uVar7 != uVar4 && (uVar7 & uVar14) != uVar5) break;
                        if (uVar7 == uVar4 && plVar6[2] == (long)uVar4) goto LAB_0c;
                        plVar6 = (long*)*plVar6;
                    } while (plVar6 != nullptr);
                } else {
                    do {
                        uVar7 = (unsigned long)plVar6[1];
                        if (uVar7 == uVar4) {
                            if (plVar6[2] == (long)uVar4) goto LAB_0c;
                        } else {
                            if (uVar13 <= uVar7) {
                                uVar3 = 0;
                                if (uVar13 != 0) {
                                    uVar3 = uVar7 / uVar13;
                                }
                                uVar7 = uVar7 - uVar3 * uVar13;
                            }
                            if (uVar7 != uVar5) break;
                        }
                        plVar6 = (long*)*plVar6;
                    } while (plVar6 != nullptr);
                }
            }
        }
        goto LAB_10;
LAB_0c:
        plVar8 = plVar6 + 3;
LAB_10:
        if (*(char*)*plVar8 != '\0' && lVar11 == *(long*)((char*)*plVar8 + 0x30)) {
            goto LAB_40;
        }
        lVar12 = lVar12 + 0x330;
        if (lVar12 == *(long*)(param_1 + 0xE8)) {
            return 0;
        }
        goto LAB_ff48;
LAB_40:
        *(long*)(*(long*)(lVar9 + 8) + 0x178) = lVar12;
    } else {
        uVar10 = 0;
    }
    lVar9 = lVar9 + 0x20;
    if (lVar9 == lVar2) {
        return uVar10;
    }
    goto LAB_ff24;
}

// ============================================================================
// FUN_710354e4e0 — pipeline_update (3,360 bytes)
// STUB — needs full implementation after simpler functions verified
// ============================================================================
long FUN_710354e4e0(long param_1, long param_2) {
    // Step 1: extract data pointers from param_2
    if (*(long**)(param_2 + 0x10) == nullptr ||
        **(long**)(param_2 + 0x10) != *(long*)(param_2 + 0x18)) {
        DAT_7105333000 = 0;
        DAT_7105333010 = 0;
        DAT_7105333008 = nullptr;
    } else {
        DAT_7105333000 = *(long*)(param_2 + 8);
        if (DAT_7105333000 == 0) {
            DAT_7105333010 = 0;
            DAT_7105333008 = nullptr;
        } else {
            DAT_7105333008 = *(long**)(DAT_7105333000 + 8);
            DAT_7105333010 = *DAT_7105333008;
        }
    }
    if (*(long**)(param_2 + 0x30) == nullptr ||
        **(long**)(param_2 + 0x30) != *(long*)(param_2 + 0x38)) {
        DAT_7105333020 = 0;
        DAT_7105333030 = 0;
        DAT_7105333028 = nullptr;
    } else {
        DAT_7105333020 = *(long*)(param_2 + 0x28);
        if (DAT_7105333020 == 0) {
            DAT_7105333030 = 0;
            DAT_7105333028 = nullptr;
        } else {
            DAT_7105333028 = *(long**)(DAT_7105333020 + 8);
            DAT_7105333030 = *DAT_7105333028;
        }
    }
    if (*(long**)(param_2 + 0x50) == nullptr ||
        **(long**)(param_2 + 0x50) != *(long*)(param_2 + 0x58)) {
        DAT_7105333040 = 0;
        DAT_7105333050 = 0;
        DAT_7105333048 = nullptr;
    } else {
        DAT_7105333040 = *(long*)(param_2 + 0x48);
        if (DAT_7105333040 == 0) {
            DAT_7105333050 = 0;
            DAT_7105333048 = nullptr;
        } else {
            DAT_7105333048 = *(long**)(DAT_7105333040 + 8);
            DAT_7105333050 = *DAT_7105333048;
        }
    }

    FUN_710354f200(param_1);
    FUN_710354f380(param_1 + 0x98, (long)(DAT_710447157c / *(float*)(param_1 + 0xB8)));

    // TODO: remaining pipeline_update body (vector resize, tree build, hash map insert)
    // Deferred until simpler functions are verified matching

    FUN_710354f900(nullptr);  // placeholder — real code builds and destroys a tree
    return 1;
}

// ============================================================================
// FUN_710354d400 — pipeline_init (3,456 bytes)
// STUB — needs full implementation after simpler functions verified
// ============================================================================
long FUN_710354d400(long param_1, unsigned long param_2, unsigned long param_3, long param_4) {
    // TODO: full implementation
    // This is the largest function (3,456B) with:
    // - OOM-retry allocation patterns
    // - Identity matrix initialization (0x3f800000 = 1.0f)
    // - shared_ptr cleanup
    // - Hash map clearing
    // - 0x110-byte state object allocation
    // - "ErrorDummy" string setup
    return 1;
}
