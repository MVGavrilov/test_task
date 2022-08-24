cmake_minimum_required(VERSION 3.20)
project(some_hash-example)

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(some_hash-example)
target_sources(some_hash-example PRIVATE ${sources})
target_link_libraries(some_hash-example PRIVATE some_hash::some_hash)