#include "bitbyte_operator.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <limits.h>
#include <malloc.h>
#include <memory.h>

/*
 * private left shift method declaration
 */
static void lshift(const bitbyte_seq *b);

/*
 * Single left shift implementation
 */
bitbyte_seq *bitbyte_left_shift(const bitbyte_seq *b) {
    lshift(b);
}

/*
 * multiple left shift implementation
 */
bitbyte_seq *bitbyte_left_shift_m(const bitbyte_seq *b, const int count) {
    for (int i = 0; i < count; i++) {
        lshift(b);
    }
}

/*
 * bitbyte_XOR of 2 bit sequence implementation
 */
bitbyte_seq *bitbyte_XOR(const bitbyte_seq *a, const bitbyte_seq *b) {
    // Creating new zero bitbyte sequence
    bitbyte_seq *c = bitbyte_zero(bitbyte_get_size_bit(a));

    // XOR
    for (int i = 0; i < bitbyte_get_size_bit(c); i++) {
        bitbyte_set_bit(c, i, bitbyte_get_bit(a, i) ^ bitbyte_get_bit(b, i));
    }

    // Returning
    return c;
}

/*
 * bitbyte_split implementation
 * if bit size of original % count != 0,
 * function behavior is undefined
 */
bitbyte_seq **bitbyte_split(const bitbyte_seq *original, const int count) {
    // Allocating parts array
    bitbyte_seq **parts = (bitbyte_seq **) malloc(count * sizeof(bitbyte_seq *));

    // Calculating new common bit size for each new part
    int new_bit_size = bitbyte_get_size_bit(original) / count;

    // Creating parts
    for (int i = 0; i < count; i++) {
        parts[i] = bitbyte_zero(new_bit_size);
    }

    // Copying
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < new_bit_size; j++) {
            bitbyte_set_bit(parts[i], j,
                            bitbyte_get_bit(original, i * new_bit_size + j));
        }
    }

    // Returning
    return parts;
}

/*
 * Joins given array of bitbyte_seq in 1 structure
 * returns size of joined bitbyte_seq
 */
bitbyte_seq *bitbyte_join(bitbyte_seq **parts, const int count) {
    // Calculating size bit of result
    int result_size_bit = 0;
    for (int i = 0; i < count; i++) {
        result_size_bit += bitbyte_get_size_bit(parts[i]);
    }

    // Creating result bitbyte_seq
    bitbyte_seq *result = bitbyte_zero(result_size_bit);

    // Copying
    int shift = 0;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < bitbyte_get_size_bit(parts[i]); j++) {
            bitbyte_set_bit(result, shift + j, bitbyte_get_bit(parts[i], j));
        }
        shift += bitbyte_get_size_bit(parts[i]);
    }

    // Returning
    return result;
}

/*
 * private left shift method implementation
 */
static void lshift(const bitbyte_seq *b) {
    // Saving 0 bit
    BYTE temp = bitbyte_get_bit(b, 0);

    // Shifting
    for (int i = 0; i < bitbyte_get_size_bit(b) - 1; i++) {
        bitbyte_set_bit(b, i, bitbyte_get_bit(b, i + 1));
    }

    // Assigning last
    bitbyte_set_bit(b, bitbyte_get_size_bit(b) - 1, temp);
}
