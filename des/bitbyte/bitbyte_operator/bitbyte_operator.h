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
 * Creates full copy of given bitbyte_seq
 */
bitbyte_seq *bitbyte_clone(bitbyte_seq *origin);

/*
 * Splits origin bitbyte_seq
 * in parts, each part_bit_size bits.
 * Returns count of parts.
 *
 * If bitbyte_get_size_bit(origin) < part_bit_size,
 * single bitbyte_seq with size part_bit_size created,
 * all bits from origin are copied, other bits are zero.
 *
 * If bitbyte_get_size_bit(origin) % part_bit_size == 0,
 * just split
 * Else just split + 1 bitbyte_seq with
 * bitbyte_get_size_bit(origin) - (count - 1) * part_bit_size
 * copied as last origin bits.
 * Other bits are zero.
 */
int bitbyte_split(const bitbyte_seq *origin, const int part_bit_size,
                  bitbyte_seq ***result);

/*
 * Joins given array of bitbyte_seq in 1 structure
 * returns size of joined bitbyte_seq
 */
bitbyte_seq *bitbyte_join(bitbyte_seq **parts, const int count);

#endif
