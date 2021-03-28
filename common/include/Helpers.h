#include "Logger.h"

namespace common {

template <typename T>
using Expected = tl::expected<T, std::error_code>;
using Unexpected = tl::unexpected<std::error_code>;

class Helpers {
 public:
  static auto SetCurrentThreadName(const std::string& name) noexcept -> void;
};

}
