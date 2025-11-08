// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>

#include "glad/gl.h"

namespace prototype::renderer {

class Image;

struct Texture {
  GLuint handle = 0;
  uint32_t width = 0;
  uint32_t height = 0;

  // texture Format
  uint32_t internal_format;  // format of texture object
  uint32_t image_format;     // format of loaded image
  // texture configuration
  uint32_t wrap_s;      // wrapping mode on S axis
  uint32_t wrap_t;      // wrapping mode on T axis
  uint32_t filter_min;  // filtering mode if texture pixels < screen pixels
  uint32_t filter_max;  // filtering mode if texture pixels > screen pixels

  // constructor (sets default texture modes)
  Texture();
  // generates texture from image data
  void GenerateFromImageData(uint32_t width, uint32_t height,
                             unsigned char* data);
  void GenerateFromImage(const Image& image);
  // binds the texture as the current active GL_TEXTURE_2D texture object
  void Bind() const;
};

Texture LoadTexture(const std::filesystem::path& path,
                    bool flip_vertically = false);

}  // namespace prototype::renderer
