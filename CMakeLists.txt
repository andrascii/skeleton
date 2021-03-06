cmake_minimum_required(VERSION 3.16)

if (UNIX AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
  set(CMAKE_C_COMPILER "clang")
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project("Skeleton" LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(clang_options)
include(msvc_options)

message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

set(VERSION_MAJOR 0 CACHE STRING "Major version #" FORCE)
set(VERSION_MINOR 1 CACHE STRING "Minor version #" FORCE)
set(VERSION_PATCH 0 CACHE STRING "Patch version #" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# deps packages
#
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS thread program_options REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

#
# project variables
#
set(EVENT_LIB event)
set(ECHO_LIB echo)
set(SKELETON_APP skeleton)
set(ECHO_LIB_TESTS echotests)
set(COMMON_LIB common)

add_subdirectory(${COMMON_LIB})
add_subdirectory(${EVENT_LIB})
add_subdirectory(${ECHO_LIB})
add_subdirectory(${SKELETON_APP})

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(${ECHO_LIB_TESTS})
endif()

include(InstallRequiredSystemLibraries)

set(CPACK_GENERATOR "TGZ;RPM")
set(CPACK_PACKAGE_NAME "Skeleton")
set(CPACK_PACKAGE_CONTACT "apugachevdev@gmail.com")
set(CPACK_PACKAGE_VENDOR "Andrey Pugachev")
set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_COMPONENT_DISPLAY_NAME "Skeleton")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.x86_64")
set(CPACK_PACKAGE_DESCRIPTION "Skeleton Release")
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};CMake;ALL;/")
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/bin" isSystemDir)

if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")
endif("${isSystemDir}" STREQUAL "-1")

include(CPack)
