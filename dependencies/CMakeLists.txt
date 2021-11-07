cmake_minimum_required(VERSION 3.13)

option(BUILD_TESTING OFF)
option(EIGEN_BUILD_DOC OFF)
add_subdirectory(eigen)

add_subdirectory(sofa)

