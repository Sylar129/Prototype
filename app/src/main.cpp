// Copyright (c) 2025 Sylar129. All rights reserved

#include "app_layer.h"
#include "core/application.h"
#include "core/log.h"

int main() {
  prototype::core::Log::Init();
  prototype::core::ApplicationSpecification app_spec;
  app_spec.name = "Architecture";
  app_spec.window_spec.width = 1920;
  app_spec.window_spec.height = 1080;

  prototype::core::Application application(app_spec);
  application.Init();
  application.PushLayer(std::make_shared<prototype::AppLayer>());
  application.Run();
  application.Clear();
}
