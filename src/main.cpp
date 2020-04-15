#include "player.hpp"
#include "map.hpp"
#include "graphics.hpp"

#include <iostream> 

int main() {
    Renderer engine;
    Map grid(32);

    engine.gradient();
    engine.draw_map(grid);
    engine.write();    

    return 0;
}
