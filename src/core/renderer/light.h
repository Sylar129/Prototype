// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glm/glm.hpp"

namespace prototype {

class Shader;

struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  void DrawContextMenu();
};

class LightCube {
 public:
  LightCube();

  void Draw(Shader& shader);

 private:
  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ebo_;
};

}  // namespace prototype
