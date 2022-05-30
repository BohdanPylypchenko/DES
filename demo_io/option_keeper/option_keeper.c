#include "option_keeper.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

/*
 * Private variables (mainly for print)
 */
static int MAXSIZE = 0xFFF;
static char proclnk[0xFFF];
static char filename[0xFFF];
static int fno;
static ssize_t r;

/*
 * demo option_keeper structure
 */
typedef struct option_keeper {
    // mode type
    mode m;

    // input, output files
    FILE *input, *output;

    // key file (read/write)
    FILE *key;

    // random key flag
    int rand_key_flag;
} option_keeper;

/*
 * Private file info printer
 */
static void print_file_info(FILE *f);

/*
 * empty option_keeper struct constructor
 */
option_keeper *new_option_keeper() {
    // Allocating memory
    option_keeper *o = (option_keeper *) malloc(sizeof(option_keeper));

    // Assigning default values
    o->m = encrypt;
    o->input = NULL;
    o->output = NULL;
    o->key = NULL;
    o->rand_key_flag = 1;

    // Returning
    return o;
}

/*
 * mode getter
 */
mode get_mode(option_keeper *o) {
    return o->m;
}

/*
 * mode setter
 */
mode set_mode(option_keeper *o, mode m) {
    o->m = m;
}

/*
 * input file getter
 */
FILE *get_input_file(option_keeper *o) {
    return o->input;
}

/*
 * input file setter
 */
FILE *set_input_file(option_keeper *o, FILE *input_file) {
    o->input = input_file;
}

/*
 * output file getter
 */
FILE *get_output_file(option_keeper *o) {
    return o->output;
}

/*
 * output file setter
 */
FILE *set_output_file(option_keeper *o, FILE *output_file) {
    o->output = output_file;
}

/*
 * key file getter
 */
FILE *get_key_file(option_keeper *o) {
    return o->key;
}

/*
 * key file setter
 */
FILE *set_key_file(option_keeper *o, FILE *key_file) {
    o->key = key_file;
}

/*
 * random key flag getter
 */
int get_rand_key_flag(option_keeper *o) {
    return o->rand_key_flag;
}

/*
 * random key flag setter
 */
int set_rand_key_flag(option_keeper *o, int key_flag) {
    o->rand_key_flag = key_flag;
}

/*
 * stdout printer implementation
 */
void print_option_keeper(option_keeper *o) {
    printf("option_keeper struct at %p\n", o);
    printf("    mode: %s\n", (o->m == encrypt) ? ("encrypt") : ("decrypt"));
    printf("    input file:\n");
    print_file_info(o->input);
    printf("    key file:\n");
    print_file_info(o->key);
    printf("    output file:\n");
    print_file_info(o->output);
    printf("    rand key flag: %i\n", o->rand_key_flag);
}

/*
 * option_keeper deallocator implementation
 */
option_keeper *free_option_keeper(option_keeper *o) {
    // Close all files if not null
    if (o->input != NULL) {
        fclose(o->input);
    }
    if (o->output != NULL) {
        fclose(o->output);
    }
    if (o->key != NULL) {
        fclose(o->key);
    }

    // free option_keeper pointer
    free(o);

    // Returning NULL as success
    return NULL;
}

/*
 * Private file info printer implementation
 */
static void print_file_info(FILE *f) {
    if (f == NULL) {
        return;
    }
    fno = fileno(f);
    sprintf(proclnk, "/proc/self/fd/%d", fno);
    r = readlink(proclnk, filename, MAXSIZE);
    filename[r] = '\0';
    printf("    fp -> fno -> filename: %p -> %d -> %s\n",
           f, fno, filename);
}
