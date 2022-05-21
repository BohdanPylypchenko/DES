#ifndef DES_DEMO_BITBYTE_OPERATOR_H
#define DES_DEMO_BITBYTE_OPERATOR_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

/*
 * single left shift declaration
 */
bitbyte_seq *bitbyte_left_shift(const bitbyte_seq *b);

/*
 * multiple left shift declaration
 */
bitbyte_seq *bitbyte_left_shift_m(const bitbyte_seq *b, const int count);

/*
 * bitbyte_XOR of 2 bit sequence declaration
 */
bitbyte_seq *bitbyte_XOR(const bitbyte_seq *a, const bitbyte_seq *b);

#endif
