#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "map.hpp"
#include "player.hpp"


#include <Eigen/Dense>
#include <Eigen/StdVector> 

#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>


class Renderer {
    public:
        Renderer( void );
        virtual ~Renderer( void ) {};
        
        void init( void ); // also load all the textures into the framebuffers
        void load_textures( void );

        // File framebuffer with a gradient color scheme
        void gradient( void ); 

        void constant(const Eigen::Ref<const Eigen::Vector3f>& input_color);

        void write( void );
        void write(const std::string& filename);
        
        // clear the framebuffers and all member variables
        void clear( void ); 

        // input the map/grid and draw a solid color for each cube
        void draw_map(const Map& input_map); 
        // given a location coord draw a pixel

        // draw player location
        void draw_player(const Player& input_player, const Map& input_map);

        void draw_point(const Map& input_map,
                        const Eigen::Ref<const Eigen::Vector2f>& point_coord,
                        const Eigen::Ref<const Eigen::Vector3f>& primary_color=(Eigen::Vector3f() << 1, 0, 0).finished(),
                        const Eigen::Ref<const Eigen::Vector3f>& secondary_color=(Eigen::Vector3f() << 0, 1, 0).finished());
    
        void draw_line(const Eigen::Ref<const Eigen::Vector2f>& start_point,
                       const Eigen::Ref<const Eigen::Vector2f>& end_point,
                       const Map& input_map);

        // draw a rectangle on the projection plane
        void draw_rectangle(const Eigen::Ref<const Eigen::Vector2i>& upper_left_pixel, 
                            const Eigen::Ref<const Eigen::Vector2i>& bottom_right_pixel,
                            const Eigen::Ref<const Eigen::Vector3f>& color=(Eigen::Vector3f() << 0.5, 0.5, 0.5).finished());     

        void draw_fov(const Player& player, const Map& input_map);

        void draw_projection(const Player& player, const Map& input_map);

        Eigen::Vector2i get_pp_size( void ) const;
        Eigen::Vector2i get_mm_size( void ) const;
    private:
        // this is for the minimap
        int m_width = 512;
        int m_height = 512;
        
        // minimap
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_framebuffer;

        // projection plane framebuffer
        size_t m_pp_width = 640;
        size_t m_pp_height = 480;
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_pp_framebuffer;

        // create framebuffer for each expected texture
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_redbrick_fb;
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_wood_fb;
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_bluestone_fb;
        std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > m_greystone_fb;
    
};

#endif
