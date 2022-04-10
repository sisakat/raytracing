#include "color.hpp"
#include "common.hpp"

void writeColor(std::ostream& out, Color pixel_color, int samples_per_pixel)
{
    auto scale = 1.0 / samples_per_pixel;
    pixel_color *= scale;

    auto r = sqrt(pixel_color.x());
    auto g = sqrt(pixel_color.y());
    auto b = sqrt(pixel_color.z());

    out << fmt::format("{} {} {}\n",
                       static_cast<int>(256 * clamp(r, 0.0, 0.999)),
                       static_cast<int>(256 * clamp(g, 0.0, 0.999)),
                       static_cast<int>(256 * clamp(b, 0.0, 0.999)));
}

Color randomColor(double min, double max)
{
    return Color(randomDouble(min, max), randomDouble(min, max),
                 randomDouble(min, max));
}

Color randomColor()
{
    return randomColor(0.0, 1.0);
}