#include "graphics.hpp"

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
