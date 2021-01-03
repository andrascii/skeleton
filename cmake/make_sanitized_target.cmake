#
# Must be outer visible SANITIZE_FLAGS
#
function(make_sanitized_target)
  set(options)
  set(oneValueArgs TARGET_NAME PRECOMPILED_HEADER)
  set(multiValueArgs SOURCES HEADERS DEPS)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (ARG_PRECOMPILED_HEADER)
    target_precompile_headers(${ARG_TARGET_NAME} PRIVATE ${ARG_PRECOMPILED_HEADER})
  endif()

  message(STATUS "make_sanitized_target: TARGET_NAME - ${ARG_TARGET_NAME}")
  message(STATUS "make_sanitized_target: SOURCES - ${ARG_SOURCES}")
  message(STATUS "make_sanitized_target: HEADERS - ${ARG_HEADERS}")
  message(STATUS "make_sanitized_target: DEPS - ${ARG_DEPS}")
  message(STATUS "make_sanitized_target: PRECOMPILED_HEADER - ${ARG_PRECOMPILED_HEADER}")

  target_link_libraries(${ARG_TARGET_NAME} PRIVATE ${ARG_DEPS})
  target_compile_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${SANITIZE_FLAGS}>")
  target_compile_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${SANITIZE_FLAGS}>")
  target_compile_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${SANITIZE_FLAGS}>")
  target_compile_options(${ARG_TARGET_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${SANITIZE_FLAGS}>")
endfunction()
