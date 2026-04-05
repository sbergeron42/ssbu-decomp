#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 003
// Range: 0x7101000000 -- 0x7101FFFFFF
// Rewritten: pool-e — meaningful names, SORT_KEY_MASK, float annotations

// Sort key extraction mask — zeroes bits [47:40], keeps top byte + lower 40 bits
#define SORT_KEY_MASK 0xff0000ffffffffffULL

// Forward declarations
[[noreturn]] extern "C" void abort();
extern "C" void *je_aligned_alloc(u64, u64);
extern "C" void FUN_7103776360(u64 *, u64, const char *);
extern "C" u64 FUN_7101704c50(s64);
extern "C" void FUN_710326f0f0(s64 *, s32, s32, s32, s32, s32, s32);
extern "C" u64 FUN_7101797640(u64, s32, s32);
extern "C" void FUN_710392e590(s64);
extern "C" u64 FUN_7101aab430(s32);
extern "C" s32 FUN_710328cae0(u64, u64);
extern "C" u64 FUN_7103262bf0(u64, u64);
extern "C" s32 FUN_71032b82d0(u64, u64, u32 *);
extern "C" void ui2d_apply_named_animation(u32, u64, const char *);
extern "C" void FUN_7103779b70(s64, s64);
extern "C" void FUN_7103779cd0(s64, const char *, ...);
extern "C" void FUN_710377a1a0(s64, ...);
extern "C" void FUN_710377a930(u32, s64);
extern "C" void FUN_710377aa60(u32, s64);
extern "C" void FUN_710377ab90(s64);
extern "C" void FUN_7103775b40(u64, s32);
extern "C" void FUN_71018e80b0(u64 *, u64 *, u64 *, u64 *, u64 *);
extern "C" void FUN_71019919c0(u64 *, u64 *, u64 *, u64 *, u64 *);
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);

// Data symbols
extern u8 PTR_LAB_71050a90b8 __attribute__((visibility("hidden")));
extern u8 DAT_7104ad95d0 __attribute__((visibility("hidden")));
extern u8 PTR_DAT_710523c9a8;
extern s64 *DAT_7105331f00;
extern u64 DAT_71052c3c58;
extern u64 DAT_710532e730;
extern s64 *g_profile_chain_root;

// 0x71017ac210
// Initializes a 6-element packed-value array with sentinel values
void FUN_71017ac210(u64 *out)
{
  out[0] = 0x69ffff0000000000ULL;
  out[1] = 0x69ffff0000000000ULL;
  out[2] = 0;
  out[3] = 0xd9ffff0000000000ULL;
  out[4] = 0;
  out[5] = 0xd9ffff0000000000ULL;
  return;
}

// 0x71018e8290
// Insertion sort (variant A) with small-array specialization (cases 2–5).
// Elements are packed u64 with sort key extracted via SORT_KEY_MASK.
// Bails after 8 insertions (introsort partial-sort threshold) returning false.
// Note: uVar6/uVar7/uVar9/uVar11 have swapped roles across switch cases due to register reuse.
u8 FUN_71018e8290(u64 *first, u64 *last)
{
  u8 flag;
  u64 temp;
  u64 *dst;
  u64 *cur;
  s32 insert_count;
  u64 uVar6;
  u64 uVar7;
  u64 elem;
  u64 uVar9;
  u64 elem2;
  u64 uVar11;
  u64 *shift;

  switch(((s64)last - (s64)first) >> 3) {
  case 0:
  case 1:
    return true;
  case 2:
    elem = *first;
    if ((elem & SORT_KEY_MASK) <= (last[-1] & SORT_KEY_MASK)) {
      return true;
    }
    *first = last[-1];
    break;
  case 3:
    elem = *first;
    elem2 = first[1];
    temp = last[-1];
    uVar6 = elem2 & SORT_KEY_MASK;  // key of second
    if ((elem & SORT_KEY_MASK) <= uVar6) {
      if (uVar6 <= (temp & SORT_KEY_MASK)) {
        return true;
      }
      first[1] = temp;
      last[-1] = elem2;
      elem = *first;
      if ((elem & SORT_KEY_MASK) <= (first[1] & SORT_KEY_MASK)) {
        return true;
      }
      *first = first[1];
      first[1] = elem;
      return true;
    }
    if ((temp & SORT_KEY_MASK) < uVar6) {
      *first = temp;
    }
    else {
      *first = elem2;
      first[1] = elem;
      if ((elem & SORT_KEY_MASK) <= (last[-1] & SORT_KEY_MASK)) {
        return true;
      }
      first[1] = last[-1];
    }
    break;
  case 4:
    elem = *first;
    elem2 = first[1];
    uVar9 = first[2];                // third element
    uVar7 = elem2 & SORT_KEY_MASK;   // key of second
    uVar11 = elem & SORT_KEY_MASK;    // key of first
    uVar6 = uVar9 & SORT_KEY_MASK;    // key of third
    temp = uVar9;
    if (uVar7 < uVar11) {
      if (uVar6 < uVar7) {
        *first = uVar9;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (uVar11 <= uVar6) goto LAB_71018e851c;
        first[1] = uVar9;
      }
      first[2] = elem;
      temp = elem;
      uVar6 = uVar11;
    }
    else if (uVar6 < uVar7) {
      flag = uVar6 < uVar11;
      first[1] = uVar9;
      first[2] = elem2;
      temp = elem2;
      uVar6 = uVar7;
      if (flag) {
        *first = uVar9;
        first[1] = elem;
      }
    }
LAB_71018e851c:
    if (uVar6 <= (last[-1] & SORT_KEY_MASK)) {
      return true;
    }
    first[2] = last[-1];
    last[-1] = temp;
    elem = first[1];
    elem2 = first[2];
    if ((elem & SORT_KEY_MASK) <= (elem2 & SORT_KEY_MASK)) {
      return true;
    }
    first[1] = elem2;
    first[2] = elem;
    elem = *first;
    if ((elem & SORT_KEY_MASK) <= (elem2 & SORT_KEY_MASK)) {
      return true;
    }
    *first = elem2;
    first[1] = elem;
    return true;
  case 5:
    FUN_71018e80b0(first, first + 1, first + 2, first + 3, last - 1);
    return true;
  default:
    // Sort first 3 elements, then insertion-sort the rest
    elem = *first;
    elem2 = first[1];
    uVar6 = first[2];                 // third element (uVar6 = element here, not key)
    uVar11 = elem2 & SORT_KEY_MASK;   // key of second
    uVar7 = elem & SORT_KEY_MASK;     // key of first
    uVar9 = uVar6 & SORT_KEY_MASK;    // key of third (uVar9 = key here, not element)
    temp = uVar6;
    if (uVar11 < uVar7) {
      if (uVar9 < uVar11) {
        *first = uVar6;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (uVar7 <= uVar9) goto LAB_71018e8438;
        first[1] = uVar6;
      }
      first[2] = elem;
      temp = elem;
    }
    else if (uVar9 < uVar11) {
      first[1] = uVar6;
      first[2] = elem2;
      temp = elem2;
      if (uVar9 < uVar7) {
        *first = uVar6;
        first[1] = elem;
      }
    }
LAB_71018e8438:
    if (first + 3 == last) {
      return true;
    }
    // Insertion sort from element 3 onward; bail after 8 insertions
    insert_count = 0;
    cur = first + 3;
    do {
      elem = *cur;
      elem2 = elem & SORT_KEY_MASK;  // current element's sort key
      dst = cur;
      if (elem2 < (temp & SORT_KEY_MASK)) {
        // Shift elements right to make room
        do {
          shift = dst;
          *shift = temp;
          dst = first;
          if (shift - 1 == first) goto LAB_71018e8498;
          temp = shift[-2];
          dst = shift - 1;
        } while (elem2 < (temp & SORT_KEY_MASK));
        dst = shift - 1;
LAB_71018e8498:
        insert_count = insert_count + 1;
        *dst = elem;
        if (insert_count == 8) {
          return (u8)(cur + 1 == last);
        }
      }
      if (cur + 1 == last) {
        return true;
      }
      temp = *cur;
      cur = cur + 1;
    } while( true );
  }
  last[-1] = elem;
  return true;
}

// 0x7101991ba0
// Insertion sort (variant B) — same algorithm as FUN_71018e8290, different sort5 helper
u8 FUN_7101991ba0(u64 *first, u64 *last)
{
  u8 flag;
  u64 temp;
  u64 *dst;
  u64 *cur;
  s32 insert_count;
  u64 uVar6;
  u64 uVar7;
  u64 elem;
  u64 uVar9;
  u64 elem2;
  u64 uVar11;
  u64 *shift;

  switch(((s64)last - (s64)first) >> 3) {
  case 0:
  case 1:
    return true;
  case 2:
    elem = *first;
    if ((elem & SORT_KEY_MASK) <= (last[-1] & SORT_KEY_MASK)) {
      return true;
    }
    *first = last[-1];
    break;
  case 3:
    elem = *first;
    elem2 = first[1];
    temp = last[-1];
    uVar6 = elem2 & SORT_KEY_MASK;
    if ((elem & SORT_KEY_MASK) <= uVar6) {
      if (uVar6 <= (temp & SORT_KEY_MASK)) {
        return true;
      }
      first[1] = temp;
      last[-1] = elem2;
      elem = *first;
      if ((elem & SORT_KEY_MASK) <= (first[1] & SORT_KEY_MASK)) {
        return true;
      }
      *first = first[1];
      first[1] = elem;
      return true;
    }
    if ((temp & SORT_KEY_MASK) < uVar6) {
      *first = temp;
    }
    else {
      *first = elem2;
      first[1] = elem;
      if ((elem & SORT_KEY_MASK) <= (last[-1] & SORT_KEY_MASK)) {
        return true;
      }
      first[1] = last[-1];
    }
    break;
  case 4:
    elem = *first;
    elem2 = first[1];
    uVar9 = first[2];
    uVar7 = elem2 & SORT_KEY_MASK;
    uVar11 = elem & SORT_KEY_MASK;
    uVar6 = uVar9 & SORT_KEY_MASK;
    temp = uVar9;
    if (uVar7 < uVar11) {
      if (uVar6 < uVar7) {
        *first = uVar9;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (uVar11 <= uVar6) goto LAB_7101991e2c;
        first[1] = uVar9;
      }
      first[2] = elem;
      temp = elem;
      uVar6 = uVar11;
    }
    else if (uVar6 < uVar7) {
      flag = (u8)(uVar6 < uVar11);
      first[1] = uVar9;
      first[2] = elem2;
      temp = elem2;
      uVar6 = uVar7;
      if (flag) {
        *first = uVar9;
        first[1] = elem;
      }
    }
LAB_7101991e2c:
    if (uVar6 <= (last[-1] & SORT_KEY_MASK)) {
      return true;
    }
    first[2] = last[-1];
    last[-1] = temp;
    elem = first[1];
    elem2 = first[2];
    if ((elem & SORT_KEY_MASK) <= (elem2 & SORT_KEY_MASK)) {
      return true;
    }
    first[1] = elem2;
    first[2] = elem;
    elem = *first;
    if ((elem & SORT_KEY_MASK) <= (elem2 & SORT_KEY_MASK)) {
      return true;
    }
    *first = elem2;
    first[1] = elem;
    return true;
  case 5:
    FUN_71019919c0(first, first + 1, first + 2, first + 3, last - 1);
    return true;
  default:
    elem = *first;
    elem2 = first[1];
    uVar6 = first[2];
    uVar11 = elem2 & SORT_KEY_MASK;
    uVar7 = elem & SORT_KEY_MASK;
    uVar9 = uVar6 & SORT_KEY_MASK;
    temp = uVar6;
    if (uVar11 < uVar7) {
      if (uVar9 < uVar11) {
        *first = uVar6;
      }
      else {
        *first = elem2;
        first[1] = elem;
        if (uVar7 <= uVar9) goto LAB_7101991d48;
        first[1] = uVar6;
      }
      first[2] = elem;
      temp = elem;
    }
    else if (uVar9 < uVar11) {
      first[1] = uVar6;
      first[2] = elem2;
      temp = elem2;
      if (uVar9 < uVar7) {
        *first = uVar6;
        first[1] = elem;
      }
    }
LAB_7101991d48:
    if (first + 3 == last) {
      return true;
    }
    insert_count = 0;
    cur = first + 3;
    do {
      elem = *cur;
      elem2 = elem & SORT_KEY_MASK;
      dst = cur;
      if (elem2 < (temp & SORT_KEY_MASK)) {
        do {
          shift = dst;
          *shift = temp;
          dst = first;
          if (shift - 1 == first) goto LAB_7101991da8;
          temp = shift[-2];
          dst = shift - 1;
        } while (elem2 < (temp & SORT_KEY_MASK));
        dst = shift - 1;
LAB_7101991da8:
        insert_count = insert_count + 1;
        *dst = elem;
        if (insert_count == 8) {
          return (u8)(cur + 1 == last);
        }
      }
      if (cur + 1 == last) {
        return true;
      }
      temp = *cur;
      cur = cur + 1;
    } while( true );
  }
  last[-1] = elem;
  return true;
}

// 0x7101aeeac0
// Initializes a pair: sets vtable pointer and copies a u64 from source+8
void FUN_7101aeeac0(s64 src, u64 *out)
{
  *out = (u64)&PTR_LAB_71050a90b8;
  out[1] = *(u64 *)(src + 8);
  return;
}

// 0x7101addcc0
// Selects a representative image name by category index, or allocates empty data for default case
void FUN_7101addcc0(u64 *out, u32 category, u64 layout)
{
  u64 *alloc;
  u64 result;
  const char *name;
  u64 local_28;
  u32 local_14;

  switch(category) {
  case 0:
    name = "set_rep_img_af";
    break;
  case 1:
    name = "set_rep_img_pokemon";
    break;
  case 2:
    name = "set_rep_img_item";
    break;
  case 3:
    name = "set_rep_img_stage";
    break;
  default:
    *out = (u64)&PTR_DAT_710523c9a8;
    alloc = (u64 *)je_aligned_alloc(0x10, 0x20);
    if (alloc == nullptr) {
      if (DAT_7105331f00 != nullptr) {
        local_14 = 0;
        local_28 = 0x20;
        result = (*(u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))(DAT_7105331f00, &local_14, &local_28);
        if (((result & 1) != 0) &&
           (alloc = (u64 *)je_aligned_alloc(0x10, 0x20), alloc != nullptr))
        goto LAB_7101addd84;
      }
      alloc = nullptr;
    }
LAB_7101addd84:
    alloc[2] = 0;
    alloc[3] = 0;
    *alloc = 0;
    alloc[1] = 0;
    out[1] = (u64)alloc;
    return;
  case 5:
    name = "set_rep_img_fighter";
    break;
  case 6:
    name = "set_rep_img_fighter_00";
  }
  FUN_7103776360(out, layout, name);
  return;
}

// 0x7101adddd0
// Applies a UI category animation based on type index
void FUN_7101adddd0(u64 *self, s64 layout)
{
  u8 is_match;
  s32 lookup_result;
  u64 xref_result;
  u64 pane;
  const char *anim_name;
  u64 entry_hash;
  u64 entry_key;
  s64 data;
  u32 local_34;

  switch(*(u32 *)(self + 3)) {
  case 1:
    data = *(s64 *)(DAT_710532e730 + 8);
    entry_hash = self[4];
    xref_result = FUN_7103262bf0(*(u64 *)(data + 0x168), 0xfd5f7fa78ULL);
    entry_key = xref_result & 0xffffffffffULL;
    is_match = (u8)((xref_result & 0xff00000000000000ULL) == 0xc100000000000000ULL);
    if ((entry_hash & 0xffffffffffULL) == 0) {
      if (!is_match || entry_key == 0) goto LAB_7101addee4;
    }
    else if ((is_match && entry_key != 0) && entry_key == (entry_hash & 0xffffffffffULL)) {
LAB_7101addee4:
      pane = *(u64 *)(layout + 8);
      anim_name = "category02";
      goto LAB_7101addefc;
    }
    local_34 = 0;
    lookup_result = FUN_71032b82d0(*(u64 *)(data + 0x1b8), *self, &local_34);
    pane = *(u64 *)(layout + 8);
    if (lookup_result == 5) {
      anim_name = "category00";
    }
    else {
      anim_name = "category00_01";
    }
LAB_7101addefc:
    ui2d_apply_named_animation(0x3f800000, pane, anim_name);  // frame = 1.0f
    return;
  case 2:
    pane = *(u64 *)(layout + 8);
    anim_name = "category01";
    break;
  default:
    pane = *(u64 *)(layout + 8);
    anim_name = "category05";
    break;
  case 4:
    pane = *(u64 *)(layout + 8);
    anim_name = "category04";
    break;
  case 5:
    pane = *(u64 *)(layout + 8);
    anim_name = "category03";
  }
  ui2d_apply_named_animation(0x3f800000, pane, anim_name);  // frame = 1.0f
  return;
}

// 0x7101b00680
// Checks if a packed entry matches specific kind criteria (bitmask 0xcb = kinds 0,1,3,6,7)
u8 FUN_7101b00680(u64 *entry)
{
  u8 kind;

  kind = (u8)entry[1];
  if (kind < 8) {
    if ((1 << (u64)(kind & 0x1f) & 0xcbU) != 0) {
      return true;
    }
    if (kind == 4) {
      return (*entry & SORT_KEY_MASK) == 0xc100001b5affd87fULL;
    }
  }
  return false;
}

// 0x7101b43330
// Sets up Star Fox appeal conversation text (1–4 lines via layout pane at +0x1e8)
void FUN_7101b43330(s64 self, u32 line_count, s64 text_data)
{
  switch(line_count) {
  case 1:
    FUN_7103779b70(self + 0x1e8, text_data + 8);
    return;
  case 2:
    FUN_7103779cd0(self + 0x1e8, "scr_appeal_starfox_line2", 2, text_data + 8, text_data + 0x50);
    return;
  case 3:
    FUN_7103779cd0(self + 0x1e8, "scr_appeal_starfox_line3", 3, text_data + 8, text_data + 0x50,
                   text_data + 0x98);
    return;
  case 4:
    FUN_7103779cd0(self + 0x1e8, "scr_appeal_starfox_line4", 4, text_data + 8, text_data + 0x50,
                   text_data + 0x98, text_data + 0xe0);
    return;
  default:
    return;
  }
}

// 0x7101b433c0
// Star Fox appeal text variant (uses FUN_710377a1a0 instead)
void FUN_7101b433c0(s64 self, u32 line_count, s64 text_data)
{
  switch(line_count) {
  case 1:
    FUN_710377a1a0(self + 0x1e8, text_data + 8, 0);
    return;
  case 2:
    FUN_710377a1a0(self + 0x1e8, "scr_appeal_starfox_line2", 2, text_data + 8, text_data + 0x50);
    return;
  case 3:
    FUN_710377a1a0(self + 0x1e8, "scr_appeal_starfox_line3", 3, text_data + 8, text_data + 0x50,
                   text_data + 0x98);
    return;
  case 4:
    FUN_710377a1a0(self + 0x1e8, "scr_appeal_starfox_line4", 4, text_data + 8, text_data + 0x50,
                   text_data + 0x98, text_data + 0xe0);
    return;
  default:
    return;
  }
}

// 0x7101b4afe0
// Pokemon Stadium stage — plays pane animation by index
// Cases 0–12 map to direct pane offsets; 13–20 play "defeated" animation first
void FUN_7101b4afe0(s64 self, u32 pane_index)
{
  u64 defeated_id;

  switch(pane_index) {
  case 0:
    self = self + 0x1d8;
    break;
  case 1:
    self = self + 0x1e8;
    break;
  case 2:
    self = self + 0x1f8;
    break;
  case 3:
    self = self + 0x208;
    break;
  case 4:
    self = self + 0x218;
    break;
  case 5:
    self = self + 0x228;
    break;
  case 6:
    self = self + 0x278;
    break;
  case 7:
    self = self + 0x238;
    break;
  case 8:
    self = self + 0x288;
    break;
  case 9:
    self = self + 0x298;
    break;
  case 10:
    self = self + 0x258;
    break;
  default:
    return;
  case 0xc:
    self = self + 0x268;
    break;
  case 0xd:
    defeated_id = 1;
    goto play_defeated;
  case 0xe:
    defeated_id = 2;
    goto play_defeated;
  case 0xf:
    defeated_id = 3;
    goto play_defeated;
  case 0x10:
    defeated_id = 4;
    goto play_defeated;
  case 0x11:
    defeated_id = 5;
    goto play_defeated;
  case 0x12:
    defeated_id = 6;
    goto play_defeated;
  case 0x13:
    defeated_id = 7;
    goto play_defeated;
  case 0x14:
    defeated_id = 8;
play_defeated:
    FUN_7103779cd0(self + 0xa8, "mel_info_stage_poke_stadium_defeated", 1, defeated_id);
    self = self + 0x248;
  }
  FUN_710377a930(0x3f800000, self);  // frame = 1.0f
  return;
}

// 0x7101b4f170
// Table lookup by index; returns sentinel hash on out-of-bounds
u8 *FUN_7101b4f170(u32 index)
{
  if (index < 0xd) {
    return *(u8 **)(&DAT_7104ad95d0 + (s64)(s32)index * 8);
  }
  return (u8 *)0xc1ffff0000000000ULL;
}

// 0x7101b508e0
// Applies animation frames to 3 layout panes based on level/flag parameters
// u32 float encoding: 0=0.0f, 0x3f800000=1.0f, 0x40000000=2.0f, 0x40400000=3.0f
void FUN_7101b508e0(s64 layout, u32 level, u32 flag_a, u32 flag_b)
{
  u32 frame;

  switch(level) {
  case 0:
    frame = 0;                    // 0.0f
    break;
  case 1:
    frame = 0x3f800000;           // 1.0f
    break;
  case 2:
    frame = 0x40000000;           // 2.0f
    break;
  case 3:
    frame = 0x40400000;           // 3.0f
    break;
  default:
    goto switchD_7101b50918_caseD_4;
  }
  FUN_710377aa60(frame, layout + 0x70);
switchD_7101b50918_caseD_4:
  if ((flag_a & 1) == 0) {
    frame = 0;                    // 0.0f
  }
  else {
    frame = 0x3f800000;           // 1.0f
  }
  FUN_710377aa60(frame, layout + 0x80);
  frame = 0x40000000;             // 2.0f
  if ((flag_b & 1) == 0) {
    frame = 0x3f800000;           // 1.0f
  }
  FUN_710377a930(frame, layout + 0x60);
  return;
}

// 0x7101b95a70
// Plays animation on one of several panes; case 0 resets two panes first
void FUN_7101b95a70(s64 self, u32 pane_index)
{
  switch(pane_index) {
  case 0:
    FUN_710377ab90(self + 0x4e0);
    FUN_710377ab90(self + 0x520);
    return;
  case 1:
    self = self + 0x4c0;
    break;
  case 2:
    self = self + 0x4e0;
    break;
  case 3:
    self = self + 0x520;
    break;
  case 4:
    self = self + 0x500;
    break;
  default:
    return;
  }
  FUN_710377a930(0x3f800000, self);  // frame = 1.0f
  return;
}
