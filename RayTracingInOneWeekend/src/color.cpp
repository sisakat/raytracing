#include "color.hpp"

void writeColor(std::ostream& out, Color pixel_color)
{
    out << fmt::format("{} {} {}\n",
                       static_cast<int>(255.999 * pixel_color.x()),
                       static_cast<int>(255.999 * pixel_color.y()),
                       static_cast<int>(255.999 * pixel_color.z()));
}