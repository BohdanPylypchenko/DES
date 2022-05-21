#include "bitbyte_operator.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <limits.h>

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
    for (int i = 0; i < bitbyte_get_size_byte(c); i++) {
        bitbyte_set_byte(c, i, bitbyte_get_byte(a, i) ^ bitbyte_get_byte(b, i));
    }

    // Returning
    return c;
}

/*
 * private left shift method implementation
 */
static void lshift(const bitbyte_seq *b) {
    BYTE *current_byte;
    int size = bitbyte_get_size_byte(b);

    for (current_byte = bitbyte_get_ptr(b); size--; ++current_byte) {
        BYTE bit = 0;

        if (size) {
            bit = current_byte[1] & (1 << (CHAR_BIT - 1)) ? 1 : 0;
        }

        *current_byte <<= 1;
        *current_byte |= bit;
    }
}
//void shiftl(void *object, size_t size)
//{
//    unsigned char *byte;
//    for ( byte = object; size--; ++byte )
//    {
//        unsigned char bit = 0;
//        if ( size )
//        {
//            bit = byte[1] & (1 << (CHAR_BIT - 1)) ? 1 : 0;
//        }
//        *byte <<= 1;
//        *byte  |= bit;
//    }
//}
