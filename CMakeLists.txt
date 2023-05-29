cmake_minimum_required(VERSION 3.21)

project(static_vector LANGUAGES CXX VERSION 0.9.0)

option(STATIC_VECTOR_BUILD_TESTS "Forces building test cases" OFF)

add_library(static_vector INTERFACE)
add_library(ecpp::static_vector ALIAS static_vector)

target_include_directories(static_vector INTERFACE include)
target_compile_features(static_vector INTERFACE cxx_std_20)


if (PROJECT_IS_TOP_LEVEL OR STATIC_VECTOR_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()
