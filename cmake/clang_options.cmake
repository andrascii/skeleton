if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  find_program(LLVM_COV NAMES "llvm-cov" REQUIRED)
  find_program(LLVM_PROFDATA NAMES "llvm-profdata" REQUIRED)

  message(STATUS "LLVM_COV: ${LLVM_COV}")
  message(STATUS "LLVM_PROFDATA: ${LLVM_PROFDATA}")

  list(APPEND COVERAGE_FLAGS -fcoverage-mapping)
  list(APPEND COVERAGE_FLAGS -fprofile-instr-generate)

  list(APPEND SANITIZE_FLAGS "-fno-omit-frame-pointer")
  list(APPEND SANITIZE_FLAGS "-fsanitize=address,undefined")

  add_compile_options("$<$<CONFIG:DEBUG>:-O0>")
  add_compile_options("$<$<CONFIG:RELEASE>:-O3>")
  add_compile_options("-Wall")
  add_compile_options("-Wextra")
  add_compile_options("-Werror")
  add_compile_options("-msse4.2")
  add_compile_options("-Werror=return-type")
  add_compile_options("-Wno-implicit-fallthrough")
  add_compile_options("-Wno-unused-parameter")
  add_compile_options("-pedantic")
endif()