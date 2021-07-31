#pragma once

#include "vec.hh"

class Ray
{
 public:
    Ray() {}
    Ray(const Point& origin, const Point& direction) 
        :
        origin_(origin), direction_(direction)
        {}
    
    auto Origin() const {return origin_;}
    auto Direction() const {return direction_;}
    auto At(double t) const {return Origin() + Direction()*t;}
 private:
    Point origin_;
    Vec3 direction_;
};

Color RayColor(const Ray& r) {
    auto unit_direction = r.Direction().UnitVector();
    const auto t = 0.5 * (unit_direction.Y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}
