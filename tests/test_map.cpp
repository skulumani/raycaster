#include "gtest/gtest.h"

#include "map.hpp"

#include <iostream>

TEST(TestMap, MapSizeDefault) {
    Map grid;
    size_t map_size = grid.get_map_size();
    ASSERT_EQ(map_size, 16);
}

TEST(TestMap, MapSize) {
    Map grid(8);
    size_t map_size = grid.get_map_size();
    ASSERT_EQ(map_size, 8);
}

TEST(TestMap, Point2GridOrigin) {
    Map grid;
    // define a point
    Eigen::Vector2f point(63.45, 63.0);
    Eigen::Vector2i grid_coord = grid.point2grid(point);
    ASSERT_TRUE(grid_coord.isApprox((Eigen::Vector2i() << 0, 0).finished()));
}

TEST(TestMap, Point2GridOneTwo) {
    Map grid;
    // define a point
    Eigen::Vector2f point(64.01, 128.1);
    Eigen::Vector2i grid_coord = grid.point2grid(point);
    ASSERT_TRUE(grid_coord.isApprox((Eigen::Vector2i() << 1, 2).finished()));
}

TEST(TestMap, Grid2PointOrigin) {
    Map grid;
    // define a grid point
    Eigen::Vector2i grid_coord(0, 0);
    Eigen::Vector2f point_coord = grid.grid2point(grid_coord);
    ASSERT_TRUE(point_coord.isApprox((Eigen::Vector2f() << 0, 0).finished()));
}

TEST(TestMap, Grid2PointOneOne) {
    Map grid;
    // define a grid point
    Eigen::Vector2i grid_coord(1, 1);
    Eigen::Vector2f point_coord = grid.grid2point(grid_coord);
    std::cout << point_coord << std::endl;
    ASSERT_TRUE(point_coord.isApprox((Eigen::Vector2f() << 64, 64).finished()));
}

