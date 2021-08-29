#pragma once

#include "consts.h"

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 
{
    public:
        vec3() : e{0,0,0}{}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2}{}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        inline static vec3 random() {
            return vec3(randouble(), randouble(), randouble());
        }

        inline static vec3 random(double min, double max) {
            return vec3(randouble(min, max), randouble(min, max), randouble(min, max));
        }

        std::ostream &operator<<(std::ostream &out){
            return out << e[0] << ' ' << e[1] << ' ' << e[2];
        }

        bool near_zero() const {
            const auto s = 1e-8;
            return (fabs(e[0]) < s && fabs(e[1]) < s && fabs(e[2]) < s);
        }

    public:
        double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 *zero_vector() {
    return new vec3(0,0,0);
}

inline vec3 rand_unit_sphere() {
    while(true) {
        auto point = vec3::random(-1, 1);
        if (point.length() >= 1) 
            continue;
        return point;
    }
}

inline static vec3 random_unit_vec() {
    return unit_vector(rand_unit_sphere());
}

inline static vec3 reflect(const vec3 &v, const vec3& n) {
    auto proj_vn = dot(v, n) * n;
    return v - 2*(proj_vn);
}

inline static vec3 random_in_hemisphere(const vec3 &normal) {
    vec3 inus = rand_unit_sphere();
    return dot(inus, normal) > 0.0 ? inus : -inus;
}

