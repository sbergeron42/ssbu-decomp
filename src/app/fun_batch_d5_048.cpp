#include "types.h"

extern "C" {
    void *memset(void *s, int c, u64 n);
    void *memcpy(void *dst, const void *src, u64 n);
    void *malloc(s64 size);
}

// MEDIUM-tier FUN_* functions — batch d5-048
// Pool-d worker: misc small functions from 0x71000* range
// Rewritten: pool-e — meaningful param names, pattern comments

// ---- Struct initializers and field setters ----

// 0x7100031390 — 32B struct initializer
void FUN_7100031390(u8 *out) {
    *out = 1;
    *(u64 *)(out + 4) = 0;
    *(u16 *)(out + 2) = 0;
    *(u32 *)(out + 0xc) = 1;
    *(u64 *)(out + 0x18) = 0;
}

// 0x71000313b0 — 32B struct initializer
void FUN_71000313b0(u8 *out) {
    *out = 1;
    *(u16 *)(out + 2) = 0;
    *(u64 *)(out + 8) = 0x100000000ULL;
    *(u64 *)(out + 0x18) = 0;
}

// 0x71000314e0 — set active flag + value
void FUN_71000314e0(u8 *self, u64 value) {
    *self = 1;
    self[1] = self[1] | 1;
    *(u64 *)(self + 8) = value;
}

// 0x7100031850 — zero 9 u64 fields
void FUN_7100031850(u64 *out) {
    out[7] = 0;
    out[8] = 0;
    out[0] = 0;
    out[5] = 0;
    out[6] = 0;
    out[3] = 0;
    out[4] = 0;
    out[1] = 0;
    out[2] = 0;
}

// 0x7100044c70 — init render state
void FUN_7100044c70(s64 self, u64 value) {
    *(u8 *)(self + 0x18c) = 1;
    *(u64 *)(self + 400) = 0;
    *(u16 *)(self + 0x198) = 0;
    *(u64 *)(self + 0xc0) = value;
}

// 0x7100047c70 — doubly-linked list splice
void FUN_7100047c70(s64 *node, s64 list) {
    s64 *list_next = (s64 *)(list + 8);
    s64 old_next = *list_next;
    *list_next = *node;
    *(s64 **)(old_next + 8) = node;
    *(s64 **)(node[0] + 8) = list_next;
    *node = old_next;
}

// 0x710004c5e0 — reverse index access into array
u64 FUN_710004c5e0(s64 *arr, u32 index) {
    return *(u64 *)(*arr + (s64)(s32)((s32)arr[1] + ~(s32)index) * 8);
}

// 0x7100055470 — get base ptr with offset from nested struct
s64 FUN_7100055470(s64 self, s64 context) {
    s64 base = *(s64 *)(*(s64 *)(context + 200) + 0x38);
    if (base != 0) {
        return base + (u64)*(u32 *)(self + 0x34);
    }
    return 0;
}

// 0x7100060e80 — clear 4 u16 fields, set flags
void FUN_7100060e80(u16 *self) {
    self[4] = 0;
    self[5] = 0;
    self[6] = 0;
    self[7] = 0;
    *self = (u16)(*self & 0xe000 | 0x90);
}

// 0x7100060f20 — bit field write (2 bits each)
void FUN_7100060f20(u16 *self, u16 field_a, u32 field_b) {
    *self = (u16)(field_a & 3) | (u16)((field_b & 3) << 2) | (*self & 0xfff0);
}

// 0x7100060f40 — bit field write (3+1 bits)
void FUN_7100060f40(u16 *self, u32 field_a, u32 field_b) {
    *self = (u16)((field_a & 7) << 4) | (u16)((field_b & 1) << 7) | (*self & 0xff0f);
}

// 0x7100066040 — check nested char flag
u64 FUN_7100066040(u64 self) {
    if (self != 0) {
        self = (u64)(**(char **)(self + 0x68) != '\0');
    }
    return self;
}

// 0x7100077eb0 — SNPrintf with format "%s_%d"
extern int FUN_7100a85650(char *buf, s64 sz, const char *fmt, ...); // nn::util::SNPrintf
int FUN_7100077eb0(char *buf, s32 buf_size, u64 name, s64 entry) {
    return FUN_7100a85650(buf, (s64)buf_size, "%s_%d", name, (u64)*(u32 *)(entry + 4));
}

// 0x71000093f0 — check flags bitfield
u64 FUN_71000093f0(u64 self, s32 mask) {
    if (self != 0) {
        self = (u64)((*(u64 *)(self + 0xe8) & (s64)mask) != 0);
    }
    return self;
}

// 0x71000145a0 — compare obj ptr at +0x8f0
bool FUN_71000145a0(s64 target, s64 self) {
    if (*(s64 **)(self + 0x8f0) != (s64 *)0) {
        return **(s64 **)(self + 0x8f0) == target;
    }
    return false;
}

// 0x71000145c0 — compare obj ptr at +0x8d0
bool FUN_71000145c0(s64 target, s64 self) {
    if (*(s64 **)(self + 0x8d0) != (s64 *)0) {
        return **(s64 **)(self + 0x8d0) == target;
    }
    return false;
}

// 0x7100013730 — socket fcntl set nonblocking
extern s32 FUN_71001a9ba0(u64 sock, s32 cmd, u32 flags); // nnsocketFcntl
void FUN_7100013730(u64 sock, s32 nonblocking) {
    u32 flags = 2;
    if (nonblocking != 0) {
        flags = 0x802;
    }
    FUN_71001a9ba0(sock, 4, flags);
}

// 0x71000b1940 — SDK version symbol reference
extern void FUN_71000b1950(const char *sym); // nn::util::ReferSymbol
void FUN_71000b1940(void) {
    FUN_71000b1950("SDK MW+Nintendo+PiaCommon-5_19_1");
}

// 0x71000b65e0 — init Pia timestamp entry
extern void FUN_71000b65f0(u32 *); // nn::pia::common::Time::SetNow
void FUN_71000b65e0(u32 *entry) {
    *entry = 0xffffffff;
    *(u64 *)(entry + 2) = 0;
    *(u8 *)(entry + 4) = 1;
    FUN_71000b65f0(entry + 2);
}

// 0x710013bc98 — SendMessageQueue wrapper returning 1
extern void FUN_710013bc00(void *q, u64 val); // nn::os::SendMessageQueue
u64 FUN_710013bc98(void *queue, u64 msg) {
    FUN_710013bc00(queue, msg);
    return 1;
}

// 0x710013bd08 — JamMessageQueue wrapper returning 1
extern void FUN_710013bd20(void *q, u64 val); // nn::os::JamMessageQueue
u64 FUN_710013bd08(void *queue, u64 msg) {
    FUN_710013bd20(queue, msg);
    return 1;
}

// 0x7100113400 — set byte field + set bit 3 in flags
void FUN_7100113400(s64 self, u8 value) {
    *(u8 *)(self + 0xa3d) = value & 1;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 8;
}

// 0x7100113480 — set byte field + set bit 0x1000 in flags
void FUN_7100113480(s64 self, u8 value) {
    *(u8 *)(self + 0x9ca) = value & 1;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 0x1000;
}

// 0x71001133a0 — set u16 pair + bit 2 in flags
void FUN_71001133a0(s64 self, u16 value) {
    *(u16 *)(self + 0xa38) = 0xffff;
    *(u16 *)(self + 0xa3a) = value;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 2;
}

// 0x71001133c0 — set u16 pair (both params) + bit 2 in flags
void FUN_71001133c0(s64 self, u16 value_a, u16 value_b) {
    *(u16 *)(self + 0xa38) = value_b;
    *(u16 *)(self + 0xa3a) = value_a;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 2;
}

// 0x71001133e0 — set byte field + bit 4 in flags
void FUN_71001133e0(s64 self, u8 value) {
    *(u8 *)(self + 0xa3c) = value & 1;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 4;
}

// 0x71001134a0 — set byte field + bit 0x2000 in flags
void FUN_71001134a0(s64 self, u8 value) {
    *(u8 *)(self + 0x9cb) = value & 1;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 0x2000;
}

// 0x71001136c0 — set byte field + bit 0x100000 in flags
void FUN_71001136c0(s64 self, u8 value) {
    *(u8 *)(self + 0xa08) = value & 1;
    *(u32 *)(self + 0xd30) = *(u32 *)(self + 0xd30) | 0x100000;
}

// 0x710012eb20 — set two u16 fields + bit 1 in flags
void FUN_710012eb20(s64 self, u16 value) {
    *(u16 *)(self + 0x256) = value;
    *(u16 *)(self + 600) = value;
    *(u32 *)(self + 0x260) = *(u32 *)(self + 0x260) | 1;
}

// 0x710012eb40 — set two u16 fields + bit 2 in flags
void FUN_710012eb40(s64 self, u16 value) {
    *(u16 *)(self + 0x25a) = value;
    *(u16 *)(self + 0x25c) = value;
    *(u32 *)(self + 0x260) = *(u32 *)(self + 0x260) | 2;
}

// 0x710012eb60 — set bool field + bit 4 in flags
void FUN_710012eb60(s64 self, u8 value) {
    *(u8 *)(self + 0x25e) = value & 1;
    *(u32 *)(self + 0x260) = *(u32 *)(self + 0x260) | 4;
}

// 0x710012eb80 — set bool field + bit 8 in flags
void FUN_710012eb80(s64 self, u8 value) {
    *(u8 *)(self + 0x25f) = value & 1;
    *(u32 *)(self + 0x260) = *(u32 *)(self + 0x260) | 8;
}

// 0x7100130ac0 — intrusive list insert before (head)
void FUN_7100130ac0(s64 *head, s64 *new_node) {
    s64 old_first = *head;
    *head = (s64)new_node;
    *new_node = old_first;
    new_node[1] = (s64)head;
    if (old_first != 0) {
        *(s64 **)(old_first + 8) = new_node;
    }
}

// 0x710014f090 — copy 3 u32 fields from src to dst
void FUN_710014f090(s64 dst, s64 src) {
    *(u32 *)(dst + 0x10) = *(u32 *)(src + 0x10);
    *(u32 *)(dst + 8) = *(u32 *)(src + 8);
    *(u32 *)(dst + 0xc) = *(u32 *)(src + 0xc);
}

// 0x71001604a0 — set 2-bit field in byte
void FUN_71001604a0(s64 self, u32 value) {
    *(u8 *)(self + 0x78) = (u8)(*(u8 *)(self + 0x78) & 0xf3 | (u8)((value & 3) << 2));
}
