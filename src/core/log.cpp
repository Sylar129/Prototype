// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace prototype::core {

std::shared_ptr<spdlog::logger> Log::kCoreLogger;
std::shared_ptr<spdlog::logger> Log::kAppLogger;

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  kCoreLogger = spdlog::stdout_color_mt("Core");
  kCoreLogger->set_level(spdlog::level::trace);

  kAppLogger = spdlog::stdout_color_mt("App");
  kAppLogger->set_level(spdlog::level::trace);
}

}  // namespace prototype::core
