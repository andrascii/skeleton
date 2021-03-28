#include "AbstractNamedThread.h"
#include "Errors.h"
#include "Logger.h"
#include "Helpers.h"

namespace event {

AbstractNamedThread::AbstractNamedThread(const std::string& name)
  : name_{ name } {}

std::function<void()> AbstractNamedThread::StartHelper() noexcept {
  return [this] {
    common::Helpers::SetCurrentThreadName(name_);
    Run();
  };
}

}
