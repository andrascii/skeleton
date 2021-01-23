#pragma once

#include "ISocket.h"

namespace dataapi {

class PlainSocket : public ISocket {
 public:
  explicit PlainSocket(boost::asio::io_context& io_context);

  auto Connect(const boost::asio::ip::tcp::endpoint& endpoint) noexcept -> boost::system::error_code override;
  auto Close() noexcept -> boost::system::error_code override;

  auto Read(boost::asio::streambuf& buffer, size_t count) noexcept -> boost::system::error_code override;
  auto Write(const std::string& data) noexcept -> boost::system::error_code override;
  auto Write(const boost::asio::streambuf& buffer) noexcept -> boost::system::error_code override;

 private:
  boost::asio::ip::tcp::socket socket_;
};

}
