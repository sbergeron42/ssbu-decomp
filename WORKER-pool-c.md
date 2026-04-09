# Worker: pool-c

## Model: Opus

## Task: Phase 1 — EffectModule typed wrapper adoption

## Priority: QUALITY REFACTOR (not new decomp)

## Context
The `BattleObjectModuleAccessor` fields are now typed (`EffectModule*` not `void*`).
A code reviewer (`tools/review_diff.py`) now gates all merges.
Your job is to replace raw vtable dispatch with typed method wrappers.

## File Territory
- `src/app/sv_animcmd_effect.cpp` (42 raw VT calls to convert — biggest single file)
- `src/app/fighter_effects.cpp` (6 raw EffectModule VT calls)
- `src/app/modules/EffectModule.cpp` (3 remaining raw VT calls)
- `src/app/camera_functions.cpp` (fix your 6 STRUCT_REQUIRED violations)

## Step 1: Fix your own pending REJECT violations
Your diff scored 80/100 but has 6 STRUCT_REQUIRED rejections in camera_functions.cpp. These functions access 3-8 distinct offsets without structs:
- `send_event_on_start_boss_entry`, `find_active_item_from_id` (4 offsets each)
- `remove_item_from_id` (3 offsets)
- `get_near_pos` (3 offsets)
- `restore_pos_dead_range_gravity`, `convert_pos_dead_range_gravity` (5-8 offsets)

Define stub structs in `include/` for the types these functions operate on, then rewrite with field access.

## Step 2: Convert sv_animcmd_effect.cpp
This file has 42 raw effect module vtable calls. Add `#include "app/modules/EffectModule.h"`. Replace:
```cpp
// BEFORE:
void** vt = *reinterpret_cast<void***>(effect_mod);
reinterpret_cast<u64(*)(void*, u64, ...)>(vt[0x80/8])(effect_mod, hash, ...);

// AFTER:
acc->effect_module->req_follow(hash, ...);
```

## Key vtable slot -> method mapping
| Slot | Method | Occurrences |
|------|--------|-------------|
| 0x80/8 | `req_follow` | 20 (most common!) |
| 0x70/8 | `req_on_joint` | 6 |
| 0xd8/8 | `kill` | 3 |
| 0x108/8 | `detach` | 3 |
| 0x88/8 | `req` | 2 |
| 0xe0/8 | `kill_kind` | 2 |

See `include/app/modules/EffectModule.h` for the complete list (89 methods).

## Step 3: Clean up EffectModule.cpp
3 remaining raw VT calls for `req_after_image` variants. Check if the header signatures match; if not, add/fix the wrappers in the header.

## Self-Check (MANDATORY before committing)
```bash
python tools/review_diff.py pool-c
```
Must score 50+ with zero REJECT violations.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
