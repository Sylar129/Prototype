// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/light.h"

#include <typeinfo>

#include "glad/gl.h"
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

namespace {
float vertices[] = {
    // positions
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
    0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

    -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
};
}

LightCube::LightCube() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned
  // int),
  //              &indices_[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
                        (void*)0);

  glBindVertexArray(0);
}

void LightCube::Draw(Shader& shader) {
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
}

}  // namespace prototype
