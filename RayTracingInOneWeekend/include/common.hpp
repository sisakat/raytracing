#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double deg = pi / 180.0;
const double rad = 1.0;

/**
 * @brief Returns a random double [0, 1)
 */
inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

#include "color.hpp"
#include "ray.hpp"
#include "types.hpp"