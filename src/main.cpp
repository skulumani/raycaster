#include "player.hpp"
#include "map.hpp"
#include "graphics.hpp"

#include <iostream> 

int main() {
    Renderer engine;
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();

    player.set_point_coord((Eigen::Vector2f() << 3.0/2 * cube_size, 3.0/2 * cube_size).finished());
    player.set_direction(0.0*PI);

    float dist = player.cast(grid); 

    std::cout << "Dist: " << dist << std::endl;
    Eigen::Vector2f endpoint = player.cast_endpoint(dist);
    std::cout << "endpoint: " << endpoint.transpose() << std::endl;

    /* engine.gradient(); */
    engine.constant((Eigen::Vector3f() << 0.5, 0.5, 0.5).finished());
    engine.draw_map(grid);
    engine.draw_player(player, grid);
    engine.draw_point(grid, endpoint);
    engine.draw_line(player.get_point_coord(), endpoint, grid);
    // draw wall intersection point
    
    engine.write();    
    
    return 0;
}
