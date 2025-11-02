// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/components/transform.h"

#include <typeinfo>

#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

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
}  // namespace

glm::mat4 TransformComponent::getMatrix() const {
  glm::mat4 m = glm::mat4(1.0f);
  m = glm::translate(m, translation);
  m *= glm::toMat4(glm::quat(rotation));
  m = glm::scale(m, scale);
  return m;
}

void TransformComponent::DrawMenu(const std::string& label) {
  constexpr ImGuiTreeNodeFlags kTreeNodeFlags =
      ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowOverlap |
      ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
      ImGuiTreeNodeFlags_FramePadding;

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
  float line_height =
      GImGui->Font->LegacySize + GImGui->Style.FramePadding.y * 2.0f;
  ImGui::Separator();
  // NOLINTNEXTLINE
  bool open = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(),
                                kTreeNodeFlags, "%s", label.c_str());
  ImGui::PopStyleVar();

  if (open) {
    DrawVec3Control("Translation", translation);

    glm::vec3 r = glm::degrees(rotation);
    DrawVec3Control("Rotation", r);
    rotation = glm::radians(r);

    DrawVec3Control("Scale", scale, 1.0f);

    ImGui::TreePop();
  }
}
}  // namespace prototype
