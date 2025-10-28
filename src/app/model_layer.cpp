// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include "core/components/transform.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace prototype {

namespace {
void DrawVec3Control(const std::string& label, glm::vec3& values,
                     float reset_value = 0.0f, float column_width = 100.0f) {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, column_width);
  ImGui::Text("%s", label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

  float line_height =
      GImGui->Font->LegacySize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 button_size = {line_height + 3.0f, line_height};

  // X Button
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
  if (ImGui::Button("X", button_size)) {
    values.x = reset_value;
  }
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  // Y Button
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.3f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
  if (ImGui::Button("Y", button_size)) {
    values.y = reset_value;
  }
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  // Z Button
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                        ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
  if (ImGui::Button("Z", button_size)) {
    values.z = reset_value;
  }
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();

  ImGui::Columns(1);

  ImGui::PopID();
}

template <typename T, typename UIFunction>
void DrawComponent(const std::string& label, T& component,
                   UIFunction ui_function) {
  constexpr ImGuiTreeNodeFlags kTreeNodeFlags =
      ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowOverlap |
      ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
      ImGuiTreeNodeFlags_FramePadding;

  ImVec2 content_region_available = ImGui::GetContentRegionAvail();

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
  float line_height =
      GImGui->Font->LegacySize + GImGui->Style.FramePadding.y * 2.0f;
  ImGui::Separator();
  // NOLINTNEXTLINE
  bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), kTreeNodeFlags,
                                "%s", label.c_str());
  ImGui::PopStyleVar();

  ImGui::SameLine(content_region_available.x - line_height * 0.5f);
  if (ImGui::Button("+", ImVec2{line_height, line_height})) {
    ImGui::OpenPopup("ComponentSettings");
  }

  if (open) {
    ui_function(component);
    ImGui::TreePop();
  }
}

void DrawTransformMenu(TransformComponent& transform) {
  DrawComponent("Transform", transform, [](TransformComponent& component) {
    DrawVec3Control("Translation", component.translation);

    glm::vec3 rotation = glm::degrees(component.rotation);
    DrawVec3Control("Rotation", rotation);
    component.rotation = glm::radians(rotation);

    DrawVec3Control("Scale", component.scale, 1.0f);
  });
}
}  // namespace

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

  ImGui::Begin("Camera Controller");
  camera_.DrawController();
  DrawTransformMenu(model_transform_);
  ImGui::End();

  ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
  viewport_size_ = {viewport_panel_size.x, viewport_panel_size.y};
  // flip uv here
  ImGui::Image(framebuffer_.color_attachment, viewport_size_, {0, 1}, {1, 0});

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
