// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include "core/components/transform.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "imgui.h"

namespace prototype {

ModelLayer::ModelLayer()
    : model_("assets/models/backpack/backpack.obj"),
      camera_(glm::vec3(0.0f, 0.0f, 20.0f)),
      viewport_size_(1920, 1080) {}

ModelLayer::~ModelLayer() {}

void ModelLayer::OnAttach() {
  // Create shaders
  shader_.Compile("assets/shaders/model.vert", "assets/shaders/model.frag");
  framebuffer_ = renderer::CreateFrameBuffer();
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

  framebuffer_.Bind();
  shader_.Use();

  auto projection = glm::perspective(glm::radians(camera_.GetZoom()),
                                     (float)1920 / (float)1080, 0.1f, 100.0f);
  shader_.SetMat4("projection", projection);
  shader_.SetMat4("view", camera_.GetViewMatrix());

  // render the loaded model
  shader_.SetMat4("model", model_transform_.getMatrix());
  model_.Draw(shader_);
  framebuffer_.Unbind();
}

void ModelLayer::OnRender() {
  ImGui::Begin("viewport");

  ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
  viewport_size_ = {viewport_panel_size.x, viewport_panel_size.y};
  // flip uv here
  ImGui::Image(framebuffer_.color_attachment, viewport_size_, {0, 1}, {1, 0});

  ImGui::End();

  ImGui::Begin("Camera Controller");
  camera_.DrawController();
  model_transform_.DrawMenu("Model Transform");
  ImGui::End();
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
