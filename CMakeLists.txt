cmake_minimum_required(VERSION 3.23)
project(DES_Demo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "-march=skylake")

add_executable(DES_Demo main.c demo_io/option_keeper/option_keeper.c demo_io/option_keeper/option_keeper.h demo_io/io_utils/io_utils.c demo_io/io_utils/io_utils.h demo/demo_run.c demo/demo_run.h)

include_directories(des)
add_subdirectory(des)
target_link_libraries(DES_Demo DES -lsodium)

add_subdirectory(tests)
add_subdirectory(tests/test_utils)
