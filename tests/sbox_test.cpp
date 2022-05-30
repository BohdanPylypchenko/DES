#include "gtest/gtest.h"

extern "C" {
#include "test_utils/test_utils.h"

#include "sbox/sbox.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"
}

/*
 * Whole sboxes permutation test
 */
TEST(sbox, test_all) {
    // Original input string
    char in_str[49] = "011000010001011110111010100001100110010100100111";

    // Getting bitbyte_seq from str
    bitbyte_seq *in = get_from_str(in_str, 48);

    // Splitting
    bitbyte_seq **parts;
    bitbyte_split(in, 6, &parts);

    // sboxing
    bitbyte_seq *sboxed[8];
    sboxed[0] = sbox1(parts[0]);
    sboxed[1] = sbox2(parts[1]);
    sboxed[2] = sbox3(parts[2]);
    sboxed[3] = sbox4(parts[3]);
    sboxed[4] = sbox5(parts[4]);
    sboxed[5] = sbox6(parts[5]);
    sboxed[6] = sbox7(parts[6]);
    sboxed[7] = sbox8(parts[7]);

    // Joining
    bitbyte_seq *result = bitbyte_join(sboxed, 8);

    // Asserting
    char expected[33] = "01011100100000101011010110010111";
    for (int i = 0; i < 32; i++) {
        ASSERT_EQ(bitbyte_get_bit(result, i), (BYTE)expected[i] - '0');
    }

    // Deallocating
    in = bitbyte_free(in);
    for (int i = 0; i < 8; i++) {
        bitbyte_free(parts[i]);
        bitbyte_free(sboxed[i]);
    }
    free(parts);
    result = bitbyte_free(result);
}
