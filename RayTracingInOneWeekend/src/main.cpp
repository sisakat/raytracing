#include "common.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <spdlog/spdlog.h>

Color rayColor(const Ray& r, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + Color(1, 1, 1));
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
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    Point3 lower_left_corner =
        origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // Render

    std::cout << fmt::format("P3\n{} {}\n255", image_width, image_height)
              << std::endl;

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << fmt::format("\rScanlines remaining: {}", j) << std::endl;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray ray(origin,
                    lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color = rayColor(ray, world);
            writeColor(std::cout, pixel_color);
        }
    }

    std::cerr << "Done" << std::endl;
}