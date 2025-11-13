// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/components/locomotion.h"

namespace prototype {

glm::vec3 SpiralMotion::UpdatePosition(float dt) {
  current_theta_ += omega_theta_ * dt;
  current_phi_ += omega_phi_ * dt;
  current_theta_ = std::fmod(current_theta_, 2.0 * M_PI);

  return CalculatePositionFromAngles();
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
