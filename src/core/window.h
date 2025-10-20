// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "GLFW/glfw3.h"
#include "core/events/event.h"
#include "glm/glm.hpp"

namespace prototype::core {

struct WindowSpecification {
  std::string title;
  uint32_t width = 1280;
  uint32_t height = 720;
};

class Window {
 public:
  using EventCallbackFn = std::function<void(Event&)>;

  Window(const WindowSpecification& specification);
  ~Window();

  void Init();
  void Clean();

  void Update();

  void SetEventCallback(const EventCallbackFn& callback);

  glm::vec2 GetFramebufferSize() const;

  bool ShouldClose() const;

  GLFWwindow* GetHandle() { return handle_; }

 private:
  struct WindowData {
    std::string title;
    int width;
    int height;
    EventCallbackFn event_callback;
  };

  void SetCallback();

  GLFWwindow* handle_ = nullptr;
  WindowData data_;
};

}  // namespace prototype::core
