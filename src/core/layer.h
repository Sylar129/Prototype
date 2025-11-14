// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/events/event.h"

namespace prototype {

class Window;

class Layer {
 public:
  virtual ~Layer() = default;

  virtual void OnAttach(const Window& window) = 0;
  virtual void OnDetach() = 0;
  virtual void OnEvent(Event& event) = 0;
  virtual void OnUpdate(float ts) = 0;
  virtual void OnRender() = 0;
};

}  // namespace prototype
