// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glm/glm.hpp"

namespace prototype {

struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  void DrawContextMenu();
};

}  // namespace prototype
