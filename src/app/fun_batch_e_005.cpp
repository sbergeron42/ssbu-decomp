#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 005
// Rewritten with derivation chains + VT macro

#define VT(m) (*reinterpret_cast<void***>(m))

// Called functions
extern void FUN_71001f2180(s64);
extern void FUN_71001bee30(u64, u32);
extern void FUN_71001f24a0(s64);
extern void FUN_71001b0ab0(s64, const char *);
extern u64  FUN_7100230c50(void);
extern void FUN_7100230a20(u64);
extern u32  FUN_7100251150(s64, u64, u64, u64 *, u64);
extern u32  FUN_71002513c0(s64, u64, u64, u64 *, u64);
extern u32  FUN_710026d770(s64, u64, u16 *, u8 *);
extern s32  FUN_71002babe0(void);
extern u64  FUN_71002babd0(u32);
extern u64  FUN_71002babf0(u64, u32);
extern u32  FUN_71002c2f60(u32, u32);
extern void FUN_71002c2df0(u32);
extern void FUN_71002c2e50(u64, u32, u32);
extern u32  FUN_71002c2d60(u32, u32);
extern void FUN_71002c2bf0(u32);
extern void FUN_71002c2c30(u64, u32, u32);
extern void FUN_71037378c0(u64 *);
extern void FUN_710170de70(s64, u64, s64);
extern void FUN_710170f2a0(s64, u64, u64);
extern void FUN_710170d890(s64, u64, u64);
extern u8   FUN_71001b34a0(u32);
extern void FUN_71001b47e0(s64, s64, s64);
extern void FUN_71001b6470(s64, u32);
extern u64  FUN_71001b0fd0(void);
extern void FUN_71002ba5e0(u64);
extern void FUN_71002c1d20(u64);

// Data
extern void *PTR_FUN_7104f61778;
extern u8    DAT_7104348271;

// ---- Functions --------------------------------------------------------------

// 0x71001e59e0 -- conditional init then dispatch command
// param_1 [inferred: session/connection struct]
//   +0x08 [inferred: inner handle, passed to FUN_71001bee30]
//   +0x68 [inferred: bool, true = already initialized]
//   +0x69 [inferred: bool, cleared after dispatch]
void FUN_71001e59e0(s64 param_1, u32 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {   // +0x68 [inferred: initialized flag]
        FUN_71001f2180(param_1);
    }
    FUN_71001bee30(*(u64 *)(param_1 + 8), param_2);  // +0x08 [inferred: inner handle]
    *(u8 *)(param_1 + 0x69) = 0;                      // +0x69 [inferred: pending flag, cleared]
}

// 0x71001f3690 -- conditional init then read name string
// param_2 [inferred: session/connection struct, same as FUN_71001e59e0]
//   +0x60 [inferred: const char* name pointer]
//   +0x69 [inferred: bool, true = name is current/valid]
void FUN_71001f3690(u64 param_1, s64 param_2)
{
    if (*(char *)(param_2 + 0x69) == '\0') {   // +0x69 [inferred: valid flag]
        FUN_71001f24a0(param_2);
    }
    FUN_71001b0ab0(param_1, (const char *)*(u64 *)(param_2 + 0x60));  // +0x60 [inferred: name string ptr]
}

// 0x7100251110 -- wrapper: forward to FUN_7100251150 via effect_module, return bit 0
// param_1 [inferred: BattleObjectModuleAccessor*]
//   +0x140 [derived: effect_module, EffectModule__*_impl (.dynsym) loads from accessor+0x140]
u32 FUN_7100251110(s64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    u32 result;
    u64 out = param_3;

    // +0x140 [derived: effect_module, EffectModule__*_impl (.dynsym)]
    result = FUN_7100251150(param_1 + 0x140, param_2, param_5, &out, param_4);
    return result & 1;
}

// 0x7100251380 -- wrapper: forward to FUN_71002513c0 via effect_module, return bit 0
// param_1 [inferred: BattleObjectModuleAccessor*]
//   +0x140 [derived: effect_module, EffectModule__*_impl (.dynsym) loads from accessor+0x140]
u32 FUN_7100251380(s64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    u32 result;
    u64 out = param_3;

    // +0x140 [derived: effect_module, EffectModule__*_impl (.dynsym)]
    result = FUN_71002513c0(param_1 + 0x140, param_2, param_5, &out, param_4);
    return result & 1;
}

// 0x710026d730 -- wrapper: forward to FUN_710026d770 with local args, return bit 0
// param_1 [inferred: container struct]
//   +0x28 [inferred: embedded sub-object]
u32 FUN_710026d730(s64 param_1, u64 param_2, u16 param_3, u8 param_4)
{
    u32 result;
    u8  flag[4];
    u16 value[2];

    flag[0] = param_4 & 1;
    value[0] = param_3;
    result = FUN_710026d770(param_1 + 0x28, param_2, value, flag);  // +0x28 [inferred: sub-object]
    return result & 1;
}

// 0x71002b3e80 -- endian/byte-order helper
// FUN_71002babe0 [inferred: returns byte order — 1 = little-endian]
// FUN_71002babd0 [inferred: encode u32 for byte swap]
// FUN_71002babf0 [inferred: byte swap with mode param]
u64 FUN_71002b3e80(u64 param_1)
{
    s32 byte_order;
    u64 encoded;
    u64 swapped;

    byte_order = FUN_71002babe0();
    if (byte_order == 1) {
        return param_1 & 0xffffffff;
    }
    encoded = FUN_71002babd0((u32)param_1);
    swapped = FUN_71002babf0(encoded, 1);
    return swapped;
}

// 0x7100254160 -- copy operator: copy byte field + conditional deep copy
// dst/src [inferred: variant/tagged-union struct]
//   +0x08 [inferred: u8 tag/type field]
//   +0x10 [inferred: data start — FUN_710170de70 performs deep copy from src+0x18]
s64 FUN_7100254160(s64 dst, s64 src)
{
    *(u8 *)(dst + 8) = *(u8 *)(src + 8);    // +0x08 [inferred: tag/type byte]
    if (dst != src) {
        // +0x10 [inferred: data payload, deep-copied via FUN_710170de70]
        FUN_710170de70(dst + 0x10, *(u64 *)(src + 0x10), src + 0x18);
    }
    return dst;
}

// 0x7100261490 -- copy operator: copy fields + conditional deep copy
// dst/src [inferred: tagged struct with u8+u32+u32 header]
//   +0x08 [inferred: u8 tag]
//   +0x0c [inferred: u32 field A]
//   +0x10 [inferred: u32 field B]
//   +0x18 [inferred: data start — deep-copied via FUN_710170f2a0]
//   +0x20 [inferred: data size/end — passed to FUN_710170f2a0]
s64 FUN_7100261490(s64 dst, s64 src)
{
    *(u8 *)(dst + 8) = *(u8 *)(src + 8);      // +0x08 [inferred: tag byte]
    *(u32 *)(dst + 0xc) = *(u32 *)(src + 0xc); // +0x0c [inferred: u32 field]
    *(u32 *)(dst + 0x10) = *(u32 *)(src + 0x10); // +0x10 [inferred: u32 field]
    if (dst != src) {
        // +0x18, +0x20 [inferred: deep-copy payload via FUN_710170f2a0]
        FUN_710170f2a0(dst + 0x18, *(u64 *)(src + 0x18), *(u64 *)(src + 0x20));
    }
    return dst;
}

// 0x710028af20 -- copy operator: copy two byte fields + conditional deep copy
// dst/src [inferred: tagged struct with u8+u8 header]
//   +0x08 [inferred: u8 field A]
//   +0x09 [inferred: u8 field B]
//   +0x10 [inferred: data start — deep-copied via FUN_710170d890]
//   +0x18 [inferred: data size/end — passed to FUN_710170d890]
s64 FUN_710028af20(s64 dst, s64 src)
{
    *(u8 *)(dst + 8) = *(u8 *)(src + 8);    // +0x08 [inferred: field A]
    *(u8 *)(dst + 9) = *(u8 *)(src + 9);    // +0x09 [inferred: field B]
    if (dst != src) {
        // +0x10, +0x18 [inferred: deep-copy payload via FUN_710170d890]
        FUN_710170d890(dst + 0x10, *(u64 *)(src + 0x10), *(u64 *)(src + 0x18));
    }
    return dst;
}

// 0x7100213040 -- vtable dispatch with 8 args, return 1
// param_1 [inferred: event/handler wrapper]
//   +0x10 [inferred: handler object pointer with vtable]
//   handler vtable+0x18 [inferred: process/execute method]
// param_2 [inferred: event data struct]
//   +0x42 [inferred: u8 flag passed as arg to handler]
u64 FUN_7100213040(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *handler = *(s64 **)(param_1 + 0x10);  // +0x10 [inferred: handler object]
    // vtable+0x18 [inferred: execute/process virtual method]
    reinterpret_cast<void (*)(s64 *, s64, s32, s32, u8, u64, s32, u64)>(VT(handler)[0x18 / 8])
        (handler, param_2, 1, 0, *(u8 *)(param_2 + 0x42), param_3, 0, param_5);
    return 1;
}

// 0x71002134a0 -- identical to FUN_7100213040 (different address, same logic)
u64 FUN_71002134a0(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *handler = *(s64 **)(param_1 + 0x10);  // +0x10 [inferred: handler object]
    // vtable+0x18 [inferred: execute/process virtual method]
    reinterpret_cast<void (*)(s64 *, s64, s32, s32, u8, u64, s32, u64)>(VT(handler)[0x18 / 8])
        (handler, param_2, 1, 0, *(u8 *)(param_2 + 0x42), param_3, 0, param_5);
    return 1;
}

// 0x7100223fa0 -- fill buffer with random bytes
// FUN_71001b34a0 [inferred: random byte generator, param = max value]
u64 FUN_7100223fa0(u64 param_1, u8 *buf, s64 count)
{
    u8 byte;

    if (count != 0) {
        do {
            byte = FUN_71001b34a0(0xff);
            count--;
            *buf = byte;
            buf++;
        } while (count != 0);
    }
    return 0;
}

// 0x71001b2f70 -- copy assignment: copy inner pointer via FUN_71001b47e0
// param_1/param_2 [inferred: string/buffer wrapper]
//   +0x18 [inferred: inner data pointer, -1 sentinel = full copy]
s64 FUN_71001b2f70(s64 param_1, s64 param_2)
{
    if (param_1 != param_2) {
        // +0x18 [inferred: inner value/pointer from source]
        FUN_71001b47e0(param_1, *(s64 *)(param_2 + 0x18), 0xffffffffffffffff);
    }
    return param_1;
}

// 0x71001b65c0 -- conditional string dispatch: bool-to-string conversion
// param_1 [inferred: string/output object]
//   +0x122 [inferred: bool flag — if true, use literal string conversion]
// DAT_7104348271 [inferred: "true" string constant]
void FUN_71001b65c0(s64 param_1, u32 param_2)
{
    if (*(char *)(param_1 + 0x122) == '\0') {  // +0x122 [inferred: use-string-mode flag]
        FUN_71001b6470(param_1, param_2 & 1);
        return;
    }
    if ((param_2 & 1) != 0) {
        FUN_71001b0ab0(param_1, (const char *)&DAT_7104348271);  // [inferred: "true" literal]
        return;
    }
    FUN_71001b0ab0(param_1, "false");
}
