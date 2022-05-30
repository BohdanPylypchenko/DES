#include "demo_run.h"

#include "../demo_io/option_keeper/option_keeper.h"
#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "bitbyte/bitbyte_io/bitbyte_io.h"
#include "bitbyte/bitbyte_operator/bitbyte_operator.h"
#include "key/key.h"
#include "des.h"
#include "../demo_io/io_utils/io_utils.h"

#include <stdio.h>
#include <malloc.h>

/*
 * Demo encrypt declaration
 */
static int demo_encrypt(const FILE *f_msg, const FILE *f_key, const FILE *f_encrypted,
                        const int rand_key_flag);

/*
 * Demo decrypt declaration
 */
static int demo_decrypt(const FILE *f_encrypted, const FILE *f_key, const FILE *f_msg);

/*
 * Demo run implementation
 */
int demo_run(option_keeper *o) {
    // Checking mode
    if (get_mode(o) == encrypt) {
        return demo_encrypt(get_input_file(o),
                            get_key_file(o),
                            get_output_file(o),
                            get_rand_key_flag(o));
    } else {
        return demo_decrypt(get_input_file(o),
                            get_key_file(o),
                            get_output_file(o));
    }
}

/*
 * Demo encrypt implementation
 */
static int demo_encrypt(const FILE *f_msg, const FILE *f_key, const FILE *f_encrypted,
                        const int rand_key_flag) {
    // Reading msg
    bitbyte_seq *msg;
    bitbyte_read(f_msg, &msg);

    // Getting key
    bitbyte_seq *key;
    if (rand_key_flag == 1) {
        key = key_init();
    } else {
        bitbyte_read(f_key, &key);
    }

    // Splitting
    bitbyte_seq **parts_origin;
    int count = bitbyte_split(msg, 64, &parts_origin);

    // Encrypting
    bitbyte_seq **parts_encrypted = (bitbyte_seq **)malloc(count * sizeof(bitbyte_seq *));
    for (int i = 0; i < count; i++) {
        parts_encrypted[i] = des_encrypt(parts_origin[i], key);
    }

    // Joining
    bitbyte_seq *encrypted = bitbyte_join(parts_encrypted, count);

    // Writing key
    bitbyte_write(f_key, key);

    // Writing encrypted
    bitbyte_write(f_encrypted, encrypted);

    // Deallocating
    msg = bitbyte_free(msg);
    key = bitbyte_free(key);
    encrypted = bitbyte_free(encrypted);
    for (int i = 0; i < count; i++) {
        bitbyte_free(parts_origin[i]);
        bitbyte_free(parts_encrypted[i]);
    }
    free(parts_origin);
    free(parts_encrypted);

    // Returning
    return 0;
}

/*
 * Demo decrypt implementation
 */
static int demo_decrypt(const FILE *f_encrypted, const FILE *f_key, const FILE *f_msg) {
    // Reading encrypted
    bitbyte_seq *encrypted;
    bitbyte_read(f_encrypted, &encrypted);

    // Reading key
    bitbyte_seq *key;
    bitbyte_read(f_key, &key);

    // Splitting
    bitbyte_seq **parts_encrypted;
    int count = bitbyte_split(encrypted, 64, &parts_encrypted);

    // Decrypting
    bitbyte_seq **parts_origin = (bitbyte_seq **)malloc(count * sizeof(bitbyte_seq *));
    for (int i = 0; i < count; i++) {
        parts_origin[i] = des_decrypt(parts_encrypted[i], key);
    }

    // Joining
    bitbyte_seq *msg = bitbyte_join(parts_origin, count);

    // Writing msg
    convert_bytes_to_file(f_msg, msg);

    // Deallocating
    encrypted = bitbyte_free(encrypted);
    key = bitbyte_free(key);
    msg = bitbyte_free(msg);
    for (int i = 0; i < count; i++) {
        bitbyte_free(parts_origin[i]);
        bitbyte_free(parts_encrypted[i]);
    }
    free(parts_origin);
    free(parts_encrypted);

    // Returning
    return 0;
}
