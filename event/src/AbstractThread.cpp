#include "AbstractThread.h"
#include "Errors.h"
#include "Helpers.h"
#include "Logger.h"

namespace event {

AbstractThread::~AbstractThread() {
  Stop();
  Wait();
}

void AbstractThread::Wait() noexcept {
  if (!thread_.joinable()) {
    return;
  }

  thread_.join();
}

void AbstractThread::Stop() noexcept {
  std::lock_guard lock{ mutex_ };
  completed_ = true;
}

std::error_code AbstractThread::Start() noexcept {
  std::lock_guard lock{ mutex_ };
  completed_ = false;

  if (thread_.joinable()) {
    return common::MakeErrorCode(common::ThreadError::kThreadAlreadyStarted);
  }

  try {
    thread_ = std::thread{ StartHelper() };
  } catch (const std::exception& error) {
    common::Logger()->error("{}", error.what());
    return common::MakeErrorCode(common::ThreadError::kStartThreadError);
  }

  return std::error_code{};
}

void AbstractThread::Terminate() noexcept {
  if (!thread_.joinable()) {
    return;
  }

#ifdef _WIN32
  TerminateThread(thread_.native_handle(), 0);
#else
  pthread_cancel(thread_.native_handle());
#endif
}

std::function<void()> AbstractThread::StartHelper() noexcept {
  return [this] {
    Run();
  };
}

}
