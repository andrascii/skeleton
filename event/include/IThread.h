#pragma once

namespace event {

class IThread {
 public:
  virtual ~IThread() = default;

  virtual void Wait() noexcept = 0;

  virtual void Stop() noexcept = 0;

  virtual std::error_code Start() noexcept = 0;

  virtual void Terminate() noexcept = 0;
};

}
