cmake_minimum_required(VERSION 3.21)

project(static_vector LANGUAGES CXX VERSION 1.0.0)

option(STATIC_VECTOR_TESTS "Configure unit tests" OFF)
option(STATIC_VECTOR_INSTALL "Configure install target" ON)

add_library(static_vector INTERFACE)
add_library(ecpp::static_vector ALIAS static_vector)

target_include_directories(
  static_vector INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                          $<INSTALL_INTERFACE:include>
)
target_compile_features(static_vector INTERFACE cxx_std_20)

if (PROJECT_IS_TOP_LEVEL OR STATIC_VECTOR_TESTS)
  enable_testing()
  add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()

if (PROJECT_IS_TOP_LEVEL OR STATIC_VECTOR_INSTALL)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install.cmake)
endif ()
