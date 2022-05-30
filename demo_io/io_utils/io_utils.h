#ifndef DES_DEMO_IO_UTILS_H
#define DES_DEMO_IO_UTILS_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include <stdio.h>

#define READ_MODE "rb"
#define WRITE_MODE "wb"
#define READ_WRITE_MODE_OVERRIDE "wb+"
#define READ_WRITE_MODE_KEEP "rb+"

/*
 * Converts file (given by name) into bitbyte_seq
 * and saves result to new file
 */
void convert_from_file_to_bitbyte_seq_file(const char *origin_file_name,
                                           const char *bitbyte_file_name);

/*
 * Reads all input till \n from stdin
 */
char *input(const char *msg);

/*
 * Converts bytes of bitbyte_seq to file
 */
void convert_bytes_to_file(FILE *f_b, bitbyte_seq *b);

#endif
