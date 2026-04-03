# SSBU Game State Serialization for Rollback

Research findings on game state save/restore patterns in SSBU 13.0.4 for rollback netplay.

## 1. Main Game Loop

### nnMain (Entry Point)
- **Address**: `0x71002c5620` (1,744 bytes)
- Nintendo SDK entry point. Initializes the game and enters the main dispatch loop.

### main_loop
- **Address**: `0x7103747270` (24,576 bytes)
- This is the primary game loop — a massive 24KB function.
- Located in the network/online subsystem region of the binary (0x7103xx addresses).
- Too large for Ghidra MCP decompilation (times out). Needs manual analysis.
- **Priority: HIGH** — Understanding this function's per-frame dispatch is critical for rollback.

## 2. CSS (Character Select Screen) State Serialization Trio

The game has a fully-fledged CSS state save/restore system. This is the strongest existing serialization pattern — a direct model for how battle state could be snapshotted.

### css_serialize_state_to_buffer
- **Address**: `0x71016ed7c0` (5,744 bytes)
- **Signature**: `void css_serialize_state_to_buffer(void** param_1, long buffer, ulong flags, byte param_4)`
- Serializes CSS state into a flat buffer at `param_2`
- **State serialized**:
  - Player slot data (up to 8 players, at buffer+0x60 through buffer+0x160)
  - Player names — null-terminated UTF-16 strings with FNV-1a hashing (0x811c9dc5 seed)
  - Game mode and rule flags (`CSS_MODE_FLAGS`, `CSS_MAX_PLAYER_COUNT`, `CSS_INITIAL_PLAYER_BITMASK`, `CSS_MAX_SLOTS_VARIANT`)
  - Team configuration (guarded by `g_team_param_init_guard`)
  - Download/DLC content status (bitmask at buffer+0x50..0x58)
  - Online-specific overrides: when `mode == 2` (online), different player name/tag/icon data from global state (`DAT_71053059b0..DAT_7105305f06`)
  - Max download timer (float, from 17 download slot entries)
  - Mutex-protected network buffer copy at the end
- **Key globals**: `DAT_7105307760..DAT_7105309968` (CSS state region in BSS)
- **Companion comment**: "Companion to css_read_state_to_compact_buffer and css_restore_state_from_save"

### css_read_state_to_compact_buffer
- **Address**: `0x71016e2df0` (560 bytes)
- Reads CSS state into a compact/compressed format for network transmission.

### css_restore_state_from_save
- **Address**: `0x71017a24f0` (4,928 bytes)
- **Signature**: `void css_restore_state_from_save(void** param_1)`
- Restores CSS state from a saved buffer back into global state.
- Restores: player data for 7 slots (each 0x1C8 bytes apart), player names (FNV-1a rehashed), game mode, rules, team config, DLC content bitmasks, profile chain data.
- Uses `FUN_71016b6bb0` for deep player data copy.
- Writes to BSS globals: `DAT_7105307760` through `DAT_710530d368` (entire CSS state block ~11KB).
- **Note**: Ghidra comment says "potentially useful for CSS re-entry persistence (Phase 4 item 5)."

## 3. L2C Table Serialization (store/load_from_l2c_table_impl)

The `store_l2c_table_impl` / `load_from_l2c_table_impl` pattern is the game's per-struct serialization mechanism. Each game data type that needs serialization implements this pair. These serialize struct fields into L2CValue tables (Lua-compatible dictionaries).

### Pattern
Each type has 3 functions:
1. `Foo__load_from_l2c_table_impl` — Deserialize from L2CValue table to struct (large, 500-7000 bytes)
2. `Foo__store_l2c_table_impl` — Allocate L2CValue table and call impl (small, 16-208 byte thunk)
3. `Foo__store_l2c_table_impl_ADDR` — Actual serialization logic (varying size)

### DamageInfo__store_l2c_table_impl (Decompiled)
- Allocates 0x48 bytes via `je_aligned_alloc(0x10, 0x48)` — a 72-byte L2CValue table
- Zeroes 18 L2CValue slots (0x48 / 4 = 18 fields)
- Sets table type = 1, element count = 5
- Calls `FUN_7102011ba0()` to populate the 5 fields
- Fields likely: damage amount, knockback reaction, attacker ID, hit part, damage type

### Complete List of Serializable Types

#### Core Battle State (rollback-critical)
| Type | store addr | load addr | load size | Notes |
|------|-----------|-----------|-----------|-------|
| **AttackData** | 0x7101feecd0 | 0x7101fed120 | 7,088 B | Attack hitbox data — largest load impl |
| **AttackAbsoluteData** | 0x7101fec200 | 0x7101febaa0 | 1,888 B | Absolute attack data |
| **DamageInfo** | 0x7102011ad0 | 0x71020112a0 | 2,096 B | Damage dealt/received |
| **DamageLog** | 0x71020143a0 | 0x7102013080 | 4,896 B | Damage history |
| **AreaContactLog** | 0x7101fcacc0 | 0x7101fca860 | 1,120 B | Area contact tracking |
| **Circle** | 0x71020f1b60 | 0x71020f1980 | 480 B | Collision circle |
| **Rhombus2** | 0x71020f0750 | 0x71020f0250 | 1,280 B | Collision rhombus |
| **lib::Rect** | 0x71020fb560 | 0x71020fb380 | 480 B | Rectangle primitive |
| **stWaterAreaInfo** | 0x71020d4040 | 0x71020d3e40 | 512 B | Water area state |

#### Link Events (inter-object communication)
| Type | store addr | load addr | Notes |
|------|-----------|-----------|-------|
| **LinkEvent** | 0x71020542b0 | 0x71020542a0 | Base link event |
| **LinkEventPos** | 0x71020547a0 | 0x71020547a0 | Position sync |
| **LinkEventMask** | 0x7102055a40 | 0x7102055a30 | Mask data |
| **LinkEventFinal** | 0x71020b1930 | 0x71020b1920 | Final Smash events |
| **LinkEventCapture** | 0x7101ff8cd0 | 0x7101ff8cc0 | Grab/capture state |
| **LinkEventCapturePulled** | 0x71020b49f0 | 0x71020b49e0 | Being pulled |
| **LinkEventCaptureItem** | 0x71020b60f0 | 0x71020b60e0 | Item grab |
| **LinkEventCaptureDriver** | 0x71020b9560 | 0x71020b9550 | Driver capture |
| **LinkEventCaptureMimikkyu** | 0x71020b8980 | 0x71020b8970 | Mimikyu grab |
| **LinkEventCaptureFishingrodDamage** | 0x71021a6290 | 0x71021a6280 | Isabelle rod |
| **LinkEventThrow** | 0x7101ffd070 | 0x7101ffd060 | Throw event |
| **LinkEventStarShot** | 0x71020b38b0 | 0x71020b38a0 | Star shot |
| **LinkEventLassoHang** | 0x7102122380 | 0x7102122370 | Lasso hang |
| **LinkEventTouchItem** | 0x71020f2e90 | 0x71020f2e80 | Item touch |
| **OnCalcParamEvent** | 0x71020bbee0 | 0x71020bbed0 | Param calculation |
| **lib::BasicEvent** | 0x71020faf70 | 0x71020faf60 | Basic event base |

#### Gimmick Events (stage interactions)
| Type | store addr | load addr |
|------|-----------|-----------|
| **GimmickEvent** | 0x71020d4750 | 0x71020d4740 |
| **GimmickEventPos** | 0x71020d5860 | 0x71020d5850 |
| **GimmickEventNotify** | 0x71020d6a00 | 0x71020d69f0 |
| **GimmickEventWarp** | 0x71020d7530 | 0x71020d7520 |
| **GimmickEventBarrel** | 0x71020d8060 | 0x71020d8050 |
| **GimmickEventSpring** | 0x71020dcfb0 | 0x71020dcfa0 |
| **GimmickEventPipe** | 0x71020df7a0 | 0x71020df790 |
| **GimmickEventTornadoMoveInfo** | 0x71020e1bc0 | 0x71020e1bb0 |
| **GimmickEventTornadoShootInfo** | 0x71020e3570 | 0x71020e3560 |
| **GimmickEventTornadoEscape** | 0x71020e4ff0 | 0x71020e4fe0 |
| **GimmickEventLadder** | 0x71020e59a0 | 0x71020e5990 |
| **GimmickEventCatch** | 0x71020e7930 | 0x71020e7920 |
| **GimmickEventDrumCheckNeedLock** | 0x71020e9450 | 0x71020e9440 |
| **GimmickEventDrumCheckNeedHide** | 0x71020e9f60 | 0x71020e9f50 |
| **GimmickEventDrumPos** | 0x71020eac00 | 0x71020eabf0 |
| **GimmickEventDrumShake** | 0x71020ebd90 | 0x71020ebd80 |
| **GimmickEventDrumEscape** | 0x71020ec740 | 0x71020ec730 |
| **GimmickEventDrumRelease** | 0x71020ed0f0 | 0x71020ed0e0 |
| **GimmickEventSlashLockInfo** | 0x71020edc00 | 0x71020edbf0 |
| **GimmickEventSlashEscape** | 0x71020eef20 | 0x71020eef10 |

#### Fighter-Specific Link Events
| Type | store addr | load addr |
|------|-----------|-----------|
| **FighterCloudLinkEventFinal** | 0x71021992d0 | 0x71021992c0 |
| **FighterInklingLinkEventPaint** | 0x710219f220 | 0x710219f210 |
| **FighterPikminLinkEvent** (8 subtypes) | 0x710216b2f0..0x71021718d0 | various |
| **FighterPokemonLinkEventChange** | 0x71021aff60 | 0x71021aff50 |
| **FighterRidleyLinkEventMotion** | 0x71021aa540 | 0x71021aa530 |
| **FighterRyuLinkEventFinalDeadDamage** | 0x7102195b30 | 0x7102195b20 |
| **FighterRyuLinkEventFinalMoveTarget** | 0x7102196650 | 0x7102196640 |
| **WeaponRobotHominglaserLinkEvent** (2) | 0x710217c4a0..0x710217d460 | various |
| **WeaponShizueFishingrodLinkEvent** (4) | 0x71021a2ff0..0x71021a5710 | various |
| **LinkEventYoshiTamagoDamageEffect** | 0x7102148ae0 | 0x7102148ad0 |

## 4. Low-Level Serialization Primitives

| Function | Address | Size | Purpose |
|----------|---------|------|---------|
| **serializeU64** | 0x71000bb930 | 64 B | Serialize uint64 |
| **serializeU32** | 0x71000bb980 | 32 B | Serialize uint32 |
| **deserializeU32** | 0x71000bb9a0 | 16 B | Deserialize uint32 |
| **serializeU16** | 0x71000bb9b0 | 16 B | Serialize uint16 |

These are byte-swapping + buffer-write primitives. For rollback, they'd be used for the raw state buffer format.

## 5. BattleObject Per-Frame State (Module System)

Each BattleObject (fighter, item, weapon) has 30+ modules at fixed offsets in `BattleObjectModuleAccessor`. For rollback, each module's mutable state must be saved/restored.

### Rollback-Critical Modules

| Module | Offset | Key State | Functions |
|--------|--------|-----------|-----------|
| **PostureModule** | +0x38 | Position (x,y,z), rotation, scale, LR facing, prev_pos | `pos_impl`, `set_pos_impl`, `lr_impl`, `prev_pos_impl` |
| **StatusModule** | +0x40 | Current status kind, prev status, situation (air/ground), interrupt status | `status_kind_impl`, `change_status_request_impl`, `situation_kind_impl` |
| **ControlModule** | +0x48 | Stick x/y, sub-stick, prev stick, attack stick direction | `get_stick_x_impl`, `get_stick_y_impl`, `get_stick_prev_x_impl` |
| **WorkModule** | +0x50 | Int/float/flag work variables (per-status scratch state), transition terms | `get_int_impl`, `set_float_impl`, `is_flag_impl`, 50+ functions |
| **GroundModule** | +0x58 | Ground attachment, cliff data, touch flags, pass-through floors | `correct_impl`, `get_touch_flag_impl`, `cliff_check_impl` |
| **KineticModule** | +0x68 | Velocity (speed), kinetic type, energy states, acceleration | `get_sum_speed_impl`, `add_speed_impl`, `change_kinetic_impl` |
| **MotionModule** | +0x88 | Current animation, frame, blend weight, 2nd motion, partial motion | `frame_impl`, `change_motion_impl`, `is_end_impl` |
| **AttackModule** | +0xA0 | Active hitboxes, attack data, power, lerp state | `set_attack_impl`, `clear_all_impl`, `is_attack_impl` |
| **DamageModule** | +0xA8 | Current damage %, damage log, knockback reaction, damage lock | `damage_impl`, `add_damage_impl`, `reaction_impl` |
| **SlowModule** | +0x170 | Hitlag/hitstop state, slow rate, skip frame tracking | `is_slow_impl`, `rate_impl`, `is_skip_impl` |

### Per-Frame State Summary
For a single fighter, the minimum rollback state includes:
- **Position**: 3 floats (x, y, z) + rotation + facing (LR) = ~24 bytes
- **Velocity**: 3 floats (speed x, y, z) + kinetic type = ~16 bytes
- **Status**: current + prev status kind + situation kind = ~12 bytes
- **Damage**: current damage % (float) + damage log + reaction = ~32 bytes
- **Motion**: animation kind (hash) + frame (float) + blend = ~12 bytes
- **Work variables**: fighter-dependent, typically 32-64 ints + 16-32 floats = ~256-384 bytes
- **Hitboxes**: up to 8 active hitboxes x AttackData = variable
- **Ground state**: touch flags + cliff state + attach info = ~32 bytes
- **Control input**: stick x/y + prev + sub-stick = ~32 bytes

**Rough estimate per fighter: ~500-800 bytes minimum**, 2-4KB with full work variables and hitbox data.

## 6. Fighter-Specific State

### FighterInformation (per-fighter global state)
- **Key functions**: `hit_point_impl`, `stock_count_impl`, `dead_count_impl`, `fighter_color_impl`, `suicide_count_impl`, `total_beat_count_impl`, `is_operation_cpu_impl`
- Contains: HP, stock count, death count, character color, whether CPU-controlled
- Address range: `0x71020c9d60..0x71020c9fa0`

### FighterManager (global battle manager)
- **Key functions**: `entry_count_impl`, `total_fighter_num_impl`, `is_final_impl`, `is_ready_go_impl`, `get_fighter_pos_impl`, `get_top_rank_player_impl`
- Manages: fighter entry/exit, final smash state, KO camera, movie processing
- Address range: `0x7102140d60..0x7102141930`

### Special Fighter State
- `save_aura_ball_status` @ `0x7100c5e1a0` (13,348 bytes!) — Saves Lucario's Aura Sphere charge state
- `save_shadowball_status` @ `0x7100d295b0` (96 bytes) — Saves Mewtwo's Shadow Ball charge state
- These are character-specific projectile save functions — essential for correct rollback of charge moves

## 7. Slow/Hitstop System

### BattleObjectSlow (per-object slow state)
| Function | Address | Purpose |
|----------|---------|---------|
| `rate_impl` | 0x7101fca5b0 | Current slow rate |
| `rate_request_impl` | 0x7101fca5c0 | Requested rate |
| `is_adjust_impl` | 0x7101fca670 | Whether adjusting |
| `is_estimate_impl` | 0x7101fca650 | Whether estimating |

### BattleObjectWorld (global physics state)
| Function | Address | Purpose |
|----------|---------|---------|
| `gravity_pos_impl` | 0x7101fca220 | Gravity position vector |
| `gravity_speed_coefficient_impl` | 0x7101fca1f0 | Gravity speed multiplier |
| `is_gravity_normal_impl` | 0x7101fca2b0 | Normal gravity check |
| `is_move_impl` | 0x7101fca2d0 | Whether world is moving |
| `move_speed_impl` | 0x7101fca2e0 | World move speed |
| `scale_z_impl` | 0x7101fca200 | Z-axis scale |
| `is_disable_reverse_impl` | 0x7101fca2f0 | Reverse disable flag |

## 8. Network Infrastructure

### game_network_session_create
- **Address**: `0x7103705150`
- Creates network sessions for 3 modes:
  - Mode 1 (LDN/Local): Uses `nn::ldn::GetState()` and `nn::ldn::GetNetworkInfo()`. Local wireless.
  - Mode 2 (Online P2P): Sets up 4 player session slots with 0x4D8 byte buffers each. Uses `nn::err::ErrorResultVariant` for error handling. Sets timeout of 300 (frames?).
  - Mode 3 (Arena/Spectate): 4 session slots with 0x50 byte buffers, player index mapping (0x706050403020100 = identity map for 16 slots).
- Player identity stored via `DAT_710593a580` — global session table, 0x198 (408) bytes per session entry.

### ClockSnapshot
- `0x71039c5c70` and `0x710744a0e0` — Two instances (SDK and game), used for timing/synchronization.

### GetSystemTick
- `0x71001b1490`, `0x71039c0200`, `0x710744a7b0` — Three instances. Used for frame timing.

## 9. Rollback Implementation Strategy

### What Needs Saving (Per Frame)
1. **Per fighter** (~2-4KB each):
   - All module state (PostureModule through SlowModule)
   - WorkModule int/float/flag arrays
   - Active hitbox data (AttackData l2c tables)
   - DamageInfo + DamageLog
   - ControlModule input state
   
2. **Global state** (~1KB):
   - BattleObjectWorld (gravity, world movement)
   - BattleObjectSlow (global hitstop)
   - FighterManager state (final smash, KO camera)
   - Frame counter / game timer
   
3. **Per item/weapon** (~0.5-2KB each):
   - Same module pattern as fighters but fewer modules
   - Gimmick event state for stage interactions
   
4. **Link events** (variable):
   - Active LinkEvent instances between objects
   - All the GimmickEvent types for stage state

### Estimated Total State Size
- 2-player match: ~8-16KB per frame
- 4-player match: ~20-40KB per frame
- With 7-frame rollback window: ~56-280KB ring buffer

### Recommended Approach
1. **Start with CSS serialization as a model** — the css_serialize/restore trio shows the exact pattern: flat buffer + structured copy + FNV hash for integrity
2. **Use the l2c table infrastructure for per-struct serialization** — the store/load_from_l2c_table_impl pairs already exist for all the critical types
3. **Focus on PostureModule + KineticModule + StatusModule + WorkModule first** — these are the minimum viable rollback state
4. **Manual analysis of `main_loop` (0x7103747270) is required** — need to understand exactly what runs per frame and in what order
5. **The `serializeU64/U32/U16` primitives** can be used for the raw buffer format

### Key Open Questions
- Where is the per-frame dispatch in `main_loop`? (24KB function, too large for MCP decompilation)
- How does the game's existing delay-based netcode buffer inputs? (No `rollback` or `input_buffer` functions found — likely unnamed)
- What is the RNG state and where is it seeded per frame?
- How are items spawned deterministically? (Item spawn RNG would desync rollback)
