#ifndef DES_DEMO_DES_H
#define DES_DEMO_DES_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

/*
 * Runs des algorithm on origin sequence
 * with given subkeys
 */
bitbyte_seq *des(bitbyte_seq *origin, bitbyte_seq *subkeys[16]);

/*
 * Encrypts given 8 byte block with given key
 */
bitbyte_seq *des_encrypt(bitbyte_seq *origin, bitbyte_seq *key);

/*
 * Decrypts given 8 byte block with given key
 */
bitbyte_seq *des_decrypt(bitbyte_seq *encrypted, bitbyte_seq *key);

#endif
