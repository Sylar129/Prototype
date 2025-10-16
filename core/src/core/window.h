// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "GLFW/glfw3.h"
#include "core/renderer/camera.h"
#include "glm/glm.hpp"

namespace prototype::core {

struct WindowSpecification {
  std::string title;
  uint32_t width = 1280;
  uint32_t height = 720;
};

class Window {
 public:
  Window(const WindowSpecification& specification = WindowSpecification());
  ~Window();

  void Init();
  void Clear();

  void Update();

  glm::mat4 GetPorjection() const;
  glm::mat4 GetView() const;
  glm::vec2 GetFramebufferSize() const;

  bool ShouldClose() const;

  GLFWwindow* GetHandle() { return handle_; }

 private:
  WindowSpecification specification_;

  GLFWwindow* handle_ = nullptr;
  renderer::Camera camera_;
};

}  // namespace prototype::core
