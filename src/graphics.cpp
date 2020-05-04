#include "graphics.hpp"

#include <Eigen/Dense>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <string> 

Renderer::Renderer( void ) {
    init();
    // load wall textures
    load_wall_textures();
}

void Renderer::init( void ) {
    m_framebuffer.clear();
    m_pp_framebuffer.clear();

    m_framebuffer.resize(m_width * m_height, (Eigen::Vector3f() << 1, 1, 1).finished());
    m_pp_framebuffer.resize(m_pp_width * m_pp_height, (Eigen::Vector3f() << 0, 0, 0).finished());

}

void Renderer::load_textures( void ) {

    // load each texture to framebuffer
}

void Renderer::clear( void ) {
    init();
}

void Renderer::gradient( void ) {
    // loop over pixels in the frame buffer
    #pragma omp parallel for
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            m_framebuffer[ii+jj*m_width] = (Eigen::Vector3f() << jj/float(m_height), ii/float(m_width), 0).finished();
        }
    }
}

void Renderer::load_wall_textures( void ) {
    // load all the wall textures
    load_texture("data/redbrick.png", m_redbrick_framebuffer);
    load_texture("data/wood.png", m_wood_framebuffer);
    load_texture("data/bluestone.png", m_bluestone_framebuffer);
    load_texture("data/greystone.png", m_greystone_framebuffer);
}

bool Renderer::load_texture(const std::string& filename,
                             std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> >& texture_framebuffer ) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (!image) {
        std::cerr << "Error: can not load textures" << std::endl;
        return false;
    }
    
    if (channels != 3) {
        std::cerr << "Error: the texture must be a 24 bit image" << std::endl;
        stbi_image_free(image);
        return false;
    }
    
    texture_framebuffer.resize(width * height, (Eigen::Vector3f() << 0, 0, 0).finished());
    // loop over image and store into framebuffer
    for (size_t jj=0; jj<height; jj++) {
        for (size_t ii=0; ii<width; ii++) {
            uint8_t r = image[(ii+jj*width)*3 + 0];
            uint8_t g = image[(ii+jj*width)*3 + 1];
            uint8_t b = image[(ii+jj*width)*3 + 2];
            texture_framebuffer[ii+jj*width] = (Eigen::Vector3f() << unsigned(r)/255.0,
                    unsigned(g)/255.0,
                    unsigned(b)/255.0).finished();
        }
    }
    stbi_image_free(image);
    return true;
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
    std::uint8_t image[m_width * m_height * 3];
    #pragma omp parallel for
    for (size_t ii = 0; ii < m_width * m_height; ii++) {
        image[ii * 3 + 0] = (int)(255 * m_framebuffer[ii](0));
        image[ii * 3 + 1] = (int)(255 * m_framebuffer[ii](1));
        image[ii * 3 + 2] = (int)(255 * m_framebuffer[ii](2));
    }

    stbi_write_jpg("map.jpg", m_width, m_height, 3, image, 95);

    // now saving to file
    std::uint8_t image_pp[m_pp_width * m_pp_height * 3];
    #pragma omp parallel for
    for (size_t ii = 0; ii < m_pp_width * m_pp_height; ii++) {
        image_pp[ii * 3 + 0] = (int)(255 * m_pp_framebuffer[ii](0));
        image_pp[ii * 3 + 1] = (int)(255 * m_pp_framebuffer[ii](1));
        image_pp[ii * 3 + 2] = (int)(255 * m_pp_framebuffer[ii](2));
    }

    stbi_write_jpg("proj.jpg", m_pp_width, m_pp_height, 3, image_pp, 95);

}


void Renderer::write(const std::string& filename) {
    
    // now saving to file
    std::uint8_t image[512 * 512 * 3] = {0};
    /* #pragma omp parallel for */
    for (size_t ii = 0; ii < m_width * m_height; ii++) {
        image[ii * 3 + 0] = (int)(255 * m_framebuffer[ii](0));
        image[ii * 3 + 1] = (int)(255 * m_framebuffer[ii](1));
        image[ii * 3 + 2] = (int)(255 * m_framebuffer[ii](2));
    }
    
    std::string map_fname;
    map_fname = filename + "map.jpg";
    stbi_write_jpg(map_fname.c_str(), m_width, m_height, 3, image, 95);

    // now saving to file
    std::uint8_t image_pp[640 * 480 * 3] = {0};
    /* #pragma omp parallel for */
    for (size_t ii = 0; ii < m_pp_width * m_pp_height; ii++) {
        image_pp[ii * 3 + 0] = (int)(255 * m_pp_framebuffer[ii](0));
        image_pp[ii * 3 + 1] = (int)(255 * m_pp_framebuffer[ii](1));
        image_pp[ii * 3 + 2] = (int)(255 * m_pp_framebuffer[ii](2));
    }
    std::string proj_fname;
    proj_fname = filename + "proj.jpg";
    stbi_write_jpg(proj_fname.c_str(), m_pp_width, m_pp_height, 3, image_pp, 95);

}
void Renderer::draw_map(const Map& input_map) {
    float pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    
    Eigen::Vector2f point_coord;
    Eigen::Vector2i grid_coord;

    #pragma omp parallel for
    for (size_t jj = 0; jj < m_height; jj++) {
        for (size_t ii = 0; ii < m_width; ii++) {
            // convert from pixel to map units
            point_coord << ii, jj;
            point_coord = point_coord * pixel2map;
            // loop over each pixel in the framebuffer and compute grid location
            grid_coord = input_map.point2grid(point_coord);
            // if inside grid point then draw special color, if not then do nothing
            if (input_map.inside_wall(grid_coord)) {
                m_framebuffer[ii+jj*m_width] = input_map.get_color(grid_coord);
                /* m_framebuffer[ii+jj*m_width] = (Eigen::Vector3f() << 0, 1, 1).finished(); */
            } 
        }
    }


    // draw the wall texture in the top corner
    for (size_t jj=0; jj<64; jj++) {
        for (size_t ii=0; ii < 64; ii++) {
            m_framebuffer[ii + jj*m_width] = m_wood_framebuffer[ii + jj*64];
        }
    }
}

void Renderer::draw_player(const Player& input_player, const Map& input_map) {
    draw_point(input_map, input_player.get_point_coord(), 
            (Eigen::Vector3f() << 1, 0, 0).finished(),
            (Eigen::Vector3f() << 0, 1, 0).finished());
}

void Renderer::draw_point(const Map& input_map,
                          const Eigen::Ref<const Eigen::Vector2f>& point_coord, 
                          const Eigen::Ref<const Eigen::Vector3f>& primary_color,
                          const Eigen::Ref<const Eigen::Vector3f>& secondary_color) {
    // draw a square centered at the player location
    size_t player_half_size = 2; // half size in pixels of marker
    float pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    float map2pixel = 1.0 / pixel2map;
    Eigen::Vector2i pixel_coord(point_coord(0)*map2pixel, point_coord(1)*map2pixel);

    // get the pixel extents of the player marker
    #pragma omp parallel for
    for (size_t jj = 0; jj < 2*player_half_size+1; jj++) {
        for (size_t ii = 0; ii < 2*player_half_size+1; ii++) {
            int px =  pixel_coord(0) - player_half_size + ii;
            int py = pixel_coord(1) - player_half_size + jj;
            // make sure px,py lie in the framebuffer
            if ( px >= 0 && px < m_width && py >= 0 && py < m_height) {
                m_framebuffer[px + py*m_width] = primary_color;
            }
        }
    }

    m_framebuffer[pixel_coord(0) + pixel_coord(1) * m_width] = secondary_color;

}

void Renderer::draw_rectangle(const Eigen::Ref<const Eigen::Vector2i>& upper_left_pixel, 
                            const Eigen::Ref<const Eigen::Vector2i>& bottom_right_pixel,
                            const Eigen::Ref<const Eigen::Vector3f>& color) {

    #pragma omp parallel for
    for (size_t ii=upper_left_pixel(0);ii<bottom_right_pixel(0);ii++) {
        for (size_t jj = upper_left_pixel(1); jj < bottom_right_pixel(1); jj++) {
                m_pp_framebuffer[ii + jj*m_pp_width] = color;
        }

    }
}

// draws a rectangle on the projection plane
void Renderer::draw_line(const Eigen::Ref<const Eigen::Vector2f>& start_point,
                         const Eigen::Ref<const Eigen::Vector2f>& end_point,
                         const Map& input_map) {
    
    // draw line between start and end
    float pixel2map = input_map.get_cube_size() * input_map.get_map_size() * 1.0 / m_height;
    float map2pixel = 1.0 / pixel2map;
    /* Eigen::Vector2i pixel_coord(point_coord(1)*map2pixel, point_coord(0)*map2pixel); */
    Eigen::Vector2f unit_vec = (end_point-start_point).normalized();
    Eigen::Vector2f point_coord = start_point;
    Eigen::Vector2i pixel_coord;
    
    #pragma omp parallel for
    for (float d = 0; d < (start_point - end_point).norm(); d+=1) {
        // compute pixel location on line
        point_coord = start_point + d * unit_vec;
        pixel_coord << point_coord(0)*map2pixel, point_coord(1)*map2pixel;

        m_framebuffer[pixel_coord(0) + pixel_coord(1)*m_width] = (Eigen::Vector3f() << 1, 1, 1).finished();
    }
}

void Renderer::draw_fov(const Player& player, const Map& input_map) {
    float fov = player.get_fov();

    #pragma omp parallel for
    for (size_t ii=0;ii<m_width;ii+=10) {
        // loop over FOV and cast a ray in each direction
        float angle = player.get_direction() - fov/2.0 +  fov * ii / float(m_width);
        angle = player.wrap_angle(angle);
        float dist = std::get<0>(player.cast(angle, input_map));
        Eigen::Vector2f endpoint = player.cast_endpoint(dist, angle);
        // draw line for each cast
        draw_line(player.get_point_coord(), endpoint, input_map);
    }
}

// TODO textured wall function
// get the correct texture column and scale based on required height
void Renderer::draw_textured_projection(const Player& player, const Map& input_map) {
    // initialize the projection framebuffer
    float fov = player.get_fov();
    size_t cube_size = input_map.get_cube_size();
    
    // cast over the field of view
    #pragma omp parallel for
    for (size_t ii=0;ii<m_pp_width;ii++) {
        float angle = player.get_direction() - fov/2.0 + ii * player.get_angle_step();
        angle = player.wrap_angle(angle);
        float beta = std::abs(player.get_direction() - angle);
        // for each get the distance to wall
        auto cast_out = player.cast(angle, input_map);
        float true_dist = std::get<0>(cast_out);
        int side = std::get<1>(cast_out);

        // determine wall that is hit for color
        Eigen::Vector2f endpoint = player.cast_endpoint(true_dist, angle);
        // get fractional position of wall endpoint
        float tex_hpos; //
        if (side == 0) {
            tex_hpos = endpoint(0) - std::floor(endpoint(0));
        } else if (side == 1) {
            tex_hpos = endpoint(1) - std::floor(endpoint(1));
        }

        Eigen::Vector3f color = input_map.get_color(endpoint); 
        if (side) {
            color = color * 1.0/2.0; // scale color for vertical walls
        }
        // compute height of wall on projection plane
        size_t proj_wall_height = std::ceil(float(cube_size) / (std::cos(beta) * true_dist) * player.get_projection_dist());

        // get the correct column of the wall texture
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > column(proj_wall_height);
        for (size_t jj=0; jj < proj_wall_height; jj++) {
            // texture location in horizontal direction
            size_t pix_x = tex_hpos * 64;
            size_t pix_y = (jj*64)/proj_wall_height;
            column[jj] = m_redbrick_framebuffer[pix_x + pix_y*64];
        }

        /* #pragma omp parallel for */
        for (size_t jj = 0; jj < proj_wall_height; jj++) {
            size_t px =  ii;
            size_t py = m_pp_height/2-proj_wall_height/2 + jj;
            // make sure px,py lie in the framebuffer
            if ( px < m_pp_width && py < m_pp_height) {
                /* m_pp_framebuffer[px + py*m_pp_width] = color; */
                m_pp_framebuffer[px + py*m_pp_width] = column[jj];
            }
        }

    }
}
// draw projection plane with solid colors
void Renderer::draw_projection(const Player& player, const Map& input_map) {
    // initialize the projection framebuffer
    float fov = player.get_fov();
    size_t cube_size = input_map.get_cube_size();
    
    // cast over the field of view
    #pragma omp parallel for
    for (size_t ii=0;ii<m_pp_width;ii++) {
        float angle = player.get_direction() - fov/2.0 + ii * player.get_angle_step();
        angle = player.wrap_angle(angle);
        float beta = std::abs(player.get_direction() - angle);
        // for each get the distance to wall
        auto cast_out = player.cast(angle, input_map);
        float true_dist = std::get<0>(cast_out);
        int side = std::get<1>(cast_out);

        // determine wall that is hit for color
        Eigen::Vector2f endpoint = player.cast_endpoint(true_dist, angle);
        Eigen::Vector3f color = input_map.get_color(endpoint); 
        if (side) {
            color = color * 1.0/2.0; // scale color for vertical walls
        }
        // compute height of wall on projection plane
        size_t proj_wall_height = std::ceil(float(cube_size) / (std::cos(beta) * true_dist) * player.get_projection_dist());
        // set the appropriate pixels in pp_framebuffer to a color
        // get the pixel extents of the player marker
        /* #pragma omp parallel for */
        for (size_t jj = 0; jj < proj_wall_height; jj++) {
            size_t px =  ii;
            size_t py = m_pp_height/2-proj_wall_height/2 + jj;
            // make sure px,py lie in the framebuffer
            if ( px < m_pp_width && py < m_pp_height) {
                m_pp_framebuffer[px + py*m_pp_width] = color;
            }
        }

    }
}

Eigen::Vector2i Renderer::get_pp_size( void ) const {
    return (Eigen::Vector2i() << m_pp_width, m_pp_height).finished();
}

Eigen::Vector2i Renderer::get_mm_size( void ) const {
    return (Eigen::Vector2i() << m_width, m_height).finished();
}
