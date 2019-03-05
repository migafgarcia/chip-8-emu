//
// Created by migafgarcia on 25-02-2019.
//

#ifndef CHIP_8_EMU_CPU_H
#define CHIP_8_EMU_CPU_H




#include <cstdint>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#undef main


class Chip8 {
public:
	static constexpr const uint8_t width = 64;
	static constexpr const uint8_t height = 32;

    explicit Chip8(SDL_Renderer* renderer);

	void handle_keydown(int32_t keycode);
	void handle_keyup(int32_t keycode);

	void read_rom(std::string filename);

	void emulate_cycle();

private:
	uint8_t memory[4096] = { 0 };

	uint8_t registers[16] = { 0 };
	uint16_t index = 0;
	uint16_t pc = 512;

	uint16_t stack[16] = { 0 };
	uint16_t sp = 0;

	uint8_t keys[16] = { 0 };
	uint8_t pixels[width * height] = { 0 };

	uint8_t delay_timer = 0;
	uint8_t sound_timer = 0;

    std::random_device rd;
	std::mt19937_64 rng = std::mt19937_64(rd());
	std::uniform_int_distribution<int> random = std::uniform_int_distribution<int>(0, 255);

	static const uint8_t chip8_fontset[80];

	SDL_Renderer* renderer;

};


#endif //CHIP_8_EMU_CPU_H
