#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, hard tier 001
// Range: 0x7102000000 -- 0x7102FFFFFF
// Functions: FUN_7102145710, FUN_710262ca80, FUN_71020ad9f0, FUN_7102ff3320

[[noreturn]] extern "C" void abort();

// Global data symbols (hidden visibility avoids GOT indirection)
extern long*  DAT_71053299d8  __attribute__((visibility("hidden")));  // lib::Singleton<app::StageManager>::instance_
extern long   DAT_7104861960  __attribute__((visibility("hidden")));  // sentinel/null L2CValue (type=0,val=0)

// External functions
[[noreturn]] extern "C" void _ZNKSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv(void* vec_this);
extern "C" long FUN_710262f730();

// 0x7102145710
// StageManager__is_discretion_final_enabled helper -- reads stage type, pushes bool to Lua output
u32 FUN_7102145710(long param_1)
{
    u32 uVar3;
    u32 uVar1;

    if (DAT_71053299d8 == nullptr) {
        return 0;
    }

    long data = *DAT_71053299d8;
    u32 stage_type = *(u32*)(data + 0x17c);
    uVar3 = 1;

    if (stage_type == 0xffffffffu) {
        uVar1 = 1;
    } else {
        if (stage_type > 2u) abort();
        void** stage_obj = *(void***)(data + (u64)stage_type * 8 + 0x110);
        void** vtable = *(void***)stage_obj;
        uVar1 = ((u32(*)())vtable[0x4a0 / 8])() & 1u;
    }

    u32* out = *(u32**)(param_1 + 0x10);
    *out = uVar1;
    out[2] = 1;
    *(long*)(param_1 + 0x10) += 0x10;

    return uVar3;
}

// 0x710262ca80
// Iterator advance for multi-level vector structure -- moves to next valid frame entry
void FUN_710262ca80(long* param_1)
{
    long lVar2 = *param_1;
    if (lVar2 == 0) return;

    u32 uVar1 = *(u32*)(param_1 + 2) + 1;
    void* vec_this = (void*)(lVar2 + 0x1a8);
    *(u32*)(param_1 + 2) = uVar1;
    u32 uVar3 = *(u32*)(param_1 + 1);

    long vec_begin = *(long*)(lVar2 + 0x1a8);
    long vec_end   = *(long*)(lVar2 + 0x1b0);
    long count0 = (vec_end - vec_begin) >> 3;
    asm("");  // MATCHING_HACK_NX_CLANG: force asr before cmp
    if ((u64)count0 <= (u64)uVar3) {
        _ZNKSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv(vec_this);
    }
    long lVar4 = *(long*)(*(long*)(vec_begin + (u64)uVar3 * 8) + 0x10);

    u32 w13 = *(u32*)(lVar4 + 0x108);
    if (w13 > uVar1) {
        u64 base = *(u64*)(lVar4 + 0x110);
        u64 result = base + (u64)uVar1 * 0x130u;
        if (result != 0) return;
    }

    *(u32*)(param_1 + 2) = 0;
    uVar3 = uVar3 + 1;
    while (true) {
        *(u32*)(param_1 + 1) = uVar3;
        vec_begin = *(long*)(lVar2 + 0x1a8);
        vec_end   = *(long*)(lVar2 + 0x1b0);
        if ((u32)((u64)(vec_end - vec_begin) >> 3) <= uVar3) {
            *param_1 = 0;
            return;
        }
        if ((u64)((vec_end - vec_begin) >> 3) <= (u64)uVar3) {
            _ZNKSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv(vec_this);
        }
        lVar4 = *(long*)(*(long*)(vec_begin + (u64)uVar3 * 8) + 0x10);
        if (*(u32*)(lVar4 + 0x108) != 0 && *(long*)(lVar4 + 0x110) != 0) return;
        uVar3 = uVar3 + 1;
    }
}

// 0x71020ad9f0
// Lua binding -- reads module at accessor+0x78, queries state, pushes s32 result
u64 FUN_71020ad9f0(long param_1)
{
    long* plVar1;
    s32 iVar2;
    u64 uVar3;
    long* plVar4;
    long  lVar5;
    long* plVar6;

    long accessor = *(long*)(param_1 + -8);
    if ((accessor == 0) ||
        (plVar6 = *(long**)(accessor + 0x78), plVar6 == nullptr))
    {
        return 0;
    }

    plVar4 = *(long**)(param_1 + 0x10);
    plVar1 = (long*)(**(long**)(param_1 + 0x20) + 0x10);

    if (0 < (s32)((u64)((long)plVar4 - (long)plVar1) >> 4)) {
        plVar6 = plVar1;
        if (plVar4 <= plVar1) {
            plVar6 = (long*)&DAT_7104861960;
        }
        if ((*(u32*)(plVar6 + 1) & 0xfu) == 2) {
            lVar5 = *plVar6;
        } else if ((*(u32*)(plVar6 + 1) & 0xfu) == 7) {
            lVar5 = *plVar6 + 0x28;
        } else {
            lVar5 = 0;
        }
        plVar6 = *(long**)(lVar5 + 0x90);
        *(long*)(param_1 + 0x10) = (long)plVar4 +
            (((long)plVar4 - (long)plVar1) * -(long)0x10000000 >> 0x1c);
    }

    iVar2 = (*(s32(**)())(*(long**)*(long**)(plVar6[1] + 0x40) + 0x110))();

    if (iVar2 < 200) {
        if ((4 < (u32)(iVar2 - 0x47)) ||
            (uVar3 = (*(u64(*)(long*, u64))(*(long*)*(long**)(plVar6[1] + 0x50) + 0x108))
                        (*(long**)(plVar6[1] + 0x50), 0x2100000f),
             (uVar3 & 1) == 0))
        {
            goto call_vtable_200;
        }
    } else if ((iVar2 != 200) && (iVar2 != 0x149) && (iVar2 != 0x14c)) {
        goto call_vtable_200;
    }

    iVar2 = (*(s32(*)(long*, u64))(*(long*)*(long**)(plVar6[1] + 0x50) + 0x98))
                (*(long**)(plVar6[1] + 0x50), 0x11000006);
    goto push_result;

call_vtable_200:
    iVar2 = (*(s32(*)(long*))(*(long*)plVar6 + 200))(plVar6);

push_result:
    plVar6 = *(long**)(param_1 + 0x10);
    *plVar6 = (long)iVar2;
    *(u32*)(plVar6 + 1) = 0x13;
    *(long*)(param_1 + 0x10) += 0x10;
    return 1;
}

// 0x7102ff3320
// Recursive helper -- determines which animation frame slots are active/inactive
u8 FUN_7102ff3320(long param_1, s32 param_2, s32 param_3, long param_4, u8 param_5)
{
    s32* piVar1;
    u8 bVar2;
    u64 uVar3;
    u8 bVar4;
    s32 iVar5;
    long lVar6;
    long lVar7;

    piVar1 = (s32*)(param_4 + (long)param_2 * 0x24 + (long)param_3 * 4);
    iVar5 = *piVar1;
    if (iVar5 != 0) {
        bVar2 = (u8)(iVar5 == 2);
        goto store_and_return;
    }

    lVar6 = *(long*)(param_1 + (long)param_2 * 0x48 + (long)param_3 * 8 + 0x40);
    if ((lVar6 == 0) || (*(long*)(lVar6 + 0xc0) == 0) ||
        (*(s32*)(*(long*)(lVar6 + 0xc0) + 0x38) == 0))
    {
        bVar2 = 0;
        iVar5 = 1;
    } else {
        // Check if any active motion layers exist
        lVar7 = 0;
        if (*(s32*)(lVar6 + 0x3c) >= 1) {
            lVar7 = *(long*)(*(long*)(lVar6 + 0x18) +
                             (long)*(s32*)(lVar6 + 0x38) * 0x48 +
                             (long)(*(s32*)(lVar6 + 0x3c) - 1) * 8 + 0x40);
        }
        if (lVar7 != 0) {
            bVar4 = 0;
            long** p0 = *(long***)(lVar7 + 0x40);
            long** p1 = *(long***)(lVar7 + 0x48);
            long** p2 = *(long***)(lVar7 + 0x50);
            long** p3 = *(long***)(lVar7 + 0x58);
            if ((p0 != nullptr && ((*(u64(**)())(*(long*)p0 + 8))() & 1)) ||
                (p1 != nullptr && ((*(u64(**)())(*(long*)p1 + 8))() & 1)) ||
                (p2 != nullptr && ((*(u64(**)())(*(long*)p2 + 8))() & 1)) ||
                (p3 != nullptr && ((*(u64(**)())(*(long*)p3 + 8))() & 1)))
            {
                bVar4 = 1;
            }
        } else {
            bVar4 = 0;
        }

        if ((*(long*)(lVar6 + 0xc0) != 0) &&
            (*(s32*)(*(long*)(lVar6 + 0xc0) + 0x38) != 0) && (param_2 < 2))
        {
            long next_layer = (long)param_2 + 1;
            lVar7 = *(long*)(param_1 + next_layer * 0x48 + (long)param_3 * 8 + 0x40);
            if ((lVar7 != 0) &&
                ((lVar7 = *(long*)(lVar7 + 0xc0), lVar7 != 0 &&
                  (*(s32*)(lVar7 + 0x38) != 0))))
            {
                bVar2 = FUN_7102ff3320(param_1, (s32)next_layer, param_3, param_4,
                                       bVar4 | (param_5 & 1));
                iVar5 = 1;
                if ((bVar2 & 1) != 0) {
                    iVar5 = 2;
                }
                goto store_and_return;
            }
        }
        bVar2 = (u8)((bVar4 | param_5) ^ 1u);
        iVar5 = 1;
        if (bVar4 == 0 && (param_5 & 1) == 0) {
            iVar5 = 2;
        }
    }

store_and_return:
    *piVar1 = iVar5;
    return bVar2 & 1u;
}
