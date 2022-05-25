#include "key.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "permut/permut.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"

#include "sodium.h"

// defines left shift count for each subkey iteration
static const SHIFT[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

/*
 * Initial key generator implementation
 */
bitbyte_seq *key_init() {
    // Initializing sodium
    if (sodium_init() < 0) { return NULL; }

    // Allocating memory
    BYTE *keybyte = (BYTE *) malloc(8);

    // Generating
    randombytes_buf(keybyte, 8);

    // Returning
    return bitbyte_new(keybyte, 64);
}

/*
 * Subkeys generator implementation
 */
bitbyte_seq **key_subkeys(const bitbyte_seq *key64) {
    // KP1 permutation
    bitbyte_seq *key56 = permut_KP1(key64);

    // Half split
    bitbyte_seq **cd = bitbyte_split(key56, 2);

    // Cycling
    bitbyte_seq **subkeys = (bitbyte_seq **) malloc(16 * sizeof(bitbyte_seq *));
    bitbyte_seq *temp;
    for (int i = 0; i < 16; i++) {
        // Shifting
        bitbyte_left_shift_m(cd[0], SHIFT[i]);
        bitbyte_left_shift_m(cd[1], SHIFT[i]);

        // Joining in temp
        temp = bitbyte_join(cd, 2);

        // Final permutation
        subkeys[i] = permut_KP2(temp);

        // Free temp
        temp = bitbyte_free(temp);
    }

    // Free more
    key56 = bitbyte_free(key56);
    cd[0] = bitbyte_free(cd[0]);
    cd[1] = bitbyte_free(cd[1]);
    free(cd);

    // Returning
    return subkeys;
}
