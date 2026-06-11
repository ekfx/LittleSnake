#define APPLICATION_DEBUG_MODE
// para release é necessario apenas omitir define.
#include <iostream>
#include "LittleSnake.h"

int main() {
    #ifdef APPLICATION_DEBUG_MODE        
        std::cerr << "APPLICATION_DEBUG_MODE\n";
    #endif

    LittleSnake Game;
    Game.Loop(); 
    
    return 0;
}