cmake_minimum_required(VERSION 3.21)

project(static_vector LANGUAGES CXX VERSION 0.9.0)

option(STATIC_VECTOR_TESTS "Build unit tests" OFF)
option(STATIC_VECTOR_INSTALL "Enable install target" OFF)

add_library(static_vector INTERFACE)
add_library(ecpp::static_vector ALIAS static_vector)

target_include_directories(
  static_vector INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                          $<INSTALL_INTERFACE:include>
)
target_compile_features(static_vector INTERFACE cxx_std_20)

if (PROJECT_IS_TOP_LEVEL OR STATIC_VECTOR_TESTS)
  enable_testing()
  add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()

if (PROJECT_IS_TOP_LEVEL OR STATIC_VECTOR_INSTALL)
  include(${PROJECT_SOURCE_DIR}/cmake/static_vector_install.cmake)
endif ()
