include(make_sanitized_target)

function(make_static_library_sanitized_target)

  set(options)
  set(oneValueArgs TARGET_NAME PRECOMPILED_HEADER)
  set(multiValueArgs SOURCES HEADERS DEPS)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "make_static_library_sanitized_target: TARGET_NAME - ${ARG_TARGET_NAME}")
    message(STATUS "make_static_library_sanitized_target: SOURCES - ${ARG_SOURCES}")
    message(STATUS "make_static_library_sanitized_target: HEADERS - ${ARG_HEADERS}")
    message(STATUS "make_static_library_sanitized_target: DEPS - ${ARG_DEPS}")
    message(STATUS "make_static_library_sanitized_target: PRECOMPILED_HEADER - ${ARG_PRECOMPILED_HEADER}")

    add_library(${ARG_TARGET_NAME} STATIC ${ARG_SOURCES} ${ARG_HEADERS})

    make_sanitized_target(
      TARGET_NAME ${ARG_TARGET_NAME}
      SOURCES ${ARG_SOURCES}
      HEADERS ${ARG_HEADERS}
      DEPS ${ARG_DEPS}
      PRECOMPILED_HEADER ${ARG_PRECOMPILED_HEADER}
    )
  endif()

endfunction()
