
#include "Chip8.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <SDL.h>
#undef main

int main() {

	//const std::string file = R"(C:\Users\migafgarcia\Downloads\Tetris [Fran Dachille, 1991].ch8)";
	//const std::string file = R"(C:\Users\migafgarcia\Downloads\Chip8 Picture.ch8)";
	const std::string file = R"(C:\Users\migafgarcia\Downloads\myChip8-bin-src\pong2.c8)";

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
		"Chip8 Emulator",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);


	Chip8 chip8(renderer);


	chip8.init_graphics();

	chip8.read_rom(file);

	SDL_Event event;
	bool quit = false;


	while (!quit) {
		try {
			chip8.emulate_cycle();

			SDL_PollEvent(&event);

			switch (event.type) {

				case SDL_QUIT:

					quit = true;

					break;

			}
			Sleep(10);
		}
		catch (char * c)
		{
			// catch anything thrown within try block that derives from std::exception
			std::cerr << c << std::endl;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}