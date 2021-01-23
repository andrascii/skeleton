#include "PlainSocket.h"
#include "Logger.h"

namespace dataapi {

PlainSocket::PlainSocket(boost::asio::io_context& io_context)
  : socket_(io_context) {}

auto PlainSocket::Connect(const boost::asio::ip::tcp::endpoint& endpoint) noexcept -> boost::system::error_code {
  common::Logger()->debug("Connecting to {}...", endpoint.address().to_string());

  boost::system::error_code error;
  boost::asio::connect(socket_, std::vector{ endpoint }, error);

  if (error) {
    common::Logger()->error("{}", error.message());
  } else {
    common::Logger()->debug("Connected to {}...", endpoint.address().to_string());
  }

  return error;
}

auto PlainSocket::Close() noexcept -> boost::system::error_code {
  common::Logger()->debug("Connection closed");
  boost::system::error_code error;
  socket_.close(error);
  return error;
}

auto PlainSocket::Read(boost::asio::streambuf& buffer, size_t count) noexcept -> boost::system::error_code {
  common::Logger()->debug("Reading {} bytes...", count);

  boost::system::error_code error;
  boost::asio::read(socket_, buffer, boost::asio::transfer_exactly(count), error);

  if (error) {
    common::Logger()->error("{}", error.message());
  } else {
    common::Logger()->debug("Received {} bytes", count);
  }

  return error;
}

auto PlainSocket::Write(const std::string& data) noexcept -> boost::system::error_code {
  common::Logger()->debug("Writing...");

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(data, data.size()), error);

  if (error) {
    common::Logger()->debug("{}", error.message());
  } else {
    common::Logger()->debug("Message sent");
  }

  return error;
}

auto PlainSocket::Write(const boost::asio::streambuf& buffer) noexcept -> boost::system::error_code {
  common::Logger()->debug("Writing...");

  boost::system::error_code error;
  boost::asio::write(socket_, buffer.data(), error);

  if (error) {
    common::Logger()->debug("{}", error.message());
  } else {
    common::Logger()->debug("Message sent");
  }

  return error;
}

}
