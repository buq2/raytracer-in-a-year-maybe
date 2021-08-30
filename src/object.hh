#pragma once
#include "vec.hh"
#include "ray.hh"
#include <vector>
#include <memory>
#include <optional>

struct HitStruct {
    double t; // ray distance to the hit location
    Vec3 location;
    Vec3 normal;
    bool front_face;

    inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
        front_face = Dot(r.Direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Object
{
 public:
    virtual std::optional<HitStruct> Hit(const Ray& r) = 0;
    virtual Vec3 NormalAt(const Vec3& pos) = 0;
};

using ObjectList = std::vector<std::unique_ptr<Object>>;

class Sphere
    : public Object
{
 public:
    Sphere(const Vec3 center, const double radius) : center_(center), radius_(radius) {}
    virtual std::optional<HitStruct> Hit(const Ray& r) {
        const auto oc = r.Origin() - center_;
        const auto a = r.Direction().LengthSquared();
        const auto half_b = Dot(oc, r.Direction());
        const auto c = oc.LengthSquared() - radius_*radius_;
        const auto disc = half_b*half_b - a*c;
        if (disc < 0) {
            return std::nullopt;
        } 

        const auto t = (-half_b - sqrt(disc)) / (a);
        if (t < 0) {
            // First surface behind camera
            // Can be around camera too
            return std::nullopt;
        }

        // Return hit point
        HitStruct s;
        s.t = t;
        s.location = r.At(t);
        s.SetFaceNormal(r, NormalAt(s.location));
        return s;
    }

    virtual Vec3 NormalAt(const Vec3& pos) {
        return pos-center_;
    }
 private:
    Vec3 center_{0,0,0};
    double radius_{1.0};
};
