// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/light.h"

#include <typeinfo>

#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace prototype {

void PointLight::DrawContextMenu() {
  constexpr ImGuiTreeNodeFlags kTreeNodeFlags =
      ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowOverlap |
      ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
      ImGuiTreeNodeFlags_FramePadding;

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
  float line_height =
      GImGui->Font->LegacySize + GImGui->Style.FramePadding.y * 2.0f;
  ImGui::Separator();
  // NOLINTNEXTLINE
  bool open = ImGui::TreeNodeEx((void*)typeid(PointLight).hash_code(),
                                kTreeNodeFlags, "%s", "PointLight");
  ImGui::PopStyleVar();

  if (open) {
    ImGui::Text("This is Light Controller");
    ImGui::BeginDisabled(true);
    ImGui::SliderFloat3("position", glm::value_ptr(position), -100, 100);
    ImGui::EndDisabled();
    ImGui::SliderFloat3("ambient", glm::value_ptr(ambient), 0, 1);
    ImGui::SliderFloat3("diffuse", glm::value_ptr(diffuse), 0, 1);
    ImGui::SliderFloat3("specular", glm::value_ptr(specular), 0, 1);
    ImGui::TreePop();
  }
}

}  // namespace prototype
