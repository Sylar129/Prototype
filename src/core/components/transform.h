// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "glm/glm.hpp"

namespace prototype {

struct TransformComponent {
  glm::vec3 translation{0, 0, 0};
  glm::vec3 rotation{0, 0, 0};
  glm::vec3 scale{1, 1, 1};

  glm::mat4 getMatrix() const;

  void DrawMenu(const std::string& label = "Transform");
};

}  // namespace prototype
