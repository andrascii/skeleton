#pragma once

#include "CommandLineArgument.h"

namespace dataapi {

class CommandLineParser final {
 public:
  auto Parse(int& argc, char** argv) -> void;

  auto AddArgument(const CommandLineArgument& argument) -> void;
  auto ArgumentValue(const CommandLineArgument& argument) const -> std::string;
  auto HasArgument(const CommandLineArgument& argument) const -> bool;
  auto HelpMessage() const noexcept -> std::string;

 private:
  auto Formatted(const CommandLineArgument& argument) const -> std::string;
  auto ArgumentMeta(const CommandLineArgument& argument) const -> boost::program_options::typed_value<std::string>*;

 private:
  std::vector<CommandLineArgument> arguments_;
  boost::program_options::options_description options_description_;
  boost::program_options::variables_map variables_map_;
};

}
