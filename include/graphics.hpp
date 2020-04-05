#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <cstdint>
#include <algorithm>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/StdVector> 

class Renderer {
    public:
        Renderer( void );
        virtual ~Renderer( void ) {};
        
        // File framebuffer with a gradient color scheme
        void gradient( void ); 
        void write( void );
    private:
        int m_width = 128;
        int m_height = 128;
    
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_framebuffer;

};

#endif
