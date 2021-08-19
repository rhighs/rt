#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "material.h"
#include <cstdint>

/*
 * For the found equation we just need the ray direction ( given by the pixel position on the 3d plane and, 
 * expressed in any form, be it normal or not) then test the equation, if it has 1 or more 2 solutions,
 * ray is a tangent or a secant.
 */

struct hit_eq {
    std::uint8_t nsol;
    double a;
    double half_b;
    double c;
    vec3 oc; // this is the A-C in the equation
    double delta;
};

hit_eq hit_sphere(const point3& center, double radius, const ray& r){
    hit_eq eq;
    eq.oc = r.origin() - center;
    eq.a = dot(r.direction(), r.direction());
    eq.half_b = dot(r.direction(), eq.oc); //dot product property, switching the orders its the same
    eq.c = eq.oc.length_squared() - radius*radius; //vector dotted with itself is its squared len
    eq.delta = eq.half_b * eq.half_b - eq.a*eq.c;

    if(!eq.delta) {
        eq.nsol = 1;
    } else if (eq.delta > 0) {
        eq.nsol = 2;
    } else if (eq.delta < 0) {
        eq.nsol = 0;
    }
    return eq;
}
//the A-C in the equation
class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, double r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {}
        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    auto eq = hit_sphere(center, radius, r);
    if(eq.nsol == 0) return false;

    auto sqrtd = sqrt(eq.delta);
    auto root = (-eq.half_b - sqrtd) / eq.a;
    if(root < t_min || t_max < root) {
        root = (-eq.half_b + sqrtd) / eq.a;
        if ( root < t_min || t_max < root )
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
