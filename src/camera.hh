#pragma once

#include "vec.hh"
#include "image.hh"
#include "ray.hh"
#include "object.hh"
class Camera
{
 public:
    Camera(double aspect_ratio) 
        : 
        viewport_height_(2.0),
        viewport_width_(aspect_ratio*viewport_height_),
        horizontal_{viewport_width_, 0, 0},
        vertical_{0, viewport_height_, 0}
        {}

    void Render(Image &img, const ObjectList& objects) {
        auto lower_left_corner = origin_ - horizontal_/2 - vertical_/2 - Vec3(0, 0, focal_length_);

        const auto w = img.width;
        const auto h = img.height;
        for (int row = 0; row < h; ++row) {
            auto rowptr = img.GetRow(row);
            auto v = double(row)/(h-1);
            auto part_dir  = lower_left_corner + v*vertical_ - origin_;
            for (int col = 0; col < w; ++col) {
                auto pxl = &rowptr[col*3];
                auto u = double(col)/(w-1);
                const Ray r(origin_, part_dir + u*horizontal_);

                const auto c = ColorByNormal(objects, r);
                pxl[0] = c[0];
                pxl[1] = c[1];
                pxl[2] = c[2];
            }
        }
    }
 private:
    bool IsHit(const ObjectList& objects, const Ray &r) {
        for (const auto &o : objects) {
            if (o->Hit(r)) return true;
        }
        return false;
    }

    Color ColorByNormal(const ObjectList& objects, const Ray &r) {
        Color out = RayColor(r);
        double closest_distance = std::numeric_limits<double>::max();
        for (const auto &o : objects) {
            auto hit = o->Hit(r);
            if (hit) {
                auto dist = (r.Origin()-(*hit)).LengthSquared();
                if (dist < closest_distance) {
                    closest_distance = dist;
                    auto n = o->NormalAt(*hit);
                    out = (n+1.0).UnitVector();
                } 
            }
        }

        return out;
    }
 private:
    double viewport_height_{2.0};
    double viewport_width_{1.0};
    double focal_length_{1.0};
    Point origin_{0.0,0.0,0.0};
    Vec3 horizontal_;
    Vec3 vertical_;
};
