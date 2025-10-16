// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/window.h"

#include <assert.h>

#include "core/log.h"
#include "glad/gl.h"

namespace prototype::core {

Window::Window(const WindowSpecification& specification)
    : specification_(specification),
      camera_(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f)) {}

Window::~Window() {}

void Window::Init() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  handle_ = glfwCreateWindow(specification_.width, specification_.height,
                             specification_.title.c_str(), nullptr, nullptr);

  if (!handle_) {
    CORE_LOG_ERROR("Failed to create GLFW window!");
    assert(false);
  }
  camera_.Init(handle_);

  glfwMakeContextCurrent(handle_);
  gladLoadGL(glfwGetProcAddress);
  glEnable(GL_DEPTH_TEST);
}

void Window::Clear() {
  if (handle_) {
    glfwDestroyWindow(handle_);
  }

  handle_ = nullptr;
}

void Window::Update() {
  camera_.ProcessInput();
  glfwSwapBuffers(handle_);
}

glm::mat4 Window::GetPorjection() const {
  return glm::perspective(
      glm::radians(camera_.GetZoom()),
      (float)specification_.width / (float)specification_.height, 0.1f, 100.0f);
}

glm::mat4 Window::GetView() const { return camera_.GetViewMatrix(); }

glm::vec2 Window::GetFramebufferSize() const {
  int width, height;
  glfwGetFramebufferSize(handle_, &width, &height);
  return {width, height};
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(handle_) != 0; }

}  // namespace prototype::core
