cmake_minimum_required(VERSION 3.21)
project(onikeiso)

enable_testing()

include_directories(3rdparty/Unity/src)
add_subdirectory(3rdparty/Unity)

add_subdirectory(src)
add_subdirectory(tests)
