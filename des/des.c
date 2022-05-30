#include "des.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "permut/permut.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"
#include "des/feistel_net/feistel_net.h"
#include "key/key.h"

#include <malloc.h>

/*
 * DES algorithm implementation
 */
bitbyte_seq *des(bitbyte_seq *origin, bitbyte_seq *subkeys[16]) {
    // Initial permutation
    bitbyte_seq *ip = permut_IP(origin);

    // Half split
    bitbyte_seq **parts;
    bitbyte_split(ip, 32, &parts);
    bitbyte_seq *l0 = parts[0];
    bitbyte_seq *r0 = parts[1];

    // 16 times feistel net
    bitbyte_seq *l, *r;
    for (int i = 0; i < 16; i++) {
        // Running feistel
        des_feistel_net(l0, r0,
                        &l, &r,
                        subkeys[i]);

        // Deallocating old
        l0 = bitbyte_free(l0);
        r0 = bitbyte_free(r0);

        // Reassigning l0 and r0 with new
        l0 = l;
        r0 = r;
    }

    // Joining
    parts[0] = r;
    parts[1] = l;
    bitbyte_seq *rl = bitbyte_join(parts, 2);

    // Final permutation
    bitbyte_seq *encrypted = permut_IP_1(rl);

    // Deallocating
    ip = bitbyte_free(ip);
    rl = bitbyte_free(rl);
    l = bitbyte_free(l);
    r = bitbyte_free(r);
    free(parts);

    // Returning
    return encrypted;
}

/*
 * DES encryption implementation
 */
bitbyte_seq *des_encrypt(bitbyte_seq *origin, bitbyte_seq *key) {
    // Creating subkeys
    bitbyte_seq **subkeys = key_subkeys(key);

    // Running DES
    bitbyte_seq *encrypted = des(origin, subkeys);

    // Deallocating
    for (int i = 0; i < 16; i++) {
        bitbyte_free(subkeys[i]);
    }
    free(subkeys);

    // Returning
    return encrypted;
}

/*
 * DES decryption implementation
 */
bitbyte_seq *des_decrypt(bitbyte_seq *encrypted, bitbyte_seq *key) {
    // Creating subkeys
    bitbyte_seq **subkeys = key_subkeys(key);

    // Inverting
    bitbyte_seq *temp;
    for (int i = 0; i < 8; i++) {
        temp = subkeys[i];
        subkeys[i] = subkeys[15 - i];
        subkeys[15 - i] = temp;
    }

    // Running DES
    bitbyte_seq *decrypted = des(encrypted, subkeys);

    // Deallocating
    for (int i = 0; i < 16; i++) {
        bitbyte_free(subkeys[i]);
    }
    free(subkeys);

    // Returning
    return decrypted;
}
