cmake_minimum_required(VERSION 3.13)

add_subdirectory(date)

option(BUILD_TESTING OFF)
add_subdirectory(eigen)

add_subdirectory(sofa)

