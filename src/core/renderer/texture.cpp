// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/texture.h"

#include "core/log.h"
#include "glad/gl.h"
#include "stb/stb_image.h"

namespace prototype::renderer {

Texture CreateTexture(int width, int height) {
  Texture result;
  result.width = width;
  result.height = height;

  glCreateTextures(GL_TEXTURE_2D, 1, &result.handle);

  glTextureStorage2D(result.handle, 1, GL_RGBA32F, width, height);

  glTextureParameteri(result.handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(result.handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  return result;
}

Texture LoadTexture(const std::filesystem::path& path) {
  int width, height, channels;
  std::string filepath = path.string();
  unsigned char* data =
      stbi_load(filepath.c_str(), &width, &height, &channels, 0);

  if (!data) {
    CORE_LOG_ERROR("Failed to load texture: {}", filepath);
    return {};
  }

  GLenum format = channels == 4   ? GL_RGBA
                  : channels == 3 ? GL_RGB
                  : channels == 1 ? GL_RED
                                  : 0;

  Texture result;
  result.width = width;
  result.height = height;

  glCreateTextures(GL_TEXTURE_2D, 1, &result.handle);

  glTextureStorage2D(result.handle, 1, (format == GL_RGBA ? GL_RGBA8 : GL_RGB8),
                     width, height);

  glTextureSubImage2D(result.handle, 0, 0, 0, width, height, format,
                      GL_UNSIGNED_BYTE, data);

  glTextureParameteri(result.handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(result.handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateTextureMipmap(result.handle);
  stbi_image_free(data);

  return result;
}

Framebuffer CreateFramebufferWithTexture(const Texture& texture) {
  Framebuffer result;

  glCreateFramebuffers(1, &result.handle);

  if (!AttachTextureToFramebuffer(result, texture)) {
    glDeleteFramebuffers(1, &result.handle);
    return {};
  }

  return result;
}

bool AttachTextureToFramebuffer(Framebuffer& framebuffer,
                                const Texture& texture) {
  glNamedFramebufferTexture(framebuffer.handle, GL_COLOR_ATTACHMENT0,
                            texture.handle, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    CORE_LOG_ERROR("Framebuffer is not complete!");
    return false;
  }

  framebuffer.color_attachment = texture;
  return true;
}

void BlitFramebufferToSwapchain(const Framebuffer& framebuffer) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer.handle);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);  // swapchain

  glBlitFramebuffer(0, 0, framebuffer.color_attachment.width,
                    framebuffer.color_attachment.height,  // Source rect
                    0, 0, framebuffer.color_attachment.width,
                    framebuffer.color_attachment.height,  // Destination rect
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

}  // namespace prototype::renderer
