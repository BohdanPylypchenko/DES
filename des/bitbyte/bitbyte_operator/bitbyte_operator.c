#include "bitbyte_operator.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <malloc.h>

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
 */
int bitbyte_split(const bitbyte_seq *origin, const int part_bit_size,
                  bitbyte_seq ***result) {

    bitbyte_seq **parts;

    // origin bit size < part bit size branch
    if (bitbyte_get_size_bit(origin) < part_bit_size) {
        // Creating bitbyte_seq * array with len = 1
        parts = (bitbyte_seq **) malloc(sizeof(bitbyte_seq *));

        // Creating new bitbyte_seq with zeroes
        parts[0] = bitbyte_zero(part_bit_size);

        // Copying from origin
        for (int i = 0; i < bitbyte_get_size_bit(origin); i++) {
            bitbyte_set_bit(parts[0], i, bitbyte_get_bit(origin, i));
        }

        // Returning
        *result = parts;
        return 1;
    }

    // Count of parts after split
    int count;

    // origin bit size is integer dividable by part bit size
    if (bitbyte_get_size_bit(origin) % part_bit_size == 0) {
        // Calculating count of parts
        count = bitbyte_get_size_bit(origin) / part_bit_size;

        // Allocating memory
        parts = (bitbyte_seq **) malloc(count * sizeof(bitbyte_seq *));

        // Creating parts
        for (int i = 0; i < count; i++) {
            parts[i] = bitbyte_zero(part_bit_size);
        }

        // Copying
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < part_bit_size; j++) {
                bitbyte_set_bit(parts[i], j,
                                bitbyte_get_bit(origin, i * part_bit_size + j));
            }
        }

        // Returning
        *result = parts;
        return count;
    } else {
        // Calculating count of parts
        count = bitbyte_get_size_bit(origin) / part_bit_size + 1;

        // Allocating memory
        parts = (bitbyte_seq **) malloc(count * sizeof(bitbyte_seq *));

        // Creating parts
        for (int i = 0; i < count; i++) {
            parts[i] = bitbyte_zero(part_bit_size);
        }

        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < part_bit_size; j++) {
                bitbyte_set_bit(parts[i], j,
                                bitbyte_get_bit(origin, i * part_bit_size + j));
            }
        }

        for (int i = 0; i < bitbyte_get_size_bit(origin) - (count - 1) * part_bit_size; i++) {
            bitbyte_set_bit(parts[count - 1], i,
                            bitbyte_get_bit(origin, (count - 1) * part_bit_size + i));
        }

        // Returning
        *result = parts;
        return count;
    }
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
 * Clone method implementation
 */
bitbyte_seq *bitbyte_clone(bitbyte_seq *origin) {
    // Creating new bitbyte_seq instance
    bitbyte_seq *cloned = bitbyte_zero(bitbyte_get_size_bit(origin));

    // Cloning bits
    for (int i = 0; i < bitbyte_get_size_bit(cloned); i++) {
        bitbyte_set_bit(cloned, i, bitbyte_get_bit(origin, i));
    }

    // Returning cloned
    return cloned;
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
