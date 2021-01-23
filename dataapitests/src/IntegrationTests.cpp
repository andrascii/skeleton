#include "TcpClient.h"
#include "EchoTcpServer.h"

namespace dataapitests {

TEST(IntegrationTests, ClientServerEchoTest) {
  unsigned short port = 44444;
  dataapi::TcpClient client;
  dataapi::EchoTcpServer server{ port };
  server.Start();

  boost::system::error_code error;
  const auto ip = boost::asio::ip::address::from_string("127.0.0.1", error);

  ASSERT_EQ(error, boost::system::error_code());
  ASSERT_EQ(client.Connect(boost::asio::ip::tcp::endpoint(ip, port)), boost::system::error_code());

  const auto write_message = [&](const std::string& message) {
    boost::asio::streambuf buffer;
    std::ostream stream{ &buffer };
    stream << message;
    client.Write(buffer);
  };

  const auto read_message = [&](size_t size) -> std::string {
    boost::asio::streambuf buffer;
    client.Read(buffer, size);
    return boost::asio::buffer_cast<const char*>(buffer.data());
  };

  auto original = "Echo Message #1"s;
  write_message(original);
  auto echo = read_message(original.size());
  EXPECT_EQ(original, echo);

  original = "Echo Message #2"s;
  write_message(original);
  echo = read_message(original.size());
  EXPECT_EQ(original, echo);

  original = "Echo Message #3"s;
  write_message(original);
  echo = read_message(original.size());
  EXPECT_EQ(original, echo);

  original = "Echo Message #4"s;
  write_message(original);
  echo = read_message(original.size());
  EXPECT_EQ(original, echo);

  server.Stop();
}

}
