//
// Created by migafgarcia on 25-02-2019.
//

#ifndef CHIP_8_EMU_CPU_H
#define CHIP_8_EMU_CPU_H


#include <cstdint>

class Chip8 {

    uint8_t memory[4096];

    uint8_t registers[16];
    uint16_t index;
    uint16_t pc;

    uint16_t stack[16];
    uint16_t sp;

    uint8_t keys[8];

};


#endif //CHIP_8_EMU_CPU_H
