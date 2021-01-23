#pragma once

#include "IConnection.h"

namespace dataapi {

class EchoTcpServer {
 public:
  explicit EchoTcpServer(unsigned short port);
  ~EchoTcpServer();

  auto Start() noexcept -> void;
  auto Stop() noexcept -> void;

 private:
  auto Accept() noexcept -> void;

  auto HandleAccept(const std::shared_ptr<IConnection>& connection,
                    const boost::system::error_code& error) noexcept -> void;

 private:
  boost::asio::io_context acceptor_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::thread_group thread_group_;

  mutable std::mutex mutex_;
  boost::asio::io_context connections_context_;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> guard_;
  std::vector<std::shared_ptr<IConnection>> connections_;
};

}
