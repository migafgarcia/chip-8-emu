//
// Created by migafgarcia on 25-02-2019.
//


#include "Chip8.h"

const uint8_t Chip8::chip8_fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, //0
	0x20, 0x60, 0x20, 0x20, 0x70, //1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
	0x90, 0x90, 0xF0, 0x10, 0x10, //4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
	0xF0, 0x10, 0x20, 0x40, 0x40, //7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
	0xF0, 0x90, 0xF0, 0x90, 0x90, //A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
	0xF0, 0x80, 0x80, 0x80, 0xF0, //C
	0xE0, 0x90, 0x90, 0x90, 0xE0, //D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
	0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

void Chip8::emulate_cycle() {

    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];

    std::cout << "Executing " << std::hex << opcode << std::endl;

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x000F) {
                case 0x0000: // 0x00E0: Clears the screen.
                    std::cerr << "Screen Cleared" << std::endl;
					for (int i = 0; i < 2048; ++i)
						pixels[i] = 0x0;
                    pc += 2;
                    break;
                case 0x000E: // 0x00EE: Returns from subroutine.
                    --sp;
                    pc = stack[sp];
                    pc += 2;
                    break;
                default:
					throw "Unknown opcode: " + std::to_string(opcode);
            }
            break;
        case 0x1000: // Jumps to address NNN.
            pc = opcode & 0x0FFF;
            break;
        case 0x2000: // Calls subroutine at NNN.
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
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
            registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            pc += 2;
            break;
        case 0x7000: // Adds NN to VX. (Carry flag is not changed)
            registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
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
                    registers[0xF] = registers[(opcode & 0x0F00) >> 8] & 0x0001;
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
            break;
        case 0x9000:
            if (registers[(opcode & 0x0F00) >> 8] != registers[(opcode & 0x00F0) >> 4])
                pc += 2;
            pc += 2;
            break;
        case 0xA000:
            index = opcode & 0x0FFF;
            pc += 2;
            break;
        case 0xB000:
            pc = opcode & 0x0FFF + registers[0];
            break;
        case 0xC000:
            registers[(opcode & 0x0F00) >> 8] = random(rng) & (opcode & 0x0FFF);
            pc += 2;
            break;
		case 0xD000: {
			std::cerr << "Draw Sprite" << std::endl;
			uint8_t x = registers[(opcode & 0x0F00) >> 8];
			uint8_t y = registers[(opcode & 0x00F0) >> 4];
			uint8_t height = opcode & 0x000F;
			uint8_t pixel;

			registers[0xF] = 0;

			for (int col = 0; col < height; col++) {
				pixel = memory[index + col];
				for (int row = 0; row < 8; row++) {
					if ((pixel & (0x80 >> row)) != 0) {
						if (pixels[(x + row + ((y + col) * width))] == 1) 
							registers[0xF] = 1;
						pixels[x + row + ((y + col) * width)] ^= 1;
					}
				}
			}
			pc += 2;
			break;
		}
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
            break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    registers[(opcode & 0x0F00) >> 8] = delay_timer;
                    pc += 2;
                    break;
                case 0x000A:
                    std::cerr << "Key Press" << std::endl;
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
                    index = registers[(opcode & 0x0F00) >> 8] * 0x5;
                    pc += 2;
                    break;
                case 0x0033:
                    memory[index] = registers[(opcode & 0x0F00) >> 8] / 100;
                    memory[index + 1] =(registers[(opcode & 0x0F00) >> 8] / 10) % 10;
                    memory[index + 2] = (registers[(opcode & 0x0F00) >> 8] % 100) % 10;
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
            break;
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



	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for (int i = 0; i < width * height; i++) {
		if (pixels[i] == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderDrawPoint(renderer, i % width, i / width);


	}

	SDL_RenderPresent(renderer);
	

}

Chip8::Chip8(SDL_Renderer* renderer) : renderer{ renderer } {
	for (int i = 0; i < 80; ++i)
		memory[i] = Chip8::chip8_fontset[i];
}

void Chip8::read_rom(const std::string filename) {
	std::ifstream fl;
	fl.open(filename, std::ifstream::binary);
	fl.seekg(0, std::ios::end);
	size_t len = fl.tellg();
	fl.seekg(0, std::ios::beg);
	fl.read(reinterpret_cast<char*>(memory + 512), len);
	fl.close();
}






