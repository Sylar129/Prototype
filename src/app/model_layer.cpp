// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include "core/components/transform.h"
#include "core/renderer/light.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "imgui.h"

namespace prototype {

ModelLayer::ModelLayer()
    : camera_(glm::vec3(0.0f, 0.0f, 20.0f)),
      light_({1.2, 1.0, 2.0},  // postion
             {0.2, 0.2, 0.2},  // ambient
             {0.5, 0.5, 0.5},  // diffuse
             {1.0, 1.0, 1.0}   // specular
             ),
      viewport_size_(1920, 1080) {}

ModelLayer::~ModelLayer() {}

void ModelLayer::OnAttach() {
  // Create shaders
  shader_.Compile("assets/shaders/model.vert", "assets/shaders/model.frag");
  framebuffer_ = CreateFrameBuffer();
  model_.LoadModel("assets/models/backpack/backpack.obj");
  model_.Process();
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
  shader_.SetVec3("view_pos", camera_.GetPosition());

  shader_.SetPointLight("light", light_);

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
  light_.DrawContextMenu();
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
      camera_move_ = Camera::Movement::kForward;
      break;
    case KeyCode::kS:
      camera_move_ = Camera::Movement::kBackward;
      break;
    case KeyCode::kA:
      camera_move_ = Camera::Movement::kLeft;
      break;
    case KeyCode::kD:
      camera_move_ = Camera::Movement::kRight;
      break;
    default:
      camera_move_ = Camera::Movement::kStill;
  }
  return false;
}

bool ModelLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
  camera_move_ = Camera::Movement::kStill;
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
