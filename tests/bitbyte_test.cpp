#include "gtest/gtest.h"

extern "C" {
#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"
#include "bitbyte/bitbyte_io/bitbyte_io.h"

#include "byte.h"

#include <malloc.h>
#include <stdio.h>
}

/*
 * Creates bit sequence for tests
 */
static bitbyte_seq *get_test_sequence() {
    // Creating new bit sequence
    BYTE *bytes = (BYTE *)malloc(2);
    bytes[0] = 7;
    bytes[1] = 7;
    return bitbyte_new(bytes, 16);
}

/*
 * bitbyte sequence constructor test (16 bit / 2 byte)
 */
TEST(bitbyte_seq, constructor_16_2) {
    // Creating test sequence
    bitbyte_seq *b = get_test_sequence();

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(b), 16);
    ASSERT_EQ(bitbyte_get_size_byte(b), 2);
    ASSERT_EQ(bitbyte_get_byte(b, 0), 7);
    ASSERT_EQ(bitbyte_get_byte(b, 1), 7);

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * bitbyte sequence constructor test (6 bit / 1 byte)
 */
TEST(bitbyte_seq, constructor_6_1) {
    // Creating test sequence
    bitbyte_seq *b = bitbyte_zero(6);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(b), 6);
    ASSERT_EQ(bitbyte_get_size_byte(b), 1);
    ASSERT_EQ(bitbyte_get_byte(b, 0), 0);

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * bitbyte sequence constructor test (55 bit / 7 byte)
 */
TEST(bitbyte_seq, constructor_55_8) {
    // Creating test sequence
    bitbyte_seq *b = bitbyte_zero(55);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(b), 55);
    ASSERT_EQ(bitbyte_get_size_byte(b), 7);
    for (int i = 0; i < bitbyte_get_size_byte(b); i++) {
        ASSERT_EQ(bitbyte_get_byte(b, i), 0);
    }

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * bit sequence bit getter test
 */
TEST(bitbyte_seq, bitgetter) {
    // Creating test sequence
    bitbyte_seq *b = get_test_sequence();

    // Running getter
    BYTE actual[16];
    for (int i = 0; i < 16; i++) {
        actual[i] = bitbyte_get_bit(b, i);
    }

    // Asserting
    BYTE expected[16] = {0, 0, 0, 0, 0, 1, 1, 1,
                         0, 0, 0, 0, 0, 1, 1, 1};
    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(actual[i], expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * bit sequence bit setter test
 */
TEST(bitbyte_seq, bitsetter) {
    // Creating test sequence
    bitbyte_seq *b = get_test_sequence();

    // Setting specific bits
    bitbyte_set_bit(b, 4, 1);
    bitbyte_set_bit(b, 14, 0);

    // Asserting
    ASSERT_EQ(bitbyte_get_bit(b, 4), 1);
    ASSERT_EQ(bitbyte_get_bit(b, 14), 0);

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * left shift test
 */
TEST(bitbyte_seq, single_leftshift) {
    // Creating special test sequence
    BYTE *bytes = (BYTE *)malloc(2);
    bytes[0] = 0;
    bytes[1] = 1;
    bitbyte_seq *b = bitbyte_new(bytes, 16);

    // Shifting
    bitbyte_left_shift(b);

    // Asserting
    for (int i = 0; i < bitbyte_get_size_bit(b); i++) {
        printf("%i", bitbyte_get_bit(b, i));
    }
    ASSERT_EQ(bitbyte_get_bit(b, 14), 1);

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * multiple left shift test
 */
TEST(bitbyte_seq, multiple_leftshift) {
    // Creating special test sequence
    BYTE *bytes = (BYTE *)malloc(2);
    bytes[0] = 0;
    bytes[1] = 1;
    bitbyte_seq *b = bitbyte_new(bytes, 16);

    // Shifting
    bitbyte_left_shift_m(b, 2);

    // Asserting
    for (int i = 0; i < bitbyte_get_size_bit(b); i++) {
        printf("%i", bitbyte_get_bit(b, i));
    }
    ASSERT_EQ(bitbyte_get_bit(b, 13), 1);

    // Deallocating
    b = bitbyte_free(b);
    ASSERT_EQ(NULL, b);
}

/*
 * bitbyte_XOR test
 */
TEST(bitbyte_seq, XOR) {
    // Creating special test sequences
    BYTE *bytes1 = (BYTE *)malloc(2);
    bytes1[0] = 128;
    bytes1[1] = 7;
    BYTE *bytes2 = (BYTE *)malloc(2);
    bytes2[0] = 0;
    bytes2[1] = 7;
    bitbyte_seq *b1 = bitbyte_new(bytes1, 16);
    bitbyte_seq *b2 = bitbyte_new(bytes2, 16);

    // bitbyte_XOR
    bitbyte_seq *result = bitbyte_XOR(b1, b2);

    // ASSERTING
    for (int i = 0; i < bitbyte_get_size_bit(result); i++) {
        printf("%i", bitbyte_get_bit(result, i));
    }
    ASSERT_EQ(bitbyte_get_bit(result, 0), 1);
    for (int i = 1; i < bitbyte_get_size_bit(result); i++) {
        ASSERT_EQ(bitbyte_get_bit(result, i), 0);
    }

    // Deallocating
    b1 = bitbyte_free(b1);
    b2 = bitbyte_free(b2);
    result = bitbyte_free(result);
}

/*
 * Write bitbyte_seq test
 */
TEST(bitbyte_seq, write_read){
    // Creating test sequence
    bitbyte_seq *b = get_test_sequence();

    // Writing
    FILE *f = fopen("test_seq.dat", "wb");
    bitbyte_write(f, b);

    // Deallocating
    fclose(f);
    b = bitbyte_free(b);

    // Reading
    f = fopen("test_seq.dat", "rb");
    bitbyte_read(f, &b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(b), 16);
    ASSERT_EQ(bitbyte_get_size_byte(b), 2);
    for (int i = 0; i < bitbyte_get_size_byte(b); i++) {
        ASSERT_EQ(bitbyte_get_byte(b, i), 7);
    }

    // Deallocating
    fclose(f);
    b = bitbyte_free(b);
}