#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 002
// Range: 0x7101000000 -- 0x7101FFFFFF
// Rewritten: pool-e — meaningful names, sort annotations

// Forward declarations
extern "C" void FUN_71016ec6a0(s32*, s32*, s32*, s32*, s32*);

// PTR_LAB vtable tables (hidden: original uses adrp+add, not GOT)
extern u8 PTR_LAB_7105065310 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_71050652c8 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_7105065280 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_7105065238 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_71050651f0 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_71050651a8 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_7105065160 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_7105065118 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_7105078920 __attribute__((visibility("hidden")));

// 0x710140f9b0
void FUN_710140f9b0(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065310;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x710140faa0
void FUN_710140faa0(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_71050652c8;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x710140fba0
void FUN_710140fba0(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065280;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x710140fd30
void FUN_710140fd30(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065238;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x710140fe40
void FUN_710140fe40(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_71050651f0;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x710140ff70
void FUN_710140ff70(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_71050651a8;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x7101410100
void FUN_7101410100(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065160;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x7101410210
void FUN_7101410210(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_7105065118;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x7101434010
// Remaps fighter IDs to canonical values, stores ID + color at struct offsets, sets active flags
void FUN_7101434010(s64 self, u32 fighter_id, u32 color)
{
  u32 canonical_id;

  canonical_id = 0x6e;
  switch(fighter_id) {
  case 0x24:
  case 0x6f:
    canonical_id = 0x24;
    break;
  case 0x25:
  case 0x70:
    canonical_id = 0x25;
    break;
  case 0x26:
  case 0x71:
    canonical_id = 0x26;
    break;
  default:
    canonical_id = fighter_id;
    break;
  case 0x4b:
  case 0x4c:
    break;
  case 0x72:
    canonical_id = 0x72;
  }
  *(u32 *)(self + 0x170) = canonical_id;
  *(u32 *)(self + 0x174) = color & 0xff;
  *(u8 *)(self + 0x168) = 1;
  *(u8 *)(self + 0x16a) = 1;
  return;
}

// 0x7101648bc0
// Initializes a triple: vtable + two u64 fields from source
void FUN_7101648bc0(s64 src, u64 *out)
{
  u64 field2;

  *out = (u64)&PTR_LAB_7105078920;
  field2 = *(u64 *)(src + 0x10);
  out[1] = *(u64 *)(src + 8);
  out[2] = field2;
  return;
}

// 0x71016ec830
// Insertion sort (s32) with small-array specialization (cases 2–5).
// Direct s32 comparison (no key mask). Bails after 8 insertions.
u8 FUN_71016ec830(s32 *first, s32 *last)
{
  s32 elem2;
  s32 elem3;
  s64 shift_pos;
  s32 last_sorted;
  s32 *dst;
  s32 elem;
  s32 *cur;
  s64 offset;
  s64 pos;

  switch(((s64)last - (s64)first) >> 2) {
  case 0:
  case 1:
    break;
  case 2:
    elem = *first;
    if (elem <= last[-1]) {
      return true;
    }
    *first = last[-1];
LAB_71016eca4c:
    last[-1] = elem;
    return true;
  case 3:
    elem = *first;
    elem2 = first[1];
    elem3 = last[-1];
    if (elem2 < elem) {
      if (elem3 < elem2) {
        *first = elem3;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (elem <= last[-1]) {
          return true;
        }
        first[1] = last[-1];
      }
      goto LAB_71016eca4c;
    }
    if (elem2 <= elem3) {
      return true;
    }
    first[1] = elem3;
    last[-1] = elem2;
    elem = *first;
    if (first[1] < elem) {
      *first = first[1];
      first[1] = elem;
      return true;
    }
    break;
  case 4:
    elem = *first;
    elem2 = first[1];
    elem3 = first[2];
    last_sorted = elem3;
    if (elem2 < elem) {
      if (elem3 < elem2) {
        *first = elem3;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (elem <= elem3) goto LAB_71016eca7c;
        first[1] = elem3;
      }
      first[2] = elem;
      last_sorted = elem;
    }
    else if (elem3 < elem2) {
      first[1] = elem3;
      first[2] = elem2;
      last_sorted = elem2;
      if (elem3 < elem) {
        *first = elem3;
        first[1] = elem;
      }
    }
LAB_71016eca7c:
    if (last_sorted <= last[-1]) {
      return true;
    }
    first[2] = last[-1];
    last[-1] = last_sorted;
    elem = first[1];
    elem2 = first[2];
    if (elem <= elem2) {
      return true;
    }
    elem3 = *first;
    first[1] = elem2;
    first[2] = elem;
    if (elem2 < elem3) {
      *first = elem2;
      first[1] = elem3;
      return true;
    }
    break;
  case 5:
    FUN_71016ec6a0(first, first + 1, first + 2, first + 3, last - 1);
    return true;
  default:
    // Sort first 3 elements, then insertion-sort the rest
    elem = *first;
    elem2 = first[1];
    elem3 = first[2];
    last_sorted = elem3;
    if (elem2 < elem) {
      if (elem3 < elem2) {
        *first = elem3;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (elem <= elem3) goto LAB_71016ec9a0;
        first[1] = elem3;
      }
      first[2] = elem;
      last_sorted = elem;
    }
    else if (elem3 < elem2) {
      first[1] = elem3;
      first[2] = elem2;
      last_sorted = elem2;
      if (elem3 < elem) {
        *first = elem3;
        first[1] = elem;
      }
    }
LAB_71016ec9a0:
    if (first + 3 == last) {
      return true;
    }
    offset = 0;
    elem = 0;
    cur = first + 3;
    do {
      elem2 = *cur;
      pos = offset;
      if (elem2 < last_sorted) {
        // Shift elements right to insert current
        do {
          shift_pos = pos;
          *(s32 *)((s64)first + shift_pos + 0xc) = last_sorted;
          dst = first;
          if (shift_pos == -8) goto LAB_71016eca04;
          last_sorted = *(s32 *)((s64)first + shift_pos + 4);
          pos = shift_pos + -4;
        } while (elem2 < last_sorted);
        dst = (s32 *)((s64)first + shift_pos + 8);
LAB_71016eca04:
        elem = elem + 1;
        *dst = elem2;
        if (elem == 8) {
          return (u8)(cur + 1 == last);
        }
      }
      if (cur + 1 == last) {
        return true;
      }
      last_sorted = *cur;
      offset = offset + 4;
      cur = cur + 1;
    } while( true );
  }
  return true;
}

// 0x710177e0f0
// Filters slot IDs into a result list based on bitmask and slot-value checks.
// Iterates 4 columns per row; skips slots whose value array contains certain matches.
void FUN_710177e0f0(u16 *bitmask, s32 row, s32 col_start, s32 *slot_values, u32 check_secondary,
                   u32 force_include, s64 result_list)
{
  u32 slot_id;
  u32 bit;
  s32 col;

  col = 0;
  do {
    if ((row * 4 - col_start) + col != 0) {
      slot_id = row * 4 + col;
      // Skip certain slot IDs if any of the 8 slot_values match a forbidden value
      switch(slot_id) {
      case 9:
        if ((*slot_values == 2) ||
           ((((slot_values[1] == 2 || (slot_values[2] == 2)) ||
             ((slot_values[3] == 2 || (((slot_values[4] == 2 || (slot_values[5] == 2)) || (slot_values[6] == 2))))))\
            || (slot_values[7] == 2)))) goto next_col;
        break;
      case 0xb:
        if ((((*slot_values == 3) || (slot_values[1] == 3)) ||
            ((slot_values[2] == 3 || (((slot_values[3] == 3 || (slot_values[4] == 3)) || (slot_values[5] == 3))))))\
           || ((slot_values[6] == 3 || (slot_values[7] == 3)))) goto next_col;
        break;
      case 0xc:
        if ((*slot_values == 6) ||
           ((((((slot_values[1] == 6 || (slot_values[2] == 6)) || (slot_values[3] == 6)) ||
              ((slot_values[4] == 6 || (slot_values[5] == 6)))) || (slot_values[6] == 6)) || (slot_values[7] == 6)))\
           ) goto next_col;
        break;
      case 0xe:
        if ((((*slot_values == 7) || (slot_values[1] == 7)) || (slot_values[2] == 7)) ||
           (((slot_values[3] == 7 || (slot_values[4] == 7)) ||
            ((slot_values[5] == 7 || ((slot_values[6] == 7 || (slot_values[7] == 7)))))))) goto next_col;
      }
      // Include slot if force_include is set, or if bitmask permits it
      if (((force_include & 1) != 0) ||
         ((bit = 1 << (u64)(slot_id & 0x1f), (bit & *bitmask) == 0 &&
          (((check_secondary & 1) == 0 || ((bit & bitmask[1]) == 0)))))) {
        *(u32 *)(*(s64 *)(result_list + 0x10) + *(s64 *)(result_list + 0x18) * 4) = slot_id;
        *(s64 *)(result_list + 0x18) = *(s64 *)(result_list + 0x18) + 1;
      }
    }
next_col:
    col = col + 1;
    if (col == 4) {
      return;
    }
  } while( true );
}
