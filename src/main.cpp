#include "player.hpp"
#include "map.hpp"
#include "graphics.hpp"

#include <iostream> 

int main(int argc, char* argv[]) {
    Renderer engine;
    Map grid(16);
    grid.fill(1,2,4);
    // set some blocks up
    //
    Player player;
    size_t cube_size = grid.get_cube_size();

    player.set_point_coord((Eigen::Vector2f() << 6.1 * cube_size, 6 * cube_size).finished());
    if (argc > 1) {
        player.set_direction(PI * atof(argv[1]));
    } else {
        player.set_direction(PI * 0.75);
    }

    float dist = std::get<0>(player.cast(player.get_direction(),grid));
    std::cout << "Dist: " << dist << std::endl;
    Eigen::Vector2f endpoint = player.cast_endpoint(dist, player.get_direction());
    std::cout << "endpoint: " << endpoint.transpose() << std::endl;
    std::cout << "grid: " << grid.point2grid(endpoint).transpose() << std::endl;

    Eigen::Vector2i pp_size = engine.get_pp_size();

    /* engine.gradient(); */
    engine.constant((Eigen::Vector3f() << 0.5, 0.5, 0.5).finished());
    engine.load_textures();
    // draw projection plane ceiling
    engine.draw_rectangle((Eigen::Vector2i() << 0, 0).finished(), (Eigen::Vector2i() << pp_size(0), pp_size(1)/2).finished());

    engine.draw_map(grid);
    engine.draw_player(player, grid);
    engine.draw_point(grid, endpoint, (Eigen::Vector3f() << 0.5, 1.0, 0.5).finished(), (Eigen::Vector3f() << 1, 0.5, 0.5).finished());
    /* engine.draw_line(player.get_point_coord(), endpoint, grid); */
    engine.draw_fov(player, grid); 

    engine.draw_projection(player, grid);

    engine.write();    
    engine.clear();

    return 0;
}

