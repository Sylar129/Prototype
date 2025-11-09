// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/texture.h"

#include "core/log.h"
#include "core/renderer/image.h"
#include "glad/gl.h"

namespace prototype {

namespace {
constexpr GLenum GetFormat(int channels) {
  switch (channels) {
    case 1:
      return GL_RED;
    case 2:
      return GL_RG;
    case 3:
      return GL_RGB;
    case 4:
      return GL_RGBA;
    default:
      return GL_RGBA;
  }
}

constexpr GLenum GetInternalFormat(int channels) {
  switch (channels) {
    case 1:
      return GL_R8;
    case 2:
      return GL_RG8;
    case 3:
      return GL_RGB8;
    case 4:
      return GL_RGBA8;
    default:
      return GL_RGBA8;
  }
}
}  // namespace

Texture::Texture()
    : width(0),
      height(0),
      internal_format(GL_RGB8),
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
  if constexpr (true) {
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
  } else {
    glCreateTextures(GL_TEXTURE_2D, 1, &handle);

    glTextureStorage2D(handle, 1, internal_format, width, height);
    glTextureSubImage2D(handle, 0, 0, 0, width, height, image_format,
                        GL_UNSIGNED_BYTE, data);

    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, filter_min);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, filter_max);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, wrap_s);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, wrap_t);

    glGenerateTextureMipmap(handle);
  }
}

void Texture::GenerateFromImage(const Image& image) {
  image_format = GetFormat(image.channels_);
  internal_format = GetInternalFormat(image.channels_);
  GenerateFromImageData(image.width_, image.height_, image.data_);
}

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, handle); }

}  // namespace prototype
