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
    #pragma omp parallel for
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            m_framebuffer[ii+jj*m_width] = (Eigen::Vector3f() << jj/float(m_height), ii/float(m_width), 0).finished();
        }
    }
}

void Renderer::constant(const Eigen::Ref<const Eigen::Vector3f>& input_color) {
    // loop over pixels in the frame buffer
    #pragma omp parallel for
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            m_framebuffer[ii+jj*m_width] = input_color;
        }
    }
}

void Renderer::write( void ) {
    
    // now saving to file
    std::uint8_t image[m_height * m_width * 3];
    #pragma omp parallel for
    for (size_t ii = 0; ii < m_width * m_height; ii++) {
        image[ii * 3 + 0] = (int)(255 * m_framebuffer[ii](0));
        image[ii * 3 + 1] = (int)(255 * m_framebuffer[ii](1));
        image[ii * 3 + 2] = (int)(255 * m_framebuffer[ii](2));
    }

    stbi_write_jpg("out.jpg", m_width, m_height, 3, image, 95);
}


void Renderer::draw_map(const Map& input_map) {
    float pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    
    Eigen::Vector2f point_coord;
    Eigen::Vector2i pixel_coord, grid_coord;

    #pragma omp parallel for
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

void Renderer::draw_player(const Player& input_player, const Map& input_map) {
    // draw a square centered at the player location
    size_t player_half_size = 2; // half size in pixels of player marker
    float pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    float map2pixel = 1.0 / pixel2map;

    Eigen::Vector2f point_coord = input_player.get_point_coord();
    Eigen::Vector2i pixel_coord = (point_coord * map2pixel).cast<int>();
    // get the pixel extents of the player marker

    #pragma omp parallel for
    for (size_t jj = 0; jj < 2*player_half_size+1; jj++) {
        for (size_t ii = 0; ii < 2*player_half_size+1; ii++) {
            int px =  pixel_coord(0) - player_half_size + jj;
            int py = pixel_coord(1) - player_half_size + ii;
            // make sure px,py lie in the framebuffer
            if ( px >= 0 && px < m_width && py >= 0 && py < m_height) {
                m_framebuffer[py + px*m_width] = (Eigen::Vector3f() << 1, 0, 0).finished();
            }
        }
    }

    m_framebuffer[pixel_coord(1) + pixel_coord(0) * m_width] = (Eigen::Vector3f() << 0, 1, 0).finished();

}
