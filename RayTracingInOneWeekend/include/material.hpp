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
    Metal(const Color& a, double roughness = 1)
        : m_albedo{a}, m_roughness{roughness < 1 ? roughness : 1}
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        Vec3 reflected = reflect(r_in.direction().normalized(), rec.normal);
        scattered = Ray(rec.p, reflected + m_roughness * randomInUnitSphere());
        attenuation = m_albedo;
        return (scattered.direction().dot(rec.normal)) > 0;
    }

private:
    Color m_albedo;
    double m_roughness;
};

class Dialectric : public Material
{
public:
    Dialectric(double index_of_refraction)
        : m_index_of_refraction{index_of_refraction}
    {
    }

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / m_index_of_refraction)
                                                 : m_index_of_refraction;
        Vec3 unit_direction = r_in.direction().normalized();
        Vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
        scattered = Ray(rec.p, refracted);
        return true;
    }

private:
    double m_index_of_refraction;
};