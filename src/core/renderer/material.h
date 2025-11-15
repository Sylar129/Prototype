// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/renderer/texture.h"
#include "glm/glm.hpp"

struct aiMaterial;

namespace prototype {
struct Material {
  float shininess;     // Ns
  glm::vec3 ambient;   // Ka
  glm::vec3 diffuse;   // Kd
  glm::vec3 specular;  // Ks
  glm::vec3 emissive;  // Ke
  float refraction;    // Ni
  float transparency;  // d

  void UpdateShader();

  static Material FromAssimp(const aiMaterial* material);
};

}  // namespace prototype
