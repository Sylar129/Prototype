// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/application.h"

#include <assert.h>

// clang-format off
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// clang-format on
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
  if (specification_.window_spec.title.empty()) {
    specification_.window_spec.title = specification_.name;
  }

  window_ = std::make_shared<Window>(specification_.window_spec);
  window_->Init();

  window_->SetEventCallback([this](Event& event) { OnEvent(event); });

  imgui_layer_ = std::make_unique<ImguiLayer>();
  imgui_layer_->Init(window_->GetHandle());

  renderer::utils::InitOpenGLDebugMessageCallback();
}

void Application::Run() {
  running_ = true;

  float last_time = GetTime();

  // Main Application loop
  while (running_) {
    if (window_->ShouldClose()) {
      Stop();
      break;
    }

    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // event
    glfwPollEvents();

    // update
    float current_time = GetTime();
    float timestep = glm::clamp(current_time - last_time, 0.001f, 0.1f);
    last_time = current_time;

    for (const auto& layer : layer_stack_) {
      layer->OnUpdate(timestep);
    }

    // render
    imgui_layer_->OnRenderBegin();
    // imgui_layer_->OnRender();

    // NOTE: rendering can be done elsewhere (eg. render thread)
    for (const auto& layer : layer_stack_) {
      layer->OnRender();
    }

    imgui_layer_->OnRenderEnd();

    window_->Update();
  }
}

void Application::Stop() { running_ = false; }

void Application::Clean() {
  for (const auto& layer : layer_stack_) {
    layer->OnDetach();
  }
  layer_stack_.clear();
  imgui_layer_->Clean();
  window_->Clean();

  glfwTerminate();

  kApplication = nullptr;
}

void Application::OnEvent(Event& event) {
  for (const auto& layer : layer_stack_) {
    layer->OnEvent(event);
  }
}

void Application::PushLayer(std::shared_ptr<Layer> layer) {
  layer_stack_.push_back(layer);
  layer->OnAttach();
}

Application& Application::Get() {
  assert(kApplication);
  return *kApplication;
}

float Application::GetTime() { return (float)glfwGetTime(); }

}  // namespace prototype::core
