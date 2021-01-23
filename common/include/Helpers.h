#include "Logger.h"

namespace common {

class Helpers {
 public:
  static auto SetCurrentThreadName(const std::string& name) noexcept -> void;
};

}
