#pragma once

#include "IConnection.h"

namespace echo {

class EchoConnection final : public std::enable_shared_from_this<EchoConnection>, public IConnection {
 public:
  explicit EchoConnection(boost::asio::io_context& context);

  auto Start() noexcept -> void override;
  auto Socket() noexcept -> boost::asio::ip::tcp::socket& override;
  auto Shutdown() noexcept -> void override;

 private:
  auto HandleWrite() noexcept -> void;
  auto HandleRead(const boost::system::error_code& error, size_t bytes_transferred) noexcept -> void;

  auto DoRead() noexcept -> void;
  auto DoWrite(size_t count) noexcept -> void;

 private:
  boost::asio::ip::tcp::socket socket_;

  enum {
    kMaxLength = 1024
  };

  char data_[kMaxLength];
};

}
