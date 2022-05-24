#include "gtest/gtest.h"

extern "C" {
#include "byte.h"
#include "permut/permut.h"
}

/*
 * permut_KP1 test
 */
TEST(permut, KP1) {
    // Creating initial key
    BYTE *temp = (BYTE *) malloc(8);
    temp[0] = 19;
    temp[1] = 52;
    temp[2] = 87;
    temp[3] = 121;
    temp[4] = 155;
    temp[5] = 188;
    temp[6] = 223;
    temp[7] = 241;
    bitbyte_seq *b = bitbyte_new(temp, 64);

    // Permutation
    bitbyte_seq *result = permut_KP1(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 56);
    ASSERT_EQ(bitbyte_get_size_byte(result), 7);
    BYTE expected[7] = { 240, 204, 170, 245, 86, 103, 143 };
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}

/*
 * permut_KP2 test
 */
TEST(permut, KP2) {
    // Creating initial C + D (56 bit)
    BYTE *temp = (BYTE *) malloc(7);
    temp[0] = 225;
    temp[1] = 153;
    temp[2] = 85;
    temp[3] = 250;
    temp[4] = 172;
    temp[5] = 207;
    temp[6] = 30;
    bitbyte_seq *b = bitbyte_new(temp, 56);

    // Permutation
    bitbyte_seq *result = permut_KP2(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 48);
    ASSERT_EQ(bitbyte_get_size_byte(result), 6);
    BYTE expected[6] = { 27, 2, 239, 252, 112, 114};
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}

/*
 * Initial permutation test
 */
TEST(permut, IP) {
    // Creating initial block
    BYTE *temp = (BYTE *) malloc(8);
    temp[0] = 1;
    temp[1] = 35;
    temp[2] = 69;
    temp[3] = 103;
    temp[4] = 137;
    temp[5] = 171;
    temp[6] = 205;
    temp[7] = 239;
    bitbyte_seq *b = bitbyte_new(temp, 64);

    // Permutation
    bitbyte_seq *result = permut_IP(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 64);
    ASSERT_EQ(bitbyte_get_size_byte(result), 8);
    BYTE expected[8] = { 204, 0, 204, 255, 240, 170, 240, 170};
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}

/*
 * Expansion test
 */
TEST(permut, expansion) {
    // Creating initial block
    BYTE *temp = (BYTE *) malloc(4);
    temp[0] = 240;
    temp[1] = 170;
    temp[2] = 240;
    temp[3] = 170;
    bitbyte_seq *b = bitbyte_new(temp, 32);

    // Permutation
    bitbyte_seq *result = permut_E(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 48);
    ASSERT_EQ(bitbyte_get_size_byte(result), 6);
    BYTE expected[6] = { 122, 21, 85, 122, 21, 85 };
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}

/*
 * Permutation P test
 */
TEST(permut, P) {
    // Creating initial block
    BYTE *temp = (BYTE *) malloc(4);
    temp[0] = 92;
    temp[1] = 130;
    temp[2] = 181;
    temp[3] = 151;
    bitbyte_seq *b = bitbyte_new(temp, 32);

    // Permutation
    bitbyte_seq *result = permut_P(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 32);
    ASSERT_EQ(bitbyte_get_size_byte(result), 4);
    BYTE expected[4] = { 35, 74, 169, 187 };
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}

/*
 * IP_1 permutation test
 */
TEST(permut, IP_1) {
    // Creating initial block
    BYTE *temp = (BYTE *) malloc(8);
    temp[0] = 10;
    temp[1] = 76;
    temp[2] = 217;
    temp[3] = 149;
    temp[4] = 67;
    temp[5] = 66;
    temp[6] = 50;
    temp[7] = 52;
    bitbyte_seq *b = bitbyte_new(temp, 64);

    // Permutation
    bitbyte_seq *result = permut_IP_1(b);

    // Asserting
    ASSERT_EQ(bitbyte_get_size_bit(result), 64);
    ASSERT_EQ(bitbyte_get_size_byte(result), 8);
    BYTE expected[8] = { 133, 232, 19, 84, 15, 10, 180, 5};
    for (int i = 0; i < bitbyte_get_size_byte(result); i++) {
        ASSERT_EQ(bitbyte_get_byte(result, i), expected[i]);
    }

    // Deallocating
    b = bitbyte_free(b);
    result = bitbyte_free(result);
}
