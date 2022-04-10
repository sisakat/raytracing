#include "camera.hpp"
#include "common.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

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

int main(int argc, char* argv[])
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    auto R = cos(pi / 4);
    HittableList world;
    
    auto material_left = std::make_shared<Lambertian>(Color(0, 0, 1));
    auto material_right = std::make_shared<Lambertian>(Color(1, 0, 0));

    world.add(std::make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
    world.add(std::make_shared<Sphere>(Point3(R, 0, -1), R, material_right));

    // Camera
    Camera camera(90.0, aspect_ratio);

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