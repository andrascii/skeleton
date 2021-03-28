#include "EchoTcpServer.h"
#include "ConnectionFactory.h"
#include "Logger.h"
#include "Helpers.h"

namespace echo {

EchoTcpServer::EchoTcpServer(unsigned short port)
  : acceptor_(acceptor_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    guard_(boost::asio::make_work_guard(connections_context_)) {}

EchoTcpServer::~EchoTcpServer() {
  Stop();
}

auto EchoTcpServer::Start() noexcept -> void {
  thread_group_.create_thread([this] {
    common::Helpers::SetCurrentThreadName("TcpServer Accept Connections Thread");
    Accept();
    acceptor_context_.run();
  });

  
  thread_group_.create_thread([this] {
    common::Helpers::SetCurrentThreadName("TcpServer Connections Communication Thread");
    connections_context_.run();
  });
}

auto EchoTcpServer::Stop() noexcept -> void {
  {
    std::lock_guard locker{ mutex_ };

    for (const auto& connection : connections_) {
      connection->Shutdown();
    }

    connections_.clear();
  }

  guard_.reset();
  acceptor_context_.stop();
  connections_context_.stop();
  thread_group_.join_all();
}

auto EchoTcpServer::Accept() noexcept -> void {
  std::shared_ptr<IConnection> incoming_connection;

  {
    std::lock_guard locker{ mutex_ };
    ConnectionFactory factory;
    incoming_connection = factory.Create(ConnectionFactory::TypeEcho, connections_context_);
    connections_.push_back(incoming_connection);
  }

  const auto callback = boost::bind(&EchoTcpServer::HandleAccept,
                                    this,
                                    incoming_connection,
                                    boost::asio::placeholders::error);

  acceptor_.async_accept(incoming_connection->Socket(), callback);
}

auto EchoTcpServer::HandleAccept(const std::shared_ptr<IConnection>& connection,
                                 const boost::system::error_code& error) noexcept -> void {
  if (error) {
    common::Logger()->error("TcpServer::HandleAccept: {}", error.message());
    return;
  }

  common::Logger()->info("Incoming connection...");

  connections_context_.post([connection] {
    connection->Start();
  });

  Accept();
}

}
