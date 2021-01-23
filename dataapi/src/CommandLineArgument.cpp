#include "CommandLineArgument.h"

namespace dataapi {

CommandLineArgument::CommandLineArgument(const std::string& short_name,
                                         const std::string& verbose_name,
                                         const std::string& description,
                                         const std::string& default_value,
                                         bool required)
  : short_name_(short_name),
    verbose_name_(verbose_name),
    description_(description),
    default_value_(default_value),
    is_required_(required) {}

auto CommandLineArgument::DefaultValue() const noexcept -> const std::string& {
  return default_value_;
}

auto CommandLineArgument::Description() const noexcept -> const std::string& {
  return description_;
}

auto CommandLineArgument::ShortName() const noexcept -> const std::string& {
  return short_name_;
}

auto CommandLineArgument::VerboseName() const noexcept -> const std::string& {
  return verbose_name_;
}

auto CommandLineArgument::IsRequired() const noexcept -> bool {
  return is_required_;
}

}
