cmake_minimum_required(VERSION 3.16)
project(ssbu-decomp LANGUAGES C CXX ASM)

# Include paths
include_directories(include)

# Collect source files
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

# Build as object library (no linking, just compile to .o for diffing)
add_library(ssbu-decomp OBJECT ${SOURCES})
