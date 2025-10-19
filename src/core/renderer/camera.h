// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <algorithm>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

  Camera(const glm::vec3& pos, const glm::vec3& up) : pos_(pos), world_up_(up) {
    UpdateCameraVectors();
  }

  glm::vec3 GetPosition() const { return pos_; }

  glm::mat4 GetViewMatrix() const {
    return glm::lookAt(pos_, pos_ + front_, up_);
  }

  float GetZoom() const { return zoom_; }

  // processes input received from any keyboard-like input system. Accepts input
  // parameter in the form of camera defined ENUM (to abstract it from windowing
  // systems)
  void ProcessKeyboard(Movement direction, float delta_time) {
    float velocity = speed_ * delta_time;
    if (direction == Movement::kForward) pos_ += front_ * velocity;
    if (direction == Movement::kBackward) pos_ -= front_ * velocity;
    if (direction == Movement::kLeft) pos_ -= right_ * velocity;
    if (direction == Movement::kRight) pos_ += right_ * velocity;
  }

  // processes input received from a mouse input system. Expects the offset
  // value in both the x and y direction.
  void ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouse_sensitivity_;
    yoffset *= mouse_sensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    pitch_ = std::clamp(pitch_, -89.0f, 89.0f);

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
  }

  // processes input received from a mouse scroll-wheel event. Only requires
  // input on the vertical wheel-axis
  void ProcessMouseScroll(float yoffset) {
    zoom_ -= yoffset;
    zoom_ = std::clamp(zoom_, 1.0f, 45.0f);
  }

 private:
  // calculates the front vector from the Camera's (updated) Euler Angles
  void UpdateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right_ = glm::normalize(glm::cross(
        front_, world_up_));  // normalize the vectors, because their length
                              // gets closer to 0 the more you look up or down
                              // which results in slower movement.
    up_ = glm::normalize(glm::cross(right_, front_));
  }

  glm::vec3 pos_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 world_up_;

  float yaw_ = -90.0f;
  float pitch_ = 0.0f;

  float speed_ = 0.5f;
  float mouse_sensitivity_ = 0.1f;
  float zoom_ = 45.0f;
};

}  // namespace prototype::renderer