#include "gtest/gtest.h"

extern "C" {
#include "key/key.h"
#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <stdio.h>
}

/*
 * converts string literal to bitbyte_seq
 */
static bitbyte_seq *get_from_str(const char *str, const int size) {
    bitbyte_seq *result = bitbyte_zero(size);
    for (int i = 0; i < size; i++) {
        bitbyte_set_bit(result, i, str[i] - '0');
    }
    return result;
}

/*
 * Initial key generation test
 */
TEST(key, init) {
    // Generating key
    bitbyte_seq *key = key_init();

    // Asserting and Printing
    ASSERT_EQ(bitbyte_get_size_bit(key), 64);
    ASSERT_EQ(bitbyte_get_size_byte(key), 8);
    for (int i = 0; i < bitbyte_get_size_byte(key); i++) {
        printf("%i ", bitbyte_get_byte(key, i));
    }
    printf("\n");
    key = bitbyte_free(key);
    ASSERT_EQ(NULL, key);
}

/*
 * 16 subkeys generation test
 */
TEST(key, sub16) {
    // Creating initial key
    char str_init_key[65] = "0001001100110100010101110111100110011011101111001101111111110001";
    bitbyte_seq *init_key = get_from_str(str_init_key, 64);

    // Generating subkeys
    bitbyte_seq **subkeys = key_subkeys(init_key);

    // Asserting
    char *str_subkeys[16];
    str_subkeys[0] = "000110110000001011101111111111000111000001110010";
    str_subkeys[1] = "011110011010111011011001110110111100100111100101";
    str_subkeys[2] = "010101011111110010001010010000101100111110011001";
    str_subkeys[3] = "011100101010110111010110110110110011010100011101";
    str_subkeys[4] = "011111001110110000000111111010110101001110101000";
    str_subkeys[5] = "011000111010010100111110010100000111101100101111";
    str_subkeys[6] = "111011001000010010110111111101100001100010111100";
    str_subkeys[7] = "111101111000101000111010110000010011101111111011";
    str_subkeys[8] = "111000001101101111101011111011011110011110000001";
    str_subkeys[9] = "101100011111001101000111101110100100011001001111";
    str_subkeys[10] = "001000010101111111010011110111101101001110000110";
    str_subkeys[11] = "011101010111000111110101100101000110011111101001";
    str_subkeys[12] = "100101111100010111010001111110101011101001000001";
    str_subkeys[13] = "010111110100001110110111111100101110011100111010";
    str_subkeys[14] = "101111111001000110001101001111010011111100001010";
    str_subkeys[15] = "110010110011110110001011000011100001011111110101";
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < bitbyte_get_size_bit(subkeys[i]); j++) {
            EXPECT_EQ((BYTE)bitbyte_get_bit(subkeys[i], j), (BYTE)str_subkeys[i][j] - '0');
        }
    }

    // Deallocating
    init_key = bitbyte_free(init_key);
    for (int i = 0; i < 16; i++) {
        bitbyte_free(subkeys[i]);
    }
    free(subkeys);
}
