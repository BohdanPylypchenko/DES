#ifndef DES_DEMO_BITBYTE_IO_H
#define DES_DEMO_BITBYTE_IO_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <stdio.h>

/*
 * bitbyte_seq writer
 */
void bitbyte_write(FILE *f, bitbyte_seq *b);

/*
 * bitbyte_seq reader
 */
void bitbyte_read(FILE *f, bitbyte_seq **b);

#endif
