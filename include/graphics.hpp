#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "map.hpp"
#include "player.hpp"

#include <Eigen/Dense>
#include <Eigen/StdVector> 

#include <cstdint>
#include <algorithm>
#include <vector>



class Renderer {
    public:
        Renderer( void );
        virtual ~Renderer( void ) {};
        
        // File framebuffer with a gradient color scheme
        void gradient( void ); 

        void constant(const Eigen::Ref<const Eigen::Vector3f>& input_color);

        void write( void );

        // input the map/grid and draw a solid color for each cube
        void draw_map(const Map& input_map); 
        // given a location coord draw a pixel

        // draw player location
        void draw_player(const Player& input_player, const Map& input_map);
    private:
        int m_width = 512;
        int m_height = 512;
    
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_framebuffer;

};

#endif
