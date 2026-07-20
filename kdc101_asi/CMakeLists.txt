cmake_minimum_required(VERSION 3.10)
project(KDC101_ASI)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_MAKE_PROGRAM mingw32-make CACHE STRING "并行构建工具" FORCE)
    set(CMAKE_MAKE_PROGRAM_FLAGS -j${N} CACHE STRING "并行线程数" FORCE)
endif()


add_subdirectory(kdc101)
add_subdirectory(asi)