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
    /* m_map(1, 5) = 1; */
}

Eigen::MatrixXi Map::get_map( void ) const {
    return m_map;
}

size_t Map::get_map_size( void ) const {
    return m_size;
}

size_t Map::get_cube_size( void ) const {
    return m_height;
}

Eigen::Vector2i Map::point2grid(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const {
    Eigen::Vector2i grid_coord(point_coord(0), point_coord(1));
    return grid_coord / m_height;
}

Eigen::Vector2f Map::grid2point(const Eigen::Ref<const  Eigen::Vector2i>& grid_coord) const {
    Eigen::Vector2f point_coord(grid_coord(0), grid_coord(1));
    /* m_height; // returns bottom left coord of cube */
    return point_coord * m_height;
}

bool Map::inside_map(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const {
    if (grid_coord.maxCoeff() < m_size && grid_coord.minCoeff() >= 0 ) {
        return true;
    } else {
        return false;
    }
}

bool Map::inside_map(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const {
    if (point_coord.maxCoeff() < (m_size * m_height) && point_coord.minCoeff() >= 0 ) {
        return true;
    } else {
        return false;
    }
}

bool Map::inside_wall(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const {
    Eigen::Vector2i grid_coord = point2grid(point_coord);
    return inside_wall(grid_coord);
}

bool Map::inside_wall(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const {
    if (inside_map(grid_coord) && m_map(grid_coord(0), grid_coord(1)) > 0) {
        return true;
    } else {
        return false;
    }
}
