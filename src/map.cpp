#include "map.hpp"

Map::Map( void ) {
    init();
}

Map::Map(size_t map_size) {
    m_size = map_size; // make sure it's a power of 2
    init();
}

void Map::init( void ) {
    // initialize the map
    m_map.setZero(m_size, m_size);
    m_map.row(0) = Eigen::VectorXi::Constant(m_size, 1);
    m_map.row(m_map.rows()-1) = Eigen::VectorXi::Constant(m_size, 1);

    m_map.col(0) = Eigen::VectorXi::Constant(m_size, 1);
    m_map.col(m_map.cols()-1) = Eigen::VectorXi::Constant(m_size, 1);

    // define interior

}
Eigen::MatrixXi Map::get_map( void ) const {
    return m_map;
}

size_t Map::get_map_size( void ) const {
    return m_size;
}

Eigen::Vector2i Map::point2grid(const Eigen::Ref<const Eigen::Vector2i>& point_coord) {
    Eigen::Vector2i grid_coord = point_coord / m_height;
    return grid_coord;
}

Eigen::Vector2i Map::grid2point(const Eigen::Ref<const  Eigen::Vector2i>& grid_coord) {
    Eigen::Vector2i point_coord = grid_coord * m_height; // returns bottom left coord of cube
    return point_coord;
}
