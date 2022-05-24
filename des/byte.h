#ifndef DES_DEMO_BYTE_H
#define DES_DEMO_BYTE_H

/*
 * My BYTE definition
 */
#define BYTE unsigned char

/*
 * Byte nth bit getter
 */
#define GET_LNB(b, n) (b >> (7 - n)) & 1

/*
 * Byte nth bit setter
 */
#define SET_LNB(b, n, x) b ^= (-x ^ b) & (1 << (7 - n))

/*
 * Print BYTE in binary macros
 */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(BYTE)  \
  (BYTE & 0x80 ? '1' : '0'), \
  (BYTE & 0x40 ? '1' : '0'), \
  (BYTE & 0x20 ? '1' : '0'), \
  (BYTE & 0x10 ? '1' : '0'), \
  (BYTE & 0x08 ? '1' : '0'), \
  (BYTE & 0x04 ? '1' : '0'), \
  (BYTE & 0x02 ? '1' : '0'), \
  (BYTE & 0x01 ? '1' : '0')

#endif
