cmake_minimum_required(VERSION 3.26)

project(lab6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/)

# add gtest lib for testing
enable_testing()
include(FetchContent)
FetchContent_Declare(
    GTest
    VERSION v1.14.0
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(GTest)

add_executable(vec_test vec.cpp vec_test.cpp)
target_link_libraries(vec_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
