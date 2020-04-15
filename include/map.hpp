#ifndef MAP_HPP
#define MAP_HPP

#include <Eigen/Dense>

class Map {
    public:
        Map( void );
        Map( size_t map_size);
        virtual ~Map( void ) {};
        
        void init( void );

        Eigen::MatrixXi get_map( void ) const;
        
        size_t get_map_size( void ) const;
        size_t get_cube_size( void ) const;
        // function to convert from location coord to grid/block coord
        Eigen::Vector2i point2grid(const Eigen::Ref<const Eigen::Vector2i>& point_coord);
        Eigen::Vector2i grid2point(const Eigen::Ref<const Eigen::Vector2i>& grid_coord);

        // functiont to check if outside total map
    private:
        
        size_t m_height = 64; // every block is size 64 units across
        size_t m_size = 16; // number of cubes/blocks in the map
        Eigen::MatrixXi m_map;
};

#endif
