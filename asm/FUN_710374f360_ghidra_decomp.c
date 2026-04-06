
/* WARNING: Removing unreachable block (ram,0x00710375060c) */
/* WARNING: Removing unreachable block (ram,0x00710375066c) */
/* WARNING: Removing unreachable block (ram,0x00710375061c) */
/* WARNING: Removing unreachable block (ram,0x007103750684) */
/* WARNING: Removing unreachable block (ram,0x0071037506b0) */
/* WARNING: Removing unreachable block (ram,0x0071037506a0) */
/* WARNING: Removing unreachable block (ram,0x0071037506a4) */
/* WARNING: Removing unreachable block (ram,0x0071037506b8) */
/* WARNING: Removing unreachable block (ram,0x0071037506c4) */
/* WARNING: Removing unreachable block (ram,0x0071037506e8) */
/* WARNING: Removing unreachable block (ram,0x0071037506d4) */
/* WARNING: Removing unreachable block (ram,0x007103750700) */
/* WARNING: Removing unreachable block (ram,0x00710375072c) */
/* WARNING: Removing unreachable block (ram,0x00710375071c) */
/* WARNING: Removing unreachable block (ram,0x007103750720) */
/* WARNING: Removing unreachable block (ram,0x007103750734) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "FsSearchHeader": ignoring overlapping field "body" */
/* WARNING: Struct "LoadedArc": ignoring overlapping field "extra_count" */

void FUN_710374e2e0(undefined8 *param_1)

{
  undefined1 *puVar1;
  vector<uint> **ppvVar2;
  vector<uint> **ppvVar3;
  mutex *pmVar4;
  StreamEntry *pSVar5;
  StreamData *pSVar6;
  FilePath *pFVar7;
  FileInfoBucket *pFVar8;
  int iVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  ExtraEntry *pEVar12;
  uint uVar13;
  char cVar14;
  char cVar15;
  undefined1 uVar16;
  ushort uVar17;
  ushort uVar18;
  char cVar19;
  bool bVar20;
  int iVar21;
  Result RVar22;
  size_t sVar23;
  undefined8 *puVar24;
  void *pvVar25;
  ResServiceState *pRVar26;
  recursive_mutex *prVar27;
  EventType ***pppEVar28;
  SemaphoreType *pSVar29;
  undefined *puVar30;
  LoadedTables *pLVar31;
  astruct_6 *paVar32;
  LoadedData *pLVar33;
  int *piVar34;
  LoadedFsSearch *pLVar35;
  uint *puVar36;
  File_NX **ppFVar37;
  void *__dest;
  FileSystemHeader *fs_header;
  FsSearchHeader *__dest_00;
  LoadedDirectory *__s;
  Table1Entry *__s_00;
  Table2Entry *__s_01;
  long lVar38;
  long lVar39;
  ulong uVar40;
  __tree_node_base *p_Var41;
  long *plVar42;
  undefined1 *puVar43;
  code *pcVar44;
  size_t size;
  StreamHeader *pSVar45;
  HashToIndex *folder_child_hashes;
  FileInfoV2 *pFVar46;
  HashGroup *pHVar47;
  byte *pbVar48;
  HashToIndex *pHVar49;
  FileInfoV2 *pFVar50;
  ulong uVar51;
  ulong uVar52;
  undefined8 uVar53;
  FileData *file_datas;
  ExtraEntry *pEVar54;
  ulong file_data_count_2;
  DirInfo *pDVar55;
  uint *extra_entry_index;
  undefined8 uVar56;
  undefined8 *puVar57;
  LoadedArc *loaded_arc;
  long extra_curr_pos;
  char *pcVar58;
  ExtraEntry *__src;
  byte *pbVar59;
  long *plVar60;
  ulong curr_extra_entry_idx;
  undefined **ppuVar61;
  byte *pbVar62;
  FileSystemHeader *fs_header_cpy;
  LoadedFsSearch *pLVar63;
  char *pcVar64;
  undefined **ppuVar65;
  long lVar66;
  ulong unaff_x25;
  __tree_node_base *p_Var67;
  __tree_node_base *p_Var68;
  float fVar69;
  undefined1 local_4a0 [16];
  void *local_490;
  undefined8 local_488;
  long *local_480;
  char *local_478;
  undefined1 local_470 [16];
  void *local_460;
  ulong local_458;
  undefined8 local_450;
  void *local_448;
  undefined1 local_440;
  char local_43f;
  undefined2 local_43e;
  undefined8 local_430;
  code *local_428;
  void *local_420;
  ResServiceState *pRStack_418;
  long *local_410;
  ushort local_330;
  undefined2 local_22e;
  char cStack_221;
  undefined8 local_220;
  astruct_6 *local_218;
  long *local_200;
  ushort local_120;
  long *local_f0;
  undefined8 local_e0;
  long *local_c0;
  undefined1 local_b0 [24];
  undefined1 local_98 [8];
  long *local_90;
  undefined1 *local_88;
  size_t local_78;
  undefined4 local_6c [3];
  uint file_info_count;
  uint folder_count;
  uint file_data_count;
  uint file_data_count2;
  uint file_data_extra_count;
  
  local_4a0[8] = 0;
  local_4a0[9] = 0;
  local_4a0[10] = 0;
  local_4a0[0xb] = 0;
  local_4a0[0xc] = 0;
  local_4a0[0xd] = 0;
  local_4a0[0xe] = 0;
  local_4a0[0xf] = 0;
  local_490 = (void *)0x0;
  local_4a0._0_8_ = (void *)0x74736f6808;
  local_488 = 0x6d6f7206;
  local_470[8] = 0;
  local_470[9] = 0;
  local_470[10] = 0;
  local_470[0xb] = 0;
  local_470[0xc] = 0;
  local_470[0xd] = 0;
  local_470[0xe] = 0;
  local_470[0xf] = 0;
  local_470._0_8_ = 0x6576617308;
  local_460 = (void *)0x0;
  local_458 = 0x636d647308;
  local_480 = (long *)0x0;
  local_478 = (char *)0x0;
  local_450 = 0;
  local_448 = (void *)0x0;
  cVar14 = *(char *)(param_1 + 0xf);
  cVar15 = *(char *)(param_1 + 0x13);
  local_43f = cVar15 != '\0' || cVar14 != '\0';
  local_440 = 0;
  local_43e = 0;
  if (DAT_710593b288 == (long *)0x0) {
    do {
      if (DAT_710593b280 != 0) {
        ClearExclusiveLocal();
        goto LAB_710374e474;
      }
      cVar19 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x710593b280,0x10);
      if (bVar20) {
        DAT_710593b280 = 1;
        cVar19 = ExclusiveMonitorsStatus();
      }
    } while (cVar19 != '\0');
    iVar21 = je_posix_memalign((void **)&local_220,0x10,0x8148);
    if ((iVar21 == 0xc) && (DAT_710593b2b0 != (long *)0x0)) {
      local_430 = (undefined **)&DAT_00008148;
      curr_extra_entry_idx = (**(code **)(*DAT_710593b2b0 + 0x30))(DAT_710593b2b0,&local_430);
      if ((curr_extra_entry_idx & 1) != 0) {
        je_posix_memalign((void **)&local_220,0x10,0x8148);
      }
    }
    if (PTR_VirtualAllocHook_71052a6a78 != (undefined *)0x0) {
      nu::VirtualAllocHook(0x8148,0x10,local_220);
    }
    plVar60 = (long *)local_220;
    FUN_71037c4f70(local_220);
    *plVar60 = (long)&PTR_LAB_710523fcb8;
    plVar60[0x1027] = 0;
    plVar60[0x1026] = 0;
    plVar60[0x1028] = 0;
    DAT_710593b288 = plVar60;
  }
LAB_710374e474:
  pmVar4 = (mutex *)(DAT_710593b288 + 0x1022);
  std::__1::mutex::lock(pmVar4);
  pcVar64 = (char *)((long)&local_488 + 1);
  if ((local_488 & 1) != 0) {
    pcVar64 = local_478;
  }
  std::__1::basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>>::operator=
            ((basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>> *)
             &DAT_710593b268,(basic_string *)local_4a0);
  std::__1::basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>>::operator=
            ((basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>> *)
             &DAT_710593b250,(basic_string *)local_470);
  if (local_43f != '\0') {
    local_b0._0_8_ = (undefined1 *)0x0;
    RVar22 = nn::fs::QueryMountRomCacheSize((size_t *)local_b0);
    uVar56 = local_b0._0_8_;
    if (RVar22.m_Value == 0) {
      iVar21 = je_posix_memalign((void **)&local_220,0x10,local_b0._0_8_);
      if ((iVar21 == 0xc) && (DAT_710593b2b0 != (long *)0x0)) {
        local_430 = (undefined **)uVar56;
        curr_extra_entry_idx = (**(code **)(*DAT_710593b2b0 + 0x30))(DAT_710593b2b0,&local_430);
        if ((curr_extra_entry_idx & 1) != 0) {
          je_posix_memalign((void **)&local_220,0x10,uVar56);
        }
      }
      puVar30 = PTR_VirtualAllocHook_71052a6a78;
      if (PTR_VirtualAllocHook_71052a6a78 != (undefined *)0x0) {
        nu::VirtualAllocHook(uVar56,0x10,local_220);
      }
      RVar22 = nn::fs::MountRom(pcVar64,local_220,local_b0._0_8_);
      curr_extra_entry_idx = DAT_710593b028;
      if (RVar22.m_Value == 0) {
        file_data_count_2 =
             (((ulong)pcVar64 & 0x1fffffff) * 8 + 8 ^ (ulong)pcVar64 >> 0x20) * -0x622015f714c7d297;
        file_data_count_2 =
             (file_data_count_2 ^ (ulong)pcVar64 >> 0x20 ^ file_data_count_2 >> 0x2f) *
             -0x622015f714c7d297;
        file_data_count_2 = (file_data_count_2 ^ file_data_count_2 >> 0x2f) * -0x622015f714c7d297;
        if (DAT_710593b028 == 0) {
LAB_710374e644:
          iVar21 = je_posix_memalign((void **)&local_220,0x10,0x20);
          if ((iVar21 == 0xc) && (DAT_710593b2b0 != (long *)0x0)) {
            local_430 = (undefined **)0x20;
            uVar40 = (**(code **)(*DAT_710593b2b0 + 0x30))(DAT_710593b2b0,&local_430);
            if ((uVar40 & 1) != 0) {
              je_posix_memalign((void **)&local_220,0x10,0x20);
            }
          }
          if (puVar30 != (undefined *)0x0) {
            nu::VirtualAllocHook(0x20,0x10,local_220);
          }
          plVar60 = (long *)local_220;
          ((long *)local_220)[2] = (long)pcVar64;
          ((long *)local_220)[3] = 0;
          *local_220 = (undefined *)0x0;
          ((long *)local_220)[1] = file_data_count_2;
          if ((curr_extra_entry_idx == 0) ||
             (DAT_710593b040 * (float)curr_extra_entry_idx < (float)(DAT_710593b038 + 1))) {
            if (curr_extra_entry_idx < 3) {
              uVar40 = 1;
            }
            else {
              uVar40 = (ulong)((curr_extra_entry_idx - 1 & curr_extra_entry_idx) != 0);
            }
            uVar40 = uVar40 | curr_extra_entry_idx << 1;
            curr_extra_entry_idx = (ulong)((float)(DAT_710593b038 + 1) / DAT_710593b040);
            if (curr_extra_entry_idx <= uVar40) {
              curr_extra_entry_idx = uVar40;
            }
            if (curr_extra_entry_idx - 1 == 0) {
              curr_extra_entry_idx = 2;
            }
            else if ((curr_extra_entry_idx - 1 & curr_extra_entry_idx) != 0) {
              curr_extra_entry_idx = std::__1::__next_prime(curr_extra_entry_idx);
            }
            uVar40 = DAT_710593b028;
            if (DAT_710593b028 < curr_extra_entry_idx) {
              FUN_71037c4c80(curr_extra_entry_idx);
            }
            else if (curr_extra_entry_idx < DAT_710593b028) {
              uVar52 = (ulong)((float)DAT_710593b038 / DAT_710593b040);
              if (DAT_710593b028 < 3 || (DAT_710593b028 - 1 & DAT_710593b028) != 0) {
                uVar52 = std::__1::__next_prime(uVar52);
              }
              else if (1 < uVar52) {
                uVar52 = 1L << (-LZCOUNT(uVar52 - 1) & 0x3fU);
              }
              if (uVar52 <= curr_extra_entry_idx) {
                uVar52 = curr_extra_entry_idx;
              }
              if (uVar52 < uVar40) {
                FUN_71037c4c80();
              }
            }
            curr_extra_entry_idx = DAT_710593b028;
            if ((DAT_710593b028 - 1 & DAT_710593b028) == 0) {
              unaff_x25 = DAT_710593b028 - 1 & file_data_count_2;
            }
            else {
              unaff_x25 = file_data_count_2;
              if (DAT_710593b028 <= file_data_count_2) {
                uVar40 = 0;
                if (DAT_710593b028 != 0) {
                  uVar40 = file_data_count_2 / DAT_710593b028;
                }
                unaff_x25 = file_data_count_2 - uVar40 * DAT_710593b028;
              }
            }
          }
          plVar42 = *(long **)(DAT_710593b020 + unaff_x25 * 8);
          if (plVar42 == (long *)0x0) {
            *plVar60 = (long)DAT_710593b030;
            DAT_710593b030 = plVar60;
            *(long ***)(DAT_710593b020 + unaff_x25 * 8) = &DAT_710593b030;
            if (*plVar60 != 0) {
              file_data_count_2 = *(ulong *)(*plVar60 + 8);
              if ((curr_extra_entry_idx - 1 & curr_extra_entry_idx) == 0) {
                file_data_count_2 = file_data_count_2 & curr_extra_entry_idx - 1;
              }
              else if (curr_extra_entry_idx <= file_data_count_2) {
                uVar40 = 0;
                if (curr_extra_entry_idx != 0) {
                  uVar40 = file_data_count_2 / curr_extra_entry_idx;
                }
                file_data_count_2 = file_data_count_2 - uVar40 * curr_extra_entry_idx;
              }
              plVar42 = (long *)(DAT_710593b020 + file_data_count_2 * 8);
              goto LAB_710374e860;
            }
          }
          else {
            *plVar60 = *plVar42;
LAB_710374e860:
            *plVar42 = (long)plVar60;
          }
          DAT_710593b038 = DAT_710593b038 + 1;
        }
        else {
          uVar40 = DAT_710593b028 - 1;
          if ((uVar40 & DAT_710593b028) == 0) {
            unaff_x25 = file_data_count_2 & uVar40;
          }
          else {
            unaff_x25 = file_data_count_2;
            if (DAT_710593b028 <= file_data_count_2) {
              uVar52 = 0;
              if (DAT_710593b028 != 0) {
                uVar52 = file_data_count_2 / DAT_710593b028;
              }
              unaff_x25 = file_data_count_2 - uVar52 * DAT_710593b028;
            }
          }
          plVar60 = *(long **)(DAT_710593b020 + unaff_x25 * 8);
          if (plVar60 == (long *)0x0) goto LAB_710374e644;
          if ((uVar40 & DAT_710593b028) == 0) {
            do {
              plVar60 = (long *)*plVar60;
              if ((plVar60 == (long *)0x0) ||
                 (plVar60[1] != file_data_count_2 && (plVar60[1] & uVar40) != unaff_x25))
              goto LAB_710374e644;
            } while ((char *)plVar60[2] != pcVar64);
          }
          else {
            do {
              plVar60 = (long *)*plVar60;
              if (plVar60 == (long *)0x0) goto LAB_710374e644;
              uVar40 = plVar60[1];
              if (uVar40 != file_data_count_2) {
                if (DAT_710593b028 <= uVar40) {
                  uVar52 = 0;
                  if (DAT_710593b028 != 0) {
                    uVar52 = uVar40 / DAT_710593b028;
                  }
                  uVar40 = uVar40 - uVar52 * DAT_710593b028;
                }
                if (uVar40 != unaff_x25) goto LAB_710374e644;
              }
            } while ((char *)plVar60[2] != pcVar64);
          }
        }
        plVar60[3] = (long)"";
        local_22e = 0;
        local_430 = (undefined **)((ulong)local_430 & 0xffffffffffffff00);
        sVar23 = strlen(pcVar64);
        FUN_71037c34d0(&local_430,pcVar64,sVar23);
        FUN_71037c35b0(&local_430,&DAT_710433770b);
        memcpy(&DAT_710593b048,&local_430,0x201);
        DAT_710593b24a = local_22e;
      }
    }
  }
  std::__1::mutex::unlock(pmVar4);
  plVar60 = (long *)param_1[0x10];
  if (plVar60 != param_1 + 0x11) {
    do {
      std::__1::basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>>::
      basic_string((basic_string *)local_b0);
      std::__1::basic_string<char,std::__1::char_traits<char>,std::__1::allocator<char>>::
      basic_string((basic_string *)local_98);
      pcVar64 = (char *)((ulong)local_b0 | 1);
      if ((local_b0._0_8_ & 1) != 0) {
        pcVar64 = (char *)local_b0._16_8_;
      }
      puVar43 = local_98 + 1;
      if ((local_98[0] & 1) != 0) {
        puVar43 = local_88;
      }
      local_220 = (undefined **)((ulong)local_220 & 0xffffffffffffff00);
      sVar23 = strlen(pcVar64);
      local_120 = 0;
      if (sVar23 == 0) {
        puVar24 = &local_220;
      }
      else {
        if (sVar23 == 1) {
          curr_extra_entry_idx = 0;
LAB_710374ea30:
          local_120 = (short)curr_extra_entry_idx + 1;
          *(char *)((long)&local_220 + curr_extra_entry_idx) = *pcVar64;
          curr_extra_entry_idx = (ulong)local_120;
        }
        else {
          curr_extra_entry_idx = 0;
          extra_curr_pos = (sVar23 & 1) - sVar23;
          do {
            local_120 = (short)curr_extra_entry_idx + 1;
            *(char *)((long)&local_220 + curr_extra_entry_idx) = *pcVar64;
            curr_extra_entry_idx = (ulong)local_120;
            pcVar58 = pcVar64 + 1;
            pcVar64 = pcVar64 + 2;
            local_120 = local_120 + 1;
            extra_curr_pos = extra_curr_pos + 2;
            *(char *)((long)&local_220 + curr_extra_entry_idx) = *pcVar58;
            curr_extra_entry_idx = (ulong)local_120;
          } while (extra_curr_pos != 0);
          if ((sVar23 & 1) != 0) goto LAB_710374ea30;
        }
        puVar24 = (undefined8 *)((long)&local_220 + curr_extra_entry_idx);
      }
      *(undefined1 *)puVar24 = 0;
      curr_extra_entry_idx = (ulong)local_120;
      if (curr_extra_entry_idx != 0) {
        extra_curr_pos = 0;
        do {
          if (-extra_curr_pos == curr_extra_entry_idx) goto LAB_710374eb6c;
          lVar38 = extra_curr_pos + curr_extra_entry_idx;
          extra_curr_pos = extra_curr_pos + -1;
        } while (*(char *)((long)&local_220 + lVar38 + -1) != ':');
        if (extra_curr_pos != 0) {
          file_data_count_2 = (long)&local_220 + extra_curr_pos + curr_extra_entry_idx;
          uVar40 = file_data_count_2 - (long)&local_220;
          if (uVar40 != 0xffffffffffffffff) {
            uVar52 = curr_extra_entry_idx;
            if (uVar40 <= curr_extra_entry_idx) {
              uVar52 = uVar40;
            }
            local_430 = (undefined **)((ulong)local_430 & 0xffffffffffffff00);
            local_330 = 0;
            if (uVar52 == 0) {
              puVar24 = &local_430;
            }
            else {
              puVar24 = &local_220;
              pcVar64 = (char *)(~file_data_count_2 + (long)puVar24);
              if (pcVar64 <= (char *)~curr_extra_entry_idx) {
                pcVar64 = (char *)~curr_extra_entry_idx;
              }
              if (pcVar64 == (char *)0xfffffffffffffffe) {
                curr_extra_entry_idx = 0;
                file_data_count = 0;
              }
              else {
                pcVar64 = &cStack_221 + -file_data_count_2;
                if (pcVar64 <= (char *)~curr_extra_entry_idx) {
                  pcVar64 = (char *)~curr_extra_entry_idx;
                }
                curr_extra_entry_idx = 0;
                puVar24 = &local_220;
                pcVar64 = pcVar64 + (uVar52 & 1) + 1;
                do {
                  local_330 = (short)curr_extra_entry_idx + 1;
                  *(undefined1 *)((long)&local_430 + curr_extra_entry_idx) = *(undefined1 *)puVar24;
                  curr_extra_entry_idx = (ulong)local_330;
                  puVar1 = (undefined1 *)((long)puVar24 + 1);
                  puVar24 = (undefined8 *)((long)puVar24 + 2);
                  local_330 = local_330 + 1;
                  pcVar64 = pcVar64 + 2;
                  *(undefined1 *)((long)&local_430 + curr_extra_entry_idx) = *puVar1;
                  curr_extra_entry_idx = (ulong)local_330;
                  file_data_count = (uint)local_330;
                } while (pcVar64 != (char *)0x0);
              }
              if ((uVar52 & 1) != 0) {
                local_330 = (short)file_data_count + 1;
                *(undefined1 *)((long)&local_430 + (ulong)file_data_count) = *(undefined1 *)puVar24;
                curr_extra_entry_idx = (ulong)local_330;
              }
              puVar24 = (undefined8 *)((long)&local_430 + curr_extra_entry_idx);
            }
            *(undefined1 *)puVar24 = 0;
            memcpy(&local_220,&local_430,0x100);
            curr_extra_entry_idx = (ulong)local_330;
            local_120 = local_330;
          }
        }
      }
LAB_710374eb6c:
      file_data_count = (uint)curr_extra_entry_idx;
      if (3 < file_data_count) {
        curr_extra_entry_idx = 4;
      }
      if (((curr_extra_entry_idx == 0) ||
          (((byte)local_220 == 0x68 &&
           ((curr_extra_entry_idx == 1 ||
            ((local_220._1_1_ == 'o' &&
             ((curr_extra_entry_idx == 2 ||
              ((local_220._2_1_ == 's' && ((curr_extra_entry_idx == 3 || (local_220._3_1_ == 't'))))
              )))))))))) && (file_data_count == 4)) {
LAB_710374eddc:
        if ((local_98[0] & 1) == 0) goto LAB_710374ef74;
LAB_710374ede4:
        if (local_88 == (undefined1 *)0x0) goto LAB_710374ef74;
        free_default(local_88);
        if ((local_b0._0_8_ & 1) != 0) goto LAB_710374edf8;
LAB_710374ef7c:
        plVar42 = (long *)plVar60[1];
      }
      else {
        if (DAT_710593b288 == (long *)0x0) {
          do {
            if (DAT_710593b280 != 0) {
              ClearExclusiveLocal();
              goto LAB_710374eca0;
            }
            cVar19 = '\x01';
            bVar20 = (bool)ExclusiveMonitorPass(0x710593b280,0x10);
            if (bVar20) {
              DAT_710593b280 = 1;
              cVar19 = ExclusiveMonitorsStatus();
            }
          } while (cVar19 != '\0');
          iVar21 = je_posix_memalign((void **)&local_e0,0x10,0x8148);
          if ((iVar21 == 0xc) && (DAT_710593b2b0 != (long *)0x0)) {
            local_430 = (undefined **)&DAT_00008148;
            curr_extra_entry_idx = (**(code **)(*DAT_710593b2b0 + 0x30))(DAT_710593b2b0,&local_430);
            if ((curr_extra_entry_idx & 1) != 0) {
              je_posix_memalign((void **)&local_e0,0x10,0x8148);
            }
          }
          if (PTR_VirtualAllocHook_71052a6a78 != (undefined *)0x0) {
            nu::VirtualAllocHook(0x8148,0x10,(void *)CONCAT44(local_e0._4_4_,(undefined4)local_e0));
          }
          plVar42 = (long *)CONCAT44(local_e0._4_4_,(undefined4)local_e0);
          FUN_71037c4f70(plVar42);
          *plVar42 = (long)&PTR_LAB_710523fcb8;
          plVar42[0x1028] = 0;
          plVar42[0x1027] = 0;
          plVar42[0x1026] = 0;
          DAT_710593b288 = plVar42;
        }
LAB_710374eca0:
        (**(code **)(*DAT_710593b288 + 0x10))(&local_430,DAT_710593b288,&local_220,puVar43);
        if ((int)local_430 < 0) goto LAB_710374eddc;
        if (((DAT_7105330ed8 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_7105330ed8), iVar21 != 0)) {
          DAT_7105330ec8 = (__tree_node_base *)0x0;
          DAT_7105330ed0 = 0;
          DAT_7105330ec0 = &DAT_7105330ec8;
          FUN_71000001c0(&LAB_710353a780,&DAT_7105330ec0,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_7105330ed8);
        }
        p_Var67 = (__tree_node_base *)&DAT_7105330ec8;
        p_Var68 = p_Var67;
        if (DAT_7105330ec8 != (__tree_node_base *)0x0) {
          curr_extra_entry_idx = (ulong)local_120;
          file_data_count_2 = ~curr_extra_entry_idx;
          p_Var41 = DAT_7105330ec8;
LAB_710374ecf4:
          do {
            p_Var67 = p_Var41;
            uVar52 = (ulong)*(ushort *)&p_Var67[8].field_0x1a;
            pbVar59 = &p_Var67->field_0x1a;
            uVar40 = uVar52;
            if (curr_extra_entry_idx <= uVar52) {
              uVar40 = curr_extra_entry_idx;
            }
            file_data_count = (uint)local_120;
            file_data_count2 = (uint)*(ushort *)&p_Var67[8].field_0x1a;
            if (uVar40 != 0) {
              uVar51 = file_data_count_2;
              if (file_data_count_2 < ~uVar52) {
                uVar51 = ~uVar52;
              }
              pbVar62 = (byte *)&local_220;
              extra_curr_pos = uVar51 + 1;
              pbVar48 = pbVar59;
              do {
                iVar21 = (uint)*pbVar62 - (uint)*pbVar48;
                if (iVar21 != 0) {
                  iVar9 = file_data_count - file_data_count2;
                  if (iVar21 != 0) {
                    iVar9 = iVar21;
                  }
                  if (iVar9 < 0) goto LAB_710374eda4;
                  goto LAB_710374ed4c;
                }
                if (*pbVar62 == 0) break;
                pbVar62 = pbVar62 + 1;
                pbVar48 = pbVar48 + 1;
                extra_curr_pos = extra_curr_pos + 1;
              } while (extra_curr_pos != 0);
            }
            if (-1 < (int)(file_data_count - file_data_count2)) {
LAB_710374ed4c:
              if (uVar40 != 0) {
                uVar40 = file_data_count_2;
                if (file_data_count_2 < ~uVar52) {
                  uVar40 = ~uVar52;
                }
                pbVar62 = (byte *)&local_220;
                extra_curr_pos = uVar40 + 1;
                do {
                  iVar21 = (uint)*pbVar59 - (uint)*pbVar62;
                  if (iVar21 != 0) {
                    iVar9 = file_data_count2 - file_data_count;
                    if (iVar21 != 0) {
                      iVar9 = iVar21;
                    }
                    goto joined_r0x00710374edc4;
                  }
                  if (*pbVar59 == 0) break;
                  pbVar59 = pbVar59 + 1;
                  pbVar62 = pbVar62 + 1;
                  extra_curr_pos = extra_curr_pos + 1;
                } while (extra_curr_pos != 0);
              }
              iVar9 = file_data_count2 - file_data_count;
joined_r0x00710374edc4:
              if (iVar9 < 0) {
                p_Var68 = (__tree_node_base *)&p_Var67->__right_;
                p_Var41 = *(__tree_node_base **)p_Var68;
                if (*(__tree_node_base **)p_Var68 != (__tree_node_base *)0x0) goto LAB_710374ecf4;
              }
              p_Var41 = p_Var68->__left_;
              goto joined_r0x00710374eeb0;
            }
LAB_710374eda4:
            p_Var41 = p_Var67->__left_;
            p_Var68 = p_Var67;
          } while (p_Var67->__left_ != (__tree_node_base *)0x0);
          p_Var41 = p_Var67->__left_;
joined_r0x00710374eeb0:
          if (p_Var41 != (__tree_node_base *)0x0) goto LAB_710374eddc;
        }
        p_Var41 = (__tree_node_base *)je_aligned_alloc(0x10,0x120);
        if (p_Var41 == (__tree_node_base *)0x0) {
          if (GlobalAllocator != (void *)0x0) {
            local_e0._0_4_ = 0;
            local_430 = (undefined **)0x120;
                    /* WARNING: Load size is inaccurate */
            curr_extra_entry_idx =
                 (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_e0,&local_430);
            if (((curr_extra_entry_idx & 1) != 0) &&
               (p_Var41 = (__tree_node_base *)je_aligned_alloc(0x10,0x120),
               p_Var41 != (__tree_node_base *)0x0)) goto LAB_710374ee78;
          }
          p_Var41 = (__tree_node_base *)0x0;
        }
LAB_710374ee78:
        puVar43 = &p_Var41->field_0x1a;
        *puVar43 = 0;
        curr_extra_entry_idx = (ulong)local_120;
        *(undefined2 *)&p_Var41[8].field_0x1a = 0;
        if (curr_extra_entry_idx != 0) {
          if (local_120 == 1) {
            file_data_count_2 = 0;
            puVar24 = &local_220;
          }
          else {
            file_data_count_2 = 0;
            puVar24 = &local_220;
            extra_curr_pos = (curr_extra_entry_idx & 1) - curr_extra_entry_idx;
            do {
              uVar16 = *(undefined1 *)puVar24;
              *(short *)&p_Var41[8].field_0x1a = (short)file_data_count_2 + 1;
              extra_curr_pos = extra_curr_pos + 2;
              (&p_Var41->field_0x1a)[file_data_count_2] = uVar16;
              uVar17 = *(ushort *)&p_Var41[8].field_0x1a;
              uVar16 = *(undefined1 *)((long)puVar24 + 1);
              puVar24 = (undefined8 *)((long)puVar24 + 2);
              *(ushort *)&p_Var41[8].field_0x1a = uVar17 + 1;
              (&p_Var41->field_0x1a)[uVar17] = uVar16;
              file_data_count_2 = (ulong)*(ushort *)&p_Var41[8].field_0x1a;
            } while (extra_curr_pos != 0);
          }
          if ((local_120 & 1) != 0) {
            uVar16 = *(undefined1 *)puVar24;
            *(short *)&p_Var41[8].field_0x1a = (short)file_data_count_2 + 1;
            (&p_Var41->field_0x1a)[file_data_count_2] = uVar16;
            file_data_count_2 = (ulong)*(ushort *)&p_Var41[8].field_0x1a;
          }
          puVar43 = &p_Var41->field_0x1a + file_data_count_2;
        }
        *puVar43 = 0;
        p_Var41->__parent_ = p_Var67;
        p_Var41->__left_ = (__tree_node_base *)0x0;
        p_Var41->__right_ = (__tree_node_base *)0x0;
        p_Var68->__left_ = p_Var41;
        if ((undefined8 *)*DAT_7105330ec0 != (undefined8 *)0x0) {
          p_Var41 = p_Var68->__left_;
          DAT_7105330ec0 = (undefined8 *)*DAT_7105330ec0;
        }
        std::__1::__tree_balance_after_insert<std::__1::__tree_node_base<void*>*>
                  (DAT_7105330ec8,p_Var41);
        DAT_7105330ed0 = DAT_7105330ed0 + 1;
        if ((local_98[0] & 1) != 0) goto LAB_710374ede4;
LAB_710374ef74:
        if ((local_b0._0_8_ & 1) == 0) goto LAB_710374ef7c;
LAB_710374edf8:
        if ((char *)local_b0._16_8_ == (char *)0x0) goto LAB_710374ef7c;
        free_default((void *)local_b0._16_8_);
        plVar42 = (long *)plVar60[1];
      }
      if (plVar42 == (long *)0x0) {
        plVar42 = plVar60 + 2;
        bVar20 = *(long **)*plVar42 != plVar60;
        plVar60 = (long *)*plVar42;
        if (bVar20) {
          do {
            extra_curr_pos = *plVar42;
            plVar42 = (long *)(extra_curr_pos + 0x10);
            plVar60 = (long *)*plVar42;
          } while (*(long *)*plVar42 != extra_curr_pos);
        }
      }
      else {
        do {
          plVar60 = plVar42;
          plVar42 = (long *)*plVar60;
        } while (plVar42 != (long *)0x0);
      }
    } while (plVar60 != param_1 + 0x11);
  }
  if (cVar15 != '\0' || cVar14 != '\0') {
    if (((DAT_7105330ed8 & 1) == 0) &&
       (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_7105330ed8), iVar21 != 0)) {
      DAT_7105330ec8 = (__tree_node_base *)0x0;
      DAT_7105330ed0 = 0;
      DAT_7105330ec0 = &DAT_7105330ec8;
      FUN_71000001c0(&LAB_710353a780,&DAT_7105330ec0,&PTR_LOOP_7104f15000);
      __cxa_guard_release((uint64_t *)&DAT_7105330ed8);
    }
    local_430 = (undefined **)CONCAT44(local_430._4_4_,0x6d6f72);
    local_330 = 3;
    FUN_710353a7d0(&local_430,&local_430);
  }
  if (((DAT_7105330ed8 & 1) == 0) &&
     (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_7105330ed8), iVar21 != 0)) {
    DAT_7105330ec8 = (__tree_node_base *)0x0;
    DAT_7105330ed0 = 0;
    DAT_7105330ec0 = &DAT_7105330ec8;
    FUN_71000001c0(&LAB_710353a780,&DAT_7105330ec0,&PTR_LOOP_7104f15000);
    __cxa_guard_release((uint64_t *)&DAT_7105330ed8);
  }
  local_330 = 4;
  local_430 = (undefined **)CONCAT35(local_430._5_3_,0x65766173);
  FUN_710353a7d0(&local_430,&local_430);
  if (((DAT_7105330ed8 & 1) == 0) &&
     (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_7105330ed8), iVar21 != 0)) {
    DAT_7105330ec8 = (__tree_node_base *)0x0;
    DAT_7105330ed0 = 0;
    DAT_7105330ec0 = &DAT_7105330ec8;
    FUN_71000001c0(&LAB_710353a780,&DAT_7105330ec0,&PTR_LOOP_7104f15000);
    __cxa_guard_release((uint64_t *)&DAT_7105330ed8);
  }
  local_330 = 5;
  local_430 = (undefined **)CONCAT26(local_430._6_2_,0x6568636163);
  FUN_710353a7d0(&local_430,&local_430);
  if ((char)local_43e != '\0') {
    if (((DAT_7105330ed8 & 1) == 0) &&
       (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_7105330ed8), iVar21 != 0)) {
      DAT_7105330ec8 = (__tree_node_base *)0x0;
      DAT_7105330ed0 = 0;
      DAT_7105330ec0 = &DAT_7105330ec8;
      FUN_71000001c0(&LAB_710353a780,&DAT_7105330ec0,&PTR_LOOP_7104f15000);
      __cxa_guard_release((uint64_t *)&DAT_7105330ed8);
    }
    local_330 = 4;
    local_430 = (undefined **)CONCAT35(local_430._5_3_,0x636d6473);
    FUN_710353a7d0(&local_430,&local_430);
  }
  if (((local_458 & 1) != 0) && (local_448 != (void *)0x0)) {
    free_default(local_448);
  }
  if (((local_470._0_8_ & 1) != 0) && (local_460 != (void *)0x0)) {
    free_default(local_460);
  }
  if (((local_488 & 1) != 0) && (local_478 != (char *)0x0)) {
    free_default(local_478);
  }
  if (((local_4a0._0_8_ & 1) != 0) && (local_490 != (void *)0x0)) {
    free_default(local_490);
  }
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x40;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40), puVar24 != (undefined8 *)0x0))
      goto LAB_710374f144;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_710374f144:
  puVar24[2] = &PTR_FUN_710523b150;
  puVar24[6] = puVar24 + 2;
  *puVar24 = &DAT_71059394d0;
  puVar24[1] = DAT_71059394d8;
  *DAT_71059394d8 = puVar24;
  DAT_71059394e0 = DAT_71059394e0 + 1;
  DAT_71059394d8 = puVar24;
  while (DAT_71052b4e70 == (undefined8 *)0x0) {
    do {
      if (DAT_71052b4e78 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4e80 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4e80), iVar21 != 0)) {
          DAT_71052b4748 = 0;
          DAT_71052b4750 = 0x40000000;
          DAT_71052b4758 = 0x10;
          DAT_71052b4770 = 0;
          DAT_71052b4740 = 0;
          DAT_71052b4760 = 0;
          DAT_71052b4768 = 1;
          DAT_71052b4738 = &PTR_LAB_710523fe98;
          DAT_71052b4778 = 0;
          DAT_71052b4780 = 0;
          FUN_71000001c0(&LAB_71002c42b0,&DAT_71052b4738,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4e80);
        }
        DAT_71052b4e70 = &DAT_71052b4738;
        goto LAB_710374f1d0;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4e78,0x10);
      if (bVar20) {
        DAT_71052b4e78 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f1d0:
  puVar24 = DAT_71052b4e70;
  pmVar4 = (mutex *)(DAT_71052b4e70 + 6);
  std::__1::mutex::lock(pmVar4);
  uVar56 = *param_1;
  uVar11 = param_1[1];
  uVar53 = param_1[3];
  puVar24[3] = param_1[2];
  puVar24[4] = uVar53;
  puVar24[1] = uVar56;
  puVar24[2] = uVar11;
  std::__1::mutex::unlock(pmVar4);
  extra_curr_pos = nu::ModuleInitializer<nu::GraphicsModule,nu::GraphicsModuleDesc>::Instance();
  std::__1::mutex::lock((mutex *)(extra_curr_pos + 0x38));
  *(undefined8 *)(extra_curr_pos + 8) = param_1[4];
  uVar53 = param_1[7];
  uVar56 = param_1[5];
  uVar11 = param_1[6];
  *(undefined2 *)(extra_curr_pos + 0x28) = *(undefined2 *)(param_1 + 8);
  *(undefined8 *)(extra_curr_pos + 0x10) = uVar56;
  *(undefined8 *)(extra_curr_pos + 0x18) = uVar11;
  *(undefined8 *)(extra_curr_pos + 0x20) = uVar53;
  std::__1::mutex::unlock((mutex *)(extra_curr_pos + 0x38));
  while (DAT_71052b4ed0 == (undefined8 *)0x0) {
    do {
      if (DAT_71052b4ed8 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4ee0 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4ee0), iVar21 != 0)) {
          DAT_71052b4cb8 = &PTR_FUN_710528eea8;
          DAT_71052b4c60 = &PTR_LAB_710528fc98;
          DAT_71052b4d10 = &PTR_LAB_710522f8d0;
          DAT_71052b4d18 = 0;
          DAT_71052b4d70 = &PTR_LAB_710522f8d0;
          DAT_71052b4d78 = 0;
          DAT_71052b4c8c = 0;
          DAT_71052b4c84 = 0;
          DAT_71052b4c7c = 0;
          DAT_71052b4c74 = 0;
          DAT_71052b4c6c = 0x100000000;
          DAT_71052b4cb0 = 0x3f800000;
          DAT_71052b4ce0 = 0x3f800000;
          DAT_71052b4d08 = 0x3f800000;
          DAT_71052b4db0 = 0;
          DAT_71052b4db8 = &PTR_FUN_710528fba8;
          DAT_71052b4de0 = 0x3f800000;
          DAT_71052b4ca0 = 0;
          DAT_71052b4ca8 = 0;
          DAT_71052b4c90 = 0;
          DAT_71052b4c98 = 0;
          DAT_71052b4cd0 = 0;
          DAT_71052b4cd8 = 0;
          DAT_71052b4cc0 = 0;
          DAT_71052b4cc8 = 0;
          DAT_71052b4cf8 = 0;
          DAT_71052b4d00 = 0;
          DAT_71052b4ce8 = 0;
          DAT_71052b4cf0 = 0;
          DAT_71052b4d20 = 0;
          DAT_71052b4d28 = 0;
          DAT_71052b4d40 = 0;
          DAT_71052b4d48 = 0;
          DAT_71052b4d30 = &PTR_LAB_710522e2c0;
          DAT_71052b4d38 = 0;
          DAT_71052b4d60 = 0;
          DAT_71052b4d68 = 0;
          DAT_71052b4d50 = &PTR_LAB_710522f730;
          DAT_71052b4d58 = 0;
          DAT_71052b4d80 = 0;
          DAT_71052b4d88 = 0;
          DAT_71052b4da0 = 0;
          DAT_71052b4da8 = 0;
          DAT_71052b4d90 = &PTR_LAB_710522e2c0;
          DAT_71052b4d98 = 0;
          DAT_71052b4dd0 = 0;
          DAT_71052b4dd8 = 0;
          DAT_71052b4dc0 = 0;
          DAT_71052b4dc8 = 0;
          DAT_71052b4df8 = 0;
          DAT_71052b4e00 = 0;
          DAT_71052b4df0 = 0;
          DAT_71052b4de8 = 1;
          FUN_71000001c0(&LAB_71038b5ca0,&DAT_71052b4c60,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4ee0);
        }
        DAT_71052b4ed0 = &DAT_71052b4c60;
        goto LAB_710374f288;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4ed8,0x10);
      if (bVar20) {
        DAT_71052b4ed8 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f288:
  pmVar4 = (mutex *)(DAT_71052b4ed0 + 2);
  std::__1::mutex::lock(pmVar4);
  std::__1::mutex::unlock(pmVar4);
  extra_curr_pos = FUN_71002c53c0();
  std::__1::mutex::lock((mutex *)(extra_curr_pos + 0x10));
  *(undefined4 *)(extra_curr_pos + 8) = *(undefined4 *)((long)param_1 + 0x4c);
  std::__1::mutex::unlock((mutex *)(extra_curr_pos + 0x10));
  while (DAT_71052b4ea0 == (long *)0x0) {
    do {
      if (DAT_71052b4ea8 != 0) {
        ClearExclusiveLocal();
        FUN_71002c4f60();
        DAT_71052b4ea0 = &DAT_71052b49f8;
        goto LAB_710374f310;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4ea8,0x10);
      if (bVar20) {
        DAT_71052b4ea8 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f310:
  plVar60 = DAT_71052b4ea0;
  pmVar4 = (mutex *)(DAT_71052b4ea0 + 5);
  std::__1::mutex::lock(pmVar4);
  if (plVar60 + 1 != param_1 + 10) {
    curr_extra_entry_idx = param_1[0xb];
    extra_curr_pos = param_1[0xc];
    if ((*(byte *)(param_1 + 10) & 1) == 0) {
      extra_curr_pos = (long)param_1 + 0x51;
      curr_extra_entry_idx = (ulong)(*(byte *)(param_1 + 10) >> 1);
    }
    FUN_71002c51f0(plVar60 + 1,extra_curr_pos,curr_extra_entry_idx);
  }
  std::__1::mutex::unlock(pmVar4);
  while (DAT_71052b4ee8 == (long *)0x0) {
    do {
      if (DAT_71052b4ef0 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4ef8 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4ef8), iVar21 != 0)) {
          DAT_71052b4e34 = 0;
          DAT_71052b4e2c = 0;
          DAT_71052b4e24 = 0;
          DAT_71052b4e1c = 0;
          DAT_71052b4e14 = 0x100000000;
          DAT_71052b4e08 = &PTR_LAB_7105290260;
          FUN_71000001c0(&LAB_71038dee90,&DAT_71052b4e08,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4ef8);
        }
        DAT_71052b4ee8 = (long *)&DAT_71052b4e08;
        goto LAB_710374f3a4;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4ef0,0x10);
      if (bVar20) {
        DAT_71052b4ef0 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f3a4:
  pmVar4 = (mutex *)(DAT_71052b4ee8 + 2);
  std::__1::mutex::lock(pmVar4);
  std::__1::mutex::unlock(pmVar4);
  while (DAT_71052b4f00 == (long *)0x0) {
    do {
      if (DAT_71052b4f08 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4f10 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4f10), iVar21 != 0)) {
          DAT_71052b4e48 = 0;
          DAT_71052b4e38 = &PTR_LAB_7105291ad8;
          DAT_71052b4e40 = 4;
          DAT_71052b4e60 = 0;
          DAT_71052b4e68 = 0;
          DAT_71052b4e58 = 0;
          DAT_71052b4e50 = 1;
          FUN_71000001c0(&LAB_71038f2450,&DAT_71052b4e38,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4f10);
        }
        DAT_71052b4f00 = (long *)&DAT_71052b4e38;
        goto LAB_710374f410;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4f08,0x10);
      if (bVar20) {
        DAT_71052b4f08 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f410:
  plVar60 = DAT_71052b4f00;
  pmVar4 = (mutex *)(DAT_71052b4f00 + 3);
  std::__1::mutex::lock(pmVar4);
  plVar60[1] = param_1[0xe];
  std::__1::mutex::unlock(pmVar4);
  FUN_71037c9e70(&local_430);
  plVar60 = (long *)nu::ModuleInitializer<nu::GraphicsModule,nu::GraphicsModuleDesc>::Instance();
  std::__1::mutex::lock((mutex *)(plVar60 + 7));
  iVar21 = (int)plVar60[6];
  if (iVar21 == 0) {
    (**(code **)(*plVar60 + 0x10))(plVar60);
    (**(code **)*plVar60)(&local_430,plVar60,plVar60 + 1);
    (**(code **)(*plVar60 + 0x20))(plVar60);
    iVar21 = (int)plVar60[6];
  }
  *(int *)(plVar60 + 6) = iVar21 + 1;
  std::__1::mutex::unlock((mutex *)(plVar60 + 7));
  FUN_71038cbec0(&local_430);
  plVar60 = (long *)FUN_71002c53c0();
  std::__1::mutex::lock((mutex *)(plVar60 + 2));
  iVar21 = *(int *)((long)plVar60 + 0xc);
  if (iVar21 == 0) {
    (**(code **)(*plVar60 + 0x10))(plVar60);
    (**(code **)*plVar60)(&local_430,plVar60,plVar60 + 1);
    (**(code **)(*plVar60 + 0x20))(plVar60);
    iVar21 = *(int *)((long)plVar60 + 0xc);
  }
  *(int *)((long)plVar60 + 0xc) = iVar21 + 1;
  std::__1::mutex::unlock((mutex *)(plVar60 + 2));
  while (DAT_71052b4ea0 == (long *)0x0) {
    do {
      if (DAT_71052b4ea8 != 0) {
        ClearExclusiveLocal();
        FUN_71002c4f60();
        DAT_71052b4ea0 = &DAT_71052b49f8;
        goto LAB_710374f554;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4ea8,0x10);
      if (bVar20) {
        DAT_71052b4ea8 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f554:
  plVar60 = DAT_71052b4ea0;
  pmVar4 = (mutex *)(DAT_71052b4ea0 + 5);
  std::__1::mutex::lock(pmVar4);
  iVar21 = (int)plVar60[4];
  if (iVar21 == 0) {
    (**(code **)(*plVar60 + 0x10))(plVar60);
    (**(code **)*plVar60)(&local_430,plVar60,plVar60 + 1);
    (**(code **)(*plVar60 + 0x20))(plVar60);
    iVar21 = (int)plVar60[4];
  }
  *(int *)(plVar60 + 4) = iVar21 + 1;
  std::__1::mutex::unlock(pmVar4);
  while (DAT_71052b4ee8 == (long *)0x0) {
    do {
      if (DAT_71052b4ef0 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4ef8 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4ef8), iVar21 != 0)) {
          DAT_71052b4e34 = 0;
          DAT_71052b4e2c = 0;
          DAT_71052b4e24 = 0;
          DAT_71052b4e1c = 0;
          DAT_71052b4e14 = 0x100000000;
          DAT_71052b4e08 = &PTR_LAB_7105290260;
          FUN_71000001c0(&LAB_71038dee90,&DAT_71052b4e08,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4ef8);
        }
        DAT_71052b4ee8 = (long *)&DAT_71052b4e08;
        goto LAB_710374f608;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4ef0,0x10);
      if (bVar20) {
        DAT_71052b4ef0 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f608:
  plVar60 = DAT_71052b4ee8;
  pmVar4 = (mutex *)(DAT_71052b4ee8 + 2);
  std::__1::mutex::lock(pmVar4);
  iVar21 = *(int *)((long)plVar60 + 0xc);
  if (iVar21 == 0) {
    (**(code **)(*plVar60 + 0x10))(plVar60);
    (**(code **)*plVar60)(&local_430,plVar60,plVar60 + 1);
    (**(code **)(*plVar60 + 0x20))(plVar60);
    iVar21 = *(int *)((long)plVar60 + 0xc);
  }
  *(int *)((long)plVar60 + 0xc) = iVar21 + 1;
  std::__1::mutex::unlock(pmVar4);
  while (DAT_71052b4f00 == (long *)0x0) {
    do {
      if (DAT_71052b4f08 != 0) {
        ClearExclusiveLocal();
        if (((DAT_71052b4f10 & 1) == 0) &&
           (iVar21 = __cxa_guard_acquire((uint64_t *)&DAT_71052b4f10), iVar21 != 0)) {
          DAT_71052b4e48 = 0;
          DAT_71052b4e38 = &PTR_LAB_7105291ad8;
          DAT_71052b4e40 = 4;
          DAT_71052b4e60 = 0;
          DAT_71052b4e68 = 0;
          DAT_71052b4e58 = 0;
          DAT_71052b4e50 = 1;
          FUN_71000001c0(&LAB_71038f2450,&DAT_71052b4e38,&PTR_LOOP_7104f15000);
          __cxa_guard_release((uint64_t *)&DAT_71052b4f10);
        }
        DAT_71052b4f00 = (long *)&DAT_71052b4e38;
        goto LAB_710374f6bc;
      }
      cVar14 = '\x01';
      bVar20 = (bool)ExclusiveMonitorPass(0x71052b4f08,0x10);
      if (bVar20) {
        DAT_71052b4f08 = 1;
        cVar14 = ExclusiveMonitorsStatus();
      }
    } while (cVar14 != '\0');
    nn::os::YieldThread();
  }
LAB_710374f6bc:
  plVar60 = DAT_71052b4f00;
  pmVar4 = (mutex *)(DAT_71052b4f00 + 3);
  std::__1::mutex::lock(pmVar4);
  iVar21 = (int)plVar60[2];
  if (iVar21 == 0) {
    (**(code **)(*plVar60 + 0x10))(plVar60);
    (**(code **)*plVar60)(&local_430,plVar60,plVar60 + 1);
    (**(code **)(*plVar60 + 0x20))(plVar60);
    iVar21 = (int)plVar60[2];
  }
  *(int *)(plVar60 + 2) = iVar21 + 1;
  std::__1::mutex::unlock(pmVar4);
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x40;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40), puVar24 != (undefined8 *)0x0))
      goto LAB_710374f770;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_710374f770:
  puVar24[2] = &PTR_FUN_710523b198;
  puVar24[6] = puVar24 + 2;
  *puVar24 = &DAT_71059394d0;
  puVar24[1] = DAT_71059394d8;
  *DAT_71059394d8 = puVar24;
  DAT_71059394e0 = DAT_71059394e0 + 1;
  DAT_710522dbe8 = param_1[0x81];
  DAT_710522dbe0 = (undefined4)param_1[0x80];
  DAT_71059394d8 = puVar24;
  pvVar25 = je_aligned_alloc(0x10,0x60);
  if (pvVar25 == (void *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x60;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pvVar25 = je_aligned_alloc(0x10,0x60), pvVar25 != (void *)0x0)) goto LAB_710374f810;
    }
    pvVar25 = (void *)0x0;
  }
LAB_710374f810:
  FUN_7103548bf0(pvVar25,0,param_1 + 0x7d);
  DAT_7105331f58 = pvVar25;
  pvVar25 = je_aligned_alloc(0x10,0x60);
  if (pvVar25 == (void *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x60;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pvVar25 = je_aligned_alloc(0x10,0x60), pvVar25 != (void *)0x0)) goto LAB_710374f884;
    }
    pvVar25 = (void *)0x0;
  }
LAB_710374f884:
  FUN_7103548bf0(pvVar25,1,(long)param_1 + 0x3f4);
  DAT_7105331f60 = pvVar25;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x40;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40), puVar24 != (undefined8 *)0x0))
      goto LAB_710374f8f0;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_710374f8f0:
  puVar24[2] = &PTR_FUN_710523b1e0;
  puVar24[6] = puVar24 + 2;
  *puVar24 = &DAT_71059394d0;
  puVar24[1] = DAT_71059394d8;
  *DAT_71059394d8 = puVar24;
  DAT_71059394e0 = DAT_71059394e0 + 1;
  DAT_71059394d8 = puVar24;
  pRVar26 = (ResServiceState *)je_aligned_alloc(0x10,0x250);
  if (pRVar26 == (ResServiceState *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x250;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pRVar26 = (ResServiceState *)je_aligned_alloc(0x10,0x250),
         pRVar26 != (ResServiceState *)0x0)) goto LAB_710374f978;
    }
    pRVar26 = (ResServiceState *)0x0;
  }
LAB_710374f978:
  prVar27 = (recursive_mutex *)je_aligned_alloc(0x10,0x20);
  if (prVar27 == (recursive_mutex *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x20;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (prVar27 = (recursive_mutex *)je_aligned_alloc(0x10,0x20),
         prVar27 != (recursive_mutex *)0x0)) goto LAB_710374f9d4;
    }
    prVar27 = (recursive_mutex *)0x0;
  }
LAB_710374f9d4:
  std::__1::recursive_mutex::recursive_mutex(prVar27);
  pRVar26->mutex = prVar27;
  pppEVar28 = (EventType ***)je_aligned_alloc(0x10,8);
  if (pppEVar28 == (EventType ***)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pppEVar28 = (EventType ***)je_aligned_alloc(0x10,8), pppEVar28 != (EventType ***)0x0))
      goto LAB_710374fa3c;
    }
    pppEVar28 = (EventType ***)0x0;
  }
LAB_710374fa3c:
  FUN_710353b700(pppEVar28,0);
  pRVar26->update_performed = pppEVar28;
  pvVar25 = je_aligned_alloc(0x10,8);
  if (pvVar25 == (void *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pvVar25 = je_aligned_alloc(0x10,8), pvVar25 != (void *)0x0)) goto LAB_710374faa8;
    }
    pvVar25 = (void *)0x0;
  }
LAB_710374faa8:
  FUN_710353b700(pvVar25,0);
  *(void **)&pRVar26->field_0x10 = pvVar25;
  pppEVar28 = (EventType ***)je_aligned_alloc(0x10,8);
  if (pppEVar28 == (EventType ***)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pppEVar28 = (EventType ***)je_aligned_alloc(0x10,8), pppEVar28 != (EventType ***)0x0))
      goto LAB_710374fb14;
    }
    pppEVar28 = (EventType ***)0x0;
  }
LAB_710374fb14:
  FUN_710353b700(pppEVar28,0);
  pRVar26->io_swap_event = pppEVar28;
  pvVar25 = je_aligned_alloc(0x10,8);
  if (pvVar25 == (void *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pvVar25 = je_aligned_alloc(0x10,8), pvVar25 != (void *)0x0)) goto LAB_710374fb80;
    }
    pvVar25 = (void *)0x0;
  }
LAB_710374fb80:
  FUN_710353b700(pvVar25,0);
  *(void **)&pRVar26->field_0x20 = pvVar25;
  pSVar29 = (SemaphoreType *)je_aligned_alloc(0x10,8);
  if (pSVar29 == (SemaphoreType *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pSVar29 = (SemaphoreType *)je_aligned_alloc(0x10,8), pSVar29 != (SemaphoreType *)0x0))
      goto LAB_710374fbec;
    }
    pSVar29 = (SemaphoreType *)0x0;
  }
LAB_710374fbec:
  FUN_7103545d80(pSVar29,2,2);
  pRVar26->field19_0x28 = pSVar29;
  puVar30 = (undefined *)je_aligned_alloc(0x10,8);
  if (puVar30 == (undefined *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar30 = (undefined *)je_aligned_alloc(0x10,8), puVar30 != (undefined *)0x0))
      goto LAB_710374fc5c;
    }
    puVar30 = (undefined *)0x0;
  }
LAB_710374fc5c:
  FUN_7103545d80(puVar30,1,1);
  pRVar26->field20_0x30 = puVar30;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  if (puVar24 == (undefined8 *)0x0) {
    local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
    local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
    (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
    puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  }
  *puVar24 = 0;
  pRVar26->res_update_thread = (undefined *)puVar24;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  if (puVar24 == (undefined8 *)0x0) {
    local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
    local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
    (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
    puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  }
  *puVar24 = 0;
  pRVar26->res_loading_thread = (undefined *)puVar24;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  if (puVar24 == (undefined8 *)0x0) {
    local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
    local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
    (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
    puVar24 = (undefined8 *)je_aligned_alloc(0x10,8);
  }
  *puVar24 = 0;
  pRVar26->res_inflate_thread = (undefined *)puVar24;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x90);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x90;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x90), puVar24 != (undefined8 *)0x0))
      goto LAB_710374fda8;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_710374fda8:
  *puVar24 = 0;
  *(undefined4 *)(puVar24 + 1) = 0;
  puVar24[2] = 0;
  puVar24[3] = 0;
  puVar24[4] = 0;
  puVar24[6] = &PTR_LAB_710522db60;
  puVar24[7] = &LAB_7103545540;
  puVar24[10] = puVar24 + 6;
  puVar24[0xc] = &PTR_LAB_710522dba8;
  puVar24[0xd] = &LAB_71035455c0;
  ppvVar2 = &pRVar26->field32_0x58[0].end;
  puVar24[0x10] = puVar24 + 0xc;
  ppvVar3 = &pRVar26->field32_0x58[2].end;
  pRVar26->field32_0x58[0].end = (vector<uint> *)ppvVar2;
  pRVar26->field32_0x58[0].eos = (vector<uint> *)ppvVar2;
  ppvVar2 = &pRVar26->field32_0x58[1].end;
  *(undefined8 **)&pRVar26->field_0x50 = puVar24;
  pRVar26->field32_0x58[0].start = (vector<uint> *)0x0;
  pRVar26->field32_0x58[1].start = (vector<uint> *)0x0;
  pRVar26->field32_0x58[1].end = (vector<uint> *)ppvVar2;
  pRVar26->field32_0x58[1].eos = (vector<uint> *)ppvVar2;
  pRVar26->field32_0x58[2].start = (vector<uint> *)0x0;
  ppvVar2 = &pRVar26->field32_0x58[3].end;
  pRVar26->field32_0x58[2].end = (vector<uint> *)ppvVar3;
  pRVar26->field32_0x58[2].eos = (vector<uint> *)ppvVar3;
  pRVar26->field32_0x58[3].start = (vector<uint> *)0x0;
  pRVar26->field32_0x58[3].end = (vector<uint> *)ppvVar2;
  pRVar26->field32_0x58[3].eos = (vector<uint> *)ppvVar2;
  pRVar26->field33_0xb8 = (undefined *)0x0;
  *(undefined1 **)&pRVar26->field_0xc0 = &pRVar26->field_0xc0;
  *(undefined1 **)&pRVar26->field_0xc8 = &pRVar26->field_0xc0;
  pLVar31 = (LoadedTables *)je_aligned_alloc(0x10,0x88);
  if (pLVar31 == (LoadedTables *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x88;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pLVar31 = (LoadedTables *)je_aligned_alloc(0x10,0x88), pLVar31 != (LoadedTables *)0x0))
      goto LAB_710374fe88;
    }
    pLVar31 = (LoadedTables *)0x0;
  }
LAB_710374fe88:
  uVar56 = param_1[0x7b];
  prVar27 = (recursive_mutex *)je_aligned_alloc(0x10,0x20);
  if (prVar27 == (recursive_mutex *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x20;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (prVar27 = (recursive_mutex *)je_aligned_alloc(0x10,0x20),
         prVar27 != (recursive_mutex *)0x0)) goto LAB_710374fee8;
    }
    prVar27 = (recursive_mutex *)0x0;
  }
LAB_710374fee8:
  std::__1::recursive_mutex::recursive_mutex(prVar27);
  pLVar31->mutex = prVar27;
  (pLVar31->field11_0x50).end = (uint *)0x0;
  (pLVar31->field11_0x50).eos = (uint *)0x0;
  pLVar31->loaded_directory_table_size = 0;
  pLVar31->loaded_directory_table_entry_count = 0;
  (pLVar31->field11_0x50).start = (uint *)0x0;
  (pLVar31->table1_list).eos = (uint *)0x0;
  pLVar31->loaded_directory_table = (LoadedDirectory *)0x0;
  (pLVar31->table1_list).start = (uint *)0x0;
  (pLVar31->table1_list).end = (uint *)0x0;
  pLVar31->loaded_table_1_size = 0;
  pLVar31->loaded_table_2_size = 0;
  pLVar31->loaded_t1_entry_count = 0;
  pLVar31->loaded_t2_entry_count = 0;
  pLVar31->loaded_table_1 = (Table1Entry *)0x0;
  pLVar31->loaded_table_2 = (Table2Entry *)0x0;
  pLVar31->field12_0x68 = 0;
  paVar32 = (astruct_6 *)je_aligned_alloc(0x10,0x70);
  if (paVar32 == (astruct_6 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x70;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (paVar32 = (astruct_6 *)je_aligned_alloc(0x10,0x70), paVar32 != (astruct_6 *)0x0))
      goto LAB_710374ff64;
    }
    paVar32 = (astruct_6 *)0x0;
  }
LAB_710374ff64:
  *(undefined8 *)&paVar32->field2_0x10 = 0;
  paVar32->field9_0x18 = 0;
  paVar32->field2_0x10 = 1;
  paVar32->field16_0x50 = 0x3f800000;
  paVar32->field_0x12 = 0;
  paVar32->field23_0x68 = 0;
  paVar32->field10_0x20 = 0;
  paVar32->field11_0x28 = 0;
  paVar32->field0_0x0 = 0;
  paVar32->field1_0x8 = 0;
  paVar32->field14_0x40 = 0;
  paVar32->field15_0x48 = 0;
  paVar32->field12_0x30 = 0;
  paVar32->field13_0x38 = 0;
  paVar32->field21_0x58 = &paVar32->field21_0x58;
  paVar32->field22_0x60 = &paVar32->field21_0x58;
  pLVar31->field20_0x70 = paVar32;
  pLVar33 = (LoadedData *)je_aligned_alloc(0x10,0x18);
  if (pLVar33 == (LoadedData *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x18;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pLVar33 = (LoadedData *)je_aligned_alloc(0x10,0x18), pLVar33 != (LoadedData *)0x0))
      goto LAB_710374fff8;
    }
    pLVar33 = (LoadedData *)0x0;
  }
LAB_710374fff8:
  loaded_arc = (LoadedArc *)je_aligned_alloc(0x10,0x140);
  if (loaded_arc == (LoadedArc *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x140;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (loaded_arc = (LoadedArc *)je_aligned_alloc(0x10,0x140), loaded_arc != (LoadedArc *)0x0))
      goto LAB_7103750054;
    }
    loaded_arc = (LoadedArc *)0x0;
  }
LAB_7103750054:
  (loaded_arc->extra_entry_vector).end = (ExtraEntry *)0x0;
  (loaded_arc->extra_entry_vector).eos = (ExtraEntry *)0x0;
  loaded_arc->extra_folder_offsets = (DirectoryOffset *)0x0;
  (loaded_arc->extra_entry_vector).start = (ExtraEntry *)0x0;
  loaded_arc->unk_offset_2 = (FileSystemHeader *)0x0;
  *(undefined4 *)&loaded_arc->version = 0xffff;
  loaded_arc->extra_buckets = (FileInfoBucket *)0x0;
  loaded_arc->extra_entries = (ExtraEntry *)0x0;
  loaded_arc->stream_file_indices = (ulonglong *)0x0;
  loaded_arc->stream_datas = (StreamData *)0x0;
  loaded_arc->stream_hash_to_entries = (HashToIndex *)0x0;
  loaded_arc->stream_entries = (StreamEntry *)0x0;
  loaded_arc->stream_header = (StreamHeader *)0x0;
  loaded_arc->quick_dirs = (void *)0x0;
  loaded_arc->file_datas = (FileData *)0x0;
  loaded_arc->unk_section = (void *)0x0;
  loaded_arc->file_infos = (FileInfoV2 *)0x0;
  loaded_arc->file_info_to_datas = (FileInfoToFileData *)0x0;
  loaded_arc->folder_offsets = (DirectoryOffset *)0x0;
  loaded_arc->folder_child_hashes = (HashToIndex *)0x0;
  loaded_arc->directory_hash_to_info_group = (HashToIndex *)0x0;
  loaded_arc->dir_info = (DirInfo *)0x0;
  loaded_arc->file_paths = (FilePath *)0x0;
  loaded_arc->file_info_indices = (FileInfoIndex *)0x0;
  loaded_arc->file_info_buckets = (FileInfoBucket *)0x0;
  loaded_arc->file_hash_to_path_index = (HashToIndex *)0x0;
  loaded_arc->fs_header = (FileSystemHeader *)0x0;
  loaded_arc->region_entries = (void *)0x0;
  if (LoadedTables != (LoadedTables *)0x0) {
    piVar34 = (int *)&local_430;
    local_430 = (undefined **)
                (CONCAT44(local_430._4_4_,LoadedTables->loaded_data->arc->fs_header->version) &
                0xffffffff00ffffff);
    something_file_version(piVar34);
    *(int *)&loaded_arc->version = (int)piVar34;
  }
  *(undefined4 *)((long)&loaded_arc->version + 4) = 0xffffffff;
  loaded_arc->loaded_fs_search_ = (LoadedFsSearch *)0x0;
  loaded_arc->region_tree = (undefined *)0x0;
  loaded_arc->region_count = (undefined *)0x0;
  loaded_arc->magic = 0;
  loaded_arc->unk_data = (undefined *)0x0;
  *(undefined ***)&loaded_arc->field_0x128 = &loaded_arc->region_tree;
  loaded_arc->fs_search_offset = 0;
  loaded_arc->unk_offset = 0;
  loaded_arc->file_data_offset_2 = 0;
  loaded_arc->fs_offset = 0;
  loaded_arc->music_data_offset = 0;
  loaded_arc->file_data_offset = 0;
  pLVar33->arc = loaded_arc;
  pLVar35 = (LoadedFsSearch *)je_aligned_alloc(0x10,0x38);
  if (pLVar35 == (LoadedFsSearch *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x38;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (pLVar35 = (LoadedFsSearch *)je_aligned_alloc(0x10,0x38), pLVar35 != (LoadedFsSearch *)0x0)
         ) goto LAB_7103750144;
    }
    pLVar35 = (LoadedFsSearch *)0x0;
  }
LAB_7103750144:
  pLVar35->idx_to_path_group_idx = (uint *)0x0;
  pLVar35->path_group = (HashGroup *)0x0;
  pLVar35->idx_to_group = (HashGroup *)0x0;
  pLVar35->path_to_idx = (HashToIndex *)0x0;
  pLVar35->header = (FsSearchHeader *)0x0;
  pLVar35->body = (FsSearchBody *)0x0;
  pLVar35->file_path_to_idx = (HashToIndex *)0x0;
  pLVar33->search = pLVar35;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x28);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x28;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x28), puVar24 != (undefined8 *)0x0))
      goto LAB_71037501ac;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_71037501ac:
  puVar24[3] = 0;
  puVar24[4] = 0;
  puVar24[1] = 0;
  puVar24[2] = 0;
  *puVar24 = 0;
  pLVar33->patch = puVar24;
  pLVar31->loaded_data = pLVar33;
  pLVar31->version = 0xffff;
  if (LoadedTables != (LoadedTables *)0x0) {
    piVar34 = (int *)&local_430;
    local_430 = (undefined **)
                (CONCAT44(local_430._4_4_,LoadedTables->loaded_data->arc->fs_header->version) &
                0xffffffff00ffffff);
    something_file_version(piVar34);
    pLVar31->version = (dword)piVar34;
  }
  extra_entry_index = (pLVar31->table1_list).start;
  LoadedTables = pLVar31;
  if ((ulong)((long)(pLVar31->table1_list).eos - (long)extra_entry_index >> 2) < 0x800) {
    sVar23 = (long)(pLVar31->table1_list).end - (long)extra_entry_index;
    puVar36 = (uint *)je_aligned_alloc(0x10,0x2000);
    if (puVar36 == (uint *)0x0) {
      if (GlobalAllocator != (void *)0x0) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
        local_430 = (undefined **)0x2000;
                    /* WARNING: Load size is inaccurate */
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if (((curr_extra_entry_idx & 1) != 0) &&
           (puVar36 = (uint *)je_aligned_alloc(0x10,0x2000), puVar36 != (uint *)0x0))
        goto LAB_7103750278;
      }
      puVar36 = (uint *)0x0;
    }
LAB_7103750278:
    if (0 < (long)sVar23) {
      memcpy(puVar36,extra_entry_index,sVar23);
    }
    (pLVar31->table1_list).start = puVar36;
    (pLVar31->table1_list).end = puVar36 + ((long)sVar23 >> 2);
    (pLVar31->table1_list).eos = puVar36 + 0x800;
    if (extra_entry_index != (uint *)0x0) {
      free_default(extra_entry_index);
    }
  }
  extra_entry_index = (pLVar31->field11_0x50).start;
  if ((ulong)((long)(pLVar31->field11_0x50).eos - (long)extra_entry_index >> 2) < 0x200) {
    sVar23 = (long)(pLVar31->field11_0x50).end - (long)extra_entry_index;
    puVar36 = (uint *)je_aligned_alloc(0x10,0x800);
    if (puVar36 == (uint *)0x0) {
      if (GlobalAllocator != (void *)0x0) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
        local_430 = (undefined **)0x800;
                    /* WARNING: Load size is inaccurate */
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if (((curr_extra_entry_idx & 1) != 0) &&
           (puVar36 = (uint *)je_aligned_alloc(0x10,0x800), puVar36 != (uint *)0x0))
        goto LAB_7103750330;
      }
      puVar36 = (uint *)0x0;
    }
LAB_7103750330:
    if (0 < (long)sVar23) {
      memcpy(puVar36,extra_entry_index,sVar23);
    }
    (pLVar31->field11_0x50).start = puVar36;
    (pLVar31->field11_0x50).end = puVar36 + ((long)sVar23 >> 2);
    (pLVar31->field11_0x50).eos = puVar36 + 0x200;
    if (extra_entry_index != (uint *)0x0) {
      free_default(extra_entry_index);
    }
  }
  paVar32 = pLVar31->field20_0x70;
  fVar69 = DAT_7104470a50 / (float)paVar32->field16_0x50;
  paVar32->field0_0x0 = uVar56;
  FUN_7103541490(&paVar32->field12_0x30,(long)fVar69);
  local_220 = &PTR_LAB_710522da68;
  local_200 = &local_220;
  local_218 = paVar32;
  FUN_71037c7d50(&local_430,&local_220);
  if (&local_430 == local_410) {
    pcVar44 = *(code **)(*local_410 + 0x20);
LAB_71037503d8:
    (*pcVar44)();
  }
  else if (local_410 != (long *)0x0) {
    pcVar44 = *(code **)(*local_410 + 0x28);
    goto LAB_71037503d8;
  }
  if (&local_220 == local_200) {
    pcVar44 = *(code **)(*local_200 + 0x20);
LAB_7103750404:
    (*pcVar44)();
  }
  else if (local_200 != (long *)0x0) {
    pcVar44 = *(code **)(*local_200 + 0x28);
    goto LAB_7103750404;
  }
  local_220 = &PTR_LAB_710522dab0;
  local_218 = paVar32;
  local_200 = &local_220;
  FUN_710353af00(&local_220);
  if (&local_220 == local_200) {
    pcVar44 = *(code **)(*local_200 + 0x20);
LAB_710375044c:
    (*pcVar44)();
  }
  else if (local_200 != (long *)0x0) {
    pcVar44 = *(code **)(*local_200 + 0x28);
    goto LAB_710375044c;
  }
  pcVar58 = pRVar26->data_arc_string;
  *pcVar58 = '\0';
  pRVar26->loaded_tables = pLVar31;
  pRVar26->unk_region_idx = 0xffffffff;
  pRVar26->regular_region_idx = 0xffffffff;
  pRVar26->loading_thread_state_ = 0;
  pRVar26->some_sort_of_state_ = 0;
  pRVar26->current_index_loaded_status_ = false;
  pRVar26->is_loader_thread_running = 0;
  pRVar26->field_0xe7 = 0;
  uVar17 = *(ushort *)((long)param_1 + 0x19a);
  curr_extra_entry_idx = (ulong)uVar17;
  *(undefined2 *)&pRVar26->field59_0x1e8 = 0;
  pcVar64 = pcVar58;
  if (curr_extra_entry_idx != 0) {
    pcVar64 = (char *)((long)param_1 + 0x9a);
    if (uVar17 == 1) {
      file_data_count_2 = 0;
    }
    else {
      file_data_count_2 = 0;
      extra_curr_pos = (curr_extra_entry_idx & 1) - curr_extra_entry_idx;
      do {
        cVar14 = *pcVar64;
        *(short *)&pRVar26->field59_0x1e8 = (short)file_data_count_2 + 1;
        extra_curr_pos = extra_curr_pos + 2;
        pRVar26->data_arc_string[file_data_count_2] = cVar14;
        uVar18 = *(ushort *)&pRVar26->field59_0x1e8;
        cVar14 = pcVar64[1];
        pcVar64 = pcVar64 + 2;
        *(ushort *)&pRVar26->field59_0x1e8 = uVar18 + 1;
        pRVar26->data_arc_string[uVar18] = cVar14;
        file_data_count_2 = (ulong)*(ushort *)&pRVar26->field59_0x1e8;
      } while (extra_curr_pos != 0);
    }
    if ((uVar17 & 1) != 0) {
      cVar14 = *pcVar64;
      *(short *)&pRVar26->field59_0x1e8 = (short)file_data_count_2 + 1;
      pRVar26->data_arc_string[file_data_count_2] = cVar14;
      file_data_count_2 = (ulong)*(ushort *)&pRVar26->field59_0x1e8;
    }
    pcVar64 = pRVar26->data_arc_string + file_data_count_2;
  }
  *pcVar64 = '\0';
  pRVar26->data_arc_file = (File_NX **)0x0;
  *(undefined4 *)&pRVar26->buffer_size = *(undefined4 *)(param_1 + 0x76);
  pRVar26->buffer_arr_idx = 0;
  pRVar26->processing_file_idx_start = 0;
  pRVar26->processing_type = 0;
  pRVar26->processing_file_idx_curr = 0;
  pRVar26->processing_file_idx_count = 0;
  pRVar26->off_into_read = 0;
  pRVar26->data_ptr = (undefined *)0x0;
  *(undefined1 **)&pRVar26->processing_dir_idx_start = &DAT_ffffff00ffffff;
  *(undefined1 **)&pRVar26->current_index_ = &DAT_ffffff00ffffff;
  pRVar26->is_updated = false;
  ppFVar37 = (File_NX **)je_aligned_alloc(0x10,8);
  if (ppFVar37 == (File_NX **)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x8;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (ppFVar37 = (File_NX **)je_aligned_alloc(0x10,8), ppFVar37 != (File_NX **)0x0))
      goto LAB_7103750598;
    }
    ppFVar37 = (File_NX **)0x0;
  }
LAB_7103750598:
  FUN_710353a3c0(ppFVar37);
  iVar21 = (int)pRVar26->buffer_size;
  pRVar26->data_arc_file = ppFVar37;
  if (iVar21 == 0) {
    iVar21 = 0x400000;
    *(undefined4 *)&pRVar26->buffer_size = 0x400000;
  }
  file_data_count = iVar21 << 1;
  if (file_data_count == 0) {
    file_data_count = 1;
  }
  curr_extra_entry_idx = (ulong)file_data_count;
  pvVar25 = je_aligned_alloc(4,curr_extra_entry_idx);
  if ((pvVar25 == (void *)0x0) && (pvVar25 = GlobalAllocator, GlobalAllocator != (void *)0x0)) {
    local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
    local_430 = (undefined **)curr_extra_entry_idx;
    file_data_count_2 =
         (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
    if ((file_data_count_2 & 1) == 0) {
      pvVar25 = (void *)0x0;
    }
    else {
      pvVar25 = je_aligned_alloc(4,curr_extra_entry_idx);
    }
  }
  pRVar26->buffer_arr[0] = pvVar25;
  pRVar26->buffer_arr[1] = (void *)((long)pvVar25 + (ulong)(uint)pRVar26->buffer_size);
  puVar57 = *(undefined8 **)&pRVar26->field_0x50;
  *puVar57 = 0x20;
  *(undefined4 *)(puVar57 + 1) = 0x1000;
  local_90 = (long *)0x0;
  local_c0 = (long *)0x0;
  local_f0 = (long *)0x0;
  local_480 = (long *)0x0;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x60);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x60;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x60), puVar24 != (undefined8 *)0x0))
      goto LAB_7103750794;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_7103750794:
  puVar24[10] = 0;
  *(undefined4 *)(puVar24 + 4) = 0;
  puVar24[2] = 0;
  puVar24[3] = 0;
  *puVar24 = 0;
  puVar24[1] = 0;
  plVar60 = (long *)puVar57[10];
  if (plVar60 == (long *)0x0) {
    local_410 = (long *)0x0;
    plVar60 = (long *)puVar57[0x10];
joined_r0x0071037507f8:
    if (plVar60 == (long *)0x0) goto LAB_71037507fc;
LAB_71037507d0:
    if (puVar57 + 0xc == plVar60) {
      local_200 = &local_220;
      (**(code **)(*plVar60 + 0x18))(plVar60,&local_220);
    }
    else {
      local_200 = (long *)(**(code **)(*plVar60 + 0x10))();
    }
  }
  else {
    if (puVar57 + 6 == plVar60) {
      local_410 = &local_430;
      (**(code **)(*plVar60 + 0x18))(plVar60,&local_430);
      plVar60 = (long *)puVar57[0x10];
      goto joined_r0x0071037507f8;
    }
    local_410 = (long *)(**(code **)(*plVar60 + 0x10))();
    plVar60 = (long *)puVar57[0x10];
    if (plVar60 != (long *)0x0) goto LAB_71037507d0;
LAB_71037507fc:
    local_200 = (long *)0x0;
  }
  FUN_7103546210(puVar24,0x20,0x1000,&local_430,&local_220);
  if (&local_220 == local_200) {
    pcVar44 = *(code **)(*local_200 + 0x20);
LAB_7103750880:
    (*pcVar44)();
  }
  else if (local_200 != (long *)0x0) {
    pcVar44 = *(code **)(*local_200 + 0x28);
    goto LAB_7103750880;
  }
  if (&local_430 == local_410) {
    pcVar44 = *(code **)(*local_410 + 0x20);
LAB_71037508ac:
    (*pcVar44)();
  }
  else if (local_410 != (long *)0x0) {
    pcVar44 = *(code **)(*local_410 + 0x28);
    goto LAB_71037508ac;
  }
  puVar10 = (undefined8 *)puVar57[3];
  if (puVar10 == (undefined8 *)puVar57[4]) {
    pvVar25 = (void *)puVar57[2];
    sVar23 = (long)puVar10 - (long)pvVar25;
    curr_extra_entry_idx = ((long)sVar23 >> 3) + 1;
    if (curr_extra_entry_idx >> 0x3d != 0) {
                    /* WARNING: Subroutine does not return */
      std::__1::__vector_base_common<true>::__throw_length_error();
    }
    extra_curr_pos = (long)puVar57[4] - (long)pvVar25;
    if ((ulong)(extra_curr_pos >> 3) < 0xfffffffffffffff) {
      file_data_count_2 = extra_curr_pos >> 2;
      if (curr_extra_entry_idx <= file_data_count_2) {
        curr_extra_entry_idx = file_data_count_2;
      }
      if (curr_extra_entry_idx != 0) {
        if (curr_extra_entry_idx >> 0x3d != 0) {
                    /* WARNING: Subroutine does not return */
          abort();
        }
        goto LAB_7103750920;
      }
LAB_7103750980:
      __dest = (void *)0x0;
    }
    else {
      curr_extra_entry_idx = 0x1fffffffffffffff;
LAB_7103750920:
      size = curr_extra_entry_idx * 8;
      if (size == 0) {
        size = 1;
      }
      __dest = je_aligned_alloc(0x10,size);
      if (__dest == (void *)0x0) {
        if (GlobalAllocator != (void *)0x0) {
          local_6c[0] = 0;
                    /* WARNING: Load size is inaccurate */
          local_78 = size;
          file_data_count_2 =
               (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,local_6c,&local_78);
          if (((file_data_count_2 & 1) != 0) &&
             (__dest = je_aligned_alloc(0x10,size), __dest != (void *)0x0)) goto LAB_7103750984;
        }
        goto LAB_7103750980;
      }
    }
LAB_7103750984:
    puVar10 = (undefined8 *)((long)__dest + ((long)sVar23 >> 3) * 8);
    *puVar10 = puVar24;
    if (0 < (long)sVar23) {
      memcpy(__dest,pvVar25,sVar23);
    }
    puVar57[2] = __dest;
    puVar57[3] = puVar10 + 1;
    puVar57[4] = (void *)((long)__dest + curr_extra_entry_idx * 8);
    if (pvVar25 != (void *)0x0) {
      free_default(pvVar25);
    }
  }
  else {
    *puVar10 = puVar24;
    puVar57[3] = puVar57[3] + 8;
  }
  if ((long *)local_b0 == local_90) {
    pcVar44 = *(code **)(*local_90 + 0x20);
LAB_71037509f0:
    (*pcVar44)();
  }
  else if (local_90 != (long *)0x0) {
    pcVar44 = *(code **)(*local_90 + 0x28);
    goto LAB_71037509f0;
  }
  if ((long *)local_4a0 == local_480) {
    pcVar44 = *(code **)(*local_480 + 0x20);
LAB_7103750a1c:
    (*pcVar44)();
  }
  else if (local_480 != (long *)0x0) {
    pcVar44 = *(code **)(*local_480 + 0x28);
    goto LAB_7103750a1c;
  }
  if (local_f0 != (long *)0x0) {
    (**(code **)(*local_f0 + 0x28))();
  }
  if (local_c0 != (long *)0x0) {
    (**(code **)(*local_c0 + 0x28))();
  }
  local_430 = &PTR_FUN_710522daf8;
  local_428 = ResUpdateThread;
  local_420 = (void *)0x0;
  pRStack_418 = pRVar26;
  local_410 = &local_430;
  FUN_710353c5d0(pRVar26->res_update_thread,&local_430,*(undefined4 *)((long)param_1 + 0x3b4),
                 *(undefined4 *)(param_1 + 0x77),"ResUpdateThread",0x40000);
  if (&local_430 == local_410) {
    pcVar44 = *(code **)(*local_410 + 0x20);
LAB_7103750aac:
    (*pcVar44)();
  }
  else if (local_410 != (long *)0x0) {
    pcVar44 = *(code **)(*local_410 + 0x28);
    goto LAB_7103750aac;
  }
  local_430 = &PTR_FUN_710522daf8;
  local_428 = ResLoadingThread;
  local_420 = (void *)0x0;
  pRStack_418 = pRVar26;
  local_410 = &local_430;
  FUN_710353c5d0(pRVar26->res_loading_thread,&local_430,*(undefined4 *)((long)param_1 + 0x3bc),
                 *(undefined4 *)(param_1 + 0x78),"ResLoadingThread",0x40000);
  if (&local_430 == local_410) {
    pcVar44 = *(code **)(*local_410 + 0x20);
LAB_7103750b0c:
    (*pcVar44)();
  }
  else if (local_410 != (long *)0x0) {
    pcVar44 = *(code **)(*local_410 + 0x28);
    goto LAB_7103750b0c;
  }
  local_430 = &PTR_FUN_710522daf8;
  local_428 = ResInflateThread;
  local_420 = (void *)0x0;
  pRStack_418 = pRVar26;
  local_410 = &local_430;
  FUN_710353c5d0(pRVar26->res_inflate_thread,&local_430,*(undefined4 *)((long)param_1 + 0x3c4),
                 *(undefined4 *)(param_1 + 0x79),"ResInflateThread",0x40000);
  if (&local_430 == local_410) {
    pcVar44 = *(code **)(*local_410 + 0x20);
LAB_7103750b6c:
    (*pcVar44)();
  }
  else if (local_410 != (long *)0x0) {
    pcVar44 = *(code **)(*local_410 + 0x28);
    goto LAB_7103750b6c;
  }
  ResService = pRVar26;
  if ((*(short *)&pRVar26->field59_0x1e8 != 0) &&
     (curr_extra_entry_idx = FUN_710353a500(pRVar26->data_arc_file,pcVar58),
     (curr_extra_entry_idx & 1) != 0)) {
    pLVar31 = pRVar26->loaded_tables;
    pLVar33 = pLVar31->loaded_data;
    loaded_arc = pLVar33->arc;
    FUN_710353a3c0(&local_220);
    curr_extra_entry_idx = FUN_710353a500(&local_220,pcVar58);
    if ((curr_extra_entry_idx & 1) == 0) {
LAB_7103750dfc:
      bVar20 = false;
      goto LAB_7103750e00;
    }
    if (loaded_arc->unk_offset_2 != (FileSystemHeader *)0x0) {
      free_default(loaded_arc->unk_offset_2);
      loaded_arc->unk_offset_2 = (FileSystemHeader *)0x0;
    }
    if (loaded_arc->loaded_fs_search_ != (LoadedFsSearch *)0x0) {
      free_default(loaded_arc->loaded_fs_search_);
      loaded_arc->loaded_fs_search_ = (LoadedFsSearch *)0x0;
    }
    if (loaded_arc->unk_data != (undefined *)0x0) {
      free_default(loaded_arc->unk_data);
      loaded_arc->unk_data = (undefined *)0x0;
    }
    ppuVar61 = local_220;
    if (*(char *)((long)local_220 + 0x22c) != '\0') {
      extra_curr_pos = FUN_71037c58c0(local_220,loaded_arc,0x38);
      if ((extra_curr_pos == 0x38) && (loaded_arc->magic == 0xabcdef9876543210)) {
        fs_header = (FileSystemHeader *)FUN_7103540a90(&local_220,loaded_arc->fs_offset);
        loaded_arc->unk_offset_2 = fs_header;
        if (fs_header != (FileSystemHeader *)0x0) {
          if (loaded_arc->fs_search_offset != 0) {
            pLVar35 = (LoadedFsSearch *)FUN_7103540a90(&local_220);
            loaded_arc->loaded_fs_search_ = pLVar35;
            if (pLVar35 == (LoadedFsSearch *)0x0) goto LAB_7103750dfc;
          }
          if (loaded_arc->unk_offset != 0) {
            puVar30 = (undefined *)FUN_7103540a90(&local_220);
            loaded_arc->unk_data = puVar30;
            if (puVar30 == (undefined *)0x0) goto LAB_7103750dfc;
          }
          if (*(char *)((long)ppuVar61 + 0x22c) != '\0') {
            (**(code **)(*ppuVar61 + 0x30))(&local_430,ppuVar61);
            *(undefined1 *)((long)ppuVar61 + 0x22c) = 0;
          }
          fs_header = loaded_arc->unk_offset_2;
          loaded_arc->fs_header = fs_header;
          loaded_arc->region_entries = fs_header->field24_0x58;
          pSVar45 = (StreamHeader *)(fs_header->field24_0x58 + fs_header->regional_count_1);
          loaded_arc->stream_header = pSVar45;
          loaded_arc->quick_dirs = pSVar45 + 1;
          pHVar49 = (HashToIndex *)(&pSVar45[1].UnkCount + (ulong)pSVar45->UnkCount * 3);
          loaded_arc->stream_hash_to_entries = pHVar49;
          pSVar5 = (StreamEntry *)(pHVar49 + pSVar45->StreamHashCount);
          loaded_arc->stream_entries = pSVar5;
          file_data_count = pSVar45->StreamHashCount;
          loaded_arc->stream_file_indices = (ulonglong *)(pSVar5 + file_data_count);
          pSVar6 = (StreamData *)(&pSVar5[file_data_count].Hash + pSVar45->StreamIndexToOffsetCount)
          ;
          loaded_arc->stream_datas = pSVar6;
          pSVar6 = pSVar6 + pSVar45->StreamOffsetCount;
          loaded_arc->file_info_buckets = (FileInfoBucket *)pSVar6;
          pHVar49 = (HashToIndex *)(&pSVar6->Offset + *(uint *)((long)&pSVar6->Size + 4));
          loaded_arc->file_hash_to_path_index = pHVar49;
          pFVar7 = (FilePath *)(pHVar49 + fs_header->file_info_path_count);
          loaded_arc->file_paths = pFVar7;
          file_data_count = fs_header->file_info_path_count;
          loaded_arc->file_info_indices = (FileInfoIndex *)(pFVar7 + file_data_count);
          pHVar49 = &pFVar7[file_data_count].Path + fs_header->file_info_index_count;
          loaded_arc->directory_hash_to_info_group = pHVar49;
          folder_count = fs_header->folder_count;
          loaded_arc->dir_info = (DirInfo *)(pHVar49 + folder_count);
          pDVar55 = (DirInfo *)(pHVar49 + folder_count) + fs_header->folder_count;
          loaded_arc->folder_offsets = (DirectoryOffset *)pDVar55;
          folder_child_hashes =
               (HashToIndex *)
               ((long)&pDVar55->FullPath +
               (ulong)(fs_header->folder_offset_count_2 + fs_header->folder_offset_count_1 +
                      fs_header->extra_folder) * 0x1c);
          loaded_arc->folder_child_hashes = folder_child_hashes;
          pFVar46 = (FileInfoV2 *)(folder_child_hashes + fs_header->hash_folder_count);
          loaded_arc->file_infos = pFVar46;
          pFVar50 = pFVar46 + (fs_header->file_data_count_2 + fs_header->file_info_count +
                              fs_header->file_info_extra_count);
          loaded_arc->file_info_to_datas = (FileInfoToFileData *)pFVar50;
          file_datas = (FileData *)
                       (&pFVar50->file_path_idx +
                       (ulong)(fs_header->file_data_count_2 + fs_header->file_info_to_data_count +
                              fs_header->file_info_to_data_extra_count) * 3);
          loaded_arc->file_datas = file_datas;
          file_data_count = fs_header->file_data_count;
          file_data_count2 = fs_header->file_data_count_2;
          file_data_extra_count = fs_header->file_data_extra_count;
          loaded_arc->unk_section =
               file_datas + (file_data_count2 + file_data_count + file_data_extra_count);
          if (fs_header->extra_count != 0) {
            pFVar8 = (FileInfoBucket *)
                     (&file_datas[file_data_count2 + file_data_count + file_data_extra_count].Offset
                     + (ulong)fs_header->padding * 2);
            pEVar54 = (ExtraEntry *)(pFVar8 + 1);
            loaded_arc->extra_buckets = pFVar8;
            loaded_arc->extra_entries = pEVar54;
            fs_header_cpy = loaded_arc->fs_header;
            extra_entry_index = &pFVar8->Size;
            if (*extra_entry_index != 0) {
              ppuVar61 = &pEVar54->field0_0x0 + (ulong)*extra_entry_index * 4;
              extra_curr_pos = 0;
              curr_extra_entry_idx = 1;
              do {
                file_data_count = fs_header_cpy->file_info_to_data_count;
                file_data_count2 = fs_header_cpy->file_data_count;
                file_info_count = fs_header_cpy->file_info_count;
                file_data_count_2 = (ulong)fs_header_cpy->file_data_count_2;
                puVar36 = (uint *)((long)ppuVar61 +
                                  (ulong)*(uint *)((long)&pEVar54->field0_0x0 + extra_curr_pos + 4)
                                  * 0x14);
                file_data_extra_count = *(uint *)((long)&pEVar54->file_path + extra_curr_pos);
                uVar13 = *puVar36;
                pEVar54 = (loaded_arc->extra_entry_vector).end;
                pEVar12 = (loaded_arc->extra_entry_vector).eos;
                if (pEVar54 < pEVar12) {
                  pEVar54->field0_0x0 = (undefined *)ppuVar61;
                  pEVar54->buckets = (undefined *)puVar36;
                  pEVar54->file_path = (HashToIndex *)(puVar36 + (ulong)uVar13 * 2 + 2);
                  pEVar54->file_info = pFVar46 + file_data_count_2 + file_info_count;
                  pEVar54->file_info_to_data =
                       (FileInfoToFileData *)
                       (&pFVar50->file_path_idx + (file_data_count + file_data_count_2) * 3);
                  pEVar54->file_data = file_datas + file_data_count2 + file_data_count_2;
                  (loaded_arc->extra_entry_vector).end = (loaded_arc->extra_entry_vector).end + 1;
                }
                else {
                  __src = (loaded_arc->extra_entry_vector).start;
                  sVar23 = (long)pEVar54 - (long)__src;
                  uVar52 = 0x555555555555555;
                  uVar40 = ((long)sVar23 >> 4) * -0x5555555555555555 + 1;
                  if (0x555555555555555 < uVar40) {
                    /* WARNING: Subroutine does not return */
                    std::__1::__vector_base_common<true>::__throw_length_error();
                  }
                  lVar38 = (long)pEVar12 - (long)__src >> 4;
                  if ((ulong)(lVar38 * -0x5555555555555555) < 0x2aaaaaaaaaaaaaa) {
                    uVar51 = lVar38 * 0x5555555555555556;
                    uVar52 = uVar40;
                    if (uVar40 <= uVar51) {
                      uVar52 = uVar51;
                    }
                    if (uVar52 != 0) goto LAB_7103750f28;
                    pvVar25 = (void *)0x0;
                  }
                  else {
LAB_7103750f28:
                    ppuVar65 = (undefined **)(uVar52 * 0x30);
                    if (ppuVar65 == (undefined **)0x0) {
                      ppuVar65 = (undefined **)0x1;
                    }
                    pvVar25 = je_aligned_alloc(0x10,(size_t)ppuVar65);
                    if (pvVar25 == (void *)0x0) {
                      if (GlobalAllocator != (void *)0x0) {
                        local_4a0._0_8_ = local_4a0._0_8_ & 0xffffffff00000000;
                    /* WARNING: Load size is inaccurate */
                        local_430 = ppuVar65;
                        uVar40 = (**(code **)(*GlobalAllocator + 0x30))
                                           (GlobalAllocator,local_4a0,&local_430);
                        if (((uVar40 & 1) != 0) &&
                           (pvVar25 = je_aligned_alloc(0x10,(size_t)ppuVar65),
                           pvVar25 != (void *)0x0)) goto LAB_7103750f90;
                      }
                      pvVar25 = (void *)0x0;
                    }
                  }
LAB_7103750f90:
                  lVar38 = SUB168(SEXT816((long)sVar23) * SEXT816(-0x2aaaaaaaaaaaaaab),8);
                  puVar24 = (undefined8 *)((long)pvVar25 + ((long)sVar23 >> 4) * 0x10);
                  puVar24[2] = (HashToIndex *)(puVar36 + (ulong)uVar13 * 2 + 2);
                  puVar24[3] = pFVar46 + file_data_count_2 + file_info_count;
                  *puVar24 = ppuVar61;
                  puVar24[1] = puVar36;
                  puVar24[4] = (FileInfoToFileData *)
                               (&pFVar50->file_path_idx + (file_data_count + file_data_count_2) * 3)
                  ;
                  puVar24[5] = file_datas + file_data_count2 + file_data_count_2;
                  if (0 < (long)sVar23) {
                    memcpy((ExtraEntry *)(puVar24 + ((lVar38 >> 3) - (lVar38 >> 0x3f)) * 6),__src,
                           sVar23);
                  }
                  (loaded_arc->extra_entry_vector).start =
                       (ExtraEntry *)(puVar24 + ((lVar38 >> 3) - (lVar38 >> 0x3f)) * 6);
                  (loaded_arc->extra_entry_vector).end = (ExtraEntry *)(puVar24 + 6);
                  (loaded_arc->extra_entry_vector).eos =
                       (ExtraEntry *)((long)pvVar25 + uVar52 * 0x30);
                  if (__src != (ExtraEntry *)0x0) {
                    free_default(__src);
                  }
                }
                extra_entry_index = &loaded_arc->extra_buckets->Size;
                if (*extra_entry_index <= curr_extra_entry_idx) goto LAB_7103751898;
                pEVar54 = loaded_arc->extra_entries;
                pFVar46 = loaded_arc->file_infos;
                pFVar50 = (FileInfoV2 *)loaded_arc->file_info_to_datas;
                file_datas = loaded_arc->file_datas;
                ppuVar61 = (undefined **)((long)puVar36 + (ulong)file_data_extra_count);
                curr_extra_entry_idx = curr_extra_entry_idx + 1;
                extra_curr_pos = extra_curr_pos + 0x20;
              } while( true );
            }
            goto LAB_71037518a4;
          }
          goto LAB_71037518c4;
        }
      }
      goto LAB_7103750dfc;
    }
    bVar20 = false;
    cVar14 = *(char *)((long)local_220 + 0x22c);
    goto joined_r0x007103750e08;
  }
LAB_71037512cc:
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x40;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40), puVar24 != (undefined8 *)0x0))
      goto LAB_7103751320;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_7103751320:
  puVar24[2] = &PTR_FUN_710523b228;
  puVar24[6] = puVar24 + 2;
  *puVar24 = &DAT_71059394d0;
  puVar24[1] = DAT_71059394d8;
  *DAT_71059394d8 = puVar24;
  DAT_71059394e0 = DAT_71059394e0 + 1;
  DAT_71059394d8 = puVar24;
  puVar24 = DAT_71059394e8;
  if (DAT_71059394e8 == (undefined8 *)0x0) {
    puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x198);
    if (puVar24 == (undefined8 *)0x0) {
      if (GlobalAllocator != (void *)0x0) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
        local_430 = (undefined **)0x198;
                    /* WARNING: Load size is inaccurate */
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if (((curr_extra_entry_idx & 1) != 0) &&
           (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x198), puVar24 != (undefined8 *)0x0))
        goto LAB_71037513b4;
      }
      puVar24 = (undefined8 *)0x0;
    }
LAB_71037513b4:
    puVar24[0x2e] = 0;
    puVar24[4] = 0;
    puVar24[5] = 0;
    *puVar24 = 0;
    puVar24[1] = 0;
    puVar24[2] = 0;
    puVar24[3] = &PTR_LAB_710522ec18;
    puVar24[8] = 0;
    puVar24[9] = 0;
    puVar24[6] = 0;
    puVar24[7] = &PTR_LAB_710522ec18;
    puVar24[0xc] = 0;
    puVar24[0xd] = 0;
    puVar24[10] = 0;
    puVar24[0xb] = &PTR_LAB_710522ec18;
    puVar24[0x10] = 0;
    puVar24[0x11] = 0;
    puVar24[0xe] = 0;
    puVar24[0xf] = &PTR_LAB_710522ec18;
    puVar24[0x14] = 0;
    puVar24[0x15] = 0;
    puVar24[0x12] = 0;
    puVar24[0x13] = &PTR_LAB_710522ec18;
    puVar24[0x18] = 0;
    puVar24[0x19] = 0;
    puVar24[0x16] = 0;
    puVar24[0x17] = &PTR_LAB_710522ec18;
    puVar24[0x1c] = 0;
    puVar24[0x1d] = 0;
    puVar24[0x1a] = 0;
    puVar24[0x1b] = &PTR_LAB_710522ec18;
    puVar24[0x20] = 0;
    puVar24[0x21] = 0;
    puVar24[0x1e] = 0;
    puVar24[0x1f] = &PTR_LAB_710522ec18;
    puVar24[0x24] = 0;
    puVar24[0x25] = 0;
    puVar24[0x22] = 0;
    puVar24[0x23] = &PTR_LAB_710522ec18;
    puVar24[0x28] = 0;
    puVar24[0x29] = 0;
    puVar24[0x26] = 0;
    puVar24[0x27] = &PTR_LAB_710522ec18;
    puVar24[0x2c] = 0;
    puVar24[0x2d] = 0;
    puVar24[0x2a] = 0;
    puVar24[0x2b] = &PTR_LAB_710522ec18;
    puVar24[0x31] = 0;
    puVar24[0x32] = 0;
    puVar24[0x2f] = &PTR_LAB_710522ec18;
    puVar24[0x30] = 0;
    FUN_71037cbfe0(puVar24,"HBSS@");
    nu::ModuleInitializer<nu::GraphicsModule,nu::GraphicsModuleDesc>::Instance();
    lVar38 = nu::ModuleInitializer<nu::GraphicsModule,nu::GraphicsModuleDesc>::Instance();
    extra_curr_pos = 0;
    pmVar4 = (mutex *)(lVar38 + 0x88);
    ppuVar61 = &PTR_s_phxSystemDebugDrawConstantVS_710523b2a8;
    do {
      pcVar64 = *ppuVar61;
      local_420 = (void *)0x0;
      local_430 = (undefined **)0x0;
      local_428 = (code *)0x0;
      pcVar44 = (code *)strlen(pcVar64);
      if ((code *)0xffffffffffffffef < pcVar44) {
                    /* WARNING: Subroutine does not return */
        std::__1::__basic_string_common<true>::__throw_length_error();
      }
      if (pcVar44 < (code *)0x17) {
        local_430 = (undefined **)CONCAT71(local_430._1_7_,(char)((int)pcVar44 << 1));
        pvVar25 = (void *)((ulong)&local_430 | 1);
        if (pcVar44 != (code *)0x0) goto LAB_7103751514;
      }
      else {
        ppuVar65 = (undefined **)((ulong)(pcVar44 + 0x10) & 0xfffffffffffffff0);
        iVar21 = je_posix_memalign((void **)local_4a0,0x10,(size_t)ppuVar65);
        if (((iVar21 == 0xc) && (DAT_710593b2b0 != (long *)0x0)) &&
           (local_220 = ppuVar65,
           curr_extra_entry_idx = (**(code **)(*DAT_710593b2b0 + 0x30))(DAT_710593b2b0,&local_220),
           (curr_extra_entry_idx & 1) != 0)) {
          je_posix_memalign((void **)local_4a0,0x10,(size_t)ppuVar65);
        }
        if (PTR_VirtualAllocHook_71052a6a78 != (undefined *)0x0) {
          nu::VirtualAllocHook((ulong)ppuVar65,0x10,(void *)local_4a0._0_8_);
        }
        local_430 = (undefined **)((ulong)ppuVar65 | 1);
        local_420 = (void *)local_4a0._0_8_;
        pvVar25 = (void *)local_4a0._0_8_;
        local_428 = pcVar44;
LAB_7103751514:
        memcpy(pvVar25,pcVar64,(size_t)pcVar44);
      }
      *(code *)((long)pvVar25 + (long)pcVar44) = (code)0x0;
      std::__1::mutex::lock(pmVar4);
      lVar39 = FUN_71037e41a0(lVar38 + 0x60,&local_430);
      if (((*(long **)(lVar39 + 0x38) == (long *)0x0) ||
          (**(long **)(lVar39 + 0x38) != *(long *)(lVar39 + 0x40))) ||
         (lVar39 = *(long *)(lVar39 + 0x30), lVar39 == 0)) {
        std::__1::mutex::unlock(pmVar4);
LAB_710375159c:
        plVar60 = (long *)0x0;
        lVar39 = 0;
        *(undefined8 *)((long)puVar24 + extra_curr_pos + 0x20) = 0;
        *(undefined8 *)((long)puVar24 + extra_curr_pos + 0x28) = 0;
      }
      else {
        plVar60 = *(long **)(lVar39 + 8);
        lVar66 = *plVar60;
        std::__1::mutex::unlock(pmVar4);
        if ((plVar60 == (long *)0x0) || (*plVar60 != lVar66)) goto LAB_710375159c;
        *(long *)((long)puVar24 + extra_curr_pos + 0x20) = lVar39;
        plVar60 = *(long **)(lVar39 + 8);
        *(long **)((long)puVar24 + extra_curr_pos + 0x28) = plVar60;
        lVar39 = *plVar60;
      }
      pvVar25 = local_420;
      *(long *)((long)puVar24 + extra_curr_pos + 0x30) = lVar39;
      if (((ulong)local_430 & 1) != 0) {
        if (PTR_VirtualFreeHook_71052a6a70 != (undefined *)0x0) {
          nu::VirtualFreeHook(local_420);
        }
        free_default(pvVar25);
        plVar60 = *(long **)((long)puVar24 + extra_curr_pos + 0x28);
      }
      puVar57 = DAT_71059394e8;
      if ((plVar60 == (long *)0x0) || (*plVar60 != *(long *)((long)puVar24 + extra_curr_pos + 0x30))
         ) {
        FUN_7103753480(puVar24);
        pbVar59 = (byte *)*puVar24;
        puVar57 = puVar24;
        puVar10 = DAT_71059394e8;
        if (pbVar59 != (byte *)0x0) {
          pbVar48 = (byte *)puVar24[1];
          pbVar62 = pbVar59;
          if (pbVar48 != pbVar59) {
            do {
              pbVar62 = pbVar48 + -0x18;
              if ((*pbVar62 & 1) != 0) {
                pvVar25 = *(void **)(pbVar48 + -8);
                if (PTR_VirtualFreeHook_71052a6a70 != (undefined *)0x0) {
                  nu::VirtualFreeHook(pvVar25);
                }
                free_default(pvVar25);
              }
              pbVar48 = pbVar62;
            } while (pbVar59 != pbVar62);
            pbVar62 = (byte *)*puVar24;
          }
          puVar24[1] = pbVar59;
          if (PTR_VirtualFreeHook_71052a6a70 != (undefined *)0x0) {
            nu::VirtualFreeHook(pbVar62);
          }
          free_default(pbVar62);
          puVar10 = DAT_71059394e8;
        }
        goto LAB_71037517dc;
      }
      extra_curr_pos = extra_curr_pos + 0x20;
      ppuVar61 = ppuVar61 + 1;
    } while (extra_curr_pos != 0x180);
    if (DAT_71059394e8 != (undefined8 *)0x0) {
      pbVar59 = (byte *)*DAT_71059394e8;
      puVar10 = puVar24;
      if (pbVar59 != (byte *)0x0) {
        pbVar48 = (byte *)DAT_71059394e8[1];
        pbVar62 = pbVar59;
        DAT_71059394e8 = puVar24;
        if (pbVar48 != pbVar59) {
          do {
            pbVar62 = pbVar48 + -0x18;
            if ((*pbVar62 & 1) != 0) {
              pvVar25 = *(void **)(pbVar48 + -8);
              if (PTR_VirtualFreeHook_71052a6a70 != (undefined *)0x0) {
                nu::VirtualFreeHook(pvVar25);
              }
              free_default(pvVar25);
            }
            pbVar48 = pbVar62;
          } while (pbVar59 != pbVar62);
          pbVar62 = (byte *)*puVar57;
        }
        puVar57[1] = pbVar59;
        if (PTR_VirtualFreeHook_71052a6a70 != (undefined *)0x0) {
          nu::VirtualFreeHook(pbVar62);
        }
        free_default(pbVar62);
        puVar10 = DAT_71059394e8;
      }
LAB_71037517dc:
      DAT_71059394e8 = puVar10;
      free_default(puVar57);
      puVar24 = DAT_71059394e8;
    }
  }
  DAT_71059394e8 = puVar24;
  puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40);
  if (puVar24 == (undefined8 *)0x0) {
    if (GlobalAllocator != (void *)0x0) {
      local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
      local_430 = (undefined **)0x40;
                    /* WARNING: Load size is inaccurate */
      curr_extra_entry_idx =
           (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
      if (((curr_extra_entry_idx & 1) != 0) &&
         (puVar24 = (undefined8 *)je_aligned_alloc(0x10,0x40), puVar24 != (undefined8 *)0x0))
      goto LAB_7103751834;
    }
    puVar24 = (undefined8 *)0x0;
  }
LAB_7103751834:
  puVar24[2] = &PTR_FUN_710523b270;
  puVar24[6] = puVar24 + 2;
  *puVar24 = &DAT_71059394d0;
  puVar24[1] = DAT_71059394d8;
  *DAT_71059394d8 = puVar24;
  DAT_71059394d8 = puVar24;
  DAT_71059394e0 = DAT_71059394e0 + 1;
  return;
LAB_7103751898:
  fs_header_cpy = loaded_arc->fs_header;
  pDVar55 = (DirInfo *)loaded_arc->folder_offsets;
LAB_71037518a4:
  loaded_arc->extra_folder_offsets =
       (DirectoryOffset *)
       ((long)&pDVar55->FullPath +
       (ulong)(fs_header_cpy->folder_offset_count_2 + fs_header_cpy->folder_offset_count_1) * 0x1c);
  *(uint *)((long)&loaded_arc->version + 4) = *extra_entry_index;
LAB_71037518c4:
  ppuVar61 = &loaded_arc->region_tree;
  FUN_71004b0680(loaded_arc->region_tree);
  loaded_arc->region_tree = (undefined *)0x0;
  loaded_arc->region_count = (undefined *)0x0;
  *(undefined ***)&loaded_arc->field_0x128 = ppuVar61;
  curr_extra_entry_idx = (ulong)fs_header->regional_count_1;
  if (fs_header->regional_count_1 != 0) {
    p_Var67 = (__tree_node_base *)0x0;
    file_data_count_2 = 0;
    do {
      file_data_count = *(uint *)((long)loaded_arc->region_entries + file_data_count_2 * 0xc);
      p_Var41 = (__tree_node_base *)ppuVar61;
      p_Var68 = (__tree_node_base *)ppuVar61;
      while (p_Var67 != (__tree_node_base *)0x0) {
        while (p_Var68 = p_Var67, file_data_count < *(uint *)&p_Var68->field_0x1c) {
          p_Var67 = p_Var68->__left_;
          p_Var41 = p_Var68;
          if (p_Var68->__left_ == (__tree_node_base *)0x0) {
            p_Var67 = p_Var68->__left_;
            goto joined_r0x007103751a04;
          }
        }
        if (file_data_count <= *(uint *)&p_Var68->field_0x1c) break;
        p_Var41 = (__tree_node_base *)&p_Var68->__right_;
        p_Var67 = *(__tree_node_base **)p_Var41;
      }
      p_Var67 = p_Var41->__left_;
joined_r0x007103751a04:
      if (p_Var67 == (__tree_node_base *)0x0) {
        p_Var67 = (__tree_node_base *)je_aligned_alloc(0x10,0x28);
        if (p_Var67 == (__tree_node_base *)0x0) {
          if (GlobalAllocator != (void *)0x0) {
            local_4a0._0_8_ = local_4a0._0_8_ & 0xffffffff00000000;
            local_430 = (undefined **)0x28;
                    /* WARNING: Load size is inaccurate */
            curr_extra_entry_idx =
                 (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,local_4a0,&local_430);
            if (((curr_extra_entry_idx & 1) != 0) &&
               (p_Var67 = (__tree_node_base *)je_aligned_alloc(0x10,0x28),
               p_Var67 != (__tree_node_base *)0x0)) goto LAB_71037519b8;
          }
          p_Var67 = (__tree_node_base *)0x0;
        }
LAB_71037519b8:
        *(uint *)&p_Var67->field_0x1c = file_data_count;
        *(int *)&p_Var67[1].__left_ = (int)file_data_count_2;
        p_Var67->__left_ = (__tree_node_base *)0x0;
        p_Var67->__right_ = (__tree_node_base *)0x0;
        p_Var67->__parent_ = p_Var68;
        p_Var41->__left_ = p_Var67;
        if (**(long **)&loaded_arc->field_0x128 != 0) {
          *(long *)&loaded_arc->field_0x128 = **(long **)&loaded_arc->field_0x128;
          p_Var67 = p_Var41->__left_;
        }
        std::__1::__tree_balance_after_insert<std::__1::__tree_node_base<void*>*>
                  ((__tree_node_base *)loaded_arc->region_tree,p_Var67);
        loaded_arc->region_count = loaded_arc->region_count + 1;
        curr_extra_entry_idx = (ulong)fs_header->regional_count_1;
      }
      file_data_count_2 = file_data_count_2 + 1;
      if (curr_extra_entry_idx <= file_data_count_2) break;
      p_Var67 = (__tree_node_base *)*ppuVar61;
    } while( true );
  }
  bVar20 = true;
LAB_7103750e00:
  cVar14 = *(char *)((long)local_220 + 0x22c);
  ppuVar61 = local_220;
joined_r0x007103750e08:
  local_220 = ppuVar61;
  if (cVar14 == '\0') {
    if (ppuVar61 != (undefined **)0x0) goto LAB_7103751038;
  }
  else {
    (**(code **)(*ppuVar61 + 0x30))(&local_430,ppuVar61);
    *(undefined1 *)((long)ppuVar61 + 0x22c) = 0;
LAB_7103751038:
    (**(code **)(*ppuVar61 + 8))(ppuVar61);
  }
  if (bVar20) {
    loaded_arc = pLVar33->arc;
    pLVar35 = loaded_arc->loaded_fs_search_;
    if (pLVar35 != (LoadedFsSearch *)0x0) {
      pLVar63 = pLVar33->search;
      file_data_count = *(uint *)&pLVar35->header;
      curr_extra_entry_idx = (ulong)file_data_count;
      if (pLVar63->header != (FsSearchHeader *)0x0) {
        free_default(pLVar63->header);
      }
      if (file_data_count == 0) {
        file_data_count = 1;
      }
      ppuVar61 = (undefined **)(ulong)file_data_count;
      __dest_00 = (FsSearchHeader *)je_aligned_alloc(4,(size_t)ppuVar61);
      if (__dest_00 == (FsSearchHeader *)0x0) {
        if (GlobalAllocator != (void *)0x0) {
          local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
          local_430 = ppuVar61;
          file_data_count_2 =
               (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
          if ((file_data_count_2 & 1) != 0) {
            __dest_00 = (FsSearchHeader *)je_aligned_alloc(4,(size_t)ppuVar61);
            goto LAB_71037510cc;
          }
        }
        __dest_00 = (FsSearchHeader *)0x0;
      }
LAB_71037510cc:
      pLVar63->header = __dest_00;
      memcpy(__dest_00,pLVar35,curr_extra_entry_idx);
      pLVar63->body = (FsSearchBody *)&__dest_00->field_0x8;
      pLVar63->file_path_to_idx = (HashToIndex *)&__dest_00->field_0x14;
      pHVar47 = (HashGroup *)(&__dest_00->field_0x14 + (ulong)*(uint *)&__dest_00->field_0x8 * 8);
      pLVar63->idx_to_group = pHVar47;
      file_data_count = *(uint *)&__dest_00->field_0x8;
      pLVar63->path_to_idx = &pHVar47[file_data_count].path;
      pHVar47 = (HashGroup *)(&pHVar47[file_data_count].path + *(uint *)&__dest_00->field_0x10);
      if (*(int *)&__dest_00->field_0xc != 0) {
        pLVar63->idx_to_path_group_idx = (uint *)pHVar47;
        pHVar47 = (HashGroup *)
                  (&(pHVar47->path).field_0x0 + (ulong)*(uint *)&__dest_00->field_0xc * 4);
      }
      pLVar63->path_group = pHVar47;
      loaded_arc = pLVar33->arc;
    }
    extra_entry_index = (uint *)loaded_arc->unk_data;
    if (extra_entry_index != (uint *)0x0) {
      puVar24 = (undefined8 *)pLVar33->patch;
      if ((void *)*puVar24 != (void *)0x0) {
        free_default((void *)*puVar24);
      }
      file_data_count = *extra_entry_index;
      curr_extra_entry_idx = (ulong)file_data_count;
      if (file_data_count == 0) {
        file_data_count = 1;
      }
      ppuVar61 = (undefined **)(ulong)file_data_count;
      pvVar25 = je_aligned_alloc(8,(size_t)ppuVar61);
      if (pvVar25 == (void *)0x0) {
        if (GlobalAllocator != (void *)0x0) {
          local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
          local_430 = ppuVar61;
          file_data_count_2 =
               (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
          if ((file_data_count_2 & 1) != 0) {
            pvVar25 = je_aligned_alloc(8,(size_t)ppuVar61);
            goto LAB_71037511a0;
          }
        }
        pvVar25 = (void *)0x0;
      }
LAB_71037511a0:
      *puVar24 = pvVar25;
      memcpy(pvVar25,extra_entry_index,curr_extra_entry_idx);
      puVar24[1] = pvVar25;
      puVar24[2] = (long)pvVar25 + 0x10;
      puVar24[3] = (long)pvVar25 + 0x10 + (ulong)*(uint *)((long)pvVar25 + 0x10) * 8 + 8;
      puVar24[4] = (long)pvVar25 + *(long *)((long)pvVar25 + 8);
      loaded_arc = pLVar33->arc;
    }
    if (loaded_arc != (LoadedArc *)0x0) {
      fs_header = loaded_arc->fs_header;
      file_data_count =
           fs_header->folder_offset_count_2 +
           fs_header->folder_offset_count_2 + fs_header->folder_offset_count_1 +
           fs_header->extra_folder;
      pLVar31->loaded_directory_table_size = file_data_count;
      ppuVar61 = (undefined **)((ulong)file_data_count * 0x48);
      if (file_data_count == 0) {
        ppuVar61 = (undefined **)0x1;
      }
      __s = (LoadedDirectory *)je_aligned_alloc(4,(size_t)ppuVar61);
      if ((__s == (LoadedDirectory *)0x0) &&
         (__s = (LoadedDirectory *)GlobalAllocator, GlobalAllocator != (void *)0x0)) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
        local_430 = ppuVar61;
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if ((curr_extra_entry_idx & 1) == 0) {
          __s = (LoadedDirectory *)0x0;
        }
        else {
          __s = (LoadedDirectory *)je_aligned_alloc(4,(size_t)ppuVar61);
        }
      }
      pLVar31->loaded_directory_table = __s;
      memset(__s,0,(ulong)pLVar31->loaded_directory_table_size * 0x48);
      file_data_count = loaded_arc->fs_header->file_info_path_count;
      ppuVar61 = (undefined **)((ulong)file_data_count << 3);
      if (file_data_count == 0) {
        ppuVar61 = (undefined **)0x1;
      }
      pLVar31->loaded_table_1_size = file_data_count;
      __s_00 = (Table1Entry *)je_aligned_alloc(4,(size_t)ppuVar61);
      if ((__s_00 == (Table1Entry *)0x0) &&
         (__s_00 = (Table1Entry *)GlobalAllocator, GlobalAllocator != (void *)0x0)) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
        local_430 = ppuVar61;
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if ((curr_extra_entry_idx & 1) == 0) {
          __s_00 = (Table1Entry *)0x0;
        }
        else {
          __s_00 = (Table1Entry *)je_aligned_alloc(4,(size_t)ppuVar61);
        }
      }
      pLVar31->loaded_table_1 = __s_00;
      memset(__s_00,0,(ulong)pLVar31->loaded_table_1_size << 3);
      file_data_count = loaded_arc->fs_header->file_info_index_count;
      ppuVar61 = (undefined **)((ulong)file_data_count * 0x18);
      if (file_data_count == 0) {
        ppuVar61 = (undefined **)0x1;
      }
      pLVar31->loaded_table_2_size = file_data_count;
      __s_01 = (Table2Entry *)je_aligned_alloc(4,(size_t)ppuVar61);
      if ((__s_01 == (Table2Entry *)0x0) &&
         (__s_01 = (Table2Entry *)GlobalAllocator, GlobalAllocator != (void *)0x0)) {
        local_220 = (undefined **)((ulong)local_220 & 0xffffffff00000000);
                    /* WARNING: Load size is inaccurate */
        local_430 = ppuVar61;
        curr_extra_entry_idx =
             (**(code **)(*GlobalAllocator + 0x30))(GlobalAllocator,&local_220,&local_430);
        if ((curr_extra_entry_idx & 1) == 0) {
          __s_01 = (Table2Entry *)0x0;
        }
        else {
          __s_01 = (Table2Entry *)je_aligned_alloc(4,(size_t)ppuVar61);
        }
      }
      pLVar31->loaded_table_2 = __s_01;
      memset(__s_01,0,(ulong)pLVar31->loaded_table_2_size * 0x18);
      pLVar31->version = pLVar31->loaded_data->arc->fs_header->version & 0xffffff;
    }
  }
  goto LAB_71037512cc;
}
