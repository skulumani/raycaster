#include "player.hpp"

#include <Eigen/Dense>

#include <limits>
#include <cmath>
#include <iostream>
#include <tuple>

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
    m_direction = wrap_angle(input_angle);
}

float Player::wrap_angle(const float& input_angle) const {
    float output_angle = std::fmod(input_angle, (2*PI));
    return (output_angle < 0) ? output_angle + 2*PI : output_angle;
}
// finds nearest horizontal wall intersection
float Player::cast_horizontal(const float& direction, const Map& input_map,
                              const bool& up, const bool& right) const {
    // find nearest grid intersection
    float intersection_y = std::floor(m_point_coord(1) / input_map.get_cube_size()) * input_map.get_cube_size() + (up ? -0.1 : input_map.get_cube_size());
    float intersection_x = m_point_coord(0) + std::abs(m_point_coord(1) - intersection_y) / std::tan(direction) * ( right ? 1.0 : -1.0);
    Eigen::Vector2f grid_int(intersection_x, intersection_y);
   
    // calculate deltas to get the next grid intersections
    float delta_y = up ? -float(input_map.get_cube_size()) : float(input_map.get_cube_size());
    float delta_x = input_map.get_cube_size() / std::tan(direction) * (right ? 1.0 : -1.0);
    // return nearest horizontal wall
    Eigen::Vector2f wall_int = find_wall(input_map, grid_int, delta_x, delta_y);
    return (m_point_coord - wall_int).norm();
}

// finds the closest vertical wall intersection
float Player::cast_vertical(const float& direction, const Map& input_map,
                            const bool& up, const bool& right) const {
    
    // find nearest grid intersection
    float intersection_x = std::floor(m_point_coord(0) / input_map.get_cube_size()) * input_map.get_cube_size() + (right ? input_map.get_cube_size() : -0.1);
    float intersection_y = m_point_coord(1) + std::abs(m_point_coord(0) - intersection_x) * std::tan(direction) * (up ? -1.0: 1.0);
    Eigen::Vector2f grid_int(intersection_x, intersection_y);
    
    // calculate deltas to get the next grid intersections
    float delta_x = right ? float(input_map.get_cube_size()) : -float(input_map.get_cube_size());
    float delta_y = std::abs(input_map.get_cube_size() * std::tan(direction)) * (up ? -1.0 : 1.0);
    
    // recursively find wall in vertical direction
    Eigen::Vector2f wall_int = find_wall(input_map, grid_int, delta_x, delta_y);
    return (m_point_coord - wall_int).norm();
}

std::tuple<float, int> Player::cast(const float& direction, const Map& input_map) const {

    bool up = (direction > PI) && (direction < 2.0 * PI);
    bool right = (direction < PI/2.0) || (direction > 3.0/2.0 * PI); 

    // check if looking upwards or downwards
    // change angle based on up/right booleans
    float angle = direction;
    if (up) {
        if (right) {
            // up and right
             angle = 2.0 * PI - wrap_angle(direction);
        } else {
            // up and left
             angle = wrap_angle(direction) - PI;
        }
    } else {
        if (right) {
            // down and right
             angle = wrap_angle(direction);
        } else {
            // down and left
             angle = PI - wrap_angle(direction);
        }
    }
    
    float h_dist = cast_horizontal(angle, input_map, up, right);
    float v_dist = cast_vertical(angle, input_map, up, right);
    
    int side = (h_dist < v_dist) ? 0 : 1;
    return std::make_tuple(std::min(h_dist, v_dist), side);
}

Eigen::Vector2f Player::find_wall(const Map& input_map, const Eigen::Ref<const Eigen::Vector2f>& grid_pos, const float& delta_x, const float& delta_y) const {
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

Eigen::Vector2f Player::cast_endpoint(const float& dist, const float& direction) const {
    // compute end point given distance and angle
    Eigen::Vector2f endpoint;
    endpoint = m_point_coord + (dist + 0.01)  * (Eigen::Vector2f() << std::cos(direction), std::sin(direction)).finished();
    return endpoint;
}

float Player::get_fov( void ) const {
    return m_fov;
}

Eigen::Vector2i Player::get_projection_plane( void ) const {
    return projection_plane;
}

float Player::get_angle_step( void ) const {
    return angle_step;
}

float Player::get_projection_dist( void ) const {
    return projection_dist;
}
