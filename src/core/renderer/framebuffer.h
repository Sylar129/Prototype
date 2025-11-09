// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glad/gl.h"

namespace prototype {

struct Framebuffer {
  GLuint handle = 0;
  GLuint color_attachment = 0;
  GLuint render_buffer = 0;

  void Bind();
  void Unbind();
};

Framebuffer CreateFrameBuffer();

}  // namespace prototype
