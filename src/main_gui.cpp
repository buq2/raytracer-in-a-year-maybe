#include <GL/glew.h>
#include <chrono>
#include "camera.hh"
#include "gui.hh"
#include "image.hh"
#include "imgui.h"

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
