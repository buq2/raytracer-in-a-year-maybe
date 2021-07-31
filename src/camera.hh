#pragma once

#include "vec.hh"
#include "image.hh"
#include "ray.hh"

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

    void Render(Image &img) {
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
                const auto c = RayColor(r);
                pxl[0] = c[0];
                pxl[1] = c[1];
                pxl[2] = c[2];
            }
        }
    }
 private:
    double viewport_height_{2.0};
    double viewport_width_{1.0};
    double focal_length_{1.0};
    Point origin_{0.0,0.0,0.0};
    Vec3 horizontal_;
    Vec3 vertical_;
};
