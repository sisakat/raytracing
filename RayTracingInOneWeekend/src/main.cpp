#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "common.hpp"
#include "material.hpp"

#include <spdlog/spdlog.h>

Color rayColor(const Ray& r, const Hittable& world, int depth)
{
    HitRecord rec;

    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation.cwiseProduct(
                rayColor(scattered, world, depth - 1));
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = r.direction().normalized();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    // linear blending
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList randomScene()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(
        std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2,
                          b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).norm() > 0.9)
            {
                std::shared_ptr<Material> Sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = randomColor().cwiseProduct(randomColor());
                    Sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, Sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = randomColor(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    Sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, Sphere_material));
                }
                else
                {
                    // glass
                    Sphere_material = std::make_shared<Dialectric>(1.5);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, Sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dialectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main(int argc, char* argv[])
{
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World
    auto world = randomScene();

    // Camera
    Point3 look_from(13, 2, 3);
    Point3 look_at(0, 0, 0);
    Vec3 up(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera camera(look_from, look_at, up, 20, aspect_ratio, aperture,
                  dist_to_focus);

    // Render

    std::cout << fmt::format("P3\n{} {}\n255", image_width, image_height)
              << std::endl;

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << fmt::format("\rScanlines remaining: {}", j) << std::endl;
        for (int i = 0; i < image_width; ++i)
        {
            Color pixel_color(0, 0, 0);
            for (int s{0}; s < samples_per_pixel; ++s)
            {
                auto u = double(i + randomDouble()) / (image_width - 1);
                auto v = double(j + randomDouble()) / (image_height - 1);
                Ray r = camera.getRay(u, v);
                pixel_color += rayColor(r, world, max_depth);
            }
            writeColor(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "Done" << std::endl;
}