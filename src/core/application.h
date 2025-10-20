// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/layer.h"
#include "core/window.h"

namespace prototype::core {

class ImguiLayer;

struct ApplicationSpecification {
  std::string name = "Application";
  WindowSpecification window_spec;
};

class Application {
 public:
  Application(const ApplicationSpecification& specification);
  ~Application();

  void Init();
  void Run();
  void Stop();
  void Clean();

  void OnEvent(Event& event);

  void PushLayer(std::shared_ptr<Layer> layer);

  static Application& Get();
  static float GetTime();

 private:
  ApplicationSpecification specification_;
  std::shared_ptr<Window> window_;
  bool running_ = false;

  std::unique_ptr<ImguiLayer> imgui_layer_;
  std::vector<std::shared_ptr<Layer>> layer_stack_;
};

}  // namespace prototype::core
