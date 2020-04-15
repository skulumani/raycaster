#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Eigen/Dense>

const double PI = std::atan(1.0)*4;

class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};

    private:
    
        Eigen::Vector2f point_pos;
        Eigen::Vector2i grid_pos;

        float direction = 0; // view direction, angle CCW from x axis
        
        float height = 32;
        float fov = 60 * PI/180.0;

        /* size_t image_width = 320; */
        /* size_t image_height = 200; */

        /* Eigen::Matrix<int, 1, 2> center{ 320/2, 200/2 }; */
        
        /* int image_dist = 320/2 / std::tan(60*PI/180/2); */

        /* double col_step = 60/320; */
};

#endif
