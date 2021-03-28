#pragma once

namespace common {

class CommandLineArgument final {
 public:
  CommandLineArgument(const std::string& name, const std::string& description);

  auto SetDefaultValue(const std::string& value) noexcept -> void;
  auto SetRequired(bool value) noexcept -> void;
  auto SetValueless(bool value) noexcept -> void;

  auto AddArgumentIfThereIsThis(const CommandLineArgument& argument) -> void;
  auto ArgumentIfThereIsThis() const noexcept -> const std::vector<CommandLineArgument>&;

  auto AddArgumentIfThereIsNoThis(const CommandLineArgument& argument) -> void;
  auto ArgumentIfThereIsNoThis() const noexcept -> const std::vector<CommandLineArgument>&;

  auto DefaultValue() const noexcept -> const std::string&;
  auto Description() const noexcept -> const std::string&;
  auto Name() const noexcept -> const std::string&;
  auto IsRequired() const noexcept -> bool;
  auto IsValueless() const noexcept -> bool;

 private:
  std::string name_;
  std::string description_;
  std::string default_value_;
  bool required_;
  bool valueless_;

  std::vector<CommandLineArgument> args_if_there_is_this_;
  std::vector<CommandLineArgument> args_if_there_is_no_this_;
};

}
