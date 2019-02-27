//
// Created by migafgarcia on 25-02-2019.
//

#ifndef CHIP_8_EMU_CPU_H
#define CHIP_8_EMU_CPU_H



#include "glad/glad.h"

#include <cstdint>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>


class Chip8 {

    static const uint8_t width = 64;
    static const uint8_t height = 32;

	uint8_t memory[4096] = { 0 };

	uint8_t registers[16] = { 0 };
    uint16_t index = 0;
    uint16_t pc = 512;

	uint16_t stack[16] = { 0 };
    uint16_t sp = 0;

    uint8_t keys[8] = { 0 };
    uint8_t pixels[width * height] = { 0 };

    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;

    std::mt19937_64 rng = std::mt19937_64(1234); // TODO(migafgarcia): use dynamic seed
    std::uniform_int_distribution<int> random = std::uniform_int_distribution<int>(0, 255);


public:

    Chip8();

    void init_graphics();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void read_rom(const std::string filename);

    void emulate_cycle();

};


#endif //CHIP_8_EMU_CPU_H
