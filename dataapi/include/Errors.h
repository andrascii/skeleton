#pragma once

namespace dataapi {

enum class BootstrapError : int32_t {
  kBootstrapError = 1,
};

enum class ApplicationError : int32_t {
  kInvalidApplicationTypeError = 1,
  kUnableToConnectToServer,
};

auto MakeSuccessError() noexcept -> std::error_code;
auto MakeErrorCode(ApplicationError error) noexcept -> std::error_code;
auto MakeErrorCode(BootstrapError error) noexcept -> std::error_code;

}
