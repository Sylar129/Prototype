// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <stdint.h>

#include "core/layer.h"
#include "core/renderer/shader.h"

namespace prototype {

class AppLayer : public core::Layer {
 public:
  AppLayer();
  virtual ~AppLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(float ts) override;
  virtual void OnRender() override;

 private:
  renderer::Shader shader_;
  uint32_t vertex_array_ = 0;
  uint32_t vertex_buffer_ = 0;
};

}  // namespace prototype
