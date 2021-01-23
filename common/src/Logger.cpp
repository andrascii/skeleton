#include "Logger.h"

namespace common {

[[nodiscard]] auto Logger() noexcept -> std::shared_ptr<spdlog::logger> {
  using namespace spdlog;
  static std::once_flag flag;

  const auto name = "logger";

  std::call_once(flag, [name]{
    try {
      const auto console_sink = std::make_shared<sinks::stdout_color_sink_mt>();
      const auto instance = std::make_shared<spdlog::logger>(logger(name, { console_sink }));
      register_logger(instance);
    } catch (const std::exception& error) {
      std::cerr << "Logger initialization failed: " << error.what() << std::endl;
      std::abort();
    }
  });

  return get(name);
}

}
