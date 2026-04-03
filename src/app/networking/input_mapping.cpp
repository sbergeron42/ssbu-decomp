// =============================================================================
// SSBU Input Mapping Pipeline
//
// Decompilation of the core input pipeline: hardware polling -> button mapping
// -> game-consumable input. These functions run every frame and are the
// foundation for both local and network play.
//
// Addresses:
//   input_poll_all_players  @ 0x71017547f0
//   final_input_mapping     @ 0x7101750f70
//   normalize_stick         @ 0x7101752390
//   fim_cstick_handler      @ 0x7101752a10
//
// See include/app/InputState.h for struct definitions and flag constants.
// See src/docs/input_handling.md for full pipeline documentation.
// =============================================================================

#include "app/InputState.h"
#include <cstdlib>  // abort()
#include <cmath>    // fabsf

// External param lookup function (hash-based binary search in param data)
// Address: 0x710175ff70
extern void* param_lookup(void* param_manager, uint64_t hash);

// Global param manager instance
// DAT_71052c4160 in Ghidra
extern void* g_param_manager;

// Stick normalization scale factor: converts float range to int8 (-127..127)
// DAT_7104471fac in Ghidra — value is 127.0f
extern float g_stick_scale;   // = 127.0f

// Guard variable for one-time initialization
extern uint8_t g_guard_var;   // DAT_71052b82e0
extern char    g_guard_flag;  // DAT_71052b82f0
extern int     g_guard_val;   // DAT_71052b82e8

// Team battle params
extern uint8_t g_team_param_init_guard;  // g_team_param_init_guard
extern uint32_t g_team_mode;             // DAT_71052c4188
extern uint16_t g_team_count;            // DAT_71052c418a

// Forward declarations for C runtime guard functions
extern "C" int __cxa_guard_acquire(void*);
extern "C" void __cxa_guard_release(void*);
extern void global_param_init_sets_team_flag();

// =============================================================================
// input_poll_all_players — Per-frame input polling loop
// Address: 0x71017547f0
//
// Called once per frame from the scene update path. For each of 8 player slots:
//   1. Looks up the controller assigned to that slot
//   2. Handles controller disconnection (3-frame grace period)
//   3. Calls final_input_mapping to produce an 8-byte MappedInput
//   4. After the loop, applies network override slots (the injection point
//      for remote player inputs in online play)
//
// Returns true always (signals frame was processed).
//
// ROLLBACK NOTE: This function is the main entry point that would need to be
// called during rollback resimulation. The override slots at 0x540-0x578 are
// where replayed/predicted inputs would be injected.
// =============================================================================
bool input_poll_all_players(InputPollStruct* input)
{
    for (int player_idx = 0; player_idx < INPUT_MAX_PLAYERS; player_idx++) {

        uint32_t controller_id = input->controller_ids[player_idx];
        ControllerStruct* controller;

        // Look up controller for this player slot.
        // If the controller subsystem hasn't been initialized yet (flag == '\0'),
        // use the default controller. Otherwise, index into the global array.
        if (controller_id < INPUT_MAX_CONTROLLERS) {
            if (g_controller_subsystem_flag == '\0') {
                // Subsystem not yet initialized — use default
                controller = &g_default_controller;
            } else {
                controller = g_controller_array[controller_id];
                if (controller == nullptr) {
                    // No controller at this index — zero out input for this slot
                    goto zero_input;
                }
            }
        } else {
            // Invalid controller ID — zero out input
            goto zero_input;
        }

        // Disconnection handling: the controller struct has an "active" flag at
        // +0x10 -> +0xB8. If inactive, we give a 3-frame grace period before
        // zeroing input, to ride out momentary disconnects.
        {
            char active = *(char*)((char*)controller->npad_state + 0xB8);

            if (active == '\0') {
                // Controller reports inactive — increment disconnect counter
                uint8_t count = input->disconnect_counter[player_idx];
                if (count > 2) {
                    // Already past grace period
                    goto zero_input;
                }
                count++;
                input->disconnect_counter[player_idx] = count;
                if (count > 2) {
                    // Just exceeded grace period this frame
                    goto zero_input;
                }
            } else {
                // Controller is active — reset disconnect counter
                input->disconnect_counter[player_idx] = 0;
            }
        }

        // Map raw controller input to game input.
        // arg5 is true only for player 0 when player0_special_flag is set
        // (suppresses certain button mappings, possibly for menu/UI contexts).
        final_input_mapping(
            input->mappings,
            player_idx,
            &input->mapped_inputs[player_idx],
            controller,
            (player_idx == 0) && (input->player0_special_flag != 0)
        );
        continue;

    zero_input:
        // No valid controller or disconnected — write zero input
        *(uint64_t*)&input->mapped_inputs[player_idx] = 0;
    }

    // =========================================================================
    // INPUT OVERRIDE MECHANISM — CRITICAL FOR NETWORK PLAY
    //
    // After computing local input for all 8 players, check each player's
    // override flag. If set, REPLACE the locally-computed input with the
    // override data. This is how remote player inputs get injected:
    //
    //   - Local player:  override_enable = 0, uses real controller input
    //   - Remote player: override_enable = 1, uses network-received input
    //
    // The override data at 0x540-0x578 is written by the network receive path
    // before this function runs (or between frames).
    //
    // After applying overrides, the override slots are cleared to zero,
    // ready for the next frame's network data.
    // =========================================================================
    for (int i = 0; i < INPUT_MAX_PLAYERS; i++) {
        if (input->override_enable[i] != 0) {
            input->mapped_inputs[i] = input->override_inputs[i];
        }
    }

    // Clear all override slots for next frame
    for (int i = 0; i < INPUT_MAX_PLAYERS; i++) {
        *(uint64_t*)&input->override_inputs[i] = 0;
    }

    return true;
}

// =============================================================================
// Helper: map_button_to_flags
//
// Given a mapping byte from the per-player mapping table, returns the
// corresponding button flag bits and updates jump/shield counters.
// This is the core of the repeated pattern in final_input_mapping.
// =============================================================================
static inline uint32_t map_button_to_flags(uint8_t mapping_byte,
                                           uint32_t* jump_count,
                                           uint32_t* shield_count)
{
    if (mapping_byte == MAP_UNBOUND) {
        return 0;
    }
    if (mapping_byte == MAP_JUMP_ATTACK) {
        // Jump+Attack macro — sets bits 3+4 (0x18)
        return BTN_JUMP_MACRO;
    }

    uint32_t flag = 1u << (mapping_byte & 0x1F);

    if (mapping_byte == MAP_JUMP) {
        (*jump_count)++;
    } else if (mapping_byte == MAP_SHIELD) {
        (*shield_count)++;
    }

    return flag;
}

// =============================================================================
// Helper: apply_common_postprocess
//
// After accumulating all button flags, applies mirror bits, grab macro logic,
// appeal flag, shoulder shield check, and jump/shield multi-press detection.
// Used by all three controller style paths.
// =============================================================================
static uint32_t apply_common_postprocess(uint32_t raw_flags,
                                         uint32_t hw_buttons,
                                         uint32_t shoulder_mask,
                                         PerPlayerMapping* mapping,
                                         int player_idx,
                                         bool grab_macro_enabled,
                                         bool appeal_enabled,
                                         uint8_t special_map_byte,
                                         uint32_t jump_count,
                                         uint32_t shield_count)
{
    uint32_t flags = raw_flags;

    // Mirror attack bit to bit 9
    if (flags & BTN_ATTACK) {
        flags |= BTN_ATTACK_MIRROR;
    }

    // Mirror special bit to bits 11 + 15 (SPECIAL_MIRROR + APPEAL area)
    if (flags & BTN_SPECIAL) {
        flags |= BTN_SPECIAL_MIRROR | BTN_SPECIAL_BOTH;
    }

    // Grab macro: if attack + special are both pressed simultaneously,
    // track this state. On the first frame both are pressed, convert to grab.
    // On subsequent frames of holding both, suppress both to prevent
    // unintended attack/special inputs.
    if (grab_macro_enabled) {
        if ((flags & (BTN_ATTACK | BTN_SPECIAL)) == (BTN_ATTACK | BTN_SPECIAL)) {
            // Both pressed — set grab macro state, replace with grab
            mapping[player_idx].grab_macro_state = 1;
            flags = (flags & ~BTN_SPECIAL) | BTN_GRAB;
        } else {
            if ((flags & (BTN_ATTACK | BTN_SPECIAL)) == 0) {
                // Neither pressed — clear state
                mapping[player_idx].grab_macro_state = 0;
            } else if (mapping[player_idx].grab_macro_state != 0) {
                // One still held from a grab — suppress both
                flags &= ~(BTN_ATTACK | BTN_SPECIAL);
            }
        }
    }

    // Appeal / taunt button
    if (appeal_enabled) {
        flags |= BTN_APPEAL;
    }

    // Shoulder shield check: if both L+R shoulder buttons are pressed,
    // set the shield flag
    if ((~hw_buttons & shoulder_mask) == 0) {
        flags |= BTN_SHIELD_L;
    }

    // Special case: if the button mapped to value 0x0B (unused special value)
    // is active, inherit D-pad taunt flags from hardware
    if (special_map_byte == 0x0B) {
        if (hw_buttons & 0x08) flags |= BTN_TAUNT_DOWN;
        if (hw_buttons & 0x02) flags |= BTN_TAUNT_UP;
    }

    // Shield double: two or more shield-mapped buttons pressed
    if (shield_count >= 2) {
        flags |= BTN_SHIELD_DOUBLE;
    }

    // Short hop: two or more jump-mapped buttons pressed
    if (jump_count >= 2) {
        flags |= BTN_JUMP_MINI;
    }

    return flags;
}

// =============================================================================
// final_input_mapping — Core button mapping function
// Address: 0x7101750f70
//
// Maps raw controller buttons to the game's internal button bitfield format.
// Handles three controller style paths:
//   - Type 7 (Pro Controller):    mapping table offsets 0x00-0x0E
//   - Types 1-6 (Standard):       mapping table offsets 0x0F-0x1E
//   - Types 3-4 (D-pad modes):    mapping table offsets 0x1F-0x2A
//
// The per-player mapping table (0x50 bytes, see PerPlayerMapping) contains
// mapping bytes that translate physical buttons to game actions.
//
// DETERMINISM NOTE: This function is nearly pure — the only mutable state is
// the grab macro byte at mapping+0x33. Given the same raw controller state and
// mapping table, it produces the same output. This makes it safe for rollback
// replay, provided the grab macro state is saved/restored.
// =============================================================================
void final_input_mapping(PerPlayerMapping* mappings, int player_idx,
                         MappedInput* out, ControllerStruct* controller, bool arg)
{
    if (player_idx == -1) {
        return;
    }
    if ((unsigned)player_idx > 7) {
        abort();
    }

    // Zero output
    *(uint64_t*)out = 0;

    if (controller == nullptr) {
        return;
    }

    NpadStateMinimal* npad = controller->npad_state;
    int style = npad->style_type;
    PerPlayerMapping* map = &mappings[player_idx];
    uint32_t hw = npad->raw_buttons;

    uint32_t flags = 0;
    uint32_t jump_count = 0;
    uint32_t shield_count = 0;

    // =========================================================================
    // PATH 1: Pro Controller (style type 7)
    // Uses mapping table offsets 0x00-0x0E (map->pro_button[])
    //
    // Hardware button bit layout for Pro Controller:
    //   Bit 0:  A button       -> map->pro_button[3]
    //   Bit 1:  B button       -> map->pro_button[1] (only when guard_flag == 0)
    //   Bit 2:  X button       -> map->pro_button[5]
    //   Bit 3:  Y button (also bit 1) -> map->pro_button[4]
    //   Bit 4:  L trigger      -> map->pro_button[10]  (aka ZL analog)
    //   Bit 5:  R bumper       -> map->pro_button[6]   (aka R)
    //   Bit 6:  ZR trigger     -> map->pro_button[7]
    //   Bit 7:  ZL bumper      -> map->pro_button[9]   (aka L)
    //   Bit 8:  Minus/Plus     -> map->pro_button[0]   (only when !arg)
    //   Bit 9:  Home/Capture   -> map->pro_button[1]
    //   Bit 10: (unused)
    //   Bit 11: SL/SR          -> map->pro_button[2]   (only when guard_flag == 0)
    // =========================================================================
    if (style == CTRL_STYLE_PRO) {
        // R bumper (bit 5)
        if (hw & (1 << 5)) {
            flags |= map_button_to_flags(map->pro_button[6], &jump_count, &shield_count);
        }
        // ZR trigger (bit 6)
        if (hw & (1 << 6)) {
            flags |= map_button_to_flags(map->pro_button[7], &jump_count, &shield_count);
        }
        // L trigger / ZL analog (bit 4)
        if (hw & (1 << 4)) {
            flags |= map_button_to_flags(map->pro_button[10], &jump_count, &shield_count);
        }
        // ZL bumper (bit 7)
        if (hw & (1 << 7)) {
            flags |= map_button_to_flags(map->pro_button[9], &jump_count, &shield_count);
        }
        // Minus/Plus (bit 8) — suppressed when arg is true (player 0 special)
        if ((hw & (1 << 8)) && !arg) {
            flags |= map_button_to_flags(map->pro_button[0], &jump_count, &shield_count);
        }

        // One-time guard initialization
        if ((g_guard_var & 1) == 0) {
            int r = __cxa_guard_acquire(&g_guard_var);
            if (r != 0) {
                __cxa_guard_release(&g_guard_var);
            }
        }

        // Re-read hw buttons (may have been updated by guard init)
        hw = npad->raw_buttons;

        // SL/SR (bit 11) — only when guard_flag is clear
        if (g_guard_flag == '\0' && (hw & (1 << 11))) {
            flags |= map_button_to_flags(map->pro_button[2], &jump_count, &shield_count);
        }
        // Home/Capture (bit 9)
        if (hw & (1 << 9)) {
            flags |= map_button_to_flags(map->pro_button[1], &jump_count, &shield_count);
        }
        // A button (bit 0)
        if (hw & 1) {
            flags |= map_button_to_flags(map->pro_button[3], &jump_count, &shield_count);
        }
        // Y button (bits 1+3)
        if (hw & 0x0A) {
            flags |= map_button_to_flags(map->pro_button[4], &jump_count, &shield_count);
        }
        // X button (bit 2)
        if (hw & (1 << 2)) {
            flags |= map_button_to_flags(map->pro_button[5], &jump_count, &shield_count);
        }

        // Post-process: mirrors, grab macro, appeal, shield, short hop
        flags = apply_common_postprocess(
            flags, hw,
            0x60,  // shoulder mask: bits 5+6 (R + ZR)
            mappings, player_idx,
            map->pro_ab_grab != 0,
            map->pro_appeal != 0,
            map->pro_button[4],
            jump_count, shield_count
        );

        out->buttons = flags;

        // Normalize main stick
        float stick_normalized[2] = {0, 0};
        normalize_stick(stick_normalized, (float*)&npad->stick_data[0], style);
        out->stick_x = (int8_t)(int)(g_stick_scale * stick_normalized[0]);
        out->stick_y = (int8_t)(int)(g_stick_scale * stick_normalized[1]);

        // C-stick processing
        int sc = (int)shield_count;
        int jc = (int)jump_count;
        fim_cstick_handler(out, npad, map->pro_cstick_mode, map->std_cstick_mode,
                           map->cstick_config, &sc, &jc);
        return;
    }

    // =========================================================================
    // PATH 2: Standard controllers (style types 1, 2, 4, 5, 6)
    // Uses mapping table offsets 0x0F-0x1E (map->std_button[])
    //
    // These are types where (style-1) & 0x33 has bit set, i.e. types 1,2,4,5,6
    // Same button iteration logic as Pro but with different mapping table offsets.
    // =========================================================================
    if (style >= 1 && style <= 6 && ((0x33u >> ((style - 1) & 0x1F)) & 1)) {
        // Standard controller path — same pattern as Pro but using std_button[]
        // R bumper (bit 5)
        if (hw & (1 << 5)) {
            flags |= map_button_to_flags(map->std_button[7], &jump_count, &shield_count);
        }
        // ZR (bit 6)
        if (hw & (1 << 6)) {
            flags |= map_button_to_flags(map->std_button[8], &jump_count, &shield_count);
        }
        // L trigger (bit 4)
        if (hw & (1 << 4)) {
            flags |= map_button_to_flags(map->std_button[10], &jump_count, &shield_count);
        }
        // ZL (bit 7)
        if (hw & (1 << 7)) {
            flags |= map_button_to_flags(map->std_button[11], &jump_count, &shield_count);
        }

        // One-time guard init (same as Pro path)
        if ((g_guard_var & 1) == 0) {
            int r = __cxa_guard_acquire(&g_guard_var);
            if (r != 0) {
                __cxa_guard_release(&g_guard_var);
            }
        }

        hw = npad->raw_buttons;

        // Plus button (bit 8) — only when guard_flag clear
        if (g_guard_flag == '\0' && (hw & (1 << 8))) {
            flags |= map_button_to_flags(map->std_button[0], &jump_count, &shield_count);
        }
        // Capture (bit 9)
        if (hw & (1 << 9)) {
            flags |= map_button_to_flags(map->std_button[1], &jump_count, &shield_count);
        }
        // Minus (bit 10) — suppressed when arg is true
        if ((hw & (1 << 10)) && !arg) {
            flags |= map_button_to_flags(map->std_button[2], &jump_count, &shield_count);
        }
        // SL (bit 11)
        if (hw & (1 << 11)) {
            flags |= map_button_to_flags(map->std_button[3], &jump_count, &shield_count);
        }
        // A (bit 0)
        if (hw & 1) {
            flags |= map_button_to_flags(map->std_button[4], &jump_count, &shield_count);
        }
        // Y (bits 1+3)
        if (hw & 0x0A) {
            flags |= map_button_to_flags(map->std_button[5], &jump_count, &shield_count);
        }
        // X (bit 2)
        if (hw & (1 << 2)) {
            flags |= map_button_to_flags(map->std_button[6], &jump_count, &shield_count);
        }

        flags = apply_common_postprocess(
            flags, hw,
            0x60,  // shoulder mask
            mappings, player_idx,
            map->std_ab_grab != 0,
            map->std_appeal != 0,
            map->std_button[5],
            jump_count, shield_count
        );

        out->buttons = flags;

        // Normalize stick
        float stick_normalized[2] = {0, 0};
        normalize_stick(stick_normalized, (float*)&npad->stick_data[0], style);
        out->stick_x = (int8_t)(int)(g_stick_scale * stick_normalized[0]);
        out->stick_y = (int8_t)(int)(g_stick_scale * stick_normalized[1]);

        // C-stick
        int sc = (int)shield_count;
        int jc = (int)jump_count;
        fim_cstick_handler(out, npad, map->std_cstick_mode, map->pro_cstick_mode,
                           map->cstick_config, &sc, &jc);
        return;
    }

    // =========================================================================
    // PATH 3: D-pad modes (style types 3 and 4)
    // Uses mapping table offsets 0x1F-0x2A (map->dpad_button[])
    //
    // Style 3 = Right Joy-Con (axes inverted)
    // Style 4 = Left Joy-Con
    //
    // D-pad controllers map directional buttons and a reduced set of face
    // buttons. The hardware bit assignments change between left and right
    // Joy-Con because the physical buttons are in different positions.
    //
    // Unlike the other paths, D-pad mode does NOT use fim_cstick_handler
    // (no C-stick on a single Joy-Con). It also handles stick axis inversion
    // for the right Joy-Con (type 3).
    // =========================================================================
    if (style < 3 || style > 4) {
        return;
    }

    bool is_right_joycon = (style == CTRL_STYLE_RIGHT_JOYCON);

    // D-pad direction masks differ between left and right Joy-Con
    uint32_t mask_up    = is_right_joycon ? 0x02 : 0x80;
    uint32_t mask_right = is_right_joycon ? 0x04 : 0x10;
    uint32_t mask_down  = is_right_joycon ? 0x01 : 0x40;
    uint32_t mask_left  = is_right_joycon ? 0x08 : 0x20;
    uint32_t mask_extra = is_right_joycon ? 0x10000 : 0x20000;

    // Up direction -> map->dpad_button[4] (offset 0x23)
    if (hw & mask_up) {
        if (hw & mask_extra) {
            // Digital input mode — map to fixed taunt flag
            flags |= 0x400;
        } else {
            flags |= map_button_to_flags(map->dpad_button[4], &jump_count, &shield_count);
        }
    }
    // Right direction -> map->dpad_button[5] (offset 0x24)
    if (hw & mask_right) {
        if (hw & mask_extra) {
            flags |= BTN_TAUNT_DOWN;
        } else {
            flags |= map_button_to_flags(map->dpad_button[5], &jump_count, &shield_count);
        }
    }
    // Down direction -> map->dpad_button[6] (offset 0x25)
    if (hw & mask_down) {
        if (hw & mask_extra) {
            flags |= BTN_TAUNT_UP;
        } else {
            flags |= map_button_to_flags(map->dpad_button[6], &jump_count, &shield_count);
        }
    }
    // Left direction -> map->dpad_button[7] (offset 0x26)
    if (hw & mask_left) {
        if (hw & mask_extra) {
            flags |= 0x1000;
        } else {
            flags |= map_button_to_flags(map->dpad_button[7], &jump_count, &shield_count);
        }
    }

    // Guard init
    if ((g_guard_var & 1) == 0) {
        int r = __cxa_guard_acquire(&g_guard_var);
        if (r != 0) {
            __cxa_guard_release(&g_guard_var);
        }
    }

    hw = npad->raw_buttons;

    // Face buttons for D-pad mode (fewer buttons available on single Joy-Con)
    // SL (bit 8) — only when guard_flag clear
    if (g_guard_flag == '\0' && (hw & (1 << 8))) {
        flags |= map_button_to_flags(map->dpad_button[0], &jump_count, &shield_count);
    }
    // SR (bit 9)
    if (hw & (1 << 9)) {
        flags |= map_button_to_flags(map->dpad_button[0], &jump_count, &shield_count);
    }
    // Bumper (bits 10+11)
    if (hw & 0xC00) {
        flags |= map_button_to_flags(map->dpad_button[1], &jump_count, &shield_count);
    }
    // Trigger (bits 12+14) — suppressed when arg is true
    if ((hw & 0x5000) && !arg) {
        flags |= map_button_to_flags(map->dpad_button[2], &jump_count, &shield_count);
    }
    // Other (bits 13+15)
    if (hw & 0xA000) {
        flags |= map_button_to_flags(map->dpad_button[3], &jump_count, &shield_count);
    }

    // Post-process
    // Mirror bits
    if (flags & BTN_ATTACK) {
        flags |= BTN_ATTACK_MIRROR;
    }
    if (flags & BTN_SPECIAL) {
        flags |= BTN_SPECIAL_MIRROR | BTN_SPECIAL_BOTH;
    }

    // Grab macro for D-pad mode
    if (map->dpad_ab_grab != 0) {
        // (Same logic as other paths but using D-pad grab macro offset)
        if ((flags & (BTN_ATTACK | BTN_SPECIAL)) == (BTN_ATTACK | BTN_SPECIAL)) {
            map->grab_macro_state = 1;
            flags = (flags & ~BTN_SPECIAL) | BTN_GRAB;
        } else {
            if ((flags & (BTN_ATTACK | BTN_SPECIAL)) == 0) {
                map->grab_macro_state = 0;
            } else if (map->grab_macro_state != 0) {
                flags &= ~(BTN_ATTACK | BTN_SPECIAL);
            }
        }
    }

    // Appeal
    if (map->dpad_appeal != 0) {
        flags |= BTN_APPEAL;
    }

    // Shoulder shield check — mask differs for style 3 vs 4
    uint32_t dpad_shoulder_mask = is_right_joycon ? 0x0C : 0x30;
    if ((~hw & dpad_shoulder_mask) == 0) {
        flags |= BTN_SHIELD_L;
    }

    // Shield double / short hop
    if (shield_count >= 2) {
        flags |= BTN_SHIELD_DOUBLE;
    }
    if (jump_count >= 2) {
        flags |= BTN_JUMP_MINI;
    }

    out->buttons = flags;

    // Stick handling for D-pad controllers.
    // Right Joy-Con (type 3) has its stick axes inverted because the physical
    // orientation is rotated 180 degrees when held sideways.
    float stick_x, stick_y;
    float raw_x = npad->stick_data[0];
    float raw_y = npad->stick_data[1];

    if (is_right_joycon) {
        // Invert both axes for right Joy-Con held sideways
        stick_x = -raw_y;
        stick_y = raw_x;
    } else {
        // Left Joy-Con — normal but negated (held upside down sideways)
        stick_x = raw_y;
        stick_y = -raw_x;
    }

    float stick_raw[2] = { stick_x, stick_y };
    float stick_normalized[2] = {0, 0};
    normalize_stick(stick_normalized, stick_raw);
    out->stick_x = (int8_t)(int)(g_stick_scale * stick_normalized[0]);
    out->stick_y = (int8_t)(int)(g_stick_scale * stick_normalized[1]);

    // No C-stick on single Joy-Con — D-pad mode skips fim_cstick_handler
}

// =============================================================================
// normalize_stick — Analog stick normalization
// Address: 0x7101752390
//
// Applies deadzone and scaling parameters to convert raw float stick input
// to a -1.0..1.0 range. Parameters are loaded from the game's param data
// (hash 0x11d670f167) via binary search lookup.
//
// The function handles both positive and negative stick deflections with
// separate deadzone thresholds, and clamps output to [-1.0, 1.0].
//
// For Pro Controller (type 7) vs other controllers, different param hashes
// are used to look up the deadzone/sensitivity values:
//   Pro:      0x1485d5e329, 0x1463b54cc8, 0x143d69844c, 0x14db092bad
//   Standard: 0x118320c8a3, 0x115e3f3f8e, 0x11f427f835, 0x1129380f18
//
// These correspond to:
//   - inner_deadzone_x: stick must exceed this to register
//   - outer_deadzone_x: full deflection threshold
//   - inner_deadzone_y: same for Y axis
//   - outer_deadzone_y: same for Y axis
//
// Output formula (for positive X):
//   normalized = clamp((raw - inner_dz) / (outer_dz - inner_dz), 0.0, 1.0)
// For negative X:
//   normalized = clamp((inner_dz + raw) / (outer_dz - inner_dz), -1.0, 0.0)
// =============================================================================
void normalize_stick(float* out_xy, float* raw_stick_xy, int style_type)
{
    // Param lookup for deadzone values
    void** param_entry = (void**)param_lookup(g_param_manager, 0x11d670f167);
    char* param_data = (char*)param_entry[1];

    float inner_dz_x, outer_dz_x, inner_dz_y, outer_dz_y;

    // The param data is a binary-searchable structure. The game looks up
    // four float values by hash, with different hashes for Pro vs Standard.
    // For readability, we represent this as the computed result:
    // (The actual code does binary search through hash tables — see Ghidra
    //  decompilation at 0x7101752390 for the raw param lookup logic.)
    //
    // TODO: Implement the actual param hash binary search.
    // For now, document the lookup hashes:
    //   Pro Controller hashes:    0x1485d5e329, 0x1463b54cc8, 0x143d69844c, 0x14db092bad
    //   Standard controller hashes: 0x118320c8a3, 0x115e3f3f8e, 0x11f427f835, 0x1129380f18
    //
    // Each hash resolves to a float value in the param data structure.
    // Default values if lookup fails: 0.0 for all (no deadzone).

    inner_dz_x = 0.0f; // placeholder — real value from param lookup
    outer_dz_x = 0.0f;
    inner_dz_y = 0.0f;
    outer_dz_y = 0.0f;

    // (In the actual binary, the param lookup runs here. The pattern is:
    //   param_data is a tagged structure where byte 0 indicates format,
    //   followed by a binary-searchable hash table. Each entry maps a
    //   40-bit hash to a float value. The game performs binary search
    //   with hash comparison to find each deadzone parameter.)

    float raw_x = raw_stick_xy[0];
    float raw_y = raw_stick_xy[1];

    // X axis normalization
    float norm_x;
    if (raw_x >= 0.0f) {
        float range = outer_dz_x - inner_dz_x;
        float adjusted = (raw_x - inner_dz_x) / range;
        norm_x = (adjusted < 0.0f) ? 0.0f : (adjusted > 1.0f ? 1.0f : adjusted);
    } else {
        float range = outer_dz_x - inner_dz_x;
        float adjusted = (inner_dz_x + raw_x) / range;
        norm_x = (adjusted < -1.0f) ? -1.0f : (adjusted > 0.0f ? 0.0f : adjusted);
    }

    // Y axis normalization
    float norm_y;
    float y_pos = (raw_y - inner_dz_y) / (outer_dz_y - inner_dz_y);
    float y_neg = (inner_dz_y + raw_y) / (outer_dz_y - inner_dz_y);

    if (raw_y >= 0.0f) {
        norm_y = (y_pos < 0.0f) ? 0.0f : (y_pos > 1.0f ? 1.0f : y_pos);
    } else {
        norm_y = (y_neg < -1.0f) ? -1.0f : (y_neg > 0.0f ? 0.0f : y_neg);
    }

    out_xy[2] = 0; // clear upper output (Y goes to out[1], padding at out[2-3])
    out_xy[3] = 0;
    out_xy[0] = norm_x;
    out_xy[1] = norm_y;
}

// =============================================================================
// fim_cstick_handler — C-stick post-processing
// Address: 0x7101752a10
//
// Processes the right analog stick (C-stick) based on the control scheme mode.
// This function is stateful — it maintains frame counters and cached values
// across calls, which is important for rollback state management.
//
// Modes (from the cstick_mode mapping byte):
//   0 = Tilt Stick:    C-stick inputs map to tilt attacks. Sets CSTICK_ON flag
//                      and writes normalized C-stick values to output.
//   1 = Tilt variant:  Same as 0 but with different sensitivity params.
//   2 = Jump mode:     C-stick increments jump counter (for JUMP_MINI).
//   3 = Shield mode:   C-stick increments shield counter (for SHIELD_DOUBLE).
//   4 = Shield variant: Shield with different timing behavior.
//   5 = Smash Stick:   C-stick direction overwrites main stick values for
//                      smash attack input. Has frame delay logic for charge.
//                      The most complex mode.
//
// Parameters:
//   out            — MappedInput being built (may modify buttons, stick_x/y)
//   npad           — Raw NpadState for C-stick float values
//   cstick_mode    — Control scheme mode (0-5, from mapping table)
//   param_unused   — Param index for mode-specific sensitivity lookup
//   cstick_config  — 11-byte stateful config block (PerPlayerMapping+0x2B):
//                      [0]:  history tracking byte 0
//                      [1]:  history tracking byte 1
//                      [3]:  smash charge delay counter (frames)
//                      [4-5]: cached smash direction (x, y int8)
//                      [9]:  frame delay countdown
//                      [10]: tilt latch flag
//   shield_count   — Running shield button count (may be incremented)
//   jump_count     — Running jump button count (may be incremented)
//
// ROLLBACK STATE: The cstick_config block (11 bytes) must be saved/restored
// for correct rollback. Specifically:
//   - cstick_config[3] (smash charge counter) accumulates each frame in mode 5
//   - cstick_config[9] (frame delay) counts down each frame in modes 0/1/5
//   - cstick_config[10] (tilt latch) prevents re-triggering within a window
//
// The full decompilation of this function involves extensive param hash lookups
// (hash 0x12af32a7be via FUN_710175ff70) for sensitivity/deadzone values and
// frame delay parameters. The param data structure uses tagged binary search
// with 40-bit hashes. See the Ghidra decompilation at 0x7101752a10 for the
// complete implementation with all param lookups.
//
// For the purposes of understanding the input pipeline for rollback, the key
// takeaway is: this function may modify out->buttons (adding CSTICK_ON,
// JUMP_MINI, SHIELD_DOUBLE, or smash flags) and may overwrite out->stick_x/y
// (in smash stick mode 5, replacing main stick with C-stick direction).
// =============================================================================
// NOTE: Full implementation omitted — the function body is ~700 lines of param
// hash lookups and mode-dependent logic. The Ghidra decompilation is captured
// in the project's analysis notes. The key behaviors are documented above.
//
// TODO: Implement fim_cstick_handler once param data access patterns are
// better understood. The binary search param lookup (FUN_710175ff70) needs
// its own decomp first.
