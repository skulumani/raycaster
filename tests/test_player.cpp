#include "player.hpp"
#include "map.hpp"

#include "gtest/gtest.h"

#include <cmath>
#include <iostream> 

TEST(TestPlayer, HorizontalCastInsideWallDown) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size/2, cube_size/2).finished());
    player.set_direction(PI/2);
    float h_dist = std::get<0>(player.cast(player.get_direction(), grid));
    ASSERT_NEAR(h_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallDown) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << 3.0/2 * cube_size, 3.0/2 * cube_size).finished());
    player.set_direction(PI/2);
    float h_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(h_dist, grid.get_map_size() * cube_size - 2.5 * cube_size, 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallUp) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3*PI/2);
    float h_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(h_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWall45Deg) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3.0/2*PI + 1.0/4 * PI);
    float h_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(h_dist, cube_size/2 * std::sqrt(2), 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallNeg45Deg) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(3.0/2*PI - 1.0/4 * PI);
    float h_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(h_dist, cube_size/2 * std::sqrt(2), 1e-1);
}

TEST(TestPlayer, HorizontalCastOutsideWallDownFar) {
    Map grid(128);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size/2).finished());
    player.set_direction(0.5*PI);
    float h_dist = std::get<0>(player.cast(player.get_direction(),grid));
    std::cout << h_dist << std::endl;
    ASSERT_NEAR(h_dist, grid.get_map_size() * cube_size - 2.5*cube_size, 1e-1);
}

TEST(TestPlayer, VerticalCastInsideWallRight) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size/2, cube_size / 2).finished());
    player.set_direction(0.0);
    float v_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(v_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, VerticalCastOutsideWallLeft) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size / 2).finished());
    player.set_direction(PI);
    float v_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(v_dist, cube_size/2, 1e-1);
}

TEST(TestPlayer, VerticalCastOutsideWallRight) {
    Map grid(16);
    Player player;
    size_t cube_size = grid.get_cube_size();
    player.set_point_coord((Eigen::Vector2f() << cube_size + cube_size/2, cube_size + cube_size / 2).finished());
    player.set_direction(0);
    float v_dist = std::get<0>(player.cast(player.get_direction(),grid));
    ASSERT_NEAR(v_dist, grid.get_map_size() * cube_size - 2.5 * cube_size, 1e-1);
}

TEST(TestPlayer, CastRightSemiCircle) {
    Map grid(32);
    Player player;

    size_t cube_size = grid.get_cube_size();
    size_t map_size = grid.get_map_size();

    player.set_point_coord((Eigen::Vector2f() << cube_size * map_size/2, cube_size * map_size / 2).finished());
    for (int ii=-45;ii<45;ii++) {
        float direction = ii * PI/180.0 + 0;
        player.set_direction(direction);
        float dist = std::get<0>(player.cast(player.get_direction(),grid));
        Eigen::Vector2f endpoint = player.cast_endpoint(dist, player.get_direction());
        
        EXPECT_NEAR(endpoint(0), cube_size * (map_size - 1) , 1e-3);
    }
}

TEST(TestPlayer, CastDownSemiCircle) {
    Map grid(32);
    Player player;

    size_t cube_size = grid.get_cube_size();
    size_t map_size = grid.get_map_size();

    player.set_point_coord((Eigen::Vector2f() << cube_size * map_size/2, cube_size * map_size / 2).finished());
    for (int ii=-45;ii<45;ii++) {
        float direction = ii * PI/180.0 + 0.5 * PI;
        player.set_direction(direction);
        float dist = std::get<0>(player.cast(player.get_direction(),grid));
        Eigen::Vector2f endpoint = player.cast_endpoint(dist, player.get_direction());
        
        EXPECT_NEAR(endpoint(1), cube_size * (map_size - 1) , 1e-3);
    }
}

TEST(TestPlayer, CastLeftSemiCircle) {
    Map grid(32);
    Player player;

    size_t cube_size = grid.get_cube_size();
    size_t map_size = grid.get_map_size();

    player.set_point_coord((Eigen::Vector2f() << cube_size * map_size/2, cube_size * map_size / 2).finished());
    for (int ii=-45;ii<45;ii++) {
        float direction = ii * PI/180.0 + 1.0 * PI;
        player.set_direction(direction);
        float dist = std::get<0>(player.cast(player.get_direction(),grid));
        Eigen::Vector2f endpoint = player.cast_endpoint(dist, player.get_direction());
        
        EXPECT_NEAR(endpoint(0), cube_size, 1e-3);
    }
}

TEST(TestPlayer, CastUpSemiCircle) {
    Map grid(32);
    Player player;

    size_t cube_size = grid.get_cube_size();
    size_t map_size = grid.get_map_size();

    player.set_point_coord((Eigen::Vector2f() << cube_size * map_size/2, cube_size * map_size / 2).finished());
    for (int ii=-45;ii<45;ii++) {
        float direction = ii * PI/180.0 + 1.5 * PI;
        player.set_direction(direction);
        float dist = std::get<0>(player.cast(player.get_direction(),grid));
        Eigen::Vector2f endpoint = player.cast_endpoint(dist, player.get_direction());
        
        EXPECT_NEAR(endpoint(1), cube_size, 1e-3);
    }
}
