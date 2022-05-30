#include "bitbyte_seq.h"

#include <malloc.h>

/*
 * Bit byte sequence structure implementation
 */
typedef struct bit_byte_sequence {
    // Bytes array to represent bit sequence
    BYTE *bit_byte;

    // Size in bits
    int size_bit;

    // Size in bytes
    int size_byte;
} bitbyte_seq;

/*
 * Calculates byte size for sequence
 */
static int p_calc_size_byte(const int size_bit) {
    if (size_bit % 8 == 0) {
        return size_bit / 8;
    } else {
        return size_bit / 8 + 1;
    }
}

/*
 * Private constructor
 */
static bitbyte_seq *p_bitbyte_new(const BYTE *bit_byte,
                                  const int size_bit, const int size_byte);
/*
 * Custom bit byte sequence constructor implementation
 */
bitbyte_seq *bitbyte_new(const BYTE *bit_byte, const int size_bit) {
    // Returning
    return p_bitbyte_new(bit_byte, size_bit, p_calc_size_byte(size_bit));
}

/*
 * Zero-initialized bit byte sequence constructor implementation
 */
bitbyte_seq *bitbyte_zero(const int size_bit) {
    // Calculating byte size
    int size_byte = p_calc_size_byte(size_bit);

    // Creating zero byte array
    BYTE *temp = (BYTE *) calloc(size_byte, 1);

    // Returning
    return p_bitbyte_new(temp, size_bit, size_byte);
}

/*
 * bitbyte pointer getter implementation
 */
BYTE *bitbyte_get_ptr(const bitbyte_seq *b) {
    return b->bit_byte;
}

/*
 * bit getter implementation
 */
BYTE bitbyte_get_bit(const bitbyte_seq *b, const int pos) {
    // Calculating byte and bit positions
    int byte_pos = pos / (int)8;
    int bit_pos = pos % 8;

    // Returning bit on pos
    return GET_LNB(b->bit_byte[byte_pos], bit_pos);
}

/*
 * bit setter implementation
 */
BYTE bitbyte_set_bit(const bitbyte_seq *b, const int pos, const BYTE x) {
    // Calculating byte and bit positions
    int byte_pos = pos / (int)8;
    int bit_pos = pos % 8;

    // Setting bit on pos
    return SET_LNB(b->bit_byte[byte_pos], bit_pos, x);
}

/*
 * byte getter implementation
 */
BYTE bitbyte_get_byte(const bitbyte_seq *b, const int pos) {
    return b->bit_byte[pos];
}

/*
 * byte setter implementation
 */
BYTE bitbyte_set_byte(const bitbyte_seq *b, const int pos, const BYTE x) {
    b->bit_byte[pos] = x;
    return b->bit_byte[pos];
}

/*
 * size_bit getter implementation
 */
int bitbyte_get_size_bit(const bitbyte_seq *b) {
    return b->size_bit;
}

/*
 * size_byte getter implementation
 */
int bitbyte_get_size_byte(const bitbyte_seq *b) {
    return b->size_byte;
}

/*
 * bitbyte destructor implementation
 */
bitbyte_seq *bitbyte_free(bitbyte_seq *b) {
    // Free bitbyte
    free(b->bit_byte);

    // Free b
    free(b);

    // Returning
    return NULL;
}

/*
 * Private constructor implementation
 */
static bitbyte_seq *p_bitbyte_new(const BYTE *bit_byte,
                                  const int size_bit, const int size_byte) {
    // Allocating memory for new object
    bitbyte_seq *b = (bitbyte_seq *) malloc(sizeof(bitbyte_seq));

    // Assigning
    b->size_bit = size_bit;
    b->size_byte = size_byte;
    b->bit_byte = bit_byte;

    // Returning
    return b;
}
