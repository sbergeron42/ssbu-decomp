# SSBU Input Handling Pipeline

Research document mapping the input flow from controller hardware to game state consumption, with focus on network implications for rollback.

## Pipeline Overview

```
nn::hid (SDK)           Controller hardware polling
    |
GetNpadState()          Read raw NpadState per controller type
    |
FUN_71017547f0          Per-frame input poll loop (iterates 8 players)
    |                   Reads controller structs from global array DAT_7105338830/DAT_7105338860
    |
final_input_mapping()   Maps raw buttons/sticks to game-internal bitfield
    |                   Uses per-player mapping table (stride 0x50, 8 slots)
    |
fim_cstick_handler()    C-stick post-processing (tilt vs smash attack modes)
    |
    v
Mapped Input (8 bytes)  Buttons (uint32 bitfield) + stick X/Y (int8 each) + C-stick
    |
    +--- Local: written to player input slots at param_1+0x2B8 (8 x 8-byte entries)
    +--- Online: serialized into network transport layer
    |
ControlModule            Game-side abstraction — reads mapped inputs via vtable
    |
FighterControlModuleImpl Fighter-specific layer (command detection, smash inputs)
    |
Game Simulation          Status transitions, physics, animcmd
```

## Layer 1: Hardware Polling — nn::hid

The SDK's Npad (Nintendo Pad) API provides controller state.

### Key SDK Functions

| Function | Address(es) | Purpose |
|----------|-------------|---------|
| `InitializeNpad` | 71039c75c0, 7107449900 | One-time Npad system init |
| `SetSupportedNpadStyleSet` | 71039c75d0, 7107449908 | Configure supported controller types |
| `SetSupportedNpadIdType` | 71039c6960, 7107449910 | Set which player slots are active |
| `GetNpadState` | 71039c69d0..71039c6ac0 (6 variants) | Read current NpadState for a controller |
| `GetNpadStyleSet` | 71039c6980, 7107449960 | Query connected controller type |
| `GetNpadControllerColor` | 71039c69e0, 7107449990 | Get Joy-Con body/button color |
| `SetNpadJoyHoldType` | 71039c75e0, 7107449918 | Set horizontal/vertical hold mode |
| `DisconnectNpad` | 71039c6a40, 7107449950 | Disconnect a controller |

**Note:** Each SDK function appears at two addresses — the first set (71039cxxxx) are the actual implementations, the second set (710744xxxx) are SDK import stubs. `GetNpadState` has 6 variants corresponding to different controller types (Pro Controller, Handheld, Joy-Con Dual, Joy-Con Left, Joy-Con Right, System).

### NpadState Structure

The raw `NpadState` contains at minimum:
- `+0x08`: Button bitfield (uint32) — each bit = one physical button
- `+0x10`: Analog stick data (two sticks, float pairs)
- `+0x9C`: Controller style type (int) — determines which button mapping path to use

Controller style type values observed in `final_input_mapping`:
- `1`: D-pad only controller (e.g., NES controller)
- `2`: Left-side controller
- `3`: Right-side controller (buttons/stick axes are inverted)
- `4`: Dual Joy-Con / standard
- `5`: Standard variant
- `6`: Standard variant
- `7`: Pro Controller / Full controller

## Layer 2: Input Mapping — final_input_mapping

**Address:** `7101750f70`
**Signature:** `void final_input_mapping(void* mappings, int player_idx, void* out_mapped_inputs, void* controller_struct, bool arg)`

This is the core function that converts raw controller state to game-consumable input. It fires once per connected controller each frame.

### How It Works

1. **Validates** `player_idx` (0-7, aborts if >7)
2. **Reads controller style** from `controller_struct->+0x10->+0x9C`
3. **Iterates physical buttons** — for each pressed hardware button, looks up the mapping byte in the per-player mapping table at `mappings + player_idx * 0x50`
4. **Translates to game buttons** via mapping byte values:
   - `0x00` = Attack (bit 0)
   - `0x01` = Special (bit 1)
   - `0x02` = Jump (counted, 2+ = short hop macro, bit 6 = `JUMP_MINI`)
   - `0x03` = Shield (counted, 2+ = double-shield, bit 16 = `SHIELD_DOUBLE`)
   - `0x04` = Jump+Attack (bits 3+4, smash attack macro)
   - `0x0D` = Unbound (ignored)
5. **Computes stick values** via `FUN_7101752390` — normalizes analog stick to int8 range (-127..127) using `DAT_7104471fac` scale factor
6. **Calls `fim_cstick_handler`** for C-stick post-processing

### Mapped Input Format (8 bytes at out_mapped_inputs)

```
Offset 0: uint32 button_flags
  Bit 0:  ATTACK
  Bit 1:  SPECIAL  
  Bit 2:  (unused / reserved)
  Bit 3:  JUMP (part of jump+attack macro)
  Bit 4:  JUMP (part of jump+attack macro)
  Bit 5:  ATTACK+SPECIAL simultaneous (grab shortcut)
  Bit 6:  JUMP_MINI (short hop — two jump buttons)
  Bit 7:  CSTICK_ON (C-stick is active)
  Bit 8:  SHIELD_L (from shoulder check)
  Bit 9:  ATTACK_MIRROR (mirrors bit 0)
  Bit 11: SPECIAL_MIRROR (mirrors bit 1)
  Bit 13: TAUNT_UP (from D-pad, context-dependent)
  Bit 14: TAUNT_DOWN
  Bit 15: APPEAL (taunt button held)
  Bit 16: SHIELD_DOUBLE (two shield buttons)
  Bit 17: SMASH_ATTACK (from jump+attack macro)
Offset 4: int8 stick_x (-127..127)
Offset 5: int8 stick_y (-127..127)
Offset 6-7: C-stick data (set by fim_cstick_handler)
```

### Per-Player Mapping Table Layout (0x50 bytes per player)

The mapping table at `mappings + player_idx * 0x50` contains three sections for different controller styles:

- **Offsets 0x00-0x0E**: Pro Controller / type 7 mappings (12 button slots + config bytes)
- **Offsets 0x0F-0x1E**: Standard / types 1-6 mappings (12 button slots + config bytes)
- **Offsets 0x1F-0x2A**: D-pad / types 3-4 mappings
- **Offsets 0x2B-0x32**: C-stick config data (passed to `fim_cstick_handler`)
- **Offset 0x33**: Grab macro state (attack+special simultaneous tracking)

### Callers

| Address | Function | Context |
|---------|----------|---------|
| `71017547f0` | `FUN_71017547f0` (input_poll_all_players) | Per-frame loop, iterates 8 player slots |
| `71017553c0` | `FUN_71017553c0` (input_poll_single) | Single-player input poll wrapper |

## Layer 2.5: C-Stick Processing — fim_cstick_handler

**Address:** `7101752a10`

Processes the C-stick (right analog stick) differently based on control scheme parameter `param_3`:

| Mode (param_3) | Behavior |
|----------------|----------|
| 0 (Tilt) | Sets `CSTICK_ON` flag only, normalizes C-stick magnitude |
| 1 (Smash Stick variant) | Same as tilt but with different normalization |
| 2 | Increments jump counter (triggers `JUMP_MINI` if 2+) |
| 3 | Increments shield counter (triggers `SHIELD_DOUBLE` if 2+) |
| 4 | Shield variant with different timing |
| 5 (Smash Attack) | Overwrites main stick X/Y with C-stick direction, sets smash attack flags, has frame delay logic for smash charge |

Reads deadzone/sensitivity parameters from a param structure (hash `0x12af32a7be`, likely `common_param`/`control_param`) via binary search lookup.

## Layer 3: Per-Frame Input Polling — FUN_71017547f0

**Address:** `71017547f0`

This is the main per-frame input polling function. Called from the scene update path (caller at `710135f570`).

### Algorithm

```
for player_idx in 0..8:
    controller_id = input_struct[+0x298 + player_idx * 4]
    controller = global_controller_array[controller_id]  // DAT_7105338860
    
    // Disconnection check: if controller reports inactive (+0xB8 flag),
    // increment disconnect counter; after 3 frames, zero out input
    if controller.active:
        reset disconnect counter
    else:
        if ++disconnect_counter > 2: zero input and skip
    
    final_input_mapping(mappings, player_idx, &mapped_inputs[player_idx], controller, ...)
    
// After loop: apply input overrides (offsets 0x540-0x578 → 0x2B8-0x2F0)
// These overrides allow network/replay systems to inject inputs
```

### Key Details

- **Global controller array**: `DAT_7105338860` — indexed by controller_id (0-9), contains pointers to controller state structs
- **Default controller**: `DAT_7105338830` — used when no specific controller is assigned
- **Input override mechanism** (offsets 0x540-0x578): After local input is computed, each slot can be overwritten by external data. This is the **critical hook point for network play** — remote player inputs arrive via network and are written into the override slots.
- **Output**: 8 mapped input entries at `+0x2B8`, each 8 bytes (buttons + sticks)

## Layer 4: Game Consumption — ControlModule

The game's battle objects read input through `ControlModule`, which is the BattleObjectModuleAccessor sub-module at offset `+0x48`.

### ControlModule Functions (lua_bind interface)

All dispatch through vtable on the underlying control module object (`*(accessor+0x48)`).

#### Button State

| Function | Vtable Offset | Purpose |
|----------|---------------|---------|
| `get_button_impl` | +0x238 | Current frame button bitfield |
| `get_button_prev_impl` | (next) | Previous frame button bitfield |
| `check_button_on_impl` | vtable | Test if specific button is held |
| `check_button_trigger_impl` | vtable | Test if button was just pressed |
| `check_button_release_impl` | vtable | Test if button was just released |
| `check_button_on_trriger_impl` | vtable | On + trigger combined check |
| `check_button_on_release_impl` | vtable | On + release combined check |
| `check_button_off_impl` | vtable | Test if button is not held |
| `reset_button_impl` | vtable | Clear button state |

#### Stick State

| Function | Vtable Offset | Purpose |
|----------|---------------|---------|
| `get_stick_x_impl` | +0x178 | Main stick X (-1.0..1.0) |
| `get_stick_y_impl` | vtable | Main stick Y |
| `get_stick_prev_x_impl` | vtable | Previous frame stick X |
| `get_stick_prev_y_impl` | vtable | Previous frame stick Y |
| `get_stick_x_no_clamp_impl` | vtable | Unclamped stick X |
| `get_stick_y_no_clamp_impl` | vtable | Unclamped stick Y |
| `get_stick_angle_impl` | vtable | Stick angle in radians |
| `get_stick_dir_impl` | vtable | Stick cardinal direction |
| `get_sub_stick_x_impl` | vtable | C-stick X |
| `get_sub_stick_y_impl` | vtable | C-stick Y |

#### Other

| Function | Purpose |
|----------|---------|
| `get_pad_flag_impl` | Raw pad flags |
| `is_input_clatter_impl` | Mash-out / clatter detection |
| `is_stick_reversed_impl` | Check if stick L/R is reversed |
| `set_stick_reverse_impl` | Set stick reversal (e.g., after turnaround) |
| `reset_main_stick_impl` | Zero main stick values |

### FighterControlModuleImpl (Fighter-Specific)

Higher-level input processing for fighters. Located at addresses `71020aea80`-`71020aee40`.

| Function | Purpose |
|----------|---------|
| `update_attack_air_kind_impl` | Determine aerial attack type from stick direction |
| `reserve_on_attack_button_impl` | Buffer attack input during hitstop |
| `reserve_on_special_button_impl` | Buffer special input during hitstop |
| `set_overwrite_pad_lr_impl` | Override pad L/R (used by network?) |
| `get_attack_s3_turn_impl` | Side-tilt turn detection |
| `get_attack_s4_turn_impl` | Side-smash turn detection |
| `get_special_s_turn_impl` | Side-special turn detection |
| `get_special_command_lr_impl` | Command input L/R direction |
| `special_command_step_impl` | Advance command input state machine |
| `special_command_623_step_impl` | Dragon Punch motion (forward, down, down-forward) |
| `special_command_236236_step_impl` | Double quarter-circle forward |
| `special_command_214214_step_impl` | Double quarter-circle back |
| `special_command_23634_step_impl` | Pretzel motion |
| `special_command_21416_step_impl` | Half-circle + forward |
| `check_hit_stop_delay_command_impl` | Process buffered inputs during hitstop |
| `is_enable_hit_stop_delay_impl` | Check if hitstop delay buffering is active |
| `get_stick_button_trigger_impl` | Stick flick as button trigger |
| `get_stick_button_repeat_impl` | Stick flick repeat detection |

## Layer 5: Network Transport

### Network Session Architecture

SSBU uses two networking modes:

#### 1. Local Wireless (LDN)
- `nn::ldn` SDK — local Switch-to-Switch communication
- `game_ldn_initialize` @ `7103741990` — game-level LDN init
- `online_ldn_initialize` @ `7100191040` — online LDN init (sets up 4 player slots with 0x88-byte session entries)
- `ldn_connect_with_retry` @ `710016f0c0`
- `ldn_initialize_wrapper` @ `710016e740`
- `ldn_open_station_wrapper` / `ldn_close_station_wrapper`
- Session data stored with `nn::ldn::GetState()` and `nn::ldn::GetNetworkInfo()`

#### 2. Internet (NEX/NPLN)
- `game_network_session_create` @ `7103705150` — main network session factory
- Supports 3 modes via `param_1+0x14`:
  - Mode 1 (`\x01`): LDN-based (uses `nn::ldn::GetState` / `GetNetworkInfo`)
  - Mode 2 (`\x02`): Internet P2P (initializes 4 player session structs with 0x50-byte entries)
  - Mode 3 (`\x03`): Internet matchmaking (similar to mode 2 with additional params)
- Each session creates up to 4 network player slots (0x50 bytes each)
- Uses `nnsocket` API for actual data transport:
  - `nnsocketSocket` / `nnsocketConnect` / `nnsocketBind`
  - `nnsocketSend` / `nnsocketRecv`
  - `nnsocketPoll` (for non-blocking I/O)
  - `Send` / `Recv` / `SendTo` / `RecvFrom` (higher-level wrappers)

### Input Override Mechanism (Network Input Injection)

The **input override slots** in the per-frame poll struct are the key mechanism for network play:

```
Offset 0x2B8: Player 0 mapped input (8 bytes) — from local final_input_mapping
Offset 0x2C0: Player 1 mapped input
...
Offset 0x2F0: Player 7 mapped input

Offset 0x540: Player 0 override input (8 bytes) — written by network layer
Offset 0x548: Player 1 override input
...
Offset 0x578: Player 7 override input

Offset 0x580: Player 0 override enable flag (1 byte)
Offset 0x581: Player 1 override enable flag
...
Offset 0x587: Player 7 override enable flag
```

After `final_input_mapping` runs for all 8 players, the polling function checks each override flag. If set, it **replaces** the locally-computed input with the override data. This is how remote player inputs are injected:

1. Local player: `final_input_mapping` produces real input, override flag is clear
2. Remote player: `final_input_mapping` may produce dummy/zero input, override flag is set, network-received data replaces it

### Network Data Flow (Estimated)

```
Local Console:
  GetNpadState → final_input_mapping → mapped_input (8 bytes)
                                            |
                                            +→ written to local slot [0x2B8]
                                            +→ serialized + sent via nnsocketSend
                                            
Remote Console:
  nnsocketRecv → deserialize → write to override slot [0x540+]
                              → set override flag [0x580+]
                              → next frame poll replaces remote player input
```

## Rollback Implications

### What Needs to Be Saved/Restored for Rollback

1. **Input state**: The 8-byte mapped input per player (buttons + sticks) — this is the atomic unit
2. **Input mapping state**: Per-player mapping table (0x50 * 8 = 0x280 bytes) — includes grab macro tracking at offset 0x33
3. **C-stick state**: The per-player C-stick config bytes at mapping+0x2B, including smash charge delay counter (`param_5[3]`, `param_5[9]`, `param_5[10]`)
4. **Disconnect counter**: Per-player 3-frame disconnect tracking at input_struct+0x538

### Key Functions to Decomp for Rollback

| Priority | Function | Address | Why |
|----------|----------|---------|-----|
| HIGH | `FUN_71017547f0` | 71017547f0 | Per-frame input poll loop — must be re-entrant for rollback |
| HIGH | `final_input_mapping` | 7101750f70 | Core mapping — must be deterministic |
| HIGH | `fim_cstick_handler` | 7101752a10 | C-stick is stateful (delay counters) |
| HIGH | `FUN_710135f570` | 710135f570 | Scene-level caller, may contain frame counter logic |
| MED | `game_network_session_create` | 7103705150 | Session setup, determines how inputs are exchanged |
| MED | `online_ldn_initialize` | 7100191040 | LDN session init with player slot setup |
| MED | `FUN_7101752390` | 7101752390 | Stick normalization subroutine |
| LOW | `ControlModule__get_button_impl` etc. | 71020013e0+ | Consumption side (vtable dispatches) |

### Critical Observations

1. **Input is compact**: Only 8 bytes per player per frame. This is very friendly for network transmission and state saving.

2. **No built-in rollback**: SSBU uses **input delay** netcode, not rollback. The override mechanism writes inputs that arrived over the network after a delay. There is no evidence of state save/restore infrastructure.

3. **Determinism**: `final_input_mapping` is pure (stateless except for the grab macro byte at offset 0x33 and C-stick state). Given the same raw controller state and mapping table, it produces the same output. This is good for rollback — inputs can be replayed deterministically.

4. **The override mechanism is the injection point**: For a rollback mod, you would:
   - Save mapped inputs each frame (8 bytes * N players)
   - On rollback: replay saved inputs through the override slots
   - Re-simulate game state from the rollback point forward
   
5. **Frame-level granularity**: Input is polled exactly once per frame in `FUN_71017547f0`, making frame-level rollback well-defined.

6. **C-stick statefulness is a complication**: The smash charge delay counter (`param_5[3]`, `param_5[9]`) in `fim_cstick_handler` accumulates across frames. This state must be saved/restored for correct rollback.
