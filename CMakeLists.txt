cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
include(FetchContent)

option(ENABLE_WEB_REQUESTS "Enable web requests in utils library" OFF)
option(ENABLE_WEB_SERVER "Enable web server in utils library" OFF)
option(ENABLE_ARGUMENT_PARSER  "Enable Argparse Integration in utils library" OFF)
option(ENABLE_JSON  "Enable JSON in utils library" OFF)
option(ENABLE_SOCKETS  "Enable SOCKETS in utils library" OFF)
option(ENABLE_REFLECTION  "Enable Reflection Support in utils library" OFF)


# Create an INTERFACE library
add_library(CppUtils INTERFACE)
target_include_directories(CppUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ENABLE_WEB_SERVER)
        
    FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG master
    )

    FetchContent_MakeAvailable(httplib)
    target_link_libraries(CppUtils INTERFACE httplib::httplib)
    target_compile_definitions(CppUtils INTERFACE ENABLE_WEB_SERVER)
message(STATUS "UTILS -  Installed HTTPLIB")

endif()

if (ENABLE_WEB_REQUESTS)
    FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
    )
    # et(CPR_USE_SYSTEM_CURL OFF CACHE INTERNAL "" FORCE)
    set(CPR_CURL_USE_LIBPSL OFF CACHE INTERNAL "" FORCE)
    set(CPR_USE_SYSTEM_LIB_PSL OFF CACHE INTERNAL "" FORCE)
set(CPR_BUILD_TESTS OFF)
set(CPR_ENABLE_CPPCHECK OFF)
set(CPR_THREAD_POOL "BUILTIN")
    FetchContent_MakeAvailable(cpr)


    target_link_libraries(CppUtils INTERFACE cpr::cpr)
    target_compile_definitions(CppUtils INTERFACE ENABLE_WEB_REQUESTS)
message(STATUS "UTILS -  Installed CPR")

endif()

# Conditionally include and link argparse
if (ENABLE_ARGUMENT_PARSER)
    set(ARGPARSE_BUILD_TESTS OFF)
    set(ARGPARSE_BUILD_SAMPLES OFF)
    FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    )
    FetchContent_MakeAvailable(argparse)
    target_link_libraries(CppUtils INTERFACE argparse)
    target_compile_definitions(CppUtils INTERFACE ENABLE_ARGUMENT_PARSER)
message(STATUS "UTILS -  Installed ArgParse")

endif()

if(ENABLE_JSON)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
    )
	set(JSON_BuildTests OFF)
    set(JSON_MultipleHeaders OFF)
   
    FetchContent_MakeAvailable(json)
    target_link_libraries(CppUtils INTERFACE nlohmann_json::nlohmann_json)
    target_compile_definitions(CppUtils INTERFACE ENABLE_JSON)
message(STATUS "UTILS -  Installed JSON")

endif()

if(ENABLE_SOCKETS)
message(STATUS "UTILS -  Installed Sockets")

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
message(STATUS "UTILS -  Installed RTTR")

endif()
# Expose the include directory
