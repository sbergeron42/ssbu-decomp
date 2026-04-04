# Worker: pool-a

## Model: Opus

## Task: Decomp frame data exchange — what gets sent per frame over UDP

Continue the networking decomp. The session manager (net_session_mgr.cpp) calls into frame-level data exchange. Trace what actually gets sent/received each frame.

### Key addresses from src/docs/networking.md
- Game data send: 0x710012b530
- Game data recv: 0x710012ac30
- Game data reply: 0x710012ba00
- Socket sendto wrapper: 0x71000ba5c0
- Socket recvfrom wrapper: 0x71000ba450
- Frame sync functions in 0x710016xxxx-0x710019xxxx

### Progress
- net_frame_exchange.cpp: 5 functions compilable (send, recv, reply + 2 helpers)
  - FUN_710012b530 (1,220B), FUN_710012ac30 (2,060B), FUN_710012ba00 (2,624B)
  - FUN_710012cf80 (128B), FUN_710012ed20 (744B)
  - These compile but don't byte-match — NX Clang scheduling differences
- net_session_mgr.cpp: 4 new functions (1 matching 100%)
  - FUN_7100190a90, FUN_710019b8b0 (100%), FUN_7100192e90, FUN_7100190270
- ldn_transport.cpp: 4 new functions (2 matching)
  - FUN_710017f1d0 (100%), FUN_7100172880 (100%), FUN_710017dcc0, FUN_7100177d40

### Key finding
Most helper functions in the 0x710012xxxx frame exchange call chain were
ALREADY compiled in batch files (fun_easy_*.cpp, fun_batch_*.cpp). All
confirmed matching 100%. The three main frame exchange functions compile
but have fundamental register allocation/scheduling differences from the
NX Clang fork, making byte-level matching very difficult without asm
reference files.

### Next steps
- Find more uncompiled functions in 0x710016xxxx-0x710019xxxx range
- 70+ uncompiled candidates under 300 bytes identified
- Focus on trivial getters/setters for matching
- Consider naked asm for the main send/recv/reply if matching needed

### Output
- src/app/networking/net_frame_exchange.cpp
- Update src/docs/networking.md with frame exchange findings
- include/app/NetFrameData.h if new structs are discovered

### Efficiency rules (MANDATORY)
- Build once: cmd /c build.bat 2>&1 | tee /tmp/build.txt then grep the file
- Save Ghidra results to /tmp/ghidra_results.txt
- 3-attempt limit per function, then skip or naked asm
- Do NOT edit tools/ or fix infrastructure

### Rules
- CAN edit: src/app/networking/*.cpp, include/app/*.h, src/docs/networking.md
- Do NOT edit other source files or tools/
