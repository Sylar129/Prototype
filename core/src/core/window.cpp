// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/window.h"

#include <assert.h>

#include "core/log.h"
#include "glad/gl.h"

namespace prototype::core {

Window::Window(const WindowSpecification& specification)
    : specification_(specification) {}

Window::~Window() {}

void Window::Create() {
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

  glfwMakeContextCurrent(handle_);
  gladLoadGL(glfwGetProcAddress);

  glfwSwapInterval(specification_.vsync ? 1 : 0);
}

void Window::Destroy() {
  if (handle_) {
    glfwDestroyWindow(handle_);
  }

  handle_ = nullptr;
}

void Window::Update() { glfwSwapBuffers(handle_); }

glm::vec2 Window::GetFramebufferSize() const {
  int width, height;
  glfwGetFramebufferSize(handle_, &width, &height);
  return {width, height};
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(handle_) != 0; }

}  // namespace prototype::core
