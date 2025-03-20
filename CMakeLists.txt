cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
include(FetchContent)

option(ENABLE_WEB_REQUESTS "Enable web requests in utils library" OFF)
option(ENABLE_ARGUMENT_PARSER  "Enable web requests in utils library" ON)


# Create an INTERFACE library
add_library(CppUtils INTERFACE)
target_include_directories(CppUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


if (ENABLE_WEB_REQUESTS)
    FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG        1.11.2 # Replace with the latest release or desired tag
    )
    FetchContent_MakeAvailable(cpr)
    target_link_libraries(CppUtils INTERFACE cpr::cpr)
    target_compile_definitions(CppUtils INTERFACE ENABLE_WEB_REQUESTS)
endif()

# Conditionally include and link argparse
if (ENABLE_ARGUMENT_PARSER)
    FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    )
    FetchContent_MakeAvailable(argparse)
    target_link_libraries(CppUtils INTERFACE argparse)
    target_compile_definitions(CppUtils INTERFACE ENABLE_ARGUMENT_PARSER)
endif()


# Expose the include directory
