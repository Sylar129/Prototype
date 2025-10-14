// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/application.h"

#include <assert.h>

#include "GLFW/glfw3.h"
#include "core/imgui_layer.h"
#include "core/log.h"
#include "core/renderer/utils.h"

namespace prototype::core {

static Application* kApplication = nullptr;

static void GLFWErrorCallback(int error, const char* description) {
  CORE_LOG_ERROR("[GLFW Error]: {}", description);
}

Application::Application(const ApplicationSpecification& specification)
    : specification_(specification) {
  kApplication = this;
}

Application::~Application() {}

void Application::Init() {
  glfwSetErrorCallback(GLFWErrorCallback);
  glfwInit();

  // Set window title to app name if empty
  if (specification_.window_spec.title.empty())
    specification_.window_spec.title = specification_.name;

  window_ = std::make_shared<Window>(specification_.window_spec);
  window_->Create();

  imgui_layer_ = std::make_unique<ImguiLayer>();
  imgui_layer_->Init(window_->GetHandle());

  renderer::utils::InitOpenGLDebugMessageCallback();
}

void Application::Run() {
  running_ = true;

  float last_time = GetTime();

  // Main Application loop
  while (running_) {
    glfwPollEvents();

    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    imgui_layer_->OnRenderBegin();
    imgui_layer_->OnRender();

    float current_time = GetTime();
    float timestep = glm::clamp(current_time - last_time, 0.001f, 0.1f);
    last_time = current_time;

    // Main layer update here
    for (const auto& layer : layer_stack_) {
      layer->OnUpdate(timestep);
    }

    // NOTE: rendering can be done elsewhere (eg. render thread)
    for (const auto& layer : layer_stack_) {
      layer->OnRender();
    }

    imgui_layer_->OnRenderEnd();

    window_->Update();
  }
}

void Application::Stop() { running_ = false; }

void Application::Clear() {
  for (const auto& layer : layer_stack_) {
    layer->OnDetach();
  }
  layer_stack_.clear();
  imgui_layer_->Clear();
  window_->Destroy();

  glfwTerminate();

  kApplication = nullptr;
}

void Application::PushLayer(std::shared_ptr<Layer> layer) {
  layer_stack_.push_back(layer);
  layer->OnAttach();
}

glm::vec2 Application::GetFramebufferSize() const {
  return window_->GetFramebufferSize();
}

Application& Application::Get() {
  assert(kApplication);
  return *kApplication;
}

float Application::GetTime() { return (float)glfwGetTime(); }

}  // namespace prototype::core
