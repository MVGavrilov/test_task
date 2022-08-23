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

if(DEFINED SOME_HASH_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${SOME_HASH_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()

if(NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
endif()

#------------------------------------------------------------------------------
# SOURCES
#------------------------------------------------------------------------------

add_library(some_hash)
# if we use find_package for our lib, it would be seen as some_hash_example::some_hash_example,
# so we use this alias to unify the names
add_library(some_hash::some_hash ALIAS some_hash)

set(public_headers
        include/SomeHash.h)
set(sources
        ${public_headers}
        src/SomeHash.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

target_sources(some_hash PRIVATE ${sources})
target_include_directories(some_hash
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
    install(TARGETS some_hash
            DESTINATION ${INSTALL_DIR}/lib)
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

