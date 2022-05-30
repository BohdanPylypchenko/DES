#include "gtest/gtest.h"

extern "C" {
#include "byte.h"

#include <malloc.h>
}

/*
 * Bit getter test
 */
TEST(mybyte, getter) {
    // Creating initial BYTE
    BYTE b = 7;

    // Expected result
    BYTE expected[8] = {0, 0, 0, 0, 0, 1, 1, 1};

    // Running getter
    BYTE actual[8];
    for (int i = 0; i < 8; i++) {
        actual[i] = GET_LNB(b, i);
    }

    // Asserting
    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(expected[i], actual[i]);
    }
}

/*
 * Bit setter test
 */
TEST(mybyte, setter) {
    // Creating initial BYTE
    BYTE b = 7;

    // Setting 2nd bit to 1
    SET_LNB(b, 2, 1);

    // Asserting
    ASSERT_EQ(1, GET_LNB(b, 2));
}
