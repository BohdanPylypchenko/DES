#ifndef DES_DEMO_BITBYTE_IO_H
#define DES_DEMO_BITBYTE_IO_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <stdio.h>

/*
 * bitbyte_seq writer
 */
void bitbyte_write(const FILE *f, const bitbyte_seq *b);

/*
 * bitbyte_seq reader
 */
void bitbyte_read(const FILE *f, bitbyte_seq **b);

#endif
