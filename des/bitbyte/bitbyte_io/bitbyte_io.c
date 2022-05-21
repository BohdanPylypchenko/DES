#include "bitbyte_io.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <stdio.h>
#include <malloc.h>

/*
 * bitbyte_seq writer implementation
 */
void bitbyte_write(FILE *f, bitbyte_seq *b) {
    // Getting size info
    int temp[2] = { bitbyte_get_size_bit(b), bitbyte_get_size_byte(b) };

    // Writing size info
    fwrite(temp, sizeof(int), 2, f);

    // Writing bit_byte
    fwrite(bitbyte_get_ptr(b), 1, bitbyte_get_size_byte(b), f);
}

/*
 * bitbyte_seq reader implementation
 */
void bitbyte_read(FILE *f, bitbyte_seq **b) {
    // Reading size info
    int size_info[2];
    fread(&size_info, sizeof(int), 2, f);

    // Reading bit_byte
    BYTE *bitbyte = (BYTE *)malloc(size_info[1]);
    fread(bitbyte, 1, size_info[1], f);

    // Creating new bitbyte_seq
    *b = bitbyte_new(bitbyte, size_info[0]);
}
