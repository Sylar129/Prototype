// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

#include "spdlog/logger.h"

namespace prototype {

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

}  // namespace prototype

#define CORE_LOG_TRACE(...) ::prototype::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...) ::prototype::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...) ::prototype::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) ::prototype::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) ::prototype::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define APP_LOG_TRACE(...) ::prototype::Log::GetAppLogger()->trace(__VA_ARGS__)
#define APP_LOG_INFO(...) ::prototype::Log::GetAppLogger()->info(__VA_ARGS__)
#define APP_LOG_WARN(...) ::prototype::Log::GetAppLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::prototype::Log::GetAppLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::prototype::Log::GetAppLogger()->critical(__VA_ARGS__)
