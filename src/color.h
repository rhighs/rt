#pragma once

#include "vec3.h"
#include "consts.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    double cmin = 0.0;
    double cmax = 0.999;
    
    //helps to dimm the color according tothe number of samples we do in it
    //in any case the values go out the interval [0, 1) those get clamped by the utility fn.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r); // sqrt basically means a gamma 2 correction
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    out << static_cast<int>(255.99 * clamp(r, cmin, cmax)) << " "
        << static_cast<int>(255.99 * clamp(g, cmin, cmax)) << " "
        << static_cast<int>(255.99 * clamp(b, cmin, cmax)) << "\n";
}
