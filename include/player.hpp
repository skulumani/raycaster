#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Eigen/Dense>

const double PI = std::atan(1.0)*4;

class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};
    
        void init( void );
        
        Eigen::Vector2f get_point_coord( void ) const;
        Eigen::Vector2i get_grid_coord( void ) const;
        
        float get_direction( void ) const;
    private:
    
        Eigen::Vector2f m_point_coord;
        Eigen::Vector2i m_grid_coord;

        float m_direction = 0; // view direction, angle CCW from x axis
        
        float m_height = 32;
        float m_fov = 60 * PI/180.0;

        /* size_t image_width = 320; */
        /* size_t image_height = 200; */

        /* Eigen::Matrix<int, 1, 2> center{ 320/2, 200/2 }; */
        
        /* int image_dist = 320/2 / std::tan(60*PI/180/2); */

        /* double col_step = 60/320; */
};

#endif
