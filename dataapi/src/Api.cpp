#include "Api.h"

namespace dataapi {

auto GetSomeNumber1() noexcept -> int {
  return 42;
}

auto GetSomeNumber2() noexcept -> double {
  return 3.1415;
}

auto HelloWorld() noexcept -> std::string {
  return "Hello World"s;
}

}
