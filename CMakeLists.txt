cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
include(FetchContent)

option(ENABLE_WEB_REQUESTS "Enable web requests in utils library" OFF)
option(ENABLE_ARGUMENT_PARSER  "Enable Argparse Integration in utils library" ON)
option(ENABLE_JSON  "Enable JSON in utils library" ON)
option(ENABLE_SOCKETS  "Enable SOCKETS in utils library" ON)
option(ENABLE_REFLECTION  "Enable Reflection Support in utils library" OFF)


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

if (ENABLE_REFLECTION)
    FetchContent_Declare(
        rttr
        GIT_REPOSITORY https://github.com/rttrorg/rttr.git
        GIT_TAG master
    )
    set(RTTR_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(RTTR_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
    set(RTTR_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(RTTR_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    set(RTTR_INSTALL_CMAKE_CONFIG_MODULE OFF CACHE BOOL "" FORCE)
    set(RTTR_BUILD_PACKAGE OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(rttr)
    target_link_libraries(CppUtils INTERFACE  RTTR::Core_Lib)
    target_compile_definitions(CppUtils INTERFACE ENABLE_REFLECTION)
endif()
# Expose the include directory
