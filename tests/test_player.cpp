#include "player.hpp"
#include "map.hpp"

#include "gtest/gtest.h"

#include <cmath>

TEST(TestPlayer, HorizontalCastInsideWallDown) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size/2, cube_size/2).finished());
    player.set_direction(PI/2);
    float h_dist = player.cast_horizontal(grid);
    ASSERT_NEAR(h_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallUp) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3*PI/2);
    float h_dist = player.cast_horizontal(grid);
    ASSERT_NEAR(h_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWall45Deg) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3.0/2*PI + 1.0/4 * PI);
    float h_dist = player.cast_horizontal(grid);
    ASSERT_NEAR(h_dist, cube_size/2 * std::sqrt(2), 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallNeg45Deg) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3.0/2*PI - 1.0/4 * PI);
    float h_dist = player.cast_horizontal(grid);
    ASSERT_NEAR(h_dist, cube_size/2 * std::sqrt(2), 1e-1);
}

TEST(TestPlayer, VerticalCastInsideWallRight) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size/2, cube_size / 2).finished());
    player.set_direction(0.0);
    float v_dist = player.cast_vertical(grid);
    ASSERT_NEAR(v_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, VerticalCastOutsideWallLeft) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size / 2).finished());
    player.set_direction(PI);
    float v_dist = player.cast_vertical(grid);
    ASSERT_NEAR(v_dist, cube_size/2, 1e-1);
}
