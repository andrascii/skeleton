#include "CommandLineArgument.h"

namespace common {

CommandLineArgument::CommandLineArgument(const std::string& name, const std::string& description)
  : name_(name),
    description_(description),
    required_(false) {}

auto CommandLineArgument::SetDefaultValue(const std::string& value) noexcept -> void {
  default_value_ = value;
}

auto CommandLineArgument::SetRequired(bool value) noexcept -> void {
  required_ = value;
}

auto CommandLineArgument::SetValueless(bool value) noexcept -> void {
  valueless_ = value;
}

auto CommandLineArgument::AddArgumentIfThereIsThis(const CommandLineArgument& argument) -> void {
  args_if_there_is_this_.push_back(argument);
}

auto CommandLineArgument::ArgumentIfThereIsThis() const noexcept -> const std::vector<CommandLineArgument>& {
  return args_if_there_is_this_;
}

auto CommandLineArgument::AddArgumentIfThereIsNoThis(const CommandLineArgument& argument) -> void {
  args_if_there_is_no_this_.push_back(argument);
}

auto CommandLineArgument::ArgumentIfThereIsNoThis() const noexcept -> const std::vector<CommandLineArgument>& {
  return args_if_there_is_no_this_;
}

auto CommandLineArgument::DefaultValue() const noexcept -> const std::string& {
  return default_value_;
}

auto CommandLineArgument::Description() const noexcept -> const std::string& {
  return description_;
}

auto CommandLineArgument::Name() const noexcept -> const std::string& {
  return name_;
}

auto CommandLineArgument::IsRequired() const noexcept -> bool {
  return required_;
}

auto CommandLineArgument::IsValueless() const noexcept -> bool {
  return valueless_;
}

}
