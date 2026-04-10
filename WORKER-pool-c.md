# Worker: pool-c

## Model: Opus

## Task: Phase 3 — Define FighterAI struct + rewrite AI helper functions

## Priority: TYPE RECOVERY (struct definition + consumer rewrite)

## Context
`FighterAI` is the context object for AI decision-making (~60 raw offset references across 3+ files). AI helpers in `ai_helpers_a.cpp` use macros `AI_CTX(L)` and `AI_STATE(L)` that hide raw deref chains. The reviewer rejects >10% cast density, and placeholder structs go in `include/app/placeholders/`.

## File Territory
- `include/app/placeholders/FighterAI.h` (CREATE — define FighterAI and FighterAIState)
- `src/app/ai_helpers_a.cpp` (rewrite to use struct access)
- Any other `src/` files with AI context offset access

## What To Do

### Step 1: Map the struct layout
The AI context is accessed via `*(u64*)(L - 8)` in all AI functions. Known offsets from `ai_helpers_a.cpp`:
- ctx + 0x168 = AI state object pointer
- ctx + 0x170 = analyst object pointer (status history)

The AI state object has:
- +0x274: predict_landing_frame (s32, scvtf'd to float)
- +0xd0: floor collision rect pointer
- +0xad0..+0xb74: indexed param tables

Use `mcp__ghidra__decompile_function_by_address` on functions at 0x710036xxxx (app::ai::* cluster) to map more fields.

### Step 2: Define the structs
Create `FighterAI`, `FighterAIState`, and `AIAnalyst` structs. Use `unk_0xNN` for gaps:
```cpp
struct FighterAIState {
    u8 unk_0x00[0xd0];
    void* floor_data;       // +0xd0 [derived: floor_width/floor_center read through this]
    u8 unk_0xd8[0x19c];
    s32 predict_landing;    // +0x274 [derived: predict_landing_frame reads as s32]
    // ...
};

struct FighterAI {
    u8 unk_0x00[0x168];
    FighterAIState* state;   // +0x168 [derived: all AI helpers deref this]
    void* analyst;           // +0x170 [derived: status_prev/status_count use this]
    // ...
};
```

### Step 3: Rewrite ai_helpers_a.cpp
Replace the `AI_CTX`/`AI_STATE` macros and raw offset access with typed struct access:
```cpp
// BEFORE:
float predict_landing_frame(u64 L) {
    return (float)*(s32*)(AI_STATE(L) + 0x274);
}

// AFTER:
float predict_landing_frame(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return (float)ctx->state->predict_landing;
}
```

### Step 4: Log in undefined_types.md
Add entries for FighterAI, FighterAIState, AIAnalyst with research leads.

## Rules
- Cast density must stay under 10% or your diff gets REJECTED
- Create placeholder structs for any new unknown types you encounter
- Every named field needs `[derived:]` or `[inferred:]` provenance

## Self-Check
```bash
python tools/review_diff.py pool-c
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
