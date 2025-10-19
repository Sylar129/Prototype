// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include "GLFW/glfw3.h"
#include "core/application.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace prototype {

ModelLayer::ModelLayer()
    : model_("assets/models/backpack/backpack.obj"),
      camera_(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f)) {}

ModelLayer::~ModelLayer() {}

void ModelLayer::OnAttach() {
  // Create shaders
  shader_.Compile("assets/shaders/model.vert", "assets/shaders/model.frag");
}

void ModelLayer::OnDetach() { shader_.Delete(); }

void ModelLayer::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch(this, &ModelLayer::OnWindowResizeEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnKeyPressedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnKeyReleasedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseButtonPressedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseButtonReleasedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseScrolledEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseMovedEvent);
}

void ModelLayer::OnUpdate(float ts) {
  camera_.ProcessKeyboard(camera_move_, ts);
}

void ModelLayer::OnRender() {
  shader_.Use();

  auto projection = glm::perspective(glm::radians(camera_.GetZoom()),
                                     (float)1920 / (float)1080, 0.1f, 100.0f);
  shader_.SetMat4("projection", projection);
  shader_.SetMat4("view", camera_.GetViewMatrix());

  // render the loaded model
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(
      model,
      glm::vec3(0.0f, 0.0f,
                0.0f));  // translate it down so it's at the center of the scene
  model = glm::scale(
      model,
      glm::vec3(1.0f, 1.0f,
                1.0f));  // it's a bit too big for our scene, so scale it down
  shader_.SetMat4("model", model);
  model_.Draw(shader_);
}

bool ModelLayer::OnWindowResizeEvent(WindowResizeEvent& event) {
  window_width_ = event.GetWidth();
  window_height_ = event.GetHeight();
  return false;
}

bool ModelLayer::OnKeyPressedEvent(KeyPressdEvent& event) {
  switch (event.GetKeyCode()) {
    case KeyCode::kW:
      camera_move_ = renderer::Camera::Movement::kForward;
      break;
    case KeyCode::kS:
      camera_move_ = renderer::Camera::Movement::kBackward;
      break;
    case KeyCode::kA:
      camera_move_ = renderer::Camera::Movement::kLeft;
      break;
    case KeyCode::kD:
      camera_move_ = renderer::Camera::Movement::kRight;
      break;
    default:
      camera_move_ = renderer::Camera::Movement::kStill;
  }
  return false;
}

bool ModelLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
  camera_move_ = renderer::Camera::Movement::kStill;
  return false;
}

bool ModelLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
  if (event.GetMouseButton() == MouseCode::kButtonRight) {
    camera_can_move_ = true;
  }
  return false;
}

bool ModelLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
  if (event.GetMouseButton() == MouseCode::kButtonRight) {
    camera_can_move_ = false;
  }
  return false;
}

bool ModelLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
  camera_.ProcessMouseScroll(event.GetYOffset());
  return false;
}

bool ModelLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
  static float last_x = 400;
  static float last_y = 300;
  static bool first = true;

  auto xpos = event.GetX();
  auto ypos = event.GetY();

  if (first) {
    last_x = xpos;
    last_y = ypos;
    first = false;
  }
  if (camera_can_move_) {
    camera_.ProcessMouseMovement(xpos - last_x, last_y - ypos);
  }
  last_x = xpos;
  last_y = ypos;
  return false;
}

}  // namespace prototype
