#include "Api.h"
#include "Logger.h"

int main() {
  common::Logger()->info("dataapi::GetSomeNumber1() returns: {}", dataapi::GetSomeNumber1());
  common::Logger()->info("dataapi::GetSomeNumber2() returns: {}", dataapi::GetSomeNumber2());
  common::Logger()->info("dataapi::HelloWorld() returns: {}", dataapi::HelloWorld());

  return EXIT_SUCCESS;
}