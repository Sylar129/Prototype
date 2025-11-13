// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <cstdint>

namespace prototype {

class Shader;

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
