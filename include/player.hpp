#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "map.hpp"

#include <Eigen/Dense>

#include <tuple>

const double PI = std::atan(1.0)*4;

class Player {

    public:
        Player( void );
        virtual ~Player( void ) {};
    
        void init( void );
        
        Eigen::Vector2f get_point_coord( void ) const;
       
        void set_point_coord( const Eigen::Ref<const Eigen::Vector2f>& input_coord);

        float get_direction( void ) const;
        void set_direction(const float& input_angle);
        float wrap_angle(const float& input_angle) const;
        float get_angle_step(void) const;
        float get_projection_dist(void) const;

        std::tuple<float, int> cast(const float& direction, const Map& input_map) const;
    
        float get_fov( void ) const;

        Eigen::Vector2f find_wall(const Map& input_map, 
                const Eigen::Ref<const Eigen::Vector2f>& grid_pos,
                const float& delta_x, const float& delta_y) const;
    
        // return a point at dist in direction of m_direction from m_point_coord
        Eigen::Vector2f cast_endpoint(const float& dist, const float& direction) const;

        Eigen::Vector2i get_projection_plane( void ) const;
    private:
    
        Eigen::Vector2f m_point_coord;

        float m_direction = 0; // view direction, angle CW from x axis radians (0 - right, pi/2 - down) always between 0 and 360
        
        float m_height = 32; // always half height of cube_size in map
        float m_fov = 60 * PI/180.0;

        float cast_horizontal(const float& direction, const Map& input_map,
                              const bool& up, const bool& right) const;
        float cast_vertical(const float& direction, const Map& input_map,
                            const bool& up, const bool& right) const;

        Eigen::Vector2i projection_plane{ 640, 480 };

        Eigen::Vector2i projection_center{ 320, 240 };
        
        float projection_dist = 640/2 / std::tan(60*PI/180/2);

        float angle_step = 60.0 * PI/180.0 /640; // angle steps between columns of projection plane
};

#endif
