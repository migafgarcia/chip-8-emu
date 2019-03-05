
#include "Chip8.h"

#include <iostream>
#include <fstream>
#include <SDL.h>

#undef main

void set_scale(SDL_Renderer *renderer, int width, int height) {
    SDL_RenderSetScale(renderer, width / Chip8::width, height / Chip8::height);
}

int main() {

    const std::string file = R"(C:\Users\migafgarcia\Downloads\c8games\TETRIS)";

    const int width = 500;
    const int height = 500;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
            "Chip8 Emulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            0
    );
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    set_scale(renderer, width, height);

    Chip8 chip8(renderer);


    chip8.read_rom(file);

    SDL_Event event;
    SDL_PollEvent(&event);

    bool quit = false;


    while (!quit) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                chip8.handle_keydown(event.key.keysym.sym);
                SDL_Log("Down %d", event.key.keysym.sym);
            } else if (event.type == SDL_KEYUP) {
                chip8.handle_keyup(event.key.keysym.sym);
                SDL_Log("Up %d", event.key.keysym.sym);
            } else if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_SHOWN:
                        SDL_Log("Window %d shown", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        SDL_Log("Window %d hidden", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        SDL_Log("Window %d exposed", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        SDL_Log("Window %d moved to %d,%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        SDL_Log("Window %d resized to %dx%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        set_scale(renderer, event.window.data1, event.window.data2);

                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        SDL_Log("Window %d size changed to %dx%d",
                                event.window.windowID, event.window.data1,
                                event.window.data2);
                        set_scale(renderer, event.window.data1, event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        SDL_Log("Window %d minimized", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        SDL_Log("Window %d maximized", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        SDL_Log("Window %d restored", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        SDL_Log("Mouse entered window %d",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        SDL_Log("Mouse left window %d", event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        SDL_Log("Window %d gained keyboard focus",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        SDL_Log("Window %d lost keyboard focus",
                                event.window.windowID);
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        SDL_Log("Window %d closed", event.window.windowID);
                        break;
                    default:
                        std::cerr << "Unknown event " << event.window.event << std::endl;
                }
            }
        }
        chip8.emulate_cycle();

        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}