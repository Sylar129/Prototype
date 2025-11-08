// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/texture.h"

#include "core/log.h"
#include "core/renderer/image.h"
#include "glad/gl.h"

namespace prototype::renderer {

Texture::Texture()
    : width(0),
      height(0),
      internal_format(GL_RGB),
      image_format(GL_RGB),
      wrap_s(GL_REPEAT),
      wrap_t(GL_REPEAT),
      filter_min(GL_LINEAR),
      filter_max(GL_LINEAR) {
  glGenTextures(1, &handle);
}

void Texture::GenerateFromImageData(uint32_t w, uint32_t h,
                                    unsigned char* data) {
  width = w;
  height = h;
  // create Texture
  glBindTexture(GL_TEXTURE_2D, handle);
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, image_format,
               GL_UNSIGNED_BYTE, data);
  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateFromImage(const Image& image) {
  GenerateFromImageData(image.width_, image.height_, image.data_);
}

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, handle); }

Texture LoadTexture(const std::filesystem::path& path, bool flip_vertically) {
  Image image(path, flip_vertically);

  if (!image.IsValid()) {
    return {};
  }

  int channels = image.GetChannels();
  GLenum format = channels == 4   ? GL_RGBA
                  : channels == 3 ? GL_RGB
                  : channels == 1 ? GL_RED
                                  : 0;
  int width = image.GetWidth();
  int height = image.GetHeight();

  Texture result;
  result.width = width;
  result.height = height;

  glCreateTextures(GL_TEXTURE_2D, 1, &result.handle);

  glTextureStorage2D(result.handle, 1, (format == GL_RGBA ? GL_RGBA8 : GL_RGB8),
                     width, height);

  glTextureSubImage2D(result.handle, 0, 0, 0, width, height, format,
                      GL_UNSIGNED_BYTE, image.GetRawData());

  glTextureParameteri(result.handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(result.handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(result.handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateTextureMipmap(result.handle);

  return result;
}

}  // namespace prototype::renderer
