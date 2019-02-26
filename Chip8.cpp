//
// Created by migafgarcia on 25-02-2019.
//

#include <iostream>
#include <string>
#include "Chip8.h"

void Chip8::emulate_cycle() {

    uint16_t opcode = memory[pc];
    opcode >>= 8;
    opcode |= memory[pc + 1];

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x000F) {
                case 0x0000: // 0x00E0: Clears the screen.
                    std::cerr << "Opcode " << std::to_string(opcode) << " not implemented" << std::endl;
                    break;
                case 0x000E: // 0x00EE: Returns from subroutine.
                    --sp;
                    pc = stack[sp];
                    pc += 2;
                    break;
                default:
                    throw "Unknown opcode: " + std::to_string(opcode);
            }
        case 0x1000: // Jumps to address NNN.
            pc = static_cast<uint16_t>(opcode & 0x0FFF);
            break;
        case 0x2000: // Calls subroutine at NNN.
            stack[sp] = pc;
            ++sp;
            pc = static_cast<uint16_t>(opcode & 0x0FFF);
            break;
        case 0x3000: // Skips the next instruction if VX equals NN.
            if (registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
                pc += 2;
            pc += 2;
            break;
        case 0x4000: // Skips the next instruction if VX doesn't equal NN.
            if (registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
                pc += 2;
            pc += 2;
            break;
        case 0x5000: // Skips the next instruction if VX equals VY.
            if (registers[(opcode & 0x0F00) >> 8] == registers[(opcode & 0x00F0) >> 4])
                pc += 2;
            pc += 2;
            break;
        case 0x6000: // Sets VX to NN.
            registers[(opcode & 0x0F00) >> 8] = static_cast<uint8_t>(opcode & 0x00FF);
            pc += 2;
            break;
        case 0x7000: // Adds NN to VX. (Carry flag is not changed)
            registers[(opcode & 0x0F00) >> 8] += static_cast<uint8_t>(opcode & 0x00FF);
            pc += 2;
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0001:
                    registers[(opcode & 0x0F00) >> 8] |= registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0002:
                    registers[(opcode & 0x0F00) >> 8] &= registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0003:
                    registers[(opcode & 0x0F00) >> 8] ^= registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0004: // Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
                    if (registers[(opcode & 0x00F0) >> 4] > (0xFF - registers[(opcode & 0x0F00) >> 8]))
                        registers[0xF] = 1;
                    else
                        registers[0xF] = 0;
                    registers[(opcode & 0x0F00) >> 8] += registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0005:
                    if (registers[(opcode & 0x00F0) >> 4] > registers[(opcode & 0x0F00) >> 8])
                        registers[0xF] = 0;
                    else
                        registers[0xF] = 1;
                    registers[(opcode & 0x0F00) >> 8] -= registers[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
                case 0x0006:
                    registers[0xF] = static_cast<uint8_t>(registers[(opcode & 0x0F00) >> 8] & 0x0001);
                    registers[(opcode & 0x0F00) >> 8] >>= 1;
                    pc += 2;
                    break;
                case 0x0007:
                    if (registers[(opcode & 0x00F0) >> 4] > registers[(opcode & 0x0F00) >> 8])
                        registers[0xF] = 0;
                    else
                        registers[0xF] = 1;
                    registers[(opcode & 0x0F00) >> 8] =
                            registers[(opcode & 0x00F0) >> 4] - registers[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x000E:
                    registers[0xF] = registers[(opcode & 0x0F00) >> 8] >> 7;
                    registers[(opcode & 0x0F00) >> 8] <<= 1;
                    pc += 2;
                    break;
                default:
                    throw "Unknown opcode: " + std::to_string(opcode);
            }
        case 0x9000:
            if (registers[(opcode & 0x0F00) >> 8] != registers[(opcode & 0x00F0) >> 4])
                pc += 2;
            pc += 2;
            break;
        case 0xA000:
            index = static_cast<uint16_t>(opcode & 0x0FFF);
            pc += 2;
            break;
        case 0xB000:
            pc = static_cast<uint16_t>(opcode & 0x0FFF) + registers[0];
            break;
        case 0xC000:
            registers[(opcode & 0x0F00) >> 8] = static_cast<uint8_t>(random(rng) & (opcode & 0x0FFF));
            pc += 2;
            break;
        case 0xD000:
            std::cerr << "Opcode " << std::to_string(opcode) << " not implemented" << std::endl;
            pc += 2;
            break;
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    if(keys[registers[(opcode & 0x0F00) >> 8]] != 0)
                        pc += 2;
                    pc += 2;
                    break;
                case 0x00A1:
                    if(keys[registers[(opcode & 0x0F00) >> 8]] == 0)
                        pc += 4;
                    pc += 2;
                    break;
                default:
                    throw "Unknown opcode: " + std::to_string(opcode);
            }
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    registers[(opcode & 0x0F00) >> 8] = delay_timer;
                    pc += 2;
                    break;
                case 0x000A:
                    std::cerr << "Opcode " << std::to_string(opcode) << " not implemented" << std::endl;
                    pc += 2;
                    break;
                case 0x0015:
                    delay_timer = registers[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x0018:
                    sound_timer = registers[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x001E:
                    if(index + registers[(opcode & 0x0F00) >> 8] > 0xFFF)
                        registers[0xF] = 1;
                    else
                        registers[0xF] = 0;
                    index += registers[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                case 0x0029:
                    index = static_cast<uint16_t>(registers[(opcode & 0x0F00) >> 8] * 0x5);
                    pc += 2;
                    break;
                case 0x0033:
                    memory[index] = static_cast<uint8_t>(registers[(opcode & 0x0F00) >> 8] / 100);
                    memory[index + 1] = static_cast<uint8_t>((registers[(opcode & 0x0F00) >> 8] / 10) % 10);
                    memory[index + 2] = static_cast<uint8_t>((registers[(opcode & 0x0F00) >> 8] % 100) % 10);
                    pc += 2;
                    break;
                case 0x0055:
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                        memory[index + i] = registers[i];
                    index += ((opcode & 0x0F00) >> 8) + 1;
                    pc += 2;
                    break;
                case 0x0065:
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                        registers[i] = memory[index + i];
                    index += ((opcode & 0x0F00) >> 8) + 1;
                    pc += 2;
                    break;
                default:
                    throw "Unknown opcode: " + std::to_string(opcode);
            }
        default:
            throw "Unknown opcode: " + std::to_string(opcode);
    }

    if (delay_timer > 0)
        --delay_timer;

    if (sound_timer > 0) {
        if (sound_timer == 1)
            std::cout << "Beep" << std::endl;
        --sound_timer;
    }

}

Chip8::Chip8() {}



