#include "player.hpp"

#include <Eigen/Dense>

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


