#pragma once

#include "vec3.h"
#include "consts.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();
    
    //helps to dimm the color according tothe number of samples we do in it
    //in any case the values go out the interval [0, 1) those get clamped by the utility fn.
    auto scale = 1.0 / samples_per_pixel;
    r = clamp(r * scale, 0, 0.99);
    g = clamp(g * scale, 0, 0.99);
    b = clamp(b * scale, 0, 0.99);
    out << static_cast<int>(255.99 * r) << " "
        << static_cast<int>(255.99 * g) << " "
        << static_cast<int>(255.99 * b) << "\n";
}
