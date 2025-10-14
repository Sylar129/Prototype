// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace prototype::core {

struct WindowSpecification {
  std::string title;
  uint32_t width = 1280;
  uint32_t height = 720;
  bool is_resizeable = true;
  bool vsync = true;
};

class Window {
 public:
  Window(const WindowSpecification& specification = WindowSpecification());
  ~Window();

  void Create();
  void Destroy();

  void Update();

  glm::vec2 GetFramebufferSize() const;

  bool ShouldClose() const;

  GLFWwindow* GetHandle() { return handle_; }

 private:
  WindowSpecification specification_;

  GLFWwindow* handle_ = nullptr;
};

}  // namespace prototype::core
