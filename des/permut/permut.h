#ifndef DES_DEMO_PERMUT_H
#define DES_DEMO_PERMUT_H

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

/*
 * Initial permutation
 */
bitbyte_seq *permut_IP(const bitbyte_seq *original);

/*
 * Final permutation
 */
bitbyte_seq *permut_IP_1(const bitbyte_seq *original);

/*
 * Key permutation 1
 */
bitbyte_seq *permut_KP1(const bitbyte_seq *original);

/*
 * Key permutation 2
 */
bitbyte_seq *permut_KP2(const bitbyte_seq *original);

/*
 * Expansion permutation
 */
bitbyte_seq *permut_E(const bitbyte_seq *original);

/*
 * P permutation
 */
bitbyte_seq *permut_P(const bitbyte_seq *original);

#endif
