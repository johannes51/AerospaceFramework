find_package(GTest REQUIRED)
include(GoogleTest)

add_custom_target(tests)
include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

enable_testing()

set(TEST_TIDY_FLAGS "\
-cppcoreguidelines-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-avoid-magic-numbers,\
-cppcoreguidelines-avoid-goto,-cppcoreguidelines-pro-type-vararg,-cppcoreguidelines-pro-type-member-init,\
-cppcoreguidelines-non-private-member-variables-in-classes,-misc-non-private-member-variables-in-classes,\
-hicpp-special-member-functions,-hicpp-avoid-goto,-hicpp-vararg,-hicpp-member-init,\
-readability-magic-numbers,-fuchsia-statically-constructed-objects")

set(TEST_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/geometry/testvector.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/geometry/testtensor.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testwgs84.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/geometry/frame/testecef.cpp"
)

add_executable(AerospaceFramework_test ${TEST_SRCS})

target_link_libraries(AerospaceFramework_test PRIVATE AerospaceFramework_lib gtest gtest_main pthread)
target_include_directories(AerospaceFramework_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

gtest_add_tests(TARGET AerospaceFramework_test)
add_dependencies(tests AerospaceFramework_test)

cxx_14(AerospaceFramework_test)
enable_wall(AerospaceFramework_test)
clang_format(format_AerospaceFramework_test AerospaceFramework_test)
clang_tidy(AerospaceFramework_test "-checks=${CLANG_TIDY_STD_FLAGS},${TEST_TIDY_FLAGS}")
cppcheck(AerospaceFramework_test)

target_code_coverage(AerospaceFramework_test)
