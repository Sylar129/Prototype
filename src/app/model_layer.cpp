// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include <memory>

#include "core/components/transform.h"
#include "core/renderer/framebuffer.h"
#include "core/renderer/light.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"

namespace prototype {

ModelLayer::ModelLayer()
    : camera_(glm::vec3(0.0f, 0.0f, 20.0f)),
      light_({1.2, 1.0, 2.0},  // postion
             {0.2, 0.2, 0.2},  // ambient
             {0.5, 0.5, 0.5},  // diffuse
             {1.0, 1.0, 1.0}   // specular
             ),
      orbit_light_(5, {0.0, 0.0, 0.0}, 1, 0.5, 0, 0) {}

ModelLayer::~ModelLayer() {}

void ModelLayer::OnAttach() {
  // Create shaders
  model_shader_.Compile("assets/shaders/model.vert",
                        "assets/shaders/model.frag");
  light_shader_.Compile("assets/shaders/light.vert",
                        "assets/shaders/light.frag");
  framebuffer_ = std::make_unique<Framebuffer>(1920, 1080);
  model_.LoadModel("assets/models/backpack/backpack.obj");
  model_.Process();
}

void ModelLayer::OnDetach() {
  model_shader_.Delete();
  light_shader_.Delete();
}

void ModelLayer::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch(this, &ModelLayer::OnKeyPressedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnKeyReleasedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseButtonPressedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseButtonReleasedEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseScrolledEvent);
  dispatcher.Dispatch(this, &ModelLayer::OnMouseMovedEvent);
}

void ModelLayer::OnUpdate(float ts) {
  camera_.ProcessKeyboard(camera_move_, ts);

  framebuffer_->BeginRecording();
  model_shader_.Use();

  light_.position = orbit_light_.UpdatePosition(ts);

  model_shader_.SetCamara("", camera_);
  model_shader_.SetPointLight("light", light_);

  // render the loaded model
  model_shader_.SetMat4("model", model_transform_.getMatrix());
  model_.Draw(model_shader_);

  light_shader_.Use();
  auto projection = glm::perspective(glm::radians(camera_.GetZoom()),
                                     (float)1920 / (float)1080, 0.1f, 100.0f);
  light_shader_.SetMat4("projection", projection);
  light_shader_.SetMat4("view", camera_.GetViewMatrix());
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::mat4(1.0f);
  model = glm::translate(model, light_.position);
  model = glm::scale(model, glm::vec3(0.2f));  // a smaller cube
  light_shader_.SetMat4("model", model);
  light_cube_.Draw(light_shader_);

  framebuffer_->EndRecording();
}

void ModelLayer::OnRender() {
  ImGui::Begin("viewport");

  ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
  // flip uv here
  ImGui::Image(framebuffer_->color_attachment, viewport_panel_size, {0, 1},
               {1, 0});

  ImGui::End();

  ImGui::Begin("Camera Controller");
  camera_.DrawContextMenu();
  light_.DrawContextMenu();
  orbit_light_.DrawMenu();
  model_transform_.DrawMenu("Model Transform");
  ImGui::End();
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
