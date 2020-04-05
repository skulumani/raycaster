#ifndef MAP_HPP
#define MAP_HPP

#include <Eigen/Dense>

class Map {
    public:
        Map( void );
        virtual ~Map( void ) {};
        

    private:
        
        size_t height = 64; // all walls made up of cubes of size 64
        size_t size = 10;
        Eigen::Matrix<int, 10, 10> grid;
            /* 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, */ 
            /* 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, */
            /* 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, */
            /* 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, */
            /* 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, */
            /* 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, */
            /* 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, */
            /* 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, */
            /* 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, */
            /* 1, 1, 1, 1, 1, 1, 1, 1, 1, 1; */
};

#endif
