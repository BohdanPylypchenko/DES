#ifndef DES_DEMO_BITBYTE_SEQ_H
#define DES_DEMO_BITBYTE_SEQ_H

#include "byte.h"

/*
 * Bit byte sequence structure declaration
 */
typedef struct bit_byte_sequence bitbyte_seq;

/*
 * Custom bit byte sequence constructor
 */
bitbyte_seq *bitbyte_new(const BYTE *bit_byte, const int size_bit);

/*
 * Zero-initialized bit byte sequence constructor
 */
bitbyte_seq *bitbyte_zero(const int size_bit);

/*
 * bitbyte pointer getter
 */
BYTE *bitbyte_get_ptr(const bitbyte_seq *b);

/*
 * bit getter
 */
BYTE bitbyte_get_bit(const bitbyte_seq *b, const int pos);

/*
 * bit setter
 */
BYTE bitbyte_set_bit(const bitbyte_seq *b, const int pos, const BYTE x);

/*
 * byte getter
 */
BYTE bitbyte_get_byte(const bitbyte_seq *b, const int pos);

/*
 * byte setter
 */
BYTE bitbyte_set_byte(const bitbyte_seq *b, const int pos, const BYTE x);

/*
 * size_bit getter
 */
int bitbyte_get_size_bit(const bitbyte_seq *b);

/*
 * size_byte getter
 */
int bitbyte_get_size_byte(const bitbyte_seq *b);

/*
 * bitbyte destructor
 */
bitbyte_seq *bitbyte_free(bitbyte_seq *b);

#endif
