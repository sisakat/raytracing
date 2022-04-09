#include "color.hpp"
#include "common.hpp"

void writeColor(std::ostream& out, Color pixel_color, int samples_per_pixel)
{
    auto scale = 1.0 / samples_per_pixel;
    pixel_color *= scale;

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    out << fmt::format("{} {} {}\n",
                       static_cast<int>(256 * clamp(r, 0.0, 0.999)),
                       static_cast<int>(256 * clamp(g, 0.0, 0.999)),
                       static_cast<int>(256 * clamp(b, 0.0, 0.999)));
}