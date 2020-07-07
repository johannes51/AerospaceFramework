cmake_minimum_required(VERSION 3.13)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -fno-omit-frame-pointer")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../analysis;")
include(doxygen)
include(formatting)
include(tools)
include(compiler-options)
include(cpp-standards)

add_subdirectory(util/sofa)

set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/statevector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/statevector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/tensor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/tensor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/transformations.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/transformations.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/vector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/vector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/ecef.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/ecef.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/eci.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/eci.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/frame.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/frameimpl.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/frameimpl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/wgs84.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/wgs84.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/local.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/local.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/vehicleframe.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/vehicleframe.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/asf_definitions.h"
    ${SOFA_SRCS}
)

find_package(Eigen3 3.3.1 REQUIRED)

add_library(AerospaceFramework_lib ${LIB_SOURCES})
target_include_directories(AerospaceFramework_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AerospaceFramework_lib PUBLIC date Eigen3::Eigen)
