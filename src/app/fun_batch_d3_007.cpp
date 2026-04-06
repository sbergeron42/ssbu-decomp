#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71002 address range, batch d3-007
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void *FUN_7100228110(u64);
extern s64   FUN_71001d6b80(s64);
extern void  FUN_71001b4300(s64, u64 *);
extern void  FUN_71001df8d0(u64, u64, u64);
extern void  FUN_71001df950(u64, u64, u64 *);
extern void  FUN_710023d9c0(s64, u64 *);
extern void  FUN_710024c6d0(s64, s64);
extern void  FUN_7100228e20(s64, s64);
extern u32   FUN_71002659f0();
extern u32   FUN_710026c2c0(s64, u64, u64, u8 *);
extern void  FUN_7100031140();
extern void  FUN_71002b9660(u64);
extern void  FUN_71002b9360(u64);
extern void  FUN_71002bbb30(u64, u64 *);
extern void  FUN_71002be4e0(u64);
extern void  FUN_71002be0b0(u64);
extern void  FUN_71002c31d0(s64);
extern void  FUN_7100031070();

// ---- Functions ---------------------------------------------------------------

// 0x7100228250 — queue push: alloc 0x10-byte node, enqueue at head+tail (80 bytes)
u64 FUN_7100228250(s64 *param_1, u64 param_2)
{
    u64 *node;

    node = (u64 *)FUN_7100228110(0x10);
    if (node == (u64 *)0x0) {
        return 0xfffffe0c;
    }
    *node = param_2;
    node[1] = (u64)*param_1;
    *param_1 = (s64)node;
    if (param_1[1] != 0) {
        return 0;
    }
    param_1[1] = (s64)node;
    return 0;
}

// 0x710022b140 — stream buf: read next byte into out, advance or set EOF (96 bytes)
void FUN_710022b140(s64 param_1, s64 param_2)
{
    s64 buffer;
    s8 eof_flag;

    *(u8 *)(param_2 + 8) = 0;
    if (*(s8 *)(param_1 + 0x69) == '\0') {
        buffer = *(s64 *)(param_1 + 0x10);
        if (*(s64 *)(buffer + 0x18) == *(s64 *)(param_1 + 0x18)) {
            *(s8 *)(param_1 + 8) = '\x01';
            *(u8 *)(param_2 + 8) = 0;
            eof_flag = *(s8 *)(param_1 + 8);
        } else {
            *(u8 *)(param_2 + 8) = *(u8 *)(*(s64 *)(buffer + 0x10) + *(s64 *)(buffer + 0x28) +
                                            *(s64 *)(param_1 + 0x18));
            *(s64 *)(param_1 + 0x18) = *(s64 *)(param_1 + 0x18) + 1;
            eof_flag = *(s8 *)(param_1 + 8);
        }
        if (eof_flag == '\0') {
            if (3 < (u64)(*(s64 *)(*(s64 *)(param_1 + 0x10) + 0x18) - *(s64 *)(param_1 + 0x18))) {
                *(s64 *)(param_1 + 0x18) = *(s64 *)(param_1 + 0x18) + 4;
                return;
            }
            *(u8 *)(param_1 + 8) = 1;
        }
    }
}

// 0x710022b560 — delegate: copy 3 fields from param_2, pass to FUN_71001b4300 (80 bytes)
void FUN_710022b560(s64 param_1, u64 *param_2)
{
    s64 target;
    u64 vec_x;
    u64 vec_y;
    u64 vec_z;

    target = FUN_71001d6b80(*(s64 *)(param_1 + 0x58) + 0x50);
    vec_x = param_2[0];
    vec_y = param_2[1];
    vec_z = param_2[2];
    FUN_71001b4300(target + 0x40, &vec_x);
}

// 0x7100231580 — setter: store param_2 at +0x20, call two update fns (80 bytes)
void FUN_7100231580(s64 param_1, u64 param_2, u64 param_3)
{
    u64 value_copy;

    *(u64 *)(param_1 + 0x20) = param_2;
    FUN_71001df8d0(*(u64 *)(param_1 + 0x30), param_2, 0);
    value_copy = param_2;
    FUN_71001df950(*(u64 *)(param_1 + 0x30), param_3, &value_copy);
}

// 0x7100240210 — delegate: copy 3 fields at +0x2a0, forward to FUN_710023d9c0 (80 bytes)
void FUN_7100240210(s64 param_1)
{
    u64 pos_x;
    u64 pos_y;
    u64 pos_z;

    pos_x = *(u64 *)(param_1 + 0x2a0);
    pos_y = *(u64 *)(param_1 + 0x2a8);
    pos_z = *(u64 *)(param_1 + 0x2b0);
    FUN_710023d9c0(param_1, &pos_x);
}

// 0x710024cc70 — delegate: forward, then conditionally clear flag and call second (64 bytes)
void FUN_710024cc70(s64 param_1, s64 param_2)
{
    FUN_710024c6d0(param_2, param_1);
    if (*(s8 *)(param_2 + 8) != '\0') {
        return;
    }
    *(u8 *)(param_1 + 0x60) = 0;
    FUN_7100228e20(param_2, param_1 + 0x68);
}

// 0x7100265d20 — bool wrapper: FUN_71002659f0() & 1 (32 bytes)
u32 FUN_7100265d20(void)
{
    u32 result = FUN_71002659f0();
    return result & 1;
}

// 0x710026c5f0 — delegate: mask param_4 bit0, forward to FUN_710026c2c0 (48 bytes)
u32 FUN_710026c5f0(s64 param_1, u64 param_2, u64 param_3, u8 param_4)
{
    u32 result;
    u8 flag_buf[4];

    flag_buf[0] = param_4 & 1;
    result = FUN_710026c2c0(param_1 + 8, param_2, param_3, flag_buf);
    return result & 1;
}

// 0x71002b3940 — ctor: parent init, set 3 fields (48 bytes)
void FUN_71002b3940(u16 *param_1)
{
    FUN_7100031140();
    param_1[3] = 0x29;
    *param_1 = 0x101;
    *(u8 *)(param_1 + 1) = 1;
}

// 0x71002b4340 — cleanup: call two dtor helpers on *param_1, then clear (48 bytes)
void FUN_71002b4340(u64 *param_1)
{
    FUN_71002b9660(*param_1);
    FUN_71002b9360(*param_1);
    *param_1 = 0;
}

// 0x71002b46c0 — delegate: copy 2 fields from param_2 to stack, call FUN_71002bbb30 (48 bytes)
void FUN_71002b46c0(u64 *param_1, u64 *param_2)
{
    u64 val_y;
    u64 val_x;

    val_y = param_2[1];
    val_x = param_2[0];
    FUN_71002bbb30(*param_1, &val_x);
}

// 0x71002b4c70 — cleanup: call two dtor helpers on *param_1, then clear (48 bytes)
void FUN_71002b4c70(u64 *param_1)
{
    FUN_71002be4e0(*param_1);
    FUN_71002be0b0(*param_1);
    *param_1 = 0;
}

// 0x71002b92c0 — bit util: negate low 10 bits, or set 0x1ff/0x200 sentinel (64 bytes)
void FUN_71002b92c0(u32 *param_1)
{
    u32 negated;
    u32 sentinel;
    u32 current;

    current = *param_1;
    negated = -current & 0x3ff;
    if ((current & 0x3ff) == 0x1ff) {
        negated = 0x200;
    }
    sentinel = 0x1ff;
    if ((current & 0x3ff) != 0x200) {
        sentinel = negated;
    }
    *param_1 = current & 0xfffffc00u | sentinel;
}

// 0x71002ba550 — delegate: compute indexed offset, call FUN_71002c31d0 (32 bytes)
void FUN_71002ba550(s64 param_1, u32 param_2)
{
    FUN_71002c31d0(param_1 + (u64)param_2 * 0x128 + 0x5a0);
}

// 0x71002bae40 — ctor: parent init, set field to 0x1000000040 (32 bytes)
void FUN_71002bae40(u64 *param_1)
{
    FUN_7100031070();
    *param_1 = 0x1000000040ULL;
}
