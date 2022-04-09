#pragma once
#include "common.hpp"

class Camera
{
public:
    Camera()
    {
        const auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        m_origin = Point3(0, 0, 0);
        m_horizontal = Vec3(viewport_width, 0.0, 0.0);
        m_vertical = Vec3(0.0, viewport_height, 0.0);
        m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 -
                              Vec3(0, 0, focal_length);
    }

    Ray getRay(double u, double v) const
    {
        return Ray(m_origin, m_lower_left_corner + u * m_horizontal +
                                 v * m_vertical - m_origin);
    }

private:
    Point3 m_origin;
    Point3 m_lower_left_corner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};