#pragma once

namespace echo {

class ISocket {
 public:
  virtual ~ISocket() = default;

  [[nodiscard]] virtual auto Connect(const boost::asio::ip::tcp::endpoint& endpoint) noexcept -> boost::system::error_code = 0;
  [[nodiscard]] virtual auto Close() noexcept -> boost::system::error_code = 0;

  [[nodiscard]] virtual auto Read(boost::asio::streambuf& buffer, size_t count) noexcept -> boost::system::error_code = 0;
  [[nodiscard]] virtual auto Write(const std::string& data) noexcept -> boost::system::error_code = 0;
  [[nodiscard]] virtual auto Write(const boost::asio::streambuf& buffer) noexcept -> boost::system::error_code = 0;
};

}
