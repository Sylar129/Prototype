// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/light.h"

#include <typeinfo>

#include "core/renderer/shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace prototype {

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient,
                       const glm::vec3& diffuse, const glm::vec3& specular)
    : position(position),
      ambient(ambient),
      diffuse(diffuse),
      specular(specular) {}

void PointLight::SetupMotion(const SpiralMotion& motion) { motion_ = motion; }

void PointLight::Update(float dt) {
  position = motion_.UpdatePosition(movable_ ? dt : 0);
}

void PointLight::Render(const Camera& camera) {
  auto& light_shader = *ShaderLibrary::GetInstance().Get("light");
  light_shader.Use();
  auto projection = glm::perspective(glm::radians(camera.GetZoom()),
                                     (float)1920 / (float)1080, 0.1f, 100.0f);
  light_shader.SetMat4("projection", projection);
  light_shader.SetMat4("view", camera.GetViewMatrix());
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::scale(model, glm::vec3(0.2f));  // a smaller cube
  light_shader.SetMat4("model", model);
  light_cube_.Draw(light_shader);
}

void PointLight::RenderMenu() {
  DrawContextMenu();
  ImGui::BeginDisabled(movable_);
  motion_.DrawMenu();
  ImGui::EndDisabled();
}

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
    ImGui::Checkbox("auto move", &movable_);
    ImGui::TreePop();
  }
}

}  // namespace prototype
