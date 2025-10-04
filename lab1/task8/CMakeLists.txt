cmake_minimum_required(VERSION 3.10)
project(lab1_task8)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=maybe-uninitialized")


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

add_library(${CMAKE_PROJECT_NAME}_lib src/func.c)
add_executable(${CMAKE_PROJECT_NAME}_exe main.c)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)


enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main gtest)

add_test(NAME GrowCounterTests COMMAND tests)   