#pragma once

namespace echo {

class Application final {
 public:
  enum Type {
    kTypeClient,
    kTypeServer,
  };

  Application(Type type, unsigned short port);

  auto Start() const noexcept -> std::error_code;

 private:
  auto StartEchoClient() const noexcept -> std::error_code;
  auto StartEchoServer() const noexcept -> std::error_code;

 private:
  Type type_;
  unsigned short port_;
};

}
