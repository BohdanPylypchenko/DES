#include "feistel_net.h"

#include "des/f_func/f_func.h"
#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"

/*
 * feistel net implementation
 */
void des_feistel_net(bitbyte_seq *o_left, bitbyte_seq *o_right,
                     bitbyte_seq **n_left, bitbyte_seq **n_right,
                     bitbyte_seq *subkey) {
    // next <- == original ->
    *n_left = bitbyte_clone(o_right);

    // Running f function on original -> part
    bitbyte_seq *f = des_f_func(o_right, subkey);

    // next -> = original <- xor f(original ->, subkey)
    *n_right = bitbyte_XOR(o_left, f);

    // Deallocating
    f = bitbyte_free(f);
}
