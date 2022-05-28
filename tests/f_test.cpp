#include "gtest/gtest.h"

extern "C" {
#include "des/f_func/f_func.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "test_utils/test_utils.h"
}

/*
 * des_f_func function test
 */
TEST(ffunc_call, test_all) {
    // R0 str
    char r0_str[33] = "11110000101010101111000010101010";

    // Getting R0 bitbyte from str
    bitbyte_seq *r0 = get_from_str(r0_str, 32);

    // subkey str
    char subk_str[49] = "000110110000001011101111111111000111000001110010";

    // Gettng subkey from str
    bitbyte_seq *subkey = get_from_str(subk_str, 48);

    // Running des_f_func function
    bitbyte_seq *f_out = des_f_func(r0, subkey);

    // Asserting
    char expected[33] = "00100011010010101010100110111011";
    for (int i = 0; i < 32; i++) {
        ASSERT_EQ(bitbyte_get_bit(f_out, i), (BYTE)expected[i] - '0');
    }

    // Deallocating
    r0 = bitbyte_free(r0);
    subkey = bitbyte_free(subkey);
    f_out = bitbyte_free(f_out);
}
