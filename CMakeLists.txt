cmake_minimum_required(VERSION 3.13)
project(chip_8_emu)

set(CMAKE_CXX_STANDARD 14)

add_executable(chip_8_emu main.cpp Opcode.h Chip8.cpp Chip8.h)