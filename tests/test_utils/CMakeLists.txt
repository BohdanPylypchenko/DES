project(Test_utils)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        test_utils.h)

set(SOURCE_FILES
        test_utils.c)

add_library(Test_utils STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Test_utils)
