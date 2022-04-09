#include "sphere.hpp"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Vec3 oc = r.origin() - m_center;
    double a = r.direction().squaredNorm();
    double half_b = oc.dot(r.direction());
    double c = oc.squaredNorm() - m_radius * m_radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    // find the nearest root that lies in the acceptable image
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - m_center) / m_radius;
    rec.setFaceNormal(r, outward_normal);

    return true;
}