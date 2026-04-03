# Worker: pool-e

## Model: Opus

## Task: Build post-processing tools for register allocation divergence

4,525 non-matching functions remain. After prologue/epilogue (pool-d), the next biggest category is register allocation differences. Build tools to fix these.

### Known divergence patterns
1. Return register: mov w0,wzr vs mov x0,xzr (32-bit vs 64-bit zero)
2. Tail call register: br x1 vs br x5 (which register holds the function pointer)
3. Scratch register choice: x8 vs x9 for intermediate values
4. Parameter passing: x8 for indirect result location (C++ ABI difference)

### Approach
1. Sample 100 non-matching functions and categorize the diff patterns
2. For each pattern, determine if it can be post-processed (byte patch in .o)
3. Write fix_*.py tools for the automatable ones
4. Add to build.bat pipeline

### Also: analyze the x8-dispatch pattern more deeply
Pool-c used naked asm for 268 x8-dispatch functions. Can a post-processor fix these instead? The x8 register issue might be patchable by rewriting the mov instruction in the .o file.

### Results

#### Analysis (1,632 non-matching functions sampled)
| Category | Count | % | Automatable? |
|----------|-------|---|-------------|
| OTHER (fundamental codegen diff) | 1,301 | 79.7% | No — wrong source/decompilation |
| PCREL_ONLY (b/bl/adrp offsets) | 105 | 6.4% | Link-time only |
| X8_DISPATCH (x8 vs x9 scratch) | 97 | 5.9% | **Yes — fix_x8_regalloc.py** |
| RETURN_ZERO_WIDTH (w0 vs x0) | 25+ | 1.5% | **Yes — fix_return_width.py** |
| SCRATCH_REG (other register) | 39 | 2.4% | No — varied patterns |
| EPILOGUE_ORDER | 2 | 0.1% | Already handled |
| INSN_REORDER | 10 | 0.6% | No — too varied |

#### New tools delivered
1. **tools/analyze_regalloc.py** — Categorizes all non-matching functions by divergence type
2. **tools/fix_return_width.py** — Patches `mov w0,wzr` ↔ `mov x0,xzr` width differences (~259 patches)
3. **tools/fix_x8_regalloc.py** — Rewrites x8-dispatch register allocation from x8→x9 scratch (~96 functions)

#### Build pipeline updated
- `build.bat` now includes fix_return_width.py and fix_x8_regalloc.py after existing steps

#### X8-dispatch conclusion
The 96/97 x8-dispatch functions (9-insn pattern) can be fixed by post-processor, **eliminating the need for naked asm** in those cases. The post-processor rewrites `mov x0,x8; ldr x8,[x8]; ldr x8,[x8,#off]; blr x8` to `ldr x9,[x8]; ldr x9,[x9,#off]; mov x0,x8; blr x9`.

### Output
- New tools/fix_*.py scripts
- tools/analyze_regalloc.py analysis tool
- Analysis of which patterns are automatable vs need naked asm
- build/regalloc_analysis.csv with per-function categorization

### Rules
- ONLY create/edit files in tools/
- CAN edit build.bat to add post-processing steps
- Do NOT edit source files
- Do NOT modify data/functions.csv
