cmake_minimum_required(VERSION 3.21)
project(onikeiso)

enable_testing()

include_directories(Unity/src)
add_subdirectory(Unity)

add_subdirectory(src)
