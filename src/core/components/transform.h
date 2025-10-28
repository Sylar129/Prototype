// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace prototype {

struct TransformComponent {
  glm::vec3 translation{0, 0, 0};
  glm::vec3 rotation{0, 0, 0};
  glm::vec3 scale{1, 1, 1};

  glm::mat4 getMatrix() const {
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, translation);
    m *= glm::toMat4(glm::quat(rotation));
    m = glm::scale(m, scale);
    return m;
  }
};

}  // namespace prototype
