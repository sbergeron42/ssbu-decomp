#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 001
// Range: 0x7101000000 -- 0x7101FFFFFF
// Rewritten: pool-e — meaningful names, pattern annotations

// CXA guard
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
[[noreturn]] extern "C" void abort();

// Called functions
extern "C" u64 FUN_7101315480(s64, u64);
extern "C" u64 FUN_7103263870(s64, u32);
extern "C" u64 FUN_71032643e0(s64, u64);
extern "C" u64 FUN_7103264500(s64, u64);
extern "C" u64 FUN_7103262bf0(u64, u64);

// Guard variables (bit 0 = initialized)
extern u64 DAT_71052c18b8;
extern u64 DAT_71052c18d0;
extern u64 DAT_71052c1900;
extern u64 DAT_71052c1958;
extern u64 DAT_71052c1980;
extern u64 DAT_71052c1a38;
extern u64 DAT_71052c1bc0;

// Data pointer variables
extern void *DAT_71052c18c0;
extern void *DAT_71052c18c8;
extern void *DAT_71052c1908;
extern void *DAT_71052c1960;
extern void *DAT_71052c1988;
extern void *DAT_71052c1a40;
extern void *DAT_71052c1bc8;

// PTR_LAB vtable tables
extern u8 PTR_LAB_71050238b8;
extern u8 PTR_LAB_7105027340;
extern u8 PTR_LAB_7105029988;
extern u8 PTR_LAB_7105033200;
extern u8 PTR_LAB_7105039af0;
extern u8 PTR_LAB_7105045e18;
extern u8 PTR_LAB_710505ce38;
extern u8 PTR_LAB_7105065358 __attribute__((visibility("hidden")));

// Misc data
extern u64 DAT_710532e730;
extern u8 DAT_00001790;

// 0x7101005850
// Registers vtable at +0x318, sets kind byte at +0xe8 to 7
void FUN_7101005850(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c18b8 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c18b8);
    if (acquired != 0) {
      DAT_71052c18c0 = &PTR_LAB_71050238b8;
      __cxa_guard_release((s64 *)&DAT_71052c18b8);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c18c0;
  *(u8 *)(obj + 0xe8) = 7;
  return;
}

// 0x71010439b0
// Registers vtable at +0x180
void FUN_71010439b0(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c18d0 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c18d0);
    if (acquired != 0) {
      DAT_71052c18c8 = &PTR_LAB_7105027340;
      __cxa_guard_release((s64 *)&DAT_71052c18d0);
    }
  }
  *(void ***)(obj + 0x180) = &DAT_71052c18c8;
  return;
}

// 0x710105bc60
// Registers vtable at +0x318, sets kind byte at +0xe8 to 7
void FUN_710105bc60(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c1900 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c1900);
    if (acquired != 0) {
      DAT_71052c1908 = &PTR_LAB_7105029988;
      __cxa_guard_release((s64 *)&DAT_71052c1900);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c1908;
  *(u8 *)(obj + 0xe8) = 7;
  return;
}

// 0x71010d44f0
// Registers vtable at +0x318, sets kind byte at +0xe8 to 6
void FUN_71010d44f0(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c1958 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c1958);
    if (acquired != 0) {
      DAT_71052c1960 = &PTR_LAB_7105033200;
      __cxa_guard_release((s64 *)&DAT_71052c1958);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c1960;
  *(u8 *)(obj + 0xe8) = 6;
  return;
}

// 0x71011208a0
// Registers vtable at +0x318
void FUN_71011208a0(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c1980 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c1980);
    if (acquired != 0) {
      DAT_71052c1988 = &PTR_LAB_7105039af0;
      __cxa_guard_release((s64 *)&DAT_71052c1980);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c1988;
  return;
}

// 0x71011d5680
// Registers vtable at +0x318
void FUN_71011d5680(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c1a38 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c1a38);
    if (acquired != 0) {
      DAT_71052c1a40 = &PTR_LAB_7105045e18;
      __cxa_guard_release((s64 *)&DAT_71052c1a38);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c1a40;
  return;
}

// 0x710130e1f0
// Registers vtable at +0x318
void FUN_710130e1f0(u64 unused, s64 obj)
{
  s32 acquired;

  if ((DAT_71052c1bc0 & 1) == 0) {
    acquired = __cxa_guard_acquire((s64 *)&DAT_71052c1bc0);
    if (acquired != 0) {
      DAT_71052c1bc8 = &PTR_LAB_710505ce38;
      __cxa_guard_release((s64 *)&DAT_71052c1bc0);
    }
  }
  *(void ***)(obj + 0x318) = &DAT_71052c1bc8;
  return;
}

// 0x7101315010
// Looks up a tagged hash by case_id (0x23–0x28), copies 36-byte entry to out. Returns 1 on success.
u64 FUN_7101315010(s64 self, u32 case_id, u64 *out)
{
  u64 field_1;
  u64 field_2;
  u64 *entry;
  u64 hash;
  u64 field_3;

  switch(case_id) {
  case 0x23:
    hash = 0x6f9741949;
    goto do_lookup;
  case 0x24:
    hash = 0x53e1c61;
    break;
  case 0x25:
    hash = 0xe0a45c026;
    goto do_lookup;
  case 0x26:
    hash = 0xf33c2ac;
    break;
  case 0x27:
    hash = 0x6a96d306;
    goto tag_08;
  case 0x28:
    hash = 0xc50ca65a;
  tag_08:
    hash = hash | 0x800000000ULL;
    goto do_lookup;
  default:
    return 0;
  }
  hash = hash | 0x500000000ULL;
do_lookup:
  entry = (u64 *)FUN_7101315480(self + 0x30, hash);
  *out = *entry;
  field_3 = entry[3];
  field_1 = entry[1];
  field_2 = entry[2];
  *(u32 *)(out + 4) = *(u32 *)(entry + 4);
  out[1] = field_1;
  out[2] = field_2;
  out[3] = field_3;
  return 1;
}

// 0x7101382240
// Checks if all 8 slots (stride 0x3860) pass a threshold comparison.
// Two modes based on byte at +3: mode 1-2 use char field at +0x7c, mode 0 uses s32 at +0x3864.
u64 FUN_7101382240(s64 self, s32 threshold)
{
  s32 ref_value;
  s64 active_index;

  if (((*(char *)(self + 0x1e) == '\x01') &&
      (active_index = (s64)*(s32 *)(self + 0x24), *(s32 *)(self + 0x24) != -1)) &&
     (*(char *)(self + active_index * 0x3860 + 0x62) == '\0')) {
    if (*(u8 *)(self + 3) - 1 < 2) {
      // Mode 1-2: compare threshold against char differences (stride 0x3860, field +0x7c)
      ref_value = (s32)*(char *)(self + active_index * 0x3860 + 0x7c);
      if (((((*(char *)(self + 0x62) != '\x01') || (threshold <= ref_value - *(char *)(self + 0x7c))
            ) && ((*(char *)(self + 0x38c2) != '\x01' ||
                  (threshold <= ref_value - *(char *)(self + 0x38dc))))) &&
          (((*(char *)(self + 0x7122) != '\x01' ||
            (threshold <= ref_value - *(char *)(self + 0x713c))) &&
           ((*(char *)(self + 0xa982) != '\x01' ||
            (threshold <= ref_value - *(char *)(self + 0xa99c))))))) &&
         (((((*(char *)(self + 0xe1e2) != '\x01' ||
             (threshold <= ref_value - *(char *)(self + 0xe1fc))) &&
            ((*(char *)(self + 0x11a42) != '\x01' ||
             (threshold <= ref_value - *(char *)(self + 0x11a5c))))) &&
           ((*(char *)(self + 0x152a2) != '\x01' ||
            (threshold <= ref_value - *(char *)(self + 0x152bc))))) &&
          ((*(char *)(self + 0x18b02) != '\x01' ||
           (threshold <= ref_value - *(char *)(self + 0x18b1c))))))) {
        return 1;
      }
    }
    else {
      if (*(u8 *)(self + 3) != 0) {
        return 1;
      }
      // Mode 0: compare threshold against s32 differences (stride 0x3860, field +0x3864)
      ref_value = *(s32 *)(self + active_index * 0x3860 + 0x3864);
      if ((((((*(char *)(self + 0x62) != '\x01') ||
             (threshold <= ref_value - *(s32 *)(self + 0x3864))) &&
            ((*(char *)(self + 0x38c2) != '\x01' ||
             (threshold <= ref_value - *(s32 *)(self + 0x70c4))))) &&
           ((*(char *)(self + 0x7122) != '\x01' ||
            (threshold <= ref_value - *(s32 *)(self + 0xa924))))) &&
          (((*(char *)(self + 0xa982) != '\x01' ||
            (threshold <= ref_value - *(s32 *)(self + 0xe184))) &&
           ((((*(char *)(self + 0xe1e2) != '\x01' ||
              (threshold <= ref_value - *(s32 *)(self + 0x119e4))) &&
             ((*(char *)(self + 0x11a42) != '\x01' ||
              (threshold <= ref_value - *(s32 *)(self + 0x15244))))) &&
            ((*(char *)(self + 0x152a2) != '\x01' ||
             (threshold <= ref_value - *(s32 *)(self + 0x18aa4))))))))) &&
         ((*(char *)(self + 0x18b02) != '\x01' ||
          (threshold <= ref_value - *(s32 *)(self + 0x1c304))))) {
        return 1;
      }
    }
  }
  return 0;
}

// 0x7101388b90
// Returns a category value based on input kind
u64 FUN_7101388b90(u8 kind)
{
  u64 result;

  result = 0;
  switch(kind) {
  case 0:
  case 2:
  case 3:
  case 0x22:
    return 2;
  case 0x1d:
  case 0x29:
  case 0x3e:
  case 0x45:
    result = 5;
  }
  return result;
}

// 0x710138ac00
// Checks bool field at offset 200 (0xC8) via double-deref from info+8
u8 FUN_710138ac00(s64 info)
{
  if (*(s64 **)(info + 8) != nullptr) {
    return *(char *)(**(s64 **)(info + 8) + 200) != '\0';
  }
  return false;
}

// 0x710138b020
// Checks bool field at offset 0x6A0 via double-deref from info+8
u8 FUN_710138b020(s64 info)
{
  if (*(s64 **)(info + 8) != nullptr) {
    return *(char *)(**(s64 **)(info + 8) + 0x6a0) != '\0';
  }
  return false;
}

// 0x710138b120
// Checks bool field at offset 0x178 via double-deref from info+8
u8 FUN_710138b120(s64 info)
{
  if (*(s64 **)(info + 8) != nullptr) {
    return *(char *)(**(s64 **)(info + 8) + 0x178) != '\0';
  }
  return false;
}

// 0x710138b1c0
// Checks bool at +0x70 via double-deref, then validates index at +0x14
u8 FUN_710138b1c0(s64 info)
{
  if (*(s64 **)(info + 8) == nullptr) {
    return false;
  }
  if (*(char *)(**(s64 **)(info + 8) + 0x70) != '\0') {
    return *(s32 *)(info + 0x14) != -1;
  }
  return false;
}

// 0x710138c450
// Checks bool field at offset 0x648 via double-deref from info+8
u8 FUN_710138c450(s64 info)
{
  if (*(s64 **)(info + 8) != nullptr) {
    return *(char *)(**(s64 **)(info + 8) + 0x648) != '\0';
  }
  return false;
}

// 0x710138c9b0
// Remaps certain fighter IDs, then looks up from game DB at +0x160/+0x168.
// Falls back to a secondary hash lookup if the first result indicates redirect.
u64 FUN_710138c9b0(u32 fighter_id)
{
  u64 result;
  u64 check;
  u64 db_ptr;
  s64 game_data;

  switch(fighter_id) {
  case 0x4b:
  case 0x4c:
    fighter_id = 0x6e;
    break;
  case 0x6f:
    fighter_id = 0x24;
    break;
  case 0x70:
    fighter_id = 0x25;
    break;
  case 0x71:
    fighter_id = 0x26;
    break;
  case 0x73:
    fighter_id = 0x5a;
    break;
  case 0x74:
    fighter_id = 0x5b;
  }
  result = FUN_7103263870(*(s64 *)(DAT_710532e730 + 8) + 0x160, fighter_id);
  if ((result & 0xff00000000000000ULL) != 0xc100000000000000ULL || (result & 0xffffffffffULL) == 0) {
    return result;
  }
  game_data = *(s64 *)(DAT_710532e730 + 8);
  check = FUN_71032643e0(game_data + 0x160, result);
  if ((check & 1) == 0) {
    check = FUN_7103264500(game_data + 0x160, result);
    if ((check & 1) == 0) {
      return result;
    }
    db_ptr = *(u64 *)(game_data + 0x168);
    result = 0xb3e567a6;
  }
  else {
    db_ptr = *(u64 *)(game_data + 0x168);
    result = 0xb28d453e;
  }
  result = FUN_7103262bf0(db_ptr, result | 0x1300000000ULL);
  return result;
}

// 0x710139eae0
// Returns a pointer from a slot table; aborts if slot >= 8
u8 *FUN_710139eae0(s64 self, u32 slot)
{
  if (*(char *)(self + 0x10) == '\0' || slot == 0xffffffff) {
    return (u8 *)0xc1ffff0000000000ULL;
  }
  if (slot < 8) {
    return *(u8 **)(*(s64 *)(&DAT_00001790 + *(s64 *)(self + 0x50)) +
             ((s64)((u64)slot << 0x20) >> 0x17) + 0x170);
  }
  /* WARNING: Subroutine does not return */
  abort();
}

// 0x71013fc1e0
// Hash table lookup: probes an open-chaining hash map (buckets at +0x90, count at +0x98)
// Returns pointer to entry data (node+4) on match, or end sentinel (table+0x10) on miss
s64 *FUN_71013fc1e0(s64 self, s32 key)
{
  u64 rem;
  s64 table;
  u64 hash;
  u64 bucket_idx;
  u64 bucket_count;
  s64 *node;
  u64 node_hash;

  switch(key) {
  case 0x4b:
  case 0x4c:
    key = 0x6e;
    break;
  case 0x6f:
    key = 0x24;
    break;
  case 0x70:
    key = 0x25;
    break;
  case 0x71:
    key = 0x26;
    break;
  case 0x73:
    key = 0x5a;
    break;
  case 0x74:
    key = 0x5b;
  }
  table = *(s64 *)(self + 0x58);
  bucket_count = *(u64 *)(table + 0x98);
  if (bucket_count != 0) {
    node_hash = bucket_count - 1;
    hash = (u64)key;
    if ((node_hash & bucket_count) == 0) {
      // Power-of-two bucket count: use bitmask
      bucket_idx = node_hash & hash;
    }
    else {
      bucket_idx = hash;
      if (bucket_count <= hash) {
        bucket_idx = 0;
        if (bucket_count != 0) {
          bucket_idx = hash / bucket_count;
        }
        bucket_idx = hash - bucket_idx * bucket_count;
      }
    }
    node = *(s64 **)(*(s64 *)(table + 0x90) + bucket_idx * 8);
    if ((node != nullptr) && (node = (s64 *)*node, node != nullptr)) {
      if ((node_hash & bucket_count) == 0) {
        // Power-of-two path: bucket check via bitmask
        do {
          bucket_count = node[1];
          if (bucket_count != hash && (bucket_count & node_hash) != bucket_idx) break;
          if ((bucket_count == hash) && ((s32)node[2] == key)) goto found;
          node = (s64 *)*node;
        } while (node != nullptr);
      }
      else {
        // General path: bucket check via modulo
        do {
          node_hash = node[1];
          if (node_hash == hash) {
            if ((s32)node[2] == key) {
found:
              return node + 4;
            }
          }
          else {
            if (bucket_count <= node_hash) {
              rem = 0;
              if (bucket_count != 0) {
                rem = node_hash / bucket_count;
              }
              node_hash = node_hash - rem * bucket_count;
            }
            if (node_hash != bucket_idx) break;
          }
          node = (s64 *)*node;
        } while (node != nullptr);
      }
    }
  }
  return (s64 *)(table + 0x10);
}

// 0x710140f7a0
// Initializes a pair: sets vtable pointer and copies u64 from src+8
void FUN_710140f7a0(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065358;
  out[1] = *(u64 *)(src + 8);
  return;
}
