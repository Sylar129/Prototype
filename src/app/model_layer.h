// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

#include "core/components/locomotion.h"
#include "core/components/transform.h"
#include "core/events/key_event.h"
#include "core/events/mouse_event.h"
#include "core/layer.h"
#include "core/renderer/camera.h"
#include "core/renderer/framebuffer.h"
#include "core/renderer/light.h"
#include "core/renderer/shader.h"
#include "core/renderer/shape.h"

namespace prototype {

class ModelLayer : public Layer {
 public:
  ModelLayer();
  virtual ~ModelLayer();

  virtual void OnAttach(const Window& window) override;
  virtual void OnDetach() override;
  virtual void OnEvent(Event& event) override;
  virtual void OnUpdate(float ts) override;
  virtual void OnRender() override;

 private:
  bool OnKeyPressedEvent(KeyPressdEvent& event);
  bool OnKeyReleasedEvent(KeyReleasedEvent& event);
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);
  bool OnMouseMovedEvent(MouseMovedEvent& event);

  TransformComponent model_transform_;
  TransformComponent model_transform2_;
  Camera camera_;
  PointLight light_;
  Camera::Movement camera_move_;
  bool camera_can_move_ = false;
  std::unique_ptr<Framebuffer> framebuffer_;
};

}  // namespace prototype
