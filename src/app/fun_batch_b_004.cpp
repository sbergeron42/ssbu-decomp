#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 004
// Range: 0x7101000000 -- 0x7101FFFFFF

// Forward declarations
extern "C" void FUN_7103779b70(s64, ...);
extern "C" void FUN_7103779cd0(s64, const char *, ...);
extern "C" void FUN_71037a1cc0(s64, u32 *, s32, s32);
extern "C" void FUN_710326f0f0(s64 *, s32, s32, s32, s32, s32, s32);
extern "C" void jeFree_710392e590(...);
extern "C" void FUN_7101c08b50(u8 *, u8 *, u8 *, u8 *, u8 *);

// 0x7101bbbf80 -- training CPU behavior mel string dispatch
void FUN_7101bbbf80(s64 param_1, u32 param_2, u64 param_3)
{
  switch(param_2) {
  case 2:
    FUN_7103779cd0(param_3, "mel_training_cp_lv_n", 1, *(s32 *)(param_1 + 0xb50) + 1);
    return;
  case 3:
    FUN_7103779b70(param_3, "mel_training_cp_walk");
    return;
  case 4:
    FUN_7103779b70(param_3, "mel_training_cp_escape");
    return;
  case 5:
    FUN_7103779b70(param_3, "mel_training_cp_jump");
    return;
  case 6:
    FUN_7103779b70(param_3, "mel_training_cp_attack");
    return;
  case 7:
    FUN_7103779b70(param_3, "mel_training_cp_smash_side");
    return;
  case 8:
    FUN_7103779b70(param_3, "mel_training_cp_operation");
    return;
  default:
    FUN_7103779b70(param_3, "mel_training_cp_stop");
    return;
  }
}

// 0x7101bcbe40 -- mock battle state mel string dispatch
void FUN_7101bcbe40(s64 param_1, s32 param_2)
{
  s64 anim_list;
  u32 zero;

  if ((u32)(param_2 - 1) < 0xb) {
    param_1 = param_1 + 0x2e0;
    switch(param_2) {
    case 1:
      FUN_7103779b70(param_1, "mel_mockbattle_entry");
      return;
    case 2:
      FUN_7103779b70(param_1, "mel_mockbattle_hope_join");
      return;
    case 3:
      FUN_7103779b70(param_1, "mel_mockbattle_preparation");
      return;
    case 4:
      FUN_7103779b70(param_1, "mel_mockbattle_setting_rule");
      return;
    case 5:
      FUN_7103779b70(param_1, "mel_mockbattle_sel_stage");
      return;
    default:
      FUN_7103779b70(param_1, "mel_mockbattle_sel_fighter");
      return;
    case 8:
      FUN_7103779b70(param_1, "mel_mockbattle_check_rule");
      return;
    case 9:
      FUN_7103779b70(param_1, "mel_mockbattle_result");
      return;
    case 10:
      FUN_7103779b70(param_1, "mel_mockbattle_bye");
      return;
    case 0xb:
      FUN_7103779b70(param_1, "mel_mockbattle_battle");
      return;
    }
  }
  anim_list = *(s64 *)(*(s64 *)(param_1 + 0x2e8) + 0x10);
  if (anim_list != 0) {
    zero = 0;
    FUN_71037a1cc0(anim_list, &zero, 0, 0);
  }
  return;
}

// 0x7101c043c0 -- setting value getter by option index
u32 FUN_7101c043c0(s64 param_1, s64 param_2, u8 param_3)
{
  u16 frame_count;
  u64 list_size;
  u32 minutes;
  s32 count;
  s64 list_begin;
  s64 list_end;

  switch(param_3) {
  case 2:
    return (u32)*(u8 *)(param_1 + 1);
  case 3:
    return (u32)*(u8 *)(param_1 + 2);
  case 4:
    break;
  case 5:
    return *(u8 *)(param_1 + 6) - 1;
  case 6:
    return (u32)*(u8 *)(param_1 + 7);
  case 7:
    return (u32)*(u8 *)(param_1 + 8);
  case 8:
    return (u32)*(u8 *)(param_1 + 9);
  case 9:
    return (u32)*(u8 *)(param_1 + 10);
  case 10:
    return (u32)*(u8 *)(param_1 + 0xb);
  case 0xb:
    return (u32)*(u8 *)(param_1 + 0xc);
  default:
    return 0;
  case 0xe:
    return (u32)*(u8 *)(param_1 + 0xd);
  case 0xf:
    return *(u8 *)(param_1 + 0xe) - 5;
  case 0x10:
    return (u32)*(u8 *)(param_1 + 0xf);
  case 0x11:
    return (u32)*(u8 *)(param_1 + 0x10);
  case 0x12:
    return (u32)*(u8 *)(param_1 + 0x11);
  case 0x13:
    return *(u8 *)(param_1 + 0x12) - 1;
  case 0x14:
    return (u32)*(u8 *)(param_1 + 0x13);
  case 0x15:
    return (u32)*(u8 *)(param_1 + 0x14);
  case 0x16:
    return (u32)*(u8 *)(param_1 + 0x15);
  case 0x17:
    return (u32)*(u8 *)(param_1 + 0x16);
  case 0x18:
    return (u32)*(u8 *)(param_1 + 0x17);
  case 0x1b:
    if (*(s32 *)(param_2 + 4) == 0) {
      FUN_710326f0f0(&list_begin, 0, 1, 1, 0, 0, 1);
      list_size = list_end - list_begin;
      if (list_begin != 0) {
        list_end = list_begin;
        jeFree_710392e590();
      }
      count = (s32)(list_size >> 3);
      if (count < 0) {
        count = count + 1;
      }
      count = count >> 1;
      if (count < 2) {
        count = 1;
      }
      return count - 1;
    }
    return *(s32 *)(param_2 + 4) - 1;
  case 0x1c:
    return (u32)*(u8 *)(param_2 + 8);
  case 0x1d:
    return (u32)*(u8 *)(param_2 + 1);
  case 0x1e:
    return (u32)*(u8 *)(param_2 + 2);
  }
  frame_count = *(u16 *)(param_1 + 4);
  if (0x5cc < (u32)((frame_count - 1 >> 2) & 0x3fff)) {
    return 0x65;
  }
  if (0x3b < frame_count) {
    minutes = frame_count / 0x3c;
    if ((u32)frame_count != (minutes * 0x3c & 0xfffc)) {
      minutes = frame_count / 0x3c + 1;
    }
    if (2 < minutes) {
      minutes = 3;
    }
    return (frame_count / 0x3c + minutes) - 2;
  }
  return 0;
}

// 0x7101c045a0 -- max value per setting option index
s32 FUN_7101c045a0(u8 param_1)
{
  u64 list_size;
  s32 count;
  s64 list_begin;
  s64 list_end;

  count = 4;
  switch(param_1) {
  case 0:
    goto switchD_7101c045c8_caseD_0;
  case 1:
  case 2:
  case 3:
    return 3;
  case 4:
    return 0x66;
  case 5:
    return 99;
  case 6:
    return 0xc;
  case 7:
    return 5;
  case 8:
    return 2;
  case 9:
    return 10;
  case 10:
    return 3;
  case 0xb:
    return 8;
  default:
    count = 0;
switchD_7101c045c8_caseD_0:
    return count;
  case 0xe:
    return 2;
  case 0xf:
    return 0x10;
  case 0x10:
  case 0x11:
  case 0x12:
    return 2;
  case 0x13:
    return 3;
  case 0x14:
  case 0x15:
    return 0xb;
  case 0x16:
  case 0x17:
  case 0x18:
    return 2;
  case 0x1b:
    FUN_710326f0f0(&list_begin, 0, 1, 1, 0, 0, 1);
    list_size = list_end - list_begin;
    if (list_begin != 0) {
      list_end = list_begin;
      jeFree_710392e590();
    }
    count = (s32)(list_size >> 3);
    if (count < 0) {
      count = count + 1;
    }
    count = count >> 1;
    if (count < 2) {
      count = 1;
    }
    return count;
  case 0x1c:
  case 0x1d:
  case 0x1e:
    return 2;
  }
}

// 0x7101c08ce0 -- partial insertion sort (small-array optimization)
u8 FUN_7101c08ce0(u8 *first, u8 *last)
{
  u8 a;
  u8 b;
  s64 cursor;
  u8 pivot;
  u8 *dst;
  u8 c;
  u8 *iter;
  s64 idx;
  s32 swap_count;
  s64 pos;

  switch((s64)last - (s64)first) {
  case 0:
  case 1:
    return true;
  case 2:
    c = *first;
    if (c <= last[-1]) {
      return true;
    }
    *first = last[-1];
LAB_7101c08f14:
    last[-1] = c;
    return true;
  case 3:
    a = first[1];
    c = *first;
    b = last[-1];
    if (a < c) {
      if (b < a) {
        *first = b;
      }
      else {
        *first = a;
        first[1] = c;
        if (c <= last[-1]) {
          return true;
        }
        first[1] = last[-1];
      }
      goto LAB_7101c08f14;
    }
    if (a <= b) {
      return true;
    }
    first[1] = b;
    last[-1] = a;
    a = first[1];
    c = *first;
    if (c <= a) {
      return true;
    }
    goto LAB_7101c08f80;
  case 4:
    break;
  case 5:
    FUN_7101c08b50(first, first + 1, first + 2, first + 3, last + -1);
    return true;
  default:
    a = first[1];
    c = *first;
    b = first[2];
    pivot = b;
    if (a < c) {
      if (b < a) {
        *first = b;
      }
      else {
        *first = a;
        first[1] = c;
        if (c <= b) goto LAB_7101c08e64;
        first[1] = b;
      }
      first[2] = c;
      pivot = c;
    }
    else if (b < a) {
      first[1] = b;
      first[2] = a;
      pivot = a;
      if (b < c) {
        *first = b;
        first[1] = c;
      }
    }
LAB_7101c08e64:
    if (first + 3 == last) {
      return true;
    }
    idx = 0;
    swap_count = 0;
    iter = first + 3;
    do {
      a = *iter;
      cursor = idx;
      if (a < pivot) {
        do {
          pos = cursor;
          first[pos + 3] = pivot;
          dst = first;
          if (pos == -2) goto LAB_7101c08ec8;
          pivot = first[pos + 1];
          cursor = pos + -1;
        } while (a < pivot);
        dst = first + pos + 2;
LAB_7101c08ec8:
        swap_count = swap_count + 1;
        *dst = a;
        if (swap_count == 8) {
          return (u8)(iter + 1 == last);
        }
      }
      if (iter + 1 == last) {
        return true;
      }
      pivot = *iter;
      idx = idx + 1;
      iter = iter + 1;
    } while( true );
  }
  a = first[1];
  c = *first;
  b = first[2];
  pivot = b;
  if (a < c) {
    if (b < a) {
      *first = b;
    }
    else {
      *first = a;
      first[1] = c;
      if (c <= b) goto LAB_7101c08f48;
      first[1] = b;
    }
    first[2] = c;
    pivot = c;
  }
  else if (b < a) {
    first[1] = b;
    first[2] = a;
    pivot = a;
    if (b < c) {
      *first = b;
      first[1] = c;
    }
  }
LAB_7101c08f48:
  if (pivot <= last[-1]) {
    return true;
  }
  first[2] = last[-1];
  last[-1] = pivot;
  a = first[2];
  if (first[1] <= a) {
    return true;
  }
  first[2] = first[1];
  c = *first;
  first[1] = a;
  if (c <= a) {
    return true;
  }
LAB_7101c08f80:
  *first = a;
  first[1] = c;
  return true;
}
