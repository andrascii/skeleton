#pragma once

#include "AbstractThread.h"

namespace event {

class AbstractNamedThread : public AbstractThread {
 public:
  AbstractNamedThread(const std::string& name);

 private:
  std::function<void()> StartHelper() noexcept override;

 private:
  std::string name_;
};

}
