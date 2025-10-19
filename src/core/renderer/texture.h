// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>

#include "glad/gl.h"

namespace prototype::renderer {

struct Texture {
  GLuint handle = 0;
  uint32_t width = 0;
  uint32_t height = 0;
  std::string type;
  std::string path;
};

struct Framebuffer {
  GLuint handle = 0;
  Texture color_attachment;
};

Texture CreateTexture(int width, int height);
Texture LoadTexture(const std::filesystem::path& path);
Framebuffer CreateFramebufferWithTexture(const Texture& texture);
bool AttachTextureToFramebuffer(Framebuffer& framebuffer,
                                const Texture& texture);
void BlitFramebufferToSwapchain(const Framebuffer& framebuffer);
}  // namespace prototype::renderer
