// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <stdint.h>

#include "core/events/application_event.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer.h"
#include "core/renderer/camera.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"

namespace prototype {

class ModelLayer : public core::Layer {
 public:
  ModelLayer();
  virtual ~ModelLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& event);
  virtual void OnUpdate(float ts) override;
  virtual void OnRender() override;

 private:
  bool OnWindowResizeEvent(WindowResizeEvent& event);
  bool OnKeyPressedEvent(KeyPressdEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);

  renderer::Shader shader_;
  renderer::Model model_;
  renderer::Camera camera_;
  renderer::Camera::Movement camera_move_;

  int window_width_ = 0;
  int window_height_ = 0;
};

}  // namespace prototype
