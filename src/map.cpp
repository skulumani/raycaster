#include "map.hpp"

#include <Eigen/Dense> 

#include <iostream>
#include <cmath>

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

    size_t rows = m_map.rows();
    size_t cols = m_map.cols();

    m_map.row(0) = Eigen::VectorXi::Constant(m_size, 1);
    m_map.row(m_map.rows()-1) = Eigen::VectorXi::Constant(m_size, 1);
    for ( size_t ii=0; ii<cols; ii+=2) {
        m_map(0, ii) = 2;
        m_map(rows-1, ii) = 2;
    }
    
    m_map.col(0) = Eigen::VectorXi::Constant(m_size, 1);
    m_map.col(m_map.cols()-1) = Eigen::VectorXi::Constant(m_size, 1);
    for ( size_t ii=0; ii<rows; ii+=2) {
        m_map(ii, 0) = 3;
        m_map(ii, cols-1) = 3;
    }

    // define interior
    // <p, q> - size of block (i, j) - start location in map
    /* m_map.block<5, 1>(1, 9) = Eigen::VectorXi::Constant(5, 1); */
    /* m_map(1, 4) = 3; */
    /* m_map.block<1, 5>(10, 1) = Eigen::VectorXi::Constant(5,1); */
    /* m_map(10, 3) = 3; */
    /* m_map.block<1, 4>(6, 10) = Eigen::VectorXi::Constant(4,2); */
    /* m_map.transposeInPlace(); */

    /* for (size_t ii=0; ii<rows; ii+=2) { */
    /*     m_map(ii, cols/2) = 3; */
    /* } */
}

void Map::fill(const size_t& x, const size_t& y, const size_t& val) {
    m_map(x, y) = val;
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
    Eigen::Vector2i grid_coord(std::floor(point_coord(0) / m_height), std::floor(point_coord(1) / m_height));
    return grid_coord ;
}

Eigen::Vector2f Map::grid2point(const Eigen::Ref<const  Eigen::Vector2i>& grid_coord) const {
    Eigen::Vector2f point_coord(grid_coord(0), grid_coord(1));
    /* m_height; // returns top left coord of cube */
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

Eigen::Vector3f Map::get_color(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const {
    Eigen::Vector3f color(0,0,0);
    // get value of map at this point 
    switch (m_map(grid_coord(0), grid_coord(1))) {
    // switch statement to determine color
        case 1: color << 1, 0, 0; break;// red - redbrick.png
        case 2: color << 0, 1, 0; break; // green - wood.png
        case 3: color << 0, 0, 1; break; // blue - bluestone.png
        case 4: color << 0.5, 0.5, 0.5; break; // cyan - greystone.png
        default: color << 1, 1, 0; break; // yellow
    }

    return color;
}

Eigen::Vector3f Map::get_color(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const {
    Eigen::Vector2i grid_coord = point2grid(point_coord);
    return get_color(grid_coord);
}
