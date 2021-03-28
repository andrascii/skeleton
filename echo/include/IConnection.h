#pragma once

namespace echo {

class IConnection {
 public:
  virtual ~IConnection() = default;

  virtual auto Start() noexcept -> void = 0;
  virtual auto Socket() noexcept -> boost::asio::ip::tcp::socket& = 0;
  virtual auto Shutdown() noexcept -> void = 0;
};

}
