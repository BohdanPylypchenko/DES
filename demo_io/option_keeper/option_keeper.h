#ifndef DES_DEMO_OPTION_KEEPER_H
#define DES_DEMO_OPTION_KEEPER_H

#include <stdio.h>

/*
 * encrypt/decrypt mode enum
 */
typedef enum mode {
    encrypt,
    decrypt
} mode;

/*
 * option_keeper struct declaration
 */
typedef struct option_keeper option_keeper;

/*
 * empty option_keeper struct constructor
 */
option_keeper *new_option_keeper();

/*
 * mode getter
 */
mode get_mode(option_keeper *o);

/*
 * mode setter
 */
mode set_mode(option_keeper *o, mode m);

/*
 * input file getter
 */
FILE *get_input_file(option_keeper *o);

/*
 * input file setter
 */
FILE *set_input_file(option_keeper *o, FILE *input_file);

/*
 * output file getter
 */
FILE *get_output_file(option_keeper *o);

/*
 * output file setter
 */
FILE *set_output_file(option_keeper *o, FILE *output_file);

/*
 * key file getter
 */
FILE *get_key_file(option_keeper *o);

/*
 * key file setter
 */
FILE *set_key_file(option_keeper *o, FILE *key_file);

/*
 * random key flag getter
 */
int get_rand_key_flag(option_keeper *o);

/*
 * random key flag setter
 */
int set_rand_key_flag(option_keeper *o, int key_flag);

/*
 * Prints option_keeper to stdout
 */
void print_option_keeper(option_keeper *o);

/*
 * option_keeper deallocator
 */
option_keeper *free_option_keeper(option_keeper *o);

#endif
