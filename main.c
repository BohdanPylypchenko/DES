#include "byte.h"

#include <stdio.h>
#include <limits.h>

/** Shift an array right.
 * @param ar The array to shift.
 * @param size The number of array elements.
 * @param shift The number of bits to shift.
 */
void shift_right(BYTE *ar, int size, int shift)
{
    int carry = 0;                              // Clear the initial carry bit.
    while (shift--) {                           // For each bit to shift ...
        for (int i = 0; i < size; i++) {   // For each element of the array from high to low ...
            int next = (ar[i] & 1) ? 0x80 : 0;  // ... if the low bit is set, set the carry bit.
            ar[i] = carry | (ar[i] << 1);       // Shift the element one bit left and addthe old carry.
            carry = next;                       // Remember the old carry for next time.
        }
    }
}

void shiftl(void *object, size_t size)
{
    unsigned char *byte;
    for ( byte = object; size--; ++byte )
    {
        unsigned char bit = 0;
        if ( size )
        {
            bit = byte[1] & (1 << (CHAR_BIT - 1)) ? 1 : 0;
        }
        *byte <<= 1;
        *byte  |= bit;
    }
}

int main() {
    BYTE a[2] = { 0, 1 };
    printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(a[0]));
    printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(a[1]));

    //shift_right(a, 2, 2);
    for (int i = 0; i < 2; i++) {
        shiftl(&a, 2);
    }

    printf("\n");
    printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(a[0]));
    printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(a[1]));

    return 0;
}
