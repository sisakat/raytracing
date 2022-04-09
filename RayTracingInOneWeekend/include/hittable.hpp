#pragma once
#include "ray.hpp"

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double t;
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max,
                     HitRecord& rec) const = 0;
};