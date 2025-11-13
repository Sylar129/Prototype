// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "core/components/locomotion.h"
#include "core/components/transform.h"
#include "core/events/application_event.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer.h"
#include "core/renderer/camera.h"
#include "core/renderer/framebuffer.h"
#include "core/renderer/light.h"
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

  Shader model_shader_;
  Shader light_shader_;
  Model model_;
  TransformComponent model_transform_;
  Camera camera_;
  PointLight light_;
  SpiralMotion orbit_light_;
  LightCube light_cube_;
  Camera::Movement camera_move_;
  bool camera_can_move_ = false;
  Framebuffer framebuffer_;
  ImVec2 viewport_size_;

  int window_width_ = 0;
  int window_height_ = 0;
};

}  // namespace prototype
