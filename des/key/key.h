#ifndef DES_DEMO_KEY_H
#define DES_DEMO_KEY_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

/*
 * Generates initial __64__ bit key
 */
bitbyte_seq *key_init();

/*
 * Creates 16 subkeys 48 bit each from 56 bit key
 */
bitbyte_seq **key_subkeys(const bitbyte_seq *key64);

#endif
