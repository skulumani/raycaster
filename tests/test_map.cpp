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
    Eigen::Vector2i grid_coord(1, 1);
    Eigen::Vector2f point_coord = grid.grid2point(grid_coord);
    ASSERT_TRUE(point_coord.isApprox((Eigen::Vector2f() << 64, 64).finished()));
}

TEST(TestMap, PointInsideMap) {
    Map grid;
    Eigen::Vector2f point_coord(120, 120);
    ASSERT_TRUE(grid.inside_map(point_coord));
}

TEST(TestMap, PointOutsideMapPositive) {
    Map grid;
    Eigen::Vector2f point_coord(1025, 1025);
    ASSERT_FALSE(grid.inside_map(point_coord));
}

TEST(TestMap, PointOutsideMapNegative) {
    Map grid;
    Eigen::Vector2f point_coord(-1025, -1025);
    ASSERT_FALSE(grid.inside_map(point_coord));
}

TEST(TestMap, GridOutsideMapNegative) {
    Map grid;
    Eigen::Vector2i grid_coord(-20, 0);
    ASSERT_FALSE(grid.inside_map(grid_coord));
}

TEST(TestMap, GridOutsideMapPositive) {
    Map grid;
    Eigen::Vector2i grid_coord(20, 0);
    ASSERT_FALSE(grid.inside_map(grid_coord));
}

TEST(TestMap, GridInsideMap) {
    Map grid;
    Eigen::Vector2i grid_coord(3, 4);
    ASSERT_TRUE(grid.inside_map(grid_coord));
}

TEST(TestMap, GridInsideWall) {
    Map grid;
    Eigen::Vector2i grid_coord(0,0);
    ASSERT_TRUE(grid.inside_wall(grid_coord));
}

TEST(TestMap, GridOutsideWall) {
    Map grid;
    Eigen::Vector2i grid_coord(2,2);
    ASSERT_FALSE(grid.inside_wall(grid_coord));
}

TEST(TestMap, PointInsideWall) {
    Map grid;
    size_t cube_size = grid.get_cube_size();
    Eigen::Vector2f point_coord(cube_size / 2.0, cube_size / 2.0);
    ASSERT_TRUE(grid.inside_wall(point_coord));
}

TEST(TestMap, PointOutsideWall) {
    Map grid;
    size_t cube_size = grid.get_cube_size();
    Eigen::Vector2f point_coord(cube_size * 2.0, cube_size * 2.0);
    ASSERT_FALSE(grid.inside_wall(point_coord));
}

TEST(TestMap, PointOutsideEdgeWall) {
    Map grid;
    size_t cube_size = grid.get_cube_size();
    Eigen::Vector2f point_coord(cube_size, cube_size);
    ASSERT_FALSE(grid.inside_wall(point_coord));
}

TEST(TestMap, PointInsideEdgeWall) {
    Map grid;
    size_t cube_size = grid.get_cube_size();
    Eigen::Vector2f point_coord(cube_size*0.99, cube_size*0.99);
    ASSERT_TRUE(grid.inside_wall(point_coord));
}
