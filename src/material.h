#pragma once

#include "consts.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class material {
    public:
        virtual bool scatter(
            const ray &incoming,
            const hit_record &record,
            color &attenuation,
            ray& scattered
        ) const = 0;
};

class metal : public material {
    public:
        metal(const color& a) : albedo(a) {}
        virtual bool scatter(
            const ray &incoming,
            const hit_record &record,
            color &attenuation,
            ray& scattered
        ) const override {
            vec3 reflected = reflect(unit_vector(incoming.direction()), record.normal);
            scattered = ray(record.p, reflected);
            attenuation = albedo;
            return dot(scattered.direction(), record.normal) > 0;
        }

    public:
        color albedo;
};

class lambertian : public material {
    public:
        lambertian(const color& a) : albedo(a) {}

        //just reflect the ray and dont absorb it
        virtual bool scatter(
            const ray &incoming,
            const hit_record &record,
            color &attenuation,
            ray& scattered
        ) const override {
            auto scatter_dir = record.normal + random_unit_vec();
            if(scatter_dir.near_zero()) scatter_dir = record.normal;
            scattered = ray(record.p, scatter_dir);
            attenuation = albedo;
            return true;
        };

    public:
        color albedo;
};
