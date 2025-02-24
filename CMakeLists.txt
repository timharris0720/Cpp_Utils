cmake_minimum_required(VERSION 3.14)
project(CppUtils LANGUAGES CXX)
add_library(CppUtils INTERFACE)
#file(GLOB UtilFiles "include/Utils/*.h" "include/Utils/Memory/*.h" "include/Utils/Strings/*.h")
target_include_directories(CppUtils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Expose the include directory
