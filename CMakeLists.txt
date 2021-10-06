# general settings
cmake_minimum_required(VERSION 3.14)
project(gnl_tester)

add_compile_options(-Wall -Wextra -Werror)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(GNL_PATH ../../get_next_line)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# test specific
enable_testing()


add_subdirectory(${GNL_PATH} build)
include_directories(${GNL_PATH})

add_executable(
  main
  main.cpp
)
target_link_libraries(
  main
  gtest_main
  gnl
)

include(GoogleTest)
gtest_discover_tests(main)

