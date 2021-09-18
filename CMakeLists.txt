cmake_minimum_required(VERSION 3.13)
project(AerospaceFramework CXX C)

option(ASF_BUILD_TESTS Off)

set(CLANG_TIDY_STD_FLAGS "*,-readability-redundant-member-init,-readability-else-after-return,\
-llvm-else-after-return,-llvmlibc-*,-cert-err58-cpp,-android-*,-fuchsia-*,\
-clang-diagnostic-reorder,-clang-diagnostic-missing-declarations,-clang-diagnostic-error,\
-google-runtime-references,-google-runtime-int,-google-readability-todo,\
-modernize-use-trailing-return-type,-modernize-use-default-member-init")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/analysis;")
include(code-coverage)
add_subdirectory(dependencies)
add_subdirectory(src)
if (NOT MSVC AND ASF_BUILD_TESTS)
  add_subdirectory(test)
endif()
