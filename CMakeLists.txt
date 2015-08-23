cmake_minimum_required(VERSION 2.6)
project(learnsdl2)
# libsdl2 include directory
include_directories("D:/Develop/mingw_dev_lib/include")
# libsdl2 library directory
link_directories("D:/Develop/mingw_dev_lib/lib")
# turn on all compiler warnings
add_definitions("-Wall")
# C99 standard
add_definitions("-std=c99")
# force MinGW-w64 generating 32-bit code
add_definitions("-m32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")

add_subdirectory(src)
