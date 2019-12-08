cmake_minimum_required(VERSION 3.0.0)

project(showidea VERSION 0.0.1)

# Set Qt Env
# cmake .. -DQT_VERSION="5.13.2" -DQT_ROOT="/home/mpm"
option(QT_VERSION "Set Qt Version example 5.13.2" OFF)
option(QT_ROOT "Set Qt Version example 5.13.2" OFF)

if (${QT_VERSION} STREQUAL "OFF")
  message(FATAL_ERROR "Qt Version not set")
endif()

if (${QT_ROOT} STREQUAL "OFF")
  set(QT_ROOT $ENV{HOME})
endif()

include(CTest)
enable_testing()

ADD_DEFINITIONS(
-O0 -g -W -Wall
 -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
)

set(QT5_DIR ${QT_ROOT}/Qt${QT_VERSION}/${QT_VERSION}/gcc_64)
set(CMAKE_PREFIX_PATH ${QT5_DIR})

message(STATUS "Using Qt: ${QT5_DIR}")

add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
