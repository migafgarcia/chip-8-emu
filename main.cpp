
#include "Chip8.h"

#include <iostream>
#include <fstream>

int main() {

    const std::string file = R"(C:\Users\migafgarcia\Downloads\Tetris [Fran Dachille, 1991].ch8)";



    Chip8 chip8;


	chip8.init_graphics();

    chip8.read_rom(file);



    for(;;) {
        try {
        chip8.emulate_cycle();
        }
        catch (char * c)
        {
            // catch anything thrown within try block that derives from std::exception
            std::cerr << c << std::endl;
        }
    }
    return 0;
}