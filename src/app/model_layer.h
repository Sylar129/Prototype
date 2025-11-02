// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/components/transform.h"
#include "core/events/application_event.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer.h"
#include "core/renderer/camera.h"
#include "core/renderer/framebuffer.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "imgui.h"

namespace prototype {

class ModelLayer : public core::Layer {
 public:
  ModelLayer();
  virtual ~ModelLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& event) override;
  virtual void OnUpdate(float ts) override;
  virtual void OnRender() override;

 private:
  bool OnWindowResizeEvent(WindowResizeEvent& event);
  bool OnKeyPressedEvent(KeyPressdEvent& event);
  bool OnKeyReleasedEvent(KeyReleasedEvent& event);
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);
  bool OnMouseMovedEvent(MouseMovedEvent& event);

  renderer::Shader shader_;
  renderer::Model model_;
  TransformComponent model_transform_;
  renderer::Camera camera_;
  renderer::Camera::Movement camera_move_;
  bool camera_can_move_ = false;
  renderer::Framebuffer framebuffer_;
  ImVec2 viewport_size_;

  int window_width_ = 0;
  int window_height_ = 0;
};

}  // namespace prototype
