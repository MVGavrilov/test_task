cmake_minimum_required(VERSION 3.20)
project(some_hash-tests)

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
endif()

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz)

set(INSTALL_GTEST OFF)

# To be sure, that project will work without gtest installed
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)

set(sources
        tests.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(some_hash-tests)
target_sources(some_hash-tests PRIVATE ${sources})

target_link_libraries(some_hash-tests
        PRIVATE
        some_hash::some_hash
        gtest_main)

include(GoogleTest)
gtest_discover_tests(some_hash-tests)
