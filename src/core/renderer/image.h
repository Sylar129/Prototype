// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <filesystem>

namespace prototype {

class Image {
 public:
  Image(const std::filesystem::path& path, bool flip_vertically = false);
  ~Image();

  int GetWidth() const;
  int GetHeight() const;
  int GetChannels() const;
  unsigned char* GetRawData() const;

  bool IsValid() const;

 private:
  friend struct Texture;
  std::filesystem::path path_;
  int width_;
  int height_;
  int channels_;
  unsigned char* data_;
};
}  // namespace prototype
