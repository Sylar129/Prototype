// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/image.h"

#include "core/log.h"
#include "stb/stb_image.h"

namespace prototype {

Image::Image(const std::filesystem::path& path, bool flip_vertically)
    : path_(path) {
  stbi_set_flip_vertically_on_load(flip_vertically);

  data_ = stbi_load(path_.string().c_str(), &width_, &height_, &channels_, 0);

  if (!data_) {
    CORE_LOG_ERROR("Failed to load image: {}", path_.string());
  }
}

int Image::GetWidth() const { return width_; }

int Image::GetHeight() const { return height_; }

int Image::GetChannels() const { return channels_; }

unsigned char* Image::GetRawData() const { return data_; }

bool Image::IsValid() const { return data_ != nullptr; }

Image::~Image() { stbi_image_free(data_); }

}  // namespace prototype
