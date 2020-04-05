#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Eigen/Dense>

const double PI = std::atan(1.0)*4;
class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};

    private:
    
        double x = 0; // m position in y direction
        double y = 0; // m position in x direction
        double direction = 0; // view direction, angle CCW from x axis
        
        double height = 32;
        double fov = 60 * PI/180.0;

        size_t image_width = 320;
        size_t image_height = 200;

        Eigen::Matrix<int, 1, 2> center{ 320/2, 200/2 };
        
        int image_dist = 320/2 / std::tan(60*PI/180/2);

        double col_step = 60/320;
};

#endif
