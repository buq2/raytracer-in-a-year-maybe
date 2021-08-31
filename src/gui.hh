#pragma once

#include <functional>
#include <string>

class GuiWindowPrivate;

class GuiWindow {
 public:
  GuiWindow(const std::string &title = "Config");
  ~GuiWindow();

  bool Initialize();
  bool Draw(std::function<void()> fun);
  bool StartDraw();
  void EndDraw();
  void SetAutoResize(const bool auto_resize) { auto_resize_ = auto_resize; };

 private:
  void Uninit();
  GuiWindow(const GuiWindow &) = delete;
  GuiWindow &operator=(const GuiWindow &) = delete;

 private:
  GuiWindowPrivate *p_{nullptr};
  std::string title_;
  bool auto_resize_{true};
};
