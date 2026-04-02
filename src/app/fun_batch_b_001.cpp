#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 001
// Range: 0x7101000000 — 0x7101FFFFFF

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
extern u8 PTR_LAB_7105065358;

// Misc data
extern u64 DAT_710532e730;
extern u8 DAT_00001790;

// 0x7101005850
void FUN_7101005850(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c18b8 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c18b8);
    if (iVar1 != 0) {
      DAT_71052c18c0 = &PTR_LAB_71050238b8;
      __cxa_guard_release((s64 *)&DAT_71052c18b8);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c18c0;
  *(u8 *)(param_2 + 0xe8) = 7;
  return;
}

// 0x71010439b0
void FUN_71010439b0(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c18d0 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c18d0);
    if (iVar1 != 0) {
      DAT_71052c18c8 = &PTR_LAB_7105027340;
      __cxa_guard_release((s64 *)&DAT_71052c18d0);
    }
  }
  *(void ***)(param_2 + 0x180) = &DAT_71052c18c8;
  return;
}

// 0x710105bc60
void FUN_710105bc60(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c1900 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c1900);
    if (iVar1 != 0) {
      DAT_71052c1908 = &PTR_LAB_7105029988;
      __cxa_guard_release((s64 *)&DAT_71052c1900);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c1908;
  *(u8 *)(param_2 + 0xe8) = 7;
  return;
}

// 0x71010d44f0
void FUN_71010d44f0(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c1958 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c1958);
    if (iVar1 != 0) {
      DAT_71052c1960 = &PTR_LAB_7105033200;
      __cxa_guard_release((s64 *)&DAT_71052c1958);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c1960;
  *(u8 *)(param_2 + 0xe8) = 6;
  return;
}

// 0x71011208a0
void FUN_71011208a0(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c1980 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c1980);
    if (iVar1 != 0) {
      DAT_71052c1988 = &PTR_LAB_7105039af0;
      __cxa_guard_release((s64 *)&DAT_71052c1980);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c1988;
  return;
}

// 0x71011d5680
void FUN_71011d5680(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c1a38 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c1a38);
    if (iVar1 != 0) {
      DAT_71052c1a40 = &PTR_LAB_7105045e18;
      __cxa_guard_release((s64 *)&DAT_71052c1a38);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c1a40;
  return;
}

// 0x710130e1f0
void FUN_710130e1f0(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c1bc0 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c1bc0);
    if (iVar1 != 0) {
      DAT_71052c1bc8 = &PTR_LAB_710505ce38;
      __cxa_guard_release((s64 *)&DAT_71052c1bc0);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c1bc8;
  return;
}

// 0x7101315010
u64 FUN_7101315010(s64 param_1, u32 param_2, u64 *param_3)
{
  u64 uVar1;
  u64 uVar2;
  u64 *puVar3;
  u64 uVar4;
  u64 uVar5;

  switch(param_2) {
  case 0x23:
    uVar4 = 0x6f9741949;
    goto LAB_71013150ac;
  case 0x24:
    uVar4 = 0x53e1c61;
    break;
  case 0x25:
    uVar4 = 0xe0a45c026;
    goto LAB_71013150ac;
  case 0x26:
    uVar4 = 0xf33c2ac;
    break;
  case 0x27:
    uVar4 = 0x6a96d306;
    goto LAB_71013150a4;
  case 0x28:
    uVar4 = 0xc50ca65a;
  LAB_71013150a4:
    uVar4 = uVar4 | 0x800000000ULL;
    goto LAB_71013150ac;
  default:
    return 0;
  }
  uVar4 = uVar4 | 0x500000000ULL;
LAB_71013150ac:
  puVar3 = (u64 *)FUN_7101315480(param_1 + 0x30, uVar4);
  *param_3 = *puVar3;
  uVar5 = puVar3[3];
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  *(u32 *)(param_3 + 4) = *(u32 *)(puVar3 + 4);
  param_3[1] = uVar1;
  param_3[2] = uVar2;
  param_3[3] = uVar5;
  return 1;
}

// 0x7101382240
u64 FUN_7101382240(s64 param_1, s32 param_2)
{
  s32 iVar1;
  s64 lVar2;

  if (((*(char *)(param_1 + 0x1e) == '\x01') &&
      (lVar2 = (s64)*(s32 *)(param_1 + 0x24), *(s32 *)(param_1 + 0x24) != -1)) &&
     (*(char *)(param_1 + lVar2 * 0x3860 + 0x62) == '\0')) {
    if (*(u8 *)(param_1 + 3) - 1 < 2) {
      iVar1 = (s32)*(char *)(param_1 + lVar2 * 0x3860 + 0x7c);
      if (((((*(char *)(param_1 + 0x62) != '\x01') || (param_2 <= iVar1 - *(char *)(param_1 + 0x7c))
            ) && ((*(char *)(param_1 + 0x38c2) != '\x01' ||
                  (param_2 <= iVar1 - *(char *)(param_1 + 0x38dc))))) &&
          (((*(char *)(param_1 + 0x7122) != '\x01' ||
            (param_2 <= iVar1 - *(char *)(param_1 + 0x713c))) &&
           ((*(char *)(param_1 + 0xa982) != '\x01' ||
            (param_2 <= iVar1 - *(char *)(param_1 + 0xa99c))))))) &&
         (((((*(char *)(param_1 + 0xe1e2) != '\x01' ||
             (param_2 <= iVar1 - *(char *)(param_1 + 0xe1fc))) &&
            ((*(char *)(param_1 + 0x11a42) != '\x01' ||
             (param_2 <= iVar1 - *(char *)(param_1 + 0x11a5c))))) &&
           ((*(char *)(param_1 + 0x152a2) != '\x01' ||
            (param_2 <= iVar1 - *(char *)(param_1 + 0x152bc))))) &&
          ((*(char *)(param_1 + 0x18b02) != '\x01' ||
           (param_2 <= iVar1 - *(char *)(param_1 + 0x18b1c))))))) {
        return 1;
      }
    }
    else {
      if (*(u8 *)(param_1 + 3) != 0) {
        return 1;
      }
      iVar1 = *(s32 *)(param_1 + lVar2 * 0x3860 + 0x3864);
      if ((((((*(char *)(param_1 + 0x62) != '\x01') ||
             (param_2 <= iVar1 - *(s32 *)(param_1 + 0x3864))) &&
            ((*(char *)(param_1 + 0x38c2) != '\x01' ||
             (param_2 <= iVar1 - *(s32 *)(param_1 + 0x70c4))))) &&
           ((*(char *)(param_1 + 0x7122) != '\x01' ||
            (param_2 <= iVar1 - *(s32 *)(param_1 + 0xa924))))) &&
          (((*(char *)(param_1 + 0xa982) != '\x01' ||
            (param_2 <= iVar1 - *(s32 *)(param_1 + 0xe184))) &&
           ((((*(char *)(param_1 + 0xe1e2) != '\x01' ||
              (param_2 <= iVar1 - *(s32 *)(param_1 + 0x119e4))) &&
             ((*(char *)(param_1 + 0x11a42) != '\x01' ||
              (param_2 <= iVar1 - *(s32 *)(param_1 + 0x15244))))) &&
            ((*(char *)(param_1 + 0x152a2) != '\x01' ||
             (param_2 <= iVar1 - *(s32 *)(param_1 + 0x18aa4))))))))) &&
         ((*(char *)(param_1 + 0x18b02) != '\x01' ||
          (param_2 <= iVar1 - *(s32 *)(param_1 + 0x1c304))))) {
        return 1;
      }
    }
  }
  return 0;
}

// 0x7101388b90
u64 FUN_7101388b90(u8 param_1)
{
  u64 uVar1;

  uVar1 = 0;
  switch(param_1) {
  case 0:
  case 2:
  case 3:
  case 0x22:
    return 2;
  case 0x1d:
  case 0x29:
  case 0x3e:
  case 0x45:
    uVar1 = 5;
  }
  return uVar1;
}

// 0x710138ac00
u8 FUN_710138ac00(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 200) != '\0';
  }
  return false;
}

// 0x710138b020
u8 FUN_710138b020(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x6a0) != '\0';
  }
  return false;
}

// 0x710138b120
u8 FUN_710138b120(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x178) != '\0';
  }
  return false;
}

// 0x710138b1c0
u8 FUN_710138b1c0(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) == nullptr) {
    return false;
  }
  if (*(char *)(**(s64 **)(param_1 + 8) + 0x70) != '\0') {
    return *(s32 *)(param_1 + 0x14) != -1;
  }
  return false;
}

// 0x710138c450
u8 FUN_710138c450(s64 param_1)
{
  if (*(s64 **)(param_1 + 8) != nullptr) {
    return *(char *)(**(s64 **)(param_1 + 8) + 0x648) != '\0';
  }
  return false;
}

// 0x710138c9b0
u64 FUN_710138c9b0(u32 param_1)
{
  u64 uVar1;
  u64 uVar2;
  u64 uVar3;
  s64 lVar4;

  switch(param_1) {
  case 0x4b:
  case 0x4c:
    param_1 = 0x6e;
    break;
  case 0x6f:
    param_1 = 0x24;
    break;
  case 0x70:
    param_1 = 0x25;
    break;
  case 0x71:
    param_1 = 0x26;
    break;
  case 0x73:
    param_1 = 0x5a;
    break;
  case 0x74:
    param_1 = 0x5b;
  }
  uVar1 = FUN_7103263870(*(s64 *)(DAT_710532e730 + 8) + 0x160, param_1);
  if ((uVar1 & 0xff00000000000000ULL) != 0xc100000000000000ULL || (uVar1 & 0xffffffffffULL) == 0) {
    return uVar1;
  }
  lVar4 = *(s64 *)(DAT_710532e730 + 8);
  uVar2 = FUN_71032643e0(lVar4 + 0x160, uVar1);
  if ((uVar2 & 1) == 0) {
    uVar2 = FUN_7103264500(lVar4 + 0x160, uVar1);
    if ((uVar2 & 1) == 0) {
      return uVar1;
    }
    uVar3 = *(u64 *)(lVar4 + 0x168);
    uVar1 = 0xb3e567a6;
  }
  else {
    uVar3 = *(u64 *)(lVar4 + 0x168);
    uVar1 = 0xb28d453e;
  }
  uVar1 = FUN_7103262bf0(uVar3, uVar1 | 0x1300000000ULL);
  return uVar1;
}

// 0x710139eae0
u8 *FUN_710139eae0(s64 param_1, u32 param_2)
{
  if (*(char *)(param_1 + 0x10) == '\0' || param_2 == 0xffffffff) {
    return (u8 *)0xc1ffff0000000000ULL;
  }
  if (param_2 < 8) {
    return *(u8 **)(*(s64 *)(&DAT_00001790 + *(s64 *)(param_1 + 0x50)) +
             ((s64)((u64)param_2 << 0x20) >> 0x17) + 0x170);
  }
  /* WARNING: Subroutine does not return */
  abort();
}

// 0x71013fc1e0
s64 *FUN_71013fc1e0(s64 param_1, s32 param_2)
{
  u64 uVar1;
  s64 lVar2;
  u64 uVar3;
  u64 uVar4;
  u64 uVar5;
  s64 *plVar6;
  u64 uVar7;

  switch(param_2) {
  case 0x4b:
  case 0x4c:
    param_2 = 0x6e;
    break;
  case 0x6f:
    param_2 = 0x24;
    break;
  case 0x70:
    param_2 = 0x25;
    break;
  case 0x71:
    param_2 = 0x26;
    break;
  case 0x73:
    param_2 = 0x5a;
    break;
  case 0x74:
    param_2 = 0x5b;
  }
  lVar2 = *(s64 *)(param_1 + 0x58);
  uVar5 = *(u64 *)(lVar2 + 0x98);
  if (uVar5 != 0) {
    uVar7 = uVar5 - 1;
    uVar3 = (u64)param_2;
    if ((uVar7 & uVar5) == 0) {
      uVar4 = uVar7 & uVar3;
    }
    else {
      uVar4 = uVar3;
      if (uVar5 <= uVar3) {
        uVar4 = 0;
        if (uVar5 != 0) {
          uVar4 = uVar3 / uVar5;
        }
        uVar4 = uVar3 - uVar4 * uVar5;
      }
    }
    plVar6 = *(s64 **)(*(s64 *)(lVar2 + 0x90) + uVar4 * 8);
    if ((plVar6 != nullptr) && (plVar6 = (s64 *)*plVar6, plVar6 != nullptr)) {
      if ((uVar7 & uVar5) == 0) {
        do {
          uVar5 = plVar6[1];
          if (uVar5 != uVar3 && (uVar5 & uVar7) != uVar4) break;
          if ((uVar5 == uVar3) && ((s32)plVar6[2] == param_2)) goto LAB_71013fc2f4;
          plVar6 = (s64 *)*plVar6;
        } while (plVar6 != nullptr);
      }
      else {
        do {
          uVar7 = plVar6[1];
          if (uVar7 == uVar3) {
            if ((s32)plVar6[2] == param_2) {
LAB_71013fc2f4:
              return plVar6 + 4;
            }
          }
          else {
            if (uVar5 <= uVar7) {
              uVar1 = 0;
              if (uVar5 != 0) {
                uVar1 = uVar7 / uVar5;
              }
              uVar7 = uVar7 - uVar1 * uVar5;
            }
            if (uVar7 != uVar4) break;
          }
          plVar6 = (s64 *)*plVar6;
        } while (plVar6 != nullptr);
      }
    }
  }
  return (s64 *)(lVar2 + 0x10);
}

// 0x710140f7a0
void FUN_710140f7a0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065358;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}
