// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/window.h"

#include <assert.h>

#include "core/log.h"
#include "events/application_event.h"
#include "events/key_codes.h"
#include "events/key_event.h"
#include "events/mouse_codes.h"
#include "events/mouse_event.h"
#include "glad/gl.h"

namespace prototype::core {

Window::Window(const WindowSpecification& specification)
    : data_(specification.title, specification.width, specification.height) {}

Window::~Window() {}

void Window::Init() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  handle_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(),
                             nullptr, nullptr);

  if (!handle_) {
    CORE_LOG_ERROR("Failed to create GLFW window!");
    assert(false);
  }

  glfwMakeContextCurrent(handle_);
  gladLoadGL(glfwGetProcAddress);
  glEnable(GL_DEPTH_TEST);

  glfwSetWindowUserPointer(handle_, &data_);

  SetCallback();
}

void Window::Clear() {
  if (handle_) {
    glfwDestroyWindow(handle_);
  }

  handle_ = nullptr;
}

void Window::Update() { glfwSwapBuffers(handle_); }

void Window::SetEventCallback(const EventCallbackFn& callback) {
  data_.event_callback = callback;
}

glm::vec2 Window::GetFramebufferSize() const {
  return {data_.width, data_.height};
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(handle_) != 0; }

void Window::SetCallback() {
  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      handle_, [](GLFWwindow* window, int width, int height) {
        WindowData& data =
            *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
      });

  glfwSetWindowCloseCallback(handle_, [](GLFWwindow* window) {
    WindowData& data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    WindowCloseEvent event;
    data.event_callback(event);
  });

  glfwSetKeyCallback(handle_, [](GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
    WindowData& data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    KeyCode key_code = static_cast<KeyCode>(key);
    switch (action) {
      case GLFW_PRESS: {
        KeyPressdEvent event(key_code, 0);
        data.event_callback(event);
        break;
      }
      case GLFW_RELEASE: {
        KeyReleasedEvent event(key_code);
        data.event_callback(event);
        break;
      }
      case GLFW_REPEAT: {
        KeyPressdEvent event(key_code, 1);
        data.event_callback(event);
        break;
      }
      default:
        break;
    }
  });

  glfwSetCharCallback(handle_, [](GLFWwindow* window, unsigned int codepoint) {
    WindowData& data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    KeyTypedEvent event(static_cast<KeyCode>(codepoint));
    data.event_callback(event);
  });

  glfwSetMouseButtonCallback(
      handle_, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data =
            *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseCode mouse_code = static_cast<MouseCode>(button);
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(mouse_code);
            data.event_callback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(mouse_code);
            data.event_callback(event);
            break;
          }
          default:
            break;
        }
      });

  glfwSetScrollCallback(
      handle_, [](GLFWwindow* window, double x_offset, double y_offset) {
        WindowData& data =
            *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event(static_cast<float>(x_offset),
                                 static_cast<float>(y_offset));
        data.event_callback(event);
      });

  glfwSetCursorPosCallback(handle_, [](GLFWwindow* window, double x_pos,
                                       double y_pos) {
    WindowData& data =
        *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

    MouseMovedEvent event(static_cast<float>(x_pos), static_cast<float>(y_pos));
    data.event_callback(event);
  });
}

}  // namespace prototype::core
