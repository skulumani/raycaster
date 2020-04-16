#include "player.hpp"
#include "map.hpp"
#include "graphics.hpp"

#include <iostream> 

int main() {
    Renderer engine;
    Map grid(16);
    Player player;
        
    player.set_point_coord((Eigen::Vector2f() << 300, 300).finished());
    player.set_direction(1.5);
    float h_dist = player.cast_horizontal(grid);
    float v_dist = player.cast_vertical(grid);
    std::cout << h_dist << ", " << v_dist << std::endl;
    /* engine.gradient(); */
    engine.constant((Eigen::Vector3f() << 0.5, 0.5, 0.5).finished());
    engine.draw_map(grid);
    engine.draw_player(player, grid);
    engine.write();    
    
    return 0;
}
