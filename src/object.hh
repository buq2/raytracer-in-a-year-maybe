#pragma once
#include "vec.hh"
#include "ray.hh"
#include <vector>
#include <memory>
#include <optional>

class Object
{
 public:
    virtual std::optional<Vec3> Hit(const Ray& r) = 0;
    virtual Vec3 NormalAt(const Vec3& pos) = 0;
};

using ObjectList = std::vector<std::unique_ptr<Object>>;

class Sphere
    : public Object
{
 public:
    Sphere(const Vec3 center, const double radius) : center_(center), radius_(radius) {}
    virtual std::optional<Vec3> Hit(const Ray& r) {
        const auto oc = r.Origin() - center_;
        const auto a = Dot(r.Direction(), r.Direction());
        const auto b = 2.0 * Dot(oc, r.Direction());
        const auto c = Dot(oc, oc) - radius_*radius_;
        const auto disc = b*b - 4*a*c;
        if (disc < 0) {
            return std::nullopt;
        } 

        const auto t = (-b - sqrt(disc)) / (2.0 * a);
        if (t < 0) {
            // First surface behind camera
            // Can be around camera too
            return std::nullopt;
        }

        // Return hit point
        return r.At(t);
    }

    virtual Vec3 NormalAt(const Vec3& pos) {
        return pos-center_;
    }
 private:
    Vec3 center_{0,0,0};
    double radius_{1.0};
};
