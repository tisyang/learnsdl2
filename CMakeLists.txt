cmake_minimum_required(VERSION 2.6)
project(learnsdl2)
# libsdl2 include directory
include_directories("D:/mingw_dev_lib/include")
# libsdl2 library directory
link_directories("D:/mingw_dev_lib/lib")
# set all executable files built into directory "bin/"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
# turn on all compiler warnings
add_definitions("-Wall")

add_subdirectory(src)
