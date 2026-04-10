# Worker: pool-d

## Model: Opus

## Task: Continue AI function decomp (app::ai namespace)

## Priority: DECOMP NEW FUNCTIONS

## Context
Phase 3 cast density REJECT is FIXED (3.8% → under 10%).
22 AI functions decomped in ai_target_stat.cpp.
Reviewer passes: 100/100 quality, 4.0% cast density.

## Completed This Session
- Fixed BossManager cast density: BossEntity vtable struct, BossEntitySlot, typed iteration
- Decomped 22 app::ai functions in ai_target_stat.cpp:
  - 12 check_target_stat_* (relocation-only match)
  - 4 attack_data_* (relocation-only match)
  - is_update_count_odd (100% byte match)
  - is_valid_target (relocation-only match)
  - check_stat_ground_free, check_stat_air_free (86% near-match)
  - check_chr_stat (93%), check_stat_floor_damage (92%)
- 2 skipped: change_action, get_cmd_id (scheduling mismatch)

## File Territory
- src/app/BossManager.cpp
- src/app/ai_target_stat.cpp (NEW)
- src/app/audio_functions.cpp
- src/app/camera_functions.cpp
- src/app/fighter_attack.cpp
- src/app/fighter_core.cpp
- src/app/fighter_status.cpp
- src/app/fun_batch_b_026.cpp
- src/app/fun_batch_d5_047.cpp
- include/app/BattleObject.h
- include/app/BossManager.h
- include/app/placeholders/BossEntity.h (NEW)
- include/app/placeholders/AITargetStat.h (NEW)
- include/app/placeholders/FighterParamAccessor2.h
- data/undefined_types.md
- data/ghidra_cache/pool-d.txt

## Next Targets
- More app::ai check_stat_* functions (check_stat_floor_pass, check_stat_ground_free2, etc.)
- app::ai_weapon::most_earliest_hit_frame
- More named 48-96B functions in AI cluster (0x710036xxxx range)
- Extend FighterAIState with newly discovered fields (+0x64 as u32, +0xd8 as s32)

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```

## Verify
```bash
python tools/compare_bytes.py FUNC_NAME ADDRESS
```
