#pragma once

namespace common {

enum class BootstrapError {
  kBootstrapError = 1,
};

enum class ApplicationError {
  kInvalidApplicationTypeError = 1,
  kUnableToConnectToServer,
};

enum class ThreadError {
  kThreadAlreadyStarted = 1,
  kStartThreadError,
};

auto MakeErrorCode(ApplicationError error) noexcept -> std::error_code;
auto MakeErrorCode(BootstrapError error) noexcept -> std::error_code;
auto MakeErrorCode(ThreadError error) noexcept -> std::error_code;

}

namespace std {

template <> struct is_error_code_enum<common::ApplicationError> : public std::true_type {};
template <> struct is_error_code_enum<common::BootstrapError> : public std::true_type {};
template <> struct is_error_code_enum<common::ThreadError> : public std::true_type {};

}
