cmake_minimum_required(VERSION 3.21)
project(some_hash
        VERSION 1.0.0
        DESCRIPTION "Test task"
        LANGUAGES CXX)
#------------------------------------------------------------------------------
# OPTIONS
#------------------------------------------------------------------------------

option(SOME_HASH_BUILD_TESTS "Build some_hash tests" OFF)
option(SOME_HASH_BUILD_EXAMPLES "Build some_hash examples" OFF)
option(SOME_HASH_INSTALL "Generate target for installing some_hash" PROJECT_IS_TOP_LEVEL)

#------------------------------------------------------------------------------
# SOURCES
#------------------------------------------------------------------------------

add_library(some_hash INTERFACE)
# if we use find_package for our lib, it would be seen as some_hash_example::some_hash_example,
# so we use this alias to unify the names
add_library(some_hash::some_hash ALIAS some_hash)

set(public_headers
        include/SomeHash.hpp)
set(sources
        ${public_headers})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(some_hash PRIVATE ${sources})
target_include_directories(some_hash
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(some_hash INTERFACE cxx_std_17)

#------------------------------------------------------------------------------
# INSTALL
#------------------------------------------------------------------------------

if(SOME_HASH_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    if(DEFINED ENV{INSTALL_DIR})
        set(INSTALL_DIR "$ENV{INSTALL_DIR}")
    else()
        set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/INSTALL_DIR)
    endif()
    message("Library some_hash will be installed to ${INSTALL_DIR}")
    install(FILES ${public_headers}
            DESTINATION ${INSTALL_DIR}/include/)
endif()

#------------------------------------------------------------------------------
# TESTS AND EXAMPLES
#------------------------------------------------------------------------------

if(SOME_HASH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(SOME_HASH_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

