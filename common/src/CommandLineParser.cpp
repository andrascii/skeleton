#include "CommandLineParser.h"

namespace common {

auto CommandLineParser::Parse(int& argc, char** argv) -> void {
  for (const auto& argument : arguments_) {
    options_description_.add_options()
      (
        Formatted(argument).data(),
        ArgumentMeta(argument),
        argument.Description().data()
      );
  }

  const auto parsed_command_line = boost::program_options::command_line_parser(argc, argv)
    .options(options_description_)
    .allow_unregistered()
    .run();

  boost::program_options::store(parsed_command_line, variables_map_);
}

auto CommandLineParser::AddArgument(const CommandLineArgument& argument) -> void {
  arguments_.push_back(argument);
}

auto CommandLineParser::ArgumentValue(const CommandLineArgument& argument) const -> std::string {
  if (variables_map_.count(argument.ShortName().data())) {
    return variables_map_[argument.ShortName().data()].as<std::string>();
  } else if (variables_map_.count(argument.VerboseName().data())) {
    return variables_map_[argument.VerboseName().data()].as<std::string>();
  }

  return std::string{};
}

auto CommandLineParser::HasArgument(const CommandLineArgument& argument) const -> bool {
  return variables_map_.count(argument.ShortName().data()) != 0 ||
    variables_map_.count(argument.VerboseName().data()) != 0;
}

auto CommandLineParser::HelpMessage() const noexcept -> std::string {
  std::stringstream stream;
  stream << "Usage: [options]:" << std::endl;
  stream << options_description_ << std::endl;
  return stream.str();
}

auto CommandLineParser::ArgumentMeta(const CommandLineArgument& argument) const -> boost::program_options::typed_value<std::string>* {
  auto meta = boost::program_options::value<std::string>();

  if (!argument.DefaultValue().empty()) {
    meta->default_value(argument.DefaultValue().data());
  }

  if (argument.IsRequired()) {
    meta->required();
  }

  return meta;
}

auto CommandLineParser::Formatted(const CommandLineArgument& argument) const -> std::string {
  if (!argument.ShortName().empty() && !argument.VerboseName().empty()) {
    return argument.ShortName() + "," + argument.VerboseName();
  }

  if (!argument.ShortName().empty()) {
    return argument.ShortName();
  }

  if (!argument.VerboseName().empty()) {
    return argument.VerboseName();
  }

  throw std::invalid_argument{ "Invalid command line argument: there is no short and verbose version of the argument" };
}

}
