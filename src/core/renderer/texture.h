// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>

#include "glad/gl.h"

namespace prototype::renderer {

struct Texture {
  GLuint handle = 0;
  uint32_t width = 0;
  uint32_t height = 0;
};

Texture CreateTexture(int width, int height);
Texture LoadTexture(const std::filesystem::path& path, bool flip_vertically = false);

}  // namespace prototype::renderer
