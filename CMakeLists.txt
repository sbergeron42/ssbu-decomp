cmake_minimum_required(VERSION 3.16)
project(ssbu-decomp LANGUAGES C CXX ASM)

# Include paths
include_directories(include)

# Collect source files
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

# Build as shared library (linked ELF with symbol table for viking diffing)
add_library(ssbu-decomp SHARED ${SOURCES})

# Linker flags for decomp matching
target_link_options(ssbu-decomp PRIVATE
    -fuse-ld=lld
    -nostdlib
    -shared
    -fPIC
    -Wl,-Bsymbolic-functions
    -Wl,--unresolved-symbols=ignore-all
    -Wl,--no-undefined-version
)
