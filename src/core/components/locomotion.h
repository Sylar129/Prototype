// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "glm/glm.hpp"

namespace prototype {

class SpiralMotion {
 public:
  SpiralMotion(float radius, const glm::vec3& center, float omega_theta,
               float omega_phi, float theta_initial, float phi_initial)
      : radius_(radius),
        center_(center),
        omega_theta_(omega_theta),
        omega_phi_(omega_phi),
        current_theta_(theta_initial),
        current_phi_(phi_initial) {}

  glm::vec3 UpdatePosition(float dt);

  void DrawMenu(const std::string& label = "SpiralMotion");

 private:
  glm::vec3 CalculatePositionFromAngles() const;

  glm::vec3 center_;
  float radius_;
  float omega_theta_;
  float omega_phi_;

  float current_theta_;
  float current_phi_;
};

}  // namespace prototype
