#include "Application.h"
#include "TcpClient.h"
#include "EchoTcpServer.h"
#include "Errors.h"

namespace echo {

Application::Application(Type type, unsigned short port)
  : type_(type),
    port_(port) {}

auto Application::Start() const noexcept -> std::error_code {
  switch (type_) {
    case kTypeClient: {
      return StartEchoClient();
    }
    case kTypeServer: {
      return StartEchoServer();
    }
  }

  return common::MakeErrorCode(common::ApplicationError::kInvalidApplicationTypeError);
}

auto Application::StartEchoClient() const noexcept -> std::error_code {
  TcpClient client;

  boost::system::error_code error;
  const auto ip = boost::asio::ip::address::from_string("127.0.0.1", error);

  error = client.Connect(boost::asio::ip::tcp::endpoint(ip, port_));

  if (error) {
    return common::MakeErrorCode(common::ApplicationError::kUnableToConnectToServer);
  }

  const auto read_line = [](std::string& line) {
    std::cout << "Input message to send: ";
    std::getline(std::cin, line);
    return true;
  };

  const auto is_server_closed_connection = [](const auto& error) {
    return error && error == boost::asio::error::eof;
  };

  for (std::string line; read_line(line);) {
    auto error = client.Write(line);

    if (is_server_closed_connection(error)) {
      common::Logger()->info("Server closed the connection");
      return std::error_code{};
    }

    boost::asio::streambuf read_buffer;
    error = client.Read(read_buffer, line.size());

    if (is_server_closed_connection(error)) {
      common::Logger()->info("Server closed the connection");
      return std::error_code{};
    }

    common::Logger()->info("Echo response: {}", boost::asio::buffer_cast<const char*>(read_buffer.data()));
  }

  return std::error_code{};
}

auto Application::StartEchoServer() const noexcept -> std::error_code {
  std::unique_ptr<IServer> server = std::make_unique<EchoTcpServer>(port_);
  server->Start();
  std::this_thread::sleep_for(3600s);

  return std::error_code{};
}

}
