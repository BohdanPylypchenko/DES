#include "gtest/gtest.h"

extern "C" {
#include "test_utils/test_utils.h"

#include "des/feistel_net/feistel_net.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
}

/*
 * One feistel net run test
 */
TEST(feistel, one_run) {
    // String input
    char str_l0[33] = "11001100000000001100110011111111";
    char str_r0[33] = "11110000101010101111000010101010";
    char str_subkey[49] = "000110110000001011101111111111000111000001110010";

    // Getting bitbyte_seq from strings
    bitbyte_seq *l0 = get_from_str(str_l0, 32);
    bitbyte_seq *r0 = get_from_str(str_r0, 32);
    bitbyte_seq *subkey = get_from_str(str_subkey, 48);

    // Running feistel net
    bitbyte_seq *l1, *r1;
    des_feistel_net(l0, r0,
                    &l1, &r1,
                    subkey);

    // Asserting
    char str_l1[33] = "11110000101010101111000010101010";
    char str_r1[33] = "11101111010010100110010101000100";
    for (int i = 0; i < 32; i++) {
        ASSERT_EQ(bitbyte_get_bit(l1, i), (BYTE)str_l1[i] - '0');
        ASSERT_EQ(bitbyte_get_bit(r1, i), (BYTE)str_r1[i] - '0');
    }

    // Deallocating
    l0 = bitbyte_free(l0);
    l1 = bitbyte_free(l1);
    r0 = bitbyte_free(r0);
    r1 = bitbyte_free(r1);
    subkey = bitbyte_free(subkey);
}
