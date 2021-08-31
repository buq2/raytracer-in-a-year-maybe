#pragma once
#include <fstream>
#include <vector>
#include "vec.hh"

class Image {
 public:
  int width{0};
  int height{0};
  double *data{0};

  Image(int width, int height)
      : width(width), height(height), data(new double[width * height * 3]) {}

  Image(const Image &img) = delete;

  ~Image() {
    delete[] data;
    data = 0;
    width = 0;
    height = 0;
  }

  int StridePixels() const { return width * 3; }

  double *GetRow(int row) { return &data[row * StridePixels()]; }

  std::vector<uint8_t> GetAsUint8Vector() {
    std::vector<uint8_t> out(width * height * 3);
    for (int row = 0; row < height; ++row) {
      auto rowptr = GetRow(row);
      for (int col = 0; col < width; ++col) {
        const auto c = Color(&rowptr[col * 3]);

        out[row * width * 3 + col * 3 + 0] =
            static_cast<uint8_t>(c[0] * 255.999);
        out[row * width * 3 + col * 3 + 1] =
            static_cast<uint8_t>(c[1] * 255.999);
        out[row * width * 3 + col * 3 + 2] =
            static_cast<uint8_t>(c[2] * 255.999);
      }
    }

    return out;
  }

  void Write(const std::string &fname) {
    std::ofstream file(fname);
    file << "P3\n" << width << ' ' << height << "\n255\n";
    for (int row = 0; row < height; ++row) {
      auto rowptr = GetRow(row);
      for (int col = 0; col < width; ++col) {
        const auto c = Color(&rowptr[col * 3]);
        WriteColor(file, c);
      }
    }
  }

  void SetToTestImage() {
    for (int row = 0; row < height; ++row) {
      auto rowptr = GetRow(row);
      for (int col = 0; col < width; ++col) {
        auto pxl = &rowptr[col * 3];
        pxl[0] = static_cast<double>(col) / (width - 1);
        pxl[1] = static_cast<double>(row) / (height - 1);
        pxl[2] = 0.25;
      }
    }
  }

 private:
};
