#pragma once

#include <Eigen/Core>
#include <spdlog/spdlog.h>
#include <iostream>

using Color = Eigen::Vector3d;

void writeColor(std::ostream& out, Color pixel_color, int samples_per_pixel);
Color randomColor(double min, double max);
Color randomColor();