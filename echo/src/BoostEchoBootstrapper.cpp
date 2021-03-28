#include "BoostEchoBootstrapper.h"
#include "CommandLineParser.h"
#include "Application.h"
#include "Logger.h"
#include "Errors.h"

namespace echo {

BoostEchoBootstrapper::BoostEchoBootstrapper(int argc, char** argv)
  : argc_(argc),
    argv_(argv) {}

auto BoostEchoBootstrapper::Bootstrap() noexcept -> std::error_code {
  try {
    const auto help_argument = common::CommandLineArgument{
      "help",
      "Shows this message"
    };

    auto mode_argument = common::CommandLineArgument{
      "mode",
      "Specifies mode to start an application.\nValues:\n - client\n - server"
    };

    mode_argument.SetRequired(true);

    auto port_argument = common::CommandLineArgument{
      "port",
      "Specifies port to connect/listen"
    };

    port_argument.SetRequired(true);

    common::CommandLineParser parser;
    parser.AddArgument(help_argument);
    parser.AddArgument(mode_argument);
    parser.AddArgument(port_argument);
    parser.Parse(argc_, argv_);

    if (parser.HasArgument(help_argument)) {
      common::Logger()->info("{}", parser.HelpMessage());
      return common::MakeErrorCode(common::BootstrapError::kBootstrapError);
    }

    const auto mode = parser.ArgumentValue(mode_argument);

    if (mode != "client" && mode != "server") {
      throw std::invalid_argument{ "Invalid mode value " + mode + ". Must be 'client' or 'server'" };
    }

    const auto type = mode == "client" ?
      echo::Application::kTypeClient :
      echo::Application::kTypeServer;

    const auto port = parser.ArgumentValue(port_argument);
    const auto port_value = std::stoi(port);

    if (port_value < 0 || port_value > 0xffff) {
      throw std::out_of_range{ "Port value out of range: " + port + ". Must be greater than 0 and less than 65536." };
    }

    echo::Application application{ type, static_cast<unsigned short>(port_value) };
    const auto error = application.Start();

    if (error) {
      common::Logger()->error("{}", error.message());
      return common::MakeErrorCode(common::BootstrapError::kBootstrapError);
    }

    return std::error_code{};
  } catch (const std::exception& error) {
    common::Logger()->critical("{}", error.what());
    return common::MakeErrorCode(common::BootstrapError::kBootstrapError);
  }
}


}
