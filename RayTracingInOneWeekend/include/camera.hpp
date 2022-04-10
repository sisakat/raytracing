#pragma once
#include "common.hpp"

class Camera
{
public:
    Camera(Point3 look_from, Point3 look_at, Vec3 up, double vfov,
           double aspect_ratio, double aperture, double focus_dist)
    {
        auto theta = vfov * deg;
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        m_w = (look_from - look_at).normalized();
        m_u = up.cross(m_w).normalized();
        m_v = m_w.cross(m_u);

        m_origin = look_from;
        m_horizontal = focus_dist * viewport_width * m_u;
        m_vertical = focus_dist * viewport_height * m_v;
        m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - focus_dist * m_w;

        m_lens_radius = aperture / 2;
    }

    Ray getRay(double s, double t) const
    {
        return Ray(m_origin, m_lower_left_corner + s * m_horizontal +
                                 t * m_vertical - m_origin);
    }

private:
    Point3 m_origin;
    Point3 m_lower_left_corner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_u, m_v, m_w;
    double m_lens_radius;
};