#include "Errors.h"

namespace {

using namespace common;

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

struct ThreadErrorCategory : public std::error_category {
  [[nodiscard]] auto name() const noexcept -> const char* override {
    return "Thread Error";
  }

  auto message(int error) const -> std::string override {
    switch (static_cast<ThreadError>(error)) {
      case ThreadError::kThreadAlreadyStarted: {
        return "Thread already started";
      }
      case ThreadError::kStartThreadError: {
        return "Starting thread error";
      }
      default: {
        return "Undefined error";
      }
    }
  }
};


}

namespace common {

auto MakeErrorCode(ApplicationError error) noexcept -> std::error_code {
  static ApplicationErrorCategory category;
  return std::error_code{ static_cast<int>(error), category };
}

auto MakeErrorCode(BootstrapError error) noexcept -> std::error_code {
  static BootstrapErrorCategory category;
  return std::error_code{ static_cast<int>(error), category };
}

auto MakeErrorCode(ThreadError error) noexcept -> std::error_code {
  static ThreadErrorCategory category;
  return std::error_code{ static_cast<int>(error), category };
}

}
