//
// Created by migafgarcia on 25-02-2019.
//

#ifndef CHIP_8_EMU_CPU_H
#define CHIP_8_EMU_CPU_H


#include <cstdint>
#include <random>


class Chip8 {

    uint8_t memory[4096];

    uint8_t registers[16];
    uint16_t index;
    uint16_t pc;

    uint16_t stack[16];
    uint16_t sp;

    uint8_t keys[8];

    uint8_t delay_timer;
    uint8_t sound_timer;

    std::mt19937_64 rng = std::mt19937_64(1234);
    std::uniform_int_distribution<int> random = std::uniform_int_distribution<int>(0, 255);


public:
    void emulate_cycle();

};


#endif //CHIP_8_EMU_CPU_H
