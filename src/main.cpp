#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "consts.h"
#include "cam.h"

#include <iostream>

//making a linear gradient as background
color ray_color(const ray& r, const hittable &w, int depth) {
    hit_record rec;
    if (depth <= 0)
        return color(0,0,0);
    if (w.hit(r, 0, inf, rec)) {
        point3 target = rec.p + rec.normal + rand_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), w, depth - 1); //fix negatives, might fuck up colors
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const int samples = 100;
    const int image_width = 400;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int max_depth = 50;

    // Camera
    cam cam;

    hittable_list w;
    w.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    w.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    auto render = [&](){
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = image_height-1; j >= 0; --j) {
            std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples; ++s) {
                    auto u = (i + randouble()) / (image_width-1);
                    auto v = (j + randouble()) / (image_height-1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, w, max_depth);
                }
                write_color(std::cout, pixel_color, samples);
            }
        }
        std::cerr << "\nDone.\n";
    };

    render();
}
