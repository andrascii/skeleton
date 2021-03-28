#include "CommandLineParser.h"

namespace common {

auto CommandLineParser::Parse(int& argc, char** argv) -> void {
  for (const auto& argument : arguments_) {
    options_description_.add_options()
      (
        argument.Name().data(),
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
  if (variables_map_.count(argument.Name().data())) {
    return variables_map_[argument.Name().data()].as<std::string>();
  }

  return std::string{};
}

auto CommandLineParser::HasArgument(const CommandLineArgument& argument) const -> bool {
  return variables_map_.count(argument.Name().data()) != 0;
}

auto CommandLineParser::HelpMessage() const noexcept -> std::string {
  std::stringstream stream;
  stream << "Usage: [options]:" << std::endl;
  stream << options_description_ << std::endl;
  return stream.str();
}

auto CommandLineParser::HandleArgumentWithDependants(const CommandLineArgument& argument) -> void {
  boost::program_options::options_description group;

  for (const auto& argument : argument.ArgumentIfThereIsNoThis()) {
    group.add_options()(argument.Name().data(), ArgumentMeta(argument), argument.Description().data());

    if (argument.ArgumentIfThereIsNoThis().empty()) {
      continue;
    }

    HandleArgumentWithDependants(argument);
  }

  options_description_.add(group);
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

}
