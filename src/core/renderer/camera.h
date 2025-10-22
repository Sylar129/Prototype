// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glm/glm.hpp"

namespace prototype::renderer {

class Camera {
 public:
  enum class Movement {
    kStill,
    kForward,
    kBackward,
    kLeft,
    kRight,
  };

  explicit Camera(const glm::vec3& pos);

  glm::vec3 GetPosition() const;

  glm::mat4 GetViewMatrix() const;

  float GetZoom() const;

  void DrawController();

  // processes input received from any keyboard-like input system. Accepts input
  // parameter in the form of camera defined ENUM (to abstract it from windowing
  // systems)
  void ProcessKeyboard(Movement direction, float delta_time);

  // processes input received from a mouse input system. Expects the offset
  // value in both the x and y direction.
  void ProcessMouseMovement(float xoffset, float yoffset);

  // processes input received from a mouse scroll-wheel event. Only requires
  // input on the vertical wheel-axis
  void ProcessMouseScroll(float yoffset);

 private:
  // calculates the front vector from the Camera's (updated) Euler Angles
  void UpdateCameraVectors();

  glm::vec3 pos_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;

  float yaw_ = -90.0f;
  float pitch_ = 0.0f;

  float speed_ = 0.5f;
  float mouse_sensitivity_ = 0.1f;
  float zoom_ = 45.0f;
};

}  // namespace prototype::renderer