#include "Errors.h"

namespace {

using namespace dataapi;

enum class SuccessError : int32_t {
  kSuccessError,
};

struct SuccessErrorCategory : public std::error_category {
  [[nodiscard]] auto name() const noexcept -> const char* override {
    return "Success Error";
  }

  auto message(int error) const -> std::string override {
    switch (static_cast<SuccessError>(error)) {
      case SuccessError::kSuccessError: {
        return "Success error";
      }
      default: {
        return "Undefined application error";
      }
    }
  }
};

struct BootstrapErrorCategory : public std::error_category {
  [[nodiscard]] auto name() const noexcept -> const char* override {
    return "Bootstrap Error";
  }

  auto message(int error) const -> std::string override {
    switch (static_cast<BootstrapError>(error)) {
      case BootstrapError::kBootstrapError: {
        return "Bootstrap error";
      }
      default: {
        return "Undefined application error";
      }
    }
  }
};

struct ApplicationErrorCategory : public std::error_category {
  [[nodiscard]] auto name() const noexcept -> const char* override {
    return "Application Error";
  }

  auto message(int error) const -> std::string override {
    switch (static_cast<ApplicationError>(error)) {
      case ApplicationError::kInvalidApplicationTypeError: {
        return "Invalid application type error. Not a client nor server";
      }
      case ApplicationError::kUnableToConnectToServer: {
        return "Unable to connect to the specified server";
      }
      default: {
        return "Undefined application error";
      }
    }
  }
};

}

namespace dataapi {

auto MakeSuccessError() noexcept -> std::error_code {
  static SuccessErrorCategory category;
  return std::error_code{ static_cast<int>(SuccessError::kSuccessError), category };
}

auto MakeErrorCode(ApplicationError error) noexcept -> std::error_code {
  static ApplicationErrorCategory category;
  return std::error_code{ static_cast<int>(error), category };
}

auto MakeErrorCode(BootstrapError error) noexcept -> std::error_code {
  static BootstrapErrorCategory category;
  return std::error_code{ static_cast<int>(error), category };
}

}
