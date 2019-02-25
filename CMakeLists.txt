cmake_minimum_required(VERSION 3.13)
project(chip_8_emu)

set(CMAKE_CXX_STANDARD 14)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("glfw")
add_subdirectory("glm")
add_subdirectory("glad")

add_executable(chip_8_emu main.cpp Opcode.h Chip8.cpp Chip8.h)

target_link_libraries(chip_8_emu glfw)
target_link_libraries(chip_8_emu glm)
target_link_libraries(chip_8_emu glad)