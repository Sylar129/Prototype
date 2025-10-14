// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/event.h"

namespace prototype::core {

class Layer {
 public:
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnEvent(Event& event) {}
  virtual void OnUpdate(float ts) {}
  virtual void OnRender() {}
};

}  // namespace prototype::core
