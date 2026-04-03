#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-024
// Pool-d worker: flag check, linked-list search, LCG float, singleton dtor, byte-copy, hash-lookup, varint

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8  *PTR_DAT_71052a3d30           HIDDEN;
extern s64 *PTR_sStaticDisposer_71052a3d38 HIDDEN;
extern s64 **PTR_sInstance_71052a2c08    HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_7100088320(void);

namespace pead {
    void IDisposer_dtor(s64 *);
}

// ---- Functions ---------------------------------------------------------------

// 0x7100004200 — conditional flag set/clear via three-way param_2 switch (112 bytes)
void FUN_7100004200(s64 param_1, s32 param_2)
{
    u8  bVar3;
    s8  cVar2;

    if (param_2 == 1) {
        bVar3 = 1;
        cVar2 = *(s8 *)(param_1 + 0x811);
    } else {
        if (param_2 != 2) {
            bVar3 = 0;
            if (*(s8 *)(param_1 + 0x811) == '\0') {
                return;
            }
            goto set_flag;
        }
        u32 uVar1 = *(u32 *)(*(s64 *)(param_1 + 0x858) + 0x84);
        if ((uVar1 >> 9 & 1) != 0) {
            return;
        }
        bVar3 = ((u8)(uVar1 >> 9) & 1) ^ 1;
        cVar2 = *(s8 *)(param_1 + 0x811);
    }
    if (cVar2 == '\x01') {
        return;
    }
set_flag:
    *(u8 *)(param_1 + 0x811) = bVar3;
}

// 0x7100047c90 — walk intrusive linked list, find node whose string at +0x20 matches param_2 (112 bytes)
// CSV name: AttackData
s64 FUN_7100047c90(s64 param_1, s64 param_2)
{
    s64 lVar2 = *(s64 *)(param_1 + 8);
    do {
        if (lVar2 == param_1) {
            return 0;
        }
        u64 uVar3 = 0;
        char cVar1;
        while ((cVar1 = *(char *)(*(s64 *)(lVar2 + 0x20) + (s64)uVar3)),
               cVar1 == *(char *)(param_2 + (s64)uVar3))
        {
            if (cVar1 == '\0' || (uVar3 += 1, uVar3 > 0x1f)) {
                return lVar2 - 8;
            }
        }
        lVar2 = *(s64 *)(lVar2 + 8);
    } while (true);
}

// 0x7100088750 — LCG PRNG step + float computation from sub-struct tables (128 bytes)
void FUN_7100088750(s64 param_1, f32 *param_2)
{
    f32 fVar1 = (f32)*(s32 *)(*(s64 *)(param_1 + 0xa0) + 0x808) + 1.0f
              + (f32)(s32)((u64)*(u32 *)(param_1 + 0xac)
                           * (s64)*(s32 *)(*(s64 *)(param_1 + 0xa0) + 0x80c) >> 32);
    *(u32 *)(param_1 + 0xac) = *(u32 *)(param_1 + 0xac) * 0x41c64e6d + 0x3039;
    *param_2 = fVar1;
    fVar1 = *(f32 *)(param_1 + 0x64) * fVar1;
    *param_2 = fVar1;
    *param_2 = *(f32 *)(*(s64 *)(param_1 + 0x78) + 0x54) * fVar1;
    if (*(s8 *)(*(s64 *)(param_1 + 0xa0) + 0x758) != '\0') {
        FUN_7100088320();
    }
}

// 0x710013c310 — pead singleton dtor: reset vtable, check static disposer, destroy singleton (128 bytes)
void FUN_710013c310(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3d30 + 0x10);
    if (PTR_sStaticDisposer_71052a3d38 != param_1) {
        pead::IDisposer_dtor(param_1);
        return;
    }
    PTR_sStaticDisposer_71052a3d38 = nullptr;
    s64 *pInst = *PTR_sInstance_71052a2c08;
    (*(void (**)(void))(*pInst))();  // vtable[0] = virtual destructor
    *PTR_sInstance_71052a2c08 = nullptr;
    pead::IDisposer_dtor(param_1);
}

// 0x71000002a0 — byte-copy loop: 4-at-a-time unrolled, then tail (144 bytes)
void FUN_71000002a0(void *dst, const void *src, u32 count)
{
    if ((s32)count < 1) {
        return;
    }
    u32 n    = count;
    u64 rem  = (u64)n & 3u;
    u64 bulk = (u64)(n - (u32)rem);
    u64 i    = 0;
    if (n - 1 >= 3) {
        do {
            ((u8 *)dst)[i]     = ((const u8 *)src)[i];
            ((u8 *)dst)[i + 1] = ((const u8 *)src)[i + 1];
            ((u8 *)dst)[i + 2] = ((const u8 *)src)[i + 2];
            ((u8 *)dst)[i + 3] = ((const u8 *)src)[i + 3];
            i += 4;
        } while (bulk != i);
    }
    if (rem != 0) {
        u8       *d = (u8 *)dst + i;
        const u8 *s = (const u8 *)src + i;
        for (u64 j = 0; j < rem; ++j) {
            d[j] = s[j];
        }
    }
}

// 0x71000055b0 — hash-table lookup with key-compare callback, walks linked-list bucket (144 bytes)
// table[0] = bucket array; table[1] = hash fn; table[2] = compare fn; table[4] = tableSize
s64 *FUN_71000055b0(s64 *table, u64 key1, u64 key2)
{
    if (table == nullptr) {
        return nullptr;
    }
    s64 *buckets  = (s64 *)table[0];
    s64  bucketIdx = ((s64(*)(u64, u64, s32))table[1])(key1, key2, (s32)table[4]);
    for (s64 *node = *(s64 **)(buckets + bucketIdx * 4);
         node != nullptr;
         node = (s64 *)node[2])
    {
        s64 *nodeData = (s64 *)node[0];
        s64 match = ((s64(*)(s64, u64, u64, u64))table[2])(
            nodeData[0] + 0x28, *(u64 *)(nodeData[0] + 0x20), key1, key2);
        if (match != 0) {
            return (s64 *)*(s64 *)(nodeData[0] + 0x18);
        }
    }
    return nullptr;
}

// 0x710022a760 — variable-length int decoder: 7-bit value + 1-bit flag; 0x7F escape = u16 extended (144 bytes)
void FUN_710022a760(s64 ctx, u32 *outFlag, u16 *outValue)
{
    s64 *info   = (s64 *)*(s64 *)(ctx + 0x10);
    s64  endPos = info[3];
    s64  pos    = *(s64 *)(ctx + 0x18);

    u32 byte;
    if (endPos == pos) {
        byte = 0;
        *(u8 *)(ctx + 8) = 1;
    } else {
        u8 *buf      = (u8 *)info[2];
        s64 bufOff   = info[5];
        byte = (u32)buf[bufOff + pos];
        pos += 1;
        *(s64 *)(ctx + 0x18) = pos;
    }
    *outFlag  = byte >> 7;
    *outValue = (u16)(byte & 0x7f);

    if ((byte & 0x7f) == 0x7f) {
        if ((u64)(endPos - pos) < 2) {
            *(u8 *)(ctx + 8) = 1;
            *outValue = 0;
            return;
        }
        u8 *buf    = (u8 *)info[2];
        s64 bufOff = info[5];
        *outValue = *(u16 *)(buf + bufOff + pos);
        *(s64 *)(ctx + 0x18) = pos + 2;
    }
}
