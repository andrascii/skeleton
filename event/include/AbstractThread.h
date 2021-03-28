#pragma once

#include "IThread.h"

namespace event {

class AbstractThread : public IThread {
 public:
  ~AbstractThread();

  void Wait() noexcept override;

  void Stop() noexcept override;

  std::error_code Start() noexcept override;

  void Terminate() noexcept override;

 protected:
  virtual void Run() = 0;

 private:
  virtual std::function<void()> StartHelper() noexcept;

 private:
  mutable std::mutex mutex_;
  std::thread thread_;
  bool completed_;
};

}
