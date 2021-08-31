#include <GL/glew.h>
#include <chrono>
#include "camera.hh"
#include "gui.hh"
#include "image.hh"
#include "imgui.h"

class Texture {
 public:
  ~Texture() { DestroyTexture(); }

  GLuint GetTexture() { return image_texture_; }

  void Display() {
    if (texture_created_) {
      ImGui::Image(
          (void *)(intptr_t)image_texture_,
          ImVec2(static_cast<float>(width_), static_cast<float>(height_)));
    }
  }

  void SetTexture(const int image_width, const int image_height,
                  const unsigned char *image_data) {
    DestroyTexture();

    glGenTextures(1, &image_texture_);
    texture_created_ = true;
    width_ = image_width;
    height_ = image_height;
    glBindTexture(GL_TEXTURE_2D, image_texture_);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);  // This is required on WebGL for non
                                        // power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE);  // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image_data);
  }

 private:
  void DestroyTexture() {
    if (texture_created_) {
      glDeleteTextures(1, &image_texture_);
      texture_created_ = false;
    }
  }

 private:
  int width_{0};
  int height_{0};
  bool texture_created_{false};
  GLuint image_texture_;
};

struct SceneCreator {
  float pos_x{0.0f};
  float pos_y{0.0f};
  float pos_z{0.0f};
  float radius{0.5f};
  ObjectList objects;
  double aspect_ratio = 16.0 / 9.0;
  const int width = 400;
  Image im{width, static_cast<int>(width / aspect_ratio)};
  Texture texture;
  float previous_command_time_{0.0f};

  SceneCreator() {
    objects.emplace_back(new Sphere(Vec3(0.0, 0.0, -1.0), 0.5));
    objects.emplace_back(new Sphere(Vec3(0.5, 0.0, -1.0), 0.7));
  }

  class Timer {
   public:
    Timer(float *out_time)
        : out_time_(out_time),
          start_(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = finish - start_;
      *out_time_ = static_cast<float>(
          std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
              .count());
    }

   private:
    float *out_time_{0};
    std::chrono::steady_clock::time_point start_;
  };

  void CreateScene() {
    Camera cam(aspect_ratio);

    ImGui::SliderFloat("x", &pos_x, -1.0f, 1.0f);
    ImGui::SliderFloat("y", &pos_y, -1.0f, 1.0f);
    ImGui::SliderFloat("z", &pos_z, -1.0f, 1.0f);
    ImGui::SliderFloat("radius", &radius, 0.0f, 1.0f);

    if (ImGui::Button("Add sphere")) {
      objects.emplace_back(new Sphere(Vec3(pos_x, pos_y, pos_z), radius));
    }

    if (ImGui::Button("Render")) {
      Timer timer(&previous_command_time_);
      cam.Render(im, objects);
      const auto data = im.GetAsUint8Vector();
      texture.SetTexture(im.width, im.height, &data[0]);
    }

    if (ImGui::Button("Render to pgm")) {
      Timer timer(&previous_command_time_);
      cam.Render(im, objects);
      im.Write("test.ppm");
    }

    ImGui::Text("%0.0fms", previous_command_time_);

    ImGui::Begin("img");
    texture.Display();
    ImGui::End();
  }
};

int main(int argc, char *argv[]) {
  GuiWindow conf("win");
  SceneCreator scene_creator;

  conf.SetAutoResize(false);
  conf.Initialize();
  while (!conf.Draw([&]() { scene_creator.CreateScene(); })) {
  }

  return 0;
}
