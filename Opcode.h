//
// Created by migafgarcia on 25-02-2019.
//

#ifndef CHIP_8_EMU_OPCODE_H
#define CHIP_8_EMU_OPCODE_H

#include <cstdint>
#include <string>

struct Opcode {
    uint16_t opcode;
    std::string opcode_str;
};

#endif //CHIP_8_EMU_OPCODE_H
