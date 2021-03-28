#pragma once

#include "IConnection.h"

namespace echo {

class ConnectionFactory final {
 public:
  enum Type {
    TypeEcho
  };

  auto Create(Type type, boost::asio::io_context& context) const -> std::shared_ptr<IConnection>;
};

}
