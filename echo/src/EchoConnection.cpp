#include "EchoConnection.h"
#include "Logger.h"

namespace echo {

EchoConnection::EchoConnection(boost::asio::io_context& context)
  : socket_(context) {}

auto EchoConnection::Start() noexcept -> void {
  DoRead();
}

auto EchoConnection::Socket() noexcept -> boost::asio::ip::tcp::socket& {
  return socket_;
}

auto EchoConnection::Shutdown() noexcept -> void {
  boost::system::error_code error;
  socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, error);

  if (error) {
    common::Logger()->error("Shutdown error: {}", error.message());
  }
}

auto EchoConnection::HandleWrite() noexcept -> void {
  DoRead();
}

auto EchoConnection::HandleRead(const boost::system::error_code& error,
                                size_t bytes_transferred) noexcept -> void {
  if (error && error == boost::asio::error::eof) {
    common::Logger()->info("Connection closed by the client");
    boost::system::error_code error;
    socket_.close(error);
    return;
  }

  if (error) {
    common::Logger()->error("Read error: {}", error.message());
    Shutdown();
  }

  DoWrite(bytes_transferred);
}

auto EchoConnection::DoRead() noexcept -> void {
  const auto callback = boost::bind(&EchoConnection::HandleRead, shared_from_this(), _1, _2);
  socket_.async_read_some(boost::asio::buffer(data_, kMaxLength), callback);
}

auto EchoConnection::DoWrite(size_t count) noexcept -> void {
  const auto callback = boost::bind(&EchoConnection::HandleWrite, shared_from_this());
  boost::asio::async_write(socket_, boost::asio::buffer(data_, count), callback);
}

}
