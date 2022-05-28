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

/*
 * bitbyte_split
 * if bit size of origin % count != 0,
 * function behavior is undefined
 * returns bit size of 1 part
 */
bitbyte_seq **bitbyte_split(const bitbyte_seq *origin, const int count);

/*
 * Joins given array of bitbyte_seq in 1 structure
 * returns size of joined bitbyte_seq
 */
bitbyte_seq *bitbyte_join(bitbyte_seq **parts, const int count);

/*
 * Creates full copy of given bitbyte_seq
 */
bitbyte_seq *bitbyte_clone(bitbyte_seq *origin);

#endif
