project(DES)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(HEADER_FILES
        permut/permut.h)

set(SOURCE_FILES
        permut/permut.c)

add_library(DES STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(DES -lsodium)
