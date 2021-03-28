#include "BoostEchoBootstrapper.h"

int main(int argc, char** argv) {
  const std::unique_ptr<echo::IBootstrapper> bootstrapper =
    std::make_unique<echo::BoostEchoBootstrapper>(argc, argv);

  return bootstrapper->Bootstrap() ?
    EXIT_FAILURE :
    EXIT_SUCCESS;
}
