#include "test_utils.h"

/*
 * bitbyte from str implementation
 */
bitbyte_seq *get_from_str(const char *str, const int size) {
    bitbyte_seq *result = bitbyte_zero(size);
    for (int i = 0; i < size; i++) {
        bitbyte_set_bit(result, i, str[i] - '0');
    }
    return result;
}
