#include "gtest/gtest.h"

extern "C" {
#include "test_utils/test_utils.h"

#include "des.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "key/key.h"

#include <malloc.h>
}

/*
 * DES algorithm test
 */
TEST(des_t, des_alrogithm) {
    // Message to run DES with
    char str_origin[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    bitbyte_seq *origin = get_from_str(str_origin, 64);

    // Creating initial key
    char str_key[65] = "0001001100110100010101110111100110011011101111001101111111110001";
    bitbyte_seq *key = get_from_str(str_key, 64);

    // Creating subkeys
    bitbyte_seq **subkeys = key_subkeys(key);

    // Running DES
    bitbyte_seq *encrypted = des(origin, subkeys);

    // Asserting
    char str_expected[65] = "1000010111101000000100110101010000001111000010101011010000000101";
    for (int i = 0; i < 64; i++) {
        ASSERT_EQ(bitbyte_get_bit(encrypted, i), (BYTE)str_expected[i] - '0');
    }

    // Deallocating
    origin = bitbyte_free(origin);
    key = bitbyte_free(key);
    for (int i = 0; i < 16; i++) {
        bitbyte_free(subkeys[i]);
    }
    free(subkeys);
    encrypted = bitbyte_free(encrypted);
}

/*
 * DES encryption test
 */
TEST(des_t, des_encrypt) {
    // Message to run DES with
    char str_origin[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    bitbyte_seq *origin = get_from_str(str_origin, 64);

    // Creating initial key
    char str_key[65] = "0001001100110100010101110111100110011011101111001101111111110001";
    bitbyte_seq *key = get_from_str(str_key, 64);

    // Encrypting
    bitbyte_seq *encrypted = des_encrypt(origin, key);

    // Asserting
    char str_expected[65] = "1000010111101000000100110101010000001111000010101011010000000101";
    for (int i = 0; i < 64; i++) {
        ASSERT_EQ(bitbyte_get_bit(encrypted, i), (BYTE)str_expected[i] - '0');
    }

    // Deallocating
    origin = bitbyte_free(origin);
    key = bitbyte_free(key);
    encrypted = bitbyte_free(encrypted);
}

/*
 * DES decryption test
 */
TEST(des_t, decryption) {
    // Getting encrypted message
    char str_encrypted[65] = "1000010111101000000100110101010000001111000010101011010000000101";
    bitbyte_seq *encrypted = get_from_str(str_encrypted, 64);

    // Getting key
    char str_key[65] = "0001001100110100010101110111100110011011101111001101111111110001";
    bitbyte_seq *key = get_from_str(str_key, 64);

    // Decrypting
    bitbyte_seq *decrypted = des_decrypt(encrypted, key);

    // Asserting
    char str_expected[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    for (int i = 0; i < 64; i++) {
        ASSERT_EQ(bitbyte_get_bit(decrypted, i), (BYTE)str_expected[i] - '0');
    }

    // Deallocating
    encrypted = bitbyte_free(encrypted);
    key = bitbyte_free(key);
    decrypted = bitbyte_free(decrypted);
}
