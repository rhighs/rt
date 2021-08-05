#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double inf = std::numeric_limits<double>::infinity();
const double pi = M_PI;

inline double randouble() {
    //real € [0,1)
    return rand() / (RAND_MAX / + 1.0);
}

inline double randouble(double min, double max) {
    return min + (max - min) * randouble();
}

inline double deg_to_rad(double degrees) {
    return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max){
    if (x<min) return min;
    if (x>max) return max;
    return x;
}

