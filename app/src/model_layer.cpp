// Copyright (c) 2025 Sylar129. All rights reserved

#include "model_layer.h"

#include "GLFW/glfw3.h"
#include "core/application.h"
#include "core/renderer/model.h"
#include "core/renderer/shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace prototype {

ModelLayer::ModelLayer() : model_("backpack/backpack.obj") {}

ModelLayer::~ModelLayer() {}

void ModelLayer::OnAttach() {
  // Create shaders
  shader_.Compile("shaders/model.vert", "shaders/model.frag");
}

void ModelLayer::OnDetach() { shader_.Delete(); }

void ModelLayer::OnUpdate(float ts) {}

void ModelLayer::OnRender() {
  shader_.Use();

  shader_.SetMat4("projection", core::Application::Get().GetWindow().GetPorjection());
  shader_.SetMat4("view", core::Application::Get().GetWindow().GetView());

  // render the loaded model
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(
      model,
      glm::vec3(0.0f, 0.0f,
                0.0f));  // translate it down so it's at the center of the scene
  model = glm::scale(
      model,
      glm::vec3(1.0f, 1.0f,
                1.0f));  // it's a bit too big for our scene, so scale it down
  shader_.SetMat4("model", model);
  model_.Draw(shader_);
}
}  // namespace prototype
