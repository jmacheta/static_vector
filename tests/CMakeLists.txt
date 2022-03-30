# This is a standalone build, so fetch GoogleTest and build unit tests
enable_testing()

include(FetchContent)

FetchContent_Declare( googletest URL https://github.com/google/googletest/archive/main.zip)

# For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

FILE(GLOB_RECURSE STATIC_VECTOR_TEST_CASES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(ecpp_static_vector_ut ${STATIC_VECTOR_TEST_CASES})
target_include_directories(ecpp_static_vector_ut PUBLIC include)
target_link_libraries(ecpp_static_vector_ut ecpp_static_vector gtest_main)

include(GoogleTest)
gtest_discover_tests(ecpp_static_vector_ut)

add_custom_command(TARGET ecpp_static_vector_ut
    COMMENT "Run tests"
    POST_BUILD COMMAND ctest ARGS --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
