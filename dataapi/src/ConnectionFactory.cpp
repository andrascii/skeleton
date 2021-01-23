#include "ConnectionFactory.h"
#include "EchoConnection.h"

namespace dataapi {

auto ConnectionFactory::Create(Type type, boost::asio::io_context& context) const -> std::shared_ptr<IConnection> {
  switch (type) {
    case TypeEcho: {
      return std::make_shared<EchoConnection>(context);
    }
  }

  throw std::runtime_error("Invalid type of connection");
}

}
