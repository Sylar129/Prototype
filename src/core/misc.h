// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

namespace prototype {

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace prototype
