#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <format>
#include <memory>
#include <string>

namespace util {

enum class LoggerColor {
  Cyan,
  BrightCyan,
  Blue,
  BrightBlue,
  Magenta,
  BrightMagenta,
  Gray
};

constexpr const char *to_ansi(LoggerColor color) {
  switch (color) {
    case LoggerColor::Cyan:
      return "\033[36m";
    case LoggerColor::BrightCyan:
      return "\033[96m";
    case LoggerColor::Blue:
      return "\033[34m";
    case LoggerColor::BrightBlue:
      return "\033[94m";
    case LoggerColor::Magenta:
      return "\033[35m";
    case LoggerColor::BrightMagenta:
      return "\033[95m";
    case LoggerColor::Gray:
      return "\033[90m";
  }
  return "\033[0m";
}

inline std::shared_ptr<spdlog::logger> get_logger(const std::string &name,
                                                  LoggerColor color) {
  if (auto existing = spdlog::get(name)) {
    return existing;
  }

  auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto pattern = std::format("[%Y-%m-%d %H:%M:%S] [{}%n\033[0m] [%^%l%$] %v",
                             to_ansi(color));

  sink->set_pattern(pattern);

  auto logger = std::make_shared<spdlog::logger>(name, sink);
  spdlog::register_logger(logger);
  return logger;
}

}  // namespace util