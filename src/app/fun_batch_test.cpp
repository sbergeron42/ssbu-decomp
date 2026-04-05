#include "types.h"

// Batch decompiled via Ghidra MCP

// Forward declarations for called functions
[[noreturn]] extern "C" void nn__detail__UnexpectedDefaultImpl(const char*, const char*, s32);
extern "C" void FUN_7101429330(s32*, s32*, s32*, s32*, s32*);

// Data symbol declarations (absolute addresses in the original binary)
extern u8 DAT_71044a7cd0;
extern u8 DAT_71044a7d50;
extern u8 PTR_LAB_7105065888 __attribute__((visibility("hidden")));

// 0x710022b510
u32 FUN_710022b510(s64 param_1)
{
  s64 stream;
  s64 offset;
  u32 value;

  stream = *(s64 *)(param_1 + 0x10);
  offset = *(s64 *)(param_1 + 0x18);
  if ((u64)(*(s64 *)(stream + 0x18) - offset) < 4) {
    *(u8 *)(param_1 + 8) = 1;
    return 0;
  }
  s64 base = *(s64 *)(stream + 0x10) + *(s64 *)(stream + 0x28);
#ifdef MATCHING_HACK_NX_CLANG
  asm("" : "+r"(base));
#endif
  value = *(u32 *)(base + offset);
  *(s64 *)(param_1 + 0x18) = offset + 4;
  return value;
}

// 0x710022e510
u32 FUN_710022e510(s64 param_1)
{
  s64 stream;
  s64 offset;
  u32 value;

  stream = *(s64 *)(param_1 + 0x10);
  offset = *(s64 *)(param_1 + 0x18);
  if ((u64)(*(s64 *)(stream + 0x18) - offset) < 4) {
    *(u8 *)(param_1 + 8) = 1;
    return 0;
  }
  s64 base = *(s64 *)(stream + 0x10) + *(s64 *)(stream + 0x28);
#ifdef MATCHING_HACK_NX_CLANG
  asm("" : "+r"(base));
#endif
  value = *(u32 *)(base + offset);
  *(s64 *)(param_1 + 0x18) = offset + 4;
  return value;
}

// 0x71004794b0
void FUN_71004794b0(s64 param_1, u32 param_2)
{
  (**(void(**)(s64*, u32, s64, u64))(*(s64*)(*(s64 *)(param_1 + 0x1c0)) + 0x48))
            (*(s64 **)(param_1 + 0x1c0), param_2, param_1 + 0x10, *(u64 *)(param_1 + 8));
  *(u32 *)(param_1 + 0x1b8) = param_2;
  return;
}

// 0x71004f5770
void FUN_71004f5770(u64 *param_1)
{
  *param_1 = 0xc1ffff0000000000ULL;
  param_1[3] = 0xc1ffff0000000000ULL;
  param_1[6] = 0xc1ffff0000000000ULL;
  param_1[9] = 0xc1ffff0000000000ULL;
  param_1[0xc] = 0xc1ffff0000000000ULL;
  param_1[0xf] = 0xc1ffff0000000000ULL;
  param_1[0x12] = 0xc1ffff0000000000ULL;
  param_1[0x15] = 0xc1ffff0000000000ULL;
  return;
}

// 0x7100b30f90
u64 FUN_7100b30f90(s32 param_1)
{
  switch(param_1) {
  case 0x60:
  case 0x62:
  case 99:
  case 100:
  case 0x66:
  case 0xab:
  case 0xac:
  case 0xad:
  case 0xae:
  case 0xaf:
  case 0xb0:
  case 0xb1:
  case 0xb2:
  case 0xb3:
  case 0xb4:
  case 0xb5:
  case 0xce:
  case 0xd5:
  case 0xd6:
  case 0xd8:
  case 0x100:
  case 0x133:
    goto switchD_7100b30fb4_caseD_60;
  case 0x61:
  case 0x65:
  case 0x67:
  case 0x68:
  case 0x69:
  case 0x6a:
  case 0x6b:
  case 0x6c:
  case 0x6d:
  case 0x6e:
  case 0x6f:
  case 0x70:
  case 0x71:
  case 0x72:
  case 0x73:
  case 0x74:
  case 0x75:
  case 0x76:
  case 0x77:
  case 0x78:
  case 0x79:
  case 0x7a:
  case 0x7b:
  case 0x7c:
  case 0x7d:
  case 0x7e:
  case 0x7f:
  case 0x80:
  case 0x81:
  case 0x82:
  case 0x83:
  case 0x84:
  case 0x85:
  case 0x86:
  case 0x87:
  case 0x88:
  case 0x89:
  case 0x8a:
  case 0x8b:
  case 0x8c:
  case 0x8d:
  case 0x8e:
  case 0x8f:
  case 0x90:
  case 0x91:
  case 0x92:
  case 0x93:
  case 0x94:
  case 0x95:
  case 0x96:
  case 0x97:
  case 0x98:
  case 0x99:
  case 0x9a:
  case 0x9b:
  case 0x9c:
  case 0x9d:
  case 0x9e:
  case 0x9f:
  case 0xa0:
  case 0xa1:
  case 0xa2:
  case 0xa3:
  case 0xa4:
  case 0xa5:
  case 0xa6:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xaa:
  case 0xb6:
  case 0xb7:
  case 0xb8:
  case 0xb9:
  case 0xba:
  case 0xbb:
  case 0xbc:
  case 0xbd:
  case 0xbe:
  case 0xbf:
  case 0xc0:
  case 0xc1:
  case 0xc2:
  case 0xc3:
  case 0xc4:
  case 0xc5:
  case 0xc6:
  case 199:
  case 200:
  case 0xc9:
  case 0xca:
  case 0xcb:
  case 0xcc:
  case 0xcd:
  case 0xcf:
  case 0xd0:
  case 0xd1:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd7:
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xdc:
  case 0xdd:
  case 0xde:
  case 0xdf:
  case 0xe0:
  case 0xe1:
  case 0xe2:
  case 0xe3:
  case 0xe4:
  case 0xe5:
  case 0xe6:
  case 0xe7:
  case 0xe8:
  case 0xe9:
  case 0xea:
  case 0xeb:
  case 0xec:
  case 0xed:
  case 0xee:
  case 0xef:
  case 0xf0:
  case 0xf1:
  case 0xf2:
  case 0xf3:
  case 0xf4:
  case 0xf5:
  case 0xf6:
  case 0xf7:
  case 0xf8:
  case 0xf9:
  case 0xfa:
  case 0xfb:
  case 0xfc:
  case 0xfd:
  case 0xfe:
  case 0xff:
  case 0x101:
  case 0x102:
  case 0x103:
  case 0x104:
  case 0x105:
  case 0x106:
  case 0x107:
  case 0x108:
  case 0x109:
  case 0x10a:
  case 0x10b:
  case 0x10c:
  case 0x10d:
  case 0x10e:
  case 0x10f:
  case 0x110:
  case 0x111:
  case 0x112:
  case 0x113:
  case 0x114:
  case 0x115:
  case 0x116:
  case 0x117:
  case 0x118:
  case 0x119:
  case 0x11a:
  case 0x11b:
  case 0x11c:
  case 0x11d:
  case 0x11e:
  case 0x11f:
  case 0x120:
  case 0x121:
  case 0x122:
  case 0x123:
  case 0x124:
  case 0x125:
  case 0x126:
  case 0x127:
  case 0x128:
  case 0x129:
  case 0x12a:
  case 299:
  case 300:
  case 0x12d:
  case 0x12e:
  case 0x12f:
  case 0x130:
  case 0x131:
  case 0x132:
    return 0;
  default:
    if (2 < (u32)(param_1 - 0x1a3)) {
      return 0;
    }
switchD_7100b30fb4_caseD_60:
    return 1;
  }
}

// 0x710138b0d0
u8 FUN_710138b0d0(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x120) != '\0';
  }
  return false;
}

// 0x710138b6c0
u8 FUN_710138b6c0(s64 param_1)
{
  s64 inner;
  s64 base_offset;

  if (*(s64 **)(param_1 + 8) != nullptr) {
    inner = **(s64 **)(param_1 + 8);
    base_offset = inner + 0x3d0;
    if (*(char *)(inner + 0xd3a) != '\0') {
      base_offset = inner + 0xa00;
    }
    return *(char *)(base_offset + 0x10) != '\0';
  }
  return false;
}

// 0x710138c3b0
u8 FUN_710138c3b0(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x2d8) != '\0';
  }
  return false;
}

// 0x710138c400
u8 FUN_710138c400(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x228) != '\0';
  }
  return false;
}

// 0x710138c4c0
u8 FUN_710138c4c0(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x4e8) != '\0';
  }
  return false;
}

// 0x710138c510
u8 FUN_710138c510(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x1d0) != '\0';
  }
  return false;
}

// 0x710139e5b0
void FUN_710139e5b0(s64 param_1, u64 param_2)
{
  u8 *entry;

  if ((*(char *)(param_1 + 0x10) != '\0') && ((param_2 & 0xff0000ffffffffff) != 0xd900001e3d9517e5))
  {
    entry = *(u8 **)(0x17c0 + *(s64 *)(param_1 + 0x50));
    *(u64 *)(entry + 8) = param_2;
    *entry = 1;
  }
  return;
}

// 0x710141a920
void FUN_710141a920(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065888;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101429540
u64 FUN_7101429540(s32 *param_1, s32 *param_2)
{
  s32 val_a;
  s64 scan_offset;
  u64 result;
  s64 prev_offset;
  s32 val_b;
  s32 *next;
  s32 val_c;
  s64 write_offset;
  s32 *scan;
  s32 move_count;

  switch(((s64)param_2 - (s64)param_1) >> 2) {
  case 0:
  case 1:
    break;
  case 2:
    if ((*param_1 == 7) && (param_2[-1] != 7)) {
      *param_1 = param_2[-1];
LAB_7101429604:
      param_2[-1] = 7;
      return 1;
    }
    break;
  case 3:
    val_b = param_1[1];
    val_a = param_2[-1];
    if ((*param_1 == 7) && (val_b != 7)) {
      if (val_b != 7 || val_a == val_b) {
        *param_1 = val_b;
        param_1[1] = 7;
        if (param_2[-1] != 7) {
          param_1[1] = param_2[-1];
          param_2[-1] = 7;
          return 1;
        }
        return 1;
      }
      *param_1 = val_a;
      goto LAB_7101429604;
    }
    if (val_b != 7 || val_a == val_b) {
      return 1;
    }
    param_1[1] = val_a;
    param_2[-1] = 7;
    if (*param_1 != 7) {
      return 1;
    }
    val_b = param_1[1];
    if (val_b == 7) {
      return 1;
    }
    goto LAB_7101429880;
  case 4:
    val_b = param_1[1];
    val_a = param_1[2];
    if ((*param_1 == 7) && (val_b != 7)) {
      if (val_b != 7 || val_a == val_b) {
        *param_1 = val_b;
        param_1[1] = 7;
        val_c = 7;
        if (val_a == 7) goto LAB_7101429820;
        param_1[1] = val_a;
      }
      else {
        *param_1 = val_a;
      }
      param_1[2] = 7;
      val_c = 7;
    }
    else {
      val_c = val_a;
      if (val_b == 7 && val_a != val_b) {
        param_1[1] = val_a;
        param_1[2] = 7;
        val_c = 7;
        if ((*param_1 == 7) && (val_a != 7)) {
          *param_1 = val_a;
          param_1[1] = 7;
          val_c = 7;
        }
      }
    }
LAB_7101429820:
    if ((val_c == 7) && (param_2[-1] != 7)) {
      param_1[2] = param_2[-1];
      param_2[-1] = 7;
      if ((param_1[1] == 7) && (val_b = param_1[2], val_b != 7)) {
        param_1[1] = val_b;
        param_1[2] = 7;
        if ((*param_1 == 7) && (val_b != 7)) {
LAB_7101429880:
          *param_1 = val_b;
          param_1[1] = 7;
          return 1;
        }
      }
    }
    break;
  case 5:
    FUN_7101429330(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 + -1);
    return 1;
  default:
    val_b = param_1[1];
    val_a = param_1[2];
    if ((*param_1 == 7) && (val_b != 7)) {
      if (val_b != 7 || val_a == val_b) {
        *param_1 = val_b;
        param_1[1] = 7;
        val_c = 7;
        if (val_a == 7) goto LAB_7101429744;
        param_1[1] = val_a;
      }
      else {
        *param_1 = val_a;
      }
      param_1[2] = 7;
      val_c = 7;
    }
    else {
      val_c = val_a;
      if (val_b == 7 && val_a != val_b) {
        param_1[1] = val_a;
        param_1[2] = 7;
        val_c = 7;
        if ((*param_1 == 7) && (val_a != 7)) {
          *param_1 = val_a;
          param_1[1] = 7;
          val_c = 7;
        }
      }
    }
LAB_7101429744:
    next = param_1 + 3;
    if (next == param_2) {
      return 1;
    }
    scan_offset = 0;
    val_b = 0;
    if (val_c == 7) goto LAB_710142977c;
    do {
      do {
        do {
          scan = next + 1;
          if (scan == param_2) {
            return 1;
          }
          val_c = *next;
          scan_offset = scan_offset + 4;
          next = scan;
        } while (val_c != 7);
LAB_710142977c:
        val_a = *next;
        prev_offset = scan_offset;
      } while (val_a == val_c);
      do {
        write_offset = prev_offset;
        *(u32 *)((s64)param_1 + write_offset + 0xc) = 7;
        scan = param_1;
        if (write_offset == -8) goto LAB_71014297c0;
        val_c = *(s32 *)((s64)param_1 + write_offset + 4);
        prev_offset = write_offset + -4;
      } while (val_c == 7 && val_a != val_c);
      scan = (s32 *)((s64)param_1 + write_offset + 8);
LAB_71014297c0:
      val_b = val_b + 1;
      *scan = val_a;
      if (val_b == 8) {
        return (u64)(next + 1 == param_2);
      }
    } while( true );
  }
  return 1;
}
