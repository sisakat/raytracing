#pragma once
#include "common.hpp"

class Camera
{
public:
    Camera(Point3 look_from, Point3 look_at, Vec3 up, double vfov,
           double aspect_ratio)
    {
        auto theta = vfov * deg;
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        Vec3 w = (look_from - look_at).normalized();
        Vec3 u = up.cross(w).normalized();
        Vec3 v = w.cross(u);

        m_origin = look_from;
        m_horizontal = viewport_width * u;
        m_vertical = viewport_height * v;
        m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - w;
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
};