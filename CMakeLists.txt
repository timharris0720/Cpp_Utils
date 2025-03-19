cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
include(FetchContent)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG        1.11.2 # Replace with the latest release or desired tag
)
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)
add_library(CppUtils INTERFACE)
file(GLOB UtilFiles "include/Utils/*.h" "include/Utils/*.hpp" "include/Utils/Web/*.h" "include/Utils/System/*.h" "include/Utils/FileIO/*.h" "include/Utils/Memory/*.h" "include/Utils/Strings/*.h" "include/Utils/Typese/*.h")
  target_include_directories(CppUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(CppUtils INTERFACE UtilFiles)
target_link_libraries(CppUtils INTERFACE cpr::cpr argparse)
# Expose the include directory
