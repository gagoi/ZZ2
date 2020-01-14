#include <stdint.h>
#include <stdio.h>

unsigned lfsr1(void)
{
    uint8_t start_state = 0xACu;  /* Any nonzero start state will work. */
    uint8_t lfsr = start_state;
    uint8_t bit;                    /* Must be 16-bit to allow bit<<15 later in the code */
    unsigned period = 0;

    do
    {   /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
        bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) /* & 1u */;
        lfsr = (lfsr >> 1) | (bit << 15);
        ++period;
    }
    while (lfsr != start_state);

    return period;
}

int main()
{
    uint8_t test = 0xFFu;

    printf("%d\n", test);

    return 0;
}