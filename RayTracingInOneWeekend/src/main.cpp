#include "color.hpp"

#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
    const int image_width = 256;
    const int image_height = 256;

    std::cout << fmt::format("P3\n{} {}\n255", image_width, image_height)
              << std::endl;

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << fmt::format("\rScanlines remaining: {}", j) << std::endl;
        for (int i = 0; i < image_width; ++i)
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            Color pixel_color(r, g, b);
            writeColor(std::cout, pixel_color);
        }
    }

    std::cerr << "Done" << std::endl;
}