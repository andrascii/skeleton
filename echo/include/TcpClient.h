#include "Logger.h"
#include "ISocket.h"

namespace echo {

class TcpClient {
 public:
  TcpClient();

  auto Connect(const boost::asio::ip::tcp::endpoint& endpoint) noexcept -> boost::system::error_code;
  auto Close() noexcept -> boost::system::error_code;

  auto Read(boost::asio::streambuf& buffer, size_t count) noexcept -> boost::system::error_code;
  auto Write(const std::string& data) noexcept -> boost::system::error_code;
  auto Write(const boost::asio::streambuf& buffer) noexcept -> boost::system::error_code;

private:
  boost::asio::io_context io_context_;
  std::unique_ptr<ISocket> socket_;
};

}
