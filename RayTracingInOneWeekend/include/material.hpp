#pragma once
#include "common.hpp"

struct HitRecord;

class Material
{
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& a) : m_albedo{a} {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        Vec3 scatter_direction = rec.normal + randomUnitVector();

        if (scatter_direction.isZero(eps))
        {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.p, scatter_direction);
        attenuation = m_albedo;
        return true;
    }

private:
    Color m_albedo;
};

class Metal : public Material
{
public:
    Metal(const Color& a) : m_albedo{a} {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        Vec3 reflected = reflect(r_in.direction().normalized(), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = m_albedo;
        return (scattered.direction().dot(rec.normal)) > 0;
    }

private:
    Color m_albedo;
};