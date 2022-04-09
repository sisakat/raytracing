#include "color.hpp"
#include "ray.hpp"

#include <iostream>
#include <spdlog/spdlog.h>

double hitSphere(const Point3& center, double radius, const Ray& ray)
{
    Vec3 oc = ray.origin() - center;
    double a = ray.direction().squaredNorm();
    double half_b = oc.dot(ray.direction());
    double c = oc.squaredNorm() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Color rayColor(const Ray& r)
{
    auto t = hitSphere(Point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        Vec3 n = (r.at(t) - Vec3(0, 0, -1)).normalized();
        return 0.5 * Color(n.x() + 1, n.y() + 1, n.z() + 1);
    }
    Vec3 unit_direction = r.direction().normalized();
    t = 0.5 * (unit_direction.y() + 1.0);
    // linear blending
    // blendedValue = (1 - t) * startValue + t * endValue
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

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
            Color pixel_color = rayColor(ray);
            writeColor(std::cout, pixel_color);
        }
    }

    std::cerr << "Done" << std::endl;
}