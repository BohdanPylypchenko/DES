project(DES)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        permut/permut.h
        byte.h
        bitbyte/bitbyte_seq/bitbyte_seq.h
        bitbyte/bitbyte_operator/bitbyte_operator.h
        bitbyte/bitbyte_io/bitbyte_io.h
        key/key.h
        sbox/sbox.h
        des/f_func/f_func.h
        des/feistel_net/feistel_net.h
        des.h)

set(SOURCE_FILES
        permut/permut.c
        bitbyte/bitbyte_seq/bitbyte_seq.c
        bitbyte/bitbyte_operator/bitbyte_operator.c
        bitbyte/bitbyte_io/bitbyte_io.c
        key/key.c
        sbox/sbox.c
        des/f_func/f_func.c
        des/feistel_net/feistel_net.c
        des.c)

add_library(DES STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(DES -lsodium)
