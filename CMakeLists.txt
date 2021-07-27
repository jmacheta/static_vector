
cmake_minimum_required(VERSION 3.14)

project(ecpp_static_vector)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_library(ecpp_static_vector INTERFACE)
target_include_directories(ecpp_static_vector INTERFACE include)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
# This is a standalone build, so fetch GoogleTest and build unit tests
enable_testing()

include(FetchContent)

FetchContent_Declare( googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FILE(GLOB_RECURSE STATIC_VECTOR_TEST_CASES CONFIGURE_DEPENDS "tests/src/*.cpp")
add_executable(ecpp_static_vector_ut ${STATIC_VECTOR_TEST_CASES})
target_include_directories(ecpp_static_vector_ut PUBLIC tests/include)
target_link_libraries(ecpp_static_vector_ut ecpp_static_vector gtest_main)

include(GoogleTest)
gtest_discover_tests(ecpp_static_vector_ut)

add_custom_command(TARGET ecpp_static_vector_ut
                   COMMENT "Run tests"
                   POST_BUILD COMMAND ctest ARGS --output-on-failure
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)


endif()