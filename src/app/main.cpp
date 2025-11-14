// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/application.h"
#include "core/log.h"
#include "model_layer.h"

int main() {
  prototype::Log::Init();
  prototype::ApplicationSpecification app_spec;
  app_spec.name = "Prototype";
  app_spec.window_spec.width = 1920;
  app_spec.window_spec.height = 1080;

  prototype::Application application(app_spec);
  application.Init();
  // application.PushLayer(std::make_shared<prototype::AppLayer>());
  application.PushLayer(std::make_shared<prototype::ModelLayer>());
  application.Run();
  application.Clean();
}
