cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
include(FetchContent)

option(ENABLE_WEB_REQUESTS "Enable web requests in utils library" OFF)
option(ENABLE_ARGUMENT_PARSER  "Enable Argparse Integration in utils library" ON)
option(ENABLE_JSON  "Enable JSON in utils library" ON)
option(ENABLE_SOCKETS  "Enable SOCKETS in utils library" ON)


# Create an INTERFACE library
add_library(CppUtils INTERFACE)
target_include_directories(CppUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


FetchContent_Declare(
    utf8cpp
    GIT_REPOSITORY https://github.com/nemtrif/utfcpp.git
    GIT_TAG master  # or specify a stable commit/tag
)

FetchContent_MakeAvailable(utf8cpp)
target_include_directories(CppUtils PUBLIC  ${utf8cpp_SOURCE_DIR}/source )


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

if(ENABLE_JSON)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(json)
    target_link_libraries(CppUtils INTERFACE nlohmann_json::nlohmann_json)
    target_compile_definitions(CppUtils INTERFACE ENABLE_JSON)
endif()

if(ENABLE_SOCKETS)
    target_compile_definitions(CppUtils INTERFACE ENABLE_SOCKETS)
endif()
# Expose the include directory
