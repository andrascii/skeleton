#pragma once

namespace common {

class CommandLineArgument final {
 public:
  CommandLineArgument(const std::string& short_name,
                      const std::string& verbose_name,
                      const std::string& description,
                      const std::string& default_value = std::string{},
                      bool required = false);

  auto DefaultValue() const noexcept -> const std::string&;
  auto Description() const noexcept -> const std::string&;
  auto ShortName() const noexcept -> const std::string&;
  auto VerboseName() const noexcept -> const std::string&;
  auto IsRequired() const noexcept -> bool;

 private:
  std::string short_name_;
  std::string verbose_name_;
  std::string description_;
  std::string default_value_;
  bool is_required_;
};

}
