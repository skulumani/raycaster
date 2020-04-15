#include "player.hpp"

#include <Eigen/Dense>

Player::Player( void ) {
    init();
}

void Player::init( void ) {
    m_point_coord << 0, 0;
    m_grid_coord << 0, 0;
}

Eigen::Vector2f Player::get_point_coord( void ) const {
    return m_point_coord;
}

Eigen::Vector2i Player::get_grid_coord( void ) const {
    return m_grid_coord;
}

float Player::get_direction( void ) const {
    return m_direction;
}


