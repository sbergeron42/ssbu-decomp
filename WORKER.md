# Worker: pool-b

## Model: Opus

## Task: Resource service decomp — game_ldn_initialize area

### Verified Matches
- **FUN_7103741520** (1,136 bytes) — Language detection — **VERIFIED MATCH** (101/117 instructions, 16 diffs are BL relocations only)
  - Source: `src/resource/game_init.cpp`

### Ghidra Exports Available (in `asm/`)
- **game_ldn_initialize** (22,464 bytes, 4517 lines) — Full game init
- **FUN_7103747270** (~22K bytes, 3947 lines) — Post-init continuation
- **FUN_710374f360** (19,552 bytes) — ResServiceNX init — cached at `/tmp/res_service_init.txt`

### Structure of game_ldn_initialize (from Ghidra export)
1. nn::oe (Initialize, SetPerformanceConfiguration x2, SetFocusHandlingMode, DisableRecording)
2. FUN_7103747220 — vtable-based swap (module initializer pattern)
3. nn::oe::GetNotificationMessageEvent, GetOperationMode
4. nn::os::InitializeEvent + SignalEvent
5. FUN_710353d000 — thread creation (priority=5, stack=0x40000)
6. **FUN_7103741520** — language detection → DAT_710523c00c (DECOMPED)
7. **FUN_710374f360** — ResServiceNX init (param_1)
8. FUN_710353e760 — language string setup
9. FUN_71035481d0 x5 — recursive spinlock init on 5 global objects
10. NIFM network init (je_aligned_alloc + nn::nifm::Initialize + error handling)
11. Account system (0x7320 byte struct, ListAllUsers loop, GetNickname, TryOpenPreselectedUser)
12. HID controller manager (10 npad slots, nn::hid::InitializeNpad, SetSupportedNpadStyleSet(0x3f))
13. 8x FUN_7103666880(ptr, 0..7) — controller objects (0xd0 + 0x30 + 0x340 bytes each)
14. Vibration device init loop (GetVibrationDeviceHandles, InitializeVibrationDevice)
15. TouchScreen init (0x2B8 byte struct, nn::hid::InitializeTouchScreen)
16. SixAxisSensor init (0x340 byte struct, GetSixAxisSensorHandles, StartSixAxisSensor)
17. More input managers stored to globals
18. nn::prepo::Initialize
19. Resource hash table binary search + mutex poll loops (region/language lookup)
20. nn::vi::Initialize, OpenDefaultDisplay, CreateLayer, GetNativeWindow
21. Shader loading (6x FUN_710358eed0 + FUN_710353d480 for render/shader/bin/*.*)
22. 13x FUN_7103720ad0 — module init calls
23. nn::ro::Initialize (final)

### SDK Headers Modified
- `lib/NintendoSDK/include/nn/settings.h` — Added Language_SimplifiedChinese/TraditionalChinese, operator==(LanguageCode, Language)
- `include/resource/LoadedArc.h` — Added PathInformation struct

### Cached Ghidra Decompilations (in /tmp/ghidra_results.txt)
- FUN_7103741010 (ring buffer logging), FUN_7103741260/1330/1410 (time conversion)
- FUN_7103740880 (scene/resource manager tick), FUN_710374d270 (scene loading)
- FUN_710353d480 (hash40 lookup), FUN_710353e980 (file swap), FUN_710353eb70 (file release)
- FUN_710353cf40 (TLS helper), FUN_7103666880 (controller init)

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/*.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per sub-section
