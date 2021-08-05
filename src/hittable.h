#pragma once

#include "ray.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face; //the face directed towards the eye

    //implementation to set normal always point against eye at geometry time rather than color time
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0; //checks ray and normal direction
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

class hittable_list : public hittable {
    public:
        hittable_list() {}
        hittable_list(shared_ptr<hittable> obj){ add(obj); }
        void clear() { objs.clear(); }
        void add(shared_ptr<hittable> obj) { objs.push_back(obj); }
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objs;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_some = false;
    auto closest = t_max;
    auto scan_hit = [&](shared_ptr<hittable> object) {
        if(object->hit(r, t_min, closest, temp_rec)) {
            hit_some = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    };
    for(const auto& obj : objs){
        scan_hit(obj);
    }
    return hit_some;
}
