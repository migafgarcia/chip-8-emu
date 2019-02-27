cmake_minimum_required(VERSION 3.12)
project(chip_8_emu)

set(SDL2_DIR "./SDL2-2.0.9")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip_8_emu main.cpp Chip8.cpp Chip8.h)
target_link_libraries(chip_8_emu ${SDL2_LIBRARIES})