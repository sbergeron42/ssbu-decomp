#include "types.h"

// HARD-tier FUN_* functions — 0x71000 address range, batch hard-d-003
// Pool-d worker: hash table lookup, linked-list splice, format search

// ---- External declarations -----------------------------------------------

extern "C" {
    extern u64   strlen(const char *s);
    extern void  FUN_7100007ef0(char *buf, u64 size, const char *fmt, ...);
}

extern s64 *FUN_71000055b0(s64 *param_1, u64 param_2, u64 param_3);

// ---- Functions ---------------------------------------------------------------

// 0x71000055b0 — hash-table lookup: hash fn at [1], compare fn at [2] (144 bytes)
s64 *FUN_71000055b0(s64 *param_1, u64 param_2, u64 param_3)
{
    s64 lVar1;
    s64 lVar2;
    s64 *plVar3;

    if (param_1 != nullptr) {
        lVar2 = *param_1;
        lVar1 = ((s64(*)(u64, u64, s32))param_1[1])(param_2, param_3, (s32)param_1[4]);
        for (plVar3 = *(s64 **)(lVar2 + lVar1 * 0x20);
             plVar3 != nullptr;
             plVar3 = (s64 *)plVar3[2]) {
            lVar1 = *plVar3;
            lVar2 = ((s64(*)(s64, u64, u64, u64))param_1[2])(lVar1 + 0x28,
                        *(u64 *)(lVar1 + 0x20), param_2, param_3);
            if (lVar2 != 0) {
                return *(s64 **)(lVar1 + 0x18);
            }
        }
        param_1 = nullptr;
    }
    return param_1;
}

// 0x7100004360 — build key string from field flags, search in hash table (160 bytes)
u64 FUN_7100004360(s64 param_1, s64 param_2)
{
    u64 uVar2;
    u64 *puVar3;
    char acStack_a0[128];

    if (param_2 == 0) {
        return 0;
    }
    if (*(s8 *)(param_1 + 0x817) == '\0') {
        if (*(s8 *)(param_1 + 0x816) == '\0') {
            puVar3 = (u64 *)(param_1 + 0xd8);
            if (*(s8 *)(param_1 + 0x813) != '\0') {
                puVar3 = (u64 *)(param_1 + 0x100);
            }
        } else {
            puVar3 = (u64 *)(param_1 + 0x160);
        }
    } else {
        puVar3 = (u64 *)(param_1 + 0x120);
    }
    FUN_7100007ef0(acStack_a0, 0x80, "%ld%s", *(u64 *)(param_1 + 0x190), *puVar3);
    u64 sVar1 = strlen(acStack_a0);
    uVar2 = (u64)FUN_71000055b0((s64 *)param_2, (u64)acStack_a0, sVar1);
    return uVar2;
}

// 0x71000069b0 — doubly-linked list: remove param_2 from src, insert after param_4 in dst (192 bytes)
void FUN_71000069b0(s64 *param_1, s64 param_2, s64 *param_3, s64 param_4)
{
    s64 *plVar1;
    s64 lVar2;
    s64 *plVar3;

    if ((param_2 != 0) && (param_1[3] != 0)) {
        // Remove param_2 from source list
        lVar2 = *(s64 *)(param_2 + 0x10);   // param_2->next
        if (*param_1 == param_2) {
            // param_2 is the head
            *param_1 = lVar2;
            if (lVar2 == 0) {
                param_1[1] = 0;
            } else {
                *(u64 *)(*(s64 *)(param_2 + 0x10) + 8) = 0;  // new_head->prev = NULL
            }
        } else {
            *(s64 *)(*(s64 *)(param_2 + 8) + 0x10) = lVar2;  // prev->next = next
            if (*(s64 *)(param_2 + 0x10) == 0) {
                param_1[1] = *(s64 *)(param_2 + 8);           // update tail
            } else {
                *(s64 *)(*(s64 *)(param_2 + 0x10) + 8) = *(s64 *)(param_2 + 8);  // next->prev = prev
            }
        }
        param_1[3] = param_1[3] + -1;

        // Insert param_2 into destination list after param_4
        if (param_3[3] == 0) {
            *param_3 = param_2;
            *(u64 *)(param_2 + 8) = 0;
            plVar3 = param_3 + 1;
            *(u64 *)(*param_3 + 0x10) = 0;
        } else {
            plVar3 = (s64 *)(param_4 + 0x10);
            lVar2 = *plVar3;
            *(s64 *)(param_2 + 8) = param_4;
            *(s64 *)(param_2 + 0x10) = lVar2;
            plVar1 = param_3 + 1;
            if (*plVar3 != 0) {
                plVar1 = (s64 *)(*plVar3 + 8);
            }
            *plVar1 = param_2;
        }
        *plVar3 = param_2;
        param_3[3] = param_3[3] + 1;
    }
}
