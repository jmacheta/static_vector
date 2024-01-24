cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(
  googletest URL https://github.com/google/googletest/archive/main.zip FIND_PACKAGE_ARGS NAMES
                 GTest
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(
  static_vector_ut
  01_construction.cpp
  # 02_assignment.cpp
  # 03_access.cpp
  04_iterators.cpp
  05_capacity.cpp
  06_modifiers.cpp
  07_non_member_functions.cpp
)

target_include_directories(static_vector_ut PUBLIC include)
target_link_libraries(static_vector_ut static_vector GTest::gtest_main)
target_link_options(static_vector_ut PUBLIC -pthread)

gtest_discover_tests(static_vector_ut)