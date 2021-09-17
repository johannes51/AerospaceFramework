find_package(GTest REQUIRED)
include(GoogleTest)

add_custom_target(tests)

enable_testing()

set(TEST_TIDY_FLAGS "\
    -cppcoreguidelines-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-avoid-magic-numbers,\
    -cppcoreguidelines-avoid-goto,-cppcoreguidelines-pro-type-vararg,-cppcoreguidelines-pro-type-member-init,\
    -cppcoreguidelines-non-private-member-variables-in-classes,-cppcoreguidelines-avoid-non-const-global-variables,\
    -hicpp-special-member-functions,-hicpp-avoid-goto,-hicpp-vararg,-hicpp-member-init,\
    -readability-magic-numbers,-fuchsia-statically-constructed-objects,-google-build-using-namespace,-llvmlibc-*,\
    -misc-non-private-member-variables-in-classes")

set(TEST_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/testtensor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/testvector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testecef.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testlocal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testvehicleframe.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testwgs84.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mock/mockcjd.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/mock/mockstatevector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/mock/mocktensor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/mock/mockvector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testconv_helpers.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testconversion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/testsofa_helpers.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testtai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testtt.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testut1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time/testutc.cpp"
    )

add_executable(AerospaceFramework_test ${TEST_SRCS})

target_link_libraries(AerospaceFramework_test PRIVATE AerospaceFramework_lib gtest pthread)
target_include_directories(AerospaceFramework_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AerospaceFramework_test SYSTEM PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS})

get_target_property(Eigen_include_dirs Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(AerospaceFramework_test SYSTEM PRIVATE ${Eigen_include_dirs})

gtest_add_tests(TARGET AerospaceFramework_test)
add_dependencies(tests AerospaceFramework_test)

cxx_17(AerospaceFramework_test)
if (UNIX AND CMAKE_BUILD_TYPE MATCHES "Debug")
    enable_wall(AerospaceFramework_test)
    enable_effcpp(AerospaceFramework_test)
    clang_format(format_AerospaceFramework_test AerospaceFramework_test)
    clang_tidy(AerospaceFramework_test)
    cppcheck(AerospaceFramework_test)

    target_code_coverage(AerospaceFramework_test)
else()
    enable_wnone(AerospaceFramework_test)
endif()

