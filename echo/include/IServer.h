#pragma once

namespace echo {

class IServer {
 public:
  virtual ~IServer() = default;

  virtual auto Start() noexcept -> void = 0;
  virtual auto Stop() noexcept -> void = 0;
};

}
