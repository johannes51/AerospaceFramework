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
    "${CMAKE_CURRENT_SOURCE_DIR}/util/definitions.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/sofa.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/utcut1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/ut1tai.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/ut1tt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/c2t06a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/xy06.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/tr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/jd2cal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/dat.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/utctai.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/taiut1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/c2i06a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/era00.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/sp00.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/pom00.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/c2tcio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/falp03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/faf03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fad03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/faom03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fave03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fae03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fama03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/faju03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fasa03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fame03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/faur03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fane03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fapa03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fal03.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/dtf2d.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/cal2jd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/pnm06a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/cr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/bpn2xy.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/s06.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/c2ixys.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/anp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/ir.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/rz.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/pfw06.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/cp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/c2tcio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/nut00a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/nut06a.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/fw2m.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/rx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/rxr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/ry.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/sofa/obl06.c"
)

find_package(Eigen3 3.3.1 REQUIRED)

add_library(AerospaceFramework_lib ${LIB_SOURCES})
target_include_directories(AerospaceFramework_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AerospaceFramework_lib PUBLIC date Eigen3::Eigen)
