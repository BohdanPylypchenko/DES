#include "f_func.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "permut/permut.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"
#include "sbox/sbox.h"

#include <malloc.h>

bitbyte_seq *des_f_func(const bitbyte_seq *r, const bitbyte_seq *subkey) {
    // Expansion
    bitbyte_seq *expansion = permut_E(r);

    // XOR
    bitbyte_seq *xor = bitbyte_XOR(expansion, subkey);

    // sboxes
    //bitbyte_seq **xor_split = bitbyte_split(xor, 8);
    bitbyte_seq **xor_split;
    bitbyte_split(xor, 6, &xor_split);
    bitbyte_seq *sboxed[8];
    sboxed[0] = sbox1(xor_split[0]);
    sboxed[1] = sbox2(xor_split[1]);
    sboxed[2] = sbox3(xor_split[2]);
    sboxed[3] = sbox4(xor_split[3]);
    sboxed[4] = sbox5(xor_split[4]);
    sboxed[5] = sbox6(xor_split[5]);
    sboxed[6] = sbox7(xor_split[6]);
    sboxed[7] = sbox8(xor_split[7]);

    // Joining
    bitbyte_seq *sbox_joined = bitbyte_join(sboxed, 8);

    // P permutation
    bitbyte_seq *p = permut_P(sbox_joined);

    // Deallocation
    expansion = bitbyte_free(expansion);
    xor = bitbyte_free(xor);
    for (int i = 0; i < 8; i++) {
        bitbyte_free(xor_split[i]);
        bitbyte_free(sboxed[i]);
    }
    free(xor_split);
    sbox_joined = bitbyte_free(sbox_joined);

    // Returning
    return p;
}
