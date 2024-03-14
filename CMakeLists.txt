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

find_package(OpenGL REQUIRED)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)

list(APPEND CMAKE_MODULE_PATH ${COPPELIASIM_PROG_PATH}/cmake)

find_package(CoppeliaSim 4.6.0 REQUIRED)

# cmake-format: off
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

coppeliasim_add_plugin(
    simKeyboard
    LEGACY
    SOURCES
    ${PROJECT_SOURCE_DIR}/source/simKeyboard.cpp
    # Dear ImGui sources
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    # GLAD source
    ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c
)
# cmake-format: on

target_include_directories(simKeyboard PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(simKeyboard
                           PUBLIC ${PROJECT_SOURCE_DIR}/vendor/imgui/)
target_include_directories(simKeyboard
                           PUBLIC ${PROJECT_SOURCE_DIR}/vendor/glad/include)
target_link_libraries(simKeyboard PUBLIC glfw OpenGL::GL)
