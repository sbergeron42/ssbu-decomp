#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 002
// Range: 0x7101000000 — 0x7101FFFFFF

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
void FUN_710140f9b0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065310;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x710140faa0
void FUN_710140faa0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050652c8;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x710140fba0
void FUN_710140fba0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065280;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x710140fd30
void FUN_710140fd30(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065238;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x710140fe40
void FUN_710140fe40(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050651f0;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x710140ff70
void FUN_710140ff70(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050651a8;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101410100
void FUN_7101410100(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065160;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101410210
void FUN_7101410210(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105065118;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101434010
void FUN_7101434010(s64 param_1, u32 param_2, u32 param_3)
{
  u32 uVar1;

  uVar1 = 0x6e;
  switch(param_2) {
  case 0x24:
  case 0x6f:
    uVar1 = 0x24;
    break;
  case 0x25:
  case 0x70:
    uVar1 = 0x25;
    break;
  case 0x26:
  case 0x71:
    uVar1 = 0x26;
    break;
  default:
    uVar1 = param_2;
    break;
  case 0x4b:
  case 0x4c:
    break;
  case 0x72:
    uVar1 = 0x72;
  }
  *(u32 *)(param_1 + 0x170) = uVar1;
  *(u32 *)(param_1 + 0x174) = param_3 & 0xff;
  *(u8 *)(param_1 + 0x168) = 1;
  *(u8 *)(param_1 + 0x16a) = 1;
  return;
}

// 0x7101648bc0
void FUN_7101648bc0(s64 param_1, u64 *param_2)
{
  u64 uVar1;

  *param_2 = (u64)&PTR_LAB_7105078920;
  uVar1 = *(u64 *)(param_1 + 0x10);
  param_2[1] = *(u64 *)(param_1 + 8);
  param_2[2] = uVar1;
  return;
}

// 0x71016ec830
u8 FUN_71016ec830(s32 *param_1, s32 *param_2)
{
  s32 iVar1;
  s32 iVar2;
  s64 lVar3;
  s32 iVar4;
  s32 *piVar5;
  s32 iVar6;
  s32 *piVar7;
  s64 lVar8;
  s64 lVar9;

  switch(((s64)param_2 - (s64)param_1) >> 2) {
  case 0:
  case 1:
    break;
  case 2:
    iVar6 = *param_1;
    if (iVar6 <= param_2[-1]) {
      return true;
    }
    *param_1 = param_2[-1];
LAB_71016eca4c:
    param_2[-1] = iVar6;
    return true;
  case 3:
    iVar6 = *param_1;
    iVar1 = param_1[1];
    iVar2 = param_2[-1];
    if (iVar1 < iVar6) {
      if (iVar2 < iVar1) {
        *param_1 = iVar2;
      }
      else {
        *param_1 = iVar1;
        param_1[1] = iVar6;
        if (iVar6 <= param_2[-1]) {
          return true;
        }
        param_1[1] = param_2[-1];
      }
      goto LAB_71016eca4c;
    }
    if (iVar1 <= iVar2) {
      return true;
    }
    param_1[1] = iVar2;
    param_2[-1] = iVar1;
    iVar6 = *param_1;
    if (param_1[1] < iVar6) {
      *param_1 = param_1[1];
      param_1[1] = iVar6;
      return true;
    }
    break;
  case 4:
    iVar6 = *param_1;
    iVar1 = param_1[1];
    iVar2 = param_1[2];
    iVar4 = iVar2;
    if (iVar1 < iVar6) {
      if (iVar2 < iVar1) {
        *param_1 = iVar2;
      }
      else {
        *param_1 = iVar1;
        param_1[1] = iVar6;
        if (iVar6 <= iVar2) goto LAB_71016eca7c;
        param_1[1] = iVar2;
      }
      param_1[2] = iVar6;
      iVar4 = iVar6;
    }
    else if (iVar2 < iVar1) {
      param_1[1] = iVar2;
      param_1[2] = iVar1;
      iVar4 = iVar1;
      if (iVar2 < iVar6) {
        *param_1 = iVar2;
        param_1[1] = iVar6;
      }
    }
LAB_71016eca7c:
    if (iVar4 <= param_2[-1]) {
      return true;
    }
    param_1[2] = param_2[-1];
    param_2[-1] = iVar4;
    iVar6 = param_1[1];
    iVar1 = param_1[2];
    if (iVar6 <= iVar1) {
      return true;
    }
    iVar2 = *param_1;
    param_1[1] = iVar1;
    param_1[2] = iVar6;
    if (iVar1 < iVar2) {
      *param_1 = iVar1;
      param_1[1] = iVar2;
      return true;
    }
    break;
  case 5:
    FUN_71016ec6a0(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 + -1);
    return true;
  default:
    iVar6 = *param_1;
    iVar1 = param_1[1];
    iVar2 = param_1[2];
    iVar4 = iVar2;
    if (iVar1 < iVar6) {
      if (iVar2 < iVar1) {
        *param_1 = iVar2;
      }
      else {
        *param_1 = iVar1;
        param_1[1] = iVar6;
        if (iVar6 <= iVar2) goto LAB_71016ec9a0;
        param_1[1] = iVar2;
      }
      param_1[2] = iVar6;
      iVar4 = iVar6;
    }
    else if (iVar2 < iVar1) {
      param_1[1] = iVar2;
      param_1[2] = iVar1;
      iVar4 = iVar1;
      if (iVar2 < iVar6) {
        *param_1 = iVar2;
        param_1[1] = iVar6;
      }
    }
LAB_71016ec9a0:
    if (param_1 + 3 == param_2) {
      return true;
    }
    lVar8 = 0;
    iVar6 = 0;
    piVar7 = param_1 + 3;
    do {
      iVar1 = *piVar7;
      lVar3 = lVar8;
      if (iVar1 < iVar4) {
        do {
          lVar9 = lVar3;
          *(s32 *)((s64)param_1 + lVar9 + 0xc) = iVar4;
          piVar5 = param_1;
          if (lVar9 == -8) goto LAB_71016eca04;
          iVar4 = *(s32 *)((s64)param_1 + lVar9 + 4);
          lVar3 = lVar9 + -4;
        } while (iVar1 < iVar4);
        piVar5 = (s32 *)((s64)param_1 + lVar9 + 8);
LAB_71016eca04:
        iVar6 = iVar6 + 1;
        *piVar5 = iVar1;
        if (iVar6 == 8) {
          return (u8)(piVar7 + 1 == param_2);
        }
      }
      if (piVar7 + 1 == param_2) {
        return true;
      }
      iVar4 = *piVar7;
      lVar8 = lVar8 + 4;
      piVar7 = piVar7 + 1;
    } while( true );
  }
  return true;
}

// 0x710177e0f0
void FUN_710177e0f0(u16 *param_1, s32 param_2, s32 param_3, s32 *param_4, u32 param_5, u32 param_6,
                   s64 param_7)
{
  u32 uVar1;
  u32 uVar2;
  s32 iVar3;

  iVar3 = 0;
  do {
    if ((param_2 * 4 - param_3) + iVar3 != 0) {
      uVar1 = param_2 * 4 + iVar3;
      switch(uVar1) {
      case 9:
        if ((*param_4 == 2) ||
           ((((param_4[1] == 2 || (param_4[2] == 2)) ||
             ((param_4[3] == 2 || (((param_4[4] == 2 || (param_4[5] == 2)) || (param_4[6] == 2))))))\
            || (param_4[7] == 2)))) goto LAB_710177e2f4;
        break;
      case 0xb:
        if ((((*param_4 == 3) || (param_4[1] == 3)) ||
            ((param_4[2] == 3 || (((param_4[3] == 3 || (param_4[4] == 3)) || (param_4[5] == 3))))))\
           || ((param_4[6] == 3 || (param_4[7] == 3)))) goto LAB_710177e2f4;
        break;
      case 0xc:
        if ((*param_4 == 6) ||
           ((((((param_4[1] == 6 || (param_4[2] == 6)) || (param_4[3] == 6)) ||
              ((param_4[4] == 6 || (param_4[5] == 6)))) || (param_4[6] == 6)) || (param_4[7] == 6)))\
           ) goto LAB_710177e2f4;
        break;
      case 0xe:
        if ((((*param_4 == 7) || (param_4[1] == 7)) || (param_4[2] == 7)) ||
           (((param_4[3] == 7 || (param_4[4] == 7)) ||
            ((param_4[5] == 7 || ((param_4[6] == 7 || (param_4[7] == 7)))))))) goto LAB_710177e2f4;
      }
      if (((param_6 & 1) != 0) ||
         ((uVar2 = 1 << (u64)(uVar1 & 0x1f), (uVar2 & *param_1) == 0 &&
          (((param_5 & 1) == 0 || ((uVar2 & param_1[1]) == 0)))))) {
        *(u32 *)(*(s64 *)(param_7 + 0x10) + *(s64 *)(param_7 + 0x18) * 4) = uVar1;
        *(s64 *)(param_7 + 0x18) = *(s64 *)(param_7 + 0x18) + 1;
      }
    }
LAB_710177e2f4:
    iVar3 = iVar3 + 1;
    if (iVar3 == 4) {
      return;
    }
  } while( true );
}
