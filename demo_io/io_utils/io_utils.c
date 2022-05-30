#include "io_utils.h"

#include "bitbyte/bitbyte_seq/bitbyte_seq.h"
#include "bitbyte/bitbyte_io/bitbyte_io.h"
#include "byte.h"

#include <stdio.h>
#include "sys/stat.h"
#include <malloc.h>

/*
 * file to bitbyte_seq file convertor implementation
 */
void convert_from_file_to_bitbyte_seq_file(const char *origin_file_name,
                                           const char *bitbyte_file_name) {
    // Obtaining file info
    struct stat f_info;
    stat(origin_file_name, &f_info);

    // Creating bibyte_seq with file content
    BYTE *bitbyte = (BYTE *) malloc(f_info.st_size);
    FILE *f = fopen(origin_file_name, READ_MODE);
    fread(bitbyte, 1, f_info.st_size, f);
    bitbyte_seq *b = bitbyte_new(bitbyte, f_info.st_size * 8);

    // Closing original file
    fclose(f);

    // Writing created bitbyte_seq
    f = fopen(bitbyte_file_name, WRITE_MODE);
    bitbyte_write(f, b);

    // Closing file
    fclose(f);

    // Deallocating
    b = bitbyte_free(b);
}

/*
 * stdin \n input reader implementation
 */
char *input(const char *msg) {
    // Printing given msg
    printf("%s\n", msg);

    char *result = (char *) malloc(1);
    char buff = NULL;

    int i = 2;
    while ((buff = getchar()) != '\n') {
        // Reallocating
        result = (char *) realloc(result, i);

        // Assigning buffer to last result char
        result[i - 2] = buff;

        // Incrementing i
        i++;
    }

    // Adding zero char to string end
    result[i - 2] = '\0';

    // Returning
    return result;
}

/*
 * Converts bytes of bitbyte_seq to file
 */
void convert_bytes_to_file(FILE *f_b, bitbyte_seq *b) {
    fwrite(bitbyte_get_ptr(b), 1, bitbyte_get_size_byte(b), f_b);
}