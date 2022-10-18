#pragma once

#include "Core.h"

// ---FMT package include for spdlog & Clang compilation-----------
#define FMT_HEADER_ONLY
#include "spdlog/fmt/ostr.h"
// ----------------------------------------------------------------

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Based {
class BASED_API Log {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
} // namespace Based

// Core log macros
#define BSD_CORE_ERROR(...) ::Based::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BSD_CORE_WARN(...) ::Based::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BSD_CORE_INFO(...) ::Based::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BSD_CORE_TRACE(...) ::Based::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BSD_CORE_FATAL(...) ::Based::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BSD_ERROR(...) ::Based::Log::GetClientLogger()->error(__VA_ARGS__)
#define BSD_WARN(...) ::Based::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BSD_INFO(...) ::Based::Log::GetClientLogger()->info(__VA_ARGS__)
#define BSD_TRACE(...) ::Based::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BSD_FATAL(...) ::Based::Log::GetClientLogger()->fatal(__VA_ARGS__)
