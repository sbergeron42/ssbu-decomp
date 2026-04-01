@echo off
REM Build script for SSBU decomp matching compilation
REM Uses upstream Clang 8.0.0 targeting AArch64

set CLANG=C:\llvm-8.0.0\bin\clang++.exe
set OBJDUMP=C:\llvm-8.0.0\bin\llvm-objdump.exe
set CFLAGS=-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs

if not exist build mkdir build

echo Building...
for /R src %%f in (*.cpp) do (
    echo   %%f
    %CLANG% %CFLAGS% -c "%%f" -o "build\%%~nf.o"
    if errorlevel 1 goto :error
)

REM Post-process: upstream Clang emits movz for bitmask immediates,
REM but the NX original uses orr-with-wzr. Patch to match.
echo Patching movz-^>orr...
for %%f in (build\*.o) do (
    python tools\fix_movz_to_orr.py "%%f"
)

echo.
echo Disassembly:
for %%f in (build\*.o) do (
    echo.
    echo === %%~nf ===
    %OBJDUMP% -d --no-show-raw-insn "%%f"
)

echo.
echo Build complete.
goto :eof

:error
echo Build FAILED.
exit /b 1
