
cmake_minimum_required(VERSION 3.14)

project(ecpp_static_vector)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_library(ecpp_static_vector INTERFACE)
target_include_directories(ecpp_static_vector INTERFACE include)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(tests)
endif()