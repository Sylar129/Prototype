// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/components/locomotion.h"
#include "core/renderer/camera.h"
#include "core/renderer/shape.h"
#include "glm/glm.hpp"

namespace prototype {

struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  PointLight(const glm::vec3& position, const glm::vec3& ambient,
             const glm::vec3& diffuse, const glm::vec3& specular);

  void SetupMotion(const SpiralMotion& motion);

  void Update(float dt);
  void Render(const Camera& camera);
  void RenderMenu();

 private:
  void DrawContextMenu();
  bool movable_;
  SpiralMotion motion_;
  Cube light_cube_;
};

}  // namespace prototype
