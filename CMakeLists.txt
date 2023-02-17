cmake_minimum_required(VERSION 3.21)

project(ecpp_static_vector)

option(ECPP_BUILD_TESTS "Forces building test cases" OFF)

add_library(ecpp_static_vector INTERFACE)
target_include_directories(ecpp_static_vector INTERFACE include)
target_compile_features(ecpp_static_vector INTERFACE cxx_std_20)

if (PROJECT_IS_TOP_LEVEL OR ECPP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()
