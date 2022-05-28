cmake_minimum_required(VERSION 3.23)
project(DES_Demo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_executable(DES_Demo main.c)

include_directories(des)
add_subdirectory(des)
target_link_libraries(DES_Demo DES -lsodium)

add_subdirectory(tests)
add_subdirectory(tests/test_utils)
