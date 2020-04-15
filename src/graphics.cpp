#include "graphics.hpp"

#include <Eigen/Dense>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdint>
#include <algorithm>

Renderer::Renderer( void ) {
    m_framebuffer.resize(m_width * m_height, (Eigen::Vector3f() << 1, 1, 1).finished());
};

void Renderer::gradient( void ) {
    // loop over pixels in the frame buffer
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            m_framebuffer[ii+jj*m_width] = (Eigen::Vector3f() << jj/float(m_height), ii/float(m_width), 0).finished();
        }
    }

}

void Renderer::write( void ) {
    
    // now saving to file
    std::uint8_t image[m_height * m_width * 3];
    
    for (size_t ii = 0; ii < m_width * m_height; ii++) {
        image[ii * 3 + 0] = (int)(255 * m_framebuffer[ii](0));
        image[ii * 3 + 1] = (int)(255 * m_framebuffer[ii](1));
        image[ii * 3 + 2] = (int)(255 * m_framebuffer[ii](2));
    }

    stbi_write_jpg("out.jpg", m_width, m_height, 3, image, 95);
}


void Renderer::draw_map(const Map& input_map) {
    double pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    
    Eigen::Vector2f point_coord;
    Eigen::Vector2i pixel_coord, grid_coord;
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            // convert from pixel to map units
            pixel_coord <<  ii, jj;
            point_coord << ii, jj;
            point_coord = point_coord * pixel2map;
            // loop over each pixel in the framebuffer and compute grid location
            grid_coord = input_map.point2grid(point_coord);
            // if inside grid point then draw special color, if not then do nothing
            if (input_map.inside_wall(grid_coord) ) {
                m_framebuffer[ii+jj*m_width] = (Eigen::Vector3f() << 0, 1, 1).finished();
            } 
        }
    }
}
