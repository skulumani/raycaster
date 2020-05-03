#ifndef MAP_HPP
#define MAP_HPP

#include <Eigen/Dense>

class Map {
    public:
        Map( void );
        Map( size_t map_size);
        virtual ~Map( void ) {};
        
        void init( void );
        
        // dimensions match image - x = cols, y = rows 
        void fill(const size_t& x, const size_t& y, const size_t& val);
        // randomly set interior to filled/not filled blocks - only after calling init
        void random( void ); 

        // Map defined with x,y coord. Origin is top left of map
        Eigen::MatrixXi get_map( void ) const;
        
        size_t get_map_size( void ) const;
        size_t get_cube_size( void ) const;
        // function to convert from location coord to grid/block coord
        Eigen::Vector2i point2grid(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const;
        Eigen::Vector2f grid2point(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const; // returns the top left pixel of cube

        // functiont to check if grid coord is within the map
        bool inside_map(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const;
        bool inside_map(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const;

        // check if grid/point is within a wall or is filled
        bool inside_wall(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const;
        bool inside_wall(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const;

    
        Eigen::Vector3f get_color(const Eigen::Ref<const Eigen::Vector2i>& grid_coord) const;
        Eigen::Vector3f get_color(const Eigen::Ref<const Eigen::Vector2f>& point_coord) const;
    private:
        
        size_t m_height = 64; // every block is size 64 units across
        size_t m_size = 16; // number of cubes/blocks in the map
        Eigen::MatrixXi m_map;
};

#endif
