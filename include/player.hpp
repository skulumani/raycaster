#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Eigen/Dense>

class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};

    private:
    
        double x = 0; // m position in y direction
        double y = 0; // m position in x direction
        double direction = 0; // view direction, angle CCW from x axis
};

#endif
