// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

#include "spdlog/logger.h"

namespace prototype::core {

class Log {
 public:
  static void Init();

  static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
    return kCoreLogger;
  }

  static std::shared_ptr<spdlog::logger>& GetAppLogger() { return kAppLogger; }

 private:
  static std::shared_ptr<spdlog::logger> kCoreLogger;
  static std::shared_ptr<spdlog::logger> kAppLogger;
};

}  // namespace breakout

#define CORE_LOG_TRACE(...) ::prototype::core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...) ::prototype::core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...) ::prototype::core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) ::prototype::core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) ::prototype::core::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define APP_LOG_TRACE(...) ::prototype::core::Log::GetAppLogger()->trace(__VA_ARGS__)
#define APP_LOG_INFO(...) ::prototype::core::Log::GetAppLogger()->info(__VA_ARGS__)
#define APP_LOG_WARN(...) ::prototype::core::Log::GetAppLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::prototype::core::Log::GetAppLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::prototype::core::Log::GetAppLogger()->critical(__VA_ARGS__)
