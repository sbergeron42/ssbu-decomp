set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# SDK 8.2.1 → Clang 8.0.0 (confirmed via KinokoDecomp-S / Captain Toad decomp)
if(NOT DEFINED NX_CLANG_VERSION)
    set(NX_CLANG_VERSION "8.0.0" CACHE STRING "Upstream Clang version for matching")
endif()

# Find the compiler
if(NOT DEFINED NX_CLANG_PATH)
    find_program(CMAKE_C_COMPILER clang)
    find_program(CMAKE_CXX_COMPILER clang++)
else()
    set(CMAKE_C_COMPILER "${NX_CLANG_PATH}/bin/clang")
    set(CMAKE_CXX_COMPILER "${NX_CLANG_PATH}/bin/clang++")
endif()

set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})

# Target triple
set(TRIPLE aarch64-none-elf)
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})

# Flags for matching NX release builds
# Based on KinokoDecomp-S (Captain Toad, same SDK 8.2.x generation)
# with adjustments for SSBU (cross2app engine, Bandai Namco)
set(CMAKE_C_FLAGS_INIT "\
    -target ${TRIPLE} \
    -mcpu=cortex-a57 \
    -O2 \
    -ffunction-sections \
    -fdata-sections \
    -fno-common \
    -fno-short-enums \
    -fPIC \
    -mno-implicit-float \
    -fno-strict-aliasing \
    -fno-slp-vectorize \
")

set(CMAKE_CXX_FLAGS_INIT "\
    ${CMAKE_C_FLAGS_INIT} \
    -std=c++17 \
    -fno-exceptions \
    -fno-rtti \
")

add_compile_definitions(
    MATCHING_HACK_NX_CLANG
)

# Don't try to link — we just want object files for comparison
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
