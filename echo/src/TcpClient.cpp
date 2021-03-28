#include "TcpClient.h"
#include "Logger.h"
#include "PlainSocket.h"

namespace echo {

TcpClient::TcpClient()
  : socket_(std::make_unique<PlainSocket>(io_context_)) {}

auto TcpClient::Connect(const boost::asio::ip::tcp::endpoint& endpoint) noexcept -> boost::system::error_code {
  return socket_->Connect(endpoint);
}

auto TcpClient::Close() noexcept -> boost::system::error_code {
  return socket_->Close();
}

auto TcpClient::Read(boost::asio::streambuf& buffer, size_t count) noexcept -> boost::system::error_code {
  return socket_->Read(buffer, count);
}

auto TcpClient::Write(const std::string& data) noexcept -> boost::system::error_code {
  return socket_->Write(data);
}

auto TcpClient::Write(const boost::asio::streambuf& buffer) noexcept -> boost::system::error_code {
  return socket_->Write(buffer);
}

}
