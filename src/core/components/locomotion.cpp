// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/components/locomotion.h"

#include <algorithm>
#include <numbers>
#include <typeinfo>

#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace prototype {

namespace {
template <typename T>
T Wrap(T value, T min, T max) {
  T range = max - min;
  value = std::fmod(value - min, range);
  if (value < 0) {
    value += range;
  }
  return value + min;
}
}  // namespace

glm::vec3 SpiralMotion::UpdatePosition(float dt) {
  current_theta_ = Wrap<float>(current_theta_ + omega_theta_ * dt, 0,
                               2.0 * std::numbers::pi);
  current_phi_ = Wrap<float>(current_phi_ + omega_phi_ * dt, -std::numbers::pi,
                             std::numbers::pi);

  return CalculatePositionFromAngles();
}

void SpiralMotion::DrawMenu(const std::string& label) {
  if (ImGui::TreeNode("SpiralMotion")) {
    ImGui::SliderFloat3("Center", glm::value_ptr(center_), -100, 100);
    ImGui::SliderFloat("Radius", &radius_, 1, 100);
    ImGui::SliderAngle("Omega theta", &omega_theta_);
    ImGui::SliderAngle("Omega phi", &omega_phi_);

    ImGui::SliderAngle("Current theta", &current_theta_, 0);
    ImGui::SliderAngle("Current phi", &current_phi_, -180, 180);

    ImGui::TreePop();
  }
}

glm::vec3 SpiralMotion::CalculatePositionFromAngles() const {
  float r_projection_xz = radius_ * std::sin(current_phi_);

  glm::vec3 position;
  position.x = center_.x + r_projection_xz * std::cos(current_theta_);
  position.y = center_.y + radius_ * std::cos(current_phi_);
  position.z = center_.z + r_projection_xz * std::sin(current_theta_);

  return position;
}

}  // namespace prototype
