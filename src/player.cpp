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

// finds nearest horizontal wall intersection
float Player::cast_horizontal(const Map& input_map) {
    // check if looking upwards or downwards
    bool up = (m_direction > PI);
    bool right = (m_direction < PI/2.0) || (m_direction > 3/4 * PI); 
     
    // find nearest grid intersection
    float intersection_y = std::floor(m_point_coord(1) / input_map.get_cube_size()) * input_map.get_cube_size() + (up ? -0.001 : input_map.get_cube_size());
    float intersection_x = m_point_coord(0) + (intersection_y - m_point_coord(1)) / std::tan(m_direction);
    Eigen::Vector2f grid_int(intersection_x, intersection_y);
   
    // calculate deltas to get the next grid intersections
    float delta_y = up ? -input_map.get_cube_size() : input_map.get_cube_size();
    float delta_x = std::abs(input_map.get_cube_size() / std::tan(m_direction)) * (right ? 1 : -1);
    // return nearest horizontal wall
    Eigen::Vector2f wall_int = find_wall(input_map, grid_int, delta_x, delta_y);
    return (m_point_coord - wall_int).norm();
}

// finds the closest vertical wall intersection
float Player::cast_vertical(const Map& input_map) {
    // check if looking upwards or downwards
    bool up = (m_direction > PI);
    bool right = (m_direction < PI/2.0) || (m_direction > 3.0/2.0 * PI); 
    
    // find nearest grid intersection
    float intersection_x = std::floor(m_point_coord(0) / input_map.get_cube_size()) * input_map.get_cube_size() + (right ? input_map.get_cube_size() : -0.001);
    float intersection_y = m_point_coord(1) + (intersection_x - m_point_coord(0)) * std::tan(m_direction);
    Eigen::Vector2f grid_int(intersection_x, intersection_y);
    
    // calculate deltas to get the next grid intersections
    float delta_x = right ? input_map.get_cube_size() : -input_map.get_cube_size();
    float delta_y = std::abs(input_map.get_cube_size() * std::tan(m_direction)) * (up ? -1 : 1);
    
    // recursively find wall in vertical direction
    Eigen::Vector2f wall_int = find_wall(input_map, grid_int, delta_x, delta_y);
    return (m_point_coord - wall_int).norm();
}

float Player::cast(const Map& input_map) {
    float h_dist = cast_horizontal(input_map);
    float v_dist = cast_vertical(input_map);
    
    return  std::min(h_dist, v_dist);
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

Eigen::Vector2f Player::cast_endpoint(const float& dist) {
    // compute end point given distance and angle
    Eigen::Vector2f endpoint;
    endpoint = m_point_coord + dist * (Eigen::Vector2f() << std::cos(m_direction), std::sin(m_direction)).finished();
    return endpoint;
}


