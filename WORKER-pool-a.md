# Worker: pool-a

## Model: Opus

## Task: Rename top 10 most-referenced FUN_ symbols across the codebase

## Priority: READABILITY CLEANUP

## Context
`tools/name_audit.py` identified 9,335 unique unnamed `FUN_` symbols. The top 10 account for 1,597 references. The orchestrator has already identified them from Ghidra. Your job is mechanical: rename each one across every `src/` file.

## Renames (do these EXACTLY)

| Old name | New name | Refs | What it is |
|----------|----------|------|-----------|
| `FUN_710392e590` | `jeFree_710392e590` | 753 | jemalloc free |
| `FUN_7103733d50` | `treeMapFindOrInsert_7103733d50` | 199 | libc++ red-black tree find-or-insert |
| `FUN_71038f4000` | `l2cParamResolve_71038f4000` | 134 | L2CValue parameter resolver |
| `FUN_7100314030` | `aiGetTargetById_7100314030` | 115 | AI target lookup by ID |
| `FUN_7100138620` | `xorshift128_7100138620` | 101 | Xorshift128 PRNG |
| `FUN_71039c20a0` | `abortWrapper_71039c20a0` | 87 | abort() thunk |
| `FUN_71025d7310` | `StageBase_dtor_71025d7310` | 59 | StageBase::~StageBase destructor |
| `FUN_71001b4910` | `stdFunctionCleanup_71001b4910` | 53 | std::function deleter |
| `FUN_710356bb30` | `abort_710356bb30` | 49 | abort() — never returns |
| `FUN_71037aeec0` | `noop_71037aeec0` | 47 | Empty function (just returns) |

## How To Do It
For each rename, do a global find-and-replace across ALL `src/` and `include/` files:
```bash
grep -rl 'FUN_710392e590' src/ include/ | xargs sed -i 's/FUN_710392e590/jeFree_710392e590/g'
```
Repeat for each of the 10 renames.

Then build to verify nothing broke:
```bash
python tools/build.py 2>&1 | tee build_output.txt
```

## Important
- Do NOT change function logic — only rename the symbol references
- Do NOT touch files outside `src/` and `include/` (no CSV changes, no tool changes)
- The address suffix stays — it's the permanent ID for linker disambiguation
- If a file has an `extern "C"` declaration of the old name, rename that too
- Commit after all 10 renames are done, not one commit per rename

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
