#include "player.hpp"

#include <Eigen/Dense>

#include <limits>
#include <cmath>
#include <iostream>

Player::Player( void ) {
    init();
}

void Player::init( void ) {
    m_point_coord << 0, 0;
}

Eigen::Vector2f Player::get_point_coord( void ) const {
    return m_point_coord;
}

float Player::get_direction( void ) const {
    return m_direction;
}

void Player::set_point_coord(const Eigen::Ref<const Eigen::Vector2f>& input_coord) {
    m_point_coord = input_coord;
}

void Player::set_direction(const float& input_angle) {
    m_direction = std::fmod(input_angle, (2 * PI)); // in radians
    m_direction = (m_direction < 0) ? m_direction + 2*PI : m_direction;
}

float Player::cast_horizontal(const Map& input_map) {
    // check if looking upwards or downwards
    bool up = (m_direction > PI);
    bool right = (m_direction < PI/2.0) || (m_direction > 3/4 * PI); 
     
    // find nearest grid intersection
    float intersection_y = std::floor(m_point_coord(1) / input_map.get_cube_size()) * input_map.get_cube_size() + (up ? -0.01 : input_map.get_cube_size());
    float intersection_x = m_point_coord(0) + (intersection_y - m_point_coord(1)) / std::tan(m_direction);
   
    // calculate deltas to get the next grid intersections
    float delta_y = up ? -input_map.get_cube_size() : input_map.get_cube_size();
    float delta_x = std::abs(input_map.get_cube_size() / std::tan(m_direction)) * (right ? 1 : -1);

    Eigen::Vector2f grid_int(intersection_x, intersection_y);

    // return nearest horizontal wall
    Eigen::Vector2f wall_int = find_wall(input_map, grid_int, delta_x, delta_y);
    std::cout << wall_int.transpose() << std::endl;
    /* std::cout << grid_int.transpose() << std::endl; */
    /* std::cout << delta_x << ", " << delta_y << std::endl; */
    // recursively find wall
    return 0.0;
}

Eigen::Vector2f Player::find_wall(const Map& input_map, const Eigen::Ref<const Eigen::Vector2f>& grid_pos, const float& delta_x, const float& delta_y) {
    // recursive function to loop and check grid intersections for walls

    // return infinity position if not within map
    if (!input_map.inside_map(grid_pos)) {
        return (Eigen::Vector2f::Constant(std::numeric_limits<float>::infinity())); 
    }

    // check if wall and return position
    if (input_map.inside_wall(grid_pos)) {
        return grid_pos;
    }
    
    Eigen::Vector2f new_pos(grid_pos(0) + delta_x, grid_pos(1) + delta_y);
    return find_wall(input_map, new_pos, delta_x, delta_y);
}




