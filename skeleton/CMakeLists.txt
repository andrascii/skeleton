cmake_minimum_required(VERSION 3.16)

set(THIS_TARGET_NAME ${SKELETON_APP})
project(${THIS_TARGET_NAME})

#
# deps include directories
#
set(DATA_API_LIB_INCLUDE_DIR "../${DATA_API_LIB}/include")
set(COMMON_LIB_INCLUDE_DIR "../${COMMON_LIB}/include")

#
# current target sources directories
#
set(SOURCES_DIR src)
set(INCLUDES_DIR include)

#
# precompiled header
#
set(PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/stdafx.h")

#
# deps
#
list(APPEND DEPS ${DATA_API_LIB})
list(APPEND DEPS ${COMMON_LIB})
list(APPEND DEPS ${Boost_LIBRARIES})
list(APPEND DEPS spdlog::spdlog)

#
# collecting sources and headers
#
aux_source_directory(${SOURCES_DIR} SOURCES_LIST)
file(GLOB_RECURSE HEADERS_LIST "${INCLUDES_DIR}/*.h")

#
# adding precompiled header into specific folder
#
source_group("Precompiled Headers" FILES ${PRECOMPILED_HEADER})

#
# creating target
#
add_executable(${THIS_TARGET_NAME} ${HEADERS_LIST} ${SOURCES_LIST})

#
# adding include directories to created target
#
include_directories(${INCLUDES_DIR})
include_directories(${DATA_API_LIB_INCLUDE_DIR})
include_directories(${COMMON_LIB_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

#
# adding precompiled header
#
target_precompile_headers(${THIS_TARGET_NAME} PRIVATE ${PRECOMPILED_HEADER})

#
# linking this target with other targets
#
target_link_libraries(${THIS_TARGET_NAME} PRIVATE ${DEPS})
