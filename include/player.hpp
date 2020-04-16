#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "map.hpp"

#include <Eigen/Dense>

const double PI = std::atan(1.0)*4;

class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};
    
        void init( void );
        
        Eigen::Vector2f get_point_coord( void ) const;
       
        void set_point_coord( const Eigen::Ref<const Eigen::Vector2f>& input_coord);

        float get_direction( void ) const;
        void set_direction(const float& input_angle);

        float cast_horizontal(const Map& input_map);
        float cast_vertical(const Map& input_map);
    
        float cast(const Map& input_map);

        Eigen::Vector2f find_wall(const Map& input_map, 
                const Eigen::Ref<const Eigen::Vector2f>& grid_pos,
                const float& delta_x, const float& delta_y);
    
        // return a point at dist in direction of m_direction from m_point_coord
        Eigen::Vector2f cast_endpoint(const float& dist);

    private:
    
        Eigen::Vector2f m_point_coord;

        float m_direction = 0; // view direction, angle CW from x axis radians (0 - right, pi/2 - down) always between 0 and 360
        
        float m_height = 32;
        float m_fov = 60 * PI/180.0;

        /* size_t image_width = 320; */
        /* size_t image_height = 200; */

        /* Eigen::Matrix<int, 1, 2> center{ 320/2, 200/2 }; */
        
        /* int image_dist = 320/2 / std::tan(60*PI/180/2); */

        /* double col_step = 60/320; */
};

#endif
