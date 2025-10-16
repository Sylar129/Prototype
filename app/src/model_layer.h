// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <stdint.h>

#include "core/layer.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"

namespace prototype {

class ModelLayer : public core::Layer {
 public:
  ModelLayer();
  virtual ~ModelLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(float ts) override;
  virtual void OnRender() override;

 private:
  renderer::Shader shader_;
  renderer::Model model_;
};

}  // namespace prototype
