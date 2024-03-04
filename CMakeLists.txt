cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
  SimKeyboaard
  VERSION 0.0.1
  DESCRIPTION "A CoppeliaSim plugin to teleop using the keyboard"
  HOMEPAGE_URL "https://github.com/wpumacay/teleop-plugin"
  LANGUAGES C CXX)

if(DEFINED ENV{COPPELIASIM_ROOT})
  set(COPPELIASIM_PROG_PATH $ENV{COPPELIASIM_ROOT}/programming/include)
else()
  message(FATAL_ERROR "Please define the environment variable COPPELIASIM_ROOT")
endif()

list(APPEND CMAKE_MODULE_PATH ${COPPELIASIM_PROG_PATH}/cmake)

find_package(CoppeliaSim 4.6.0 REQUIRED)

# cmake-format: off
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

coppeliasim_add_plugin(
    ${PROJECT_NAME}
    LEGACY
    SOURCES
    ${PROJECT_SOURCE_DIR}/source/simKeyboard.cpp
)
# cmake-format: on

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
