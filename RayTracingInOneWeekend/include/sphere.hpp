#pragma once
#include "hittable.hpp"
#include "types.hpp"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Point3 center, double radius) : m_center{center}, m_radius{radius} {}

    bool hit(const Ray& r, double t_min, double t_max,
             HitRecord& rec) const override;

private:
    Point3 m_center;
    double m_radius;
};