#pragma once

#include "IBootstrapper.h"

namespace dataapi {

class BoostEchoBootstrapper final : public IBootstrapper {
 public:
  BoostEchoBootstrapper(int argc, char** argv);

  auto Bootstrap() noexcept -> std::error_code override;

 private:
  int argc_;
  char** argv_;
};

}
