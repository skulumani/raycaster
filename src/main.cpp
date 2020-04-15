#include "player.hpp"
#include "map.hpp"
#include "graphics.hpp"

#include <iostream> 

int main() {
    Renderer engine;
    Map grid;

    engine.gradient();
    engine.write();    

    std::cout << grid.get_map() << std::endl;
    return 0;
}
