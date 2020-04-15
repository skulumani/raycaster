#include "gtest/gtest.h"

#include "map.hpp"

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
