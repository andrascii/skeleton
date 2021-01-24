#include "BoostEchoBootstrapper.h"

int main(int argc, char** argv) {
  const std::unique_ptr<dataapi::IBootstrapper> bootstrapper =
    std::make_unique<dataapi::BoostEchoBootstrapper>(argc, argv);

  return bootstrapper->Bootstrap() ?
    EXIT_FAILURE :
    EXIT_SUCCESS;
}
