#
# For Debug build using Clang we building tests with enabled code coverage flags
# adding custom 'coverage' target to start llvm-profdata and llvm-cov utilities
# to analyze code coverage
#
# Must be visible outer variables LLVM_COV and LLVM_PROFDATA
#

function(make_coverage_target)
  set(options)
  set(oneValueArgs TARGET_NAME)
  set(multiValueArgs)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  message(STATUS "make_coverage_target: TARGET_NAME - ${ARG_TARGET_NAME}")

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${COVERAGE_FLAGS}>")
    target_link_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${COVERAGE_FLAGS}>")

    if (UNIX OR APPLE)
      add_custom_target(coverage COMMAND ${ARG_TARGET_NAME} DEPENDS ${ARG_TARGET_NAME})

      add_custom_command(TARGET coverage POST_BUILD
        COMMAND ${LLVM_PROFDATA}
          merge
          -sparse default.profraw
          -o ${ARG_TARGET_NAME}.profdata
      )

      add_custom_command(TARGET coverage POST_BUILD
        COMMAND ${LLVM_COV}
          show
          -format=html
          ./${ARG_TARGET_NAME}
          -instr-profile=${ARG_TARGET_NAME}.profdata
          --show-line-counts-or-regions
          -Xdemangler=c++filt
          --use-color > coverate.html
      )

      add_custom_command(TARGET coverage POST_BUILD
        COMMAND ${LLVM_COV}
          report
          ./${ARG_TARGET_NAME}
          -instr-profile=${ARG_TARGET_NAME}.profdata
          -Xdemangler=c++filt
      )
    endif()

  endif()
endfunction()
