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

static vec3 const & zero_vector = vec3(0, 0, 0);

std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 rand_unit_sphere() {
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

static vec3 reflect(const vec3 &v, const vec3& n) {
    auto proj_vn = dot(v, n) * n;
    return v - 2*(proj_vn);
}

static vec3 random_in_hemisphere(const vec3 &normal) {
    vec3 inus = rand_unit_sphere();
    return dot(inus, normal) > 0.0 ? inus : -inus;
}


/*
 * copied it from the book, it just gives you a clean solution for Snell's refraction law
 */
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 refract_with_eta(vec3 const & normal, vec3 const & incident, double eta1, double eta2) {
    double idx_ratio = eta1 / eta2;
    double cosI = -dot(normal, incident); //incident must be already normalized
    double sinT2 = idx_ratio * idx_ratio * (1 - cosI * cosI);
    if(sinT2 > 1.0) return zero_vector;
    double cosT = sqrt(1.0 - sinT2);
    return idx_ratio * incident + (idx_ratio * cosI - cosT) * normal;
}
