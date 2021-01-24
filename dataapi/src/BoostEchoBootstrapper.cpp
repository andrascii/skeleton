#include "BoostEchoBootstrapper.h"
#include "CommandLineParser.h"
#include "Application.h"
#include "Logger.h"
#include "Errors.h"

namespace dataapi {

BoostEchoBootstrapper::BoostEchoBootstrapper(int argc, char** argv)
  : argc_(argc),
    argv_(argv) {}

auto BoostEchoBootstrapper::Bootstrap() noexcept -> std::error_code {
  try {
    const auto help_argument = common::CommandLineArgument{
      "h",
      "help",
      "Shows this message"
    };

    const auto mode_argument = common::CommandLineArgument{
      "m",
      "mode",
      "Specifies mode to start an application.\nValues:\n - client\n - server",
      std::string{},
      true
    };

    const auto port_argument = common::CommandLineArgument{
      "p",
      "port",
      "Specifies port to connect/listen",
      std::string{},
      true
    };

    common::CommandLineParser parser;
    parser.AddArgument(help_argument);
    parser.AddArgument(mode_argument);
    parser.AddArgument(port_argument);
    parser.Parse(argc_, argv_);

    if (parser.HasArgument(help_argument)) {
      common::Logger()->info("{}", parser.HelpMessage());
      return MakeErrorCode(BootstrapError::kBootstrapError);
    }

    const auto mode = parser.ArgumentValue(mode_argument);

    if (mode != "client" && mode != "server") {
      throw std::invalid_argument{ "Invalid mode value " + mode + ". Must be 'client' or 'server'" };
    }

    const auto type = mode == "client" ?
      dataapi::Application::kTypeClient :
      dataapi::Application::kTypeServer;

    const auto port = parser.ArgumentValue(port_argument);
    const auto port_value = std::stoi(port);

    if (port_value < 0 || port_value > 0xffff) {
      throw std::out_of_range{ "Port value out of range: " + port + ". Must be greater than 0 and less than 65536." };
    }

    dataapi::Application application{ type, static_cast<unsigned short>(port_value) };
    const auto error = application.Start();

    if (error) {
      common::Logger()->error("{}", error.message());
      return MakeErrorCode(BootstrapError::kBootstrapError);
    }

    return MakeSuccessError();
  } catch (const std::exception& error) {
    common::Logger()->critical("{}", error.what());
    return MakeErrorCode(BootstrapError::kBootstrapError);
  }
}


}
