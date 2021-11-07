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

set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/time/calendartime.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/classicaljuliandate.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/conversion_helpers.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/conversion_helpers.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/conversion_internals.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/conversions.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/julianliketime.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/julianliketimeimp.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/modifiedjuliandate.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/tai.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/tai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/timepoint.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/tt.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/tt.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/ut1.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/ut1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/utc.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/utc.cpp"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/util/bilinearinterpolator.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/bilinearinterpolator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/interpolatorfactory.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/interpolatorfactory.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa_helper.h"
    ${SOFA_SRCS}
    )

find_package(Eigen3 3.4 REQUIRED)

add_library(AerospaceFramework_lib ${LIB_SOURCES})
target_include_directories(AerospaceFramework_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AerospaceFramework_lib PUBLIC Eigen3::Eigen PRIVATE sofa)

get_target_property(Eigen_include_dirs Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(AerospaceFramework_lib SYSTEM PRIVATE ${Eigen_include_dirs})

cxx_17(AerospaceFramework_lib)
if (UNIX AND CMAKE_BUILD_TYPE MATCHES "Debug")
    enable_wall(AerospaceFramework_lib)
    enable_effcpp(AerospaceFramework_lib)
    clang_format(format_AerospaceFramework_lib AerospaceFramework_lib)
    clang_tidy(AerospaceFramework_lib)
    cppcheck(AerospaceFramework_lib)

    target_code_coverage(AerospaceFramework_lib)
else()
    enable_wnone(AerospaceFramework_lib)
endif()

find_package(Python3 COMPONENTS Interpreter)
if (Python3_Interpreter_FOUND)
    add_custom_command(TARGET AerospaceFramework_lib
        POST_BUILD
        COMMAND ${Python3_EXECUTABLE} ARGS download_data.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../script
        )
endif()

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/../data/dut1.csv"
    "${CMAKE_CURRENT_BINARY_DIR}/data/dut1.csv"
    COPYONLY)

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/../data/leap_seconds.csv"
    "${CMAKE_CURRENT_BINARY_DIR}/data/leap_seconds.csv"
    COPYONLY)

