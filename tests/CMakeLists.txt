cmake_minimum_required(VERSION 3.24)

enable_testing()

cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(
  googletest URL https://github.com/google/googletest/archive/main.zip FIND_PACKAGE_ARGS NAMES
                 GTest
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(
  ecpp_static_vector_ut
  src/01_construction.cpp
  # src/02_assignment.cpp
  # src/03_access.cpp
  src/04_iterators.cpp
  src/05_capacity.cpp
  src/06_modifiers.cpp
  src/07_non_member_functions.cpp
)

target_include_directories(ecpp_static_vector_ut PUBLIC include)
target_link_libraries(ecpp_static_vector_ut ecpp_static_vector GTest::gtest_main)
target_link_options(ecpp_static_vector_ut PUBLIC -pthread)

gtest_discover_tests(ecpp_static_vector_ut)

add_custom_command(
  TARGET ecpp_static_vector_ut COMMENT "Run tests" POST_BUILD COMMAND ctest ARGS --output-on-failure
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
