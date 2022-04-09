#pragma once
#include "common.hpp"
#include "hittable.hpp"
#include "material.hpp"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Point3 center, double radius, std::shared_ptr<Material> mat)
        : m_center{center}, m_radius{radius}, m_mat{mat}
    {
    }

    bool hit(const Ray& r, double t_min, double t_max,
             HitRecord& rec) const override;

private:
    Point3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_mat;
};