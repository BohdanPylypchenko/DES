project(Tests)

add_executable(Google_Tests_run byte_test.cpp
        bitbyte_test.cpp
                                permut_test.cpp)

target_link_libraries(Google_Tests_run DES)

target_link_libraries(Google_Tests_run gtest gtest_main)
