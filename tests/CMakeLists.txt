project(Tests)

add_executable(Google_Tests_run byte_test.cpp
                                bitbyte_test.cpp
                                permut_test.cpp
                                key_test.cpp
                                sbox_test.cpp
                                f_test.cpp
                                feistel_test.cpp
                                des_test.cpp)

target_link_libraries(Google_Tests_run DES -lsodium)

target_link_libraries(Google_Tests_run Test_utils)

target_link_libraries(Google_Tests_run gtest gtest_main)
