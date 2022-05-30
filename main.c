#include "demo_io/io_utils/io_utils.h"
#include "demo_io/option_keeper/option_keeper.h"
#include "demo/demo_run.h"

#include <stdio.h>
#include <malloc.h>

// Global option_keeper instance
option_keeper *o;

void help_msg() {
    printf("Enter 'q' to quit\n");
    printf("Enter 'i' to set input file\n");
    printf("Enter 'k' to set key file\n");
    printf("Enter 'o' to set out file\n");
    printf("Enter 'r' to toggle rand key flag\n");
    printf("Enter 'c' to convert existing file to bitbyte_seq file\n");
    printf("Enter 'E' to set encrypt mode\n");
    printf("Enter 'D' to set decrypt mode\n");
    printf("Enter 'R' to run DES\n");
}

char *get_user_mode() {
    int run = 1;
    char *result;
    char *action;
    while (run) {
        action = input("Enter 1 to open with 'rb+'\nEnter 2 to open with 'wb+':");
        switch (action[0]) {
            case '1':
                result = READ_WRITE_MODE_KEEP;
                run = 0;
                break;
            case '2':
                result = READ_WRITE_MODE_OVERRIDE;
                run = 0;
                break;
            default:
                printf("Wrong input\n");
                break;
        }
        free(action);
    }
    return result;
}

void set_user_input_file() {
    char *path = input("Enter input file path:");
    FILE *f = fopen(path, get_user_mode());
    if (f == NULL) {
        printf("Error: can't open input file\n");
        free(path);
        return;
    }
    if (get_input_file(o) != NULL) {
        fclose(get_input_file(o));
    }
    set_input_file(o, f);
    free(path);
}

void set_user_key_file() {
    char *path = input("Enter key file path:");
    FILE *f = fopen(path, get_user_mode());
    if (f == NULL) {
        printf("Error: can't open key file\n");
        free(path);
        return;
    }
    if (get_key_file(o) != NULL) {
        fclose(get_key_file(o));
    }
    set_key_file(o, f);
    free(path);
}

void set_user_output_file() {
    char *path = input("Enter output file path:");
    FILE *f = fopen(path, get_user_mode());
    if (f == NULL) {
        printf("Error: can't open output file\n");
        free(path);
        return;
    }
    if (get_output_file(o) != NULL) {
        fclose(get_output_file(o));
    }
    set_output_file(o, f);
    free(path);
}

void toggle_rand_key_flag() {
    set_rand_key_flag(o, !get_rand_key_flag(o));
}

void convert_call() {
    char *origin_file_name = input("Enter origin file name:");
    char *bitbyte_file_name = input("Enter bitbyte file name:");
    convert_from_file_to_bitbyte_seq_file(origin_file_name, bitbyte_file_name);
    free(origin_file_name);
    free(bitbyte_file_name);
}

void set_encrypt_mode() {
    set_mode(o, encrypt);
}

void set_decrypt_mode() {
    set_mode(o, decrypt);
}

int main() {
    // Initializing option_keeper
    o = new_option_keeper();

    // Endless cycle
    int run = 1;
    while(run) {
        help_msg();

        printf("Current state:\n");
        print_option_keeper(o);

        char *action = input("Enter action:");
        switch (action[0]) {
            case 'q':
                run = 0;
                break;
            case 'i':
                set_user_input_file();
                break;
            case 'k':
                set_user_key_file();
                break;
            case 'o':
                set_user_output_file();
                break;
            case 'r':
                toggle_rand_key_flag();
                break;
            case 'c':
                convert_call();
                break;
            case 'E':
                set_encrypt_mode();
                break;
            case 'D':
                set_decrypt_mode();
                break;
            case 'R':
                demo_run(o);
                o = free_option_keeper(o);
                o = new_option_keeper();
                break;
            default:
                printf("Wrong input\n");
                break;
        }

        free(action);
    }

    // Returning
    return 0;
}
