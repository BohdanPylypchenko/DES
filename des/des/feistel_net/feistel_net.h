#ifndef DES_DEMO_FEISTEL_NET_H
#define DES_DEMO_FEISTEL_NET_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

/*
 * Runs feistel net on given left and right bitbyte sequences with
 * provided subkey
 * Assigns new left and right bitbyte_seq pointers to n_left and n_right
 */
void des_feistel_net(bitbyte_seq *o_left, bitbyte_seq *o_right,
                     bitbyte_seq **n_left, bitbyte_seq **n_right,
                     bitbyte_seq *subkey);

#endif
