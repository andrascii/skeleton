#pragma once

namespace dataapi {

class IBootstrapper {
 public:
  virtual ~IBootstrapper() = default;

  [[nodiscard]] virtual auto Bootstrap() noexcept -> std::error_code = 0;
};

}
